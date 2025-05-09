/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : r_drw_irq.c
 * Description  : This file defines the D/AVE D1 low-level driver IRQ setting functions.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>
#include "r_drw_base.h"
#include "r_drw_cfg.h"
#include "hal_data.h"

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
 #include "FreeRTOS.h"
 #include "semphr.h"
#elif (BSP_CFG_RTOS == 1)              // ThreadX
 #include "tx_api.h"
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DRW_PRV_IRQCTL_DLISTIRQ_ENABLE             (1U << 1)
#define DRW_PRV_IRQCTL_ENUMIRQ_CLEAR               (1U << 2)
#define DRW_PRV_IRQCTL_DLISTIRQ_CLEAR              (1U << 3)
#define DRW_PRV_IRQCTL_BUSIRQ_CLEAR                (1U << 5)
#define DRW_PRV_IRQCTL_ALLIRQ_DISABLE_AND_CLEAR    (DRW_PRV_IRQCTL_BUSIRQ_CLEAR | DRW_PRV_IRQCTL_DLISTIRQ_CLEAR | \
                                                    DRW_PRV_IRQCTL_ENUMIRQ_CLEAR)
#define DRW_PRV_IRQCTL_ALLIRQ_CLEAR_AND_DLISTIRQ_ENABLE                                           \
    (DRW_PRV_IRQCTL_BUSIRQ_CLEAR | DRW_PRV_IRQCTL_DLISTIRQ_CLEAR | DRW_PRV_IRQCTL_ENUMIRQ_CLEAR | \
     DRW_PRV_IRQCTL_DLISTIRQ_ENABLE)
#define DRW_PRV_STATUS_DLISTIRQ_TRIGGERED          (1U << 5)

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if (BSP_CFG_RTOS == 0)                // No RTOS
static volatile d1_int_t g_dlist_done = 0;
#elif (BSP_CFG_RTOS == 1)              // ThreadX
static TX_SEMAPHORE g_d1_queryirq_sem;
#elif (BSP_CFG_RTOS == 2)              // FreeRTOS
static SemaphoreHandle_t g_d1_queryirq_sem;
static StaticSemaphore_t g_d1_queryirq_sem_data;
#endif

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/
extern const uint8_t DRW_INT_IPL;

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup DRW_PRV Internal DRW Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void drw_int_isr(IRQn_Type const irq);

/*******************************************************************************************************************//**
 * Initializes DRW_INT.
 *
 * @param[in] handle    Pointer to the d1_device object.
 * @retval    0         The function returns 0 if the IRQ number is invalid.
 * @retval    1         The function returns 1 if DRW_INT is successfully initialized.
 **********************************************************************************************************************/
d1_int_t d1_initirq_intern (d1_device_flex * handle)
{
    d1_int_t ret = 0;

    if (DRW_CFG_INT_IRQ >= 0)
    {
        /* Clear all the D/AVE 2D IRQs and enable Display list IRQ. */
        R_DRW->IRQCTL = DRW_PRV_IRQCTL_ALLIRQ_CLEAR_AND_DLISTIRQ_ENABLE;

        /* Enable D/AVE 2D interrupt. */
        R_BSP_IrqCfgEnable((IRQn_Type) DRW_CFG_INT_IRQ, DRW_INT_IPL, handle);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

        /* Initialize semaphore for use in d1_queryirq() */
        g_d1_queryirq_sem = xSemaphoreCreateBinaryStatic(&g_d1_queryirq_sem_data);

        if (NULL != g_d1_queryirq_sem)
        {
            ret = 1;
        }
#elif (BSP_CFG_RTOS == 1)              // ThreadX

        /* Initialize semaphore for use in d1_queryirq() */
        if (TX_SUCCESS == tx_semaphore_create(&g_d1_queryirq_sem, (CHAR *) "g_d1_isr_semaphore", 0))
        {
            ret = 1;
        }
#else
        ret = 1;
#endif
    }

    return ret;
}

/*******************************************************************************************************************//**
 * De-initializes DRW_INT.
 *
 * @param[in] handle    Pointer to the d1_device object.
 * @retval    1         The function returns 1.
 **********************************************************************************************************************/
d1_int_t d1_shutdownirq_intern (d1_device_flex * handle)
{
    FSP_PARAMETER_NOT_USED(handle);

    /* Disable D/AVE 2D interrupt. */
    R_BSP_IrqDisable((IRQn_Type) DRW_CFG_INT_IRQ);

    /* Clear all the D/AVE 2D IRQs and disable Display list IRQ. */
    R_DRW->IRQCTL = DRW_PRV_IRQCTL_ALLIRQ_DISABLE_AND_CLEAR;

#if (BSP_CFG_RTOS == 2)                // FreeRTOS

    /* Delete semaphore */
    vSemaphoreDelete(g_d1_queryirq_sem);
#elif (BSP_CFG_RTOS == 1)              // ThreadX

    /* Delete semaphore */
    tx_semaphore_delete(&g_d1_queryirq_sem);
#endif

    return 1;
}

/*******************************************************************************************************************//**
 * This function waits for DRW_INT with timeout.
 *
 * @param[in] handle    Pointer to the d1_device object (Not used).
 * @param[in] irqmask   Interrupt ID (Not used. FSP only uses Display list IRQ).
 * @param[in] timeout   Timeout value.
 * @retval    0         The function returns 0 if the wait times out.
 * @retval    1         The function returns 1 if DRW_INT was detected.
 **********************************************************************************************************************/
d1_int_t d1_queryirq (d1_device * handle, d1_int_t irqmask, d1_int_t timeout)
{
    d1_int_t ret = 1;

    FSP_PARAMETER_NOT_USED(handle);
    FSP_PARAMETER_NOT_USED(irqmask);

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    BaseType_t err;

    /* Wait for dlist processing to complete. */
    /* d1_to_wait_forever (D2) == -1 == portMAX_DELAY (FreeRTOS), so just pass the raw timeout through. */
    err = xSemaphoreTake(g_d1_queryirq_sem, (uint32_t) timeout);

    /* If the wait timed out return 0. */
    if (pdPASS != err)
    {
        ret = 0;
    }
#elif (BSP_CFG_RTOS == 1)              // ThreadX

    /* Wait for dlist processing to complete. */
    /* d1_to_wait_forever (D2) == -1 == TX_WAIT_FOREVER (ThreadX), so just pass the raw timeout through. */
    if (TX_SUCCESS != tx_semaphore_get(&g_d1_queryirq_sem, (ULONG) timeout))
    {
        ret = 0;
    }
#else

    /* Wait for dlist processing to complete. */
    while (!g_dlist_done && timeout)
    {
        if (timeout != d1_to_wait_forever)
        {
            timeout--;
        }
    }

    /* If the wait timed out return 0. */
    if (!g_dlist_done)
    {
        ret = 0;
    }
    g_dlist_done = 0;
#endif

    return ret;
}

/*******************************************************************************************************************//**
 * @}
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Increments the dlist array pointer in indirect mode and indicates dlist completion in both modes.
 **********************************************************************************************************************/
void drw_int_isr (IRQn_Type const irq)
{
    FSP_CONTEXT_SAVE

    uint32_t int_status;

#if (BSP_CFG_RTOS == 2)                // FreeRTOS
    BaseType_t context_switch = pdFALSE;
#endif

    /* Get D/AVE 2D interrupt status. */
    int_status = R_DRW->STATUS;

    /* Clear all the D/AVE 2D interrupts (keep the Display list interrupt enable). */
    R_DRW->IRQCTL = DRW_PRV_IRQCTL_ALLIRQ_CLEAR_AND_DLISTIRQ_ENABLE;

    /* Display list interrupt? */
    if (int_status & DRW_PRV_STATUS_DLISTIRQ_TRIGGERED)
    {
#if DRW_CFG_USE_DLIST_INDIRECT
 #if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT)
        uint64_t pa;                   /* Physical Address */
        uint64_t va;                   /* Virtual Address */
 #endif

        /* Get handle from ISR context */
        d1_device_flex * p_context = (d1_device_flex *) R_FSP_IsrContextGet(irq);

        /* If indirect mode is enabled and there are more display lists left then continue with the next list */
        if ((p_context->dlist_indirect_enable) &&
            (NULL != (uint32_t *) (uintptr_t) *(p_context->pp_dlist_indirect_start)))
        {
            /* Start D/AVE 2D. */
 #if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT)
            va = (uint64_t) *(p_context->pp_dlist_indirect_start);
            R_MMU_VAtoPA(&g_mmu_ctrl, va, (void *) &pa);
            R_DRW->DLISTSTART = (uint32_t) pa;
 #else
            R_DRW->DLISTSTART = *(p_context->pp_dlist_indirect_start);
 #endif

            /* Get next display list start address. */
            p_context->pp_dlist_indirect_start = (uint32_t *) ((uint32_t **) (p_context->pp_dlist_indirect_start) + 1);
        }
        else
#endif
        {
#if (BSP_CFG_RTOS == 2)                // FreeRTOS

            /* Put semaphore */
            xSemaphoreGiveFromISR(g_d1_queryirq_sem, &context_switch);

            /* Pend a context switch at the end of this ISR, if necessary */
            portYIELD_FROM_ISR(context_switch);
#elif (BSP_CFG_RTOS == 1)              // ThreadX

            /* Put semaphore */
            tx_semaphore_ceiling_put(&g_d1_queryirq_sem, 1UL);
#else

            /* Increment dlist completion flag. */
            g_dlist_done++;
#endif
        }
    }
    else
    {
        /* Do nothing. */
    }

    /* Clear IRQ status. */
    R_BSP_IrqStatusClear(irq);

    FSP_CONTEXT_RESTORE
}

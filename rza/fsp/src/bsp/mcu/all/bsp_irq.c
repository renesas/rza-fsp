/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#include "bsp_gicv3.h"

#include "bsp_irq.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define R_BSP_GIC_LOWEST_INTERRUPT_PRIORITY    (0xF8)
#define R_BSP_GIC_INTID_1020                   (1020)
#define R_BSP_GIC_INTID_1023                   (1023)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/* This table is used to store the context in the ISR. */
void * gp_renesas_isr_context[BSP_ICU_VECTOR_MAX_ENTRIES];

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*****************************************************************************
 * external definitions
 *****************************************************************************/
extern fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES];
uint32_t            g_interrupt_nesting_count;
static uint32_t     route;

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 * Initialize interrupt controller.
 *
 * @retval       None
 **********************************************************************************************************************/
void bsp_irq_cfg (void)
{
    InitGicv3();

    route = R_BSP_GICR_GetRoute();
    g_interrupt_nesting_count = 0;

    /* Allow lowest priority interrupt */
    R_BSP_GICC_SetMaskLevel(R_BSP_GIC_LOWEST_INTERRUPT_PRIORITY);

    R_BSP_GICD_Enable(GICD_CTLR_EnableAll);

    /* Enable Interrupts */
    __enable_all_exception();

    R_BSP_GICR_SetClass(1);
}

/**********************************************************************************************************************
 * IRQ handler Function.
 * This function calls the interrupt function registered in the vector table.
 *
 * @retval        None.
 *********************************************************************************************************************/
void IRQ_ExecuteHandler (void)
{
    uint32_t       int_id;
    fsp_vector_t * p_vector;

    int_id = R_BSP_GICC_Get_IntIdGrp1();

    if (int_id < BSP_ICU_VECTOR_MAX_ENTRIES)
    {
        p_vector = &g_vector_table[int_id];
        if (p_vector)
        {
            (*p_vector)(int_id);
        }
    }

    R_BSP_GICC_SetEoiGrp1(int_id);
}

/**********************************************************************************************************************
 * FIQ handler Function.
 * This function calls the interrupt function registered in the vector table.
 *
 * @retval        None.
 *********************************************************************************************************************/
void FIQ_ExecuteHandler (void)
{
    uint32_t       int_id[2];
    uint32_t       aliased = 0;
    uint32_t       target_int_id;
    fsp_vector_t * p_vector;

    int_id[0]     = R_BSP_GICC_Get_IntIdGrp0();
    target_int_id = int_id[0];

    if ((R_BSP_GIC_INTID_1020 <= int_id[0]) && (int_id[0] <= R_BSP_GIC_INTID_1023))
    {
        int_id[1]     = R_BSP_GICC_Get_IntIdGrp1();
        aliased       = 1;
        target_int_id = int_id[1];

        if ((R_BSP_GIC_INTID_1020 <= int_id[1]) && (int_id[1] <= R_BSP_GIC_INTID_1023))
        {
            return;
        }
    }

    /* Enable nested interrupts */
    __enable_fiq();

    if (target_int_id < BSP_ICU_VECTOR_MAX_ENTRIES)
    {
        p_vector = &g_vector_table[target_int_id];
        if (p_vector)
        {
            (*p_vector)(target_int_id);
        }
    }

    if (0 == aliased)
    {
        R_BSP_GICC_SetEoiGrp0(int_id[0]);
    }
    else
    {
        R_BSP_GICC_SetEoiGrp1(int_id[1]);
    }
}

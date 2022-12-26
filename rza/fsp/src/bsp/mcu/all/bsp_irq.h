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

/** @} (end addtogroup BSP_MCU) */

#ifndef BSP_IRQ_H
#define BSP_IRQ_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include "bsp_gicv3.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_ICU_VECTOR_MAX_ENTRIES    (BSP_VECTOR_TABLE_MAX_ENTRIES - BSP_CORTEX_VECTOR_TABLE_ENTRIES)

#define CPU_CORE_NUMBER               1
#define GIC_INTERRUPT_NUMBER          512

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum bsp_irq_trigger_type_t
{
    INTC_TRIGGER_LEVEL = 0,
    INTC_TRIGGER_EDGE  = 2,
} e_bsp_irq_trigger_t;

typedef struct
{
    uint32_t               priority;
    e_gicd_icfgr_sense_t   trigger;
    e_gicd_irouter_route_t route_select;
} bsp_irq_attr_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern void               * gp_renesas_isr_context[BSP_ICU_VECTOR_MAX_ENTRIES];
extern e_gicd_icfgr_sense_t g_int_sense_array[BSP_ICU_VECTOR_MAX_ENTRIES];

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief      Sets the ISR context associated with the requested IRQ.
 *
 * @param[in]  irq            IRQ number (parameter checking must ensure the IRQ number is valid before calling this
 *                            function.
 * @param[in]  p_context      ISR context for IRQ.
 **********************************************************************************************************************/
__STATIC_INLINE void R_FSP_IsrContextSet (IRQn_Type const irq, void * p_context)
{
    /* This provides access to the ISR context array defined in bsp_irq.c. This is an inline function instead of
     * being part of bsp_irq.c for performance considerations because it is used in interrupt service routines. */
    gp_renesas_isr_context[irq] = p_context;
}

/*******************************************************************************************************************//**
 * Clear the interrupt status flag for a given interrupt. There is no processing to be performed by this function in
 * this BSP.
 *
 * @param[in] irq            Interrupt for which to clear the status flag. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqStatusClear (IRQn_Type irq)
{
    FSP_PARAMETER_NOT_USED(irq);

    /* Do nothing */
}

/*******************************************************************************************************************//**
 * Clear the interrupt status flag for a given interrupt and clear the GIC pending interrupt.
 *
 * @param[in] irq            Interrupt for which to clear the status flag and pending state. Note that the enums listed
 *                           for IRQn_Type are only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqClearPending (IRQn_Type irq)
{
    /* Clear the status flag. */
    R_BSP_IrqStatusClear(irq);

    /* Clear pending state in GIC. */
    if (irq < 32)
    {
        R_BSP_GICR_ClearSgiPpiPending(irq);
    }
    else
    {
        R_BSP_GICD_ClearSpiPending(irq);
    }
}

/*******************************************************************************************************************//**
 * Sets the routing table, interrupt priority, interrupt type, interrupt group, and interrupt class for the interrupt
 * of the specified id. Also sets the context after setting them.
 *
 * @param[in] irq            The IRQ to configure.
 * @param[in] priority       GIC priority of the interrupt
 * @param[in] p_context      The interrupt context is a pointer to data required in the ISR.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqCfg (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    uint64_t route = R_BSP_GICR_GetRoute();

    /* Calculate route information to be given to the R_BSP_GICD_SetSpiRoute function. The second argument to
     * R_BSP_GICD_SetSpiRoute function expects Affinity level 3 value to be located from bit 39 to bit 32.
     * However, in the return value of the R_BSP_GICR_GetRoute function that refers to the Affinity value bit of
     * the GICR_TYPER register, Affinity level 3 value is located from bit 31 to bit 24. Therefore, this calculation
     * adjusts the bit position of Affinity level 3 value. */
    route = (0x0000000000FFFFFF & route) | ((0x00000000FF000000 & route) << 8);

    /* Sets information that affinity level and routing mode to identify a CPU interface that notify of interrupts. */
    R_BSP_GICD_SetSpiRoute(irq, route, GICD_IROUTER_ROUTE_FIX);

    /* Sets interrupt priority. */
    R_BSP_GICD_SetSpiPriority(irq, (priority << 3) & 0xFF);

    /* Sets interrupt type that is edge-triggered or level-sensitive. */
    R_BSP_GICD_SetSpiSense(irq, (e_gicd_icfgr_sense_t) g_int_sense_array[irq]);

    /* Sets interrupt group. */
    R_BSP_GICD_SetSpiSecurity(irq, GICD_IGROUPR_G1S);

    /* Sets interrupt class to class1. */
    R_BSP_GICD_SetSpiClass(irq, 1);

    /* Store the context. The context is recovered in the ISR. */
    R_FSP_IsrContextSet(irq, p_context);
}

/*******************************************************************************************************************//**
 * Enable the IRQ in the GIC (Without clearing the pending bit).
 *
 * @param[in] irq            The IRQ to enable. Note that the enums listed for IRQn_Type are only those for the Cortex
 *                           Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqEnableNoClear (IRQn_Type const irq)
{
    R_BSP_GICD_SpiEnable(irq);
}

/*******************************************************************************************************************//**
 * Clears pending interrupts in the GIC, then enables the interrupt.
 *
 * @param[in] irq            Interrupt for which to clear status flag and enable in the GIC. Note that the enums listed
 *                           for IRQn_Type are only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqEnable (IRQn_Type const irq)
{
    /* Clear pending interrupts in the GIC. */
    R_BSP_IrqClearPending(irq);

    /* Enable the IRQ in the GIC. */
    R_BSP_IrqEnableNoClear(irq);
}

/*******************************************************************************************************************//**
 * Disables interrupts in the GIC.
 *
 * @param[in] irq            The IRQ to disable in the GIC. Note that the enums listed for IRQn_Type are
 *                           only those for the Cortex Processor Exceptions Numbers.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqDisable (IRQn_Type const irq)
{
    R_BSP_GICD_SpiDisable(irq);
}

/*******************************************************************************************************************//**
 * Sets the interrupt priority and context, clears pending interrupts, then enables the interrupt.
 *
 * @param[in] irq            Interrupt number.
 * @param[in] priority       GIC priority of the interrupt
 * @param[in] p_context      The interrupt context is a pointer to data required in the ISR.
 *
 * @warning Do not call this function for system exceptions where the IRQn_Type value is < 0.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_IrqCfgEnable (IRQn_Type const irq, uint32_t priority, void * p_context)
{
    R_BSP_IrqCfg(irq, priority, p_context);
    R_BSP_IrqEnable(irq);
}

/*******************************************************************************************************************//**
 * @brief      Finds the ISR context associated with the requested IRQ.
 *
 * @param[in]  irq            IRQ number (parameter checking must ensure the IRQ number is valid before calling this
 *                            function.
 * @return  ISR context for IRQ.
 **********************************************************************************************************************/
__STATIC_INLINE void * R_FSP_IsrContextGet (IRQn_Type const irq)
{
    /* This provides access to the ISR context array defined in bsp_irq.c. This is an inline function instead of
     * being part of bsp_irq.c for performance considerations because it is used in interrupt service routines. */
    return gp_renesas_isr_context[irq];
}

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_irq_cfg(void);                // Used internally by BSP

/** @} (end addtogroup BSP_MCU_PRV) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

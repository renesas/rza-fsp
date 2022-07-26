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

/**********************************************************************************************************************
 * File Name    : bsp_gicv3.c
 * Version      : 1.00
 * Description  : Source code for GICv3 (GIC-600).
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#include <stdint.h>

#include "bsp_api.h"
#include "bsp_gicv3.h"

#define GIC_REG_BITS2         (2U)
#define GIC_REG_BITS8         (8U)

#define GIC_REG_STRIDE04      (4U)
#define GIC_REG_STRIDE16      (16U)
#define GIC_REG_STRIDE32      (32U)

#define GIC_SHIFT_32          (32U)

#define GIC_REG_MASK_8BIT     (0xFFU)

#define GIC_REG_MASK_24BIT    (0x00FFFFFF)
#define GIC_REG_MASK_32BIT    (0x0FFFFFFFF)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static void r_bsp_gic_io_regwrite_32(volatile uint32_t * ioreg, uint32_t write_value, uint32_t shift,
                                     uint64_t mask);
static uint32_t r_bsp_gic_io_regread_32(volatile uint32_t * ioreg, uint32_t shift, uint64_t mask);

/*******************************************************************************************************************//**
 * Set GICD_CTLR Register.
 *
 * @param[in]    bit      Set value of GICD_CTRL register bit.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetCtlr (e_gicd_ctlr_bit_t bit)
{
    r_bsp_gic_io_regwrite_32(&R_INTC_GIC->GICD_CTLR, (uint32_t) bit, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);
}

/*******************************************************************************************************************//**
 * Get value of GICD_CTLR Register.
 *
 * @retval value  GICD_CTLR register value.
 **********************************************************************************************************************/
uint32_t R_BSP_GICD_GetCtlr (void)
{
    uint32_t value;

    value = r_bsp_gic_io_regread_32(&R_INTC_GIC->GICD_CTLR, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);

    return value;
}

/*******************************************************************************************************************//**
 * Enables GICD.
 *
 * @param[in]    bit      Set value of GICD_CTRL register bit.
 *
 * @retval    None.
 **********************************************************************************************************************/
void R_BSP_GICD_Enable (e_gicd_ctlr_bit_t bit)
{
    uint32_t value;

    value = R_BSP_GICD_GetCtlr();
    bit  &= GICD_CTLR_EnableAll;

    R_BSP_GICD_SetCtlr(value | bit);
}

/*******************************************************************************************************************//**
 * Disables GICD.
 *
 * @param[in]    bit      Clear value of GICD_CTRL register bit.
 *
 * @retval    None.
 **********************************************************************************************************************/
void R_BSP_GICD_Disable (e_gicd_ctlr_bit_t bit)
{
    uint32_t value;

    value = R_BSP_GICD_GetCtlr();
    bit  &= GICD_CTLR_EnableAll;

    R_BSP_GICD_SetCtlr(value & ~bit);
}

/*******************************************************************************************************************//**
 * Enables affinity routing.
 *
 * @param[in]    bit      Set value of GICD_CTRL register bit.
 *
 * @retval    None.
 **********************************************************************************************************************/
void R_BSP_GICD_AffinityRouteEnable (e_gicd_ctlr_bit_t bit)
{
    bit &= (GICD_CTLR_ARE_S | GICD_CTLR_ARE_NS);

    R_BSP_GICD_SetCtlr(bit);
}

/*******************************************************************************************************************//**
 * Enables SPI.
 *
 * @param[in]    id      Interrupt number ID.
 *
 * @retval    None.
 **********************************************************************************************************************/
void R_BSP_GICD_SpiEnable (uint32_t id)
{
    volatile uint32_t * addr;
    uint32_t            mask;

    /* GICD_ISENABLERn has 32 sources in the 32 bits         */
    /* The n can be calculated by int_id / 32                */
    /* The bit field width is 1 bit                          */
    /* The target bit can be calculated by (int_id % 32) * 1 */
    /* GICD_ICENABLERn does not effect on writing "0"        */
    /* The bits except for the target write "0"              */
    addr = &R_INTC_GIC->GICD_ISENABLER0;
    mask = 1;
    mask = mask << (id % GIC_REG_STRIDE32);   /* Create mask data */

    *(addr + (id / GIC_REG_STRIDE32)) = mask; /* Write GICD_ISENABLERn */
}

/*******************************************************************************************************************//**
 * Disables SPI.
 *
 * @param[in]    id      Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SpiDisable (uint32_t id)
{
    uint32_t            mask;
    volatile uint32_t * addr;

    /* GICD_ICENABLERn has 32 sources in the 32 bits         */
    /* The n can be calculated by int_id / 32                */
    /* The bit field width is 1 bit                          */
    /* The target bit can be calculated by (int_id % 32) * 1 */
    /* GICD_ICENABLERn does no effect on writing "0"         */
    /* Other bits except for the target write "0"            */
    addr = &R_INTC_GIC->GICD_ICENABLER0;
    mask = 1;
    mask = mask << (id % GIC_REG_STRIDE32);   /* Create mask data */

    *(addr + (id / GIC_REG_STRIDE32)) = mask; /* Write GICD_ICENABLERn */
}

/*******************************************************************************************************************//**
 * Set priority of SPI.
 *
 * @param[in]    id       Interrupt number ID.
 * @param[in]    priority Interrupt Priority.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiPriority (uint32_t id, uint32_t priority)
{
    uint32_t            shift;
    uint32_t            mask;
    volatile uint32_t * p_addr;

    /* GICD_IPRIORITYRn has 4 sources in the 32 bits        */
    /* The n can be calculated by int_id / 4                */
    /* The bit field width is 8 bits                        */
    /* The target bit can be calculated by (int_id % 4) * 8 */
    p_addr = &R_INTC_GIC->GICD_IPRIORITYR0;

    shift = (id % GIC_REG_STRIDE04) * GIC_REG_BITS8; /* 8bits per unit */
    mask  = (uint32_t) (GIC_REG_MASK_8BIT << shift); /* 8bits per unit */
    r_bsp_gic_io_regwrite_32((p_addr + (id / GIC_REG_STRIDE04)), priority, shift, mask);
}

/*******************************************************************************************************************//**
 * Get priority of SPI.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   value  interrupt priority.
 **********************************************************************************************************************/
uint32_t R_BSP_GICD_GetSpiPriority (uint32_t id)
{
    uint32_t            priority;
    uint32_t            shift;
    uint32_t            mask;
    volatile uint32_t * p_addr;

    /* GICD_IPRIORITYRn has 4 sources in the 32 bits        */
    /* The n can be calculated by int_id / 4                */
    /* The bit field width is 8 bits                        */
    /* The target bit can be calculated by (int_id % 4) * 8 */
    p_addr = &R_INTC_GIC->GICD_IPRIORITYR0;

    shift    = (id % GIC_REG_STRIDE04) * GIC_REG_BITS8; /* 8bits per unit */
    mask     = (uint32_t) (GIC_REG_MASK_8BIT << shift); /* 8bits per unit */
    priority = r_bsp_gic_io_regread_32((p_addr + (id / GIC_REG_STRIDE04)), shift, mask);

    return priority;
}

/*******************************************************************************************************************//**
 * Set routing of SPI.
 *
 * @param[in]    id       Interrupt number ID.
 * @param[in]    route    Affinity route settings.
 * @param[in]    mode     Mode of routing
 *
 * @retval   none.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiRoute (uint32_t id, uint64_t route, e_gicd_irouter_route_t mode)
{
    uint64_t   val;
    uint32_t * p_addr;

    /* GICD_IROUTERn control only SPI, GICD_IROUTERn start n = 32 */
    if (id >= GIC_SPI_START_ID)
    {
        /* work around for RZ/G2L WS1, access per 32bit wide */
        val    = route | (uint64_t) mode;
        p_addr = (uint32_t *) (&R_INTC_GIC->GICD_IROUTER32);
        id    -= GIC_SPI_START_ID;

        *(p_addr + (id * 2))       = (uint32_t) (val & GIC_REG_MASK_32BIT);
        *(p_addr + ((id * 2) + 1)) = (uint32_t) ((val >> GIC_SHIFT_32) & GIC_REG_MASK_32BIT);
    }
}

/*******************************************************************************************************************//**
 * Get affinity routing information.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval  value   interrupt routing information.
 **********************************************************************************************************************/
uint64_t R_BSP_GICD_GetSpiRoute (uint32_t id)
{
    uint64_t   val = 0;
    uint32_t * p_addr;

    /* GICD_IROUTERn control only SPI, GICD_IROUTERn start n = 32 */
    if (id >= GIC_SPI_START_ID)
    {
        /* work around for RZ/G2L WS1, access per 32bit wide */
        p_addr = (uint32_t *) (&R_INTC_GIC->GICD_IROUTER32);
        id    -= GIC_SPI_START_ID;

        val  = *(p_addr + (id * 2));
        val |= (((uint64_t) (*(p_addr + ((id * 2) + 1)))) << GIC_SHIFT_32);
    }

    return val;
}

/*******************************************************************************************************************//**
 * Set interrupt as edge trigger or level trigger.
 *
 * @param[in]    id       Interrupt number ID.
 * @param[in]    sense    Interrupt trigger sense.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiSense (uint32_t id, e_gicd_icfgr_sense_t sense)
{
    uint32_t            shift;
    uint32_t            mask;
    volatile uint32_t * p_addr;

    p_addr = &R_INTC_GIC->GICD_ICFGR0;

    shift = (id % GIC_REG_STRIDE16) * GIC_REG_BITS2; /* 2bits per unit */
    mask  = (uint32_t) (0x0000003UL << shift);       /* 2bits per unit */
    r_bsp_gic_io_regwrite_32((p_addr + (id / GIC_REG_STRIDE16)), (uint32_t) sense, shift, mask);
}

/*******************************************************************************************************************//**
 * Get interrupt trigger information.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
uint32_t R_BSP_GICD_GetSpiSense (uint32_t id)
{
    uint32_t            shift;
    uint32_t            mask;
    uint32_t            sense;
    volatile uint32_t * p_addr;

    p_addr = &R_INTC_GIC->GICD_ICFGR0;

    shift = (id % GIC_REG_STRIDE16) * GIC_REG_BITS2; /* 2bits per unit */
    mask  = (uint32_t) (0x00000003UL << shift);      /* 2bits per unit */
    sense = r_bsp_gic_io_regread_32((p_addr + (id / GIC_REG_STRIDE16)), shift, mask);

    return sense;
}

/*******************************************************************************************************************//**
 * Set SPI pending.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiPending (uint32_t id)
{
    volatile uint32_t * addr;
    uint32_t            mask;

    /* GICD_ISPENDRn has 32 sources in the 32 bits         */
    /* The n can be calculated by int_id / 32                */
    /* The bit field width is 1 bit                          */
    /* The target bit can be calculated by (int_id % 32) * 1 */
    addr = &R_INTC_GIC->GICD_ISPENDR0;
    mask = 1;
    mask = mask << (id % GIC_REG_STRIDE32);   /* Create mask data */

    *(addr + (id / GIC_REG_STRIDE32)) = mask; /* Write GICD_ISPENDRn */
}

/*******************************************************************************************************************//**
 * Clear SPI pending.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_ClearSpiPending (uint32_t id)
{
    volatile uint32_t * addr;
    uint32_t            mask;

    /* GICD_ICPENDRn has 32 sources in the 32 bits           */
    /* The n can be calculated by int_id / 32                */
    /* The bit field width is 1 bit                          */
    /* The target bit can be calculated by (int_id % 32) * 1 */
    addr = &R_INTC_GIC->GICD_ICPENDR0;
    mask = 1;
    mask = mask << (id % GIC_REG_STRIDE32);   /* Create mask data */

    *(addr + (id / GIC_REG_STRIDE32)) = mask; /* Write GICD_ICPENDRn */
}

/*******************************************************************************************************************//**
 * Get SPI pending information.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   value   Information of SPI pending.
 **********************************************************************************************************************/
uint32_t R_BSP_GICD_GetSpiPending (uint32_t id)
{
    uint32_t            shift;
    uint32_t            mask;
    uint32_t            pending;
    volatile uint32_t * p_addr;

    p_addr = &R_INTC_GIC->GICD_ICPENDR0;

    shift   = (id % GIC_REG_STRIDE32);            /* 1bits per unit */
    mask    = (uint32_t) (0x00000001UL << shift); /* 1bits per unit */
    pending = r_bsp_gic_io_regread_32((p_addr + (id / GIC_REG_STRIDE32)), shift, mask);

    return pending;
}

/*******************************************************************************************************************//**
 * Set SPI security group.
 *
 * @param[in]    id       Interrupt number ID.
 * @param[in]    group    Security group.
 *
 * @retval   none.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiSecurity (uint32_t id, e_gicd_igroupr_secure_t group)
{
    volatile uint32_t * addr;
    uint32_t            group_modfier;
    uint32_t            group_status;
    uint32_t            shift;
    uint32_t            mask;

    /* get group_modifier bit for GICD_IGRPMODRn */
    group_modfier = (group >> 1) & 0x00000001;

    /* get group_status bit for GICD_IGROUPR */
    group_status = group & 0x00000001;

    shift = (id % GIC_REG_STRIDE32);
    mask  = (uint32_t) (0x0000001UL << shift);

    /* GICD_IGROUPRn, GICD_IGRPMODRn has 32 sources in the 32 bits  */
    /* The n can be calculated by int_id / 32                       */
    /* The bit field width is 1 bit                                 */
    /* The target bit can be calculated by (int_id % 32) * 1        */
    addr = &R_INTC_GIC->GICD_IGROUPR0;
    r_bsp_gic_io_regwrite_32((addr + (id / GIC_REG_STRIDE32)), group_status, shift, mask);

    addr = &R_INTC_GIC->GICD_IGRPMODR0;
    r_bsp_gic_io_regwrite_32((addr + (id / GIC_REG_STRIDE32)), group_modfier, shift, mask);
}

/*******************************************************************************************************************//**
 * Set SPI security group for each line of GICD_IGRPMODRn register.
 *
 * @param[in]    line     Line of GICD_IGRPMODRn register.
 * @param[in]    group    Security group.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiSecurityLine (uint32_t line, e_gicd_igroupr_secure_t group)
{
    volatile uint32_t * addr;
    uint32_t            group_modfier;
    uint32_t            group_status;

    /* get group_modifier bit for GICD_IGRPMODRn */
    group_modfier = ((group >> 1) & 0x00000001);

    /* GICD_IGRPMODRn is a 32-bit register with 32 group_modifer bits. */
    /* If group_modifer = 1 is set, set 0xFFFFFFFF in the register. */
    group_modfier = (~group_modfier + 1);

    /* get group_status bit for GICD_IGROUPR*/
    group_status = (group & 0x00000001);

    /* GICD_IGRPMODRn is a 32-bit register with 32 group_modifer bits. */
    /* If group_modifer = 1 is set, set 0xFFFFFFFF in the register. */
    group_status = (~group_status + 1);

    /* GICD_IGROUPRn, GICD_IGRPMODRn has 32 sources in the 32 bits  */
    /* The n can be calculated by int_id / 32                       */
    /* The bit field width is 1 bit                                 */
    /* The target bit can be calculated by (int_id % 32) * 1        */
    addr = &R_INTC_GIC->GICD_IGROUPR0;
    r_bsp_gic_io_regwrite_32((addr + line), group_status, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);

    addr = &R_INTC_GIC->GICD_IGRPMODR0;
    r_bsp_gic_io_regwrite_32((addr + line), group_modfier, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);
}

/*******************************************************************************************************************//**
 * Set SPI security group for all GICD_IGRPMODRn register.
 *
 * @param[in]    group    Security group.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiSecurityAll (e_gicd_igroupr_secure_t group)
{
    uint32_t line;
    uint32_t cnt;

    line = r_bsp_gic_io_regread_32(&R_INTC_GIC->GICD_TYPER, GIC_NONSHIFT_ACCESS, 0x1F);

    for (cnt = 0; cnt <= line; cnt++)
    {
        R_BSP_GICD_SetSpiSecurityLine(cnt, group);
    }
}

/*******************************************************************************************************************//**
 * Set SPI interrupt class.
 *
 * @param[in]    id             Interrupt number ID.
 * @param[in]    class_group    Interrupt class.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICD_SetSpiClass (uint32_t id, uint32_t class_group)
{
    uint32_t            shift;
    uint32_t            mask;
    volatile uint32_t * p_addr;
    uint32_t            class_set;

    /* ICLAR control only SPI */
    if (id >= GIC_SPI_START_ID)
    {
        class_set = 1 << (~class_group & 0x01);

        /* ICLAR start from ICLAR2 */
        p_addr = &R_INTC_GIC->GICD_ICLAR2;

        id   -= GIC_SPI_START_ID;
        shift = (id % GIC_REG_STRIDE16) * GIC_REG_BITS2; /* 2bits per unit */
        mask  = (uint32_t) (0x0000003UL << shift);       /* 2bits per unit */
        r_bsp_gic_io_regwrite_32((p_addr + (id / GIC_REG_STRIDE16)), class_set, shift, mask);
    }
}

/*******************************************************************************************************************//**
 * Enables GICR.
 *
 * @retval   none.
 **********************************************************************************************************************/
void R_BSP_GICR_Enable (void)
{
    /* Power up Redistributor */
    r_bsp_gic_io_regwrite_32(&R_INTC_GIC->GICR_PWRR, GICR_WAKER_PROCESSOR_SLEEP, GIC_NONSHIFT_ACCESS,
                             GIC_NONMASK_ACCESS);

    /*
     * GICR_WAKER.ProcessorSleep off
     */
    r_bsp_gic_io_regwrite_32(&R_INTC_GIC->GICR_WAKER,
                             0,
                             R_INTC_GIC_GICR_WAKER_ProcessorSleep_Pos,
                             R_INTC_GIC_GICR_WAKER_ProcessorSleep_Msk);

    /* wait for ChildrenAsleep bit to be cleared */
    while (1)
    {
        if (0 ==
            r_bsp_gic_io_regread_32(&R_INTC_GIC->GICR_WAKER, R_INTC_GIC_GICR_WAKER_ChildrenAsleep_Pos,
                                    R_INTC_GIC_GICR_WAKER_ChildrenAsleep_Msk))
        {
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Enables SGI and PPI.
 *
 * @param[in]    id      Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SgiPpiEnable (uint32_t id)
{
    id &= 0x1f;

    /* Enable SGI0 - SGI15, PPI0 - PPI15 */
    r_bsp_gic_io_regwrite_32(&R_INTC_GIC->GICR_ISENABLER0, 1, id, (1 << id));
}

/*******************************************************************************************************************//**
 * Disables SGI and PPI.
 *
 * @param[in]    id      Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SgiPpiDisable (uint32_t id)
{
    id &= 0x1f;

    /* Disable SGI0 - SGI15, PPI0 - PPI15 */
    r_bsp_gic_io_regwrite_32(&R_INTC_GIC->GICR_ICENABLER0, 1, id, (1 << id));
}

/*******************************************************************************************************************//**
 * Set priority of SGI and PPI.
 *
 * @param[in]    id       Interrupt number ID.
 * @param[in]    priority Interrupt Priority.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SetSgiPpiPriority (uint32_t id, uint32_t priority)
{
    uint32_t            shift;
    uint32_t            mask;
    volatile uint32_t * p_addr;

    id &= 0x1f;

    /* GICR_IPRIORITYRn has 4 sources in the 32 bits        */
    /* The n can be calculated by int_id / 4                */
    /* The bit field width is 8 bits                        */
    /* The target bit can be calculated by (int_id % 4) * 8 */
    p_addr = &R_INTC_GIC->GICR_IPRIORITYR0;

    shift = (id % GIC_REG_STRIDE04) * GIC_REG_BITS8; /* 8bits per unit */
    mask  = (uint32_t) (GIC_REG_MASK_8BIT << shift); /* 8bits per unit */
    r_bsp_gic_io_regwrite_32((p_addr + (id / GIC_REG_STRIDE04)), priority, shift, mask);
}

/*******************************************************************************************************************//**
 * Get priority of SGI and PPI.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   value  interrupt priority.
 **********************************************************************************************************************/
uint32_t R_BSP_GICR_GetSgiPpiPriority (uint32_t id)
{
    uint32_t            priority;
    uint32_t            shift;
    uint32_t            mask;
    volatile uint32_t * p_addr;

    id &= 0x1f;

    /* GICR_IPRIORITYRn has 4 sources in the 32 bits        */
    /* The n can be calculated by int_id / 4                */
    /* The bit field width is 8 bits                        */
    /* The target bit can be calculated by (int_id % 4) * 8 */
    p_addr = &R_INTC_GIC->GICR_IPRIORITYR0;

    shift    = (id % GIC_REG_STRIDE04) * GIC_REG_BITS8; /* 8bits per unit */
    mask     = (uint32_t) (GIC_REG_MASK_8BIT << shift); /* 8bits per unit */
    priority = r_bsp_gic_io_regread_32((p_addr + (id / GIC_REG_STRIDE04)), shift, mask);

    return priority;
}

/*******************************************************************************************************************//**
 * Set pending of SGI and PPI.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SetSgiPpiPending (uint32_t id)
{
    volatile uint32_t * addr;
    uint32_t            mask;

    id &= 0x1f;

    /* GICR_ISPENDn has 32 sources in the 32 bits            */
    /* The n can be calculated by int_id / 32                */
    /* The bit field width is 1 bit                          */
    /* The target bit can be calculated by (int_id % 32) * 1 */
    addr = &R_INTC_GIC->GICR_ISPENDR0;
    mask = 1;
    mask = mask << (id % GIC_REG_STRIDE32); /* Create mask data */

    *(addr) = mask;                         /* Write GICD_ISPENDRn */
}

/*******************************************************************************************************************//**
 * Clear pending of SGI and PPI.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_ClearSgiPpiPending (uint32_t id)
{
    volatile uint32_t * addr;
    uint32_t            mask;

    id &= 0x1f;

    /* GICR_ICPENDRn has 32 sources in the 32 bits           */
    /* The n can be calculated by int_id / 32                */
    /* The bit field width is 1 bit                          */
    /* The target bit can be calculated by (int_id % 32) * 1 */
    addr = &R_INTC_GIC->GICR_ICPENDR0;
    mask = 1;
    mask = mask << (id % GIC_REG_STRIDE32); /* Create mask data */

    *(addr) = mask;                         /* Write GICD_ICPENDRn */
}

/*******************************************************************************************************************//**
 * Get SGI and PPI pending information.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   value   Information of SGI or PPI pending.
 **********************************************************************************************************************/
uint32_t R_BSP_GICR_GetSgiPpiPending (uint32_t id)
{
    uint32_t            shift;
    uint32_t            mask;
    uint32_t            pending;
    volatile uint32_t * p_addr;

    id &= 0x1f;

    p_addr = &R_INTC_GIC->GICR_ICPENDR0;

    shift   = (id % GIC_REG_STRIDE32);            /* 1bits per unit */
    mask    = (uint32_t) (0x00000001UL << shift); /* 1bits per unit */
    pending = r_bsp_gic_io_regread_32(p_addr, shift, mask);

    return pending;
}

/*******************************************************************************************************************//**
 * Set SGI and PPI security group.
 *
 * @param[in]    id       Interrupt number ID.
 * @param[in]    group    Security group.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SetSgiPpiSecurity (uint32_t id, e_gicd_igroupr_secure_t group)
{
    volatile uint32_t * addr;
    uint32_t            group_modfier;
    uint32_t            group_status;
    uint32_t            shift;
    uint32_t            mask;

    /* get group_modifier bit for GICD_IGRPMODRn */
    group_modfier = (group >> 1) & 0x00000001;

    /* get group_status bit for GICD_IGROUPR*/
    group_status = group & 0x00000001;

    shift = (id % GIC_REG_STRIDE32);
    mask  = (uint32_t) (0x0000001UL << shift);

    /* GICR_IGROUPRn, GICR_IGRPMODRn has 32 sources in the 32 bits  */
    /* The n can be calculated by int_id / 32                       */
    /* The bit field width is 1 bit                                 */
    /* The target bit can be calculated by (int_id % 32) * 1        */
    addr = &R_INTC_GIC->GICR_IGROUPR0;
    r_bsp_gic_io_regwrite_32(addr, group_status, shift, mask);

    addr = &R_INTC_GIC->GICR_IGRPMODR0;
    r_bsp_gic_io_regwrite_32(addr, group_modfier, shift, mask);
}

/*******************************************************************************************************************//**
 * Set SPI security group for each line of GICR_IGROUPR0 register.
 *
 * @param[in]    group    Security group.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SetSgiPpiSecurityLine (e_gicd_igroupr_secure_t group)
{
    volatile uint32_t * addr;
    uint32_t            group_modfier;
    uint32_t            group_status;

    /* get group_modifier bit for GICD_IGRPMODRn */
    group_modfier = ((group >> 1) & 0x00000001);

    /* GICD_IGRPMODRn is a 32-bit register with 32 group_modifer bits. */
    /* If group_modifer = 1 is set, set 0xFFFFFFFF in the register. */
    group_modfier = (~group_modfier + 1);

    /* get group_status bit for GICD_IGROUPR*/
    group_status = (group & 0x00000001);

    /* GICD_IGRPMODRn is a 32-bit register with 32 group_modifer bits. */
    /* If group_modifer = 1 is set, set 0xFFFFFFFF in the register. */
    group_status = (~group_status + 1);

    /* GICR_IGROUPRn, GIC_IGRPMODRn has 32 sources in the 32 bits  */
    /* The n can be calculated by int_id / 32                       */
    /* The bit field width is 1 bit                                 */
    /* The target bit can be calculated by (int_id % 32) * 1        */
    addr = &R_INTC_GIC->GICR_IGROUPR0;
    r_bsp_gic_io_regwrite_32(addr, group_status, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);

    addr = &R_INTC_GIC->GICR_IGRPMODR0;
    r_bsp_gic_io_regwrite_32(addr, group_modfier, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);
}

/*******************************************************************************************************************//**
 * Set interrupt class.
 *
 * @param[in]    class_group    Interrupt class group.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICR_SetClass (uint32_t class_group)
{
    r_bsp_gic_io_regwrite_32(&R_INTC_GIC->GICR_CLASS, class_group, GIC_NONSHIFT_ACCESS, GIC_NONMASK_ACCESS);
}

/*******************************************************************************************************************//**
 * Get routing information.
 *
 * @retval   value  interrupt routing information.
 **********************************************************************************************************************/
uint32_t R_BSP_GICR_GetRoute (void)
{
    uint32_t   val;
    uint32_t * p_addr;

    p_addr = (uint32_t *) (&R_INTC_GIC->GICR_TYPER);
    val    = (*(p_addr + 1));

    return val;
}

/*******************************************************************************************************************//**
 * Set interrupt mask level.
 *
 * @param[in]    mask_level  Mask level.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICC_SetMaskLevel (uint64_t mask_level)
{
    mask_level &= GIC_REG_MASK_8BIT;

    __asm("msr  S3_0_C4_C6_0, %0;"
          "isb;"
          :
          : "r" (mask_level));
}

/*******************************************************************************************************************//**
 * Get interrupt mask level information.
 *
 * @retval   value   Information of mask level.
 **********************************************************************************************************************/
uint64_t R_BSP_GICC_GetMaskLevel (void)
{
    uint64_t mask_level;

    __asm("mrs %0, S3_0_C4_C6_0;"
          "isb;"
          : "=r" (mask_level)
          :);
    mask_level &= GIC_REG_MASK_8BIT;

    return mask_level;
}

/*******************************************************************************************************************//**
 * Set end of interrupt for group0.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICC_SetEoiGrp0 (uint32_t id)
{
    uint64_t set_id;

    set_id = (uint64_t) (id & GIC_REG_MASK_24BIT); /* 23bit INTID filed */

    __asm("msr  S3_0_C12_C8_1, %0;"
          "isb;"
          :
          : "r" (set_id));
}

/*******************************************************************************************************************//**
 * Set end of interrupt for group1.
 *
 * @param[in]    id       Interrupt number ID.
 *
 * @retval   None.
 **********************************************************************************************************************/
void R_BSP_GICC_SetEoiGrp1 (uint32_t id)
{
    uint64_t set_id;

    set_id = (uint64_t) (id & GIC_REG_MASK_24BIT); /* 23bit INTID filed */

    __asm("msr  S3_0_C12_C12_1, %0;"
          "isb;"
          :
          : "r" (set_id));
}

/*******************************************************************************************************************//**
 * Get interrupt ID being asserted from group0.
 *
 * @retval   value   Interrupt ID number.
 **********************************************************************************************************************/
uint32_t R_BSP_GICC_Get_IntIdGrp0 (void)
{
    uint64_t get_id;

    __asm("mrs  %0, S3_0_C12_C8_0;"
          : "=r" (get_id)
          :
          :);
    get_id &= GIC_REG_MASK_24BIT;      /* 23bit INTID filed */

    return (uint32_t) get_id;
}

/*******************************************************************************************************************//**
 * Get interrupt ID being asserted from group1.
 *
 * @retval   Interrupt ID number.
 **********************************************************************************************************************/
uint32_t R_BSP_GICC_Get_IntIdGrp1 (void)
{
    uint64_t get_id;

    __asm("mrs  %0, S3_0_C12_C12_0;"
          : "=r" (get_id)
          :
          :);
    get_id &= GIC_REG_MASK_24BIT;      /* 23bit INTID filed */

    return (uint32_t) get_id;
}

/**********************************************************************************************************************
 * IO register 32-bit write
 *
 * @param[in]   * ioreg            IO register for writing
 * @param[in]   write_value        Write value for the IO register
 * @param[in]   shift              The number of left shifts to the target bit
 * @param[in]   mask               Mask value for the IO register (Target bit : "1")
 *
 * @retval      None.
 *********************************************************************************************************************/
static void r_bsp_gic_io_regwrite_32 (volatile uint32_t * ioreg, uint32_t write_value, uint32_t shift, uint64_t mask)
{
    uint32_t reg_value;

    if (GIC_NONMASK_ACCESS != mask)
    {
        /* Read from register */
        reg_value = *ioreg;

        /* Modify value */
        reg_value = (uint32_t) ((reg_value & (~mask)) | (write_value << shift));
    }
    else
    {
        reg_value = write_value;
    }

    /* Write to register */
    *ioreg = reg_value;
}

/**********************************************************************************************************************
 * IO register 32-bit read
 *
 * @param[in]   * ioreg            IO register for reading
 * @param[in]   shift              The number of left shifts to the target bit
 * @param[in]   mask               Mask value for the IO register (Target bit : "1")
 *
 * @retval   value         Register value
 *********************************************************************************************************************/
static uint32_t r_bsp_gic_io_regread_32 (volatile uint32_t * ioreg, uint32_t shift, uint64_t mask)
{
    uint32_t reg_value;

    /* Read from register */
    reg_value = *ioreg;

    if (GIC_NONMASK_ACCESS != mask)
    {
        /* Clear other bit and Bit shift */
        reg_value = (uint32_t) ((reg_value & mask) >> shift);
    }

    return reg_value;
}

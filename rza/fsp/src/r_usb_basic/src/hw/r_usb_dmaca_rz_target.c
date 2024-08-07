/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************
 * File Name    : r_usb_dmaca_rx_target.c
 * Device(s)    : RX
 * Tool-Chain   : Renesas RXC Toolchain v2.01.00
 * OS           : not use
 * H/W Platform : not use
 * Description  : Functions for DMACA driver
 *******************************************************************************/

/*******************************************************************************
 * History      : DD.MM.YYYY Version  Description
 *              : 30.06.2014 1.00     Initial revision
 *              : 27.08.2014 1.01     Not change program due to updating application note only.
 *              : 30.01.2015 1.02     Added RX71M.
 *              : 13.04.2015 1.03     Added RX231.
 *******************************************************************************/

/*******************************************************************************
 * Includes <System Includes>, "Project Includes"
 *******************************************************************************/

/* Definitions for DMACA support */
#include "r_usb_dmaca_rz_if.h"
#include "r_usb_dmaca_rz_private.h"

/* DMACA DMAC0I */

void r_usb_dmaca_intDMAC0I_isr(IRQn_Type const irq);

/* DMACA DMAC1I */

void r_usb_dmaca_intDMAC1I_isr(IRQn_Type const irq);

#if USB_CFG_DMA == USB_CFG_ENABLE

/*******************************************************************************
 * Macro definitions
 *******************************************************************************/
typedef void (* DMACI_Callback)(void);

/*******************************************************************************
 * Private variables and functions
 *******************************************************************************/

/*******************************************************************************
 * Exported global variables (to be accessed by other files)
 *******************************************************************************/

/*******************************************************************************
 * Function Name: r_usb_dmaca_channel_valid_check
 * Description  : Checks whether channel is valid or not.
 * Arguments    : channel -
 *                    Which channel to use
 * Return Value : true -
 *                    Channel is valid.
 *                false -
 *                    Channel is invalid.
 *******************************************************************************/
bool r_usb_dmaca_channel_valid_check (uint8_t channel)
{
    bool ret = false;

    switch (channel)
    {
        case USB_DMACA_CH0:
        case USB_DMACA_CH1:
        {
            /* The channel number is valid. */
            ret = true;
            break;
        }

        default:
        {
            /* The channel number is invalid. */
            ret = false;
            break;
        }
    }

    return ret;
}

/*******************************************************************************
 * Function Name: r_usb_dmaca_int_disable_set
 * Description  : Disables DMACmI interrupt. (m = 0 to 3, or 74)
 * Arguments    : channel -
 *                    Which channel to use
 * Return Value : USB_DMACA_SUCCESS -
 *                    DMACmI interrupt is disabled successfully.
 *                USB_DMACA_ERR_INVALID_CH -
 *                    Channel is invalid.
 *******************************************************************************/
usb_dmaca_return_t r_usb_dmaca_int_disable_set (uint8_t channel)
{
    /* Clear the DMACmI interrupt Enable bit. */
    /* Clear the DMACmI priority level. */

    /* e_r_drv_intc_priority_t *pri; */
    uint8_t * pri;

    switch (channel)
    {
        case USB_DMACA_CH0:
        {
 #if USB_CFG_USE_USBIP == USB_CFG_IP0
            R_BSP_IrqDisable(VECTOR_NUMBER_USB_FDMA0);

/* R_INTC_SetPriority(INTC_ID_USB_USBFDMA00, 0); */
 #else
            R_BSP_IrqDisable(VECTOR_NUMBER_USB_FDMA1);

/* R_INTC_SetPriority(INTC_ID_USB_USBFDMA10, 0); */
 #endif
            break;
        }

        case USB_DMACA_CH1:
        {
 #if USB_CFG_USE_USBIP == USB_CFG_IP0
            R_BSP_IrqDisable(VECTOR_NUMBER_USB_FDMA0);

/* R_INTC_SetPriority(INTC_ID_USB_USBFDMA01, 0); */
 #else
            R_BSP_IrqDisable(VECTOR_NUMBER_USB_FDMA1);

            /* R_INTC_SetPriority(INTC_ID_USB_USBFDMA11, 0); */
 #endif
            break;
        }

        default:
        {
            /* The channel number is invalid. */
            return USB_DMACA_ERR_INVALID_CH;
            break;
        }
    }

    return USB_DMACA_SUCCESS;
}

/*******************************************************************************
 * Function Name: r_usb_dmaca_int_enable_set
 * Description  : Enables DMACmI interrupt. (m = 0 to 3, or 74)
 * Arguments    : channel -
 *                    Which channel to use
 *              : priority -
 *                    DMACmI interrupt priority level
 * Return Value : USB_DMACA_SUCCESS -
 *                    DMACmI interrupt is enabled successfully.
 *                USB_DMACA_ERR_INVALID_CH -
 *                    Channel is invalid.
 *******************************************************************************/
usb_dmaca_return_t r_usb_dmaca_int_enable_set (uint8_t channel, uint8_t priority)
{
    /* Set the DMACmI priority level. */
    /* Set the DMACmI interrupt Enable bit. */
    switch (channel)
    {
        case USB_DMACA_CH0:
        {
 #if USB_CFG_USE_USBIP == USB_CFG_IP0
            R_BSP_IrqCfgEnable(VECTOR_NUMBER_USB_FDMA0, 1, NULL);
 #else
            R_BSP_IrqCfgEnable(VECTOR_NUMBER_USB_FDMA1, 1, NULL);
 #endif
            break;
        }

        case USB_DMACA_CH1:
        {
 #if USB_CFG_USE_USBIP == USB_CFG_IP0
            R_BSP_IrqCfgEnable(VECTOR_NUMBER_USB_FDMA0, 1, NULL);
 #else
            R_BSP_IrqCfgEnable(VECTOR_NUMBER_USB_FDMA1, 1, NULL);
 #endif
            break;
        }

        default:
        {
            /* The channel number is invalid. */
            return USB_DMACA_ERR_INVALID_CH;
            break;
        }
    }

    return USB_DMACA_SUCCESS;
}

/*******************************************************************************
 * Function Name: r_intc_dummy_read_enable
 * Description  : Dummy Read the enable clear of the ID specified by the int_id
 * Arguments    : uint16_t int_id   : Interrupt ID
 * Return Value : GICD_ISENABLERn dummy read value
 *******************************************************************************/
int32_t r_intc_dummy_read_enable (uint16_t int_id)
{
 #if 0
    uint32_t            icdisen;
    uint32_t            mask;
    volatile uint32_t * addr;

    /* ==== Argument check ==== */
    if (int_id >= INTC_GIC_ID_TOTAL)
    {
        return INTC_ERR_INVALID;       /* Argument error */
    }

    /* GICD_ISENABLERn has 32 sources in the 32 bits        */
    /* The n can be calculated by int_id / 32               */
    /* The bit field width is 1 bit                         */
    /* The target bit can be calclated by (int_id % 32) * 1 */
    /* GICD_ICENABLERn does not effect on writing "0"       */
    /* The bits except for the target write "0"             */
    addr     = (volatile uint32_t *) &INTC.GICD_ISENABLER0;
    icdisen  = *(addr + (int_id / 32)); /* Read GICD_ISENABLERn   */
    icdisen  = icdisen >> (int_id % 32);
    icdisen &= 0x1;

    return (int32_t) icdisen;
 #endif
}

#endif                                 /* #if USB_CFG_DMA == USB_CFG_ENABLE */

/************************************************************************************
 * Outline      : Interrupt DMAC0I handler
 * Function Name: r_usb_dmaca_intDMAC0I_isr
 * Description  : Types of interrupt requests from DMACA channel 0.
 *                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
 *                write a program under "do something" in this
 *                r_usb_dmaca_intDMAC0I_isr() function.
 * Arguments    : None
 * Return Value : None
 ************************************************************************************/
void r_usb_dmaca_intDMAC0I_isr (IRQn_Type const irq)
{
    FSP_PARAMETER_NOT_USED(irq);
#if USB_CFG_DMA == USB_CFG_ENABLE
    if (((uint32_t) NULL != (uint32_t) p_DMACI_Handlers[USB_DMACA_CH0]))
    {
        ((DMACI_Callback) p_DMACI_Handlers[USB_DMACA_CH0])();
    }
    else
    {
        /* do something */
    }
#endif
}

/************************************************************************************
 * Outline      : Interrupt DMAC1I handler
 * Function Name: r_usb_dmaca_intDMAC1I_isr
 * Description  : Types of interrupt requests from DMACA channel1.
 *                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
 *                write a program under "do something" in this
 *                r_usb_dmaca_intDMAC1I_isr() function.
 * Arguments    : None
 * Return Value : None
 ************************************************************************************/
void r_usb_dmaca_intDMAC1I_isr (IRQn_Type const irq)
{
    FSP_PARAMETER_NOT_USED(irq);
#if USB_CFG_DMA == USB_CFG_ENABLE
    if (((uint32_t) NULL != (uint32_t) p_DMACI_Handlers[USB_DMACA_CH1]))
    {
        ((DMACI_Callback) p_DMACI_Handlers[USB_DMACA_CH1])();
    }
    else
    {
        /* do something */
    }
#endif
}

/* End of File */

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
 * File Name    : bsp_clocks_setup.c
 * Version      : 1.00
 * Description  : bsp_clocks_setup source
 *********************************************************************************************************************/

#include "../all/bsp_clocks.h"

void bsp_clock_off (void)
{
    uint8_t channel;

    /* Stop unnecessary clocks to reduce power consumption. */
    for (channel = 0; BSP_FEATURE_GTM_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_GTM, channel);
    }

    R_BSP_MODULE_CLKOFF(FSP_IP_MTU3, 0);

    R_BSP_MODULE_CLKOFF(FSP_IP_POE3, 0);

    for (channel = 0; BSP_FEATURE_WDT_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_WDT, channel);
    }

    for (channel = 0; BSP_FEATURE_SDHI_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_SDHI, channel);
    }

    for (channel = 0; BSP_FEATURE_ISU_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_ISU, channel);
    }

    for (channel = 0; BSP_FEATURE_CRU_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_CRU, channel);
    }

    for (channel = 0; BSP_FEATURE_LCDC_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_LCDC, channel);
    }

    for (channel = 0; BSP_FEATURE_SSI_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_SSI, channel);
    }

    R_BSP_MODULE_CLKOFF(FSP_IP_USB0, 0);
    R_BSP_MODULE_CLKOFF(FSP_IP_USB1, 0);
    R_BSP_MODULE_CLKOFF(FSP_IP_USBPHY, 0);

    for (channel = 0; BSP_FEATURE_GETHER_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_ETHER, channel);
    }

    for (channel = 0; BSP_FEATURE_RIIC_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_RIIC, channel);
    }

    for (channel = 0; BSP_FEATURE_SCIF_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_SCIF, channel);
    }

    for (channel = 0; BSP_FEATURE_SCI_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_SCI, channel);
    }

    for (channel = 0; BSP_FEATURE_IRDA_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_IRDA, channel);
    }

    for (channel = 0; BSP_FEATURE_RSPI_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_RSPI, channel);
    }

    R_BSP_MODULE_CLKOFF(FSP_IP_CANFD, 0);

    R_BSP_MODULE_CLKOFF(FSP_IP_ADC, 0);

    for (channel = 0; BSP_FEATURE_TSU_MAX_CHANNELS > channel; channel++)
    {
        R_BSP_MODULE_CLKOFF(FSP_IP_TSU, channel);
    }
}

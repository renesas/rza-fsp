/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

#ifndef FSP_FEATURES_H
#define FSP_FEATURES_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/* C99 includes. */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

/* Different compiler support. */
#include "fsp_common_api.h"
#include "../../fsp/src/bsp/mcu/all/bsp_compiler_support.h"
#include "../../fsp/src/bsp/mcu/all/bsp_module_stop.h"
#include "../../fsp/src/bsp/mcu/all/bsp_clocks.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Cancels the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be started
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_START(ip, ch)                     (R_BSP_MODULE_START_ ## ip(ip, ch))

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_STOP(ip, ch)                      (R_BSP_MODULE_STOP_ ## ip(ip, ch))

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MODULE_START_FSP_IP_ADC(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_ADC(ip, ch)           {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_CANFD(ip, ch)        {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_CANFD(ip, ch)         {NULL;}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_CRU(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_CRU(ip, ch)           {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_DMAC_NS(ip, ch)      {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_DMAC_NS(ip, ch)       {NULL;}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_ETHER(ip, ch)        {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_ETHER(ip, ch)         {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_GTM(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTON(ip, ch); \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_GTM(ip, ch)           {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_LCDC(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_LCDC(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_MTU3(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_MTU3(ip, ch)          {NULL;}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_RIIC(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_RIIC(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_RSPI(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_RSPI(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_SCI(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_SCI(ip, ch)           {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_SCIF(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_SCIF(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_SDHI(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_SDHI(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_OCTA(ip, ch)         {NULL;}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_OCTA(ip, ch)          {R_BSP_MODULE_RSTON(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_SPI_MULTI(ip, ch)    {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_SPI_MULTI(ip, ch)     {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_SSI(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_SSI(ip, ch)           {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_USBPHY(ip, ch)       {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_USBPHY(ip, ch)        {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_USB0(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_USB0(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_USB1(ip, ch)         {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_USB1(ip, ch)          {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_WDT(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch)    \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_WDT(ip, ch)           {NULL;}

/*******************************************************************************************************************//**
 * Cancel the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_START_FSP_IP_ISU(ip, ch)          {R_BSP_MODULE_CLKON(ip, ch); \
                                                        R_BSP_MSTP_START(ip, ch);   \
                                                        R_BSP_MODULE_RSTOFF(ip, ch);}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      ch       The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/

#define R_BSP_MODULE_STOP_FSP_IP_ISU(ip, ch)           {R_BSP_MSTP_STOP(ip, ch); \
                                                        R_BSP_MODULE_CLKOFF(ip, ch);}

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */

FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Available modules. */
typedef enum e_fsp_ip
{
    FSP_IP_GTM       = 0,              ///< General Timer
    FSP_IP_PORT      = 3,              ///< I/O Ports
    FSP_IP_IA55      = 4,              ///< IA55 (Interrupt controller)
    FSP_IP_SCIF      = 5,              ///< Serial Communications Interface with FIFO
    FSP_IP_RIIC      = 6,              ///< I2C Bus Interface
    FSP_IP_RSPI      = 7,              ///< Renesas Serial Peripheral Interface
    FSP_IP_DMAC_NS   = 9,              ///< Direct Memory Access Controller
    FSP_IP_SSI       = 10,             ///< Serial Sound Interface
    FSP_IP_CANFD     = 11,             ///< CANFD Interface (RS-CANFD)
    FSP_IP_ETHER     = 12,             ///< Ethernet MAC Controller
    FSP_IP_EDMAC     = 12,             ///< Ethernet DMA Controller
    FSP_IP_CRU       = 13,             ///< Camera Data Receiving Unit
    FSP_IP_LCDC      = 14,             ///< LCD Controller
    FSP_IP_USBPHY    = 15,             ///< USB 2.0
    FSP_IP_USB0      = 16,             ///< USB 2.0
    FSP_IP_USB1      = 17,             ///< USB 2.0
    FSP_IP_ADC       = 18,             ///< A/D Converter
    FSP_IP_WDT       = 19,             ///< Watchdog Timer
    FSP_IP_SDHI      = 20,             ///< SD/MMC Host Interface
    FSP_IP_ISU       = 21,             ///< Image Scaling Unit
    FSP_IP_SCI       = 22,             ///< Serial Communications Interface
    FSP_IP_MTU3      = 23,             ///< Multi-Function Timer Pulse Unit 3
    FSP_IP_SPI_MULTI = 24,             ///< SPI Multi I/O Bus Controller
    FSP_IP_OCTA      = 25,             ///< Octa Memory Controller
} fsp_ip_t;

typedef void (* fsp_vector_t)(IRQn_Type const irq);

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

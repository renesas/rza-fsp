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

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

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
    FSP_IP_DMAC      = 9,              ///< Direct Memory Access Controller
    FSP_IP_SSI       = 10,             ///< Serial Sound Interface
    FSP_IP_CANFD     = 11,             ///< CANFD Interface (RS-CANFD)
    FSP_IP_ETHER     = 12,             ///< Ethernet MAC Controller
    FSP_IP_EDMAC     = 12,             ///< Ethernet DMA Controller
    FSP_IP_CRU       = 13,             ///< Camera Data Receiving Unit
    FSP_IP_LCDC      = 14,             ///< LCD Controller
    FSP_IP_USB       = 15,             ///< USB 2.0
    FSP_IP_ADC       = 16,             ///< A/D Converter
    FSP_IP_WDT       = 17,             ///< Watchdog Timer
    FSP_IP_SDHI      = 18,             ///< SD/MMC Host Interface
    FSP_IP_ISU       = 19,             ///< Image Scaling Unit
    FSP_IP_SCI       = 20,             ///< Serial Communications Interface
    FSP_IP_MTU3      = 21,             ///< Multi-Function Timer Pulse Unit 3
    FSP_IP_SPI_MULTI = 22,             ///< SPI Multi I/O Bus Controller
    FSP_IP_OCTA      = 23,             ///< Octa Memory Controller
} fsp_ip_t;

typedef void (* fsp_vector_t)(IRQn_Type const irq);

/** @} (end addtogroup BSP_MCU) */

#endif

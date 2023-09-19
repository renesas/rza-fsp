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

/*******************************************************************************************************************//**
 * @addtogroup GETHER
 * @{
 **********************************************************************************************************************/

#ifndef R_GETHER_H
#define R_GETHER_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_gether_cfg.h"
#include "r_ether_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions before including r_ether_api.h
 **********************************************************************************************************************/
typedef enum e_gether_descriptor_type
{
    /* Frame data */
    GETHER_DESCRIPTOR_TYPE_FMID    = 0x4,   /* Frame MIDdle */
    GETHER_DESCRIPTOR_TYPE_FSTART  = 0x5,   /* Frame START */
    GETHER_DESCRIPTOR_TYPE_FEND    = 0x6,   /* Frame END */
    GETHER_DESCRIPTOR_TYPE_FSINGLE = 0x7,   /* Frame SINGLE */
    /* Chain control */
    GETHER_DESCRIPTOR_TYPE_LINK    = 0x8,   /* LINK */
    GETHER_DESCRIPTOR_TYPE_LINKFIX = 0x9,   /* FIXed LINK */
    GETHER_DESCRIPTOR_TYPE_EOS     = 0xa,   /* End Of Set */
    /* HW/SW arbitration */
    GETHER_DESCRIPTOR_TYPE_FEMPTY    = 0xc, /* Frame EMPTY */
    GETHER_DESCRIPTOR_TYPE_FEMPTY_ND = 0xf, /* Frame EMPTY No Data storage */
    GETHER_DESCRIPTOR_TYPE_LEMPTY    = 0x2, /* Link EMPTY */
    GETHER_DESCRIPTOR_TYPE_EEMPTY    = 0x3, /* Eos EMPTY */
} gether_descriptor_type_t;

/** DMAC descriptor as defined in the hardware manual.
 * Structure must be packed at 1 byte.
 */
typedef struct st_gether_instance_rx_descriptor
{
    volatile uint32_t                 ds  : 12; /* Descriptor size */
    volatile uint32_t                 ti  : 1;  /* Truncation Indication */
    volatile uint32_t                 ei  : 1;  /* Error Indication */
    volatile uint32_t                 ps  : 2;  /* Padding Selection */
    volatile uint32_t                 msc : 8;  /* MAC status code */
    volatile uint32_t                 die : 4;  /* Descriptor interrupt enable */
    volatile gether_descriptor_type_t dt  : 4;  /* Descriptor type */
    volatile uint32_t                 dptr;     /* Descriptor pointer */
} gether_instance_rx_descriptor_t;

typedef struct st_gether_instance_tx_descriptor
{
    volatile uint32_t                 ds      : 12; /* Descriptor size  */
    volatile uint32_t                 tag     : 10; /* Frame tag */
    volatile uint32_t                 reseved : 1;  /* Reserved */
    volatile uint32_t                 msr     : 1;  /* MAC Status storage Request */
    volatile uint32_t                 die     : 4;  /* Descriptor interrupt enable */
    volatile gether_descriptor_type_t dt      : 4;  /* Descriptor type */
    volatile uint32_t                 dptr;         /* Descriptor pointer */
} gether_instance_tx_descriptor_t;

typedef enum e_gether_previous_link_status
{
    GETHER_PREVIOUS_LINK_STATUS_DOWN = 0, ///< Previous link status is down
    GETHER_PREVIOUS_LINK_STATUS_UP   = 1, ///< Previous link status is up
} gether_previous_link_status_t;

typedef enum e_gether_link_change
{
    GETHER_LINK_CHANGE_NO_CHANGE = 0,  ///< Link status is no change
    GETHER_LINK_CHANGE_LINK_DOWN = 1,  ///< Link status changes to down
    GETHER_LINK_CHANGE_LINK_UP   = 2,  ///< Link status changes to up
} gether_link_change_t;

typedef enum e_gether_link_establish_status
{
    GETHER_LINK_ESTABLISH_STATUS_DOWN = 0, ///< Link establish status is down
    GETHER_LINK_ESTABLISH_STATUS_UP   = 1, ///< Link establish status is up
} gether_link_establish_status_t;

/** EDMAC descriptor as defined in the hardware manual.
 * Structure must be packed at 1 byte.
 */
typedef struct st_ether_instance_descriptor
{
    volatile uint32_t status;
#if ((defined(__GNUC__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || (defined(__ARMCC_VERSION) && \
    !defined(__ARM_BIG_ENDIAN)) || (defined(__ICCARM__) && (__LITTLE_ENDIAN__)))

    /* Little endian */
    volatile uint16_t size;
    volatile uint16_t buffer_size;
#else
    /* Big endian */
    volatile uint16_t buffer_size;
    volatile uint16_t size;
#endif
    uint8_t * p_buffer;
    struct st_ether_instance_descriptor * p_next;
} ether_instance_descriptor_t;

/** GETHER control block. DO NOT INITIALIZE.  Initialization occurs when @ref ether_api_t::open is called. */
typedef struct st_ether_instance_ctrl
{
    uint32_t open;                                        ///< Used to determine if the channel is configured

    /* Configuration of gethernet module. */
    ether_cfg_t const * p_gether_cfg;                     ///< Pointer to initial configurations.

    /* Buffer of gethernet module. */
    gether_instance_tx_descriptor_t * p_tx_descriptor;    ///< Pointer to the currently referenced transmit descriptor
    gether_instance_rx_descriptor_t * p_rx_descriptor;    ///< Pointer to the currently referenced receive descriptor

    /* Interface for PHY-LSI chip. */
    void * p_reg_emac;                                    ///< Base register of gethernet controller for this channel
    void * p_reg_ether;                                   ///< Base register of DMA controller for this channel
    void * p_reg_toe;                                     ///< Base register of TOE controller for this channel

    /* Status of gethernet driver. */
    gether_previous_link_status_t  previous_link_status;  ///< Previous link status
    gether_link_change_t           link_change;           ///< status of link change
    gether_link_establish_status_t link_establish_status; ///< Current Link status

    /* Pointer to callback and optional working memory */
    void (* p_callback)(ether_callback_args_t *);
    ether_callback_args_t * p_callback_memory;

    /* Pointer to context to be passed into callback function */
    void const * p_context;
} ether_instance_ctrl_t;

typedef struct st_ether_instance_extend
{
    /* Buffer of gethernet module. */
    gether_instance_tx_descriptor_t * p_tx_descriptor; ///< Pointer to the currently referenced transmit descriptor
    gether_instance_rx_descriptor_t * p_rx_descriptor; ///< Pointer to the currently referenced receive descriptor
} ether_instance_extend_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_api_t g_ether_on_gether;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_GETHER_Open(ether_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg);

fsp_err_t R_GETHER_Close(ether_ctrl_t * const p_ctrl);

fsp_err_t R_GETHER_Read(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t * const length_bytes);

fsp_err_t R_GETHER_BufferRelease(ether_ctrl_t * const p_ctrl);

fsp_err_t R_GETHER_RxBufferUpdate(ether_ctrl_t * const p_ctrl, void * const p_buffer);

fsp_err_t R_GETHER_Write(ether_ctrl_t * const p_ctrl, void * const p_buffer, uint32_t const frame_length);

fsp_err_t R_GETHER_LinkProcess(ether_ctrl_t * const p_ctrl);

fsp_err_t R_GETHER_WakeOnLANEnable(ether_ctrl_t * const p_ctrl);

fsp_err_t R_GETHER_TxStatusGet(ether_ctrl_t * const p_ctrl, void * const p_buffer_address);

fsp_err_t R_GETHER_CallbackSet(ether_ctrl_t * const          p_api_ctrl,
                               void (                      * p_callback ) (ether_callback_args_t *),
                               void const * const            p_context,
                               ether_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end addtogroup GETHER)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_GETHER_H

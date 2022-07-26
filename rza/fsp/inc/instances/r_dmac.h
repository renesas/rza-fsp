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

/*******************************************************************************************************************//**
 * @addtogroup DMAC
 * @{
 **********************************************************************************************************************/

#ifndef R_DMAC_H
#define R_DMAC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_transfer_api.h"
#include "r_dmac_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Max configurable number of transfers in TRANSFER_MODE_NORMAL. */
#define DMAC_MAX_NORMAL_TRANSFER_LENGTH    (0xFFFFFFFF)

/** Max number of transfers per block in TRANSFER_MODE_BLOCK */
#define DMAC_MAX_BLOCK_TRANSFER_LENGTH     (0xFFFFFFFF)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function. */
typedef enum e_dmac_event
{
    DMAC_EVENT_TRANSFER_END   = 0,     ///< DMA transfer has completed.
    DMAC_EVENT_TRANSFER_ERROR = 1,     ///< A bus error occurred during DMA transfer.
} dmac_event_t;

/** Callback function parameter data. */
typedef struct st_dmac_callback_args_t
{
    dmac_event_t event;                ///< Event code
    void const * p_context;            ///< Placeholder for user data.  Set in r_transfer_t::open function in ::transfer_cfg_t.
} dmac_callback_args_t;

/** Transfer size specifies the size of each individual transfer. */
typedef enum e_dmac_transfer_size
{
    DMAC_TRANSFER_SIZE_1_BYTE   = 0,   ///< Each transfer transfers a 8-bit value.
    DMAC_TRANSFER_SIZE_2_BYTE   = 1,   ///< Each transfer transfers a 16-bit value.
    DMAC_TRANSFER_SIZE_4_BYTE   = 2,   ///< Each transfer transfers a 32-bit value.
    DMAC_TRANSFER_SIZE_8_BYTE   = 3,   ///< Each transfer transfers a 64-bit value.
    DMAC_TRANSFER_SIZE_16_BYTE  = 4,   ///< Each transfer transfers a 128-bit value.
    DMAC_TRANSFER_SIZE_32_BYTE  = 5,   ///< Each transfer transfers a 256-bit value.
    DMAC_TRANSFER_SIZE_64_BYTE  = 6,   ///< Each transfer transfers a 512-bit value.
    DMAC_TRANSFER_SIZE_128_BYTE = 7,   ///< Each transfer transfers a 1024-bit value.
} dmac_transfer_size_t;

/** DACK output mode. See RZ/T2M hardware manual Table 14.19 DMA Transfer Request Detection Operation Setting Table. */
typedef enum e_dmac_ack_mode
{
    DMAC_ACK_MODE_LEVEL_MODE       = 1, ///< Level mode.
    DMAC_ACK_MODE_BUS_CYCLE_MODE   = 2, ///< Bus cycle mode.
    DMAC_ACK_MODE_MASK_DACK_OUTPUT = 4, ///< Output is masked.
} dmac_ack_mode_t;

/** Detection method of the DMA request signal. See RZ/T2M hardware manual Table 14.19 DMA Transfer Request Detection Operation Setting Table. */
typedef enum e_dmac_detection
{
    DMAC_DETECTION_FALLING_EDGE = 1,   ///< Falling edge detection.
    DMAC_DETECTION_RISING_EDGE  = 2,   ///< Rising edge detection.
    DMAC_DETECTION_LOW_LEVEL    = 5,   ///< Low level detection.
    DMAC_DETECTION_HIGH_LEVEL   = 6,   ///< High level detection.
} dmac_detection_t;

/** DMA activation request source select. See RZ/T2M hardware manual Table 14.19 DMA Transfer Request Detection Operation Setting Table. */
typedef enum e_dmac_request_direction
{
    DMAC_REQUEST_DIRECTION_SOURCE_MODULE      = 0, ///< Requested by a transfer source module.
    DMAC_REQUEST_DIRECTION_DESTINATION_MODULE = 1, ///< Requested by a transfer destination module.
} dmac_request_direction_t;

/** Select the Next register set to be executed next. */
typedef enum e_dmac_continuous_setting
{
    DMAC_CONTINUOUS_SETTING_TRANSFER_NEXT0_ONCE              = 0x0, ///< Transfer only once using the Next0 register set.
    DMAC_CONTINUOUS_SETTING_TRANSFER_NEXT0_NEXT1_ALTERNATELY = 0x3, ///< Transfers are performed alternately with the Next0 register set and the Next1 register set.
} dmac_continuous_setting_t;

/** Register set settings. */
typedef struct st_dmac_next1_register_setting
{
    void const * p_src;                ///< Source pointer.
    void       * p_dest;               ///< Destination pointer.
    uint32_t     length;               ///< Transfer Byte.
} dmac_next1_register_setting_t;

/** DMAC channel scheduling. */
typedef enum e_dmac_channel_scheduling
{
    DMAC_CHANNEL_SCHEDULING_FIXED       = 0, ///< Fixed priority mode.
    DMAC_CHANNEL_SCHEDULING_ROUND_ROBIN = 1, ///< Round-robin mode.
} dmac_channel_scheduling_t;

/** DMAC mode setting. */
typedef enum e_dmac_mode_select
{
    DMAC_MODE_SELECT_REGISTER = 0,     ///< Register mode.
    DMAC_MODE_SELECT_LINK     = 1,     ///< Link mode.
} dmac_mode_select_t;

/** Control block used by driver. DO NOT INITIALIZE - this structure will be initialized in @ref transfer_api_t::open. */
typedef struct st_dmac_instance_ctrl
{
    uint32_t open;                     // Driver ID

    transfer_cfg_t const * p_cfg;

    /* Pointer to base register. */
    R_DMA0_Type * p_reg;
} dmac_instance_ctrl_t;

/** DMAC transfer configuration extension. This extension is required. */
typedef struct st_dmac_extended_cfg
{
    uint8_t   channel;                  ///< Channel number
    IRQn_Type dmac_int_irq;             ///< DMAC interrupt number
    uint8_t   dmac_int_ipl;             ///< DMAC interrupt priority
    uint32_t  dmac_int_irq_detect_type; ///< DMAC interrupt detection type

    /** Select which event will trigger the transfer. */
    dmac_trigger_event_t activation_source;

    /** The interrupt ID number that corresponds to the Activation Source. */
    IRQn_Type activation_irq_number;

    dmac_ack_mode_t  ack_mode;                         ///< DACK output mode
    dmac_detection_t detection_mode;                   ///< DMAC request detection method
    dmac_request_direction_t  activation_request_source_select; ///< DMAC activation request source

    dmac_mode_select_t dmac_mode;                      ///< DMAC Mode
    dmac_continuous_setting_t continuous_setting;      ///< Next register operation settings
    uint16_t transfer_interval;                        ///< DMA transfer interval
    dmac_channel_scheduling_t channel_scheduling;      ///< DMA channel scheduling

    /** Callback for transfer end interrupt. */
    void (* p_callback)(dmac_callback_args_t * cb_data);

    /** Placeholder for user data.  Passed to the user p_callback in ::dmac_callback_args_t. */
    void const * p_context;

    /** Communication module handler that is called when a transfer end interrupt. */
    void (* p_peripheral_module_handler)(IRQn_Type irq);
} dmac_extended_cfg_t;

/** DMAC transfer configuration extension. This extension is required. */
typedef struct st_dmac_extended_info
{
    /** Select number of source bytes to transfer at once. */
    dmac_transfer_size_t src_size;

    /** Select number of destnination bytes to transfer at once. */
    dmac_transfer_size_t dest_size;

    /** Next1 Register set settings */
    dmac_next1_register_setting_t * p_next1_register_setting;
} dmac_extended_info_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const transfer_api_t g_transfer_on_dmac;

/** @endcond */

/***********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_DMAC_Open(transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg);
fsp_err_t R_DMAC_Reconfigure(transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info);
fsp_err_t R_DMAC_Reset(transfer_ctrl_t * const p_api_ctrl,
                       void const * volatile   p_src,
                       void * volatile         p_dest,
                       uint16_t const          num_transfers);
fsp_err_t R_DMAC_SoftwareStart(transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode);
fsp_err_t R_DMAC_SoftwareStop(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_Enable(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_Disable(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_InfoGet(transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_info);
fsp_err_t R_DMAC_Close(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_Reload(transfer_ctrl_t * const p_api_ctrl,
                        void const            * p_src,
                        void                  * p_dest,
                        uint32_t const          num_transfers);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup DMAC)
 **********************************************************************************************************************/

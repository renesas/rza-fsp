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
 * @addtogroup LCDC
 * @{
 **********************************************************************************************************************/
#ifndef R_LCDC_H_
#define R_LCDC_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_display_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** LCDC hardware specific configuration */
typedef struct st_lcdc_extended_cfg
{
    uint8_t   frame_end_ipl;           ///< Frame end interrupt priority
    uint8_t   underrun_ipl;            ///< Under run interrupt priority
    IRQn_Type frame_end_irq;           ///< Frame end interrupt vector
    IRQn_Type underrun_irq;            ///< Under run interrupt vector
} lcdc_extended_cfg_t;

/* CRU context struct for callback function */
typedef struct st_display_ctrl
{
    void const * p_context;
} lcdc_ctrl_t;

/** Display control block.  DO NOT INITIALIZE. */
typedef struct st_lcdc_instance_ctrl
{
    display_state_t state;                                 // Status of LCDC module

    /* Parameters to Event processing for display devices */
    void (* p_callback)(display_callback_args_t * p_args); // Pointer to callback function
    void const          * p_context;                       // Pointer to the higher level device context
    const display_cfg_t * p_cfg;                           // Pointer to initial configurations
} lcdc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern const display_api_t g_display_on_lcdc;

/** @cond INC_HEADER_DEFS_SEC */

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_LCDC_Open(display_ctrl_t * const p_api_ctrl, display_cfg_t const * const p_cfg);
fsp_err_t R_LCDC_Close(display_ctrl_t * const p_api_ctrl);
fsp_err_t R_LCDC_Start(display_ctrl_t * const p_api_ctrl);
fsp_err_t R_LCDC_Stop(display_ctrl_t * const p_api_ctrl);
fsp_err_t R_LCDC_LayerChange(display_ctrl_t const * const        p_api_ctrl,
                             display_runtime_cfg_t const * const p_cfg,
                             display_frame_layer_t               layer);
fsp_err_t R_LCDC_BufferChange(display_ctrl_t const * const p_api_ctrl,
                              uint8_t * const              framebuffer,
                              display_frame_layer_t        layer);
fsp_err_t R_LCDC_ColorKeySet(display_ctrl_t const * const p_api_ctrl,
                             display_colorkeying_layer_t  ck_cfg,
                             display_frame_layer_t        layer);
fsp_err_t R_LCDC_StatusGet(display_ctrl_t const * const p_api_ctrl, display_status_t * const p_status);

/*******************************************************************************************************************//**
 * @} (end defgroup LCDC)
 **********************************************************************************************************************/

#endif                                 /* R_LCDC_H_ */

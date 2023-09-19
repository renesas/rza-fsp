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
 * @addtogroup ISU
 * @{
 **********************************************************************************************************************/
#ifndef FSP_INC_INSTANCES_R_ISU_H_
#define FSP_INC_INSTANCES_R_ISU_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_isu_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Image scaling control block.  DO NOT INITIALIZE. */
/** ISU hardware specific configuration */
typedef struct st_isu_extended_cfg
{
    uint8_t   isu_frame_end_ipl;       ///< Image conversion interrupt priority
    IRQn_Type isu_frame_end_irq;       ///< Image conversion IRQ number
} isu_extended_cfg_t;

typedef struct st_isu_instance_ctrl
{
    isu_state_t state;                                 // Status of ISU module

    /* Parameters to Event processing for scaling devices */
    void (* p_callback)(isu_callback_args_t * p_args); // Pointer to callback function
    void const      * p_context;                       // Pointer to the higher level device context
    const isu_cfg_t * p_cfg;                           // Pointer to initial configurations
} isu_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern const isu_api_t g_isu_on_isu;

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_ISU_Open(isu_ctrl_t * const p_api_ctrl, isu_cfg_t const * const p_cfg);
fsp_err_t R_ISU_Close(isu_ctrl_t * const p_api_ctrl);
fsp_err_t R_ISU_Start(isu_ctrl_t * const p_api_ctrl);
fsp_err_t R_ISU_ChangeCfg(isu_ctrl_t * const p_api_ctrl, isu_runtime_cfg_t * const p_runtime_cfg);

/*******************************************************************************************************************//**
 * @} (end defgroup ISU)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */

FSP_FOOTER
#endif                                 /* FSP_INC_INSTANCES_R_ISU_H_ */

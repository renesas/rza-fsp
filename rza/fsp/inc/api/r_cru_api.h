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
 * @ingroup RENESAS_INTERFACES
 * @defgroup CAMERA_API Camera Interface
 * @brief Interface for camera.
 *
 * @section Camera_API_SUMMARY Summary
 * The Camera interface provides a general API for configuring and controlling camera panels.
 *
 * Implemented by:
 * @ref CRU
 *
 * @{
 **********************************************************************************************************************/

#ifndef FSP_INC_API_R_CRU_API_H_
#define FSP_INC_API_R_CRU_API_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CAMERA states. */
typedef enum e_camera_state
{
    CAMERA_STATE_IDLE        = 0,      ///< CAMERA is idle
    CAMERA_STATE_IN_PROGRESS = 1,      ///< CAMERA capture in progress
    CAMERA_STATE_BUSY        = 2,      ///< CAMERA reset in progress
} camera_state_t;

/** CAMERA status */
typedef struct e_camera_status_t
{
    camera_state_t state;              ///< Current state
    uint32_t     * p_buffer;           ///< Pointer to active buffer
    uint32_t       data_size;          ///< Size of data written at the end of one-frame capture
} camera_status_t;

/** CAMERA callback event - see implimentation */
typedef uint32_t camera_event_t;

/** CAMERA callback function parameter data */
typedef struct st_camera_callback_args
{
    camera_event_t event;              ///< Event causing the callback
    uint8_t      * p_buffer;           ///< Pointer to buffer that contains captured data
    void const   * p_context;          ///< Placeholder for user data.  Set in @ref cru_api_t::open function in @ref cru_cfg_t.
} camera_callback_args_t;

/** Buffer addresses */
typedef struct st_cru_buffer_cfg
{
    uint8_t * pp_buffer[8];            ///< Pointer to array of buffer pointers
    uint8_t   num_buffers;             ///< Number of buffers to use
} camera_buffer_cfg_t;

/** CRU configuration parameters. */
typedef struct st_cru_cfg
{
    uint16_t            x_capture_start_pixel;            ///< Horizontal position to start capture
    uint16_t            x_capture_pixels;                 ///< Number of horizontal pixels to capture
    uint16_t            y_capture_start_pixel;            ///< Vertical position to start capture
    uint16_t            y_capture_pixels;                 ///< Number of vertical lines/pixels to capture
    camera_buffer_cfg_t buffer_cfg;                       ///< Buffer Configuration
    void (* p_callback)(camera_callback_args_t * p_args); ///< Callback provided when a image conversion ISR occurs.
    void const * p_context;
    void const * p_extend;                                ///< Placeholder for user data.
} cru_cfg_t;

/** CRU control block.  Allocate an instance specific control block to pass into the CRU API calls.
 * @par Implemented as
 * - cru_instance_ctrl_t
 */
typedef void cru_ctrl_t;

/** CRU functions implemented at the HAL layer will follow this API. */
typedef struct st_cru_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_CRU_Open()
     *
     * @note To reconfigure after calling this function, call @ref cru_api_t::close first.
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(cru_ctrl_t * const p_ctrl, cru_cfg_t const * const p_cfg);

    /** Closes the driver and allows reconfiguration. May reduce power consumption.
     * @par Implemented as
     * - @ref R_CRU_Close()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(cru_ctrl_t * const p_ctrl);

    /** Start a capture.
     * @par Implemented as
     * - @ref R_CRU_CaptureStart()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* captureStart)(cru_ctrl_t * const p_ctrl);

    /** Stop a capture
     * @par Implemented as
     * - @ref R_CRU_CaptureStop()
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* captureStop)(cru_ctrl_t * const p_ctrl);

    /** Check scan status.
     * @par Implemented as
     * - @ref R_CRU_StatusGet()
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     * @param[out] p_status Pointer to store current status in
     */
    fsp_err_t (* statusGet)(cru_ctrl_t * const p_ctrl, camera_status_t * p_status);
} cru_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_cru_instance
{
    cru_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    cru_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    cru_api_t const * p_api;           ///< Pointer to the API structure for this instance
} camera_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* FSP_INC_API_R_CRU_API_H_ */

/*******************************************************************************************************************//**
 * @} (end defgroup CRU_API)
 **********************************************************************************************************************/

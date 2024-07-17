/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RM_GUIX_PORT
 * @{
 **********************************************************************************************************************/

#ifndef RM_GUIX_PORT_H
#define RM_GUIX_PORT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "gx_api.h"
#include "r_display_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/* Includes GUIX Display component */
#include "gx_display.h"

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Low level device code for the GUIX */
typedef enum e_rm_guix_port_device
{
    RM_GUIX_PORT_DEVICE_NONE    = 0,   ///< Non hardware
    RM_GUIX_PORT_DEVICE_DISPLAY = 1,   ///< Display device
    RM_GUIX_PORT_DEVICE_DRW     = 2,   ///< 2D Graphics Engine
    RM_GUIX_PORT_DEVICE_JPEG    = 3,   ///< JPEG Codec
} rm_guix_port_device_t;

/** Display event codes */
typedef enum e_rm_guix_port_event
{
    RM_GUIX_PORT_EVENT_ERROR         = 1, ///< Low level driver error occurs
    RM_GUIX_PORT_EVENT_DISPLAY_VSYNC = 2, ///< Display interface VSYNC
    RM_GUIX_PORT_EVENT_UNDERFLOW     = 3, ///< Display interface underflow
} rm_guix_port_event_t;

/** Callback arguments for the FSP GUIX Port */
typedef struct st_rm_guix_port_callback_args
{
    rm_guix_port_device_t device;      ///< Device code
    rm_guix_port_event_t  event;       ///< Event code of the low level hardware
    uint32_t              error;       ///< Error code if RM_GUIX_PORT_EVENT_ERROR
} rm_guix_port_callback_args_t;

/* Configuration structure for the FSP GUIX Port */
typedef struct st_rm_guix_port_cfg
{
    display_instance_t  * p_display_instance;                   // Pointer to a display instance
    display_frame_layer_t inherit_frame_layer;                  // Configured Inherit Screen Layer
    void                * p_canvas;                             // Pointer to a canvas(reserved)
    void                * p_framebuffer_a;                      // Pointer to a frame buffer(A)
    void                * p_framebuffer_b;                      // Pointer to a frame buffer(B)
    void (* p_callback)(rm_guix_port_callback_args_t * p_args); // Pointer to callback function
    void   * p_context;                                         // Pointer to a context
    void   * p_jpegbuffer;                                      // Pointer to a JPEG work buffer
    uint32_t jpegbuffer_size;                                   // Size of a JPEG work buffer
    int32_t  rotation_angle;                                    // Screen rotation angle
    void   * p_jpeg_instance;                                   // Pointer to a JPEG Codec driver instance
} rm_guix_port_cfg_t;

/* Instance control block for GUIX Port */
typedef struct st_rm_guix_port_instance_ctrl
{
    GX_DISPLAY          * p_display;                            // Pointer to the GUIX display context
    display_instance_t  * p_display_instance;                   // Pointer to a display instance
    display_frame_layer_t inherit_frame_layer;                  // Configured Inherit Screen Layer
    void                * p_framebuffer_read;                   // Pointer to a frame buffer (for displaying)
    void                * p_framebuffer_write;                  // Pointer to a frame buffer (for rendering)
    void (* p_callback)(rm_guix_port_callback_args_t * p_args); // Pointer to callback function
    void   * p_context;                                         // Pointer to a context
    bool     rendering_enable;                                  // Sync flag between Rendering and displaying
    bool     display_list_flushed;                              // Flag to show the display list is flushed
    void   * p_jpegbuffer;                                      // Pointer to a JPEG work buffer
    uint32_t jpegbuffer_size;                                   // Size of a JPEG work buffer
    int32_t  rotation_angle;                                    // Screen rotation angle
    void   * p_jpeg_instance;                                   // Pointer to a JPEG Codec instance
} rm_guix_port_instance_ctrl_t;

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_GUIX_PORT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // RM_GUIX_PORT_H

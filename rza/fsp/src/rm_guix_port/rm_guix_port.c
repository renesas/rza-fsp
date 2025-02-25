/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_guix_port.h"

#include "r_lcdc.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Mutex timeout count */
#define RM_GUIX_PORT_MUTEX_WAIT_TIMER             (300)

/** Display device timeout count */
#define RM_GUIX_PORT_DISPLAY_HW_WAIT_COUNT_MAX    (5000)

/** A macro to mean GUIX color format invalid. */
#ifndef GX_COLOR_FORMAT_INVALID
 #define GX_COLOR_FORMAT_INVALID                  (0)
#endif

/***********************************************************************************************************************
 * External definitions
 **********************************************************************************************************************/
extern rm_guix_port_instance_ctrl_t _g_guix_port_ctrl;
extern rm_guix_port_cfg_t const     _g_guix_port_cfg;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
fsp_err_t rm_guix_port_hw_deinitialize(void);

static fsp_err_t rm_guix_port_driver_setup(GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl);

static fsp_err_t rm_guix_port_display_open(rm_guix_port_instance_ctrl_t * const p_ctrl);

static void rm_guix_port_canvas_clear(GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl);

void _rm_guix_port_display_callback(display_callback_args_t * p_args);

/* GUIX common callback functions setup function */
extern UINT _gx_rz_display_driver_setup(GX_DISPLAY * display);

/* GUIX FSP Port callback functions */
void rm_guix_port_frame_pointers_get(ULONG display_handle, GX_UBYTE ** pp_visible, GX_UBYTE ** pp_working);

void rm_guix_port_frame_toggle(ULONG display_handle, GX_BYTE ** pp_visible_frame);

INT rm_guix_port_display_rotation_get(ULONG handle);

void rm_guix_port_display_actual_size_get(ULONG display_handle, INT * p_width, INT * p_height);

void rm_guix_port_display_8bit_palette_assign(ULONG display_handle);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static TX_SEMAPHORE gx_renesas_display_semaphore;

/* LUT for GX_COLOR_FORMAT_ macros corresponding to display_in_format_t enum values */
static const GX_VALUE gx_display_color_format_lut[] =
{
    GX_COLOR_FORMAT_32ARGB,            // ARGB8888, 32 bits
    GX_COLOR_FORMAT_24XRGB,            // RGB888,   32 bits
    GX_COLOR_FORMAT_565RGB,            // RGB565,   16 bits
    GX_COLOR_FORMAT_INVALID,           // ARGB1555, 16 bits
    GX_COLOR_FORMAT_4444ARGB,          // ARGB4444, 16 bits
    GX_COLOR_FORMAT_8BIT_PALETTE,      // CLUT8
    GX_COLOR_FORMAT_INVALID,           // CLUT4
    GX_COLOR_FORMAT_INVALID,           // CLUT1
    GX_COLOR_FORMAT_32RGBA,            // RGBA8888,                        32 bits
    GX_COLOR_FORMAT_24BGR,             // BGR888,                          24 bits
    GX_COLOR_FORMAT_24RGB,             // RGB888,                          24 bits
    GX_COLOR_FORMAT_32ABGR,            // ABGR8888,                        32 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr444 interleaved,             24 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr422 interleaved type0 UYVY,  16 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr422 interleaved type0 YUY2,  16 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr422 interleaved type0 YVYU,  16 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr420 interleaved type1,       16 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr420 interleaved,             12 bits
    GX_COLOR_FORMAT_INVALID,           // YCbCr420 planar,                  16bits
};

/***********************************************************************************************************************
 * Functions
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RM_GUIX_PORT
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Callback function to be passed to gx_studio_display_configure in order to start hardware modules.
 *
 * Example:
 * @snippet rm_guix_port_example.c rm_guix_port_hw_initialize
 *
 * @note This function should only be called by GUIX.
 *
 * @retval  GX_SUCCESS    Device driver setup is successfully done.
 * @retval  GX_FAILURE    Device driver setup failed.
 **********************************************************************************************************************/
UINT rm_guix_port_hw_initialize (GX_DISPLAY * p_display)
{
    UINT      status;
    fsp_err_t error;

    /* Returns if GUIX display driver context is NULL. */
    if (NULL == p_display)
    {
        return (UINT) GX_FAILURE;
    }

    /** Creates a semaphore for frame buffer flip */
    status = tx_semaphore_create(&gx_renesas_display_semaphore, (CHAR *) "rm_guix_drv_display_sem", 0);
    if (TX_SUCCESS != status)
    {
        return GX_FAILURE;
    }

    /** Initializes the RM_GUIX_PORT control block */
    _g_guix_port_ctrl.p_display_instance  = _g_guix_port_cfg.p_display_instance;
    _g_guix_port_ctrl.p_callback          = _g_guix_port_cfg.p_callback;
    _g_guix_port_ctrl.inherit_frame_layer = _g_guix_port_cfg.inherit_frame_layer;
    _g_guix_port_ctrl.p_framebuffer_read  = _g_guix_port_cfg.p_framebuffer_a;
    if (NULL != _g_guix_port_cfg.p_framebuffer_b)
    {
        _g_guix_port_ctrl.p_framebuffer_write = _g_guix_port_cfg.p_framebuffer_b;
    }
    else
    {
        /* If frame buffer B is NULL, specify frame buffer A instead. */
        _g_guix_port_ctrl.p_framebuffer_write = _g_guix_port_cfg.p_framebuffer_a;
    }

    _g_guix_port_ctrl.rendering_enable = false;
    _g_guix_port_ctrl.rotation_angle   = _g_guix_port_cfg.rotation_angle;

    /* Get the GUIX color format corresponding to the format configured for the Display module */
    p_display->gx_display_color_format =
        (GX_UBYTE) gx_display_color_format_lut[_g_guix_port_ctrl.p_display_instance->p_cfg->input[0].format];

    /* Check that the configured Display input format is compatible with GUIX */
    if (GX_COLOR_FORMAT_INVALID == (INT) p_display->gx_display_color_format)
    {
        FSP_ERROR_LOG(FSP_ERR_INVALID_ARGUMENT);

        tx_semaphore_delete(&gx_renesas_display_semaphore);

        return (UINT) GX_FAILURE;
    }

    /** Copies the GX_DISPLAY context for later use. */
    _g_guix_port_ctrl.p_display = p_display;

    /** Setup GUIX low level device drivers */
    error = rm_guix_port_driver_setup(p_display, &_g_guix_port_ctrl);
    if (FSP_SUCCESS != error)
    {
        FSP_ERROR_LOG(error);

        tx_semaphore_delete(&gx_renesas_display_semaphore);

        return (UINT) GX_FAILURE;
    }

    return (UINT) GX_SUCCESS;
}                                      /* End of function rm_guix_port_hw_initialize() */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_GUIX_PORT)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Optional function allowing clean deinitialization of hardware peripherals and semaphores if GUIX is stopped.
 *
 * @retval  FSP_SUCCESS                    Closed the module successfully.
 **********************************************************************************************************************/
fsp_err_t rm_guix_port_hw_deinitialize ()
{
    /** Stop display */
    uint32_t attempts = 10;
    while (FSP_SUCCESS != R_LCDC_Close(_g_guix_port_ctrl.p_display_instance->p_ctrl) && (attempts-- > 0))
    {
        tx_thread_sleep(1);
    }

    /** Delete semaphores */
    tx_semaphore_delete(&gx_renesas_display_semaphore);

    return FSP_SUCCESS;
}                                      /* End of function rm_guix_port_hw_deinitialize() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get frame buffer address.
 * This function is called by GUIX.
 * @param[in]     display_handle    Pointer to the RM_GUIX_PORT control block
 * @param[in,out] pp_visible        Pointer to a pointer to store visible frame buffer
 * @param[in,out] pp_working        Pointer to a pointer to store working frame buffer
 * @note NULL check for the frame buffers are not performed. This function does not expect NULL for them but does
 *       nothing even if the caller function passed NULL.
 **********************************************************************************************************************/
void rm_guix_port_frame_pointers_get (ULONG display_handle, GX_UBYTE ** pp_visible, GX_UBYTE ** pp_working)
{
    /** Gets control block */
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (uintptr_t) (display_handle);

    *pp_visible = p_ctrl->p_framebuffer_read;
    *pp_working = p_ctrl->p_framebuffer_write;
}                                      /* End of function rm_guix_port_frame_pointers_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, toggle frame buffer.
 * This function calls display_api_t::layerChange to flips the frame buffer and tx_semaphore_get to suspend a thread
 * until a display device going into blanking period.
 * This function is called by GUIX when following functions are executed.
 * - _gx_canvas_drawing_complete()
 * - _gx_system_canvas_refresh()
 * @param[in]     display_handle     Pointer to the RM_GUIX_PORT control block
 * @param[in,out] pp_visible_frame   Pointer to a pointer to store visible frame buffer
 **********************************************************************************************************************/
void rm_guix_port_frame_toggle (ULONG display_handle, GX_BYTE ** pp_visible_frame)
{
    /** Gets control block */
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (uintptr_t) display_handle;

    /** Requests display driver to toggle frame buffer */
    R_LCDC_BufferChange(p_ctrl->p_display_instance->p_ctrl, p_ctrl->p_framebuffer_write, p_ctrl->inherit_frame_layer);

    /** Updates the frame buffer addresses */
    void * p_next_temp = p_ctrl->p_framebuffer_read;
    p_ctrl->p_framebuffer_read  = p_ctrl->p_framebuffer_write;
    p_ctrl->p_framebuffer_write = p_next_temp;

    /** Returns the address of visible frame buffer */
    *(pp_visible_frame) = (GX_BYTE *) p_next_temp;

    /** Sets rendering_enable flag to the display driver to synchronize the timing */
    p_ctrl->rendering_enable = true;

    /** Waits until the set of semaphore which is set when the display device going into blanking period */
    tx_semaphore_get(&gx_renesas_display_semaphore, TX_WAIT_FOREVER);
}                                      /* End of function rm_guix_port_frame_toggle() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, Display interface setup function
 * This function calls display_api_t::open and display_api_t::start.
 * This function is called by rm_guix_port_driver_setup().
 * @param[in]    p_ctrl       Pointer to a RM_GUIX_PORT control block
 * @retval  FSP_SUCCESS       Display device was opened successfully.
 *
 * See @ref Common_Error_Codes for other possible return codes. This function calls
 * display_api_t::open and display_api_t::start.
 *
 * @note This function is only allowed to be called by rm_guix_port_driver_setup().
 * @note Parameter check is not required since it is done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static fsp_err_t rm_guix_port_display_open (rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t            error;
    display_instance_t * p_display_instance = p_ctrl->p_display_instance;

    /**  Display driver open */
    error = R_LCDC_Open(p_display_instance->p_ctrl, p_display_instance->p_cfg);
    if (FSP_SUCCESS == error)
    {
        /**  Display driver start */
        error = R_LCDC_Start(p_display_instance->p_ctrl);
    }

    return error;
}                                      /* End of function rm_guix_port_display_open() */

/*******************************************************************************************************************//**
 * @brief  Setups GUIX display driver.
 * This function calls _gx_rz_display_driver_setup(), which is generated by GUIX Studio, and calls subroutines
 * rm_guix_port_d2_open() and rm_guix_port_display_open() to setup graphics hardwares, also calls rm_guix_port_canvas_clear to clear
 * a canvas.
 * This function is called by rm_guix_port_hw_initialize().
 * @param[in]    p_display     Pointer to the GUIX display control block
 * @param[in]    p_ctrl        Pointer to a RM_GUIX_PORT control block
 * @retval  FSP_SUCCESS  The GUIX drivers are successfully configured.
 *
 * See @ref Common_Error_Codes for other possible return codes.
 * This function calls display_api_t::open and display_api_t::start.
 *
 * @note Parameter checks are not required since they are done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static fsp_err_t rm_guix_port_driver_setup (GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    fsp_err_t error;

    /** Setups GUIX draw functions */
    _gx_rz_display_driver_setup(p_display);

    /** Clear canvas with zero */
    rm_guix_port_canvas_clear(p_display, p_ctrl);

    /** Setups Display interface */
    error = rm_guix_port_display_open(p_ctrl);
    FSP_ERROR_RETURN(error == FSP_SUCCESS, error);

    /** Registers the RM_GUIX_PORT context to GUIX display handle */
    p_display->gx_display_handle = (ULONG) (uintptr_t) p_ctrl;

    return FSP_SUCCESS;
}                                      /* End of function rm_guix_port_driver_setup() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, Canvas clear function, clear the frame buffers with zero.
 * This function is called by rm_guix_port_driver_setup().
 * @param[in]    p_display    Pointer to a GUIX display control block
 * @param[in]    p_ctrl       Pointer to a RM_GUIX_PORT control block
 * @retval  none.
 * @note This function is designed to be called by rm_guix_port_driver_setup().
 * @note Parameter checks are not required since they are done in rm_guix_port_hw_initialize().
 **********************************************************************************************************************/
static void rm_guix_port_canvas_clear (GX_DISPLAY * p_display, rm_guix_port_instance_ctrl_t * const p_ctrl)
{
    int32_t divisor;
    ULONG * put;

    INT format = (INT) p_display->gx_display_color_format;

    /* Determine how many pixels are in one 32-bit span */
    if ((GX_COLOR_FORMAT_24XRGB == format) || (GX_COLOR_FORMAT_32ARGB == format))
    {
        divisor = 1;
    }
    else if ((GX_COLOR_FORMAT_565RGB == format) || (GX_COLOR_FORMAT_4444ARGB == format))
    {
        divisor = 2;
    }
    else
    {
        divisor = 4;
    }

    /** Clear the frame buffers */

    int32_t len = (p_display->gx_display_width * p_display->gx_display_height) / divisor;
    put = (ULONG *) p_ctrl->p_framebuffer_read;
    for (int32_t loop = 0; loop < len; loop++)
    {
        *put = 0UL;
        ++put;
    }

    put = (ULONG *) p_ctrl->p_framebuffer_write;
    for (int32_t loop = 0; loop < len; loop++)
    {
        *put = 0UL;
        ++put;
    }
}                                      /* End of function rm_guix_port_canvas_clear() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get screen rotation angle.
 * This function is called by GUIX.
 * @param[in]   display_handle      Pointer to the RM_GUIX_PORT control block
 * @retval      Angle               Screen rotation angle. {0, 90, 180 or 270} is supposed to be returned.
 **********************************************************************************************************************/
INT rm_guix_port_display_rotation_get (ULONG display_handle)
{
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (uintptr_t) (display_handle);

    return (INT) (p_ctrl->rotation_angle);
}                                      /* End of function rm_guix_port_display_rotation_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, get active video screen size.
 * This function is called by GUIX.
 * @param[in]     display_handle     Pointer to the RM_GUIX_PORT control block
 * @param[out]    p_width            Pointer to an int size memory to return screen width in pixels
 * @param[out]    p_height           Pointer to an int size memory to return screen height in pixels
 **********************************************************************************************************************/
void rm_guix_port_display_actual_size_get (ULONG display_handle, INT * p_width, INT * p_height)
{
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (uintptr_t) (display_handle);
    *p_width  = (INT) p_ctrl->p_display_instance->p_cfg->output.htiming.display_cyc;
    *p_height = (INT) p_ctrl->p_display_instance->p_cfg->output.vtiming.display_cyc;
}                                      /* End of function rm_guix_port_display_actual_size_get() */

/*******************************************************************************************************************//**
 * @brief  GUIX Port for FSP, set CLUT table in the display module by calling display_api_t::clut.
 * This function is called by GUIX.
 * @param[in]     display_handle     Pointer to the RM_GUIX_PORT control block
 **********************************************************************************************************************/
void rm_guix_port_display_8bit_palette_assign (ULONG display_handle)
{
    rm_guix_port_instance_ctrl_t * p_ctrl = (rm_guix_port_instance_ctrl_t *) (uintptr_t) (display_handle);
    display_clut_cfg_t             clut_cfg;

    clut_cfg.p_base = (uint32_t *) p_ctrl->p_display->gx_display_palette;
    clut_cfg.start  = (uint16_t) 0;
    clut_cfg.size   = (uint16_t) p_ctrl->p_display->gx_display_palette_size;

    /* Write palette data to LCDC CLUT */
    R_LCDC_ClutUpdate(p_ctrl->p_display_instance->p_ctrl, &clut_cfg, p_ctrl->inherit_frame_layer);
}                                      /* End of function rm_guix_port_display_8bit_palette_assign() */

/*******************************************************************************************************************//**
 * @brief  Callback function for GUIX Port. This function is called back from a Display HAL driver module.
 * If DISPLAY_EVENT_LINE_DETECTION is returned from Display HAL driver module, it sets the semaphore for rendering and
 * displaying synchronization. This function invokes a user callback function if registered through rm_guix_port_hw_initialize()
 * function.
 * @param[in]    p_args   Pointer to the Display interface callback argument.
 **********************************************************************************************************************/
void _rm_guix_port_display_callback (display_callback_args_t * p_args)
{
    rm_guix_port_callback_args_t cb_arg;

    if (DISPLAY_EVENT_FRAME_END == p_args->event)
    {
        if (_g_guix_port_ctrl.rendering_enable)
        {
            /** Let GUIX know the display been in blanking period */

            /* Return code not checked here as this RTOS object is called inside callback
             * function and there is no return from it */
            tx_semaphore_ceiling_put(&gx_renesas_display_semaphore, 1UL);
            _g_guix_port_ctrl.rendering_enable = false;
        }

        cb_arg.event = RM_GUIX_PORT_EVENT_DISPLAY_VSYNC;
    }
    else if (DISPLAY_EVENT_GR1_UNDERFLOW == p_args->event)
    {
        cb_arg.event = RM_GUIX_PORT_EVENT_UNDERFLOW;
    }
    else
    {
        /* Do nothing */
    }

    /** Invoke a user callback function if registered */
    if (_g_guix_port_ctrl.p_callback)
    {
        cb_arg.device = RM_GUIX_PORT_DEVICE_DISPLAY;
        cb_arg.error  = FSP_SUCCESS;
        _g_guix_port_ctrl.p_callback(&cb_arg);
    }
}                                      /* End of function rm_guix_port_callback() */

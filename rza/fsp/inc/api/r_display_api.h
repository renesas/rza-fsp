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
 * @defgroup DISPLAY_API Display Interface
 * @brief Interface for display panels.
 *
 * @section DISPLAY_API_SUMMARY Summary
 * The Display interface provides a general API for configuring and controlling display panels.
 *
 * Implemented by:
 * @ref LCDC
 *
 * @{
 **********************************************************************************************************************/
#ifndef R_DISPLAY_API_H
#define R_DISPLAY_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Display frame number */
typedef enum e_display_frame_layer
{
    DISPLAY_FRAME_LAYER_1 = 0,         ///< Frame layer 1
    DISPLAY_FRAME_LAYER_2 = 1          ///< Frame layer 2
} display_frame_layer_t;

/** Display interface operation state */
typedef enum e_display_state
{
    DISPLAY_STATE_CLOSED     = 0,      ///< Display closed
    DISPLAY_STATE_OPENED     = 1,      ///< Display opened
    DISPLAY_STATE_DISPLAYING = 2       ///< Displaying
} display_state_t;

/** Display event codes */
typedef enum e_display_event
{
    DISPLAY_EVENT_UNDERFLOW      = 1,  ///< Graphics frame underflow occurs
    DISPLAY_EVENT_LINE_DETECTION = 2,  ///< Specified line is processed
    DISPLAY_EVENT_FRAME_END      = 3,  ///< Frame end is processed
} display_event_t;

/** Input format setting */
typedef enum e_display_in_format
{
    DISPLAY_IN_FORMAT_32BITS_ARGB8888 = 0,                         ///< ARGB8888, 32 bits
    DISPLAY_IN_FORMAT_32BITS_RGB888   = 1,                         ///< RGB888,   32 bits
    DISPLAY_IN_FORMAT_16BITS_RGB565   = 2,                         ///< RGB565,   16 bits
    DISPLAY_IN_FORMAT_16BITS_ARGB1555 = 3,                         ///< ARGB1555, 16 bits
    DISPLAY_IN_FORMAT_16BITS_ARGB4444 = 4,                         ///< ARGB4444, 16 bits

    DISPLAY_IN_FORMAT_CLUT8 = 5,                                   ///< CLUT8
    DISPLAY_IN_FORMAT_CLUT4 = 6,                                   ///< CLUT4
    DISPLAY_IN_FORMAT_CLUT1 = 7,                                   ///< CLUT1

    DISPLAY_IN_FORMAT_32BITS_RGBA8888                        = 8,  ///< RGBA8888,                        32 bits
    DISPLAY_IN_FORMAT_24BITS_BGR888                          = 9,  ///< BGR888,                          24 bits
    DISPLAY_IN_FORMAT_24BITS_RGB888                          = 10, ///< RGB888,                          24 bits
    DISPLAY_IN_FORMAT_32BITS_ABGR8888                        = 11, ///< ABGR8888,                        32 bits
    DISPLAY_IN_FORMAT_24BITS_YCBCR444_INTERLEAVED            = 12, ///< YCbCr444 interleaved,             24 bits
    DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_UYVY = 13, ///< YCbCr422 interleaved type0 UYVY,  16 bits
    DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_YUY2 = 14, ///< YCbCr422 interleaved type0 YUY2,  16 bits
    DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_YVYU = 15, ///< YCbCr422 interleaved type0 YVYU,  16 bits
    DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE1      = 16, ///< YCbCr420 interleaved type1,       16 bits
    DISPLAY_IN_FORMAT_16BITS_YCBCR420_INTERLEAVED            = 17, ///< YCbCr420 interleaved,             12 bits
    DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR                 = 18, ///< YCbCr420 planar,                  16bits

    /** All other options start at this value. */
    DISPLAY_IN_FORMAT_CUSTOM = 0x80,
} display_in_format_t;

/** Output format setting */
typedef enum e_display_out_format
{
    DISPLAY_OUT_FORMAT_24BITS_RGB888 = 0, ///< RGB888, 24 bits
    DISPLAY_OUT_FORMAT_18BITS_RGB666 = 1, ///< RGB666, 18 bits
    DISPLAY_OUT_FORMAT_16BITS_RGB565 = 2, ///< RGB565, 16 bits
    DISPLAY_OUT_FORMAT_8BITS_SERIAL  = 3, ///< SERIAL, 8 bits

    /** All other options start at this value. */
    DISPLAY_OUT_FORMAT_CUSTOM = 0x80,
} display_out_format_t;

/** Polarity of a signal select */
typedef enum st_display_signal_polarity
{
    DISPLAY_SIGNAL_POLARITY_LOACTIVE,  ///< Low active signal
    DISPLAY_SIGNAL_POLARITY_HIACTIVE,  ///< High active signal
} display_signal_polarity_t;

/** Signal synchronization edge select */
typedef enum e_display_sync_edge
{
    DISPLAY_SIGNAL_SYNC_EDGE_RISING,   ///< Signal is synchronized to rising edge
    DISPLAY_SIGNAL_SYNC_EDGE_FALLING,  ///< Signal is synchronized to falling edge
} display_sync_edge_t;

/** Color Keying enable or disable */
typedef enum e_display_color_keying
{
    DISPLAY_COLOR_KEYING_DISABLE = 0,  ///< Color keying disable
    DISPLAY_COLOR_KEYING_ENABLE  = 1   ///< Color keying enable
} display_color_keying_t;

typedef enum e_display_data_swap
{
    DISPLAY_DATA_SWAP_8BIT  = 1,
    DISPLAY_DATA_SWAP_16BIT = 2,
    DISPLAY_DATA_SWAP_32BIT = 4,
    DISPLAY_DATA_SWAP_64BIT = 8,
} display_data_swap_t;

/** Display signal timing setting */
typedef struct st_display_timing
{
    uint16_t total_cyc;                      ///< Total cycles in one line or total lines in one frame
    uint16_t display_cyc;                    ///< Active video cycles or lines
    uint16_t back_porch;                     ///< Back porch cycles or lines
    uint16_t sync_width;                     ///< Sync signal asserting width
    display_signal_polarity_t sync_polarity; ///< Sync signal polarity
} display_timing_t;

/** RGB Color setting */
typedef struct st_display_color
{
    union
    {
        uint32_t argb;                 ///< Entire color
        struct
        {
            uint8_t b;                 ///< blue
            uint8_t g;                 ///< green
            uint8_t r;                 ///< red
            uint8_t a;                 ///< alpha
        } byte;
    };
} display_color_t;

/** Color Keying enable or disable */
typedef struct e_display_colorkeying_cfg
{
    display_color_t        src_color;   ///< Source color
    display_color_t        dst_color;   ///< Destination color
    display_color_keying_t enable_ckey; ///< Select enable or disable
} display_colorkeying_cfg_t;

typedef struct e_display_colorkeying_layer
{
    display_colorkeying_cfg_t layer[2];
} display_colorkeying_layer_t;

/** Graphics plane input configuration structure */
typedef struct st_display_input_cfg
{
    uint32_t          * p_base;        ///< Base address to the frame buffer
    uint32_t          * p_base_cb;     ///< Base address to the frame buffer for Cb plane
    uint32_t          * p_base_cr;     ///< Base address to the frame buffer for Cr plane
    uint16_t            hsize;         ///< Horizontal pixels in a line
    uint16_t            vsize;         ///< Vertical pixels in a frame
    uint16_t            coordinate_x;  ///< Coordinate X
    uint16_t            coordinate_y;  ///< Coordinate Y
    uint16_t            hstride;       ///< Memory stride (bytes) in a line
    uint16_t            hstride_cbcr;  ///< Memory stride (bytes) in a line for Cb and Cr plane
    display_in_format_t format;        ///< Input format setting
    display_data_swap_t data_swap;     ///< Input data swap_Setting
} display_input_cfg_t;

/** Display output configuration structure */
typedef struct st_display_output_cfg
{
    display_timing_t          htiming;              ///< Horizontal display cycle setting
    display_timing_t          vtiming;              ///< Vertical display cycle setting
    display_out_format_t      format;               ///< Output format setting
    display_signal_polarity_t data_enable_polarity; ///< Data Enable signal polarity
    display_sync_edge_t       sync_edge;            ///< Signal sync edge selection
    display_color_t           bg_color;             ///< Background color
    bool dithering_on;                              ///< Dithering on/off
} display_output_cfg_t;

/** Display callback parameter definition */
typedef struct st_display_callback_args
{
    display_event_t event;             ///< Event code
    void const    * p_context;         ///< Context provided to user during callback
} display_callback_args_t;

/** Display main configuration structure */
typedef struct st_display_cfg
{
    /** Generic configuration for display devices */
    display_input_cfg_t  input[2];                         ///< Graphics input frame setting
    display_output_cfg_t output;                           ///< Graphics output frame setting

    /** Configuration for display event processing */
    void (* p_callback)(display_callback_args_t * p_args); ///< Pointer to callback function
    void const * p_context;                                ///< User defined context passed into callback function

    /** Pointer to display peripheral specific configuration */
    void const * p_extend;                                 ///< Display hardware dependent configuration
} display_cfg_t;

/** Display main configuration structure */
typedef struct st_display_runtime_cfg
{
    /** Generic configuration for display devices */
    display_input_cfg_t input;         ///< Graphics input frame setting
} display_runtime_cfg_t;

/** Display control block.  Allocate an instance specific control block to pass into the display API calls.
 * @par Implemented as
 * - glcdc_instance_ctrl_t
 * - lcdc_instance_ctrl_t
 */

/** Display control block */
typedef void display_ctrl_t;

/** Display Status */
typedef struct st_display_status
{
    display_state_t state;             ///< Status of display module
} display_status_t;

/** Shared Interface definition for display peripheral */

typedef struct st_display_api
{
    /** Open display device.
     * @par Implemented as
     * - @ref R_LCDC_Open()
     * @param[in,out]  p_ctrl        Pointer to display interface control block.
     * @param[in]      p_cfg         Pointer to display configuration structure.
     */
    fsp_err_t (* open)(display_ctrl_t * const p_ctrl, display_cfg_t const * const p_cfg);

    /** Close display device.
     * @par Implemented as
     * - @ref R_LCDC_Close()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    fsp_err_t (* close)(display_ctrl_t * const p_ctrl);

    /** Display start.
     * @par Implemented as
     * - @ref R_LCDC_Start()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    fsp_err_t (* start)(display_ctrl_t * const p_ctrl);

    /** Display stop.
     * @par Implemented as
     * - @ref R_LCDC_Stop()
     * @param[in]     p_ctrl   Pointer to display interface control block.
     */
    fsp_err_t (* stop)(display_ctrl_t * const p_ctrl);

    /** Change layer parameters at runtime.
     * @par Implemented as
     * - @ref R_LCDC_LayerChange()
     * @param[in]   p_ctrl     Pointer to display interface control block.
     * @param[in]   p_cfg      Pointer to run-time layer configuration structure.
     * @param[in]   layer      Graphics layer to configure.
     */
    fsp_err_t (* layerChange)(display_ctrl_t const * const p_ctrl, display_runtime_cfg_t const * const p_cfg,
                              display_frame_layer_t layer);

    /** Change layer framebuffer pointer.
     * @par Implemented as
     * - @ref R_LCDC_BufferChange()
     * @param[in]   p_ctrl       Pointer to display interface control block.
     * @param[in]   framebuffer  Pointer to desired framebuffer.
     * @param[in]   layer        Layer to set framebuffer.
     */
    fsp_err_t (* bufferChange)(display_ctrl_t const * const p_ctrl, uint8_t * const framebuffer,
                               display_frame_layer_t layer);

    /** Configure color keying.
     * @par Implemented as
     * - @ref R_LCDC_ColorKeySet()
     * @param[in]   p_ctrl    Pointer to display interface control block.
     * @param[in]   key_cfg   Pointer to color keying configuration.
     * @param[in]   layer     Layer to apply color keying.
     */
    fsp_err_t (* colorKeySet)(display_ctrl_t const * const p_ctrl, display_colorkeying_layer_t key_cfg,
                              display_frame_layer_t layer);

    /** Get status for display device.
     * @par Implemented as
     * - @ref R_LCDC_StatusGet()
     * @param[in]   p_ctrl     Pointer to display interface control block.
     * @param[in]   status     Pointer to display interface status structure.
     */
    fsp_err_t (* statusGet)(display_ctrl_t const * const p_ctrl, display_status_t * const p_status);
} display_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_display_instance
{
    display_ctrl_t      * p_ctrl;      ///< Pointer to the control structure for this instance
    display_cfg_t const * p_cfg;       ///< Pointer to the configuration structure for this instance
    display_api_t const * p_api;       ///< Pointer to the API structure for this instance
} display_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif                                 /* R_DISPLAY_API_H_ */

/*******************************************************************************************************************//**
 * @} (end defgroup LCDC_API)
 **********************************************************************************************************************/

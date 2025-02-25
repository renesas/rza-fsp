/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include    <stdio.h>
#include    <string.h>

#include    "gx_api.h"
#include    "gx_display.h"
#include    "gx_utility.h"

#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/** Space used to store int to fixed point polygon vertices. */
#define MAX_POLYGON_VERTICES    GX_POLYGON_MAX_EDGE_NUM

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** indicator for the number of visible frame buffer */
typedef enum e_frame_buffers
{
    FRAME_BUFFER_A = 0,
    FRAME_BUFFER_B
} frame_buffers_t;

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** indicator for the number of visible frame buffer */
static GX_UBYTE * visible_frame = NULL;
static GX_UBYTE * working_frame = NULL;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static VOID gx_copy_visible_to_working_8bpp(GX_CANVAS * canvas, GX_RECTANGLE * copy);

static VOID gx_rotate_canvas_to_working_8bpp(GX_CANVAS * canvas, GX_RECTANGLE * copy, INT angle);

static VOID gx_rotate_canvas_to_working_8bpp_draw(GX_UBYTE * pGetRow,
                                                  GX_UBYTE * pPutRow,
                                                  INT        width,
                                                  INT        height,
                                                  INT        stride);
static VOID gx_rotate_canvas_to_working_8bpp_draw_rotate90(GX_UBYTE * pGetRow,
                                                           GX_UBYTE * pPutRow,
                                                           INT        width,
                                                           INT        height,
                                                           INT        canvas_stride,
                                                           INT        disp_stride);
static VOID gx_rotate_canvas_to_working_8bpp_draw_rotate180(GX_UBYTE * pGetRow,
                                                            GX_UBYTE * pPutRow,
                                                            INT        width,
                                                            INT        height,
                                                            INT        stride);
static VOID gx_rotate_canvas_to_working_8bpp_draw_rotate270(GX_UBYTE * pGetRow,
                                                            GX_UBYTE * pPutRow,
                                                            INT        width,
                                                            INT        height,
                                                            INT        canvas_stride,
                                                            INT        disp_stride);

/** functions provided by rm_guix_port.c */
extern void rm_guix_port_frame_toggle(ULONG display_handle, GX_UBYTE ** visible);
extern void rm_guix_port_frame_pointers_get(ULONG display_handle, GX_UBYTE ** visible, GX_UBYTE ** working);
extern INT  rm_guix_port_display_rotation_get(ULONG display_handle);
extern void rm_guix_port_display_actual_size_get(ULONG display_handle, INT * width, INT * height);
extern void rm_guix_port_display_8bit_palette_assign(ULONG display_handle);

/***********************************************************************************************************************
 * GUIX display driver function prototypes (called by GUIX)
 **********************************************************************************************************************/

VOID _gx_rz_buffer_toggle_8bpp(GX_CANVAS * canvas, GX_RECTANGLE * dirty);
VOID _gx_display_driver_8bit_palette_assign(GX_DISPLAY * display, GX_COLOR * palette, INT count);

/***********************************************************************************************************************
 * Functions
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8-bit Palette setup for display hardware.
 * This function is called by GUIX.
 * @param[in]    display       Pointer to a GUIX display
 * @param[in]    palette       Pointer to a GUIX color palette entries
 * @param[in]    count         Number of palette entries.
 **********************************************************************************************************************/
VOID _gx_display_driver_8bit_palette_assign (GX_DISPLAY * display, GX_COLOR * palette, INT count)
{
    display->gx_display_palette      = palette;
    display->gx_display_palette_size = (UINT) count;

    rm_guix_port_display_8bit_palette_assign(display->gx_display_handle);
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Software 8bpp draw function to toggle frame buffer.
 *  This function performs copies canvas memory to working frame buffer if a canvas is used, then toggles frame buffer,
 *  finally copies visible frame buffer to working frame buffer. This function is called by GUIX if hardware rendering
 *  acceleration is not enabled.
 * @param[in]   canvas         Pointer to a GUIX canvas
 * @param[in]   dirty          Pointer to a dirty rectangle area
 **********************************************************************************************************************/
VOID _gx_rz_buffer_toggle_8bpp (GX_CANVAS * canvas, GX_RECTANGLE * dirty)
{
    GX_PARAMETER_NOT_USED(dirty);

    GX_RECTANGLE Limit;
    GX_RECTANGLE copy;
    GX_DISPLAY * display;
    INT          rotation_angle;

    display = canvas->gx_canvas_display;

    _gx_utility_rectangle_define(&Limit, 0, 0, (GX_VALUE) (canvas->gx_canvas_x_resolution - 1),
                                 (GX_VALUE) (canvas->gx_canvas_y_resolution - 1));

    rotation_angle = rm_guix_port_display_rotation_get(display->gx_display_handle);
    rm_guix_port_frame_pointers_get(display->gx_display_handle, &visible_frame, &working_frame);

    if (canvas->gx_canvas_memory != (GX_COLOR *) working_frame)
    {
        if (_gx_utility_rectangle_overlap_detect(&Limit, &canvas->gx_canvas_dirty_area, &copy))
        {
            gx_rotate_canvas_to_working_8bpp(canvas, &copy, rotation_angle);
        }
    }

    rm_guix_port_frame_toggle(canvas->gx_canvas_display->gx_display_handle, &visible_frame);
    rm_guix_port_frame_pointers_get(canvas->gx_canvas_display->gx_display_handle, &visible_frame, &working_frame);

    if (canvas->gx_canvas_memory == (GX_COLOR *) visible_frame)
    {
        canvas->gx_canvas_memory = (GX_COLOR *) working_frame;
    }

    if (_gx_utility_rectangle_overlap_detect(&Limit, &canvas->gx_canvas_dirty_area, &copy))
    {
        if (canvas->gx_canvas_memory == (GX_COLOR *) working_frame)
        {
            gx_copy_visible_to_working_8bpp(canvas, &copy);
        }
        else
        {
            gx_rotate_canvas_to_working_8bpp(canvas, &copy, rotation_angle);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, Frame buffer toggle operation with copying data by software without
 * D/AVE 2D acceleration and screen rotation.
 * This function is called by _gx_rz_buffer_toggle_8bpp().
 * @param[in]     canvas            Pointer to a canvas
 * @param[in]     copy              Pointer to a rectangle region to copy
 **********************************************************************************************************************/
static VOID gx_copy_visible_to_working_8bpp (GX_CANVAS * canvas, GX_RECTANGLE * copy)
{
    GX_RECTANGLE display_size;
    GX_RECTANGLE copy_clip;

    ULONG * pGetRow;
    ULONG * pPutRow;

    INT copy_width;
    INT copy_height;
    INT canvas_stride;
    INT display_stride;

    ULONG * pGet;
    ULONG * pPut;
    INT     row;
    INT     col;

    GX_DISPLAY * display = canvas->gx_canvas_display;

    _gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                 (GX_VALUE) (display->gx_display_height - 1));
    copy_clip = *copy;

    /** Align copy region on 32-bit boundary. */
    copy_clip.gx_rectangle_left  = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_left & 0xfffcU);
    copy_clip.gx_rectangle_right = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_right | 3U);

    /** Offset canvas within frame buffer. */
    _gx_utility_rectangle_shift(&copy_clip, canvas->gx_canvas_display_offset_x, canvas->gx_canvas_display_offset_y);

    _gx_utility_rectangle_overlap_detect(&copy_clip, &display_size, &copy_clip);
    copy_width  = (INT) (copy_clip.gx_rectangle_right - copy_clip.gx_rectangle_left) + 1;
    copy_height = (INT) (copy_clip.gx_rectangle_bottom - copy_clip.gx_rectangle_top) + 1;

    if ((copy_width <= 0) || (copy_height <= 0))
    {
        return;
    }

    pGetRow = (ULONG *) visible_frame;
    pPutRow = (ULONG *) working_frame;

    copy_width   /= 4;
    canvas_stride = (INT) canvas->gx_canvas_x_resolution / 4;
    pPutRow       = pPutRow + ((INT) copy_clip.gx_rectangle_top * canvas_stride);
    pPutRow       = pPutRow + ((INT) copy_clip.gx_rectangle_left / 4);

    display_stride = (INT) display->gx_display_width / 4;
    pGetRow        = pGetRow +
                     ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * display_stride);
    pGetRow = pGetRow + (INT) ((canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left) / 4);

    for (row = 0; row < copy_height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (col = 0; col < copy_width; col++)
        {
            *pPut = *pGet;
            ++pPut;
            ++pGet;
        }

        pPutRow += canvas_stride;
        pGetRow += display_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8bpp Frame buffer software draw function.
 * This function is called by gx_rotate_canvas_to_working_8bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     stride            Image memory stride
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_8bpp_draw (GX_UBYTE * pGetRow,
                                                   GX_UBYTE * pPutRow,
                                                   INT        width,
                                                   INT        height,
                                                   INT        stride)
{
    GX_UBYTE * pGet;
    GX_UBYTE * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;
        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pPut;
            ++pGet;
        }

        pGetRow += stride;
        pPutRow += stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8bpp Frame buffer software draw function with rotating image 90 degree.
 * This function is called by gx_rotate_canvas_to_working_8bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     canvas_stride     Frame buffer memory stride (of the canvas)
 * @param[in]     disp_stride       Frame buffer memory stride (of the destination frame buffer)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_8bpp_draw_rotate90 (GX_UBYTE * pGetRow,
                                                            GX_UBYTE * pPutRow,
                                                            INT        width,
                                                            INT        height,
                                                            INT        canvas_stride,
                                                            INT        disp_stride)
{
    GX_UBYTE * pGet;
    GX_UBYTE * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pGet;
            pPut += disp_stride;
        }

        pPutRow--;
        pGetRow += canvas_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8bpp Frame buffer software draw function with rotating image 180 degree.
 * This function is called by gx_rotate_canvas_to_working_8bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     stride            Image memory stride
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_8bpp_draw_rotate180 (GX_UBYTE * pGetRow,
                                                             GX_UBYTE * pPutRow,
                                                             INT        width,
                                                             INT        height,
                                                             INT        stride)
{
    GX_UBYTE * pGet;
    GX_UBYTE * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;
        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            --pPut;
            ++pGet;
        }

        pGetRow += stride;
        pPutRow -= stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8bpp Frame buffer software draw function with rotating image 270 degree.
 * This function is called by gx_rotate_canvas_to_working_8bpp().
 * @param[in]     pGetRow           Pointer to copy source address
 * @param[in]     pPutRow           Pointer to copy destination address
 * @param[in]     width             Image width to copy
 * @param[in]     height            Image height to copy
 * @param[in]     canvas_stride     Frame buffer memory stride (of the canvas)
 * @param[in]     disp_stride       Frame buffer memory stride (of the destination frame buffer)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_8bpp_draw_rotate270 (GX_UBYTE * pGetRow,
                                                             GX_UBYTE * pPutRow,
                                                             INT        width,
                                                             INT        height,
                                                             INT        canvas_stride,
                                                             INT        disp_stride)
{
    GX_UBYTE * pGet;
    GX_UBYTE * pPut;

    for (INT row = 0; row < height; row++)
    {
        pGet = pGetRow;
        pPut = pPutRow;

        for (INT col = 0; col < width; col++)
        {
            *pPut = *pGet;
            ++pGet;
            pPut -= disp_stride;
        }

        pPutRow++;
        pGetRow += canvas_stride;
    }
}

/*******************************************************************************************************************//**
 * @brief  GUIX display driver for FSP, 8bpp Frame buffer software copy operation with screen rotation.
 * This function is called by _gx_rz_buffer_toggle_8bpp().
 * @param[in]     canvas            Pointer to a canvas
 * @param[in]     copy              Pointer to a rectangle region to copy.
 * @param[in]     angle    Rotation angle (0, 90, 180 or 270)
 **********************************************************************************************************************/
static VOID gx_rotate_canvas_to_working_8bpp (GX_CANVAS * canvas, GX_RECTANGLE * copy, INT angle)
{
    GX_RECTANGLE display_size;
    GX_RECTANGLE copy_clip;

    GX_UBYTE * pGetRow;
    GX_UBYTE * pPutRow;

    INT copy_width;
    INT copy_height;
    INT canvas_stride;
    INT display_stride;

    GX_DISPLAY * display = canvas->gx_canvas_display;
    gx_utility_rectangle_define(&display_size, 0, 0, (GX_VALUE) (display->gx_display_width - 1),
                                (GX_VALUE) (display->gx_display_height - 1));
    copy_clip = *copy;

    /** Align copy region on 32-bit boundary. */
    copy_clip.gx_rectangle_left   = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_left & 0xfffcU);
    copy_clip.gx_rectangle_top    = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_top & 0xfffcU);
    copy_clip.gx_rectangle_right  = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_right | 3U);
    copy_clip.gx_rectangle_bottom = (GX_VALUE) ((USHORT) copy_clip.gx_rectangle_bottom | 3U);

    /** Offset canvas within frame buffer. */
    gx_utility_rectangle_shift(&copy_clip, canvas->gx_canvas_display_offset_x, canvas->gx_canvas_display_offset_y);

    gx_utility_rectangle_overlap_detect(&copy_clip, &display_size, &copy_clip);
    copy_width  = (INT) (copy_clip.gx_rectangle_right - copy_clip.gx_rectangle_left) + 1;
    copy_height = (INT) (copy_clip.gx_rectangle_bottom - copy_clip.gx_rectangle_top) + 1;

    if ((copy_width <= 0) || (copy_height <= 0))
    {
        return;
    }

    pGetRow = (GX_UBYTE *) canvas->gx_canvas_memory;
    pPutRow = working_frame;

    display_stride = (INT) display->gx_display_height;
    canvas_stride  = (INT) canvas->gx_canvas_x_resolution;

    if (angle == GX_SCREEN_ROTATION_NONE)
    {
        pPutRow = pPutRow + ((INT) copy_clip.gx_rectangle_top * canvas_stride);
        pPutRow = pPutRow + (INT) copy_clip.gx_rectangle_left;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_8bpp_draw(pGetRow, pPutRow, copy_width, copy_height, canvas_stride);
    }
    else if (angle == GX_SCREEN_ROTATION_FLIP)
    {
        pPutRow = pPutRow + ((INT) (display->gx_display_height - copy_clip.gx_rectangle_top) * canvas_stride);
        pPutRow = pPutRow - ((INT) copy_clip.gx_rectangle_left + 1);

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_8bpp_draw_rotate180(pGetRow, pPutRow, copy_width, copy_height, canvas_stride);
    }
    else if (angle == GX_SCREEN_ROTATION_CCW)
    {
        pPutRow = pPutRow + ((INT) ((display->gx_display_width - 1) - copy_clip.gx_rectangle_left) * display_stride);
        pPutRow = pPutRow + (INT) copy_clip.gx_rectangle_top;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_8bpp_draw_rotate270(pGetRow,
                                                        pPutRow,
                                                        copy_width,
                                                        copy_height,
                                                        canvas_stride,
                                                        display_stride);
    }
    else                               /* angle == GX_SCREEN_ROTATION_CW */
    {
        pPutRow = pPutRow + ((INT) copy_clip.gx_rectangle_left * display_stride);
        pPutRow = pPutRow + (INT) (display_stride - 1);
        pPutRow = pPutRow - (INT) copy_clip.gx_rectangle_top;

        pGetRow = pGetRow + ((INT) (canvas->gx_canvas_display_offset_y + copy_clip.gx_rectangle_top) * canvas_stride);
        pGetRow = pGetRow + (INT) (canvas->gx_canvas_display_offset_x + copy_clip.gx_rectangle_left);

        gx_rotate_canvas_to_working_8bpp_draw_rotate90(pGetRow,
                                                       pPutRow,
                                                       copy_width,
                                                       copy_height,
                                                       canvas_stride,
                                                       display_stride);
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_GUIX_PORT)
 **********************************************************************************************************************/

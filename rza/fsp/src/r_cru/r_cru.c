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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_cru.h"
#include "r_cru_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define CSI2_DPHYTIM0                  (0x040137B9)
#define CSI2_DPHYTIM1                  (0x0A0A0C12)
#define CSI2_DPHYSKW0                  (0x00001111)
#define CSI2_MCT2                      (0x0016000B)

#define YUV422_10BIT_FORMAT_ENALBE     (1U)
#define YUV422_8BIT_FORMAT_ENALBE      (1U)
#define YUV420_10BIT_FORMAT_ENALBE     (1U)
#define YUV420_8BIT_FORMAT_ENALBE      (1U)
#define GENERIC_LONG_PACKET_ENALBE     (1U)
#define GENERIC_SHORT_PACKET_ENALBE    (1U)
#define USER_DEFINED_DATA_ENALBE       (1U)
#define RAW20_FORMAT_ENALBE            (1U)
#define RAW16_FORMAT_ENABLE            (1U)
#define RAW14_FORMAT_ENABLE            (1U)
#define RAW12_FORMAT_ENABLE            (1U)
#define RAW10_FORMAT_ENABLE            (1U)
#define RAW8_FORMAT_ENABLE             (1U)
#define RAW7_FORMAT_ENABLE             (1U)
#define RAW6_FORMAT_ENABLE             (1U)
#define RGB888_FORMAT_ENALBE           (1U)
#define RGB666_FORMAT_ENALBE           (1U)
#define RGB565_FORMAT_ENALBE           (1U)
#define RGB555_FORMAT_ENALBE           (1U)
#define RGB444_FORMAT_ENALBE           (1U)

#define CAST_TO_UINT32                 (0xFFFFFFFFU)
#define CAST_TO_UINT12                 (0xFFFU)
#define CAST_TO_UINT6                  (0x3FU)
#define CAST_TO_UINT3                  (0x7U)
#define CAST_TO_UINT2                  (0x3U)
#define CAST_TO_UINT1                  (0x1U)

#define CSI2_DTEL                      (YUV422_10BIT_FORMAT_ENALBE) << 31 | (YUV422_8BIT_FORMAT_ENALBE) << 30 | \
    (YUV420_10BIT_FORMAT_ENALBE) << 29 | (YUV420_8BIT_FORMAT_ENALBE) << 28 |                                    \
    (YUV420_8BIT_FORMAT_ENALBE) << 26 | (YUV420_10BIT_FORMAT_ENALBE) << 25 |                                    \
    (YUV420_8BIT_FORMAT_ENALBE) << 24 | (GENERIC_LONG_PACKET_ENALBE) << 22 |                                    \
    (GENERIC_LONG_PACKET_ENALBE) << 21 | (GENERIC_LONG_PACKET_ENALBE) << 20 |                                   \
    (GENERIC_LONG_PACKET_ENALBE) << 19 | (GENERIC_SHORT_PACKET_ENALBE) << 15 |                                  \
    (GENERIC_SHORT_PACKET_ENALBE) << 14 | (GENERIC_SHORT_PACKET_ENALBE) << 13 |                                 \
    (GENERIC_SHORT_PACKET_ENALBE) << 12 | (GENERIC_SHORT_PACKET_ENALBE) << 11 |                                 \
    (GENERIC_SHORT_PACKET_ENALBE) << 10 | (GENERIC_SHORT_PACKET_ENALBE) << 9 |                                  \
    (GENERIC_SHORT_PACKET_ENALBE) << 8

#define CSI2_DTEH                      (USER_DEFINED_DATA_ENALBE) << 23 | (USER_DEFINED_DATA_ENALBE) << 22 | \
    (USER_DEFINED_DATA_ENALBE) << 21 | (USER_DEFINED_DATA_ENALBE) << 20 |                                    \
    (USER_DEFINED_DATA_ENALBE) << 19 | (USER_DEFINED_DATA_ENALBE) << 18 |                                    \
    (USER_DEFINED_DATA_ENALBE) << 17 | (USER_DEFINED_DATA_ENALBE) << 16 |                                    \
    (RAW20_FORMAT_ENALBE) << 15 | (RAW16_FORMAT_ENABLE) << 14 |                                              \
    (RAW14_FORMAT_ENABLE) << 13 | (RAW12_FORMAT_ENABLE) << 12 |                                              \
    (RAW10_FORMAT_ENABLE) << 11 | (RAW8_FORMAT_ENABLE) << 10 |                                               \
    (RAW7_FORMAT_ENABLE) << 9 | (RAW6_FORMAT_ENABLE) << 8 |                                                  \
    (RGB888_FORMAT_ENALBE) << 4 | (RGB666_FORMAT_ENALBE) << 3 |                                              \
    (RGB565_FORMAT_ENALBE) << 2 | (RGB555_FORMAT_ENALBE) << 1 |                                              \
    (RGB444_FORMAT_ENALBE)

#define MICROSEC_WAIT_20               (20U)
#define MICROSEC_WAIT_10               (10U)
#define MILISEC_WAIT_1                 (1U)

#define CAPTURE_HSIZE_MAX              (2800)
#define CAPTURE_VSIZE_MAX              (4095)
#define CAPTURE_HSIZE_MIN              (320)
#define CAPTURE_VSIZE_MIN              (240)
#define BUFFER_ALIGNMENT_512           (512)
#define BUFFER_NUM_MIN                 (1)
#define BUFFER_NUM_MAX                 (8)
#define INPUT_FORMAT_MIN_INVLID        (0)
#define INPUT_FORMAT_MAX_INVLID        (9)
#define OUTPUT_FORMAT_MIN_INVLID       (0)
#define OUTPUT_FORMAT_MAX_INVLID       (7)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_cru_mipi_dphy_set();
static void r_cru_mipi_link_set(cru_cfg_t const * const p_cfg);
static void r_cru_axi_set(cru_cfg_t const * const p_cfg);
static void r_cru_image_processing_set(cru_cfg_t const * const p_cfg);
static void r_cru_stop_linkpacket();
static void r_cru_stop_dphy();
static void r_cru_stop_imageprocessing();
static void r_cru_interrupt_enable(cru_instance_ctrl_t * const p_instance_ctrl);
void        cru_image_conv_int(IRQn_Type const irq);

#if (CRU_CFG_PARAM_CHECKING_ENABLE)
static fsp_err_t r_cru_open_param_check(cru_cfg_t const * const p_cfg);
static fsp_err_t r_cru_open_param_check_size_setting(cru_cfg_t const * const p_cfg);
static fsp_err_t r_cru_open_param_check_buffer_setting(cru_cfg_t const * const p_cfg);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* This table values are written to CRU register */
static const uint8_t capture_input_format[] =
{
    0x18,                              /* YUV420 8bit  */
    0x19,                              /* YUV420 10bit */
    0x1E,                              /* YUV422 8bit  */
    0x1F,                              /* YUV422 10bit */
    0x22,                              /* RGB565       */
    0x24,                              /* RGB888       */
    0x2A,                              /* RAW8         */
    0x2B,                              /* RAW10        */
    0x2C,                              /* RAW12        */
    0x2D,                              /* RAW14        */
};

/* This table values are written to CRU register */
static const uint8_t capture_output_format[] =
{
    0x4,                               /* YUYV (YUV420) */
    0x5,                               /* UYVY (YUV420) */
    0x0,                               /* YUYV (YUV422) */
    0x1,                               /* UYVY (YUV422) */
    0x0,                               /* RGB888 24bit  */
    0x1, /* RGB888 32bit  */           ///< Upper 8bit : 0x00
    0x3, /* RGB888 32bit  */           ///< A-R-G-B
    0x2, /* RGB888 32bit  */           ///< B-G-R-A
};

static cru_instance_ctrl_t * r_cru_blk;

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* CRU API */
const cru_api_t g_cru_on_cru =
{
    .open         = R_CRU_Open,
    .close        = R_CRU_Close,
    .captureStart = R_CRU_CaptureStart,
    .captureStop  = R_CRU_CaptureStop,
    .statusGet    = R_CRU_StatusGet,
};

/*******************************************************************************************************************//**
 *
 * @addtogroup CRU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *　Initializes the CRU modules and enables interrupts
 *
 * @retval FSP_SUCCESS              Initializes the CRU modules.
 * @retval FSP_ERR_ASSERTION        Pointer to the control block is NULL.
 * @retval FSP_ERR_ALREADY_OPEN     CRU module is already open
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid argument error
 * @retval FSP_ERR_INVALID_ALIGNMENT       Input buffer alignment
 **********************************************************************************************************************/
fsp_err_t R_CRU_Open (cru_ctrl_t * const p_api_ctrl, cru_cfg_t const * const p_cfg)
{
    fsp_err_t             err    = FSP_SUCCESS;
    cru_instance_ctrl_t * p_ctrl = (cru_instance_ctrl_t *) p_api_ctrl;

    p_ctrl->p_cfg        = p_cfg;
    p_ctrl->p_context    = p_cfg->p_context;
    p_ctrl->p_callback   = p_cfg->p_callback;
    r_cru_blk->p_context = p_ctrl;

#if  (CRU_CFG_PARAM_CHECKING_ENABLE)

    /* Check parameters */
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(p_ctrl->state <= CAMERA_STATE_IDLE, FSP_ERR_ALREADY_OPEN);
    err = r_cru_open_param_check(p_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }
#endif

    R_BSP_MODULE_RSTON(FSP_IP_CRU, 0);
    R_BSP_MODULE_RSTON(FSP_IP_CRU, 1);
    R_BSP_MODULE_RSTON(FSP_IP_CRU, 2);

    R_BSP_MODULE_CLKON(FSP_IP_CRU, 1);
    R_BSP_MODULE_CLKON(FSP_IP_CRU, 2);
    R_BSP_MODULE_CLKON(FSP_IP_CRU, 3);
    R_BSP_MODULE_CLKON(FSP_IP_CRU, 4);

    /* MIPI-CSI2 input receive start */
    R_BSP_MODULE_RSTOFF(FSP_IP_CRU, 1);
    R_BSP_MODULE_RSTOFF(FSP_IP_CRU, 2);

    /* D-PHY setting */
    r_cru_mipi_dphy_set();

    /* select MIPI I/F -> select MIPI*/
    R_CRU->CRUnCTRL_b.VINSEL = 0b0;

    /* release the Image Processing Module form the reset state */
    R_CRU->CRUnRST_b.VRESETN = 0b1;

    /* interrupt setting */
    R_CRU->CRUnIE   = 0x00000000;
    R_CRU->CRUnINTS = 0x00000000;

    /* AXI-MASTER setting */
    r_cru_axi_set(p_cfg);

    /* Image Processing module setting */
    r_cru_image_processing_set(p_cfg);

    /* Enable CRU interrupts */
    r_cru_interrupt_enable(p_api_ctrl);

    /* LINK setting */
    r_cru_mipi_link_set(p_cfg);

    /* Change Capture Status */
    p_ctrl->state = CAMERA_STATE_IN_PROGRESS;

    return err;
}

/*******************************************************************************************************************//**
 * Close the capture while the CRU module is operating
 *
 * @retval FSP_SUCCESS          Close the CRU module
 * @retval FSP_ERR_ASSERTION    Pointer to the control block is NULL.
 * @retval FSP_ERR_NOT_OPEN     CRU module is not open
 **********************************************************************************************************************/
fsp_err_t R_CRU_Close (cru_ctrl_t * const p_api_ctrl)
{
    fsp_err_t             err    = FSP_SUCCESS;
    cru_instance_ctrl_t * p_ctrl = (cru_instance_ctrl_t *) p_api_ctrl;

#if  (CRU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(CAMERA_STATE_IDLE != p_ctrl->state, FSP_ERR_NOT_OPEN);
#endif

    /* Disable interrupts */
    R_CRU->CRUnIE_b.SFE    = false;
    R_CRU->CRUnIE_b.EFE    = false;
    R_CRU->CRUnIE_b.SIE    = false;
    R_CRU->CRUnIE_b.WIE    = false;
    R_CRU->CRUnIE_b.FEOVWE = false;
    R_CRU->CRUnIE_b.DECEE  = false;
    R_CRU->CRUnIE_b.SLVEE  = false;
    R_CRU->CRUnIE_b.FOE    = false;

    /* stop Link packet */
    r_cru_stop_linkpacket();

    /* stop D-PHY */
    r_cru_stop_dphy();

    /* LINK stop reception */
    R_CRU->CSI2nMCT3_b.RXEN = 0b0;

    /* software reset */
    R_CRU->CSI2nRTCT_b.VSRST = 0b1;
    while (R_CRU->CSI2nRTST_b.VSRSTS == 0b1)
    {
        /*
         * No operation
         */
    }

    /* stop image processing module */
    r_cru_stop_imageprocessing();

    /* Change Capture Status */
    p_ctrl->state = CAMERA_STATE_IDLE;

    return err;
}

/*******************************************************************************************************************//**
 * Start a capture. It is only possible when CRU is open.
 *
 * @retval FSP_SUCCESS              start a capture.
 * @retval FSP_ERR_ASSERTION    Pointer to the control block is NULL.
 * @retval FSP_ERR_INVALID_MODE     CRU module is not CAMERA_STATE_IN_PROGRESS
 **********************************************************************************************************************/
fsp_err_t R_CRU_CaptureStart (cru_ctrl_t * const p_api_ctrl)
{
    fsp_err_t             err    = FSP_SUCCESS;
    cru_instance_ctrl_t * p_ctrl = (cru_instance_ctrl_t *) p_api_ctrl;

#if  (CRU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(CAMERA_STATE_IN_PROGRESS == p_ctrl->state, FSP_ERR_INVALID_MODE);
#endif

    /* Start the operation of Image processing */
    R_CRU->ICnEN_b.ICEN = 0b1;

    R_BSP_MODULE_RSTOFF(FSP_IP_CRU, 0);
    R_BSP_SoftwareDelay(MILISEC_WAIT_1, BSP_DELAY_UNITS_MILLISECONDS);

    /* Change Capture Status */
    p_ctrl->state = CAMERA_STATE_BUSY;

    return err;
}

/*******************************************************************************************************************//**
 * Stop a capture. It is only possible when CRU is running.
 *
 * @retval FSP_SUCCESS              stop a capture.
 * @retval FSP_ERR_ASSERTION        Pointer to the control block is NULL.
 * @retval FSP_ERR_INVALID_MODE     CRU module is not CAMERA_STATE_BUSY
 **********************************************************************************************************************/
fsp_err_t R_CRU_CaptureStop (cru_ctrl_t * const p_api_ctrl)
{
    fsp_err_t             err    = FSP_SUCCESS;
    cru_instance_ctrl_t * p_ctrl = (cru_instance_ctrl_t *) p_api_ctrl;

#if  (CRU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(CAMERA_STATE_BUSY == p_ctrl->state, FSP_ERR_INVALID_MODE);
#endif

    /* Start the operation of Image processing */
    R_CRU->ICnEN_b.ICEN = 0b0;

    /* Change Capture Status */
    p_ctrl->state = CAMERA_STATE_IN_PROGRESS;

    return err;
}

/*******************************************************************************************************************//**
 * Get the camera status, CAMERA module status and buffer address.
 * It is only possible when CRU is running.
 *
 * @retval FSP_SUCCESS              stop a capture.
 * @retval FSP_ERR_ASSERTION        Pointer to the control block is NULL.
 * @retval FSP_ERR_INVALID_MODE     CRU module is not CAMERA_STATE_BUSY
 **********************************************************************************************************************/
fsp_err_t R_CRU_StatusGet (cru_ctrl_t * const p_api_ctrl, camera_status_t * p_status)
{
    fsp_err_t             err    = FSP_SUCCESS;
    cru_instance_ctrl_t * p_ctrl = (cru_instance_ctrl_t *) p_api_ctrl;
    uint32_t              buffer_id;

#if  (CRU_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ERROR_RETURN(CAMERA_STATE_BUSY == p_ctrl->state, FSP_ERR_INVALID_MODE);
#endif

    buffer_id          = R_CRU->AMnMBS_b.MBSTS;
    p_status->p_buffer = (uint32_t *) ((uint64_t) p_ctrl->p_cfg->buffer_cfg.pp_buffer[buffer_id] & CAST_TO_UINT32);

    p_status->state = p_ctrl->state;

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IOPORT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Set the MIPI D-PHY configurations
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_cru_mipi_dphy_set (void)
{
    /* D-PHY timing setting */
    R_CRU->CSIDPHYTIM0 = CSI2_DPHYTIM0;
    R_CRU->CSIDPHYTIM1 = CSI2_DPHYTIM1;

    /* skew adjustment setting */
    R_CRU->CSIDPHYSKW0 = CSI2_DPHYSKW0;

    /* D-PHY control setting */
    R_CRU->CSIDPHYCTRL0_b.EN_BGR = 0b1;
    R_BSP_SoftwareDelay(MICROSEC_WAIT_20, BSP_DELAY_UNITS_MICROSECONDS);

    R_CRU->CSIDPHYCTRL0_b.EN_LDO1200 = 0b1;
    R_BSP_SoftwareDelay(MICROSEC_WAIT_10, BSP_DELAY_UNITS_MICROSECONDS);

    R_BSP_MODULE_CLKON(FSP_IP_CRU, 0);
}

/*******************************************************************************************************************//**
 * Set the MIPI LINK configurations
 *
 * @param[in]       p_cfg       CRU configuration parameters
 * @retval          none
 **********************************************************************************************************************/
static void r_cru_mipi_link_set (cru_cfg_t const * const p_cfg)
{
    cru_extended_cfg_t * pextend = (cru_extended_cfg_t *) p_cfg->p_extend;

    /* disable de-scrambling */
    R_CRU->CSI2nMCT0_b.LFSREN = 0b0;

    /* ECC  0:26bit 1:24bit*/
    R_CRU->CSI2nMCT0_b.ECCV13 = 0b0;

    /* number of used data lanes */
    R_CRU->CSI2nMCT0_b.VDLN = pextend->num_datalane;

    /* internal setting parameter */
    R_CRU->CSI2nMCT2 = CSI2_MCT2;

    /*input data type setting, all format enable */
    R_CRU->CSI2nDTEL = CSI2_DTEL;
    R_CRU->CSI2nDTEH = CSI2_DTEH;

    /* enable LINK receive */
    R_CRU->CSI2nMCT3_b.RXEN = 0b1;
}

/*******************************************************************************************************************//**
 * Set the AXI configurations
 *
 * @param[in]       p_cfg       CRU configuration parameters
 * @retval          none
 **********************************************************************************************************************/
static void r_cru_axi_set (cru_cfg_t const * const p_cfg)
{
    /* MB setting */
    uint16_t wait;
    uint8_t  MB_valid = 1;
    for (wait = 0; wait < p_cfg->buffer_cfg.num_buffers; wait++)
    {
        MB_valid *= 2;
    }

    MB_valid--;
    R_CRU->AMnMBVALID_b.MBVALID = MB_valid;

    /* Buffer address setting  */
    if (p_cfg->buffer_cfg.pp_buffer[0] != NULL)
    {
        R_CRU->AMnMB1ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[0]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[1] != NULL)
    {
        R_CRU->AMnMB2ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[1]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[2] != NULL)
    {
        R_CRU->AMnMB3ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[2]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[3] != NULL)
    {
        R_CRU->AMnMB4ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[3]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[4] != NULL)
    {
        R_CRU->AMnMB5ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[4]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[5] != NULL)
    {
        R_CRU->AMnMB6ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer)[5] & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[6] != NULL)
    {
        R_CRU->AMnMB7ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[6]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[7] != NULL)
    {
        R_CRU->AMnMB8ADDRL = (uint64_t) (p_cfg->buffer_cfg.pp_buffer[7]) & CAST_TO_UINT32;
    }
    else
    {
        /* Do Nothing */
    }

    /* AXI Master transfer stop setting */
    R_CRU->AMnAXISTP_b.AXI_STOP = 0b0;
}

/*******************************************************************************************************************//**
 * Set the Image Processing Module configurations
 *
 * @param[in]       p_cfg       CRU configuration parameters
 * @retval          none
 **********************************************************************************************************************/
static void r_cru_image_processing_set (cru_cfg_t const * const p_cfg)
{
    cru_extended_cfg_t * pextend = (cru_extended_cfg_t *) p_cfg->p_extend;

    /* MIPI input format setting */
    R_CRU->ICnMC_b.INF = capture_input_format[pextend->color_input] & CAST_TO_UINT6;

    /* virtual channel setting */
    R_CRU->ICnMC_b.VCSEL = 0x0;

    /* Bypassing all image processing for an MIPI input */
    R_CRU->ICnMC_b.ICTHR = 0b0;

    /* disable sub-sampling */
    R_CRU->ICnMC_b.DECTHR = 0b1;

    /* enable clipping */
    R_CRU->ICnMC_b.CLPTHR = 0b0;

    /* disable color space conversion */
    R_CRU->ICnMC_b.CSCTHR = 0b1;

    /* disable LUT (10bit to 8bit) */
    R_CRU->ICnMC_b.LUTTHR = 0b1;

    /* select offset binary of U and V */
    R_CRU->ICnMC_b.IBINSEL = 0b0;

    /* Alpha value setting in ARGB format */
    R_CRU->ICnDMR_b.A8BIT = 0x00;

    /* YUV data order setting */
    R_CRU->ICnDMR_b.YCMODE = capture_output_format[pextend->color_output] & CAST_TO_UINT3;

    /* RGB data order setting */
    R_CRU->ICnDMR_b.RGBMODE = capture_output_format[pextend->color_output] & CAST_TO_UINT2;

    /* YUV output binary setting */
    R_CRU->ICnDMR_b.OBINSEL = 0b0;

    /* data clipping setting for YUV format */
    R_CRU->ICnMC_b.CLP = 0b11;

    /* Image Clipping */
    R_CRU->ICnSLPrC_b.SLPrC = p_cfg->y_capture_start_pixel & CAST_TO_UINT12;
    R_CRU->ICnELPrC_b.ELPrC = (p_cfg->y_capture_start_pixel + p_cfg->y_capture_pixels) & CAST_TO_UINT12;
    R_CRU->ICnSPPrC_b.SPPrC = p_cfg->x_capture_start_pixel & CAST_TO_UINT12;
    R_CRU->ICnEPPrC_b.EPPrC = (p_cfg->x_capture_start_pixel + p_cfg->x_capture_pixels) & CAST_TO_UINT12;
}

/*******************************************************************************************************************//**
 * Stop LINK packet
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_cru_stop_linkpacket (void)
{
    /* wait for a frame to be received for a period of one frame */
    while (R_CRU->CSI2nRXST_b.RACTDET == 1)
    {
        /* clear CSI2nRXST.RACTDET */
        R_CRU->CSI2nRXSC_b.RACTDETC = 0b1;
    }
}

/*******************************************************************************************************************//**
 * Stop the D-PHY
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_cru_stop_dphy (void)
{
    /* Reset the CRU (D-PHY) */
    R_CPG->CPG_RST_CRU_b.UNIT0_RSTB = 0b0;

    /* Stop the D-PHY clock */
    R_CPG->CPG_CLKON_CRU_b.CLK0_ON = 0b0;

    /* Cancel the EN_LDO1200 register settings */
    R_CRU->CSIDPHYCTRL0_b.EN_LDO1200 = 0b0;

    /* Cancel the EN_BGR register settings */
    R_CRU->CSIDPHYCTRL0_b.EN_BGR = 0b0;
}

/*******************************************************************************************************************//**
 * Stop the image processing
 *
 * @retval        none
 **********************************************************************************************************************/
static void r_cru_stop_imageprocessing (void)
{
    /* Stop the operation of Image Processing*/
    R_CRU->ICnEN_b.ICEN = 0b0;

    /* Image data has not been received yet */
    while (R_CRU->ICnMS_b.IA == 1)
    {
        /*
         * No operation
         */
    }

    /* wait until the FIFO becomes empty */
    while (R_CRU->AMnFIFOPNTR_b.FIFORPNTR_Y != R_CRU->AMnFIFOPNTR_b.FIFOWPNTR)
    {
        /*
         * No operation
         */
    }

    /* Request the AXI bus to stop */
    R_CRU->AMnAXISTP_b.AXI_STOP = 0b1;

    /* Check AXi bus stopped */
    while (R_CRU->AMnAXISTPACK_b.AXI_STOP_ACK == 0)
    {
        /*
         * No operation
         */
    }

    /* Cancel the AXI bus stop request */
    R_CRU->AMnAXISTP_b.AXI_STOP = 0b0;

    /* Reset the CRU */
    R_CPG->CPG_RST_CRU_b.UNIT2_RSTB = 0b0;

    /* Reset the CRU */
    R_CRU->CRUnRST_b.VRESETN = 0b0;
}

/*******************************************************************************************************************//**
 * Set the interrupt settings for CRU module
 *
 * @param[in]       p_instance_ctrl         CRU instance control block
 * @retval          none
 **********************************************************************************************************************/
static void r_cru_interrupt_enable (cru_instance_ctrl_t * const p_instance_ctrl)
{
    cru_extended_cfg_t * pextend = (cru_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Enable interrupt register for image conv int */
    R_CRU->CRUnIE_b.SFE = (pextend->interrupt_enable) & CAST_TO_UINT1;
    R_CRU->CRUnIE_b.EFE = (pextend->interrupt_enable >> 1) & CAST_TO_UINT1;
    R_CRU->CRUnIE_b.SIE = (pextend->interrupt_enable >> 2) & CAST_TO_UINT1;
    R_CRU->ICnSI_b.SI   = (pextend->scan_line_num) & CAST_TO_UINT12;

    if (pextend->image_conv_int_irq >= 0)
    {
        R_BSP_IrqCfgEnable(pextend->image_conv_int_irq, pextend->image_conv_int_ipl, p_instance_ctrl);
    }
    else
    {
        /* Do Nothing */
    }
}

/*******************************************************************************************************************//**
 * Interrupt function for CRU Image Conv Interrupt
 *
 * @param[in]       irq     FSP error type
 * @retval          none
 **********************************************************************************************************************/
void cru_image_conv_int (IRQn_Type const irq)
{
    FSP_CONTEXT_SAVE FSP_PARAMETER_NOT_USED(irq);

    camera_callback_args_t args;
    uint32_t               event_flag;
    uint32_t               scan_line_flag;
    uint32_t               frame_end_flag;
    uint32_t               frame_start_flag;
    uint32_t               reg_val;
    cru_instance_ctrl_t  * p_ctrl = (cru_instance_ctrl_t *) r_cru_blk->p_context;

    /* clear event flag */
    event_flag = 0;

    /* get register value of  interrupt status (CRUnINIS) */
    reg_val          = R_CRU->CRUnINTS;
    scan_line_flag   = (reg_val >> 18) & CAST_TO_UINT1;
    frame_end_flag   = (reg_val >> 17) & CAST_TO_UINT1;
    frame_start_flag = (reg_val >> 16) & CAST_TO_UINT1;

    /* Check which interrupt is generated */
    if (frame_start_flag == 0b1)
    {
        event_flag |= CRU_EVENT_FRAME_START;
    }
    else
    {
        /* Do Nothing */
    }

    if (frame_end_flag == 0b1)
    {
        event_flag |= CRU_EVENT_FRAME_END;
    }
    else
    {
        /* Do Nothing */
    }

    if (scan_line_flag == 0b1)
    {
        event_flag |= CRU_EVENT_SCAN_LINE;
    }
    else
    {
        /* Do Nothing */
    }

    /* Call back callback function if it is registered */
    if (NULL != p_ctrl->p_callback)
    {
        args.event     = event_flag;
        args.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&args);
    }
    else
    {
        /* Do Nothing */
    }

    /* Clear interrupt flag */
    if (scan_line_flag == 0b1)
    {
        R_CRU->CRUnINTS_b.SIS = 1;
    }
    else
    {
        /* Do Nothing */
    }

    if (frame_end_flag == 0b1)
    {
        R_CRU->CRUnINTS_b.EFS = 1;
    }
    else
    {
        /* Do Nothing */
    }

    if (frame_start_flag == 0b1)
    {
        R_CRU->CRUnINTS_b.SFS = 1;
    }
    else
    {
        /* Do Nothing */
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if (CRU_CFG_PARAM_CHECKING_ENABLE)

/*******************************************************************************************************************//**
 * Parameter Checking for R_CRU_Open.
 *
 * @param[in]       p_cfg       CRU configuration parameters
 * @retval          FSP_SUCCESS                       No parameter error found
 * @retval          FSP_ERR_ASSERTION                 Pointer to the control block is NULL.
 * @retval          FSP_ERR_INVALID_ARGUMENT          Invalid argument error
 * @retval          FSP_ERR_INVALID_ALIGNMENT         Input buffer alignment
 **********************************************************************************************************************/
static fsp_err_t r_cru_open_param_check (cru_cfg_t const * const p_cfg)
{
    fsp_err_t error;

    FSP_ASSERT(p_cfg);

    cru_extended_cfg_t * pextend = (cru_extended_cfg_t *) p_cfg->p_extend;

    /* check parameter for capture size */
    error = r_cru_open_param_check_size_setting(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

    /* check parameter for buffer address alignment */
    error = r_cru_open_param_check_buffer_setting(p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == error, error);

    /* check parameter for color format */
    FSP_ERROR_RETURN((pextend->color_input >= INPUT_FORMAT_MIN_INVLID), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((pextend->color_input <= INPUT_FORMAT_MAX_INVLID), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((pextend->color_output >= OUTPUT_FORMAT_MIN_INVLID), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((pextend->color_output <= OUTPUT_FORMAT_MAX_INVLID), FSP_ERR_INVALID_ARGUMENT);

    /* check parameter for number datalane */
    FSP_ERROR_RETURN((pextend->num_datalane ==
                      CRU_DATALANE_1) |
                     (pextend->num_datalane == CRU_DATALANE_2) | (pextend->num_datalane == CRU_DATALANE_4),
                     FSP_ERR_INVALID_ARGUMENT);

    /* check parameter for number of buffers */
    FSP_ERROR_RETURN(p_cfg->buffer_cfg.num_buffers >= BUFFER_NUM_MIN, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_cfg->buffer_cfg.num_buffers <= BUFFER_NUM_MAX, FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Cheking parameters of capture size setting.
 *
 * @param[in]       p_cfg                                   CRU configuration parameters
 * @retval          FSP_SUCCESS                             No parameter error found
 * @retval          FSP_ERR_INVALID_ARGUMENT                Invalid argument error
 **********************************************************************************************************************/
static fsp_err_t r_cru_open_param_check_size_setting (cru_cfg_t const * const p_cfg)
{
    FSP_ERROR_RETURN(p_cfg->x_capture_start_pixel + p_cfg->x_capture_pixels >= CAPTURE_HSIZE_MIN,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_cfg->y_capture_start_pixel + p_cfg->y_capture_pixels >= CAPTURE_VSIZE_MIN,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_cfg->x_capture_start_pixel + p_cfg->x_capture_pixels <= CAPTURE_HSIZE_MAX,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_cfg->y_capture_start_pixel + p_cfg->y_capture_pixels <= CAPTURE_VSIZE_MAX,
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_cfg->x_capture_start_pixel <= CAPTURE_HSIZE_MAX, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_cfg->y_capture_start_pixel <= CAPTURE_VSIZE_MAX, FSP_ERR_INVALID_ARGUMENT);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Cheking parameters of buffer address alignment setting.
 *
 * @param[in]       p_cfg                           CRU configuration parameters
 * @retval          FSP_SUCCESS                     No parameter error found
 * @retval          FSP_ERR_INVALID_ALIGNMENT       Input buffer alignment
 **********************************************************************************************************************/
static fsp_err_t r_cru_open_param_check_buffer_setting (cru_cfg_t const * const p_cfg)
{
    if (p_cfg->buffer_cfg.pp_buffer[0])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[0]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[1])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[1]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[2])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[2]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[3])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[3]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[4])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[4]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[5])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[5]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[6])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[6]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    if (p_cfg->buffer_cfg.pp_buffer[7])
    {
        FSP_ERROR_RETURN(0U == (((uint64_t) (p_cfg->buffer_cfg.pp_buffer[7]) & CAST_TO_UINT32) % BUFFER_ALIGNMENT_512),
                         FSP_ERR_INVALID_ALIGNMENT);
    }
    else
    {
        /* Do Nothing */
    }

    return FSP_SUCCESS;
}

#endif

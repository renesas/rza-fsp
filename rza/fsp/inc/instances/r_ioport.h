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
 * @addtogroup IOPORT
 * @{
 **********************************************************************************************************************/

#ifndef R_IOPORT_H
#define R_IOPORT_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#include "r_ioport_api.h"
#include "r_ioport_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IOPORT private control block. DO NOT MODIFY. Initialization occurs when R_IOPORT_Open() is called. */
typedef struct st_ioport_instance_ctrl
{
    uint32_t     open;
    void const * p_context;
} ioport_instance_ctrl_t;

/* This typedef is here temporarily. See SWFLEX-144 for details. */
/** Superset list of all possible IO port pins. */
typedef enum e_ioport_port_pin_t
{
    IOPORT_PORT_00_PIN_00 = 0x0000,       ///< IO port 0 pin 0
    IOPORT_PORT_00_PIN_01 = 0x0001,       ///< IO port 0 pin 1
    IOPORT_PORT_00_PIN_02 = 0x0002,       ///< IO port 0 pin 2
    IOPORT_PORT_00_PIN_03 = 0x0003,       ///< IO port 0 pin 3

    IOPORT_PORT_01_PIN_00 = 0x0100,       ///< IO port 1 pin 0
    IOPORT_PORT_01_PIN_01 = 0x0101,       ///< IO port 1 pin 1
    IOPORT_PORT_01_PIN_02 = 0x0102,       ///< IO port 1 pin 2
    IOPORT_PORT_01_PIN_03 = 0x0103,       ///< IO port 1 pin 3
    IOPORT_PORT_01_PIN_04 = 0x0104,       ///< IO port 1 pin 4

    IOPORT_PORT_02_PIN_00 = 0x0200,       ///< IO port 2 pin 0
    IOPORT_PORT_02_PIN_01 = 0x0201,       ///< IO port 2 pin 1
    IOPORT_PORT_02_PIN_02 = 0x0202,       ///< IO port 2 pin 2
    IOPORT_PORT_02_PIN_03 = 0x0203,       ///< IO port 2 pin 3

    IOPORT_PORT_03_PIN_00 = 0x0300,       ///< IO port 3 pin 0
    IOPORT_PORT_03_PIN_01 = 0x0301,       ///< IO port 3 pin 1
    IOPORT_PORT_03_PIN_02 = 0x0302,       ///< IO port 3 pin 2
    IOPORT_PORT_03_PIN_03 = 0x0303,       ///< IO port 3 pin 3

    IOPORT_PORT_04_PIN_00 = 0x0400,       ///< IO port 4 pin 0
    IOPORT_PORT_04_PIN_01 = 0x0401,       ///< IO port 4 pin 1
    IOPORT_PORT_04_PIN_02 = 0x0402,       ///< IO port 4 pin 2
    IOPORT_PORT_04_PIN_03 = 0x0403,       ///< IO port 4 pin 3
    IOPORT_PORT_04_PIN_04 = 0x0404,       ///< IO port 4 pin 4
    IOPORT_PORT_04_PIN_05 = 0x0405,       ///< IO port 4 pin 5

    IOPORT_PORT_05_PIN_00 = 0x0500,       ///< IO port 5 pin 0
    IOPORT_PORT_05_PIN_01 = 0x0501,       ///< IO port 5 pin 1
    IOPORT_PORT_05_PIN_02 = 0x0502,       ///< IO port 5 pin 2
    IOPORT_PORT_05_PIN_03 = 0x0503,       ///< IO port 5 pin 3
    IOPORT_PORT_05_PIN_04 = 0x0504,       ///< IO port 5 pin 4

    IOPORT_PORT_06_PIN_00 = 0x0600,       ///< IO port 6 pin 0
    IOPORT_PORT_06_PIN_01 = 0x0601,       ///< IO port 6 pin 1
    IOPORT_PORT_06_PIN_02 = 0x0602,       ///< IO port 6 pin 2
    IOPORT_PORT_06_PIN_03 = 0x0603,       ///< IO port 6 pin 3
    IOPORT_PORT_06_PIN_04 = 0x0604,       ///< IO port 6 pin 4

    IOPORT_PORT_07_PIN_00 = 0x0700,       ///< IO port 7 pin 0
    IOPORT_PORT_07_PIN_01 = 0x0701,       ///< IO port 7 pin 1
    IOPORT_PORT_07_PIN_02 = 0x0702,       ///< IO port 7 pin 2
    IOPORT_PORT_07_PIN_03 = 0x0703,       ///< IO port 7 pin 3
    IOPORT_PORT_07_PIN_04 = 0x0704,       ///< IO port 7 pin 4

    IOPORT_PORT_08_PIN_00 = 0x0800,       ///< IO port 8 pin 0
    IOPORT_PORT_08_PIN_01 = 0x0801,       ///< IO port 8 pin 1
    IOPORT_PORT_08_PIN_02 = 0x0802,       ///< IO port 8 pin 2
    IOPORT_PORT_08_PIN_03 = 0x0803,       ///< IO port 8 pin 3
    IOPORT_PORT_08_PIN_04 = 0x0804,       ///< IO port 8 pin 4

    IOPORT_PORT_09_PIN_00 = 0x0900,       ///< IO port 9 pin 0
    IOPORT_PORT_09_PIN_01 = 0x0901,       ///< IO port 9 pin 1
    IOPORT_PORT_09_PIN_02 = 0x0902,       ///< IO port 9 pin 2
    IOPORT_PORT_09_PIN_03 = 0x0903,       ///< IO port 9 pin 3

    IOPORT_PORT_10_PIN_00 = 0x0A00,       ///< IO port 10 pin 0
    IOPORT_PORT_10_PIN_01 = 0x0A01,       ///< IO port 10 pin 1
    IOPORT_PORT_10_PIN_02 = 0x0A02,       ///< IO port 10 pin 2
    IOPORT_PORT_10_PIN_03 = 0x0A03,       ///< IO port 10 pin 3
    IOPORT_PORT_10_PIN_04 = 0x0A04,       ///< IO port 10 pin 4

    IOPORT_PORT_11_PIN_00 = 0x0B00,       ///< IO port 11 pin 0
    IOPORT_PORT_11_PIN_01 = 0x0B01,       ///< IO port 11 pin 1
    IOPORT_PORT_11_PIN_02 = 0x0B02,       ///< IO port 11 pin 2
    IOPORT_PORT_11_PIN_03 = 0x0B03,       ///< IO port 11 pin 3

    IOPORT_PORT_12_PIN_00 = 0x0C00,       ///< IO port 12 pin 0
    IOPORT_PORT_12_PIN_01 = 0x0C01,       ///< IO port 12 pin 1

    IOPORT_PORT_13_PIN_00 = 0x0D00,       ///< IO port 13 pin 0
    IOPORT_PORT_13_PIN_01 = 0x0D01,       ///< IO port 13 pin 1
    IOPORT_PORT_13_PIN_02 = 0x0D02,       ///< IO port 13 pin 2
    IOPORT_PORT_13_PIN_03 = 0x0D03,       ///< IO port 13 pin 3
    IOPORT_PORT_13_PIN_04 = 0x0D04,       ///< IO port 13 pin 4

    IOPORT_PORT_14_PIN_00 = 0x0E00,       ///< IO port 14 pin 0
    IOPORT_PORT_14_PIN_01 = 0x0E01,       ///< IO port 14 pin 1
    IOPORT_PORT_14_PIN_02 = 0x0E02,       ///< IO port 14 pin 2

    IOPORT_PORT_15_PIN_00 = 0x0F00,       ///< IO port 15 pin 0
    IOPORT_PORT_15_PIN_01 = 0x0F01,       ///< IO port 15 pin 1
    IOPORT_PORT_15_PIN_02 = 0x0F02,       ///< IO port 15 pin 2
    IOPORT_PORT_15_PIN_03 = 0x0F03,       ///< IO port 15 pin 3

    IOPORT_PORT_16_PIN_00 = 0x1000,       ///< IO port 16 pin 0
    IOPORT_PORT_16_PIN_01 = 0x1001,       ///< IO port 16 pin 1

    IOPORT_PORT_17_PIN_00 = 0x1100,       ///< IO port 17 pin 0
    IOPORT_PORT_17_PIN_01 = 0x1101,       ///< IO port 17 pin 1
    IOPORT_PORT_17_PIN_02 = 0x1102,       ///< IO port 17 pin 2
    IOPORT_PORT_17_PIN_03 = 0x1103,       ///< IO port 17 pin 3

    IOPORT_PORT_18_PIN_00 = 0x1200,       ///< IO port 18 pin 0
    IOPORT_PORT_18_PIN_01 = 0x1201,       ///< IO port 18 pin 1
    IOPORT_PORT_18_PIN_02 = 0x1202,       ///< IO port 18 pin 2
    IOPORT_PORT_18_PIN_03 = 0x1203,       ///< IO port 18 pin 3
    IOPORT_PORT_18_PIN_04 = 0x1204,       ///< IO port 18 pin 4
    IOPORT_PORT_18_PIN_05 = 0x1205,       ///< IO port 18 pin 5

    /* Special purpose port */
    IOPORT_NMI = 0xFFFF0100,              ///< NMI

    IOPORT_TMS_SWDIO = 0xFFFF0200,        ///< TMS_SWDIO

    IOPORT_TDO = 0xFFFF0300,              ///< TDO

    IOPORT_AUDIO_CLK1 = 0xFFFF0400,       ///< AUDIO_CLK1
    IOPORT_AUDIO_CLK2 = 0xFFFF0401,       ///< AUDIO_CLK2

    IOPORT_SD0_CLK   = 0xFFFF0600,        ///< CD0_CLK
    IOPORT_SD0_CMD   = 0xFFFF0601,        ///< CD0_CMD
    IOPORT_SD0_RST_N = 0xFFFF0602,        ///< CD0_RST_N

    IOPORT_SD0_DATA0 = 0xFFFF0700,        ///< SD0_DATA0
    IOPORT_SD0_DATA1 = 0xFFFF0701,        ///< SD0_DATA1
    IOPORT_SD0_DATA2 = 0xFFFF0702,        ///< SD0_DATA2
    IOPORT_SD0_DATA3 = 0xFFFF0703,        ///< SD0_DATA3
    IOPORT_SD0_DATA4 = 0xFFFF0704,        ///< SD0_DATA4
    IOPORT_SD0_DATA5 = 0xFFFF0705,        ///< SD0_DATA5
    IOPORT_SD0_DATA6 = 0xFFFF0706,        ///< SD0_DATA6
    IOPORT_SD0_DATA7 = 0xFFFF0707,        ///< SD0_DATA7

    IOPORT_SD1_CLK = 0xFFFF0800,          ///< SD1_CLK
    IOPORT_SD1_CMD = 0xFFFF0801,          ///< SD1_CMD

    IOPORT_SD1_DATA0 = 0xFFFF0900,        ///< SD1_DATA0
    IOPORT_SD1_DATA1 = 0xFFFF0901,        ///< SD1_DATA1
    IOPORT_SD1_DATA2 = 0xFFFF0902,        ///< SD1_DATA2
    IOPORT_SD1_DATA3 = 0xFFFF0903,        ///< SD1_DATA3

    IOPORT_QSPI0_SPCLK = 0xFFFF0A00,      ///< QSPI0_SPCLK
    IOPORT_QSPI0_IO0   = 0xFFFF0A01,      ///< QSPI0_IO0
    IOPORT_QSPI0_IO1   = 0xFFFF0A02,      ///< QSPI0_IO1
    IOPORT_QSPI0_IO2   = 0xFFFF0A03,      ///< QSPI0_IO2
    IOPORT_QSPI0_IO3   = 0xFFFF0A04,      ///< QSPI0_IO3
    IOPORT_QSPI0_SSL   = 0xFFFF0A05,      ///< QSPI0_SSL

    IOPORT_OM_CS1_N = 0xFFFF0B00,         ///< OM_CS1_N
    IOPORT_OM_DQS   = 0xFFFF0B01,         ///< OM_DQS
    IOPORT_OM_SIO4  = 0xFFFF0B02,         ///< OM_SIO4
    IOPORT_OM_SIO5  = 0xFFFF0B03,         ///< OM_SIO5
    IOPORT_OM_SIO6  = 0xFFFF0B04,         ///< OM_SIO6
    IOPORT_OM_SIO7  = 0xFFFF0B05,         ///< OM_SIO7

    IOPORT_QSPI_RESET_N = 0xFFFF0C00,     ///< QSPI_RESET_N
    IOPORT_QSPI_WP_N    = 0xFFFF0C01,     ///< QSPI_WP_N

    IOPORT_WDTOVF_PERROUT_N = 0xFFFF0D00, ///< WDTOVF_PERROUT_N

    IOPORT_RIIC0_SDA = 0xFFFF0E00,        ///< RIIC0_SDA
    IOPORT_RIIC0_SCL = 0xFFFF0E01,        ///< RIIC0_SCL
    IOPORT_RIIC1_SDA = 0xFFFF0E02,        ///< RIIC1_SDA
    IOPORT_RIIC1_SCL = 0xFFFF0E03,        ///< RIIC1_SCL
} ioport_port_pin_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ioport_api_t g_ioport_on_ioport;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_IOPORT_Open(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_IOPORT_Close(ioport_ctrl_t * const p_ctrl);
fsp_err_t R_IOPORT_PinsCfg(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);
fsp_err_t R_IOPORT_PinCfg(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);
fsp_err_t R_IOPORT_PinEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event);
fsp_err_t R_IOPORT_PinEventOutputWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value);
fsp_err_t R_IOPORT_PinRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);
fsp_err_t R_IOPORT_PinWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);
fsp_err_t R_IOPORT_PortDirectionSet(ioport_ctrl_t * const p_ctrl,
                                    bsp_io_port_t         port,
                                    ioport_size_t         direction_values,
                                    ioport_size_t         mask);
fsp_err_t R_IOPORT_PortEventInputRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * event_data);
fsp_err_t R_IOPORT_PortEventOutputWrite(ioport_ctrl_t * const p_ctrl,
                                        bsp_io_port_t         port,
                                        ioport_size_t         event_data,
                                        ioport_size_t         mask_value);
fsp_err_t R_IOPORT_PortRead(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value);
fsp_err_t R_IOPORT_PortWrite(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask);
fsp_err_t R_IOPORT_SDVoltageModeCfg(ioport_ctrl_t * const p_ctrl,
                                    ioport_sd_channel_t   channel,
                                    ioport_sd_voltage_t   voltage);
fsp_err_t R_IOPORT_QSPIVoltageModeCfg(ioport_ctrl_t * const p_ctrl,
                                      ioport_qspi_channel_t channel,
                                      ioport_qspi_voltage_t voltage);
fsp_err_t R_IOPORT_EthernetVoltageModeCfg(ioport_ctrl_t * const     p_ctrl,
                                          ioport_ethernet_channel_t channel,
                                          ioport_ethernet_voltage_t voltage);
fsp_err_t R_IOPORT_EthernetModeCfg(ioport_ctrl_t * const     p_ctrl,
                                   ioport_ethernet_channel_t channel,
                                   ioport_ethernet_mode_t    mode);

/*******************************************************************************************************************//**
 * @} (end defgroup IOPORT)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_IOPORT_H

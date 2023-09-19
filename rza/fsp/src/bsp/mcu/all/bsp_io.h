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
 * @defgroup BSP_IO BSP I/O access
 * @ingroup RENESAS_COMMON
 * @brief This module provides basic read/write access to port pins.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_IO_H
#define BSP_IO_H

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Private definition to set enumeration values. */
#define BSP_IO_PRV_8BIT_MASK            (0xFF)
#define BSP_IO_PRV_PIN_MASK             (1U)
#define BSP_IO_PRV_PORT_OFFSET          (8U)
#define BSP_IO_PRV_PFCWE_MASK           (0xFFFFFFBF)
#define BSP_IO_PRV_OENWE_MASK           (0xFFFFFFDF)
#define BSP_IO_PRV_SET_OEN_ENABLE       (0U)
#define BSP_IO_PRV_SET_SSEL0_SELCTL2    (0x1000U)
#define BSP_IO_PRV_SET_SSEL1_SELCTL0    (0x0100U)
#define BSP_IO_PWPR_B0WI_OFFSET         (7U)
#define BSP_IO_PWPR_PFSWE_OFFSET        (6U)
#define BSP_IO_PWPR_OENWE_OFFSET        (5U)
#define BSP_IO_PM_PM_OUTPUT             (3U)

#define BSP_IO_PRV_P_REG_BASE_SET(base)      BSP_IO_PRV_P_REG_BASE(base)
#define BSP_IO_PRV_P_REG_BASE(base)          (&R_GPIO->P ## base)
#define BSP_IO_PRV_PM_REG_BASE_SET(base)     BSP_IO_PRV_PM_REG_BASE(base)
#define BSP_IO_PRV_PM_REG_BASE(base)         (&R_GPIO->PM ## base)
#define BSP_IO_PRV_PIN_REG_BASE_SET(base)    BSP_IO_PRV_PIN_REG_BASE(base)
#define BSP_IO_PRV_PIN_REG_BASE(base)        (&R_GPIO->PIN ## base)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Levels that can be set and read for individual pins */
typedef enum e_bsp_io_level
{
    BSP_IO_LEVEL_LOW = 0,              ///< Low
    BSP_IO_LEVEL_HIGH                  ///< High
} bsp_io_level_t;

/** Direction of individual pins */
typedef enum e_bsp_io_dir
{
    BSP_IO_DIRECTION_HIZ    = 0x0,                  ///< Hi-Z
    BSP_IO_DIRECTION_INPUT  = 0x4,                  ///< Input
    BSP_IO_DIRECTION_OUTPUT = 0x8,                  ///< Output (Input disable)
    BSP_IO_DIRECTION_OUTPUT_WITH_INPUT_ENABLE = 0xC ///< Output (Input enable)
} bsp_io_direction_t;

#ifndef BSP_OVERRIDE_BSP_PORT_T

/** Superset list of all possible IO ports. */
typedef enum e_bsp_io_port
{
    BSP_IO_PORT_00 = 0x0000,           ///< IO port 0
    BSP_IO_PORT_01 = 0x0100,           ///< IO port 1
    BSP_IO_PORT_02 = 0x0200,           ///< IO port 2
    BSP_IO_PORT_03 = 0x0300,           ///< IO port 3
    BSP_IO_PORT_04 = 0x0400,           ///< IO port 4
    BSP_IO_PORT_05 = 0x0500,           ///< IO port 5
    BSP_IO_PORT_06 = 0x0600,           ///< IO port 6
    BSP_IO_PORT_07 = 0x0700,           ///< IO port 7
    BSP_IO_PORT_08 = 0x0800,           ///< IO port 8
    BSP_IO_PORT_09 = 0x0900,           ///< IO port 9
    BSP_IO_PORT_10 = 0x0A00,           ///< IO port 10
    BSP_IO_PORT_11 = 0x0B00,           ///< IO port 11
    BSP_IO_PORT_12 = 0x0C00,           ///< IO port 12
    BSP_IO_PORT_13 = 0x0D00,           ///< IO port 13
    BSP_IO_PORT_14 = 0x0E00,           ///< IO port 14
    BSP_IO_PORT_15 = 0x0F00,           ///< IO port 15
    BSP_IO_PORT_16 = 0x1000,           ///< IO port 16
    BSP_IO_PORT_17 = 0x1100,           ///< IO port 17
    BSP_IO_PORT_18 = 0x1200,           ///< IO port 18
} bsp_io_port_t;

#endif

#ifndef BSP_OVERRIDE_BSP_PIN_T

/** Superset list of all possible IO port pins. */
typedef enum e_bsp_io_port_pin_t
{
    BSP_IO_PORT_00_PIN_00 = 0x0000,       ///< IO port 0 pin 0
    BSP_IO_PORT_00_PIN_01 = 0x0001,       ///< IO port 0 pin 1
    BSP_IO_PORT_00_PIN_02 = 0x0002,       ///< IO port 0 pin 2
    BSP_IO_PORT_00_PIN_03 = 0x0003,       ///< IO port 0 pin 3

    BSP_IO_PORT_01_PIN_00 = 0x0100,       ///< IO port 1 pin 0
    BSP_IO_PORT_01_PIN_01 = 0x0101,       ///< IO port 1 pin 1
    BSP_IO_PORT_01_PIN_02 = 0x0102,       ///< IO port 1 pin 2
    BSP_IO_PORT_01_PIN_03 = 0x0103,       ///< IO port 1 pin 3
    BSP_IO_PORT_01_PIN_04 = 0x0104,       ///< IO port 1 pin 4

    BSP_IO_PORT_02_PIN_00 = 0x0200,       ///< IO port 2 pin 0
    BSP_IO_PORT_02_PIN_01 = 0x0201,       ///< IO port 2 pin 1
    BSP_IO_PORT_02_PIN_02 = 0x0202,       ///< IO port 2 pin 2
    BSP_IO_PORT_02_PIN_03 = 0x0203,       ///< IO port 2 pin 3

    BSP_IO_PORT_03_PIN_00 = 0x0300,       ///< IO port 3 pin 0
    BSP_IO_PORT_03_PIN_01 = 0x0301,       ///< IO port 3 pin 1
    BSP_IO_PORT_03_PIN_02 = 0x0302,       ///< IO port 3 pin 2
    BSP_IO_PORT_03_PIN_03 = 0x0303,       ///< IO port 3 pin 3

    BSP_IO_PORT_04_PIN_00 = 0x0400,       ///< IO port 4 pin 0
    BSP_IO_PORT_04_PIN_01 = 0x0401,       ///< IO port 4 pin 1
    BSP_IO_PORT_04_PIN_02 = 0x0402,       ///< IO port 4 pin 2
    BSP_IO_PORT_04_PIN_03 = 0x0403,       ///< IO port 4 pin 3
    BSP_IO_PORT_04_PIN_04 = 0x0404,       ///< IO port 4 pin 4
    BSP_IO_PORT_04_PIN_05 = 0x0405,       ///< IO port 4 pin 5

    BSP_IO_PORT_05_PIN_00 = 0x0500,       ///< IO port 5 pin 0
    BSP_IO_PORT_05_PIN_01 = 0x0501,       ///< IO port 5 pin 1
    BSP_IO_PORT_05_PIN_02 = 0x0502,       ///< IO port 5 pin 2
    BSP_IO_PORT_05_PIN_03 = 0x0503,       ///< IO port 5 pin 3
    BSP_IO_PORT_05_PIN_04 = 0x0504,       ///< IO port 5 pin 4

    BSP_IO_PORT_06_PIN_00 = 0x0600,       ///< IO port 6 pin 0
    BSP_IO_PORT_06_PIN_01 = 0x0601,       ///< IO port 6 pin 1
    BSP_IO_PORT_06_PIN_02 = 0x0602,       ///< IO port 6 pin 2
    BSP_IO_PORT_06_PIN_03 = 0x0603,       ///< IO port 6 pin 3
    BSP_IO_PORT_06_PIN_04 = 0x0604,       ///< IO port 6 pin 4

    BSP_IO_PORT_07_PIN_00 = 0x0700,       ///< IO port 7 pin 0
    BSP_IO_PORT_07_PIN_01 = 0x0701,       ///< IO port 7 pin 1
    BSP_IO_PORT_07_PIN_02 = 0x0702,       ///< IO port 7 pin 2
    BSP_IO_PORT_07_PIN_03 = 0x0703,       ///< IO port 7 pin 3
    BSP_IO_PORT_07_PIN_04 = 0x0704,       ///< IO port 7 pin 4

    BSP_IO_PORT_08_PIN_00 = 0x0800,       ///< IO port 8 pin 0
    BSP_IO_PORT_08_PIN_01 = 0x0801,       ///< IO port 8 pin 1
    BSP_IO_PORT_08_PIN_02 = 0x0802,       ///< IO port 8 pin 2
    BSP_IO_PORT_08_PIN_03 = 0x0803,       ///< IO port 8 pin 3
    BSP_IO_PORT_08_PIN_04 = 0x0804,       ///< IO port 8 pin 4

    BSP_IO_PORT_09_PIN_00 = 0x0900,       ///< IO port 9 pin 0
    BSP_IO_PORT_09_PIN_01 = 0x0901,       ///< IO port 9 pin 1
    BSP_IO_PORT_09_PIN_02 = 0x0902,       ///< IO port 9 pin 2
    BSP_IO_PORT_09_PIN_03 = 0x0903,       ///< IO port 9 pin 3

    BSP_IO_PORT_10_PIN_00 = 0x0A00,       ///< IO port 10 pin 0
    BSP_IO_PORT_10_PIN_01 = 0x0A01,       ///< IO port 10 pin 1
    BSP_IO_PORT_10_PIN_02 = 0x0A02,       ///< IO port 10 pin 2
    BSP_IO_PORT_10_PIN_03 = 0x0A03,       ///< IO port 10 pin 3
    BSP_IO_PORT_10_PIN_04 = 0x0A04,       ///< IO port 10 pin 4

    BSP_IO_PORT_11_PIN_00 = 0x0B00,       ///< IO port 11 pin 0
    BSP_IO_PORT_11_PIN_01 = 0x0B01,       ///< IO port 11 pin 1
    BSP_IO_PORT_11_PIN_02 = 0x0B02,       ///< IO port 11 pin 2
    BSP_IO_PORT_11_PIN_03 = 0x0B03,       ///< IO port 11 pin 3

    BSP_IO_PORT_12_PIN_00 = 0x0C00,       ///< IO port 12 pin 0
    BSP_IO_PORT_12_PIN_01 = 0x0C01,       ///< IO port 12 pin 1

    BSP_IO_PORT_13_PIN_00 = 0x0D00,       ///< IO port 13 pin 0
    BSP_IO_PORT_13_PIN_01 = 0x0D01,       ///< IO port 13 pin 1
    BSP_IO_PORT_13_PIN_02 = 0x0D02,       ///< IO port 13 pin 2
    BSP_IO_PORT_13_PIN_03 = 0x0D03,       ///< IO port 13 pin 3
    BSP_IO_PORT_13_PIN_04 = 0x0D04,       ///< IO port 13 pin 4

    BSP_IO_PORT_14_PIN_00 = 0x0E00,       ///< IO port 14 pin 0
    BSP_IO_PORT_14_PIN_01 = 0x0E01,       ///< IO port 14 pin 1
    BSP_IO_PORT_14_PIN_02 = 0x0E02,       ///< IO port 14 pin 2

    BSP_IO_PORT_15_PIN_00 = 0x0F00,       ///< IO port 15 pin 0
    BSP_IO_PORT_15_PIN_01 = 0x0F01,       ///< IO port 15 pin 1
    BSP_IO_PORT_15_PIN_02 = 0x0F02,       ///< IO port 15 pin 2
    BSP_IO_PORT_15_PIN_03 = 0x0F03,       ///< IO port 15 pin 3

    BSP_IO_PORT_16_PIN_00 = 0x1000,       ///< IO port 16 pin 0
    BSP_IO_PORT_16_PIN_01 = 0x1001,       ///< IO port 16 pin 1

    BSP_IO_PORT_17_PIN_00 = 0x1100,       ///< IO port 17 pin 0
    BSP_IO_PORT_17_PIN_01 = 0x1101,       ///< IO port 17 pin 1
    BSP_IO_PORT_17_PIN_02 = 0x1102,       ///< IO port 17 pin 2
    BSP_IO_PORT_17_PIN_03 = 0x1103,       ///< IO port 17 pin 3

    BSP_IO_PORT_18_PIN_00 = 0x1200,       ///< IO port 18 pin 0
    BSP_IO_PORT_18_PIN_01 = 0x1201,       ///< IO port 18 pin 1
    BSP_IO_PORT_18_PIN_02 = 0x1202,       ///< IO port 18 pin 2
    BSP_IO_PORT_18_PIN_03 = 0x1203,       ///< IO port 18 pin 3
    BSP_IO_PORT_18_PIN_04 = 0x1204,       ///< IO port 18 pin 4
    BSP_IO_PORT_18_PIN_05 = 0x1205,       ///< IO port 18 pin 5

    /* Special purpose port */
    BSP_IO_NMI = 0xFFFF0100,              ///< NMI

    BSP_IO_TMS_SWDIO = 0xFFFF0200,        ///< TMS_SWDIO

    BSP_IO_TDO = 0xFFFF0300,              ///< TDO

    BSP_IO_AUDIO_CLK1 = 0xFFFF0400,       ///< AUDIO_CLK1
    BSP_IO_AUDIO_CLK2 = 0xFFFF0401,       ///< AUDIO_CLK2

    BSP_IO_SD0_CLK   = 0xFFFF0600,        ///< CD0_CLK
    BSP_IO_SD0_CMD   = 0xFFFF0601,        ///< CD0_CMD
    BSP_IO_SD0_RST_N = 0xFFFF0602,        ///< CD0_RST_N

    BSP_IO_SD0_DATA0 = 0xFFFF0700,        ///< SD0_DATA0
    BSP_IO_SD0_DATA1 = 0xFFFF0701,        ///< SD0_DATA1
    BSP_IO_SD0_DATA2 = 0xFFFF0702,        ///< SD0_DATA2
    BSP_IO_SD0_DATA3 = 0xFFFF0703,        ///< SD0_DATA3
    BSP_IO_SD0_DATA4 = 0xFFFF0704,        ///< SD0_DATA4
    BSP_IO_SD0_DATA5 = 0xFFFF0705,        ///< SD0_DATA5
    BSP_IO_SD0_DATA6 = 0xFFFF0706,        ///< SD0_DATA6
    BSP_IO_SD0_DATA7 = 0xFFFF0707,        ///< SD0_DATA7

    BSP_IO_SD1_CLK = 0xFFFF0800,          ///< SD1_CLK
    BSP_IO_SD1_CMD = 0xFFFF0801,          ///< SD1_CMD

    BSP_IO_SD1_DATA0 = 0xFFFF0900,        ///< SD1_DATA0
    BSP_IO_SD1_DATA1 = 0xFFFF0901,        ///< SD1_DATA1
    BSP_IO_SD1_DATA2 = 0xFFFF0902,        ///< SD1_DATA2
    BSP_IO_SD1_DATA3 = 0xFFFF0903,        ///< SD1_DATA3

    BSP_IO_QSPI0_SPCLK = 0xFFFF0A00,      ///< QSPI0_SPCLK
    BSP_IO_QSPI0_IO0   = 0xFFFF0A01,      ///< QSPI0_IO0
    BSP_IO_QSPI0_IO1   = 0xFFFF0A02,      ///< QSPI0_IO1
    BSP_IO_QSPI0_IO2   = 0xFFFF0A03,      ///< QSPI0_IO2
    BSP_IO_QSPI0_IO3   = 0xFFFF0A04,      ///< QSPI0_IO3
    BSP_IO_QSPI0_SSL   = 0xFFFF0A05,      ///< QSPI0_SSL

    BSP_IO_OM_CS1_N = 0xFFFF0B00,         ///< OM_CS1_N
    BSP_IO_OM_DQS   = 0xFFFF0B01,         ///< OM_DQS
    BSP_IO_OM_SIO4  = 0xFFFF0B02,         ///< OM_SIO4
    BSP_IO_OM_SIO5  = 0xFFFF0B03,         ///< OM_SIO5
    BSP_IO_OM_SIO6  = 0xFFFF0B04,         ///< OM_SIO6
    BSP_IO_OM_SIO7  = 0xFFFF0B05,         ///< OM_SIO7

    BSP_IO_QSPI_RESET_N = 0xFFFF0C00,     ///< QSPI_RESET_N
    BSP_IO_QSPI_WP_N    = 0xFFFF0C01,     ///< QSPI_WP_N

    BSP_IO_WDTOVF_PERROUT_N = 0xFFFF0D00, ///< WDTOVF_PERROUT_N

    BSP_IO_RIIC0_SDA = 0xFFFF0E00,        ///< RIIC0_SDA
    BSP_IO_RIIC0_SCL = 0xFFFF0E01,        ///< RIIC0_SCL
    BSP_IO_RIIC1_SDA = 0xFFFF0E02,        ///< RIIC1_SDA
    BSP_IO_RIIC1_SCL = 0xFFFF0E03,        ///< RIIC1_SCL
} bsp_io_port_pin_t;

#endif

/** Superset of SD channels. */
typedef enum e_bsp_sd_ch
{
    BSP_SD_CHANNEL_0 = 0x00,           ///< Used to select SD channel 0
    BSP_SD_CHANNEL_1 = 0x01,           ///< Used to select SD channel 1
} bsp_sd_channel_t;

/** Superset of Ethernet channels. */
typedef enum e_bsp_eth_ch
{
    BSP_ETHERNET_CHANNEL_0 = 0x00,     ///< Used to select Ethernet channel 0
    BSP_ETHERNET_CHANNEL_1 = 0x01,     ///< Used to select Ethernet channel 1
} bsp_ethernet_channel_t;

/** Superset of SD voltages. */
typedef enum e_bsp_sd_voltage
{
    BSP_SD_VOLTAGE_33 = 0x00,          ///< SD voltage set to 3.3V
    BSP_SD_VOLTAGE_18 = 0x01,          ///< SD voltage set to 1.8V
} bsp_sd_voltage_t;

/** Superset of QSPI voltages. */
typedef enum e_bsp_qspi_voltage
{
    BSP_QSPI_VOLTAGE_33 = 0x00,        ///< QSPI voltage set to 3.3V
    BSP_QSPI_VOLTAGE_18 = 0x01,        ///< QSPI voltage set to 1.8V
} bsp_qspi_voltage_t;

/** Superset of XSPI voltages. */
typedef enum e_bsp_xspi_voltage
{
    BSP_XSPI_VOLTAGE_33 = 0x00,        ///< XSPI voltage set to 3.3V
    BSP_XSPI_VOLTAGE_18 = 0x01,        ///< XSPI voltage set to 1.8V
    BSP_XSPI_VOLTAGE_25 = 0x02,        ///< XSPI voltage set to 2.5V
} bsp_xspi_voltage_t;

/** Superset of Ethernet voltages. */
typedef enum e_bsp_eth_voltage
{
    BSP_ETHERNET_VOLTAGE_33 = 0x00,    ///< Ethernet voltage set to 3.3V
    BSP_ETHERNET_VOLTAGE_18 = 0x01,    ///< Ethernet voltage set to 1.8V
    BSP_ETHERNET_VOLTAGE_25 = 0x02,    ///< Ethernet voltage set to 2.5V
} bsp_ethernet_voltage_t;

/** Superset of I3C voltages. */
typedef enum e_bsp_i3c_voltage
{
    BSP_I3C_VOLTAGE_18 = 0x00,         ///< I3C voltage set to 1.8V
    BSP_I3C_VOLTAGE_12 = 0x01,         ///< I3C voltage set to 1.2V
} bsp_i3c_voltage_t;

/** Superset of Ethernet PHY modes. */
typedef enum e_bsp_eth_mode
{
    BSP_ETHERNET_MODE_RMII = 0x00,     ///< Ethernet PHY mode set to RMII
    BSP_ETHERNET_MODE_MII  = 0x01,     ///< Ethernet PHY mode set to MII
} bsp_ethernet_mode_t;

/** Superset of Standby modes for I3C. */
typedef enum e_bsp_i3c_mode
{
    BSP_I3C_MODE_STB = 0x00,           ///< Standby mode set to Standby mode
    BSP_I3C_MODE_NOR = 0x01,           ///< Standby mode set to Normal mode
} bsp_i3c_mode_t;

/** Superset of oscillator for bypass mode. */
typedef enum e_bsp_bypass_oscillator
{
    BSP_BYPASS_OSCILLATOR_RTC   = 0x00, ///< Oscillator set to RTC
    BSP_BYPASS_OSCILLATOR_AUDIO = 0x01, ///< Oscillator set to Audio
    BSP_BYPASS_OSCILLATOR_EMCLK = 0x02, ///< Oscillator set to EMCLK
} bsp_bypass_oscillator_t;

/** Superset of bypass modes. */
typedef enum e_bsp_bypass_mode
{
    BSP_BYPASS_MODE_CRYSTAL_OSC  = 0x00, ///< Bypass mode set to Crystal oscillator
    BSP_BYPASS_MODE_EXTERNAL_CLK = 0x01, ///< Bypass mode set to External clock receive
    BSP_BYPASS_MODE_POWER_DOWN   = 0x02, ///< Bypass mode set to Power-down
} bsp_bypass_mode_t;

/** Superset of frequency range for bypass mode. */
typedef enum e_bsp_bypass_freq_range
{
    BSP_BYPASS_FREQ_RANGE_1MHZ  = 0x00, ///< Frequency range set to 32KHz to 1MHz
    BSP_BYPASS_FREQ_RANGE_12MHZ = 0x02, ///< Frequency range set to 1.1MHz to 12MHz
    BSP_BYPASS_FREQ_RANGE_24MHZ = 0x01, ///< Frequency range set to 12.1MHz to 24MHz
    BSP_BYPASS_FREQ_RANGE_48MHZ = 0x03, ///< Frequency range set to 24.1MHz to 48MHz
} bsp_bypass_freq_range_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern volatile uint32_t g_protect_pfswe_counter;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Read the current input level of the pin.
 *
 * @param[in]  pin             The pin
 *
 * @retval     Current input level
 **********************************************************************************************************************/
__STATIC_INLINE uint32_t R_BSP_PinRead (bsp_io_port_pin_t pin)
{
    /* Read pin level. */
    volatile const uint8_t * p_pin;

    p_pin = BSP_IO_PRV_PIN_REG_BASE_SET(BSP_FEATURE_IOPORT_GP_REG_BASE_NUM);
    p_pin = &p_pin[pin >> BSP_IO_PRV_PORT_OFFSET];

    return (uint32_t) ((*p_pin) >> (pin & BSP_IO_PRV_8BIT_MASK)) & BSP_IO_PRV_PIN_MASK;
}

/*******************************************************************************************************************//**
 * Set a pin to output and set the output level to the level provided
 *
 * @param[in]  pin      The pin
 * @param[in]  level    The level
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinWrite (bsp_io_port_pin_t pin, bsp_io_level_t level)
{
    /* Set output level and pin direction to output. */
    volatile uint16_t * p_pm;
    volatile uint8_t  * p_p;
    uint16_t            reg_value_pm;
    uint8_t             reg_value_p;
    uint16_t            mask_pm;
    uint8_t             mask_p;
    uint16_t            write_value_pm;
    uint8_t             write_value_p;

    p_pm = BSP_IO_PRV_PM_REG_BASE_SET(BSP_FEATURE_IOPORT_GP_REG_BASE_NUM);
    p_p  = BSP_IO_PRV_P_REG_BASE_SET(BSP_FEATURE_IOPORT_GP_REG_BASE_NUM);

    reg_value_pm = p_pm[pin >> BSP_IO_PRV_PORT_OFFSET];
    reg_value_p  = p_p[pin >> BSP_IO_PRV_PORT_OFFSET];

    mask_pm = (uint16_t) (~(BSP_IO_PM_PM_OUTPUT << ((pin & BSP_IO_PRV_8BIT_MASK) * 2)));
    mask_p  = (uint8_t) (~(1 << (pin & BSP_IO_PRV_8BIT_MASK)));

    write_value_pm = (uint16_t) (BSP_IO_PM_PM_OUTPUT << ((pin & BSP_IO_PRV_8BIT_MASK) * 2));
    write_value_p  = (uint8_t) (level << (pin & BSP_IO_PRV_8BIT_MASK));

    p_pm[pin >> BSP_IO_PRV_PORT_OFFSET] = ((reg_value_pm & mask_pm) | write_value_pm);
    p_p[pin >> BSP_IO_PRV_PORT_OFFSET]  = ((reg_value_p & mask_p) | write_value_p);
}

/*******************************************************************************************************************//**
 * Enable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur
 * via multiple threads or an ISR re-entering this code.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessEnable (void)
{
#if BSP_CFG_PFS_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /** If this is first entry then allow writing of PFS. */
    if (0 == g_protect_pfswe_counter)
    {
 #if BSP_FEATURE_BSP_SUPPORT_PFCWE_PROTECT
        R_GPIO->PWPR = 0;                              ///< Clear BOWI bit - writing to PFSWE bit enabled
        R_GPIO->PWPR = 1U << BSP_IO_PWPR_PFSWE_OFFSET; ///< Set PFSWE bit - writing to PFS register enabled
 #else
        R_GPIO->PWPR = (uint32_t) ((BSP_IO_PRV_PFCWE_MASK & R_GPIO->PWPR) | (1U << BSP_IO_PWPR_PFSWE_OFFSET));
 #endif
    }

    /** Increment the protect counter */
    g_protect_pfswe_counter++;

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/*******************************************************************************************************************//**
 * Disable access to the PFS registers. Uses a reference counter to protect against interrupts that could occur via
 * multiple threads or an ISR re-entering this code.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_PinAccessDisable (void)
{
#if BSP_CFG_PFS_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /** Is it safe to disable PFS register? */
    if (0 != g_protect_pfswe_counter)
    {
        /* Decrement the protect counter */
        g_protect_pfswe_counter--;
    }

    /** Is it safe to disable writing of PFS? */
    if (0 == g_protect_pfswe_counter)
    {
 #if BSP_FEATURE_BSP_SUPPORT_PFCWE_PROTECT
        R_GPIO->PWPR = 0;                             ///< Clear PFSWE bit - writing to PFS register disabled
        R_GPIO->PWPR = 1U << BSP_IO_PWPR_B0WI_OFFSET; ///< Set BOWI bit - writing to PFSWE bit disabled
 #else
        R_GPIO->PWPR = (uint32_t) (BSP_IO_PRV_PFCWE_MASK & R_GPIO->PWPR);
 #endif
    }

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
#endif
}

/*******************************************************************************************************************//**
 * Enable access to the OEN registers.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_OENAccessEnable (void)
{
#if BSP_FEATURE_BSP_SUPPORT_OEN_PROTECT
 #if BSP_CFG_PFS_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    R_GPIO->PWPR = (uint32_t) ((BSP_IO_PRV_OENWE_MASK & R_GPIO->PWPR) | (1U << BSP_IO_PWPR_OENWE_OFFSET));

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
 #endif
#endif
}

/*******************************************************************************************************************//**
 * Disable access to the OEN registers.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_OENAccessDisable (void)
{
#if BSP_FEATURE_BSP_SUPPORT_OEN_PROTECT
 #if BSP_CFG_PFS_PROTECT

    /** Get the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    R_GPIO->PWPR = (uint32_t) (BSP_IO_PRV_OENWE_MASK & R_GPIO->PWPR);

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
 #endif
#endif
}

/*******************************************************************************************************************//**
 * Configures Ethernet channel PHY mode.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_EthernetModeCfg (bsp_ethernet_channel_t channel, bsp_ethernet_mode_t mode)
{
#if BSP_FEATURE_BSP_SUPPORT_ETHER_MODE
 #if BSP_FEATURE_BSP_HAS_PFC_OEN_REG
    if (mode == BSP_ETHERNET_MODE_RMII)
    {
        if (channel == BSP_ETHERNET_CHANNEL_0)
        {
            R_CPG->CPG_SSEL0 |= BSP_IO_PRV_SET_SSEL0_SELCTL2;
        }
        else
        {
            R_CPG->CPG_SSEL1 |= BSP_IO_PRV_SET_SSEL1_SELCTL0;
        }
    }

    R_BSP_OENAccessEnable();

    if (BSP_ETHERNET_CHANNEL_0 == channel)
    {
        R_GPIO->PFC_OEN_b.OEN0 = mode;
    }
    else if (BSP_ETHERNET_CHANNEL_1 == channel)
    {
        R_GPIO->PFC_OEN_b.OEN1 = mode;
    }

    R_BSP_OENAccessDisable();
 #elif BSP_FEATURE_BSP_HAS_ETHER_MODE_REG
    uint32_t reg_value = R_GPIO->ETH_MODE;

    reg_value = (uint32_t) ((reg_value & (uint32_t) (~(1 << channel))) | (mode << channel));

    R_GPIO->ETH_MODE = reg_value;
 #else
    uint8_t reg_value = R_GPIO->ETH_MII_RGMII;

    reg_value = (uint8_t) ((reg_value & (uint8_t) (~(1 << channel))) | (mode << channel));

    R_GPIO->ETH_MII_RGMII = reg_value;
 #endif
#else
    FSP_PARAMETER_NOT_USED(channel);
    FSP_PARAMETER_NOT_USED(mode);
#endif
}

/*******************************************************************************************************************//**
 * Configures SD channel voltage mode.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_SDVoltageModeCfg (bsp_sd_channel_t channel, bsp_sd_voltage_t voltage)
{
#if BSP_FEATURE_BSP_SUPPORT_SD_VOLT
    if (BSP_SD_CHANNEL_0 == channel)
    {
 #if BSP_FEATURE_BSP_HAS_SD_CH_POC_REG
        R_GPIO->SD_CH0_POC = voltage;
 #else
        R_GPIO->SD_ch0 = voltage;
 #endif
    }
    else if (BSP_SD_CHANNEL_1 == channel)
    {
 #if BSP_FEATURE_BSP_HAS_SD_CH_POC_REG
        R_GPIO->SD_CH1_POC = voltage;
 #else
        R_GPIO->SD_ch1 = voltage;
 #endif
    }
    else
    {
        /* Do nothing. */
        FSP_PARAMETER_NOT_USED(voltage);
    }

#else
    FSP_PARAMETER_NOT_USED(channel);
    FSP_PARAMETER_NOT_USED(voltage);
#endif
}

/*******************************************************************************************************************//**
 * Configures QSPI channel voltage mode.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_QSPIVoltageModeCfg (bsp_qspi_voltage_t voltage)
{
#if BSP_FEATURE_BSP_SUPPORT_QSPI_VOLT
    R_GPIO->QSPI = voltage;
#else
    FSP_PARAMETER_NOT_USED(voltage);
#endif
}

/*******************************************************************************************************************//**
 * Configures XSPI channel voltage mode.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_XSPIVoltageModeCfg (bsp_xspi_voltage_t voltage)
{
#if BSP_FEATURE_BSP_SUPPORT_XSPI_VOLT
    R_GPIO->XSPI_POC = voltage;
#else
    FSP_PARAMETER_NOT_USED(voltage);
#endif
}

/*******************************************************************************************************************//**
 * Configures Ethernet channel voltage mode.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_EthernetVoltageModeCfg (bsp_ethernet_channel_t channel, bsp_ethernet_voltage_t voltage)
{
#if BSP_FEATURE_BSP_SUPPORT_ETHER_VOLT
    if (BSP_ETHERNET_CHANNEL_0 == channel)
    {
 #if BSP_FEATURE_BSP_HAS_ETH_POC_REG
        R_GPIO->ETH0_POC = voltage;
 #else
        R_GPIO->ETH_ch0 = voltage;
 #endif
    }
    else if (BSP_ETHERNET_CHANNEL_1 == channel)
    {
 #if BSP_FEATURE_BSP_HAS_ETH_POC_REG
        R_GPIO->ETH1_POC = voltage;
 #else
        R_GPIO->ETH_ch1 = voltage;
 #endif
    }
    else
    {
        /* Do nothing. */
        FSP_PARAMETER_NOT_USED(voltage);
    }

#else
    FSP_PARAMETER_NOT_USED(channel);
    FSP_PARAMETER_NOT_USED(voltage);
#endif
}

/*******************************************************************************************************************//**
 * Configures I3C control.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_I3CControlCfg (bsp_i3c_voltage_t voltage, bsp_i3c_mode_t mode)
{
#if BSP_FEATURE_BSP_SUPPORT_I3C
    R_GPIO->I3C_SET_b.POC  = voltage;
    R_GPIO->I3C_SET_b.STBN = mode;
#else
    FSP_PARAMETER_NOT_USED(voltage);
    FSP_PARAMETER_NOT_USED(mode);
#endif
}

/*******************************************************************************************************************//**
 * Configures bypass mode for RTC, Audio and EMCLK oscillator.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_BypassModeCfg (bsp_bypass_oscillator_t oscillator,
                                          bsp_bypass_mode_t       mode,
                                          bsp_bypass_freq_range_t freq_range)
{
#if BSP_FEATURE_BSP_SUPPORT_BYPASS
    switch (oscillator)
    {
        case BSP_BYPASS_OSCILLATOR_AUDIO:
        {
            R_GPIO->PFC_OSCBYPS_b.OSCBYPS1 = mode & 1U;
            R_GPIO->PFC_OSCBYPS_b.OSCPW1   = ((mode >> 1U) & 1U);
            R_GPIO->PFC_OSCBYPS_b.OSCSF1   = freq_range;
            break;
        }

        case BSP_BYPASS_OSCILLATOR_EMCLK:
        {
            R_GPIO->PFC_OSCBYPS_b.OSCBYPS2 = mode & 1U;
            R_GPIO->PFC_OSCBYPS_b.OSCPW2   = ((mode >> 1U) & 1U);
            R_GPIO->PFC_OSCBYPS_b.OSCSF2   = freq_range;
            break;
        }

        case BSP_BYPASS_OSCILLATOR_RTC:
        {
            R_GPIO->PFC_OSCBYPS_b.OSCBYPS0 = mode & 1U;
            R_GPIO->PFC_OSCBYPS_b.OSCPW0   = ((mode >> 1U) & 1U);
            FSP_PARAMETER_NOT_USED(freq_range);
            break;
        }

        default:

            /* Do nothing. */
            FSP_PARAMETER_NOT_USED(mode);
            FSP_PARAMETER_NOT_USED(freq_range);
    }

#else
    FSP_PARAMETER_NOT_USED(oscillator);
    FSP_PARAMETER_NOT_USED(mode);
    FSP_PARAMETER_NOT_USED(freq_range);
#endif
}

/*******************************************************************************************************************//**
 * Configures XSPI output Enable.
 **********************************************************************************************************************/
__STATIC_INLINE void R_BSP_XSPIOutputEnableCfg (void)
{
#if BSP_FEATURE_BSP_SUPPORT_XSPI_OUTPUT
    R_BSP_OENAccessEnable();
    R_GPIO->PFC_OEN_b.OEN2 = BSP_IO_PRV_SET_OEN_ENABLE;
    R_GPIO->PFC_OEN_b.OEN3 = BSP_IO_PRV_SET_OEN_ENABLE;
    R_GPIO->PFC_OEN_b.OEN4 = BSP_IO_PRV_SET_OEN_ENABLE;
    R_GPIO->PFC_OEN_b.OEN5 = BSP_IO_PRV_SET_OEN_ENABLE;
    R_BSP_OENAccessDisable();
#endif
}

/** @} (end addtogroup BSP_IO) */

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

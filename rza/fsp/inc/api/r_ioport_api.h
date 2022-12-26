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
 * @ingroup RENESAS_INTERFACES
 * @defgroup IOPORT_API I/O Port Interface
 * @brief Interface  for accessing I/O ports and configuring I/O functionality.
 *
 * @section IOPORT_API_SUMMARY Summary
 * The IOPort shared interface provides the ability to access the IOPorts of a device at both bit and port level.
 * Port and pin direction can be changed.
 *
 * IOPORT Interface description: @ref IOPORT
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_IOPORT_API_H
#define R_IOPORT_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common error codes and definitions. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Private definition to set enumeration values. */
#define IOPORT_PRV_PFS_PSEL_OFFSET    (24)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** IO port type used with ports */
typedef uint16_t ioport_size_t;        ///< IO port size on this device

/** Superset of all peripheral functions.  */
typedef enum e_ioport_peripheral
{
    /** Pin will function as a Mode0 peripheral pin */
    IOPORT_PERIPHERAL_MODE0 = (0x0UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode1 peripheral pin */
    IOPORT_PERIPHERAL_MODE1 = (0x1UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode2 peripheral pin */
    IOPORT_PERIPHERAL_MODE2 = (0x2UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode3 peripheral pin */
    IOPORT_PERIPHERAL_MODE3 = (0x3UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode4 peripheral pin */
    IOPORT_PERIPHERAL_MODE4 = (0x4UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode5 peripheral pin */
    IOPORT_PERIPHERAL_MODE5 = (0x5UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode6 peripheral pin */
    IOPORT_PERIPHERAL_MODE6 = (0x6UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Pin will function as a Mode7 peripheral pin */
    IOPORT_PERIPHERAL_MODE7 = (0x7UL << IOPORT_PRV_PFS_PSEL_OFFSET),

    /** Marks end of enum - used by parameter checking */
    IOPORT_PERIPHERAL_END
} ioport_peripheral_t;

/** Superset of SD channels. */
typedef enum e_ioport_sd_ch
{
    IOPORT_SD_CHANNEL_0 = 0x10,        ///< Used to select SD channel 0
    IOPORT_SD_CHANNEL_1 = 0x20,        ///< Used to select SD channel 1
    IOPORT_SD_CHANNEL_END              ///< Marks end of enum - used by parameter checking
} ioport_sd_channel_t;

/** Superset of QSPI channels. */
typedef enum e_ioport_qspi_ch
{
    IOPORT_QSPI_CHANNEL_0 = 0x10,      ///< Used to select QSPI channel 0
    IOPORT_QSPI_CHANNEL_1 = 0x20,      ///< Used to select QSPI channel 1
    IOPORT_QSPI_CHANNEL_END            ///< Marks end of enum - used by parameter checking
} ioport_qspi_channel_t;

/* DEPRECATED Superset of Ethernet channels. */
typedef enum e_ioport_eth_ch
{
    IOPORT_ETHERNET_CHANNEL_0 = 0x10,  ///< Used to select Ethernet channel 0
    IOPORT_ETHERNET_CHANNEL_1 = 0x20,  ///< Used to select Ethernet channel 1
    IOPORT_ETHERNET_CHANNEL_END        ///< Marks end of enum - used by parameter checking
} ioport_ethernet_channel_t;

/** Superset of SD voltages. */
typedef enum e_ioport_sd_voltage
{
    IOPORT_SD_VOLTAGE_33 = 0x00,       ///< SD voltage set to 3.3V
    IOPORT_SD_VOLTAGE_18 = 0x01,       ///< SD voltage set to 1.8V
    IOPORT_SD_VOLTAGE_END              ///< Marks end of enum - used by parameter checking
} ioport_sd_voltage_t;

/** Superset of QSPI voltages. */
typedef enum e_ioport_qspi_voltage
{
    IOPORT_QSPI_VOLTAGE_33 = 0x00,     ///< QSPI voltage set to 3.3V
    IOPORT_QSPI_VOLTAGE_18 = 0x01,     ///< QSPI voltage set to 1.8V
    IOPORT_QSPI_VOLTAGE_END            ///< Marks end of enum - used by parameter checking
} ioport_qspi_voltage_t;

/** Superset of Ethernet voltages. */
typedef enum e_ioport_eth_voltage
{
    IOPORT_ETHERNET_VOLTAGE_33 = 0x00, ///< Ethernet voltage set to 3.3V
    IOPORT_ETHERNET_VOLTAGE_18 = 0x01, ///< Ethernet voltage set to 1.8V
    IOPORT_ETHERNET_VOLTAGE_25 = 0x02, ///< Ethernet voltage set to 2.5V
    RESERVED,
    IOPORT_ETHERNET_VOLTAGE_END        ///< Marks end of enum - used by parameter checking
} ioport_ethernet_voltage_t;

/* DEPRECATED Superset of Ethernet PHY modes. */
typedef enum e_ioport_eth_mode
{
    IOPORT_ETHERNET_MODE_RMII = 0x00,  ///< Ethernet PHY mode set to MII
    IOPORT_ETHERNET_MODE_MII  = 0x01,  ///< Ethernet PHY mode set to RMII
    IOPORT_ETHERNET_MODE_END           ///< Marks end of enum - used by parameter checking
} ioport_ethernet_mode_t;

/** Options to configure pin functions  */
typedef enum e_ioport_cfg_options
{
    /* For PM Register */
    IOPORT_CFG_PORT_DIRECTION_HIZ          = 0x00000000,        ///< Sets the pin direction to Hi-Z (default)
    IOPORT_CFG_PORT_DIRECTION_INPUT        = 0x00000004,        ///< Sets the pin direction to input
    IOPORT_CFG_PORT_DIRECTION_OUTPUT       = 0x00000008,        ///< Sets the pin direction to output (input disable)
    IOPORT_CFG_PORT_DIRECTION_OUTPUT_INPUT = 0x0000000C,        ///< Sets the pin direction to output (input enable)

    /* For P Register */
    IOPORT_CFG_PORT_OUTPUT_LOW  = 0x00000000,                   ///< Sets the pin level to low
    IOPORT_CFG_PORT_OUTPUT_HIGH = 0x00000001,                   ///< Sets the pin level to high

    /* For PUPD Register */
    IOPORT_CFG_PULLUP_PULLDOWN_DISABLE = 0x00000000,            ///< Disable the pin's internal pull-up and pull-down
    IOPORT_CFG_PULLUP_ENABLE           = 0x00000010,            ///< Enables the pin's internal pull-up
    IOPORT_CFG_PULLDOWN_ENABLE         = 0x00000020,            ///< Enables the pin's internal pull-down

    /* For IOLH Register */
    IOPORT_CFG_DRIVE_B00 = 0x00000000,                          ///< Sets the IOLH register value to b'00
    IOPORT_CFG_DRIVE_B01 = 0x00000400,                          ///< Sets the IOLH register value to b'01
    IOPORT_CFG_DRIVE_B10 = 0x00000800,                          ///< Sets the IOLH register value to b'10
    IOPORT_CFG_DRIVE_B11 = 0x00000C00,                          ///< Sets the IOLH register value to b'11

    /* For ISEL Register */
    IOPORT_CFG_TINT_DISABLE = 0x00000000,                       ///< Disable IRQ functionality for a pin
    IOPORT_CFG_TINT_ENABLE  = 0x00004000,                       ///< Sets pin as an IRQ pin

    /* For SR Register */
    IOPORT_CFG_SLEW_RATE_SLOW = 0x00000000,                     ///< Sets the pin slew-rate to slow
    IOPORT_CFG_SLEW_RATE_FAST = 0x00020000,                     ///< Sets the pin slew-rate to fast
    IOPORT_CFG_SLEW_RATE_FLAT = 0x00020000,                     ///< DEPRECATED Sets the pin slew-rate to flat

    /* For IEN Register */
    IOPORT_CFG_SPECIAL_PURPOSE_PORT_INPUT_DISABLE = 0x00000000, ///< Disable input the pin of special purpose port
    IOPORT_CFG_SPECIAL_PURPOSE_PORT_INPUT_ENABLE  = 0x00040000, ///< Sets the pin of special purpose port to input

    /* For FILONOFF Register */
    IOPORT_CFG_NOISE_FILTER_OFF = 0x00000000,                   ///< Noise filter disable
    IOPORT_CFG_NOISE_FILTER_ON  = 0x00080000,                   ///< Noise filter enable

    /* For FILNUM Register */
    IOPORT_CFG_NOISE_FILTER_NUM_4STAGE  = 0x00000000,           ///< Sets the pin noise filter to 4-stage filter
    IOPORT_CFG_NOISE_FILTER_NUM_8STAGE  = 0x00100000,           ///< Sets the pin noise filter to 8-stage filter
    IOPORT_CFG_NOISE_FILTER_NUM_12STAGE = 0x00200000,           ///< Sets the pin noise filter to 12-stage filter
    IOPORT_CFG_NOISE_FILTER_NUM_16STAGE = 0x00300000,           ///< Sets the pin noise filter to 16-stage filter

    /* For FILCLKSEL Register */
    IOPORT_CFG_NOISE_FILTER_NOT_DIVIDED   = 0x00000000,         ///< Noise filter not divided
    IOPORT_CFG_NOISE_FILTER_DIVIDED_9000  = 0x00400000,         ///< Noise filter divided by 9000
    IOPORT_CFG_NOISE_FILTER_DIVIDED_18000 = 0x00800000,         ///< Noise filter divided by 18000
    IOPORT_CFG_NOISE_FILTER_DIVIDED_36000 = 0x00C00000,         ///< Noise filter divided by 36000

    /* For PMC Register */
    IOPORT_CFG_PERIPHERAL_PIN = 0x00010000                      ///< Enables pin to operate as a peripheral pin
} ioport_cfg_options_t;

/** PFS writing enable/disable. */
typedef enum e_ioport_pwpr
{
    IOPORT_PFS_WRITE_DISABLE = 0,      ///< Disable PFS write access
    IOPORT_PFS_WRITE_ENABLE  = 1       ///< Enable PFS write access
} ioport_pwpr_t;

/** Pin identifier and Pin Function Setting (PFS) value */
typedef struct st_ioport_pin_cfg
{
    uint32_t          pin_cfg;         ///< Pin PFS configuration - Use ioport_cfg_options_t parameters to configure
    bsp_io_port_pin_t pin;             ///< Pin identifier
} ioport_pin_cfg_t;

/** Multiple pin configuration data for loading into each GPIO register by R_IOPORT_Init()  */
typedef struct st_ioport_cfg
{
    uint16_t                 number_of_pins; ///< Number of pins for which there is configuration data
    ioport_pin_cfg_t const * p_pin_cfg_data; ///< Pin configuration data
} ioport_cfg_t;

/** IOPORT control block.  Allocate an instance specific control block to pass into the IOPORT API calls.
 * @par Implemented as
 * - ioport_instance_ctrl_t
 */
typedef void ioport_ctrl_t;

/** IOPort driver structure. IOPort functions implemented at the HAL layer will follow this API. */
typedef struct st_ioport_api
{
    /** Initialize internal driver data and initial pin configurations.  Called during startup.  Do
     * not call this API during runtime.  Use @ref ioport_api_t::pinsCfg for runtime reconfiguration of
     * multiple pins.
     * @par Implemented as
     * - @ref R_IOPORT_Open()
     * @param[in]  p_cfg                Pointer to pin configuration data array.
     */
    fsp_err_t (* open)(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);

    /** Close the API.
     * @par Implemented as
     * - @ref R_IOPORT_Close()
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* close)(ioport_ctrl_t * const p_ctrl);

    /** Configure multiple pins.
     * @par Implemented as
     * - @ref R_IOPORT_PinsCfg()
     * @param[in]  p_cfg                Pointer to pin configuration data array.
     */
    fsp_err_t (* pinsCfg)(ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg);

    /** Configure settings for an individual pin.
     * @par Implemented as
     * - @ref R_IOPORT_PinCfg()
     * @param[in]  pin                  Pin to be read.
     * @param[in]  cfg                  Configuration options for the pin.
     */
    fsp_err_t (* pinCfg)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg);

    /** Read the event input data of the specified pin and return the level.
     * @par Implemented as
     * - @ref R_IOPORT_PinEventInputRead()
     * @param[in]  pin                  Pin to be read.
     * @param[in]  p_pin_event         Pointer to return the event data.
     */
    fsp_err_t (* pinEventInputRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event);

    /** Write pin event data.
     * @par Implemented as
     * - @ref R_IOPORT_PinEventOutputWrite()
     * @param[in]  pin                  Pin event data is to be written to.
     * @param[in]  pin_value            Level to be written to pin output event.
     */
    fsp_err_t (* pinEventOutputWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value);

    /** Configure the SD voltage of the SD channels.
     * @par Implemented as
     * - @ref R_IOPORT_SDVoltageModeCfg()
     * @param[in]  channel              Channel configuration will be set for.
     * @param[in]  voltage              Voltage to set the channel to.
     */
    fsp_err_t (* pinSDVoltageModeCfg)(ioport_ctrl_t * const p_ctrl, ioport_sd_channel_t channel,
                                      ioport_sd_voltage_t voltage);

    /** Configure the QSPI voltage of the QSPI channels.
     * @par Implemented as
     * - @ref R_IOPORT_QSPIVoltageModeCfg()
     * @param[in]  channel              Channel configuration will be set for.
     * @param[in]  voltage              Voltage to set the channel to.
     */
    fsp_err_t (* pinQSPIVoltageModeCfg)(ioport_ctrl_t * const p_ctrl, ioport_qspi_channel_t channel,
                                        ioport_qspi_voltage_t voltage);

    /** Configure the Ethernet voltage of the Ethernet channels.
     * @par Implemented as
     * - @ref R_IOPORT_EthernetVoltageModeCfg()
     * @param[in]  channel              Channel configuration will be set for.
     * @param[in]  voltage              Voltage to set the channel to.
     */
    fsp_err_t (* pinEthernetVoltageModeCfg)(ioport_ctrl_t * const p_ctrl, ioport_ethernet_channel_t channel,
                                            ioport_ethernet_voltage_t voltage);

    /* DEPRECATED Configure the PHY mode of the Ethernet channels.
     * @par Implemented as
     * - @ref R_IOPORT_EthernetModeCfg()
     * @param[in]  channel              Channel configuration will be set for.
     * @param[in]  mode                 PHY mode to set the channel to.
     */
    fsp_err_t (* pinEthernetModeCfg)(ioport_ctrl_t * const p_ctrl, ioport_ethernet_channel_t channel,
                                     ioport_ethernet_mode_t mode);

    /** Read level of a pin.
     * @par Implemented as
     * - @ref R_IOPORT_PinRead()
     * @param[in]  pin                  Pin to be read.
     * @param[in]  p_pin_value          Pointer to return the pin level.
     */
    fsp_err_t (* pinRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value);

    /** Write specified level to a pin.
     * @par Implemented as
     * - @ref R_IOPORT_PinWrite()
     * @param[in]  pin                  Pin to be written to.
     * @param[in]  level                State to be written to the pin.
     */
    fsp_err_t (* pinWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level);

    /** Set the direction of one or more pins on a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortDirectionSet()
     * @param[in]  port                 Port being configured.
     * @param[in]  direction_values     Value controlling direction of pins on port
     *                                  (3 - output (input enable), 2 - output (input disable), 1 input, 0 - Hi-Z).
     * @param[in]  mask                 Mask controlling which pins on the port are to be configured.
     */
    fsp_err_t (* portDirectionSet)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t direction_values,
                                   ioport_size_t mask);

    /** Read captured event data for a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortEventInputRead()
     * @param[in]  port                 Port to be read.
     * @param[in]  p_event_data         Pointer to return the event data.
     */
    fsp_err_t (* portEventInputRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data);

    /** Write event output data for a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortEventOutputWrite()
     * @param[in]  port                 Port event data will be written to.
     * @param[in]  event_data           Data to be written as event data to specified port.
     * @param[in]  mask_value           Each bit set to 1 in the mask corresponds to that bit's value in event data.
     * being written to port.
     */
    fsp_err_t (* portEventOutputWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t event_data,
                                       ioport_size_t mask_value);

    /** Read states of pins on the specified port.
     * @par Implemented as
     * - @ref R_IOPORT_PortRead()
     * @param[in]  port                 Port to be read.
     * @param[in]  p_port_value         Pointer to return the port value.
     */
    fsp_err_t (* portRead)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value);

    /** Write to multiple pins on a port.
     * @par Implemented as
     * - @ref R_IOPORT_PortWrite()
     * @param[in]  port                 Port to be written to.
     * @param[in]  value                Value to be written to the port.
     * @param[in]  mask                 Mask controlling which pins on the port are written to.
     */
    fsp_err_t (* portWrite)(ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask);
} ioport_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ioport_instance
{
    ioport_ctrl_t      * p_ctrl;       ///< Pointer to the control structure for this instance
    ioport_cfg_t const * p_cfg;        ///< Pointer to the configuration structure for this instance
    ioport_api_t const * p_api;        ///< Pointer to the API structure for this instance
} ioport_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup IOPORT_API)
 **********************************************************************************************************************/

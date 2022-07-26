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
#include <stdint.h>
#include "bsp_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "PORT" in ASCII, used to determine if the module is open */
#define IOPORT_OPEN                       (0x504F5254U)
#define IOPORT_CLOSED                     (0x00000000U)

/* Shift to get pin 0 on a package in extended data. */
#define IOPORT_PRV_EXISTS_B0_SHIFT        (16UL)

/* Mask to determine if any pins on port exist on this package. */
#define IOPORT_PRV_PORT_EXISTS_MASK       (0xFFFF0000U)

/* Shift to get port in bsp_io_port_t and bsp_io_port_pin_t enums. */
#define IOPORT_PRV_PORT_OFFSET            (8U)

#define IOPORT_PRV_PORT_BITS              (0xFF00U)
#define IOPORT_PRV_PIN_BITS               (0x00FFU)

/* Macro definition for generating the values to set for each register from the ioport_cfg_options_t enums. */
#define IOPORT_PRV_P_OFFSET               (0U)
#define IOPORT_PRV_PM_OFFSET              (2U)
#define IOPORT_PRV_PUPD_OFFSET            (4U)
#define IOPORT_PRV_IOLH_OFFSET            (10U)
#define IOPORT_PRV_ISEL_OFFSET            (14U)
#define IOPORT_PRV_PMC_OFFSET             (16U)
#define IOPORT_PRV_SR_OFFSET              (17U)
#define IOPORT_PRV_IEN_OFFSET             (18U)
#define IOPORT_PRV_FILONOFF_OFFSET        (19U)
#define IOPORT_PRV_FILNUM_OFFSET          (20U)
#define IOPORT_PRV_FILCLKSEL_OFFSET       (22U)
#define IOPORT_PRV_PFC_OFFSET             (24U)

#define IOPORT_PRV_PERIPHERAL_FUNCTION    (1U << 16)

#define IOPORT_PRV_2BIT_MASK              (0x3U)
#define IOPORT_PRV_8BIT_MASK              (0xFFU)

#define IOPORT_PRV_BITFIELD_1BIT          (1U)
#define IOPORT_PRV_BITFIELD_2BIT          (3U)
#define IOPORT_PRV_BITFIELD_3BIT          (7U)

#define IOPORT_PRV_POS_ALIGN_2BIT         (2U)
#define IOPORT_PRV_POS_ALIGN_4BIT         (4U)
#define IOPORT_PRV_POS_ALIGN_8BIT         (8U)

#define IOPORT_PRV_SET_PWPR_PFSWE         (0x40U)
#define IOPORT_PRV_SET_PWPR_BOWI          (0x80U)

#define IOPORT_PRV_NONMASK_ACCESS         (0xFFFFFFFFUL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_ioport_pins_config(const ioport_cfg_t * p_cfg);

static void r_ioport_pfs_write(bsp_io_port_pin_t pin, uint32_t value);

static void r_ioport_dedicated_port_cfg(bsp_io_port_pin_t pin, uint32_t value);
static void r_ioport_peri_mode_pin_config(bsp_io_port_pin_t pin, uint32_t value);
static void r_ioport_port_mode_pin_config(bsp_io_port_pin_t pin, uint32_t value);
static void r_ioport_make_port_pin_num(bsp_io_port_pin_t pin, uint8_t * p_port_number, uint8_t * p_pin_number);
static void r_ioport_regwrite_8(volatile uint8_t * ioreg, uint8_t write_value, uint8_t shift, uint8_t mask);
static void r_ioport_regwrite_16(volatile uint16_t * ioreg, uint16_t write_value, uint16_t shift, uint16_t mask);
static void r_ioport_regwrite_32(volatile uint32_t * ioreg, uint32_t write_value, uint32_t shift, uint32_t mask);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/* IOPort Implementation of IOPort Driver  */
const ioport_api_t g_ioport_on_ioport =
{
    .open                      = R_IOPORT_Open,
    .close                     = R_IOPORT_Close,
    .pinsCfg                   = R_IOPORT_PinsCfg,
    .pinCfg                    = R_IOPORT_PinCfg,
    .pinEventInputRead         = R_IOPORT_PinEventInputRead,
    .pinEventOutputWrite       = R_IOPORT_PinEventOutputWrite,
    .pinSDVoltageModeCfg       = R_IOPORT_SDVoltageModeCfg,
    .pinQSPIVoltageModeCfg     = R_IOPORT_QSPIVoltageModeCfg,
    .pinEthernetVoltageModeCfg = R_IOPORT_EthernetVoltageModeCfg,
    .pinEthernetModeCfg        = R_IOPORT_EthernetModeCfg,
    .pinRead                   = R_IOPORT_PinRead,
    .pinWrite                  = R_IOPORT_PinWrite,
    .portDirectionSet          = R_IOPORT_PortDirectionSet,
    .portEventInputRead        = R_IOPORT_PortEventInputRead,
    .portEventOutputWrite      = R_IOPORT_PortEventOutputWrite,
    .portRead                  = R_IOPORT_PortRead,
    .portWrite                 = R_IOPORT_PortWrite,
};

/*******************************************************************************************************************//**
 * @addtogroup IOPORT
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initializes internal driver data, then calls pin configuration function to configure pins.
 *
 * @retval FSP_SUCCESS                  Pin configuration data written to PFS register(s)
 * @retval FSP_ERR_ASSERTION            NULL pointer
 * @retval FSP_ERR_ALREADY_OPEN         Module is already open.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_Open (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data);
    FSP_ERROR_RETURN(IOPORT_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set driver status to open */
    p_instance_ctrl->open = IOPORT_OPEN;

    r_ioport_pins_config(p_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Resets IOPORT registers. Implements @ref ioport_api_t::close
 *
 * @retval FSP_SUCCESS             The IOPORT was successfully uninitialized
 * @retval FSP_ERR_ASSERTION       p_ctrl was NULL
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_Close (ioport_ctrl_t * const p_ctrl)
{
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Set state to closed */
    p_instance_ctrl->open = IOPORT_CLOSED;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the functions of multiple pins by loading configuration data into each registers.
 * Implements @ref ioport_api_t::pinsCfg.
 *
 * This function initializes the supplied list of each registers with the supplied values. This data define in
 * pin_data.c. Different pin configurations can be loaded for different situations such as low power modes and testing.
 *
 * @retval FSP_SUCCESS             Pin configuration data written to each registers
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 * @retval FSP_ERR_ASSERTION       NULL pointer
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinsCfg (ioport_ctrl_t * const p_ctrl, const ioport_cfg_t * p_cfg)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_pin_cfg_data);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    r_ioport_pins_config(p_cfg);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the settings of a pin. Implements @ref ioport_api_t::pinCfg.
 *
 * @retval FSP_SUCCESS             Pin configured
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 * @retval FSP_ERR_ASSERTION       NULL pointer
 *
 * @note This function is re-entrant for different pins.
 * This function will change the configuration of the pin with the new configuration. For example it is not possible
 * with this function to change the drive strength of a pin while leaving all the other pin settings unchanged. To
 * achieve this the original settings with the required change will need to be written using this function.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinCfg (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, uint32_t cfg)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    R_BSP_PinAccessEnable();

    r_ioport_pfs_write(pin, cfg);

    R_BSP_PinAccessDisable();

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the level on a pin. Implements @ref ioport_api_t::pinRead.
 *
 * @retval FSP_SUCCESS             Pin read
 * @retval FSP_ERR_ASSERTION       NULL pointer
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 * @note This function is re-entrant for different pins.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_value)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_pin_value);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    *p_pin_value = (bsp_io_level_t) R_BSP_PinRead(pin);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads the value on an IO port. Implements @ref ioport_api_t::portRead.
 *
 * The specified port will be read, and the levels for all the pins will be returned.
 * Each bit in the returned value corresponds to a pin on the port. For example, bit 4 corresponds
 * to pin 4, bit 3 to pin 3, and so on.
 *
 * @retval FSP_SUCCESS             Port read
 * @retval FSP_ERR_ASSERTION       NULL pointer
 * @retval FSP_ERR_NOT_OPEN        The module has not been opened
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_port_value)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_port_value);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the port address */
    volatile const uint8_t * p_ioport_regs;
    p_ioport_regs = &R_GPIO->PIN10;
    p_ioport_regs = &p_ioport_regs[port >> IOPORT_PRV_PORT_OFFSET];

    /* Read current value of PIN register for the specified port */
    *p_port_value = *p_ioport_regs;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes to multiple pins on a port. Implements @ref ioport_api_t::portWrite.
 *
 * The input value will be written to the specified port. Each bit in the value parameter corresponds to a bit
 * on the port. For example, bit 4 corresponds to pin 4, bit 3 to pin 3, and so on.
 * Each bit in the mask parameter corresponds to a pin on the port.
 *
 * Only the bits with the corresponding bit in the mask value set will be updated.
 * For example, value = 0xFFFF, mask = 0x0003 results in only bits 0 and 1 being updated.
 *
 * @retval FSP_SUCCESS                  Port written to
 * @retval FSP_ERR_INVALID_ARGUMENT     The port and/or mask not valid
 * @retval FSP_ERR_NOT_OPEN             The module has not been opened
 * @retval FSP_ERR_ASSERTION            NULL pointerd
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t value, ioport_size_t mask)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the port address */
    volatile uint8_t * p_ioport_regs;
    p_ioport_regs = &R_GPIO->P10;
    p_ioport_regs = &p_ioport_regs[port >> IOPORT_PRV_PORT_OFFSET];

    /* Set the port level to P register */
    r_ioport_regwrite_8(p_ioport_regs, (uint8_t) value, 0, (uint8_t) mask);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets a pin's output either high or low. Implements @ref ioport_api_t::pinWrite.
 *
 * @retval FSP_SUCCESS                  Pin written to
 * @retval FSP_ERR_INVALID_ARGUMENT     The pin and/or level not valid
 * @retval FSP_ERR_NOT_OPEN             The module has not been opene
 * @retval FSP_ERR_ASSERTION            NULL pointerd
 *
 * @note This function is re-entrant for different pins.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t level)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(level <= BSP_IO_LEVEL_HIGH, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    bsp_io_port_t port     = (bsp_io_port_t) (IOPORT_PRV_PORT_BITS & (ioport_size_t) pin);
    ioport_size_t shift    = IOPORT_PRV_PIN_BITS & (ioport_size_t) pin;
    ioport_size_t pin_mask = (ioport_size_t) (1U << shift);

    /* Get the port address */
    volatile uint8_t * p_ioport_regs;
    p_ioport_regs = &R_GPIO->P10;
    p_ioport_regs = &p_ioport_regs[port >> IOPORT_PRV_PORT_OFFSET];

    /* Set the pin level to P register */
    r_ioport_regwrite_8(p_ioport_regs, (uint8_t) level, (uint8_t) shift, (uint8_t) pin_mask);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the direction of individual pins on a port. Implements @ref ioport_api_t::portDirectionSet().
 *
 * Multiple pins on a port can be set to inputs or outputs at once.
 * Each bit in the mask parameter corresponds to a pin on the port. For example, bit[9:8] corresponds to pin 4,
 * bit[7:6] to pin 3, and so on.
 * If bits are set to b'11 then the corresponding pin will be changed to an input or an output or Hi-Z as specified by
 * the direction values. If a mask bits are set to b'00 then the direction of the pin will not be changed.
 *
 * @retval FSP_SUCCESS                 Port direction updated
 * @retval FSP_ERR_INVALID_ARGUMENT    The port and/or mask not valid
 * @retval FSP_ERR_NOT_OPEN            The module has not been opened
 * @retval FSP_ERR_ASSERTION           NULL pointer
 *
 * @note This function is re-entrant for different ports.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortDirectionSet (ioport_ctrl_t * const p_ctrl,
                                     bsp_io_port_t         port,
                                     ioport_size_t         direction_values,
                                     ioport_size_t         mask)
{
#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(mask > (ioport_size_t) 0, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    /* Get the port address */
    volatile uint16_t * p_ioport_regs;
    p_ioport_regs = &R_GPIO->PM10;
    p_ioport_regs = &p_ioport_regs[port >> IOPORT_PRV_PORT_OFFSET];

    /* Set the port direction to PM register */
    r_ioport_regwrite_16(p_ioport_regs, direction_values, 0, mask);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures SD channel voltage mode. Implements @ref ioport_api_t::pinSDVoltageModeCfg.
 *
 * @retval FSP_SUCCESS              SD voltage mode set
 * @retval FSP_ERR_INVALID_ARGUMENT Channel or voltage not valid
 * @retval FSP_ERR_UNSUPPORTED      SD voltage configuration not supported on this device.
 * @retval FSP_ERR_NOT_OPEN         The module has not been opened
 * @retval FSP_ERR_ASSERTION        NULL pointer
 *
 * @note This function is not re-entrant.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_SDVoltageModeCfg (ioport_ctrl_t * const p_ctrl,
                                     ioport_sd_channel_t   channel,
                                     ioport_sd_voltage_t   voltage)
{
    FSP_ERROR_RETURN(1U == BSP_FEATURE_IOPORT_HAS_SD, FSP_ERR_UNSUPPORTED);

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(channel < IOPORT_SD_CHANNEL_END, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(voltage < IOPORT_SD_VOLTAGE_END, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    if (IOPORT_SD_CHANNEL_0 == channel)
    {
        R_GPIO->SD_ch0 = voltage;
    }
    else if (IOPORT_SD_CHANNEL_1 == channel)
    {
        R_GPIO->SD_ch1 = voltage;
    }
    else
    {
        ;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures QSPI channel voltage mode. Implements @ref ioport_api_t::pinQSPIVoltageModeCfg.
 *
 * @retval FSP_SUCCESS              QSPI voltage mode set
 * @retval FSP_ERR_INVALID_ARGUMENT Channel or voltage not valid
 * @retval FSP_ERR_UNSUPPORTED      QSPI voltage configuration not supported on this device.
 * @retval FSP_ERR_NOT_OPEN         The module has not been opened
 * @retval FSP_ERR_ASSERTION        NULL pointer
 *
 * @note This function is not re-entrant.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_QSPIVoltageModeCfg (ioport_ctrl_t * const p_ctrl,
                                       ioport_qspi_channel_t channel,
                                       ioport_qspi_voltage_t voltage)
{
    FSP_ERROR_RETURN(1U == BSP_FEATURE_IOPORT_HAS_QSPI, FSP_ERR_UNSUPPORTED);

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(channel < IOPORT_QSPI_CHANNEL_END, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(voltage < IOPORT_QSPI_VOLTAGE_END, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(channel);
#endif

    R_GPIO->QSPI = voltage;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures Ethernet channel voltage mode. Implements @ref ioport_api_t::pinEthernetVoltageModeCfg.
 *
 * @retval FSP_SUCCESS              Ethernet voltage mode set
 * @retval FSP_ERR_INVALID_ARGUMENT Channel or voltage not valid
 * @retval FSP_ERR_UNSUPPORTED      Ethernet voltage configuration not supported on this device.
 * @retval FSP_ERR_NOT_OPEN         The module has not been opened
 * @retval FSP_ERR_ASSERTION        NULL pointer
 *
 * @note This function is not re-entrant.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_EthernetVoltageModeCfg (ioport_ctrl_t * const     p_ctrl,
                                           ioport_ethernet_channel_t channel,
                                           ioport_ethernet_voltage_t voltage)
{
    FSP_ERROR_RETURN(1U == BSP_FEATURE_IOPORT_HAS_ETHERNET, FSP_ERR_UNSUPPORTED);

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(channel < IOPORT_ETHERNET_CHANNEL_END, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(voltage < IOPORT_ETHERNET_VOLTAGE_END, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    if (IOPORT_ETHERNET_CHANNEL_0 == channel)
    {
        R_GPIO->ETH_ch0 = voltage;
    }
    else if (IOPORT_ETHERNET_CHANNEL_1 == channel)
    {
        R_GPIO->ETH_ch1 = voltage;
    }
    else
    {
        ;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * This API function has NOT been supported because RZ/A does not have an ELC.
 *
 * @retval FSP_ERR_UNSUPPORTED      R_IOPORT_PortEventInputRead is not supported on this device.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_t port, ioport_size_t * p_event_data)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(port);
    FSP_PARAMETER_NOT_USED(p_event_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * This API function has NOT been supported because RZ/A does not have an ELC.
 *
 * @retval FSP_ERR_UNSUPPORTED      R_IOPORT_PinEventInputRead is not supported on this device.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinEventInputRead (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t * p_pin_event)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(pin);
    FSP_PARAMETER_NOT_USED(p_pin_event);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * This API function has NOT been supported because RZ/A does not have an ELC.
 *
 * @retval FSP_ERR_UNSUPPORTED      R_IOPORT_PortEventOutputWrite is not supported on this device.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PortEventOutputWrite (ioport_ctrl_t * const p_ctrl,
                                         bsp_io_port_t         port,
                                         ioport_size_t         event_data,
                                         ioport_size_t         mask_value)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(port);
    FSP_PARAMETER_NOT_USED(event_data);
    FSP_PARAMETER_NOT_USED(mask_value);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * This API function has NOT been supported because RZ/A does not have an ELC.
 *
 * @retval FSP_ERR_UNSUPPORTED      R_IOPORT_PinEventOutputWrite is not supported on this device.
 *
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_PinEventOutputWrite (ioport_ctrl_t * const p_ctrl, bsp_io_port_pin_t pin, bsp_io_level_t pin_value)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(pin);
    FSP_PARAMETER_NOT_USED(pin_value);

    return FSP_ERR_UNSUPPORTED;
}

/***********************************************************************************************************************
 * DEPRECATED Configures Ethernet channel PHY mode. Implements @ref ioport_api_t::pinEthernetModeCfg.
 *
 * @retval FSP_SUCCESS              Ethernet PHY mode set
 * @retval FSP_ERR_INVALID_ARGUMENT Channel or mode not valid
 * @retval FSP_ERR_UNSUPPORTED      Ethernet configuration not supported on this device.
 * @retval FSP_ERR_NOT_OPEN         The module has not been opened
 * @retval FSP_ERR_ASSERTION        NULL pointer
 *
 * @note This function is not re-entrant.
 **********************************************************************************************************************/
fsp_err_t R_IOPORT_EthernetModeCfg (ioport_ctrl_t * const     p_ctrl,
                                    ioport_ethernet_channel_t channel,
                                    ioport_ethernet_mode_t    mode)
{
    FSP_ERROR_RETURN(1U == BSP_FEATURE_IOPORT_HAS_ETHERNET, FSP_ERR_UNSUPPORTED);

#if (1 == IOPORT_CFG_PARAM_CHECKING_ENABLE)
    ioport_instance_ctrl_t * p_instance_ctrl = (ioport_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(IOPORT_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(channel < IOPORT_ETHERNET_CHANNEL_END, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(mode < IOPORT_ETHERNET_MODE_END, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    volatile uint8_t * p;
    uint8_t            mask;
    uint8_t            shift;

    p     = &R_GPIO->ETH_MII_RGMII;
    mask  = (uint8_t) (channel >> IOPORT_PRV_POS_ALIGN_4BIT);
    shift = (uint8_t) (channel >> (IOPORT_PRV_POS_ALIGN_4BIT + 1));

    r_ioport_regwrite_8(p, mode, shift, mask);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup IOPORT)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Configures pins.
 *
 * @param[in]    p_cfg          Pin configuration data
 **********************************************************************************************************************/
static void r_ioport_pins_config (const ioport_cfg_t * p_cfg)
{
    uint16_t       pin_count;
    ioport_cfg_t * p_pin_data;

    p_pin_data = (ioport_cfg_t *) p_cfg;

    R_BSP_PinAccessEnable();           // Protect PWPR from re-entrancy

    for (pin_count = 0U; pin_count < p_pin_data->number_of_pins; pin_count++)
    {
        r_ioport_pfs_write(p_pin_data->p_pin_cfg_data[pin_count].pin, p_pin_data->p_pin_cfg_data[pin_count].pin_cfg);
    }

    R_BSP_PinAccessDisable();
}

/**********************************************************************************************************************
 * End of function r_ioport_pins_config
 *********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Writes to the specified pin's PFS register
 *
 * @param[in]    pin        Pin to write PFS data for
 * @param[in]    value      Value to be written to the PFS register
 *
 **********************************************************************************************************************/
static void r_ioport_pfs_write (bsp_io_port_pin_t pin, uint32_t value)
{
    if (0 != (pin & IOPORT_PRV_PORT_EXISTS_MASK))
    {
        r_ioport_dedicated_port_cfg(pin, value);
    }
    else if ((value & IOPORT_PRV_PERIPHERAL_FUNCTION) > 0)
    {
        r_ioport_peri_mode_pin_config(pin, value);
    }
    else
    {
        r_ioport_port_mode_pin_config(pin, value);
    }
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's each registers for dedicated pin's
 *
 * @param[in]    pin        Pin to write pin function setting data for
 * @param[in]    value      Value to be written to the each registers
 *
 **********************************************************************************************************************/
static void r_ioport_dedicated_port_cfg (bsp_io_port_pin_t pin, uint32_t value)
{
    uint8_t             u_port;
    uint8_t             u_pin;
    uint32_t            bitpos_align;
    uint8_t             adr_offset;
    volatile uint32_t * p_ien;
    volatile uint32_t * p_iolh;
    volatile uint32_t * p_filonoff;
    volatile uint32_t * p_filnum;
    volatile uint32_t * p_filclksel;
    uint32_t            mask_ien;
    uint32_t            mask_iolh;
    uint32_t            mask_filonoff;
    uint32_t            mask_filnum;
    uint32_t            mask_filclksel;
    uint32_t            value_ien;
    uint32_t            value_iolh;
    uint32_t            value_filonoff;
    uint32_t            value_filnum;
    uint32_t            value_filclksel;

    r_ioport_make_port_pin_num(pin, &u_port, &u_pin);
    bitpos_align = (u_pin & IOPORT_PRV_2BIT_MASK) * IOPORT_PRV_POS_ALIGN_8BIT;

    adr_offset = (uint8_t) (((u_port - 2) * 2) + (u_pin >> 2));

    p_ien       = &R_GPIO->IEN02;
    p_iolh      = &R_GPIO->IOLH02;
    p_filonoff  = &R_GPIO->FILONOFF01;
    p_filnum    = &R_GPIO->FILNUM01;
    p_filclksel = &R_GPIO->FILCLKSEL01;

    mask_ien       = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_iolh      = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_filonoff  = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_filnum    = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_filclksel = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;

    value_ien       = (value >> IOPORT_PRV_IEN_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_iolh      = (value >> IOPORT_PRV_IOLH_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_filonoff  = (value >> IOPORT_PRV_FILONOFF_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_filnum    = (value >> IOPORT_PRV_FILNUM_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_filclksel = (value >> IOPORT_PRV_FILCLKSEL_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;

    /* Configure of IEN Register, IOLH Register, SR Register and PUPD Register */
    r_ioport_regwrite_32(&p_ien[adr_offset], value_ien, bitpos_align, mask_ien);
    r_ioport_regwrite_32(&p_iolh[adr_offset], value_iolh, bitpos_align, mask_iolh);

    /* When use NMI pin, configure FILONOFF, FILNUM, FILCLKSEL register. */
    if (((IOPORT_NMI & IOPORT_PRV_PORT_BITS) >> IOPORT_PRV_PORT_OFFSET) == u_port)
    {
        r_ioport_regwrite_32(p_filonoff, value_filonoff, bitpos_align, mask_filonoff);
        r_ioport_regwrite_32(p_filnum, value_filnum, bitpos_align, mask_filnum);
        r_ioport_regwrite_32(p_filclksel, value_filclksel, bitpos_align, mask_filclksel);
    }
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's each registers for peripheral pin's
 *
 * @param[in]    pin        Pin to write pin function setting data for
 * @param[in]    value      Value to be written to the each registers
 *
 **********************************************************************************************************************/
static void r_ioport_peri_mode_pin_config (bsp_io_port_pin_t pin, uint32_t value)
{
    uint8_t             u_port;
    uint8_t             u_pin;
    uint32_t            bitpos_align;
    uint8_t             adr_offset;
    volatile uint8_t  * p_pmc;
    volatile uint32_t * p_iolh;
    volatile uint32_t * p_sr;
    volatile uint32_t * p_pupd;
    volatile uint32_t * p_filonoff;
    volatile uint32_t * p_filnum;
    volatile uint32_t * p_filclksel;
    volatile uint32_t * p_pfc;
    uint8_t             mask_pmc;
    uint32_t            mask_iolh;
    uint32_t            mask_sr;
    uint32_t            mask_pupd;
    uint32_t            mask_filonoff;
    uint32_t            mask_filnum;
    uint32_t            mask_filclksel;
    uint32_t            mask_pfc;
    uint8_t             value_pmc;
    uint32_t            value_iolh;
    uint32_t            value_sr;
    uint32_t            value_pupd;
    uint32_t            value_filonoff;
    uint32_t            value_filnum;
    uint32_t            value_filclksel;
    uint32_t            value_pfc;

    r_ioport_make_port_pin_num(pin, &u_port, &u_pin);
    bitpos_align = (u_pin & IOPORT_PRV_2BIT_MASK) * IOPORT_PRV_POS_ALIGN_8BIT;

    adr_offset = (uint8_t) ((u_port * 2) + (u_pin >> 2));

    p_pmc       = &R_GPIO->PMC10;
    p_iolh      = &R_GPIO->IOLH10;
    p_sr        = &R_GPIO->SR10;
    p_pupd      = &R_GPIO->PUPD10;
    p_filonoff  = &R_GPIO->FILONOFF10;
    p_filnum    = &R_GPIO->FILNUM10;
    p_filclksel = &R_GPIO->FILCLKSEL10;
    p_pfc       = &R_GPIO->PFC10;

    mask_pmc       = (uint8_t) (IOPORT_PRV_BITFIELD_1BIT << u_pin);
    mask_iolh      = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_sr        = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_pupd      = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_filonoff  = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_filnum    = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_filclksel = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_pfc       = IOPORT_PRV_BITFIELD_3BIT << (u_pin * IOPORT_PRV_POS_ALIGN_4BIT);

    value_pmc       = (uint8_t) ((value >> IOPORT_PRV_PMC_OFFSET) & IOPORT_PRV_BITFIELD_1BIT);
    value_iolh      = (value >> IOPORT_PRV_IOLH_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_sr        = (value >> IOPORT_PRV_SR_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_pupd      = (value >> IOPORT_PRV_PUPD_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_filonoff  = (value >> IOPORT_PRV_FILONOFF_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_filnum    = (value >> IOPORT_PRV_FILNUM_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_filclksel = (value >> IOPORT_PRV_FILCLKSEL_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_pfc       = ((value >> IOPORT_PRV_PFC_OFFSET) & IOPORT_PRV_BITFIELD_3BIT);

    r_ioport_regwrite_8(&p_pmc[u_port], value_pmc, u_pin, mask_pmc);

    /* Configure of IOLH Register, SR Register, PUPD Register */
    r_ioport_regwrite_32(&p_iolh[adr_offset], value_iolh, bitpos_align, mask_iolh);
    r_ioport_regwrite_32(&p_sr[adr_offset], value_sr, bitpos_align, mask_sr);
    r_ioport_regwrite_32(&p_pupd[adr_offset], value_pupd, bitpos_align, mask_pupd);

    r_ioport_regwrite_32(&p_filonoff[adr_offset], value_filonoff, bitpos_align, mask_filonoff);
    r_ioport_regwrite_32(&p_filnum[adr_offset], value_filnum, bitpos_align, mask_filnum);
    r_ioport_regwrite_32(&p_filclksel[adr_offset], value_filclksel, bitpos_align, mask_filclksel);

    r_ioport_regwrite_32(&p_pfc[u_port], value_pfc, (uint32_t) (u_pin * IOPORT_PRV_POS_ALIGN_4BIT), mask_pfc);
}

/*******************************************************************************************************************//**
 * Writes to the specified pin's each registers for general purpose pin's
 *
 * @param[in]    pin        Pin to write pin function setting data for
 * @param[in]    value      Value to be written to the each registers
 *
 **********************************************************************************************************************/
static void r_ioport_port_mode_pin_config (bsp_io_port_pin_t pin, uint32_t value)
{
    uint8_t             u_port;
    uint8_t             u_pin;
    uint32_t            bitpos_align;
    uint8_t             adr_offset;
    volatile uint8_t  * p_pmc;
    volatile uint32_t * p_iolh;
    volatile uint32_t * p_sr;
    volatile uint32_t * p_pupd;
    volatile uint32_t * p_isel;
    volatile uint32_t * p_filonoff;
    volatile uint32_t * p_filnum;
    volatile uint32_t * p_filclksel;
    volatile uint16_t * p_pm;
    volatile uint8_t  * p_p;
    uint8_t             mask_pmc;
    uint32_t            mask_iolh;
    uint32_t            mask_sr;
    uint32_t            mask_pupd;
    uint32_t            mask_isel;
    uint32_t            mask_filonoff;
    uint32_t            mask_filnum;
    uint32_t            mask_filclksel;
    uint16_t            mask_pm;
    uint8_t             mask_p;
    uint8_t             value_pmc;
    uint32_t            value_iolh;
    uint32_t            value_sr;
    uint32_t            value_pupd;
    uint32_t            value_isel;
    uint32_t            value_filonoff;
    uint32_t            value_filnum;
    uint32_t            value_filclksel;
    uint16_t            value_pm;
    uint8_t             value_p;

    r_ioport_make_port_pin_num(pin, &u_port, &u_pin);
    bitpos_align = (u_pin & IOPORT_PRV_2BIT_MASK) * IOPORT_PRV_POS_ALIGN_8BIT;

    adr_offset = (uint8_t) ((u_port * 2) + (u_pin >> 2));

    p_pmc       = &R_GPIO->PMC10;
    p_iolh      = &R_GPIO->IOLH10;
    p_sr        = &R_GPIO->SR10;
    p_pupd      = &R_GPIO->PUPD10;
    p_isel      = &R_GPIO->ISEL10;
    p_filonoff  = &R_GPIO->FILONOFF10;
    p_filnum    = &R_GPIO->FILNUM10;
    p_filclksel = &R_GPIO->FILCLKSEL10;
    p_pm        = &R_GPIO->PM10;
    p_p         = &R_GPIO->P10;

    mask_pmc       = (uint8_t) (IOPORT_PRV_BITFIELD_1BIT << u_pin);
    mask_pm        = (uint16_t) (IOPORT_PRV_BITFIELD_2BIT << (u_pin * IOPORT_PRV_POS_ALIGN_2BIT));
    mask_iolh      = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_sr        = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_pupd      = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_isel      = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_filonoff  = IOPORT_PRV_BITFIELD_1BIT << bitpos_align;
    mask_filnum    = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_filclksel = IOPORT_PRV_BITFIELD_2BIT << bitpos_align;
    mask_p         = (uint8_t) (IOPORT_PRV_BITFIELD_1BIT << u_pin);

    value_pmc       = (uint8_t) ((value >> IOPORT_PRV_PMC_OFFSET) & IOPORT_PRV_BITFIELD_1BIT);
    value_iolh      = (value >> IOPORT_PRV_IOLH_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_sr        = (value >> IOPORT_PRV_SR_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_pupd      = (value >> IOPORT_PRV_PUPD_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_isel      = (value >> IOPORT_PRV_ISEL_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_filonoff  = (value >> IOPORT_PRV_FILONOFF_OFFSET) & IOPORT_PRV_BITFIELD_1BIT;
    value_filnum    = (value >> IOPORT_PRV_FILNUM_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_filclksel = (value >> IOPORT_PRV_FILCLKSEL_OFFSET) & IOPORT_PRV_BITFIELD_2BIT;
    value_pm        = (uint16_t) ((value >> IOPORT_PRV_PM_OFFSET) & IOPORT_PRV_BITFIELD_2BIT);
    value_p         = (uint8_t) ((value >> IOPORT_PRV_P_OFFSET) & IOPORT_PRV_BITFIELD_1BIT);

    /* Write configuration */
    r_ioport_regwrite_8(&p_pmc[u_port], value_pmc, u_pin, mask_pmc);

    r_ioport_regwrite_32(&p_iolh[adr_offset], value_iolh, bitpos_align, mask_iolh);
    r_ioport_regwrite_32(&p_sr[adr_offset], value_sr, bitpos_align, mask_sr);
    r_ioport_regwrite_32(&p_pupd[adr_offset], value_pupd, bitpos_align, mask_pupd);

    /* When setting the interrupt input using the GPIO input pin, set the ISEL register to "1". */
    r_ioport_regwrite_32(&p_isel[adr_offset], value_isel, bitpos_align, mask_isel);

    r_ioport_regwrite_32(&p_filonoff[adr_offset], value_filonoff, bitpos_align, mask_filonoff);
    r_ioport_regwrite_32(&p_filnum[adr_offset], value_filnum, bitpos_align, mask_filnum);
    r_ioport_regwrite_32(&p_filclksel[adr_offset], value_filclksel, bitpos_align, mask_filclksel);

    r_ioport_regwrite_16(&p_pm[u_port], value_pm, (uint16_t) (u_pin * IOPORT_PRV_POS_ALIGN_2BIT), mask_pm);
    r_ioport_regwrite_8(&p_p[u_port], value_p, u_pin, mask_p);
}

/*******************************************************************************************************************//**
 * Make pin and port number
 *
 * @param[in]    pin             Pin and port number
 * @param[out]   p_port_number   Port number
 * @param[out]   p_pin_number    Pin number
 *
 **********************************************************************************************************************/
static void r_ioport_make_port_pin_num (bsp_io_port_pin_t pin, uint8_t * p_port_number, uint8_t * p_pin_number)
{
    *p_port_number = (uint8_t) ((pin & IOPORT_PRV_PORT_BITS) >> IOPORT_PRV_PORT_OFFSET);
    *p_pin_number  = (uint8_t) (pin & IOPORT_PRV_PIN_BITS);
}

/**********************************************************************************************************************
 * IO register 8-bit write
 *
 * @param[in]   ioreg          IO register for writing
 *                             Use register definition name of the iodefine.h
 * @param[in]   write_value    Write value for the IO register
 * @param[in]   shift          The number of left shifts to the target bit
 * @param[in]   mask           Mask value for the IO register (Target bit : "1")
 *
 *********************************************************************************************************************/
static void r_ioport_regwrite_8 (volatile uint8_t * ioreg, uint8_t write_value, uint8_t shift, uint8_t mask)
{
    uint8_t reg_value;

    if ((uint8_t) IOPORT_PRV_NONMASK_ACCESS != mask)
    {
        /* Read from register */
        reg_value = *ioreg;

        /* Modify value */
        reg_value = (uint8_t) ((reg_value & (~mask)) | (write_value << shift));
    }
    else
    {
        reg_value = write_value;
    }

    /* Write to register */
    *ioreg = reg_value;
}

/**********************************************************************************************************************
 * IO register 16-bit write
 *
 * @param[in]   ioreg          IO register for writing
 *                             Use register definition name of the iodefine.h
 * @param[in]   write_value    Write value for the IO register
 * @param[in]   shift          The number of left shifts to the target bit
 * @param[in]   mask           Mask value for the IO register (Target bit : "1")
 *
 *********************************************************************************************************************/
static void r_ioport_regwrite_16 (volatile uint16_t * ioreg, uint16_t write_value, uint16_t shift, uint16_t mask)
{
    uint16_t reg_value;

    if ((uint16_t) IOPORT_PRV_NONMASK_ACCESS != mask)
    {
        /* Read from register */
        reg_value = *ioreg;

        /* Modify value */
        reg_value = (uint16_t) ((reg_value & (~mask)) | (write_value << shift));
    }
    else
    {
        reg_value = write_value;
    }

    /* Write to register */
    *ioreg = reg_value;
}

/**********************************************************************************************************************
 * IO register 32-bit write
 *
 * @param[in]   ioreg          IO register for writing
 *                             Use register definition name of the iodefine.h
 * @param[in]   write_value    Write value for the IO register
 * @param[in]   shift          The number of left shifts to the target bit
 * @param[in]   mask           Mask value for the IO register (Target bit : "1")
 *
 *********************************************************************************************************************/
static void r_ioport_regwrite_32 (volatile uint32_t * ioreg, uint32_t write_value, uint32_t shift, uint32_t mask)
{
    uint32_t reg_value;

    if (IOPORT_PRV_NONMASK_ACCESS != mask)
    {
        /* Read from register */
        reg_value = *ioreg;

        /* Modify value */
        reg_value = (uint32_t) ((reg_value & (~mask)) | (write_value << shift));
    }
    else
    {
        reg_value = write_value;
    }

    /* Write to register */
    *ioreg = reg_value;
}

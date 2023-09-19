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
 * @addtogroup SPIBSC
 * @{
 **********************************************************************************************************************/

#ifndef R_SPIBSC_H
#define R_SPIBSC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_spibsc_cfg.h"
#include "r_spi_flash_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Delay settings. */
typedef struct st_spibsc_delay
{
    uint8_t slch : 3;                  ///< SLCH (Select to Clock Delay) cycles
    uint8_t clsh : 3;                  ///< CLSH (Clock Low to Deselect Delay) cycles
    uint8_t shsl : 3;                  ///< SHSL (Deselect to Select Delay) cycles
} spibsc_delay_t;

/* Extended configuration. */
typedef struct st_spibsc_extended_cfg
{
    spibsc_delay_t delay;              ///< Delay setting
    uint8_t        io_fix_mask;        ///< Enable to fixture IOn signal level during idle state (bit mapped)
    uint8_t        io_fix_value;       ///< Value to fixture IOn signal level during idle state (bit mapped)
} spibsc_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_spibsc_instance_ctrl
{
    spi_flash_cfg_t             cfg;                  // Copy of configuration
    spibsc_extended_cfg_t       ext;                  // Copy of extended configuration
    spi_flash_erase_command_t * p_erase_command_list; // Copy of erase command list (dynamically allocated)
    uint32_t        open;                             // Whether or not driver is open
    bool            is_xip_enabled;                   // The driver enables XIP (omitting cmd) mode
    R_SPIBSC_Type * p_reg;                            // Controller register base address
} spibsc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_flash_api_t g_spi_flash_on_spibsc;

/** @endcond */

fsp_err_t R_SPIBSC_Open(spi_flash_ctrl_t * p_api_ctrl, spi_flash_cfg_t const * const p_cfg) BSP_PLACE_IN_SECTION(
    SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_Close(spi_flash_ctrl_t * p_api_ctrl) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_DirectWrite(spi_flash_ctrl_t    * p_api_ctrl,
                               uint8_t const * const p_src,
                               uint32_t const        bytes,
                               bool const            read_after_write) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_DirectRead(spi_flash_ctrl_t * p_api_ctrl, uint8_t * const p_dest,
                              uint32_t const bytes) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_SpiProtocolSet(spi_flash_ctrl_t   * p_api_ctrl,
                                  spi_flash_protocol_t spi_protocol) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_XipEnter(spi_flash_ctrl_t * p_api_ctrl) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_XipExit(spi_flash_ctrl_t * p_api_ctrl) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_Write(spi_flash_ctrl_t    * p_api_ctrl,
                         uint8_t const * const p_src,
                         uint8_t * const       p_dest,
                         uint32_t              byte_count) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_Erase(spi_flash_ctrl_t * p_api_ctrl, uint8_t * const p_device_address,
                         uint32_t byte_count) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_StatusGet(spi_flash_ctrl_t * p_api_ctrl, spi_flash_status_t * const p_status) BSP_PLACE_IN_SECTION(
    SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_BankSet(spi_flash_ctrl_t * p_api_ctrl, uint32_t bank) BSP_PLACE_IN_SECTION(SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_DirectTransfer(spi_flash_ctrl_t                  * p_api_ctrl,
                                  spi_flash_direct_transfer_t * const p_transfer,
                                  spi_flash_direct_transfer_dir_t     direction) BSP_PLACE_IN_SECTION(
    SPIBSC_CFG_CODE_SECTION);
fsp_err_t R_SPIBSC_AutoCalibrate(spi_flash_ctrl_t * p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup SPIBSC)
 **********************************************************************************************************************/

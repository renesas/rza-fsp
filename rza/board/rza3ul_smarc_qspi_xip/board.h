/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : board.h
 * Version      : 1.00
 * Description  : board header
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * @ingroup BOARDS
 * @defgroup BOARD_RZA3UL_SMARC_QSPI BSP for the RZA3UL-SMARC-QSPI board
 * @brief BSP for the RZA3UL-SMARC-QSPI Board
 *
 * The RZA3UL_SMARC is a evaluation kit for the Renesas R9A07G063U02GBG microcontroller in a LFBGA361 package.
 *
 * @{
 *********************************************************************************************************************/

#ifndef BOARD_H
#define BOARD_H

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/* BSP Board Specific Includes. */
#include "board_init.h"
#include "board_leds.h"
#include "board_ethernet_phy.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#define BOARD_RZA3UL_SMARC_QSPI_XIP
#define BSP_XIP_LOAD

#define BOARD_TYPE_RZA3UL_SMARC_QSPI

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 *********************************************************************************************************************/

/** @} (end defgroup BOARD_RZA3UL_SMARC_QSPI) */

#endif                                 /* BOARD_H */

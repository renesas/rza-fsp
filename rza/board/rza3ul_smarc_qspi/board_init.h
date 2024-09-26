/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : board_init.h
 * Version      : 1.00
 * Description  : board_init header
 *********************************************************************************************************************/

/******************************************************************************************************************//**
 * @addtogroup BOARD_RZA3UL_SMARC_QSPI
 * @brief Board specific code for the RZA3UL-SMARC-QSPI Board
 *
 * This include file is specific to the RZA3UL-SMARC-QSPI board.
 *
 * @{
 *********************************************************************************************************************/

#ifndef BOARD_INIT_H
#define BOARD_INIT_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 *********************************************************************************************************************/
void bsp_init(void * p_args);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* BOARD_INIT_H */

/** @} (end addtogroup BOARD_RZA3UL_SMARC_QSPI) */
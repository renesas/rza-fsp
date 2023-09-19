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

/**********************************************************************************************************************
 * File Name    : tsu_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for tsu.
 *********************************************************************************************************************/

#ifndef TSU_IOBITMASK_H
#define TSU_IOBITMASK_H

#define R_TSU_TSU_SM_EN_TS_Msk                      (0x00000001UL)
#define R_TSU_TSU_SM_EN_TS_Pos                      (0UL)
#define R_TSU_TSU_SM_ADC_EN_TS_Msk                  (0x00000002UL)
#define R_TSU_TSU_SM_ADC_EN_TS_Pos                  (1UL)
#define R_TSU_TSU_ST_START_Msk                      (0x00000001UL)
#define R_TSU_TSU_ST_START_Pos                      (0UL)
#define R_TSU_TSU_ST_RSV_Msk                        (0x00000002UL)
#define R_TSU_TSU_ST_RSV_Pos                        (1UL)
#define R_TSU_TSU_SAD_OUT_12BIT_TS_Msk              (0x00000FFFUL)
#define R_TSU_TSU_SAD_OUT_12BIT_TS_Pos              (0UL)
#define R_TSU_TSU_SS_CONV_Msk                       (0x00000001UL)
#define R_TSU_TSU_SS_CONV_Pos                       (0UL)
#define R_TSU_OTPTSUTRIM0_REG_OTPTSUTRIM0_Msk       (0x00000FFFUL)
#define R_TSU_OTPTSUTRIM0_REG_OTPTSUTRIM0_Pos       (0UL)
#define R_TSU_OTPTSUTRIM0_REG_OTPTSUTRIM0_EN_Msk    (0x80000000UL)
#define R_TSU_OTPTSUTRIM0_REG_OTPTSUTRIM0_EN_Pos    (31UL)
#define R_TSU_OTPTSUTRIM1_REG_OTPTSUTRIM1_Msk       (0x00000FFFUL)
#define R_TSU_OTPTSUTRIM1_REG_OTPTSUTRIM1_Pos       (0UL)
#define R_TSU_OTPTSUTRIM1_REG_OTPTSUTRIM1_EN_Msk    (0x80000000UL)
#define R_TSU_OTPTSUTRIM1_REG_OTPTSUTRIM1_EN_Pos    (31UL)

#endif

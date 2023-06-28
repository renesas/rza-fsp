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

/**********************************************************************************************************************
 * File Name    : tsu_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for tsu.
 *********************************************************************************************************************/

/* =========================================================================================================================== */
/* ================                              Device Specific Cluster Section                              ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */

#ifndef TSU_IODEFINE_H
#define TSU_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint32_t TSU_SM;
        struct
        {
            __IOM uint32_t EN_TS     : 1;
            __IOM uint32_t ADC_EN_TS : 1;
            uint32_t                 : 30;
        } TSU_SM_b;
    };
    union
    {
        __IOM uint32_t TSU_ST;
        struct
        {
            __IOM uint32_t START : 1;
            __IOM uint32_t RSV   : 1;
            uint32_t             : 30;
        } TSU_ST_b;
    };
    __IM uint8_t RESERVED[4];
    union
    {
        __IM uint32_t TSU_SAD;
        struct
        {
            __IM uint32_t OUT_12BIT_TS : 12;
            uint32_t                   : 20;
        } TSU_SAD_b;
    };
    union
    {
        __IM uint32_t TSU_SS;
        struct
        {
            __IM uint32_t CONV : 1;
            uint32_t           : 31;
        } TSU_SS_b;
    };
    __IM uint8_t RESERVED1[4];
    union
    {
        __IM uint32_t OTPTSUTRIM0_REG;
        struct
        {
            __IM uint32_t OTPTSUTRIM0    : 12;
            uint32_t                     : 19;
            __IM uint32_t OTPTSUTRIM0_EN : 1;
        } OTPTSUTRIM0_REG_b;
    };
    union
    {
        __IM uint32_t OTPTSUTRIM1_REG;
        struct
        {
            __IM uint32_t OTPTSUTRIM1    : 12;
            uint32_t                     : 19;
            __IM uint32_t OTPTSUTRIM1_EN : 1;
        } OTPTSUTRIM1_REG_b;
    };
} R_TSU_Type;

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

#define R_TSU_BASE    0x10059400

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

#define R_TSU    ((R_TSU_Type *) R_TSU_BASE)

#endif

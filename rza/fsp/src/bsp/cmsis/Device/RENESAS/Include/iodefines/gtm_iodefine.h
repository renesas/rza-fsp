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
 * File Name    : gtm_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for gtm.
 *********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                              Device Specific Cluster Section                              ====== */
/* ================================================================================================================= */

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

#ifndef GTM_IODEFINE_H
#define GTM_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint32_t OSTMnCMP;
        struct
        {
            __IOM uint32_t OSTMnCMP : 32;
        } OSTMnCMP_b;
    };

    union
    {
        __IM uint32_t OSTMnCNT;
        struct
        {
            __IM uint32_t OSTMnCNT : 32;
        } OSTMnCNT_b;
    };

    __IM uint8_t RESERVED[8];
    union
    {
        __IM uint8_t OSTMnTE;
        struct
        {
            __IM uint8_t OSTMnTE : 1;
            uint8_t              : 7;
        } OSTMnTE_b;
    };

    __IM uint8_t RESERVED1[3];
    union
    {
        __IOM uint8_t OSTMnTS;
        struct
        {
            __OM uint8_t OSTMnTS : 1;
            uint8_t              : 7;
        } OSTMnTS_b;
    };

    __IM uint8_t RESERVED2[3];
    union
    {
        __IOM uint8_t OSTMnTT;
        struct
        {
            __OM uint8_t OSTMnTT : 1;
            uint8_t              : 7;
        } OSTMnTT_b;
    };

    __IM uint8_t RESERVED3[7];
    union
    {
        __IOM uint8_t OSTMnCTL;
        struct
        {
            __IOM uint8_t OSTMnMD0 : 1;
            __IOM uint8_t OSTMnMD1 : 1;
            uint8_t                : 6;
        } OSTMnCTL_b;
    };
} R_GTM0_Type;

/* ================================================================================================================= */
/* ================                          Device Specific Peripheral Address Map                           ====== */
/* ================================================================================================================= */

#define R_GTM0_BASE    0x12801000
#define R_GTM1_BASE    0x12801400
#define R_GTM2_BASE    0x12801800

/* ================================================================================================================= */
/* ================                                  Peripheral declaration                                   ====== */
/* ================================================================================================================= */

#define R_GTM0    ((R_GTM0_Type *) R_GTM0_BASE)
#define R_GTM1    ((R_GTM0_Type *) R_GTM1_BASE)
#define R_GTM2    ((R_GTM0_Type *) R_GTM2_BASE)

#endif

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
 * File Name    : adc_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for adc.
 *********************************************************************************************************************/

/* =========================================================================================================================== */
/* ================                              Device Specific Cluster Section                              ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */

#ifndef ADC_IODEFINE_H
#define ADC_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint32_t ADM0;
        struct
        {
            __IOM uint32_t ADCE   : 1;
            __IM uint32_t  ADBSY  : 1;
            __IOM uint32_t PWDWNB : 1;
            uint32_t              : 12;
            __IOM uint32_t SRESB  : 1;
            uint32_t              : 16;
        } ADM0_b;
    };
    union
    {
        __IOM uint32_t ADM1;
        struct
        {
            __IOM uint32_t TRG   : 1;
            __IOM uint32_t TRGIN : 1;
            __IOM uint32_t MS    : 1;
            __IOM uint32_t RPS   : 1;
            __IOM uint32_t BS    : 1;
            uint32_t             : 7;
            __IOM uint32_t EGA   : 2;
            uint32_t             : 2;
            __IM uint32_t TRGEN  : 6;
            uint32_t             : 10;
        } ADM1_b;
    };
    union
    {
        __IOM uint32_t ADM2;
        struct
        {
            __IOM uint32_t CHSEL : 2;
            uint32_t             : 30;
        } ADM2_b;
    };
    union
    {
        __IOM uint32_t ADM3;
        struct
        {
            __IOM uint32_t ADSMP : 16;
            __IOM uint32_t ADCMP : 8;
            __IOM uint32_t ADIL  : 8;
        } ADM3_b;
    };
    __IM uint8_t RESERVED[16];
    union
    {
        __IOM uint32_t ADINT;
        struct
        {
            __IOM uint32_t INTEN : 4;
            uint32_t             : 12;
            __IOM uint32_t CSEEN : 1;
            uint32_t             : 14;
            __IM uint32_t INTS   : 1;
        } ADINT_b;
    };
    union
    {
        __IOM uint32_t ADSTS;
        struct
        {
            __IOM uint32_t INTST : 4;
            uint32_t             : 12;
            __IOM uint32_t CSEST : 1;
            uint32_t             : 14;
            __IOM uint32_t TRGS  : 1;
        } ADSTS_b;
    };
    union
    {
        __IOM uint32_t ADIVC;
        struct
        {
            __IOM uint32_t DIVADC : 9;
            uint32_t              : 23;
        } ADIVC_b;
    };
    union
    {
        __IOM uint32_t ADFIL;
        struct
        {
            __IOM uint32_t FILONOFF : 1;
            uint32_t                : 3;
            __IOM uint32_t FILNUM   : 2;
            uint32_t                : 26;
        } ADFIL_b;
    };
    union
    {
        __IM uint32_t ADCR0;
        struct
        {
            __IM uint32_t AD0  : 1;
            __IM uint32_t AD1  : 1;
            __IM uint32_t AD2  : 1;
            __IM uint32_t AD3  : 1;
            __IM uint32_t AD4  : 1;
            __IM uint32_t AD5  : 1;
            __IM uint32_t AD6  : 1;
            __IM uint32_t AD7  : 1;
            __IM uint32_t AD8  : 1;
            __IM uint32_t AD9  : 1;
            __IM uint32_t AD10 : 1;
            __IM uint32_t AD11 : 1;
            uint32_t           : 20;
        } ADCR0_b;
    };
    union
    {
        __IM uint32_t ADCR1;
        struct
        {
            __IM uint32_t AD0  : 1;
            __IM uint32_t AD1  : 1;
            __IM uint32_t AD2  : 1;
            __IM uint32_t AD3  : 1;
            __IM uint32_t AD4  : 1;
            __IM uint32_t AD5  : 1;
            __IM uint32_t AD6  : 1;
            __IM uint32_t AD7  : 1;
            __IM uint32_t AD8  : 1;
            __IM uint32_t AD9  : 1;
            __IM uint32_t AD10 : 1;
            __IM uint32_t AD11 : 1;
            uint32_t           : 20;
        } ADCR1_b;
    };
    union
    {
        __IM uint32_t ADCR2;
        struct
        {
            __IM uint32_t AD0  : 1;
            __IM uint32_t AD1  : 1;
            __IM uint32_t AD2  : 1;
            __IM uint32_t AD3  : 1;
            __IM uint32_t AD4  : 1;
            __IM uint32_t AD5  : 1;
            __IM uint32_t AD6  : 1;
            __IM uint32_t AD7  : 1;
            __IM uint32_t AD8  : 1;
            __IM uint32_t AD9  : 1;
            __IM uint32_t AD10 : 1;
            __IM uint32_t AD11 : 1;
            uint32_t           : 20;
        } ADCR2_b;
    };
    union
    {
        __IM uint32_t ADCR3;
        struct
        {
            __IM uint32_t AD0  : 1;
            __IM uint32_t AD1  : 1;
            __IM uint32_t AD2  : 1;
            __IM uint32_t AD3  : 1;
            __IM uint32_t AD4  : 1;
            __IM uint32_t AD5  : 1;
            __IM uint32_t AD6  : 1;
            __IM uint32_t AD7  : 1;
            __IM uint32_t AD8  : 1;
            __IM uint32_t AD9  : 1;
            __IM uint32_t AD10 : 1;
            __IM uint32_t AD11 : 1;
            uint32_t           : 20;
        } ADCR3_b;
    };
} R_ADC_Type;

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

#define R_ADC_BASE    0x10059000

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

#define R_ADC    ((R_ADC_Type *) R_ADC_BASE)

#endif

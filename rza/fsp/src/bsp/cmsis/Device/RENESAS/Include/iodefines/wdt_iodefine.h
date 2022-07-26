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
 * File Name    : wdt_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for wdt.
 *********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                              Device Specific Cluster Section                              ====== */
/* ================================================================================================================= */

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

#ifndef WDT_IODEFINE_H
#define WDT_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint32_t WDTCNT;
        struct
        {
            __IOM uint32_t WDTEN : 1;
            uint32_t             : 31;
        } WDTCNT_b;
    };

    union
    {
        __IOM uint32_t WDTSET;
        struct
        {
            uint32_t               : 20;
            __IOM uint32_t WDTTIME : 12;
        } WDTSET_b;
    };

    union
    {
        __IOM uint32_t WDTTIM;
        struct
        {
            __IOM uint32_t CRTTIME : 32;
        } WDTTIM_b;
    };

    union
    {
        __IOM uint32_t WDTINT;
        struct
        {
            __IOM uint32_t INTDISP : 1;
            uint32_t               : 31;
        } WDTINT_b;
    };

    union
    {
        __IOM uint32_t PECR;
        struct
        {
            __IOM uint32_t PECR : 32;
        } PECR_b;
    };

    union
    {
        __IOM uint32_t PEEN;
        struct
        {
            __IOM uint32_t PEEN : 1;
            uint32_t            : 31;
        } PEEN_b;
    };

    union
    {
        __IOM uint32_t PESR;
        struct
        {
            __IOM uint32_t PESR : 32;
        } PESR_b;
    };

    union
    {
        __IOM uint32_t PEER;
        struct
        {
            __IOM uint32_t PEER : 32;
        } PEER_b;
    };

    union
    {
        __IOM uint32_t PEPO;
        struct
        {
            __IOM uint32_t PEPO : 32;
        } PEPO_b;
    };
} R_WDT0_Type;

/* ================================================================================================================= */
/* ================                          Device Specific Peripheral Address Map                           ====== */
/* ================================================================================================================= */

#define R_WDT0_BASE    0x12800800
#define R_WDT1_BASE    0x12800C00
#define R_WDT2_BASE    0x12800400

/* ================================================================================================================= */
/* ================                                  Peripheral declaration                                   ====== */
/* ================================================================================================================= */

#define R_WDT0    ((R_WDT0_Type *) R_WDT0_BASE)
#define R_WDT1    ((R_WDT0_Type *) R_WDT1_BASE)
#define R_WDT2    ((R_WDT0_Type *) R_WDT2_BASE)

#endif                                 /* WDT_IODEFINE_H */

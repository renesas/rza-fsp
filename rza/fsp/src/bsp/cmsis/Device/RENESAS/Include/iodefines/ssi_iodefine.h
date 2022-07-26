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
 * File Name    : ssi_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for ssi.
 *********************************************************************************************************************/

/* =========================================================================================================================== */
/* ================                              Device Specific Cluster Section                              ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */

#ifndef SSI_IODEFINE_H
#define SSI_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint32_t SSICR;
        struct
        {
            __IOM uint32_t REN   : 1;
            __IOM uint32_t TEN   : 1;
            uint32_t             : 1;
            __IOM uint32_t MUEN  : 1;
            __IOM uint32_t CKDV  : 4;
            __IOM uint32_t DEL   : 1;
            __IOM uint32_t PDTA  : 1;
            __IOM uint32_t SDTA  : 1;
            __IOM uint32_t SPDP  : 1;
            __IOM uint32_t LRCKP : 1;
            __IOM uint32_t BCKP  : 1;
            __IOM uint32_t MST   : 1;
            uint32_t             : 1;
            __IOM uint32_t SWL   : 3;
            __IOM uint32_t DWL   : 3;
            __IOM uint32_t FRM   : 2;
            uint32_t             : 1;
            __IOM uint32_t IIEN  : 1;
            __IOM uint32_t ROIEN : 1;
            __IOM uint32_t RUIEN : 1;
            __IOM uint32_t TOIEN : 1;
            __IOM uint32_t TUIEN : 1;
            __IOM uint32_t CKS   : 1;
            uint32_t             : 1;
        } SSICR_b;
    };
    union
    {
        __IOM uint32_t SSISR;
        struct
        {
            uint32_t             : 25;
            __IOM uint32_t IIRQ  : 1;
            __IOM uint32_t ROIRQ : 1;
            __IOM uint32_t RUIRQ : 1;
            __IOM uint32_t TOIRQ : 1;
            __IOM uint32_t TUIRQ : 1;
            uint32_t             : 2;
        } SSISR_b;
    };
    __IM uint8_t RESERVED[8];
    union
    {
        __IOM uint32_t SSIFCR;
        struct
        {
            __IOM uint32_t RFRST   : 1;
            __IOM uint32_t TFRST   : 1;
            __IOM uint32_t RIE     : 1;
            __IOM uint32_t TIE     : 1;
            uint32_t               : 4;
            __IOM uint32_t RXDNCE  : 1;
            __IOM uint32_t LRCKNCE : 1;
            __IOM uint32_t BCKNCE  : 1;
            __IOM uint32_t BSW     : 1;
            uint32_t               : 4;
            __IOM uint32_t SSIRST  : 1;
            uint32_t               : 14;
            __IOM uint32_t AUCKE   : 1;
        } SSIFCR_b;
    };
    union
    {
        __IOM uint32_t SSIFSR;
        struct
        {
            __IOM uint32_t RDF : 1;
            uint32_t           : 7;
            __IM uint32_t RDC  : 6;
            uint32_t           : 2;
            __IOM uint32_t TDE : 1;
            uint32_t           : 7;
            __IM uint32_t TDC  : 6;
            uint32_t           : 2;
        } SSIFSR_b;
    };
    union
    {
        __OM uint32_t SSIFTDR;
        struct
        {
            __OM uint16_t L;
            __OM uint16_t H;
        } SSIFTDR_hword;
        struct
        {
            __OM uint8_t LL;
            __OM uint8_t LH;
            __OM uint8_t HL;
            __OM uint8_t HH;
        } SSIFTDR_byte;
        struct
        {
            __OM uint32_t SSIFTDR : 32;
        } SSIFTDR_b;
    };
    union
    {
        __IM uint32_t SSIFRDR;
        struct
        {
            __IM uint16_t L;
            __IM uint16_t H;
        } SSIFRDR_hword;
        struct
        {
            __IM uint8_t LL;
            __IM uint8_t LH;
            __IM uint8_t HL;
            __IM uint8_t HH;
        } SSIFRDR_byte;
        struct
        {
            __IM uint32_t SSIFRDR : 32;
        } SSIFRDR_b;
    };
    union
    {
        __IOM uint32_t SSIOFR;
        struct
        {
            __IOM uint32_t OMOD   : 2;
            uint32_t              : 6;
            __IOM uint32_t LRCONT : 1;
            __IOM uint32_t BCKSTP : 1;
            uint32_t              : 22;
        } SSIOFR_b;
    };
    union
    {
        __IOM uint32_t SSISCR;
        struct
        {
            __IOM uint32_t RDFS : 5;
            uint32_t            : 3;
            __IOM uint32_t TDES : 5;
            uint32_t            : 19;
        } SSISCR_b;
    };
} R_SSI0_Type;

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

#define R_SSI0_BASE    0x10049C00
#define R_SSI1_BASE    0x1004A000
#define R_SSI2_BASE    0x1004A400
#define R_SSI3_BASE    0x1004A800

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

#define R_SSI0    ((R_SSI0_Type *) R_SSI0_BASE)
#define R_SSI1    ((R_SSI0_Type *) R_SSI1_BASE)
#define R_SSI2    ((R_SSI0_Type *) R_SSI2_BASE)
#define R_SSI3    ((R_SSI0_Type *) R_SSI3_BASE)

#endif

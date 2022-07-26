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
 * File Name    : scifa_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for scifa.
 *********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                              Device Specific Cluster Section                              ====== */
/* ================================================================================================================= */

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

#ifndef SCIFA_IODEFINE_H
#define SCIFA_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint16_t SMR;
        struct
        {
            __IOM uint16_t CKS  : 2;
            uint16_t            : 1;
            __IOM uint16_t STOP : 1;
            __IOM uint16_t PM   : 1;
            __IOM uint16_t PE   : 1;
            __IOM uint16_t CHR  : 1;
            __IOM uint16_t CM   : 1;
            uint16_t            : 8;
        } SMR_b;
    };

    union
    {
        union
        {
            __IOM uint8_t MDDR;
            struct
            {
                __IOM uint8_t MDDR : 8;
            } MDDR_b;
        };

        union
        {
            __IOM uint8_t BRR;
            struct
            {
                __IOM uint8_t BRR : 8;
            } BRR_b;
        };
    };

    __IM uint8_t RESERVED[1];
    union
    {
        __IOM uint16_t SCR;
        struct
        {
            __IOM uint16_t CKE  : 2;
            __IOM uint16_t TEIE : 1;
            __IOM uint16_t REIE : 1;
            __IOM uint16_t RE   : 1;
            __IOM uint16_t TE   : 1;
            __IOM uint16_t RIE  : 1;
            __IOM uint16_t TIE  : 1;
            uint16_t            : 8;
        } SCR_b;
    };

    union
    {
        __OM uint8_t FTDR;
        struct
        {
            __OM uint8_t FTDR : 8;
        } FTDR_b;
    };

    __IM uint8_t RESERVED1[1];
    union
    {
        __IOM uint16_t FSR;
        struct
        {
            __IOM uint16_t DR   : 1;
            __IOM uint16_t RDF  : 1;
            __IM uint16_t  PER  : 1;
            __IM uint16_t  FER  : 1;
            __IOM uint16_t BRK  : 1;
            __IOM uint16_t TDFE : 1;
            __IOM uint16_t TEND : 1;
            __IOM uint16_t ER   : 1;
            uint16_t            : 8;
        } FSR_b;
    };

    union
    {
        __IM uint8_t FRDR;
        struct
        {
            __IM uint8_t FRDR : 8;
        } FRDR_b;
    };

    __IM uint8_t RESERVED2[1];
    union
    {
        __IOM uint16_t FCR;
        struct
        {
            __IOM uint16_t LOOP  : 1;
            __IOM uint16_t RFRST : 1;
            __IOM uint16_t TFRST : 1;
            __IOM uint16_t MCE   : 1;
            __IOM uint16_t TTRG  : 2;
            __IOM uint16_t RTRG  : 2;
            __IOM uint16_t RSTRG : 3;
            uint16_t             : 5;
        } FCR_b;
    };

    union
    {
        __IM uint16_t FDR;
        struct
        {
            __IM uint16_t R : 5;
            uint16_t        : 3;
            __IM uint16_t T : 5;
            uint16_t        : 3;
        } FDR_b;
    };

    union
    {
        __IOM uint16_t SPTR;
        struct
        {
            __IOM uint16_t SPB2DT : 1;
            __IOM uint16_t SPB2IO : 1;
            __IOM uint16_t SCKDT  : 1;
            __IOM uint16_t SCKIO  : 1;
            __IOM uint16_t CTS2DT : 1;
            __IOM uint16_t CTS2IO : 1;
            __IOM uint16_t RTS2DT : 1;
            __IOM uint16_t RTS2IO : 1;
            uint16_t              : 8;
        } SPTR_b;
    };

    union
    {
        __IOM uint16_t LSR;
        struct
        {
            __IOM uint16_t ORER : 1;
            uint16_t            : 1;
            __IM uint16_t FER   : 4;
            uint16_t            : 2;
            __IM uint16_t PER   : 4;
            uint16_t            : 4;
        } LSR_b;
    };

    union
    {
        __IOM uint8_t SEMR;
        struct
        {
            __IOM uint8_t ABCS0 : 1;
            uint8_t             : 1;
            __IOM uint8_t NFEN  : 1;
            __IOM uint8_t DIR   : 1;
            __IOM uint8_t MDDRS : 1;
            __IOM uint8_t BRME  : 1;
            uint8_t             : 1;
            __IOM uint8_t BGDM  : 1;
        } SEMR_b;
    };

    __IM uint8_t RESERVED3[1];
    union
    {
        __IOM uint16_t FTCR;
        struct
        {
            __IOM uint16_t TFTC  : 5;
            uint16_t             : 2;
            __IOM uint16_t TTRGS : 1;
            __IOM uint16_t RFTC  : 5;
            uint16_t             : 2;
            __IOM uint16_t RTRGS : 1;
        } FTCR_b;
    };
} R_SCIFA0_Type;

/* ================================================================================================================= */
/* ================                          Device Specific Peripheral Address Map                           ====== */
/* ================================================================================================================= */

#define R_SCIFA0_BASE    0x1004B800
#define R_SCIFA1_BASE    0x1004BC00
#define R_SCIFA2_BASE    0x1004C000
#define R_SCIFA3_BASE    0x1004C400
#define R_SCIFA4_BASE    0x1004C800

/* ================================================================================================================= */
/* ================                                  Peripheral declaration                                   ====== */
/* ================================================================================================================= */

#define R_SCIFA0    ((R_SCIFA0_Type *) R_SCIFA0_BASE)
#define R_SCIFA1    ((R_SCIFA0_Type *) R_SCIFA1_BASE)
#define R_SCIFA2    ((R_SCIFA0_Type *) R_SCIFA2_BASE)
#define R_SCIFA3    ((R_SCIFA0_Type *) R_SCIFA3_BASE)
#define R_SCIFA4    ((R_SCIFA0_Type *) R_SCIFA4_BASE)

#endif                                 /* SCIFA_IODEFINE_H */

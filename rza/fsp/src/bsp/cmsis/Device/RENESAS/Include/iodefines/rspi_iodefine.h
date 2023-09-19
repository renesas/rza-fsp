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
 * File Name    : rspi_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for rspi.
 *********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                              Device Specific Cluster Section                              ====== */
/* ================================================================================================================= */

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

#ifndef RSPI_IODEFINE_H
#define RSPI_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint8_t SPCR;
        struct
        {
            uint8_t              : 2;
            __IOM uint8_t MODFEN : 1;
            __IOM uint8_t MSTR   : 1;
            __IOM uint8_t SPEIE  : 1;
            __IOM uint8_t SPTIE  : 1;
            __IOM uint8_t SPE    : 1;
            __IOM uint8_t SPRIE  : 1;
        } SPCR_b;
    };

    union
    {
        __IOM uint8_t SSLP;
        struct
        {
            __IOM uint8_t SSL0P : 1;
            uint8_t             : 7;
        } SSLP_b;
    };

    union
    {
        __IOM uint8_t SPPCR;
        struct
        {
            __IOM uint8_t SPLP  : 1;
            uint8_t             : 3;
            __IOM uint8_t MOIFV : 1;
            __IOM uint8_t MOIFE : 1;
            uint8_t             : 2;
        } SPPCR_b;
    };

    union
    {
        __IOM uint8_t SPSR;
        struct
        {
            __IOM uint8_t OVRF : 1;
            uint8_t            : 1;
            __IOM uint8_t MODF : 1;
            uint8_t            : 2;
            __IM uint8_t SPTEF : 1;
            __IM uint8_t TEND  : 1;
            __IM uint8_t SPRF  : 1;
        } SPSR_b;
    };

    union
    {
        __IOM uint32_t SPDR;
        struct
        {
            __IOM uint16_t L;
            __IOM uint16_t H;
        } SPDR_hword;
        struct
        {
            __IOM uint8_t LL;
            __IOM uint8_t LH;
            __IOM uint8_t HL;
            __IOM uint8_t HH;
        } SPDR_byte;
        struct
        {
            __IOM uint32_t SPD : 32;
        } SPDR_b;
    };

    union
    {
        __IOM uint8_t SPSCR;
        struct
        {
            __IOM uint8_t SPSLN : 2;
            uint8_t             : 6;
        } SPSCR_b;
    };

    union
    {
        __IM uint8_t SPSSR;
        struct
        {
            __IM uint8_t SPCP : 2;
            uint8_t           : 6;
        } SPSSR_b;
    };

    union
    {
        __IOM uint8_t SPBR;
        struct
        {
            __IOM uint8_t SPR : 8;
        } SPBR_b;
    };

    union
    {
        __IOM uint8_t SPDCR;
        struct
        {
            uint8_t             : 5;
            __IOM uint8_t SPLW  : 2;
            __IOM uint8_t TXDMY : 1;
        } SPDCR_b;
    };

    union
    {
        __IOM uint8_t SPCKD;
        struct
        {
            __IOM uint8_t SCKDL : 3;
            uint8_t             : 5;
        } SPCKD_b;
    };

    union
    {
        __IOM uint8_t SSLND;
        struct
        {
            __IOM uint8_t SLNDL : 3;
            uint8_t             : 5;
        } SSLND_b;
    };

    union
    {
        __IOM uint8_t SPND;
        struct
        {
            __IOM uint8_t SPNDL : 3;
            uint8_t             : 5;
        } SPND_b;
    };

    __IM uint8_t RESERVED[1];
    union
    {
        __IOM uint16_t SPCMD0;
        struct
        {
            __IOM uint16_t CPHA   : 1;
            __IOM uint16_t CPOL   : 1;
            __IOM uint16_t BRDV   : 2;
            uint16_t              : 3;
            __IOM uint16_t SSLKP  : 1;
            __IOM uint16_t SPB    : 4;
            __IOM uint16_t LSBF   : 1;
            __IOM uint16_t SPNDEN : 1;
            __IOM uint16_t SLNDEN : 1;
            __IOM uint16_t SCKDEN : 1;
        } SPCMD0_b;
    };

    union
    {
        __IOM uint16_t SPCMD1;
        struct
        {
            __IOM uint16_t CPHA   : 1;
            __IOM uint16_t CPOL   : 1;
            __IOM uint16_t BRDV   : 2;
            uint16_t              : 3;
            __IOM uint16_t SSLKP  : 1;
            __IOM uint16_t SPB    : 4;
            __IOM uint16_t LSBF   : 1;
            __IOM uint16_t SPNDEN : 1;
            __IOM uint16_t SLNDEN : 1;
            __IOM uint16_t SCKDEN : 1;
        } SPCMD1_b;
    };

    union
    {
        __IOM uint16_t SPCMD2;
        struct
        {
            __IOM uint16_t CPHA   : 1;
            __IOM uint16_t CPOL   : 1;
            __IOM uint16_t BRDV   : 2;
            uint16_t              : 3;
            __IOM uint16_t SSLKP  : 1;
            __IOM uint16_t SPB    : 4;
            __IOM uint16_t LSBF   : 1;
            __IOM uint16_t SPNDEN : 1;
            __IOM uint16_t SLNDEN : 1;
            __IOM uint16_t SCKDEN : 1;
        } SPCMD2_b;
    };

    union
    {
        __IOM uint16_t SPCMD3;
        struct
        {
            __IOM uint16_t CPHA   : 1;
            __IOM uint16_t CPOL   : 1;
            __IOM uint16_t BRDV   : 2;
            uint16_t              : 3;
            __IOM uint16_t SSLKP  : 1;
            __IOM uint16_t SPB    : 4;
            __IOM uint16_t LSBF   : 1;
            __IOM uint16_t SPNDEN : 1;
            __IOM uint16_t SLNDEN : 1;
            __IOM uint16_t SCKDEN : 1;
        } SPCMD3_b;
    };

    __IM uint8_t RESERVED1[8];
    union
    {
        __IOM uint8_t SPBFCR;
        struct
        {
            __IOM uint8_t RXTRG : 3;
            uint8_t             : 1;
            __IOM uint8_t TXTRG : 2;
            __IOM uint8_t RXRST : 1;
            __IOM uint8_t TXRST : 1;
        } SPBFCR_b;
    };

    __IM uint8_t RESERVED2[1];
    union
    {
        __IM uint16_t SPBFDR;
        struct
        {
            __IM uint16_t R : 6;
            uint16_t        : 2;
            __IM uint16_t T : 4;
            uint16_t        : 4;
        } SPBFDR_b;
    };
} R_RSPI0_Type;

/* ================================================================================================================= */
/* ================                          Device Specific Peripheral Address Map                           ====== */
/* ================================================================================================================= */

#define R_RSPI0_BASE    0x1004AC00
#define R_RSPI1_BASE    0x1004B000
#define R_RSPI2_BASE    0x1004B400

/* ================================================================================================================= */
/* ================                                  Peripheral declaration                                   ====== */
/* ================================================================================================================= */

#define R_RSPI0    ((R_RSPI0_Type *) R_RSPI0_BASE)
#define R_RSPI1    ((R_RSPI0_Type *) R_RSPI1_BASE)
#define R_RSPI2    ((R_RSPI0_Type *) R_RSPI2_BASE)

#endif                                 /* RSPI_IODEFINE_H */

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
 * File Name    : scig_iodefine.h
 * Version      : 1.00
 * Description  : IO define file for scig.
 *********************************************************************************************************************/

/* =========================================================================================================================== */
/* ================                              Device Specific Cluster Section                              ================ */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */

#ifndef SCIG_IODEFINE_H
#define SCIG_IODEFINE_H

typedef struct
{
    union
    {
        __IOM uint8_t SMR;
        struct
        {
            __IOM uint8_t CKS  : 2;
            __IOM uint8_t MP   : 1;
            __IOM uint8_t STOP : 1;
            __IOM uint8_t PM   : 1;
            __IOM uint8_t PE   : 1;
            __IOM uint8_t CHR  : 1;
            __IOM uint8_t CM   : 1;
        } SMR_b;
    };

    union
    {
        __IOM uint8_t BRR;
        struct
        {
            __IOM uint8_t BRR : 8;
        } BRR_b;
    };

    union
    {
        __IOM uint8_t SCR;
        struct
        {
            __IOM uint8_t CKE  : 2;
            __IOM uint8_t TEIE : 1;
            __IOM uint8_t MPIE : 1;
            __IOM uint8_t RE   : 1;
            __IOM uint8_t TE   : 1;
            __IOM uint8_t RIE  : 1;
            __IOM uint8_t TIE  : 1;
        } SCR_b;
    };

    union
    {
        __IOM uint8_t TDR;
        struct
        {
            __IOM uint8_t TDR : 8;
        } TDR_b;
    };

    union
    {
        __IOM uint8_t SSR;
        struct
        {
            __IOM uint8_t MPBT : 1;
            __IM uint8_t  MPB  : 1;
            __IM uint8_t  TEND : 1;
            __IOM uint8_t PER  : 1;
            __IOM uint8_t FER  : 1;
            __IOM uint8_t ORER : 1;
            __IOM uint8_t RDRF : 1;
            __IOM uint8_t TDRE : 1;
        } SSR_b;
    };

    union
    {
        __IM uint8_t RDR;
        struct
        {
            __IM uint8_t RDR : 8;
        } RDR_b;
    };

    union
    {
        __IOM uint8_t SCMR;
        struct
        {
            __IOM uint8_t SMIF : 1;
            uint8_t            : 1;
            __IOM uint8_t SINV : 1;
            __IOM uint8_t SDIR : 1;
            __IOM uint8_t CHR1 : 1;
            uint8_t            : 2;
            uint8_t            : 1;
        } SCMR_b;
    };

    union
    {
        __IOM uint8_t SEMR;
        struct
        {
            __IOM uint8_t ACS0    : 1;
            uint8_t               : 1;
            __IOM uint8_t BRME    : 1;
            uint8_t               : 1;
            __IOM uint8_t ABCS    : 1;
            __IOM uint8_t NFEN    : 1;
            __IOM uint8_t BGDM    : 1;
            __IOM uint8_t RXDESEL : 1;
        } SEMR_b;
    };

    union
    {
        __IOM uint8_t SNFR;
        struct
        {
            __IOM uint8_t NFCS : 3;
            uint8_t            : 5;
        } SNFR_b;
    };

    __IM uint8_t RESERVED[4];
    union
    {
        __IOM uint8_t SECR;
        struct
        {
            uint8_t            : 1;
            __IOM uint8_t CTSE : 1;
            uint8_t            : 6;
        } SECR_b;
    };

    union
    {
        struct
        {
            union
            {
                __IOM uint16_t TDRHL;
                struct
                {
                    __IOM uint16_t TDRHL : 16;
                } TDRHL_b;
            };
        };

        struct
        {
            union
            {
                __IOM uint8_t TDRH;
                struct
                {
                    __IOM uint8_t TDRH : 8;
                } TDRH_b;
            };

            union
            {
                __IOM uint8_t TDRL;
                struct
                {
                    __IOM uint8_t TDRL : 8;
                } TDRL_b;
            };
        };
    };

    union
    {
        struct
        {
            union
            {
                __IM uint16_t RDRHL;
                struct
                {
                    __IM uint16_t RDRHL : 16;
                } RDRHL_b;
            };
        };

        struct
        {
            union
            {
                __IM uint8_t RDRH;
                struct
                {
                    __IM uint8_t RDRH : 8;
                } RDRH_b;
            };

            union
            {
                __IM uint8_t RDRL;
                struct
                {
                    __IM uint8_t RDRL : 8;
                } RDRL_b;
            };
        };
    };

    union
    {
        __IOM uint8_t MDDR;
        struct
        {
            __IOM uint8_t MDDR : 8;
        } MDDR_b;
    };
} R_SCI0_Type;

/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

#define R_SCI0_BASE    0x1004D000
#define R_SCI1_BASE    0x1004D400

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

#define R_SCI0    ((R_SCI0_Type *) R_SCI0_BASE)
#define R_SCI1    ((R_SCI0_Type *) R_SCI1_BASE)

#endif

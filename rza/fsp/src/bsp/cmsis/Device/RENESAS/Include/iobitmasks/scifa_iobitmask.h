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
 * File Name    : scifa_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for scifa.
 *********************************************************************************************************************/

#ifndef SCIFA_IOBITMASK_H
#define SCIFA_IOBITMASK_H

#define R_SCIFA0_SMR_CKS_Msk        (0x0003UL)
#define R_SCIFA0_SMR_CKS_Pos        (0UL)
#define R_SCIFA0_SMR_STOP_Msk       (0x0008UL)
#define R_SCIFA0_SMR_STOP_Pos       (3UL)
#define R_SCIFA0_SMR_PM_Msk         (0x0010UL)
#define R_SCIFA0_SMR_PM_Pos         (4UL)
#define R_SCIFA0_SMR_PE_Msk         (0x0020UL)
#define R_SCIFA0_SMR_PE_Pos         (5UL)
#define R_SCIFA0_SMR_CHR_Msk        (0x0040UL)
#define R_SCIFA0_SMR_CHR_Pos        (6UL)
#define R_SCIFA0_SMR_CM_Msk         (0x0080UL)
#define R_SCIFA0_SMR_CM_Pos         (7UL)
#define R_SCIFA0_MDDR_MDDR_Msk      (0xFFUL)
#define R_SCIFA0_MDDR_MDDR_Pos      (0UL)
#define R_SCIFA0_BRR_BRR_Msk        (0xFFUL)
#define R_SCIFA0_BRR_BRR_Pos        (0UL)
#define R_SCIFA0_SCR_CKE_Msk        (0x0003UL)
#define R_SCIFA0_SCR_CKE_Pos        (0UL)
#define R_SCIFA0_SCR_TEIE_Msk       (0x0004UL)
#define R_SCIFA0_SCR_TEIE_Pos       (2UL)
#define R_SCIFA0_SCR_REIE_Msk       (0x0008UL)
#define R_SCIFA0_SCR_REIE_Pos       (3UL)
#define R_SCIFA0_SCR_RE_Msk         (0x0010UL)
#define R_SCIFA0_SCR_RE_Pos         (4UL)
#define R_SCIFA0_SCR_TE_Msk         (0x0020UL)
#define R_SCIFA0_SCR_TE_Pos         (5UL)
#define R_SCIFA0_SCR_RIE_Msk        (0x0040UL)
#define R_SCIFA0_SCR_RIE_Pos        (6UL)
#define R_SCIFA0_SCR_TIE_Msk        (0x0080UL)
#define R_SCIFA0_SCR_TIE_Pos        (7UL)
#define R_SCIFA0_FTDR_FTDR_Msk      (0xFFUL)
#define R_SCIFA0_FTDR_FTDR_Pos      (0UL)
#define R_SCIFA0_FSR_DR_Msk         (0x0001UL)
#define R_SCIFA0_FSR_DR_Pos         (0UL)
#define R_SCIFA0_FSR_RDF_Msk        (0x0002UL)
#define R_SCIFA0_FSR_RDF_Pos        (1UL)
#define R_SCIFA0_FSR_PER_Msk        (0x0004UL)
#define R_SCIFA0_FSR_PER_Pos        (2UL)
#define R_SCIFA0_FSR_FER_Msk        (0x0008UL)
#define R_SCIFA0_FSR_FER_Pos        (3UL)
#define R_SCIFA0_FSR_BRK_Msk        (0x0010UL)
#define R_SCIFA0_FSR_BRK_Pos        (4UL)
#define R_SCIFA0_FSR_TDFE_Msk       (0x0020UL)
#define R_SCIFA0_FSR_TDFE_Pos       (5UL)
#define R_SCIFA0_FSR_TEND_Msk       (0x0040UL)
#define R_SCIFA0_FSR_TEND_Pos       (6UL)
#define R_SCIFA0_FSR_ER_Msk         (0x0080UL)
#define R_SCIFA0_FSR_ER_Pos         (7UL)
#define R_SCIFA0_FRDR_FRDR_Msk      (0xFFUL)
#define R_SCIFA0_FRDR_FRDR_Pos      (0UL)
#define R_SCIFA0_FCR_LOOP_Msk       (0x0001UL)
#define R_SCIFA0_FCR_LOOP_Pos       (0UL)
#define R_SCIFA0_FCR_RFRST_Msk      (0x0002UL)
#define R_SCIFA0_FCR_RFRST_Pos      (1UL)
#define R_SCIFA0_FCR_TFRST_Msk      (0x0004UL)
#define R_SCIFA0_FCR_TFRST_Pos      (2UL)
#define R_SCIFA0_FCR_MCE_Msk        (0x0008UL)
#define R_SCIFA0_FCR_MCE_Pos        (3UL)
#define R_SCIFA0_FCR_TTRG_Msk       (0x0030UL)
#define R_SCIFA0_FCR_TTRG_Pos       (4UL)
#define R_SCIFA0_FCR_RTRG_Msk       (0x00C0UL)
#define R_SCIFA0_FCR_RTRG_Pos       (6UL)
#define R_SCIFA0_FCR_RSTRG_Msk      (0x0700UL)
#define R_SCIFA0_FCR_RSTRG_Pos      (8UL)
#define R_SCIFA0_FDR_R_Msk          (0x001FUL)
#define R_SCIFA0_FDR_R_Pos          (0UL)
#define R_SCIFA0_FDR_T_Msk          (0x1F00UL)
#define R_SCIFA0_FDR_T_Pos          (8UL)
#define R_SCIFA0_SPTR_SPB2DT_Msk    (0x0001UL)
#define R_SCIFA0_SPTR_SPB2DT_Pos    (0UL)
#define R_SCIFA0_SPTR_SPB2IO_Msk    (0x0002UL)
#define R_SCIFA0_SPTR_SPB2IO_Pos    (1UL)
#define R_SCIFA0_SPTR_SCKDT_Msk     (0x0004UL)
#define R_SCIFA0_SPTR_SCKDT_Pos     (2UL)
#define R_SCIFA0_SPTR_SCKIO_Msk     (0x0008UL)
#define R_SCIFA0_SPTR_SCKIO_Pos     (3UL)
#define R_SCIFA0_SPTR_CTS2DT_Msk    (0x0010UL)
#define R_SCIFA0_SPTR_CTS2DT_Pos    (4UL)
#define R_SCIFA0_SPTR_CTS2IO_Msk    (0x0020UL)
#define R_SCIFA0_SPTR_CTS2IO_Pos    (5UL)
#define R_SCIFA0_SPTR_RTS2DT_Msk    (0x0040UL)
#define R_SCIFA0_SPTR_RTS2DT_Pos    (6UL)
#define R_SCIFA0_SPTR_RTS2IO_Msk    (0x0080UL)
#define R_SCIFA0_SPTR_RTS2IO_Pos    (7UL)
#define R_SCIFA0_LSR_ORER_Msk       (0x0001UL)
#define R_SCIFA0_LSR_ORER_Pos       (0UL)
#define R_SCIFA0_LSR_FER_Msk        (0x003CUL)
#define R_SCIFA0_LSR_FER_Pos        (2UL)
#define R_SCIFA0_LSR_PER_Msk        (0x0F00UL)
#define R_SCIFA0_LSR_PER_Pos        (8UL)
#define R_SCIFA0_SEMR_ABCS0_Msk     (0x01UL)
#define R_SCIFA0_SEMR_ABCS0_Pos     (0UL)
#define R_SCIFA0_SEMR_NFEN_Msk      (0x04UL)
#define R_SCIFA0_SEMR_NFEN_Pos      (2UL)
#define R_SCIFA0_SEMR_DIR_Msk       (0x08UL)
#define R_SCIFA0_SEMR_DIR_Pos       (3UL)
#define R_SCIFA0_SEMR_MDDRS_Msk     (0x10UL)
#define R_SCIFA0_SEMR_MDDRS_Pos     (4UL)
#define R_SCIFA0_SEMR_BRME_Msk      (0x20UL)
#define R_SCIFA0_SEMR_BRME_Pos      (5UL)
#define R_SCIFA0_SEMR_BGDM_Msk      (0x80UL)
#define R_SCIFA0_SEMR_BGDM_Pos      (7UL)
#define R_SCIFA0_FTCR_TFTC_Msk      (0x001FUL)
#define R_SCIFA0_FTCR_TFTC_Pos      (0UL)
#define R_SCIFA0_FTCR_TTRGS_Msk     (0x0080UL)
#define R_SCIFA0_FTCR_TTRGS_Pos     (7UL)
#define R_SCIFA0_FTCR_RFTC_Msk      (0x1F00UL)
#define R_SCIFA0_FTCR_RFTC_Pos      (8UL)
#define R_SCIFA0_FTCR_RTRGS_Msk     (0x8000UL)
#define R_SCIFA0_FTCR_RTRGS_Pos     (15UL)

#endif                                 /* SCIFA_IOBITMASK_H */

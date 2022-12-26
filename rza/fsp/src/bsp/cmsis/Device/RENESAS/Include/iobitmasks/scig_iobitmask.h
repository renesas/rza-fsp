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
 * File Name    : scig_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for scig.
 *********************************************************************************************************************/

#ifndef SCIG_IOBITMASK_H
#define SCIG_IOBITMASK_H

#define R_SCIG_SMR_CKS_Msk         (0x03UL)
#define R_SCIG_SMR_CKS_Pos         (0UL)
#define R_SCIG_SMR_MP_Msk          (0x04UL)
#define R_SCIG_SMR_MP_Pos          (2UL)
#define R_SCIG_SMR_STOP_Msk        (0x08UL)
#define R_SCIG_SMR_STOP_Pos        (3UL)
#define R_SCIG_SMR_PM_Msk          (0x10UL)
#define R_SCIG_SMR_PM_Pos          (4UL)
#define R_SCIG_SMR_PE_Msk          (0x20UL)
#define R_SCIG_SMR_PE_Pos          (5UL)
#define R_SCIG_SMR_CHR_Msk         (0x40UL)
#define R_SCIG_SMR_CHR_Pos         (6UL)
#define R_SCIG_SMR_CM_Msk          (0x80UL)
#define R_SCIG_SMR_CM_Pos          (7UL)
#define R_SCIG_BRR_BRR_Msk         (0xFFUL)
#define R_SCIG_BRR_BRR_Pos         (0UL)
#define R_SCIG_SCR_CKE_Msk         (0x03UL)
#define R_SCIG_SCR_CKE_Pos         (0UL)
#define R_SCIG_SCR_TEIE_Msk        (0x04UL)
#define R_SCIG_SCR_TEIE_Pos        (2UL)
#define R_SCIG_SCR_MPIE_Msk        (0x08UL)
#define R_SCIG_SCR_MPIE_Pos        (3UL)
#define R_SCIG_SCR_RE_Msk          (0x10UL)
#define R_SCIG_SCR_RE_Pos          (4UL)
#define R_SCIG_SCR_TE_Msk          (0x20UL)
#define R_SCIG_SCR_TE_Pos          (5UL)
#define R_SCIG_SCR_RIE_Msk         (0x40UL)
#define R_SCIG_SCR_RIE_Pos         (6UL)
#define R_SCIG_SCR_TIE_Msk         (0x80UL)
#define R_SCIG_SCR_TIE_Pos         (7UL)
#define R_SCIG_TDR_TDR_Msk         (0xFFUL)
#define R_SCIG_TDR_TDR_Pos         (0UL)
#define R_SCIG_SSR_MPBT_Msk        (0x01UL)
#define R_SCIG_SSR_MPBT_Pos        (0UL)
#define R_SCIG_SSR_MPB_Msk         (0x02UL)
#define R_SCIG_SSR_MPB_Pos         (1UL)
#define R_SCIG_SSR_TEND_Msk        (0x04UL)
#define R_SCIG_SSR_TEND_Pos        (2UL)
#define R_SCIG_SSR_PER_Msk         (0x08UL)
#define R_SCIG_SSR_PER_Pos         (3UL)
#define R_SCIG_SSR_FER_Msk         (0x10UL)
#define R_SCIG_SSR_FER_Pos         (4UL)
#define R_SCIG_SSR_ORER_Msk        (0x20UL)
#define R_SCIG_SSR_ORER_Pos        (5UL)
#define R_SCIG_SSR_RDRF_Msk        (0x40UL)
#define R_SCIG_SSR_RDRF_Pos        (6UL)
#define R_SCIG_SSR_TDRE_Msk        (0x80UL)
#define R_SCIG_SSR_TDRE_Pos        (7UL)
#define R_SCIG_RDR_RDR_Msk         (0xFFUL)
#define R_SCIG_RDR_RDR_Pos         (0UL)
#define R_SCIG_SCMR_SMIF_Msk       (0x01UL)
#define R_SCIG_SCMR_SMIF_Pos       (0UL)
#define R_SCIG_SCMR_SINV_Msk       (0x04UL)
#define R_SCIG_SCMR_SINV_Pos       (2UL)
#define R_SCIG_SCMR_SDIR_Msk       (0x08UL)
#define R_SCIG_SCMR_SDIR_Pos       (3UL)
#define R_SCIG_SCMR_CHR1_Msk       (0x10UL)
#define R_SCIG_SCMR_CHR1_Pos       (4UL)
#define R_SCIG_SEMR_ACS0_Msk       (0x01UL)
#define R_SCIG_SEMR_ACS0_Pos       (0UL)
#define R_SCIG_SEMR_BRME_Msk       (0x04UL)
#define R_SCIG_SEMR_BRME_Pos       (2UL)
#define R_SCIG_SEMR_ABCS_Msk       (0x10UL)
#define R_SCIG_SEMR_ABCS_Pos       (4UL)
#define R_SCIG_SEMR_NFEN_Msk       (0x20UL)
#define R_SCIG_SEMR_NFEN_Pos       (5UL)
#define R_SCIG_SEMR_BGDM_Msk       (0x40UL)
#define R_SCIG_SEMR_BGDM_Pos       (6UL)
#define R_SCIG_SEMR_RXDESEL_Msk    (0x80UL)
#define R_SCIG_SEMR_RXDESEL_Pos    (7UL)
#define R_SCIG_SNFR_NFCS_Msk       (0x07UL)
#define R_SCIG_SNFR_NFCS_Pos       (0UL)
#define R_SCIG_SECR_CTSE_Msk       (0x02UL)
#define R_SCIG_SECR_CTSE_Pos       (1UL)
#define R_SCIG_TDRHL_TDRHL_Msk     (0xFFFFUL)
#define R_SCIG_TDRHL_TDRHL_Pos     (0UL)
#define R_SCIG_TDRH_TDRH_Msk       (0xFFUL)
#define R_SCIG_TDRH_TDRH_Pos       (0UL)
#define R_SCIG_TDRL_TDRL_Msk       (0xFFUL)
#define R_SCIG_TDRL_TDRL_Pos       (0UL)
#define R_SCIG_RDRHL_RDRHL_Msk     (0xFFFFUL)
#define R_SCIG_RDRHL_RDRHL_Pos     (0UL)
#define R_SCIG_RDRH_RDRH_Msk       (0xFFUL)
#define R_SCIG_RDRH_RDRH_Pos       (0UL)
#define R_SCIG_RDRL_RDRL_Msk       (0xFFUL)
#define R_SCIG_RDRL_RDRL_Pos       (0UL)
#define R_SCIG_MDDR_MDDR_Msk       (0xFFUL)
#define R_SCIG_MDDR_MDDR_Pos       (0UL)

#endif

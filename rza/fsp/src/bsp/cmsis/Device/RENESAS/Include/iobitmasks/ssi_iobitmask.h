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
 * File Name    : ssi_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for ssi.
 *********************************************************************************************************************/

#ifndef SSI_IOBITMASK_H
#define SSI_IOBITMASK_H

#define R_SSI_SSICR_REN_Msk          (0x00000001UL)
#define R_SSI_SSICR_REN_Pos          (0UL)
#define R_SSI_SSICR_TEN_Msk          (0x00000002UL)
#define R_SSI_SSICR_TEN_Pos          (1UL)
#define R_SSI_SSICR_MUEN_Msk         (0x00000008UL)
#define R_SSI_SSICR_MUEN_Pos         (3UL)
#define R_SSI_SSICR_CKDV_Msk         (0x000000F0UL)
#define R_SSI_SSICR_CKDV_Pos         (4UL)
#define R_SSI_SSICR_DEL_Msk          (0x00000100UL)
#define R_SSI_SSICR_DEL_Pos          (8UL)
#define R_SSI_SSICR_PDTA_Msk         (0x00000200UL)
#define R_SSI_SSICR_PDTA_Pos         (9UL)
#define R_SSI_SSICR_SDTA_Msk         (0x00000400UL)
#define R_SSI_SSICR_SDTA_Pos         (10UL)
#define R_SSI_SSICR_SPDP_Msk         (0x00000800UL)
#define R_SSI_SSICR_SPDP_Pos         (11UL)
#define R_SSI_SSICR_LRCKP_Msk        (0x00001000UL)
#define R_SSI_SSICR_LRCKP_Pos        (12UL)
#define R_SSI_SSICR_BCKP_Msk         (0x00002000UL)
#define R_SSI_SSICR_BCKP_Pos         (13UL)
#define R_SSI_SSICR_MST_Msk          (0x00004000UL)
#define R_SSI_SSICR_MST_Pos          (14UL)
#define R_SSI_SSICR_SWL_Msk          (0x00070000UL)
#define R_SSI_SSICR_SWL_Pos          (16UL)
#define R_SSI_SSICR_DWL_Msk          (0x00380000UL)
#define R_SSI_SSICR_DWL_Pos          (19UL)
#define R_SSI_SSICR_FRM_Msk          (0x00C00000UL)
#define R_SSI_SSICR_FRM_Pos          (22UL)
#define R_SSI_SSICR_IIEN_Msk         (0x02000000UL)
#define R_SSI_SSICR_IIEN_Pos         (25UL)
#define R_SSI_SSICR_ROIEN_Msk        (0x04000000UL)
#define R_SSI_SSICR_ROIEN_Pos        (26UL)
#define R_SSI_SSICR_RUIEN_Msk        (0x08000000UL)
#define R_SSI_SSICR_RUIEN_Pos        (27UL)
#define R_SSI_SSICR_TOIEN_Msk        (0x10000000UL)
#define R_SSI_SSICR_TOIEN_Pos        (28UL)
#define R_SSI_SSICR_TUIEN_Msk        (0x20000000UL)
#define R_SSI_SSICR_TUIEN_Pos        (29UL)
#define R_SSI_SSICR_CKS_Msk          (0x40000000UL)
#define R_SSI_SSICR_CKS_Pos          (30UL)
#define R_SSI_SSISR_IIRQ_Msk         (0x02000000UL)
#define R_SSI_SSISR_IIRQ_Pos         (25UL)
#define R_SSI_SSISR_ROIRQ_Msk        (0x04000000UL)
#define R_SSI_SSISR_ROIRQ_Pos        (26UL)
#define R_SSI_SSISR_RUIRQ_Msk        (0x08000000UL)
#define R_SSI_SSISR_RUIRQ_Pos        (27UL)
#define R_SSI_SSISR_TOIRQ_Msk        (0x10000000UL)
#define R_SSI_SSISR_TOIRQ_Pos        (28UL)
#define R_SSI_SSISR_TUIRQ_Msk        (0x20000000UL)
#define R_SSI_SSISR_TUIRQ_Pos        (29UL)
#define R_SSI_SSIFCR_RFRST_Msk       (0x00000001UL)
#define R_SSI_SSIFCR_RFRST_Pos       (0UL)
#define R_SSI_SSIFCR_TFRST_Msk       (0x00000002UL)
#define R_SSI_SSIFCR_TFRST_Pos       (1UL)
#define R_SSI_SSIFCR_RIE_Msk         (0x00000004UL)
#define R_SSI_SSIFCR_RIE_Pos         (2UL)
#define R_SSI_SSIFCR_TIE_Msk         (0x00000008UL)
#define R_SSI_SSIFCR_TIE_Pos         (3UL)
#define R_SSI_SSIFCR_RXDNCE_Msk      (0x00000100UL)
#define R_SSI_SSIFCR_RXDNCE_Pos      (8UL)
#define R_SSI_SSIFCR_LRCKNCE_Msk     (0x00000200UL)
#define R_SSI_SSIFCR_LRCKNCE_Pos     (9UL)
#define R_SSI_SSIFCR_BCKNCE_Msk      (0x00000400UL)
#define R_SSI_SSIFCR_BCKNCE_Pos      (10UL)
#define R_SSI_SSIFCR_BSW_Msk         (0x00000800UL)
#define R_SSI_SSIFCR_BSW_Pos         (11UL)
#define R_SSI_SSIFCR_SSIRST_Msk      (0x00010000UL)
#define R_SSI_SSIFCR_SSIRST_Pos      (16UL)
#define R_SSI_SSIFCR_AUCKE_Msk       (0x80000000UL)
#define R_SSI_SSIFCR_AUCKE_Pos       (31UL)
#define R_SSI_SSIFSR_RDF_Msk         (0x00000001UL)
#define R_SSI_SSIFSR_RDF_Pos         (0UL)
#define R_SSI_SSIFSR_RDC_Msk         (0x00003F00UL)
#define R_SSI_SSIFSR_RDC_Pos         (8UL)
#define R_SSI_SSIFSR_TDE_Msk         (0x00010000UL)
#define R_SSI_SSIFSR_TDE_Pos         (16UL)
#define R_SSI_SSIFSR_TDC_Msk         (0x3F000000UL)
#define R_SSI_SSIFSR_TDC_Pos         (24UL)
#define R_SSI_SSIFTDR_SSIFTDR_Msk    (0xFFFFFFFFUL)
#define R_SSI_SSIFTDR_SSIFTDR_Pos    (0UL)
#define R_SSI_SSIFRDR_SSIFRDR_Msk    (0xFFFFFFFFUL)
#define R_SSI_SSIFRDR_SSIFRDR_Pos    (0UL)
#define R_SSI_SSIOFR_OMOD_Msk        (0x00000003UL)
#define R_SSI_SSIOFR_OMOD_Pos        (0UL)
#define R_SSI_SSIOFR_LRCONT_Msk      (0x00000100UL)
#define R_SSI_SSIOFR_LRCONT_Pos      (8UL)
#define R_SSI_SSIOFR_BCKSTP_Msk      (0x00000200UL)
#define R_SSI_SSIOFR_BCKSTP_Pos      (9UL)
#define R_SSI_SSISCR_RDFS_Msk        (0x0000001FUL)
#define R_SSI_SSISCR_RDFS_Pos        (0UL)
#define R_SSI_SSISCR_TDES_Msk        (0x00001F00UL)
#define R_SSI_SSISCR_TDES_Pos        (8UL)

#endif

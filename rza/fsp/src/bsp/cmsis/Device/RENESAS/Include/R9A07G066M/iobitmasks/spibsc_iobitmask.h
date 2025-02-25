/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : spibsc_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for spibsc.
 *********************************************************************************************************************/

#ifndef SPIBSC_IOBITMASK_H
#define SPIBSC_IOBITMASK_H

#define R_SPIBSC_CMNCR_BSZ_Msk            (0x00000003UL)
#define R_SPIBSC_CMNCR_BSZ_Pos            (0UL)
#define R_SPIBSC_CMNCR_IO0FV_Msk          (0x00000300UL)
#define R_SPIBSC_CMNCR_IO0FV_Pos          (8UL)
#define R_SPIBSC_CMNCR_IO2FV_Msk          (0x00003000UL)
#define R_SPIBSC_CMNCR_IO2FV_Pos          (12UL)
#define R_SPIBSC_CMNCR_IO3FV_Msk          (0x0000C000UL)
#define R_SPIBSC_CMNCR_IO3FV_Pos          (14UL)
#define R_SPIBSC_CMNCR_MOIIO0_Msk         (0x00030000UL)
#define R_SPIBSC_CMNCR_MOIIO0_Pos         (16UL)
#define R_SPIBSC_CMNCR_MOIIO1_Msk         (0x000C0000UL)
#define R_SPIBSC_CMNCR_MOIIO1_Pos         (18UL)
#define R_SPIBSC_CMNCR_MOIIO2_Msk         (0x00300000UL)
#define R_SPIBSC_CMNCR_MOIIO2_Pos         (20UL)
#define R_SPIBSC_CMNCR_MOIIO3_Msk         (0x00C00000UL)
#define R_SPIBSC_CMNCR_MOIIO3_Pos         (22UL)
#define R_SPIBSC_CMNCR_MD_Msk             (0x80000000UL)
#define R_SPIBSC_CMNCR_MD_Pos             (31UL)
#define R_SPIBSC_SSLDR_SCKDL_Msk          (0x00000007UL)
#define R_SPIBSC_SSLDR_SCKDL_Pos          (0UL)
#define R_SPIBSC_SSLDR_SLNDL_Msk          (0x00000700UL)
#define R_SPIBSC_SSLDR_SLNDL_Pos          (8UL)
#define R_SPIBSC_SSLDR_SPNDL_Msk          (0x00070000UL)
#define R_SPIBSC_SSLDR_SPNDL_Pos          (16UL)
#define R_SPIBSC_DRCR_SSLE_Msk            (0x00000001UL)
#define R_SPIBSC_DRCR_SSLE_Pos            (0UL)
#define R_SPIBSC_DRCR_RBE_Msk             (0x00000100UL)
#define R_SPIBSC_DRCR_RBE_Pos             (8UL)
#define R_SPIBSC_DRCR_RCF_Msk             (0x00000200UL)
#define R_SPIBSC_DRCR_RCF_Pos             (9UL)
#define R_SPIBSC_DRCR_RBURST_Msk          (0x001F0000UL)
#define R_SPIBSC_DRCR_RBURST_Pos          (16UL)
#define R_SPIBSC_DRCR_SSLN_Msk            (0x01000000UL)
#define R_SPIBSC_DRCR_SSLN_Pos            (24UL)
#define R_SPIBSC_DRCMR_OCMD_Msk           (0x000000FFUL)
#define R_SPIBSC_DRCMR_OCMD_Pos           (0UL)
#define R_SPIBSC_DRCMR_CMD_Msk            (0x00FF0000UL)
#define R_SPIBSC_DRCMR_CMD_Pos            (16UL)
#define R_SPIBSC_DREAR_EAC_Msk            (0x00000007UL)
#define R_SPIBSC_DREAR_EAC_Pos            (0UL)
#define R_SPIBSC_DREAR_EAV_Msk            (0x00FF0000UL)
#define R_SPIBSC_DREAR_EAV_Pos            (16UL)
#define R_SPIBSC_DROPR_OPD0_Msk           (0x000000FFUL)
#define R_SPIBSC_DROPR_OPD0_Pos           (0UL)
#define R_SPIBSC_DROPR_OPD1_Msk           (0x0000FF00UL)
#define R_SPIBSC_DROPR_OPD1_Pos           (8UL)
#define R_SPIBSC_DROPR_OPD2_Msk           (0x00FF0000UL)
#define R_SPIBSC_DROPR_OPD2_Pos           (16UL)
#define R_SPIBSC_DROPR_OPD3_Msk           (0xFF000000UL)
#define R_SPIBSC_DROPR_OPD3_Pos           (24UL)
#define R_SPIBSC_DRENR_OPDE_Msk           (0x000000F0UL)
#define R_SPIBSC_DRENR_OPDE_Pos           (4UL)
#define R_SPIBSC_DRENR_ADE_Msk            (0x00000F00UL)
#define R_SPIBSC_DRENR_ADE_Pos            (8UL)
#define R_SPIBSC_DRENR_OCDE_Msk           (0x00001000UL)
#define R_SPIBSC_DRENR_OCDE_Pos           (12UL)
#define R_SPIBSC_DRENR_CDE_Msk            (0x00004000UL)
#define R_SPIBSC_DRENR_CDE_Pos            (14UL)
#define R_SPIBSC_DRENR_DME_Msk            (0x00008000UL)
#define R_SPIBSC_DRENR_DME_Pos            (15UL)
#define R_SPIBSC_DRENR_DRDB_Msk           (0x00030000UL)
#define R_SPIBSC_DRENR_DRDB_Pos           (16UL)
#define R_SPIBSC_DRENR_OPDB_Msk           (0x00300000UL)
#define R_SPIBSC_DRENR_OPDB_Pos           (20UL)
#define R_SPIBSC_DRENR_ADB_Msk            (0x03000000UL)
#define R_SPIBSC_DRENR_ADB_Pos            (24UL)
#define R_SPIBSC_DRENR_OCDB_Msk           (0x30000000UL)
#define R_SPIBSC_DRENR_OCDB_Pos           (28UL)
#define R_SPIBSC_DRENR_CDB_Msk            (0xC0000000UL)
#define R_SPIBSC_DRENR_CDB_Pos            (30UL)
#define R_SPIBSC_SMCR_SPIE_Msk            (0x00000001UL)
#define R_SPIBSC_SMCR_SPIE_Pos            (0UL)
#define R_SPIBSC_SMCR_SPIWE_Msk           (0x00000002UL)
#define R_SPIBSC_SMCR_SPIWE_Pos           (1UL)
#define R_SPIBSC_SMCR_SPIRE_Msk           (0x00000004UL)
#define R_SPIBSC_SMCR_SPIRE_Pos           (2UL)
#define R_SPIBSC_SMCR_SSLKP_Msk           (0x00000100UL)
#define R_SPIBSC_SMCR_SSLKP_Pos           (8UL)
#define R_SPIBSC_SMCMR_OCMD_Msk           (0x000000FFUL)
#define R_SPIBSC_SMCMR_OCMD_Pos           (0UL)
#define R_SPIBSC_SMCMR_CMD_Msk            (0x00FF0000UL)
#define R_SPIBSC_SMCMR_CMD_Pos            (16UL)
#define R_SPIBSC_SMADR_ADR_Msk            (0xFFFFFFFFUL)
#define R_SPIBSC_SMADR_ADR_Pos            (0UL)
#define R_SPIBSC_SMOPR_OPD0_Msk           (0x000000FFUL)
#define R_SPIBSC_SMOPR_OPD0_Pos           (0UL)
#define R_SPIBSC_SMOPR_OPD1_Msk           (0x0000FF00UL)
#define R_SPIBSC_SMOPR_OPD1_Pos           (8UL)
#define R_SPIBSC_SMOPR_OPD2_Msk           (0x00FF0000UL)
#define R_SPIBSC_SMOPR_OPD2_Pos           (16UL)
#define R_SPIBSC_SMOPR_OPD3_Msk           (0xFF000000UL)
#define R_SPIBSC_SMOPR_OPD3_Pos           (24UL)
#define R_SPIBSC_SMENR_SPIDE_Msk          (0x0000000FUL)
#define R_SPIBSC_SMENR_SPIDE_Pos          (0UL)
#define R_SPIBSC_SMENR_OPDE_Msk           (0x000000F0UL)
#define R_SPIBSC_SMENR_OPDE_Pos           (4UL)
#define R_SPIBSC_SMENR_ADE_Msk            (0x00000F00UL)
#define R_SPIBSC_SMENR_ADE_Pos            (8UL)
#define R_SPIBSC_SMENR_OCDE_Msk           (0x00001000UL)
#define R_SPIBSC_SMENR_OCDE_Pos           (12UL)
#define R_SPIBSC_SMENR_CDE_Msk            (0x00004000UL)
#define R_SPIBSC_SMENR_CDE_Pos            (14UL)
#define R_SPIBSC_SMENR_DME_Msk            (0x00008000UL)
#define R_SPIBSC_SMENR_DME_Pos            (15UL)
#define R_SPIBSC_SMENR_SPIDB_Msk          (0x00030000UL)
#define R_SPIBSC_SMENR_SPIDB_Pos          (16UL)
#define R_SPIBSC_SMENR_OPDB_Msk           (0x00300000UL)
#define R_SPIBSC_SMENR_OPDB_Pos           (20UL)
#define R_SPIBSC_SMENR_ADB_Msk            (0x03000000UL)
#define R_SPIBSC_SMENR_ADB_Pos            (24UL)
#define R_SPIBSC_SMENR_OCDB_Msk           (0x30000000UL)
#define R_SPIBSC_SMENR_OCDB_Pos           (28UL)
#define R_SPIBSC_SMENR_CDB_Msk            (0xC0000000UL)
#define R_SPIBSC_SMENR_CDB_Pos            (30UL)
#define R_SPIBSC_SMRDR0_RDATA0_Msk        (0xFFFFFFFFUL)
#define R_SPIBSC_SMRDR0_RDATA0_Pos        (0UL)
#define R_SPIBSC_SMWDR0_WDATA0_Msk        (0xFFFFFFFFUL)
#define R_SPIBSC_SMWDR0_WDATA0_Pos        (0UL)
#define R_SPIBSC_CMNSR_TEND_Msk           (0x00000001UL)
#define R_SPIBSC_CMNSR_TEND_Pos           (0UL)
#define R_SPIBSC_CMNSR_SSLF_Msk           (0x00000002UL)
#define R_SPIBSC_CMNSR_SSLF_Pos           (1UL)
#define R_SPIBSC_DRDMCR_DMCYC_Msk         (0x0000001FUL)
#define R_SPIBSC_DRDMCR_DMCYC_Pos         (0UL)
#define R_SPIBSC_DRDRENR_DRDRE_Msk        (0x00000001UL)
#define R_SPIBSC_DRDRENR_DRDRE_Pos        (0UL)
#define R_SPIBSC_DRDRENR_OPDRE_Msk        (0x00000010UL)
#define R_SPIBSC_DRDRENR_OPDRE_Pos        (4UL)
#define R_SPIBSC_DRDRENR_ADDRE_Msk        (0x00000100UL)
#define R_SPIBSC_DRDRENR_ADDRE_Pos        (8UL)
#define R_SPIBSC_DRDRENR_HYPE_Msk         (0x00007000UL)
#define R_SPIBSC_DRDRENR_HYPE_Pos         (12UL)
#define R_SPIBSC_SMDMCR_DMCYC_Msk         (0x0000001FUL)
#define R_SPIBSC_SMDMCR_DMCYC_Pos         (0UL)
#define R_SPIBSC_SMDRENR_SPIDRE_Msk       (0x00000001UL)
#define R_SPIBSC_SMDRENR_SPIDRE_Pos       (0UL)
#define R_SPIBSC_SMDRENR_OPDRE_Msk        (0x00000010UL)
#define R_SPIBSC_SMDRENR_OPDRE_Pos        (4UL)
#define R_SPIBSC_SMDRENR_ADDRE_Msk        (0x00000100UL)
#define R_SPIBSC_SMDRENR_ADDRE_Pos        (8UL)
#define R_SPIBSC_PHYADJ1_ADJ1_Msk         (0xFFFFFFFFUL)
#define R_SPIBSC_PHYADJ1_ADJ1_Pos         (0UL)
#define R_SPIBSC_PHYADJ2_ADJ2_Msk         (0xFFFFFFFFUL)
#define R_SPIBSC_PHYADJ2_ADJ2_Pos         (0UL)
#define R_SPIBSC_PHYCNT_PHYMEM_Msk        (0x00000003UL)
#define R_SPIBSC_PHYCNT_PHYMEM_Pos        (0UL)
#define R_SPIBSC_PHYCNT_WBUF_Msk          (0x00000004UL)
#define R_SPIBSC_PHYCNT_WBUF_Pos          (2UL)
#define R_SPIBSC_PHYCNT_WBUF2_Msk         (0x00000010UL)
#define R_SPIBSC_PHYCNT_WBUF2_Pos         (4UL)
#define R_SPIBSC_PHYCNT_CKSEL_Msk         (0x00030000UL)
#define R_SPIBSC_PHYCNT_CKSEL_Pos         (16UL)
#define R_SPIBSC_PHYCNT_HS_Msk            (0x00040000UL)
#define R_SPIBSC_PHYCNT_HS_Pos            (18UL)
#define R_SPIBSC_PHYCNT_CAL_Msk           (0x80000000UL)
#define R_SPIBSC_PHYCNT_CAL_Pos           (31UL)
#define R_SPIBSC_PHYOFFSET1_DDRTMG_Msk    (0x30000000UL)
#define R_SPIBSC_PHYOFFSET1_DDRTMG_Pos    (28UL)
#define R_SPIBSC_PHYOFFSET2_OCTTMG_Msk    (0x00000700UL)
#define R_SPIBSC_PHYOFFSET2_OCTTMG_Pos    (8UL)

#endif

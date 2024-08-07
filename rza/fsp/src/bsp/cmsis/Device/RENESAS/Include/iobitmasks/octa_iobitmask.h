/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : octa_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for octa.
 *********************************************************************************************************************/

#ifndef OCTA_IOBITMASK_H
#define OCTA_IOBITMASK_H

#define R_OCTA_DCR_DVCMD0_Msk         (0x000000FFUL)
#define R_OCTA_DCR_DVCMD0_Pos         (0UL)
#define R_OCTA_DCR_DVCMD1_Msk         (0x0000FF00UL)
#define R_OCTA_DCR_DVCMD1_Pos         (8UL)
#define R_OCTA_DAR_DVAD0_Msk          (0x000000FFUL)
#define R_OCTA_DAR_DVAD0_Pos          (0UL)
#define R_OCTA_DAR_DVAD1_Msk          (0x0000FF00UL)
#define R_OCTA_DAR_DVAD1_Pos          (8UL)
#define R_OCTA_DAR_DVAD2_Msk          (0x00FF0000UL)
#define R_OCTA_DAR_DVAD2_Pos          (16UL)
#define R_OCTA_DAR_DVAD3_Msk          (0xFF000000UL)
#define R_OCTA_DAR_DVAD3_Pos          (24UL)
#define R_OCTA_DCSR_DALEN_Msk         (0x000000FFUL)
#define R_OCTA_DCSR_DALEN_Pos         (0UL)
#define R_OCTA_DCSR_DMLEN_Msk         (0x0000FF00UL)
#define R_OCTA_DCSR_DMLEN_Pos         (8UL)
#define R_OCTA_DCSR_ACDV_Msk          (0x00080000UL)
#define R_OCTA_DCSR_ACDV_Pos          (19UL)
#define R_OCTA_DCSR_CMDLEN_Msk        (0x00700000UL)
#define R_OCTA_DCSR_CMDLEN_Pos        (20UL)
#define R_OCTA_DCSR_DAOR_Msk          (0x00800000UL)
#define R_OCTA_DCSR_DAOR_Pos          (23UL)
#define R_OCTA_DCSR_ADLEN_Msk         (0x07000000UL)
#define R_OCTA_DCSR_ADLEN_Pos         (24UL)
#define R_OCTA_DCSR_DOPI_Msk          (0x08000000UL)
#define R_OCTA_DCSR_DOPI_Pos          (27UL)
#define R_OCTA_DCSR_ACDA_Msk          (0x10000000UL)
#define R_OCTA_DCSR_ACDA_Pos          (28UL)
#define R_OCTA_DSR0_DV0SZ_Msk         (0x3FFFFFFFUL)
#define R_OCTA_DSR0_DV0SZ_Pos         (0UL)
#define R_OCTA_DSR0_DV0TYP_Msk        (0xC0000000UL)
#define R_OCTA_DSR0_DV0TYP_Pos        (30UL)
#define R_OCTA_DSR1_DV1SZ_Msk         (0x3FFFFFFFUL)
#define R_OCTA_DSR1_DV1SZ_Pos         (0UL)
#define R_OCTA_DSR1_DV1TYP_Msk        (0xC0000000UL)
#define R_OCTA_DSR1_DV1TYP_Pos        (30UL)
#define R_OCTA_MDTR_DV0DEL_Msk        (0x000000FFUL)
#define R_OCTA_MDTR_DV0DEL_Pos        (0UL)
#define R_OCTA_MDTR_DQSERAM_Msk       (0x00000F00UL)
#define R_OCTA_MDTR_DQSERAM_Pos       (8UL)
#define R_OCTA_MDTR_DQSESOPI_Msk      (0x0000F000UL)
#define R_OCTA_MDTR_DQSESOPI_Pos      (12UL)
#define R_OCTA_MDTR_DV1DEL_Msk        (0x00FF0000UL)
#define R_OCTA_MDTR_DV1DEL_Pos        (16UL)
#define R_OCTA_MDTR_DQSEDOPI_Msk      (0x0F000000UL)
#define R_OCTA_MDTR_DQSEDOPI_Pos      (24UL)
#define R_OCTA_ACTR_CTP_Msk           (0xFFFFFFFFUL)
#define R_OCTA_ACTR_CTP_Pos           (0UL)
#define R_OCTA_ACAR0_CAD0_Msk         (0xFFFFFFFFUL)
#define R_OCTA_ACAR0_CAD0_Pos         (0UL)
#define R_OCTA_ACAR1_CAD1_Msk         (0xFFFFFFFFUL)
#define R_OCTA_ACAR1_CAD1_Pos         (0UL)
#define R_OCTA_DRCSTR_CTRW0_Msk       (0x0000007FUL)
#define R_OCTA_DRCSTR_CTRW0_Pos       (0UL)
#define R_OCTA_DRCSTR_CTR0_Msk        (0x00000080UL)
#define R_OCTA_DRCSTR_CTR0_Pos        (7UL)
#define R_OCTA_DRCSTR_DVRDCMD0_Msk    (0x00000700UL)
#define R_OCTA_DRCSTR_DVRDCMD0_Pos    (8UL)
#define R_OCTA_DRCSTR_DVRDHI0_Msk     (0x00003800UL)
#define R_OCTA_DRCSTR_DVRDHI0_Pos     (11UL)
#define R_OCTA_DRCSTR_DVRDLO0_Msk     (0x0000C000UL)
#define R_OCTA_DRCSTR_DVRDLO0_Pos     (14UL)
#define R_OCTA_DRCSTR_DVRDCMD1_Msk    (0x07000000UL)
#define R_OCTA_DRCSTR_DVRDCMD1_Pos    (24UL)
#define R_OCTA_DRCSTR_DVRDHI1_Msk     (0x38000000UL)
#define R_OCTA_DRCSTR_DVRDHI1_Pos     (27UL)
#define R_OCTA_DRCSTR_DVRDLO1_Msk     (0xC0000000UL)
#define R_OCTA_DRCSTR_DVRDLO1_Pos     (30UL)
#define R_OCTA_DWCSTR_DVWCMD0_Msk     (0x00000700UL)
#define R_OCTA_DWCSTR_DVWCMD0_Pos     (8UL)
#define R_OCTA_DWCSTR_DVWHI0_Msk      (0x00003800UL)
#define R_OCTA_DWCSTR_DVWHI0_Pos      (11UL)
#define R_OCTA_DWCSTR_DVWLO0_Msk      (0x0000C000UL)
#define R_OCTA_DWCSTR_DVWLO0_Pos      (14UL)
#define R_OCTA_DWCSTR_DVWCMD1_Msk     (0x07000000UL)
#define R_OCTA_DWCSTR_DVWCMD1_Pos     (24UL)
#define R_OCTA_DWCSTR_DVWHI1_Msk      (0x38000000UL)
#define R_OCTA_DWCSTR_DVWHI1_Pos      (27UL)
#define R_OCTA_DWCSTR_DVWLO1_Msk      (0xC0000000UL)
#define R_OCTA_DWCSTR_DVWLO1_Pos      (30UL)
#define R_OCTA_DCSTR_DVSELCMD_Msk     (0x00000700UL)
#define R_OCTA_DCSTR_DVSELCMD_Pos     (8UL)
#define R_OCTA_DCSTR_DVSELHI_Msk      (0x00003800UL)
#define R_OCTA_DCSTR_DVSELHI_Pos      (11UL)
#define R_OCTA_DCSTR_DVSELLO_Msk      (0x0000C000UL)
#define R_OCTA_DCSTR_DVSELLO_Pos      (14UL)
#define R_OCTA_CDSR_DV0TTYP_Msk       (0x00000003UL)
#define R_OCTA_CDSR_DV0TTYP_Pos       (0UL)
#define R_OCTA_CDSR_DV1TTYP_Msk       (0x0000000CUL)
#define R_OCTA_CDSR_DV1TTYP_Pos       (2UL)
#define R_OCTA_CDSR_DV0PC_Msk         (0x00000010UL)
#define R_OCTA_CDSR_DV0PC_Pos         (4UL)
#define R_OCTA_CDSR_DV1PC_Msk         (0x00000020UL)
#define R_OCTA_CDSR_DV1PC_Pos         (5UL)
#define R_OCTA_CDSR_ACMEME_Msk        (0x00000C00UL)
#define R_OCTA_CDSR_ACMEME_Pos        (10UL)
#define R_OCTA_CDSR_ACMODE_Msk        (0x00003000UL)
#define R_OCTA_CDSR_ACMODE_Pos        (12UL)
#define R_OCTA_CDSR_DLFT_Msk          (0x80000000UL)
#define R_OCTA_CDSR_DLFT_Pos          (31UL)
#define R_OCTA_MDLR_DV0RDL_Msk        (0x000000FFUL)
#define R_OCTA_MDLR_DV0RDL_Pos        (0UL)
#define R_OCTA_MDLR_DV0WDL_Msk        (0x0000FF00UL)
#define R_OCTA_MDLR_DV0WDL_Pos        (8UL)
#define R_OCTA_MDLR_DV1RDL_Msk        (0x00FF0000UL)
#define R_OCTA_MDLR_DV1RDL_Pos        (16UL)
#define R_OCTA_MDLR_DV1WDL_Msk        (0xFF000000UL)
#define R_OCTA_MDLR_DV1WDL_Pos        (24UL)
#define R_OCTA_MRWCR0_D0MRCMD0_Msk    (0x000000FFUL)
#define R_OCTA_MRWCR0_D0MRCMD0_Pos    (0UL)
#define R_OCTA_MRWCR0_D0MRCMD1_Msk    (0x0000FF00UL)
#define R_OCTA_MRWCR0_D0MRCMD1_Pos    (8UL)
#define R_OCTA_MRWCR0_D0MWCMD0_Msk    (0x00FF0000UL)
#define R_OCTA_MRWCR0_D0MWCMD0_Pos    (16UL)
#define R_OCTA_MRWCR0_D0MWCMD1_Msk    (0xFF000000UL)
#define R_OCTA_MRWCR0_D0MWCMD1_Pos    (24UL)
#define R_OCTA_MRWCR1_D1MRCMD0_Msk    (0x000000FFUL)
#define R_OCTA_MRWCR1_D1MRCMD0_Pos    (0UL)
#define R_OCTA_MRWCR1_D1MRCMD1_Msk    (0x0000FF00UL)
#define R_OCTA_MRWCR1_D1MRCMD1_Pos    (8UL)
#define R_OCTA_MRWCR1_D1MWCMD0_Msk    (0x00FF0000UL)
#define R_OCTA_MRWCR1_D1MWCMD0_Pos    (16UL)
#define R_OCTA_MRWCR1_D1MWCMD1_Msk    (0xFF000000UL)
#define R_OCTA_MRWCR1_D1MWCMD1_Pos    (24UL)
#define R_OCTA_MRWCSR_MRAL0_Msk       (0x00000007UL)
#define R_OCTA_MRWCSR_MRAL0_Pos       (0UL)
#define R_OCTA_MRWCSR_MRCL0_Msk       (0x00000038UL)
#define R_OCTA_MRWCSR_MRCL0_Pos       (3UL)
#define R_OCTA_MRWCSR_MRO0_Msk        (0x00000040UL)
#define R_OCTA_MRWCSR_MRO0_Pos        (6UL)
#define R_OCTA_MRWCSR_MWAL0_Msk       (0x00000700UL)
#define R_OCTA_MRWCSR_MWAL0_Pos       (8UL)
#define R_OCTA_MRWCSR_MWCL0_Msk       (0x00003800UL)
#define R_OCTA_MRWCSR_MWCL0_Pos       (11UL)
#define R_OCTA_MRWCSR_MWO0_Msk        (0x00004000UL)
#define R_OCTA_MRWCSR_MWO0_Pos        (14UL)
#define R_OCTA_MRWCSR_MRAL1_Msk       (0x00070000UL)
#define R_OCTA_MRWCSR_MRAL1_Pos       (16UL)
#define R_OCTA_MRWCSR_MRCL1_Msk       (0x00380000UL)
#define R_OCTA_MRWCSR_MRCL1_Pos       (19UL)
#define R_OCTA_MRWCSR_MRO1_Msk        (0x00400000UL)
#define R_OCTA_MRWCSR_MRO1_Pos        (22UL)
#define R_OCTA_MRWCSR_MWAL1_Msk       (0x07000000UL)
#define R_OCTA_MRWCSR_MWAL1_Pos       (24UL)
#define R_OCTA_MRWCSR_MWCL1_Msk       (0x38000000UL)
#define R_OCTA_MRWCSR_MWCL1_Pos       (27UL)
#define R_OCTA_MRWCSR_MWO1_Msk        (0x40000000UL)
#define R_OCTA_MRWCSR_MWO1_Pos        (30UL)
#define R_OCTA_ESR_MRESR_Msk          (0x000000FFUL)
#define R_OCTA_ESR_MRESR_Pos          (0UL)
#define R_OCTA_ESR_MWESR_Msk          (0x0000FF00UL)
#define R_OCTA_ESR_MWESR_Pos          (8UL)
#define R_OCTA_CWDR_WD0_Msk           (0x000000FFUL)
#define R_OCTA_CWDR_WD0_Pos           (0UL)
#define R_OCTA_CWDR_WD1_Msk           (0x0000FF00UL)
#define R_OCTA_CWDR_WD1_Pos           (8UL)
#define R_OCTA_CWDR_WD2_Msk           (0x00FF0000UL)
#define R_OCTA_CWDR_WD2_Pos           (16UL)
#define R_OCTA_CWDR_WD3_Msk           (0xFF000000UL)
#define R_OCTA_CWDR_WD3_Pos           (24UL)
#define R_OCTA_CRR_RD0_Msk            (0x000000FFUL)
#define R_OCTA_CRR_RD0_Pos            (0UL)
#define R_OCTA_CRR_RD1_Msk            (0x0000FF00UL)
#define R_OCTA_CRR_RD1_Pos            (8UL)
#define R_OCTA_CRR_RD2_Msk            (0x00FF0000UL)
#define R_OCTA_CRR_RD2_Pos            (16UL)
#define R_OCTA_CRR_RD3_Msk            (0xFF000000UL)
#define R_OCTA_CRR_RD3_Pos            (24UL)
#define R_OCTA_RSTCNT_RSTVAL_Msk      (0x00000001UL)
#define R_OCTA_RSTCNT_RSTVAL_Pos      (0UL)
#define R_OCTA_AER_AAS_Msk            (0x00000007UL)
#define R_OCTA_AER_AAS_Pos            (0UL)

#endif

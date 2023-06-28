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
 * File Name    : isu_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for isu.
 *********************************************************************************************************************/

#ifndef ISU_IOBITMASK_H
#define ISU_IOBITMASK_H

#define R_ISU_ISU_FM_DL_STADDH_DLADD_Msk           (0x00000003UL)
#define R_ISU_ISU_FM_DL_STADDH_DLADD_Pos           (0UL)
#define R_ISU_ISU_FM_DL_STADDL_DLADD_Msk           (0xFFFFFFFFUL)
#define R_ISU_ISU_FM_DL_STADDL_DLADD_Pos           (0UL)
#define R_ISU_ISU_FM_FRCON_START_Msk               (0x00000001UL)
#define R_ISU_ISU_FM_FRCON_START_Pos               (0UL)
#define R_ISU_ISU_FM_FRCON_DESON_Msk               (0x00010000UL)
#define R_ISU_ISU_FM_FRCON_DESON_Pos               (16UL)
#define R_ISU_ISU_FM_STOP_STOP_Msk                 (0x00000001UL)
#define R_ISU_ISU_FM_STOP_STOP_Pos                 (0UL)
#define R_ISU_ISU_FM_INT_EN_FRENDE_Msk             (0x00000001UL)
#define R_ISU_ISU_FM_INT_EN_FRENDE_Pos             (0UL)
#define R_ISU_ISU_FM_INT_EN_DESENDE_Msk            (0x00000002UL)
#define R_ISU_ISU_FM_INT_EN_DESENDE_Pos            (1UL)
#define R_ISU_ISU_FM_INT_EN_SRSTENDE_Msk           (0x00000100UL)
#define R_ISU_ISU_FM_INT_EN_SRSTENDE_Pos           (8UL)
#define R_ISU_ISU_FM_INT_EN_LISTERRE_Msk           (0x00010000UL)
#define R_ISU_ISU_FM_INT_EN_LISTERRE_Pos           (16UL)
#define R_ISU_ISU_FM_INT_EN_AXITXERRE_Msk          (0x01000000UL)
#define R_ISU_ISU_FM_INT_EN_AXITXERRE_Pos          (24UL)
#define R_ISU_ISU_FM_INT_EN_AXIRXERRE_Msk          (0x10000000UL)
#define R_ISU_ISU_FM_INT_EN_AXIRXERRE_Pos          (28UL)
#define R_ISU_ISU_FM_INT_STA_FREND_Msk             (0x00000001UL)
#define R_ISU_ISU_FM_INT_STA_FREND_Pos             (0UL)
#define R_ISU_ISU_FM_INT_STA_DESEND_Msk            (0x00000002UL)
#define R_ISU_ISU_FM_INT_STA_DESEND_Pos            (1UL)
#define R_ISU_ISU_FM_INT_STA_SRSTEND_Msk           (0x00000100UL)
#define R_ISU_ISU_FM_INT_STA_SRSTEND_Pos           (8UL)
#define R_ISU_ISU_FM_INT_STA_LISTERR_Msk           (0x00010000UL)
#define R_ISU_ISU_FM_INT_STA_LISTERR_Pos           (16UL)
#define R_ISU_ISU_FM_INT_STA_BRESPERR_Msk          (0x03800000UL)
#define R_ISU_ISU_FM_INT_STA_BRESPERR_Pos          (23UL)
#define R_ISU_ISU_FM_INT_STA_RRESPERR_Msk          (0x38000000UL)
#define R_ISU_ISU_FM_INT_STA_RRESPERR_Pos          (27UL)
#define R_ISU_ISU_AXI_ERACT_BRESPDEC_ACT_Msk       (0x00800000UL)
#define R_ISU_ISU_AXI_ERACT_BRESPDEC_ACT_Pos       (23UL)
#define R_ISU_ISU_AXI_ERACT_BRESPSLV_ACT_Msk       (0x01000000UL)
#define R_ISU_ISU_AXI_ERACT_BRESPSLV_ACT_Pos       (24UL)
#define R_ISU_ISU_AXI_ERACT_BRESPEXO_ACT_Msk       (0x02000000UL)
#define R_ISU_ISU_AXI_ERACT_BRESPEXO_ACT_Pos       (25UL)
#define R_ISU_ISU_AXI_ERACT_RRESPDEC_ACT_Msk       (0x08000000UL)
#define R_ISU_ISU_AXI_ERACT_RRESPDEC_ACT_Pos       (27UL)
#define R_ISU_ISU_AXI_ERACT_RRESPSLV_ACT_Msk       (0x10000000UL)
#define R_ISU_ISU_AXI_ERACT_RRESPSLV_ACT_Pos       (28UL)
#define R_ISU_ISU_AXI_ERACT_RRESPEXO_ACT_Msk       (0x20000000UL)
#define R_ISU_ISU_AXI_ERACT_RRESPEXO_ACT_Pos       (29UL)
#define R_ISU_ISU_AXI_FIFO_CAP_DCAP_PL1_Msk        (0x0000003FUL)
#define R_ISU_ISU_AXI_FIFO_CAP_DCAP_PL1_Pos        (0UL)
#define R_ISU_ISU_AXI_FIFO_CAP_DCAP_PL0_Msk        (0x00007F00UL)
#define R_ISU_ISU_AXI_FIFO_CAP_DCAP_PL0_Pos        (8UL)
#define R_ISU_ISU_AXI_FIFO_CAP_SCAP_PL1_Msk        (0x003F0000UL)
#define R_ISU_ISU_AXI_FIFO_CAP_SCAP_PL1_Pos        (16UL)
#define R_ISU_ISU_AXI_FIFO_CAP_SCAP_PL0_Msk        (0x7F000000UL)
#define R_ISU_ISU_AXI_FIFO_CAP_SCAP_PL0_Pos        (24UL)
#define R_ISU_ISU_RPF_SRC_SIZE_S_VSIZE_Msk         (0x00000FFFUL)
#define R_ISU_ISU_RPF_SRC_SIZE_S_VSIZE_Pos         (0UL)
#define R_ISU_ISU_RPF_SRC_SIZE_S_HSIZE_Msk         (0x0FFF0000UL)
#define R_ISU_ISU_RPF_SRC_SIZE_S_HSIZE_Pos         (16UL)
#define R_ISU_ISU_RPF_SRC_STRD_SSTRPL1_Msk         (0x0000FFFFUL)
#define R_ISU_ISU_RPF_SRC_STRD_SSTRPL1_Pos         (0UL)
#define R_ISU_ISU_RPF_SRC_STRD_SSTRPL0_Msk         (0xFFFF0000UL)
#define R_ISU_ISU_RPF_SRC_STRD_SSTRPL0_Pos         (16UL)
#define R_ISU_ISU_RPF_SRC_ADDH_PL0_SADD_PL0_Msk    (0x00000003UL)
#define R_ISU_ISU_RPF_SRC_ADDH_PL0_SADD_PL0_Pos    (0UL)
#define R_ISU_ISU_RPF_SRC_ADDL_PL0_SADD_PL0_Msk    (0xFFFFFFFFUL)
#define R_ISU_ISU_RPF_SRC_ADDL_PL0_SADD_PL0_Pos    (0UL)
#define R_ISU_ISU_RPF_SRC_ADDH_PL1_SADD_PL1_Msk    (0x00000003UL)
#define R_ISU_ISU_RPF_SRC_ADDH_PL1_SADD_PL1_Pos    (0UL)
#define R_ISU_ISU_RPF_SRC_ADDL_PL1_SADD_PL1_Msk    (0xFFFFFFFFUL)
#define R_ISU_ISU_RPF_SRC_ADDL_PL1_SADD_PL1_Pos    (0UL)
#define R_ISU_ISU_RPF_FMT_RDFM_Msk                 (0x0000003FUL)
#define R_ISU_ISU_RPF_FMT_RDFM_Pos                 (0UL)
#define R_ISU_ISU_RPF_UVBIN_UVCHG_Msk              (0x00000001UL)
#define R_ISU_ISU_RPF_UVBIN_UVCHG_Pos              (0UL)
#define R_ISU_ISU_RPF_SRC_DSWAP_RD_SWAP_Msk        (0x00000007UL)
#define R_ISU_ISU_RPF_SRC_DSWAP_RD_SWAP_Pos        (0UL)
#define R_ISU_ISU_RPF_ALPH_SEL_S_ALPH0_Msk         (0x000000FFUL)
#define R_ISU_ISU_RPF_ALPH_SEL_S_ALPH0_Pos         (0UL)
#define R_ISU_ISU_RPF_ALPH_SEL_S_ALPH1_Msk         (0x0000FF00UL)
#define R_ISU_ISU_RPF_ALPH_SEL_S_ALPH1_Pos         (8UL)
#define R_ISU_ISU_RPF_ALPH_SEL_S_A1SEL_Msk         (0x00010000UL)
#define R_ISU_ISU_RPF_ALPH_SEL_S_A1SEL_Pos         (16UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_STEP_Msk       (0x0000000FUL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_STEP_Pos       (0UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_TYPE_Msk       (0x00000010UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_TYPE_Pos       (4UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_B_Msk          (0x00010000UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_B_Pos          (16UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_G_Msk          (0x00020000UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_G_Pos          (17UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_R_Msk          (0x00040000UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_R_Pos          (18UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_A_Msk          (0x00080000UL)
#define R_ISU_ISU_RPF_SRC_TD1_GRADA_A_Pos          (19UL)
#define R_ISU_ISU_RPF_SRC_TD1_TMODE_EN_Msk         (0x80000000UL)
#define R_ISU_ISU_RPF_SRC_TD1_TMODE_EN_Pos         (31UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_B_Msk           (0x000000FFUL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_B_Pos           (0UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_G_Msk           (0x0000FF00UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_G_Pos           (8UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_R_Msk           (0x00FF0000UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_R_Pos           (16UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_A_Msk           (0xFF000000UL)
#define R_ISU_ISU_RPF_SRC_TD2_INIT_A_Pos           (24UL)
#define R_ISU_ISU_RS_HSCALE_HFRAC_Msk              (0x00000FFFUL)
#define R_ISU_ISU_RS_HSCALE_HFRAC_Pos              (0UL)
#define R_ISU_ISU_RS_HSCALE_HMANT_Msk              (0x000F0000UL)
#define R_ISU_ISU_RS_HSCALE_HMANT_Pos              (16UL)
#define R_ISU_ISU_RS_VSCALE_VFRAC_Msk              (0x00000FFFUL)
#define R_ISU_ISU_RS_VSCALE_VFRAC_Pos              (0UL)
#define R_ISU_ISU_RS_VSCALE_VMANT_Msk              (0x000F0000UL)
#define R_ISU_ISU_RS_VSCALE_VMANT_Pos              (16UL)
#define R_ISU_ISU_RS_STPOS_VSTART_Msk              (0x000007FFUL)
#define R_ISU_ISU_RS_STPOS_VSTART_Pos              (0UL)
#define R_ISU_ISU_RS_STPOS_HSTART_Msk              (0x07FF0000UL)
#define R_ISU_ISU_RS_STPOS_HSTART_Pos              (16UL)
#define R_ISU_ISU_RS_POS_TUNE_VST_TUNE_Msk         (0x00000FFFUL)
#define R_ISU_ISU_RS_POS_TUNE_VST_TUNE_Pos         (0UL)
#define R_ISU_ISU_RS_POS_TUNE_HST_TUNE_Msk         (0x0FFF0000UL)
#define R_ISU_ISU_RS_POS_TUNE_HST_TUNE_Pos         (16UL)
#define R_ISU_ISU_RS_OS_CROP_O_VSIZE_Msk           (0x000007FFUL)
#define R_ISU_ISU_RS_OS_CROP_O_VSIZE_Pos           (0UL)
#define R_ISU_ISU_RS_OS_CROP_O_HSIZE_Msk           (0x07FF0000UL)
#define R_ISU_ISU_RS_OS_CROP_O_HSIZE_Pos           (16UL)
#define R_ISU_ISU_RS_PADDMODE_PADDSEL_Msk          (0x00000001UL)
#define R_ISU_ISU_RS_PADDMODE_PADDSEL_Pos          (0UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L0_Msk            (0x000000FFUL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L0_Pos            (0UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L1_Msk            (0x0000FF00UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L1_Pos            (8UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L2_Msk            (0x00FF0000UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L2_Pos            (16UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L3_Msk            (0xFF000000UL)
#define R_ISU_ISU_RS_PADDVAL_VAL_L3_Pos            (24UL)
#define R_ISU_ISU_WPF_DST_ADDH_PL0_DADD_PL0_Msk    (0x00000003UL)
#define R_ISU_ISU_WPF_DST_ADDH_PL0_DADD_PL0_Pos    (0UL)
#define R_ISU_ISU_WPF_DST_ADDL_PL0_DADD_PL0_Msk    (0xFFFFFFFFUL)
#define R_ISU_ISU_WPF_DST_ADDL_PL0_DADD_PL0_Pos    (0UL)
#define R_ISU_ISU_WPF_DST_ADDH_PL1_DADD_PL1_Msk    (0x00000003UL)
#define R_ISU_ISU_WPF_DST_ADDH_PL1_DADD_PL1_Pos    (0UL)
#define R_ISU_ISU_WPF_DST_ADDL_PL1_DADD_PL1_Msk    (0xFFFFFFFFUL)
#define R_ISU_ISU_WPF_DST_ADDL_PL1_DADD_PL1_Pos    (0UL)
#define R_ISU_ISU_WPF_DST_STRD_DSTRPL1_Msk         (0x0000FFFFUL)
#define R_ISU_ISU_WPF_DST_STRD_DSTRPL1_Pos         (0UL)
#define R_ISU_ISU_WPF_DST_STRD_DSTRPL0_Msk         (0xFFFF0000UL)
#define R_ISU_ISU_WPF_DST_STRD_DSTRPL0_Pos         (16UL)
#define R_ISU_ISU_WPF_FMT_WDFMT_Msk                (0x0000003FUL)
#define R_ISU_ISU_WPF_FMT_WDFMT_Pos                (0UL)
#define R_ISU_ISU_WPF_CCOL_CMAT_ASEL_Msk           (0x00000001UL)
#define R_ISU_ISU_WPF_CCOL_CMAT_ASEL_Pos           (0UL)
#define R_ISU_ISU_WPF_CCOL_CMAT_SEL_Msk            (0x00000002UL)
#define R_ISU_ISU_WPF_CCOL_CMAT_SEL_Pos            (1UL)
#define R_ISU_ISU_WPF_MUL1_K11_Msk                 (0x00003FFFUL)
#define R_ISU_ISU_WPF_MUL1_K11_Pos                 (0UL)
#define R_ISU_ISU_WPF_MUL2_K12_Msk                 (0x00003FFFUL)
#define R_ISU_ISU_WPF_MUL2_K12_Pos                 (0UL)
#define R_ISU_ISU_WPF_MUL2_K13_Msk                 (0x3FFF0000UL)
#define R_ISU_ISU_WPF_MUL2_K13_Pos                 (16UL)
#define R_ISU_ISU_WPF_MUL3_K21_Msk                 (0x00003FFFUL)
#define R_ISU_ISU_WPF_MUL3_K21_Pos                 (0UL)
#define R_ISU_ISU_WPF_MUL4_K22_Msk                 (0x00003FFFUL)
#define R_ISU_ISU_WPF_MUL4_K22_Pos                 (0UL)
#define R_ISU_ISU_WPF_MUL4_K23_Msk                 (0x3FFF0000UL)
#define R_ISU_ISU_WPF_MUL4_K23_Pos                 (16UL)
#define R_ISU_ISU_WPF_MUL5_K31_Msk                 (0x00003FFFUL)
#define R_ISU_ISU_WPF_MUL5_K31_Pos                 (0UL)
#define R_ISU_ISU_WPF_MUL6_K32_Msk                 (0x00003FFFUL)
#define R_ISU_ISU_WPF_MUL6_K32_Pos                 (0UL)
#define R_ISU_ISU_WPF_MUL6_K33_Msk                 (0x3FFF0000UL)
#define R_ISU_ISU_WPF_MUL6_K33_Pos                 (16UL)
#define R_ISU_ISU_WPF_OFST1_OFST_C1_Msk            (0x0000FF00UL)
#define R_ISU_ISU_WPF_OFST1_OFST_C1_Pos            (8UL)
#define R_ISU_ISU_WPF_OFST1_OFST_B1_Msk            (0x00FF0000UL)
#define R_ISU_ISU_WPF_OFST1_OFST_B1_Pos            (16UL)
#define R_ISU_ISU_WPF_OFST1_OFST_A1_Msk            (0xFF000000UL)
#define R_ISU_ISU_WPF_OFST1_OFST_A1_Pos            (24UL)
#define R_ISU_ISU_WPF_OFST2_OFST_C2_Msk            (0x0000FF00UL)
#define R_ISU_ISU_WPF_OFST2_OFST_C2_Pos            (8UL)
#define R_ISU_ISU_WPF_OFST2_OFST_B2_Msk            (0x00FF0000UL)
#define R_ISU_ISU_WPF_OFST2_OFST_B2_Pos            (16UL)
#define R_ISU_ISU_WPF_OFST2_OFST_A2_Msk            (0xFF000000UL)
#define R_ISU_ISU_WPF_OFST2_OFST_A2_Pos            (24UL)
#define R_ISU_ISU_WPF_CLP1_CLPMIN_A_Msk            (0x000000FFUL)
#define R_ISU_ISU_WPF_CLP1_CLPMIN_A_Pos            (0UL)
#define R_ISU_ISU_WPF_CLP1_CLPMAX_A_Msk            (0x0000FF00UL)
#define R_ISU_ISU_WPF_CLP1_CLPMAX_A_Pos            (8UL)
#define R_ISU_ISU_WPF_CLP2_CLPMIN_C_Msk            (0x000000FFUL)
#define R_ISU_ISU_WPF_CLP2_CLPMIN_C_Pos            (0UL)
#define R_ISU_ISU_WPF_CLP2_CLPMAX_C_Msk            (0x0000FF00UL)
#define R_ISU_ISU_WPF_CLP2_CLPMAX_C_Pos            (8UL)
#define R_ISU_ISU_WPF_CLP2_CLPMIN_B_Msk            (0x00FF0000UL)
#define R_ISU_ISU_WPF_CLP2_CLPMIN_B_Pos            (16UL)
#define R_ISU_ISU_WPF_CLP2_CLPMAX_B_Msk            (0xFF000000UL)
#define R_ISU_ISU_WPF_CLP2_CLPMAX_B_Pos            (24UL)
#define R_ISU_ISU_WPF_DST_DSWAP_WD_SWAP_Msk        (0x00000007UL)
#define R_ISU_ISU_WPF_DST_DSWAP_WD_SWAP_Pos        (0UL)
#define R_ISU_ISU_WPF_ALPH_SEL1_D_A1THR_Msk        (0x000000FFUL)
#define R_ISU_ISU_WPF_ALPH_SEL1_D_A1THR_Pos        (0UL)
#define R_ISU_ISU_WPF_ALPH_SEL1_D_A1SEL_Msk        (0x00010000UL)
#define R_ISU_ISU_WPF_ALPH_SEL1_D_A1SEL_Pos        (16UL)
#define R_ISU_ISU_WPF_ALPH_SEL2_D_A8THR0_Msk       (0x000000FFUL)
#define R_ISU_ISU_WPF_ALPH_SEL2_D_A8THR0_Pos       (0UL)
#define R_ISU_ISU_WPF_ALPH_SEL2_D_A8THR1_Msk       (0x0000FF00UL)
#define R_ISU_ISU_WPF_ALPH_SEL2_D_A8THR1_Pos       (8UL)
#define R_ISU_ISU_WPF_ALPH_SEL2_D_A8SEL_Msk        (0x00010000UL)
#define R_ISU_ISU_WPF_ALPH_SEL2_D_A8SEL_Pos        (16UL)
#define R_ISU_ISU_WPF_ALPH_VAL_D_ALPH0_Msk         (0x000000FFUL)
#define R_ISU_ISU_WPF_ALPH_VAL_D_ALPH0_Pos         (0UL)
#define R_ISU_ISU_WPF_ALPH_VAL_D_ALPH1_Msk         (0x0000FF00UL)
#define R_ISU_ISU_WPF_ALPH_VAL_D_ALPH1_Pos         (8UL)
#define R_ISU_ISU_WPF_ALPH_VAL_D_ALPH2_Msk         (0x00FF0000UL)
#define R_ISU_ISU_WPF_ALPH_VAL_D_ALPH2_Pos         (16UL)
#define R_ISU_ISU_AXI_BLEN_AWLEN_MAX_Msk           (0x0000000FUL)
#define R_ISU_ISU_AXI_BLEN_AWLEN_MAX_Pos           (0UL)
#define R_ISU_ISU_AXI_BLEN_ARLEN_MAX_Msk           (0x000F0000UL)
#define R_ISU_ISU_AXI_BLEN_ARLEN_MAX_Pos           (16UL)

#endif

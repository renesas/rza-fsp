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
 * File Name    : sysc_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for sysc.
 *********************************************************************************************************************/

#ifndef SYSC_IOBITMASK_H
#define SYSC_IOBITMASK_H

#define R_SYSC_SYS_RAM0_ECC_VECCEN_Msk                      (0x00000001UL)
#define R_SYSC_SYS_RAM0_ECC_VECCEN_Pos                      (0UL)
#define R_SYSC_SYS_RAM0_EN_VCEN_Msk                         (0x00000001UL)
#define R_SYSC_SYS_RAM0_EN_VCEN_Pos                         (0UL)
#define R_SYSC_SYS_RAM0_EN_VLWEN_Msk                        (0x00000002UL)
#define R_SYSC_SYS_RAM0_EN_VLWEN_Pos                        (1UL)
#define R_SYSC_SYS_RAM1_ECC_VECCEN_Msk                      (0x00000001UL)
#define R_SYSC_SYS_RAM1_ECC_VECCEN_Pos                      (0UL)
#define R_SYSC_SYS_RAM1_EN_VCEN_Msk                         (0x00000001UL)
#define R_SYSC_SYS_RAM1_EN_VCEN_Pos                         (0UL)
#define R_SYSC_SYS_RAM1_EN_VLWEN_Msk                        (0x00000002UL)
#define R_SYSC_SYS_RAM1_EN_VLWEN_Pos                        (1UL)
#define R_SYSC_SYS_WDT0_CTRL_WDTSTOP_Msk                    (0x00000001UL)
#define R_SYSC_SYS_WDT0_CTRL_WDTSTOP_Pos                    (0UL)
#define R_SYSC_SYS_WDT0_CTRL_WDTSTOPMASK_Msk                (0x00010000UL)
#define R_SYSC_SYS_WDT0_CTRL_WDTSTOPMASK_Pos                (16UL)
#define R_SYSC_SYS_GETH0_CFG_FEC_GIGA_ENABLE_Msk            (0x01000000UL)
#define R_SYSC_SYS_GETH0_CFG_FEC_GIGA_ENABLE_Pos            (24UL)
#define R_SYSC_SYS_GETH1_CFG_FEC_GIGA_ENABLE_Msk            (0x01000000UL)
#define R_SYSC_SYS_GETH1_CFG_FEC_GIGA_ENABLE_Pos            (24UL)
#define R_SYSC_SYS_I2C0_CFG_af_bypass_Msk                   (0x00000001UL)
#define R_SYSC_SYS_I2C0_CFG_af_bypass_Pos                   (0UL)
#define R_SYSC_SYS_I2C1_CFG_af_bypass_Msk                   (0x00000001UL)
#define R_SYSC_SYS_I2C1_CFG_af_bypass_Pos                   (0UL)
#define R_SYSC_SYS_I2C2_CFG_af_bypass_Msk                   (0x00000001UL)
#define R_SYSC_SYS_I2C2_CFG_af_bypass_Pos                   (0UL)
#define R_SYSC_SYS_I2C3_CFG_af_bypass_Msk                   (0x00000001UL)
#define R_SYSC_SYS_I2C3_CFG_af_bypass_Pos                   (0UL)
#define R_SYSC_SYS_CA55_CFG_RVAL0_RVBARADDRL0_Msk           (0xFFFFFFFCUL)
#define R_SYSC_SYS_CA55_CFG_RVAL0_RVBARADDRL0_Pos           (2UL)
#define R_SYSC_SYS_CA55_CFG_RVAH0_RVBARADDRH0_Msk           (0x000000FFUL)
#define R_SYSC_SYS_CA55_CFG_RVAH0_RVBARADDRH0_Pos           (0UL)
#define R_SYSC_SYS_LSI_MODE_STAT_MD_BOOT_Msk                (0x00000007UL)
#define R_SYSC_SYS_LSI_MODE_STAT_MD_BOOT_Pos                (0UL)
#define R_SYSC_SYS_LSI_MODE_STAT_DEBUGEN_Msk                (0x00000200UL)
#define R_SYSC_SYS_LSI_MODE_STAT_DEBUGEN_Pos                (9UL)
#define R_SYSC_SYS_LSI_MODE_STAT_MD_CLKS_Msk                (0x00001000UL)
#define R_SYSC_SYS_LSI_MODE_STAT_MD_CLKS_Pos                (12UL)
#define R_SYSC_SYS_LSI_MODE_STAT_MD_OSCDRV_Msk              (0x0000C000UL)
#define R_SYSC_SYS_LSI_MODE_STAT_MD_OSCDRV_Pos              (14UL)
#define R_SYSC_SYS_AOF0_OFS00_SXSDHI_0_Msk                  (0x0000000FUL)
#define R_SYSC_SYS_AOF0_OFS00_SXSDHI_0_Pos                  (0UL)
#define R_SYSC_SYS_AOF0_OFS01_SXSDHI_0_Msk                  (0x000000F0UL)
#define R_SYSC_SYS_AOF0_OFS01_SXSDHI_0_Pos                  (4UL)
#define R_SYSC_SYS_AOF0_OFS10_SXSDHI_0_Msk                  (0x00000F00UL)
#define R_SYSC_SYS_AOF0_OFS10_SXSDHI_0_Pos                  (8UL)
#define R_SYSC_SYS_AOF0_OFS11_SXSDHI_0_Msk                  (0x0000F000UL)
#define R_SYSC_SYS_AOF0_OFS11_SXSDHI_0_Pos                  (12UL)
#define R_SYSC_SYS_AOF0_OFS00_SXSDHI_1_Msk                  (0x000F0000UL)
#define R_SYSC_SYS_AOF0_OFS00_SXSDHI_1_Pos                  (16UL)
#define R_SYSC_SYS_AOF0_OFS01_SXSDHI_1_Msk                  (0x00F00000UL)
#define R_SYSC_SYS_AOF0_OFS01_SXSDHI_1_Pos                  (20UL)
#define R_SYSC_SYS_AOF0_OFS10_SXSDHI_1_Msk                  (0x0F000000UL)
#define R_SYSC_SYS_AOF0_OFS10_SXSDHI_1_Pos                  (24UL)
#define R_SYSC_SYS_AOF0_OFS11_SXSDHI_1_Msk                  (0xF0000000UL)
#define R_SYSC_SYS_AOF0_OFS11_SXSDHI_1_Pos                  (28UL)
#define R_SYSC_SYS_AOF1_OFS00_SXGIGE_0_Msk                  (0x0000000FUL)
#define R_SYSC_SYS_AOF1_OFS00_SXGIGE_0_Pos                  (0UL)
#define R_SYSC_SYS_AOF1_OFS01_SXGIGE_0_Msk                  (0x000000F0UL)
#define R_SYSC_SYS_AOF1_OFS01_SXGIGE_0_Pos                  (4UL)
#define R_SYSC_SYS_AOF1_OFS10_SXGIGE_0_Msk                  (0x00000F00UL)
#define R_SYSC_SYS_AOF1_OFS10_SXGIGE_0_Pos                  (8UL)
#define R_SYSC_SYS_AOF1_OFS11_SXGIGE_0_Msk                  (0x0000F000UL)
#define R_SYSC_SYS_AOF1_OFS11_SXGIGE_0_Pos                  (12UL)
#define R_SYSC_SYS_AOF1_OFS00_SXGIGE_1_Msk                  (0x000F0000UL)
#define R_SYSC_SYS_AOF1_OFS00_SXGIGE_1_Pos                  (16UL)
#define R_SYSC_SYS_AOF1_OFS01_SXGIGE_1_Msk                  (0x00F00000UL)
#define R_SYSC_SYS_AOF1_OFS01_SXGIGE_1_Pos                  (20UL)
#define R_SYSC_SYS_AOF1_OFS10_SXGIGE_1_Msk                  (0x0F000000UL)
#define R_SYSC_SYS_AOF1_OFS10_SXGIGE_1_Pos                  (24UL)
#define R_SYSC_SYS_AOF1_OFS11_SXGIGE_1_Msk                  (0xF0000000UL)
#define R_SYSC_SYS_AOF1_OFS11_SXGIGE_1_Pos                  (28UL)
#define R_SYSC_SYS_AOF2_OFS00_SXUSB2_0_H_Msk                (0x0000000FUL)
#define R_SYSC_SYS_AOF2_OFS00_SXUSB2_0_H_Pos                (0UL)
#define R_SYSC_SYS_AOF2_OFS01_SXUSB2_0_H_Msk                (0x000000F0UL)
#define R_SYSC_SYS_AOF2_OFS01_SXUSB2_0_H_Pos                (4UL)
#define R_SYSC_SYS_AOF2_OFS10_SXUSB2_0_H_Msk                (0x00000F00UL)
#define R_SYSC_SYS_AOF2_OFS10_SXUSB2_0_H_Pos                (8UL)
#define R_SYSC_SYS_AOF2_OFS11_SXUSB2_0_H_Msk                (0x0000F000UL)
#define R_SYSC_SYS_AOF2_OFS11_SXUSB2_0_H_Pos                (12UL)
#define R_SYSC_SYS_AOF2_OFS00_SXUSB2_1_Msk                  (0x000F0000UL)
#define R_SYSC_SYS_AOF2_OFS00_SXUSB2_1_Pos                  (16UL)
#define R_SYSC_SYS_AOF2_OFS01_SXUSB2_1_Msk                  (0x00F00000UL)
#define R_SYSC_SYS_AOF2_OFS01_SXUSB2_1_Pos                  (20UL)
#define R_SYSC_SYS_AOF2_OFS10_SXUSB2_1_Msk                  (0x0F000000UL)
#define R_SYSC_SYS_AOF2_OFS10_SXUSB2_1_Pos                  (24UL)
#define R_SYSC_SYS_AOF2_OFS11_SXUSB2_1_Msk                  (0xF0000000UL)
#define R_SYSC_SYS_AOF2_OFS11_SXUSB2_1_Pos                  (28UL)
#define R_SYSC_SYS_AOF3_OFS00_SXUSB2_0_F_Msk                (0x0000000FUL)
#define R_SYSC_SYS_AOF3_OFS00_SXUSB2_0_F_Pos                (0UL)
#define R_SYSC_SYS_AOF3_OFS01_SXUSB2_0_F_Msk                (0x000000F0UL)
#define R_SYSC_SYS_AOF3_OFS01_SXUSB2_0_F_Pos                (4UL)
#define R_SYSC_SYS_AOF3_OFS10_SXUSB2_0_F_Msk                (0x00000F00UL)
#define R_SYSC_SYS_AOF3_OFS10_SXUSB2_0_F_Pos                (8UL)
#define R_SYSC_SYS_AOF3_OFS11_SXUSB2_0_F_Msk                (0x0000F000UL)
#define R_SYSC_SYS_AOF3_OFS11_SXUSB2_0_F_Pos                (12UL)
#define R_SYSC_SYS_AOF4_OFS00_SXLCDC_Msk                    (0x0000000FUL)
#define R_SYSC_SYS_AOF4_OFS00_SXLCDC_Pos                    (0UL)
#define R_SYSC_SYS_AOF4_OFS01_SXLCDC_Msk                    (0x000000F0UL)
#define R_SYSC_SYS_AOF4_OFS01_SXLCDC_Pos                    (4UL)
#define R_SYSC_SYS_AOF4_OFS10_SXLCDC_Msk                    (0x00000F00UL)
#define R_SYSC_SYS_AOF4_OFS10_SXLCDC_Pos                    (8UL)
#define R_SYSC_SYS_AOF4_OFS11_SXLCDC_Msk                    (0x0000F000UL)
#define R_SYSC_SYS_AOF4_OFS11_SXLCDC_Pos                    (12UL)
#define R_SYSC_SYS_AOF6_OFS00_SXDMAC_S_Msk                  (0x0000000FUL)
#define R_SYSC_SYS_AOF6_OFS00_SXDMAC_S_Pos                  (0UL)
#define R_SYSC_SYS_AOF6_OFS01_SXDMAC_S_Msk                  (0x000000F0UL)
#define R_SYSC_SYS_AOF6_OFS01_SXDMAC_S_Pos                  (4UL)
#define R_SYSC_SYS_AOF6_OFS10_SXDMAC_S_Msk                  (0x00000F00UL)
#define R_SYSC_SYS_AOF6_OFS10_SXDMAC_S_Pos                  (8UL)
#define R_SYSC_SYS_AOF6_OFS11_SXDMAC_S_Msk                  (0x0000F000UL)
#define R_SYSC_SYS_AOF6_OFS11_SXDMAC_S_Pos                  (12UL)
#define R_SYSC_SYS_AOF6_OFS00_SXDMAC_NS_Msk                 (0x000F0000UL)
#define R_SYSC_SYS_AOF6_OFS00_SXDMAC_NS_Pos                 (16UL)
#define R_SYSC_SYS_AOF6_OFS01_SXDMAC_NS_Msk                 (0x00F00000UL)
#define R_SYSC_SYS_AOF6_OFS01_SXDMAC_NS_Pos                 (20UL)
#define R_SYSC_SYS_AOF6_OFS10_SXDMAC_NS_Msk                 (0x0F000000UL)
#define R_SYSC_SYS_AOF6_OFS10_SXDMAC_NS_Pos                 (24UL)
#define R_SYSC_SYS_AOF6_OFS11_SXDMAC_NS_Msk                 (0xF0000000UL)
#define R_SYSC_SYS_AOF6_OFS11_SXDMAC_NS_Pos                 (28UL)
#define R_SYSC_SYS_LP_CTL2_CA55_STBYCTL_Msk                 (0x00000001UL)
#define R_SYSC_SYS_LP_CTL2_CA55_STBYCTL_Pos                 (0UL)
#define R_SYSC_SYS_LP_CTL5_ASCLKQDENY_F_Msk                 (0x00000002UL)
#define R_SYSC_SYS_LP_CTL5_ASCLKQDENY_F_Pos                 (1UL)
#define R_SYSC_SYS_LP_CTL5_AMCLKQDENY_F_Msk                 (0x00000004UL)
#define R_SYSC_SYS_LP_CTL5_AMCLKQDENY_F_Pos                 (2UL)
#define R_SYSC_SYS_LP_CTL6_ASCLKQDENY_E_Msk                 (0x00000002UL)
#define R_SYSC_SYS_LP_CTL6_ASCLKQDENY_E_Pos                 (1UL)
#define R_SYSC_SYS_LP_CTL6_AMCLKQDENY_E_Msk                 (0x00000004UL)
#define R_SYSC_SYS_LP_CTL6_AMCLKQDENY_E_Pos                 (2UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_ASCLKQACTIVE_Msk          (0x00000002UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_ASCLKQACTIVE_Pos          (1UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_AMCLKQACTIVE_Msk          (0x00000004UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_AMCLKQACTIVE_Pos          (2UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_PCLKQACTIVE_Msk           (0x00000100UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_PCLKQACTIVE_Pos           (8UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_ATCLKQACTIVE_Msk          (0x00000200UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_ATCLKQACTIVE_Pos          (9UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_GICCLKQACTIVE_Msk         (0x00000400UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_GICCLKQACTIVE_Pos         (10UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_PDBGCLKQACTIVE_Msk        (0x00000800UL)
#define R_SYSC_SYS_LP_CA55CK_CTL1_PDBGCLKQACTIVE_Pos        (11UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_ASCLKQREQn_Msk            (0x00000002UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_ASCLKQREQn_Pos            (1UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_AMCLKQREQn_Msk            (0x00000004UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_AMCLKQREQn_Pos            (2UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_PCLKQREQn_Msk             (0x00000100UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_PCLKQREQn_Pos             (8UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_ATCLKQREQn_Msk            (0x00000200UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_ATCLKQREQn_Pos            (9UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_GICCLKQREQn_Msk           (0x00000400UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_GICCLKQREQn_Pos           (10UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_PDBGCLKQREQn_Msk          (0x00000800UL)
#define R_SYSC_SYS_LP_CA55CK_CTL2_PDBGCLKQREQn_Pos          (11UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_CA55_COREINSTRRUN0_Msk    (0x00000001UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_CA55_COREINSTRRUN0_Pos    (0UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ASCLKQACCEPTn_Msk         (0x00000002UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ASCLKQACCEPTn_Pos         (1UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_AMCLKQACCEPTn_Msk         (0x00000004UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_AMCLKQACCEPTn_Pos         (2UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PCLKQACCEPTn_Msk          (0x00000100UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PCLKQACCEPTn_Pos          (8UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ATCLKQACCEPTn_Msk         (0x00000200UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ATCLKQACCEPTn_Pos         (9UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_GICCLKQACCEPTn_Msk        (0x00000400UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_GICCLKQACCEPTn_Pos        (10UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PDBGCLKQACCEPTn_Msk       (0x00000800UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PDBGCLKQACCEPTn_Pos       (11UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ASCLKQDENY_Msk            (0x00020000UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ASCLKQDENY_Pos            (17UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_AMCLKQDENY_Msk            (0x00040000UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_AMCLKQDENY_Pos            (18UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PCLKQDENY_Msk             (0x01000000UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PCLKQDENY_Pos             (24UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ATCLKQDENY_Msk            (0x02000000UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_ATCLKQDENY_Pos            (25UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_GICCLKQDENY_Msk           (0x04000000UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_GICCLKQDENY_Pos           (26UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PDBGCLKQDENY_Msk          (0x08000000UL)
#define R_SYSC_SYS_LP_CA55CK_CTL3_PDBGCLKQDENY_Pos          (27UL)
#define R_SYSC_SYS_GPREG_0_GPREG0_Msk                       (0xFFFFFFFFUL)
#define R_SYSC_SYS_GPREG_0_GPREG0_Pos                       (0UL)
#define R_SYSC_SYS_GPREG_1_GPREG1_Msk                       (0xFFFFFFFFUL)
#define R_SYSC_SYS_GPREG_1_GPREG1_Pos                       (0UL)
#define R_SYSC_SYS_GPREG_2_GPREG2_Msk                       (0xFFFFFFFFUL)
#define R_SYSC_SYS_GPREG_2_GPREG2_Pos                       (0UL)
#define R_SYSC_SYS_GPREG_3_GPREG3_Msk                       (0xFFFFFFFFUL)
#define R_SYSC_SYS_GPREG_3_GPREG3_Pos                       (0UL)
#define R_SYSC_SYS_IPCONT_SEL_SPI_OCTA_SEL_SPI_OCTA_Msk     (0x00000001UL)
#define R_SYSC_SYS_IPCONT_SEL_SPI_OCTA_SEL_SPI_OCTA_Pos     (0UL)

#endif

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
 * File Name    : intc_ia55_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for intc_ia55.
 *********************************************************************************************************************/

#ifndef INTC_IA55_IOBITMASK_H
#define INTC_IA55_IOBITMASK_H

#define R_INTC_IA55_NSCR_NSTAT_Msk         (0x00000001UL)
#define R_INTC_IA55_NSCR_NSTAT_Pos         (0UL)
#define R_INTC_IA55_NSCR_NSMON_Msk         (0x00010000UL)
#define R_INTC_IA55_NSCR_NSMON_Pos         (16UL)
#define R_INTC_IA55_NITSR_NTSEL_Msk        (0x00000001UL)
#define R_INTC_IA55_NITSR_NTSEL_Pos        (0UL)
#define R_INTC_IA55_ISCR_ISTAT0_Msk        (0x00000001UL)
#define R_INTC_IA55_ISCR_ISTAT0_Pos        (0UL)
#define R_INTC_IA55_ISCR_ISTAT1_Msk        (0x00000002UL)
#define R_INTC_IA55_ISCR_ISTAT1_Pos        (1UL)
#define R_INTC_IA55_ISCR_ISTAT2_Msk        (0x00000004UL)
#define R_INTC_IA55_ISCR_ISTAT2_Pos        (2UL)
#define R_INTC_IA55_ISCR_ISTAT3_Msk        (0x00000008UL)
#define R_INTC_IA55_ISCR_ISTAT3_Pos        (3UL)
#define R_INTC_IA55_ISCR_ISTAT4_Msk        (0x00000010UL)
#define R_INTC_IA55_ISCR_ISTAT4_Pos        (4UL)
#define R_INTC_IA55_ISCR_ISTAT5_Msk        (0x00000020UL)
#define R_INTC_IA55_ISCR_ISTAT5_Pos        (5UL)
#define R_INTC_IA55_ISCR_ISTAT6_Msk        (0x00000040UL)
#define R_INTC_IA55_ISCR_ISTAT6_Pos        (6UL)
#define R_INTC_IA55_ISCR_ISTAT7_Msk        (0x00000080UL)
#define R_INTC_IA55_ISCR_ISTAT7_Pos        (7UL)
#define R_INTC_IA55_IITSR_IITSEL0_Msk      (0x00000003UL)
#define R_INTC_IA55_IITSR_IITSEL0_Pos      (0UL)
#define R_INTC_IA55_IITSR_IITSEL1_Msk      (0x0000000CUL)
#define R_INTC_IA55_IITSR_IITSEL1_Pos      (2UL)
#define R_INTC_IA55_IITSR_IITSEL2_Msk      (0x00000030UL)
#define R_INTC_IA55_IITSR_IITSEL2_Pos      (4UL)
#define R_INTC_IA55_IITSR_IITSEL3_Msk      (0x000000C0UL)
#define R_INTC_IA55_IITSR_IITSEL3_Pos      (6UL)
#define R_INTC_IA55_IITSR_IITSEL4_Msk      (0x00000300UL)
#define R_INTC_IA55_IITSR_IITSEL4_Pos      (8UL)
#define R_INTC_IA55_IITSR_IITSEL5_Msk      (0x00000C00UL)
#define R_INTC_IA55_IITSR_IITSEL5_Pos      (10UL)
#define R_INTC_IA55_IITSR_IITSEL6_Msk      (0x00003000UL)
#define R_INTC_IA55_IITSR_IITSEL6_Pos      (12UL)
#define R_INTC_IA55_IITSR_IITSEL7_Msk      (0x0000C000UL)
#define R_INTC_IA55_IITSR_IITSEL7_Pos      (14UL)
#define R_INTC_IA55_TSCR_TSTAT0_Msk        (0x00000001UL)
#define R_INTC_IA55_TSCR_TSTAT0_Pos        (0UL)
#define R_INTC_IA55_TSCR_TSTAT1_Msk        (0x00000002UL)
#define R_INTC_IA55_TSCR_TSTAT1_Pos        (1UL)
#define R_INTC_IA55_TSCR_TSTAT2_Msk        (0x00000004UL)
#define R_INTC_IA55_TSCR_TSTAT2_Pos        (2UL)
#define R_INTC_IA55_TSCR_TSTAT3_Msk        (0x00000008UL)
#define R_INTC_IA55_TSCR_TSTAT3_Pos        (3UL)
#define R_INTC_IA55_TSCR_TSTAT4_Msk        (0x00000010UL)
#define R_INTC_IA55_TSCR_TSTAT4_Pos        (4UL)
#define R_INTC_IA55_TSCR_TSTAT5_Msk        (0x00000020UL)
#define R_INTC_IA55_TSCR_TSTAT5_Pos        (5UL)
#define R_INTC_IA55_TSCR_TSTAT6_Msk        (0x00000040UL)
#define R_INTC_IA55_TSCR_TSTAT6_Pos        (6UL)
#define R_INTC_IA55_TSCR_TSTAT7_Msk        (0x00000080UL)
#define R_INTC_IA55_TSCR_TSTAT7_Pos        (7UL)
#define R_INTC_IA55_TSCR_TSTAT8_Msk        (0x00000100UL)
#define R_INTC_IA55_TSCR_TSTAT8_Pos        (8UL)
#define R_INTC_IA55_TSCR_TSTAT9_Msk        (0x00000200UL)
#define R_INTC_IA55_TSCR_TSTAT9_Pos        (9UL)
#define R_INTC_IA55_TSCR_TSTAT10_Msk       (0x00000400UL)
#define R_INTC_IA55_TSCR_TSTAT10_Pos       (10UL)
#define R_INTC_IA55_TSCR_TSTAT11_Msk       (0x00000800UL)
#define R_INTC_IA55_TSCR_TSTAT11_Pos       (11UL)
#define R_INTC_IA55_TSCR_TSTAT12_Msk       (0x00001000UL)
#define R_INTC_IA55_TSCR_TSTAT12_Pos       (12UL)
#define R_INTC_IA55_TSCR_TSTAT13_Msk       (0x00002000UL)
#define R_INTC_IA55_TSCR_TSTAT13_Pos       (13UL)
#define R_INTC_IA55_TSCR_TSTAT14_Msk       (0x00004000UL)
#define R_INTC_IA55_TSCR_TSTAT14_Pos       (14UL)
#define R_INTC_IA55_TSCR_TSTAT15_Msk       (0x00008000UL)
#define R_INTC_IA55_TSCR_TSTAT15_Pos       (15UL)
#define R_INTC_IA55_TSCR_TSTAT16_Msk       (0x00010000UL)
#define R_INTC_IA55_TSCR_TSTAT16_Pos       (16UL)
#define R_INTC_IA55_TSCR_TSTAT17_Msk       (0x00020000UL)
#define R_INTC_IA55_TSCR_TSTAT17_Pos       (17UL)
#define R_INTC_IA55_TSCR_TSTAT18_Msk       (0x00040000UL)
#define R_INTC_IA55_TSCR_TSTAT18_Pos       (18UL)
#define R_INTC_IA55_TSCR_TSTAT19_Msk       (0x00080000UL)
#define R_INTC_IA55_TSCR_TSTAT19_Pos       (19UL)
#define R_INTC_IA55_TSCR_TSTAT20_Msk       (0x00100000UL)
#define R_INTC_IA55_TSCR_TSTAT20_Pos       (20UL)
#define R_INTC_IA55_TSCR_TSTAT21_Msk       (0x00200000UL)
#define R_INTC_IA55_TSCR_TSTAT21_Pos       (21UL)
#define R_INTC_IA55_TSCR_TSTAT22_Msk       (0x00400000UL)
#define R_INTC_IA55_TSCR_TSTAT22_Pos       (22UL)
#define R_INTC_IA55_TSCR_TSTAT23_Msk       (0x00800000UL)
#define R_INTC_IA55_TSCR_TSTAT23_Pos       (23UL)
#define R_INTC_IA55_TSCR_TSTAT24_Msk       (0x01000000UL)
#define R_INTC_IA55_TSCR_TSTAT24_Pos       (24UL)
#define R_INTC_IA55_TSCR_TSTAT25_Msk       (0x02000000UL)
#define R_INTC_IA55_TSCR_TSTAT25_Pos       (25UL)
#define R_INTC_IA55_TSCR_TSTAT26_Msk       (0x04000000UL)
#define R_INTC_IA55_TSCR_TSTAT26_Pos       (26UL)
#define R_INTC_IA55_TSCR_TSTAT27_Msk       (0x08000000UL)
#define R_INTC_IA55_TSCR_TSTAT27_Pos       (27UL)
#define R_INTC_IA55_TSCR_TSTAT28_Msk       (0x10000000UL)
#define R_INTC_IA55_TSCR_TSTAT28_Pos       (28UL)
#define R_INTC_IA55_TSCR_TSTAT29_Msk       (0x20000000UL)
#define R_INTC_IA55_TSCR_TSTAT29_Pos       (29UL)
#define R_INTC_IA55_TSCR_TSTAT30_Msk       (0x40000000UL)
#define R_INTC_IA55_TSCR_TSTAT30_Pos       (30UL)
#define R_INTC_IA55_TSCR_TSTAT31_Msk       (0x80000000UL)
#define R_INTC_IA55_TSCR_TSTAT31_Pos       (31UL)
#define R_INTC_IA55_TITSR0_TITSEL0_Msk     (0x00000003UL)
#define R_INTC_IA55_TITSR0_TITSEL0_Pos     (0UL)
#define R_INTC_IA55_TITSR0_TITSEL1_Msk     (0x0000000CUL)
#define R_INTC_IA55_TITSR0_TITSEL1_Pos     (2UL)
#define R_INTC_IA55_TITSR0_TITSEL2_Msk     (0x00000030UL)
#define R_INTC_IA55_TITSR0_TITSEL2_Pos     (4UL)
#define R_INTC_IA55_TITSR0_TITSEL3_Msk     (0x000000C0UL)
#define R_INTC_IA55_TITSR0_TITSEL3_Pos     (6UL)
#define R_INTC_IA55_TITSR0_TITSEL4_Msk     (0x00000300UL)
#define R_INTC_IA55_TITSR0_TITSEL4_Pos     (8UL)
#define R_INTC_IA55_TITSR0_TITSEL5_Msk     (0x00000C00UL)
#define R_INTC_IA55_TITSR0_TITSEL5_Pos     (10UL)
#define R_INTC_IA55_TITSR0_TITSEL6_Msk     (0x00003000UL)
#define R_INTC_IA55_TITSR0_TITSEL6_Pos     (12UL)
#define R_INTC_IA55_TITSR0_TITSEL7_Msk     (0x0000C000UL)
#define R_INTC_IA55_TITSR0_TITSEL7_Pos     (14UL)
#define R_INTC_IA55_TITSR0_TITSEL8_Msk     (0x00030000UL)
#define R_INTC_IA55_TITSR0_TITSEL8_Pos     (16UL)
#define R_INTC_IA55_TITSR0_TITSEL9_Msk     (0x000C0000UL)
#define R_INTC_IA55_TITSR0_TITSEL9_Pos     (18UL)
#define R_INTC_IA55_TITSR0_TITSEL10_Msk    (0x00300000UL)
#define R_INTC_IA55_TITSR0_TITSEL10_Pos    (20UL)
#define R_INTC_IA55_TITSR0_TITSEL11_Msk    (0x00C00000UL)
#define R_INTC_IA55_TITSR0_TITSEL11_Pos    (22UL)
#define R_INTC_IA55_TITSR0_TITSEL12_Msk    (0x03000000UL)
#define R_INTC_IA55_TITSR0_TITSEL12_Pos    (24UL)
#define R_INTC_IA55_TITSR0_TITSEL13_Msk    (0x0C000000UL)
#define R_INTC_IA55_TITSR0_TITSEL13_Pos    (26UL)
#define R_INTC_IA55_TITSR0_TITSEL14_Msk    (0x30000000UL)
#define R_INTC_IA55_TITSR0_TITSEL14_Pos    (28UL)
#define R_INTC_IA55_TITSR0_TITSEL15_Msk    (0xC0000000UL)
#define R_INTC_IA55_TITSR0_TITSEL15_Pos    (30UL)
#define R_INTC_IA55_TITSR1_TITSEL16_Msk    (0x00000003UL)
#define R_INTC_IA55_TITSR1_TITSEL16_Pos    (0UL)
#define R_INTC_IA55_TITSR1_TITSEL17_Msk    (0x0000000CUL)
#define R_INTC_IA55_TITSR1_TITSEL17_Pos    (2UL)
#define R_INTC_IA55_TITSR1_TITSEL18_Msk    (0x00000030UL)
#define R_INTC_IA55_TITSR1_TITSEL18_Pos    (4UL)
#define R_INTC_IA55_TITSR1_TITSEL19_Msk    (0x000000C0UL)
#define R_INTC_IA55_TITSR1_TITSEL19_Pos    (6UL)
#define R_INTC_IA55_TITSR1_TITSEL20_Msk    (0x00000300UL)
#define R_INTC_IA55_TITSR1_TITSEL20_Pos    (8UL)
#define R_INTC_IA55_TITSR1_TITSEL21_Msk    (0x00000C00UL)
#define R_INTC_IA55_TITSR1_TITSEL21_Pos    (10UL)
#define R_INTC_IA55_TITSR1_TITSEL22_Msk    (0x00003000UL)
#define R_INTC_IA55_TITSR1_TITSEL22_Pos    (12UL)
#define R_INTC_IA55_TITSR1_TITSEL23_Msk    (0x0000C000UL)
#define R_INTC_IA55_TITSR1_TITSEL23_Pos    (14UL)
#define R_INTC_IA55_TITSR1_TITSEL24_Msk    (0x00030000UL)
#define R_INTC_IA55_TITSR1_TITSEL24_Pos    (16UL)
#define R_INTC_IA55_TITSR1_TITSEL25_Msk    (0x000C0000UL)
#define R_INTC_IA55_TITSR1_TITSEL25_Pos    (18UL)
#define R_INTC_IA55_TITSR1_TITSEL26_Msk    (0x00300000UL)
#define R_INTC_IA55_TITSR1_TITSEL26_Pos    (20UL)
#define R_INTC_IA55_TITSR1_TITSEL27_Msk    (0x00C00000UL)
#define R_INTC_IA55_TITSR1_TITSEL27_Pos    (22UL)
#define R_INTC_IA55_TITSR1_TITSEL28_Msk    (0x03000000UL)
#define R_INTC_IA55_TITSR1_TITSEL28_Pos    (24UL)
#define R_INTC_IA55_TITSR1_TITSEL29_Msk    (0x0C000000UL)
#define R_INTC_IA55_TITSR1_TITSEL29_Pos    (26UL)
#define R_INTC_IA55_TITSR1_TITSEL30_Msk    (0x30000000UL)
#define R_INTC_IA55_TITSR1_TITSEL30_Pos    (28UL)
#define R_INTC_IA55_TITSR1_TITSEL31_Msk    (0xC0000000UL)
#define R_INTC_IA55_TITSR1_TITSEL31_Pos    (30UL)
#define R_INTC_IA55_TSSR0_TSSEL0_Msk       (0x0000007FUL)
#define R_INTC_IA55_TSSR0_TSSEL0_Pos       (0UL)
#define R_INTC_IA55_TSSR0_TIEN0_Msk        (0x00000080UL)
#define R_INTC_IA55_TSSR0_TIEN0_Pos        (7UL)
#define R_INTC_IA55_TSSR0_TSSEL1_Msk       (0x00007F00UL)
#define R_INTC_IA55_TSSR0_TSSEL1_Pos       (8UL)
#define R_INTC_IA55_TSSR0_TIEN1_Msk        (0x00008000UL)
#define R_INTC_IA55_TSSR0_TIEN1_Pos        (15UL)
#define R_INTC_IA55_TSSR0_TSSEL2_Msk       (0x007F0000UL)
#define R_INTC_IA55_TSSR0_TSSEL2_Pos       (16UL)
#define R_INTC_IA55_TSSR0_TIEN2_Msk        (0x00800000UL)
#define R_INTC_IA55_TSSR0_TIEN2_Pos        (23UL)
#define R_INTC_IA55_TSSR0_TSSEL3_Msk       (0x7F000000UL)
#define R_INTC_IA55_TSSR0_TSSEL3_Pos       (24UL)
#define R_INTC_IA55_TSSR0_TIEN3_Msk        (0x80000000UL)
#define R_INTC_IA55_TSSR0_TIEN3_Pos        (31UL)
#define R_INTC_IA55_TSSR1_TSSEL4_Msk       (0x0000007FUL)
#define R_INTC_IA55_TSSR1_TSSEL4_Pos       (0UL)
#define R_INTC_IA55_TSSR1_TIEN4_Msk        (0x00000080UL)
#define R_INTC_IA55_TSSR1_TIEN4_Pos        (7UL)
#define R_INTC_IA55_TSSR1_TSSEL5_Msk       (0x00007F00UL)
#define R_INTC_IA55_TSSR1_TSSEL5_Pos       (8UL)
#define R_INTC_IA55_TSSR1_TIEN5_Msk        (0x00008000UL)
#define R_INTC_IA55_TSSR1_TIEN5_Pos        (15UL)
#define R_INTC_IA55_TSSR1_TSSEL6_Msk       (0x007F0000UL)
#define R_INTC_IA55_TSSR1_TSSEL6_Pos       (16UL)
#define R_INTC_IA55_TSSR1_TIEN6_Msk        (0x00800000UL)
#define R_INTC_IA55_TSSR1_TIEN6_Pos        (23UL)
#define R_INTC_IA55_TSSR1_TSSEL7_Msk       (0x7F000000UL)
#define R_INTC_IA55_TSSR1_TSSEL7_Pos       (24UL)
#define R_INTC_IA55_TSSR1_TIEN7_Msk        (0x80000000UL)
#define R_INTC_IA55_TSSR1_TIEN7_Pos        (31UL)
#define R_INTC_IA55_TSSR2_TSSEL8_Msk       (0x0000007FUL)
#define R_INTC_IA55_TSSR2_TSSEL8_Pos       (0UL)
#define R_INTC_IA55_TSSR2_TIEN8_Msk        (0x00000080UL)
#define R_INTC_IA55_TSSR2_TIEN8_Pos        (7UL)
#define R_INTC_IA55_TSSR2_TSSEL9_Msk       (0x00007F00UL)
#define R_INTC_IA55_TSSR2_TSSEL9_Pos       (8UL)
#define R_INTC_IA55_TSSR2_TIEN9_Msk        (0x00008000UL)
#define R_INTC_IA55_TSSR2_TIEN9_Pos        (15UL)
#define R_INTC_IA55_TSSR2_TSSEL10_Msk      (0x007F0000UL)
#define R_INTC_IA55_TSSR2_TSSEL10_Pos      (16UL)
#define R_INTC_IA55_TSSR2_TIEN10_Msk       (0x00800000UL)
#define R_INTC_IA55_TSSR2_TIEN10_Pos       (23UL)
#define R_INTC_IA55_TSSR2_TSSEL11_Msk      (0x7F000000UL)
#define R_INTC_IA55_TSSR2_TSSEL11_Pos      (24UL)
#define R_INTC_IA55_TSSR2_TIEN11_Msk       (0x80000000UL)
#define R_INTC_IA55_TSSR2_TIEN11_Pos       (31UL)
#define R_INTC_IA55_TSSR3_TSSEL12_Msk      (0x0000007FUL)
#define R_INTC_IA55_TSSR3_TSSEL12_Pos      (0UL)
#define R_INTC_IA55_TSSR3_TIEN12_Msk       (0x00000080UL)
#define R_INTC_IA55_TSSR3_TIEN12_Pos       (7UL)
#define R_INTC_IA55_TSSR3_TSSEL13_Msk      (0x00007F00UL)
#define R_INTC_IA55_TSSR3_TSSEL13_Pos      (8UL)
#define R_INTC_IA55_TSSR3_TIEN13_Msk       (0x00008000UL)
#define R_INTC_IA55_TSSR3_TIEN13_Pos       (15UL)
#define R_INTC_IA55_TSSR3_TSSEL14_Msk      (0x007F0000UL)
#define R_INTC_IA55_TSSR3_TSSEL14_Pos      (16UL)
#define R_INTC_IA55_TSSR3_TIEN14_Msk       (0x00800000UL)
#define R_INTC_IA55_TSSR3_TIEN14_Pos       (23UL)
#define R_INTC_IA55_TSSR3_TSSEL15_Msk      (0x7F000000UL)
#define R_INTC_IA55_TSSR3_TSSEL15_Pos      (24UL)
#define R_INTC_IA55_TSSR3_TIEN15_Msk       (0x80000000UL)
#define R_INTC_IA55_TSSR3_TIEN15_Pos       (31UL)
#define R_INTC_IA55_TSSR4_TSSEL16_Msk      (0x0000007FUL)
#define R_INTC_IA55_TSSR4_TSSEL16_Pos      (0UL)
#define R_INTC_IA55_TSSR4_TIEN16_Msk       (0x00000080UL)
#define R_INTC_IA55_TSSR4_TIEN16_Pos       (7UL)
#define R_INTC_IA55_TSSR4_TSSEL17_Msk      (0x00007F00UL)
#define R_INTC_IA55_TSSR4_TSSEL17_Pos      (8UL)
#define R_INTC_IA55_TSSR4_TIEN17_Msk       (0x00008000UL)
#define R_INTC_IA55_TSSR4_TIEN17_Pos       (15UL)
#define R_INTC_IA55_TSSR4_TSSEL18_Msk      (0x007F0000UL)
#define R_INTC_IA55_TSSR4_TSSEL18_Pos      (16UL)
#define R_INTC_IA55_TSSR4_TIEN18_Msk       (0x00800000UL)
#define R_INTC_IA55_TSSR4_TIEN18_Pos       (23UL)
#define R_INTC_IA55_TSSR4_TSSEL19_Msk      (0x7F000000UL)
#define R_INTC_IA55_TSSR4_TSSEL19_Pos      (24UL)
#define R_INTC_IA55_TSSR4_TIEN19_Msk       (0x80000000UL)
#define R_INTC_IA55_TSSR4_TIEN19_Pos       (31UL)
#define R_INTC_IA55_TSSR5_TSSEL20_Msk      (0x0000007FUL)
#define R_INTC_IA55_TSSR5_TSSEL20_Pos      (0UL)
#define R_INTC_IA55_TSSR5_TIEN20_Msk       (0x00000080UL)
#define R_INTC_IA55_TSSR5_TIEN20_Pos       (7UL)
#define R_INTC_IA55_TSSR5_TSSEL21_Msk      (0x00007F00UL)
#define R_INTC_IA55_TSSR5_TSSEL21_Pos      (8UL)
#define R_INTC_IA55_TSSR5_TIEN21_Msk       (0x00008000UL)
#define R_INTC_IA55_TSSR5_TIEN21_Pos       (15UL)
#define R_INTC_IA55_TSSR5_TSSEL22_Msk      (0x007F0000UL)
#define R_INTC_IA55_TSSR5_TSSEL22_Pos      (16UL)
#define R_INTC_IA55_TSSR5_TIEN22_Msk       (0x00800000UL)
#define R_INTC_IA55_TSSR5_TIEN22_Pos       (23UL)
#define R_INTC_IA55_TSSR5_TSSEL23_Msk      (0x7F000000UL)
#define R_INTC_IA55_TSSR5_TSSEL23_Pos      (24UL)
#define R_INTC_IA55_TSSR5_TIEN23_Msk       (0x80000000UL)
#define R_INTC_IA55_TSSR5_TIEN23_Pos       (31UL)
#define R_INTC_IA55_TSSR6_TSSEL24_Msk      (0x0000007FUL)
#define R_INTC_IA55_TSSR6_TSSEL24_Pos      (0UL)
#define R_INTC_IA55_TSSR6_TIEN24_Msk       (0x00000080UL)
#define R_INTC_IA55_TSSR6_TIEN24_Pos       (7UL)
#define R_INTC_IA55_TSSR6_TSSEL25_Msk      (0x00007F00UL)
#define R_INTC_IA55_TSSR6_TSSEL25_Pos      (8UL)
#define R_INTC_IA55_TSSR6_TIEN25_Msk       (0x00008000UL)
#define R_INTC_IA55_TSSR6_TIEN25_Pos       (15UL)
#define R_INTC_IA55_TSSR6_TSSEL26_Msk      (0x007F0000UL)
#define R_INTC_IA55_TSSR6_TSSEL26_Pos      (16UL)
#define R_INTC_IA55_TSSR6_TIEN26_Msk       (0x00800000UL)
#define R_INTC_IA55_TSSR6_TIEN26_Pos       (23UL)
#define R_INTC_IA55_TSSR6_TSSEL27_Msk      (0x7F000000UL)
#define R_INTC_IA55_TSSR6_TSSEL27_Pos      (24UL)
#define R_INTC_IA55_TSSR6_TIEN27_Msk       (0x80000000UL)
#define R_INTC_IA55_TSSR6_TIEN27_Pos       (31UL)
#define R_INTC_IA55_TSSR7_TSSEL28_Msk      (0x0000007FUL)
#define R_INTC_IA55_TSSR7_TSSEL28_Pos      (0UL)
#define R_INTC_IA55_TSSR7_TIEN28_Msk       (0x00000080UL)
#define R_INTC_IA55_TSSR7_TIEN28_Pos       (7UL)
#define R_INTC_IA55_TSSR7_TSSEL29_Msk      (0x00007F00UL)
#define R_INTC_IA55_TSSR7_TSSEL29_Pos      (8UL)
#define R_INTC_IA55_TSSR7_TIEN29_Msk       (0x00008000UL)
#define R_INTC_IA55_TSSR7_TIEN29_Pos       (15UL)
#define R_INTC_IA55_TSSR7_TSSEL30_Msk      (0x007F0000UL)
#define R_INTC_IA55_TSSR7_TSSEL30_Pos      (16UL)
#define R_INTC_IA55_TSSR7_TIEN30_Msk       (0x00800000UL)
#define R_INTC_IA55_TSSR7_TIEN30_Pos       (23UL)
#define R_INTC_IA55_TSSR7_TSSEL31_Msk      (0x7F000000UL)
#define R_INTC_IA55_TSSR7_TSSEL31_Pos      (24UL)
#define R_INTC_IA55_TSSR7_TIEN31_Msk       (0x80000000UL)
#define R_INTC_IA55_TSSR7_TIEN31_Pos       (31UL)
#define R_INTC_IA55_BEISR0_BESTAT0_Msk     (0x00000001UL)
#define R_INTC_IA55_BEISR0_BESTAT0_Pos     (0UL)
#define R_INTC_IA55_BEISR0_BESTAT1_Msk     (0x00000002UL)
#define R_INTC_IA55_BEISR0_BESTAT1_Pos     (1UL)
#define R_INTC_IA55_BEISR0_BESTAT2_Msk     (0x00000004UL)
#define R_INTC_IA55_BEISR0_BESTAT2_Pos     (2UL)
#define R_INTC_IA55_BEISR0_BESTAT3_Msk     (0x00000008UL)
#define R_INTC_IA55_BEISR0_BESTAT3_Pos     (3UL)
#define R_INTC_IA55_BEISR0_BESTAT4_Msk     (0x00000010UL)
#define R_INTC_IA55_BEISR0_BESTAT4_Pos     (4UL)
#define R_INTC_IA55_BEISR0_BESTAT5_Msk     (0x00000020UL)
#define R_INTC_IA55_BEISR0_BESTAT5_Pos     (5UL)
#define R_INTC_IA55_BEISR0_BESTAT6_Msk     (0x00000040UL)
#define R_INTC_IA55_BEISR0_BESTAT6_Pos     (6UL)
#define R_INTC_IA55_BEISR0_BESTAT7_Msk     (0x00000080UL)
#define R_INTC_IA55_BEISR0_BESTAT7_Pos     (7UL)
#define R_INTC_IA55_BEISR0_BESTAT8_Msk     (0x00000100UL)
#define R_INTC_IA55_BEISR0_BESTAT8_Pos     (8UL)
#define R_INTC_IA55_BEISR0_BESTAT9_Msk     (0x00000200UL)
#define R_INTC_IA55_BEISR0_BESTAT9_Pos     (9UL)
#define R_INTC_IA55_BEISR0_BESTAT10_Msk    (0x00000400UL)
#define R_INTC_IA55_BEISR0_BESTAT10_Pos    (10UL)
#define R_INTC_IA55_BEISR0_BESTAT11_Msk    (0x00000800UL)
#define R_INTC_IA55_BEISR0_BESTAT11_Pos    (11UL)
#define R_INTC_IA55_BEISR0_BESTAT12_Msk    (0x00001000UL)
#define R_INTC_IA55_BEISR0_BESTAT12_Pos    (12UL)
#define R_INTC_IA55_BEISR0_BESTAT13_Msk    (0x00002000UL)
#define R_INTC_IA55_BEISR0_BESTAT13_Pos    (13UL)
#define R_INTC_IA55_BEISR0_BESTAT14_Msk    (0x00004000UL)
#define R_INTC_IA55_BEISR0_BESTAT14_Pos    (14UL)
#define R_INTC_IA55_BEISR0_BESTAT15_Msk    (0x00008000UL)
#define R_INTC_IA55_BEISR0_BESTAT15_Pos    (15UL)
#define R_INTC_IA55_BEISR0_BESTAT16_Msk    (0x00010000UL)
#define R_INTC_IA55_BEISR0_BESTAT16_Pos    (16UL)
#define R_INTC_IA55_BEISR0_BESTAT17_Msk    (0x00020000UL)
#define R_INTC_IA55_BEISR0_BESTAT17_Pos    (17UL)
#define R_INTC_IA55_BEISR0_BESTAT18_Msk    (0x00040000UL)
#define R_INTC_IA55_BEISR0_BESTAT18_Pos    (18UL)
#define R_INTC_IA55_BEISR0_BESTAT19_Msk    (0x00080000UL)
#define R_INTC_IA55_BEISR0_BESTAT19_Pos    (19UL)
#define R_INTC_IA55_BEISR0_BESTAT20_Msk    (0x00100000UL)
#define R_INTC_IA55_BEISR0_BESTAT20_Pos    (20UL)
#define R_INTC_IA55_BEISR0_BESTAT21_Msk    (0x00200000UL)
#define R_INTC_IA55_BEISR0_BESTAT21_Pos    (21UL)
#define R_INTC_IA55_BEISR0_BESTAT22_Msk    (0x00400000UL)
#define R_INTC_IA55_BEISR0_BESTAT22_Pos    (22UL)
#define R_INTC_IA55_BEISR0_BESTAT23_Msk    (0x00800000UL)
#define R_INTC_IA55_BEISR0_BESTAT23_Pos    (23UL)
#define R_INTC_IA55_BEISR0_BESTAT24_Msk    (0x01000000UL)
#define R_INTC_IA55_BEISR0_BESTAT24_Pos    (24UL)
#define R_INTC_IA55_BEISR0_BESTAT25_Msk    (0x02000000UL)
#define R_INTC_IA55_BEISR0_BESTAT25_Pos    (25UL)
#define R_INTC_IA55_BEISR0_BESTAT26_Msk    (0x04000000UL)
#define R_INTC_IA55_BEISR0_BESTAT26_Pos    (26UL)
#define R_INTC_IA55_BEISR0_BESTAT27_Msk    (0x08000000UL)
#define R_INTC_IA55_BEISR0_BESTAT27_Pos    (27UL)
#define R_INTC_IA55_BEISR0_BESTAT28_Msk    (0x10000000UL)
#define R_INTC_IA55_BEISR0_BESTAT28_Pos    (28UL)
#define R_INTC_IA55_BEISR0_BESTAT29_Msk    (0x20000000UL)
#define R_INTC_IA55_BEISR0_BESTAT29_Pos    (29UL)
#define R_INTC_IA55_BEISR0_BESTAT30_Msk    (0x40000000UL)
#define R_INTC_IA55_BEISR0_BESTAT30_Pos    (30UL)
#define R_INTC_IA55_BEISR0_BESTAT31_Msk    (0x80000000UL)
#define R_INTC_IA55_BEISR0_BESTAT31_Pos    (31UL)
#define R_INTC_IA55_BEISR1_BESTAT32_Msk    (0x00000001UL)
#define R_INTC_IA55_BEISR1_BESTAT32_Pos    (0UL)
#define R_INTC_IA55_BEISR1_BESTAT33_Msk    (0x00000002UL)
#define R_INTC_IA55_BEISR1_BESTAT33_Pos    (1UL)
#define R_INTC_IA55_BEISR1_BESTAT34_Msk    (0x00000004UL)
#define R_INTC_IA55_BEISR1_BESTAT34_Pos    (2UL)
#define R_INTC_IA55_BEISR1_BESTAT35_Msk    (0x00000008UL)
#define R_INTC_IA55_BEISR1_BESTAT35_Pos    (3UL)
#define R_INTC_IA55_BEISR1_BESTAT36_Msk    (0x00000010UL)
#define R_INTC_IA55_BEISR1_BESTAT36_Pos    (4UL)
#define R_INTC_IA55_BEISR1_BESTAT37_Msk    (0x00000020UL)
#define R_INTC_IA55_BEISR1_BESTAT37_Pos    (5UL)
#define R_INTC_IA55_BEISR1_BESTAT38_Msk    (0x00000040UL)
#define R_INTC_IA55_BEISR1_BESTAT38_Pos    (6UL)
#define R_INTC_IA55_BEISR1_BESTAT39_Msk    (0x00000080UL)
#define R_INTC_IA55_BEISR1_BESTAT39_Pos    (7UL)
#define R_INTC_IA55_BEISR1_BESTAT40_Msk    (0x00000100UL)
#define R_INTC_IA55_BEISR1_BESTAT40_Pos    (8UL)
#define R_INTC_IA55_BEISR1_BESTAT41_Msk    (0x00000200UL)
#define R_INTC_IA55_BEISR1_BESTAT41_Pos    (9UL)
#define R_INTC_IA55_BEISR1_BESTAT42_Msk    (0x00000400UL)
#define R_INTC_IA55_BEISR1_BESTAT42_Pos    (10UL)
#define R_INTC_IA55_BEISR1_BESTAT43_Msk    (0x00000800UL)
#define R_INTC_IA55_BEISR1_BESTAT43_Pos    (11UL)
#define R_INTC_IA55_BEISR1_BESTAT44_Msk    (0x00001000UL)
#define R_INTC_IA55_BEISR1_BESTAT44_Pos    (12UL)
#define R_INTC_IA55_EREISR0_E1STAT0_Msk    (0x00000001UL)
#define R_INTC_IA55_EREISR0_E1STAT0_Pos    (0UL)
#define R_INTC_IA55_EREISR0_E1STAT1_Msk    (0x00000002UL)
#define R_INTC_IA55_EREISR0_E1STAT1_Pos    (1UL)
#define R_INTC_IA55_EREISR0_E1STAT2_Msk    (0x00000004UL)
#define R_INTC_IA55_EREISR0_E1STAT2_Pos    (2UL)
#define R_INTC_IA55_EREISR0_E1STAT3_Msk    (0x00000008UL)
#define R_INTC_IA55_EREISR0_E1STAT3_Pos    (3UL)
#define R_INTC_IA55_EREISR0_E1STAT4_Msk    (0x00000010UL)
#define R_INTC_IA55_EREISR0_E1STAT4_Pos    (4UL)
#define R_INTC_IA55_EREISR0_E1STAT5_Msk    (0x00000020UL)
#define R_INTC_IA55_EREISR0_E1STAT5_Pos    (5UL)
#define R_INTC_IA55_EREISR0_E1STAT6_Msk    (0x00000040UL)
#define R_INTC_IA55_EREISR0_E1STAT6_Pos    (6UL)
#define R_INTC_IA55_EREISR0_E1STAT7_Msk    (0x00000080UL)
#define R_INTC_IA55_EREISR0_E1STAT7_Pos    (7UL)
#define R_INTC_IA55_EREISR0_E2STAT0_Msk    (0x00000100UL)
#define R_INTC_IA55_EREISR0_E2STAT0_Pos    (8UL)
#define R_INTC_IA55_EREISR0_E2STAT1_Msk    (0x00000200UL)
#define R_INTC_IA55_EREISR0_E2STAT1_Pos    (9UL)
#define R_INTC_IA55_EREISR0_E2STAT2_Msk    (0x00000400UL)
#define R_INTC_IA55_EREISR0_E2STAT2_Pos    (10UL)
#define R_INTC_IA55_EREISR0_E2STAT3_Msk    (0x00000800UL)
#define R_INTC_IA55_EREISR0_E2STAT3_Pos    (11UL)
#define R_INTC_IA55_EREISR0_E2STAT4_Msk    (0x00001000UL)
#define R_INTC_IA55_EREISR0_E2STAT4_Pos    (12UL)
#define R_INTC_IA55_EREISR0_E2STAT5_Msk    (0x00002000UL)
#define R_INTC_IA55_EREISR0_E2STAT5_Pos    (13UL)
#define R_INTC_IA55_EREISR0_E2STAT6_Msk    (0x00004000UL)
#define R_INTC_IA55_EREISR0_E2STAT6_Pos    (14UL)
#define R_INTC_IA55_EREISR0_E2STAT7_Msk    (0x00008000UL)
#define R_INTC_IA55_EREISR0_E2STAT7_Pos    (15UL)
#define R_INTC_IA55_EREISR0_OFSTAT0_Msk    (0x00010000UL)
#define R_INTC_IA55_EREISR0_OFSTAT0_Pos    (16UL)
#define R_INTC_IA55_EREISR0_OFSTAT1_Msk    (0x00020000UL)
#define R_INTC_IA55_EREISR0_OFSTAT1_Pos    (17UL)
#define R_INTC_IA55_EREISR0_OFSTAT2_Msk    (0x00040000UL)
#define R_INTC_IA55_EREISR0_OFSTAT2_Pos    (18UL)
#define R_INTC_IA55_EREISR0_OFSTAT3_Msk    (0x00080000UL)
#define R_INTC_IA55_EREISR0_OFSTAT3_Pos    (19UL)
#define R_INTC_IA55_EREISR0_OFSTAT4_Msk    (0x00100000UL)
#define R_INTC_IA55_EREISR0_OFSTAT4_Pos    (20UL)
#define R_INTC_IA55_EREISR0_OFSTAT5_Msk    (0x00200000UL)
#define R_INTC_IA55_EREISR0_OFSTAT5_Pos    (21UL)
#define R_INTC_IA55_EREISR0_OFSTAT6_Msk    (0x00400000UL)
#define R_INTC_IA55_EREISR0_OFSTAT6_Pos    (22UL)
#define R_INTC_IA55_EREISR0_OFSTAT7_Msk    (0x00800000UL)
#define R_INTC_IA55_EREISR0_OFSTAT7_Pos    (23UL)
#define R_INTC_IA55_EREISR1_E1STAT0_Msk    (0x00000001UL)
#define R_INTC_IA55_EREISR1_E1STAT0_Pos    (0UL)
#define R_INTC_IA55_EREISR1_E1STAT1_Msk    (0x00000002UL)
#define R_INTC_IA55_EREISR1_E1STAT1_Pos    (1UL)
#define R_INTC_IA55_EREISR1_E1STAT2_Msk    (0x00000004UL)
#define R_INTC_IA55_EREISR1_E1STAT2_Pos    (2UL)
#define R_INTC_IA55_EREISR1_E1STAT3_Msk    (0x00000008UL)
#define R_INTC_IA55_EREISR1_E1STAT3_Pos    (3UL)
#define R_INTC_IA55_EREISR1_E1STAT4_Msk    (0x00000010UL)
#define R_INTC_IA55_EREISR1_E1STAT4_Pos    (4UL)
#define R_INTC_IA55_EREISR1_E1STAT5_Msk    (0x00000020UL)
#define R_INTC_IA55_EREISR1_E1STAT5_Pos    (5UL)
#define R_INTC_IA55_EREISR1_E1STAT6_Msk    (0x00000040UL)
#define R_INTC_IA55_EREISR1_E1STAT6_Pos    (6UL)
#define R_INTC_IA55_EREISR1_E1STAT7_Msk    (0x00000080UL)
#define R_INTC_IA55_EREISR1_E1STAT7_Pos    (7UL)
#define R_INTC_IA55_EREISR1_E2STAT0_Msk    (0x00000100UL)
#define R_INTC_IA55_EREISR1_E2STAT0_Pos    (8UL)
#define R_INTC_IA55_EREISR1_E2STAT1_Msk    (0x00000200UL)
#define R_INTC_IA55_EREISR1_E2STAT1_Pos    (9UL)
#define R_INTC_IA55_EREISR1_E2STAT2_Msk    (0x00000400UL)
#define R_INTC_IA55_EREISR1_E2STAT2_Pos    (10UL)
#define R_INTC_IA55_EREISR1_E2STAT3_Msk    (0x00000800UL)
#define R_INTC_IA55_EREISR1_E2STAT3_Pos    (11UL)
#define R_INTC_IA55_EREISR1_E2STAT4_Msk    (0x00001000UL)
#define R_INTC_IA55_EREISR1_E2STAT4_Pos    (12UL)
#define R_INTC_IA55_EREISR1_E2STAT5_Msk    (0x00002000UL)
#define R_INTC_IA55_EREISR1_E2STAT5_Pos    (13UL)
#define R_INTC_IA55_EREISR1_E2STAT6_Msk    (0x00004000UL)
#define R_INTC_IA55_EREISR1_E2STAT6_Pos    (14UL)
#define R_INTC_IA55_EREISR1_E2STAT7_Msk    (0x00008000UL)
#define R_INTC_IA55_EREISR1_E2STAT7_Pos    (15UL)
#define R_INTC_IA55_EREISR1_OFSTAT0_Msk    (0x00010000UL)
#define R_INTC_IA55_EREISR1_OFSTAT0_Pos    (16UL)
#define R_INTC_IA55_EREISR1_OFSTAT1_Msk    (0x00020000UL)
#define R_INTC_IA55_EREISR1_OFSTAT1_Pos    (17UL)
#define R_INTC_IA55_EREISR1_OFSTAT2_Msk    (0x00040000UL)
#define R_INTC_IA55_EREISR1_OFSTAT2_Pos    (18UL)
#define R_INTC_IA55_EREISR1_OFSTAT3_Msk    (0x00080000UL)
#define R_INTC_IA55_EREISR1_OFSTAT3_Pos    (19UL)
#define R_INTC_IA55_EREISR1_OFSTAT4_Msk    (0x00100000UL)
#define R_INTC_IA55_EREISR1_OFSTAT4_Pos    (20UL)
#define R_INTC_IA55_EREISR1_OFSTAT5_Msk    (0x00200000UL)
#define R_INTC_IA55_EREISR1_OFSTAT5_Pos    (21UL)
#define R_INTC_IA55_EREISR1_OFSTAT6_Msk    (0x00400000UL)
#define R_INTC_IA55_EREISR1_OFSTAT6_Pos    (22UL)
#define R_INTC_IA55_EREISR1_OFSTAT7_Msk    (0x00800000UL)
#define R_INTC_IA55_EREISR1_OFSTAT7_Pos    (23UL)

#endif                                 /* INTC_IA55_IOBITMASK_H */

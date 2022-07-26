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
 * File Name    : wdt_iobitmask.h
 * Version      : 1.00
 * Description  : IO bit mask file for wdt.
 *********************************************************************************************************************/

#ifndef WDT_IOBITMASK_H
#define WDT_IOBITMASK_H

#define R_WDT0_WDTCNT_WDTEN_Msk      (0x00000001UL)
#define R_WDT0_WDTCNT_WDTEN_Pos      (0UL)
#define R_WDT0_WDTSET_WDTTIME_Msk    (0xFFF00000UL)
#define R_WDT0_WDTSET_WDTTIME_Pos    (20UL)
#define R_WDT0_WDTTIM_CRTTIME_Msk    (0xFFFFFFFFUL)
#define R_WDT0_WDTTIM_CRTTIME_Pos    (0UL)
#define R_WDT0_WDTINT_INTDISP_Msk    (0x00000001UL)
#define R_WDT0_WDTINT_INTDISP_Pos    (0UL)
#define R_WDT0_PECR_PECR_Msk         (0xFFFFFFFFUL)
#define R_WDT0_PECR_PECR_Pos         (0UL)
#define R_WDT0_PEEN_PEEN_Msk         (0x00000001UL)
#define R_WDT0_PEEN_PEEN_Pos         (0UL)
#define R_WDT0_PESR_PESR_Msk         (0xFFFFFFFFUL)
#define R_WDT0_PESR_PESR_Pos         (0UL)
#define R_WDT0_PEER_PEER_Msk         (0xFFFFFFFFUL)
#define R_WDT0_PEER_PEER_Pos         (0UL)
#define R_WDT0_PEPO_PEPO_Msk         (0xFFFFFFFFUL)
#define R_WDT0_PEPO_PEPO_Pos         (0UL)

#endif                                 /* WDT_IOBITMASK_H */

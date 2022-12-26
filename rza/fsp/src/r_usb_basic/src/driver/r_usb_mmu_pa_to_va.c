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

/***********************************************************************************************************************
 * File Name    : r_usb_MMU_va_to_pa.c
 * Description  : USB Host MSC application code
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 31.08.2015 1.00    First Release
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "stdint.h"
#include "hal_data.h"
#include "r_mmu.h"

/***********************************************************************************************************************
 * Constant macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

uint64_t r_usb_pa_to_va(uint64_t paddr);
uint64_t r_usb_va_to_pa(uint64_t vaddr);
uint64_t r_usb_readtbl(uint64_t address);

/******************************************************************************
 * Function Name: r_usb_pa_to_va
 * Description  : Convert physical address to virtual address
 * Arguments    : uint32_t   paddr  ; I : physical address to be convert
 * Return Value : virtual address
 ******************************************************************************/
uint64_t r_usb_pa_to_va (uint64_t paddr)
{
    uint64_t vaddr;

#if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT)
    R_MMU_PAtoVA(&g_mmu_ctrl, paddr, &vaddr);
#else                                  /* #if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT) */
    vaddr = paddr;
#endif /* #if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT) */

    return vaddr;
}                                      /* End of function r_usb_pa_to_va() */

/******************************************************************************
 * End of function usb_serial_input
 ******************************************************************************/

/******************************************************************************
 * Function Name: r_usb_va_to_pa
 * Description  : Convert virtual address to physical address
 * Arguments    : uint32_t   vaddress  ; I : virtual address to be convert
 *              : uint32_t * paddress  ; O : physical address
 * Return Value : MMU_SUCCESS         : successful
 *                MMU_ERR_TRANSLATION : translation error
 ******************************************************************************/
uint64_t r_usb_va_to_pa (uint64_t vaddr)
{
    uint64_t paddr;

#if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT)
    R_MMU_VAtoPA(&g_mmu_ctrl, vaddr, &paddr);
#else                                  /* #if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT) */
    paddr = vaddr;
#endif /* #if (BSP_FEATURE_BSP_HAS_MMU_SUPPORT) */

    return paddr;
}

/******************************************************************************
 * End of function R_MMU_VAtoPA
 ******************************************************************************/

/***********************************************************************************************************************
 * End  Of File
 ***********************************************************************************************************************/

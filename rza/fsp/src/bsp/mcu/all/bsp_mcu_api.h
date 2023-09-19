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

#ifndef BSP_MCU_API_H
#define BSP_MCU_API_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
fsp_err_t R_BSP_GroupIrqWrite(bsp_grp_irq_t irq, void (* p_callback)(bsp_grp_irq_t irq));
void      R_BSP_SoftwareDelay(uint32_t delay, bsp_delay_units_t units) __attribute__((section("FASTCODE")));

/***********************************************************************************************************************
 * function prototype
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Initialize interrupt controller.
 *
 **********************************************************************************************************************/
void InitGicv3(void);

/*******************************************************************************************************************//**
 * Enable exception.
 *
 **********************************************************************************************************************/
void __enable_all_exception(void);

/*******************************************************************************************************************//**
 * Enable fiq.
 *
 **********************************************************************************************************************/
void __enable_fiq(void);

/*******************************************************************************************************************//**
 * Disable fiq.
 *
 **********************************************************************************************************************/
void __disable_fiq(void);

/*******************************************************************************************************************//**
 * FIQ handler.
 *
 **********************************************************************************************************************/
void FIQ_ExecuteHandler(void);

/*******************************************************************************************************************//**
 * IRQ handler.
 *
 **********************************************************************************************************************/
void IRQ_ExecuteHandler(void);

/*******************************************************************************************************************//**
 * Enables instruction cache.
 *
 **********************************************************************************************************************/
unsigned long long R_BSP_CACHE_EnableInst(void);

/*******************************************************************************************************************//**
 * Enables data cache.
 *
 **********************************************************************************************************************/
unsigned long long R_BSP_CACHE_EnableData(void);

/*******************************************************************************************************************//**
 * Disables instruction cache.
 *
 **********************************************************************************************************************/
unsigned long long R_BSP_CACHE_DisableInst(void);

/*******************************************************************************************************************//**
 * Disables data cache.
 *
 **********************************************************************************************************************/
unsigned long long R_BSP_CACHE_DisableData(void);

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Clean whole cache.
 *
 * Execute DC CSW instruction for all set/way of cache.
 *
 * @note DC CSW instructions in AArch64 perform both a clean and invalidate of the target set/way.
 **********************************************************************************************************************/
void R_BSP_CACHE_CleanAll(void);

/*******************************************************************************************************************//**
 * Clean&Invalidate whole cache.
 *
 * Execute DC CISW instruction for all set/way of cache.
 **********************************************************************************************************************/
void R_BSP_CACHE_CleanInvalidateAll(void);

/*******************************************************************************************************************//**
 * Invalidate whole cache.
 *
 * Execute DC ISW instruction for all set/way of cache.
 *
 * @note DC ISW instructions in AArch64 perform both a clean and invalidate of the target set/way.
 **********************************************************************************************************************/
void R_BSP_CACHE_InvalidateAll(void);

/*******************************************************************************************************************//**
 * Cache Clean by MVA.
 *
 * @param[in]     base_address      start address (Must be a 4-byte aligned address)
 * @param[in]     length            number of bytes (Must be a multiple of 4)
 *
 * Executes DC CVAC and IC IVAU instruction for cache lines within the specified address range.
 **********************************************************************************************************************/
void R_BSP_CACHE_CleanRange(uint64_t base_address, uint64_t length);

/*******************************************************************************************************************//**
 * Cache Invalidate by MVA.
 *
 * @param[in]     base_address      start address (Must be a 4-byte aligned address)
 * @param[in]     length            number of bytes (Must be a multiple of 4)
 *
 * Executes DC IVAC and IC IVAU instruction for cache lines within the specified address range.
 *
 * @note DC IVAC instructions in AArch64 perform both a clean and invalidate.
 **********************************************************************************************************************/
void R_BSP_CACHE_InvalidateRange(uint64_t base_address, uint64_t length);

/*******************************************************************************************************************//**
 * Cache Clean&Invalidate by MVA.
 *
 * @param[in]     base_address      start address (Must be a 4-byte aligned address)
 * @param[in]     length            number of bytes (Must be a multiple of 4)
 *
 * Executes DC CIVAC and IC IVAU instruction for cache lines within the specified address range.
 **********************************************************************************************************************/
void R_BSP_CACHE_CleanInvalidateRange(uint64_t base_address, uint64_t length);

/** @} (end addtogroup BSP_MCU) */

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

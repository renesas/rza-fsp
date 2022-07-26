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
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_clocks.h"

#if BSP_TZ_NONSECURE_BUILD
 #include "bsp_guard.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The number of clocks is used to size the g_clock_freq array. */
#define BSP_PRV_NUM_CLOCKS    (FSP_PRIV_CLOCK_NUM)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/* This array stores the clock frequency of each bus clock. This section of RAM should not be initialized by the C
 * runtime environment. This is initialized and used in bsp_clock_init, which is called before the C runtime
 * environment is initialized. */
static uint32_t g_clock_freq[BSP_PRV_NUM_CLOCKS] =
{
    BSP_CFG_CLOCK_ICLK_HZ,             /* Initial value of Cortex-A55 Clock */
    BSP_CFG_CLOCK_I2CLK_HZ,            /* Initial value of Cortex-M33 Clock */
    BSP_CFG_CLOCK_S0CLK_HZ,            /* Initial value of DDR-PHY Clock */
    BSP_CFG_CLOCK_SPI0CLK_HZ,          /* Initial value of SPI0 Clock */
    BSP_CFG_CLOCK_SPI1CLK_HZ,          /* Initial value of SPI1 Clock */
    BSP_CFG_CLOCK_OC0CLK_HZ,           /* Initial value of OC0 Clock */
    BSP_CFG_CLOCK_OC1CLK_HZ,           /* Initial value of OC1 Clock */
    BSP_CFG_CLOCK_SD0CLK_HZ,           /* Initial value of SDH0 Clock */
    BSP_CFG_CLOCK_SD1CLK_HZ,           /* Initial value of SDH1 Clock */
    BSP_CFG_CLOCK_M0CLK_HZ,            /* Initial value of VCP, LCDC Clock */
    BSP_CFG_CLOCK_M2CLK_HZ,            /* Initial value of CRU, MIPI-DSI Clock */
    BSP_CFG_CLOCK_M3CLK_HZ,            /* Initial value of MIPI-DSI, LCDC Clock */
    BSP_CFG_CLOCK_HPCLK_HZ,            /* Initial value of Ethernet Clock */
    BSP_CFG_CLOCK_TSUCLK_HZ,           /* Initial value of TSU Clock */
    BSP_CFG_CLOCK_ZTCLK_HZ,            /* Initial value of JAUTH Clock */
    BSP_CFG_CLOCK_P0CLK_HZ,            /* Initial value of APB-BUS Clock */
    BSP_CFG_CLOCK_P1CLK_HZ,            /* Initial value of AXI-BUS Clock */
    BSP_CFG_CLOCK_P2CLK_HZ,            /* Initial value of P2CLK */
    BSP_CFG_CLOCK_ATCLK_HZ,            /* Initial value of ATCLK */
    BSP_CFG_CLOCK_OSCCLK_HZ,           /* Initial value of OSC Clock */
};

/*******************************************************************************************************************//**
 * Update SystemCoreClock variable based on current clock settings.
 **********************************************************************************************************************/
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = g_clock_freq[FSP_PRIV_CLOCK_ICLK];
}

/*******************************************************************************************************************//**
 * Initializes variable to store system clock frequencies.
 **********************************************************************************************************************/
#if BSP_TZ_CFG_INIT_SECURE_ONLY
void bsp_clock_freq_var_init(void);

void bsp_clock_freq_var_init (void)
#else
static void bsp_clock_freq_var_init (void)
#endif
{
    g_clock_freq[FSP_PRIV_CLOCK_ICLK]    = BSP_CFG_CLOCK_ICLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_I2CLK]   = BSP_CFG_CLOCK_I2CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_S0CLK]   = BSP_CFG_CLOCK_S0CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_SPI0CLK] = BSP_CFG_CLOCK_SPI0CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_SPI1CLK] = BSP_CFG_CLOCK_SPI1CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_OC0CLK]  = BSP_CFG_CLOCK_OC0CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_OC1CLK]  = BSP_CFG_CLOCK_OC1CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_SD0CLK]  = BSP_CFG_CLOCK_SD0CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_SD1CLK]  = BSP_CFG_CLOCK_SD1CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_M0CLK]   = BSP_CFG_CLOCK_M0CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_M2CLK]   = BSP_CFG_CLOCK_M2CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_M3CLK]   = BSP_CFG_CLOCK_M3CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_HPCLK]   = BSP_CFG_CLOCK_HPCLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_TSUCLK]  = BSP_CFG_CLOCK_TSUCLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_ZTCLK]   = BSP_CFG_CLOCK_ZTCLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_P0CLK]   = BSP_CFG_CLOCK_P0CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_P1CLK]   = BSP_CFG_CLOCK_P1CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_P2CLK]   = BSP_CFG_CLOCK_P2CLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_ATCLK]   = BSP_CFG_CLOCK_ATCLK_HZ;
    g_clock_freq[FSP_PRIV_CLOCK_OSCCLK]  = BSP_CFG_CLOCK_OSCCLK_HZ;

    /* The SystemCoreClock needs to be updated before calling R_BSP_SoftwareDelay. */
    SystemCoreClockUpdate();
}

/*******************************************************************************************************************//**
 * Initializes system clocks.  Makes no assumptions about current register settings.
 **********************************************************************************************************************/
void bsp_clock_init (void)
{
    bsp_clock_freq_var_init();

    /* Stop unnecessary clocks to reduce power consumption. */
    bsp_clock_off();

#if BSP_FEATURE_CPG_HAS_ICLK

    /* ICLK setting */
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL1_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL1_STS_Pos,
                               0U);
    R_CPG->CPG_PL1_DDIV = (uint32_t) (R_CPG_CPG_PL1_DDIV_DIV_PLL1SET_WEN_Msk | \
                                      (R_CPG_CPG_PL1_DDIV_DIVPL1_SET_Msk &     \
                                       (BSP_CFG_DIVPL1_SET_DIV << R_CPG_CPG_PL1_DDIV_DIVPL1_SET_Pos)));
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL1_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL1_STS_Pos,
                               0U);
#endif

#if BSP_FEATURE_CPG_HAS_SD0CLK

    /* SD0CLK setting */
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_SELSDHI0_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_SELSDHI0_STS_Pos,
                               0U);
    R_CPG->CPG_PL2SDHI_DSEL = (uint32_t) (R_CPG_CPG_PL2SDHI_DSEL_SEL_SDHI0_WEN_Msk |  \
                                          (R_CPG_CPG_PL2SDHI_DSEL_SEL_SDHI0_SET_Msk & \
                                           (BSP_CFG_SEL_SDHI0_SET_SOURCE << R_CPG_CPG_PL2SDHI_DSEL_SEL_SDHI0_SET_Pos)));
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_SELSDHI0_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_SELSDHI0_STS_Pos,
                               0U);
#endif

#if BSP_FEATURE_CPG_HAS_SD1CLK

    /* SD1CLK setting */
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_SELSDHI1_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_SELSDHI1_STS_Pos,
                               0U);
    R_CPG->CPG_PL2SDHI_DSEL = (uint32_t) (R_CPG_CPG_PL2SDHI_DSEL_SEL_SDHI1_WEN_Msk |  \
                                          (R_CPG_CPG_PL2SDHI_DSEL_SEL_SDHI1_SET_Msk & \
                                           (BSP_CFG_SEL_SDHI1_SET_SOURCE << R_CPG_CPG_PL2SDHI_DSEL_SEL_SDHI1_SET_Pos)));
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_SELSDHI1_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_SELSDHI1_STS_Pos,
                               0U);
#endif

#if BSP_FEATURE_CPG_HAS_P0CLK

    /* P0CLK setting */
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL2A_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL2A_STS_Pos,
                               0U);
    R_CPG->CPG_PL2_DDIV = (uint32_t) (R_CPG_CPG_PL2_DDIV_DIV_PLL2_A_WEN_Msk | \
                                      (R_CPG_CPG_PL2_DDIV_DIVPL2A_SET_Msk &   \
                                       (BSP_CFG_DIVPL2A_SET_DIV << R_CPG_CPG_PL2_DDIV_DIVPL2A_SET_Pos)));
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL2A_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL2A_STS_Pos,
                               0U);
#endif

#if BSP_FEATURE_CPG_HAS_P1CLK

    /* P1CLK setting */
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL3B_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL3B_STS_Pos,
                               0U);
    R_CPG->CPG_PL3A_DDIV = (uint32_t) (R_CPG_CPG_PL3A_DDIV_DIV_PLL3_B_WEN_Msk | \
                                       (R_CPG_CPG_PL3A_DDIV_DIVPL3B_SET_Msk &   \
                                        (BSP_CFG_DIVPL3B_SET_DIV << R_CPG_CPG_PL3A_DDIV_DIVPL3B_SET_Pos)));
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL3B_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL3B_STS_Pos,
                               0U);
#endif

#if BSP_FEATURE_CPG_HAS_P2CLK

    /* P2CLK setting */
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL3A_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL3A_STS_Pos,
                               0U);
    R_CPG->CPG_PL3A_DDIV = (uint32_t) (R_CPG_CPG_PL3A_DDIV_DIV_PLL3_A_WEN_Msk | \
                                       (R_CPG_CPG_PL3A_DDIV_DIVPL3A_SET_Msk &   \
                                        (BSP_CFG_DIVPL3A_SET_DIV << R_CPG_CPG_PL3A_DDIV_DIVPL3A_SET_Pos)));
    FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL3A_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                               R_CPG_CPG_CLKSTATUS_DIVPL3A_STS_Pos,
                               0U);
#endif

#if BSP_FEATURE_CPG_HAS_I2CLK

    /* I2CLK setting */
    if ((BSP_CFG_DIVPL3CLK200FIX_SET_DIV << R_CPG_CPG_PL3B_DDIV_DIVPL3CLK200FIX_SET_Pos) != R_CPG->CPG_PL3B_DDIV)
    {
        FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL3CLK200FIX_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                                   R_CPG_CPG_CLKSTATUS_DIVPL3CLK200FIX_STS_Pos,
                                   0U);
        R_CPG->CPG_PL3B_DDIV = (uint32_t) (R_CPG_CPG_PL3B_DDIV_DIV_PLL3_CLK200FIX_WEN_Msk | \
                                           (R_CPG_CPG_PL3B_DDIV_DIVPL3CLK200FIX_SET_Msk &   \
                                            (BSP_CFG_DIVPL3CLK200FIX_SET_DIV <<
                                             R_CPG_CPG_PL3B_DDIV_DIVPL3CLK200FIX_SET_Pos)));
        FSP_HARDWARE_REGISTER_WAIT((R_CPG_CPG_CLKSTATUS_DIVPL3CLK200FIX_STS_Msk & R_CPG->CPG_CLKSTATUS) >> \
                                   R_CPG_CPG_CLKSTATUS_DIVPL3CLK200FIX_STS_Pos,
                                   0U);
    }
    else
    {
        /* Do nothing when the value which want to set and the value of CPG_PL3B_DDIV register is equal.*/
    }
#endif

#if BSP_FEATURE_CPG_HAS_M3CLK

    /* M3CLK setting  */
    R_CPG->CPG_PL5_SDIV = (uint32_t) (R_CPG_CPG_PL5_SDIV_DIV_DSI_A_WEN_Msk | \
                                      (R_CPG_CPG_PL5_SDIV_DIVDSIA_SET_Msk &  \
                                       (BSP_CFG_DIVDSIA_SET_DIV << R_CPG_CPG_PL5_SDIV_DIVDSIA_SET_Pos)));
#endif

#if BSP_FEATURE_CPG_HAS_HPCLK

    /* HPCLK setting  */
    R_CPG->CPG_PL6_ETH_SSEL = (uint32_t) (R_CPG_CPG_PL6_ETH_SSEL_SEL_PLL6_2_WEN_Msk |  \
                                          (R_CPG_CPG_PL6_ETH_SSEL_SEL_PLL6_2_SET_Msk & \
                                           (BSP_CFG_SEL_PLL6_2_SET_SOURCE <<
                                            R_CPG_CPG_PL6_ETH_SSEL_SEL_PLL6_2_SET_Pos)));
#endif
}

/** @} (end addtogroup BSP_MCU_PRV) */

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Get the system clock frequency.
 *
 * @param[in]   clock                 Element number of the array that defines the frequency of the bus clock.
 *
 * @retval      g_clock_freq[clock]   System clock frequency.
 **********************************************************************************************************************/
uint32_t R_FSP_SystemClockHzGet (fsp_priv_clock_t clock)
{
    return g_clock_freq[clock];
}

/** @} (end addtogroup BSP_MCU_PRV) */

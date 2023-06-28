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

#ifndef BSP_MODULE_H
#define BSP_MODULE_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Cancels the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be started
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MSTP_START(ip, channel)             {FSP_CRITICAL_SECTION_DEFINE;                                      \
                                                   FSP_CRITICAL_SECTION_ENTER;                                       \
                                                   BSP_MSTP_REG_ ## ip(channel) = 0x00000000U                        \
                                                                                  | (BSP_MSTP_BIT_ ## ip(channel) << \
                                                                                     16U);                           \
                                                   BSP_MSTP_REG_ ## ip(channel);                                     \
                                                   FSP_CRITICAL_SECTION_EXIT;}

/*******************************************************************************************************************//**
 * Enables the module stop state.
 *
 * @param      ip       fsp_ip_t enum value for the module to be stopped
 * @param      channel  The channel. Use channel 0 for modules without channels.
 **********************************************************************************************************************/
#define R_BSP_MSTP_STOP(ip, channel)              {FSP_CRITICAL_SECTION_DEFINE;                                      \
                                                   FSP_CRITICAL_SECTION_ENTER;                                       \
                                                   BSP_MSTP_REG_ ## ip(channel) = 0x0000FFFFU                        \
                                                                                  | (BSP_MSTP_BIT_ ## ip(channel) << \
                                                                                     16U);                           \
                                                   BSP_MSTP_REG_ ## ip(channel);                                     \
                                                   FSP_CRITICAL_SECTION_EXIT;}

/** @} (end addtogroup BSP_MCU) */

#define BSP_MSTP_REG_FSP_IP_ADC(channel)          (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_ADC(channel)          (1U << (R_MSTP_MCPU2_MPADC_Pos))

#define BSP_MSTP_REG_FSP_IP_CANFD(channel)        (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_CANFD(channel)        (1U << (R_MSTP_MCPU2_MPCANFD_Pos))

#define BSP_MSTP_REG_FSP_IP_CRU(channel)          (R_MSTP->PERI_VIDEO)
#define BSP_MSTP_BIT_FSP_IP_CRU(channel)          (7U << (R_MSTP_PERI_VIDEO_MPCRU_Pos))

#define BSP_MSTP_REG_FSP_IP_CST(channel)          (R_MSTP->PERI_CPU)
#define BSP_MSTP_BIT_FSP_IP_CST(channel)          (1U << (R_MSTP_PERI_CPU_MPCST_Pos))

#define BSP_MSTP_REG_FSP_IP_DMAC_NS(channel)      (R_MSTP->REG1)
#define BSP_MSTP_BIT_FSP_IP_DMAC_NS(channel)      (3U << (R_MSTP_REG1_MXDMAC_NS_Pos))

#define BSP_MSTP_REG_FSP_IP_DMAC_S(channel)       (R_MSTP->REG1)
#define BSP_MSTP_BIT_FSP_IP_DMAC_S(channel)       (3U << (R_MSTP_REG1_MXDMAC_S_Pos))

#define BSP_MSTP_REG_FSP_IP_ETHER(channel)        (R_MSTP->PERI_COM)
#define BSP_MSTP_BIT_FSP_IP_ETHER(channel)        (1U << (R_MSTP_PERI_COM_MPGIGE0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_GIC(channel)          (R_MSTP->REG1)
#define BSP_MSTP_BIT_FSP_IP_GIC(channel)          (1U << (R_MSTP_REG1_MXGIC_Pos))

#define BSP_MSTP_REG_FSP_IP_GTM(channel)          (R_MSTP->REG0)
#define BSP_MSTP_BIT_FSP_IP_GTM(channel)          (1U << (R_MSTP_REG0_MPOSTM0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_IA55(channel)         (R_MSTP->PERI_CPU)
#define BSP_MSTP_BIT_FSP_IP_IA55(channel)         (1U << (R_MSTP_PERI_CPU_MPIA55_Pos))

#define BSP_MSTP_REG_FSP_IP_IRDA(channel)         (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_IRDA(channel)         (1U << (R_MSTP_MCPU2_MHIRDA_Pos))

#define BSP_MSTP_REG_FSP_IP_ISU(channel)          (R_MSTP->PERI_VIDEO)
#define BSP_MSTP_BIT_FSP_IP_ISU(channel)          (1U << (R_MSTP_PERI_VIDEO_MPISU_Pos))

#define BSP_MSTP_REG_FSP_IP_LCDC(channel)         (R_MSTP->PERI_VIDEO)
#define BSP_MSTP_BIT_FSP_IP_LCDC(channel)         (7U << (R_MSTP_PERI_VIDEO_MPVSPD_Pos))

#define BSP_MSTP_REG_FSP_IP_MTU3(channel)         (R_MSTP->MCPU1)
#define BSP_MSTP_BIT_FSP_IP_MTU3(channel)         (1U << (R_MSTP_MCPU1_MHMTU3A_Pos))

#define BSP_MSTP_REG_FSP_IP_OCTA(channel)         (R_MSTP->MCPU3)
#define BSP_MSTP_BIT_FSP_IP_OCTA(channel)         (1U << (R_MSTP_MCPU3_MXOCTA_Pos))

#define BSP_MSTP_REG_FSP_IP_POE3(channel)         (R_MSTP->MCPU1)
#define BSP_MSTP_BIT_FSP_IP_POE3(channel)         (1U << (R_MSTP_MCPU1_MHPOE3_Pos))

#define BSP_MSTP_REG_FSP_IP_RIIC(channel)         (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_RIIC(channel)         (1U << (R_MSTP_MCPU2_MPI2C0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_RSPI(channel)         (R_MSTP->MCPU1)
#define BSP_MSTP_BIT_FSP_IP_RSPI(channel)         (1U << (R_MSTP_MCPU1_MHRSPI0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_SCI(channel)          (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)          (1U << (R_MSTP_MCPU2_MHSCI0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_SCIF(channel)         (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_SCIF(channel)         (1U << (R_MSTP_MCPU2_MHSCIF0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_SDHI(channel)         (R_MSTP->PERI_COM)
#define BSP_MSTP_BIT_FSP_IP_SDHI(channel)         (1U << (R_MSTP_PERI_COM_MXSDHI0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_SPI_MULTI(channel)    (R_MSTP->MCPU1)
#define BSP_MSTP_BIT_FSP_IP_SPI_MULTI(channel)    (1U << (R_MSTP_MCPU1_MHSPI_Pos))

#define BSP_MSTP_REG_FSP_IP_SSI(channel)          (R_MSTP->MCPU1)
#define BSP_MSTP_BIT_FSP_IP_SSI(channel)          (1U << (R_MSTP_MCPU1_MHSSIF0_Pos + (channel)))

#define BSP_MSTP_REG_FSP_IP_SYC(channel)          (R_MSTP->PERI_CPU)
#define BSP_MSTP_BIT_FSP_IP_SYC(channel)          (1U << (R_MSTP_PERI_CPU_MPSYC_Pos))

#define BSP_MSTP_REG_FSP_IP_TSU(channel)          (R_MSTP->MCPU2)
#define BSP_MSTP_BIT_FSP_IP_TSU(channel)          (1U << (R_MSTP_MCPU2_MPTSU_Pos))

#define BSP_MSTP_REG_FSP_IP_USB0(channel)         (R_MSTP->PERI_COM)
#define BSP_MSTP_BIT_FSP_IP_USB0(channel)         (3U << (R_MSTP_PERI_COM_MHUSB2H_Pos))

#define BSP_MSTP_REG_FSP_IP_USB1(channel)         (R_MSTP->PERI_COM)
#define BSP_MSTP_BIT_FSP_IP_USB1(channel)         (1U << (R_MSTP_PERI_COM_MHUSB21_Pos))

#define BSP_MSTP_REG_FSP_IP_USBPHY(channel)       (R_MSTP->PERI_COM)
#define BSP_MSTP_BIT_FSP_IP_USBPHY(channel)       (1U << (R_MSTP_PERI_COM_MPUSBT_Pos))

#define BSP_MSTP_REG_FSP_IP_WDT(channel)          (R_MSTP->REG0)
#define BSP_MSTP_BIT_FSP_IP_WDT(channel)          (1U << (R_MSTP_REG0_MPWDT0_Pos))

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

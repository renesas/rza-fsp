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

#ifndef BSP_FEATURE_H
#define BSP_FEATURE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#define BSP_FEATURE_ADC_VALID_CHANNEL_MASK           (0xF)
#define BSP_FEATURE_ADC_NUM_CALIBRATION_DATA         (2U)
#define BSP_FEATURE_ADC_NUM_CHANNELS                 (2U)

#define BSP_FEATURE_BSP_HAS_MMU_SUPPORT              (1)

#define BSP_FEATURE_CANFD_NUM_CHANNELS               (2U)

#define BSP_FEATURE_CPG_HAS_ICLK                     (1U)
#define BSP_FEATURE_CPG_HAS_SD0CLK                   (1U)
#define BSP_FEATURE_CPG_HAS_SD1CLK                   (1U)
#define BSP_FEATURE_CPG_HAS_P0CLK                    (1U)
#define BSP_FEATURE_CPG_HAS_P1CLK                    (1U)
#define BSP_FEATURE_CPG_HAS_P2CLK                    (1U)
#define BSP_FEATURE_CPG_HAS_I2CLK                    (1U)
#define BSP_FEATURE_CPG_HAS_M3CLK                    (1U)
#define BSP_FEATURE_CPG_HAS_HPCLK                    (1U)

#define BSP_FEATURE_BSP_HAS_ELC                      (0U)

#define BSP_FEATURE_BSP_SUPPORT_SD_VOLT              (1U)
#define BSP_FEATURE_BSP_SUPPORT_ETHER_VOLT           (1U)
#define BSP_FEATURE_BSP_SUPPORT_ETHER_MODE           (1U)
#define BSP_FEATURE_BSP_SUPPORT_QSPI_VOLT            (1U)
#define BSP_FEATURE_BSP_SUPPORT_XSPI_VOLT            (0U)
#define BSP_FEATURE_BSP_SUPPORT_XSPI_OUTPUT          (0U)
#define BSP_FEATURE_BSP_SUPPORT_I3C                  (0U)
#define BSP_FEATURE_BSP_SUPPORT_BYPASS               (0U)
#define BSP_FEATURE_BSP_SUPPORT_PFCWE_PROTECT        (1U)
#define BSP_FEATURE_BSP_SUPPORT_OEN_PROTECT          (0U)
#define BSP_FEATURE_BSP_HAS_PFC_OEN_REG              (0U)
#define BSP_FEATURE_BSP_HAS_ETHER_MODE_REG           (0U)
#define BSP_FEATURE_BSP_HAS_SD_CH_POC_REG            (0U)
#define BSP_FEATURE_BSP_HAS_ETH_POC_REG              (0U)

#define BSP_FEATURE_CRU_MAX_CHANNELS                 (1U)

#define BSP_FEATURE_DMAC_MAX_CHANNEL                 (16U)

#define BSP_FEATURE_GTM_MAX_CHANNELS                 (3U)
#define BSP_FEATURE_GTM_VALID_CHANNEL_MASK           (0x7)

#define BSP_FEATURE_IIC_VALID_CHANNEL_MASK           (0x0F)
#define BSP_FEATURE_IIC_REGISTER_SIZE_BY_BIT         (32)

#define BSP_FEATURE_INTC_IRQ_VALID_CHANNEL_MASK      (0xFFU)
#define BSP_FEATURE_INTC_TINT_VALID_CHANNEL_MASK     (0xFFFFFFFFU)

#define BSP_FEATURE_IOPORT_SUPPORT_SR_REG            (1U)
#define BSP_FEATURE_IOPORT_GP_REG_BASE_NUM           10
#define BSP_FEATURE_IOPORT_SP_REG_BASE_NUM           2
#define BSP_FEATURE_IOPORT_FIL_SP_REG_BASE_NUM       01
#define BSP_FEATURE_IOPORT_IEN_SP_REG_BASE_NUM       02
#define BSP_FEATURE_IOPORT_IOLH_SP_REG_BASE_NUM      02
#define BSP_FEATURE_IOPORT_SR_SP_REG_BASE_NUM        02
#define BSP_FEATURE_IOPORT_GP_REG_BASE_NUM           10

#define BSP_FEATURE_IRDA_MAX_CHANNELS                (1U)

#define BSP_FEATURE_ISU_MAX_CHANNELS                 (1U)

#define BSP_FEATURE_LCDC_MAX_CHANNELS                (1U)

#define BSP_FEATURE_MTU3_VALID_CHANNEL_MASK          (0x01FF)
#define BSP_FEATURE_MTU3_MAX_CHANNELS                (9U)
#define BSP_FEATURE_MTU3_UVW_MAX_CHANNELS            (3U)

#define BSP_FEATURE_RIIC_MAX_CHANNELS                (4U)

#define BSP_FEATURE_RSPI_VALID_CHANNELS_MASK         (0x7)
#define BSP_FEATURE_RSPI_CLOCK                       (FSP_PRIV_CLOCK_P0CLK)
#define BSP_FEATURE_RSPI_MAX_CHANNELS                (3U)
#define BSP_FEATURE_RSPI_CLK_MAX_DIV                 (4096U)
#define BSP_FEATURE_RSPI_CLK_MIN_DIV                 (4U)

#define BSP_FEATURE_SDHI_VALID_CHANNEL_MASK          (0x3)
#define BSP_FEATURE_SDHI_MAX_CHANNELS                (2U)
#define BSP_FEATURE_SDHI_MIN_CLOCK_DIVISION_SHIFT    (0U)

#define BSP_FEATURE_SCI_CHANNELS                     (0x03U)
#define BSP_FEATURE_SCI_UART_CSTPEN_CHANNELS         (0U)
#define BSP_FEATURE_SCI_CLOCK                        (FSP_PRIV_CLOCK_P0CLK)
#define BSP_FEATURE_SCI_MAX_CHANNELS                 (2U)

#define BSP_FEATURE_SCIF_CHANNELS                    (0x1FU)
#define BSP_FEATURE_SCIF_CHANNELS_HAS_RTSCTS         (0x07U)
#define BSP_FEATURE_SCIF_CLOCK                       (FSP_PRIV_CLOCK_P0CLK)
#define BSP_FEATURE_SCIF_MAX_CHANNELS                (5U)

#define BSP_FEATURE_SSI_FIFO_NUM_STAGES              (32U)
#define BSP_FEATURE_SSI_VALID_CHANNEL_MASK           (0x0FU)
#define BSP_FEATURE_SSI_MAX_CHANNELS                 (4U)

#define BSP_FEATURE_CANFD_FD_SUPPORT                 (1U)
#define BSP_FEATURE_CANFD_NUM_INSTANCES              (1U)

#define BSP_FEATURE_TSU_MAX_CHANNELS                 (1U)

#define BSP_FEATURE_GETHER_MAX_CHANNELS              (2U)

#define BSP_FEATURE_WDT_MAX_CHANNELS                 (1U)

#define BSP_FEATURE_TZ_HAS_TRUSTZONE                 (0U)

#endif                                 /* BSP_FEATURE_H */

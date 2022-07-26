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
 * File Name    : bsp_irq_id.h
 * Version      : 1.00
 * Description  : bsp_irq_id header
 *********************************************************************************************************************/

#ifndef BSP_IRQ_ID_H
#define BSP_IRQ_ID_H

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * @addtogroup BSP_MPU_RZA3UL
 * @{
 *********************************************************************************************************************/

typedef enum IRQn
{
    Reset_IRQn            = -15,
    NonMaskableInt_IRQn   = -14,
    HardFault_IRQn        = -13,
    MemoryManagement_IRQn = -12,
    BusFault_IRQn         = -11,
    UsageFault_IRQn       = -10,
    SecureFault_IRQn      = -9,
    SVCall_IRQn           = -5,
    DebugMonitor_IRQn     = -4,
    PendSV_IRQn           = -2,
    SysTick_IRQn          = -1,

    SGI0_IRQn  = 0,                    /* Interrupt ID:0,  SGI0        */
    SGI1_IRQn  = 1,                    /* Interrupt ID:1,  SGI1        */
    SGI2_IRQn  = 2,                    /* Interrupt ID:2,  SGI2        */
    SGI3_IRQn  = 3,                    /* Interrupt ID:3,  SGI3        */
    SGI4_IRQn  = 4,                    /* Interrupt ID:4,  SGI4        */
    SGI5_IRQn  = 5,                    /* Interrupt ID:5,  SGI5        */
    SGI6_IRQn  = 6,                    /* Interrupt ID:6,  SGI6        */
    SGI7_IRQn  = 7,                    /* Interrupt ID:7,  SGI7        */
    SGI8_IRQn  = 8,                    /* Interrupt ID:8,  SGI8        */
    SGI9_IRQn  = 9,                    /* Interrupt ID:9,  SGI9        */
    SGI10_IRQn = 10,                   /* Interrupt ID:10,  SGI10      */
    SGI11_IRQn = 11,                   /* Interrupt ID:11,  SGI11      */
    SGI12_IRQn = 12,                   /* Interrupt ID:12,  SGI12      */
    SGI13_IRQn = 13,                   /* Interrupt ID:13,  SGI13      */
    SGI14_IRQn = 14,                   /* Interrupt ID:14,  SGI14      */
    SGI15_IRQn = 15,                   /* Interrupt ID:15,  SGI15      */
                                       /* Interrupt ID:16, Reserved */
                                       /* Interrupt ID:17, Reserved */
                                       /* Interrupt ID:18, Reserved */
                                       /* Interrupt ID:19, Reserved */
                                       /* Interrupt ID:20, Reserved */
                                       /* Interrupt ID:21, Reserved */
    COMM_PPI6_IRQn    = 22,            /* Interrupt ID:22,  nCOMMIRQ */
    PMU_PPI7_IRQn     = 23,            /* Interrupt ID:23,  nPMUIRQ  */
    CTI_PPI8_IRQn     = 24,            /* Interrupt ID:24,  CTIIRQ   */
    VCPUMNT_PPI9_IRQn = 25,            /* Interrupt ID:25,  nVCPUMNTIRQ */
    CNTHP_PPI10_IRQn  = 26,            /* Interrupt ID:26,  nCNTHPIRQ */
    CNTV_PPI11_IRQn   = 27,            /* Interrupt ID:27,  nCNTVRQ */
    CNTHV_PPI12_IRQn  = 28,            /* Interrupt ID:28,  nCNTHVIRQ */
    CNTPS_PPI13_IRQn  = 29,            /* Interrupt ID:29,  nCNTPSIRQ */
    CNTPNS_PPI14_IRQn = 30,            /* Interrupt ID:30,  nCNTPNSIRQ */
                                       /* Interrupt ID:31, Reserved */
    NMI_IRQn                = 32,      /* Interrupt ID:32,  NMI         */
    GPIO_IRQ0_IRQn          = 33,      /* Interrupt ID:33,  IRQ0        */
    GPIO_IRQ1_IRQn          = 34,      /* Interrupt ID:34,  IRQ1        */
    GPIO_IRQ2_IRQn          = 35,      /* Interrupt ID:35,  IRQ2        */
    GPIO_IRQ3_IRQn          = 36,      /* Interrupt ID:36,  IRQ3        */
    GPIO_IRQ4_IRQn          = 37,      /* Interrupt ID:37,  IRQ4        */
    GPIO_IRQ5_IRQn          = 38,      /* Interrupt ID:38,  IRQ5        */
    GPIO_IRQ6_IRQn          = 39,      /* Interrupt ID:39,  IRQ6        */
    GPIO_IRQ7_IRQn          = 40,      /* Interrupt ID:40,  IRQ7        */
    CA55_COMMIRQ1_IRQn      = 41,      /* Interrupt ID:41,  nCOMMIRQ[1] */
    CA55_COMMIRQ0_IRQn      = 42,      /* Interrupt ID:42, nCOMMIRQ[0] */
    CA55_PMUIRQ1_IRQn       = 43,      /* Interrupt ID:43, nPMUIRQ[1]  */
    CA55_PMUIRQ0_IRQn       = 44,      /* Interrupt ID:44, nPMUIRQ[0]  */
    CA55_CLUSTERPMUIRQ_IRQn = 45,      /* Interrupt ID:45, nCLUSTERPMUIRQ */
                                       /* Interrupt ID:46, Reserved */
    CA55_ERRIRQ1_IRQn = 47,            /* Interrupt ID:47, nERRIRQ[1] */
    CA55_ERRIRQ0_IRQn = 48,            /* Interrupt ID:48, nERRIRQ[0] */
                                       /* Interrupt ID:49, Reserved */
    CA55_FAULTIRQ1_IRQn = 50,          /* Interrupt ID:50, nFAULTIRQ[1] */
    CA55_FAULTIRQ0_IRQn = 51,          /* Interrupt ID:51, nFAULTIRQ[0] */
                                       /* Interrupt ID:52, Reserved */
                                       /* Interrupt ID:53, Reserved */
    GIC_FAULT_INT_IRQn         = 54,   /* Interrupt ID:54, fault_int */
    GIC_ERR_INT_IRQn           = 55,   /* Interrupt ID:55, err_int */
    GIC_PMU_INT_IRQn           = 56,   /* Interrupt ID:56, pmu_int */
    SYSTEMBUS_BUS_ERR_INT_IRQn = 57,   /* Interrupt ID:57, BUS_ERR_INTR_W_SXCA55 */
                                       /* Interrupt ID:58, Reserved */
                                       /* Interrupt ID:59, Reserved */
                                       /* Interrupt ID:60, Reserved */
                                       /* Interrupt ID:61, Reserved */
                                       /* Interrupt ID:62, Reserved */
                                       /* Interrupt ID:63, Reserved */
                                       /* Interrupt ID:64, Reserved */
                                       /* Interrupt ID:65, Reserved */
    ECCRAM0_EC7TIE1_IRQn  = 66,        /* Interrupt ID:66, ACPU EC7TIE1[0] */
    ECCRAM0_EC7TIE2_IRQn  = 67,        /* Interrupt ID:67, ACPU EC7TIE2[0] */
    ECCRAM0_EC7TIOVF_IRQn = 68,        /* Interrupt ID:68, ACPU EC7TIOVF[0] */
    ECCRAM1_EC7TIE1_IRQn  = 69,        /* Interrupt ID:69, MCPU EC7TIE1[0] */
    ECCRAM1_EC7TIE2_IRQn  = 70,        /* Interrupt ID:70, MCPU EC7TIE2[0] */
    ECCRAM1_EC7TIOVF_IRQn = 71,        /* Interrupt ID:71, MCPU EC7TIOVF[0] */
    DDR_CONTROLL_INT_IRQn = 72,        /* Interrupt ID:72, DDR3L/4 Interrupt signal from the controller */
                                       /* Interrupt ID:73, Reserved */
    SYSC_LPM_INT_IRQn          = 74,   /* Interrupt ID:74, SYS_LPM_INT */
    SYSC_CA55STBYDONE_INT_IRQn = 75,   /* Interrupt ID:75, SYS_CA55STBYDONE_INT */
                                       /* Interrupt ID:76, Reserved */
    SYSC_CA55_DENY_IRQn  = 77,         /* Interrupt ID:77, SYS_CA55_DENY */
    GTM0_OSTM0INT_IRQn   = 78,         /* Interrupt ID:78, General Timer ch 0 Interrupt signal */
    GTM1_OSTM1INT_IRQn   = 79,         /* Interrupt ID:79, General Timer ch 1 Interrupt signal */
    GTM2_OSTM2INT_IRQn   = 80,         /* Interrupt ID:80, General Timer ch 2 Interrupt signal */
    WDT0_WDTINT_A0_IRQn  = 81,         /* Interrupt ID:81, CA55 core 0 WDTINT  */
    WDT0_PERROUT_A0_IRQn = 82,         /* Interrupt ID:82, CA55 core 0 PERROUT */
                                       /* Interrupt ID:83, Reserved */
                                       /* Interrupt ID:84, Reserved */
                                       /* Interrupt ID:85, Reserved */
                                       /* Interrupt ID:86, Reserved */
                                       /* Interrupt ID:87, Reserved */
                                       /* Interrupt ID:88, Reserved */
                                       /* Interrupt ID:89, Reserved */
                                       /* Interrupt ID:90, Reserved */
                                       /* Interrupt ID:91, Reserved */
                                       /* Interrupt ID:92, Reserved */
                                       /* Interrupt ID:93, Reserved */
                                       /* Interrupt ID:94, Reserved */
                                       /* Interrupt ID:95, Reserved */
                                       /* Interrupt ID:96, Reserved */
                                       /* Interrupt ID:97, Reserved */
                                       /* Interrupt ID:98, Reserved */
                                       /* Interrupt ID:99, Reserved */
                                       /* Interrupt ID:100, Reserved */
                                       /* Interrupt ID:101, Reserved */
                                       /* Interrupt ID:102, Reserved */
                                       /* Interrupt ID:103, Reserved */
                                       /* Interrupt ID:104, Reserved */
                                       /* Interrupt ID:105, Reserved */
                                       /* Interrupt ID:106, Reserved */
                                       /* Interrupt ID:107, Reserved */
                                       /* Interrupt ID:108, Reserved */
                                       /* Interrupt ID:109, Reserved */
                                       /* Interrupt ID:110, Reserved */
                                       /* Interrupt ID:111, Reserved */
                                       /* Interrupt ID:112, Reserved */
                                       /* Interrupt ID:113, Reserved */
                                       /* Interrupt ID:114, Reserved */
                                       /* Interrupt ID:115, Reserved */
    ETH0_PIF_INT_N_IRQn      = 116,    /* Interrupt ID:116, pif_int_n */
    ETH0_FIL_INT_N_IRQn      = 117,    /* Interrupt ID:117, int_fil_n */
    ETH0_ARP_NS_N_IRQn       = 118,    /* Interrupt ID:118, int_arp_ns_n */
    ETH1_PIF_INT_N_IRQn      = 119,    /* Interrupt ID:119, pif_int_n */
    ETH1_FIL_INT_N_IRQn      = 120,    /* Interrupt ID:120, int_fil_n */
    ETH1_ARP_NS_N_IRQn       = 121,    /* Interrupt ID:121, int_arp_ns_n */
    USB_U2H0_INT_IRQn        = 122,    /* Interrupt ID:122, U2H0_INT */
    USB_U2H0_OHCI_INT_IRQn   = 123,    /* Interrupt ID:123, U2H0_OHCI_INT */
    USB_U2H0_EHCI_INT_IRQn   = 124,    /* Interrupt ID:124, U2H0_EHCI_INT */
    USB_U2H0_WAKEON_INT_IRQn = 125,    /* Interrupt ID:125, U2H0_WAKEON_INT */
    USB_U2H0_OBINT_IRQn      = 126,    /* Interrupt ID:126, U2H0_OBINT */
    USB_U2H1_INT_IRQn        = 127,    /* Interrupt ID:127, U2H1_INT */
    USB_U2H1_OHCI_INT_IRQn   = 128,    /* Interrupt ID:128, U2H1_OHCI_INT */
    USB_U2H1_EHCI_INT_IRQn   = 129,    /* Interrupt ID:129, U2H1_EHCI_INT */
    USB_U2H1_WAKEON_INT_IRQn = 130,    /* Interrupt ID:130, U2H1_WAKEON_INT */
    USB_U2H1_OBINT_IRQn      = 131,    /* Interrupt ID:131, U2H1_OBINT */
    USB_U2P_IXL_INT_IRQn     = 132,    /* Interrupt ID:132, U2P_IXL_INT */
    USB_U2P_INT_DMA0_IRQn    = 133,    /* Interrupt ID:133, U2P_INT_DMA[0] */
    USB_U2P_INT_DMA1_IRQn    = 134,    /* Interrupt ID:134, U2P_INT_DMA[1] */
    USB_U2P_INT_DMAERR_IRQn  = 135,    /* Interrupt ID:135, U2P_INT_DMAERR */
    SDHI_eMMC0_OXMN_IRQn     = 136,    /* Interrupt ID:136, SDHI_eMMC0 OXMNIRQ */
    SDHI_eMMC0_OXASIO_IRQn   = 137,    /* Interrupt ID:137, SDHI_eMMC0 OXASIOIRQ */
    SDHI_eMMC1_OXMN_IRQn     = 138,    /* Interrupt ID:138, SDHI_eMMC1 OXMNIRQ */
    SDHI_eMMC1_OXASIO_IRQn   = 139,    /* Interrupt ID:139, SDHI_eMMC1 OXASIOIRQ */
                                       /* Interrupt ID:140, Reserved */
                                       /* Interrupt ID:141, Reserved */
                                       /* Interrupt ID:142, Reserved */
                                       /* Interrupt ID:143, Reserved */
                                       /* Interrupt ID:143, Reserved */
                                       /* Interrupt ID:145, Reserved */
                                       /* Interrupt ID:146, Reserved */
                                       /* Interrupt ID:147, Reserved */
                                       /* Interrupt ID:148, Reserved */
                                       /* Interrupt ID:149, Reserved */
                                       /* Interrupt ID:150, Reserved */
                                       /* Interrupt ID:151, Reserved */
                                       /* Interrupt ID:152, Reserved */
                                       /* Interrupt ID:153, Reserved */
                                       /* Interrupt ID:154, Reserved */
                                       /* Interrupt ID:155, Reserved */
                                       /* Interrupt ID:156, Reserved */
    DMAC_DMAINT0_NS_IRQn  = 157,       /* Interrupt ID:157, DMAC_intreq_dmaint0(Non-Secure) */
    DMAC_DMAINT1_NS_IRQn  = 158,       /* Interrupt ID:158, DMAC_intreq_dmaint1(Non-Secure) */
    DMAC_DMAINT2_NS_IRQn  = 159,       /* Interrupt ID:159, DMAC_intreq_dmaint2(Non-Secure) */
    DMAC_DMAINT3_NS_IRQn  = 160,       /* Interrupt ID:160, DMAC_intreq_dmaint3(Non-Secure) */
    DMAC_DMAINT4_NS_IRQn  = 161,       /* Interrupt ID:161, DMAC_intreq_dmaint4(Non-Secure) */
    DMAC_DMAINT5_NS_IRQn  = 162,       /* Interrupt ID:162, DMAC_intreq_dmaint5(Non-Secure) */
    DMAC_DMAINT6_NS_IRQn  = 163,       /* Interrupt ID:163, DMAC_intreq_dmaint6(Non-Secure) */
    DMAC_DMAINT7_NS_IRQn  = 164,       /* Interrupt ID:164, DMAC_intreq_dmaint7(Non-Secure) */
    DMAC_DMAINT8_NS_IRQn  = 165,       /* Interrupt ID:165, DMAC_intreq_dmaint8(Non-Secure) */
    DMAC_DMAINT9_NS_IRQn  = 166,       /* Interrupt ID:166, DMAC_intreq_dmaint9(Non-Secure) */
    DMAC_DMAINT10_NS_IRQn = 167,       /* Interrupt ID:167, DMAC_intreq_dmaint10(Non-Secure) */
    DMAC_DMAINT11_NS_IRQn = 168,       /* Interrupt ID:168, DMAC_intreq_dmaint11(Non-Secure) */
    DMAC_DMAINT12_NS_IRQn = 169,       /* Interrupt ID:169, DMAC_intreq_dmaint12(Non-Secure) */
    DMAC_DMAINT13_NS_IRQn = 170,       /* Interrupt ID:170, DMAC_intreq_dmaint13(Non-Secure) */
    DMAC_DMAINT14_NS_IRQn = 171,       /* Interrupt ID:171, DMAC_intreq_dmaint14(Non-Secure) */
    DMAC_DMAINT15_NS_IRQn = 172,       /* Interrupt ID:172, DMAC_intreq_dmaint15(Non-Secure) */
    DMAC_DMAERR_NS_IRQn   = 173,       /* Interrupt ID:173, DMAERR(Non-Secure) */
                                       /* Interrupt ID:174, Reserved */
                                       /* Interrupt ID:175, Reserved */
                                       /* Interrupt ID:176, Reserved */
                                       /* Interrupt ID:177, Reserved */
                                       /* Interrupt ID:178, Reserved */
                                       /* Interrupt ID:179, Reserved */
                                       /* Interrupt ID:180, Reserved */
    LCDC_VSPD_INT_IRQn = 181,          /* Interrupt ID:181, vs1o_intreq_n */
                                       /* Interrupt ID:182, Reserved */
                                       /* Interrupt ID:183, Reserved */
    LCDC_DU_INT_IRQn = 184,            /* Interrupt ID:184, duo_intr_n */
                                       /* Interrupt ID:185, Reserved */
                                       /* Interrupt ID:186, Reserved */
                                       /* Interrupt ID:187, Reserved */
                                       /* Interrupt ID:188, Reserved */
    ISU_INT_FRE_IRQn   = 189,          /* Interrupt ID:189, ISU_INT_FRE */
    ISU_INT_DESE_IRQn  = 190,          /* Interrupt ID:190, ISU_INT_DESE */
    ISU_INT_STOPE_IRQn = 191,          /* Interrupt ID:191, ISU_INT_STOPE */
    ISU_INT_ERR_IRQn   = 192,          /* Interrupt ID:192, ISU_INT_ERR */
                                       /* Interrupt ID:193, Reserved */
                                       /* Interrupt ID:194, Reserved */
                                       /* Interrupt ID:195, Reserved */
                                       /* Interrupt ID:196, Reserved */
                                       /* Interrupt ID:197, Reserved */
    CRU_CSI2_LINK_INT_IRQn      = 198, /* Interrupt ID:198, csi2_link_int  */
    CRU_IMAGE_CONV_INT_IRQn     = 199, /* Interrupt ID:199, image_conv_int */
    CRU_IMAGE_CONV_ERR_INT_IRQn = 200, /* Interrupt ID:200, image_conv_err_int */
    CRU_AXI_MST_ERR_INT_IRQn    = 201, /* Interrupt ID:201, axi_mst_err_int */
    MTU0_TGIA_PLS_IRQn          = 202, /* Interrupt ID:202, tgi0a_pls_n */
    MTU0_TGIB_PLS_IRQn          = 203, /* Interrupt ID:203, tgi0b_pls_n */
    MTU0_TGIC_PLS_IRQn          = 204, /* Interrupt ID:204, tgi0c_pls_n */
    MTU0_TGID_PLS_IRQn          = 205, /* Interrupt ID:205, tgi0d_pls_n */
    MTU0_TCIV_PLS_IRQn          = 206, /* Interrupt ID:206, tci0v_pls_n */
    MTU0_TGIE_PLS_IRQn          = 207, /* Interrupt ID:207, tgi0e_pls_n */
    MTU0_TGIF_PLS_IRQn          = 208, /* Interrupt ID:208, tgi0f_pls_n */
    MTU1_TGIA_PLS_IRQn          = 209, /* Interrupt ID:209, tgi1a_pls_n */
    MTU1_TGIB_PLS_IRQn          = 210, /* Interrupt ID:210, tgi1b_pls_n */
    MTU1_TCIV_PLS_IRQn          = 211, /* Interrupt ID:211, tci1v_pls_n */
    MTU1_TCIU_PLS_IRQn          = 212, /* Interrupt ID:212, tci1u_pls_n */
    MTU2_TGIA_PLS_IRQn          = 213, /* Interrupt ID:213, tgi2a_pls_n */
    MTU2_TGIB_PLS_IRQn          = 214, /* Interrupt ID:214, tgi2b_pls_n */
    MTU2_TCIV_PLS_IRQn          = 215, /* Interrupt ID:215, tci2v_pls_n */
    MTU2_TCIU_PLS_IRQn          = 216, /* Interrupt ID:216, tci2u_pls_n */
    MTU3_TGIA_PLS_IRQn          = 217, /* Interrupt ID:217, tgi3ai_pls_n */
    MTU3_TGIB_PLS_IRQn          = 218, /* Interrupt ID:218, tgi3bi_pls_n */
    MTU3_TGIC_PLS_IRQn          = 219, /* Interrupt ID:219, tgi3ci_pls_n */
    MTU3_TGID_PLS_IRQn          = 220, /* Interrupt ID:220, tgi3di_pls_n */
    MTU3_TCIV_PLS_IRQn          = 221, /* Interrupt ID:221, tci3vi_pls_n */
    MTU4_TGIA_PLS_IRQn          = 222, /* Interrupt ID:222, tgi4ai_pls_n */
    MTU4_TGIB_PLS_IRQn          = 223, /* Interrupt ID:223, tgi4bi_pls_n */
    MTU4_TGIC_PLS_IRQn          = 224, /* Interrupt ID:224, tgi4ci_pls_n */
    MTU4_TGID_PLS_IRQn          = 225, /* Interrupt ID:225, tgi4di_pls_n */
    MTU4_TCIV_PLS_IRQn          = 226, /* Interrupt ID:226, tci4vi_pls_n */
    MTU5_TGIU_PLS_IRQn          = 227, /* Interrupt ID:227, tgi5ui_pls_n */
    MTU5_TGIV_PLS_IRQn          = 228, /* Interrupt ID:228, tgi5vi_pls_n */
    MTU5_TGIW_PLS_IRQn          = 229, /* Interrupt ID:229, tgi5wi_pls_n */
    MTU6_TGIA_PLS_IRQn          = 230, /* Interrupt ID:230, tgi6ai_pls_n */
    MTU6_TGIB_PLS_IRQn          = 231, /* Interrupt ID:231, tgi6bi_pls_n */
    MTU6_TGIC_PLS_IRQn          = 232, /* Interrupt ID:232, tgi6ci_pls_n */
    MTU6_TGID_PLS_IRQn          = 233, /* Interrupt ID:233, tgi6di_pls_n */
    MTU6_TCIV_PLS_IRQn          = 234, /* Interrupt ID:234, tci6vi_pls_n */
    MTU7_TGIA_PLS_IRQn          = 235, /* Interrupt ID:235, tgi7ai_pls_n */
    MTU7_TGIB_PLS_IRQn          = 236, /* Interrupt ID:236, tgi7bi_pls_n */
    MTU7_TGIC_PLS_IRQn          = 237, /* Interrupt ID:237, tgi7ci_pls_n */
    MTU7_TGID_PLS_IRQn          = 238, /* Interrupt ID:238, tgi7di_pls_n */
    MTU7_TCIV_PLS_IRQn          = 239, /* Interrupt ID:239, tci7vi_pls_n */
    MTU8_TGIA_PLS_IRQn          = 240, /* Interrupt ID:240, tgi8a_pls_n */
    MTU8_TGIB_PLS_IRQn          = 241, /* Interrupt ID:241, tgi8b_pls_n */
    MTU8_TGIC_PLS_IRQn          = 242, /* Interrupt ID:242, tgi8c_pls_n */
    MTU8_TGID_PLS_IRQn          = 243, /* Interrupt ID:243, tgi8d_pls_n */
    MTU8_TCIV_PLS_IRQn          = 244, /* Interrupt ID:244, tci8v_pls_n */
    MTU8_TCIU_PLS_IRQn          = 245, /* Interrupt ID:245, tci8u_pls_n */
    POE3_OEI1_IRQn              = 246, /* Interrupt ID:246, poe_oei1_n */
    POE3_OEI2_IRQn              = 247, /* Interrupt ID:247, poe_oei2_n */
    POE3_OEI3_IRQn              = 248, /* Interrupt ID:248, poe_oei3_n */
    POE3_OEI4_IRQn              = 249, /* Interrupt ID:249, poe_oei4_n */
                                       /* Interrupt ID:250, Reserved */
                                       /* Interrupt ID:251, Reserved */
                                       /* Interrupt ID:252, Reserved */
                                       /* Interrupt ID:253, Reserved */
                                       /* Interrupt ID:254, Reserved */
                                       /* Interrupt ID:255, Reserved */
                                       /* Interrupt ID:256, Reserved */
                                       /* Interrupt ID:257, Reserved */
                                       /* Interrupt ID:258, Reserved */
                                       /* Interrupt ID:259, Reserved */
                                       /* Interrupt ID:260, Reserved */
                                       /* Interrupt ID:261, Reserved */
                                       /* Interrupt ID:262, Reserved */
                                       /* Interrupt ID:263, Reserved */
                                       /* Interrupt ID:264, Reserved */
                                       /* Interrupt ID:265, Reserved */
                                       /* Interrupt ID:266, Reserved */
                                       /* Interrupt ID:267, Reserved */
                                       /* Interrupt ID:268, Reserved */
                                       /* Interrupt ID:269, Reserved */
                                       /* Interrupt ID:270, Reserved */
                                       /* Interrupt ID:271, Reserved */
                                       /* Interrupt ID:272, Reserved */
                                       /* Interrupt ID:273, Reserved */
                                       /* Interrupt ID:274, Reserved */
                                       /* Interrupt ID:275, Reserved */
                                       /* Interrupt ID:276, Reserved */
                                       /* Interrupt ID:277, Reserved */
                                       /* Interrupt ID:278, Reserved */
                                       /* Interrupt ID:279, Reserved */
                                       /* Interrupt ID:280, Reserved */
                                       /* Interrupt ID:281, Reserved */
                                       /* Interrupt ID:282, Reserved */
                                       /* Interrupt ID:283, Reserved */
                                       /* Interrupt ID:284, Reserved */
                                       /* Interrupt ID:285, Reserved */
                                       /* Interrupt ID:286, Reserved */
                                       /* Interrupt ID:287, Reserved */
                                       /* Interrupt ID:288, Reserved */
                                       /* Interrupt ID:289, Reserved */
                                       /* Interrupt ID:290, Reserved */
                                       /* Interrupt ID:291, Reserved */
                                       /* Interrupt ID:292, Reserved */
                                       /* Interrupt ID:293, Reserved */
                                       /* Interrupt ID:294, Reserved */
                                       /* Interrupt ID:295, Reserved */
                                       /* Interrupt ID:296, Reserved */
                                       /* Interrupt ID:297, Reserved */
                                       /* Interrupt ID:298, Reserved */
                                       /* Interrupt ID:299, Reserved */
                                       /* Interrupt ID:300, Reserved */
                                       /* Interrupt ID:301, Reserved */
                                       /* Interrupt ID:302, Reserved */
                                       /* Interrupt ID:303, Reserved */
                                       /* Interrupt ID:304, Reserved */
                                       /* Interrupt ID:305, Reserved */
                                       /* Interrupt ID:306, Reserved */
                                       /* Interrupt ID:307, Reserved */
                                       /* Interrupt ID:308, Reserved */
                                       /* Interrupt ID:309, Reserved */
                                       /* Interrupt ID:310, Reserved */
                                       /* Interrupt ID:311, Reserved */
                                       /* Interrupt ID:312, Reserved */
                                       /* Interrupt ID:313, Reserved */
                                       /* Interrupt ID:314, Reserved */
                                       /* Interrupt ID:315, Reserved */
                                       /* Interrupt ID:316, Reserved */
                                       /* Interrupt ID:317, Reserved */
                                       /* Interrupt ID:318, Reserved */
                                       /* Interrupt ID:319, Reserved */
                                       /* Interrupt ID:320, Reserved */
                                       /* Interrupt ID:321, Reserved */
                                       /* Interrupt ID:322, Reserved */
                                       /* Interrupt ID:323, Reserved */
                                       /* Interrupt ID:324, Reserved */
                                       /* Interrupt ID:325, Reserved */
                                       /* Interrupt ID:326, Reserved */
                                       /* Interrupt ID:327, Reserved */
                                       /* Interrupt ID:328, Reserved */
                                       /* Interrupt ID:329, Reserved */
                                       /* Interrupt ID:330, Reserved */
                                       /* Interrupt ID:331, Reserved */
                                       /* Interrupt ID:332, Reserved */
                                       /* Interrupt ID:333, Reserved */
                                       /* Interrupt ID:334, Reserved */
                                       /* Interrupt ID:335, Reserved */
                                       /* Interrupt ID:336, Reserved */
                                       /* Interrupt ID:337, Reserved */
                                       /* Interrupt ID:338, Reserved */
                                       /* Interrupt ID:339, Reserved */
                                       /* Interrupt ID:340, Reserved */
                                       /* Interrupt ID:341, Reserved */
                                       /* Interrupt ID:342, Reserved */
                                       /* Interrupt ID:343, Reserved */
                                       /* Interrupt ID:344, Reserved */
                                       /* Interrupt ID:345, Reserved */
                                       /* Interrupt ID:346, Reserved */
                                       /* Interrupt ID:347, Reserved */
                                       /* Interrupt ID:348, Reserved */
                                       /* Interrupt ID:349, Reserved */
                                       /* Interrupt ID:350, Reserved */
                                       /* Interrupt ID:351, Reserved */
                                       /* Interrupt ID:352, Reserved */
                                       /* Interrupt ID:353, Reserved */
                                       /* Interrupt ID:354, Reserved */
                                       /* Interrupt ID:355, Reserved */
                                       /* Interrupt ID:356, Reserved */
                                       /* Interrupt ID:357, Reserved */
    I2S0_INT_REQ_IRQn = 358,           /* Interrupt ID:358, INT_ssif_int_req */
    I2S0_DMA_RX_IRQn  = 359,           /* Interrupt ID:359, INT_ssif_dma_rx */
    I2S0_DMA_TX_IRQn  = 360,           /* Interrupt ID:360, INT_ssif_dma_tx */
                                       /* Interrupt ID:361, Reserved */
    I2S1_INT_REQ_IRQn = 362,           /* Interrupt ID:362, INT_ssif_int_req */
    I2S1_DMA_RX_IRQn  = 363,           /* Interrupt ID:363, INT_ssif_dma_rx */
    I2S1_DMA_TX_IRQn  = 364,           /* Interrupt ID:364, INT_ssif_dma_tx */
                                       /* Interrupt ID:365, Reserved */
    I2S2_INT_REQ_IRQn = 366,           /* Interrupt ID:366, INT_ssif_int_req */
                                       /* Interrupt ID:367, Reserved */
                                       /* Interrupt ID:368, Reserved */
    I2S2_DMA_RT_IRQn  = 369,           /* Interrupt ID:369, INT_ssif_dma_rt */
    I2S3_INT_REQ_IRQn = 370,           /* Interrupt ID:370, INT_ssif_int_req */
    I2S3_DMA_RX_IRQn  = 371,           /* Interrupt ID:371, INT_ssif_dma_rx */
    I2S3_DMA_TX_IRQn  = 372,           /* Interrupt ID:372, INT_ssif_dma_tx */
                                       /* Interrupt ID:373, Reserved */
                                       /* Interrupt ID:374, Reserved */
                                       /* Interrupt ID:375, Reserved */
                                       /* Interrupt ID:376, Reserved */
                                       /* Interrupt ID:377, Reserved */
                                       /* Interrupt ID:378, Reserved */
    ADC_INTAD_IRQn          = 379,     /* Interrupt ID:379, INTAD */
    RIIC0_RI_IRQn           = 380,     /* Interrupt ID:380, ri_p */
    RIIC0_TI_IRQn           = 381,     /* Interrupt ID:381, ti_p */
    RIIC0_TEI_IRQn          = 382,     /* Interrupt ID:382, tei_p */
    RIIC0_NAKI_IRQn         = 383,     /* Interrupt ID:383, naki_p */
    RIIC0_SPI_IRQn          = 384,     /* Interrupt ID:384, spi_p */
    RIIC0_STI_IRQn          = 385,     /* Interrupt ID:385, sti_p */
    RIIC0_ALI_IRQn          = 386,     /* Interrupt ID:386, ali_p */
    RIIC0_TMOI_IRQn         = 387,     /* Interrupt ID:387, tmoi_p */
    RIIC1_RI_IRQn           = 388,     /* Interrupt ID:388, ri_p */
    RIIC1_TI_IRQn           = 389,     /* Interrupt ID:389, ti_p */
    RIIC1_TEI_IRQn          = 390,     /* Interrupt ID:390, tei_p */
    RIIC1_NAKI_IRQn         = 391,     /* Interrupt ID:391, naki_p */
    RIIC1_SPI_IRQn          = 392,     /* Interrupt ID:392, spi_p */
    RIIC1_STI_IRQn          = 393,     /* Interrupt ID:393, sti_p */
    RIIC1_ALI_IRQn          = 394,     /* Interrupt ID:394, ali_p */
    RIIC1_TMOI_IRQn         = 395,     /* Interrupt ID:395, tmoi_p */
    RIIC2_RI_IRQn           = 396,     /* Interrupt ID:396, ri_p */
    RIIC2_TI_IRQn           = 397,     /* Interrupt ID:397, ti_p */
    RIIC2_TEI_IRQn          = 398,     /* Interrupt ID:398, tei_p */
    RIIC2_NAKI_IRQn         = 399,     /* Interrupt ID:399, naki_p */
    RIIC2_SPI_IRQn          = 400,     /* Interrupt ID:400, spi_p */
    RIIC2_STI_IRQn          = 401,     /* Interrupt ID:401, sti_p */
    RIIC2_ALI_IRQn          = 402,     /* Interrupt ID:402, ali_p */
    RIIC2_TMOI_IRQn         = 403,     /* Interrupt ID:403, tmoi_p */
    RIIC3_RI_IRQn           = 404,     /* Interrupt ID:404, ri_p */
    RIIC3_TI_IRQn           = 405,     /* Interrupt ID:405, ti_p */
    RIIC3_TEI_IRQn          = 406,     /* Interrupt ID:406, tei_p */
    RIIC3_NAKI_IRQn         = 407,     /* Interrupt ID:407, naki_p */
    RIIC3_SPI_IRQn          = 408,     /* Interrupt ID:408, spi_p */
    RIIC3_STI_IRQn          = 409,     /* Interrupt ID:409, sti_p */
    RIIC3_ALI_IRQn          = 410,     /* Interrupt ID:410, ali_p */
    RIIC3_TMOI_IRQn         = 411,     /* Interrupt ID:411, tmoi_p */
    SCIF0_RERR_IRQn         = 412,     /* Interrupt ID:412, ub1_rerr_n */
    SCIF0_BRK_IRQn          = 413,     /* Interrupt ID:413, ub1_brk_n */
    SCIF0_RXI_IRQn          = 414,     /* Interrupt ID:414, ub1_rxi_n */
    SCIF0_TXI_IRQn          = 415,     /* Interrupt ID:415, ub1_txi_n */
    SCIF0_TEI_DRI_IRQn      = 416,     /* Interrupt ID:416, ub1_tei_dri_n */
    SCIF1_RERR_IRQn         = 417,     /* Interrupt ID:417, ub1_rerr_n */
    SCIF1_BRK_IRQn          = 418,     /* Interrupt ID:418, ub1_brk_n */
    SCIF1_RXI_IRQn          = 419,     /* Interrupt ID:419, ub1_rxi_n */
    SCIF1_TXI_IRQn          = 420,     /* Interrupt ID:420, ub1_txi_n */
    SCIF1_TEI_DRI_IRQn      = 421,     /* Interrupt ID:421, ub1_tei_dri_n */
    SCIF2_RERR_IRQn         = 422,     /* Interrupt ID:422, ub1_rerr_n */
    SCIF2_BRK_IRQn          = 423,     /* Interrupt ID:423, ub1_brk_n */
    SCIF2_RXI_IRQn          = 424,     /* Interrupt ID:424, ub1_rxi_n */
    SCIF2_TXI_IRQn          = 425,     /* Interrupt ID:425, ub1_txi_n */
    SCIF2_TEI_DRI_IRQn      = 426,     /* Interrupt ID:426, ub1_tei_dri_n */
    SCIF3_RERR_IRQn         = 427,     /* Interrupt ID:427, ub1_rerr_n */
    SCIF3_BRK_IRQn          = 428,     /* Interrupt ID:428, ub1_brk_n */
    SCIF3_RXI_IRQn          = 429,     /* Interrupt ID:429, ub1_rxi_n */
    SCIF3_TXI_IRQn          = 430,     /* Interrupt ID:430, ub1_txi_n */
    SCIF3_TEI_DRI_IRQn      = 431,     /* Interrupt ID:431, ub1_tei_dri_n */
    SCIF4_RERR_IRQn         = 432,     /* Interrupt ID:432, ub1_rerr_n */
    SCIF4_BRK_IRQn          = 433,     /* Interrupt ID:433, ub1_brk_n */
    SCIF4_RXI_IRQn          = 434,     /* Interrupt ID:434, ub1_rxi_n */
    SCIF4_TXI_IRQn          = 435,     /* Interrupt ID:435, ub1_txi_n */
    SCIF4_TEI_DRI_IRQn      = 436,     /* Interrupt ID:436, ub1_tei_dri_n */
    SCI0_ERI_IRQn           = 437,     /* Interrupt ID:437, sc_eri_n */
    SCI0_RXI_IRQn           = 438,     /* Interrupt ID:438, sc_rxi_n */
    SCI0_TXI_IRQn           = 439,     /* Interrupt ID:439, sc_txi_n */
    SCI0_TEI_IRQn           = 440,     /* Interrupt ID:440, sc_tei_n */
    SCI1_ERI_IRQn           = 441,     /* Interrupt ID:441, sc_eri_n */
    SCI1_RXI_IRQn           = 442,     /* Interrupt ID:442, sc_rxi_n */
    SCI1_TXI_IRQn           = 443,     /* Interrupt ID:443, sc_txi_n */
    SCI1_TEI_IRQn           = 444,     /* Interrupt ID:444, sc_tei_n */
    RSPI0_RX_IRQn           = 445,     /* Interrupt ID:445, sp_rxint_n */
    RSPI0_TX_IRQn           = 446,     /* Interrupt ID:446, sp_txint_n */
    RSPI0_ERR_IRQn          = 447,     /* Interrupt ID:447, sp_errint_n */
    RSPI1_RX_IRQn           = 448,     /* Interrupt ID:448, sp_rxint_n */
    RSPI1_TX_IRQn           = 449,     /* Interrupt ID:449, sp_txint_n */
    RSPI1_ERR_IRQn          = 450,     /* Interrupt ID:450, sp_errint_n */
    RSPI2_RX_IRQn           = 451,     /* Interrupt ID:451, sp_rxint_n */
    RSPI2_TX_IRQn           = 452,     /* Interrupt ID:452, sp_txint_n */
    RSPI2_ERR_IRQn          = 453,     /* Interrupt ID:453, sp_errint_n */
    CANFD_INTRCAN0ERR_IRQn  = 454,     /* Interrupt ID:454, can_cherr_int[0]  */
    CANFD_INTRCAN1ERR_IRQn  = 455,     /* Interrupt ID:455, can_cherr_int[1] */
    CANFD_INTRCAN0REC_IRQn  = 456,     /* Interrupt ID:456, can_comfrx_int[0]  */
    CANFD_INTRCAN1REC_IRQn  = 457,     /* Interrupt ID:457, can_comfrx_int[1] */
    CANFD_INTRCANGERR_IRQn  = 458,     /* Interrupt ID:458, can_glerr_int  */
    CANFD_INTRCANGRECC_IRQn = 459,     /* Interrupt ID:459, can_rxf_int  */
    CANFD_INTRCAN0TRX_IRQn  = 460,     /* Interrupt ID:460, can_tx_int[0]  */
    CANFD_INTRCAN1TRX_IRQn  = 461,     /* Interrupt ID:461, can_tx_int[1] */
                                       /* Interrupt ID:462, Reserved */
                                       /* Interrupt ID:463, Reserved */
                                       /* Interrupt ID:464, Reserved */
                                       /* Interrupt ID:465, Reserved */
                                       /* Interrupt ID:466, Reserved */
                                       /* Interrupt ID:467, Reserved */
                                       /* Interrupt ID:468, Reserved */
                                       /* Interrupt ID:469, Reserved */
                                       /* Interrupt ID:470, Reserved */
                                       /* Interrupt ID:471, Reserved */
                                       /* Interrupt ID:472, Reserved */
                                       /* Interrupt ID:473, Reserved */
                                       /* Interrupt ID:474, Reserved */
                                       /* Interrupt ID:475, Reserved */
    GPIO_TINT0_IRQn  = 476,            /* Interrupt ID:476, TINT0 */
    GPIO_TINT1_IRQn  = 477,            /* Interrupt ID:477, TINT1 */
    GPIO_TINT2_IRQn  = 478,            /* Interrupt ID:478, TINT2 */
    GPIO_TINT3_IRQn  = 479,            /* Interrupt ID:479, TINT3 */
    GPIO_TINT4_IRQn  = 480,            /* Interrupt ID:480, TINT4 */
    GPIO_TINT5_IRQn  = 481,            /* Interrupt ID:481, TINT5 */
    GPIO_TINT6_IRQn  = 482,            /* Interrupt ID:482, TINT6 */
    GPIO_TINT7_IRQn  = 483,            /* Interrupt ID:483, TINT7 */
    GPIO_TINT8_IRQn  = 484,            /* Interrupt ID:484, TINT8 */
    GPIO_TINT9_IRQn  = 485,            /* Interrupt ID:485, TINT9 */
    GPIO_TINT10_IRQn = 486,            /* Interrupt ID:486, TINT10 */
    GPIO_TINT11_IRQn = 487,            /* Interrupt ID:487, TINT11 */
    GPIO_TINT12_IRQn = 488,            /* Interrupt ID:488, TINT12 */
    GPIO_TINT13_IRQn = 489,            /* Interrupt ID:489, TINT13 */
    GPIO_TINT14_IRQn = 490,            /* Interrupt ID:490, TINT14 */
    GPIO_TINT15_IRQn = 491,            /* Interrupt ID:491, TINT15 */
    GPIO_TINT16_IRQn = 492,            /* Interrupt ID:492, TINT16 */
    GPIO_TINT17_IRQn = 493,            /* Interrupt ID:493, TINT17 */
    GPIO_TINT18_IRQn = 494,            /* Interrupt ID:494, TINT18 */
    GPIO_TINT19_IRQn = 495,            /* Interrupt ID:495, TINT19 */
    GPIO_TINT20_IRQn = 496,            /* Interrupt ID:496, TINT20 */
    GPIO_TINT21_IRQn = 497,            /* Interrupt ID:497, TINT21 */
    GPIO_TINT22_IRQn = 498,            /* Interrupt ID:498, TINT22 */
    GPIO_TINT23_IRQn = 499,            /* Interrupt ID:499, TINT23 */
    GPIO_TINT24_IRQn = 500,            /* Interrupt ID:500, TINT24 */
    GPIO_TINT25_IRQn = 501,            /* Interrupt ID:501, TINT25 */
    GPIO_TINT26_IRQn = 502,            /* Interrupt ID:502, TINT26 */
    GPIO_TINT27_IRQn = 503,            /* Interrupt ID:503, TINT27 */
    GPIO_TINT28_IRQn = 504,            /* Interrupt ID:504, TINT28 */
    GPIO_TINT29_IRQn = 505,            /* Interrupt ID:505, TINT29 */
    GPIO_TINT30_IRQn = 506,            /* Interrupt ID:506, TINT30 */
    GPIO_TINT31_IRQn = 507,            /* Interrupt ID:507, TINT31 */
                                       /* Interrupt ID:508, Reserved */
                                       /* Interrupt ID:509, Reserved */
                                       /* Interrupt ID:510, Reserved */
                                       /* Interrupt ID:511, Reserved */
} IRQn_Type;

/** @} (end addtogroup BSP_MPU_RZA3UL) */

#endif                                 /* BSP_IRQ_ID_H */

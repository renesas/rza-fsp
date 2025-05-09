/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

 #define USB_VAL_BWAIT3F    (0x003f)

/******************************************************************************
 * Function Name   : hw_usb_pset_dprpu
 * Description     : Set DPRPU-bit SYSCFG0 register.
 *               : (Enable D+Line pullup when PeripheralController function is selected)
 * Arguments       : usb_utr_t *ptr  : USB internal structure. Selects USB channel.
 * Return value    : none
 ******************************************************************************/
void hw_usb_pset_dprpu (uint8_t usb_ip)
{
 #if defined(BSP_MCU_GROUP_RZT2M) || defined(BSP_MCU_GROUP_RZA_USB)
    FSP_PARAMETER_NOT_USED(usb_ip);
    USB_M0->SYSCFG0 |= USB_DPRPU;
 #else                                 /*  #if defined(BSP_MCU_GROUP_RZT2M)|| defined(BSP_MCU_GROUP_RZA3UL) */
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->SYSCFG |= USB_DPRPU;
    }
    else
    {
        USB_M1->SYSCFG |= USB_DPRPU;
    }
 #endif                                /* defined(BSP_MCU_GROUP_RZT2M) */
}

/******************************************************************************
 * End of function hw_usb_pset_dprpu
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pclear_dprpu
 * Description     : Clear DPRPU-bit of the SYSCFG0 register.
 *               : (Disable D+Line pullup when PeripheralController function is
 *               : selected.)
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_pclear_dprpu (uint8_t usb_ip)
{
 #if defined(BSP_MCU_GROUP_RZT2M) || defined(BSP_MCU_GROUP_RZA_USB)
    FSP_PARAMETER_NOT_USED(usb_ip);
    USB_M0->SYSCFG0 = (uint16_t) (USB_M0->SYSCFG0 & (~USB_DPRPU));
 #else                                 /* BSP_MCU_GROUP_RZT2M == 1 */
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->SYSCFG = (uint16_t) (USB_M0->SYSCFG & (~USB_DPRPU));
    }
    else
    {
        USB_M1->SYSCFG = (uint16_t) (USB_M1->SYSCFG & (~USB_DPRPU));
    }
 #endif                                /* defined(BSP_MCU_GROUP_RZT2M) */
}

/******************************************************************************
 * End of function hw_usb_pclear_dprpu
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pset_wkup
 * Description     : Set WKUP-bit DVSTCTR register.
 *               : (Output Remote wakeup signal when PeripheralController function is selected)
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return value    : none
 ******************************************************************************/
void hw_usb_pset_wkup (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->DVSTCTR0 |= USB_WKUP;
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->DVSTCTR0 |= USB_WKUP;
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pset_wkup
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pset_enb_rsme
 * Description     : Enable interrupt from RESUME
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_pset_enb_rsme (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->INTENB0 |= USB_RSME;
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->INTENB0 |= USB_RSME;
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pset_enb_rsme
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pclear_enb_rsme
 * Description     : Disable interrupt from RESUME
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_pclear_enb_rsme (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->INTENB0 = (uint16_t) (USB_M0->INTENB0 & (~USB_RSME));
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->INTENB0 = (uint16_t) (USB_M1->INTENB0 & (~USB_RSME));
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pclear_enb_rsme
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pclear_sts_resm
 * Description     : Clear interrupt status of RESUME.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_pclear_sts_resm (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->INTSTS0 = (uint16_t) ~USB_RESM;
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->INTSTS0 = (uint16_t) ~USB_RESM;
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pclear_sts_resm
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pclear_sts_valid
 * Description     : Clear the Setup Packet Reception interrupt flag.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_pclear_sts_valid (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->INTSTS0 = (uint16_t) ~USB_VALID;
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->INTSTS0 = (uint16_t) ~USB_VALID;
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pclear_sts_valid
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pset_ccpl
 * Description     : Enable termination of control transfer status stage.
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_pset_ccpl (uint8_t usb_ip)
{
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->DCPCTR |= USB_CCPL;
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->DCPCTR |= USB_CCPL;
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pset_ccpl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pmodule_init
 * Description     :
 * Arguments       : none
 * Return value    : none
 ******************************************************************************/
void hw_usb_pmodule_init (uint8_t usb_ip)
{
 #if defined(BSP_MCU_GROUP_RZT2M) || defined(BSP_MCU_GROUP_RZA_USB)
    FSP_PARAMETER_NOT_USED(usb_ip);
    USB_M0->SYSCFG1   = (USB_CFG_BUSWAIT & USB_VAL_BWAIT3F);
    USB_M0->CFIFOSEL  = USB0_CFIFO_MBW;
    USB_M0->D0FIFOSEL = USB0_D0FIFO_MBW;
    USB_M0->D1FIFOSEL = USB0_D1FIFO_MBW;
  #if USB_CFG_ENDIAN == USB_CFG_BIG
    USB_M0->CFIFOSEL  |= USB_BIGEND;
    USB_M0->D0FIFOSEL |= USB_BIGEND;
    USB_M0->D1FIFOSEL |= USB_BIGEND;
  #endif                               /* USB_CFG_ENDIAN == USB_CFG_BIG */
 #else  /* defined(BSP_MCU_GROUP_RZT2M) */
    if (USB_CFG_IP0 == usb_ip)
    {
        USB_M0->SYSCFG |= USB_SCKE;

        /* WAIT_LOOP */
        while (USB_SCKE != (USB_M0->SYSCFG & USB_SCKE))
        {
            /* Wait for Set of SCKE */
        }

  #if defined(BSP_MCU_GROUP_RA6M3)
        USB_M0->PHYSLEW = 0x5;
  #endif                               /* defined(BSP_MCU_GROUP_RA6M3) */
        USB_M0->SYSCFG   &= (uint16_t) (~USB_DRPD);
        USB_M0->SYSCFG   |= USB_USBE;
        USB_M0->CFIFOSEL  = USB0_CFIFO_MBW;
        USB_M0->D0FIFOSEL = USB0_D0FIFO_MBW;
        USB_M0->D1FIFOSEL = USB0_D1FIFO_MBW;
  #if USB_CFG_ENDIAN == USB_CFG_BIG
        USB_M0->CFIFOSEL  |= USB_BIGEND;
        USB_M0->D0FIFOSEL |= USB_BIGEND;
        USB_M0->D1FIFOSEL |= USB_BIGEND;
  #endif                               /* USB_CFG_ENDIAN == USB_CFG_BIG */
        USB_M0->INTENB0 = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);
    }
    else
    {
  #if defined(BSP_MCU_GROUP_RA6M3)
   #if USB_CFG_CLKSEL == USB_CFG_20MHZ
        USB_M1->PHYSET &= (uint16_t) ~USB_CLKSEL;
        USB_M1->PHYSET |= USB_CLKSEL_20;
   #endif                              /* USB_CFG_CLKSEL == USB_CFG_20MHZ */

   #if USB_CFG_CLKSEL == USB_CFG_12MHZ
        USB_M1->PHYSET &= (uint16_t) ~USB_CLKSEL;
        USB_M1->PHYSET |= USB_CLKSEL_12;
   #endif                                /* USB_CFG_CLKSEL == USB_CFG_12MHZ */

   #if USB_CFG_CLKSEL == USB_CFG_OTHER
        USB_M1->PHYSET |= USB_HSEB;
   #endif                                /* USB_CFG_OTHER == USB_CFG_OTHER */

        usb_cpu_delay_1us((uint16_t) 1); /* wait 1usec */

        USB_M1->PHYSET = (uint16_t) (USB_M1->PHYSET & (~USB_DIRPD));
        usb_cpu_delay_xms(1);            /* wait 1msec */

   #if ((USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
        USB_M1->PHYSET = (uint16_t) (USB_M1->PHYSET & (~USB_PLLRESET));
   #endif /* (USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */
        USB_M1->SYSCFG = (uint16_t) (USB_M1->SYSCFG & (~USB_DRPD));

        USB_M1->SYSCFG |= USB_USBE;

        USB_M1->LPSTS |= USB_SUSPENDM;

   #if ((USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
        /* WAIT_LOOP */
        while (USB_PLLLOCK != (USB_M1->PLLSTA & USB_PLLLOCK))
        {
            /* Wait for PLL Lock */
        }
   #endif                              /* (USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */

        USB_M1->BUSWAIT = (USB_CFG_BUSWAIT | USB_BWAIT_B11_B8_WRITE);

        USB_M1->PHYSET |= USB_REPSEL_16;

        USB_M1->CFIFOSEL  = USB1_CFIFO_MBW;
        USB_M1->D0FIFOSEL = USB1_D0FIFO_MBW;
        USB_M1->D1FIFOSEL = USB1_D1FIFO_MBW;

   #if USB_CFG_ENDIAN == USB_CFG_BIG
        USB_M1->CFIFOSEL  |= USB_BIGEND;
        USB_M1->D0FIFOSEL |= USB_BIGEND;
        USB_M1->D1FIFOSEL |= USB_BIGEND;
   #endif                              /* USB_CFG_ENDIAN == USB_CFG_BIG */

        USB_M1->INTENB0 = (USB_BEMPE | USB_BRDYE | USB_VBSE | USB_DVSE | USB_CTRE);
  #endif                               /* defined(BSP_MCU_GROUP_RA6M3) */
    }
 #endif  /* defined(BSP_MCU_GROUP_RZT2M) */
}

/******************************************************************************
 * End of function hw_usb_pmodule_init
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pcontrol_dprpu
 * Description     : Set/Clear DPRPU-bit SYSCFG0 register.
 * Arguments       : usb_ip   : USB module number (USB_IP0/USB_IP1)
 *               : state    : USB_ON  (D+ Line Pullup Enable)
 *               :          : USB_OFF (D+ Line Pullup Disable)
 * Return value    : none
 ******************************************************************************/
void hw_usb_pcontrol_dprpu (uint8_t usb_ip, uint8_t state)
{
 #if defined(BSP_MCU_GROUP_RZT2M) || defined(BSP_MCU_GROUP_RZA_USB)
    FSP_PARAMETER_NOT_USED(usb_ip);
    if (USB_ON == state)
    {
        USB_M0->SYSCFG0 |= (uint16_t) (USB_DPRPU);
    }
    else
    {
        USB_M0->SYSCFG0 &= (uint16_t) (~USB_DPRPU);
    }
 #else                                 /* defined(BSP_MCU_GROUP_RZT2M) */
    if (USB_IP0 == usb_ip)
    {
        if (USB_ON == state)
        {
            USB_M0->SYSCFG |= (uint16_t) (USB_DPRPU);
        }
        else
        {
            USB_M0->SYSCFG &= (uint16_t) (~USB_DPRPU);
        }
    }
    else
    {
        if (USB_ON == state)
        {
            USB_M1->SYSCFG |= (uint16_t) (USB_DPRPU);
        }
        else
        {
            USB_M1->SYSCFG &= (uint16_t) (~USB_DPRPU);
        }
    }
 #endif                                /* defined(BSP_MCU_GROUP_RZT2M) */
}

/******************************************************************************
 * End of function hw_usb_pcontrol_dprpu
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_pcontrol_dcpctr_pid
 * Description     : Set ACK /STALL to PID bit for DCPCTR register
 * Arguments       : usb_ip   : USB module number (USB_IP0/USB_IP1)
 *               : data     : USB_PID_BUF   (ACK)
 *               :          : USB_PID_STALL (STALL)
 * Return value    : none
 ******************************************************************************/
void hw_usb_pcontrol_dcpctr_pid (uint8_t usb_ip, uint16_t data)
{
    if (USB_IP0 == usb_ip)
    {
        USB_M0->DCPCTR &= (uint16_t) (~USB_PID);
        if (data == USB_SETUP_STATUS_ACK)
        {
            USB_M0->DCPCTR |= (uint16_t) USB_PID_BUF;
        }
        else
        {
            USB_M0->DCPCTR |= (uint16_t) USB_PID_STALL;
        }
    }
    else
    {
 #if !defined(BSP_MCU_GROUP_RZA_USB)
        USB_M1->DCPCTR &= (uint16_t) (~USB_PID);
        if (data == USB_SETUP_STATUS_ACK)
        {
            USB_M1->DCPCTR |= (uint16_t) USB_PID_BUF;
        }
        else
        {
            USB_M1->DCPCTR |= (uint16_t) USB_PID_STALL;
        }
 #endif
    }
}

/******************************************************************************
 * End of function hw_usb_pcontrol_dcpctr_pid
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 * End of file
 ******************************************************************************/

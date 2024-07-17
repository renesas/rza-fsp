/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : r_usb_hohci_def_usr.h
 * Version      : 1.0
 * Description  : OHCI User Define Header
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.01.2017 1.00     First Release
 **********************************************************************************************************************/

#ifndef R_USB_HOHCIDEFUSR_H
#define R_USB_HOHCIDEFUSR_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* The maximum number of Endpoint memory */
#define USB_OHCI_NUM_ENDPOINT           (USB_HCI_TRREQ_NUM + USB_HCI_DEVICE_NUM)

/* The maximum number of Endpoint Descriptor memory */
#define USB_OHCI_NUM_ED                 ((USB_OHCI_ED_INTERRUPT_32ms * USB_OHCI_NUM_DEVICEDATA) + USB_OHCI_NUM_ENDPOINT)

/* The maximum number of Transfer Descriptor memory */
#define USB_OHCI_NUM_TD                 (0x100000 / USB_OHCI_MAXTDSIZE)

/* The maximum number of OHCI Isochronous Device */
#define USB_OHCI_ISO_MAXDEVICE          (4U)

/* The maximum number of OHCI Isochronous Packet Size */
#define USB_OHCI_ISO_MAX_PACKET_SIZE    (1023U)

/* Time-out setting (msec) */
#define USB_OHCI_TIMEOUT                (3000U)

#endif                                 /* R_USB_HOHCIDEFUSR_H */

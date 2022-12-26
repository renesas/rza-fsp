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

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <r_usb_basic.h>
#include <r_usb_basic_api.h>
#include <string.h>
#include "inc/r_usb_typedef.h"
#include "inc/r_usb_extern.h"
#include "../hw/inc/r_usb_bitdefine.h"
#include "../hw/inc/r_usb_reg_access.h"
#include "r_usb_hhci.h"
#include "r_usb_hhci_local.h"

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/*******************************************************************************
 * Macro definitions
 ******************************************************************************/

 #define USB_PET_VID       (0x1a0a)    /* USB-PET Vendor ID  */
 #define USB_PET_PID       (0x0200)    /* USB-PET Product ID (Use Embedded Host Test) */
 #define USB_VALUE_FFH     (0xFF)
 #define USB_VALUE_40H     (0x40)
 #define USB_VALUE_100     (100)
 #define USB_VALUE_3000    (3000)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/

static uint16_t  usb_shstd_std_request[USB_NUM_USBIP][5]    USB_BUFFER_PLACE_IN_SECTION;
static usb_utr_t usb_shstd_std_req_msg[USB_NUM_USBIP]       USB_BUFFER_PLACE_IN_SECTION;

/* Manager */
uint16_t  g_usb_hstd_enum_seq[USB_NUM_USBIP]; /* Enumeration request */
uint16_t  g_usb_hstd_device_descriptor[USB_NUM_USBIP][USB_DEVICESIZE / 2U]   USB_BUFFER_PLACE_IN_SECTION;
uint16_t  g_usb_hstd_config_descriptor[USB_NUM_USBIP][USB_CONFIGSIZE / 2U]   USB_BUFFER_PLACE_IN_SECTION;
uint16_t  g_usb_hstd_suspend_pipe[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];
uint16_t  g_usb_hstd_check_enu_result[USB_NUM_USBIP];
uint8_t   g_usb_hstd_class_data[USB_NUM_USBIP][CLSDATASIZE] USB_BUFFER_PLACE_IN_SECTION;
usb_utr_t g_usb_hstd_class_ctrl[USB_NUM_USBIP]              USB_BUFFER_PLACE_IN_SECTION;
uint16_t  g_usb_hstd_class_request[USB_NUM_USBIP][5]        USB_BUFFER_PLACE_IN_SECTION;

/* Condition compilation by the difference of the operating system */
 #if (BSP_CFG_RTOS == 0)
  #if USB_IP_EHCI_OHCI == 0
static uint16_t usb_shstd_reg_pointer[USB_NUM_USBIP];
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
 #endif                                /* (BSP_CFG_RTOS == 0) */
static usb_mgrinfo_t * p_usb_shstd_mgr_msg[USB_NUM_USBIP];
static uint16_t        usb_shstd_mgr_msginfo[USB_NUM_USBIP];
static usb_cb_t        usb_shstd_mgr_callback[USB_NUM_USBIP];
 #if (BSP_CFG_RTOS == 0)
static uint16_t usb_shstd_suspend_seq[USB_NUM_USBIP];
static uint16_t usb_shstd_resume_seq[USB_NUM_USBIP];
static void usb_hstd_susp_cont(usb_utr_t * ptr, uint16_t devaddr);
static void usb_hstd_resu_cont(usb_utr_t * ptr, uint16_t devaddr);

 #endif                                /* (BSP_CFG_RTOS == 0) */

static uint16_t usb_hstd_chk_device_class(usb_utr_t * ptr, usb_hcdreg_t * driver);
static void     usb_hstd_enumeration_err(uint16_t Rnum);

 #if (BSP_CFG_RTOS == 2)
static usb_er_t usb_hstd_cmd_submit(usb_utr_t * ptr);

 #else                                 /* (BSP_CFG_RTOS == 2) */
static uint16_t usb_hstd_cmd_submit(usb_utr_t * ptr, usb_cb_t complete);

 #endif /* (BSP_CFG_RTOS == 2) */

static uint16_t usb_hstd_chk_remote(usb_utr_t * ptr);

static void usb_hstd_mgr_rel_mpl(usb_utr_t * ptr, uint16_t n);

BSP_ALIGN_VARIABLE(4) uint32_t g_int_flag USB_BUFFER_PLACE_IN_SECTION;

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* Enumeration Table */
void (* g_usb_hstd_enumaration_process[8])(usb_utr_t *, uint16_t, uint16_t) =
{
    usb_hstd_enum_get_descriptor,    usb_hstd_enum_set_address,
    usb_hstd_enum_get_descriptor,    usb_hstd_enum_get_descriptor,
    usb_hstd_enum_get_descriptor,    usb_hstd_enum_get_descriptor,
    usb_hstd_enum_set_configuration, usb_hstd_enum_dummy_request,
};

 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
uint16_t         g_usb_disp_param_set[USB_NUM_USBIP];
usb_compliance_t g_usb_disp_param[USB_NUM_USBIP];
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Function Name   : usb_hstd_mgr_rel_mpl
 * Description     : Release a memory block.
 * Argument        : uint16_t n    : Error no.
 * Return          : none
 ******************************************************************************/
static void usb_hstd_mgr_rel_mpl (usb_utr_t * ptr, uint16_t n)
{
    usb_er_t err;

    (void) n;
    err = USB_REL_BLK(USB_MGR_MPL, (usb_mh_t) p_usb_shstd_mgr_msg[ptr->ip]);
    if (USB_OK != err)
    {
        USB_PRINTF1("### USB MGR rel_blk error: %d\n", n);
    }
}

/******************************************************************************
 * End of function usb_hstd_mgr_rel_mpl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_chgdevst_cb
 * Description     : Call the callback function specified by the argument given to
 * : the API usb_hstd_change_device_state.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
static void usb_hstd_mgr_chgdevst_cb (usb_utr_t * ptr)
{
    if (0 != usb_shstd_mgr_msginfo[ptr->ip])
    {
        (*usb_shstd_mgr_callback[ptr->ip])(ptr, USB_NULL, usb_shstd_mgr_msginfo[ptr->ip]);
        usb_shstd_mgr_msginfo[ptr->ip] = 0;
    }
}

/******************************************************************************
 * End of function usb_hstd_mgr_chgdevst_cb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_enumeration
 * Description     : Execute enumeration on the connected USB device.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 * Return          : uint16_t                 : Enumeration status.
 ******************************************************************************/
static uint16_t usb_hstd_enumeration (usb_utr_t * ptr)
{
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    uint16_t vendor_id;
    uint16_t product_id;
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

    uint16_t       md;
    uint16_t       flg = 0;
    usb_hcdreg_t * driver;
    uint16_t       enume_mode;         /* Enumeration mode (device state) */
    uint8_t      * descriptor_table = 0;
    uint16_t       devsel           = 0;
 #if USB_IP_EHCI_OHCI == 1
    uint16_t              rootport;
    st_usb_hci_device_t * p_dev_info;
    uint16_t              retval;
    uint8_t             * p_descriptor_table;
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
  #if (BSP_CFG_RTOS == 0)
    usb_instance_ctrl_t ctrl;
  #endif                               /* (BSP_CFG_RTOS == 0) */
 #endif                                /* USB_IP_EHCI_OHCI == 1 */

    /* Attach Detect Mode */
    enume_mode = USB_NONDEVICE;
 #if USB_IP_EHCI_OHCI == 1
    FSP_PARAMETER_NOT_USED(flg);
    FSP_PARAMETER_NOT_USED(descriptor_table);
    FSP_PARAMETER_NOT_USED(devsel);

    /* Get root port number from device addr */
    rootport = usb_hstd_get_rootport(g_usb_hstd_device_addr[ptr->ip]);

    /* Manager Mode Change */
    switch (p_usb_shstd_mgr_msg[ptr->ip]->result)
    {
        case USB_CTRL_END:
        {
            enume_mode = USB_DEVICEENUMERATION;
            switch (g_usb_hstd_enum_seq[ptr->ip])
            {
                case 0:                /* Receive Device Descriptor */
                {
                    usb_hstd_enum_set_address(ptr, (uint16_t) USB_DEVICE_0, g_usb_hstd_device_addr[ptr->ip]);
                    break;
                }

                case 1:                /* Set Address Result */
                {
                    /* Device descriptor information is copied */
                    p_dev_info = r_usb_hstd_hci_get_device_infomation(g_usb_hstd_device_addr[ptr->ip]);
                    memcpy(&p_dev_info->devicedesc,
                           g_usb_hstd_device_descriptor[ptr->ip],
                           sizeof(p_dev_info->devicedesc));

                    /* Set device speed */
                    usb_hstd_set_rootport(g_usb_hstd_device_addr[ptr->ip], rootport);

                    /* Get Descriptor */
                    usb_hstd_enum_get_descriptor(ptr, g_usb_hstd_device_addr[ptr->ip], g_usb_hstd_enum_seq[ptr->ip]);
                    break;
                }

                case 2:                /* Receive Device Descriptor(18) */
                {
                    usb_hstd_enum_get_descriptor(ptr, g_usb_hstd_device_addr[ptr->ip], g_usb_hstd_enum_seq[ptr->ip]);
                    break;
                }

                case 3:                /* Receive Configuration Descriptor(9) */
                {
                    usb_hstd_enum_get_descriptor(ptr, g_usb_hstd_device_addr[ptr->ip], g_usb_hstd_enum_seq[ptr->ip]);
                    break;
                }

                case 4:                /* Receive Configuration Descriptor(xx) */
                {
  #ifdef USB_HOST_COMPLIANCE_MODE
                    p_descriptor_table = (uint8_t *) g_usb_hstd_device_descriptor[ptr->ip];

                    /* If 'vendor_id' and 'product_id' value is defined by PET, */
                    /*    system works for compliance test mode. */
                    /* Values ??defined by PET is the following. */
                    /* vendor_id : 0x1A0A  */
                    /* product_id : 0x0101 - 0x0108 , 0x0200 */

                    vendor_id = (uint16_t) (p_descriptor_table[USB_DEV_ID_VENDOR_L] +
                                            ((uint16_t) p_descriptor_table[USB_DEV_ID_VENDOR_H] << 8));

                    if (0x1A0A == vendor_id)
                    {
                        product_id = (uint16_t) (p_descriptor_table[USB_DEV_ID_PRODUCT_L] +
                                                 ((uint16_t) p_descriptor_table[USB_DEV_ID_PRODUCT_H] << 8));

                        if ((0x0100 < product_id) && (product_id < 0x0109))
                        {
                            g_usb_hstd_enum_seq[ptr->ip] = 6; /* Enumeration End */
                            usb_hstd_electrical_test_mode(ptr, product_id);
                            enume_mode = USB_NOTTPL;
                            break;
                        }

                        if (0x0200 == product_id)
                        {
                            g_usb_hstd_enum_seq[ptr->ip] = 5; /* Skip EnumSeq 5 */
                            p_descriptor_table           = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
                            usb_hstd_enum_set_configuration(ptr,
                                                            g_usb_hstd_device_addr[ptr->ip],
                                                            (uint16_t) (p_descriptor_table[USB_CON_B_CONFIGURATION_VALUE
                                                                        ]));
                            break;
                        }
                    }
  #endif                               /* USB_HOST_COMPLIANCE_MODE */

                    /* Device descriptor and Config descriptor information is copied. */
                    p_dev_info = r_usb_hstd_hci_get_device_infomation(g_usb_hstd_device_addr[ptr->ip]);

                    /* Device Descriptor copy */
                    memcpy(&p_dev_info->devicedesc,
                           g_usb_hstd_device_descriptor[ptr->ip],
                           sizeof(p_dev_info->devicedesc));

                    /* Configuration Descroptor copy */
                    memcpy(&p_dev_info->rawconfigdesc,
                           g_usb_hstd_config_descriptor[ptr->ip],
                           sizeof(p_dev_info->rawconfigdesc));

                    /* Driver open */
                    retval = USB_ERROR;
                    for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                    {
                        driver = &g_usb_hstd_device_drv[ptr->ip][md];
                        if (USB_DETACHED == driver->devstate)
                        {
                            /* In this function, check device class of enumeration flow move to class */

                            retval = usb_hstd_chk_device_class(ptr, driver);

                            /* "R_USB_HstdReturnEnuMGR()" is used to return */
                            if (USB_OK == retval)
                            {
                                driver->rootport = rootport;
                                driver->devaddr  = g_usb_hstd_device_addr[ptr->ip];
                                break;
                            }
                        }
                    }

                    if (USB_ERROR == retval)
                    {
  #ifdef USB_HOST_COMPLIANCE_MODE
                        g_usb_hstd_enum_seq[ptr->ip] = 6; /* Enumeration End */
                        enume_mode = USB_NOTTPL;
  #else /* USB_HOST_COMPLIANCE_MODE */
                        g_usb_hstd_enum_seq[ptr->ip] = 5; /* Skip EnumSeq 5 */
                        p_descriptor_table           = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
                        usb_hstd_enum_set_configuration(ptr,
                                                        g_usb_hstd_device_addr[ptr->ip],
                                                        (uint16_t) (p_descriptor_table[USB_CON_B_CONFIGURATION_VALUE]));
  #endif                               /* USB_HOST_COMPLIANCE_MODE */
                    }

                    break;
                }

                case 5:                /* Class Check Result */
                {
                    switch (g_usb_hstd_check_enu_result[ptr->ip])
                    {
                        case USB_OK:
                        {
                            p_descriptor_table = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
                            usb_hstd_enum_set_configuration(ptr,
                                                            g_usb_hstd_device_addr[ptr->ip],
                                                            (uint16_t) (p_descriptor_table[USB_CON_B_CONFIGURATION_VALUE
                                                                        ]));
                            break;
                        }

                        case USB_ERROR:
                        {
                            enume_mode = USB_NOTTPL;
                            break;
                        }

                        default:
                        {
                            enume_mode = USB_NONDEVICE;
                            break;
                        }
                    }

                    break;
                }

                case 6:                /* Set Configuration Result */
                {
                    /* Device enumeration function */
                    /* USB_PRINTF0(" Configured Device\n"); */
                    for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                    {
                        driver = &g_usb_hstd_device_drv[ptr->ip][md];
                        if (g_usb_hstd_device_addr[ptr->ip] == driver->devaddr)
                        {
                            /* Device state */
                            g_usb_hstd_device_info[ptr->ip][g_usb_hstd_device_addr[ptr->ip]][1] = USB_CONFIGURED;

                            /* Device speed */
                            g_usb_hstd_device_info[ptr->ip][g_usb_hstd_device_addr[ptr->ip]][4] =
                                g_usb_hstd_device_speed[ptr->ip];

                            /* Device state */
                            driver->devstate = USB_CONFIGURED;
                            (*driver->devconfig)(ptr, g_usb_hstd_device_addr[ptr->ip], (uint16_t) USB_NO_ARG); /* Call Back */
                            break;
                        }
                    }

                    enume_mode = USB_COMPLETEPIPESET;
                    break;
                }

                default:
                {
                    break;
                }
            }

            g_usb_hstd_enum_seq[ptr->ip]++;
            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF0("### Enumeration is stoped(SETUP or DATA-ERROR)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }

        case USB_DATA_OVR:
        {
            USB_PRINTF0("### Enumeration is stoped(receive data over)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }

        case USB_DATA_STALL:
        {
            USB_PRINTF0("### Enumeration is stoped(SETUP or DATA-STALL)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }

        default:
        {
            USB_PRINTF0("### Enumeration is stoped(result error)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }
    }

    return enume_mode;
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
    /* Manager Mode Change */
    switch (p_usb_shstd_mgr_msg[ptr->ip]->result)
    {
        case USB_CTRL_END:
        {
            enume_mode = USB_DEVICEENUMERATION;
            switch (g_usb_hstd_enum_seq[ptr->ip])
            {
                /* Receive Device Descriptor */
                case 0:
                {
                    break;
                }

                /* Set Address */
                case 1:
                {
                    descriptor_table = (uint8_t *) g_usb_hstd_device_descriptor[ptr->ip];
                    devsel           = (uint16_t) (g_usb_hstd_device_addr[ptr->ip] << USB_DEVADDRBIT);

                    /* Set device speed */
                    usb_hstd_set_dev_addr(ptr, devsel, g_usb_hstd_device_speed[ptr->ip]);
                    g_usb_hstd_dcp_register[ptr->ip][g_usb_hstd_device_addr[ptr->ip]] =
                        (uint16_t) ((uint16_t) (descriptor_table[7] & USB_MAXPFIELD) | devsel);
                    break;
                }

                /* Receive Device Descriptor(18) */
                case 2:
                {
                    break;
                }

                /* Receive Configuration Descriptor(9) */
                case 3:
                {
                    break;
                }

                /* Receive Configuration Descriptor(xx) */
                case 4:
                {
  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                    descriptor_table = (uint8_t *) g_usb_hstd_device_descriptor[ptr->ip];

                    /* If 'vendor_id' and 'product_id' value is defined by PET, */
                    /*    system works for compliance test mode. */
                    /* Values ??defined by PET is the following. */
                    /* vendor_id : 0x1A0A  */
                    /* product_id : 0x0101 - 0x0108 , 0x0200 */

                    vendor_id = (uint16_t) (descriptor_table[USB_DEV_ID_VENDOR_L] +
                                            ((uint16_t) descriptor_table[USB_DEV_ID_VENDOR_H] << 8));

                    if (0x1A0A == vendor_id)
                    {
                        product_id = (uint16_t) (descriptor_table[USB_DEV_ID_PRODUCT_L] +
                                                 ((uint16_t) descriptor_table[USB_DEV_ID_PRODUCT_H] << 8));

                        descriptor_table = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
   #if USB_CFG_ELECTRICAL == USB_CFG_ENABLE
                        if ((0x0100 < product_id) && (product_id < 0x0109))
                        {
                            usb_hstd_electrical_test_mode(ptr, product_id);
                            enume_mode = USB_NOTTPL;
                            break;
                        }
   #endif                              /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */

                        if (0x0200 == product_id)
                        {
                            g_usb_hstd_enum_seq[ptr->ip]++;
                            break;
                        }
                    }
  #endif                               /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */

                    /* Driver open */
  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                    g_usb_disp_param_set[ptr->ip] = USB_OFF;
  #endif                               /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

                    flg = 0U;

                    /* WAIT_LOOP */
                    for (md = 0; (md < g_usb_hstd_device_num[ptr->ip]) && (0U == flg); md++)
                    {
                        driver = &g_usb_hstd_device_drv[ptr->ip][md];
                        if (USB_DETACHED == driver->devstate)
                        {
                            uint16_t retval;
                            retval = usb_hstd_chk_device_class(ptr, driver);
  #if (BSP_CFG_RTOS == 2)
                            if (USB_OK == retval)
                            {
                                driver->devaddr = g_usb_hstd_device_addr[ptr->ip];
                                flg             = 1; /* break; */
                            }
  #else /* (BSP_CFG_RTOS == 2) */
                            g_usb_hstd_check_enu_result[ptr->ip] = USB_OK;

                            /* In this function, check device class of       */
                            /*              enumeration flow move to class   */
                            /* "usb_hstd_return_enu_mgr()" is used to return */
                            if (USB_OK == retval)
                            {
                                usb_shstd_reg_pointer[ptr->ip] = md;
                                flg = 1; /* break; */
                            }
  #endif /* (BSP_CFG_RTOS == 2) */
                        }
                    }

  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                    if (USB_ON == g_usb_disp_param_set[ptr->ip])
                    {
                        usb_compliance_disp((void *) &g_usb_disp_param[ptr->ip]);
                    }
  #endif                               /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

  #if (BSP_CFG_RTOS == 0)
                    if (1 != flg)
                    {
                        ctrl.device_address = (uint8_t) g_usb_hstd_device_addr[ptr->ip]; /* USB Device address */
                        ctrl.module_number  = ptr->ip;                                   /* Module number setting */
                        usb_set_event(USB_STATUS_NOT_SUPPORT, &ctrl);                    /* Set Event()  */

   #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                        g_usb_hstd_enum_seq[ptr->ip] = g_usb_hstd_enum_seq[ptr->ip] + 2;
   #else /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
                        g_usb_hstd_enum_seq[ptr->ip]++;
   #endif                              /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
                    }
  #endif                               /* (BSP_CFG_RTOS == 0) */
                    break;
                }

                /* Class Check Result */
                case 5:
                {
  #if (BSP_CFG_RTOS == 0)
                    switch (g_usb_hstd_check_enu_result[ptr->ip])
                    {
                        case USB_OK:
                        {
                            driver = &g_usb_hstd_device_drv[ptr->ip][usb_shstd_reg_pointer[ptr->ip]];

                            /* Root port */
                            driver->devaddr = g_usb_hstd_device_addr[ptr->ip];
                            break;
                        }

                        case USB_ERROR:
                        {
                            enume_mode = USB_NOTTPL;
                            break;
                        }

                        default:
                        {
                            enume_mode = USB_NONDEVICE;
                            break;
                        }
                    }
  #endif                               /* (BSP_CFG_RTOS == 0) */
                    break;
                }

                /* Set Configuration */
                case 6:
                {
                    /* Device enumeration function */
                    USB_PRINTF0(" Configured Device\n");

                    /* WAIT_LOOP */
                    for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                    {
                        driver = &g_usb_hstd_device_drv[ptr->ip][md];
                        if (g_usb_hstd_device_addr[ptr->ip] == driver->devaddr)
                        {
                            /* Device state */
                            g_usb_hstd_device_info[ptr->ip][g_usb_hstd_device_addr[ptr->ip]][1] = USB_CONFIGURED;

                            /* Device speed */
                            g_usb_hstd_device_info[ptr->ip][g_usb_hstd_device_addr[ptr->ip]][4] =
                                g_usb_hstd_device_speed[ptr->ip];

                            /* Device state */
                            driver->devstate = USB_CONFIGURED;

                            /* Call Back */
                            (*driver->devconfig)(ptr, g_usb_hstd_device_addr[ptr->ip], (uint16_t) USB_NO_ARG);

                            return USB_COMPLETEPIPESET;
                        }
                    }

                    enume_mode = USB_COMPLETEPIPESET;
                    break;
                }

                default:
                {
                    break;
                }
            }

            g_usb_hstd_enum_seq[ptr->ip]++;

            /* Device Enumeration */
            if (USB_DEVICEENUMERATION == enume_mode)
            {
                switch (g_usb_hstd_enum_seq[ptr->ip])
                {
                    case 1:
                    {
                        (*g_usb_hstd_enumaration_process[1])(ptr,
                                                             (uint16_t) USB_DEVICE_0,
                                                             g_usb_hstd_device_addr[ptr->ip]);

                        descriptor_table = (uint8_t *) g_usb_hstd_device_descriptor[ptr->ip];
                        devsel           = (uint16_t) (g_usb_hstd_device_addr[ptr->ip] << USB_DEVADDRBIT);

                        /* Set device speed */
                        usb_hstd_set_dev_addr(ptr, devsel, g_usb_hstd_device_speed[ptr->ip]);
                        g_usb_hstd_dcp_register[ptr->ip][g_usb_hstd_device_addr[ptr->ip]] =
                            (uint16_t) ((uint16_t) (descriptor_table[7] & USB_MAXPFIELD) | devsel);
                        break;
                    }

                    case 5:
                    {
  #if (BSP_CFG_RTOS == 2)
                        (*g_usb_hstd_enumaration_process[5])(ptr,
                                                             g_usb_hstd_device_addr[ptr->ip],
                                                             g_usb_hstd_enum_seq[ptr->ip]);
  #endif                               /* (BSP_CFG_RTOS == 2) */
                        break;
                    }

                    case 6:
                    {
                        descriptor_table = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];

                        /* Device state */
                        g_usb_hstd_device_info[ptr->ip][g_usb_hstd_device_addr[ptr->ip]][2] = descriptor_table[5];
                        (*g_usb_hstd_enumaration_process[6])(ptr,
                                                             g_usb_hstd_device_addr[ptr->ip],
                                                             (uint16_t) (descriptor_table[5]));
                        break;
                    }

  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                    case 7:
                    {
                        enume_mode = USB_NOTTPL;
                        break;
                    }
  #endif                               /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
                    default:
                    {
                        (*g_usb_hstd_enumaration_process[g_usb_hstd_enum_seq[ptr->ip]])(ptr,
                                                                                        g_usb_hstd_device_addr[ptr->ip],
                                                                                        g_usb_hstd_enum_seq[ptr->ip]);
                        break;
                    }
                }
            }

            break;
        }

        case USB_DATA_ERR:
        {
            USB_PRINTF0("### Enumeration is stopped(SETUP or DATA-ERROR)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }

        case USB_DATA_OVR:
        {
            USB_PRINTF0("### Enumeration is stopped(receive data over)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }

        case USB_DATA_STALL:
        {
            USB_PRINTF0("### Enumeration is stopped(SETUP or DATA-STALL)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }

        default:
        {
            USB_PRINTF0("### Enumeration is stopped(result error)\n");
            usb_hstd_enumeration_err(g_usb_hstd_enum_seq[ptr->ip]);
            break;
        }
    }
    return enume_mode;
 #endif                                /* USB_IP_EHCI_OHCI == 1 */
}

/******************************************************************************
 * End of function usb_hstd_enumeration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_enumeration_err
 * Description     : Output error information when enumeration error occurred.
 * Argument        : uint16_t Rnum             : enumeration sequence
 * Return          : none
 ******************************************************************************/
static void usb_hstd_enumeration_err (uint16_t Rnum)
{
    (void) Rnum;

    /* Condition compilation by the difference of useful function */
 #if defined(USB_DEBUG_ON)
    switch (Rnum)
    {
        case 0:
        {
            USB_PRINTF0(" Get_DeviceDescrip(8)\n");
            break;
        }

        case 1:
        {
            USB_PRINTF0(" Set_Address\n");
            break;
        }

        case 2:
        {
            USB_PRINTF0(" Get_DeviceDescrip(18)\n");
            break;
        }

        case 3:
        {
            USB_PRINTF0(" Get_ConfigDescrip(9)\n");
            break;
        }

        case 4:
        {
            USB_PRINTF0(" Get_ConfigDescrip(xx)\n");
            break;
        }

        case 5:
        {
            USB_PRINTF0(" Get_DeviceDescrip(8-2)\n");
            break;                     /* Device enumeration function */
        }

        case 6:
        {
            USB_PRINTF0(" Set_Configuration\n");
            break;
        }

        default:
        {}
        break;
    }
 #endif                                /* defined(USB_DEBUG_ON) */
}

/******************************************************************************
 * End of function usb_hstd_enumeration_err
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_chk_device_class
 * Description     : Interface class search
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure.
 *               : usb_hcdreg_t *driver     : Class driver
 * Return          : uint16_t                 : USB_OK / USB_ERROR
 ******************************************************************************/
static uint16_t usb_hstd_chk_device_class (usb_utr_t * ptr, usb_hcdreg_t * driver)
{
    uint8_t  * descriptor_table;
    uint16_t   total_length1;
    uint16_t   total_length2;
    uint16_t   result = USB_ERROR;
    uint16_t   hub_device;
    uint16_t * table[9];
    uint16_t   tmp4;
    uint16_t   tmp5;
    uint16_t   tmp6;
    uint16_t   vendor_id;
    uint16_t   product_id;
    uint16_t   id_check = 0;
    uint16_t   i;

    descriptor_table = (uint8_t *) &g_usb_hstd_device_descriptor[ptr->ip];

    /* Device class check */
    tmp4       = descriptor_table[USB_DEV_B_DEVICE_CLASS];
    tmp5       = descriptor_table[USB_DEV_B_DEVICE_SUBCLASS];
    tmp6       = descriptor_table[USB_DEV_B_DEVICE_PROTOCOL];
    hub_device = USB_OK;
    if (((USB_VALUE_FFH == tmp4) && (USB_VALUE_FFH == tmp5)) && (USB_VALUE_FFH == tmp6))
    {
        USB_PRINTF0("*** Vendor specific device.\n\n");
    }
    else if (((USB_IFCLS_HUB == tmp4) && (0X00 == tmp5)) && (0X00 == tmp6))
    {
        USB_PRINTF0("*** Full-Speed HUB device.\n\n");
        hub_device = USB_FSHUB;
    }
    else if (((USB_IFCLS_HUB == tmp4) && (0x00 == tmp5)) && (0x01 == tmp6))
    {
        USB_PRINTF0("*** High-Speed single TT device.\n\n");
        hub_device = USB_HSHUBS;
    }
    else if (((USB_IFCLS_HUB == tmp4) && (0x00 == tmp5)) && (0x02 == tmp6))
    {
        USB_PRINTF0("*** High-Speed multiple TT device.\n\n");
        hub_device = USB_HSHUBM;
    }
    else if (((0 != tmp4) || (0 != tmp5)) || (0 != tmp6))
    {
        USB_PRINTF0("### Device class information error!\n\n");
    }
    else
    {
        /* Non */
    }

    vendor_id = (uint16_t) (descriptor_table[USB_DEV_ID_VENDOR_L] +
                            ((uint16_t) descriptor_table[USB_DEV_ID_VENDOR_H] << 8));
    product_id = (uint16_t) (descriptor_table[USB_DEV_ID_PRODUCT_L] +
                             ((uint16_t) descriptor_table[USB_DEV_ID_PRODUCT_H] << 8));

    /* Check PET connect */
    if ((USB_PET_VID == vendor_id) && (USB_PET_PID == product_id))
    {
        result = USB_OK;
    }
    else
    {
        id_check = USB_ERROR;

        /* WAIT_LOOP */
        for (i = 0; i < driver->p_tpl[0]; i++)
        {
            if ((USB_NOVENDOR == driver->p_tpl[(i * 2) + 2]) || (driver->p_tpl[(i * 2) + 2] == vendor_id))
            {
                if ((USB_NOPRODUCT == driver->p_tpl[(i * 2) + 3]) || (driver->p_tpl[(i * 2) + 3] == product_id))
                {
                    id_check = USB_OK;
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                    g_usb_disp_param[ptr->ip].status = USB_COMPLIANCETEST_TPL;
                    g_usb_disp_param[ptr->ip].pid    = product_id;
                    g_usb_disp_param[ptr->ip].vid    = vendor_id;
                    g_usb_disp_param_set[ptr->ip]    = USB_ON;
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
                }
            }
        }
    }

    if (USB_OK == result)
    {
        return result;
    }

    if (USB_ERROR == id_check)
    {
        USB_PRINTF0("### Not support device\n");
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
        if (USB_IFCLS_HUB == descriptor_table[4])
        {
            g_usb_disp_param[ptr->ip].status = USB_COMPLIANCETEST_HUB;
            g_usb_disp_param[ptr->ip].pid    = product_id;
            g_usb_disp_param[ptr->ip].vid    = vendor_id;
            g_usb_disp_param_set[ptr->ip]    = USB_ON;
        }
        else
        {
            g_usb_disp_param[ptr->ip].status = USB_COMPLIANCETEST_NOTTPL;
            g_usb_disp_param[ptr->ip].pid    = product_id;
            g_usb_disp_param[ptr->ip].vid    = vendor_id;
            g_usb_disp_param_set[ptr->ip]    = USB_ON;
        }
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

        return USB_ERROR;
    }

    descriptor_table = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
    total_length1    = 0;
    total_length2    = (uint16_t) (descriptor_table[USB_DEV_W_TOTAL_LENGTH_L] +
                                   ((uint16_t) descriptor_table[USB_DEV_W_TOTAL_LENGTH_H] << 8));

    if (total_length2 > USB_CONFIGSIZE)
    {
        total_length2 = USB_CONFIGSIZE;
    }

    /* Search within configuration total-length */
    /* WAIT_LOOP */
    while (total_length1 < total_length2)
    {
        switch (descriptor_table[total_length1 + 1])
        {
            /* Configuration Descriptor ? */
            case USB_DT_CONFIGURATION:
            {
                table[1] = (uint16_t *) &descriptor_table[total_length1];
                break;
            }

            /* Interface Descriptor ? */
            case USB_DT_INTERFACE:
            {
                if ((uint16_t) descriptor_table[total_length1 + 5] == driver->ifclass)
                {
                    result   = USB_ERROR;
                    table[0] = (uint16_t *) &g_usb_hstd_device_descriptor[ptr->ip];
                    table[2] = (uint16_t *) &descriptor_table[total_length1];
                    table[3] = &result;
                    table[4] = &hub_device;
                    table[6] = &g_usb_hstd_device_speed[ptr->ip];
                    table[7] = &g_usb_hstd_device_addr[ptr->ip];
                    (*driver->classcheck)(ptr, (uint16_t **) &table);

                    /* Interface Class */
                    g_usb_hstd_device_info[ptr->ip][g_usb_hstd_device_addr[ptr->ip]][3] =
                        descriptor_table[total_length1 +
                                         5];

                    return result;
                }

                /*          USB_PRINTF2("*** Interface class is 0x%02x (not 0x%02x)\n",
                 * descriptor_table[total_length1 + 5], driver->ifclass);*/
                break;
            }

            default:
            {
                break;
            }
        }

        total_length1 = (uint16_t) (total_length1 + descriptor_table[total_length1]);
        if (0 == descriptor_table[total_length1])
        {
            break;
        }
    }

    return USB_ERROR;
}

/******************************************************************************
 * End of function usb_hstd_chk_device_class
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_notif_ator_detach
 * Description     : Notify MGR (manager) task that attach or detach occurred.
 * Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t result   : Result.
 * Return          : none
 ******************************************************************************/
void usb_hstd_notif_ator_detach (usb_utr_t * ptr, uint16_t result)
{
    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_MGR_AORDETACH, USB_NULL, result);
}

/******************************************************************************
 * End of function usb_hstd_notif_ator_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_ovcr_notifiation
 * Description     : Notify MGR (manager) task that overcurrent was generated
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hstd_ovcr_notifiation (usb_utr_t * ptr)
{
    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_MGR_OVERCURRENT, USB_NULL, (uint16_t) 0U);
}

/******************************************************************************
 * End of function usb_hstd_ovcr_notifiation
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_status_result
 * Description     : This is a callback as a result of calling
 *               : usb_hstd_change_device_state. This notifies the MGR (manager)
 *               : task that the change of USB Device status completed.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t     data1   : No use.
 *               : uint16_t     result  : Result.
 * Return          : none
 ******************************************************************************/
void usb_hstd_status_result (usb_utr_t * ptr, uint16_t data1, uint16_t result)
{
    (void) data1;
    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_MGR_STATUSRESULT, USB_NULL, result);
}

/******************************************************************************
 * End of function usb_hstd_status_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_submit_result
 * Description     : Callback after completion of a standard request.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     data1   : Not used
 *               : uint16_t     data2t  : Not used
 * Return          : none
 ******************************************************************************/
void usb_hstd_submit_result (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    (void) data1;
    (void) data2;

    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_MGR_SUBMITRESULT, ptr->keyword, ptr->status);
}

/******************************************************************************
 * End of function usb_hstd_submit_result
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_enum_get_descriptor
 * Description     : Send GetDescriptor to the connected USB device.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     addr        : Device Address
 *               : uint16_t     cnt_value   : Enumeration sequence
 * Return          : none
 ******************************************************************************/
void usb_hstd_enum_get_descriptor (usb_utr_t * ptr, uint16_t addr, uint16_t cnt_value)
{
    uint8_t * data_table;

    switch (cnt_value)
    {
 #if  USB_IP_EHCI_OHCI == 1
        case 0:
        /* continue */
        case 4:
        {
            usb_shstd_std_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1] = (uint16_t) USB_DEV_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2] = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3] = (uint16_t) USB_VALUE_40H;
            if (usb_shstd_std_request[ptr->ip][3] > USB_DEVICESIZE)
            {
                usb_shstd_std_request[ptr->ip][3] = USB_DEVICESIZE;
            }

            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_device_descriptor[ptr->ip];
            break;
        }

        case 1:
        {
            usb_shstd_std_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1] = (uint16_t) USB_DEV_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2] = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3] = (uint16_t) 0x0012;
            if (usb_shstd_std_request[ptr->ip][3] > USB_DEVICESIZE)
            {
                usb_shstd_std_request[ptr->ip][3] = USB_DEVICESIZE;
            }

            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_device_descriptor[ptr->ip];
            break;
        }

        case 2:
        {
            usb_shstd_std_request[ptr->ip][0]        = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1]        = (uint16_t) USB_CONF_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2]        = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3]        = (uint16_t) 0x0009;
            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_config_descriptor[ptr->ip];
            break;
        }

        case 3:
        {
            data_table = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
            usb_shstd_std_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1] = (uint16_t) USB_CONF_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2] = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3] = (uint16_t) (((uint16_t) data_table[3] << 8) + (uint16_t) data_table[2]);
            if (usb_shstd_std_request[ptr->ip][3] > USB_CONFIGSIZE)
            {
                usb_shstd_std_request[ptr->ip][3] = USB_CONFIGSIZE;
                USB_PRINTF0("***WARNING Descriptor size over !\n");
            }

            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_config_descriptor[ptr->ip];
            break;
        }
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
        case 0:

        /* continue */
        case 1:

        /* continue */
        case 5:
        {
            usb_shstd_std_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1] = (uint16_t) USB_DEV_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2] = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3] = (uint16_t) USB_VALUE_40H;
            if (usb_shstd_std_request[ptr->ip][3] > USB_DEVICESIZE)
            {
                usb_shstd_std_request[ptr->ip][3] = USB_DEVICESIZE;
            }

            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_device_descriptor[ptr->ip];
            break;
        }

        case 2:
        {
            usb_shstd_std_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1] = (uint16_t) USB_DEV_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2] = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3] = (uint16_t) 0x0012;
            if (usb_shstd_std_request[ptr->ip][3] > USB_DEVICESIZE)
            {
                usb_shstd_std_request[ptr->ip][3] = USB_DEVICESIZE;
            }

            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_device_descriptor[ptr->ip];
            break;
        }

        case 3:
        {
            usb_shstd_std_request[ptr->ip][0]        = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1]        = (uint16_t) USB_CONF_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2]        = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3]        = (uint16_t) 0x0009;
            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_config_descriptor[ptr->ip];
            break;
        }

        case 4:
        {
            data_table = (uint8_t *) g_usb_hstd_config_descriptor[ptr->ip];
            usb_shstd_std_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
            usb_shstd_std_request[ptr->ip][1] = (uint16_t) USB_CONF_DESCRIPTOR;
            usb_shstd_std_request[ptr->ip][2] = (uint16_t) 0x0000;
            usb_shstd_std_request[ptr->ip][3] = (uint16_t) (((uint16_t) data_table[3] << 8) + (uint16_t) data_table[2]);
            if (usb_shstd_std_request[ptr->ip][3] > USB_CONFIGSIZE)
            {
                usb_shstd_std_request[ptr->ip][3] = USB_CONFIGSIZE;
                USB_PRINTF0("***WARNING Descriptor size over !\n");
            }

            usb_shstd_std_req_msg[ptr->ip].p_tranadr = g_usb_hstd_config_descriptor[ptr->ip];
            break;
        }
 #endif                                /* USB_IP_EHCI_OHCI == 1 */

        default:
        {
            return;
            break;
        }
    }

    usb_shstd_std_request[ptr->ip][4]       = addr;
    usb_shstd_std_req_msg[ptr->ip].keyword  = (uint16_t) USB_PIPE0;
    usb_shstd_std_req_msg[ptr->ip].tranlen  = (uint32_t) usb_shstd_std_request[ptr->ip][3];
    usb_shstd_std_req_msg[ptr->ip].p_setup  = usb_shstd_std_request[ptr->ip];
    usb_shstd_std_req_msg[ptr->ip].status   = USB_DATA_NONE;
    usb_shstd_std_req_msg[ptr->ip].complete = (usb_cb_t) &usb_hstd_submit_result;
    usb_shstd_std_req_msg[ptr->ip].segment  = USB_TRAN_END;

    usb_shstd_std_req_msg[ptr->ip].ipp           = ptr->ipp;
    usb_shstd_std_req_msg[ptr->ip].ip            = ptr->ip;
    usb_shstd_std_req_msg[ptr->ip].p_transfer_rx = ptr->p_transfer_rx;
    usb_shstd_std_req_msg[ptr->ip].p_transfer_tx = ptr->p_transfer_tx;

 #if USB_IP_EHCI_OHCI == 1
    usb_hstd_transfer_start(&usb_shstd_std_req_msg[ptr->ip]);
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
    usb_hstd_transfer_start_req(&usb_shstd_std_req_msg[ptr->ip]);
 #endif /* USB_IP_EHCI_OHCI == 1 */
}

/******************************************************************************
 * End of function usb_hstd_enum_get_descriptor
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_enum_set_address
 * Description     : Send SetAddress to the connected USB device.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     addr    : Device Address.
 *               : uint16_t     setaddr : New address.
 * Return          : none
 ******************************************************************************/
void usb_hstd_enum_set_address (usb_utr_t * ptr, uint16_t addr, uint16_t setaddr)
{
    usb_shstd_std_request[ptr->ip][0]        = USB_SET_ADDRESS | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
    usb_shstd_std_request[ptr->ip][1]        = setaddr;
    usb_shstd_std_request[ptr->ip][2]        = (uint16_t) 0x0000;
    usb_shstd_std_request[ptr->ip][3]        = (uint16_t) 0x0000; /* wLength */
    usb_shstd_std_request[ptr->ip][4]        = addr;
    usb_shstd_std_req_msg[ptr->ip].keyword   = (uint16_t) USB_PIPE0;
    usb_shstd_std_req_msg[ptr->ip].p_tranadr = USB_NULL;
    usb_shstd_std_req_msg[ptr->ip].tranlen   = 0;
    usb_shstd_std_req_msg[ptr->ip].p_setup   = usb_shstd_std_request[ptr->ip];
    usb_shstd_std_req_msg[ptr->ip].status    = USB_DATA_NONE;
    usb_shstd_std_req_msg[ptr->ip].complete  = (usb_cb_t) &usb_hstd_submit_result;
    usb_shstd_std_req_msg[ptr->ip].segment   = USB_TRAN_END;

    usb_shstd_std_req_msg[ptr->ip].ipp = ptr->ipp;
    usb_shstd_std_req_msg[ptr->ip].ip  = ptr->ip;

 #if USB_IP_EHCI_OHCI == 1
    usb_hstd_transfer_start(&usb_shstd_std_req_msg[ptr->ip]);
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
    usb_hstd_transfer_start_req(&usb_shstd_std_req_msg[ptr->ip]);
 #endif /* USB_IP_EHCI_OHCI == 1 */
}

/******************************************************************************
 * End of function usb_hstd_enum_set_address
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_enum_set_configuration
 * Description     : Send SetConfiguration to the connected USB device.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     addr    : Device Address.
 *               : uint16_t     confnum : Configuration number.
 * Return          : none
 ******************************************************************************/
void usb_hstd_enum_set_configuration (usb_utr_t * ptr, uint16_t addr, uint16_t confnum)
{
    usb_shstd_std_request[ptr->ip][0]        = USB_SET_CONFIGURATION | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
    usb_shstd_std_request[ptr->ip][1]        = confnum;
    usb_shstd_std_request[ptr->ip][2]        = (uint16_t) 0x0000;
    usb_shstd_std_request[ptr->ip][3]        = (uint16_t) 0x0000; /* wLength */
    usb_shstd_std_request[ptr->ip][4]        = addr;
    usb_shstd_std_req_msg[ptr->ip].keyword   = (uint16_t) USB_PIPE0;
    usb_shstd_std_req_msg[ptr->ip].p_tranadr = USB_NULL;
    usb_shstd_std_req_msg[ptr->ip].tranlen   = 0;
    usb_shstd_std_req_msg[ptr->ip].p_setup   = usb_shstd_std_request[ptr->ip];
    usb_shstd_std_req_msg[ptr->ip].status    = USB_DATA_NONE;
    usb_shstd_std_req_msg[ptr->ip].complete  = (usb_cb_t) &usb_hstd_submit_result;
    usb_shstd_std_req_msg[ptr->ip].segment   = USB_TRAN_END;

    usb_shstd_std_req_msg[ptr->ip].ipp = ptr->ipp;
    usb_shstd_std_req_msg[ptr->ip].ip  = ptr->ip;
 #if USB_IP_EHCI_OHCI == 1
    usb_hstd_transfer_start(&usb_shstd_std_req_msg[ptr->ip]);
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
    usb_hstd_transfer_start_req(&usb_shstd_std_req_msg[ptr->ip]);
 #endif /* USB_IP_EHCI_OHCI == 1 */
}

/******************************************************************************
 * End of function usb_hstd_enum_set_configuration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_enum_dummy_request
 * Description     : Dummy function.
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     addr        : Device Address
 *               : uint16_t     cnt_value   : Enumeration Sequence
 * Return          : none
 ******************************************************************************/
void usb_hstd_enum_dummy_request (usb_utr_t * ptr, uint16_t addr, uint16_t cnt_value)
{
    /* Non */
    (void) *ptr;
    (void) addr;
    (void) cnt_value;
}

/******************************************************************************
 * End of function usb_hstd_enum_dummy_request
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_suspend
 * Description     : Suspend request
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     info    : Info for release of memory block.
 * Return          : none
 ******************************************************************************/
void usb_hstd_mgr_suspend (usb_utr_t * ptr, uint16_t info)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t devaddr;
    uint16_t devsel;
    uint16_t j;
    usb_er_t ret;

    devaddr = p_usb_shstd_mgr_msg[ptr->ip]->keyword;
    devsel  = (uint16_t) (devaddr << USB_DEVADDRBIT);

    /* Get root port number from device addr */
    if (USB_NOCONNECT != usb_hstd_chk_dev_addr(ptr, devsel))
    {
        /* PIPE suspend */
        /* WAIT_LOOP */
        for (j = USB_MIN_PIPE_NO; j <= USB_MAX_PIPE_NO; j++)
        {
            /* Agreement device address */
            if (usb_hstd_get_devsel(ptr, j) == devsel)
            {
                /* PID=BUF ? */
                if (USB_PID_BUF == usb_cstd_get_pid(ptr, j))
                {
                    usb_cstd_set_nak(ptr, j);
                    g_usb_hstd_suspend_pipe[ptr->ip][j] = USB_SUSPENDED;
                }
            }
        }

        /* Get Configuration Descriptor */
        usb_hstd_get_config_desc(ptr, devaddr, (uint16_t) 0x09);

        /* Check Remote Wake-up */
        if (USB_TRUE == usb_hstd_chk_remote(ptr))
        {
            /* Set Feature */
            ret = usb_hstd_set_feature(ptr, devaddr, (uint16_t) USB_VALUE_FFH);
            if (USB_OK == ret)
            {
                usb_hstd_device_state_ctrl(ptr, devaddr, (uint16_t) USB_MSG_HCD_REMOTE);
                g_usb_hstd_mgr_mode[ptr->ip] = USB_SUSPENDED;
            }
        }
        else
        {
            USB_PRINTF0("### Remote wake up disable\n");
            usb_hstd_device_state_ctrl(ptr, devaddr, (uint16_t) USB_MSG_HCD_REMOTE);
            g_usb_hstd_mgr_mode[ptr->ip] = USB_SUSPENDED;
        }
    }

    usb_hstd_mgr_rel_mpl(ptr, info);
 #else                                 /* (BSP_CFG_RTOS == 2) */
    uint16_t devaddr;
    uint16_t devsel;
    uint16_t j;

    devaddr = p_usb_shstd_mgr_msg[ptr->ip]->keyword;
    devsel  = (uint16_t) (devaddr << USB_DEVADDRBIT);

    if (USB_NOCONNECT != usb_hstd_chk_dev_addr(ptr, devsel))
    {
        /* PIPE suspend */
        /* WAIT_LOOP */
        for (j = USB_MIN_PIPE_NO; j <= USB_MAX_PIPE_NO; j++)
        {
            /* Agreement device address */
            if (usb_hstd_get_devsel(ptr, j) == devsel)
            {
                /* PID=BUF ? */
                if (USB_PID_BUF == usb_cstd_get_pid(ptr, j))
                {
                    usb_cstd_set_nak(ptr, j);
                    g_usb_hstd_suspend_pipe[ptr->ip][j] = USB_SUSPENDED;
                }
            }
        }

        usb_shstd_suspend_seq[ptr->ip] = 0;
        usb_hstd_susp_cont(ptr, devaddr);
        g_usb_hstd_mgr_mode[ptr->ip] = USB_SUSPENDED_PROCESS;
    }
    usb_hstd_mgr_rel_mpl(ptr, info);
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hstd_mgr_suspend
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_device_state_ctrl
 * Description     : Setup a call to the function usb_hstd_change_device_state to re-
 *               : quest the connected USB Device to change status.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     devaddr : Device address.
 *               : uint16_t     msginfo : Request type.
 * Return          : none
 ******************************************************************************/
void usb_hstd_device_state_ctrl (usb_utr_t * ptr, uint16_t devaddr, uint16_t msginfo)
{
    switch (devaddr)
    {
        case 0:
        {
            USB_PRINTF0("### usbd_message device address error\n");
            break;
        }

        case USB_DEVICEADDR:
        {
            usb_hstd_hcd_snd_mbx(ptr, msginfo, USB_NULL, (uint16_t *) 0, &usb_hstd_status_result);
            break;
        }

        default:
        {
            if (USB_HUBDPADDR <= devaddr)
            {
                /* Non */
            }

            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_device_state_ctrl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_device_state_ctrl2
 * Description     : Setup a call to the function usb_hstd_change_device_state to re-
 *               : quest the connected USB Device to change status.
 * Arguments       : usb_utr_t    *ptr             : Pointer to usb_utr_t structure
 *               : usb_cb_t     complete         : Callback function Pointer
 *               : uint16_t     devaddr          : Device address
 *               : uint16_t     msginfo          : Request type for HCD
 *               : uint16_t     mgr_msginfo      : Request type for MGR
 * Return          : none
 ******************************************************************************/
void usb_hstd_device_state_ctrl2 (usb_utr_t * ptr,
                                  usb_cb_t    complete,
                                  uint16_t    devaddr,
                                  uint16_t    msginfo,
                                  uint16_t    mgr_msginfo)
{
    usb_shstd_mgr_callback[ptr->ip] = complete;
    usb_shstd_mgr_msginfo[ptr->ip]  = mgr_msginfo;
    usb_hstd_device_state_ctrl(ptr, devaddr, msginfo);
}

/******************************************************************************
 * End of function usb_hstd_device_state_ctrl2
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_reset
 * Description     : Request HCD (Host Control Driver) to do a USB bus reset.
 * Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure
 *               : uint16_t     devaddr : Device address.
 * Return          : none
 ******************************************************************************/
void usb_hstd_mgr_reset (usb_utr_t * ptr, uint16_t addr)
{
    usb_hstd_device_state_ctrl(ptr, addr, (uint16_t) USB_MSG_HCD_USBRESET);
    if (USB_DEVICEADDR == addr)
    {
        g_usb_hstd_mgr_mode[ptr->ip] = USB_DEFAULT;
    }
    else
    {
        /* Non */
    }
}

/******************************************************************************
 * End of function usb_hstd_mgr_reset
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_resume
 * Description     : Request HCD (Host Control Device) to send RESUME signal.
 * Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure
 *               : uint16_t     info : Information.
 * Return          : none
 ******************************************************************************/
void usb_hstd_mgr_resume (usb_utr_t * ptr, uint16_t info)
{
 #if (BSP_CFG_RTOS == 2)
    uint16_t       rootport = 0;
    uint16_t       devaddr;
    uint16_t       devsel;
    uint16_t       md;
    uint16_t       j;
    usb_er_t       ret;
    usb_hcdreg_t * driver;

    devaddr = p_usb_shstd_mgr_msg[ptr->ip]->keyword;
    devsel  = (uint16_t) (devaddr << USB_DEVADDRBIT);

    /* Get root port number from device addr */
    if (USB_NOCONNECT != usb_hstd_chk_dev_addr(ptr, devsel))
    {
        /* Device resume */
        usb_hstd_device_state_ctrl(ptr, devaddr, p_usb_shstd_mgr_msg[ptr->ip]->msginfo);

        /* Wait resume signal */
        usb_cpu_delay_xms((uint16_t) USB_VALUE_100);

        /* Get Configuration Descriptor */
        usb_hstd_get_config_desc(ptr, devaddr, (uint16_t) 0x09);

        /* Check Remote wake-up */
        if (USB_TRUE == usb_hstd_chk_remote(ptr))
        {
            ret = usb_hstd_clr_feature(ptr, devaddr, (uint16_t) USB_VALUE_FFH, (usb_cb_t) &class_trans_result);
            if (USB_OK == ret)
            {
                g_usb_hstd_mgr_mode[ptr->ip] = USB_CONFIGURED;
            }
        }
        else
        {
            g_usb_hstd_mgr_mode[ptr->ip] = USB_CONFIGURED;
        }
    }

    if (USB_CONFIGURED == g_usb_hstd_mgr_mode[ptr->ip])
    {
        /* PIPE resume */
        /* WAIT_LOOP */
        for (j = USB_MIN_PIPE_NO; j <= USB_MAX_PIPE_NO; j++)
        {
            /* Agreement device address */
            if (usb_hstd_get_device_address(ptr, j) == devsel)
            {
                if (USB_SUSPENDED == g_usb_hstd_suspend_pipe[ptr->ip][j])
                {
                    usb_cstd_set_buf(ptr, j);
                    g_usb_hstd_suspend_pipe[ptr->ip][j] = USB_OK;
                }
            }
        }

        /* WAIT_LOOP */
        for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
        {
            driver = &g_usb_hstd_device_drv[ptr->ip][md];
            if ((rootport + USB_DEVICEADDR) == driver->devaddr)
            {
                (*driver->devresume)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);

                /* Device state */
                g_usb_hstd_device_info[ptr->ip][driver->devaddr][1] = USB_CONFIGURED;

                if (USB_DO_GLOBAL_RESUME == usb_shstd_mgr_msginfo[ptr->ip])
                {
                    usb_hstd_mgr_chgdevst_cb(ptr);
                }

                /* Device state */
                driver->devstate = USB_CONFIGURED;
            }
        }
    }

    usb_hstd_mgr_rel_mpl(ptr, info);
 #else                                 /* (BSP_CFG_RTOS == 2) */
    uint16_t devaddr;
    uint16_t devsel;

    devaddr = p_usb_shstd_mgr_msg[ptr->ip]->keyword;
    devsel  = (uint16_t) (devaddr << USB_DEVADDRBIT);

    if (USB_NOCONNECT != usb_hstd_chk_dev_addr(ptr, devsel))
    {
        /* Device resume */
  #if USB_IP_EHCI_OHCI == 1
        g_usb_hstd_mgr_mode[ptr->ip]  = USB_RESUME_PROCESS;
        usb_shstd_resume_seq[ptr->ip] = 0;
        r_usb_hstd_hci_port_resume(ptr);
        usb_hstd_resu_cont(ptr, devaddr);
  #else
        usb_hstd_device_state_ctrl(ptr, devaddr, p_usb_shstd_mgr_msg[ptr->ip]->msginfo);
        g_usb_hstd_mgr_mode[ptr->ip]  = USB_RESUME_PROCESS;
        usb_shstd_resume_seq[ptr->ip] = 0;
  #endif
    }
    usb_hstd_mgr_rel_mpl(ptr, info);
 #endif                                /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hstd_mgr_resume
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hstd_susp_cont
 * Description     : Suspend the connected USB Device (Function for nonOS)
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     devaddr     : Device Address
 * Return          : none
 ******************************************************************************/
static void usb_hstd_susp_cont (usb_utr_t * ptr, uint16_t devaddr)
{
    uint16_t checkerr;

    checkerr = p_usb_shstd_mgr_msg[ptr->ip]->result;

    switch (usb_shstd_suspend_seq[ptr->ip])
    {
        case 0:
        {
            usb_hstd_get_config_desc(ptr, devaddr, (uint16_t) 0x09, (usb_cb_t) &usb_hstd_submit_result);
            usb_shstd_suspend_seq[ptr->ip]++;
            break;
        }

        case 1:
        {
            if (USB_OK == usb_hstd_std_req_check(checkerr))
            {
                if (USB_TRUE == usb_hstd_chk_remote(ptr))
                {
                    usb_hstd_set_feature(ptr, devaddr, (uint16_t) USB_VALUE_FFH, (usb_cb_t) &usb_hstd_submit_result);
                    usb_shstd_suspend_seq[ptr->ip]++;
                }
                else
                {
                    USB_PRINTF0("### Remote wake up disable\n");
  #if USB_IP_EHCI_OHCI == 1
                    r_usb_hstd_hci_port_suspend(ptr);
  #else
                    usb_hstd_device_state_ctrl(ptr, devaddr, (uint16_t) USB_MSG_HCD_REMOTE);
  #endif

                    g_usb_hstd_mgr_mode[ptr->ip] = USB_SUSPENDED;
                }
            }

            break;
        }

        case 2:
        {
            if (USB_OK == usb_hstd_std_req_check(checkerr))
            {
                usb_hstd_device_state_ctrl(ptr, devaddr, (uint16_t) USB_MSG_HCD_REMOTE);
                g_usb_hstd_mgr_mode[ptr->ip] = USB_SUSPENDED;
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_susp_cont
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_resu_cont
 * Description     : Resume the connected USB Device (Function for nonOS)
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     devaddr     : Device Address
 * Return          : none
 ******************************************************************************/
static void usb_hstd_resu_cont (usb_utr_t * ptr, uint16_t devaddr)
{
    uint16_t       devsel;
    uint16_t       j;
    uint16_t       md;
    usb_hcdreg_t * driver;
    uint16_t       checkerr;

    devsel   = (uint16_t) (devaddr << USB_DEVADDRBIT);
    checkerr = p_usb_shstd_mgr_msg[ptr->ip]->result;

    switch (usb_shstd_resume_seq[ptr->ip])
    {
        case 0:
        {
            usb_hstd_get_config_desc(ptr, devaddr, (uint16_t) 0x09, (usb_cb_t) &usb_hstd_submit_result);
            usb_shstd_resume_seq[ptr->ip]++;
            break;
        }

        case 1:
        {
            if (USB_OK == usb_hstd_std_req_check(checkerr))
            {
                if (USB_TRUE == usb_hstd_chk_remote(ptr))
                {
                    usb_hstd_clr_feature(ptr, devaddr, (uint16_t) USB_VALUE_FFH, (usb_cb_t) &usb_hstd_submit_result);
                    usb_shstd_resume_seq[ptr->ip]++;
                }
                else
                {
                    g_usb_hstd_mgr_mode[ptr->ip] = USB_CONFIGURED;
                }
            }

            break;
        }

        case 2:
        {
            if (USB_OK == usb_hstd_std_req_check(checkerr))
            {
                g_usb_hstd_mgr_mode[ptr->ip] = USB_CONFIGURED;
            }

            break;
        }

        default:
        {
            break;
        }
    }

    if (USB_CONFIGURED == g_usb_hstd_mgr_mode[ptr->ip])
    {
        /* PIPE resume */
        /* WAIT_LOOP */
        for (j = USB_MIN_PIPE_NO; j <= USB_MAX_PIPE_NO; j++)
        {
            /* Agreement device address */
            if (usb_hstd_get_device_address(ptr, j) == devsel)
            {
                if (USB_SUSPENDED == g_usb_hstd_suspend_pipe[ptr->ip][j])
                {
                    usb_cstd_set_buf(ptr, j);
                    g_usb_hstd_suspend_pipe[ptr->ip][j] = USB_OK;
                }
            }
        }

        /* WAIT_LOOP */
        for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
        {
            driver = &g_usb_hstd_device_drv[ptr->ip][md];
            if (USB_DEVICEADDR == driver->devaddr)
            {
                (*driver->devresume)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);

                /* Device state */
                g_usb_hstd_device_info[ptr->ip][driver->devaddr][1] = USB_CONFIGURED;

                if (USB_DO_GLOBAL_RESUME == usb_shstd_mgr_msginfo[ptr->ip])
                {
                    usb_hstd_mgr_chgdevst_cb(ptr);
                }

                /* Device state */
                driver->devstate = USB_CONFIGURED;
            }
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_resu_cont
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_chk_remote
 * Description     : check remote
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
static uint16_t usb_hstd_chk_remote (usb_utr_t * ptr)
{
    if ((uint8_t) 0 != (g_usb_hstd_class_data[ptr->ip][7] & USB_CF_RWUPON))
    {
        return USB_TRUE;
    }

    return USB_FALSE;
}

/******************************************************************************
 * End of function usb_hstd_chk_remote
 ******************************************************************************/

/* Condition compilation by the difference of IP */

/******************************************************************************
 * Function Name   : usb_hstd_cmd_submit
 * Description     : command submit
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : usb_cb_t     complete    : callback info
 * Return value    : uint16_t                 : USB_OK
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 2)
static usb_er_t usb_hstd_cmd_submit (usb_utr_t * ptr)
{
    usb_er_t retval;

    g_usb_hstd_class_ctrl[ptr->ip].p_tranadr = (void *) g_usb_hstd_class_data[ptr->ip];
    g_usb_hstd_class_ctrl[ptr->ip].complete  = &class_trans_result;
    g_usb_hstd_class_ctrl[ptr->ip].tranlen   = (uint32_t) g_usb_hstd_class_request[ptr->ip][3];
    g_usb_hstd_class_ctrl[ptr->ip].keyword   = USB_PIPE0;
    g_usb_hstd_class_ctrl[ptr->ip].p_setup   = g_usb_hstd_class_request[ptr->ip];
    g_usb_hstd_class_ctrl[ptr->ip].segment   = USB_TRAN_END;

    g_usb_hstd_class_ctrl[ptr->ip].ip  = ptr->ip;
    g_usb_hstd_class_ctrl[ptr->ip].ipp = ptr->ipp;

  #if USB_IP_EHCI_OHCI == 1
    retval = usb_hstd_transfer_start(&g_usb_hstd_class_ctrl[ptr->ip]);
  #else                                /* USB_IP_EHCI_OHCI == 1 */
    retval = usb_hstd_transfer_start_req(&g_usb_hstd_class_ctrl[ptr->ip]);
  #endif /* USB_IP_EHCI_OHCI == 1 */

    if (USB_QOVR == retval)
    {
        /** Submit overlap error **/
        /** Retry **/
        /* WAIT_LOOP */
        do
        {
            usb_cpu_delay_xms((uint16_t) 2);
  #if USB_IP_EHCI_OHCI == 1
            retval = usb_hstd_transfer_start(&g_usb_hstd_class_ctrl[ptr->ip]);
  #else                                /* USB_IP_EHCI_OHCI == 1 */
            retval = usb_hstd_transfer_start_req(&g_usb_hstd_class_ctrl[ptr->ip]);
  #endif /* USB_IP_EHCI_OHCI == 1 */
        } while (USB_QOVR == retval);
    }

    return retval;
}

 #else                                 /* (BSP_CFG_RTOS == 2) */
static uint16_t usb_hstd_cmd_submit (usb_utr_t * ptr, usb_cb_t complete)
{
    g_usb_hstd_class_ctrl[ptr->ip].p_tranadr = (void *) g_usb_hstd_class_data[ptr->ip];
    g_usb_hstd_class_ctrl[ptr->ip].complete  = complete;
    g_usb_hstd_class_ctrl[ptr->ip].tranlen   = (uint32_t) g_usb_hstd_class_request[ptr->ip][3];
    g_usb_hstd_class_ctrl[ptr->ip].keyword   = USB_PIPE0;
    g_usb_hstd_class_ctrl[ptr->ip].p_setup   = g_usb_hstd_class_request[ptr->ip];
    g_usb_hstd_class_ctrl[ptr->ip].segment   = USB_TRAN_END;

    g_usb_hstd_class_ctrl[ptr->ip].ip  = ptr->ip;
    g_usb_hstd_class_ctrl[ptr->ip].ipp = ptr->ipp;

  #if USB_IP_EHCI_OHCI == 1
    usb_hstd_transfer_start(&g_usb_hstd_class_ctrl[ptr->ip]);
  #else                                /* USB_IP_EHCI_OHCI == 1 */
    usb_hstd_transfer_start_req(&g_usb_hstd_class_ctrl[ptr->ip]);
  #endif /* USB_IP_EHCI_OHCI == 1 */

    return USB_OK;
}

 #endif                                /* (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * End of function usb_hstd_cmd_submit
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_feature
 * Description     : Set SetFeature
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     addr        : device address
 *               : uint16_t     epnum       : endpoint number
 *               : usb_cb_t     complete    : callback function
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 2)
usb_er_t usb_hstd_set_feature (usb_utr_t * ptr, uint16_t addr, uint16_t epnum)
 #else                                 /* (BSP_CFG_RTOS == 2) */
uint16_t usb_hstd_set_feature (usb_utr_t * ptr, uint16_t addr, uint16_t epnum, usb_cb_t complete)
 #endif /* (BSP_CFG_RTOS == 2) */
{
    if (USB_VALUE_FFH == epnum)
    {
        /* SetFeature(Device) */
        g_usb_hstd_class_request[ptr->ip][0] = USB_SET_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
        g_usb_hstd_class_request[ptr->ip][1] = USB_DEV_REMOTE_WAKEUP;
        g_usb_hstd_class_request[ptr->ip][2] = (uint16_t) 0x0000;
    }
    else
    {
        /* SetFeature(endpoint) */
        g_usb_hstd_class_request[ptr->ip][0] = USB_SET_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_ENDPOINT;
        g_usb_hstd_class_request[ptr->ip][1] = USB_ENDPOINT_HALT;
        g_usb_hstd_class_request[ptr->ip][2] = epnum;
    }

    g_usb_hstd_class_request[ptr->ip][3] = (uint16_t) 0x0000;
    g_usb_hstd_class_request[ptr->ip][4] = addr;

 #if (BSP_CFG_RTOS == 2)

    return usb_hstd_cmd_submit(ptr);
 #else                                 /* (BSP_CFG_RTOS == 2) */

    return usb_hstd_cmd_submit(ptr, complete);
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hstd_set_feature
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_get_config_desc
 * Description     : Set GetConfigurationDescriptor
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     addr        : device address
 *               : uint16_t     length      : descriptor length
 *               : usb_cb_t     complete    : callback function
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 2)
usb_er_t usb_hstd_get_config_desc (usb_utr_t * ptr, uint16_t addr, uint16_t length)
 #else                                 /* (BSP_CFG_RTOS == 2) */
uint16_t usb_hstd_get_config_desc (usb_utr_t * ptr, uint16_t addr, uint16_t length, usb_cb_t complete)
 #endif /* (BSP_CFG_RTOS == 2) */
{
    uint16_t i;

    /* Get Configuration Descriptor */
    g_usb_hstd_class_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    g_usb_hstd_class_request[ptr->ip][1] = USB_CONF_DESCRIPTOR;
    g_usb_hstd_class_request[ptr->ip][2] = (uint16_t) 0x0000;
    g_usb_hstd_class_request[ptr->ip][3] = length;
    if (g_usb_hstd_class_request[ptr->ip][3] > CLSDATASIZE)
    {
        g_usb_hstd_class_request[ptr->ip][3] = (uint16_t) CLSDATASIZE;
        USB_PRINTF0("***WARNING Descriptor size over !\n");
    }

    g_usb_hstd_class_request[ptr->ip][4] = addr;

    /* WAIT_LOOP */
    for (i = 0; i < g_usb_hstd_class_request[ptr->ip][3]; i++)
    {
        g_usb_hstd_class_data[ptr->ip][i] = (uint8_t) USB_VALUE_FFH;
    }

 #if (BSP_CFG_RTOS == 2)

    return usb_hstd_cmd_submit(ptr);
 #else                                 /* (BSP_CFG_RTOS == 2) */

    return usb_hstd_cmd_submit(ptr, complete);
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hstd_get_config_desc
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)

/******************************************************************************
 * Function Name   : usb_hstd_std_req_check
 * Description     : Sample Standard Request Check
 * Arguments       : uint16_t errcheck        : error
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
uint16_t usb_hstd_std_req_check (uint16_t errcheck)
{
    uint16_t result_code = USB_OK;

    if (USB_DATA_TMO == errcheck)
    {
        USB_PRINTF0("*** Standard Request Timeout error !\n");
        result_code = USB_ERROR;
    }
    else if (USB_DATA_STALL == errcheck)
    {
        USB_PRINTF0("*** Standard Request STALL !\n");
        result_code = USB_ERROR;
    }
    else if (USB_CTRL_END != errcheck)
    {
        USB_PRINTF0("*** Standard Request error !\n");
        result_code = USB_ERROR;
    }
    else
    {
        /* Non */
    }

    return result_code;
}

/******************************************************************************
 * End of function usb_hstd_std_req_check
 ******************************************************************************/
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_get_string_desc
 * Description     : Set GetDescriptor
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     addr        : device address
 *               : uint16_t     string      : descriptor index
 *               : usb_cb_t     complete    : callback function
 * Return value    : uint16_t                 : error info
 ******************************************************************************/
 #if (BSP_CFG_RTOS == 2)
usb_er_t usb_hstd_get_string_desc (usb_utr_t * ptr, uint16_t addr, uint16_t string)
 #else                                 /* (BSP_CFG_RTOS == 2) */
uint16_t usb_hstd_get_string_desc (usb_utr_t * ptr, uint16_t addr, uint16_t string, usb_cb_t complete)
 #endif /* (BSP_CFG_RTOS == 2) */
{
    uint16_t i;

    if (0 == string)
    {
        g_usb_hstd_class_request[ptr->ip][2] = (uint16_t) 0x0000;
        g_usb_hstd_class_request[ptr->ip][3] = (uint16_t) 0x0004;
    }
    else
    {
        /* Set LanguageID */
        g_usb_hstd_class_request[ptr->ip][2]  = (uint16_t) (g_usb_hstd_class_data[ptr->ip][2]);
        g_usb_hstd_class_request[ptr->ip][2] |= (uint16_t) ((uint16_t) (g_usb_hstd_class_data[ptr->ip][3]) << 8);
        g_usb_hstd_class_request[ptr->ip][3]  = (uint16_t) CLSDATASIZE;
    }

    g_usb_hstd_class_request[ptr->ip][0] = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    g_usb_hstd_class_request[ptr->ip][1] = (uint16_t) (USB_STRING_DESCRIPTOR + string);
    g_usb_hstd_class_request[ptr->ip][4] = addr;

    /* WAIT_LOOP */
    for (i = 0; i < g_usb_hstd_class_request[ptr->ip][3]; i++)
    {
        g_usb_hstd_class_data[ptr->ip][i] = (uint8_t) USB_VALUE_FFH;
    }

 #if (BSP_CFG_RTOS == 2)

    return usb_hstd_cmd_submit(ptr);
 #else                                 /* (BSP_CFG_RTOS == 2) */

    return usb_hstd_cmd_submit(ptr, complete);
 #endif /* (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hstd_get_string_desc
 ******************************************************************************/

 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
  #if USB_CFG_ELECTRICAL == USB_CFG_ENABLE
   #if  USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : usb_hstd_electrical_test_mode
 * Description     : Host electrical test mode function
 * Arguments       : usb_utr_t    *ptr        : Pointer to usb_utr_t structure
 *               : uint16_t     product_id  : Task Start Code
 *               : uint16_t     port        : Port number
 * Return          : none
 ******************************************************************************/
void usb_hstd_electrical_test_mode (usb_utr_t * ptr, uint16_t product_id)
{
    uint16_t brdysts;

    switch (product_id)
    {
        case 0x0101:                   /* Test_SE0_NAK */
        {
    #if USB_IP_EHCI_OHCI == 1
            r_usb_hstd_hci_electrical_test(ptr, 0);
    #else
            usb_hstd_test_signal(ptr, 3);
    #endif

            /* WAIT_LOOP */
            while (1)
            {
                /* This loops infinitely until it's reset. */
            }

            break;
        }

        case 0x0102:                   /* Test_J */
        {
            usb_hstd_test_signal(ptr, 1);

            /* WAIT_LOOP */
            while (1)
            {
                /* This loops infinitely until it's reset. */
            }

            break;
        }

        case 0x0103:                   /* Test_K */
        {
            usb_hstd_test_signal(ptr, 2);

            /* WAIT_LOOP */
            while (1)
            {
                /* This loops infinitely until it's reset. */
            }

            break;
        }

        case 0x0104:                   /* Test_Packet */
        {
            usb_hstd_test_signal(ptr, 4);

            /* WAIT_LOOP */
            while (1)
            {
                /* This loops infinitely until it's reset. */
            }

            break;
        }

        case 0x0105:                   /* Reserved */
        {
            break;
        }

        case 0x0106:                   /* HS_HOST_PORT_SUSPEND_RESUME */
        {
            usb_cpu_delay_xms(15000);  /* wait 15sec */
            usb_hstd_test_suspend(ptr);
            usb_cpu_delay_xms(15000);  /* wait 15sec */
            usb_hstd_test_resume(ptr);
            break;
        }

        case 0x0107:                   /* SINGLE_STEP_GET_DEV_DESC */
        {
            usb_cpu_delay_xms(15000);  /* wait 15sec */
            hw_usb_hwrite_usbreq(ptr, (USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE));
            hw_usb_hset_usbval(ptr, USB_DEV_DESCRIPTOR);
            hw_usb_hset_usbleng(ptr, 0x0012);
            hw_usb_hset_sureq(ptr);
            break;
        }

        case 0x0108:                   /* SINGLE_STEP_GET_DEV_DESC_DATA */
        {
            hw_usb_hwrite_usbreq(ptr, (USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE));
            hw_usb_hset_usbval(ptr, USB_DEV_DESCRIPTOR);
            hw_usb_hset_usbindx(ptr, 0x0000);
            hw_usb_hset_usbleng(ptr, 0x0012);
            hw_usb_hset_sureq(ptr);
            usb_cpu_delay_xms(15000);  /* wait 15sec */

            usb_cstd_set_nak(ptr, USB_PIPE0);
            hw_usb_write_dcpcfg(ptr, 0);

            hw_usb_hwrite_dcpctr(ptr, USB_SQSET);                    /* debug */
            usb_hstd_do_sqtgl(ptr, (uint16_t) USB_PIPE0, USB_SQMON); /* debug */

            hw_usb_rmw_fifosel(ptr, USB_CUSE, (USB_RCNT | USB_PIPE0), (USB_RCNT | USB_ISEL | USB_CURPIPE));
            hw_usb_set_bclr(ptr, USB_CUSE);
            usb_cstd_set_buf(ptr, USB_PIPE0);

            /* WAIT_LOOP */
            do
            {
                brdysts = hw_usb_read_brdysts(ptr);
            } while (!(brdysts & USB_BRDY0));

            usb_cstd_set_nak(ptr, USB_PIPE0);
            hw_usb_set_sqclr(ptr, USB_PIPE0);
            hw_usb_set_bclr(ptr, USB_CUSE);
            break;
        }

        default:
        {
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_electrical_test_mode
 ******************************************************************************/
   #endif                              /* USB_IP_EHCI_OHCI == 0*/
  #endif                               /* USB_CFG_ELECTRICAL == USB_CFG_ENABLE */
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 * Function Name   : usb_hstd_mgr_task
 * Description     : The host manager (MGR) task.
 * Argument        : usb_vp_int_t stacd          : Task Start Code
 * Return          : none
 ******************************************************************************/
void usb_hstd_mgr_task (void * stacd)
{
    usb_utr_t         * mess;
    usb_utr_t         * ptr;
    usb_er_t            err;
    usb_hcdreg_t      * driver;
    usb_hcdinfo_t     * hp;
    uint16_t            rootport;
    uint16_t            devaddr;
    uint16_t            pipenum;
    uint16_t            msginfo;
    uint16_t            md;
    uint16_t            enume_mode;    /* Enumeration mode (device state) */
    uint16_t            connect_speed = 0;
    uint16_t            result        = 0;
    usb_instance_ctrl_t ctrl;
 #if (BSP_CFG_RTOS == 0)
    uint16_t devsel;
 #endif                                /* (BSP_CFG_RTOS == 0) */
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    usb_compliance_t disp_param;
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

    (void) stacd;

 #if USB_IP_EHCI_OHCI == 1
    r_usb_hstd_hci_task();
 #endif                                /* USB_IP_EHCI_OHCI == 1 */

    /* Receive message */
 #if (BSP_CFG_RTOS == 0)
    err = USB_TRCV_MSG(USB_MGR_MBX, (usb_msg_t **) &mess, (usb_tm_t) 10000);
 #else
    err = USB_RCV_MSG(USB_MGR_MBX, (usb_msg_t **) &mess);
 #endif
    if (USB_OK != err)
    {
        result = 0;
    }
    else
    {
        p_usb_shstd_mgr_msg[mess->ip] = (usb_mgrinfo_t *) mess;
        rootport = mess->ip;
        devaddr  = p_usb_shstd_mgr_msg[mess->ip]->keyword;
        pipenum  = p_usb_shstd_mgr_msg[mess->ip]->keyword;
 #if (BSP_CFG_RTOS == 0)
 #endif                                /* (BSP_CFG_RTOS == 2) */
        hp  = (usb_hcdinfo_t *) mess;
        ptr = mess;

        /* Detach is all device */
        msginfo = p_usb_shstd_mgr_msg[ptr->ip]->msginfo;
        switch (p_usb_shstd_mgr_msg[ptr->ip]->msginfo)
        {
            /* USB-bus control (change device state) */
            case USB_MSG_MGR_STATUSRESULT:
            {
                switch (g_usb_hstd_mgr_mode[ptr->ip])
                {
                    /* End of reset signal */
                    case USB_DEFAULT:
                    {
                        g_usb_hstd_device_speed[ptr->ip] = p_usb_shstd_mgr_msg[ptr->ip]->result;

                        /* Set device speed */
 #if USB_IP_EHCI_OHCI == 1
                        usb_hstd_set_rootport((uint16_t) (devaddr + 1), rootport);
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
                        usb_hstd_set_dev_addr(ptr, (uint16_t) USB_DEVICE_0, g_usb_hstd_device_speed[ptr->ip]);
 #endif /* USB_IP_EHCI_OHCI == 1 */
                        g_usb_hstd_dcp_register[ptr->ip][0] = (uint16_t) (USB_DEFPACKET + USB_DEVICE_0);
                        g_usb_hstd_enum_seq[ptr->ip]        = 0;
                        switch (g_usb_hstd_device_speed[ptr->ip])
                        {
                            case USB_HSCONNECT: /* Hi Speed Device Connect */
                            {
                                USB_PRINTF0(" Hi-Speed Device\n");
                                (*g_usb_hstd_enumaration_process[0])(ptr, (uint16_t) USB_DEVICE_0, (uint16_t) 0);
                                break;
                            }

                            case USB_FSCONNECT: /* Full Speed Device Connect */
                            {
                                USB_PRINTF0(" Full-Speed Device\n");
                                (*g_usb_hstd_enumaration_process[0])(ptr, (uint16_t) USB_DEVICE_0, (uint16_t) 0);
                                break;
                            }

                            case USB_LSCONNECT: /* Low Speed Device Connect */
                            {
                                USB_PRINTF0(" Low-Speed Device\n");
                                usb_hstd_ls_connect_function(ptr);
                                break;
                            }

                            default:
                            {
                                USB_PRINTF0(" Device/Detached\n");
                                g_usb_hstd_mgr_mode[ptr->ip] = USB_DETACHED;
                                break;
                            }
                        }

                        break;
                    }

                    /* End of resume signal */
                    case USB_CONFIGURED:
                    {
                        /* This Resume Sorce is moved to usb_hResuCont() by nonOS */
 #if (BSP_CFG_RTOS == 2)
                        /* WAIT_LOOP */
                        for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                        {
                            driver = &g_usb_hstd_device_drv[ptr->ip][md];
                            if ((rootport + USB_DEVICEADDR) == driver->devaddr)
                            {
                                (*driver->devresume)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);

                                if (USB_DO_GLOBAL_RESUME == usb_shstd_mgr_msginfo[ptr->ip])
                                {
                                    usb_hstd_mgr_chgdevst_cb(ptr);
                                }

                                /* Device state */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][1] = USB_CONFIGURED;

                                /* Device state */
                                driver->devstate = USB_CONFIGURED;
                            }
                        }
 #endif                                /* (BSP_CFG_RTOS == 2) */
                        break;
                    }

                    /* Start of suspended state */
                    case USB_SUSPENDED:
                    {
                        /* WAIT_LOOP */
                        for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                        {
                            driver = &g_usb_hstd_device_drv[ptr->ip][md];
                            if (USB_DEVICEADDR == driver->devaddr)
                            {
                                (*driver->devsuspend)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);

                                if (USB_DO_GLOBAL_SUSPEND == usb_shstd_mgr_msginfo[ptr->ip])
                                {
                                    usb_hstd_mgr_chgdevst_cb(ptr);
                                }

                                /* Device state */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][1] = USB_SUSPENDED;

                                /* Device state */
                                driver->devstate = USB_SUSPENDED;
                            }
                        }

                        break;
                    }

                    /* Continue of resume signal */
                    case USB_RESUME_PROCESS:
                    {
 #if (BSP_CFG_RTOS == 0)
                        /* Resume Sequence Number is 0 */
                        usb_hstd_resu_cont(ptr, USB_DEVICEADDR);
 #endif                                /* (BSP_CFG_RTOS == 0) */
                        break;
                    }

                    case USB_DETACHED:
                    {
                        switch (usb_shstd_mgr_msginfo[ptr->ip])
                        {
                            case USB_PORT_DISABLE:
                            {
                                usb_hstd_mgr_chgdevst_cb(ptr);
                                break;
                            }

                            default:
                            {
                                break;
                            }
                        }

                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_MGR_SUBMITRESULT:
            {
                /* Agreement device address */
 #if (BSP_CFG_RTOS == 2)
                usb_hstd_get_devsel(ptr, pipenum);
 #else
                devsel = usb_hstd_get_devsel(ptr, pipenum);
 #endif                                /* (BSP_CFG_RTOS == 2) */

                /* Get root port number from device addr */
                switch (g_usb_hstd_mgr_mode[ptr->ip])
                {
 #if (BSP_CFG_RTOS == 0)
                    /* Resume */
                    case USB_RESUME_PROCESS:
                    {
                        /* Resume Sequence Number is 1 to 2 */
                        usb_hstd_resu_cont(ptr, (uint16_t) (devsel >> USB_DEVADDRBIT));
                        break;
                    }

                    /* Suspend */
                    case USB_SUSPENDED_PROCESS:
                    {
                        usb_hstd_susp_cont(ptr, (uint16_t) (devsel >> USB_DEVADDRBIT));
                        break;
                    }
 #endif                                /* (BSP_CFG_RTOS == 0) */

                    /* Enumeration */
                    case USB_DEFAULT:
                    {
                        /* Peripheral Device Speed support check */
 #if USB_IP_EHCI_OHCI == 1
                        connect_speed = g_usb_hstd_device_speed[ptr->ip];
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
                        connect_speed = usb_hstd_support_speed_check(ptr);
 #endif /* USB_IP_EHCI_OHCI == 1 */
                        if (USB_NOCONNECT != connect_speed)
                        {
                            enume_mode = usb_hstd_enumeration(ptr);
                            switch (enume_mode)
                            {
                                /* Detach Mode */
                                case USB_NONDEVICE:
                                {
                                    USB_PRINTF1("### Enumeration error (address%d)\n", g_usb_hstd_device_addr[ptr->ip]);
                                    g_usb_hstd_mgr_mode[ptr->ip] = USB_DETACHED;

                                    if ((USB_DO_RESET_AND_ENUMERATION == usb_shstd_mgr_msginfo[ptr->ip]) ||
                                        (USB_PORT_ENABLE == usb_shstd_mgr_msginfo[ptr->ip]))
                                    {
                                        usb_hstd_mgr_chgdevst_cb(ptr);
                                    }

                                    break;
                                }

                                /* Detach Mode */
                                case USB_NOTTPL:
                                {
                                    USB_PRINTF1("### Not support device (address%d)\n",
                                                g_usb_hstd_device_addr[ptr->ip]);
                                    g_usb_hstd_mgr_mode[ptr->ip] = USB_DETACHED;

                                    if ((USB_DO_RESET_AND_ENUMERATION == usb_shstd_mgr_msginfo[ptr->ip]) ||
                                        (USB_PORT_ENABLE == usb_shstd_mgr_msginfo[ptr->ip]))
                                    {
                                        usb_hstd_mgr_chgdevst_cb(ptr);
                                    }

                                    break;
                                }

                                case USB_COMPLETEPIPESET:
                                {
                                    g_usb_hstd_mgr_mode[ptr->ip] = USB_CONFIGURED;

                                    if ((USB_DO_RESET_AND_ENUMERATION == usb_shstd_mgr_msginfo[ptr->ip]) ||
                                        (USB_PORT_ENABLE == usb_shstd_mgr_msginfo[ptr->ip]))
                                    {
                                        usb_hstd_mgr_chgdevst_cb(ptr);
                                    }

                                    break;
                                }

                                default:
                                {
                                    break;
                                }
                            }
                        }

                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_MGR_AORDETACH:
            {
                switch (p_usb_shstd_mgr_msg[ptr->ip]->result)
                {
                    case USB_DETACH:
                    {
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                        disp_param.status = USB_COMPLIANCETEST_DETACH;
                        disp_param.pid    = USB_NULL;
                        disp_param.vid    = USB_NULL;
  #if USB_IP_EHCI_OHCI == 0
                        usb_compliance_disp((void *) &disp_param);
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
                        g_usb_hstd_mgr_mode[ptr->ip]     = USB_DETACHED;
                        g_usb_hstd_device_speed[ptr->ip] = USB_NOCONNECT;

                        /* WAIT_LOOP */
                        for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                        {
                            driver = &g_usb_hstd_device_drv[ptr->ip][md];
                            if (USB_DEVICEADDR == driver->devaddr)
                            {
 #if defined(USB_CFG_HHID_USE)
  #if (BSP_CFG_RTOS == 0)
                                if (USB_DEVICEADDR == driver->devaddr)
                                {
                                    g_usb_change_device_state[ptr->ip] = USB_NULL;
                                }
  #endif                               /* BSP_CFG_RTOS == 0 */
 #endif                                /* defined(USB_CFG_HHID_USE) */

                                (*driver->devdetach)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);

                                /* Root port */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][0] = USB_NOPORT;

                                /* Device state */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][1] = USB_DETACHED;

                                /* Not configured */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][2] = (uint16_t) 0;

                                /* Interface Class : NO class */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][3] = (uint16_t) USB_IFCLS_NOT;

                                /* No connect */
                                g_usb_hstd_device_info[ptr->ip][driver->devaddr][4] = (uint16_t) USB_NOCONNECT;

                                /* Root port */
                                driver->rootport = USB_NOPORT;

                                /* Device address */
                                driver->devaddr = USB_NODEVICE;

                                /* Device state */
                                driver->devstate = USB_DETACHED;
                            }
                        }

                        usb_hstd_mgr_rel_mpl(ptr, msginfo);
                        break;
                    }

                    case USB_ATTACH:
                    case USB_ATTACHL:
                    /* continue */
                    case USB_ATTACHF:
                    {
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
                        disp_param.status = USB_COMPLIANCETEST_ATTACH;
                        disp_param.pid    = USB_NULL;
                        disp_param.vid    = USB_NULL;
  #if USB_IP_EHCI_OHCI == 0
                        usb_compliance_disp((void *) &disp_param);
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

                        if (USB_DETACHED == g_usb_hstd_mgr_mode[ptr->ip])
                        {
                            g_usb_hstd_device_addr[ptr->ip] = USB_DEVICEADDR;
                            if (USB_MAXDEVADDR < g_usb_hstd_device_addr[ptr->ip])
                            {
                                /* For port1 */
                                USB_PRINTF0("Device address error\n");
                            }
                            else
                            {
 #if   USB_IP_EHCI_OHCI == 1
                                g_usb_hstd_mgr_mode[ptr->ip] = USB_DEFAULT;
                                r_usb_hstd_hci_set_device_address_of_rootpoot(ptr->ip, g_usb_hstd_device_addr[ptr->ip]);
                                r_usb_hstd_hci_port_reset(ptr);
 #else                                 /* USB_IP_EHCI_OHCI == 1 */
                                g_usb_hstd_mgr_mode[ptr->ip] = USB_DEFAULT;

  #if USB_CFG_BC == USB_CFG_ENABLE
                                /* Call Back */
                                /*USB_BC_ATTACH(ptr, g_usb_hstd_device_addr[ptr->ip], (uint16_t)g_usb_hstd_bc[ptr->ip].state); */
                                if (USB_BC_STATE_CDP == g_usb_hstd_bc[ptr->ip].state)
                                {
                                    ctrl.device_address = (uint8_t) g_usb_hstd_device_addr[ptr->ip]; /* USB Device address */
                                    ctrl.module_number  = (uint8_t) ptr->ip;                         /* Module number setting */
                                    usb_set_event(USB_STATUS_BC, &ctrl);                             /* Set Event()  */
                                }
  #endif /* USB_CFG_BC == USB_CFG_ENABLE */

                                usb_hstd_attach_function();
                                usb_hstd_mgr_reset(ptr, g_usb_hstd_device_addr[ptr->ip]);
 #endif                                /* USB_IP_EHCI_OHCI == 1 */
                            }

                            usb_hstd_mgr_rel_mpl(ptr, msginfo);
                        }
                        else
                        {
                            usb_hstd_mgr_rel_mpl(ptr, msginfo);
                        }

                        break;
                    }

                    default:
                    {
                        usb_hstd_mgr_rel_mpl(ptr, msginfo);
                        break;
                    }
                }

                break;
            }

            case USB_MSG_MGR_OVERCURRENT:
            {
                ctrl.module_number = ptr->ip;                 /* Module number setting */
                usb_set_event(USB_STATUS_OVERCURRENT, &ctrl); /* Set Event()  */

                USB_PRINTF0(" Please detach device \n ");
                USB_PRINTF1("VBUS off port%d\n", rootport);
 #if USB_IP_EHCI_OHCI == 0
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBOFF);
 #endif                                /* USB_IP_EHCI_OHCI == 0 */
                g_usb_hstd_mgr_mode[ptr->ip] = USB_DEFAULT;

                /* WAIT_LOOP */
                for (md = 0; md < g_usb_hstd_device_num[ptr->ip]; md++)
                {
                    driver = &g_usb_hstd_device_drv[ptr->ip][md];
                    if (driver->rootport == rootport)
                    {
                        /* Root port */
                        g_usb_hstd_device_info[ptr->ip][driver->devaddr][0] = USB_NOPORT;

                        /* Device state */
                        g_usb_hstd_device_info[ptr->ip][driver->devaddr][1] = USB_DETACHED;

                        /* Not configured */
                        g_usb_hstd_device_info[ptr->ip][driver->devaddr][2] = (uint16_t) 0;

                        /* Interface Class : NO class */
                        g_usb_hstd_device_info[ptr->ip][driver->devaddr][3] = (uint16_t) USB_IFCLS_NOT;

                        /* No connect */
                        g_usb_hstd_device_info[ptr->ip][driver->devaddr][4] = (uint16_t) USB_NOCONNECT;

                        /* Root port */
                        driver->rootport = USB_NOPORT;

                        /* Device address */
                        driver->devaddr = USB_NODEVICE;

                        /* Device state */
                        driver->devstate = USB_DETACHED;
                    }
                }

                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_ATTACH */
            case USB_DO_RESET_AND_ENUMERATION:
            {
                ptr->msginfo = USB_MSG_HCD_ATTACH_MGR;

                if (USB_DEVICEADDR == devaddr)
                {
                    g_usb_hstd_mgr_mode[ptr->ip] = USB_DETACHED;
                }
                else
                {
                    /* Non */
                }

                usb_hstd_device_state_ctrl2(ptr, hp->complete, devaddr, ptr->msginfo, msginfo);
                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_VBON */
            case USB_PORT_ENABLE:
            {
                ptr->msginfo = USB_MSG_HCD_VBON;
                if (USB_DEVICEADDR == devaddr)
                {
                    g_usb_hstd_mgr_mode[ptr->ip] = USB_DETACHED;
                }
                else
                {
                    /* Non */
                }

                usb_hstd_device_state_ctrl2(ptr, hp->complete, devaddr, ptr->msginfo, msginfo);
                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_VBOFF */
            case USB_PORT_DISABLE:
            {
                /* VBUS is off at the time of the abnormalities in a device */
                ptr->msginfo = USB_MSG_HCD_VBOFF;
                if (USB_DEVICEADDR == devaddr)
                {
                    g_usb_hstd_mgr_mode[ptr->ip] = USB_DETACHED;
                }
                else
                {
                    /* Non */
                }

                usb_hstd_device_state_ctrl2(ptr, hp->complete, devaddr, ptr->msginfo, msginfo);
                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_SUSPEND */
            case USB_DO_GLOBAL_SUSPEND:
            {
                ptr->msginfo = USB_MSG_HCD_REMOTE;
                usb_shstd_mgr_callback[ptr->ip] = hp->complete;
                usb_shstd_mgr_msginfo[ptr->ip]  = msginfo;
                usb_hstd_mgr_suspend(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_SUSPEND */
            case USB_DO_SELECTIVE_SUSPEND:
            {
                ptr->msginfo = USB_MSG_HCD_REMOTE;
                usb_hstd_mgr_suspend(ptr, msginfo);
                usb_hstd_device_state_ctrl2(ptr, hp->complete, devaddr, ptr->msginfo, msginfo);
                break;
            }

            /* USB_MSG_HCD_RESUME */
            case USB_DO_GLOBAL_RESUME:
            {
                ptr->msginfo = USB_MSG_HCD_RESUME;
                usb_shstd_mgr_callback[ptr->ip] = hp->complete;
                usb_shstd_mgr_msginfo[ptr->ip]  = msginfo;
                usb_hstd_mgr_resume(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_RESUME */
            case USB_MSG_HCD_RESUME:
            {
                usb_shstd_mgr_msginfo[ptr->ip] = msginfo;
                usb_hstd_mgr_resume(ptr, msginfo);
                break;
            }

            /* USB_MSG_HCD_RESUME */
            case USB_DO_SELECTIVE_RESUME:
            {
                ptr->msginfo = USB_MSG_HCD_RESUME;
                usb_hstd_mgr_resume(ptr, msginfo);
                usb_hstd_device_state_ctrl2(ptr, hp->complete, devaddr, ptr->msginfo, msginfo);
                break;
            }

 #if USB_IP_EHCI_OHCI == 1
            case USB_DO_CLR_STALL:
            {
                pipenum = ptr->keyword;
                usb_hstd_clr_stall(ptr, pipenum, ptr->complete);
                break;
            }
 #endif                                /* #if USB_IP_EHCI_OHCI == 1 */

            default:
            {
                usb_hstd_mgr_rel_mpl(ptr, msginfo);
                break;
            }
        }
    }

    if (0 == result)
    {
        return;
    }
}

/******************************************************************************
 * End of function usb_hstd_mgr_task
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_open
 * Description     : Initialize global variable that contains registration status
 *               : of HDCD.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
usb_er_t usb_hstd_mgr_open (usb_utr_t * ptr)
{
    usb_er_t       err = USB_OK;
    usb_hcdreg_t * driver;
    uint16_t       i;
    static uint8_t is_init = USB_NO;

    if (USB_NO == is_init)
    {
        memset((void *) &usb_shstd_std_request, 0, (5 * 2));
        memset((void *) &usb_shstd_std_req_msg, 0, sizeof(usb_utr_t));
        is_init = USB_YES;
    }

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAX_PIPE_NO + 1); i++)
    {
        g_usb_hstd_suspend_pipe[ptr->ip][i] = 0;
    }

    memset(g_usb_hstd_class_data[ptr->ip], 0, CLSDATASIZE);
    memset(g_usb_hstd_device_descriptor[ptr->ip], 0, USB_DEVICESIZE);
    memset(g_usb_hstd_config_descriptor[ptr->ip], 0, USB_CONFIGSIZE);
    memset((void *) &g_usb_hstd_class_request[ptr->ip], 0, (5 * 2));
    memset((void *) &g_usb_hstd_class_ctrl[ptr->ip], 0, sizeof(usb_utr_t));
    memset((void *) &p_usb_shstd_mgr_msg[ptr->ip], 0, sizeof(usb_mgrinfo_t *));

    g_usb_hstd_enum_seq[ptr->ip]         = 0;
    g_usb_hstd_check_enu_result[ptr->ip] = 0;
    usb_shstd_mgr_msginfo[ptr->ip]       = 0;
 #if (BSP_CFG_RTOS == 0)
  #if USB_IP_EHCI_OHCI == 0
    usb_shstd_reg_pointer[ptr->ip] = 0;
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
    usb_shstd_suspend_seq[ptr->ip] = 0;
    usb_shstd_resume_seq[ptr->ip]  = 0;
 #endif                                /* (BSP_CFG_RTOS == 0) */
    usb_shstd_mgr_callback[ptr->ip] = 0;

    /* Manager Mode */
    g_usb_hstd_mgr_mode[ptr->ip]     = USB_DETACHED;
    g_usb_hstd_device_speed[ptr->ip] = USB_NOCONNECT;

    /* Device address */
    g_usb_hstd_device_addr[ptr->ip] = USB_DEVICE_0;

    /* Device driver number */
    g_usb_hstd_device_num[ptr->ip] = 0;

    /* WAIT_LOOP */
    for (i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++)
    {
        g_usb_hstd_suspend_pipe[ptr->ip][i] = USB_OK;
    }

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAXDEVADDR + 1U); i++)
    {
        driver = &g_usb_hstd_device_drv[ptr->ip][i];

        driver->rootport = USB_NOPORT;                                    /* Root port */
        driver->devaddr  = USB_NODEVICE;                                  /* Device address */
        driver->devstate = USB_DETACHED;                                  /* Device state */
        driver->ifclass  = (uint16_t) USB_IFCLS_NOT;                      /* Interface Class : NO class */
        g_usb_hstd_device_info[ptr->ip][i][0] = USB_NOPORT;               /* Root port */
        g_usb_hstd_device_info[ptr->ip][i][1] = USB_DETACHED;             /* Device state */
        g_usb_hstd_device_info[ptr->ip][i][2] = (uint16_t) 0;             /* Not configured */
        g_usb_hstd_device_info[ptr->ip][i][3] = (uint16_t) USB_IFCLS_NOT; /* Interface Class : NO class */
        g_usb_hstd_device_info[ptr->ip][i][4] = (uint16_t) USB_NOCONNECT; /* No connect */
    }

    USB_PRINTF0("*** Install USB-MGR ***\n");

    /* usb_cstd_set_task_pri(USB_MGR_TSK, USB_PRI_2); */

    return err;
}

/******************************************************************************
 * End of function usb_hstd_mgr_open
 ******************************************************************************/

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/

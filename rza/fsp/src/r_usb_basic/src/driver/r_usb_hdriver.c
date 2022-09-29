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
#include "r_usb_basic_local.h"

#if defined(USB_CFG_HCDC_USE)
 #include "r_usb_hcdc_api.h"

#endif                                 /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
 #include "r_usb_hhid_api.h"

#endif                                 /* defined(USB_CFG_HHID_USE) */

#if defined(USB_CFG_HMSC_USE)
 #include "r_usb_hmsc_api.h"

#endif                                 /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_PCDC_USE)
 #include "r_usb_pcdc_api.h"

#endif                                 /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_PMSC_USE)
 #include "r_usb_pmsc_api.h"

#endif                                 /* defined(USB_CFG_PMSC_USE) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
 #include "../hw/inc/r_usb_dmac.h"
#endif                                 /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if (BSP_CFG_RTOS == 2)
 #include "inc/r_usb_cstd_rtos.h"
#endif                                 /* #if (BSP_CFG_RTOS == 2) */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
  #define USB_RESPONCE_COUNTER_VALUE    (6000U)
 #endif                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

 #if defined(USB_CFG_HVND_USE)
  #define USB_EP_PIPE_NUM               (9)
  #define USB_EP_TBL_WSIZE              ((USB_EPL * USB_EP_PIPE_NUM) + 1)
 #endif                                /* defined(USB_CFG_HVND_USE) */

 #define USB_VALUE_FFH                  (0xFF)
 #define USB_VALUE_3000                 (3000)
 #define USB_VALUE_100U                 (100U)

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
 #if USB_IP_EHCI_OHCI == 0
static uint16_t usb_shstd_clr_stall_pipe[USB_NUM_USBIP];
 #endif                                /* USB_IP_EHCI_OHCI == 0 */
static uint16_t  usb_shstd_clr_stall_request[USB_NUM_USBIP][5];
static usb_utr_t usb_shstd_clr_stall_ctrl[USB_NUM_USBIP];

 #if defined(USB_CFG_HVND_USE)
static void usb_hvnd_configured(usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2);
static void usb_hvnd_detach(usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2);
static void usb_hvnd_enumeration(usb_clsinfo_t * mess, uint16_t ** table);
static void usb_hvnd_pipe_info(uint8_t * table, uint16_t speed, uint16_t length);

 #endif                                /* defined(USB_CFG_HVND_USE) */
 #if USB_IP_EHCI_OHCI == 0
static void usb_hstd_set_submitutr(usb_utr_t * ptr);
static void usb_hstd_set_retransfer(usb_utr_t * ptr, uint16_t pipe);

 #endif

 #if (BSP_CFG_RTOS == 0)

  #if USB_IP_EHCI_OHCI == 0
static usb_cb_t usb_shstd_clr_stall_call;
static void usb_hstd_clr_stall_result(usb_utr_t * ptr, uint16_t data1, uint16_t data2);

  #endif
 #endif                                /* (BSP_CFG_RTOS == 0) */

/******************************************************************************
 * Exported global variables (to be accessed by other files)
 ******************************************************************************/

/* Device driver (registration) */
BSP_ALIGN_VARIABLE(4) usb_hcdreg_t g_usb_hstd_device_drv[USB_NUM_USBIP][USB_MAXDEVADDR +
                                                                        1U] USB_BUFFER_PLACE_IN_SECTION;

/* Root port, status, config num, interface class, speed, */
volatile uint16_t g_usb_hstd_device_info[USB_NUM_USBIP][USB_MAXDEVADDR + 1U][8U];
uint16_t          g_usb_hstd_remort_port[USB_NUM_USBIP];

/* Control transfer stage management */
uint16_t g_usb_hstd_ctsq[USB_NUM_USBIP];

/* Manager mode */
uint16_t g_usb_hstd_mgr_mode[USB_NUM_USBIP];

/* DEVSEL & DCPMAXP (Multiple device) */
uint16_t g_usb_hstd_dcp_register[USB_NUM_USBIP][USB_MAXDEVADDR + 1U];

/* Device address */
uint16_t g_usb_hstd_device_addr[USB_NUM_USBIP];

/* Reset handshake result */
uint16_t g_usb_hstd_device_speed[USB_NUM_USBIP];

/* Device driver number */
uint16_t g_usb_hstd_device_num[USB_NUM_USBIP];

/* Ignore count */
uint16_t g_usb_hstd_ignore_cnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t g_usb_hstd_data_cnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];
uint32_t g_usb_hstd_data_cnt_pipe0[USB_NUM_USBIP];

/* PIPEn Buffer pointer(8bit) */
uint8_t * gp_usb_hstd_data_ptr[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/* Message pipe */
usb_utr_t * g_p_usb_hstd_pipe[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U];

/* Hi-speed enable */
uint16_t g_usb_hstd_hs_enable[USB_NUM_USBIP];
BSP_ALIGN_VARIABLE(4) usb_ctrl_trans_t g_usb_ctrl_request[USB_NUM_USBIP][USB_MAXDEVADDR +
                                                                         1] USB_BUFFER_PLACE_IN_SECTION;

 #if BSP_CFG_RTOS == 0
BSP_ALIGN_VARIABLE(4) uint16_t g_usb_hstd_pipe_request[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1U] USB_BUFFER_PLACE_IN_SECTION;
 #endif                                /* BSP_CFG_RTOS == 0 */

 #if defined(USB_CFG_HVND_USE)

/* Target Peripheral List */
const uint16_t g_usb_apl_devicetpl[] =
{
    USB_CFG_TPLCNT,                    /* Number of list */
    0,                                 /* Reserved */
    USB_CFG_TPL                        /* Vendor ID, Product ID */
};
 #endif /* defined(USB_CFG_HVND_USE) */

 #if (BSP_CFG_RTOS == 2)
usb_hdl_t g_usb_hstd_sus_res_task_id[USB_NUM_USBIP];
 #endif                                /*  #if (BSP_CFG_RTOS == 2) */

/******************************************************************************
 * Renesas USB Host Driver functions
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dev_descriptor
 * Description     : Returns buffer header pointer to fetch device descriptor.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : uint8_t *      : Device Descriptor Pointer
 ******************************************************************************/
uint8_t * usb_hstd_dev_descriptor (usb_utr_t * ptr)
{
    return (uint8_t *) &g_usb_hstd_device_descriptor[ptr->ip];
}

/******************************************************************************
 * End of function usb_hstd_dev_descriptor
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_con_descriptor
 * Description     : Returns buffer header pointer that includes the configuration
 *               : descriptor.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : uint8_t *      : Configuration Descriptor Pointer
 ******************************************************************************/
uint8_t * usb_hstd_con_descriptor (usb_utr_t * ptr)
{
    return (uint8_t *) &g_usb_hstd_config_descriptor[ptr->ip];
}

/******************************************************************************
 * End of function usb_hstd_con_descriptor
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_transfer_start_req
 * Description     : Send a request for data transfer to HCD (Host Control Driver)
 *               : using the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : usb_er_t       : USB_OK/USB_QOVR/USB_ERROR
 ******************************************************************************/
usb_er_t usb_hstd_transfer_start_req (usb_utr_t * ptr)
{
    usb_er_t err;
    uint16_t pipenum;
    uint16_t devsel;
 #if (BSP_CFG_RTOS == 0)
    uint16_t connect_inf = 0;
 #else                                 /* (BSP_CFG_RTOS == 0) */
    usb_utr_t * p_tran_data;
 #endif /* BSP_CFG_RTOS == 0 */

    pipenum = ptr->keyword;

    if (USB_PIPE0 == pipenum)
    {
        devsel = (uint16_t) (ptr->p_setup[4] << USB_DEVADDRBIT);
    }
    else
    {
        /* Get device address from pipe number */
        devsel = usb_hstd_get_devsel(ptr, pipenum);
    }

    if ((USB_DEVICE_0 == devsel) && (USB_PIPE0 != pipenum))
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req not configured %x\n", devsel);

        return USB_ERROR;
    }

    ptr->msghead = (usb_mh_t) USB_NULL;
    ptr->msginfo = USB_MSG_HCD_SUBMITUTR;

    if (USB_MAX_PIPE_NO < pipenum)
    {
        return USB_ERROR;
    }

 #if (BSP_CFG_RTOS == 0)
    if (USB_ON == g_usb_hstd_pipe_request[ptr->ip][pipenum])
    {
        return USB_QOVR;
    }

    /* Pipe Transfer Process check */
    if (NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
    {
        /* Check PIPE TYPE */
        if (usb_cstd_get_pipe_type(ptr, pipenum) != USB_TYPFIELD_ISO)
        {
            USB_PRINTF1("### usb_hstd_transfer_start_req overlaps %d\n", pipenum);

            return USB_QOVR;
        }
    }

    /* Get device speed from device address */
  #if USB_IP_EHCI_OHCI == 0
    connect_inf = usb_hstd_get_dev_speed(ptr, devsel);
    if (USB_NOCONNECT == connect_inf)
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req not connect %x\n", devsel);

        return USB_ERROR;
    }
  #else
    FSP_PARAMETER_NOT_USED(connect_inf);
  #endif                               /* USB_IP_EHCI_OHCI == 0 */

    /* Send message */
    err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) ptr);
    if (USB_OK == err)
    {
        g_usb_hstd_pipe_request[ptr->ip][pipenum] = USB_ON;
    }
    else
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req snd_msg error (%ld)\n", err);
    }
 #else                                 /* (BSP_CFG_RTOS == 0) */
    p_tran_data = (usb_utr_t *) pvPortMalloc(sizeof(usb_utr_t));
    if (NULL == p_tran_data)
    {
        return USB_ERROR;
    }

    *p_tran_data = *ptr;
    if (0 != ptr->p_setup)
    {
        p_tran_data->setup_data[0] = ptr->p_setup[0];
        p_tran_data->setup_data[1] = ptr->p_setup[1];
        p_tran_data->setup_data[2] = ptr->p_setup[2];
        p_tran_data->setup_data[3] = ptr->p_setup[3];
        p_tran_data->setup_data[4] = ptr->p_setup[4];
        p_tran_data->p_setup       = (uint16_t *) &p_tran_data->setup_data;
    }

    p_tran_data->cur_task_hdl = xTaskGetCurrentTaskHandle();
  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    if (0 != ptr->p_transfer_tx)
    {
        p_tran_data->p_transfer_tx = ptr->p_transfer_tx;
    }
    else
    {
        p_tran_data->p_transfer_tx = 0;
    }

    if (0 != ptr->p_transfer_rx)
    {
        p_tran_data->p_transfer_rx = ptr->p_transfer_rx;
    }
    else
    {
        p_tran_data->p_transfer_rx = 0;
    }
  #endif

    /* Send message */
    err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_tran_data);
    if (USB_OK != err)
    {
        vPortFree(p_tran_data);
    }
 #endif                                /* (BSP_CFG_RTOS == 0) */

    return err;
}

/******************************************************************************
 * End of function usb_hstd_transfer_start_req
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_device_resume
 * Description     : Send request for RESUME signal output to USB device to MGR task.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 * Argument        : uint16_t  devaddr    : Device Address
 * Return          : none
 ******************************************************************************/
void usb_hstd_device_resume (usb_utr_t * ptr, uint16_t devaddr)
{
    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_HCD_RESUME, devaddr, (uint16_t) 0U);
}

/******************************************************************************
 * End of function usb_hstd_device_resume
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_hcd_snd_mbx
 * Description     : Send specified message to HCD (Host Control Driver) task.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t  msginfo : Message info..
 *               : uint16_t  dat     : Pipe no.
 *               : uint16_t  *adr    : Address.
 *               : usb_cb_t  callback: Callback function pointer.
 * Return          : usb_er_t          : USB_OK etc.
 ******************************************************************************/
usb_er_t usb_hstd_hcd_snd_mbx (usb_utr_t * ptr, uint16_t msginfo, uint16_t dat, uint16_t * adr, usb_cb_t callback)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_er_t        err2;
    usb_hcdinfo_t * hp;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_HCD_MPL, &p_blf);
    if (USB_OK == err)
    {
        hp            = (usb_hcdinfo_t *) p_blf;
        hp->msghead   = (usb_mh_t) USB_NULL;
        hp->msginfo   = msginfo;
        hp->keyword   = dat;
        hp->p_tranadr = adr;
        hp->complete  = callback;
        hp->ipp       = ptr->ipp;
        hp->ip        = ptr->ip;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        hp->p_transfer_rx = ptr->p_transfer_rx;
        hp->p_transfer_tx = ptr->p_transfer_tx;
 #endif                                /* #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
 #if (BSP_CFG_RTOS == 2)
        hp->cur_task_hdl = ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS == 2) */

        /* Send message */
        err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) hp);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hHcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t) hp);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hHcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        /* Error */
        /* WAIT_LOOP */
        while (1)
        {
            /* error */
        }
    }

    return err;
}

/******************************************************************************
 * End of function usb_hstd_hcd_snd_mbx
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_mgr_snd_mbx
 * Description     : Send the message to MGR(Manager) task
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t msginfo  : Message info.
 *               : uint16_t dat      : Port no.
 *               : uint16_t res      : Result
 * Return          : none
 ******************************************************************************/
void usb_hstd_mgr_snd_mbx (usb_utr_t * ptr, uint16_t msginfo, uint16_t dat, uint16_t res)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_mgrinfo_t * mp;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
    if (USB_OK == err)
    {
        mp          = (usb_mgrinfo_t *) p_blf;
        mp->msghead = (usb_mh_t) USB_NULL;
        mp->msginfo = msginfo;
        mp->keyword = dat;
        mp->result  = res;
        mp->ipp     = ptr->ipp;
        mp->ip      = ptr->ip;
 #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        mp->p_transfer_rx = ptr->p_transfer_rx;
        mp->p_transfer_tx = ptr->p_transfer_tx;
 #endif
 #if (BSP_CFG_RTOS == 2)
        mp->cur_task_hdl = ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS == 2)*/

        /* Send message */
        err = USB_SND_MSG(USB_MGR_MBX, (usb_msg_t *) mp);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hMgrSndMbx snd_msg error (%ld)\n", err);
        }

        USB_REL_BLK(USB_MGR_MPL, p_blf);
    }
    else
    {
        /* Error */
        /* WAIT_LOOP */
        while (1)
        {
            /* error */
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_mgr_snd_mbx
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_hcd_rel_mpl
 * Description     : Release the secured memory block.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t n        : Error no.
 * Return          : none
 ******************************************************************************/
void usb_hstd_hcd_rel_mpl (usb_utr_t * ptr, uint16_t n)
{
    usb_er_t err;

    (void) n;

    /* Memory Pool Release */
    err = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t) ptr);
    if (USB_OK != err)
    {
        USB_PRINTF1("### USB HCD rel_blk error: %d\n", n);
    }
}

/******************************************************************************
 * End of function usb_hstd_hcd_rel_mpl
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_suspend
 * Description     : Request suspend for USB device.
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hstd_suspend (usb_utr_t * ptr)
{
    usb_hcdinfo_t * hp;

    /* Control transfer idle stage ? */
    if (USB_IDLEST == g_usb_hstd_ctsq[ptr->ip])
    {
        /* USB suspend process */
        usb_hstd_suspend_process(ptr);
        usb_hstd_chk_clk(ptr, (uint16_t) USB_SUSPENDED); /* Check clock */
        hp = (usb_hcdinfo_t *) ptr;                      /* Callback */
        (hp->complete)(ptr, USB_NULL, ptr->msginfo);
    }
    else
    {
        /* 1ms wait */
        usb_cpu_delay_xms((uint16_t) 1);

        /* Change device state request */
        usb_hstd_hcd_snd_mbx(ptr, ptr->msginfo, USB_NULL, (uint16_t *) 0, &usb_hstd_status_result);
    }
}

/******************************************************************************
 * End of function usb_hstd_suspend
 ******************************************************************************/
 #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : usb_hstd_set_submitutr
 * Description     : Submit utr: Get the device address via the specified pipe num-
 *               : ber and do a USB transfer.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
static void usb_hstd_set_submitutr (usb_utr_t * ptr)
{
    uint16_t    pipenum;
    uint16_t    devsel;
    uint16_t    connect_inf;
    uint16_t    end_flag;
    usb_utr_t * pp;

    pipenum = ptr->keyword;
  #if BSP_CFG_RTOS == 0
    g_p_usb_hstd_pipe[ptr->ip][pipenum]       = ptr;
    g_usb_hstd_pipe_request[ptr->ip][pipenum] = USB_OFF;
  #endif                               /* BSP_CFG_RTOS == 0 */

    /* Get device address from pipe number */
    if (USB_PIPE0 == pipenum)
    {
        devsel = (uint16_t) (ptr->p_setup[4] << USB_DEVADDRBIT);
    }
    else
    {
        /* Get device address from pipe number */
        devsel = usb_hstd_get_devsel(ptr, pipenum);
    }

    /* Get device speed from device address */
  #if USB_IP_EHCI_OHCI == 0
    connect_inf = usb_hstd_get_dev_speed(ptr, devsel);
  #endif                               /* USB_IP_EHCI_OHCI == 1 */
    if (USB_NOCONNECT == connect_inf)
    {
  #if (BSP_CFG_RTOS == 2)
        if (USB_PIPE0 == pipenum)
        {
            usb_cstd_pipe0_msg_clear(ptr, ptr->p_setup[4]);
        }
        else
        {
            usb_cstd_pipe_msg_clear(ptr, pipenum);
        }
  #else                                /* #if (BSP_CFG_RTOS == 2) */
        if (USB_PIPE0 == pipenum)
        {
            /* Control Read/Write End */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
        }
        else
        {
            /* End of data transfer (IN/OUT) */
            usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_ERR);
        }
  #endif                               /* #if (BSP_CFG_RTOS == 2) */

        return;
    }

  #if (BSP_CFG_RTOS == 2)
    /* Pipe Transfer Process check */
    if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
    {
        if (USB_PIPE0 == pipenum)
        {
            usb_cstd_pipe0_msg_forward(ptr, ptr->p_setup[4]);
        }
        else
        {
            usb_cstd_pipe_msg_forward(ptr, pipenum);
        }

        return;
    }
  #endif                               /* #if (BSP_CFG_RTOS == 2) */

  #if (BSP_CFG_RTOS == 2)
    g_p_usb_hstd_pipe[ptr->ip][pipenum] = ptr;
  #endif                               /* #if (BSP_CFG_RTOS == 2) */

    if ((USB_DEVICE_0 == devsel) && (USB_PIPE0 != pipenum))
    {
        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_ERR);

        return;
    }

    /* Control Transfer */
    if (USB_PIPE0 == pipenum)
    {
        /* Control transfer idle stage ? */
        if (USB_IDLEST == g_usb_hstd_ctsq[ptr->ip])
        {
            usb_hstd_setup_start(ptr);
        }

        /* Control Read Data */
        else if (USB_DATARDCNT == g_usb_hstd_ctsq[ptr->ip])
        {
            pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];
            usb_hstd_ctrl_read_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr); /* Control read start */
        }

        /* Control Write Data */
        else if (USB_DATAWRCNT == g_usb_hstd_ctsq[ptr->ip])
        {
            pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

            /* Control write start */
            end_flag = usb_hstd_ctrl_write_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr);
            if (USB_FIFOERROR == end_flag)
            {
                USB_PRINTF0("### FIFO access error \n");
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
            }
        }
        else
        {
            USB_PRINTF0("### Control transfer sequence error \n");

            /* Control Read/Write End */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
        }
    }
    else
    {
        usb_hstd_set_retransfer(ptr, pipenum); /* Data Transfer */
    }
}

/******************************************************************************
 * End of function usb_hstd_set_submitutr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_retransfer
 * Description     : Start IN/OUT transfer based on the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t  pipe : Pipe number
 * Return          : none
 ******************************************************************************/
static void usb_hstd_set_retransfer (usb_utr_t * ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Data Transfer */
    if (usb_cstd_get_pipe_dir(ptr, pipe) == USB_DIR_H_IN)
    {
        /* IN Transfer */
        usb_hstd_receive_start(ptr, pipe);
    }
    else
    {
        /* OUT Transfer */
        usb_hstd_send_start(ptr, pipe);
    }
}

/******************************************************************************
 * End of function usb_hstd_set_retransfer
 ******************************************************************************/
 #endif                                /* USB_IP_EHCI_OHCI == 0 */

/******************************************************************************
 * Function Name   : usb_hstd_bus_int_disable
 * Description     : Disable USB Bus Interrupts OVRCR, ATTCH, DTCH, and BCHG.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_hstd_bus_int_disable (usb_utr_t * ptr)
{
    /* ATTCH interrupt disable */
    usb_hstd_attch_disable(ptr);

    /* DTCH     interrupt disable */
    usb_hstd_dtch_disable(ptr);

    /* BCHG     interrupt disable */
    usb_hstd_bchg_disable(ptr);
}

/******************************************************************************
 * End of function usb_hstd_bus_int_disable
 ******************************************************************************/

 #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : usb_hstd_interrupt
 * Description     : Execute appropriate process depending on which USB interrupt
 *               : occurred.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
static void usb_hstd_interrupt (usb_utr_t * ptr)
{
    uint16_t    intsts;
    uint16_t    end_flag;
    usb_utr_t * pp;
  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    usb_compliance_t disp_param;
  #endif                               /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

    intsts = ptr->keyword;

    /*    bitsts = ptr->status;*/
    switch (intsts)
    {
        /***** Processing PIPE0-MAX_PIPE_NO data *****/
        case USB_INT_BRDY:
        {
            usb_hstd_brdy_pipe(ptr);
            break;
        }

        case USB_INT_BEMP:
        {
            usb_hstd_bemp_pipe(ptr);
            break;
        }

        case USB_INT_NRDY:
        {
            usb_hstd_nrdy_pipe(ptr);
            break;
        }

        /***** Processing Setup transaction *****/
        case USB_INT_SACK:
        {
            switch (g_usb_hstd_ctsq[ptr->ip])
            {
                case USB_SETUPRD:

                /* Next stage to Control read data */
                /* continue */
                case USB_SETUPRDCNT:
                {
                    /* Next stage to Control read data */
                    pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

                    /* Control read start */
                    usb_hstd_ctrl_read_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr);
                    break;
                }

                case USB_SETUPWR:

                /* Next stage to Control Write data */
                /* continue */
                case USB_SETUPWRCNT:
                {
                    /* Next stage to Control Write data */
                    pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

                    /* Control write start */
                    end_flag = usb_hstd_ctrl_write_start(ptr, pp->tranlen, (uint8_t *) pp->p_tranadr);
                    if (USB_FIFOERROR == end_flag)
                    {
                        USB_PRINTF0("### FIFO access error \n");

                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
                    }

                    break;
                }

                case USB_SETUPNDC:
                {
                    /* Next stage to Control write no data */
                    usb_hstd_status_start(ptr);
                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        case USB_INT_SIGN:
        {
            USB_PRINTF0("***SIGN\n");
  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
            disp_param.status = USB_CT_SETUP_ERR;
            disp_param.pid    = USB_NULL;
            disp_param.vid    = USB_NULL;
            usb_compliance_disp((void *) &disp_param);
  #endif                               /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            /* Ignore count */
            g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]++;
            USB_PRINTF2("### IGNORE Pipe %d is %d times (Setup) \n",
                        USB_PIPE0,
                        g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]);
            if (USB_PIPEERROR == g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0])
            {
                /* Setup Device Ignore count over */
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
            }
            else
            {
                /* Interrupt enable */
                /* 5ms wait */
                usb_cpu_delay_xms((uint16_t) 5U);

                /* Status Clear */
                hw_usb_hclear_sts_sign(ptr);
                hw_usb_hclear_sts_sack(ptr);

                /* Setup Ignore,Setup Acknowledge enable */
                hw_usb_hset_enb_signe(ptr);
                hw_usb_hset_enb_sacke(ptr);

                /* SETUP request send */
                /* Send SETUP request */
                hw_usb_hset_sureq(ptr);
            }

            break;
        }

        /***** Processing rootport0 *****/
        case USB_INT_OVRCR0:
        {
            /* Port0 OVCR interrupt function */
            usb_hstd_ovrcr0function(ptr);
            break;
        }

        case USB_INT_EOFERR0:
        {
            /* User program */
            break;
        }

        case USB_INT_ATTCH0:
        {
            /* Port0 ATCH interrupt function */
            usb_hstd_attach_process(ptr);
            break;
        }

        case USB_INT_BCHG0:
        {
            USB_PRINTF0("BCHG int port0\n");

            /* Port0 BCHG interrupt function */
            usb_hstd_bchg0function(ptr);
            break;
        }

        case USB_INT_DTCH0:
        {
            USB_PRINTF0("DTCH int port0\n");

            /* USB detach process */
            usb_hstd_detach_process(ptr);
            break;
        }

  #if USB_CFG_BC == USB_CFG_ENABLE
        case USB_INT_PDDETINT0:
        {
   #if defined(BSP_MCU_GROUP_RA6M3)
            /* Port0 PDDETINT interrupt function */
            if (USB_IP1 == ptr->ip)
            {
                usb_hstd_pddetint_process(ptr);
            }
   #endif                              /* defined(BSP_MCU_GROUP_RA6M3) */
            break;
        }
  #endif                               /* USB_CFG_BC == USB_CFG_ENABLE */

        case USB_INT_VBINT:
        {
            /* User program */
            hw_usb_clear_enb_vbse(ptr);
            break;
        }

        case USB_INT_SOFR:
        {
  #if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
            g_usb_hstd_response_counter[ptr->ip]++;
            if (USB_RESPONCE_COUNTER_VALUE == g_usb_hstd_response_counter[ptr->ip])
            {
                hw_usb_clear_enb_sofe(ptr);
                disp_param.status = USB_CT_NORES;
                disp_param.pid    = USB_NULL;
                disp_param.vid    = USB_NULL;
                usb_compliance_disp((void *) &disp_param);
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STOP);
            }
  #else                                /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            /* User program */
            hw_usb_clear_enb_sofe(ptr);
  #endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            break;
        }

  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        case USB_INT_DXFIFO:
        {
            usb_cstd_dma_stop(ptr, ptr->status); /* Stop DMA,FIFO access */
            usb_cstd_dma_send_continue(ptr, ptr->status);
            break;
        }
  #endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        /*** ERROR ***/
        case USB_INT_UNKNOWN:
        {
            USB_PRINTF0("hINT_UNKNOWN\n");
            break;
        }

        default:
        {
            USB_PRINTF1("hINT_default %X\n", intsts);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_interrupt
 ******************************************************************************/
 #endif                                /* USB_IP_EHCI_OHCI == 0 */

/******************************************************************************
 * Function Name   : usb_hstd_clr_feature
 * Description     : Send ClearFeature command to the connected USB device.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t addr     : Device address.
 *               : uint16_t epnum    : Endpoint number.
 *               : usb_cb_t complete : Callback function.
 * Return value    : uint16_t          : Error info.
 ******************************************************************************/
usb_er_t usb_hstd_clr_feature (usb_utr_t * ptr, uint16_t addr, uint16_t epnum, usb_cb_t complete)
{
    usb_er_t ret_code;

    if (USB_VALUE_FFH == epnum)
    {
        /* ClearFeature(Device) */
        usb_shstd_clr_stall_request[ptr->ip][0] = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
        usb_shstd_clr_stall_request[ptr->ip][1] = USB_DEV_REMOTE_WAKEUP;
        usb_shstd_clr_stall_request[ptr->ip][2] = (uint16_t) 0x0000;
    }
    else
    {
        /* ClearFeature(endpoint) */
        usb_shstd_clr_stall_request[ptr->ip][0] = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_ENDPOINT;
        usb_shstd_clr_stall_request[ptr->ip][1] = USB_ENDPOINT_HALT;
        usb_shstd_clr_stall_request[ptr->ip][2] = epnum;
    }

    usb_shstd_clr_stall_request[ptr->ip][3] = (uint16_t) 0x0000;
    usb_shstd_clr_stall_request[ptr->ip][4] = addr;

    usb_shstd_clr_stall_ctrl[ptr->ip].p_tranadr = USB_NULL;
    usb_shstd_clr_stall_ctrl[ptr->ip].complete  = complete;
    usb_shstd_clr_stall_ctrl[ptr->ip].tranlen   = 0;
    usb_shstd_clr_stall_ctrl[ptr->ip].keyword   = USB_PIPE0;
    usb_shstd_clr_stall_ctrl[ptr->ip].p_setup   = usb_shstd_clr_stall_request[ptr->ip];
    usb_shstd_clr_stall_ctrl[ptr->ip].segment   = USB_TRAN_END;

    usb_shstd_clr_stall_ctrl[ptr->ip].ip  = ptr->ip;
    usb_shstd_clr_stall_ctrl[ptr->ip].ipp = ptr->ipp;

    ret_code = usb_hstd_transfer_start_req(&usb_shstd_clr_stall_ctrl[ptr->ip]);

 #if (BSP_CFG_RTOS == 2)
    if (USB_QOVR == ret_code)
    {
        /** Submit overlap error **/
        /** Retry **/
        /* WAIT_LOOP */
        do
        {
            usb_cpu_delay_xms((uint16_t) 2);
            ret_code = usb_hstd_transfer_start(&usb_shstd_clr_stall_ctrl[ptr->ip]);
        } while (USB_QOVR == ret_code);
    }

    if (USB_OK == ret_code)
    {
        ret_code = class_trans_wait_tmo(ptr, (uint16_t) USB_VALUE_3000);
    }
 #endif                                /* #if (BSP_CFG_RTOS == 2) */

    return ret_code;
}

/******************************************************************************
 * End of function usb_hstd_clr_feature
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_clr_stall
 * Description     : Clear Stall
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t pipe        : Pipe number.
 *               : usb_cb_t complete    : Callback function
 * Return value    : uint16_t             : Error info.
 ******************************************************************************/
usb_er_t usb_hstd_clr_stall (usb_utr_t * ptr, uint16_t pipe, usb_cb_t complete)
{
    usb_er_t err;
    uint8_t  dir_ep;
    uint16_t devsel;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    dir_ep = usb_hstd_pipe_to_epadr(ptr, pipe);
    devsel = usb_hstd_get_device_address(ptr, pipe);

    err = usb_hstd_clr_feature(ptr, (uint16_t) (devsel >> USB_DEVADDRBIT), (uint16_t) dir_ep, complete);
 #if (BSP_CFG_RTOS == 2)
    if (USB_OK == err)
    {
  #if USB_IP_EHCI_OHCI == 0
        usb_cstd_clr_stall(ptr, usb_shstd_clr_stall_pipe[ptr->ip]);
        hw_usb_set_sqclr(ptr, usb_shstd_clr_stall_pipe[ptr->ip]); /* SQCLR */
  #endif /* #if USB_IP_EHCI_OHCI == 0 */
    }
 #endif /* #if (BSP_CFG_RTOS == 2) */

    return err;
}                                      /* End of function usb_hstd_clr_stall() */

/******************************************************************************
 * End of function usb_hstd_clr_stall
 ******************************************************************************/

 #if (BSP_CFG_RTOS == 0)
  #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : usb_hstd_clr_stall_result
 * Description     : Callback function to notify HCD task that usb_hstd_clr_stall function is completed
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t  data1  : Not Use
 *               : uint16_t  data2  : Not Use
 * Return value    : none
 ******************************************************************************/
static void usb_hstd_clr_stall_result (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_mh_t    p_blf;
    usb_er_t    err;
    usb_er_t    err2;
    usb_utr_t * up;

    FSP_PARAMETER_NOT_USED(data1);
    FSP_PARAMETER_NOT_USED(data2);

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_HCD_MPL, &p_blf);
    if (USB_OK == err)
    {
        up          = (usb_utr_t *) p_blf;
        up->msghead = (usb_mh_t) USB_NULL;
        up->msginfo = USB_MSG_HCD_CLR_STALL_RESULT;
        up->status  = ptr->status;

        up->ipp = ptr->ipp;
        up->ip  = ptr->ip;

        /* Send message */
        err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t *) p_blf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hHcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t) p_blf);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hHcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        /* Error */
        /* WAIT_LOOP */
        while (1)
        {
            /* error */
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_clr_stall_result
 ******************************************************************************/
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
 #endif                                /* (BSP_CFG_RTOS == 0) */

 #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : usb_hstd_hcd_task
 * Description     : USB Host Control Driver Task.
 * Argument        : usb_vp_int_t stacd  : Task Start Code.
 * Return          : none
 ******************************************************************************/
void usb_hstd_hcd_task (void * stacd)
{
    usb_utr_t * p_mess;
    usb_utr_t * ptr;
    usb_er_t    err;
    uint16_t    rootport;
    uint16_t    pipenum;
    uint16_t    msginfo;
    uint16_t    connect_inf;
    uint16_t    result = 0;
  #if (BSP_CFG_RTOS == 0)
    uint16_t retval;
  #endif                               /* (BSP_CFG_RTOS== 0) */
    usb_hcdinfo_t * hp;

    (void) stacd;

  #if (BSP_CFG_RTOS == 2)
    /* WAIT_LOOP */
    while (1)
    {
  #endif                               /* #if (BSP_CFG_RTOS == 2) */
    /* Receive message */
    err = USB_TRCV_MSG(USB_HCD_MBX, (usb_msg_t **) &p_mess, (usb_tm_t) 10000);
    if (USB_OK != err)
    {
  #if (BSP_CFG_RTOS == 2)
        result = 1;
  #else                                /* #if (BSP_CFG_RTOS == 2) */
        result = 2;
  #endif /* #if (BSP_CFG_RTOS == 2) */
    }

    else
    {
        ptr      = p_mess;
        hp       = (usb_hcdinfo_t *) p_mess;
        rootport = ptr->keyword;
        pipenum  = ptr->keyword;

        /* Branch Hcd Task receive Message Command */
        msginfo = ptr->msginfo;
        switch (msginfo)
        {
            case USB_MSG_HCD_INT:
            {
                /* USB INT */
                usb_hstd_interrupt(ptr);
                break;
            }

            case USB_MSG_HCD_SUBMITUTR:
            {
                /* USB Submit utr */
                usb_hstd_set_submitutr(ptr);
                break;
            }

            case USB_MSG_HCD_ATTACH:
            {
                /* USB attach / detach */
                usb_hstd_attach_process(ptr);

                /* Callback */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_ATTACH);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_ATTACH_MGR:
            {
                /* USB attach / detach */
                usb_hstd_attach_process(ptr);
                connect_inf = usb_cstd_port_speed(ptr);

                /* Callback */
                (hp->complete)(ptr, rootport, connect_inf);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_DETACH:
            {
                /* USB detach process */
                usb_hstd_detach_process(ptr);

                /* Callback */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_DETACH);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_DETACH_MGR:
            {
                hw_usb_clear_dvstctr(ptr, (USB_RWUPE | USB_USBRST | USB_RESUME | USB_UACT));
                usb_cpu_delay_xms(1);

                /* interrupt disable */
                usb_hstd_attch_disable(ptr);
                usb_hstd_dtch_disable(ptr);
                usb_hstd_bchg_disable(ptr);
                (hp->complete)(ptr, USB_NULL, USB_MSG_HCD_DETACH_MGR);
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_USBRESET:
            {
                /* USB bus reset */
                usb_hstd_bus_reset(ptr);

                /* Check current port speed */
                connect_inf = usb_cstd_port_speed(ptr);

                /* Callback */
                (hp->complete)(ptr, USB_NULL, connect_inf);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_REMOTE:
            {
                /* Suspend device */
                g_usb_hstd_remort_port[ptr->ip] = USB_SUSPENDED;
                usb_hstd_suspend(ptr);

                /* CallBack */
                (hp->complete)(ptr, USB_NULL, USB_MSG_HCD_REMOTE);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_SUSPEND:
            {
                usb_hstd_suspend(ptr);              /* Suspend device */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_SUSPEND);
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_RESUME:
            {
                usb_hstd_resume_process(ptr);                      /* USB resume */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_RESUME); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_VBON:
            {
                usb_hstd_ovrcr_enable(ptr);                      /* Interrupt Enable */
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBON); /* USB VBUS control ON */
  #if USB_CFG_BC == USB_CFG_DISABLE
                /* 100ms wait */
                usb_cpu_delay_xms((uint16_t) USB_VALUE_100U);
  #endif                                                         /* USB_CFG_BC == USB_CFG_DISABLE */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_VBON); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);              /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_VBOFF:
            {
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBOFF); /* USB VBUS control OFF */
                usb_hstd_ovrcr_disable(ptr);
                usb_cpu_delay_xms((uint16_t) USB_VALUE_100U);     /* 100ms wait */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_VBOFF); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);               /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_CLR_STALLBIT:
            {
                usb_cstd_clr_stall(ptr, pipenum);                                                /* STALL */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_CLR_STALLBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                                              /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_SQTGLBIT:
            {
                pipenum = ptr->keyword & USB_PIPENM;
                usb_hstd_do_sqtgl(ptr, pipenum, ptr->keyword);                               /* SQ toggle */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_SQTGLBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                                          /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_CLR_STALL:
            {
  #if (BSP_CFG_RTOS == 2)
                usb_shstd_clr_stall_pipe[ptr->ip] = pipenum;
                err = usb_hstd_clr_stall(ptr, pipenum, (usb_cb_t) &class_trans_result);
                (hp->complete)(ptr, (uint16_t) err, USB_MSG_HCD_CLR_STALL);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
  #else                                /* #if (BSP_CFG_RTOS == 2) */
                usb_shstd_clr_stall_call          = hp->complete;
                usb_shstd_clr_stall_pipe[ptr->ip] = pipenum;
                err = usb_hstd_clr_stall(ptr, pipenum, (usb_cb_t) &usb_hstd_clr_stall_result);
                if (USB_QOVR == err)
                {
                    USB_WAI_MSG(USB_HCD_MBX, ptr, 1000); /* Retry */
                }
                else
                {
                    /* Release Memory Block */
                    usb_hstd_hcd_rel_mpl(ptr, msginfo);
                }
  #endif                               /* #if (BSP_CFG_RTOS == 2) */
                break;
            }

            case USB_MSG_HCD_CLR_STALL_RESULT:
            {
  #if (BSP_CFG_RTOS == 2)
                /** Do nothing when running in RTOS
                 * The result will be checked immediately after issuing a "USB_MSG_HCD_CLR_STALL" request. **/
  #else                                /* #if (BSP_CFG_RTOS == 2) */
                ptr    = p_mess;
                retval = ptr->status;

                if (USB_DATA_TMO == retval)
                {
                    USB_PRINTF0("*** Standard Request Timeout error !\n");
                }
                else if (USB_DATA_STALL == retval)
                {
                    USB_PRINTF0("*** Standard Request STALL !\n");
                }
                else if (USB_CTRL_END != retval)
                {
                    USB_PRINTF0("*** Standard Request error !\n");
                }
                else
                {
                    usb_cstd_clr_stall(ptr, usb_shstd_clr_stall_pipe[ptr->ip]);
                    hw_usb_set_sqclr(ptr, usb_shstd_clr_stall_pipe[ptr->ip]); /* SQCLR */
                }

                (*usb_shstd_clr_stall_call)(ptr, retval, USB_MSG_HCD_CLR_STALL);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
  #endif                               /* #if (BSP_CFG_RTOS == 2) */
                break;
            }

            case USB_MSG_HCD_CLRSEQBIT:
            {
                hw_usb_set_sqclr(ptr, pipenum);                                               /* SQCLR */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_CLRSEQBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_SETSEQBIT:
            {
                hw_usb_set_sqset(ptr, pipenum);                                               /* SQSET */
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_SETSEQBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);                                           /* Release Memory Block */
                break;
            }

            case USB_MSG_HCD_TRANSEND1:
            {
                /* Pipe Transfer Process check */
                if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
                {
                    /* Control Transfer stop */
                    if (USB_PIPE0 == pipenum)
                    {
                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_TMO);
                    }
                    else
                    {
                        /* Transfer stop */
                        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_TMO);
                    }
                }
                else
                {
                    USB_PRINTF1("### Host not transfer %d\n", pipenum);
                }

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_TRANSEND2:
            {
                /* Pipe Transfer Process check */
                if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
                {
                    /* Control Transfer stop */
                    if (USB_PIPE0 == pipenum)
                    {
                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STOP);
                    }
                    else
                    {
                        /* Transfer stop */
                        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_STOP);
                    }
                }
                else
                {
                    USB_PRINTF1("### Host not transfer %d\n", pipenum);
                }

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
                break;
            }

            case USB_MSG_HCD_D1FIFO_INT:
            {
                break;
            }

            case USB_MSG_HCD_RESM_INT:
            {
                break;
            }

            default:
            {
                break;
            }
        }
    }

  #if (BSP_CFG_RTOS == 2)
    if (result == 1)
    {
        continue;
    }
  #else
    if (result == 2)
    {
        return;
    }
  #endif                               /* (BSP_CFG_RTOS == 2) */

  #if (BSP_CFG_RTOS == 2)
}                                      /* End of while(1) */
  #endif                               /* #if (BSP_CFG_RTOS == 2) */
}

/******************************************************************************
 * End of function usb_hstd_hcd_task
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_send_start
 * Description     : Start data transmission using CPU/DMA transfer to USB host/
 *               : /device.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_send_start (usb_utr_t * ptr, uint16_t pipe)
{
    usb_utr_t * pp;
    uint32_t    length;
    uint16_t    useport;
  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint8_t               dma_ch;
    dmac_extended_cfg_t * channel_info;
  #endif                               /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Evacuation pointer */
    pp     = g_p_usb_hstd_pipe[ptr->ip][pipe];
    length = pp->tranlen;

    /* Check transfer count */
    if (USB_TRAN_CONT == pp->segment)
    {
        /* Sequence toggle */
        usb_hstd_do_sqtgl(ptr, pipe, pp->pipectr);
    }

    usb_cstd_set_nak(ptr, pipe);                                      /* Select NAK */
    g_usb_hstd_data_cnt[ptr->ip][pipe]   = length;                    /* Set data count */
    gp_usb_hstd_data_ptr[ptr->ip][pipe]  = (uint8_t *) pp->p_tranadr; /* Set data pointer */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;              /* Ignore count clear */

    hw_usb_clear_status_bemp(ptr, pipe);                              /* BEMP Status Clear */
    hw_usb_clear_sts_brdy(ptr, pipe);                                 /* BRDY Status Clear */

    useport = usb_hstd_pipe2fport(ptr, pipe);                         /* Pipe number to FIFO port select */

    /* Check use FIFO access */
    switch (useport)
    {
        case USB_CUSE:                   /* CFIFO use */
        {
            /* Buffer to FIFO data write */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);
            usb_cstd_set_buf(ptr, pipe); /* Set BUF */

            break;
        }

  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        /* D0FIFO DMA */
        case USB_D0USE:

        /* D1FIFO DMA */
        case USB_D1USE:
        {
            if (USB_IP0 == ptr->ip)
            {
                channel_info = (dmac_extended_cfg_t *) ptr->p_transfer_tx->p_cfg->p_extend;
                dma_ch       = channel_info->channel;
            }
            else
            {
                channel_info = (dmac_extended_cfg_t *) ptr->p_transfer_tx->p_cfg->p_extend;
                dma_ch       = channel_info->channel;
            }

            /* Setting for use PIPE number */
            g_usb_cstd_dma_pipe[ptr->ip][dma_ch] = pipe;

            /* Buffer size */
            g_usb_cstd_dma_fifo[ptr->ip][dma_ch] = usb_cstd_get_buf_size(ptr, pipe);

            /* Check data count */
            if (g_usb_hstd_data_cnt[ptr->ip][pipe] <= g_usb_cstd_dma_fifo[ptr->ip][dma_ch])
            {
                /* Transfer data size */
                g_usb_cstd_dma_size[ptr->ip][dma_ch] = g_usb_hstd_data_cnt[ptr->ip][pipe];

                /* Enable Empty Interrupt */
                hw_usb_set_bempenb(ptr, pipe);
            }
            else
            {
                /* Data size == FIFO size */
                g_usb_cstd_dma_size[ptr->ip][dma_ch] = (g_usb_hstd_data_cnt[ptr->ip][pipe] -
                                                        (g_usb_hstd_data_cnt[ptr->ip][pipe] %
                                                         g_usb_cstd_dma_fifo[ptr->ip][dma_ch]));
            }

            usb_cstd_dma_send_start(ptr, pipe, useport);

            /* Set BUF */
            usb_cstd_set_buf(ptr, pipe);
            break;
        }
  #endif                               /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default:
        {
            /* Access is NG */
            USB_PRINTF1("### USB-ITRON is not support(SND-else:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_send_start
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_fifo_to_buf
 * Description     : Request readout from USB FIFO to buffer and process depending
 *               : on status; read complete or reading.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 *               : uint16_t pipe  : Pipe no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_fifo_to_buf (usb_utr_t * ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag = USB_ERROR;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;

    end_flag = usb_hstd_read_data(ptr, pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_READING:
        {
            /* Continue of data read */

            break;
        }

        case USB_READEND:
        {
            /* End of data read */
            usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_OK);

            break;
        }

        case USB_READSHRT:
        {
            /* End of data read */
            usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_SHT);

            break;
        }

        case USB_READOVER:
        {
            /* Buffer over */
            USB_PRINTF1("### Receive data over PIPE%d\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_OVR);

            break;
        }

        case USB_FIFOERROR:
        {
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

            break;
        }

        default:
        {
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_fifo_to_buf
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_buf_to_fifo
 * Description     : Set USB registers as required to write from data buffer to USB
 *              : FIFO, to have USB FIFO to write data to bus.
 * Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure.
 *              : uint16_t pipe     : Pipe no.
 *              : uint16_t useport  : Port no.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_buf_to_fifo (usb_utr_t * ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return;                        /* Error */
    }

    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;

    end_flag = usb_hstd_write_data(ptr, pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_WRITING:
        {
            /* Continue of data write */
            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);

            break;
        }

        case USB_WRITEEND:

        /* End of data write */
        /* continue */

        case USB_WRITESHRT:
        {
            /* End of data write */
            /* Enable Empty Interrupt */
            hw_usb_set_bempenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);

            break;
        }

        case USB_FIFOERROR:
        {
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

            break;
        }

        default:
        {
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
            break;
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_buf_to_fifo
 ******************************************************************************/
 #endif                                /* USB_IP_EHCI_OHCI == 0 */

/******************************************************************************
 * Function Name   : usb_class_request_complete
 * Description     : Class request transfer complete
 * Arguments       : usb_utr_t *mess  : Pointer to usb_utr_t structure.
 *               : uint16_t  data1  : Not used.
 *               : uint16_t  data2  : Not used.
 * Return          : none
 ******************************************************************************/
void usb_class_request_complete (usb_utr_t * mess, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    (void) data1;
    (void) data2;

    if (USB_CTRL_END == mess->status)        /* Check usb receive status */
    {
        ctrl.status = USB_SETUP_STATUS_ACK;
    }
    else if (USB_DATA_STALL == mess->status) /* Check usb receive status */
    {
        ctrl.status = USB_SETUP_STATUS_STALL;
    }
    else
    {
        ctrl.status = USB_ERROR;
    }

    ctrl.type                 = USB_CLASS_REQUEST;
    ctrl.module_number        = mess->ip; /* Module number setting */
    ctrl.setup.request_type   = mess->p_setup[0];
    ctrl.pipe                 = USB_PIPE0;
    ctrl.setup.request_value  = mess->p_setup[1];
    ctrl.setup.request_index  = mess->p_setup[2];
    ctrl.setup.request_length = mess->p_setup[3];
    ctrl.device_address       = (uint8_t) mess->p_setup[4];
    ctrl.data_size            = ctrl.setup.request_length - g_usb_hstd_data_cnt_pipe0[mess->ip];
 #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) mess->cur_task_hdl;
 #endif                                                /* #if (BSP_CFG_RTOS == 2) */

    usb_set_event(USB_STATUS_REQUEST_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_class_request_complete
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hstd_transfer_end
 * Description     : Request HCD to force termination of data transfer.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t pipe        : Pipe number
 *               : uint16_t status      : Data transfer status
 * Return          : usb_err_t error code : USB_OK etc
 ******************************************************************************/
usb_er_t usb_hstd_transfer_end (usb_utr_t * ptr, uint16_t pipe, uint16_t status)
{
    uint16_t msg;
    usb_er_t err;

  #if (BSP_CFG_RTOS == 0)
    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR;              /* Error */
    }

    if (USB_ON == g_usb_hstd_pipe_request[ptr->ip][pipe])
    {
        return USB_ERROR;
    }
  #endif                               /* (BSP_CFG_RTOS == 0) */

    if (NULL == g_p_usb_hstd_pipe[ptr->ip][pipe])
    {
        USB_PRINTF1("### usb_hstd_transfer_end overlaps %d\n", pipe);

        return USB_QOVR;
    }

    if (USB_DATA_TMO == status)
    {
        msg = USB_MSG_HCD_TRANSEND1;
    }
    else
    {
        msg = USB_MSG_HCD_TRANSEND2;
    }

    err = usb_hstd_hcd_snd_mbx(ptr, msg, pipe, (uint16_t *) 0, &usb_hstd_dummy_function);

    return err;
}

/******************************************************************************
 * End of function usb_hstd_transfer_end
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_driver_registration
 * Description     : The HDCD information registered in the class driver structure
 *               : is registered in HCD.
 * Arguments       : usb_utr_t *ptr           : Pointer to usb_utr_t structure.
 *               : usb_hcdreg_t *callback   : Pointer to usb_hcdreg_t structure
 * Return          : none
 ******************************************************************************/
void usb_hstd_driver_registration (usb_utr_t * ptr, usb_hcdreg_t * callback)
{
    usb_hcdreg_t * driver;

    if (g_usb_hstd_device_num[ptr->ip] <= USB_MAXDEVADDR)
    {
        driver = &g_usb_hstd_device_drv[ptr->ip][g_usb_hstd_device_num[ptr->ip]];

        driver->rootport   = USB_NOPORT;           /* Root port */
        driver->devaddr    = USB_NODEVICE;         /* Device address */
        driver->devstate   = USB_DETACHED;         /* Device state */
        driver->ifclass    = callback->ifclass;    /* Interface Class */
        driver->p_tpl      = callback->p_tpl;      /* Target peripheral list */
        driver->classinit  = callback->classinit;  /* Driver init */
        driver->classcheck = callback->classcheck; /* Driver check */
        driver->devconfig  = callback->devconfig;  /* Device configured */
        driver->devdetach  = callback->devdetach;  /* Device detach */
        driver->devsuspend = callback->devsuspend; /* Device suspend */
        driver->devresume  = callback->devresume;  /* Device resume */
        /* Initialized device driver */
        (*driver->classinit)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);
        g_usb_hstd_device_num[ptr->ip]++;
        USB_PRINTF1("*** Registration driver 0x%02x\n", driver->ifclass);
    }
}

/******************************************************************************
 * End of function usb_hstd_driver_registration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_driver_release
 * Description     : Release the Device Class Driver.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint8_t   devclass   : Interface class
 * Return          : none
 ******************************************************************************/
void usb_hstd_driver_release (usb_utr_t * ptr, uint8_t devclass)
{
    usb_hcdreg_t * driver;
    uint16_t       i;
    uint16_t       flg;

    if (USB_IFCLS_NOT == devclass)
    {
        /* Device driver number */
        g_usb_hstd_device_num[ptr->ip] = 0;
    }
    else
    {
        flg = 0U;

        /* WAIT_LOOP */
        for (i = 0U; (i < (USB_MAXDEVADDR + 1U)) && (0U == flg); i++)
        {
            driver = &g_usb_hstd_device_drv[ptr->ip][i];
            if (driver->ifclass == devclass)
            {
                driver->rootport = USB_NOPORT;   /* Root port */
                driver->devaddr  = USB_NODEVICE; /* Device address */
                driver->devstate = USB_DETACHED; /* Device state */

                /* Interface Class : NO class */
                driver->ifclass = (uint16_t) USB_IFCLS_NOT;

                g_usb_hstd_device_num[ptr->ip]--;
                USB_PRINTF1("*** Release class %d driver ***\n", devclass);
                flg = 1U;              /* break; */
            }
        }
    }
}

/******************************************************************************
 * End of function usb_hstd_driver_release
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_set_pipe_info
 * Description     : Copy information of pipe information table from source
 *               :  (2nd argument) to destination (1st argument)
 * Argument        : usb_pipe_table_t *dst_ep_tbl      : DEF_EP table pointer(destination)
 *               : usb_pipe_table_t *src_ep_tbl      : DEF_EP table pointer(source)
 * Return          : none
 ******************************************************************************/
void usb_hstd_set_pipe_info (uint16_t ip_no, uint16_t pipe_no, usb_pipe_table_reg_t * src_ep_tbl)
{
    g_usb_pipe_table[ip_no][pipe_no].use_flag = USB_TRUE;
    g_usb_pipe_table[ip_no][pipe_no].pipe_cfg = src_ep_tbl->pipe_cfg;
 #if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ip_no)
    {
        g_usb_pipe_table[ip_no][pipe_no].pipe_buf = src_ep_tbl->pipe_buf;
    }
 #endif                                /* defined(BSP_MCU_GROUP_RA6M3) */
    g_usb_pipe_table[ip_no][pipe_no].pipe_maxp = src_ep_tbl->pipe_maxp;
    g_usb_pipe_table[ip_no][pipe_no].pipe_peri = src_ep_tbl->pipe_peri;
}

/******************************************************************************
 * End of function usb_hstd_set_pipe_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_return_enu_mgr
 * Description     : Continuous enumeration is requested to MGR task (API for nonOS)
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t cls_result  : class check result
 * Return          : none
 ******************************************************************************/
void usb_hstd_return_enu_mgr (usb_utr_t * ptr, uint16_t cls_result)
{
    g_usb_hstd_check_enu_result[ptr->ip] = cls_result;
    usb_hstd_mgr_snd_mbx(ptr, USB_MSG_MGR_SUBMITRESULT, USB_PIPE0, USB_CTRL_END);
}

/******************************************************************************
 * End of function usb_hstd_return_enu_mgr
 ******************************************************************************/

 #if (USB_UT_MODE == 0)

/******************************************************************************
 * Function Name   : usb_hstd_change_device_state
 * Description     : Request to change the status of the connected USB Device
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : usb_cb_t complete    : callback function pointer
 *               : uint16_t msginfo     : Message Info
 *               : uint16_t member      : Device address/pipe number
 * Return          : usb_err_t            : USB_OK etc
 ******************************************************************************/
usb_er_t usb_hstd_change_device_state (usb_utr_t * ptr, usb_cb_t complete, uint16_t msginfo, uint16_t member)
{
    usb_mh_t        p_blf;
    usb_er_t        err;
    usb_er_t        err2;
    usb_hcdinfo_t * hp;

    switch (msginfo)
    {
        /* USB_MSG_HCD_CLR_STALL */
        case USB_DO_CLR_STALL:
        {
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_CLR_STALL, member, (uint16_t *) 0, complete);
            break;
        }

        /* USB_MSG_HCD_SQTGLBIT */
        case USB_DO_SET_SQTGL:
        {
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_SETSEQBIT, member, (uint16_t *) 0, complete);
            break;
        }

        /* USB_MSG_HCD_CLRSEQBIT */
        case USB_DO_CLR_SQTGL:
        {
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_CLRSEQBIT, member, (uint16_t *) 0, complete);
            break;
        }

        default:
        {
            /* Get memory pool blk */
            err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
            if (FSP_SUCCESS == err)
            {
                USB_PRINTF2("*** member%d : msginfo=%d ***\n", member, msginfo);
                hp           = (usb_hcdinfo_t *) p_blf;
                hp->msghead  = (usb_mh_t) USB_NULL;
                hp->msginfo  = msginfo;
                hp->keyword  = member;
                hp->complete = complete;

                hp->ipp = ptr->ipp;
                hp->ip  = ptr->ip;
  #if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
                hp->p_transfer_rx = ptr->p_transfer_rx;
                hp->p_transfer_tx = ptr->p_transfer_tx;
  #endif
  #if (BSP_CFG_RTOS == 2)
                hp->cur_task_hdl = xTaskGetCurrentTaskHandle();
  #endif                               /* #if (BSP_CFG_RTOS == 2) */

                /* Send message */
                err = USB_SND_MSG(USB_MGR_MBX, (usb_msg_t *) p_blf);
                if (FSP_SUCCESS != err)
                {
                    USB_PRINTF1("### hMgrChangeDeviceState snd_msg error (%ld)\n", err);
                    err2 = USB_REL_BLK(USB_MGR_MPL, (usb_mh_t) p_blf);
                    if (FSP_SUCCESS != err2)
                    {
                        USB_PRINTF1("### hMgrChangeDeviceState rel_blk error (%ld)\n", err2);
                    }
                }
            }
            else
            {
                /* Error */
                /* WAIT_LOOP */
                while (1)
                {
                    /* error */
                }
            }

            break;
        }
    }

    return err;
}

/******************************************************************************
 * End of function usb_hstd_change_device_state
 ******************************************************************************/
 #endif                                /* #if (USB_UT_MODE == 0) */

/***************************************************************************//**
 * @brief Start HCD(Host Control Driver) task
 *
 * @retval FSP_SUCCESS         Success.
 * @retval FSP_ERR_USB_FAILED  Failed in acquiring version information.
 ******************************************************************************/
fsp_err_t usb_hstd_hcd_open (usb_utr_t * ptr)
{
    static uint8_t is_init = USB_NO;
    uint16_t       i;
    uint16_t       j;
    fsp_err_t      err = FSP_SUCCESS;

    if (USB_MAXDEVADDR < USB_DEVICEADDR)
    {
        USB_PRINTF0("Device address error\n");

        /* >yes no process */
        return FSP_ERR_USB_FAILED;
    }

    /* Global Init */
    if (USB_NO == is_init)
    {
 #if  USB_IP_EHCI_OHCI == 0
  #if (BSP_CFG_RTOS == 0)
        usb_shstd_clr_stall_call = 0;
  #endif                               /* (BSP_CFG_RTOS == 0) */
        usb_shstd_clr_stall_pipe[0] = 0;
 #endif /* USB_IP_EHCI_OHCI == 0 */
        memset((void *) &usb_shstd_clr_stall_ctrl[0], 0, sizeof(usb_utr_t));
        memset((void *) &usb_shstd_clr_stall_request[0], 0, (5 * 2));
 #if (USB_NUM_USBIP == 2)
  #if  USB_IP_EHCI_OHCI == 0
        usb_shstd_clr_stall_pipe[1] = 0;
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
        memset((void *) &usb_shstd_clr_stall_ctrl[1], 0, sizeof(usb_utr_t));
        memset((void *) &usb_shstd_clr_stall_request[1], 0, (5 * 2));
 #endif
        is_init = USB_YES;
    }

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAXDEVADDR + 1); i++)
    {
        memset((void *) &g_usb_hstd_device_drv[ptr->ip][i], 0, sizeof(usb_hcdreg_t));
        memset((void *) &g_usb_hstd_device_info[ptr->ip][i], 0, (8 * 2));
        g_usb_hstd_dcp_register[ptr->ip][i] = 0;
        memset((void *) &g_usb_ctrl_request[ptr->ip][i], 0, sizeof(usb_ctrl_trans_t));
    }

    /* WAIT_LOOP */
    for (i = 0; i < (USB_MAX_PIPE_NO + 1); i++)
    {
        g_usb_hstd_data_cnt[ptr->ip][i]   = 0;
        gp_usb_hstd_data_ptr[ptr->ip][i]  = 0;
        g_usb_hstd_ignore_cnt[ptr->ip][i] = 0;
 #if (BSP_CFG_RTOS == 0)
        g_usb_hstd_pipe_request[ptr->ip][i] = 0;
 #endif                                /* (BSP_CFG_RTOS == 0) */
    }

    g_usb_hstd_device_addr[ptr->ip]  = 0;
    g_usb_hstd_device_speed[ptr->ip] = 0;
    g_usb_hstd_device_num[ptr->ip]   = 0;

    /* Control transfer stage management */
    g_usb_hstd_ctsq[ptr->ip] = USB_IDLEST;

    g_usb_hstd_remort_port[ptr->ip] = USB_DEFAULT;

    j = ptr->ip;

    /* WAIT_LOOP */
    for (i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++)
    {
        g_p_usb_hstd_pipe[j][i] = (usb_utr_t *) USB_NULL;
    }

 #if USB_CFG_BC == USB_CFG_ENABLE
  #if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ptr->ip)
    {
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_INIT;
    }
  #endif                               /* defined(BSP_MCU_GROUP_RA6M3) */
 #endif                                /* USB_CFG_BC == USB_CFG_ENABLE */

    USB_PRINTF0("*** Install USB-HCD ***\n");

    usb_cstd_set_task_pri(USB_HCD_TSK, USB_PRI_1);

    return err;
}

/******************************************************************************
 * End of function usb_hstd_hcd_open
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_dummy_function
 * Description     : Dummy function
 * Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *               : uint16_t data1    : Not used.
 *               : uint16_t data2    : Not used.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_dummy_function (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    (void) *ptr;
    (void) data1;
    (void) data2;

    /* None */
}

/******************************************************************************
 * End of function usb_hstd_dummy_function
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_suspend_complete
 * Description     : usb_hstd_change_device_state callback (Suspend)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t data1   : Not used.
 *               : uint16_t data2   : Not used.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_suspend_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    usb_cfg_t         * p_cfg;

    (void) data1;
    (void) data2;

 #if (BSP_CFG_RTOS == 0)
    g_usb_change_device_state[ptr->ip] &= (uint16_t) (~(1 << USB_STATUS_SUSPEND));
 #endif                                /* BSP_CFG_RTOS == 0 */

    ctrl.module_number  = ptr->ip;     /* USB Module Number */
    ctrl.device_address = 1;           /* Device Address Number */
 #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS == 2) */

    if (ptr->ip)
    {
 #if defined(BSP_MCU_GROUP_RA6M3)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
 #else
  #if defined(BSP_MCU_GROUP_RZA3UL)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) USB_U2H0_EHCI_INT_IRQn);
  #else
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USB_HI);
  #endif
 #endif
    }
    else
    {
 #if defined(BSP_MCU_GROUP_RZA3UL)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) USB_U2H1_EHCI_INT_IRQn);
 #else
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USB_HI);
 #endif
    }

    ctrl.p_context = (void *) p_cfg->p_context;

    usb_set_event(USB_STATUS_SUSPEND, &ctrl);
}

/******************************************************************************
 * End of function usb_hstd_suspend_complete
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hstd_resume_complete
 * Description     : usb_hstd_change_device_state callback (Resume)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
 *               : uint16_t data1   : Not used.
 *               : uint16_t data2   : Not used.
 * Return value    : none
 ******************************************************************************/
void usb_hstd_resume_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;
    usb_cfg_t         * p_cfg;

    (void) data1;
    (void) data2;

 #if (BSP_CFG_RTOS == 0)
    g_usb_change_device_state[ptr->ip] &= (uint16_t) (~(1 << USB_STATUS_RESUME));
 #endif                                /* BSP_CFG_RTOS == 0 */

    ctrl.module_number  = ptr->ip;
    ctrl.device_address = 1;
 #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
 #endif                                /* #if (BSP_CFG_RTOS == 2) */

    if (ptr->ip)
    {
 #if defined(BSP_MCU_GROUP_RA6M3)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USBHS_USB_INT_RESUME);
 #else
  #if defined(BSP_MCU_GROUP_RZA3UL)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) USB_U2H0_EHCI_INT_IRQn);
  #else
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USB_HI);
  #endif
 #endif
    }
    else
    {
 #if defined(BSP_MCU_GROUP_RZA3UL)
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) USB_U2H1_EHCI_INT_IRQn);
 #else
        p_cfg = (usb_cfg_t *) R_FSP_IsrContextGet((IRQn_Type) VECTOR_NUMBER_USB_HI);
 #endif
    }

    ctrl.p_context = (void *) p_cfg->p_context;

    usb_set_event(USB_STATUS_RESUME, &ctrl);
}                                      /* End of function usb_hstd_resume_complete */

/******************************************************************************
 * Function Name  : usb_hstd_device_information
 * Description    : Get the status of the connected USB Device
 * Arguments      : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 *              : uint16_t devaddr  : Device address
 *              : uint16_t *tbl     : Table Pointer
 * Return         : None
 ******************************************************************************/
void usb_hstd_device_information (usb_utr_t * ptr, uint16_t devaddr, uint16_t * tbl)
{
    uint16_t   i;
    uint16_t   port;
    uint16_t * p;

    if (0 == devaddr)
    {
        p = tbl;
        for (i = 0; i < 8; ++i)
        {
            *p++ = USB_NOPORT;
        }

        port   = g_usb_hstd_device_info[ptr->ip][devaddr][0];
        tbl[0] = port;
        tbl[1] = g_usb_hstd_mgr_mode[ptr->ip];
        tbl[4] = g_usb_hstd_device_info[ptr->ip][devaddr][4];
    }
    else
    {
        for (i = 0; i < 8; ++i)
        {
            tbl[i] = g_usb_hstd_device_info[ptr->ip][devaddr][i];
        }
    }

    tbl[8] = g_usb_hstd_mgr_mode[ptr->ip];
}

/******************************************************************************
 * End of function usb_hstd_device_information
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_host_registration
 * Description     : sample registration.
 * Argument        : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 * Return          : none
 ******************************************************************************/
void usb_host_registration (usb_utr_t * ptr)
{
    (void) *ptr;

 #if defined(USB_CFG_HCDC_USE)
    usb_hcdc_registration(ptr);
 #endif                                /* defined(USB_CFG_HCDC_USE) */

 #if defined(USB_CFG_HHID_USE)
    usb_hhid_registration(ptr);
 #endif                                /* defined(USB_CFG_HHID_USE) */

 #if defined(USB_CFG_HMSC_USE)
    usb_hmsc_registration(ptr);
 #endif                                /* defined(USB_CFG_HMSC_USE) */

 #if defined(USB_CFG_HVND_USE)
    usb_hvnd_registration(ptr);
 #endif                                /* defined(USB_CFG_HVND_USE) */
}

/******************************************************************************
 * End of function usb_host_registration
 ******************************************************************************/

 #if (USB_UT_MODE == 0)
  #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : usb_hstd_transfer_start
 * Description     : Send a request for data transfer to HCD (Host Control Driver)
 *               : using the specified pipe.
 * Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 * Return          : usb_er_t       : USB_OK/USB_QOVR/USB_ERROR
 ******************************************************************************/
usb_er_t usb_hstd_transfer_start (usb_utr_t * ptr)
{
    usb_er_t err;

    /* Check enumeration  */
    if (USB_PIPE0 == ptr->keyword)
    {
        if (USB_DEFAULT == g_usb_hstd_mgr_mode[ptr->ip])
        {
            return USB_QOVR;
        }
    }

    err = usb_hstd_transfer_start_req(ptr);

    return err;
}

/******************************************************************************
 * End of function usb_hstd_transfer_start
 ******************************************************************************/
  #endif                               /* USB_IP_EHCI_OHCI == 0 */
 #endif                                /* #if (USB_UT_MODE == 0) */

/******************************************************************************
 * Function Name   : usb_hstd_connect_err_event_set
 * Description     : Set event for "USB_STS_NOT_SUPPORT"
 * Arguments       : uint16_t ip_no  : IP no.(USB_IP0/USB_IP1)
 * Return          : none
 ******************************************************************************/
void usb_hstd_connect_err_event_set (uint16_t ip_no)
{
    usb_instance_ctrl_t ctrl;

    ctrl.device_address = (uint8_t) g_usb_hstd_device_addr[ip_no]; /* usb device address */
    ctrl.module_number  = (uint8_t) ip_no;                         /* module number setting */
    usb_set_event(USB_STATUS_NOT_SUPPORT, &ctrl);                  /* set event()  */
}

/******************************************************************************
 * End of function usb_hstd_connect_err_event_set
 ******************************************************************************/

 #if defined(USB_CFG_HVND_USE)

/******************************************************************************
 * Function Name   : usb_hvnd_set_pipe_registration
 * Description     : Host CDC pipe registration.
 * Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 *               : uint16_t  devadr     : Device address
 * Return          : usb_er_t             : Error info
 ******************************************************************************/
usb_er_t usb_hvnd_set_pipe_registration (usb_utr_t * ptr, uint16_t dev_addr)
{
    usb_er_t err;                      /* Error code */
    uint8_t  pipe_no;

    err = USB_ERROR;

    /* Device address check */
    if (0 != dev_addr)
    {
        /* Search use pipe block */
        /* WAIT_LOOP */
        for (pipe_no = USB_MIN_PIPE_NO; pipe_no < (USB_MAX_PIPE_NO + 1); pipe_no++)
        {
            /* Check use block */
            if (USB_TRUE == g_usb_pipe_table[ptr->ip][pipe_no].use_flag)
            {
                /* Check USB Device address */
                if ((dev_addr << USB_DEVADDRBIT) == (g_usb_pipe_table[ptr->ip][pipe_no].pipe_maxp & USB_DEVSEL))
                {
                    usb_hstd_set_pipe_reg(ptr, pipe_no);
                    err = USB_OK;
                }
            }
        }
    }
    else
    {
        /* Error */
        USB_PRINTF1("SmplOpen adr error %x\n", dev_addr);
    }

    return err;
}

/******************************************************************************
 * End of function usb_hvnd_set_pipe_registration()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_configured
 * Description     : Host vendor application initialization.
 * Argument        : usb_utr_t *ptr    : IP info (mode, IP no, reg. address).
 * : uint16_t dev_addr : Device address.
 * : uint16_t data2    : Not used.
 * Return          : none
 ******************************************************************************/
void usb_hvnd_configured (usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    ctrl.module  = ptr->ip;            /* Module number setting */
    ctrl.address = dev_addr;
    if (0 != dev_addr)
    {
        /* Registration */
        usb_hvnd_set_pipe_registration(ptr, dev_addr); /* Host CDC Pipe registration */
    }

    usb_set_event(USB_STS_CONFIGURED, &ctrl);
}

/******************************************************************************
 * End of function usb_hvnd_configured
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_detach
 * Description     : Close host vendor application.
 * Argument        : usb_utr_t *ptr    : IP info (mode, IP no, reg. address).
 * : uint16_t data1            : Not Use
 * : uint16_t data2            : Not Use
 * Return          : none
 ******************************************************************************/
void usb_hvnd_detach (usb_utr_t * ptr, uint16_t dev_addr, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    usb_hstd_clr_pipe_table(ptr->ip, dev_addr);

    ctrl.module  = ptr->ip;            /* Module number setting */
    ctrl.address = dev_addr;
    usb_set_event(USB_STS_DETACH, &ctrl);
}

/******************************************************************************
 * End of function usb_hvnd_detach
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_enumeration
 * Description     : Vendor class example enumeration execution by host.
 * Argument        : usb_clsinfo_t *mess   : Class info data pointer.
 * Return          : none
 ******************************************************************************/
void usb_hvnd_enumeration (usb_clsinfo_t * mess, uint16_t ** table)
{
    uint8_t * pdesc;
    uint16_t  total_len;
    uint16_t  speed;

    *table[3] = USB_OK;

    /* Pipe Information table set */
    speed = *table[6];
    pdesc = (uint8_t *) g_usb_hstd_config_descriptor[mess->ip];

    total_len  = ((uint16_t) *(pdesc + 3)) << 8;
    total_len |= (uint16_t) *(pdesc + 2);

    /* Pipe Information table set */
    usb_hvnd_pipe_info(pdesc, speed, total_len);

  #if (BSP_CFG_RTOS == 0)
    usb_hstd_return_enu_mgr(mess, USB_OK); /* Return to MGR */
  #endif /* BSP_CFG_RTOS == 0 */
}

/******************************************************************************
 * End of function usb_hvnd_enumeration
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_pipe_info
 * Description     : Host pipe information check. Set EP table.
 * Arguments       : uint8_t *table        : Descriptor start address.
 * : uint16_t speed        : Device connected speed
 * : uint16_t length       : Configuration Descriptor Length
 * Return value    : none
 ******************************************************************************/
void usb_hvnd_pipe_info (uint8_t * table, uint16_t speed, uint16_t length)
{
    uint16_t             ofdsc;
    uint16_t             pipe_no;
    usb_pipe_table_reg_t ep_tbl;

    /* Check Endpoint Descriptor */
    ofdsc = table[0];

    /* WAIT_LOOP */
    while (ofdsc < length)
    {
        /* Search within Interface */
        if (USB_DT_ENDPOINT == table[ofdsc + 1])
        {
            pipe_no = usb_hstd_make_pipe_reg_info(USB_IP0, 1, USB_HVND, speed, &table[ofdsc], &ep_tbl);
            if (USB_NULL == pipe_no)
            {
                return;
            }
            else
            {
                usb_hstd_set_pipe_info(USB_IP0, pipe_no, &ep_tbl);
            }

            ofdsc += table[ofdsc];
        }
        else
        {
            ofdsc += table[ofdsc];
        }
    }
}

/******************************************************************************
 * End of function usb_hvnd_pipe_info
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_read_complete
 * Description     : Notify application task of data reception completion.
 * : (Callback function at completion of INT data reception.)
 * Arguments       :
 * Return value    : none
 ******************************************************************************/
void usb_hvnd_read_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    ctrl.module = ptr->ip;             /* Module number setting */
    ctrl.pipe   = ptr->keyword;        /* Pipe number setting */
    ctrl.type   = USB_HVND;            /* Vendor class  */

    ctrl.size    = ptr->read_req_len - ptr->tranlen;
    ctrl.address = usb_hstd_get_devsel(ptr, ctrl.pipe) >> 12;
  #if #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
  #endif                               /* #if (BSP_CFG_RTOS == 2) */

    switch (ptr->status)
    {
        case USB_DATA_OK:
        {
            ctrl.status = USB_SUCCESS;
            break;
        }

        case USB_DATA_SHT:
        {
            ctrl.status = USB_ERR_SHORT;
            break;
        }

        case USB_DATA_OVR:
        {
            ctrl.status = USB_ERR_OVER;
            break;
        }

        case USB_DATA_ERR:
        default:
        {
            ctrl.status = USB_ERR_NG;
            break;
        }
    }

    usb_set_event(USB_STS_READ_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hvnd_read_complete()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_write_complete
 * Description     : Notify application task of data transmission completion.
 * : (Callback function at completion of INT data reception.)
 * Arguments       :
 * Return value    : none
 ******************************************************************************/
void usb_hvnd_write_complete (usb_utr_t * ptr, uint16_t data1, uint16_t data2)
{
    usb_instance_ctrl_t ctrl;

    ctrl.module  = ptr->ip;            /* Module number setting */
    ctrl.pipe    = ptr->keyword;       /* Pipe number setting */
    ctrl.type    = USB_HVND;           /* Vendor class  */
    ctrl.address = usb_hstd_get_devsel(ptr, ctrl.pipe) >> 12;
  #if #if (BSP_CFG_RTOS == 2)
    ctrl.p_data = (void *) ptr->cur_task_hdl;
  #endif /* #if (BSP_CFG_RTOS == 2) */

    if (USB_DATA_NONE == ptr->status)
    {
        ctrl.status = USB_SUCCESS;
    }
    else
    {
        ctrl.status = USB_ERR_NG;
    }

    usb_set_event(USB_STS_WRITE_COMPLETE, &ctrl); /* Set Event()  */
}

/******************************************************************************
 * End of function usb_hvnd_write_complete()
 ******************************************************************************/

/******************************************************************************
 * Function Name   : usb_hvnd_registration
 * Description     : Host vendor class registration.
 * Argument        : usb_utr_t *ptr    : IP info (mode, IP no, reg. address).
 * Return          : none
 ******************************************************************************/
void usb_hvnd_registration (usb_utr_t * ptr)
{
    usb_hcdreg_t driver;

    /* Driver registration */

    /* Interface Class */
    driver.ifclass = (uint16_t) USB_IFCLS_VEN;

    /* Target peripheral list */
    driver.p_tpl = (uint16_t *) &g_usb_apl_devicetpl;

    /* Driver init */
    driver.classinit = &usb_hstd_dummy_function;

    /* Driver check */
    driver.classcheck = &usb_hvnd_enumeration;

    /* Device configured */
    driver.devconfig = &usb_hvnd_configured;

    /* Device detach */
    driver.devdetach = &usb_hvnd_detach;

    /* Device suspend */
    driver.devsuspend = &usb_hstd_dummy_function;

    /* Device resume */
    driver.devresume = &usb_hstd_dummy_function;

    usb_hstd_driver_registration(ptr, &driver);

  #if USB_CFG_HUB == USB_CFG_ENABLE
   #if (BSP_CFG_RTOS == 0)
    usb_cstd_set_task_pri(USB_HUB_TSK, USB_PRI_3);
   #endif                              /* BSP_CFG_RTOS == 0 */
    usb_hhub_registration(ptr, USB_NULL);
  #endif                               /* USB_CFG_HUB == USB_CFG_ENABLE */
}

/******************************************************************************
 * End of function usb_hvnd_registration
 ******************************************************************************/
 #endif                                /* defined(USB_CFG_HVND_USE) */

#endif                                 /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 * End  Of File
 ******************************************************************************/

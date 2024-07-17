/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic.h"
#include "../r_usb_basic/src/driver/inc/r_usb_typedef.h"
#include "../r_usb_basic/src/driver/inc/r_usb_extern.h"
#include "../r_usb_basic/src/hw/inc/r_usb_reg_access.h"

#include "r_usb_hhid_api.h"
#include "r_usb_hhid.h"
#include "src/inc/r_usb_hhid_driver.h"

/*******************************************************************************************************************//**
 * @addtogroup USB_HHID USB_HHID
 * @{
 **********************************************************************************************************************/

/*************************************************************************//**
 * @brief Get HID protocol.(USB Mouse/USB Keyboard/Other Type.)
 *
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 ******************************************************************************/
fsp_err_t R_USB_HHID_TypeGet (usb_ctrl_t * const p_api_ctrl, uint8_t * p_type, uint8_t device_address)
{
    fsp_err_t  err = FSP_SUCCESS;
    usb_info_t info;

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);

    FSP_ASSERT(p_type);

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)),
                     FSP_ERR_USB_PARAMETER);

    FSP_ERROR_RETURN(0 != device_address, FSP_ERR_USB_PARAMETER);

    FSP_ERROR_RETURN(USB_ADDRESS5 >= device_address, FSP_ERR_USB_PARAMETER);

 #if defined(BSP_MCU_GROUP_RA2A1)
    FSP_ERROR_RETURN(!(USB_IP1 == p_ctrl->module), FSP_ERR_USB_PARAMETER);
 #endif                                /* defined(BSP_MCU_GROUP_RA2A1) */
#endif /* USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */

    err = R_USB_InfoGet(p_ctrl, &info, device_address);
    FSP_ERROR_RETURN(!((FSP_SUCCESS != err) || (USB_STATUS_CONFIGURED != info.device_status)), FSP_ERR_USB_FAILED);
    *p_type = usb_hhid_get_hid_protocol(p_ctrl->module_number, device_address);

    return FSP_SUCCESS;
}

/******************************************************************************
 * End of function R_USB_HHID_TypeGet
 ******************************************************************************/

/*************************************************************************//**
 * @brief Obtains max packet size for the connected HID device.
 *        The max packet size is set to the area.
 *        Set the direction (USB_HID_IN/USB_HID_OUT).
 *
 *
 * @retval FSP_SUCCESS           Success.
 * @retval FSP_ERR_USB_FAILED    The function could not be completed successfully.
 * @retval FSP_ERR_ASSERTION     Parameter Null pointer error.
 * @retval FSP_ERR_USB_PARAMETER Parameter error.
 ******************************************************************************/

fsp_err_t R_USB_HHID_MaxPacketSizeGet (usb_ctrl_t * const p_api_ctrl,
                                       uint16_t         * p_size,
                                       uint8_t            direction,
                                       uint8_t            device_address)

{
    fsp_err_t  err;
    usb_info_t info;
    usb_utr_t  utr;
    uint16_t   pipe = 0;
    uint16_t   pipe_bit_map;
#if defined(BSP_MCU_GROUP_RZA3UL)
    uint8_t epnum;
#endif                                 /* #if defined(BSP_MCU_GROUP_RZA3UL) */

    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

#if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);

    FSP_ASSERT(p_size);

    /* Argument Checking */
    FSP_ERROR_RETURN(!((USB_IP0 != p_ctrl->module_number) && (USB_IP1 != p_ctrl->module_number)),
                     FSP_ERR_USB_PARAMETER);

    FSP_ERROR_RETURN(!((USB_HID_IN != direction) && (USB_HID_OUT != direction)), FSP_ERR_USB_PARAMETER);

    FSP_ERROR_RETURN(0 != device_address, FSP_ERR_USB_PARAMETER);

    FSP_ERROR_RETURN(USB_ADDRESS5 >= device_address, FSP_ERR_USB_PARAMETER);

 #if defined(BSP_MCU_GROUP_RA2A1)
    FSP_ASSERT(USB_IP1 != p_ctrl->module_number);
 #endif                                /* defined(BSP_MCU_GROUP_RA2A1) */
#endif /* #if USB_CFG_PARAM_CHECKING_ENABLE == BSP_CFG_PARAM_CHECKING_ENABLE */
    err = R_USB_InfoGet(p_ctrl, &info, device_address);
    FSP_ERROR_RETURN(!((FSP_SUCCESS != err) || (USB_STATUS_CONFIGURED != info.device_status)), FSP_ERR_USB_FAILED);

    if (USB_HID_IN == direction)
    {
        pipe = usb_hstd_get_pipe_no(p_ctrl->module_number,
                                    device_address,
                                    USB_CLASS_INTERNAL_HHID,
                                    USB_EP_INT,
                                    USB_PIPE_DIR_IN);
    }
    else
    {
        pipe = usb_hstd_get_pipe_no(p_ctrl->module_number,
                                    device_address,
                                    USB_CLASS_INTERNAL_HHID,
                                    USB_EP_INT,
                                    USB_PIPE_DIR_OUT);
    }

    err = R_USB_UsedPipesGet(p_ctrl, &pipe_bit_map, device_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_USB_FAILED);

    FSP_ERROR_RETURN(!(0 == ((1 << pipe) & pipe_bit_map)), FSP_ERR_USB_FAILED);

    utr.ip      = p_ctrl->module_number;
    utr.ipp     = usb_hstd_get_usb_ip_adr(utr.ip);
    utr.keyword = p_ctrl->device_address;

#if defined(BSP_MCU_GROUP_RZA3UL)
    epnum = R_USB_HstdConvertEndpointNum(utr.ip, (uint8_t) pipe);
    pipe  = R_USB_HstdGetPipeID(utr.keyword, epnum);
#endif                                 /* #if defined(BSP_MCU_GROUP_RZA3UL) */

    *p_size = usb_cstd_get_maxpacket_size(&utr, pipe);

    return FSP_SUCCESS;
}

/******************************************************************************
 * End of function R_USB_HHID_MaxPacketSizeGet
 ******************************************************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup USB_HHID)
 **********************************************************************************************************************/

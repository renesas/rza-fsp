#include "ux_host_startup.h"
#include "bsp_api.h"
#include "r_usb_extern.h"

/***********************************************/
/* Include for host classes */
#ifdef USB_HOST_HUB_CLASS_REGISTER
 #include "ux_host_class_hub.h"
#endif
#ifdef USB_HOST_CDC_ACM_CLASS_REGISTER
 #include "ux_host_class_cdc_acm.h"
#endif

#ifdef USB_HOST_HID_CLASS_REGISTER
 #include "ux_host_class_hid.h"
 #ifdef USB_HOST_HID_CLIENT_MOUSE_REGISTER
  #include "ux_host_class_hid_mouse.h"
 #endif
 #ifdef USB_HOST_HID_CLIENT_KEYBOARD_REGISTER
  #include "ux_host_class_hid_keyboard.h"
 #endif
#endif

#ifdef USB_HOST_STORAGE_CLASS_REGISTER
 #include "ux_host_class_storage.h"
#endif
#ifdef USB_HOST_VIDEO_CLASS_REGISTER
 #include "ux_host_class_video.h"
#endif
#ifdef USB_HOST_AUDIO_CLASS_REGISTER
 #include "ux_host_class_audio.h"
#endif
#ifdef USB_HOST_PRINTER_CLASS_REGISTER
 #include "ux_host_class_printer.h"
#endif

/***********************************************/
/* Memory pool area for USBX */
uint8_t g_ux_pool_memory[USB_HOST_POOL_SIZE];
#ifdef USB_HOST_UNCACHED_POOL_SIZE
BSP_ALIGN_VARIABLE(256) uint8_t g_ux_pool_memory_uncached[USB_HOST_UNCACHED_POOL_SIZE] USB_BUFFER_PLACE_IN_SECTION;
#else
 #define USB_HOST_UNCACHED_POOL_SIZE    0
 #define g_ux_pool_memory_uncached      UX_NULL
#endif

/***********************************************/
UINT ux_host_startup (usb_ctrl_t * const      p_api_ctrl,
                      usb_cfg_t const * const p_cfg,
                      UINT (                * usb_host_controller_initialization)(void))
{
    fsp_err_t err;
    UINT      status;

    if ((NULL == p_api_ctrl) || (NULL == p_cfg))
    {
        return UX_ERROR;
    }

    if (UX_NULL == usb_host_controller_initialization)
    {
        return UX_ERROR;
    }

    /* ux_system_initialization */
    status = ux_system_initialize(g_ux_pool_memory,
                                  USB_HOST_POOL_SIZE,
                                  g_ux_pool_memory_uncached,
                                  USB_HOST_UNCACHED_POOL_SIZE);
    if (UX_SUCCESS != status)
    {
        return status;
    }

    /* Setup USB module(r_usb_basic) */
    err = usb_module_start(p_cfg->module_number);
    if (FSP_SUCCESS != err)
    {
        return UX_ERROR;
    }

    /* USB host controller initialization */
    if (UX_SUCCESS != (*usb_host_controller_initialization)())
    {
        return status;
    }

    /** Register USB Host classes. */
#ifdef USB_HOST_HUB_CLASS_REGISTER
    status = ux_host_stack_class_register(_ux_system_host_class_hub_name, ux_host_class_hub_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

#ifdef USB_HOST_CDC_ACM_CLASS_REGISTER
    status = ux_host_stack_class_register(_ux_system_host_class_cdc_acm_name, ux_host_class_cdc_acm_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

#ifdef USB_HOST_HID_CLASS_REGISTER
    status = ux_host_stack_class_register(_ux_system_host_class_hid_name, ux_host_class_hid_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }

 #ifdef USB_HOST_HID_CLIENT_MOUSE_REGISTER
    status = ux_host_class_hid_client_register(_ux_system_host_class_hid_client_mouse_name,
                                               ux_host_class_hid_mouse_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
 #endif
 #ifdef USB_HOST_HID_CLIENT_KEYBOARD_REGISTER
    status = ux_host_class_hid_client_register(_ux_system_host_class_hid_client_keyboard_name,
                                               ux_host_class_hid_keyboard_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
 #endif
#endif

#ifdef USB_HOST_STORAGE_CLASS_REGISTER

    /* fx_system_initialization */
    fx_system_initialize();

    status = ux_host_stack_class_register(_ux_system_host_class_storage_name, ux_host_class_storage_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

#ifdef USB_HOST_VIDEO_CLASS_REGISTER
    status = ux_host_stack_class_register(_ux_system_host_class_video_name, ux_host_class_video_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

#ifdef USB_HOST_AUDIO_CLASS_REGISTER
    status = ux_host_stack_class_register(_ux_system_host_class_audio_name, ux_host_class_audio_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

#ifdef USB_HOST_PRINTER_CLASS_REGISTER
    status = ux_host_stack_class_register(_ux_system_host_class_printer_name, ux_host_class_printer_entry);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

    /* Enable USB interrupt(r_usb_basic) */
    usb_cpu_usbint_init(p_cfg->module_number, p_cfg);

    return UX_SUCCESS;
}

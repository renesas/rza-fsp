#include "ux_api.h"
#include "r_usb_basic_api.h"

/***********************************************/

#ifdef   __cplusplus
extern "C" {
#endif

UINT ux_host_startup(usb_ctrl_t * const      p_api_ctrl,
                     usb_cfg_t const * const p_cfg,
                     UINT (                * usb_host_controller_initialization)(void));

#ifdef   __cplusplus
}
#endif

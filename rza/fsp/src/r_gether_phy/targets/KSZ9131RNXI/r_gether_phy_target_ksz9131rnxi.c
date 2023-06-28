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

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/* Access to peripherals and board defines. */
#include "bsp_api.h"
#include "r_gether_phy.h"
#include "r_ether_phy_api.h"
#if (GETHER_PHY_CFG_USE_PHY == GETHER_PHY_CFG_USE_PHY_KSZ9131RNXI)

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/* Vendor Specific PHY Registers */
 #define GETHER_PHY_REG_MMD_ACCESS_CONTROL            (0x0D)
 #define GETHER_PHY_REG_MMD_ADDRESS_DATA              (0x0E)

 #define GETHER_PHY_REG_MMD_ACCESS_CONTROL_ADDRESS    (0x0000)
 #define GETHER_PHY_REG_MMD_ACCESS_CONTROL_DATA       (0x4000)

 #define GETHER_PHY_DEV_RX_DDL_CONTROL                (2)
 #define GETHER_PHY_REG_RX_DDL_CONTROL                (76)
 #define GETHER_PHY_DEV_TX_DDL_CONTROL                (2)
 #define GETHER_PHY_REG_TX_DDL_CONTROL                (77)

 #define GETHER_PHY_REG_RX_DDL_CONTROL_BYPASS         (0x1000UL)
 #define GETHER_PHY_REG_TX_DDL_CONTROL_BYPASS         (0x1000UL)

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
void gether_phy_targets_ksz9131rnxi_initialize(ether_phy_instance_ctrl_t * p_instance_ctrl);
bool gether_phy_target_ksz9131rnxi_is_support_link_partner_ability(
    ether_phy_instance_ctrl_t * p_instance_ctrl,
    uint32_t                    line_speed_duplex);
extern uint32_t gether_phy_read(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr);
extern void     gether_phy_write(ether_phy_instance_ctrl_t * p_instance_ctrl, uint32_t reg_addr, uint32_t data);

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gether_phy_mmd_read
 * Description  : Read MMD register
 * Arguments    : p_instance_ctrl - Instance of Ehter PHY
 *                device_address  - Device address of the register
 *                reg_addr        - Address of the register
 * Return Value : Read data of the resigster
 ***********************************************************************************************************************/
static uint32_t gether_phy_mmd_read (ether_phy_instance_ctrl_t * p_instance_ctrl,
                                     uint32_t                    device_address,
                                     uint32_t                    reg_addr)
{
    gether_phy_write(p_instance_ctrl,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL_ADDRESS | device_address);
    gether_phy_write(p_instance_ctrl, GETHER_PHY_REG_MMD_ADDRESS_DATA, reg_addr);
    gether_phy_write(p_instance_ctrl,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL_DATA | device_address);

    return gether_phy_read(p_instance_ctrl, GETHER_PHY_REG_MMD_ADDRESS_DATA);
}                                      /* End of gether_phy_mmd_read */

/***********************************************************************************************************************
 * Function Name: gether_phy_mmd_write
 * Description  : Write MMD register
 * Arguments    : p_instance_ctrl - Instance of Ehter PHY
 *                device_address  - Device address of the register
 *                reg_addr        - Address of the register
 *                data            - Data to write
 * Return Value : none
 ***********************************************************************************************************************/
static void gether_phy_mmd_write (ether_phy_instance_ctrl_t * p_instance_ctrl,
                                  uint32_t                    device_address,
                                  uint32_t                    reg_addr,
                                  uint32_t                    data)
{
    gether_phy_write(p_instance_ctrl,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL_ADDRESS | device_address);
    gether_phy_write(p_instance_ctrl, GETHER_PHY_REG_MMD_ADDRESS_DATA, reg_addr);
    gether_phy_write(p_instance_ctrl,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL,
                     GETHER_PHY_REG_MMD_ACCESS_CONTROL_DATA | device_address);
    gether_phy_write(p_instance_ctrl, GETHER_PHY_REG_MMD_ADDRESS_DATA, data);
}                                      /* End of gether_phy_mmd_write */

/***********************************************************************************************************************
 * Function Name: gether_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_instance_ctrl - instance of Ehter PHY
 * Return Value : none
 ***********************************************************************************************************************/
void gether_phy_targets_ksz9131rnxi_initialize (ether_phy_instance_ctrl_t * p_instance_ctrl)
{
    uint32_t reg;

    /* Enable RXC DLL delay */
    reg  = gether_phy_mmd_read(p_instance_ctrl, GETHER_PHY_DEV_RX_DDL_CONTROL, GETHER_PHY_REG_RX_DDL_CONTROL);
    reg &= (uint32_t) ~GETHER_PHY_REG_RX_DDL_CONTROL_BYPASS;
    gether_phy_mmd_write(p_instance_ctrl, GETHER_PHY_DEV_RX_DDL_CONTROL, GETHER_PHY_REG_RX_DDL_CONTROL, reg);

    /* Enable TXC DLL delay */
    reg  = gether_phy_mmd_read(p_instance_ctrl, GETHER_PHY_DEV_TX_DDL_CONTROL, GETHER_PHY_REG_TX_DDL_CONTROL);
    reg &= (uint32_t) ~GETHER_PHY_REG_TX_DDL_CONTROL_BYPASS;
    gether_phy_mmd_write(p_instance_ctrl, GETHER_PHY_DEV_TX_DDL_CONTROL, GETHER_PHY_REG_TX_DDL_CONTROL, reg);
}                                      /* End of function gether_phy_targets_initialize() */

/***********************************************************************************************************************
 * Function Name: gether_phy_targets_is_support_link_partner_ability
 * Description  : Check if the PHY-LSI connected Ethernet controller supports link ability
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : bool
 ***********************************************************************************************************************/
bool gether_phy_target_ksz9131rnxi_is_support_link_partner_ability (ether_phy_instance_ctrl_t * p_instance_ctrl,
                                                                    uint32_t                    line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    /* This PHY-LSI supports half and full duplex mode. */
    return true;
}                                      /* End of function ether_phy_targets_is_support_link_partner_ability() */

#endif /* GETHER_PHY_CFG_USE_PHY == GETHER_PHY_CFG_USE_PHY_KSZ9131RNXI */

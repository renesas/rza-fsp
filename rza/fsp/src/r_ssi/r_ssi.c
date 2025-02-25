/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ssi.h"
#include "r_ssi_cfg.h"
#if SSI_CFG_DMAC_ENABLE
 #include "r_dmac.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SSI_PRV_SSICR_REN_TEN_MASK         (3U)
#define SSI_PRV_SSICR_TEN_BIT              (2U)
#define SSI_PRV_SSICR_REN_BIT              (1U)

#define SSI_PRV_SSISR_EVENT_FLAG_MASK      (0x3E000000U)
#define SSI_PRV_SSICR_TX_RX_IRQ_MASK       (0x3C000000U)

#define SSI_PRV_SSIFCR_AUCKE_BIT           (31U)
#define SSI_PRV_SSIFCR_SSIRST_BIT          (16U)
#define SSI_PRV_SSIFCR_TIE_BIT             (3U)
#define SSI_PRV_SSIFCR_RIE_BIT             (2U)
#define SSI_PRV_SSIFCR_TFRST_RFRST_MASK    (3U)

#define SSI_PRV_SSICR_TUIEN_BIT            (29U)
#define SSI_PRV_SSICR_ROIEN_BIT            (26U)
#define SSI_PRV_SSICR_IIEN_BIT             (25U)
#define SSI_PRV_SSICR_CKS_BIT              (30U)
#define SSI_PRV_SSICR_SWL_BIT              (16U)
#define SSI_PRV_SSICR_DWL_BIT              (19U)
#define SSI_PRV_SSICR_MST_BIT              (14U)
#define SSI_PRV_SSICR_PDTA_BIT             (9U)
#define SSI_PRV_SSICR_CKDV_BIT             (4U)

#define SSI_PRV_SSISR_TUIRQ_BIT            (29U)
#define SSI_PRV_SSISR_ROIRQ_BIT            (26U)

#define SSI_PRV_SSIOFR_LRCONT_BIT          (8U)

#define SSI_PRV_TRANSFER_BLOCK_SIZE        (2U)

#define SSI_DMAC_FIFO_TRIGGER_SETTING      (0U)

/* SSIFSR has two flags that can be cleared (TDE and RDF).  The other fields in SSIFSR are read only or reserved. To
 * clear one of these flags, set the other to 1 to avoid clearing it, and write all other bits to 0. */
#define SSI_PRV_SSIFSR_RDF_CLEAR           (1U << 16)
#define SSI_PRV_SSIFSR_TDE_CLEAR           (1U)

/* I2S protocol always has 2 channels (left and right). */
#define SSI_PRV_I2S_CHANNELS               (2U)
#define SSI_PRV_BITS_PER_BYTE              (8U)

/* "SSI" in ASCII, used to determine if driver is open. */
#define SSI_PRV_OPEN                       (0x535349U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * i2s_prv_ns_callback)(i2s_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile i2s_prv_ns_callback)(i2s_callback_args_t * p_args);
#endif

/* SSI communication direction */
typedef enum e_ssi_dir
{
    SSI_DIR_RX    = 1U,                ///< Receive direction only
    SSI_DIR_TX    = 2U,                ///< Transmit direction only
    SSI_DIR_TX_RX = 3U,                ///< Transmit and receive direction
} ssi_dir_t;

/* Arguments are stored in a structure for transfer reset subroutine to avoid having more than 4 arguments. */
typedef struct e_ssi_prv_transfer_reset
{
    void const * p_data;
    uint32_t     bytes;
    void const * p_src;
    void       * p_dest;
} ssi_prv_transfer_reset_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/* ISRs */
void ssi_txi_isr(IRQn_Type const irq);
void ssi_rxi_isr(IRQn_Type const irq);
void ssi_int_isr(IRQn_Type const irq);

static void r_ssi_call_callback(ssi_instance_ctrl_t * p_ctrl, i2s_event_t event);

/* ISR subroutines */
static void r_ssi_tx_fifo_write(ssi_instance_ctrl_t * p_instance_ctrl, uint32_t stages_to_write);
static void r_ssi_rx_fifo_read(ssi_instance_ctrl_t * p_instance_ctrl, uint32_t stages_to_read);

/* FIFO subroutines */
static void r_ssi_fifo_write(ssi_instance_ctrl_t * p_instance_ctrl);
static void r_ssi_fifo_read(ssi_instance_ctrl_t * p_instance_ctrl);

/* Open subroutines */

static void r_ssi_interrupts_configure(ssi_instance_ctrl_t * const p_instance_ctrl, i2s_cfg_t const * const p_cfg);

#if SSI_CFG_DMAC_ENABLE
static fsp_err_t r_ssi_dependent_drivers_configure(R_SSI0_Type           * p_reg,
                                                   i2s_cfg_t const * const p_cfg,
                                                   transfer_size_t         fifo_access_size);

void ssi_tx_dmac_callback(ssi_instance_ctrl_t * p_ctrl);
void ssi_rx_dmac_callback(ssi_instance_ctrl_t * p_ctrl);

#endif

/* Stop subroutines */
static void r_ssi_stop_sub(ssi_instance_ctrl_t * const p_instance_ctrl);

/* Start subroutines */
static fsp_err_t r_ssi_start(ssi_instance_ctrl_t * const p_instance_ctrl, ssi_dir_t dir);

/* Read and write subroutines. */
fsp_err_t r_ssi_tx_load_fifo(ssi_instance_ctrl_t * const p_instance_ctrl, void const * const p_src,
                             uint32_t const bytes);
fsp_err_t r_ssi_rx_unload_fifo(ssi_instance_ctrl_t * const p_instance_ctrl, void * const p_dest, uint32_t const bytes);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** SSI Implementation of I2S interface.  */
const i2s_api_t g_i2s_on_ssi =
{
    .open        = R_SSI_Open,
    .stop        = R_SSI_Stop,
    .write       = R_SSI_Write,
    .read        = R_SSI_Read,
    .writeRead   = R_SSI_WriteRead,
    .mute        = R_SSI_Mute,
    .statusGet   = R_SSI_StatusGet,
    .close       = R_SSI_Close,
    .callbackSet = R_SSI_CallbackSet,
};

/*******************************************************************************************************************//**
 * @addtogroup SSI
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the SSI. Implements @ref i2s_api_t::open.
 *
 * This function sets this clock divisor and the configurations specified in i2s_cfg_t.  It also opens the timer and
 * transfer instances if they are provided.
 *
 * @retval FSP_SUCCESS                     Ready for I2S communication.
 * @retval FSP_ERR_ASSERTION               The pointer to p_ctrl or p_cfg is null.
 * @retval FSP_ERR_ALREADY_OPEN            The control block has already been opened.
 * @retval FSP_ERR_IP_CHANNEL_NOT_PRESENT  Channel number is not available on this device.
 * @return                                 See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                         possible return codes. This function calls:
 *                                             * @ref transfer_api_t::open
 **********************************************************************************************************************/
fsp_err_t R_SSI_Open (i2s_ctrl_t * const p_ctrl, i2s_cfg_t const * const p_cfg)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_callback);
    FSP_ASSERT(p_cfg->int_irq >= 0);
    if (I2S_MODE_MASTER == p_cfg->operating_mode)
    {
        FSP_ASSERT(NULL != p_cfg->p_extend);
    }

 #if SSI_CFG_DMAC_ENABLE
    if (NULL != p_cfg->p_transfer_rx)
    {
        dmac_extended_cfg_t * p_dmac_rx_cfg = (dmac_extended_cfg_t *) p_cfg->p_transfer_rx->p_cfg->p_extend;
        FSP_ASSERT(NULL != p_dmac_rx_cfg);
        FSP_ASSERT(p_cfg->rxi_irq == p_dmac_rx_cfg->activation_irq_number);
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        dmac_extended_cfg_t * p_dmac_tx_cfg = (dmac_extended_cfg_t *) p_cfg->p_transfer_tx->p_cfg->p_extend;
        FSP_ASSERT(NULL != p_dmac_tx_cfg);
        FSP_ASSERT(p_cfg->txi_irq == p_dmac_tx_cfg->activation_irq_number);
    }
 #endif

    FSP_ERROR_RETURN(SSI_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
    FSP_ERROR_RETURN(0U != ((1U << p_cfg->channel) & BSP_FEATURE_SSI_VALID_CHANNEL_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);
#endif

#if BSP_FEATURE_SSI_VALID_CHANNEL_MASK == 1
    uintptr_t base_address = (uintptr_t) R_SSI0;
#else

    /* Calculate base address for registers on this channel. */
    uintptr_t base_address = (uintptr_t) R_SSI0 + (p_cfg->channel * ((uintptr_t) R_SSI1 - (uintptr_t) R_SSI0));
#endif
    R_SSI0_Type * p_reg = (R_SSI0_Type *) base_address;

    /* Determine how to access the FIFO (1 byte, 2 byte, or 4 byte access). */
    transfer_size_t fifo_access_size = TRANSFER_SIZE_4_BYTE;
    if (I2S_PCM_WIDTH_8_BITS == p_cfg->pcm_width)
    {
        fifo_access_size = TRANSFER_SIZE_1_BYTE;
    }

    if (I2S_PCM_WIDTH_16_BITS == p_cfg->pcm_width)
    {
        fifo_access_size = TRANSFER_SIZE_2_BYTE;
    }

#if SSI_CFG_DMAC_ENABLE

    /* Configure dependent timer and transfer drivers. */
    fsp_err_t err = r_ssi_dependent_drivers_configure(p_reg, p_cfg, fifo_access_size);
    FSP_ERROR_RETURN((FSP_SUCCESS == err), err);
#endif

    /* Initialize the control structure. */
    p_instance_ctrl->p_reg            = p_reg;
    p_instance_ctrl->p_cfg            = p_cfg;
    p_instance_ctrl->fifo_access_size = fifo_access_size;

    /* Configure interrupts. */
    r_ssi_interrupts_configure(p_instance_ctrl, p_cfg);

    /* Calculate register settings. */

    /* Configure operating mode. */
    uint32_t ssifcr = (uint32_t) p_cfg->operating_mode << SSI_PRV_SSIFCR_AUCKE_BIT;
    uint32_t ssicr  = (uint32_t) p_cfg->operating_mode << SSI_PRV_SSICR_MST_BIT;

    /* Configure sample size, and word length. */
    ssicr |= (uint32_t) p_cfg->word_length << SSI_PRV_SSICR_SWL_BIT;
    ssicr |= (uint32_t) p_cfg->pcm_width << SSI_PRV_SSICR_DWL_BIT;
    if ((p_cfg->pcm_width > I2S_PCM_WIDTH_16_BITS) && (p_cfg->pcm_width < I2S_PCM_WIDTH_32_BITS))
    {
        /* Right justify data for 18-bit, 20-bit, 22-bit, or 24-bit samples. This setting is prohibited for 8-bit,
         * 16-bit, and 32-bit samples  */
        ssicr |= (1U << SSI_PRV_SSICR_PDTA_BIT);
    }

    /* Configure audio clock and WS continue in master mode only. */
    uint32_t             ssiofr   = 0U;
    ssi_extended_cfg_t * p_extend = (ssi_extended_cfg_t *) p_cfg->p_extend;

    if (I2S_MODE_MASTER == p_cfg->operating_mode)
    {
        ssicr |= (uint32_t) p_extend->bit_clock_div << SSI_PRV_SSICR_CKDV_BIT;
        ssicr |= (uint32_t) p_extend->audio_clock << SSI_PRV_SSICR_CKS_BIT;

        if (I2S_WS_CONTINUE_ON == p_cfg->ws_continue)
        {
            ssiofr |= (1U << SSI_PRV_SSIOFR_LRCONT_BIT);
        }
    }

    /* Set SSI receive FIFO watermark to exactly the DMAC block size so the DMAC triggers as soon as there is
     * a block of data in the FIFO. */
    uint32_t rx_fifo_setting = SSI_PRV_TRANSFER_BLOCK_SIZE - 1U;

    /* Set SSI transmit FIFO watermark to trigger when 1/2 of the FIFO is empty so that read and write are less
     * likely to trigger at the same time. */
    uint32_t tx_fifo_setting = (BSP_FEATURE_SSI_FIFO_NUM_STAGES / 2U) - 1U;

#if SSI_CFG_DMAC_ENABLE
    if (NULL != p_cfg->p_transfer_rx)
    {
        rx_fifo_setting = SSI_DMAC_FIFO_TRIGGER_SETTING;
    }

    if (NULL != p_cfg->p_transfer_tx)
    {
        tx_fifo_setting = SSI_DMAC_FIFO_TRIGGER_SETTING;
    }
#endif

    uint32_t ssiscr = (tx_fifo_setting << R_SSI_SSISCR_TDES_Pos) | rx_fifo_setting;

    /* Initialize the SSI following the procedure in "Procedure to start communication (CPU operation
     * procedure)" of the User's Manual. This function follows this procedure except for enabling
     * interrupts and enabling communication, which are done before communication begins. */

    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_context         = p_cfg->p_context;
    p_instance_ctrl->p_callback_memory = NULL;

    /* Enable PCLK to SSI. */
    R_BSP_MODULE_START(FSP_IP_SSI, p_cfg->channel);

    /* Configure master/slave mode and associated clock settings for master mode. */
    p_instance_ctrl->p_reg->SSICR = ssicr;

    /* Reset SSI and set operating mode. Set SSIRST, then clear it and wait for it to clear. This operation resets
     * all interrupt flags in SSISR and empties the FIFOs. */
    p_instance_ctrl->p_reg->SSIFCR = ssifcr | (1U << SSI_PRV_SSIFCR_SSIRST_BIT);
    p_instance_ctrl->p_reg->SSIFCR = ssifcr;

    /* Wait for SSIRST to clear before continuing.  Reference SSIRST in section "FIFO Control Register (SSIFCR)"
     * of the User's Manual. */
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->SSIFCR, ssifcr);

    p_instance_ctrl->p_reg->SSISCR = ssiscr;
    p_instance_ctrl->p_reg->SSIOFR = ssiofr;

    /* Initialization complete. */
    p_instance_ctrl->open = SSI_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes data buffer to SSI. Implements @ref i2s_api_t::write.
 *
 * This function resets the transfer if the transfer interface is used, or writes the length of data that fits in the
 * FIFO then stores the remaining write buffer in the control block to be written in the ISR.
 *
 * Write() cannot be called if another write(), read() or writeRead() operation is in progress.  Write can be called
 * when the SSI is idle, or after the I2S_EVENT_TX_EMPTY event.
 *
 * @retval FSP_SUCCESS                 Write initiated successfully.
 * @retval FSP_ERR_ASSERTION           The pointer to p_ctrl or p_src was null, or bytes requested was 0.
 * @retval FSP_ERR_IN_USE              Another transfer is in progress, data was not written.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_UNDERFLOW           A transmit underflow error is pending. Wait for the SSI to go idle before
 *                                     resuming communication.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::reset
 **********************************************************************************************************************/
fsp_err_t R_SSI_Write (i2s_ctrl_t * const p_ctrl, void const * const p_src, uint32_t const bytes)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_src);

    /* bytes must be a non-zero multiple of the FIFO access size multiplied by 2 (for the left and right channel). */
    FSP_ASSERT(bytes > 0U);
#endif

    /* If a transfer instance is provided for write, reset the transfer. Otherwise store data to transmit in the
     * transmit interrupt. */
    fsp_err_t err = r_ssi_tx_load_fifo(p_instance_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If a transmit underflow is pending, return an error.  This could happen if the application is in an interrupt
     * context with a priority greater than or equal to the idle/error interrupt priority and does not reload the
     * transmit FIFO before it underflows. */
    FSP_ERROR_RETURN(0U == p_instance_ctrl->p_reg->SSISR_b.TUIRQ, FSP_ERR_UNDERFLOW);

    /* Make sure transmission is enabled. */
    err = r_ssi_start(p_instance_ctrl, SSI_DIR_TX);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads data into provided buffer. Implements @ref i2s_api_t::read.
 *
 * This function resets the transfer if the transfer interface is used, or reads the length of data available in the
 * FIFO then stores the remaining read buffer in the control block to be filled in the ISR.
 *
 * Read() cannot be called if another write(), read() or writeRead() operation is in progress.  Read can be called
 * when the SSI is idle, or after the I2S_EVENT_RX_FULL event.
 *
 * @retval FSP_SUCCESS                 Read initiated successfully.
 * @retval FSP_ERR_IN_USE              Peripheral is in the wrong mode or not idle.
 * @retval FSP_ERR_ASSERTION           The pointer to p_ctrl or p_dest was null, or bytes requested was 0.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_OVERFLOW            A receive overflow error is pending. Wait for the SSI to go idle before
 *                                     resuming communication.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::reset
 **********************************************************************************************************************/
fsp_err_t R_SSI_Read (i2s_ctrl_t * const p_ctrl, void * const p_dest, uint32_t const bytes)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_dest);

    /* bytes must be a non-zero multiple of the FIFO access size multiplied by 2 (for the left and right channel). */
    FSP_ASSERT(bytes > 0U);
#endif

    /* If a transfer instance is provided for read, reset the transfer. Otherwise store data to receive in the receive
     * interrupt. */
    fsp_err_t err = r_ssi_rx_unload_fifo(p_instance_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If a receive overflow is pending, return an error.  This could happen if the application is in an interrupt
     * context with a priority greater than or equal to the idle/error interrupt priority and does not read from the
     * receive FIFO before it overflows. */
    FSP_ERROR_RETURN(0U == p_instance_ctrl->p_reg->SSISR_b.ROIRQ, FSP_ERR_OVERFLOW);

    /* Make sure reception is enabled. */
    err = r_ssi_start(p_instance_ctrl, SSI_DIR_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes from source buffer and reads data into destination buffer. Implements @ref i2s_api_t::writeRead.
 *
 * This function calls R_SSI_Write and R_SSI_Read.
 *
 * writeRead() cannot be called if another write(), read() or writeRead() operation is in progress.  writeRead() can be
 * called when the SSI is idle, or after the I2S_EVENT_RX_FULL event.
 *
 * @retval FSP_SUCCESS                 Write and read initiated successfully.
 * @retval FSP_ERR_IN_USE              Peripheral is in the wrong mode or not idle.
 * @retval FSP_ERR_ASSERTION           An input parameter was invalid.
 * @retval FSP_ERR_NOT_OPEN            The channel is not opened.
 * @retval FSP_ERR_UNDERFLOW           A transmit underflow error is pending. Wait for the SSI to go idle before
 *                                     resuming communication.
 * @retval FSP_ERR_OVERFLOW            A receive overflow error is pending. Wait for the SSI to go idle before
 *                                     resuming communication.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::reset
 **********************************************************************************************************************/
fsp_err_t R_SSI_WriteRead (i2s_ctrl_t * const p_ctrl,
                           void const * const p_src,
                           void * const       p_dest,
                           uint32_t const     bytes)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* bytes must be a non-zero multiple of the FIFO access size multiplied by 2 (for the left and right channel). */
    FSP_ASSERT(bytes > 0U);
#endif

    /* If a transfer instance is provided for write, reset the transfer. Reset the transmit FIFO first since the
     * transmit FIFO will underflow before the receive FIFO overflows during full duplex communication. */
    fsp_err_t err = r_ssi_tx_load_fifo(p_instance_ctrl, p_src, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If a transfer instance is provided for read, reset the transfer. */
    err = r_ssi_rx_unload_fifo(p_instance_ctrl, p_dest, bytes);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* If a transmit underflow or receive overflow is pending, return an error.  This could happen if the application
     * is in an interrupt context with a priority greater than or equal to the idle/error interrupt priority and does
     * not reload the FIFOs before they underflow/overflow. */
    uint32_t ssisr = p_instance_ctrl->p_reg->SSISR;
    FSP_ERROR_RETURN(0U == (ssisr & (1U << SSI_PRV_SSISR_TUIRQ_BIT)), FSP_ERR_UNDERFLOW);
    FSP_ERROR_RETURN(0U == (ssisr & (1U << SSI_PRV_SSISR_ROIRQ_BIT)), FSP_ERR_OVERFLOW);

    /* Make sure transmission and reception are enabled. */
    err = r_ssi_start(p_instance_ctrl, SSI_DIR_TX_RX);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Stops SSI. Implements @ref i2s_api_t::stop.
 *
 * This function disables both transmission and reception, and disables any transfer instances used.
 *
 * The SSI will stop on the next frame boundary.  Do not restart SSI until it is idle.
 *
 * @retval FSP_SUCCESS           I2S communication stop request issued.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 * @return                       See @ref RENESAS_ERROR_CODES or lower level drivers for other possible return codes.
 **********************************************************************************************************************/
fsp_err_t R_SSI_Stop (i2s_ctrl_t * const p_ctrl)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Stop is complete after an I2S_EVENT_IDLE interrupt. */
    r_ssi_stop_sub(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Mutes SSI on the next frame boundary. Implements @ref i2s_api_t::mute.
 *
 * Data is still written while mute is enabled, but the transmit line outputs zeros.
 *
 * @retval FSP_SUCCESS           Transmission is muted.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_SSI_Mute (i2s_ctrl_t * const p_ctrl, i2s_mute_t const mute_enable)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->p_reg->SSICR_b.MUEN = mute_enable;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets SSI status and stores it in provided pointer p_status. Implements @ref i2s_api_t::statusGet.
 *
 * @retval FSP_SUCCESS           Information stored successfully.
 * @retval FSP_ERR_ASSERTION     The p_instance_ctrl or p_status parameter was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_SSI_StatusGet (i2s_ctrl_t * const p_ctrl, i2s_status_t * const p_status)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;

#if SSI_CFG_PARAM_CHECKING_ENABLE

    /* Make sure parameters are valid. */
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_status->state = (i2s_state_t) p_instance_ctrl->p_reg->SSISR_b.IIRQ;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes SSI. Implements @ref i2s_api_t::close.
 *
 * This function powers down the SSI and closes the lower level timer and transfer drivers if they are used.
 *
 * @retval FSP_SUCCESS           Device closed successfully.
 * @retval FSP_ERR_ASSERTION     The pointer to p_ctrl was null.
 * @retval FSP_ERR_NOT_OPEN      The channel is not opened.
 **********************************************************************************************************************/
fsp_err_t R_SSI_Close (i2s_ctrl_t * const p_ctrl)
{
    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) p_ctrl;
#if SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_instance_ctrl->open = 0U;

    /* Stop SSI. */
    p_instance_ctrl->p_reg->SSICR  = 0U;
    p_instance_ctrl->p_reg->SSIFCR = 0U;

    /* Disable interrupts. */
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->int_irq);
    if (p_instance_ctrl->p_cfg->rxi_irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->rxi_irq);
    }

    if (p_instance_ctrl->p_cfg->txi_irq >= 0)
    {
        R_BSP_IrqDisable(p_instance_ctrl->p_cfg->txi_irq);
    }

#if SSI_CFG_DMAC_ENABLE

    /* If transfer is used, disable transfer when stop is requested. */
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
    {
        (void) p_instance_ctrl->p_cfg->p_transfer_rx->p_api->close(p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_instance_ctrl->p_cfg->p_transfer_tx)
    {
        (void) p_instance_ctrl->p_cfg->p_transfer_tx->p_api->close(p_instance_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    /* Remove power to the channel. */
    R_BSP_MODULE_STOP(FSP_IP_SSI, p_instance_ctrl->p_cfg->channel);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 * Implements i2s_api_t::callbackSet
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_SSI_CallbackSet (i2s_ctrl_t * const          p_api_ctrl,
                             void (                    * p_callback)(i2s_callback_args_t *),
                             void const * const          p_context,
                             i2s_callback_args_t * const p_callback_memory)
{
    ssi_instance_ctrl_t * p_ctrl = (ssi_instance_ctrl_t *) p_api_ctrl;

#if (SSI_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SSI_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SSI_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    i2s_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                      CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(i2s_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup R_SSI)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * For each interrupt, if it is enabled, sets the interrupt priority based on user configuration and stores the control
 * block so it can be accessed in the ISR.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @param[in] p_cfg                    Pointer to the configuration structure.
 **********************************************************************************************************************/
static void r_ssi_interrupts_configure (ssi_instance_ctrl_t * const p_instance_ctrl, i2s_cfg_t const * const p_cfg)
{
    /* Set interrupt priority based on user configuration of interrupt number for FSP_SIGNAL_SSI_INT signal */
    R_BSP_IrqCfgEnable(p_cfg->int_irq, p_cfg->idle_err_ipl, p_instance_ctrl);

    /* Set interrupt priority based on user configuration of interrupt number for FSP_SIGNAL_SSI_RXI
     * or FSP_SIGNAL_SSI_TXI_RXI signals */
    if (p_cfg->rxi_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->rxi_irq, p_cfg->rxi_ipl, p_instance_ctrl);
    }

    /* Set interrupt priority based on user configuration of interrupt number for FSP_SIGNAL_SSI_TXI
     * or FSP_SIGNAL_SSI_TXI_RXI signals */
    if (p_cfg->txi_irq >= 0)
    {
        R_BSP_IrqCfgEnable(p_cfg->txi_irq, p_cfg->txi_ipl, p_instance_ctrl);
    }
}

#if SSI_CFG_DMAC_ENABLE

/*******************************************************************************************************************//**
 * Configures any dependent drivers selected by the user, including transfer and timer drivers.
 *
 * @param[in] p_reg                    Pointer to SSI base register address for this channel.
 * @param[in] p_cfg                    Pointer to the configuration structure.
 *
 * @retval FSP_SUCCESS                 Dependent drivers configured successfully.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::open
 **********************************************************************************************************************/
static fsp_err_t r_ssi_dependent_drivers_configure (R_SSI0_Type           * p_reg,
                                                    i2s_cfg_t const * const p_cfg,
                                                    transfer_size_t         fifo_access_size)
{
    /* Prepare transfer configuration. */
    fsp_err_t err_transfer_tx = FSP_SUCCESS;
    fsp_err_t err_transfer_rx = FSP_SUCCESS;

    /* If a transfer instance is provided for write, open the transfer instance. */
    if (NULL != p_cfg->p_transfer_tx)
    {
        dmac_extended_info_t * p_extend_info =
            (dmac_extended_info_t *) p_cfg->p_transfer_tx->p_cfg->p_info->p_extend_info;

        if (fifo_access_size == TRANSFER_SIZE_1_BYTE)
        {
            p_extend_info->src_size  = DMAC_TRANSFER_SIZE_1_BYTE;
            p_extend_info->dest_size = DMAC_TRANSFER_SIZE_1_BYTE;
            p_cfg->p_transfer_tx->p_cfg->p_info->p_dest = (void *) &(p_reg->SSIFTDR_byte.LL);
        }
        else if (fifo_access_size == TRANSFER_SIZE_2_BYTE)
        {
            p_extend_info->src_size  = DMAC_TRANSFER_SIZE_2_BYTE;
            p_extend_info->dest_size = DMAC_TRANSFER_SIZE_2_BYTE;
            p_cfg->p_transfer_tx->p_cfg->p_info->p_dest = (void *) &(p_reg->SSIFTDR_hword.L);
        }
        else
        {
            p_extend_info->src_size  = DMAC_TRANSFER_SIZE_4_BYTE;
            p_extend_info->dest_size = DMAC_TRANSFER_SIZE_4_BYTE;
            p_cfg->p_transfer_tx->p_cfg->p_info->p_dest = (void *) &(p_reg->SSIFTDR);
        }

        err_transfer_tx = p_cfg->p_transfer_tx->p_api->open(p_cfg->p_transfer_tx->p_ctrl, p_cfg->p_transfer_tx->p_cfg);
    }

 #if  SSI_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN((FSP_SUCCESS == err_transfer_tx), err_transfer_tx);
 #else
    FSP_PARAMETER_NOT_USED(err_transfer_tx);
 #endif

    /* If a transfer instance is provided for read, open the transfer instance. */
    if (NULL != p_cfg->p_transfer_rx)
    {
        dmac_extended_info_t * p_extend_info =
            (dmac_extended_info_t *) p_cfg->p_transfer_rx->p_cfg->p_info->p_extend_info;

        if (fifo_access_size == TRANSFER_SIZE_1_BYTE)
        {
            p_extend_info->src_size  = DMAC_TRANSFER_SIZE_1_BYTE;
            p_extend_info->dest_size = DMAC_TRANSFER_SIZE_1_BYTE;
            p_cfg->p_transfer_rx->p_cfg->p_info->p_src = (void *) &(p_reg->SSIFRDR_byte.LL);
        }
        else if (fifo_access_size == TRANSFER_SIZE_2_BYTE)
        {
            p_extend_info->src_size  = DMAC_TRANSFER_SIZE_2_BYTE;
            p_extend_info->dest_size = DMAC_TRANSFER_SIZE_2_BYTE;
            p_cfg->p_transfer_rx->p_cfg->p_info->p_src = (void *) &(p_reg->SSIFRDR_hword.L);
        }
        else
        {
            p_extend_info->src_size  = DMAC_TRANSFER_SIZE_4_BYTE;
            p_extend_info->dest_size = DMAC_TRANSFER_SIZE_4_BYTE;
            p_cfg->p_transfer_rx->p_cfg->p_info->p_src = (void *) &(p_reg->SSIFRDR);
        }

        err_transfer_rx = p_cfg->p_transfer_rx->p_api->open(p_cfg->p_transfer_rx->p_ctrl, p_cfg->p_transfer_rx->p_cfg);
    }

 #if  SSI_CFG_PARAM_CHECKING_ENABLE

    /* If there was an error opening the receive transfer, close the transmit transfer before returning. */
    if (FSP_SUCCESS != err_transfer_rx)
    {
        if (NULL != p_cfg->p_transfer_tx)
        {
            p_cfg->p_transfer_tx->p_api->close(p_cfg->p_transfer_tx->p_ctrl);
        }
    }

    FSP_ERROR_RETURN((FSP_SUCCESS == err_transfer_rx), err_transfer_rx);
 #else
    FSP_PARAMETER_NOT_USED(err_transfer_rx);
 #endif

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Disables SSI transmission and reception.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 **********************************************************************************************************************/
static void r_ssi_stop_sub (ssi_instance_ctrl_t * const p_instance_ctrl)
{
    /* Stop communication following the procedure from "Procedure to halt communication (CPU operation
     * procedure)" in the User's Manual. */

    /* Disable transmission and reception and associated interrupts. Enable idle interrupt. */
    uint32_t ssicr = p_instance_ctrl->p_reg->SSICR;
    ssicr &= ~SSI_PRV_SSICR_REN_TEN_MASK;
    ssicr &= ~SSI_PRV_SSICR_TX_RX_IRQ_MASK;
    ssicr |= (1U << SSI_PRV_SSICR_IIEN_BIT);

    p_instance_ctrl->p_reg->SSICR = ssicr;

    uint32_t ssifcr = p_instance_ctrl->p_reg->SSIFCR;
    ssifcr &= ~(uint32_t) (R_SSI_SSIFCR_TIE_Msk | R_SSI_SSIFCR_RIE_Msk);
    p_instance_ctrl->p_reg->SSIFCR = ssifcr;

#if SSI_CFG_DMAC_ENABLE

    /* If transfer is used, disable transfer when stop is requested. */
    if (NULL != p_instance_ctrl->p_cfg->p_transfer_rx)
    {
        (void) p_instance_ctrl->p_cfg->p_transfer_rx->p_api->disable(p_instance_ctrl->p_cfg->p_transfer_rx->p_ctrl);
    }

    if (NULL != p_instance_ctrl->p_cfg->p_transfer_tx)
    {
        (void) p_instance_ctrl->p_cfg->p_transfer_tx->p_api->disable(p_instance_ctrl->p_cfg->p_transfer_tx->p_ctrl);
    }
#endif

    /* Disable interrupt output. Clear RIE and TIE by clearing all bits except AUCKE, which is set or cleared depending
     * on the mode. All other bits can be set to 0. */
    p_instance_ctrl->p_reg->SSIFCR = (uint32_t) p_instance_ctrl->p_cfg->operating_mode << SSI_PRV_SSIFCR_AUCKE_BIT;

    /* Clear control structure data. */
    p_instance_ctrl->p_tx_src        = NULL;
    p_instance_ctrl->tx_src_samples  = 0U;
    p_instance_ctrl->p_rx_dest       = NULL;
    p_instance_ctrl->rx_dest_samples = 0U;
}

/*******************************************************************************************************************//**
 * Configures the transmit FIFO to be loaded by DMAC or stores the source data to be loaded into the FIFO in the transmit
 * interrupt.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @param[in] p_src                    Pointer to the source buffer.
 * @param[in] bytes                    Length of source buffer.
 *
 * @retval FSP_SUCCESS                 Transmit FIFO successfully loaded.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::reset
 **********************************************************************************************************************/
fsp_err_t r_ssi_tx_load_fifo (ssi_instance_ctrl_t * const p_instance_ctrl,
                              void const * const          p_src,
                              uint32_t const              bytes)
{
    void   * p_data  = (void *) p_src;
    uint32_t samples = bytes >> p_instance_ctrl->fifo_access_size;

#if SSI_CFG_DMAC_ENABLE

    /* By default, bytes are written in the ISR. */

    /* If a transfer instance is provided, reset the transfer. */
    transfer_instance_t const * const p_transfer = p_instance_ctrl->p_cfg->p_transfer_tx;

    if (NULL != p_transfer)
    {
        /* We have already verified that the 'samples' is a non-zero multiple of 2 in parameter checking. */
        p_transfer->p_cfg->p_info->p_src  = p_src;
        p_transfer->p_cfg->p_info->length = (uint16_t) bytes;
        fsp_err_t err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_transfer->p_cfg->p_info);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        p_data  = NULL;
        samples = 0U;
    }
#endif

    p_instance_ctrl->p_tx_src       = p_data;
    p_instance_ctrl->tx_src_samples = samples;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures the receive FIFO to be unloaded by DMAC or stores the destination buffer for data to be unloaded in the
 * receive interrupt.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @param[in] p_dest                   Pointer to the destination buffer.
 * @param[in] bytes                    Length of destination buffer.
 *
 * @retval FSP_SUCCESS                 Receive FIFO successfully unloaded.
 * @return                             See @ref RENESAS_ERROR_CODES or functions called by this function for other
 *                                     possible return codes. This function calls:
 *                                         * @ref transfer_api_t::reset
 **********************************************************************************************************************/
fsp_err_t r_ssi_rx_unload_fifo (ssi_instance_ctrl_t * const p_instance_ctrl, void * const p_dest, uint32_t const bytes)
{
    void   * p_data  = p_dest;
    uint32_t samples = bytes >> p_instance_ctrl->fifo_access_size;
#if SSI_CFG_DMAC_ENABLE

    /* By default, bytes are written in the ISR. */

    /* If a transfer instance is provided for reception, reset the transfer. */
    transfer_instance_t const * const p_transfer = p_instance_ctrl->p_cfg->p_transfer_rx;
    if (NULL != p_transfer)
    {
        /* Always read at least one sample from the receive interrupt. This ensures that the DMAC transfer will be over
         * by the time a transmit underflow occurs during R_SSI_WriteRead processing. This is important so the receive
         * buffer can be flushed in the transmit underflow error processing. Without this, the last frame (two samples)
         * could be lost during R_SSI_WriteRead. */
        uint32_t transfer_blocks = (samples / SSI_PRV_TRANSFER_BLOCK_SIZE) - 1U;

        if (transfer_blocks > 0)
        {
            p_transfer->p_cfg->p_info->p_dest = p_dest;
            p_transfer->p_cfg->p_info->length = (uint16_t) bytes;
            fsp_err_t err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_transfer->p_cfg->p_info);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            p_data  = NULL;
            samples = 0U;
        }
    }
#endif

    p_instance_ctrl->p_rx_dest       = p_data;
    p_instance_ctrl->rx_dest_samples = samples;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enables SSI transmission and/or reception.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @param[in] dir                      Start transmit, receive, or both.
 *
 * @retval FSP_SUCCESS                 Ready for I2S transmission.
 * @retval FSP_ERR_IN_USE              Peripheral is in the wrong mode or not idle.
 **********************************************************************************************************************/
static fsp_err_t r_ssi_start (ssi_instance_ctrl_t * const p_instance_ctrl, ssi_dir_t dir)
{
    uint32_t ssicr                 = p_instance_ctrl->p_reg->SSICR;
    uint32_t current_ssicr_ren_ten = ssicr & SSI_PRV_SSICR_REN_TEN_MASK;
    uint32_t desired_ssicr_ren_ten = (uint32_t) dir;

    /* If the peripheral is not already in the correct mode, attempt to start it. */
    if (desired_ssicr_ren_ten != (current_ssicr_ren_ten & desired_ssicr_ren_ten))
    {
        /* If the peripheral is in the wrong mode or not idle, return an error. The SSI must be idle before setting
         * REN or TEN. Reference "Switching transfer modes" in the User's Manual. */
        FSP_ERROR_RETURN(0U == current_ssicr_ren_ten, FSP_ERR_IN_USE);
        FSP_ERROR_RETURN(1U == p_instance_ctrl->p_reg->SSISR_b.IIRQ, FSP_ERR_IN_USE);

        /* Reset SSI FIFOs. Set TFRST and RFRST, then clear them and wait for them to clear. This operation empties
         * the FIFOs. */
        uint32_t ssifcr = p_instance_ctrl->p_reg->SSIFCR;
        p_instance_ctrl->p_reg->SSIFCR = ssifcr | SSI_PRV_SSIFCR_TFRST_RFRST_MASK;
        p_instance_ctrl->p_reg->SSIFCR = ssifcr;

        /* Wait for TFRST and RFRST to clear before continuing.  Reference TFRST and RFRST in section "FIFO
         * Control Register (SSIFCR)" of the User's Manual. */
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg->SSIFCR, ssifcr);

        /* If starting transmission, enable transmit interrupts. */
        ssicr |= desired_ssicr_ren_ten;
        if ((desired_ssicr_ren_ten & SSI_PRV_SSICR_TEN_BIT) > 0U)
        {
            /* Setting to start SSI Tx */
            ssicr  |= (1U << SSI_PRV_SSICR_TUIEN_BIT);
            ssifcr |= (1U << SSI_PRV_SSIFCR_TIE_BIT);
        }

        /* If starting reception, enable receive interrupts. */
        if ((desired_ssicr_ren_ten & SSI_PRV_SSICR_REN_BIT) > 0U)
        {
            /* Setting to start SSI Rx */
            ssicr  |= (1U << SSI_PRV_SSICR_ROIEN_BIT);
            ssifcr |= (1U << SSI_PRV_SSIFCR_RIE_BIT);
        }

        /* Enabling communication clears related error flags in SSISR. */
        p_instance_ctrl->p_reg->SSIFCR = ssifcr;
        p_instance_ctrl->p_reg->SSICR  = ssicr;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Writes data to FIFO.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 *
 * @return The number of stages written
 **********************************************************************************************************************/
static void r_ssi_fifo_write (ssi_instance_ctrl_t * p_instance_ctrl)
{
    /* Calculate the number of words to write, limited by the space available in the FIFO. */
    uint32_t stages_to_write = p_instance_ctrl->tx_src_samples;

    /* Calculate the number of free spaces in transmit FIFO. */
    uint32_t fifo_free_stages = BSP_FEATURE_SSI_FIFO_NUM_STAGES - p_instance_ctrl->p_reg->SSIFSR_b.TDC;
    if (stages_to_write > fifo_free_stages)
    {
        stages_to_write = fifo_free_stages;
    }

    r_ssi_tx_fifo_write(p_instance_ctrl, stages_to_write);
    uint32_t bytes_written = stages_to_write << p_instance_ctrl->fifo_access_size;
    p_instance_ctrl->tx_src_samples -= stages_to_write;
    p_instance_ctrl->p_tx_src        = (void *) ((uintptr_t) p_instance_ctrl->p_tx_src + bytes_written);

    /* If transmission is complete, clear transmit buffer to NULL. */
    if (0U == p_instance_ctrl->tx_src_samples)
    {
        p_instance_ctrl->p_tx_src = NULL;
    }
}

/*******************************************************************************************************************//**
 *  Reads data from FIFO.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 **********************************************************************************************************************/
static void r_ssi_fifo_read (ssi_instance_ctrl_t * p_instance_ctrl)
{
    /* Calculate the number of available bytes of data in receive FIFO. */
    uint32_t fifo_filled_stages = p_instance_ctrl->p_reg->SSIFSR_b.RDC;

    /* Calculate the number of FIFO stages requested to read. */
    uint32_t stages_to_read = 0U;
    stages_to_read = p_instance_ctrl->rx_dest_samples;
    if (stages_to_read > fifo_filled_stages)
    {
        stages_to_read = fifo_filled_stages;
    }

    r_ssi_rx_fifo_read(p_instance_ctrl, stages_to_read);
    uint32_t bytes_read = stages_to_read << p_instance_ctrl->fifo_access_size;
    p_instance_ctrl->rx_dest_samples -= stages_to_read;
    p_instance_ctrl->p_rx_dest        = (void *) ((uintptr_t) p_instance_ctrl->p_rx_dest + bytes_read);

    /* If reception is complete, clear receive buffer to NULL. */
    if (0U == p_instance_ctrl->rx_dest_samples)
    {
        p_instance_ctrl->p_rx_dest = NULL;
    }
}

/*******************************************************************************************************************//**
 * Writes data to the transmit FIFO based on the FIFO access size.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @param[in] stages_to_write          Number of times to write to the FIFO.
 **********************************************************************************************************************/
static void r_ssi_tx_fifo_write (ssi_instance_ctrl_t * p_instance_ctrl, uint32_t stages_to_write)
{
    if (TRANSFER_SIZE_4_BYTE == p_instance_ctrl->fifo_access_size)
    {
        uint32_t * p_src32 = (uint32_t *) p_instance_ctrl->p_tx_src;
        for (uint32_t i = 0; i < stages_to_write; i++)
        {
            p_instance_ctrl->p_reg->SSIFTDR = *p_src32;
            p_src32++;
        }
    }

    if (TRANSFER_SIZE_2_BYTE == p_instance_ctrl->fifo_access_size)
    {
        uint16_t * p_src16 = (uint16_t *) p_instance_ctrl->p_tx_src;
        for (uint32_t i = 0; i < stages_to_write; i++)
        {
            p_instance_ctrl->p_reg->SSIFTDR_hword.L = *p_src16;
            p_src16++;
        }
    }

    if (TRANSFER_SIZE_1_BYTE == p_instance_ctrl->fifo_access_size)
    {
        uint8_t * p_src8 = (uint8_t *) p_instance_ctrl->p_tx_src;
        for (uint32_t i = 0; i < stages_to_write; i++)
        {
            p_instance_ctrl->p_reg->SSIFTDR_byte.LL = *p_src8;
            p_src8++;
        }
    }
}

/*******************************************************************************************************************//**
 * Reads data from the receive FIFO based on the FIFO access size.
 *
 * @param[in] p_instance_ctrl          Pointer to the control block.
 * @param[in] stages_to_read           Number of times to read from the FIFO.
 **********************************************************************************************************************/
static void r_ssi_rx_fifo_read (ssi_instance_ctrl_t * p_instance_ctrl, uint32_t stages_to_read)
{
    if (TRANSFER_SIZE_4_BYTE == p_instance_ctrl->fifo_access_size)
    {
        uint32_t * p_dest32 = (uint32_t *) p_instance_ctrl->p_rx_dest;
        for (uint32_t i = 0; i < stages_to_read; i++)
        {
            *p_dest32 = p_instance_ctrl->p_reg->SSIFRDR;
            p_dest32++;
        }
    }

    if (TRANSFER_SIZE_2_BYTE == p_instance_ctrl->fifo_access_size)
    {
        uint16_t * p_dest16 = (uint16_t *) p_instance_ctrl->p_rx_dest;
        for (uint32_t i = 0; i < stages_to_read; i++)
        {
            *p_dest16 = p_instance_ctrl->p_reg->SSIFRDR_hword.L;
            p_dest16++;
        }
    }

    if (TRANSFER_SIZE_1_BYTE == p_instance_ctrl->fifo_access_size)
    {
        uint8_t * p_dest8 = (uint8_t *) p_instance_ctrl->p_rx_dest;
        for (uint32_t i = 0; i < stages_to_read; i++)
        {
            *p_dest8 = p_instance_ctrl->p_reg->SSIFRDR_byte.LL;
            p_dest8++;
        }
    }
}

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_ctrl     Pointer to I2S instance control block
 * @param[in]     event      Event code
 **********************************************************************************************************************/
static void r_ssi_call_callback (ssi_instance_ctrl_t * p_ctrl, i2s_event_t event)
{
    i2s_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    i2s_callback_args_t * p_args = p_ctrl->p_callback_memory;
    if (NULL == p_args)
    {
        /* Store on stack */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    p_args->event     = event;
    p_args->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_ctrl->p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_ctrl->p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        i2s_prv_ns_callback p_callback = (i2s_prv_ns_callback) (p_ctrl->p_callback);
        p_callback(p_args);
    }

#else

    /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
    p_ctrl->p_callback(p_args);
#endif
    if (NULL != p_ctrl->p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_ctrl->p_callback_memory = args;
    }
}

/*******************************************************************************************************************//**
 * Transmit ISR. Calls callback when transmission is complete.  Fills FIFO if transfer interface is not used.
 **********************************************************************************************************************/
void ssi_txi_isr (IRQn_Type const irq)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    if (NULL != p_instance_ctrl->p_tx_src)
    {
        /* If transfer is not used, write data. */
        r_ssi_fifo_write(p_instance_ctrl);
    }

    /* If there are more samples to write to the FIFO or the FIFO is above the watermark, don't call the callback. */
    if ((p_instance_ctrl->tx_src_samples == 0) &&
        (p_instance_ctrl->p_reg->SSIFSR_b.TDC > (BSP_FEATURE_SSI_FIFO_NUM_STAGES / 2U)))
    {
        r_ssi_call_callback(p_instance_ctrl, I2S_EVENT_TX_EMPTY);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Receive ISR.  Calls callback when reception is complete.  Empties FIFO if transfer interface is not used.
 **********************************************************************************************************************/
void ssi_rxi_isr (IRQn_Type const irq)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    bool call_callback = true;

    if (NULL != p_instance_ctrl->p_rx_dest)
    {
        /* If transfer is not used, read data into the destination buffer. */
        r_ssi_fifo_read(p_instance_ctrl);

        /* If there is more space in the buffer, don't call the callback. */
        if (p_instance_ctrl->rx_dest_samples > 0U)
        {
            call_callback = false;
        }
    }

    if (call_callback)
    {
        r_ssi_call_callback(p_instance_ctrl, I2S_EVENT_RX_FULL);
    }

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Error and idle ISR.
 *
 * Handles transmit underflow errors and calls callback when idle interrupt occurs.
 **********************************************************************************************************************/
void ssi_int_isr (IRQn_Type const irq)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    ssi_instance_ctrl_t * p_instance_ctrl = (ssi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* Events that are being serviced are being cleared. During this time if another error occurs then this
     * interrupt will fire again */

    /* Clear all flags in SSISR. These bits can only be cleared after reading them as 1.  Reference section
     * "Status Register (SSISR)" of the User's Manual. */
    uint32_t iirq_flag = p_instance_ctrl->p_reg->SSISR_b.IIRQ;
    p_instance_ctrl->p_reg->SSISR = 0U;

    if (1U == iirq_flag)
    {
        /* Disable idle interrupt. */
        p_instance_ctrl->p_reg->SSICR_b.IIEN = 0U;

        /* If peripheral is idle, call idle callback. */
        r_ssi_call_callback(p_instance_ctrl, I2S_EVENT_IDLE);
    }
    else
    {
        if (NULL != p_instance_ctrl->p_rx_dest)
        {
            /* If there's more data to read, flush read data into the destination buffer. */
            r_ssi_fifo_read(p_instance_ctrl);
        }

        /* SSI must go idle after a transmit or receive error. Reference section "When an error interrupt
         * is generated" in the User's Manual. */
        r_ssi_stop_sub(p_instance_ctrl);
    }

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

#if SSI_CFG_DMAC_ENABLE

/*******************************************************************************************************************//**
 * Dedicated function for DMAC linkage at the time of transmission.
 **********************************************************************************************************************/
void ssi_tx_dmac_callback (ssi_instance_ctrl_t * p_ctrl)
{
    p_ctrl->p_tx_src = NULL;
}

/*******************************************************************************************************************//**
 * Dedicated function for DMAC linkage at the time of reception.
 **********************************************************************************************************************/
void ssi_rx_dmac_callback (ssi_instance_ctrl_t * p_ctrl)
{
    p_ctrl->p_rx_dest = NULL;

    r_ssi_call_callback(p_ctrl, I2S_EVENT_RX_FULL);
}

#endif

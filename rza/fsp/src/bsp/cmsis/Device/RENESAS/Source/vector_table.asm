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

//==================================================================
// Entry point for the Reset handler
//==================================================================

    .section VECTOR_TABLE, "ax"
    .align 11

    .global Start
    .global vector_table

    .extern irq_handler
    .extern fiq_handler

//
// Current EL with SP0
//
vector_table:
SyncSp0:
    B SyncSp0

    .balign 0x80
IrqSp0:
    B irq_handler

    .balign 0x80
FiqSp0:
    B fiq_handler

    .balign 0x80
SerrSp0:
    WFI
    B SerrSp0
    .balign 0x80

//
// Current EL with SPx
//

SyncSpx:
    B SyncSpx

    .balign 0x80

IrqSpx:
    B irq_handler

    .balign 0x80
FiqSpx:
    B fiq_handler

    .balign 0x80
SerrSpx:
    WFI
    B SerrSpx

    .balign 0x80
//
// Lower EL using AArch64
//
SyncLowEl64:
    WFI
    B   SyncLowEl64

    .balign 0x80
IrqLowEl64:
    WFI
    B   IrqLowEl64

    .balign 0x80
FiqLowEl64:
    WFI
    B   FiqLowEl64

    .balign 0x80
SerrorLowEl64:
    WFI
    B   SerrorLowEl64

    .balign 0x80
//
// Lower EL using AArch32
//

SyncLowEl32:
    WFI
    B   SyncLowEl32

    .balign 0x80
IrqLowEl32:
    WFI
    B   IrqLowEl32

    .balign 0x80
FiqLowEl32:
    WFI
    B   FiqLowEl32

    .balign 0x80
SerrorLowEl32:
    WFI
    B   SerrorLowEl32

    .balign 0x80

    .END

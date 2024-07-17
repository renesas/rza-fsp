/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

//==================================================================
// Entry point for the FIQ handler
//==================================================================
    .section    IRQ_FIQ_HANDLER, "ax"
    .align 8

    .extern  IRQ_ExecuteHandler
    .extern  FIQ_ExecuteHandler

    .global  irq_handler
    .global  fiq_handler

    .equ     DAIF_BIT_F, (1 << 0)

//******************************************************************************
// fiq_handler
//******************************************************************************
fiq_handler:

        MSR             SPSEL, #0

        STP             x29, x30, [SP, #-0x10]!
        STP             x18, x19, [SP, #-0x10]!
        STP             x16, x17, [SP, #-0x10]!
        STP             x14, x15, [SP, #-0x10]!
        STP             x12, x13, [SP, #-0x10]!
        STP             x10, x11, [SP, #-0x10]!
        STP             x8, x9, [SP, #-0x10]!
        STP             x6, x7, [SP, #-0x10]!
        STP             x4, x5, [SP, #-0x10]!
        STP             x2, x3, [SP, #-0x10]!
        STP             x0, x1, [SP, #-0x10]!

        /* Save the SPSR and ELR. */
        MRS             x3, SPSR_EL3
        MRS             x2, ELR_EL3
        STP             x2, x3, [sp, #-0x10]!

        BL              FIQ_ExecuteHandler

        MSR             DAIFSET, #DAIF_BIT_F
        DSB             SY
        ISB             SY

        /* Restore volatile registers. */
        LDP             x4, x5, [sp], #0x10     /* SPSR and ELR. */

        MSR             SPSR_EL3, x5
        MSR             ELR_EL3, x4

        DSB             SY
        ISB             SY

        LDP             x0, x1, [sp], #0x10
        LDP             x2, x3, [sp], #0x10
        LDP             x4, x5, [sp], #0x10
        LDP             x6, x7, [sp], #0x10
        LDP             x8, x9, [sp], #0x10
        LDP             x10, x11, [sp], #0x10
        LDP             x12, x13, [sp], #0x10
        LDP             x14, x15, [sp], #0x10
        LDP             x16, x17, [sp], #0x10
        LDP             x18, x19, [sp], #0x10
        LDP             x29, x30, [sp], #0x10

        ERET

//******************************************************************************
// irq_handler
//******************************************************************************
irq_handler:

        MSR             SPSEL, #0

        STP     x0, x1, [sp, #-0x10]!
        STP     x2, x3, [sp, #-0x10]!
        STP     x4, x5, [sp, #-0x10]!
        STP     x6, x7, [sp, #-0x10]!
        STP     x8, x9, [sp, #-0x10]!
        STP     x10, x11, [sp, #-0x10]!
        STP     x12, x13, [sp, #-0x10]!
        STP     x14, x15, [sp, #-0x10]!
        STP     x16, x17, [sp, #-0x10]!
        STP     x18, x19, [sp, #-0x10]!
        STP     x29, x30, [sp, #-0x10]!

        /* Save the SPSR and ELR. */
//;     MRS     x3, SPSR_EL3
//;     MRS     x2, ELR_EL3
//;     STP     x2, x3, [sp, #-0x10]!
//;
//;     LDR     x5, g_interrupt_nesting_count
//;     LDR     x1, [x5]
//;     ADD     x6, x1, #1
//;     STR     x6, [x5]
//;
//;     STP     x1, x5, [sp, #-0x10]!
//;
//;     mrs     x0, ICC_IAR1_EL1
//;
//;     STP     x0, x1, [sp, #-0x10]!

        BL      IRQ_ExecuteHandler

//;     MSR     DAIFSET, #2
//;     DSB     SY
//;     ISB     SY
//;
//;     LDP     x0, x1, [sp], #0x10
//;
//;     /* End IRQ processing by writing ICCIAR to the EOI register */
//;     msr     ICC_EOIR1_EL1, x0
//;
//;     /* Restore the critical nesting count */
//;     LDP     x1, x5, [sp], #0x10
//;     STR     x1, [x5]
//;
//;     /* Restore volatile registers. */
//;     LDP     x4, x5, [sp], #0x10     /* SPSR and ELR. */
//;
//;     MSR     SPSR_EL3, x5
//;     MSR     ELR_EL3, x4
//;
//;     DSB     SY
//;     ISB     SY

        LDP     x29, x30, [sp], #0x10
        LDP     x18, x19, [sp], #0x10
        LDP     x16, x17, [sp], #0x10
        LDP     x14, x15, [sp], #0x10
        LDP     x12, x13, [sp], #0x10
        LDP     x10, x11, [sp], #0x10
        LDP     x8, x9, [sp], #0x10
        LDP     x6, x7, [sp], #0x10
        LDP     x4, x5, [sp], #0x10
        LDP     x2, x3, [sp], #0x10
        LDP     x0, x1, [sp], #0x10

        ERET

    .END

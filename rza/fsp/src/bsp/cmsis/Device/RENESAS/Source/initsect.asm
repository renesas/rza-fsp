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

        .section    INIT_SECTION, "ax"
        .global     INITSCT
        .type       INITSCT, %function

        // This program need the stack area (44bytes)
INITSCT:
        STP     x4, x5, [sp, #-0x10]!
        STP     x6, x7, [sp, #-0x10]!
        MOV     x4, x0          // 1st parameter : copy table
        STR     x1, [sp, #-0x8]!
        CMP     x4, #0
        B.NE    _COPYVAR        // copy the variables
ZEROFILL:
        LDR     x4, [sp], #0x8  // 2nd parameter : zero table
        CMP     x4, #0
        B.NE    _ZEROVAR        // fill the variables with zero
        LDP     x4, x5, [sp], #0x10
        LDP     x6, x7, [sp], #0x10
RETURN:
        RET

//
// Copy the vaiables
// This program gets from the table of coping area "DTBL[]"
_COPYVAR:

_CVAR_continue:
        LDR     x0, [x4], #8        // r0 = top of source block
        LDR     x1, [x4], #8        // r1 = end of source block
        SUB     x2, x1, x0          // r2 = bytes to copy
        LDR     x1, [x4], #8        // r1 = top of destination block

        CMP     x0, #0              // check terminator
        B.EQ    ZEROFILL            // return

        LSR     x3, x2, #4          // Number of two word (16byte) multiples
        CMP     x3, #0
        B.EQ    _CVAR_check_remain  // Fewer than two words to move

        B       _CVAR_copy_16
        .align 7                    // alignment for loop optimization
                                    // 7 : 2^7 = 128bytes boundary
_CVAR_copy_16:
        LDP     x5, x6, [x0], #0x10 // Load 2 words from the source
        STP     x5, x6, [x1], #0x10 // and put them at the destination
        SUBS    x3, x3, #1          // Decrement the counter
        B.NE    _CVAR_copy_16       // ... copy more

_CVAR_check_remain:
        ANDS    x2, x2, #0x0f       // Number of bytes to copy
        B.EQ    _CVAR_next_block    // No byte left to copy?
        B       _CVAR_copy_1
        .align 7                    // alignment for loop optimization
                                    // 7 : 2^7 = 128bytes boundary
_CVAR_copy_1:
        LDRB    w5, [x0], #1        // Load a word from the source and
        STRB    w5, [x1], #1        // store it to the destination
        SUBS    x2, x2, #1          // Decrement the counter
        B.NE    _CVAR_copy_1        // ... copy more

_CVAR_next_block:
        B       _CVAR_continue      // copy the next block


//
// Fill the vaiables
// This program gets from the table of coping area "BTBL[]"
_ZEROVAR:

_ZVAR_continue:
        LDR     x1, [x4], #8        // r1 = top of block
        LDR     x2, [x4], #8        // r2 = end of block
        SUB     x2, x2, x1          // r2 = number of bytes to fill zero

        CMP     x1, #0              // check terminator
        B.EQ    RETURN              // return

        MOV     x0, #0              // fill value

        LSR     x3, x2, #4          // Number of two word (16byte) multiples
        CMP     x3, #0
        B.EQ    _ZVAR_check_remain  // Fewer than eight words to clean?

        MOV     x5, #0              //
        MOV     x6, #0              //

        B       _ZVAR_fill_16
        .align 7                    // alignment for loop optimization
                                    // 7 : 2^7 = 128bytes boundary
_ZVAR_fill_16:
        STP     x5, x6, [x1], #0x10 // fill the block
        SUBS    x3, x3, #1          // Decrement the counter
        B.NE    _ZVAR_fill_16       // ... fill more

_ZVAR_check_remain:
        ANDS    x2, x2, #0x0f       // Number of bytes to copy
        B.EQ    _ZVAR_next_block    // No words left to copy?

        B       _ZVAR_fill_1
        .align 7                    // alignment for loop optimization
                                    // 7 : 2^7 = 128bytes boundary
_ZVAR_fill_1:
        STRB    w0, [x1], #1        // Fill the block
        SUBS    x2, x2, #1          // Decrement the counter
        B.NE     _ZVAR_fill_1       // ... fill more

_ZVAR_next_block:
        B       _ZVAR_continue      // fill the next block


        .END

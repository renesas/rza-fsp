/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** ThreadX Component                                                     */
/**                                                                       */
/**   Initialize                                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/
#ifdef TX_INCLUDE_USER_DEFINE_FILE
#include "tx_user.h"
#endif

	.extern  _tx_vector_table_set

    .text
    .align 3
/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_initialize_low_level                             ARMv8-A        */
/*                                                           6.3.0        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is responsible for any low-level processor            */
/*    initialization, including setting up interrupt vectors, setting     */
/*    up a periodic timer interrupt source, saving the system stack       */
/*    pointer for use in ISR processing later, and finding the first      */
/*    available RAM memory address for tx_application_define.             */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _tx_initialize_kernel_enter           ThreadX entry function        */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*  01-31-2022     Andres Mlinar            Updated comments,             */
/*                                            resulting in version 6.1.10 */
/*  10-31-2023     Tiejun Zhou              Modified comment(s), added    */
/*                                            #include tx_user.h,         */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/
// VOID   _tx_initialize_low_level(VOID)
// {
    .global  _tx_initialize_low_level
    .type    _tx_initialize_low_level, @function
_tx_initialize_low_level:

    /* Setup EL0 stack */
    MOV     x0, sp                              // Pickup SP
    MSR     SPSEL, #0                           // Change to EL0
    MOV     sp, x0                              // Setup to EL0 stack

    MSR     DAIFSet, 0x3                        // Lockout interrupts

    /* Save the system stack pointer.  */
    // _tx_thread_system_stack_ptr = (VOID_PTR) (sp);

    LDR     x0, =_tx_thread_system_stack_ptr    // Pickup address of system stack ptr
    MOV     x1, sp                              // Pickup SP
    SUB     x1, x1, #15                         //
    BIC     x1, x1, #0xF                        // Get 16-bit alignment
    STR     x1, [x0]                            // Store system stack

    /* Save the first available memory address.  */
    // _tx_initialize_unused_memory =  (VOID_PTR) Image$$ZI$$Limit;

    LDR     x0, =_tx_initialize_unused_memory   // Pickup address of unused memory ptr
    LDR     x1, =__top_of_ram                   // Pickup unused memory address
    LDR     x1, [x1]                            //
    STR     x1, [x0]                            // Store unused memory address

    /* Setup tick timer */
    STP     x29, x30, [sp, #-16]!               // Save x29 (frame pointer), x30 (link register)

    BL      vPortSetupTimerInterrupt

    /* Setup vector table for ThreadX */
	BL		_tx_vector_table_set

    LDP     x29, x30, [sp], #16                 // Recover x29, x30

    /* Done, return to caller.  */

    RET                                         // Return to caller
// }

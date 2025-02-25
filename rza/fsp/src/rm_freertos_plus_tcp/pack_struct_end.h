/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#if defined(__GNUC__)
 #include \
    "../../../../rza/aws/Lab-Project-FreeRTOS-TCP/source/portable/Compiler/GCC/pack_struct_end.h"
#elif defined(__IAR_SYSTEMS_ICC__)
 #include \
    "../../../../rza/aws/Lab-Project-FreeRTOS-TCP/source/portable/Compiler/IAR/pack_struct_end.h"

/* Check Pe1644 error (definition at end of file not followed by a semicolon or a declarator). */
 #pragma diag_default=Pe1644
#elif defined(__CC_ARM)
 #include \
    "../../../../rza/aws/Lab-Project-FreeRTOS-TCP/source/portable/Compiler/Keil/pack_struct_end.h"
#else
 #error Unknown compiler.
#endif

/**
 @file i_Circular_Array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for arrayed lists of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_Circular_Array type.

*/

#include "i_Circular_Array.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VALUE_DEEP_DISPOSE_FUNCTION( arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) ( arg )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( (arg1) == (arg2) )

#define VALUE_DEFAULT 0

// #define PRE_FILE DBC_YES

#define Prefix i
#define Type int32_t
#define Type_Code int32_type_code

#include "Circular_Array.c"

#undef Prefix
#undef Type
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


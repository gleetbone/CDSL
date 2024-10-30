/**
 @file i_HSet.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for hash set of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for int_DList type.

*/

#include "i_HSet.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define HASH_FUNCTION( arg ) ( arg )
#define DEEP_DISPOSE_FUNCTION( arg )
#define DEEP_CLONE_FUNCTION( arg ) ( arg )
#define DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( (arg1) == (arg2) )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i
#define Item int32_t
#define Type_Code int32_type_code

#include "HSet.c"

#undef Prefix
#undef Item
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


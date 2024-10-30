/**
 @file c_AList.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for arrayed lists of P_Command"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for c_AList type.

*/

#include "c_AList.h"
#include "p_Basic.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VALUE_DEEP_DISPOSE_FUNCTION( arg ) p_basic_deep_dispose( &arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) p_basic_deep_clone( arg )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) p_basic_is_deep_equal( (arg1), (arg2) )

#define VALUE_DEFAULT NULL

// #define PRE_FILE DBC_YES

#define Prefix c
#define Type protocol_base_t *
#define Type_Code P_CLH_COMMAND_TYPE

#include "AList.c"

#undef Prefix
#undef Type
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


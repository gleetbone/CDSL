/**
 @file s_SList.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for singly linked lists of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for s_SList type.

*/

#include "s_SList.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VALUE_DEEP_DISPOSE_FUNCTION( arg ) string_deep_dispose( &arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) string_deep_clone( arg )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) string_is_deep_equal( (arg1), (arg2) )

#define Prefix s
#define Type string_t *
#define Type_Code STRING_TYPE

#include "SList.c"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

/* End of file */


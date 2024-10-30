/**
 @file ss_HTable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for hash table of strings to strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for ss_HTable_t type.

*/

#include "ss_HTable.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define KEY_HASH_FUNCTION( arg ) string_hash_code( arg )
#define KEY_DEEP_EQUAL_FUNCTION( arg1, arg2 ) string_is_deep_equal( arg1, arg2 )
#define KEY_DEEP_DISPOSE_FUNCTION( arg ) string_deep_dispose( &arg )
#define KEY_DEEP_CLONE_FUNCTION( arg ) string_deep_clone( arg )

#define VALUE_DEEP_DISPOSE_FUNCTION( arg ) string_deep_dispose( &arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) string_deep_clone( arg )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) string_is_deep_equal( arg1, arg2 )

#define Prefix ss
#define Type string_t *
#define Key string_t *
#define Key_Code STRING_TYPE
#define Type_Code STRING_TYPE

#include "HTable.c"

#undef Prefix
#undef Type
#undef Key
#undef Key_Code
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


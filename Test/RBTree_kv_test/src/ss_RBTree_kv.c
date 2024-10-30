/**
 @file ss_RBTree_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for binary search tree of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for int_DList type.

*/

#include "ss_RBTree_kv.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define KEY_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( ( string_is_deep_equal( arg1, arg2 ) == 1 ) )
#define KEY_DEEP_DISPOSE_FUNCTION( arg ) ( string_deep_dispose( &arg ) )
#define KEY_DEEP_CLONE_FUNCTION( arg ) ( string_deep_clone( arg ) )
#define KEY_ORDER_FUNCTION( arg1, arg2 ) ( ( string_is_less_than_or_equal( arg1, arg2 ) == 1  ) )
#define KEY_DEFAULT 0

#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( ( string_is_deep_equal( arg1, arg2 ) == 1 ) )
#define VALUE_DEEP_DISPOSE_FUNCTION( arg ) ( string_deep_dispose( &arg ) )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) ( string_deep_clone( arg ) )
#define VALUE_ORDER_FUNCTION( arg1, arg2 ) ( ( string_is_less_than_or_equal( arg1, arg2 ) == 1  ) )
#define VALUE_DEFAULT 0

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix ss
#define Key string_t *
#define Type string_t *
#define Key_Code STRING_TYPE
#define Type_Code STRING_TYPE


#include "RBTree_kv.c"

#undef Prefix
#undef Key
#undef Type
#undef Key_Code
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


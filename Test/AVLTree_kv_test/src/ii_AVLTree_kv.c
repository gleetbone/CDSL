/**
 @file ii_AVLTree_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for AVL tree of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for ii_avltree_kv type.

*/

#include "ii_AVLTree_kv.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define KEY_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( ( arg1 == arg2 ) )
#define KEY_DEEP_DISPOSE_FUNCTION( arg )
#define KEY_DEEP_CLONE_FUNCTION( arg ) ( arg )
#define KEY_ORDER_FUNCTION( arg1, arg2 ) ( ( arg1 <= arg2  ) )
#define KEY_DEFAULT 0

#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( ( arg1 == arg2 ) )
#define VALUE_DEEP_DISPOSE_FUNCTION( arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) ( arg )
#define VALUE_ORDER_FUNCTION( arg1, arg2 ) ( ( arg1 <= arg2  ) )
#define VALUE_DEFAULT 0

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix ii
#define Key int32_t
#define Type int32_t
#define Key_Code int32_type_code
#define Type_Code int32_type_code


#include "AVLTree_kv.c"

#undef Prefix
#undef Key
#undef Type
#undef Key_Code
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


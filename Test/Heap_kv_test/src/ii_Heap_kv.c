/**
 @file ii_Heap_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for integer-integer heaps"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines for ii_Heap_kv type.

*/

#include "ii_Heap_kv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_EQUALITY_FUNCTION( arg1, arg2 ) ( ( arg1 == arg2 ) )
#define KEY_DISPOSE_FUNCTION( arg )
#define KEY_DUPLICATE_FUNCTION( arg ) ( arg )
#define KEY_DEFAULT_VALUE 0
#define KEY_ORDER_FUNCTION( arg1, arg2 ) ( ( arg1 < arg2  ) )

#define VALUE_EQUALITY_FUNCTION( arg1, arg2 ) ( ( arg1 == arg2 ) )
#define VALUE_DISPOSE_FUNCTION( arg )
#define VALUE_DUPLICATE_FUNCTION( arg ) ( arg )
#define VALUE_DEFAULT_VALUE 0

#define Prefix ii
#define Key int32_t
#define Type int32_t
#define Key_Code int32_type_code
#define Type_Code int32_type_code


#include "Heap_kv.c"

#undef Prefix
#undef Key
#undef Type
#undef Key_Code
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


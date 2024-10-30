/**
 @file s_Heap_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for string-string heaps"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines for ii_Heap_kv type.

*/

#include "ss_Heap_kv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_EQUALITY_FUNCTION( arg1, arg2 ) ( string_is_equal( arg1, arg2 ) )
#define KEY_DISPOSE_FUNCTION( arg ) ( string_dispose( &arg ) )
#define KEY_DUPLICATE_FUNCTION( arg ) ( string_clone( arg ) )
#define KEY_DEFAULT_VALUE NULL
#define KEY_ORDER_FUNCTION( arg1, arg2 ) ( ( string_is_less_than( arg1, arg2 ) == 1  ) || ( string_is_equal( arg1, arg2 ) == 1 ) )

#define VALUE_EQUALITY_FUNCTION( arg1, arg2 ) ( string_is_equal( arg1, arg2 ) )
#define VALUE_DISPOSE_FUNCTION( arg ) ( string_dispose( &arg ) )
#define VALUE_DUPLICATE_FUNCTION( arg ) ( string_clone( arg ) )
#define VALUE_DEFAULT_VALUE NULL

#define Prefix ss
#define Key string_t *
#define Type string_t *
#define Key_Code STRING_TYPE
#define Type_Code STRING_TYPE


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


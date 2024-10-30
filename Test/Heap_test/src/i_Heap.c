/**
 @file i_Heap.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for integer heaps"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines for i_Heap type.

*/

#include "i_Heap.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EQUALITY_FUNCTION( arg1, arg2 ) ( ( arg1 == arg2 ) )

#define DISPOSE_FUNCTION( arg )
#define DUPLICATE_FUNCTION( arg ) ( arg )
#define DEFAULT_VALUE 0
#define ORDER_FUNCTION( arg1, arg2 ) ( ( arg1 < arg2  ) )

#define Prefix i
#define Type int32_t
#define Type_Code int32_type_code


#include "Heap.c"

#undef Prefix
#undef Type
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


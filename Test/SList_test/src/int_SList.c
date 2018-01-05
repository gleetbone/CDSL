/**
 @file int_SList.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for singly linked lists of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for int_SList type.

*/

#include "int_SList.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VALUE_DISPOSE_FUNCTION( arg )
#define VALUE_DUPLICATE_FUNCTION( arg ) ( arg )

#define Prefix int
#define Type int32_t
#define Type_Code int32_type_code

#include "SList.c"

#undef Prefix
#undef Type
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


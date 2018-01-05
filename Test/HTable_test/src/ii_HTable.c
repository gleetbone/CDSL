/**
 @file ii_HTable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for hash table of ints to ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for int_DList type.

*/

#include "ii_HTable.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define HASH_FUNCTION( arg ) ( arg )

#define EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define KEY_DISPOSE_FUNCTION( arg )

#define VALUE_DISPOSE_FUNCTION( arg )

#define KEY_DUPLICATE_FUNCTION( arg ) ( arg )
 
#define VALUE_DUPLICATE_FUNCTION( arg ) ( arg )


#define Prefix ii
#define Type int32_t
#define Key int32_t
#define Key_Code int32_type_code
#define Type_Code int32_type_code

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


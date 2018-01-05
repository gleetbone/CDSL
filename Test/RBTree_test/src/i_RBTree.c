/**
 @file i_RBTree.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for binary search tree of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for int_DList type.

*/

#include "i_RBTree.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define EQUALITY_FUNCTION( arg1, arg2 ) ( ( arg1 == arg2 ) )

#define DISPOSE_FUNCTION( arg )
#define DUPLICATE_FUNCTION( arg ) ( arg )
#define ORDER_FUNCTION( arg1, arg2 ) ( ( arg1 < arg2  ) )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i
#define Type int32_t
#define Type_Code int32_type_code


#include "RBTree.c"

#undef Prefix
#undef Type
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


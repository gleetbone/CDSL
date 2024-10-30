/**
 @file s_HSet.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for hash set of Strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for s_DList type.

*/

#include "s_HSet.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define HASH_FUNCTION( arg ) ( string_hash_code( arg ) )
#define DEEP_DISPOSE_FUNCTION( arg ) ( string_deep_dispose( &arg ))
#define DEEP_CLONE_FUNCTION( arg ) ( string_deep_clone( arg ) )
#define DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( string_is_deep_equal( (arg1), (arg2) ) )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix s
#define Item string_t *
#define Type_Code STRING_TYPE

#include "HSet.c"

#undef Prefix
#undef Item
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file ss_HTable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Hash table of string_t keys to string_t values"
 
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):
 
 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package. 

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.
 
 @section Description

 Function definitions for the opaque ss_htable_t type.

*/

#include "ss_HTable.h"
#include "String_extras.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES


#define HASH_FUNCTION( arg ) ( s_hash_code( arg ) )

#define EQUALITY_FUNCTION( arg1, arg2 ) ( s_is_equal( arg1, arg2 ) == 1 )

#define KEY_DISPOSE_FUNCTION( arg ) ( ( arg != NULL ) ? s_dispose_with_contents( arg ) : 0 )
#define KEY_DUPLICATE_FUNCTION( arg ) ( ( arg != NULL ) ? s_make_from( arg ) : 0 )

#define VALUE_DISPOSE_FUNCTION( arg ) ( ( arg != NULL ) ? s_dispose_with_contents( arg ) : 0 )
#define VALUE_DUPLICATE_FUNCTION( arg ) ( ( arg != NULL ) ? s_make_from( arg ) : 0 )

#define Prefix ss
#define Type string_t *
#define Key string_t *
#define Type_Code 0xA5000500
#define Key_Code 0xA5000500

#include "HTable.c"

#undef Prefix
#undef Type_Code
#undef Key_Code
#undef Type
#undef Key
#undef HASH_FUNCTION
#undef EQUALITY_FUNCTION
#undef KEY_DISPOSE_FUNCTION
#undef VALUE_DISPOSE_FUNCTION

#ifdef __cplusplus
}
#endif

/* End of file */


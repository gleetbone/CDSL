/**
 @file s_Circular_Array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for  linked lists of strings"
 
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
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

 Defines for s_Circular_Array type.

*/

#include "s_Circular_Array.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VALUE_DEFAULT NULL

#define VALUE_DEEP_DISPOSE_FUNCTION( arg ) ( arg == NULL ? NULL : string_deep_dispose( &arg ) )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) ( arg == NULL ? NULL : string_deep_clone( arg ) )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( ( ( arg1 == NULL ) || ( arg2 == NULL  ) ) ? ( arg1 == arg2 ) : string_is_deep_equal( (arg1), (arg2) ) )

#define Prefix s
#define Type string_t *
#define Type_Code STRING_TYPE

#include "Circular_Array.c"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

/* End of file */

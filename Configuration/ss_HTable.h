/**
 @file ss_HTable.h
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

 Function declarations for the opaque ss_htable_t type.

*/

#ifndef STRING_STRING_HTABLE_H_
#define STRING_STRING_HTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#include "base.h"

#include "String.h"

#define Prefix ss
#define Type string_t *
#define Key string_t *

#include "HTable.h"

#undef Prefix
#undef Type
#undef Key

#ifdef __cplusplus
}
#endif

#endif /* STRING_STRING_HTABLE_H_ */

/* End of file */




/**
 @file String_extras_utf8.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Character Strings"

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

 Some additional function declarations for the opaque string_utf8_t type.

*/

#ifndef STRING_UTF8_EXTRAS_H
#define STRING_UTF8_EXTRAS_H


/**
   Includes
*/

#include "base.h"
#include "String_utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
   s_utf8_hash_code

   Returns hash code

   @param string the string_utf8_t instance
   @return string's hash code
*/

int32_t
s_utf8_hash_code( string_utf8_t *string );

/**
   s_utf8_is_equal

   Returns 1 if strings equal

   @param s1 the first string_utf8_t instance to compare
   @param s2 the second string_utf8_t instance to compare
   @return 1 if strings equal, 0 otherwise
*/

int32_t
s_utf8_is_equal( const string_utf8_t *s1, const string_utf8_t *s2 );

/**
   s_utf8_dispose_with_contents

   Dispose of string and its contents

   @param string the string_utf8_t instance
*/

void
s_utf8_dispose_with_contents( string_utf8_t *string );

/**
   s_utf8_make_from

   Make duplicate of string

   @param string the string_utf8_t instance
*/

string_utf8_t *
s_utf8_make_from( const string_utf8_t *string );

#ifdef __cplusplus
}
#endif

#endif /* STRING_UTF8_EXTRAS_H */

/* End of file */





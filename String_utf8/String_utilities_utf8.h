/**
 @file String_utilities_utf8.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Character String utility functions"

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

 Function declarations for the string_utf8_t utilities.

*/

#ifndef STRING_UTF8_UTILITIES_H
#define STRING_UTF8_UTILITIES_H


/**
   Includes
*/

#include "base.h"
#include "String_utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
   File operations
*/

/**
   string_utf8_from_file

   Read a (text) file, return in string

   @return string_utf8_utf8_t the file contents
*/
string_utf8_t *
string_utf8_from_file( const string_utf8_t *filename );

/**
   string_utf8_from_file_cstring
*/

string_utf8_t *
string_utf8_from_file_cstring( const char_t *filename );

/**
   string_utf8_to_file

   Write a string to a file

   @param string the text to put into the file
   @param filename the file name

*/

void
string_utf8_to_file( string_utf8_t *string, string_utf8_t *filename );

/**
   string_utf8_to_file_cstring

   Write a string to a file

   @param string the text to put into the file
   @param filename the file name

*/

void
string_utf8_to_file_cstring( const string_utf8_t *string, const char_t *filename );


/**
   cstring_to_file_cstring

   Write a cstring to a file

   @param string the text to put into the file
   @param filename the file name

*/

void
cstring_to_file_cstring( const char_t *string, const char_t *filename );

/**
   file_exists

   @param filename the name of the file
   @return 1 if file exists, 0 otherwise

*/

int32_t
file_exists( const string_utf8_t *filename );


/**
   file_exists_cstring

   @param filename the name of the file
   @return 1 if file exists, 0 otherwise

*/

int32_t
file_exists_cstring( const char_t *filename );


/**
   current_time_as_string
*/

string_utf8_t *
current_time_as_string( void );


/**
   current_time_as_cstring
*/

char_t *
current_time_as_cstring( void );

/**
   current_time_as_cstring1
*/

char_t *
current_time_as_cstring1( void );


/**
   Miscellaneous
*/

/**
   string_utf8_append_indent

   Append count worth of indention as spaces

   @param string the string to append to
*/
void
string_utf8_append_indent( string_utf8_t *string, int32_t count );

/**
   string_utf8_append_newline

   Append new line characters

   @param string the string to append to
*/
void
string_utf8_append_newline( string_utf8_t *string );

/**
   string_utf8_hex_to_uint8

   Converts two character hex string to uint8_t

   @param string the string
   @return the integer
*/
uint8_t
string_utf8_hex_to_uint8( const string_utf8_t *string );

/**
   cstring_hex_to_uint8

   Converts two character hex cstring to uint8_t

   @param string the cstring
   @return the integer
*/
uint8_t
cstring_hex_to_uint8( const char_t *string );

/**
   string_utf8_hex_from_uint8

   Converts uint8_t to two character hex string

   @param u8 the integer
   @return the string
*/
string_utf8_t *
string_utf8_hex_from_uint8( uint8_t u8 );

/**
   cstring_hex_from_uint8

   Converts uint8_t to two character hex cstring

   @param u8 the integer
   @return the string
*/
char_t *
cstring_hex_from_uint8( uint8_t u8 );

/**
   string_utf8_hex_from_int32

   Converts int32_t to eight character hex string

   @param i32 the integer
   @return the string
*/
string_utf8_t *
string_utf8_hex_from_int32( int32_t i32 );

/**
   cstring_hex_from_int32

   Converts int32_t to two character hex cstring

   @param i32 the integer
   @return the string
*/
char_t *
cstring_hex_from_int32( int32_t i32 );

#ifdef __cplusplus
}
#endif

#endif /* STRING_UTF8_UTILITIES_H */

/* End of file */





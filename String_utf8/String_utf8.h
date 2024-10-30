/**
 @file String_utf8.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Character String_utf8s (unicode)"

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

 Function declarations for the opaque string_utf8_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STRING_UTF8_T_H
#define STRING_UTF8_T_H


/**
   Includes
*/

#include "base.h"
#include <wchar.h>

/**
   Structure declaration
*/

struct string_utf8_struct;

/**
   Structure typedef
*/

typedef struct string_utf8_struct string_utf8_t;
typedef uint16_t utf16_t;
typedef uint32_t utf32_t;


/*
   Initialization
*/

/**
   string_utf8_make

   Create and initialize a string_utf8_t instance.
   Content will be the empty string and the capacity will be 1.

   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make( void );

/**
   string_utf8_make_n

   Create and initialize a string_utf8_t instance.
   Content will be the empty string and the capacity will be "capacity".

   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make_n( int32_t capacity );

/**
   string_utf8_make_from

   Create and initialize a string_utf8_t instance.
   Content will be a copy of "str" and the capacity will
   be str's byte count + 1.

   @param str the string_utf8_t instance to initialize from
   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make_from( string_utf8_t *current );

/**
   string_utf8_make_from_cstring

   Create and initialize a string_utf8_t instance.
   Content will be a copy of "str" and the capacity will
   be the byte count of str + 1.

   @param str the C string to initialize from
   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make_from_cstring( char_t *str );

/**
   string_utf8_make_from_utf16

   Create and initialize a zero terminated string_utf8_t instance.
   Content will be "str" converted from UTF-16 to UTF-8 and
   the capacity will be at least the byte count of the converted
   UTF-8 string plus 1.

   @param str the C UTF-16 string to initialize from
   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make_from_utf16( utf16_t *str );

/**
   string_utf8_make_from_utf32

   Create and initialize a zero terminated string_utf8_t instance.
   Content will be "str" converted from UTF-32 to UTF-8 and
   the capacity will be at least the byte count of the converted
   UTF-8 string plus 1.

   @param str the C UTF-32 string to initialize from
   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make_from_utf32( utf32_t *str );

/**
   string_utf8_make_from_wcstring

   Create and initialize a zero terminated string_utf8_t instance.
   Content will be "str" converted from wchar_t to UTF-8 and
   the capacity will be at least the byte count of the converted
   UTF-8 string plus 1.

   @param str the C wchar_t * string to initialize from
   @return pointer to the new data structure
*/
string_utf8_t *
string_utf8_make_from_wchar( wchar_t *str );


/*
   Disposal
*/

/**
   string_utf8_dispose

   Deallocates a string_utf8_t instance. Does not deallocate its internal char_t * string.

   @param current reference to the C string to dispose
*/
void
string_utf8_dispose( string_utf8_t **current );

/**
   string_utf8_deep_dispose

   Deallocates a string_utf8_t instance and its internal char_t * string.

   @param current the C string to dispose
*/
void
string_utf8_deep_dispose( string_utf8_t **current );


/*
   Access
*/


/**
   string_utf8_item_ascii

   Returns the character in string at "index" as an ASCII character.
   Indexing starts at 0. Invalid if character at index is not ASCII.

   @param current the string_utf8_t instance
   @param index the index to retrieve from
   @return the ASCII character in string at index
*/
char_t
string_utf8_item_ascii( string_utf8_t *current, int32_t index );

/**
   string_utf8_item

   Returns the character in string at "index" as a UTF-8 string.
   Indexing starts at 0.

   @param current the string_utf8_t instance
   @param index the index to retrieve from
   @return the zero terminated UTF-8 character (as a string) in string at index
           the result must be "free"d by the calling routine
*/
char_t *
string_utf8_item( string_utf8_t *current, int32_t index );

/**
   string_utf8_item_utf16

   Returns the character in string at "index" as a UTF-16 string.
   Indexing starts at 0.

   @param current the string_utf8_t instance
   @param index the index to retrieve from
   @return the zero terminated UTF-16 character (as a string) in string at index
           the result must be "free"d by the calling routine
*/
utf16_t
string_utf8_item_utf16( string_utf8_t *current, int32_t index );

/**
   string_utf8_item_utf32

   Returns the UTF-32 character in string at "index". Indexing starts at 0.

   @param current the string_utf8_t instance
   @param index the index to retrieve from
   @return the UTF-32 character in string at index
*/
utf32_t
string_utf8_item_utf32( string_utf8_t *current, int32_t index );

/**
   string_utf8_item_wchar

   Returns the character in string at "index" as a wchar_t.
   Indexing starts at 0.

   @param current the string_utf8_t instance
   @param index the index to retrieve from
   @return the wchar_t character in string at index
*/
wchar_t
string_utf8_item_wchar( string_utf8_t *current, int32_t index );

/**
   string_utf8_as_cstring

   Returns the contents of string as a char_t pointer.

   @param current the string_utf8_t instance
   @return pointer to the characters in string. the result is not a copy
           but a pointer to the internal data structure string storage
*/
char_t *
string_utf8_as_cstring( string_utf8_t *current );

/**
   string_utf8_as_utf8

   Returns the contents of string as a char_t pointer.

   @param current the string_utf8_t instance
   @return pointer to the characters in string. the result must
           be "free"d by the calling routine.
*/
char_t *
string_utf8_as_utf8( string_utf8_t *current );

/**
   string_utf8_as_utf16

   Returns the contents of string as a UTF-16 string.

   @param current the string_utf8_t instance
   @return pointer to the characters in string. the result must
           be "free"d by the calling routine.
*/
utf16_t *
string_utf8_as_utf16( string_utf8_t *current );

/**
   string_utf8_as_utf32

   Returns the contents of string as a UTF-32 string.

   @param current the string_utf8_t instance
   @return pointer to the characters in string. the result must
           be "free"d by the calling routine.
*/
utf32_t *
string_utf8_as_utf32( string_utf8_t *current );

/**
   string_utf8_as_wchar

   Returns the contents of string as a wchar_t string.

   @param current the string_utf8_t instance
   @return pointer to the characters in string. the result must
           be "free"d by the calling routine.
*/
wchar_t *
string_utf8_as_wchar( string_utf8_t *current );


/**
   Measurement
*/

/**
   string_utf8_count

   Returns the number of characters in string.

   @param current the string_utf8_t instance
   @return number of characters in string
*/
int32_t
string_utf8_count( string_utf8_t *current );

/**
   string_utf8_byte_count

   Returns the number of bytes used to hold the characters in string.

   @param current the string_utf8_t instance
   @return number of bytes used to hold string
*/
int32_t
string_utf8_byte_count( string_utf8_t *current );

/**
   string_utf8_capacity

   Returns the number of available bytes in string
   for storage. May be greater than count and byte_count.

   @param current the string_utf8_t instance
   @return number of bytes available for storage in string
*/
int32_t
string_utf8_capacity( string_utf8_t *current );


/*
   Status Report
*/

/**
   string_utf8_is_empty

   Returns 1 if the string content is the empty string, 0 otherwise.

   @param current the string_utf8_t instance
   @return 1 if empty, 0 otherwise
*/

int32_t
string_utf8_is_empty( string_utf8_t *current );

/**
   string_utf8_valid_index

   Returns 1 if the index is greater or equal to zero and less or equal
   to the count of characters in the string.

   @param current the string_utf8_t instance
   @return 1 if index OK, 0 otherwise
*/
int32_t
string_utf8_valid_index( string_utf8_t *current, int32_t index );

/**
   string_utf8_has

   Returns 1 if the string contains the UTF-8 character c.

   @param current the string_utf8_t instance
   @param c the character (as a null terminated string of UTF-8 bytes) to search for
   @return 1 if c present in string, 0 otherwise
*/
int32_t
string_utf8_has( string_utf8_t *current, char_t *c );

/**
   string_utf8_has_ascii

   Returns 1 if the string contains the ASCII character c.

   @param current the string_utf8_t instance
   @param c the ASCII character to search for
   @return 1 if c present in string, 0 otherwise
*/
int32_t
string_utf8_has_ascii( string_utf8_t *current, char_t c );

/**
   string_utf8_has_utf16

   Returns 1 if the string contains the UTF-16 character c.

   @param current the string_utf8_t instance
   @param c the character (as a null terminated string of UTF-16 words) to search for
   @return 1 if c present in string, 0 otherwise
*/
int32_t
string_utf8_has_utf16( string_utf8_t *current, utf16_t c );

/**
   string_utf8_has_utf32

   Returns 1 if the string contains the UTF-32 character c.

   @param current the string_utf8_t instance
   @param c the character to search for
   @return 1 if c present in string, 0 otherwise
*/
int32_t
string_utf8_has_utf32( string_utf8_t *current, utf32_t c );

/**
   string_utf8_has_wchar

   Returns 1 if the string contains the wchar_t character c.

   @param current the string_utf8_t instance
   @param c the character to search for
   @return 1 if c present in string, 0 otherwise
*/
int32_t
string_utf8_has_wchar( string_utf8_t *current, wchar_t c );

/**
   string_utf8_is_int32

   Returns 1 if the string can be parsed into an int32_t.

   @param current the string_utf8_t instance
   @return 1 if string is an int32_t, 0 otherwise
*/
int32_t
string_utf8_is_int32( string_utf8_t *current );

/**
   string_utf8_is_float64

   Returns 1 if the string can be parsed into an float64_t.

   @param current the string_utf8_t instance
   @return 1 if string is an float64_t, 0 otherwise
*/
int32_t
string_utf8_is_float64( string_utf8_t *current );

/**
   string_utf8_hash_code

   Returns hash code of the string.

   @param current the string_utf8_t instance
   @return hash code
*/
int32_t
string_utf8_hash_code( string_utf8_t *current );


/*
   Comparison
*/

/**
   string_utf8_is_equal

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first string_utf8_t instance
   @param s2 the first string_utf8_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_utf8_is_equal( string_utf8_t *s1, string_utf8_t *s2 );

/**
   string_utf8_is_equal_cstring

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first string_utf8_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_utf8_is_equal_cstring( string_utf8_t *s1, char_t *s2 );

/**
   string_utf8_is_less_than

   Returns 1 if s1 is less than s2

   @param s1 the first string_utf8_t instance
   @param s2 the first string_utf8_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_utf8_is_less_than( string_utf8_t *s1, string_utf8_t *s2 );

/**
   string_utf8_is_less_than_cstring

   Returns 1 if s1 is less than s2

   @param s1 the first string_utf8_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_utf8_is_less_than_cstring( string_utf8_t *s1, char_t *s2 );

/**
   string_utf8_is_greater_than

   Returns 1 if s1 is greater than s2

   @param s1 the first string_utf8_t instance
   @param s2 the first string_utf8_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_utf8_is_greater_than( string_utf8_t *s1, string_utf8_t *s2 );

/**
   string_utf8_is_greater_than_cstring

   Returns 1 if s1 is greater than s2

   @param s1 the first string_utf8_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_utf8_is_greater_than_cstring( string_utf8_t *s1, char_t *s2 );

/**
   string_utf8_has_substring

   Returns 1 if string contains the substring

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for in string
   @return 1 if string contains substring, 0 otherwise
*/
int32_t string_utf8_has_substring( string_utf8_t *current, string_utf8_t *substring );

/**
   string_utf8_has_substring_cstring

   Returns 1 if string contains the substring

   @param current the string_utf8_t instance
   @param substring the char_t * instance to look for in string
   @return 1 if string contains substring, 0 otherwise
*/
int32_t string_utf8_has_substring_cstring( string_utf8_t *current, char_t *substring );

/**
   string_utf8_starts_with

   Returns 1 if string starts with substring

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for at the start of string
   @return 1 if string starts with substring, 0 otherwise
*/
int32_t string_utf8_starts_with( string_utf8_t *current, string_utf8_t *substring );

/**
   string_utf8_starts_with_cstring

   Returns 1 if string starts with substring

   @param current the string_utf8_t instance
   @param substring the char_t instance to look for at the start of string
   @return 1 if string starts with substring, 0 otherwise
*/
int32_t string_utf8_starts_with_cstring( string_utf8_t *current, char_t *substring );

/**
   string_utf8_ends_with

   Returns 1 if string ends with substring

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for at the end of string
   @return 1 if string ends with substring, 0 otherwise
*/
int32_t string_utf8_ends_with( string_utf8_t *current, string_utf8_t *substring );

/**
   string_utf8_ends_with_cstring

   Returns 1 if string ends with substring

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for at the end of string
   @return 1 if string ends with substring, 0 otherwise
*/
int32_t string_utf8_ends_with_cstring( string_utf8_t *current, char_t *substring );

/**
   string_utf8_substring_index_in_bounds

   Returns index (first occurrence) where string contains substring between
   start and end indices. First index of string is 0.

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for in string
   @param start_index where to start looking in string
   @param end_index where to stop looking for substring in string
   @return index where string contains substring in specified range, -1 otherwise
*/
int32_t
string_utf8_substring_index_in_bounds
(
   string_utf8_t *current,
   string_utf8_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_utf8_substring_index_in_bounds_cstring

   Returns index (first occurrence) where string contains substring between
   start and end indices. First index of string is 0.

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for in string
   @param start_index where to start looking in string
   @param end_index where to stop looking for substring in string
   @return index where string contains substring in specified range, -1 otherwise
*/
int32_t
string_utf8_substring_index_in_bounds_cstring
(
   string_utf8_t *current,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_utf8_substring_index

   Returns index (first occurrence) where string contains substring. First
   index of string is 0.

   @param current the string_utf8_t instance
   @param substring the string_utf8_t instance to look for in string
   @return index where string contains substring, -1 otherwise
*/
int32_t
string_utf8_substring_index
(
   string_utf8_t *current,
   string_utf8_t *substring
);

/**
   string_utf8_substring_index_cstring

   Returns index (first occurrence) where string contains substring. First
   index of string is 0.

   @param current the string_utf8_t instance
   @param substring the char_t instance to look for in string
   @return index where string contains substring, -1 otherwise
*/
int32_t
string_utf8_substring_index_cstring
(
   string_utf8_t *current,
   char_t *substring
);


/*
   Conversion
*/

/**
   string_utf8_split

   Returns list of strings from original string separated by one or more
   characters in separators.

   @param current the string_utf8_t instance
   @param separators string of characters to look for in string to separate substrings
   @param count the number of substrings returned in the returned array
   @return array of strings from original string separated by separator character
           the last pointer in the array is NULL
*/
string_utf8_t **
string_utf8_split
(
   string_utf8_t *current,
   string_utf8_t *separators,
   int32_t *count
);

/**
   string_utf8_split_cstring

   Returns list of strings from original string separated by one or more
   characters in separators.

   @param current the string_utf8_t instance
   @param separators string of characters to look for in string to separate substrings
   @param count the number of substrings returned in the returned array
   @return array of strings from original string separated by separator character
           the last pointer in the array is NULL
*/
string_utf8_t **
string_utf8_split_cstring
(
   string_utf8_t *current,
   char_t *separators,
   int32_t *count
);

/**
   string_utf8_as_lower

   Returns new string that is original string with all uppercase letters
   changed to lowercase.

   @param current the string_utf8_t instance
   @return string with all lowercase letters
*/
string_utf8_t *string_utf8_as_lower( string_utf8_t *current );

/**
   string_utf8_as_upper

   Returns new string that is original string with all lowercase letters
   changed to uppercase.

   @param current the string_utf8_t instance
   @return string with all uppercase letters
*/
string_utf8_t *string_utf8_as_upper( string_utf8_t *current );

/**
   string_utf8_as_int32

   Returns int32 that is represented by string.

   @param current the string_utf8_t instance
   @return int32 as decoded from string
*/
int32_t string_utf8_as_int32( string_utf8_t *current );

/**
   string_utf8_as_float64

   Returns float64 that is represented by string.

   @param current the string_utf8_t instance
   @return float64 as decoded from string
*/
float64_t string_utf8_as_float64( string_utf8_t *current );


/*
   Element Change
*/

/**
   string_utf8_put

   Replaces character at specified index.

   @param current the string_utf8_t instance
   @param c the character (as a UTF-8 C string) to put
   @param index where to put the character c
*/
void string_utf8_put( string_utf8_t *current, char_t *c, int32_t index );

/**
   string_utf8_put_ascii

   Replaces character at specified index.

   @param current the string_utf8_t instance
   @param c the character (as a UTF-8 C string) to put
   @param index where to put the character c
*/
void string_utf8_put_ascii( string_utf8_t *current, char_t c, int32_t index );

/**
   string_utf8_put_utf16

   Replaces character at specified index.

   @param current the string_utf8_t instance
   @param c the character (as a UTF-16 C string) to put
   @param index where to put the character c
*/
void string_utf8_put_utf16( string_utf8_t *current, utf16_t c, int32_t index );

/**
   string_utf8_put_utf32

   Replaces character at specified index.

   @param current the string_utf8_t instance
   @param c the character (as a UTF-32 character) to put
   @param index where to put the character c
*/
void string_utf8_put_utf32( string_utf8_t *current, utf32_t c, int32_t index );

/**
   string_utf8_put_wchar

   Replaces character at specified index.

   @param current the string_utf8_t instance
   @param c the character (as a wchar_t character) to put
   @param index where to put the character c
*/
void string_utf8_put_wchar( string_utf8_t *current, wchar_t c, int32_t index );

/**
   string_utf8_replace

   Replaces string contents between specified indices.

   @param current the string_utf8_t instance
   @param substring the substring to put in string
   @param start_index where to start putting the substring in string
   @param end_index where to stop putting the substring in string
*/
void
string_utf8_replace
(
   string_utf8_t *current,
   string_utf8_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_utf8_replace_cstring

   Replaces string contents between specified indices.

   @param current the string_utf8_t instance
   @param substring the substring to put in string
   @param start_index where to start putting the substring in string
   @param end_index where to stop putting the substring in string
*/
void
string_utf8_replace_cstring
(
   string_utf8_t *current,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_utf8_replace_all

   Replaces all occurrences of substring in string with specified replacement.

   @param current the string_utf8_t instance
   @param substring_utf8_original the substring to find in string
   @param substring_utf8_new the substring to replace the original in string
*/
void
string_utf8_replace_all
(
   string_utf8_t *current,
   string_utf8_t *substring_original,
   string_utf8_t *substring_new
);

/**
   string_utf8_replace_all_cstring

   Replaces all occurrences of substring in string with specified replacement.

   @param current the string_utf8_t instance
   @param substring_utf8_original the substring to find in string
   @param substring_utf8_new the substring to replace the original in string
*/
void
string_utf8_replace_all_cstring
(
   string_utf8_t *current,
   string_utf8_t *substring_utf8_original,
   char_t *substring_utf8_new
);

/**
   string_utf8_replace_all_cstring2

   Replaces all occurrences of substring in string with specified replacement.

   @param current the string_utf8_t instance
   @param substring_utf8_original the substring to find in string
   @param substring_utf8_new the substring to replace the original in string
*/
void
string_utf8_replace_all_cstring2
(
   string_utf8_t *current,
   char_t *substring_utf8_original,
   char_t *substring_utf8_new
);

/**
   string_utf8_append

   Concatenate a string to the end of a string

   @param current the string_utf8_t instance
   @param s the string_utf8_t instance to append to the end of string
*/
void string_utf8_append( string_utf8_t *current, string_utf8_t *s );

/**
   string_utf8_append_cstring

   Concatenate a char_t * string to the end of a string

   @param current the string_utf8_t instance
   @param s the string_utf8_t instance to append to the end of string
*/
void string_utf8_append_cstring( string_utf8_t *current, char_t *s );

/**
   string_utf8_prepend

   Concatenate a string to the beginning of a string

   @param current the string_utf8_t instance
   @param s the string_utf8_t instance to prepend to the beginning of string
*/
void string_utf8_prepend( string_utf8_t *current, string_utf8_t *s );

/**
   string_utf8_prepend_cstring

   Concatenate a string to the beginning of a string

   @param current the string_utf8_t instance
   @param s the char_t instance to prepend to the beginning of string
*/
void string_utf8_prepend_cstring( string_utf8_t *current, char_t *s );

/**
   string_utf8_insert

   Insert a string into a string at specified index

   @param current the string_utf8_t instance
   @param s the string_utf8_t instance to insert into string
   @param index where to insert s into string
*/
void
string_utf8_insert
(
   string_utf8_t *current,
   string_utf8_t *substring,
   int32_t index
);

/**
   string_utf8_insert_cstring

   Insert a string into a string at specified index

   @param current the string_utf8_t instance
   @param s the char_t instance to insert into string
   @param index where to insert s into string
*/
void
string_utf8_insert_cstring
(
   string_utf8_t *current,
   char_t *substring,
   int32_t index
);

/**
   string_utf8_append_character

   Concatenate a character to the end of a string

   @param current the string_utf8_t instance
   @param c the character (as a UTF-8 string) to append to the end of string
*/
void string_utf8_append_character( string_utf8_t *current, char_t *c );

/**
   string_utf8_append_character_ascii

   Concatenate a character to the end of a string

   @param current the string_utf8_t instance
   @param c the ASCII character to append to the end of string
*/
void string_utf8_append_character_ascii( string_utf8_t *current, char_t c );

/**
   string_utf8_append_character_utf16

   Concatenate a character to the end of a string

   @param current the string_utf8_t instance
   @param c the character (as a UTF-16 string) to append to the end of string
*/
void string_utf8_append_character_utf16( string_utf8_t *current, utf16_t c );

/**
   string_utf8_append_character_utf32

   Concatenate a character to the end of a string

   @param current the string_utf8_t instance
   @param c the character (as a UTF-32 character) to append to the end of string
*/
void string_utf8_append_character_utf32( string_utf8_t *current, utf32_t c );

/**
   string_utf8_append_character_wchar

   Concatenate a character to the end of a string

   @param current the string_utf8_t instance
   @param c the character (as a wchar_t character) to append to the end of string
*/
void string_utf8_append_character_wchar( string_utf8_t *current, wchar_t c );

/**
   string_utf8_prepend_character

   Concatenate a UTF-8 character as a string to the beginning of a string

   @param current the string_utf8_t instance
   @param c the character (as a UTF-8 string) to prepend to the beginning of string
*/
void string_utf8_prepend_character( string_utf8_t *current, char_t *c );

/**
   string_utf8_prepend_character_ascii

   Concatenate an ASCII character to the beginning of a string

   @param current the string_utf8_t instance
   @param c the ASCII character to prepend to the beginning of string
*/
void string_utf8_prepend_character_ascii( string_utf8_t *current, char_t c );

/**
   string_utf8_prepend_character_utf16

   Concatenate a string to the beginning of a string

   @param current the string_utf8_t instance
   @param s the character (as a UTF-16 string) to prepend to the beginning of string
*/
void string_utf8_prepend_character_utf16( string_utf8_t *current, utf16_t c );

/**
   string_utf8_prepend_character_utf32

   Concatenate a string to the beginning of a string

   @param current the string_utf8_t instance
   @param s the character (as a UTF-32 character) to prepend to the beginning of string
*/
void string_utf8_prepend_character_utf32( string_utf8_t *current, utf32_t c );

/**
   string_utf8_prepend_character_wchar

   Concatenate a string to the beginning of a string

   @param current the string_utf8_t instance
   @param s the character (as a wchar_t character) to prepend to the beginning of string
*/
void string_utf8_prepend_character_wchar( string_utf8_t *current, wchar_t c );


/**
   string_utf8_insert_character

   Insert a character into a string at specified index

   @param current the string_utf8_t instance
   @param c the character to insert into string
   @param index where to insert c (as a UTF-8 string) into string
*/
void string_utf8_insert_character( string_utf8_t *current, char_t *c, int32_t index );

/**
   string_utf8_insert_character_ascii

   Insert an ASCII character into a string at specified index

   @param current the string_utf8_t instance
   @param c the ASCII character to insert into string
   @param index where to insert c into string
*/
void string_utf8_insert_character_ascii( string_utf8_t *current, char_t c, int32_t index );

/**
   string_utf8_insert_character_utf16

   Insert a character into a string at specified index

   @param current the string_utf8_t instance
   @param c the character to insert into string
   @param index where to insert c (as a UTF-16 string) into string
*/
void string_utf8_insert_character_utf16( string_utf8_t *current, utf16_t
      c, int32_t index );

/**
   string_utf8_insert_character_utf32

   Insert a character into a string at specified index

   @param current the string_utf8_t instance
   @param c the character to insert into string
   @param index where to insert c (as a UTF-32 string) into string
*/
void string_utf8_insert_character_utf32( string_utf8_t *current, utf32_t c, int32_t index );

/**
   string_utf8_insert_character_wchar

   Insert a character into a string at specified index

   @param current the string_utf8_t instance
   @param c the character to insert into string
   @param index where to insert c (as a wchar_t string) into string
*/
void string_utf8_insert_character_wchar( string_utf8_t *current, wchar_t c, int32_t index );

/**
   string_utf8_insert_int32

   Insert string version of int32 into a string at specified index

   @param current the string_utf8_t instance
   @param i the int32 to insert into string
   @param index where to insert i into string
*/
void string_utf8_insert_int32( string_utf8_t *current, int32_t i, int32_t index );

/**
   string_utf8_insert_float64

   Insert string version of float64 into a string at specified index

   @param current the string_utf8_t instance
   @param f the float64 to insert into string
   @param index where to insert f into string
*/
void string_utf8_insert_float64( string_utf8_t *current, float64_t f, int32_t index );

/**
   string_utf8_to_lower

   Modify string to convert uppercase letters to lowercase letters

   @param current the string_utf8_t instance
*/
void string_utf8_to_lower( string_utf8_t *current );

/**
   string_utf8_to_upper

   Modify string to convert lowercase letters to uppercase letters

   @param current the string_utf8_t instance
*/
void string_utf8_to_upper( string_utf8_t *current );


/*
   Duplication
*/

/**
   string_utf8_substring

   Return a new string_utf8_t instance that contains the same characters as string
   between the specified indices.

   @param current the string_utf8_t instance
   @param start_index the index in string to start the new string_utf8_t instance
   @param end_index the index in string to end the new string_utf8_t instance
   @return string_utf8_t instance having the substring from string between the specified indices
*/
string_utf8_t *string_utf8_substring( string_utf8_t *current, int32_t start_index, int32_t end_index );

/**
   string_utf8_copy

   Return a new string_utf8_t instance that contains the same characters as string.

   @param current the string_utf8_t instance
   @return string_utf8_t instance having the same content as string
*/
string_utf8_t *string_utf8_copy( string_utf8_t *current );


/*
   Removal
*/

/**
   string_utf8_remove

   Remove a character from string at the specified index.

   @param current the string_utf8_t instance
*/
void string_utf8_remove( string_utf8_t *current, int32_t index );

/**
   string_utf8_remove_substring

   Remove a substring from string at the specified indices.

   @param current the string_utf8_t instance
   @param start_index the index in string to start removing characters
   @param stop_index the index in string to stop removing characters
*/
void string_utf8_remove_substring( string_utf8_t *current, int32_t start_index, int32_t end_index );

/**
   string_utf8_keep_head

   Reduce the length of the string by eliminating characters from its
   end so that count characters remain in the string.

   @param current the string_utf8_t instance
   @param count the length of string after removing characters from its end
*/
void string_utf8_keep_head( string_utf8_t *current, int32_t count );

/**
   string_utf8_keep_tail

   Reduce the length of the string by eliminating characters from its
   start so that count characters remain in the string.

   @param current the string_utf8_t instance
   @param count the length of string after removing characters from its end
*/
void string_utf8_keep_tail( string_utf8_t *current, int32_t count );

/**
   string_utf8_remove_head

   Reduce the length of the string by eliminating count characters from its
   start.

   @param current the string_utf8_t instance
   @param count the number of characters to remove
*/
void string_utf8_remove_head( string_utf8_t *current, int32_t count );

/**
   string_utf8_remove_tail

   Reduce the length of the string by eliminating count characters from its
   end.

   @param current the string_utf8_t instance
   @param count the number of characters to remove
*/
void string_utf8_remove_tail( string_utf8_t *current, int32_t count );

/**
   string_utf8_wipe_out

   Set the string count to zero, making it the empty string. Do not change the
   string's capacity.

   @param current the string_utf8_t instance
*/
void string_utf8_wipe_out( string_utf8_t *current );


/*
   Resize
*/

/**
   string_utf8_resize

   Set the string capacity to new_capacity. Do not change the count or the
   string's contents.

   @param current the string_utf8_t instance
   @param new_capacity the new number of characters of storage in string.
*/
void string_utf8_resize( string_utf8_t *current, int32_t new_capacity );


#ifdef __cplusplus
}
#endif

#endif /* STRING_UTF8_T_H */

/* End of file */





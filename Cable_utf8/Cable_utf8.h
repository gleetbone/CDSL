/**
 @file Cable_utf8.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Character strings implemented as a binary search tree of substrings"

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

 Function declarations for the opaque cable_utf8_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CABLE_UTF8_T_H
#define CABLE_UTF8_T_H


/**
   Includes
*/

#include <wchar.h>
#include "base.h"

/**
   Structure declaration
*/

struct cable_utf8_struct;

/**
   Structure typedef
*/

typedef struct cable_utf8_struct cable_utf8_t;
typedef uint16_t utf16_t;
typedef uint32_t utf32_t;


/*
   Initialization
*/

/**
   cable_utf8_make

   Create and initialize a cable_utf8_t instance.
   Content will be the empty cable_utf8.

   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make( void );

/**
   cable_utf8_make_from

   Create and initialize a cable_utf8_t instance.
   Content will be a copy of "cable_utf8".

   @param str the cable_utf8_t instance to initialize from
   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make_from( cable_utf8_t *cable_utf8 );

/**
   cable_utf8_make_from_cstring

   Create and initialize a cable_utf8_t instance.
   Content will be a copy of "str".

   @param str the C cable_utf8 to initialize from
   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make_from_cstring( char_t *str );


/*
   Disposal
*/

/**
   cable_utf8_dispose

   Deallocates a cable_utf8_t instance.

   @param cable_utf8 the C cable_utf8 to dispose
*/
void
cable_utf8_dispose( cable_utf8_t **cable_utf8 );


/*
   Access
*/


/**
   cable_utf8_item

   Returns the character in cable_utf8 at "index". Indexing starts at 0.

   @param cable_utf8 the cable_utf8_t instance
   @param index the index to retrieve from
   @return the character in cable_utf8 at index
*/
char_t *
cable_utf8_item( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_item_ascii

   Returns the character in cable_utf8 at "index". Indexing starts at 0.

   @param cable_utf8 the cable_utf8_t instance
   @param index the index to retrieve from
   @return the character in cable_utf8 at index
*/
char_t
cable_utf8_item_ascii( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_item_utf16

   Returns the character in cable_utf8 at "index". Indexing starts at 0.

   @param cable_utf8 the cable_utf8_t instance
   @param index the index to retrieve from
   @return the character in cable_utf8 at index
*/
utf16_t *
cable_utf8_item_utf16( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_item_utf32

   Returns the character in cable_utf8 at "index". Indexing starts at 0.

   @param cable_utf8 the cable_utf8_t instance
   @param index the index to retrieve from
   @return the character in cable_utf8 at index
*/
utf32_t
cable_utf8_item_utf32( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_item_wchar

   Returns the character in cable_utf8 at "index". Indexing starts at 0.

   @param cable_utf8 the cable_utf8_t instance
   @param index the index to retrieve from
   @return the character in cable_utf8 at index
*/
wchar_t
cable_utf8_item_wchar( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_as_cstring

   Returns the contents of cable_utf8 as a char_t array. To dispose of the return
   value, free() it.

   @param cable_utf8 the cable_utf8_t instance
   @return pointer to array of the characters in cable_utf8
*/
char_t *
cable_utf8_as_cstring( cable_utf8_t *cable_utf8 );


/*
   Measurement
*/

/**
   cable_utf8_byte_count

   Returns the number of bytes used to store characters in cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @return number of bytes in cable_utf8
*/
int32_t
cable_utf8_byte_count( cable_utf8_t *cable_utf8 );

/**
   cable_utf8_count

   Returns the number of characters in cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @return number of characters in cable_utf8
*/
int32_t
cable_utf8_count( cable_utf8_t *cable_utf8 );


/*
   Status Report
*/

/**
   cable_utf8_is_empty

   Returns 1 if the cable_utf8 content is the empty cable_utf8, 0 otherwise.

   @param cable_utf8 the cable_utf8_t instance
   @return 1 if empty, 0 otherwise
*/

int32_t
cable_utf8_is_empty( cable_utf8_t *cable_utf8 );

/**
   cable_utf8_valid_index

   Returns 1 if the index is greater or equal to zero and less or equal
   to the count of characters in the cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @return 1 if index OK, 0 otherwise
*/
int32_t
cable_utf8_valid_index( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_has

   Returns 1 if the cable_utf8 contains the character c.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to search for
   @return 1 if c present in cable_utf8, 0 otherwise
*/
int32_t
cable_utf8_has( cable_utf8_t *cable_utf8, char_t *c );

/**
   cable_utf8_has_ascii

   Returns 1 if the cable_utf8 contains the character c.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to search for
   @return 1 if c present in cable_utf8, 0 otherwise
*/
int32_t
cable_utf8_has_ascii( cable_utf8_t *cable_utf8, char_t c );

/**
   cable_utf8_has_utf16

   Returns 1 if the cable_utf8 contains the character c.

   @param cable_utf8 the cable_utf8_t instance
   @param cp pointer to the (possibly multiword) character to search for
   @return 1 if c present in cable_utf8, 0 otherwise
*/
int32_t
cable_utf8_has_utf16( cable_utf8_t *cable_utf8, utf16_t *cp );

/**
   cable_utf8_has_utf32

   Returns 1 if the cable_utf8 contains the character c.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to search for
   @return 1 if c present in cable_utf8, 0 otherwise
*/
int32_t
cable_utf8_has_utf32( cable_utf8_t *cable_utf8, utf32_t c );

/**
   cable_utf8_has_wchar

   Returns 1 if the cable_utf8 contains the character c.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to search for
   @return 1 if c present in cable_utf8, 0 otherwise
*/
int32_t
cable_utf8_has_wchar( cable_utf8_t *cable_utf8, wchar_t c );

/**
   cable_utf8_hash_code

   Returns hash code of the cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @return hash code
*/
int32_t
cable_utf8_hash_code( cable_utf8_t *cable_utf8 );


/*
   Comparison
*/

/**
   cable_utf8_is_equal

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first cable_utf8_t instance
   @param s2 the first cable_utf8_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_utf8_is_equal( cable_utf8_t *s1, cable_utf8_t *s2 );
/**
   cable_utf8_is_equal_cstring

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first cable_utf8_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_utf8_is_equal_cstring( cable_utf8_t *s1, char_t *s2 );

/**
   cable_utf8_is_less_than

   Returns 1 if s1 is less than s2

   @param s1 the first cable_utf8_t instance
   @param s2 the first cable_utf8_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_utf8_is_less_than( cable_utf8_t *s1, cable_utf8_t *s2 );

/**
   cable_utf8_is_less_than_cstring

   Returns 1 if s1 is less than s2

   @param s1 the first cable_utf8_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_utf8_is_less_than_cstring( cable_utf8_t *s1, char_t *s2 );

/**
   cable_utf8_is_greater_than

   Returns 1 if s1 is greater than s2

   @param s1 the first cable_utf8_t instance
   @param s2 the first cable_utf8_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_utf8_is_greater_than( cable_utf8_t *s1, cable_utf8_t *s2 );

/**
   cable_utf8_is_greater_than_cstring

   Returns 1 if s1 is greater than s2

   @param s1 the first cable_utf8_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_utf8_is_greater_than_cstring( cable_utf8_t *s1, char_t *s2 );

/**
   cable_utf8_has_substring

   Returns 1 if cable_utf8 contains the substring

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for in cable_utf8
   @return 1 if cable_utf8 contains substring, 0 otherwise
*/
int32_t cable_utf8_has_substring( cable_utf8_t *cable_utf8, cable_utf8_t *substring );

/**
   cable_utf8_has_substring_cstring

   Returns 1 if cable_utf8 contains the substring

   @param cable_utf8 the cable_utf8_t instance
   @param substring the char_t * instance to look for in cable_utf8
   @return 1 if cable_utf8 contains substring, 0 otherwise
*/
int32_t cable_utf8_has_substring_cstring( cable_utf8_t *cable_utf8, char_t *substring );

/**
   cable_utf8_starts_with

   Returns 1 if cable_utf8 starts with substring

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for at the start of cable_utf8
   @return 1 if cable_utf8 starts with substring, 0 otherwise
*/
int32_t cable_utf8_starts_with( cable_utf8_t *cable_utf8, cable_utf8_t *substring );

/**
   cable_utf8_starts_with_cstring

   Returns 1 if cable_utf8 starts with substring

   @param cable_utf8 the cable_utf8_t instance
   @param substring the char_t instance to look for at the start of cable_utf8
   @return 1 if cable_utf8 starts with substring, 0 otherwise
*/
int32_t cable_utf8_starts_with_cstring( cable_utf8_t *cable_utf8, char_t *substring );

/**
   cable_utf8_ends_with

   Returns 1 if cable_utf8 ends with substring

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for at the end of cable_utf8
   @return 1 if cable_utf8 ends with substring, 0 otherwise
*/
int32_t cable_utf8_ends_with( cable_utf8_t *cable_utf8, cable_utf8_t *substring );

/**
   cable_utf8_ends_with_cstring

   Returns 1 if cable_utf8 ends with substring

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for at the end of cable_utf8
   @return 1 if cable_utf8 ends with substring, 0 otherwise
*/
int32_t cable_utf8_ends_with_cstring( cable_utf8_t *cable_utf8, char_t *substring );

/**
   cable_utf8_substring_index_in_bounds

   Returns index (first occurrence) where cable_utf8 contains substring between
   start and end indices. First index of cable_utf8 is 0.

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for in cable_utf8
   @param start_index where to start looking in cable_utf8
   @param end_index where to stop looking for substring in cable_utf8
   @return index where cable_utf8 contains substring in specified range, -1 otherwise
*/
int32_t
cable_utf8_substring_index_in_bounds
(
   cable_utf8_t *cable_utf8,
   cable_utf8_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_utf8_substring_index_in_bounds_cstring

   Returns index (first occurrence) where cable_utf8 contains substring between
   start and end indices. First index of cable_utf8 is 0.

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for in cable_utf8
   @param start_index where to start looking in cable_utf8
   @param end_index where to stop looking for substring in cable_utf8
   @return index where cable_utf8 contains substring in specified range, -1 otherwise
*/
int32_t
cable_utf8_substring_index_in_bounds_cstring
(
   cable_utf8_t *cable_utf8,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_utf8_substring_index

   Returns index (first occurrence) where cable_utf8 contains substring. First
   index of cable_utf8 is 0.

   @param cable_utf8 the cable_utf8_t instance
   @param substring the cable_utf8_t instance to look for in cable_utf8
   @return index where cable_utf8 contains substring, -1 otherwise
*/
int32_t cable_utf8_substring_index( cable_utf8_t *cable_utf8, cable_utf8_t *substring );

/**
   cable_utf8_substring_index_cstring

   Returns index (first occurrence) where cable_utf8 contains substring. First
   index of cable_utf8 is 0.

   @param cable_utf8 the cable_utf8_t instance
   @param substring the char_t instance to look for in cable_utf8
   @return index where cable_utf8 contains substring, -1 otherwise
*/
int32_t cable_utf8_substring_index_cstring( cable_utf8_t *cable_utf8, char_t *substring );


/*
   Conversion
*/

/**
   cable_utf8_split

   Returns list of cable_utf8s from original cable_utf8 separated by one or more
   characters in separators. Each cable_utf8 in the return array must be freed with
   cable_utf8_dispose(), and the array should be disposed with free().

   @param cable_utf8 the cable_utf8_t instance
   @param separators cable_utf8 of characters to look for in cable_utf8 to separate substrings
   @param count the number of substrings returned in the returned array
   @return array of cable_utf8s from original cable_utf8 separated by separator character
           the last pointer in the array is NULL
*/
cable_utf8_t **cable_utf8_split( cable_utf8_t *cable_utf8, char_t *separators, int32_t *count );

/**
   cable_utf8_as_lower

   Returns new cable_utf8 that is original cable_utf8 with all uppercase letters
   changed to lowercase in index range.

   @param cable_utf8 the cable_utf8_t instance
   @param start_index where to start looking in cable_utf8
   @param end_index where to stop looking for substring in cable_utf8
   @return cable_utf8 with all lowercase letters
*/
cable_utf8_t *cable_utf8_as_lower( cable_utf8_t *cable_utf8, int32_t start_index, int32_t end_index );

/**
   cable_utf8_as_upper

   Returns new cable_utf8 that is original cable_utf8 with all lowercase letters
   changed to uppercase in index range.

   @param cable_utf8 the cable_utf8_t instance
   @param start_index where to start looking in cable_utf8
   @param end_index where to stop looking for substring in cable_utf8
   @return cable_utf8 with all uppercase letters
*/
cable_utf8_t *cable_utf8_as_upper( cable_utf8_t *cable_utf8, int32_t start_index, int32_t end_index );


/*
   Element Change
*/

/**
   cable_utf8_put

   Replaces character at specified index.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to put
   @param index where to put the character c
*/
void cable_utf8_put( cable_utf8_t *cable_utf8, char_t *c, int32_t index );

/**
   cable_utf8_put_ascii

   Replaces character at specified index.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to put
   @param index where to put the character c
*/
void cable_utf8_put_ascii( cable_utf8_t *cable_utf8, char_t c, int32_t index );

/**
   cable_utf8_put_utf16

   Replaces character at specified index.

   @param cable_utf8 the cable_utf8_t instance
   @param cp pointer to the (possibly multiword) character to put
   @param index where to put the character c
*/
void cable_utf8_put_utf16( cable_utf8_t *cable_utf8, utf16_t *cp, int32_t index );

/**
   cable_utf8_put_utf32

   Replaces character at specified index.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to put
   @param index where to put the character c
*/
void cable_utf8_put_utf32( cable_utf8_t *cable_utf8, utf32_t c, int32_t index );

/**
   cable_utf8_put_wchar

   Replaces character at specified index.

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to put
   @param index where to put the character c
*/
void cable_utf8_put_wchar( cable_utf8_t *cable_utf8, wchar_t c, int32_t index );

/**
   cable_utf8_replace

   Replaces cable_utf8 contents between specified indices.

   @param cable_utf8 the cable_utf8_t instance
   @param substring the substring to put in cable_utf8
   @param start_index where to start putting the substring in cable_utf8
   @param end_index where to stop putting the substring in cable_utf8
*/
void
cable_utf8_replace
(
   cable_utf8_t *cable_utf8,
   cable_utf8_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_utf8_replace_cstring

   Replaces cable_utf8 contents between specified indices.

   @param cable_utf8 the cable_utf8_t instance
   @param substring the substring to put in cable_utf8
   @param start_index where to start putting the substring in cable_utf8
   @param end_index where to stop putting the substring in cable_utf8
*/
void
cable_utf8_replace_cstring
(
   cable_utf8_t *cable_utf8,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_utf8_replace_all

   Replaces all occurrences of substring in cable_utf8 with specified replacement.

   @param cable_utf8 the cable_utf8_t instance
   @param substring_original the substring to find in cable_utf8
   @param substring_new the substring to replace the original in cable_utf8
*/
void
cable_utf8_replace_all
(
   cable_utf8_t *cable_utf8,
   cable_utf8_t *substring_original,
   cable_utf8_t *substring_new
);

/**
   cable_utf8_replace_all_cstring

   Replaces all occurrences of substring in cable_utf8 with specified replacement.

   @param cable_utf8 the cable_utf8_t instance
   @param substring_original the substring to find in cable_utf8
   @param substring_new the substring to replace the original in cable_utf8
*/
void
cable_utf8_replace_all_cstring
(
   cable_utf8_t *cable_utf8,
   char_t *substring_original,
   char_t *substring_new
);

/**
   cable_utf8_append

   Concatenate a cable_utf8 to the end of a cable_utf8

   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to append to the end of cable_utf8
*/
void cable_utf8_append( cable_utf8_t *cable_utf8, cable_utf8_t *s );

/**
   cable_utf8_append_destructive

   Concatenate a cable_utf8 to the end of a cable_utf8. The cable_utf8 that is appended
   is destroyed.

   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to append to the end of cable_utf8, will be destroyed
*/
void cable_utf8_append_destructive( cable_utf8_t *cable_utf8, cable_utf8_t **s );

/**
   cable_utf8_append_cstring

   Concatenate a char_t * cable_utf8 to the end of a cable_utf8

   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to append to the end of cable_utf8
*/
void cable_utf8_append_cstring( cable_utf8_t *cable_utf8, char_t *s );

/**
   cable_utf8_prepend

   Concatenate a cable_utf8 to the beginning of a cable_utf8

   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to prepend to the beginning of cable_utf8
*/
void cable_utf8_prepend( cable_utf8_t *cable_utf8, cable_utf8_t *s );

/**
   cable_utf8_prepend_destructive

   Concatenate a cable_utf8 to the beginning of a cable_utf8. The cable_utf8 that is prepended
   is destroyed.


   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to prepend to the beginning of cable_utf8
*/
void cable_utf8_prepend_destructive( cable_utf8_t *cable_utf8, cable_utf8_t **s );

/**
   cable_utf8_prepend_cstring

   Concatenate a cable_utf8 to the beginning of a cable_utf8

   @param cable_utf8 the cable_utf8_t instance
   @param s the char_t instance to prepend to the beginning of cable_utf8
*/
void cable_utf8_prepend_cstring( cable_utf8_t *cable_utf8, char_t *s );

/**
   cable_utf8_insert

   Insert a cable_utf8 into a cable_utf8 at specified index

   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to insert into cable_utf8
   @param index where to insert s into cable_utf8
*/
void cable_utf8_insert( cable_utf8_t *cable_utf8, cable_utf8_t *substring, int32_t index );

/**
   cable_utf8_insert_destructive

   Insert a cable_utf8 into a cable_utf8 at specified index. The cable_utf8 that is prepended
   is destroyed.

   @param cable_utf8 the cable_utf8_t instance
   @param s the cable_utf8_t instance to insert into cable_utf8
   @param index where to insert s into cable_utf8
*/
void cable_utf8_insert_destructive( cable_utf8_t *cable_utf8, cable_utf8_t **substring, int32_t index );

/**
   cable_utf8_insert_cstring

   Insert a cable_utf8 into a cable_utf8 at specified index

   @param cable_utf8 the cable_utf8_t instance
   @param s the char_t instance to insert into cable_utf8
   @param index where to insert s into cable_utf8
*/
void cable_utf8_insert_cstring( cable_utf8_t *cable_utf8, char_t *substring, int32_t index );

/**
   cable_utf8_append_character

   Concatenate a character to the end of a cable_utf8

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to append to the end of cable_utf8
*/
void cable_utf8_append_character( cable_utf8_t *cable_utf8, char_t *c );

/**
   cable_utf8_prepend_character

   Concatenate a character to the beginning of a cable_utf8

   @param cable_utf8 the cable_utf8_t instance
   @param s the character to prepend to the beginning of cable_utf8
*/
void cable_utf8_prepend_character( cable_utf8_t *cable_utf8, char_t *c );


/**
   cable_utf8_insert_character

   Insert a character into a cable_utf8 at specified index

   @param cable_utf8 the cable_utf8_t instance
   @param c the character to insert into cable_utf8
   @param index where to insert c into cable_utf8
*/
void cable_utf8_insert_character( cable_utf8_t *cable_utf8, char_t *c, int32_t index );

/**
   cable_utf8_to_lower

   Modify cable_utf8 to convert uppercase letters to lowercase letters

   @param cable_utf8 the cable_utf8_t instance
   @param start_index where to start looking in cable_utf8
   @param end_index where to stop looking for substring in cable_utf8
*/
void cable_utf8_to_lower( cable_utf8_t *cable_utf8, int32_t start_index, int32_t end_index );

/**
   cable_utf8_to_upper

   Modify cable_utf8 to convert lowercase letters to uppercase letters

   @param cable_utf8 the cable_utf8_t instance
   @param start_index where to start looking in cable_utf8
   @param end_index where to stop looking for substring in cable_utf8
*/
void cable_utf8_to_upper( cable_utf8_t *cable_utf8, int32_t start_index, int32_t end_index );


/*
   Duplication
*/

/**
   cable_utf8_substring

   Return a new cable_utf8_t instance that contains the same characters as cable_utf8
   between the specified indices.

   @param cable_utf8 the cable_utf8_t instance
   @param start_index the index in cable_utf8 to start the new cable_utf8_t instance
   @param end_index the index in cable_utf8 to end the new cable_utf8_t instance
   @return cable_utf8_t instance having the substring from cable_utf8 between the specified indices
*/
cable_utf8_t *cable_utf8_substring( cable_utf8_t *cable_utf8, int32_t start_index, int32_t end_index );

/**
   cable_utf8_copy

   Return a new cable_utf8_t instance that contains the same characters as cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @return cable_utf8_t instance having the same content as cable_utf8
*/
cable_utf8_t *cable_utf8_copy( cable_utf8_t *cable_utf8 );


/*
   Removal
*/

/**
   cable_utf8_remove

   Remove a character from cable_utf8 at the specified index.

   @param cable_utf8 the cable_utf8_t instance
*/
void cable_utf8_remove( cable_utf8_t *cable_utf8, int32_t index );

/**
   cable_utf8_remove_substring

   Remove a substring from cable_utf8 at the specified indices.

   @param cable_utf8 the cable_utf8_t instance
   @param start_index the index in cable_utf8 to start removing characters
   @param end_index the index in cable_utf8 to stop removing characters
*/
void cable_utf8_remove_substring( cable_utf8_t *cable_utf8, int32_t start_index, int32_t end_index );

/**
   cable_utf8_keep_head

   Reduce the length of the cable_utf8 by eliminating characters from its
   end so that count characters remain in the cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @param count the length of cable_utf8 after removing characters from its end
*/
void cable_utf8_keep_head( cable_utf8_t *cable_utf8, int32_t count );

/**
   cable_utf8_keep_tail

   Reduce the length of the cable_utf8 by eliminating characters from its
   start so that count characters remain in the cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
   @param count the length of cable_utf8 after removing characters from its end
*/
void cable_utf8_keep_tail( cable_utf8_t *cable_utf8, int32_t count );

/**
   cable_utf8_remove_head

   Reduce the length of the cable_utf8 by eliminating count characters from its
   start.

   @param cable_utf8 the cable_utf8_t instance
   @param count the number of characters to remove
*/
void cable_utf8_remove_head( cable_utf8_t *cable_utf8, int32_t count );

/**
   cable_utf8_remove_tail

   Reduce the length of the cable_utf8 by eliminating count characters from its
   end.

   @param cable_utf8 the cable_utf8_t instance
   @param count the number of characters to remove
*/
void cable_utf8_remove_tail( cable_utf8_t *cable_utf8, int32_t count );

/**
   cable_utf8_wipe_out

   Set the cable_utf8 count to zero, making it the empty cable_utf8.

   @param cable_utf8 the cable_utf8_t instance
*/
void cable_utf8_wipe_out( cable_utf8_t *cable_utf8 );


/*
   Resize
*/

/**
   cable_utf8_reclaim

   Attempt to reclaim unused storage from the cable_utf8. Do not change the count or the
   cable_utf8's contents.

   @param cable_utf8 the cable_utf8_t instance
*/
void cable_utf8_reclaim( cable_utf8_t *cable_utf8 );


#ifdef __cplusplus
}
#endif

#endif /* CABLE_UTF8_T_H */

/* End of file */





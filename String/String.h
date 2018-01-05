/**
 @file String.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Character Strings (non-unicode)"
 
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

 Function declarations for the opaque string_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STRING_T_H
#define STRING_T_H


/**
   Includes
*/

#include "base.h"

/**
   Structure declaration
*/

struct string_struct;

/**
   Structure typedef
*/

typedef struct string_struct string_t;


/**
   Initialization
*/

/**
   string_make

   Create and initialize a string_t instance.
   Content will be the empty string and the capacity will be 1.

   @return pointer to the new data structure
*/
string_t *
string_make( void );

/**
   string_make_n

   Create and initialize a string_t instance.
   Content will be the empty string and the capacity will be "capacity".

   @return pointer to the new data structure
*/
string_t *
string_make_n( int32_t capacity );

/**
   string_make_from

   Create and initialize a string_t instance.
   Content will be a copy of "str" and the capacity will
   be str's count + 1.

   @param str the string_t instance to initialize from
   @return pointer to the new data structure
*/
string_t *
string_make_from( string_t *string );

/**
   string_make_from_cstring

   Create and initialize a string_t instance.
   Content will be a copy of "str" and the capacity will
   be len( str ) + 1.

   @param str the C string to initialize from
   @return pointer to the new data structure
*/
string_t *
string_make_from_cstring( char_t *str );


/**
   Disposal
*/

/**
   string_dispose

   Deallocates a string_t instance. Does not deallocate the char_t * string 
   being held.

   @param string the C string to dispose
*/
void
string_dispose( string_t *string );

/**
   string_dispose_with_contents

   Deallocates a string_t instance and its internal char_t * string.

   @param string the C string to dispose
*/
void
string_dispose_with_contents( string_t *string );


/**
   Access
*/


/**
   string_item

   Returns the character in string at "index". Indexing starts at 0.

   @param string the string_t instance
   @param index the index to retrieve from
   @return the character in string at index
*/
char_t
string_item( string_t *string, int32_t index );

/**
   string_as_cstring

   Returns the contents of string as a char_t pointer.

   @param string the string_t instance
   @return pointer to the characters in string
*/
char_t *
string_as_cstring( string_t *string );


/**
   Measurement
*/

/**
   string_count

   Returns the number of characters in string.

   @param string the string_t instance
   @return number of characters in string
*/
int32_t
string_count( string_t *string );

/**
   string_capacity

   Returns the number of available characters in string
   for storage. May be greater than count.

   @param string the string_t instance
   @return number of characters available for storage in string
*/
int32_t
string_capacity( string_t *string );


/**
   Status Report
*/

/**
   string_is_empty

   Returns 1 if the string content is the empty string, 0 otherwise.

   @param string the string_t instance
   @return 1 if empty, 0 otherwise
*/

int32_t
string_is_empty( string_t *string );

/**
   string_valid_index

   Returns 1 if the index is greater or equal to zero and less or equal
   to the count of characters in the string.

   @param string the string_t instance
   @return 1 if index OK, 0 otherwise
*/
int32_t
string_valid_index( string_t *string, int32_t index );

/**
   string_has

   Returns 1 if the string contains the character c.

   @param string the string_t instance
   @param c the character to search for
   @return 1 if c present in string, 0 otherwise
*/
int32_t
string_has( string_t *string, char_t c );

/**
   string_is_int32

   Returns 1 if the string can be parsed into an int32_t.

   @param string the string_t instance
   @return 1 if string is an int32_t, 0 otherwise
*/
int32_t
string_is_int32( string_t *string );

/**
   string_is_float64

   Returns 1 if the string can be parsed into an float64_t.

   @param string the string_t instance
   @return 1 if string is an float64_t, 0 otherwise
*/
int32_t
string_is_float64( string_t *string );

/**
   string_hash_code

   Returns hash code of the string.

   @param string the string_t instance
   @return hash code
*/
int32_t
string_hash_code( string_t *string );


/**
   Comparison
*/

/**
   string_is_equal

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first string_t instance
   @param s2 the first string_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_is_equal( string_t *s1, string_t *s2 );

/**
   string_is_equal_cstring

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first string_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_is_equal_cstring( string_t *s1, char_t *s2 );

/**
   string_is_less_than

   Returns 1 if s1 is less than s2

   @param s1 the first string_t instance
   @param s2 the first string_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_is_less_than( string_t *s1, string_t *s2 );

/**
   string_is_less_than_cstring

   Returns 1 if s1 is less than s2

   @param s1 the first string_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_is_less_than_cstring( string_t *s1, char_t *s2 );

/**
   string_is_greater_than

   Returns 1 if s1 is greater than s2

   @param s1 the first string_t instance
   @param s2 the first string_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_is_greater_than( string_t *s1, string_t *s2 );

/**
   string_is_greater_than_cstring

   Returns 1 if s1 is greater than s2

   @param s1 the first string_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t string_is_greater_than_cstring( string_t *s1, char_t *s2 );

/**
   string_has_substring

   Returns 1 if string contains the substring

   @param string the string_t instance
   @param substring the string_t instance to look for in string
   @return 1 if string contains substring, 0 otherwise
*/
int32_t string_has_substring( string_t *string, string_t *substring );

/**
   string_has_substring_cstring

   Returns 1 if string contains the substring

   @param string the string_t instance
   @param substring the char_t * instance to look for in string
   @return 1 if string contains substring, 0 otherwise
*/
int32_t string_has_substring_cstring( string_t *string, char_t *substring );

/**
   string_starts_with

   Returns 1 if string starts with substring

   @param string the string_t instance
   @param substring the string_t instance to look for at the start of string
   @return 1 if string starts with substring, 0 otherwise
*/
int32_t string_starts_with( string_t *string, string_t *substring );

/**
   string_starts_with_cstring

   Returns 1 if string starts with substring

   @param string the string_t instance
   @param substring the char_t instance to look for at the start of string
   @return 1 if string starts with substring, 0 otherwise
*/
int32_t string_starts_with_cstring( string_t *string, char_t *substring );

/**
   string_ends_with

   Returns 1 if string ends with substring

   @param string the string_t instance
   @param substring the string_t instance to look for at the end of string
   @return 1 if string ends with substring, 0 otherwise
*/
int32_t string_ends_with( string_t *string, string_t *substring );

/**
   string_ends_with_cstring

   Returns 1 if string ends with substring

   @param string the string_t instance
   @param substring the string_t instance to look for at the end of string
   @return 1 if string ends with substring, 0 otherwise
*/
int32_t string_ends_with_cstring( string_t *string, char_t *substring );

/**
   string_substring_index_in_bounds

   Returns index (first occurrence) where string contains substring between
   start and end indices. First index of string is 0.

   @param string the string_t instance
   @param substring the string_t instance to look for in string
   @param start_index where to start looking in string
   @param end_index where to stop looking for substring in string
   @return index where string contains substring in specified range, -1 otherwise
*/
int32_t
string_substring_index_in_bounds
(
   string_t *string,
   string_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_substring_index_in_bounds_cstring

   Returns index (first occurrence) where string contains substring between
   start and end indices. First index of string is 0.

   @param string the string_t instance
   @param substring the string_t instance to look for in string
   @param start_index where to start looking in string
   @param end_index where to stop looking for substring in string
   @return index where string contains substring in specified range, -1 otherwise
*/
int32_t
string_substring_index_in_bounds_cstring
(
   string_t *string,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_substring_index

   Returns index (first occurrence) where string contains substring. First
   index of string is 0.

   @param string the string_t instance
   @param substring the string_t instance to look for in string
   @return index where string contains substring, -1 otherwise
*/
int32_t string_substring_index( string_t *string, string_t *substring );

/**
   string_substring_index_cstring

   Returns index (first occurrence) where string contains substring. First
   index of string is 0.

   @param string the string_t instance
   @param substring the char_t instance to look for in string
   @return index where string contains substring, -1 otherwise
*/
int32_t string_substring_index_cstring( string_t *string, char_t *substring );


/**
   Conversion
*/

/**
   string_split

   Returns list of strings from original string separated by one or more
   characters in separators.

   @param string the string_t instance
   @param separators string of characters to look for in string to separate substrings
   @param count the number of substrings returned in the returned array
   @return array of strings from original string separated by separator character
           the last pointer in the array is NULL
*/
string_t **string_split( string_t *string, string_t *separators, int32_t *count );

/**
   string_split_cstring

   Returns list of strings from original string separated by one or more
   characters in separators.

   @param string the string_t instance
   @param separators string of characters to look for in string to separate substrings
   @param count the number of substrings returned in the returned array
   @return array of strings from original string separated by separator character
           the last pointer in the array is NULL
*/
string_t **string_split_cstring( string_t *string, char_t *separators, int32_t *count );

/**
   string_as_lower

   Returns new string that is original string with all uppercase letters
   changed to lowercase.

   @param string the string_t instance
   @return string with all lowercase letters
*/
string_t *string_as_lower( string_t *string );

/**
   string_as_upper

   Returns new string that is original string with all lowercase letters
   changed to uppercase.

   @param string the string_t instance
   @return string with all uppercase letters
*/
string_t *string_as_upper( string_t *string );

/**
   string_as_int32

   Returns int32 that is represented by string.

   @param string the string_t instance
   @return int32 as decoded from string
*/
int32_t string_as_int32( string_t *string );

/**
   string_as_float64

   Returns float64 that is represented by string.

   @param string the string_t instance
   @return float64 as decoded from string
*/
float64_t string_as_float64( string_t *string );


/**
   Element Change
*/

/**
   string_put

   Replaces character at specified index.

   @param string the string_t instance
   @param c the character to put
   @param index where to put the character c
*/
void string_put( string_t *string, char_t c, int32_t index );

/**
   string_replace

   Replaces string contents between specified indices.

   @param string the string_t instance
   @param substring the substring to put in string
   @param start_index where to start putting the substring in string
   @param end_index where to stop putting the substring in string
*/
void
string_replace
(
   string_t *string,
   string_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_replace_cstring

   Replaces string contents between specified indices.

   @param string the string_t instance
   @param substring the substring to put in string
   @param start_index where to start putting the substring in string
   @param end_index where to stop putting the substring in string
*/
void
string_replace_cstring
(
   string_t *string,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   string_replace_all

   Replaces all occurrences of substring in string with specified replacement.

   @param string the string_t instance
   @param substring_original the substring to find in string
   @param substring_new the substring to replace the original in string
*/
void
string_replace_all
(
   string_t *string,
   string_t *substring_original,
   string_t *substring_new
);

/**
   string_replace_all_cstring

   Replaces all occurrences of substring in string with specified replacement.

   @param string the string_t instance
   @param substring_original the substring to find in string
   @param substring_new the substring to replace the original in string
*/
void
string_replace_all_cstring
(
   string_t *string,
   string_t *substring_original,
   char_t *substring_new
);

/**
   string_replace_all_cstring2

   Replaces all occurrences of substring in string with specified replacement.

   @param string the string_t instance
   @param substring_original the substring to find in string
   @param substring_new the substring to replace the original in string
*/
void
string_replace_all_cstring2
(
   string_t *string,
   char_t *substring_original,
   char_t *substring_new
);

/**
   string_append

   Concatenate a string to the end of a string

   @param string the string_t instance
   @param s the string_t instance to append to the end of string
*/
void string_append( string_t *string, string_t *s );

/**
   string_append_cstring

   Concatenate a char_t * string to the end of a string

   @param string the string_t instance
   @param s the string_t instance to append to the end of string
*/
void string_append_cstring( string_t *string, char_t *s );

/**
   string_prepend

   Concatenate a string to the beginning of a string

   @param string the string_t instance
   @param s the string_t instance to prepend to the beginning of string
*/
void string_prepend( string_t *string, string_t *s );

/**
   string_prepend_cstring

   Concatenate a string to the beginning of a string

   @param string the string_t instance
   @param s the char_t instance to prepend to the beginning of string
*/
void string_prepend_cstring( string_t *string, char_t *s );

/**
   string_insert

   Insert a string into a string at specified index

   @param string the string_t instance
   @param s the string_t instance to insert into string
   @param index where to insert s into string
*/
void string_insert( string_t *string, string_t *substring, int32_t index );

/**
   string_insert_cstring

   Insert a string into a string at specified index

   @param string the string_t instance
   @param s the char_t instance to insert into string
   @param index where to insert s into string
*/
void string_insert_cstring( string_t *string, char_t *substring, int32_t index );

/**
   string_append_character

   Concatenate a string to the end of a string

   @param string the string_t instance
   @param c the character to append to the end of string
*/
void string_append_character( string_t *string, char_t c );

/**
   string_prepend_character

   Concatenate a string to the beginning of a string

   @param string the string_t instance
   @param s the character to prepend to the beginning of string
*/
void string_prepend_character( string_t *string, char_t c );


/**
   string_insert_character

   Insert a character into a string at specified index

   @param string the string_t instance
   @param c the character to insert into string
   @param index where to insert c into string
*/
void string_insert_character( string_t *string, char_t c, int32_t index );

/**
   string_insert_int32

   Insert string version of int32 into a string at specified index

   @param string the string_t instance
   @param i the int32 to insert into string
   @param index where to insert i into string
*/
void string_insert_int32( string_t *string, int32_t i, int32_t index );

/**
   string_insert_float64

   Insert string version of float64 into a string at specified index

   @param string the string_t instance
   @param f the float64 to insert into string
   @param index where to insert f into string
*/
void string_insert_float64( string_t *string, float64_t f, int32_t index );

/**
   string_to_lower

   Modify string to convert uppercase letters to lowercase letters

   @param string the string_t instance
*/
void string_to_lower( string_t *string );

/**
   string_to_upper

   Modify string to convert lowercase letters to uppercase letters

   @param string the string_t instance
*/
void string_to_upper( string_t *string );


/**
   Duplication
*/

/**
   string_substring

   Return a new string_t instance that contains the same characters as string
   between the specified indices.

   @param string the string_t instance
   @param start_index the index in string to start the new string_t instance
   @param end_index the index in string to end the new string_t instance
   @return string_t instance having the substring from string between the specified indices
*/
string_t *string_substring( string_t *string, int32_t start_index, int32_t end_index );

/**
   string_copy

   Return a new string_t instance that contains the same characters as string.

   @param string the string_t instance
   @return string_t instance having the same content as string
*/
string_t *string_copy( string_t *string );


/**
   Removal
*/

/**
   string_remove

   Remove a character from string at the specified index.

   @param string the string_t instance
*/
void string_remove( string_t *string, int32_t index );

/**
   string_remove_substring

   Remove a substring from string at the specified indices.

   @param string the string_t instance
   @param start_index the index in string to start removing characters
   @param stop_index the index in string to stop removing characters
*/
void string_remove_substring( string_t *string, int32_t start_index, int32_t end_index );

/**
   string_keep_head

   Reduce the length of the string by eliminating characters from its
   end so that count characters remain in the string.

   @param string the string_t instance
   @param count the length of string after removing characters from its end
*/
void string_keep_head( string_t *string, int32_t count );

/**
   string_keep_tail

   Reduce the length of the string by eliminating characters from its
   start so that count characters remain in the string.

   @param string the string_t instance
   @param count the length of string after removing characters from its end
*/
void string_keep_tail( string_t *string, int32_t count );

/**
   string_remove_head

   Reduce the length of the string by eliminating count characters from its
   start.

   @param string the string_t instance
   @param count the number of characters to remove
*/
void string_remove_head( string_t *string, int32_t count );

/**
   string_remove_tail

   Reduce the length of the string by eliminating count characters from its
   end.

   @param string the string_t instance
   @param count the number of characters to remove
*/
void string_remove_tail( string_t *string, int32_t count );

/**
   string_wipe_out

   Set the string count to zero, making it the empty string. Do not change the
   string's capacity.

   @param string the string_t instance
*/
void string_wipe_out( string_t *string );


/**
   Resize
*/

/**
   string_resize

   Set the string capacity to new_capacity. Do not change the count or the
   string's contents.

   @param string the string_t instance
   @param new_capacity the new number of characters of storage in string.
*/
void string_resize( string_t *string, int32_t new_capacity );


#ifdef __cplusplus
}
#endif

#endif /* STRING_T_H */

/* End of file */





/**
 @file Cable.h
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

 Function declarations for the opaque cable_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CABLE_T_H
#define CABLE_T_H


/**
   Includes
*/

#include "base.h"

/**
   Structure declaration
*/

struct cable_struct;

/**
   Structure typedef
*/

typedef struct cable_struct cable_t;


/*
   Initialization
*/

/**
   cable_make

   Create and initialize a cable_t instance.
   Content will be the empty cable.

   @return pointer to the new data structure
*/
cable_t *
cable_make( void );

/**
   cable_make_from

   Create and initialize a cable_t instance.
   Content will be a copy of "cable".

   @param str the cable_t instance to initialize from
   @return pointer to the new data structure
*/
cable_t *
cable_make_from( cable_t *cable );

/**
   cable_make_from_cstring

   Create and initialize a cable_t instance.
   Content will be a copy of "str".

   @param str the C cable to initialize from
   @return pointer to the new data structure
*/
cable_t *
cable_make_from_cstring( char_t *str );


/*
   Disposal
*/

/**
   cable_dispose

   Deallocates a cable_t instance.

   @param cable the C cable to dispose
*/
void
cable_dispose( cable_t **cable );


/*
   Access
*/


/**
   cable_item

   Returns the character in cable at "index". Indexing starts at 0.

   @param cable the cable_t instance
   @param index the index to retrieve from
   @return the character in cable at index
*/
char_t
cable_item( cable_t *cable, int32_t index );

/**
   cable_as_cstring

   Returns the contents of cable as a char_t array. To dispose of the return
   value, free() it.

   @param cable the cable_t instance
   @return pointer to array of the characters in cable
*/
char_t *
cable_as_cstring( cable_t *cable );


/*
   Measurement
*/

/**
   cable_count

   Returns the number of characters in cable.

   @param cable the cable_t instance
   @return number of characters in cable
*/
int32_t
cable_count( cable_t *cable );


/*
   Status Report
*/

/**
   cable_is_empty

   Returns 1 if the cable content is the empty cable, 0 otherwise.

   @param cable the cable_t instance
   @return 1 if empty, 0 otherwise
*/

int32_t
cable_is_empty( cable_t *cable );

/**
   cable_valid_index

   Returns 1 if the index is greater or equal to zero and less or equal
   to the count of characters in the cable.

   @param cable the cable_t instance
   @return 1 if index OK, 0 otherwise
*/
int32_t
cable_valid_index( cable_t *cable, int32_t index );

/**
   cable_has

   Returns 1 if the cable contains the character c.

   @param cable the cable_t instance
   @param c the character to search for
   @return 1 if c present in cable, 0 otherwise
*/
int32_t
cable_has( cable_t *cable, char_t c );

/**
   cable_hash_code

   Returns hash code of the cable.

   @param cable the cable_t instance
   @return hash code
*/
int32_t
cable_hash_code( cable_t *cable );


/*
   Comparison
*/

/**
   cable_is_equal

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first cable_t instance
   @param s2 the first cable_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_is_equal( cable_t *s1, cable_t *s2 );
/**
   cable_is_equal_cstring

   Returns 1 if the s1 contains the same characters as s2

   @param s1 the first cable_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_is_equal_cstring( cable_t *s1, char_t *s2 );

/**
   cable_is_less_than

   Returns 1 if s1 is less than s2

   @param s1 the first cable_t instance
   @param s2 the first cable_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_is_less_than( cable_t *s1, cable_t *s2 );

/**
   cable_is_less_than_cstring

   Returns 1 if s1 is less than s2

   @param s1 the first cable_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_is_less_than_cstring( cable_t *s1, char_t *s2 );

/**
   cable_is_greater_than

   Returns 1 if s1 is greater than s2

   @param s1 the first cable_t instance
   @param s2 the first cable_t instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_is_greater_than( cable_t *s1, cable_t *s2 );

/**
   cable_is_greater_than_cstring

   Returns 1 if s1 is greater than s2

   @param s1 the first cable_t instance
   @param s2 the second char_t * instance
   @return 1 if s1 is equal to s2, 0 otherwise
*/
int32_t cable_is_greater_than_cstring( cable_t *s1, char_t *s2 );

/**
   cable_has_substring

   Returns 1 if cable contains the substring

   @param cable the cable_t instance
   @param substring the cable_t instance to look for in cable
   @return 1 if cable contains substring, 0 otherwise
*/
int32_t cable_has_substring( cable_t *cable, cable_t *substring );

/**
   cable_has_substring_cstring

   Returns 1 if cable contains the substring

   @param cable the cable_t instance
   @param substring the char_t * instance to look for in cable
   @return 1 if cable contains substring, 0 otherwise
*/
int32_t cable_has_substring_cstring( cable_t *cable, char_t *substring );

/**
   cable_starts_with

   Returns 1 if cable starts with substring

   @param cable the cable_t instance
   @param substring the cable_t instance to look for at the start of cable
   @return 1 if cable starts with substring, 0 otherwise
*/
int32_t cable_starts_with( cable_t *cable, cable_t *substring );

/**
   cable_starts_with_cstring

   Returns 1 if cable starts with substring

   @param cable the cable_t instance
   @param substring the char_t instance to look for at the start of cable
   @return 1 if cable starts with substring, 0 otherwise
*/
int32_t cable_starts_with_cstring( cable_t *cable, char_t *substring );

/**
   cable_ends_with

   Returns 1 if cable ends with substring

   @param cable the cable_t instance
   @param substring the cable_t instance to look for at the end of cable
   @return 1 if cable ends with substring, 0 otherwise
*/
int32_t cable_ends_with( cable_t *cable, cable_t *substring );

/**
   cable_ends_with_cstring

   Returns 1 if cable ends with substring

   @param cable the cable_t instance
   @param substring the cable_t instance to look for at the end of cable
   @return 1 if cable ends with substring, 0 otherwise
*/
int32_t cable_ends_with_cstring( cable_t *cable, char_t *substring );

/**
   cable_substring_index_in_bounds

   Returns index (first occurrence) where cable contains substring between
   start and end indices. First index of cable is 0.

   @param cable the cable_t instance
   @param substring the cable_t instance to look for in cable
   @param start_index where to start looking in cable
   @param end_index where to stop looking for substring in cable
   @return index where cable contains substring in specified range, -1 otherwise
*/
int32_t
cable_substring_index_in_bounds
(
   cable_t *cable,
   cable_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_substring_index_in_bounds_cstring

   Returns index (first occurrence) where cable contains substring between
   start and end indices. First index of cable is 0.

   @param cable the cable_t instance
   @param substring the cable_t instance to look for in cable
   @param start_index where to start looking in cable
   @param end_index where to stop looking for substring in cable
   @return index where cable contains substring in specified range, -1 otherwise
*/
int32_t
cable_substring_index_in_bounds_cstring
(
   cable_t *cable,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_substring_index

   Returns index (first occurrence) where cable contains substring. First
   index of cable is 0.

   @param cable the cable_t instance
   @param substring the cable_t instance to look for in cable
   @return index where cable contains substring, -1 otherwise
*/
int32_t cable_substring_index( cable_t *cable, cable_t *substring );

/**
   cable_substring_index_cstring

   Returns index (first occurrence) where cable contains substring. First
   index of cable is 0.

   @param cable the cable_t instance
   @param substring the char_t instance to look for in cable
   @return index where cable contains substring, -1 otherwise
*/
int32_t cable_substring_index_cstring( cable_t *cable, char_t *substring );


/*
   Conversion
*/

/**
   cable_split

   Returns list of cables from original cable separated by one or more
   characters in separators. Each cable in the return array must be freed with
   cable_dispose(), and the array should be disposed with free().

   @param cable the cable_t instance
   @param separators cable of characters to look for in cable to separate substrings
   @param count the number of substrings returned in the returned array
   @return array of cables from original cable separated by separator character
           the last pointer in the array is NULL
*/
cable_t **cable_split( cable_t *cable, char_t *separators, int32_t *count );

/**
   cable_as_lower

   Returns new cable that is original cable with all uppercase letters
   changed to lowercase in index range.

   @param cable the cable_t instance
   @param start_index where to start looking in cable
   @param end_index where to stop looking for substring in cable
   @return cable with all lowercase letters
*/
cable_t *cable_as_lower( cable_t *cable, int32_t start_index, int32_t end_index );

/**
   cable_as_upper

   Returns new cable that is original cable with all lowercase letters
   changed to uppercase in index range.

   @param cable the cable_t instance
   @param start_index where to start looking in cable
   @param end_index where to stop looking for substring in cable
   @return cable with all uppercase letters
*/
cable_t *cable_as_upper( cable_t *cable, int32_t start_index, int32_t end_index );


/*
   Element Change
*/

/**
   cable_put

   Replaces character at specified index.

   @param cable the cable_t instance
   @param c the character to put
   @param index where to put the character c
*/
void cable_put( cable_t *cable, char_t c, int32_t index );

/**
   cable_replace

   Replaces cable contents between specified indices.

   @param cable the cable_t instance
   @param substring the substring to put in cable
   @param start_index where to start putting the substring in cable
   @param end_index where to stop putting the substring in cable
*/
void
cable_replace
(
   cable_t *cable,
   cable_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_replace_cstring

   Replaces cable contents between specified indices.

   @param cable the cable_t instance
   @param substring the substring to put in cable
   @param start_index where to start putting the substring in cable
   @param end_index where to stop putting the substring in cable
*/
void
cable_replace_cstring
(
   cable_t *cable,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
);

/**
   cable_replace_all

   Replaces all occurrences of substring in cable with specified replacement.

   @param cable the cable_t instance
   @param substring_original the substring to find in cable
   @param substring_new the substring to replace the original in cable
*/
void
cable_replace_all
(
   cable_t *cable,
   cable_t *substring_original,
   cable_t *substring_new
);

/**
   cable_replace_all_cstring

   Replaces all occurrences of substring in cable with specified replacement.

   @param cable the cable_t instance
   @param substring_original the substring to find in cable
   @param substring_new the substring to replace the original in cable
*/
void
cable_replace_all_cstring
(
   cable_t *cable,
   char_t *substring_original,
   char_t *substring_new
);

/**
   cable_append

   Concatenate a cable to the end of a cable

   @param cable the cable_t instance
   @param s the cable_t instance to append to the end of cable
*/
void cable_append( cable_t *cable, cable_t *s );

/**
   cable_append_destructive

   Concatenate a cable to the end of a cable. The cable that is appended
   is destroyed.

   @param cable the cable_t instance
   @param s the cable_t instance to append to the end of cable, will be destroyed
*/
void cable_append_destructive( cable_t *cable, cable_t **s );

/**
   cable_append_cstring

   Concatenate a char_t * cable to the end of a cable

   @param cable the cable_t instance
   @param s the cable_t instance to append to the end of cable
*/
void cable_append_cstring( cable_t *cable, char_t *s );

/**
   cable_prepend

   Concatenate a cable to the beginning of a cable

   @param cable the cable_t instance
   @param s the cable_t instance to prepend to the beginning of cable
*/
void cable_prepend( cable_t *cable, cable_t *s );

/**
   cable_prepend_destructive

   Concatenate a cable to the beginning of a cable. The cable that is prepended
   is destroyed.


   @param cable the cable_t instance
   @param s the cable_t instance to prepend to the beginning of cable
*/
void cable_prepend_destructive( cable_t *cable, cable_t **s );

/**
   cable_prepend_cstring

   Concatenate a cable to the beginning of a cable

   @param cable the cable_t instance
   @param s the char_t instance to prepend to the beginning of cable
*/
void cable_prepend_cstring( cable_t *cable, char_t *s );

/**
   cable_insert

   Insert a cable into a cable at specified index

   @param cable the cable_t instance
   @param s the cable_t instance to insert into cable
   @param index where to insert s into cable
*/
void cable_insert( cable_t *cable, cable_t *substring, int32_t index );

/**
   cable_insert_destructive

   Insert a cable into a cable at specified index. The cable that is prepended
   is destroyed.

   @param cable the cable_t instance
   @param s the cable_t instance to insert into cable
   @param index where to insert s into cable
*/
void cable_insert_destructive( cable_t *cable, cable_t **substring, int32_t index );

/**
   cable_insert_cstring

   Insert a cable into a cable at specified index

   @param cable the cable_t instance
   @param s the char_t instance to insert into cable
   @param index where to insert s into cable
*/
void cable_insert_cstring( cable_t *cable, char_t *substring, int32_t index );

/**
   cable_append_character

   Concatenate a character to the end of a cable

   @param cable the cable_t instance
   @param c the character to append to the end of cable
*/
void cable_append_character( cable_t *cable, char_t c );

/**
   cable_prepend_character

   Concatenate a character to the beginning of a cable

   @param cable the cable_t instance
   @param s the character to prepend to the beginning of cable
*/
void cable_prepend_character( cable_t *cable, char_t c );


/**
   cable_insert_character

   Insert a character into a cable at specified index

   @param cable the cable_t instance
   @param c the character to insert into cable
   @param index where to insert c into cable
*/
void cable_insert_character( cable_t *cable, char_t c, int32_t index );

/**
   cable_to_lower

   Modify cable to convert uppercase letters to lowercase letters

   @param cable the cable_t instance
   @param start_index where to start looking in cable
   @param end_index where to stop looking for substring in cable
*/
void cable_to_lower( cable_t *cable, int32_t start_index, int32_t end_index );

/**
   cable_to_upper

   Modify cable to convert lowercase letters to uppercase letters

   @param cable the cable_t instance
   @param start_index where to start looking in cable
   @param end_index where to stop looking for substring in cable
*/
void cable_to_upper( cable_t *cable, int32_t start_index, int32_t end_index );


/*
   Duplication
*/

/**
   cable_substring

   Return a new cable_t instance that contains the same characters as cable
   between the specified indices.

   @param cable the cable_t instance
   @param start_index the index in cable to start the new cable_t instance
   @param end_index the index in cable to end the new cable_t instance
   @return cable_t instance having the substring from cable between the specified indices
*/
cable_t *cable_substring( cable_t *cable, int32_t start_index, int32_t end_index );

/**
   cable_copy

   Return a new cable_t instance that contains the same characters as cable.

   @param cable the cable_t instance
   @return cable_t instance having the same content as cable
*/
cable_t *cable_copy( cable_t *cable );


/*
   Removal
*/

/**
   cable_remove

   Remove a character from cable at the specified index.

   @param cable the cable_t instance
*/
void cable_remove( cable_t *cable, int32_t index );

/**
   cable_remove_substring

   Remove a substring from cable at the specified indices.

   @param cable the cable_t instance
   @param start_index the index in cable to start removing characters
   @param end_index the index in cable to stop removing characters
*/
void cable_remove_substring( cable_t *cable, int32_t start_index, int32_t end_index );

/**
   cable_keep_head

   Reduce the length of the cable by eliminating characters from its
   end so that count characters remain in the cable.

   @param cable the cable_t instance
   @param count the length of cable after removing characters from its end
*/
void cable_keep_head( cable_t *cable, int32_t count );

/**
   cable_keep_tail

   Reduce the length of the cable by eliminating characters from its
   start so that count characters remain in the cable.

   @param cable the cable_t instance
   @param count the length of cable after removing characters from its end
*/
void cable_keep_tail( cable_t *cable, int32_t count );

/**
   cable_remove_head

   Reduce the length of the cable by eliminating count characters from its
   start.

   @param cable the cable_t instance
   @param count the number of characters to remove
*/
void cable_remove_head( cable_t *cable, int32_t count );

/**
   cable_remove_tail

   Reduce the length of the cable by eliminating count characters from its
   end.

   @param cable the cable_t instance
   @param count the number of characters to remove
*/
void cable_remove_tail( cable_t *cable, int32_t count );

/**
   cable_wipe_out

   Set the cable count to zero, making it the empty cable.

   @param cable the cable_t instance
*/
void cable_wipe_out( cable_t *cable );


/*
   Resize
*/

/**
   cable_reclaim

   Attempt to reclaim unused storage from the cable. Do not change the count or the
   cable's contents.

   @param cable the cable_t instance
*/
void cable_reclaim( cable_t *cable );


#ifdef __cplusplus
}
#endif

#endif /* CABLE_T_H */

/* End of file */





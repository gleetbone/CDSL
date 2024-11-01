/**
 @file AList.h
 @author Greg Lee
 @version 2.0.0
 @brief: "arrayed lists"

 @date: "$Mon Jan 01 15:22:40 PST 2018 @15 /Internet Time/$"

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

 Function declarations for the opaque AList_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define ALIST_VERSION_MAJOR 2
#define ALIST_VERSION_MINOR 0
#define ALIST_VERSION_PATCH 0

#define ALIST_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define ALIST_VERSION \
   ALIST_MAKE_VERSION( ALIST_VERSION_MAJOR, \
                       ALIST_VERSION_MINOR, \
                       ALIST_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Type   - the type of the value

   Macros that must be present (external to this file):

   VALUE_DEEP_DISPOSE_FUNCTION   -  deep disposes a value instance
   VALUE_DEEP_CLONE_FUNCTION     -  deep clones a value instance
   VALUE_DEEP_EQUAL_FUNCTION     -  returns 1 if two values are deep equal, 0 if not

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define AList_struct( arg ) PRIMITIVE_CAT( arg, _alist_struct )
#define AList_type( arg ) PRIMITIVE_CAT( arg, _alist_t )

#define AList_cursor_struct( arg ) PRIMITIVE_CAT( arg, _alist_cursor_struct )
#define AList_cursor_type( arg ) PRIMITIVE_CAT( arg, _alist_cursor_t )

/**
   Structure declarations
*/

struct AList_struct( Prefix );
struct AList_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct AList_struct( Prefix ) AList_type( Prefix );
typedef struct AList_cursor_struct( Prefix ) AList_cursor_type( Prefix );


/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   AList_make

   Return a new empty AList_t instance.

   @return AList_t instance
*/
#define AList_make( arg ) PRIMITIVE_CAT( arg, _alist_make )
AList_type( Prefix ) * AList_make( Prefix )( void );

/**
   AList_clone

   Return a new AList_t instance filled with the content of current. The value
   of the items in list are not duplicated.

   @param  current AList_t instance to copy from
   @return AList_t instance
*/
#define AList_clone( arg ) PRIMITIVE_CAT( arg, _alist_clone )
AList_type( Prefix ) * AList_clone( Prefix )( AList_type( Prefix ) *current );

/**
   AList_deep_clone

   Return a new AList_t instance filled with duplicates of the content of
   current. The value of the items in list are duplicated.

   @param  current AList_t instance to copy from
   @return AList_t instance
*/

#define AList_deep_clone( arg ) PRIMITIVE_CAT( arg, _alist_deep_clone )
AList_type( Prefix ) *
AList_deep_clone( Prefix )( AList_type( Prefix ) *current );

/**
   AList_is_equal

   Check that list contains same elements as other

   @param  current AList_t instance
   @param  other AList_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define AList_is_equal( arg ) PRIMITIVE_CAT( arg, _alist_is_equal )
int32_t
AList_is_equal( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_is_deep_equal

   Check that list contains same elements as other

   @param  current AList_t instance
   @param  other AList_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define AList_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _alist_is_deep_equal )
int32_t
AList_is_deep_equal( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_copy

   Copy other into current

   @param  current AList_t instance
   @param  other AList_t instance to copy from

*/

#define AList_copy( arg ) PRIMITIVE_CAT( arg, _alist_copy )
void
AList_copy( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_deep_copy

   Deep copy other into current

   @param  current AList_t instance
   @param  other AList_t instance to deep_copy from

*/

#define AList_deep_copy( arg ) PRIMITIVE_CAT( arg, _alist_deep_copy )
void
AList_deep_copy( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_make_from_array

   Return a new AList_t instance filled with the content of array. The value
   of the items in list are not duplicated.

   @param array array to copy from
   @param count the number of items in the array
   @return AList_t instance
*/

#define AList_make_from_array( arg ) PRIMITIVE_CAT( arg, _alist_make_from_array )
AList_type( Prefix ) * AList_make_from_array( Prefix )( Type *array, int32_t count );

/**
   AList_cursor_make

   Return a new empty AList_cursor_t instance.

   @param  current AList_t instance
   @return AList_cursor_t instance
*/
#define AList_cursor_make( arg ) PRIMITIVE_CAT( arg, _alist_cursor_make )
AList_cursor_type( Prefix ) * AList_cursor_make( Prefix )( AList_type( Prefix ) *current );


/*
   Disposal
*/

/**
   AList_dispose

   Free a AList_t instance. The value items are not disposed.

   @param  current pointer to AList_t instance
*/
#define AList_dispose( arg ) PRIMITIVE_CAT( arg, _alist_dispose )
void AList_dispose( Prefix )( AList_type( Prefix ) **current );

/**
   AList_deep_dispose

   Free a AList_t instance. The value items are disposed.

   @param  current pointer to AList_t instance
*/
#define AList_deep_dispose( arg ) PRIMITIVE_CAT( arg, _alist_deep_dispose )
void AList_deep_dispose( Prefix )( AList_type( Prefix ) **current );

/**
   AList_cursor_dispose

   Free a AList_cursor_t instance. Its associated list is not disposed.

   @param  cursor pointer to AList_cursor_t instance
*/
#define AList_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _alist_cursor_dispose )
void AList_cursor_dispose( Prefix )( AList_cursor_type( Prefix ) **cursor );


/*
   Access
*/

/**
   AList_cursor_item_at

   Return the value of the item pointed to by cursor.

   @param  cursor AList_cursor_t instance
   @return the value of the item pointed to by cursor
*/
#define AList_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _alist_cursor_item_at )
Type AList_cursor_item_at( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_item_at

   Return the value of the item pointed to by list's internal cursor.

   @param  list AList_t instance
   @return the value of the item pointed to by list's internal cursor
*/
#define AList_item_at( arg ) PRIMITIVE_CAT( arg, _alist_item_at )
Type AList_item_at( Prefix )( AList_type( Prefix ) *list );

/**
   AList_cursor_item_next

   Return the value of the next item pointed to by cursor.

   @param  cursor AList_cursor_t instance
   @return the value of the item pointed to by cursor
*/
#define AList_cursor_item_next( arg ) PRIMITIVE_CAT( arg, _alist_cursor_item_next )
Type AList_cursor_item_next( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_item_next

   Return the value of the next item pointed to by list's internal cursor.

   @param  current AList_t instance
   @return the value of the item pointed to by list's internal cursor
*/
#define AList_item_next( arg ) PRIMITIVE_CAT( arg, _alist_item_next )
Type AList_item_next( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_item_prev

   Return the value of the previous item pointed to by cursor.

   @param  cursor AList_cursor_t instance
   @return the value of the item pointed to by cursor
*/
#define AList_cursor_item_prev( arg ) PRIMITIVE_CAT( arg, _alist_cursor_item_prev )
Type AList_cursor_item_prev( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_item_prev

   Return the value of the previous item pointed to by list's internal cursor.

   @param  current AList_t instance
   @return the value of the item pointed to by list's internal cursor
*/
#define AList_item_prev( arg ) PRIMITIVE_CAT( arg, _alist_item_prev )
Type AList_item_prev( Prefix )( AList_type( Prefix ) *current );

/**
   AList_item

   Return the value of the ith item in the list.

   @param  current AList_t instance
   @param  index index of requested item
   @return the value of the item pointed to by list's internal cursor
*/
#define AList_item( arg ) PRIMITIVE_CAT( arg, _alist_item )
Type AList_item( Prefix )( AList_type( Prefix ) *current, int32_t index );

/**
   AList_first

   Return the value of the first item in the list.

   @param  current AList_t instance
   @return the value of the first item
*/
#define AList_first( arg ) PRIMITIVE_CAT( arg, _alist_first )
Type AList_first( Prefix )( AList_type( Prefix ) *current );

/**
   AList_last

   Return the value of the last item in the list.

   @param  current AList_t instance
   @return the value of the last item
*/
#define AList_last( arg ) PRIMITIVE_CAT( arg, _alist_last )
Type AList_last( Prefix )( AList_type( Prefix ) *current );

/**
   AList_as_array

   Return an array of the values contained in the list. The array does not contain
   a copy of the values, it contains the values themselves.

   @param  current AList_t instance
   @param  count pointer to returned count of items in the array
   @return array of the items in the list. must be freed with free()
*/
#define AList_as_array( arg ) PRIMITIVE_CAT( arg, _alist_as_array )
Type * AList_as_array( Prefix )( AList_type( Prefix ) *current, int32_t *count );


/*
   Measurement
*/

/**
   AList_count

   Return the number of items in the list.

   @param  current AList_t instance
   @return the number of items in the list
*/
#define AList_count( arg ) PRIMITIVE_CAT( arg, _alist_count )
int32_t AList_count( Prefix )( AList_type( Prefix ) *current );


/*
   Status report
*/

/**
   AList_off

   Returns 1 if the list's internal cursor is off, otherwise 0.

   @param  current AList_t instance
   @return 1 if internal cursor is off, 0 otherwise
*/
#define AList_off( arg ) PRIMITIVE_CAT( arg, _alist_off )
int32_t AList_off( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_off

   Returns 1 if the cursor is off, otherwise 0.

   @param  cursor AList_cursor_t instance
   @return 1 if cursor is off, 0 otherwise
*/
#define AList_cursor_off( arg ) PRIMITIVE_CAT( arg, _alist_cursor_off )
int32_t AList_cursor_off( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_is_first

   Returns 1 if the list's internal cursor is is_first, otherwise 0.

   @param  current AList_t instance
   @return 1 if internal cursor is is_first, 0 otherwise
*/
#define AList_is_first( arg ) PRIMITIVE_CAT( arg, _alist_is_first )
int32_t AList_is_first( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_is_first

   Returns 1 if the cursor is is_first, otherwise 0.

   @param  cursor AList_cursor_t instance
   @return 1 if cursor is is_first, 0 otherwise
*/
#define AList_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _alist_cursor_is_first )
int32_t AList_cursor_is_first( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_is_last

   Returns 1 if the list's internal cursor is is_last, otherwise 0.

   @param  current AList_t instance
   @return 1 if internal cursor is is_last, 0 otherwise
*/
#define AList_is_last( arg ) PRIMITIVE_CAT( arg, _alist_is_last )
int32_t AList_is_last( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_is_last

   Returns 1 if the cursor is is_last, otherwise 0.

   @param  cursor AList_cursor_t instance
   @return 1 if cursor is is_last, 0 otherwise
*/
#define AList_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _alist_cursor_is_last )
int32_t AList_cursor_is_last( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_is_empty

   Returns 1 if the list contains no items.

   @param  current AList_t instance
   @return 1 if list is empty, 0 otherwise
*/
#define AList_is_empty( arg ) PRIMITIVE_CAT( arg, _alist_is_empty )
int32_t AList_is_empty( Prefix )( AList_type( Prefix ) *current );

/**
   AList_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  current AList_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define AList_index( arg ) PRIMITIVE_CAT( arg, _alist_index )
int32_t AList_index( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  cursor AList_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define AList_cursor_index( arg ) PRIMITIVE_CAT( arg, _alist_cursor_index )
int32_t AList_cursor_index( Prefix )( AList_cursor_type( Prefix ) *cursor );

/*
   Cursor movement
*/

/**
   AList_forth

   Moves the list's internal cursor to the next item in the list.

   @param  current AList_t instance
*/
#define AList_forth( arg ) PRIMITIVE_CAT( arg, _alist_forth )
void AList_forth( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_forth

   Moves the cursor to the next item in the list.

   @param  cursor AList_cursor_t instance
*/
#define AList_cursor_forth( arg ) PRIMITIVE_CAT( arg, _alist_cursor_forth )
void AList_cursor_forth( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_back

   Moves the list's internal cursor to the previous item in the list.

   @param  current AList_t instance
*/
#define AList_back( arg ) PRIMITIVE_CAT( arg, _alist_back )
void AList_back( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_back

   Moves the cursor to the previous item in the list.

   @param  cursor AList_cursor_t instance
*/
#define AList_cursor_back( arg ) PRIMITIVE_CAT( arg, _alist_cursor_back )
void AList_cursor_back( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_go

   Moves the list's internal cursor to the ith item in the list. The first
   index is 0.

   @param  current AList_t instance
   @param  index the requested list position
*/
#define AList_go( arg ) PRIMITIVE_CAT( arg, _alist_go )
void AList_go( Prefix )( AList_type( Prefix ) *current, int32_t index );

/**
   AList_cursor_go

   Moves the cursor to the ith item in the list. The first index is 0.

   @param  cursor AList_cursor_t instance
   @param  index the requested list position
*/
#define AList_cursor_go( arg ) PRIMITIVE_CAT( arg, _alist_cursor_go )
void AList_cursor_go( Prefix )( AList_cursor_type( Prefix ) *cursor, int32_t index );

/**
   AList_start

   Moves the list's internal cursor to the first item in the list.

   @param  current AList_t instance
*/
#define AList_start( arg ) PRIMITIVE_CAT( arg, _alist_start )
void AList_start( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_start

   Moves the cursor to the first item in the list.

   @param  cursor AList_cursor_t instance
*/
#define AList_cursor_start( arg ) PRIMITIVE_CAT( arg, _alist_cursor_start )
void AList_cursor_start( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_finish

   Moves the list's internal cursor to the last item in the list.

   @param  current AList_t instance
*/
#define AList_finish( arg ) PRIMITIVE_CAT( arg, _alist_finish )
void AList_finish( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_finish

   Moves the cursor to the last item in the list.

   @param  cursor AList_cursor_t instance
*/
#define AList_cursor_finish( arg ) PRIMITIVE_CAT( arg, _alist_cursor_finish )
void AList_cursor_finish( Prefix )( AList_cursor_type( Prefix ) *cursor );


/*
   Element change
*/

/**
   AList_put

   Insert value at index.

   @param  current AList_t instance
   @param  value what to insert
   @param  index where to insert value
*/
#define AList_put( arg ) PRIMITIVE_CAT( arg, _alist_put )
void AList_put( Prefix )( AList_type( Prefix ) *current, Type value, int32_t index );

/**
   AList_put_right

   Insert value to right of list's internal cursor's position.

   @param  current AList_t instance
   @param  value what to insert
*/
#define AList_put_right( arg ) PRIMITIVE_CAT( arg, _alist_put_right )
void AList_put_right( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_cursor_put_right

   Insert value to right of cursor's position.

   @param  cursor AList_cursor_t instance
   @param  value what to insert
*/
#define AList_cursor_put_right( arg ) PRIMITIVE_CAT( arg, _alist_cursor_put_right )
void AList_cursor_put_right( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value );

/**
   AList_put_left

   Insert value to left of list's internal cursor's position.

   @param  current AList_t instance
   @param  value what to insert
*/
#define AList_put_left( arg ) PRIMITIVE_CAT( arg, _alist_put_left )
void AList_put_left( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_cursor_put_left

   Insert value to left of cursor's position.

   @param  cursor AList_cursor_t instance
   @param  value what to insert
*/
#define AList_cursor_put_left( arg ) PRIMITIVE_CAT( arg, _alist_cursor_put_left )
void AList_cursor_put_left( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value );

/**
   AList_put_first

   Insert value at beginning of list.

   @param  current AList_t instance
   @param  value what to insert
*/
#define AList_put_first( arg ) PRIMITIVE_CAT( arg, _alist_put_first )
void AList_put_first( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_put_last

   Insert value at beginning of list.

   @param  current AList_t instance
   @param  value what to insert
*/
#define AList_put_last( arg ) PRIMITIVE_CAT( arg, _alist_put_last )
void AList_put_last( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_replace

   Replace value with list item at index.

   @param  current AList_t instance
   @param  value what to replace with
   @param  index where to replace value
*/
#define AList_replace( arg ) PRIMITIVE_CAT( arg, _alist_replace )
void AList_replace( Prefix )( AList_type( Prefix ) *current, Type value, int32_t index );

/**
   AList_replace_and_dispose

   Replace value with list item at index. Dispose of original value.

   @param  current AList_t instance
   @param  value what to replace with
   @param  index where to replace value
*/
#define AList_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_replace_and_dispose )
void AList_replace_and_dispose( Prefix )( AList_type( Prefix ) *current, Type value, int32_t index );

/**
   AList_replace_at

   Replace value at list's internal cursor's position.

   @param  current AList_t instance
   @param  value what to replace with
*/
#define AList_replace_at( arg ) PRIMITIVE_CAT( arg, _alist_replace_at )
void AList_replace_at( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_cursor_replace_at

   Replace value at cursor's position.

   @param  cursor AList_cursor_t instance
   @param  value what to replace with
*/
#define AList_cursor_replace_at( arg ) PRIMITIVE_CAT( arg, _alist_cursor_replace_at )
void AList_cursor_replace_at( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value );

/**
   AList_replace_at_and_dispose

   Replace value at list's internal cursor's position. Dispose of original value.

   @param  current AList_t instance
   @param  value what to replace with
*/
#define AList_replace_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_replace_at_and_dispose )
void AList_replace_at_and_dispose( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_cursor_replace_at_and_dispose

   Replace value at cursor's position. Dispose of original value.

   @param  cursor AList_cursor_t instance
   @param  value what to replace with
*/
#define AList_cursor_replace_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_cursor_replace_at_and_dispose )
void AList_cursor_replace_at_and_dispose( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value );


/**
   AList_append

   Insert list at index.

   @param  current AList_t instance
   @param  other what to insert
   @param  index where to insert other
*/
#define AList_append( arg ) PRIMITIVE_CAT( arg, _alist_append )
void AList_append( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other, int32_t index );

/**
   AList_append_right

   Insert other to right of list's internal cursor's position.

   @param  current AList_t instance
   @param  other what to insert
*/
#define AList_append_right( arg ) PRIMITIVE_CAT( arg, _alist_append_right )
void AList_append_right( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_cursor_append_right

   Insert other to right of cursor's position.

   @param  cursor AList_cursor_t instance
   @param  other what to insert
*/
#define AList_cursor_append_right( arg ) PRIMITIVE_CAT( arg, _alist_cursor_append_right )
void AList_cursor_append_right( Prefix )( AList_cursor_type( Prefix ) *cursor, AList_type( Prefix ) *other );

/**
   AList_append_left

   Insert other to left of list's internal cursor's position.

   @param  current AList_t instance
   @param  other what to insert
*/
#define AList_append_left( arg ) PRIMITIVE_CAT( arg, _alist_append_left )
void AList_append_left( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_cursor_append_left

   Insert other to left of cursor's position.

   @param  cursor AList_cursor_t instance
   @param  other what to insert
*/
#define AList_cursor_append_left( arg ) PRIMITIVE_CAT( arg, _alist_cursor_append_left )
void AList_cursor_append_left( Prefix )( AList_cursor_type( Prefix ) *cursor, AList_type( Prefix ) *other );

/**
   AList_append_first

   Insert other at beginning of list.

   @param  current AList_t instance
   @param  other what to insert
*/
#define AList_append_first( arg ) PRIMITIVE_CAT( arg, _alist_append_first )
void AList_append_first( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );

/**
   AList_append_last

   Insert other at beginning of list.

   @param  current AList_t instance
   @param  other what to insert
*/
#define AList_append_last( arg ) PRIMITIVE_CAT( arg, _alist_append_last )
void AList_append_last( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other );


/*
   Removal
*/

/**
   AList_remove

   Remove value at index in list.

   @param  current AList_t instance
   @param  index where to remove value
*/
#define AList_remove( arg ) PRIMITIVE_CAT( arg, _alist_remove )
void AList_remove( Prefix )( AList_type( Prefix ) *current, int32_t index );

/**
   AList_remove_and_dispose

   Remove value at index in list. Dispose of removed value.

   @param  current AList_t instance
   @param  index where to remove value
*/
#define AList_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_remove_and_dispose )
void AList_remove_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t index );

/**
   AList_remove_at

   Remove value at list's internal cursor's position.

   @param  current AList_t instance
*/
#define AList_remove_at( arg ) PRIMITIVE_CAT( arg, _alist_remove_at )
void AList_remove_at( Prefix )( AList_type( Prefix ) *current );

/**
   AList_remove_at_and_dispose

   Remove value at list's internal cursor's position. Dispose of removed value.

   @param  current AList_t instance
*/
#define AList_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_remove_at_and_dispose )
void AList_remove_at_and_dispose( Prefix )( AList_type( Prefix ) *current );

/**
   AList_cursor_remove_at

   Remove value at cursor's position.

   @param  cursor AList_cursor_t instance
*/
#define AList_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _alist_cursor_remove_at )
void AList_cursor_remove_at( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_cursor_remove_at_and_dispose

   Remove value at cursor's position. Dispose of removed value.

   @param  cursor AList_cursor_t instance
*/
#define AList_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_cursor_remove_at_and_dispose )
void AList_cursor_remove_at_and_dispose( Prefix )( AList_cursor_type( Prefix ) *cursor );

/**
   AList_remove_first

   Remove first value in list.

   @param  current AList_t instance
*/
#define AList_remove_first( arg ) PRIMITIVE_CAT( arg, _alist_remove_first )
void AList_remove_first( Prefix )( AList_type( Prefix ) *current );

/**
   AList_remove_first_and_dispose. Dispose of removed value.

   Remove first value in list.

   @param  current AList_t instance
*/
#define AList_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_remove_first_and_dispose )
void AList_remove_first_and_dispose( Prefix )( AList_type( Prefix ) *current );

/**
   AList_remove_last

   Remove last value in list.

   @param  current AList_t instance
*/
#define AList_remove_last( arg ) PRIMITIVE_CAT( arg, _alist_remove_last )
void AList_remove_last( Prefix )( AList_type( Prefix ) *current );

/**
   AList_remove_last_and_dispose

   Remove last value in list. Dispose of removed value.

   @param  current AList_t instance
*/
#define AList_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_remove_last_and_dispose )
void AList_remove_last_and_dispose( Prefix )( AList_type( Prefix ) *current );

/**
   AList_prune

   Remove count items starting at index in list.

   @param  current AList_t instance
   @param  index where to start pruning
   @param  count how many items to prune
*/
#define AList_prune( arg ) PRIMITIVE_CAT( arg, _alist_prune )
void AList_prune( Prefix )( AList_type( Prefix ) *current, int32_t index, int32_t count );

/**
   AList_prune_and_dispose

   Remove count items starting at index in list.Dispose of removed values.

   @param  current AList_t instance
   @param  index where to start pruning
   @param  count how many items to prune
*/
#define AList_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_prune_and_dispose )
void AList_prune_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t index, int32_t count );

/**
   AList_prune_first

   Remove count items starting at beginning of list.

   @param  current AList_t instance
   @param  count how many items to prune
*/
#define AList_prune_first( arg ) PRIMITIVE_CAT( arg, _alist_prune_first )
void AList_prune_first( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_prune_first_and_dispose

   Remove count items starting at beginning of list. Dispose of removed values.

   @param  current AList_t instance
   @param  count how many items to prune
*/
#define AList_prune_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_prune_first_and_dispose )
void AList_prune_first_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_prune_last

   Remove count items starting at end of list.

   @param  list AList_t instance
   @param  count how many items to prune
*/
#define AList_prune_last( arg ) PRIMITIVE_CAT( arg, _alist_prune_last )
void AList_prune_last( Prefix )( AList_type( Prefix ) *list, int32_t count );

/**
   AList_prune_last_and_dispose

   Remove count items starting at end of list.

   @param  current AList_t instance
   @param  count how many items to prune
*/
#define AList_prune_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_prune_last_and_dispose )
void AList_prune_last_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_keep_first

   Remove items from end of list to leave count items at start of list.

   @param  current AList_t instance
   @param  count how many items to leave
*/
#define AList_keep_first( arg ) PRIMITIVE_CAT( arg, _alist_keep_first )
void AList_keep_first( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_keep_first_and_dispose

   Remove items from end of list to leave count items at start of list.  Dispose
   of removed values.

   @param  current AList_t instance
   @param  count how many items to leave
*/
#define AList_keep_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_keep_first_and_dispose )
void AList_keep_first_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_keep_last

   Remove items from start of list to leave count items at end of list.

   @param  current AList_t instance
   @param  count how many items to leave
*/
#define AList_keep_last( arg ) PRIMITIVE_CAT( arg, _alist_keep_last )
void AList_keep_last( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_keep_last_and_dispose

   Remove items from start of list to leave count items at end of list.
   Dispose of removed values.

   @param  current AList_t instance
   @param  count how many items to leave
*/
#define AList_keep_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_keep_last_and_dispose )
void AList_keep_last_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count );

/**
   AList_wipe_out

   Remove all items from list.

   @param  current AList_t instance
*/
#define AList_wipe_out( arg ) PRIMITIVE_CAT( arg, _alist_wipe_out )
void AList_wipe_out( Prefix )( AList_type( Prefix ) *current );

/**
   AList_wipe_out_and_dispose

   Remove all items from list. Dispose of removed values.

   @param  current AList_t instance
*/
#define AList_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _alist_wipe_out_and_dispose )
void AList_wipe_out_and_dispose( Prefix )( AList_type( Prefix ) *current );

/**
   AList_has

   Returns 1 if AList contains item using "==" as comparison test

   @param current the AList
   @param item the item to look for
*/
#define AList_has( arg ) PRIMITIVE_CAT( arg, _alist_has )
int32_t AList_has( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_has_eq_fn

   Returns 1 if AList contains item using equality_test_func as comparison test

   @param current the AList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define AList_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _alist_has_eq_fn )
int32_t AList_has_eq_fn( Prefix )( AList_type( Prefix ) *current, Type value, int32_t ( *equality_test_func )( Type v1, Type v2 ) );

/**
   AList_search_forth

   Search through AList starting at current position, stopping when item
   is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param current the AList
   @param item the item to look for
*/
#define AList_search_forth( arg ) PRIMITIVE_CAT( arg, _alist_search_forth )
void AList_search_forth( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_search_forth_eq_fn

   Search through AList starting at current position, stopping when item
   is equal to value, using equality_test_func as comparison test
   if value not found, list will be "off"

   @param current the AList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define AList_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _alist_search_forth_eq_fn )
void AList_search_forth_eq_fn( Prefix )( AList_type( Prefix ) *current, Type value, int32_t ( *equality_test_func )( Type v1, Type v2 ) );

/**
   AList_search_back

   Search backwards through AList starting at current position, stopping when
   item is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param current the AList
   @param item the item to look for
*/
#define AList_search_back( arg ) PRIMITIVE_CAT( arg, _alist_search_back )
void AList_search_back( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_search_back_eq_fn

   Search backwards through AList starting at current
   position, stopping when item is equal to value, using equality_test_func as
   comparison test.
   if value not found, list will be "off"

   @param current the AList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define AList_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _alist_search_back_eq_fn )
void AList_search_back_eq_fn( Prefix )( AList_type( Prefix ) *current, Type value, int32_t ( *equality_test_func )( Type v1, Type v2 ) );

/**
   AList_cursor_search_forth

   Search through AList starting at current cursor position, stopping when item
   is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param cursor the AList cursor
   @param item the item to look for
*/
#define AList_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _alist_cursor_search_forth )
void AList_cursor_search_forth( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value );

/**
   AList_cursor_search_forth_eq_fn

   Search through AList starting at current cursor position, stopping when item
   is equal to value, using equality_test_func as comparison test
   if value not found, list will be "off"

   @param cursor the AList cursor
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define AList_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _alist_cursor_search_forth_eq_fn )
void AList_cursor_search_forth_eq_fn( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value, int32_t ( *equality_test_func )( Type v1, Type v2 ) );

/**
   AList_cursor_search_back

   Search backwards through AList starting at current cursor position, stopping when
   item is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param cursor the AList cursor
   @param item the item to look for
*/
#define AList_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _alist_cursor_search_back )
void AList_cursor_search_back( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value );

/**
   AList_cursor_search_back_eq_fn

   Search backwards through AList starting at current cursor
   position, stopping when item is equal to value, using equality_test_func as
   comparison test.
   if value not found, list will be "off"

   @param cursor the AList cursor
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define AList_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _alist_cursor_search_back_eq_fn )
void AList_cursor_search_back_eq_fn( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value, int32_t ( *equality_test_func )( Type v1, Type v2 ) );

/**
   AList_occurrences

   Returns count of items in AList equal to value using "==" as comparison test

   @param current the AList
   @param item the item to look for
*/
#define AList_occurrences( arg ) PRIMITIVE_CAT( arg, _alist_occurrences )
int32_t AList_occurrences( Prefix )( AList_type( Prefix ) *current, Type value );

/**
   AList_occurrences_eq_fn

   Returns count of items in AList equal to value using equality_test_func
   as comparison test

   @param current the AList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define AList_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _alist_occurrences_eq_fn )
int32_t AList_occurrences_eq_fn( Prefix )( AList_type( Prefix ) *current, Type value, int32_t ( *equality_test_func )( Type v1, Type v2 ) );

/**
   AList_swap

   Swaps items in AList at index i and j

   @param current the AList
   @param i an index into the list
   @param j the other index into the list
*/
#define AList_swap( arg ) PRIMITIVE_CAT( arg, _alist_swap )
void AList_swap( Prefix )( AList_type( Prefix ) *current, int32_t i, int32_t j );


/**
   AList_sort

   Sort items in list using sort_func.

   @param  current AList_t instance
   @param sort_func function compare two list items
*/
#define AList_sort( arg ) PRIMITIVE_CAT( arg, _alist_sort )
void AList_sort( Prefix )( AList_type( Prefix ) *current, int32_t (*func)( Type v1, Type v2 ) );


#ifdef __cplusplus
}
#endif

/* End of file */




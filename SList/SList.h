/**
 @file SList.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Singly Linked Lists"
 
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

 Function declarations for the opaque SList_t type.

*/

/**
   includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   Prefix - string used to name this container type
   Type   - the type of the value
   
   Macros that must be present (external to this file):
   
   VALUE_DISPOSE_FUNCTION  -  frees a value instance  
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define SList_struct( arg ) PRIMITIVE_CAT( arg, _slist_struct )
#define SList_type( arg ) PRIMITIVE_CAT( arg, _slist_t )
#define SList_name( arg ) PRIMITIVE_CAT( arg, _slist )

#define SList_cursor_struct( arg ) PRIMITIVE_CAT( arg, _slist_cursor_struct )
#define SList_cursor_type( arg ) PRIMITIVE_CAT( arg, _slist_cursor_t )
#define SList_cursor_name( arg ) PRIMITIVE_CAT( arg, _slist_cursor )

/** 
   Structure declarations
*/

struct SList_struct( Prefix );
struct SList_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct SList_struct( Prefix ) SList_type( Prefix );
typedef struct SList_cursor_struct( Prefix ) SList_cursor_type( Prefix );


/**
   Function names below are prepended with "Prefix_".
*/


/** 
   Initialization
*/

/**
   SList_make
   
   Return a new empty SList_t instance.
   
   @return SList_t instance 
*/
#define SList_make( arg ) PRIMITIVE_CAT( arg, _slist_make )
SList_type( Prefix ) * SList_make( Prefix )( void );

/**
   SList_make_from
   
   Return a new SList_t instance filled with the content of list. The value
   of the items in list are not copied.
   
   @param  list SList_t instance to copy from 
   @return SList_t instance 
*/
#define SList_make_from( arg ) PRIMITIVE_CAT( arg, _slist_make_from )
SList_type( Prefix ) * SList_make_from( Prefix )( SList_type( Prefix ) *list );

/**
   SList_make_from_array
   
   Return a new SList_t instance filled with the content of array. The value
   of the items in array are not copied.
   
   @param  list array to copy from 
   @param  count number of items to copy 
   @return SList_t instance 
*/
#define SList_make_from_array( arg ) PRIMITIVE_CAT( arg, _slist_make_from_array )
SList_type( Prefix ) * SList_make_from_array( Prefix )( Type *array, int32_t count );

/**
   SList_make_duplicate_from
   
   Return a new SList_t instance filled with duplicates of the content of list. 
   The value of the items in list are copied.
   
   @param  list SList_t instance to copy from 
   @return SList_t instance 
*/

#define SList_make_duplicate_from( arg ) PRIMITIVE_CAT( arg, _slist_make_duplicate_from )
SList_type( Prefix ) *
SList_make_duplicate_from( Prefix )( SList_type( Prefix ) *oher );

/**
   SList_cursor_make
   
   Return a new empty SList_cursor_t instance.
   
   @param  list SList_t instance 
   @return SList_cursor_t instance 
*/
#define SList_cursor_make( arg ) PRIMITIVE_CAT( arg, _slist_cursor_make )
SList_cursor_type( Prefix ) * SList_cursor_make( Prefix )( SList_type( Prefix ) *list );


/**
   Disposal
*/

/**
   SList_dispose
   
   Free a Slist_t instance. The value items are not disposed.
   
   @param  list SList_t instance 
*/
#define SList_dispose( arg ) PRIMITIVE_CAT( arg, _slist_dispose )
void SList_dispose( Prefix )( SList_type( Prefix ) *list );

/**
   SList_dispose_with_contents
   
   Free a Slist_t instance. The value items are disposed.
   
   @param  list SList_t instance 
*/
#define SList_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _slist_dispose_with_contents )
void SList_dispose_with_contents( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_dispose
   
   Free a Slist_cursor_t instance. Its associated list is not disposed.
   
   @param  cursor SList_cursor_t instance 
*/
#define SList_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _slist_cursor_dispose )
void SList_cursor_dispose( Prefix )( SList_cursor_type( Prefix ) *cursor );


/** 
   Access
*/

/**
   SList_cursor_item_at
   
   Return the value of the item pointed to by cursor.
   
   @param  cursor SList_cursor_t instance 
   @return the value of the item pointed to by cursor
*/
#define SList_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _slist_cursor_item_at )
Type SList_cursor_item_at( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_item_at
   
   Return the value of the item pointed to by list's internal cursor.
   
   @param  list SList_t instance 
   @return the value of the item pointed to by list's internal cursor
*/
#define SList_item_at( arg ) PRIMITIVE_CAT( arg, _slist_item_at )
Type SList_item_at( Prefix )( SList_type( Prefix ) *list );

/**
   SList_item
   
   Return the value of the ith item in the list.
   
   @param  list SList_t instance 
   @param  index index of requested item 
   @return the value of the item pointed to by list's internal cursor
*/
#define SList_item( arg ) PRIMITIVE_CAT( arg, _slist_item )
Type SList_item( Prefix )( SList_type( Prefix ) *list, int32_t index );

/**
   SList_first
   
   Return the value of the first item in the list.
   
   @param  list SList_t instance 
   @return the value of the first item
*/
#define SList_first( arg ) PRIMITIVE_CAT( arg, _slist_first )
Type SList_first( Prefix )( SList_type( Prefix ) *list );

/**
   SList_last
   
   Return the value of the last item in the list.
   
   @param  list SList_t instance 
   @return the value of the last item
*/
#define SList_last( arg ) PRIMITIVE_CAT( arg, _slist_last )
Type SList_last( Prefix )( SList_type( Prefix ) *list );

/**
   SList_as_array
   
   Return the values of the list as an array.
   
   @param  list SList_t instance 
   @param  count pointer to the returned item count 
   @return the array of items
*/
#define SList_as_array( arg ) PRIMITIVE_CAT( arg, _slist_as_array )
Type * SList_as_array( Prefix )( SList_type( Prefix ) *list, int32_t *count );


/** 
   Measurement
*/

/**
   SList_count
   
   Return the number of items in the list.
   
   @param  list SList_t instance 
   @return the number of items in the list
*/
#define SList_count( arg ) PRIMITIVE_CAT( arg, _slist_count )
int32_t SList_count( Prefix )( SList_type( Prefix ) *list );


/** 
   Status report
*/

/**
   SList_off
   
   Returns 1 if the list's internal cursor is off, otherwise 0.
   
   @param  list SList_t instance 
   @return 1 if internal cursor is off, 0 otherwise
*/
#define SList_off( arg ) PRIMITIVE_CAT( arg, _slist_off )
int32_t SList_off( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_off
   
   Returns 1 if the cursor is off, otherwise 0.
   
   @param  list SList_cursor_t instance 
   @return 1 if cursor is off, 0 otherwise
*/
#define SList_cursor_off( arg ) PRIMITIVE_CAT( arg, _slist_cursor_off )
int32_t SList_cursor_off( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_is_first
   
   Returns 1 if the list's internal cursor is is_first, otherwise 0.
   
   @param  list SList_t instance 
   @return 1 if internal cursor is is_first, 0 otherwise
*/
#define SList_is_first( arg ) PRIMITIVE_CAT( arg, _slist_is_first )
int32_t SList_is_first( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_is_first
   
   Returns 1 if the cursor is is_first, otherwise 0.
   
   @param  list SList_cursor_t instance 
   @return 1 if cursor is is_first, 0 otherwise
*/
#define SList_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _slist_cursor_is_first )
int32_t SList_cursor_is_first( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_is_last
   
   Returns 1 if the list's internal cursor is is_last, otherwise 0.
   
   @param  list SList_t instance 
   @return 1 if internal cursor is is_last, 0 otherwise
*/
#define SList_is_last( arg ) PRIMITIVE_CAT( arg, _slist_is_last )
int32_t SList_is_last( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_is_last
   
   Returns 1 if the cursor is is_last, otherwise 0.
   
   @param  list SList_cursor_t instance 
   @return 1 if cursor is is_last, 0 otherwise
*/
#define SList_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _slist_cursor_is_last )
int32_t SList_cursor_is_last( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_is_empty
   
   Returns 1 if the list contains no items.
   
   @param  list SList_t instance 
   @return 1 if list is empty, 0 otherwise
*/
#define SList_is_empty( arg ) PRIMITIVE_CAT( arg, _slist_is_empty )
int32_t SList_is_empty( Prefix )( SList_type( Prefix ) *list );

/**
   SList_index
   
   Returns index of the internal cursor - if internal cursor is off, returns -1
   
   @param  list SList_t instance 
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define SList_index( arg ) PRIMITIVE_CAT( arg, _slist_index )
int32_t SList_index( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_index
   
   Returns index of the cursor - if cursor is off, returns -1
   
   @param  list SList_cursor_t instance 
   @return index in list of cursor if not off, -1 otherwise
*/
#define SList_cursor_index( arg ) PRIMITIVE_CAT( arg, _slist_cursor_index )
int32_t SList_cursor_index( Prefix )( SList_cursor_type( Prefix ) *cursor );


// Cursor movement

/**
   SList_forth
   
   Moves the list's internal cursor to the next item in the list.
   
   @param  list SList_t instance 
*/
#define SList_forth( arg ) PRIMITIVE_CAT( arg, _slist_forth )
void SList_forth( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_forth
   
   Moves the cursor to the next item in the list.
   
   @param  list SList_cursor_t instance 
*/
#define SList_cursor_forth( arg ) PRIMITIVE_CAT( arg, _slist_cursor_forth )
void SList_cursor_forth( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_go
   
   Moves the list's internal cursor to the ith item in the list. The first
   index is 0.
   
   @param  list SList_t instance 
   @param  index the requested list position 
*/
#define SList_go( arg ) PRIMITIVE_CAT( arg, _slist_go )
void SList_go( Prefix )( SList_type( Prefix ) *list, int32_t index );

/**
   SList_cursor_go
   
   Moves the cursor to the ith item in the list. The first index is 0.
   
   @param  list SList_cursor_t instance 
   @param  index the requested list position 
*/
#define SList_cursor_go( arg ) PRIMITIVE_CAT( arg, _slist_cursor_go )
void SList_cursor_go( Prefix )( SList_cursor_type( Prefix ) *cursor, int32_t index );

/**
   SList_start
   
   Moves the list's internal cursor to the first item in the list.
   
   @param  list SList_t instance 
*/
#define SList_start( arg ) PRIMITIVE_CAT( arg, _slist_start )
void SList_start( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_start
   
   Moves the cursor to the first item in the list.
   
   @param  list SList_cursor_t instance 
*/
#define SList_cursor_start( arg ) PRIMITIVE_CAT( arg, _slist_cursor_start )
void SList_cursor_start( Prefix )( SList_cursor_type( Prefix ) *cursor );


/** 
   Element change
*/

/**
   SList_put
   
   Insert value at index.
   
   @param  list SList_t instance 
   @param  value what to insert
   @param  index where to insert value 
*/
#define SList_put( arg ) PRIMITIVE_CAT( arg, _slist_put )
void SList_put( Prefix )( SList_type( Prefix ) *list, Type value, int32_t index );

/**
   SList_put_right
   
   Insert value to right of list's internal cursor's position.
   
   @param  list SList_t instance 
   @param  value what to insert
*/
#define SList_put_right( arg ) PRIMITIVE_CAT( arg, _slist_put_right )
void SList_put_right( Prefix )( SList_type( Prefix ) *list, Type value );

/**
   SList_cursor_put_right
   
   Insert value to right of cursor's position.
   
   @param  cursor SList_cursor_t instance 
   @param  value what to insert
*/
#define SList_cursor_put_right( arg ) PRIMITIVE_CAT( arg, _slist_cursor_put_right )
void SList_cursor_put_right( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value );

/**
   SList_put_first
   
   Insert value at beginning of list.
   
   @param  list SList_t instance 
   @param  value what to insert
*/
#define SList_put_first( arg ) PRIMITIVE_CAT( arg, _slist_put_first )
void SList_put_first( Prefix )( SList_type( Prefix ) *list, Type value );

/**
   SList_put_last
   
   Insert value at beginning of list.
   
   @param  list SList_t instance 
   @param  value what to insert
*/
#define SList_put_last( arg ) PRIMITIVE_CAT( arg, _slist_put_last )
void SList_put_last( Prefix )( SList_type( Prefix ) *list, Type value );

/**
   SList_replace
   
   Replace value with list item at index.
   
   @param  list SList_t instance 
   @param  value what to replace with
   @param  index where to replace value
*/
#define SList_replace( arg ) PRIMITIVE_CAT( arg, _slist_replace )
void SList_replace( Prefix )( SList_type( Prefix ) *list, Type value, int32_t index );

/**
   SList_replace_and_dispose
   
   Replace value with list item at index. Dispose of original value.
   
   @param  list SList_t instance 
   @param  value what to replace with
   @param  index where to replace value
*/
#define SList_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_replace_and_dispose )
void SList_replace_and_dispose( Prefix )( SList_type( Prefix ) *list, Type value, int32_t index );

/**
   SList_replace_at
   
   Replace value at list's internal cursor's position.
   
   @param  list SList_t instance 
   @param  value what to replace with
*/
#define SList_replace_at( arg ) PRIMITIVE_CAT( arg, _slist_replace_at )
void SList_replace_at( Prefix )( SList_type( Prefix ) *list, Type value );

/**
   SList_cursor_replace_at
   
   Replace value at cursor's position.
   
   @param  cursor SList_cursor_t instance 
   @param  value what to replace with
*/
#define SList_cursor_replace_at( arg ) PRIMITIVE_CAT( arg, _slist_cursor_replace_at )
void SList_cursor_replace_at( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value );

/**
   SList_replace_at_and_dispose
   
   Replace value at list's internal cursor's position. Dipose of original value.
   
   @param  list SList_t instance 
   @param  value what to replace with
*/
#define SList_replace_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_replace_at_and_dispose )
void SList_replace_at_and_dispose( Prefix )( SList_type( Prefix ) *list, Type value );

/**
   SList_cursor_replace_at_and_dispose
   
   Replace value at cursor's position. Dipose of original value.
   
   @param  cursor SList_cursor_t instance 
   @param  value what to replace with
*/
#define SList_cursor_replace_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_cursor_replace_at_and_dispose )
void SList_cursor_replace_at_and_dispose( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value );


/**
   SList_append
   
   Insert list at index.
   
   @param  list SList_t instance 
   @param  other what to insert
   @param  index where to insert other 
*/
#define SList_append( arg ) PRIMITIVE_CAT( arg, _slist_append )
void SList_append( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other, int32_t index );

/**
   SList_append_right
   
   Insert other to right of list's internal cursor's position.
   
   @param  list SList_t instance 
   @param  other what to insert
*/
#define SList_append_right( arg ) PRIMITIVE_CAT( arg, _slist_append_right )
void SList_append_right( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other );

/**
   SList_cursor_append_right
   
   Insert other to right of cursor's position.
   
   @param  cursor SList_cursor_t instance 
   @param  other what to insert
*/
#define SList_cursor_append_right( arg ) PRIMITIVE_CAT( arg, _slist_cursor_append_right )
void SList_cursor_append_right( Prefix )( SList_cursor_type( Prefix ) *cursor, SList_type( Prefix ) *other );

/**
   SList_append_first
   
   Insert other at beginning of list.
   
   @param  list SList_t instance 
   @param  other what to insert
*/
#define SList_append_first( arg ) PRIMITIVE_CAT( arg, _slist_append_first )
void SList_append_first( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other );

/**
   SList_append_last
   
   Insert other at beginning of list.
   
   @param  list SList_t instance 
   @param  other what to insert
*/
#define SList_append_last( arg ) PRIMITIVE_CAT( arg, _slist_append_last )
void SList_append_last( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other );


/**
   Removal
*/

/**
   SList_remove
   
   Remove value at index in list.
   
   @param  list SList_t instance 
   @param  index where to remove value
*/
#define SList_remove( arg ) PRIMITIVE_CAT( arg, _slist_remove )
void SList_remove( Prefix )( SList_type( Prefix ) *list, int32_t index );

/**
   SList_remove_and_dispose
   
   Remove value at index in list. Dipose of removed values.
   
   @param  list SList_t instance 
   @param  index where to remove value
*/
#define SList_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_remove_and_dispose )
void SList_remove_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t index );

/**
   SList_remove_at
   
   Remove value at list's internal cursor's position.
   
   @param  list SList_t instance 
*/
#define SList_remove_at( arg ) PRIMITIVE_CAT( arg, _slist_remove_at )
void SList_remove_at( Prefix )( SList_type( Prefix ) *list );

/**
   SList_remove_at_and_dispose
   
   Remove value at list's internal cursor's position. Dipose of removed values.
   
   @param  list SList_t instance 
*/
#define SList_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_remove_at_and_dispose )
void SList_remove_at_and_dispose( Prefix )( SList_type( Prefix ) *list );

/**
   SList_cursor_remove_at
   
   Remove value at cursor's position.
   
   @param  cursor SList_cursor_t instance 
*/
#define SList_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _slist_cursor_remove_at )
void SList_cursor_remove_at( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_cursor_remove_at_and_dispose
   
   Remove value at cursor's position. Dipose of removed values.
   
   @param  cursor SList_cursor_t instance 
*/
#define SList_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_cursor_remove_at_and_dispose )
void SList_cursor_remove_at_and_dispose( Prefix )( SList_cursor_type( Prefix ) *cursor );

/**
   SList_remove_first
   
   Remove first value in list.
   
   @param  list SList_t instance 
*/
#define SList_remove_first( arg ) PRIMITIVE_CAT( arg, _slist_remove_first )
void SList_remove_first( Prefix )( SList_type( Prefix ) *list );

/**
   SList_remove_first_and_dispose
   
   Remove first value in list.
   
   @param  list SList_t instance 
*/
#define SList_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_remove_first_and_dispose )
void SList_remove_first_and_dispose( Prefix )( SList_type( Prefix ) *list );

/**
   SList_remove_last
   
   Remove last value in list.
   
   @param  list SList_t instance 
*/
#define SList_remove_last( arg ) PRIMITIVE_CAT( arg, _slist_remove_last )
void SList_remove_last( Prefix )( SList_type( Prefix ) *list );

/**
   SList_remove_last_and_dispose
   
   Remove last value in list. Dipose of removed values.
   
   @param  list SList_t instance 
*/
#define SList_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_remove_last_and_dispose )
void SList_remove_last_and_dispose( Prefix )( SList_type( Prefix ) *list );

/**
   SList_prune
   
   Remove count items starting at index in list. 
   
   @param  list SList_t instance 
   @param  index where to start pruning
   @param  count how many items to prune
*/
#define SList_prune( arg ) PRIMITIVE_CAT( arg, _slist_prune )
void SList_prune( Prefix )( SList_type( Prefix ) *list, int32_t index, int32_t count );

/**
   SList_prune_and_dispose
   
   Remove count items starting at index in list.Dipose of removed values.
   
   @param  list SList_t instance 
   @param  index where to start pruning
   @param  count how many items to prune
*/
#define SList_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_prune_and_dispose )
void SList_prune_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t index, int32_t count );

/**
   SList_prune_first
   
   Remove count items starting at beginning of list.
   
   @param  list SList_t instance 
   @param  count how many items to prune
*/
#define SList_prune_first( arg ) PRIMITIVE_CAT( arg, _slist_prune_first )
void SList_prune_first( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_prune_first_and_dispose
   
   Remove count items starting at beginning of list. Dipose of removed values.
   
   @param  list SList_t instance 
   @param  count how many items to prune
*/
#define SList_prune_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_prune_first_and_dispose )
void SList_prune_first_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_prune_last
   
   Remove count items starting at end of list.
   
   @param  list SList_t instance 
   @param  count how many items to prune
*/
#define SList_prune_last( arg ) PRIMITIVE_CAT( arg, _slist_prune_last )
void SList_prune_last( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_prune_last_and_dispose
   
   Remove count items starting at end of list.
   
   @param  list SList_t instance 
   @param  count how many items to prune
*/
#define SList_prune_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_prune_last_and_dispose )
void SList_prune_last_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_keep_first
   
   Remove items from end of list to leave count items at start of list.
   
   @param  list SList_t instance 
   @param  count how many items to leave
*/
#define SList_keep_first( arg ) PRIMITIVE_CAT( arg, _slist_keep_first )
void SList_keep_first( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_keep_first_and_dispose
   
   Remove items from end of list to leave count items at start of list.
   
   @param  list SList_t instance 
   @param  count how many items to leave
*/
#define SList_keep_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_keep_first_and_dispose )
void SList_keep_first_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_keep_last
   
   Remove items from start of list to leave count items at end of list.
   
   @param  list SList_t instance 
   @param  count how many items to leave
*/
#define SList_keep_last( arg ) PRIMITIVE_CAT( arg, _slist_keep_last )
void SList_keep_last( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_keep_last_and_dispose
   
   Remove items from start of list to leave count items at end of list. 
   Dipose of removed values.
   
   @param  list SList_t instance 
   @param  count how many items to leave
*/
#define SList_keep_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_keep_last_and_dispose )
void SList_keep_last_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count );

/**
   SList_wipe_out
   
   Remove all items from list.
   
   @param  list SList_t instance 
*/
#define SList_wipe_out( arg ) PRIMITIVE_CAT( arg, _slist_wipe_out )
void SList_wipe_out( Prefix )( SList_type( Prefix ) *list );

/**
   SList_wipe_out_and_dispose
   
   Remove all items from list. Dipose of removed values.
   
   @param  list SList_t instance 
*/
#define SList_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _slist_wipe_out_and_dispose )
void SList_wipe_out_and_dispose( Prefix )( SList_type( Prefix ) *list );

/**
   SList_sort
   
   Sort items in list using sort_func.
   
   @param  list SList_t instance 
   @param sort_func function compare two list items
*/
#define SList_sort( arg ) PRIMITIVE_CAT( arg, _slist_sort )
void SList_sort( Prefix )( SList_type( Prefix ) *list, int32_t (*func)( Type v1, Type v2 ) );



/* End of file */




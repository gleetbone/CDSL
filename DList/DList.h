/**
 @file DList.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Doubly linked lists (next and previous)"

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

 Function declarations for the opaque DList_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define DLIST_VERSION_MAJOR 2
#define DLIST_VERSION_MINOR 0
#define DLIST_VERSION_PATCH 0

#define DLIST_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define DLIST_VERSION \
   DLIST_MAKE_VERSION( DLIST_VERSION_MAJOR, \
                       DLIST_VERSION_MINOR, \
                       DLIST_VERSION_PATCH )

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

   VALUE_DEEP_DISPOSE_FUNCTION   - frees a value instance
   VALUE_DEEP_CLONE_FUNCTION     - clones a value instance
   VALUE_DEEP_EQUAL_FUNCTION     - compares two value instances for equality

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define DList_struct( arg ) PRIMITIVE_CAT( arg, _dlist_struct )
#define DList_type( arg ) PRIMITIVE_CAT( arg, _dlist_t )
#define DList_name( arg ) PRIMITIVE_CAT( arg, _dlist )

#define DList_cursor_struct( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_struct )
#define DList_cursor_type( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_t )
#define DList_cursor_name( arg ) PRIMITIVE_CAT( arg, _dlist_cursor )

/**
   Structure declarations
*/

struct DList_struct( Prefix );
struct DList_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct DList_struct( Prefix ) DList_type( Prefix );
typedef struct DList_cursor_struct( Prefix ) DList_cursor_type( Prefix );


/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   DList_make

   Return a new empty DList_t instance.

   @return DList_t instance
*/
#define DList_make( arg ) PRIMITIVE_CAT( arg, _dlist_make )
DList_type( Prefix ) * DList_make( Prefix )( void );

/**
   DList_make_from_array

   Return a new DList_t instance filled with the contents of array. The value
   of the items in array are not copied.

   @param  array array to copy from
   @param  count number of items in array
   @return DList_t instance
*/
#define DList_make_from_array( arg ) PRIMITIVE_CAT( arg, _dlist_make_from_array )
DList_type( Prefix ) * DList_make_from_array( Prefix )( Type *array, int32_t count );

/*
   Basic
*/

/**
   DList_clone

   Return a new DList_t instance filled with the content of list. The value
   of the items in list are not copied.

   @param  list DList_t instance to copy from
   @return DList_t instance
*/
#define DList_clone( arg ) PRIMITIVE_CAT( arg, _dlist_clone )
DList_type( Prefix ) * DList_clone( Prefix )( DList_type( Prefix ) *list );

/**
   DList_deep_clone

   Return a new DList_t instance filled with duplicates of the content of list.
   The value of the items in list are copied.

   @param  list DList_t instance to copy from
   @return DList_t instance
*/

#define DList_deep_clone( arg ) PRIMITIVE_CAT( arg, _dlist_deep_clone )
DList_type( Prefix ) *
DList_deep_clone( Prefix )( DList_type( Prefix ) *oher );

/**
   DList_is_equal

   Check that list contains same elements as other

   @param  current DList_t instance
   @param  other DList_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define DList_is_equal( arg ) PRIMITIVE_CAT( arg, _dlist_is_equal )
int32_t
DList_is_equal( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other );

/**
   DList_is_deep_equal

   Check that list contains same elements as other

   @param  current DList_t instance
   @param  other DList_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define DList_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _dlist_is_deep_equal )
int32_t
DList_is_deep_equal( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other );

/**
   DList_copy

   Copy other into current

   @param  current DList_t instance
   @param  other DList_t instance to copy from

*/

#define DList_copy( arg ) PRIMITIVE_CAT( arg, _dlist_copy )
void
DList_copy( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other );

/**
   DList_deep_copy

   Deep copy other into current

   @param  current DList_t instance
   @param  other DList_t instance to deep_copy from

*/

#define DList_deep_copy( arg ) PRIMITIVE_CAT( arg, _dlist_deep_copy )
void
DList_deep_copy( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other );

/**
   DList_cursor_make

   Return a new empty DList_cursor_t instance.

   @param  list DList_t instance
   @return DList_cursor_t instance
*/
#define DList_cursor_make( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_make )
DList_cursor_type( Prefix ) * DList_cursor_make( Prefix )( DList_type( Prefix ) *list );


/*
   Disposal
*/

/**
   DList_dispose

   Free a Slist_t instance. The value items are not disposed.

   @param  list pointer to DList_t instance
*/
#define DList_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_dispose )
void DList_dispose( Prefix )( DList_type( Prefix ) **list );

/**
   DList_deep_dispose

   Free a Slist_t instance. The value items are disposed.

   @param  list pointer to DList_t instance
*/
#define DList_deep_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_deep_dispose )
void DList_deep_dispose( Prefix )( DList_type( Prefix ) **list );

/**
   DList_cursor_dispose

   Free a Slist_cursor_t instance. Its associated list is not disposed.

   @param  cursor pointer to DList_cursor_t instance
*/
#define DList_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_dispose )
void DList_cursor_dispose( Prefix )( DList_cursor_type( Prefix ) **cursor );


/*
   Access
*/

/**
   DList_cursor_item_at

   Return the value of the item pointed to by cursor.

   @param  cursor DList_cursor_t instance
   @return the value of the item pointed to by cursor
*/
#define DList_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_item_at )
Type DList_cursor_item_at( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_item_at

   Return the value of the item pointed to by list's internal cursor.

   @param  list DList_t instance
   @return the value of the item pointed to by list's internal cursor
*/
#define DList_item_at( arg ) PRIMITIVE_CAT( arg, _dlist_item_at )
Type DList_item_at( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_item_next

   Return the value of the next item pointed to by cursor.

   @param  cursor DList_cursor_t instance
   @return the value of the item pointed to by cursor
*/
#define DList_cursor_item_next( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_item_next )
Type DList_cursor_item_next( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_item_next

   Return the value of the next item pointed to by list's internal cursor.

   @param  list DList_t instance
   @return the value of the item pointed to by list's internal cursor
*/
#define DList_item_next( arg ) PRIMITIVE_CAT( arg, _dlist_item_next )
Type DList_item_next( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_item_prev

   Return the value of the previous item pointed to by cursor.

   @param  cursor DList_cursor_t instance
   @return the value of the item pointed to by cursor
*/
#define DList_cursor_item_prev( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_item_prev )
Type DList_cursor_item_prev( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_item_prev

   Return the value of the previous item pointed to by list's internal cursor.

   @param  list DList_t instance
   @return the value of the item pointed to by list's internal cursor
*/
#define DList_item_prev( arg ) PRIMITIVE_CAT( arg, _dlist_item_prev )
Type DList_item_prev( Prefix )( DList_type( Prefix ) *list );

/**
   DList_item

   Return the value of the ith item in the list.

   @param  list DList_t instance
   @param  index index of requested item
   @return the value of the item pointed to by list's internal cursor
*/
#define DList_item( arg ) PRIMITIVE_CAT( arg, _dlist_item )
Type DList_item( Prefix )( DList_type( Prefix ) *list, int32_t index );

/**
   DList_first

   Return the value of the first item in the list.

   @param  list DList_t instance
   @return the value of the first item
*/
#define DList_first( arg ) PRIMITIVE_CAT( arg, _dlist_first )
Type DList_first( Prefix )( DList_type( Prefix ) *list );

/**
   DList_last

   Return the value of the last item in the list.

   @param  list DList_t instance
   @return the value of the last item
*/
#define DList_last( arg ) PRIMITIVE_CAT( arg, _dlist_last )
Type DList_last( Prefix )( DList_type( Prefix ) *list );

/**
   DList_as_array

   Return the values of the list as an array. The array must freed with free();

   @param  list DList_t instance
   @param  count points to the returned array count
   @return the value of the last item
*/
#define DList_as_array( arg ) PRIMITIVE_CAT( arg, _dlist_as_array )
Type * DList_as_array( Prefix )( DList_type( Prefix ) *list, int32_t *count );


/*
   Measurement
*/

/**
   DList_count

   Return the number of items in the list.

   @param  list DList_t instance
   @return the number of items in the list
*/
#define DList_count( arg ) PRIMITIVE_CAT( arg, _dlist_count )
int32_t DList_count( Prefix )( DList_type( Prefix ) *list );


/*
   Status report
*/

/**
   DList_off

   Returns 1 if the list's internal cursor is off, otherwise 0.

   @param  list DList_t instance
   @return 1 if internal cursor is off, 0 otherwise
*/
#define DList_off( arg ) PRIMITIVE_CAT( arg, _dlist_off )
int32_t DList_off( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_off

   Returns 1 if the cursor is off, otherwise 0.

   @param  list DList_cursor_t instance
   @return 1 if cursor is off, 0 otherwise
*/
#define DList_cursor_off( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_off )
int32_t DList_cursor_off( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_is_first

   Returns 1 if the list's internal cursor is is_first, otherwise 0.

   @param  list DList_t instance
   @return 1 if internal cursor is is_first, 0 otherwise
*/
#define DList_is_first( arg ) PRIMITIVE_CAT( arg, _dlist_is_first )
int32_t DList_is_first( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_is_first

   Returns 1 if the cursor is is_first, otherwise 0.

   @param  list DList_cursor_t instance
   @return 1 if cursor is is_first, 0 otherwise
*/
#define DList_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_is_first )
int32_t DList_cursor_is_first( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_is_last

   Returns 1 if the list's internal cursor is is_last, otherwise 0.

   @param  list DList_t instance
   @return 1 if internal cursor is is_last, 0 otherwise
*/
#define DList_is_last( arg ) PRIMITIVE_CAT( arg, _dlist_is_last )
int32_t DList_is_last( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_is_last

   Returns 1 if the cursor is is_last, otherwise 0.

   @param  list DList_cursor_t instance
   @return 1 if cursor is is_last, 0 otherwise
*/
#define DList_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_is_last )
int32_t DList_cursor_is_last( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_is_empty

   Returns 1 if the list contains no items.

   @param  list DList_t instance
   @return 1 if list is empty, 0 otherwise
*/
#define DList_is_empty( arg ) PRIMITIVE_CAT( arg, _dlist_is_empty )
int32_t DList_is_empty( Prefix )( DList_type( Prefix ) *list );

/**
   DList_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  list DList_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define DList_index( arg ) PRIMITIVE_CAT( arg, _dlist_index )
int32_t DList_index( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list DList_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define DList_cursor_index( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_index )
int32_t DList_cursor_index( Prefix )( DList_cursor_type( Prefix ) *cursor );


/*
   Cursor movement
*/

/**
   DList_forth

   Moves the list's internal cursor to the next item in the list.

   @param  list DList_t instance
*/
#define DList_forth( arg ) PRIMITIVE_CAT( arg, _dlist_forth )
void DList_forth( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_forth

   Moves the cursor to the next item in the list.

   @param  list DList_cursor_t instance
*/
#define DList_cursor_forth( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_forth )
void DList_cursor_forth( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_back

   Moves the list's internal cursor to the previous item in the list.

   @param  list DList_t instance
*/
#define DList_back( arg ) PRIMITIVE_CAT( arg, _dlist_back )
void DList_back( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_back

   Moves the cursor to the previous item in the list.

   @param  list DList_cursor_t instance
*/
#define DList_cursor_back( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_back )
void DList_cursor_back( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_go

   Moves the list's internal cursor to the ith item in the list. The first
   index is 0.

   @param  list DList_t instance
   @param  index the requested list position
*/
#define DList_go( arg ) PRIMITIVE_CAT( arg, _dlist_go )
void DList_go( Prefix )( DList_type( Prefix ) *list, int32_t index );

/**
   DList_cursor_go

   Moves the cursor to the ith item in the list. The first index is 0.

   @param  list DList_cursor_t instance
   @param  index the requested list position
*/
#define DList_cursor_go( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_go )
void DList_cursor_go( Prefix )( DList_cursor_type( Prefix ) *cursor, int32_t index );

/**
   DList_start

   Moves the list's internal cursor to the first item in the list.

   @param  list DList_t instance
*/
#define DList_start( arg ) PRIMITIVE_CAT( arg, _dlist_start )
void DList_start( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_start

   Moves the cursor to the first item in the list.

   @param  list DList_cursor_t instance
*/
#define DList_cursor_start( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_start )
void DList_cursor_start( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_finish

   Moves the list's internal cursor to the last item in the list.

   @param  list DList_t instance
*/
#define DList_finish( arg ) PRIMITIVE_CAT( arg, _dlist_finish )
void DList_finish( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_finish

   Moves the cursor to the last item in the list.

   @param  list DList_cursor_t instance
*/
#define DList_cursor_finish( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_finish )
void DList_cursor_finish( Prefix )( DList_cursor_type( Prefix ) *cursor );


/*
   Element change
*/

/**
   DList_put

   Insert value at index.

   @param  list DList_t instance
   @param  value what to insert
   @param  index where to insert value
*/
#define DList_put( arg ) PRIMITIVE_CAT( arg, _dlist_put )
void DList_put( Prefix )( DList_type( Prefix ) *list, Type value, int32_t index );

/**
   DList_put_right

   Insert value to right of list's internal cursor's position.

   @param  list DList_t instance
   @param  value what to insert
*/
#define DList_put_right( arg ) PRIMITIVE_CAT( arg, _dlist_put_right )
void DList_put_right( Prefix )( DList_type( Prefix ) *list, Type value );

/**
   DList_cursor_put_right

   Insert value to right of cursor's position.

   @param  cursor DList_cursor_t instance
   @param  value what to insert
*/
#define DList_cursor_put_right( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_put_right )
void DList_cursor_put_right( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value );

/**
   DList_put_left

   Insert value to left of list's internal cursor's position.

   @param  list DList_t instance
   @param  value what to insert
*/
#define DList_put_left( arg ) PRIMITIVE_CAT( arg, _dlist_put_left )
void DList_put_left( Prefix )( DList_type( Prefix ) *list, Type value );

/**
   DList_cursor_put_left

   Insert value to left of cursor's position.

   @param  cursor DList_cursor_t instance
   @param  value what to insert
*/
#define DList_cursor_put_left( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_put_left )
void DList_cursor_put_left( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value );

/**
   DList_put_first

   Insert value at beginning of list.

   @param  list DList_t instance
   @param  value what to insert
*/
#define DList_put_first( arg ) PRIMITIVE_CAT( arg, _dlist_put_first )
void DList_put_first( Prefix )( DList_type( Prefix ) *list, Type value );

/**
   DList_put_last

   Insert value at beginning of list.

   @param  list DList_t instance
   @param  value what to insert
*/
#define DList_put_last( arg ) PRIMITIVE_CAT( arg, _dlist_put_last )
void DList_put_last( Prefix )( DList_type( Prefix ) *list, Type value );

/**
   DList_replace

   Replace value with list item at index.

   @param  list DList_t instance
   @param  value what to replace with
   @param  index where to replace value
*/
#define DList_replace( arg ) PRIMITIVE_CAT( arg, _dlist_replace )
void DList_replace( Prefix )( DList_type( Prefix ) *list, Type value, int32_t index );

/**
   DList_replace_and_dispose

   Replace value with list item at index. Dispose of original value.

   @param  list DList_t instance
   @param  value what to replace with
   @param  index where to replace value
*/
#define DList_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_replace_and_dispose )
void DList_replace_and_dispose( Prefix )( DList_type( Prefix ) *list, Type value, int32_t index );

/**
   DList_replace_at

   Replace value at list's internal cursor's position.

   @param  list DList_t instance
   @param  value what to replace with
*/
#define DList_replace_at( arg ) PRIMITIVE_CAT( arg, _dlist_replace_at )
void DList_replace_at( Prefix )( DList_type( Prefix ) *list, Type value );

/**
   DList_cursor_replace_at

   Replace value at cursor's position.

   @param  cursor DList_cursor_t instance
   @param  value what to replace with
*/
#define DList_cursor_replace_at( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_replace_at )
void DList_cursor_replace_at( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value );

/**
   DList_replace_at_and_dispose

   Replace value at list's internal cursor's position. Dipose of original value.

   @param  list DList_t instance
   @param  value what to replace with
*/
#define DList_replace_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_replace_at_and_dispose )
void DList_replace_at_and_dispose( Prefix )( DList_type( Prefix ) *list, Type value );

/**
   DList_cursor_replace_at_and_dispose

   Replace value at cursor's position. Dipose of original value.

   @param  cursor DList_cursor_t instance
   @param  value what to replace with
*/
#define DList_cursor_replace_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_replace_at_and_dispose )
void DList_cursor_replace_at_and_dispose( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value );


/**
   DList_append

   Insert list at index.

   @param  list DList_t instance
   @param  other what to insert
   @param  index where to insert other
*/
#define DList_append( arg ) PRIMITIVE_CAT( arg, _dlist_append )
void DList_append( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other, int32_t index );

/**
   DList_append_right

   Insert other to right of list's internal cursor's position.

   @param  list DList_t instance
   @param  other what to insert
*/
#define DList_append_right( arg ) PRIMITIVE_CAT( arg, _dlist_append_right )
void DList_append_right( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other );

/**
   DList_cursor_append_right

   Insert other to right of cursor's position.

   @param  cursor DList_cursor_t instance
   @param  other what to insert
*/
#define DList_cursor_append_right( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_append_right )
void DList_cursor_append_right( Prefix )( DList_cursor_type( Prefix ) *cursor, DList_type( Prefix ) *other );

/**
   DList_append_left

   Insert other to left of list's internal cursor's position.

   @param  list DList_t instance
   @param  other what to insert
*/
#define DList_append_left( arg ) PRIMITIVE_CAT( arg, _dlist_append_left )
void DList_append_left( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other );

/**
   DList_cursor_append_left

   Insert other to left of cursor's position.

   @param  cursor DList_cursor_t instance
   @param  other what to insert
*/
#define DList_cursor_append_left( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_append_left )
void DList_cursor_append_left( Prefix )( DList_cursor_type( Prefix ) *cursor, DList_type( Prefix ) *other );

/**
   DList_append_first

   Insert other at beginning of list.

   @param  list DList_t instance
   @param  other what to insert
*/
#define DList_append_first( arg ) PRIMITIVE_CAT( arg, _dlist_append_first )
void DList_append_first( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other );

/**
   DList_append_last

   Insert other at beginning of list.

   @param  list DList_t instance
   @param  other what to insert
*/
#define DList_append_last( arg ) PRIMITIVE_CAT( arg, _dlist_append_last )
void DList_append_last( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other );


/*
   Removal
*/

/**
   DList_remove

   Remove value at index in list.

   @param  list DList_t instance
   @param  index where to remove value
*/
#define DList_remove( arg ) PRIMITIVE_CAT( arg, _dlist_remove )
void DList_remove( Prefix )( DList_type( Prefix ) *list, int32_t index );

/**
   DList_remove_and_dispose

   Remove value at index in list. Dipose of removed values.

   @param  list DList_t instance
   @param  index where to remove value
*/
#define DList_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_remove_and_dispose )
void DList_remove_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t index );

/**
   DList_remove_at

   Remove value at list's internal cursor's position.

   @param  list DList_t instance
*/
#define DList_remove_at( arg ) PRIMITIVE_CAT( arg, _dlist_remove_at )
void DList_remove_at( Prefix )( DList_type( Prefix ) *list );

/**
   DList_remove_at_and_dispose

   Remove value at list's internal cursor's position. Dipose of removed values.

   @param  list DList_t instance
*/
#define DList_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_remove_at_and_dispose )
void DList_remove_at_and_dispose( Prefix )( DList_type( Prefix ) *list );

/**
   DList_cursor_remove_at

   Remove value at cursor's position.

   @param  cursor DList_cursor_t instance
*/
#define DList_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_remove_at )
void DList_cursor_remove_at( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_cursor_remove_at_and_dispose

   Remove value at cursor's position. Dipose of removed values.

   @param  cursor DList_cursor_t instance
*/
#define DList_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_remove_at_and_dispose )
void DList_cursor_remove_at_and_dispose( Prefix )( DList_cursor_type( Prefix ) *cursor );

/**
   DList_remove_first

   Remove first value in list.

   @param  list DList_t instance
*/
#define DList_remove_first( arg ) PRIMITIVE_CAT( arg, _dlist_remove_first )
void DList_remove_first( Prefix )( DList_type( Prefix ) *list );

/**
   DList_remove_first_and_dispose

   Remove first value in list.

   @param  list DList_t instance
*/
#define DList_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_remove_first_and_dispose )
void DList_remove_first_and_dispose( Prefix )( DList_type( Prefix ) *list );

/**
   DList_remove_last

   Remove last value in list.

   @param  list DList_t instance
*/
#define DList_remove_last( arg ) PRIMITIVE_CAT( arg, _dlist_remove_last )
void DList_remove_last( Prefix )( DList_type( Prefix ) *list );

/**
   DList_remove_last_and_dispose

   Remove last value in list. Dipose of removed values.

   @param  list DList_t instance
*/
#define DList_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_remove_last_and_dispose )
void DList_remove_last_and_dispose( Prefix )( DList_type( Prefix ) *list );

/**
   DList_prune

   Remove count items starting at index in list.

   @param  list DList_t instance
   @param  index where to start pruning
   @param  count how many items to prune
*/
#define DList_prune( arg ) PRIMITIVE_CAT( arg, _dlist_prune )
void DList_prune( Prefix )( DList_type( Prefix ) *list, int32_t index, int32_t count );

/**
   DList_prune_and_dispose

   Remove count items starting at index in list.Dipose of removed values.

   @param  list DList_t instance
   @param  index where to start pruning
   @param  count how many items to prune
*/
#define DList_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_prune_and_dispose )
void DList_prune_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t index, int32_t count );

/**
   DList_prune_first

   Remove count items starting at beginning of list.

   @param  list DList_t instance
   @param  count how many items to prune
*/
#define DList_prune_first( arg ) PRIMITIVE_CAT( arg, _dlist_prune_first )
void DList_prune_first( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_prune_first_and_dispose

   Remove count items starting at beginning of list. Dipose of removed values.

   @param  list DList_t instance
   @param  count how many items to prune
*/
#define DList_prune_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_prune_first_and_dispose )
void DList_prune_first_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_prune_last

   Remove count items starting at end of list.

   @param  list DList_t instance
   @param  count how many items to prune
*/
#define DList_prune_last( arg ) PRIMITIVE_CAT( arg, _dlist_prune_last )
void DList_prune_last( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_prune_last_and_dispose

   Remove count items starting at end of list.

   @param  list DList_t instance
   @param  count how many items to prune
*/
#define DList_prune_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_prune_last_and_dispose )
void DList_prune_last_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_keep_first

   Remove items from end of list to leave count items at start of list.

   @param  list DList_t instance
   @param  count how many items to leave
*/
#define DList_keep_first( arg ) PRIMITIVE_CAT( arg, _dlist_keep_first )
void DList_keep_first( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_keep_first_and_dispose

   Remove items from end of list to leave count items at start of list.

   @param  list DList_t instance
   @param  count how many items to leave
*/
#define DList_keep_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_keep_first_and_dispose )
void DList_keep_first_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_keep_last

   Remove items from start of list to leave count items at end of list.

   @param  list DList_t instance
   @param  count how many items to leave
*/
#define DList_keep_last( arg ) PRIMITIVE_CAT( arg, _dlist_keep_last )
void DList_keep_last( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_keep_last_and_dispose

   Remove items from start of list to leave count items at end of list.
   Dipose of removed values.

   @param  list DList_t instance
   @param  count how many items to leave
*/
#define DList_keep_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_keep_last_and_dispose )
void DList_keep_last_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count );

/**
   DList_wipe_out

   Remove all items from list.

   @param  list DList_t instance
*/
#define DList_wipe_out( arg ) PRIMITIVE_CAT( arg, _dlist_wipe_out )
void DList_wipe_out( Prefix )( DList_type( Prefix ) *list );

/**
   DList_wipe_out_and_dispose

   Remove all items from list. Dipose of removed values.

   @param  list DList_t instance
*/
#define DList_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _dlist_wipe_out_and_dispose )
void DList_wipe_out_and_dispose( Prefix )( DList_type( Prefix ) *list );

/**
   DList_has

   Returns 1 if DList contains item using "==" as comparison test

   @param current the DList
   @param item the item to look for
*/
#define DList_has( arg ) PRIMITIVE_CAT( arg, _dlist_has )
int32_t DList_has( Prefix )( DList_type( Prefix ) *current, Type value );

/**
   DList_has_eq_fn

   Returns 1 if DList contains item using equality_test_func as comparison test

   @param current the DList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define DList_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _dlist_has_eq_fn )
int32_t DList_has_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
   Type value, int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   DList_search_forth

   Search through DList starting at current position, stopping when item
   is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param current the DList
   @param item the item to look for
*/
#define DList_search_forth( arg ) PRIMITIVE_CAT( arg, _dlist_search_forth )
void DList_search_forth( Prefix )( DList_type( Prefix ) *current, Type value );

/**
   DList_search_forth_eq_fn

   Search through DList starting at current position, stopping when item
   is equal to value, using equality_test_func as comparison test
   if value not found, list will be "off"

   @param current the DList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define DList_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _dlist_search_forth_eq_fn )
void DList_search_forth_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   DList_search_back

   Search backwards through DList starting at current position, stopping when
   item is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param current the DList
   @param item the item to look for
*/
#define DList_search_back( arg ) PRIMITIVE_CAT( arg, _dlist_search_back )
void DList_search_back( Prefix )( DList_type( Prefix ) *current, Type value );

/**
   DList_search_back_eq_fn

   Search backwards through DList starting at current
   position, stopping when item is equal to value, using equality_test_func as
   comparison test.
   if value not found, list will be "off"

   @param current the DList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define DList_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _dlist_search_back_eq_fn )
void DList_search_back_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   DList_cursor_search_forth

   Search through DList starting at current cursor position, stopping when item
   is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param cursor the DList cursor
   @param item the item to look for
*/
#define DList_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_search_forth )
void DList_cursor_search_forth( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value );

/**
   DList_cursor_search_forth_eq_fn

   Search through DList starting at current cursor position, stopping when item
   is equal to value, using equality_test_func as comparison test
   if value not found, list will be "off"

   @param cursor the DList cursor
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define DList_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_search_forth_eq_fn )
void DList_cursor_search_forth_eq_fn( Prefix )
(
   DList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   DList_cursor_search_back

   Search backwards through DList starting at current cursor position, stopping when
   item is equal to value, using "==" as comparison test
   if value not found, list will be "off"

   @param cursor the DList cursor
   @param item the item to look for
*/
#define DList_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_search_back )
void DList_cursor_search_back( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value );

/**
   DList_cursor_search_back_eq_fn

   Search backwards through DList starting at current cursor
   position, stopping when item is equal to value, using equality_test_func as
   comparison test.
   if value not found, list will be "off"

   @param cursor the DList cursor
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define DList_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _dlist_cursor_search_back_eq_fn )
void DList_cursor_search_back_eq_fn( Prefix )
(
   DList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   DList_occurrences

   Returns count of items in DList equal to value using "==" as comparison test

   @param current the DList
   @param item the item to look for
*/
#define DList_occurrences( arg ) PRIMITIVE_CAT( arg, _dlist_occurrences )
int32_t DList_occurrences( Prefix )( DList_type( Prefix ) *current, Type value );

/**
   DList_occurrences_eq_fn

   Returns count of items in DList equal to value using equality_test_func
   as comparison test

   @param current the DList
   @param item the item to look for
   @param equality_test_func the function to compare values with
*/
#define DList_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _dlist_occurrences_eq_fn )
int32_t DList_occurrences_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   DList_swap

   Swaps items in DList at index i and j

   @param current the DList
   @param i an index into the list
   @param j the other index into the list
*/
#define DList_swap( arg ) PRIMITIVE_CAT( arg, _dlist_swap )
void DList_swap( Prefix )( DList_type( Prefix ) *current, int32_t i, int32_t j );


/**
   DList_sort

   Sort items in list using sort_func.

   @param  list DList_t instance
   @param sort_func function compare two list items
*/
#define DList_sort( arg ) PRIMITIVE_CAT( arg, _dlist_sort )
void DList_sort( Prefix )( DList_type( Prefix ) *list, int32_t (*func)( Type v1, Type v2 ) );


#ifdef __cplusplus
}
#endif

/* End of file */




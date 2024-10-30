/**
 @file BSTree.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Binary Search Trees"

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

 Function declarations for the opaque BSTree_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define BSTREE_VERSION_MAJOR 2
#define BSTREE_VERSION_MINOR 0
#define BSTREE_VERSION_PATCH 0

#define BSTREE_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define BSTREE_VERSION \
   BSTREE_MAKE_VERSION( BSTREE_VERSION_MAJOR, \
                       BSTREE_VERSION_MINOR, \
                       BSTREE_VERSION_PATCH )

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
   VALUE_DEEP_CLONE_FUNCTION     - makes a duplicate of a value
   VALUE_DEEP_EQUAL_FUNCTION     - compares two instances for equality
   VALUE_DEFAULT                 -- value default

   ORDER_FUNCTION                -  returns 1 if first argument is "before" second argument

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define BSTree_struct( arg ) PRIMITIVE_CAT( arg, _bstree_struct )
#define BSTree_type( arg ) PRIMITIVE_CAT( arg, _bstree_t )
#define BSTree_name( arg ) PRIMITIVE_CAT( arg, _bstree )

#define BSTree_cursor_struct( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_struct )
#define BSTree_cursor_type( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_t )
#define BSTree_cursor_name( arg ) PRIMITIVE_CAT( arg, _bstree_cursor )

/**
   Structure declarations
*/

struct BSTree_struct( Prefix );
struct BSTree_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct BSTree_struct( Prefix ) BSTree_type( Prefix );
typedef struct BSTree_cursor_struct( Prefix ) BSTree_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   BSTree_make

   Return a new BSTree_t instance with a default number of buckets.

   @return BSTree_t instance
*/
#define BSTree_make( arg ) PRIMITIVE_CAT( arg, _bstree_make )
BSTree_type( Prefix ) * BSTree_make( Prefix )( void );

/**
   BSTree_make_from_array

   Return a new BSTree_t instance that has the same content as array. The
   items in array are not copied.

   @param  current the BSTree_t instance to copy from
   @return BSTree_t instance
*/
#define BSTree_make_from_array( arg ) PRIMITIVE_CAT( arg, _bstree_make_from_array )
BSTree_type( Prefix ) * BSTree_make_from_array( Prefix )( Type *array, int32_t count );

/**
   BSTree_clone

   Return a new BSTree_t instance that has the same content as bstree. The
   items in bstree are not copied.

   @param  current the BSTree_t instance to copy from
   @return BSTree_t instance
*/
#define BSTree_clone( arg ) PRIMITIVE_CAT( arg, _bstree_clone )
BSTree_type( Prefix ) * BSTree_clone( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_deep_clone

   Return a new BSTree_t instance with a duplicate items from bstree

   @return BSTree_t instance
*/

#define BSTree_deep_clone( arg ) PRIMITIVE_CAT( arg, _bstree_deep_clone )
BSTree_type( Prefix ) *
BSTree_deep_clone( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_is_equal

   Check that bstree contains same elements as other

   @param  current BSTree_t instance
   @param  other BSTree_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define BSTree_is_equal( arg ) PRIMITIVE_CAT( arg, _bstree_is_equal )
int32_t
BSTree_is_equal( Prefix )( BSTree_type( Prefix ) *current, BSTree_type( Prefix ) *other );

/**
   BSTree_is_deep_equal

   Check that bstree contains same elements as other

   @param  current BSTree_t instance
   @param  other BSTree_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define BSTree_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _bstree_is_deep_equal )
int32_t
BSTree_is_deep_equal( Prefix )( BSTree_type( Prefix ) *current, BSTree_type( Prefix ) *other );

/**
   BSTree_copy

   Copy other into current

   @param  current BSTree_t instance
   @param  other BSTree_t instance to copy from

*/

#define BSTree_copy( arg ) PRIMITIVE_CAT( arg, _bstree_copy )
void
BSTree_copy( Prefix )( BSTree_type( Prefix ) *current, BSTree_type( Prefix ) *other );

/**
   BSTree_deep_copy

   Deep copy other into current

   @param  current BSTree_t instance
   @param  other BSTree_t instance to deep_copy from

*/

#define BSTree_deep_copy( arg ) PRIMITIVE_CAT( arg, _bstree_deep_copy )
void
BSTree_deep_copy( Prefix )( BSTree_type( Prefix ) *current, BSTree_type( Prefix ) *other );


/**
   BSTree_cursor_make

   Return a new BSTree_t cursor instance.

   @param  current the BSTree_t instance the new cursor works on
   @return BSTree_cursor_t instance
*/
#define BSTree_cursor_make( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_make )
BSTree_cursor_type( Prefix ) * BSTree_cursor_make( Prefix )( BSTree_type( Prefix ) *current );


/*
   Disposal
*/

/**
   BSTree_dispose

   Frees a BSTree_t instance without freeing its contained keys and values.

   @param current BSTree_t instance
*/
#define BSTree_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_dispose )
void BSTree_dispose( Prefix )( BSTree_type( Prefix ) **current );

/**
   BSTree_deep_dispose

   Frees a BSTree_t instance and its contained keys and values.

   @param current BSTree_t instance
*/
#define BSTree_deep_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_deep_dispose )
void BSTree_deep_dispose( Prefix )( BSTree_type( Prefix ) **current );

/**
   BSTree_cursor_dispose

   Frees a BSTree_cursor_t instance. Its bstree is not disposed.

   @param current BSTree_cursor_t instance
*/
#define BSTree_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_dispose )
void BSTree_cursor_dispose( Prefix )( BSTree_cursor_type( Prefix ) **cursor );


/*
   Access
*/

/**
   BSTree_cursor_item_at

   Returns the value of the item that the BSTree_cursor_t instance is pointing to.

   @param  current BSTree_cursor_t instance
   @return a Type value
*/
#define BSTree_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_item_at )
Type BSTree_cursor_item_at( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_item_at

   Returns the value of the item that the BSTree_t instance's internal
   cursor is pointing to.

   @param  current BSTree_t instance
   @return a Type value
*/
#define BSTree_item_at( arg ) PRIMITIVE_CAT( arg, _bstree_item_at )
Type BSTree_item_at( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_item

   Returns the value of the item pointed to by index. First index is 0.

   @param  current BSTree_t instance
   @param  index desired index
   @return a Type value
*/
#define BSTree_item( arg ) PRIMITIVE_CAT( arg, _bstree_item )
Type BSTree_item( Prefix )( BSTree_type( Prefix ) *current, int32_t index );

/**
   BSTree_first

   Returns the value of the first item.

   @param  current BSTree_t instance
   @return a Type value
*/
#define BSTree_first( arg ) PRIMITIVE_CAT( arg, _bstree_first )
Type BSTree_first( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_last

   Returns the value of the last item.

   @param  current BSTree_t instance
   @return a Type value
*/
#define BSTree_last( arg ) PRIMITIVE_CAT( arg, _bstree_last )
Type BSTree_last( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_as_array

   Returns the values of the items in the BSTree_t instance as an array.

   @param  current BSTree_t instance
   @param  count pointer to the returned count
   @return array of values
*/
#define BSTree_as_array( arg ) PRIMITIVE_CAT( arg, _bstree_as_array )
Type * BSTree_as_array( Prefix )( BSTree_type( Prefix ) *current, int32_t *count );


/*
   Measurement
*/

/**
   BSTree_count

   Returns the number of items in the BSTree_t instance.

   @param  current BSTree_t instance
   @return number of items in BSTree instance
*/
#define BSTree_count( arg ) PRIMITIVE_CAT( arg, _bstree_count )
int32_t BSTree_count( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_height

   Returns the (max) height of the BSTree_t instance.

   @param  current BSTree_t instance
   @return (max) height of the BSTree instance
*/
#define BSTree_height( arg ) PRIMITIVE_CAT( arg, _bstree_height )
int32_t BSTree_height( Prefix )( BSTree_type( Prefix ) *current );


/*
   Status report
*/

/**
   BSTree_off

   Returns 1 if the BSTree_t instance's internal cursor is off, otherwise 0.

   @param  current BSTree_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define BSTree_off( arg ) PRIMITIVE_CAT( arg, _bstree_off )
int32_t BSTree_off( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_is_first

   Returns 1 if the BSTree_t instance's internal cursor is at "start", otherwise 0.

   @param  current BSTree_t instance
   @return 1 if internal cursor is at "start", otherwise 0
*/
#define BSTree_is_first( arg ) PRIMITIVE_CAT( arg, _bstree_is_first )
int32_t BSTree_is_first( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_is_last

   Returns 1 if the BSTree_t instance's internal cursor is at "finish", otherwise 0.

   @param  current BSTree_t instance
   @return 1 if internal cursor is at "finish", otherwise 0
*/
#define BSTree_is_last( arg ) PRIMITIVE_CAT( arg, _bstree_is_last )
int32_t BSTree_is_last( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_cursor_off

   Returns 1 if the BSTree_cursor_t instance is off, otherwise 0.

   @param  cursor BSTree_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define BSTree_cursor_off( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_off )
int32_t BSTree_cursor_off( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_is_first

   Returns 1 if the BSTree_cursor_t instance is at "start", otherwise 0.

   @param  cursor BSTree_cursor_t instance
   @return 1 if internal cursor is at "start", otherwise 0
*/
#define BSTree_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_is_first )
int32_t BSTree_cursor_is_first( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_is_last

   Returns 1 if the BSTree_cursor_t instance is at "finish", otherwise 0.

   @param  cursor BSTree_cursor_t instance
   @return 1 if internal cursor is at "finish", otherwise 0
*/
#define BSTree_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_is_last )
int32_t BSTree_cursor_is_last( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_search_forth

   Sets internal cursor to next item found searching forth, or off if
   nothing found.

   @param  cursor BSTree_cursor_t instance
   @param  value the value to search for
*/
#define BSTree_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_search_forth )
void BSTree_cursor_search_forth( Prefix )( BSTree_cursor_type( Prefix ) *cursor, Type value );

/**
   BSTree_cursor_search_forth_eq_fn

   Sets internal cursor to next item found searching forth using
   equality_test_func, or off if nothing found.

   @param  cursor BSTree_cursor_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define BSTree_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_search_forth_eq_fn )
void BSTree_cursor_search_forth_eq_fn( Prefix )
(
   BSTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_cursor_search_back

   Sets internal cursor to next item found searching back, or off if
   nothing found.

   @param  cursor BSTree_cursor_t instance
   @param  value the value to search for
*/
#define BSTree_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_search_back )
void BSTree_cursor_search_back( Prefix )( BSTree_cursor_type( Prefix ) *cursor, Type value );

/**
   BSTree_cursor_search_back_eq_fn

   Sets internal cursor to next item found searching back using
   equality_test_func, or off if nothing found.

   @param  cursor BSTree_cursor_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define BSTree_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_search_back_eq_fn )
void BSTree_cursor_search_back_eq_fn( Prefix )
(
   BSTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_is_empty

   Returns 1 if the BSTree_t instance contains no items, otherwise 0.

   @param  current BSTree_t instance
   @return 1 if empty, otherwise 0
*/
#define BSTree_is_empty( arg ) PRIMITIVE_CAT( arg, _bstree_is_empty )
int32_t BSTree_is_empty( Prefix )( BSTree_type( Prefix ) *current );

/*
   Search
*/

/**
   BSTree_has

   Returns 1 if the BSTree_t instance contains the key, otherwise 0.

   @param  current BSTree_t instance
   @param  value the value to search for
   @return 1 if bstree has key, otherwise 0
*/
#define BSTree_has( arg ) PRIMITIVE_CAT( arg, _bstree_has )
int32_t BSTree_has( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_has_eq_fn

   Returns 1 if the BSTree_t instance has a key that returns 1 for
   test_equality_fn, otherwise 0.

   @param  current BSTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
   @return 1 if bstree has key, otherwise 0
*/
#define BSTree_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_has_eq_fn )
int32_t BSTree_has_eq_fn( Prefix )
(
   BSTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_occurrences

   Returns count of how many equal keys are in the BSTree_t instance.

   @param  current BSTree_t instance
   @param  value the value to search for
   @return count of equal keys
*/
#define BSTree_occurrences( arg ) PRIMITIVE_CAT( arg, _bstree_occurrences )
int32_t BSTree_occurrences( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_occurrences_eq_fn

   Returns count of how many equal keys are in the BSTree_t instance according
   to equality_test_fn.

   @param  current BSTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
   @return count of equal keys
*/
#define BSTree_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_occurrences_eq_fn )
int32_t BSTree_occurrences_eq_fn( Prefix )
(
   BSTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_search_forth

   Sets internal cursor to next item found searching forth, or off if
   nothing found.

   @param  current BSTree_t instance
   @param  value the value to search for
*/
#define BSTree_search_forth( arg ) PRIMITIVE_CAT( arg, _bstree_search_forth )
void BSTree_search_forth( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_search_forth_eq_fn

   Sets internal cursor to next item found searching forth using
   equality_test_func, or off if nothing found.

   @param  current BSTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define BSTree_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_search_forth_eq_fn )
void BSTree_search_forth_eq_fn( Prefix )
(
   BSTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_search_back

   Sets internal cursor to next item found searching back, or off if
   nothing found.

   @param  current BSTree_t instance
   @param  value the value to search for
*/
#define BSTree_search_back( arg ) PRIMITIVE_CAT( arg, _bstree_search_back )
void BSTree_search_back( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_search_back_eq_fn

   Sets internal cursor to next item found searching back using
   equality_test_func, or off if nothing found.

   @param  current BSTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define BSTree_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_search_back_eq_fn )
void BSTree_search_back_eq_fn( Prefix )
(
   BSTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);


/*
   Cursor movement
*/

/**
   BSTree_cursor_back

   Moves the BSTree_cursor_t instance to the previous item or off.

   @param  current_cursor BSTree_cursor_t instance
*/
#define BSTree_cursor_back( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_back )
void BSTree_cursor_back( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_forth

   Moves the BSTree_cursor_t instance to the next item or off.

   @param  current_cursor BSTree_cursor_t instance
*/
#define BSTree_cursor_forth( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_forth )
void BSTree_cursor_forth( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_go

   Moves the BSTree_t instance's internal cursor to the ith item in the bstree.

   @param  current_cursor BSTree_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define BSTree_cursor_go( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_go )
void BSTree_cursor_go( Prefix )( BSTree_cursor_type( Prefix ) *cursor, int32_t index );

/**
   BSTree_cursor_go_to_value

   Moves the BSTree_t instance's internal cursor to the item in bstree with the
   same value or if not present, the item in the bstree with the value less than
   and closest to the desired value .

   @param  current_cursor BSTree_cursor_t instance
   @param  value the value of the item where the cursor will be moved to
*/
#define BSTree_cursor_go_to_value( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_go_to_value )
void BSTree_cursor_go_to_value( Prefix )( BSTree_cursor_type( Prefix ) *cursor, Type value );

/**
   BSTree_cursor_start

   Moves the BSTree_cursor_t instance to the first item or off if the bstree is empty.

   @param  current_cursor BSTree_cursor_t instance
*/
#define BSTree_cursor_start( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_start )
void BSTree_cursor_start( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_finish

   Moves the BSTree_cursor_t instance to the last item or off if the bstree is empty.

   @param  current_cursor BSTree_cursor_t instance
*/
#define BSTree_cursor_finish( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_finish )
void BSTree_cursor_finish( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  currenT BSTree_cursor_t instance
   @return index in bstree of cursor if not off, -1 otherwise
*/
#define BSTree_cursor_index( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_index )
int32_t BSTree_cursor_index( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_remove_at

   Removes item pointed to by the cursor.

   @param  cursor BSTree_cursor_t instance
*/
#define BSTree_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_remove_at )
void BSTree_cursor_remove_at( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_remove_at_and_dispose

   Removes and disposes of item pointed to by the cursor.

   @param  cursor BSTree_cursor_t instance
*/
#define BSTree_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_remove_at_and_dispose )
void BSTree_cursor_remove_at_and_dispose( Prefix )( BSTree_cursor_type( Prefix ) *cursor );


/**
   BSTree_back

   Moves the BSTree_t instance internal cursor to the previous item or off.

   @param  current BSTree_t instance
*/
#define BSTree_back( arg ) PRIMITIVE_CAT( arg, _bstree_back )
void BSTree_back( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_forth

   Moves the BSTree_t instance internal cursor to the next item or off.

   @param  current BSTree_t instance
*/
#define BSTree_forth( arg ) PRIMITIVE_CAT( arg, _bstree_forth )
void BSTree_forth( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_go

   Moves the BSTree_t instance's internal cursor to the ith item in the bstree.

   @param  current BSTree_t instance
   @param  index the index where the internal cursor will be moved to
*/
#define BSTree_go( arg ) PRIMITIVE_CAT( arg, _bstree_go )
void BSTree_go( Prefix )( BSTree_type( Prefix ) *current, int32_t index );

/**
   BSTree_go_to_value

   Moves the BSTree_t instance's internal cursor to the item in the bstree with \
   the desired value or if not present to the item just before where the desired
   value would be.

   @param  current BSTree_t instance
   @param  value the value where the internal cursor will be moved to
*/
#define BSTree_go_to_value( arg ) PRIMITIVE_CAT( arg, _bstree_go_to_value )
void BSTree_go_to_value( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_start

   Moves the BSTree_t instance's internal cursor to the first item or off if the bstree is empty.

   @param  current BSTree_t instance
*/
#define BSTree_start( arg ) PRIMITIVE_CAT( arg, _bstree_start )
void BSTree_start( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_finish

   Moves the BSTree_t instance's internal cursor to the last item or off if the bstree is empty.

   @param  current BSTree_t instance
*/
#define BSTree_finish( arg ) PRIMITIVE_CAT( arg, _bstree_finish )
void BSTree_finish( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  current BSTree_t instance
   @return index in bstree of internal cursor if not off, -1 otherwise
*/
#define BSTree_index( arg ) PRIMITIVE_CAT( arg, _bstree_index )
int32_t BSTree_index( Prefix )( BSTree_type( Prefix ) *bstree );



/*
   Element change
*/

/**
   BSTree_put

   Put the key-value pair into the BSTree_t instance. Replace any existing item
   that has the same key.

   @param  current BSTree_t instance
   @param  value the value to insert
*/
#define BSTree_put( arg ) PRIMITIVE_CAT( arg, _bstree_put )
void BSTree_put( Prefix )( BSTree_type( Prefix ) *current, Type value );


/*
   Removal
*/

/**
   BSTree_remove

   Remove the item in the BSTree_t instance at the index.

   @param  current BSTree_t instance
   @param index the index of the item to remove
*/
#define BSTree_remove( arg ) PRIMITIVE_CAT( arg, _bstree_remove )
void BSTree_remove( Prefix )( BSTree_type( Prefix ) *current, int32_t index );

/**
   BSTree_remove_and_dispose

   Remove the item in the BSTree_t instance at the index and dispose
   of the key and the value.

   @param  current BSTree_t instance
   @param index the index of the item to remove
*/
#define BSTree_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_remove_and_dispose )
void BSTree_remove_and_dispose( Prefix )( BSTree_type( Prefix ) *current, int32_t index );

/**
   BSTree_remove_value

   Remove the item in the BSTree_t instance that has the key.

   @param  current BSTree_t instance
   @param  key the key for the value
*/
#define BSTree_remove_value( arg ) PRIMITIVE_CAT( arg, _bstree_remove_value )
void BSTree_remove_value( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_remove_value_and_dispose

   Remove the item in the BSTree_t instance that has the key and dispose
   of the key and the value.

   @param  current BSTree_t instance
   @param  key the key for the value
*/
#define BSTree_remove_value_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_remove_value_and_dispose )
void BSTree_remove_value_and_dispose( Prefix )( BSTree_type( Prefix ) *current, Type value );

/**
   BSTree_remove_at

   Remove the item in the BSTree_t instance at the internal cursor.

   @param current BSTree_t instance
*/
#define BSTree_remove_at( arg ) PRIMITIVE_CAT( arg, _bstree_remove_at )
void BSTree_remove_at( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_remove_at_and_dispose

   Remove the item in the BSTree_t instance at the cursor and dispose
   of the key and the value.

   @param current BSTree_t instance
*/
#define BSTree_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_remove_at_and_dispose )
void BSTree_remove_at_and_dispose( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_remove_first

   Remove the first item in the BSTree_t instance.

   @param current BSTree_t instance
*/
#define BSTree_remove_first( arg ) PRIMITIVE_CAT( arg, _bstree_remove_first )
void BSTree_remove_first( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_remove_first_and_dispose

   Remove and dispose the first item in the BSTree_t instance.

   @param current BSTree_t instance
*/
#define BSTree_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_remove_first_and_dispose )
void BSTree_remove_first_and_dispose( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_remove_last

   Remove the last item in the BSTree_t instance.

   @param current BSTree_t instance
*/
#define BSTree_remove_last( arg ) PRIMITIVE_CAT( arg, _bstree_remove_last )
void BSTree_remove_last( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_remove_last_and_dispose

   Remove and dispose the last item in the BSTree_t instance.

   @param current BSTree_t instance
*/
#define BSTree_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_remove_last_and_dispose )
void BSTree_remove_last_and_dispose( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_wipe_out

   Remove all items in the BSTree_t instance.

   @param  current BSTree_t instance
*/
#define BSTree_wipe_out( arg ) PRIMITIVE_CAT( arg, _bstree_wipe_out )
void BSTree_wipe_out( Prefix )( BSTree_type( Prefix ) *current );

/**
   BSTree_wipe_out_and_dispose

   Remove all items in the BSTree_t instance. Dispose of all keys and values.

   @param  current BSTree_t instance
*/
#define BSTree_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_wipe_out_and_dispose )
void BSTree_wipe_out_and_dispose( Prefix )( BSTree_type( Prefix ) *current );


/*
   Resize
*/

/**
   BSTree_balance

   Balance the tree

   @param  current BSTree_t instance
*/
#define BSTree_balance( arg ) PRIMITIVE_CAT( arg, _bstree_balance )
void BSTree_balance( Prefix )( BSTree_type( Prefix ) *current );


#ifdef __cplusplus
}
#endif

/* End of file */




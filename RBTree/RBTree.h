/**
 @file RBTree.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Red Black Binary Search Trees"

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

 Function declarations for the opaque RBTree_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define RBTREE_VERSION_MAJOR 2
#define RBTREE_VERSION_MINOR 0
#define RBTREE_VERSION_PATCH 0

#define RBTREE_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define RBTREE_VERSION \
   RBTREE_MAKE_VERSION( RBTREE_VERSION_MAJOR, \
                       RBTREE_VERSION_MINOR, \
                       RBTREE_VERSION_PATCH )

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

#define RBTree_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_struct )
#define RBTree_type( arg ) PRIMITIVE_CAT( arg, _rbtree_t )
#define RBTree_name( arg ) PRIMITIVE_CAT( arg, _rbtree )

#define RBTree_cursor_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_struct )
#define RBTree_cursor_type( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_t )
#define RBTree_cursor_name( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor )

/**
   Structure declarations
*/

struct RBTree_struct( Prefix );
struct RBTree_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct RBTree_struct( Prefix ) RBTree_type( Prefix );
typedef struct RBTree_cursor_struct( Prefix ) RBTree_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   RBTree_make

   Return a new RBTree_t instance with a default number of buckets.

   @return RBTree_t instance
*/
#define RBTree_make( arg ) PRIMITIVE_CAT( arg, _rbtree_make )
RBTree_type( Prefix ) * RBTree_make( Prefix )( void );

/**
   RBTree_make_from_array

   Return a new RBTree_t instance that has the same content as array. The key
   and value items in rbtree are not copied.

   @param  rbtree the RBTree_t instance to copy from
   @return RBTree_t instance
*/
#define RBTree_make_from_array( arg ) PRIMITIVE_CAT( arg, _rbtree_make_from_array )
RBTree_type( Prefix ) * RBTree_make_from_array( Prefix )( Type *array, int32_t count );

/**
   RBTree_clone

   Return a new RBTree_t instance that has the same content as rbtree. The key
   and value items in rbtree are not copied.

   @param  rbtree the RBTree_t instance to copy from
   @return RBTree_t instance
*/
#define RBTree_clone( arg ) PRIMITIVE_CAT( arg, _rbtree_clone )
RBTree_type( Prefix ) * RBTree_clone( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_deep_clone

   Return a new RBTree_t instance with a duplicate items from rbtree

   @return RBTree_t instance
*/

#define RBTree_deep_clone( arg ) PRIMITIVE_CAT( arg, _rbtree_deep_clone )
RBTree_type( Prefix ) *
RBTree_deep_clone( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_is_equal

   Check that rbtree contains same elements as other

   @param  current RBTree_t instance
   @param  other RBTree_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define RBTree_is_equal( arg ) PRIMITIVE_CAT( arg, _rbtree_is_equal )
int32_t
RBTree_is_equal( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other );

/**
   RBTree_is_deep_equal

   Check that rbtree contains same elements as other

   @param  current RBTree_t instance
   @param  other RBTree_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define RBTree_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _rbtree_is_deep_equal )
int32_t
RBTree_is_deep_equal( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other );

/**
   RBTree_copy

   Copy other into current

   @param  current RBTree_t instance
   @param  other RBTree_t instance to copy from

*/

#define RBTree_copy( arg ) PRIMITIVE_CAT( arg, _rbtree_copy )
void
RBTree_copy( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other );

/**
   RBTree_deep_copy

   Deep copy other into current

   @param  current RBTree_t instance
   @param  other RBTree_t instance to deep_copy from

*/

#define RBTree_deep_copy( arg ) PRIMITIVE_CAT( arg, _rbtree_deep_copy )
void
RBTree_deep_copy( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other );


/**
   RBTree_cursor_make

   Return a new RBTree_t cursor instance.

   @param  the RBTree_t instance the new cursor works on
   @return RBTree_cursor_t instance
*/
#define RBTree_cursor_make( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_make )
RBTree_cursor_type( Prefix ) * RBTree_cursor_make( Prefix )( RBTree_type( Prefix ) *rbtree );


/**
   Disposal
*/

/**
   RBTree_dispose

   Frees a RBTree_t instance without freeing its contained keys and values.

   @param RBTree_t instance
*/
#define RBTree_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_dispose )
void RBTree_dispose( Prefix )( RBTree_type( Prefix ) **rbtree );

/**
   RBTree_deep_dispose

   Frees a RBTree_t instance and its contained keys and values.

   @param RBTree_t instance
*/
#define RBTree_deep_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_deep_dispose )
void RBTree_deep_dispose( Prefix )( RBTree_type( Prefix ) **rbtree );

/**
   RBTree_cursor_dispose

   Frees a RBTree_cursor_t instance. Its rbtree is not disposed.

   @param RBTree_cursor_t instance
*/
#define RBTree_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_dispose )
void RBTree_cursor_dispose( Prefix )( RBTree_cursor_type( Prefix ) **cursor );


/*
   Access
*/

/**
   RBTree_cursor_item_at

   Returns the value of the item that the RBTree_cursor_t instance is pointing to.

   @param  RBTree_cursor_t instance
   @return a Type value
*/
#define RBTree_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_item_at )
Type RBTree_cursor_item_at( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_item_at

   Returns the value of the item that the RBTree_t instance's internal
   cursor is pointing to.

   @param  rbtree RBTree_t instance
   @return a Type value
*/
#define RBTree_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_item_at )
Type RBTree_item_at( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_item

   Returns the value of the item pointed to by index. First index is 0.

   @param  rbtree RBTree_t instance
   @param  index desired index
   @return a Type value
*/
#define RBTree_item( arg ) PRIMITIVE_CAT( arg, _rbtree_item )
Type RBTree_item( Prefix )( RBTree_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_first

   Returns the value of the first item.

   @param  current RBTree_t instance
   @return a Type value
*/
#define RBTree_first( arg ) PRIMITIVE_CAT( arg, _rbtree_first )
Type RBTree_first( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_last

   Returns the value of the last item.

   @param  current RBTree_t instance
   @return a Type value
*/
#define RBTree_last( arg ) PRIMITIVE_CAT( arg, _rbtree_last )
Type RBTree_last( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_as_array

   Returns the values as an array.

   @param  RBTree_t instance
   @param  count how many items in array
   @return array of Type values
*/
#define RBTree_as_array( arg ) PRIMITIVE_CAT( arg, _rbtree_as_array )
Type *RBTree_as_array( Prefix )( RBTree_type( Prefix ) *rbtree, int32_t *count );


/*
   Measurement
*/

/**
   RBTree_count

   Returns the number of items in the RBTree_t instance.

   @param  rbtree RBTree_t instance
   @return number of items in RBTree instance
*/
#define RBTree_count( arg ) PRIMITIVE_CAT( arg, _rbtree_count )
int32_t RBTree_count( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_height

   Returns the (max) height of the RBTree_t instance.

   @param  rbtree RBTree_t instance
   @return (max) height of the RBTree instance
*/
#define RBTree_height( arg ) PRIMITIVE_CAT( arg, _rbtree_height )
int32_t RBTree_height( Prefix )( RBTree_type( Prefix ) *rbtree );


/*
   Status report
*/

/**
   RBTree_off

   Returns 1 if the RBTree_t instance's internal cursor is off, otherwise 0.

   @param  rbtree RBTree_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_off( arg ) PRIMITIVE_CAT( arg, _rbtree_off )
int32_t RBTree_off( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_is_first

   Returns 1 if the RBTree_t instance's internal cursor is at "start", otherwise 0.

   @param  current RBTree_t instance
   @return 1 if internal cursor is at "start", otherwise 0
*/
#define RBTree_is_first( arg ) PRIMITIVE_CAT( arg, _rbtree_is_first )
int32_t RBTree_is_first( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_is_last

   Returns 1 if the RBTree_t instance's internal cursor is at "finish", otherwise 0.

   @param  current RBTree_t instance
   @return 1 if internal cursor is at "finish", otherwise 0
*/
#define RBTree_is_last( arg ) PRIMITIVE_CAT( arg, _rbtree_is_last )
int32_t RBTree_is_last( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_cursor_off

   Returns 1 if the RBTree_cursor_t instance is off, otherwise 0.

   @param  cursor RBTree_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_cursor_off( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_off )
int32_t RBTree_cursor_off( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_is_first

   Returns 1 if the RBTree_cursor_t instance is at "start", otherwise 0.

   @param  cursor RBTree_cursor_t instance
   @return 1 if internal cursor is at "start", otherwise 0
*/
#define RBTree_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_is_first )
int32_t RBTree_cursor_is_first( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_is_last

   Returns 1 if the RBTree_cursor_t instance is at "finish", otherwise 0.

   @param  cursor RBTree_cursor_t instance
   @return 1 if internal cursor is at "finish", otherwise 0
*/
#define RBTree_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_is_last )
int32_t RBTree_cursor_is_last( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_search_forth

   Sets internal cursor to next item found searching forth, or off if
   nothing found.

   @param  cursor RBTree_cursor_t instance
   @param  value the value to search for
*/
#define RBTree_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_search_forth )
void RBTree_cursor_search_forth( Prefix )( RBTree_cursor_type( Prefix ) *cursor, Type value );

/**
   RBTree_cursor_search_forth_eq_fn

   Sets internal cursor to next item found searching forth using
   equality_test_func, or off if nothing found.

   @param  cursor RBTree_cursor_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define RBTree_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_search_forth_eq_fn )
void RBTree_cursor_search_forth_eq_fn( Prefix )
(
   RBTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_cursor_search_back

   Sets internal cursor to next item found searching back, or off if
   nothing found.

   @param  cursor RBTree_cursor_t instance
   @param  value the value to search for
*/
#define RBTree_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_search_back )
void RBTree_cursor_search_back( Prefix )( RBTree_cursor_type( Prefix ) *cursor, Type value );

/**
   RBTree_cursor_search_back_eq_fn

   Sets internal cursor to next item found searching back using
   equality_test_func, or off if nothing found.

   @param  cursor RBTree_cursor_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define RBTree_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_search_back_eq_fn )
void RBTree_cursor_search_back_eq_fn( Prefix )
(
   RBTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_is_empty

   Returns 1 if the RBTree_t instance contains no items, otherwise 0.

   @param  rbtree RBTree_t instance
   @return 1 if empty, otherwise 0
*/
#define RBTree_is_empty( arg ) PRIMITIVE_CAT( arg, _rbtree_is_empty )
int32_t RBTree_is_empty( Prefix )( RBTree_type( Prefix ) *rbtree );

/*
   Search
*/

/**
   RBTree_has

   Returns 1 if the RBTree_t instance contains the key, otherwise 0.

   @param  rbtree RBTree_t instance
   @param  value the value to search for
   @return 1 if rbtree has key, otherwise 0
*/
#define RBTree_has( arg ) PRIMITIVE_CAT( arg, _rbtree_has )
int32_t RBTree_has( Prefix )( RBTree_type( Prefix ) *rbtree, Type value );

/**
   RBTree_has_eq_fn

   Returns 1 if the RBTree_t instance has a key that returns 1 for
   test_equality_fn, otherwise 0.

   @param  current RBTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
   @return 1 if rbtree has key, otherwise 0
*/
#define RBTree_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_has_eq_fn )
int32_t RBTree_has_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_occurrences

   Returns count of how many equal keys are in the RBTree_t instance.

   @param  current RBTree_t instance
   @param  value the value to search for
   @return count of equal keys
*/
#define RBTree_occurrences( arg ) PRIMITIVE_CAT( arg, _rbtree_occurrences )
int32_t RBTree_occurrences( Prefix )( RBTree_type( Prefix ) *current, Type value );

/**
   RBTree_occurrences_eq_fn

   Returns count of how many equal keys are in the RBTree_t instance according
   to equality_test_fn.

   @param  current RBTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
   @return count of equal keys
*/
#define RBTree_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_occurrences_eq_fn )
int32_t RBTree_occurrences_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_search_forth

   Sets internal cursor to next item found searching forth, or off if
   nothing found.

   @param  current RBTree_t instance
   @param  value the value to search for
*/
#define RBTree_search_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_search_forth )
void RBTree_search_forth( Prefix )( RBTree_type( Prefix ) *current, Type value );

/**
   RBTree_search_forth_eq_fn

   Sets internal cursor to next item found searching forth using
   equality_test_func, or off if nothing found.

   @param  current RBTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define RBTree_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_search_forth_eq_fn )
void RBTree_search_forth_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_search_back

   Sets internal cursor to next item found searching back, or off if
   nothing found.

   @param  current RBTree_t instance
   @param  value the value to search for
*/
#define RBTree_search_back( arg ) PRIMITIVE_CAT( arg, _rbtree_search_back )
void RBTree_search_back( Prefix )( RBTree_type( Prefix ) *current, Type value );

/**
   RBTree_search_back_eq_fn

   Sets internal cursor to next item found searching back using
   equality_test_func, or off if nothing found.

   @param  current RBTree_t instance
   @param  value the value to search for
   @param equality_test_func function to check equality of values
*/
#define RBTree_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_search_back_eq_fn )
void RBTree_search_back_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);


/*
   Cursor movement
*/

/**
   RBTree_cursor_forth

   Moves the RBTree_cursor_t instance to the next item or off.

   @param  rbtree_cursor RBTree_cursor_t instance
*/
#define RBTree_cursor_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_forth )
void RBTree_cursor_forth( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_back

   Moves the RBTree_cursor_t instance to the previous item or off.

   @param  rbtree_cursor RBTree_cursor_t instance
*/
#define RBTree_cursor_back( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_back )
void RBTree_cursor_back( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_go

   Moves the RBTree_t instance's internal cursor to the ith item in the rbtree.

   @param  rbtree_cursor RBTree_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define RBTree_cursor_go( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_go )
void RBTree_cursor_go( Prefix )( RBTree_cursor_type( Prefix ) *cursor, int32_t index );

/**
   RBTree_cursor_go_to_value

   Moves the RBTree_t instance's internal cursor to the item in rbtree with the
   same value or if not present, the item in the rbtree with the value less than
   and closest to the desired value .

   @param  current_cursor RBTree_cursor_t instance
   @param  value the value of the item where the cursor will be moved to
*/
#define RBTree_cursor_go_to_value( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_go_to_value )
void RBTree_cursor_go_to_value( Prefix )( RBTree_cursor_type( Prefix ) *cursor, Type value );

/**
   RBTree_cursor_start

   Moves the RBTree_cursor_t instance to the first item or off if the rbtree is empty.

   @param  rbtree_cursor RBTree_cursor_t instance
*/
#define RBTree_cursor_start( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_start )
void RBTree_cursor_start( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_finish

   Moves the RBTree_cursor_t instance to the last item or off if the rbtree is empty.

   @param  rbtree_cursor RBTree_cursor_t instance
*/
#define RBTree_cursor_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_finish )
void RBTree_cursor_finish( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list RBTree_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define RBTree_cursor_index( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_index )
int32_t RBTree_cursor_index( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_remove_at

   Removes item pointed to by the cursor.

   @param  cursor RBTree_cursor_t instance
*/
#define RBTree_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_remove_at )
void RBTree_cursor_remove_at( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_remove_at_and_dispose

   Removes and disposes of item pointed to by the cursor.

   @param  cursor RBTree_cursor_t instance
*/
#define RBTree_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_remove_at_and_dispose )
void RBTree_cursor_remove_at_and_dispose( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_forth

   Moves the RBTree_t instance internal cursor to the next item or off.

   @param  rbtree RBTree_t instance
*/
#define RBTree_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_forth )
void RBTree_forth( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_back

   Moves the RBTree_t instance internal cursor to the previous item or off.

   @param  rbtree RBTree_t instance
*/
#define RBTree_back( arg ) PRIMITIVE_CAT( arg, _rbtree_back )
void RBTree_back( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_go

   Moves the RBTree_t instance's internal cursor to the ith item in the rbtree.

   @param  rbtree RBTree_t instance
   @param  index the index where the  will be moved to
*/
#define RBTree_go( arg ) PRIMITIVE_CAT( arg, _rbtree_go )
void RBTree_go( Prefix )( RBTree_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_go_to_value

   Moves the RBTree_t instance's internal cursor to the item in the rbtree with \
   the desired value or if not present to the item just before where the desired
   value would be.

   @param  current RBTree_t instance
   @param  value the value where the internal cursor will be moved to
*/
#define RBTree_go_to_value( arg ) PRIMITIVE_CAT( arg, _rbtree_go_to_value )
void RBTree_go_to_value( Prefix )( RBTree_type( Prefix ) *current, Type value );

/**
   RBTree_start

   Moves the RBTree_t instance's internal cursor to the first item or off if the rbtree is empty.

   @param  rbtree RBTree_t instance
*/
#define RBTree_start( arg ) PRIMITIVE_CAT( arg, _rbtree_start )
void RBTree_start( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_finish

   Moves the RBTree_t instance's internal cursor to the last item or off if the rbtree is empty.

   @param  rbtree RBTree_t instance
*/
#define RBTree_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_finish )
void RBTree_finish( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  list RBTree_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define RBTree_index( arg ) PRIMITIVE_CAT( arg, _rbtree_index )
int32_t RBTree_index( Prefix )( RBTree_type( Prefix ) *list );



/*
   Element change
*/

/**
   RBTree_put

   Put the key-value pair into the RBTree_t instance. Replace any existing item
   that has the same key.

   @param  rbtree RBTree_t instance
   @param  value the value to insert
*/
#define RBTree_put( arg ) PRIMITIVE_CAT( arg, _rbtree_put )
void RBTree_put( Prefix )( RBTree_type( Prefix ) *rbtree, Type value );


/*
   Removal
*/

/**
   RBTree_remove

   Remove the item in the RBTree_t instance at the index.

   @param  current RBTree_t instance
   @param index the index of the item to remove
*/
#define RBTree_remove( arg ) PRIMITIVE_CAT( arg, _rbtree_remove )
void RBTree_remove( Prefix )( RBTree_type( Prefix ) *current, int32_t index );

/**
   RBTree_remove_and_dispose

   Remove the item in the RBTree_t instance at the index and dispose
   of the key and the value.

   @param  current RBTree_t instance
   @param index the index of the item to remove
*/
#define RBTree_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_and_dispose )
void RBTree_remove_and_dispose( Prefix )( RBTree_type( Prefix ) *current, int32_t index );

/**
   RBTree_remove_value

   Remove the item in the RBTree_t instance that has the key.

   @param  current RBTree_t instance
   @param  key the key for the value
*/
#define RBTree_remove_value( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_value )
void RBTree_remove_value( Prefix )( RBTree_type( Prefix ) *current, Type value );

/**
   RBTree_remove_value_and_dispose

   Remove the item in the RBTree_t instance that has the key and dispose
   of the key and the value.

   @param  current RBTree_t instance
   @param  key the key for the value
*/
#define RBTree_remove_value_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_value_and_dispose )
void RBTree_remove_value_and_dispose( Prefix )( RBTree_type( Prefix ) *current, Type value );

/**
   RBTree_remove_at

   Remove the item in the RBTree_t instance at the internal cursor.

   @param current RBTree_t instance
*/
#define RBTree_remove_at( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_at )
void RBTree_remove_at( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_remove_at_and_dispose

   Remove the item in the RBTree_t instance at the cursor and dispose
   of the key and the value.

   @param current RBTree_t instance
*/
#define RBTree_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_at_and_dispose )
void RBTree_remove_at_and_dispose( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_remove_first

   Remove the first item in the RBTree_t instance.

   @param current RBTree_t instance
*/
#define RBTree_remove_first( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_first )
void RBTree_remove_first( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_remove_first_and_dispose

   Remove and dispose the first item in the RBTree_t instance.

   @param current RBTree_t instance
*/
#define RBTree_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_first_and_dispose )
void RBTree_remove_first_and_dispose( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_remove_last

   Remove the last item in the RBTree_t instance.

   @param current RBTree_t instance
*/
#define RBTree_remove_last( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_last )
void RBTree_remove_last( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_remove_last_and_dispose

   Remove and dispose the last item in the RBTree_t instance.

   @param current RBTree_t instance
*/
#define RBTree_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_last_and_dispose )
void RBTree_remove_last_and_dispose( Prefix )( RBTree_type( Prefix ) *current );

/**
   RBTree_wipe_out

   Remove all items in the RBTree_t instance.

   @param  rbtree RBTree_t instance
*/
#define RBTree_wipe_out( arg ) PRIMITIVE_CAT( arg, _rbtree_wipe_out )
void RBTree_wipe_out( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_wipe_out_and_dispose

   Remove all items in the RBTree_t instance. Dispose of all keys and values.

   @param  rbtree RBTree_t instance
*/
#define RBTree_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_wipe_out_and_dispose )
void RBTree_wipe_out_and_dispose( Prefix )( RBTree_type( Prefix ) *rbtree );


/*
   Miscellaneous
*/

/**
   RBTree_as_string

   Convert the tree to a string representation

   @param  rbtree RBTree_t instance
   @param  astr array of strings
   @param  width number of characters for each value as a string
   @param  func function to put string representation of value into string
*/

#define RBTree_as_string( arg ) PRIMITIVE_CAT( arg, _rbtree_as_string )
void RBTree_as_string( Prefix )
(
   RBTree_type( Prefix ) *rbtree,
   char_t **astr,
   int32_t width,
   void ( func )( char_t *, Type value )
);


#ifdef __cplusplus
}
#endif

/* End of file */




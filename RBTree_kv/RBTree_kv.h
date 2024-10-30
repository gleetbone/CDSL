/**
 @file RBTree_kv.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Red Black Binary Search Trees of keys with values"

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

 Function declarations for the opaque RBTree_kv_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define RBTREE_KV_VERSION_MAJOR 2
#define RBTREE_KV_VERSION_MINOR 0
#define RBTREE_KV_VERSION_PATCH 0

#define RBTREE_KV_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define RBTREE_KV_VERSION \
   RBTREE_KV_MAKE_VERSION( RBTREE_KV_VERSION_MAJOR, \
                           RBTREE_KV_VERSION_MINOR, \
                           RBTREE_KV_VERSION_PATCH )

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

   KEY_DEEP_EQUAL_FUNCTION    - compares two key instances for equality
   KEY_DEEP_DISPOSE_FUNCTION  - frees a key instance
   KEY_DEEP_CLONE_FUNCTION    - duplicates a key instance
   KEY_ORDER_FUNCTION         - returns 1 if first key argument is "before" second argument
   KEY_DEFAULT                - default key value

   VALUE_DEEP_EQUAL_FUNCTION     - compares two value instances for equality
   VALUE_DEEP_DISPOSE_FUNCTION   - frees a value instance
   VALUE_DEEP_CLONE_FUNCTION     - duplicates a value instance
   VALUE_ORDER_FUNCTION          - returns 1 if first value argument is "before" second argument
   VALUE_DEFAULT                 - default value value
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define RBTree_kv_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_struct )
#define RBTree_kv_type( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_t )
#define RBTree_kv_name( arg ) PRIMITIVE_CAT( arg, _rbtree_kv )

#define RBTree_kv_cursor_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_struct )
#define RBTree_kv_cursor_type( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_t )
#define RBTree_kv_cursor_name( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor )

/**
   Structure declarations
*/

struct RBTree_kv_struct( Prefix );
struct RBTree_kv_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct RBTree_kv_struct( Prefix ) RBTree_kv_type( Prefix );
typedef struct RBTree_kv_cursor_struct( Prefix ) RBTree_kv_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   RBTree_kv_make

   Return a new RBTree_kv_t instance with a default number of buckets.

   @return RBTree_kv_t instance
*/
#define RBTree_kv_make( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_make )
RBTree_kv_type( Prefix ) * RBTree_kv_make( Prefix )( void );

/**
   RBTree_kv_make_from_array

   Return a new RBTree_kv_t instance that has the same content as array. The key
   and value items in array are not copied.

   @param  key_array key array to copy from
   @param  value_array value array to copy from
   @param  count the number of items to copy
   @return RBTree_kv_t instance
*/
#define RBTree_kv_make_from_array( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_make_from_array )
RBTree_kv_type( Prefix ) * RBTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count );

/**
   RBTree_kv_clone

   Return a new RBTree_kv_t instance that has the same content as rbtree. The key
   and value items in rbtree are not copied.

   @param  rbtree the RBTree_kv_t instance to copy from
   @return RBTree_kv_t instance
*/
#define RBTree_kv_clone( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_clone )
RBTree_kv_type( Prefix ) * RBTree_kv_clone( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_deep_clone

   Return a new RBTree_kv_t instance with a duplicate items from rbtree

   @return RBTree_kv_t instance
*/

#define RBTree_kv_deep_clone( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_deep_clone )
RBTree_kv_type( Prefix ) *
RBTree_kv_deep_clone( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_is_equal

   Returns 1 if current is equal to other

   @param  current the RBTree_kv_t instance to compare to
   @param  other the RBTree_kv_t instance to compare
   @return 1 if equal, 0 otherwise
*/
#define RBTree_kv_is_equal( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_is_equal )
int32_t RBTree_kv_is_equal( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other );

/**
   RBTree_kv_is_deep_equal

   Returns 1 if current is deep equal to other

   @param  current the RBTree_kv_t instance to compare to
   @param  other the RBTree_kv_t instance to compare
   @return 1 if deep equal, 0 otherwise
*/
#define RBTree_kv_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_is_deep_equal )
int32_t RBTree_kv_is_deep_equal( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other );

/**
   RBTree_kv_copy

   Copies (shallow) contents of other into current. Contents of current are deep
   disposed.

   @param  current the RBTree_kv_t instance to copy into
   @param  other the RBTree_kv_t instance to copy
*/
#define RBTree_kv_copy( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_copy )
void RBTree_kv_copy( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other );

/**
   RBTree_kv_deep_copy

   Copies (deep) contents of other into current. Contents of current are deep
   disposed.

   @param  current the RBTree_kv_t instance to copy into
   @param  other the RBTree_kv_t instance to copy
*/
#define RBTree_kv_deep_copy( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_deep_copy )
void RBTree_kv_deep_copy( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other );

/**
   RBTree_kv_cursor_make

   Return a new RBTree_kv_t cursor instance.

   @param  the RBTree_kv_t instance the new cursor works on
   @return RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_make( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_make )
RBTree_kv_cursor_type( Prefix ) * RBTree_kv_cursor_make( Prefix )( RBTree_kv_type( Prefix ) *current );


/*
   Disposal
*/

/**
   RBTree_kv_dispose

   Frees a RBTree_kv_t instance without freeing its contained keys and values.

   @param RBTree_kv_t instance
*/
#define RBTree_kv_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_dispose )
void RBTree_kv_dispose( Prefix )( RBTree_kv_type( Prefix ) **current );

/**
   RBTree_kv_deep_dispose

   Frees a RBTree_kv_t instance and its contained keys and values.

   @param RBTree_kv_t instance
*/
#define RBTree_kv_deep_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_deep_dispose )
void RBTree_kv_deep_dispose( Prefix )( RBTree_kv_type( Prefix ) **current );

/**
   RBTree_kv_cursor_dispose

   Frees a RBTree_kv_cursor_t instance. Its rbtree is not disposed.

   @param RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_dispose )
void RBTree_kv_cursor_dispose( Prefix )( RBTree_kv_cursor_type( Prefix ) **cursor );


/**
   RBTree_kv_keys_as_array

   Returns the values as an array.

   @param  RBTree_kv_t instance
   @return array of Key values
*/
#define RBTree_kv_keys_as_array( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_keys_as_array )
Key *RBTree_kv_keys_as_array( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t *count );

/**
   RBTree_kv_values_as_array

   Returns the values as an array.

   @param  RBTree_kv_t instance
   @return array of Type values
*/
#define RBTree_kv_values_as_array( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_values_as_array )
Type *RBTree_kv_values_as_array( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t *count );

/*
   Access
*/

/**
   RBTree_kv_cursor_key_at

   Returns the key of the item that the RBTree_kv_cursor_t instance is pointing to.

   @param  RBTree_kv_cursor_t instance
   @return a Key value
*/
#define RBTree_kv_cursor_key_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_key_at )
Key RBTree_kv_cursor_key_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_item_at

   Returns the value of the item that the RBTree_kv_cursor_t instance is pointing to.

   @param  RBTree_kv_cursor_t instance
   @return a Type value
*/
#define RBTree_kv_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_item_at )
Type RBTree_kv_cursor_item_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_key_at

   Returns the key of the item that the RBTree_kv_t instance's internal
   cursor is pointing to.

   @param  rbtree RBTree_kv_t instance
   @return a Key value
*/
#define RBTree_kv_key_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_at )
Key RBTree_kv_key_at( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_item_at

   Returns the value of the item that the RBTree_kv_t instance's internal
   cursor is pointing to.

   @param  rbtree RBTree_kv_t instance
   @return a Type value
*/
#define RBTree_kv_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_item_at )
Type RBTree_kv_item_at( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_key

   Returns the key of the item pointed to by index. First index is 0.

   @param  rbtree RBTree_kv_t instance
   @param  index desired index
   @return a Key value
*/
#define RBTree_kv_key( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key )
Key RBTree_kv_key( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index );

/**
   RBTree_kv_item

   Returns the value of the item pointed to by index. First index is 0.

   @param  rbtree RBTree_kv_t instance
   @param  index desired index
   @return a Type value
*/
#define RBTree_kv_item( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_item )
Type RBTree_kv_item( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index );

/**
   RBTree_kv_first

   Returns the value of the first item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
   @return a Type value
*/
#define RBTree_kv_first( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_first )
Type RBTree_kv_first( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_last

   Returns the value of the last item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
   @return a Type value
*/
#define RBTree_kv_last( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_last )
Type RBTree_kv_last( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_key_first

   Returns the key of the first item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
   @return a Key value
*/
#define RBTree_kv_key_first( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_first )
Key RBTree_kv_key_first( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_key_last

   Returns the key of the last item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
   @return a Key value
*/
#define RBTree_kv_key_last( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_last )
Key RBTree_kv_key_last( Prefix )( RBTree_kv_type( Prefix ) *current );


/*
   Measurement
*/

/**
   RBTree_kv_count

   Returns the number of items in the RBTree_kv_t instance.

   @param  rbtree RBTree_kv_t instance
   @return number of items in RBTree instance
*/
#define RBTree_kv_count( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_count )
int32_t RBTree_kv_count( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_height

   Returns the (max) height of the RBTree_kv_t instance.

   @param  rbtree RBTree_kv_t instance
   @return (max) height of the RBTree instance
*/
#define RBTree_kv_height( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_height )
int32_t RBTree_kv_height( Prefix )( RBTree_kv_type( Prefix ) *current );


/*
   Status report
*/

/**
   RBTree_kv_off

   Returns 1 if the RBTree_kv_t instance's internal cursor is off, otherwise 0.

   @param  rbtree RBTree_kv_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_kv_off( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_off )
int32_t RBTree_kv_off( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_cursor_off

   Returns 1 if the RBTree_kv_cursor_t instance is off, otherwise 0.

   @param  cursor RBTree_kv_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_kv_cursor_off( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_off )
int32_t RBTree_kv_cursor_off( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_is_first

   Returns 1 if the RBTree_kv_cursor_t instance is at the first item, otherwise 0.

   @param  cursor RBTree_kv_cursor_t instance
   @return 1 if internal cursor is at the first item, otherwise 0
*/
#define RBTree_kv_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_is_first )
int32_t RBTree_kv_cursor_is_first( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_is_last

   Returns 1 if the RBTree_kv_cursor_t instance is at the last item, otherwise 0.

   @param  cursor RBTree_kv_cursor_t instance
   @return 1 if internal cursor is at the last item, otherwise 0
*/
#define RBTree_kv_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_is_last )
int32_t RBTree_kv_cursor_is_last( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_key_search_forth

   Searches from the current position of the RBTree_kv_cursor_t instance for key.

   @param  cursor RBTree_kv_cursor_t instance
   @param  key the key to search for
*/
#define RBTree_kv_cursor_key_search_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_key_search_forth )
void RBTree_kv_cursor_key_search_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   RBTree_kv_cursor_key_search_forth_eq_fn

   Searches from the current position of the RBTree_kv_cursor_t instance for
   key that satisfies equalty_test_func

   @param  cursor RBTree_kv_cursor_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define RBTree_kv_cursor_key_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_key_search_forth_eq_fn )
void RBTree_kv_cursor_key_search_forth_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   RBTree_kv_cursor_search_forth

   Searches from the current position of the RBTree_kv_cursor_t instance for value.

   @param  cursor RBTree_kv_cursor_t instance
   @param  value the value to search for
*/
#define RBTree_kv_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_search_forth )
void RBTree_kv_cursor_search_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Type value );

/**
   RBTree_kv_cursor_search_forth_eq_fn

   Searches from the current position of the RBTree_kv_cursor_t instance for
   value that satisfies equalty_test_func

   @param  cursor RBTree_kv_cursor_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define RBTree_kv_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_search_forth_eq_fn )
void RBTree_kv_cursor_search_forth_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_kv_cursor_key_search_back

   Searches from the current position of the RBTree_kv_cursor_t instance for key.

   @param  cursor RBTree_kv_cursor_t instance
   @param  key the key to search for
*/
#define RBTree_kv_cursor_key_search_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_key_search_back )
void RBTree_kv_cursor_key_search_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   RBTree_kv_cursor_key_search_back_eq_fn

   Searches from the current position of the RBTree_kv_cursor_t instance for
   key that satisfies equalty_test_func

   @param  cursor RBTree_kv_cursor_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define RBTree_kv_cursor_key_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_key_search_back_eq_fn )
void RBTree_kv_cursor_key_search_back_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   RBTree_kv_cursor_search_back

   Searches from the current position of the RBTree_kv_cursor_t instance for value.

   @param  cursor RBTree_kv_cursor_t instance
   @param  value the value to search for
*/
#define RBTree_kv_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_search_back )
void RBTree_kv_cursor_search_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Type value );

/**
   RBTree_kv_cursor_search_back_eq_fn

   Searches from the current position of the RBTree_kv_cursor_t instance for
   value that satisfies equalty_test_func

   @param  cursor RBTree_kv_cursor_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define RBTree_kv_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_search_back_eq_fn )
void RBTree_kv_cursor_search_back_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_kv_is_empty

   Returns 1 if the RBTree_kv_t instance contains no items, otherwise 0.

   @param  rbtree RBTree_kv_t instance
   @return 1 if empty, otherwise 0
*/
#define RBTree_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_is_empty )
int32_t RBTree_kv_is_empty( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_is_first

   Returns 1 if the RBTree_kv_t instance is at the first item, otherwise 0.

   @param  current RBTree_kv_t instance
   @return 1 if internal cursor is at the first item, otherwise 0
*/
#define RBTree_kv_is_first( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_is_first )
int32_t RBTree_kv_is_first( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_is_last

   Returns 1 if the RBTree_kv_t instance is at the last item, otherwise 0.

   @param  current RBTree_kv_t instance
   @return 1 if internal cursor is at the last item, otherwise 0
*/
#define RBTree_kv_is_last( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_is_last )
int32_t RBTree_kv_is_last( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_has

   Returns 1 if the RBTree_kv_t instance contains the key, otherwise 0.

   @param  rbtree RBTree_kv_t instance
   @param  key the value to search for
   @return 1 if rbtree has key, otherwise 0
*/
#define RBTree_kv_has( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_has )
int32_t RBTree_kv_has( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_has_eq_fn

   Returns 1 if the RBTree_kv_t instance contains the key, otherwise 0.

   @param  rbtree RBTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key matches
   @return 1 if rbtree has key, otherwise 0
*/
#define RBTree_kv_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_has_eq_fn )
int32_t RBTree_kv_has_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *rbtree,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   RBTree_kv_has_value

   Returns 1 if the RBTree_kv_t instance contains the key, otherwise 0.

   @param  rbtree RBTree_kv_t instance
   @param  value the value to search for
   @return 1 if rbtree has value, otherwise 0
*/
#define RBTree_kv_has_value( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_has_value )
int32_t RBTree_kv_has_value( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Type value );

/**
   RBTree_kv_has_value_eq_fn

   Returns 1 if the RBTree_kv_t instance contains the key, otherwise 0.

   @param  rbtree RBTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value matches
   @return 1 if rbtree has value, otherwise 0
*/
#define RBTree_kv_has_value_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_has_value_eq_fn )
int32_t RBTree_kv_has_value_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *rbtree,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_kv_occurrences

   Returns count of matching keys int the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
   @param  key the key to search for
   @return count of matching keys in rbtree
*/
#define RBTree_kv_occurrences( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_occurrences )
int32_t RBTree_kv_occurrences( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_occurrences_eq_fn

   Returns count of matching keys in the RBTree_kv_t instance according to
   equality_test_func.

   @param  current RBTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key matches
   @return count of matching keys in rbtree
*/
#define RBTree_kv_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_occurrences_eq_fn )
int32_t RBTree_kv_occurrences_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   RBTree_kv_occurrences_value

   Returns count of matching values int the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
   @param  value the value to search for
   @return count of matching values in rbtree
*/
#define RBTree_kv_occurrences_value( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_occurrences_value )
int32_t RBTree_kv_occurrences_value( Prefix )( RBTree_kv_type( Prefix ) *current, Type value );

/**
   RBTree_kv_occurrences_value_eq_fn

   Returns count of matching values in the RBTree_kv_t instance according to
   equality_test_func.

   @param  current RBTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value matches
   @return count of matching values in rbtree
*/
#define RBTree_kv_occurrences_value_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_occurrences_value_eq_fn )
int32_t RBTree_kv_occurrences_value_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);


/*
   Cursor movement
*/

/**
   RBTree_kv_cursor_forth

   Moves the RBTree_kv_cursor_t instance to the next item or off.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_forth )
void RBTree_kv_cursor_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_back

   Moves the RBTree_kv_cursor_t instance to the previous item or off.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_back )
void RBTree_kv_cursor_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_go

   Moves the RBTree_kv_t instance's internal cursor to the ith item in the rbtree.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define RBTree_kv_cursor_go( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_go )
void RBTree_kv_cursor_go( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, int32_t index );

/**
   RBTree_kv_cursor_go_to_key

   Moves the RBTree_kv_t instance's internal cursor to the item in the rbtree with
   a matching key.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
   @param  key the key where the cursor will be moved to
*/
#define RBTree_kv_cursor_go_to_key( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_go_to_key )
void RBTree_kv_cursor_go_to_key( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   RBTree_kv_cursor_start

   Moves the RBTree_kv_cursor_t instance to the first item or off if the rbtree is empty.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_start( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_start )
void RBTree_kv_cursor_start( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_finish

   Moves the RBTree_kv_cursor_t instance to the last item or off if the rbtree is empty.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_finish )
void RBTree_kv_cursor_finish( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_remove_at

   Remove the item at the RBTree_kv_cursor_t instance.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_remove_at )
void RBTree_kv_cursor_remove_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_remove_at_and_dispose

   Remove and dispose the item at the RBTree_kv_cursor_t instance.

   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance
*/
#define RBTree_kv_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_remove_at_and_dispose )
void RBTree_kv_cursor_remove_at_and_dispose( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list RBTree_kv_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define RBTree_kv_cursor_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_index )
int32_t RBTree_kv_cursor_index( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_forth

   Moves the RBTree_kv_t instance internal cursor to the next item or off.

   @param  rbtree RBTree_kv_t instance
*/
#define RBTree_kv_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_forth )
void RBTree_kv_forth( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_back

   Moves the RBTree_kv_t instance internal cursor to the previous item or off.

   @param  rbtree RBTree_kv_t instance
*/
#define RBTree_kv_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_back )
void RBTree_kv_back( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_go

   Moves the RBTree_kv_t instance's internal cursor to the ith item in the rbtree.

   @param  rbtree RBTree_kv_t instance
   @param  index the index where the  will be moved to
*/
#define RBTree_kv_go( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_go )
void RBTree_kv_go( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index );

/**
   RBTree_kv_go_to_key

   Moves the RBTree_kv_t instance's internal cursor to the item in the rbtree with
   a matching key.

   @param  current RBTree_kv_t instance
   @param  key the key where the cursor will be moved to
*/
#define RBTree_kv_go_to_key( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_go_to_key )
void RBTree_kv_go_to_key( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_start

   Moves the RBTree_kv_t instance's internal cursor to the first item or off if the rbtree is empty.

   @param  rbtree RBTree_kv_t instance
*/
#define RBTree_kv_start( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_start )
void RBTree_kv_start( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_finish

   Moves the RBTree_kv_t instance's internal cursor to the first item or off if the rbtree is empty.

   @param  rbtree RBTree_kv_t instance
*/
#define RBTree_kv_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_finish )
void RBTree_kv_finish( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  list RBTree_kv_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define RBTree_kv_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_index )
int32_t RBTree_kv_index( Prefix )( RBTree_kv_type( Prefix ) *list );

/**
   RBTree_kv_key_search_forth

   Searches from the current position of the RBTree_kv_t instance for key.

   @param  current RBTree_kv_t instance
   @param  key the key to search for
*/
#define RBTree_kv_key_search_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_search_forth )
void RBTree_kv_key_search_forth( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_key_search_forth_eq_fn

   Searches from the current position of the RBTree_kv_t instance for
   key that satisfies equalty_test_func

   @param  current RBTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define RBTree_kv_key_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_search_forth_eq_fn )
void RBTree_kv_key_search_forth_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   RBTree_kv_search_forth

   Searches from the current position of the RBTree_kv_t instance for value.

   @param  current RBTree_kv_t instance
   @param  value the value to search for
*/
#define RBTree_kv_search_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_search_forth )
void RBTree_kv_search_forth( Prefix )( RBTree_kv_type( Prefix ) *current, Type value );

/**
   RBTree_kv_search_forth_eq_fn

   Searches from the current position of the RBTree_kv_t instance for
   value that satisfies equalty_test_func

   @param  current RBTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define RBTree_kv_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_search_forth_eq_fn )
void RBTree_kv_search_forth_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   RBTree_kv_key_search_back

   Searches from the current position of the RBTree_kv_t instance for key.

   @param  current RBTree_kv_t instance
   @param  key the key to search for
*/
#define RBTree_kv_key_search_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_search_back )
void RBTree_kv_key_search_back( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_key_search_back_eq_fn

   Searches from the current position of the RBTree_kv_t instance for
   key that satisfies equalty_test_func

   @param  current RBTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define RBTree_kv_key_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_search_back_eq_fn )
void RBTree_kv_key_search_back_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   RBTree_kv_search_back

   Searches from the current position of the RBTree_kv_t instance for value.

   @param  current RBTree_kv_t instance
   @param  value the value to search for
*/
#define RBTree_kv_search_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_search_back )
void RBTree_kv_search_back( Prefix )( RBTree_kv_type( Prefix ) *current, Type value );

/**
   RBTree_kv_search_back_eq_fn

   Searches from the current position of the RBTree_kv_t instance for
   value that satisfies equalty_test_func

   @param  current RBTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define RBTree_kv_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_search_back_eq_fn )
void RBTree_kv_search_back_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);


/*
   Element change
*/

/**
   RBTree_kv_put

   Put the key-value pair into the RBTree_kv_t instance. Replace any existing item
   that has the same key.

   @param  rbtree RBTree_kv_t instance
   @param  value the value to insert
*/
#define RBTree_kv_put( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_put )
void RBTree_kv_put( Prefix )( RBTree_kv_type( Prefix ) *current, Type value, Key key );


/*
   Removal
*/

/**
   RBTree_kv_remove

   Remove the item in the RBTree_kv_t instance that has the key.

   @param  rbtree RBTree_kv_t instance
   @param  key the key for the value
*/
#define RBTree_kv_remove( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove )
void RBTree_kv_remove( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_remove_and_dispose

   Remove the item in the RBTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  rbtree RBTree_kv_t instance
   @param  key the key for the value
*/
#define RBTree_kv_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_and_dispose )
void RBTree_kv_remove_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current, Key key );

/**
   RBTree_kv_remove_by_index

   Remove the item in the RBTree_kv_t instance at index.

   @param  rbtree RBTree_kv_t instance
   @param  index the index for the item
*/
#define RBTree_kv_remove_by_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_by_index )
void RBTree_kv_remove_by_index( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_kv_remove_by_index_and_dispose

   Remove the item in the RBTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  rbtree RBTree_kv_t instance
   @param  index the index for the item
*/
#define RBTree_kv_remove_by_index_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_by_index_and_dispose )
void RBTree_kv_remove_by_index_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_kv_remove_value

   Remove the item in the RBTree_kv_t instance at index.

   @param  rbtree RBTree_kv_t instance
   @param  value the value to remove
*/
#define RBTree_kv_remove_value( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_value )
void RBTree_kv_remove_value( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Type value );

/**
   RBTree_kv_remove_value_and_dispose

   Remove the item in the RBTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  rbtree RBTree_kv_t instance
   @param  value the value to remove and dispose
*/
#define RBTree_kv_remove_value_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_value_and_dispose )
void RBTree_kv_remove_value_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Type value );

/**
   RBTree_kv_remove_at

   Remove the item at the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
*/
#define RBTree_kv_remove_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_at )
void RBTree_kv_remove_at( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_remove_at_and_dispose

   Remove and dispose the item at the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
*/
#define RBTree_kv_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_at_and_dispose )
void RBTree_kv_remove_at_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_remove_first

   Remove the first item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
*/
#define RBTree_kv_remove_first( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_first )
void RBTree_kv_remove_first( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_remove_first_and_dispose

   Remove and dispose the first item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
*/
#define RBTree_kv_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_first_and_dispose )
void RBTree_kv_remove_first_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_remove_last

   Remove the last item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
*/
#define RBTree_kv_remove_last( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_last )
void RBTree_kv_remove_last( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_remove_last_and_dispose

   Remove and dispose the last item in the RBTree_kv_t instance.

   @param  current RBTree_kv_t instance
*/
#define RBTree_kv_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_last_and_dispose )
void RBTree_kv_remove_last_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_wipe_out

   Remove all items in the RBTree_kv_t instance.

   @param  rbtree RBTree_kv_t instance
*/
#define RBTree_kv_wipe_out( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_wipe_out )
void RBTree_kv_wipe_out( Prefix )( RBTree_kv_type( Prefix ) *current );

/**
   RBTree_kv_wipe_out_and_dispose

   Remove all items in the RBTree_kv_t instance. Dispose of all keys and values.

   @param  rbtree RBTree_kv_t instance
*/
#define RBTree_kv_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_wipe_out_and_dispose )
void RBTree_kv_wipe_out_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current );


/*
   Miscellaneous
*/

/**
   RBTree_as_string

   Put a representation of the tree into an array of strings

   @param  rbtree RBTree_kv_t instance
   @param astr array of strings to put the representation into
   @param width the number of characters to place a node's data into
   @param func a function to put node's data into a character string
*/
#define RBTree_kv_as_string( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_as_string )
void RBTree_kv_as_string( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   char_t **astr,
   int32_t width,
   void ( func )( char_t *, Key key, Type value )
);


#ifdef __cplusplus
}
#endif

/* End of file */




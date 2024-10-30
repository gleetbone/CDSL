/**
 @file BSTree_kv.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Binary Search Trees of keys with values"

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

 Function declarations for the opaque BSTree_kv_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define BSTREE_KV_VERSION_MAJOR 2
#define BSTREE_KV_VERSION_MINOR 0
#define BSTREE_KV_VERSION_PATCH 0

#define BSTREE_KV_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define BSTREE_KV_VERSION \
   BSTREE_KV_MAKE_VERSION( BSTREE_KV_VERSION_MAJOR, \
                           BSTREE_KV_VERSION_MINOR, \
                           BSTREE_KV_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Key    - the type of the key
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

#define BSTree_kv_struct( arg ) PRIMITIVE_CAT( arg, _bstree_kv_struct )
#define BSTree_kv_type( arg ) PRIMITIVE_CAT( arg, _bstree_kv_t )
#define BSTree_kv_name( arg ) PRIMITIVE_CAT( arg, _bstree )

#define BSTree_kv_cursor_struct( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_struct )
#define BSTree_kv_cursor_type( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_t )
#define BSTree_kv_cursor_name( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor )

/**
   Structure declarations
*/

struct BSTree_kv_struct( Prefix );
struct BSTree_kv_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct BSTree_kv_struct( Prefix ) BSTree_kv_type( Prefix );
typedef struct BSTree_kv_cursor_struct( Prefix ) BSTree_kv_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   BSTree_kv_make

   Return a new BSTree_kv_t instance with a default number of buckets.

   @return BSTree_kv_t instance
*/
#define BSTree_kv_make( arg ) PRIMITIVE_CAT( arg, _bstree_kv_make )
BSTree_kv_type( Prefix ) * BSTree_kv_make( Prefix )( void );

/**
   BSTree_kv_make_from_array

   Return a new BSTree_kv_t instance that has the same content as bstree. The key
   and value items in bstree are not copied.

   @param key_array the array of keys to copy from
   @param value_array the array of values to copy from
   @param count the number of items to copy
   @return BSTree_kv_t instance
*/
#define BSTree_kv_make_from_array( arg ) PRIMITIVE_CAT( arg, _bstree_kv_make_from_array )
BSTree_kv_type( Prefix ) * BSTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count );

/**
   BSTree_kv_clone

   Return a new BSTree_kv_t instance that has the same content as bstree. The key
   and value items in bstree are not copied.

   @param  bstree the BSTree_kv_t instance to copy from
   @return BSTree_kv_t instance
*/
#define BSTree_kv_clone( arg ) PRIMITIVE_CAT( arg, _bstree_kv_clone )
BSTree_kv_type( Prefix ) * BSTree_kv_clone( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_deep_clone

   Return a new BSTree_kv_t instance with a duplicate items from bstree

   @return BSTree_kv_t instance
*/

#define BSTree_kv_deep_clone( arg ) PRIMITIVE_CAT( arg, _bstree_kv_deep_clone )
BSTree_kv_type( Prefix ) *
BSTree_kv_deep_clone( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_is_equal

   Returns 1 if current is equal to other

   @param  current the BSTree_kv_t instance to compare to
   @param  other the BSTree_kv_t instance to compare
   @return 1 if equal, 0 otherwise
*/
#define BSTree_kv_is_equal( arg ) PRIMITIVE_CAT( arg, _bstree_kv_is_equal )
int32_t BSTree_kv_is_equal( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other );

/**
   BSTree_kv_is_deep_equal

   Returns 1 if current is deep equal to other

   @param  current the BSTree_kv_t instance to compare to
   @param  other the BSTree_kv_t instance to compare
   @return 1 if deep equal, 0 otherwise
*/
#define BSTree_kv_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _bstree_kv_is_deep_equal )
int32_t BSTree_kv_is_deep_equal( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other );

/**
   BSTree_kv_copy

   Copies (shallow) contents of other into current. Contents of current are deep
   disposed.

   @param  current the BSTree_kv_t instance to copy into
   @param  other the BSTree_kv_t instance to copy
*/
#define BSTree_kv_copy( arg ) PRIMITIVE_CAT( arg, _bstree_kv_copy )
void BSTree_kv_copy( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other );

/**
   BSTree_kv_deep_copy

   Copies (deep) contents of other into current. Contents of current are deep
   disposed.

   @param  current the BSTree_kv_t instance to copy into
   @param  other the BSTree_kv_t instance to copy
*/
#define BSTree_kv_deep_copy( arg ) PRIMITIVE_CAT( arg, _bstree_kv_deep_copy )
void BSTree_kv_deep_copy( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other );

/**
   BSTree_kv_cursor_make

   Return a new BSTree_kv_t cursor instance.

   @param  the BSTree_kv_t instance the new cursor works on
   @return BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_make( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_make )
BSTree_kv_cursor_type( Prefix ) * BSTree_kv_cursor_make( Prefix )( BSTree_kv_type( Prefix ) *bstree );


/*
   Disposal
*/

/**
   BSTree_kv_dispose

   Frees a BSTree_kv_t instance without freeing its contained keys and values.

   @param BSTree_kv_t instance
*/
#define BSTree_kv_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_dispose )
void BSTree_kv_dispose( Prefix )( BSTree_kv_type( Prefix ) **bstree );

/**
   BSTree_kv_deep_dispose

   Frees a BSTree_kv_t instance and its contained keys and values.

   @param BSTree_kv_t instance
*/
#define BSTree_kv_deep_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_deep_dispose )
void BSTree_kv_deep_dispose( Prefix )( BSTree_kv_type( Prefix ) **bstree );

/**
   BSTree_kv_cursor_dispose

   Frees a BSTree_kv_cursor_t instance. Its bstree is not disposed.

   @param BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_dispose )
void BSTree_kv_cursor_dispose( Prefix )( BSTree_kv_cursor_type( Prefix ) **cursor );


/**
   BSTree_kv_keys_as_array

   Returns the keys as an array.

   @param  BSTree_kv_t instance
   @param  count pointer to returned count of rarray
   @return array of Key values
*/
#define BSTree_kv_keys_as_array( arg ) PRIMITIVE_CAT( arg, _bstree_kv_keys_as_array )
Key *BSTree_kv_keys_as_array( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t *count );

/**
   BSTree_kv_values_as_array

   Returns the values as an array.

   @param  BSTree_kv_t instance
   @param  count pointer to returned count of rarray
   @return array of Type values
*/
#define BSTree_kv_values_as_array( arg ) PRIMITIVE_CAT( arg, _bstree_kv_values_as_array )
Type *BSTree_kv_values_as_array( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t *count );

/*
   Access
*/

/**
   BSTree_kv_cursor_key_at

   Returns the value of the key that the BSTree_kv_cursor_t instance is pointing to.

   @param  BSTree_kv_cursor_t instance
   @return a Key value
*/
#define BSTree_kv_cursor_key_at( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_key_at )
Key BSTree_kv_cursor_key_at( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_item_at

   Returns the value of the item that the BSTree_kv_cursor_t instance is pointing to.

   @param  BSTree_kv_cursor_t instance
   @return a Type value
*/
#define BSTree_kv_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_item_at )
Type BSTree_kv_cursor_item_at( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_key_at

   Returns the value of the key that the BSTree_kv_t instance's internal
   cursor is pointing to.

   @param  bstree BSTree_kv_t instance
   @return a Key value
*/
#define BSTree_kv_key_at( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_at )
Key BSTree_kv_key_at( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_item_at

   Returns the value of the item that the BSTree_kv_t instance's internal
   cursor is pointing to.

   @param  bstree BSTree_kv_t instance
   @return a Type value
*/
#define BSTree_kv_item_at( arg ) PRIMITIVE_CAT( arg, _bstree_kv_item_at )
Type BSTree_kv_item_at( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_key

   Returns the value of the key pointed to by index. First index is 0.

   @param  bstree BSTree_kv_t instance
   @param  index desired index
   @return a Key value
*/
#define BSTree_kv_key( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key )
Type BSTree_kv_key( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_kv_item

   Returns the value of the item pointed to by index. First index is 0.

   @param  bstree BSTree_kv_t instance
   @param  index desired index
   @return a Type value
*/
#define BSTree_kv_item( arg ) PRIMITIVE_CAT( arg, _bstree_kv_item )
Type BSTree_kv_item( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_kv_first

   Returns the value of the first item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
   @return a Type value
*/
#define BSTree_kv_first( arg ) PRIMITIVE_CAT( arg, _bstree_kv_first )
Type BSTree_kv_first( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_last

   Returns the value of the last item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
   @return a Type value
*/
#define BSTree_kv_last( arg ) PRIMITIVE_CAT( arg, _bstree_kv_last )
Type BSTree_kv_last( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_key_first

   Returns the key of the first item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
   @return a Key value
*/
#define BSTree_kv_key_first( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_first )
Key BSTree_kv_key_first( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_key_last

   Returns the key of the last item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
   @return a Key value
*/
#define BSTree_kv_key_last( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_last )
Key BSTree_kv_key_last( Prefix )( BSTree_kv_type( Prefix ) *current );


/*
   Measurement
*/

/**
   BSTree_kv_count

   Returns the number of items in the BSTree_kv_t instance.

   @param  bstree BSTree_kv_t instance
   @return number of items in BSTree_kv instance
*/
#define BSTree_kv_count( arg ) PRIMITIVE_CAT( arg, _bstree_kv_count )
int32_t BSTree_kv_count( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_height

   Returns the (max) height of the BSTree_kv_t instance.

   @param  bstree BSTree_kv_t instance
   @return (max) height of the BSTree_kv instance
*/
#define BSTree_kv_height( arg ) PRIMITIVE_CAT( arg, _bstree_kv_height )
int32_t BSTree_kv_height( Prefix )( BSTree_kv_type( Prefix ) *bstree );


/*
   Status report
*/

/**
   BSTree_kv_off

   Returns 1 if the BSTree_kv_t instance's internal cursor is off, otherwise 0.

   @param  bstree BSTree_kv_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define BSTree_kv_off( arg ) PRIMITIVE_CAT( arg, _bstree_kv_off )
int32_t BSTree_kv_off( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_cursor_off

   Returns 1 if the BSTree_kv_cursor_t instance is off, otherwise 0.

   @param  cursor BSTree_kv_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define BSTree_kv_cursor_off( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_off )
int32_t BSTree_kv_cursor_off( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_is_first

   Returns 1 if the BSTree_kv_cursor_t instance is at the first item, otherwise 0.

   @param  cursor BSTree_kv_cursor_t instance
   @return 1 if internal cursor is at the first item, otherwise 0
*/
#define BSTree_kv_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_is_first )
int32_t BSTree_kv_cursor_is_first( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_is_last

   Returns 1 if the BSTree_kv_cursor_t instance is at the last item, otherwise 0.

   @param  cursor BSTree_kv_cursor_t instance
   @return 1 if internal cursor is at the last item, otherwise 0
*/
#define BSTree_kv_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_is_last )
int32_t BSTree_kv_cursor_is_last( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_key_search_forth

   Searches from the current position of the BSTree_kv_cursor_t instance for key.

   @param  cursor BSTree_kv_cursor_t instance
   @param  key the key to search for
*/
#define BSTree_kv_cursor_key_search_forth( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_key_search_forth )
void BSTree_kv_cursor_key_search_forth( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   BSTree_kv_cursor_key_search_forth_eq_fn

   Searches from the current position of the BSTree_kv_cursor_t instance for
   key that satisfies equalty_test_func

   @param  cursor BSTree_kv_cursor_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define BSTree_kv_cursor_key_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_key_search_forth_eq_fn )
void BSTree_kv_cursor_key_search_forth_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   BSTree_kv_cursor_search_forth

   Searches from the current position of the BSTree_kv_cursor_t instance for value.

   @param  cursor BSTree_kv_cursor_t instance
   @param  value the value to search for
*/
#define BSTree_kv_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_search_forth )
void BSTree_kv_cursor_search_forth( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Type value );

/**
   BSTree_kv_cursor_search_forth_eq_fn

   Searches from the current position of the BSTree_kv_cursor_t instance for
   value that satisfies equalty_test_func

   @param  cursor BSTree_kv_cursor_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define BSTree_kv_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_search_forth_eq_fn )
void BSTree_kv_cursor_search_forth_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_kv_cursor_key_search_back

   Searches from the current position of the BSTree_kv_cursor_t instance for key.

   @param  cursor BSTree_kv_cursor_t instance
   @param  key the key to search for
*/
#define BSTree_kv_cursor_key_search_back( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_key_search_back )
void BSTree_kv_cursor_key_search_back( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   BSTree_kv_cursor_key_search_back_eq_fn

   Searches from the current position of the BSTree_kv_cursor_t instance for
   key that satisfies equalty_test_func

   @param  cursor BSTree_kv_cursor_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define BSTree_kv_cursor_key_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_key_search_back_eq_fn )
void BSTree_kv_cursor_key_search_back_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   BSTree_kv_cursor_search_back

   Searches from the current position of the BSTree_kv_cursor_t instance for value.

   @param  cursor BSTree_kv_cursor_t instance
   @param  value the value to search for
*/
#define BSTree_kv_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_search_back )
void BSTree_kv_cursor_search_back( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Type value );

/**
   BSTree_kv_cursor_search_back_eq_fn

   Searches from the current position of the BSTree_kv_cursor_t instance for
   value that satisfies equalty_test_func

   @param  cursor BSTree_kv_cursor_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define BSTree_kv_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_search_back_eq_fn )
void BSTree_kv_cursor_search_back_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_kv_is_empty

   Returns 1 if the BSTree_kv_t instance contains no items, otherwise 0.

   @param  bstree BSTree_kv_t instance
   @return 1 if empty, otherwise 0
*/
#define BSTree_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _bstree_kv_is_empty )
int32_t BSTree_kv_is_empty( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_is_first

   Returns 1 if the BSTree_kv_t instance is at the first item, otherwise 0.

   @param  current BSTree_kv_t instance
   @return 1 if internal cursor is at the first item, otherwise 0
*/
#define BSTree_kv_is_first( arg ) PRIMITIVE_CAT( arg, _bstree_kv_is_first )
int32_t BSTree_kv_is_first( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_is_last

   Returns 1 if the BSTree_kv_t instance is at the last item, otherwise 0.

   @param  current BSTree_kv_t instance
   @return 1 if internal cursor is at the last item, otherwise 0
*/
#define BSTree_kv_is_last( arg ) PRIMITIVE_CAT( arg, _bstree_kv_is_last )
int32_t BSTree_kv_is_last( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_has

   Returns 1 if the BSTree_kv_t instance contains the key, otherwise 0.

   @param  bstree BSTree_kv_t instance
   @param  key the key to search for
   @return 1 if bstree has key, otherwise 0
*/
#define BSTree_kv_has( arg ) PRIMITIVE_CAT( arg, _bstree_kv_has )
int32_t BSTree_kv_has( Prefix )( BSTree_kv_type( Prefix ) *bstree, Key key );

/**
   BSTree_kv_has_eq_fn

   Returns 1 if the BSTree_kv_t instance contains the key, otherwise 0.

   @param  bstree BSTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key matches
   @return 1 if bstree has key, otherwise 0
*/
#define BSTree_kv_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_has_eq_fn )
int32_t BSTree_kv_has_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *bstree,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   BSTree_kv_has_value

   Returns 1 if the BSTree_kv_t instance contains the key, otherwise 0.

   @param  bstree BSTree_kv_t instance
   @param  value the value to search for
   @return 1 if bstree has value, otherwise 0
*/
#define BSTree_kv_has_value( arg ) PRIMITIVE_CAT( arg, _bstree_kv_has_value )
int32_t BSTree_kv_has_value( Prefix )( BSTree_kv_type( Prefix ) *bstree, Type value );

/**
   BSTree_kv_has_value_eq_fn

   Returns 1 if the BSTree_kv_t instance contains the key, otherwise 0.

   @param  bstree BSTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value matches
   @return 1 if bstree has value, otherwise 0
*/
#define BSTree_kv_has_value_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_has_value_eq_fn )
int32_t BSTree_kv_has_value_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *bstree,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_kv_occurrences

   Returns count of matching keys int the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
   @param  key the key to search for
   @return count of matching keys in bstree
*/
#define BSTree_kv_occurrences( arg ) PRIMITIVE_CAT( arg, _bstree_kv_occurrences )
int32_t BSTree_kv_occurrences( Prefix )( BSTree_kv_type( Prefix ) *current, Key key );

/**
   BSTree_kv_occurrences_eq_fn

   Returns count of matching keys in the BSTree_kv_t instance according to
   equality_test_func.

   @param  current BSTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key matches
   @return count of matching keys in bstree
*/
#define BSTree_kv_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_occurrences_eq_fn )
int32_t BSTree_kv_occurrences_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   BSTree_kv_occurrences_value

   Returns count of matching values int the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
   @param  value the value to search for
   @return count of matching values in bstree
*/
#define BSTree_kv_occurrences_value( arg ) PRIMITIVE_CAT( arg, _bstree_kv_occurrences_value )
int32_t BSTree_kv_occurrences_value( Prefix )( BSTree_kv_type( Prefix ) *current, Type value );

/**
   BSTree_kv_occurrences_value_eq_fn

   Returns count of matching values in the BSTree_kv_t instance according to
   equality_test_func.

   @param  current BSTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value matches
   @return count of matching values in bstree
*/
#define BSTree_kv_occurrences_value_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_occurrences_value_eq_fn )
int32_t BSTree_kv_occurrences_value_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);


/*
   Cursor movement
*/

/**
   BSTree_kv_cursor_back

   Moves the BSTree_kv_cursor_t instance to the previous item or off.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_back( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_back )
void BSTree_kv_cursor_back( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_forth

   Moves the BSTree_kv_cursor_t instance to the next item or off.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_forth( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_forth )
void BSTree_kv_cursor_forth( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_go

   Moves the BSTree_kv_t instance's internal cursor to the ith item in the bstree.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define BSTree_kv_cursor_go( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_go )
void BSTree_kv_cursor_go( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, int32_t index );

/**
   BSTree_kv_cursor_go_to_key

   Moves the BSTree_kv_t instance's internal cursor to the item in the bstree with
   a matching key.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
   @param  key the key where the cursor will be moved to
*/
#define BSTree_kv_cursor_go_to_key( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_go_to_key )
void BSTree_kv_cursor_go_to_key( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   BSTree_kv_cursor_finish

   Moves the BSTree_kv_cursor_t instance to the last item or off if the bstree is empty.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_finish( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_finish )
void BSTree_kv_cursor_finish( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_start

   Moves the BSTree_kv_cursor_t instance to the first item or off if the bstree is empty.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_start( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_start )
void BSTree_kv_cursor_start( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_remove_at

   Remove the item at the BSTree_kv_cursor_t instance.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_remove_at )
void BSTree_kv_cursor_remove_at( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_remove_at_and_dispose

   Remove and dispose the item at the BSTree_kv_cursor_t instance.

   @param  bstree_kv_cursor BSTree_kv_cursor_t instance
*/
#define BSTree_kv_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_remove_at_and_dispose )
void BSTree_kv_cursor_remove_at_and_dispose( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list BSTree_kv_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define BSTree_kv_cursor_index( arg ) PRIMITIVE_CAT( arg, _bstree_kv_cursor_index )
int32_t BSTree_kv_cursor_index( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor );

/**
   BSTree_kv_back

   Moves the BSTree_kv_t instance internal cursor to the previous item or off.

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_back( arg ) PRIMITIVE_CAT( arg, _bstree_kv_back )
void BSTree_kv_back( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_forth

   Moves the BSTree_kv_t instance internal cursor to the next item or off.

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_forth( arg ) PRIMITIVE_CAT( arg, _bstree_kv_forth )
void BSTree_kv_forth( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_go

   Moves the BSTree_kv_t instance's internal cursor to the ith item in the bstree.

   @param  bstree BSTree_kv_t instance
   @param  index the index where the  will be moved to
*/
#define BSTree_kv_go( arg ) PRIMITIVE_CAT( arg, _bstree_kv_go )
void BSTree_kv_go( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_kv_go_to_key

   Moves the BSTree_kv_t instance's internal cursor to the item in the bstree with
   a matching key.

   @param  current BSTree_kv_t instance
   @param  key the key where the cursor will be moved to
*/
#define BSTree_kv_go_to_key( arg ) PRIMITIVE_CAT( arg, _bstree_kv_go_to_key )
void BSTree_kv_go_to_key( Prefix )( BSTree_kv_type( Prefix ) *current, Key key );

/**
   BSTree_kv_finish

   Moves the BSTree_kv_t instance's internal cursor to the last item or off if the bstree is empty.

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_finish( arg ) PRIMITIVE_CAT( arg, _bstree_kv_finish )
void BSTree_kv_finish( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_start

   Moves the BSTree_kv_t instance's internal cursor to the first item or off if the bstree is empty.

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_start( arg ) PRIMITIVE_CAT( arg, _bstree_kv_start )
void BSTree_kv_start( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  list BSTree_kv_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define BSTree_kv_index( arg ) PRIMITIVE_CAT( arg, _bstree_kv_index )
int32_t BSTree_kv_index( Prefix )( BSTree_kv_type( Prefix ) *list );


/**
   BSTree_kv_key_search_forth

   Searches from the current position of the BSTree_kv_t instance for key.

   @param  current BSTree_kv_t instance
   @param  key the key to search for
*/
#define BSTree_kv_key_search_forth( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_search_forth )
void BSTree_kv_key_search_forth( Prefix )( BSTree_kv_type( Prefix ) *current, Key key );

/**
   BSTree_kv_key_search_forth_eq_fn

   Searches from the current position of the BSTree_kv_t instance for
   key that satisfies equalty_test_func

   @param  current BSTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define BSTree_kv_key_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_search_forth_eq_fn )
void BSTree_kv_key_search_forth_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   BSTree_kv_search_forth

   Searches from the current position of the BSTree_kv_t instance for value.

   @param  current BSTree_kv_t instance
   @param  value the value to search for
*/
#define BSTree_kv_search_forth( arg ) PRIMITIVE_CAT( arg, _bstree_kv_search_forth )
void BSTree_kv_search_forth( Prefix )( BSTree_kv_type( Prefix ) *current, Type value );

/**
   BSTree_kv_search_forth_eq_fn

   Searches from the current position of the BSTree_kv_t instance for
   value that satisfies equalty_test_func

   @param  current BSTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define BSTree_kv_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_search_forth_eq_fn )
void BSTree_kv_search_forth_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   BSTree_kv_key_search_back

   Searches from the current position of the BSTree_kv_t instance for key.

   @param  current BSTree_kv_t instance
   @param  key the key to search for
*/
#define BSTree_kv_key_search_back( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_search_back )
void BSTree_kv_key_search_back( Prefix )( BSTree_kv_type( Prefix ) *current, Key key );

/**
   BSTree_kv_key_search_back_eq_fn

   Searches from the current position of the BSTree_kv_t instance for
   key that satisfies equalty_test_func

   @param  current BSTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define BSTree_kv_key_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_key_search_back_eq_fn )
void BSTree_kv_key_search_back_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   BSTree_kv_search_back

   Searches from the current position of the BSTree_kv_t instance for value.

   @param  current BSTree_kv_t instance
   @param  value the value to search for
*/
#define BSTree_kv_search_back( arg ) PRIMITIVE_CAT( arg, _bstree_kv_search_back )
void BSTree_kv_search_back( Prefix )( BSTree_kv_type( Prefix ) *current, Type value );

/**
   BSTree_kv_search_back_eq_fn

   Searches from the current position of the BSTree_kv_t instance for
   value that satisfies equalty_test_func

   @param  current BSTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define BSTree_kv_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _bstree_kv_search_back_eq_fn )
void BSTree_kv_search_back_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/*
   Element change
*/

/**
   BSTree_kv_put

   Put the key-value pair into the BSTree_kv_t instance. Replace any existing item
   that has the same key.

   @param  bstree BSTree_kv_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define BSTree_kv_put( arg ) PRIMITIVE_CAT( arg, _bstree_kv_put )
void BSTree_kv_put( Prefix )( BSTree_kv_type( Prefix ) *bstree, Type value, Key key );


/*
   Removal
*/

/**
   BSTree_kv_remove

   Remove the item in the BSTree_kv_t instance that has the key.

   @param  bstree BSTree_kv_t instance
   @param  key the key for the value
*/
#define BSTree_kv_remove( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove )
void BSTree_kv_remove( Prefix )( BSTree_kv_type( Prefix ) *bstree, Key key );

/**
   BSTree_kv_remove_and_dispose

   Remove the item in the BSTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  bstree BSTree_kv_t instance
   @param  key the key for the value
*/
#define BSTree_kv_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_and_dispose )
void BSTree_kv_remove_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *bstree, Key key );

/**
   BSTree_kv_remove_by_index

   Remove the item in the BSTree_kv_t instance at index.

   @param  bstree BSTree_kv_t instance
   @param  index the index for the item
*/
#define BSTree_kv_remove_by_index( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_by_index )
void BSTree_kv_remove_by_index( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_kv_remove_by_index_and_dispose

   Remove the item in the BSTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  bstree BSTree_kv_t instance
   @param  index the index for the item
*/
#define BSTree_kv_remove_by_index_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_by_index_and_dispose )
void BSTree_kv_remove_by_index_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_kv_remove_value

   Remove the item in the BSTree_kv_t instance at index.

   @param  bstree BSTree_kv_t instance
   @param  value the value to remove
*/
#define BSTree_kv_remove_value( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_value )
void BSTree_kv_remove_value( Prefix )( BSTree_kv_type( Prefix ) *bstree, Type value );

/**
   BSTree_kv_remove_value_and_dispose

   Remove the item in the BSTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  bstree BSTree_kv_t instance
   @param  value the value to remove and dispose
*/
#define BSTree_kv_remove_value_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_value_and_dispose )
void BSTree_kv_remove_value_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *bstree, Type value );

/**
   BSTree_kv_remove_at

   Remove the item at the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
*/
#define BSTree_kv_remove_at( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_at )
void BSTree_kv_remove_at( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_remove_at_and_dispose

   Remove and dispose the item at the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
*/
#define BSTree_kv_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_at_and_dispose )
void BSTree_kv_remove_at_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_remove_first

   Remove the first item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
*/
#define BSTree_kv_remove_first( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_first )
void BSTree_kv_remove_first( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_remove_first_and_dispose

   Remove and dispose the first item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
*/
#define BSTree_kv_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_first_and_dispose )
void BSTree_kv_remove_first_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_remove_last

   Remove the last item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
*/
#define BSTree_kv_remove_last( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_last )
void BSTree_kv_remove_last( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_remove_last_and_dispose

   Remove and dispose the last item in the BSTree_kv_t instance.

   @param  current BSTree_kv_t instance
*/
#define BSTree_kv_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_remove_last_and_dispose )
void BSTree_kv_remove_last_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current );

/**
   BSTree_kv_wipe_out

   Remove all items in the BSTree_kv_t instance.

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_wipe_out( arg ) PRIMITIVE_CAT( arg, _bstree_kv_wipe_out )
void BSTree_kv_wipe_out( Prefix )( BSTree_kv_type( Prefix ) *bstree );

/**
   BSTree_kv_wipe_out_and_dispose

   Remove all items in the BSTree_kv_t instance. Dispose of all keys and values.

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_kv_wipe_out_and_dispose )
void BSTree_kv_wipe_out_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *bstree );


/*
   Resize
*/

/**
   BSTree_kv_balance

   Balance the tree

   @param  bstree BSTree_kv_t instance
*/
#define BSTree_kv_balance( arg ) PRIMITIVE_CAT( arg, _bstree_kv_balance )
void BSTree_kv_balance( Prefix )( BSTree_kv_type( Prefix ) *bstree );


#ifdef __cplusplus
}
#endif

/* End of file */




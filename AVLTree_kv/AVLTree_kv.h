/**
 @file AVLTree_kv.h
 @author Greg Lee
 @version 2.0.0
 @brief: "AVL Binary Search Trees of keys with values"

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

 Function declarations for the opaque AVLTree_kv_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define AVLTREE_KV_VERSION_MAJOR 2
#define AVLTREE_KV_VERSION_MINOR 0
#define AVLTREE_KV_VERSION_PATCH 0

#define AVLTREE_KV_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define AVLTREE_KV_VERSION \
   AVLTREE_KV_MAKE_VERSION( AVLTREE_KV_VERSION_MAJOR, \
                           AVLTREE_KV_VERSION_MINOR, \
                           AVLTREE_KV_VERSION_PATCH )

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

#define AVLTree_kv_struct( arg ) PRIMITIVE_CAT( arg, _avltree_kv_struct )
#define AVLTree_kv_type( arg ) PRIMITIVE_CAT( arg, _avltree_kv_t )
#define AVLTree_kv_name( arg ) PRIMITIVE_CAT( arg, _avltree_kv )

#define AVLTree_kv_cursor_struct( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_struct )
#define AVLTree_kv_cursor_type( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_t )
#define AVLTree_kv_cursor_name( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor )

/**
   Structure declarations
*/

struct AVLTree_kv_struct( Prefix );
struct AVLTree_kv_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct AVLTree_kv_struct( Prefix ) AVLTree_kv_type( Prefix );
typedef struct AVLTree_kv_cursor_struct( Prefix ) AVLTree_kv_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   AVLTree_kv_make

   Return a new AVLTree_kv_t instance with a default number of buckets.

   @return AVLTree_kv_t instance
*/
#define AVLTree_kv_make( arg ) PRIMITIVE_CAT( arg, _avltree_kv_make )
AVLTree_kv_type( Prefix ) * AVLTree_kv_make( Prefix )( void );

/**
   AVLTree_kv_make_from_array

   Return a new AVLTree_kv_t instance that has the same content as arrays. The key
   and value items in arrays are not copied.

   @param  key_array the array to copy keys from
   @param  value_array the array to copy values from
   @param  count the number of items to copy
   @return AVLTree_kv_t instance
*/
#define AVLTree_kv_make_from_array( arg ) PRIMITIVE_CAT( arg, _avltree_kv_make_from_array )
AVLTree_kv_type( Prefix ) * AVLTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count );

/**
   AVLTree_kv_clone

   Return a new AVLTree_kv_t instance that has the same content as avltree_kv. The key
   and value items in avltree_kv are not copied.

   @param  avltree_kv the AVLTree_kv_t instance to copy from
   @return AVLTree_kv_t instance
*/
#define AVLTree_kv_clone( arg ) PRIMITIVE_CAT( arg, _avltree_kv_clone )
AVLTree_kv_type( Prefix ) * AVLTree_kv_clone( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_deep_clone

   Return a new AVLTree_kv_t instance with a duplicate items from avltree_kv

   @return AVLTree_kv_t instance
*/

#define AVLTree_kv_deep_clone( arg ) PRIMITIVE_CAT( arg, _avltree_kv_deep_clone )
AVLTree_kv_type( Prefix ) *
AVLTree_kv_deep_clone( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_is_equal

   Returns 1 if current is equal to other

   @param  current the AVLTree_kv_t instance to compare to
   @param  other the AVLTree_kv_t instance to compare
   @return 1 if equal, 0 otherwise
*/
#define AVLTree_kv_is_equal( arg ) PRIMITIVE_CAT( arg, _avltree_kv_is_equal )
int32_t AVLTree_kv_is_equal( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other );

/**
   AVLTree_kv_is_deep_equal

   Returns 1 if current is deep equal to other

   @param  current the AVLTree_kv_t instance to compare to
   @param  other the AVLTree_kv_t instance to compare
   @return 1 if deep equal, 0 otherwise
*/
#define AVLTree_kv_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _avltree_kv_is_deep_equal )
int32_t AVLTree_kv_is_deep_equal( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other );

/**
   AVLTree_kv_copy

   Copies (shallow) contents of other into current. Contents of current are deep
   disposed.

   @param  current the AVLTree_kv_t instance to copy into
   @param  other the AVLTree_kv_t instance to copy
*/
#define AVLTree_kv_copy( arg ) PRIMITIVE_CAT( arg, _avltree_kv_copy )
void AVLTree_kv_copy( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other );

/**
   AVLTree_kv_deep_copy

   Copies (deep) contents of other into current. Contents of current are deep
   disposed.

   @param  current the AVLTree_kv_t instance to copy into
   @param  other the AVLTree_kv_t instance to copy
*/
#define AVLTree_kv_deep_copy( arg ) PRIMITIVE_CAT( arg, _avltree_kv_deep_copy )
void AVLTree_kv_deep_copy( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other );

/**
   AVLTree_kv_cursor_make

   Return a new AVLTree_kv_t cursor instance.

   @param  the AVLTree_kv_t instance the new cursor works on
   @return AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_make( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_make )
AVLTree_kv_cursor_type( Prefix ) * AVLTree_kv_cursor_make( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );


/*
   Disposal
*/

/**
   AVLTree_kv_dispose

   Frees a AVLTree_kv_t instance without freeing its contained keys and values.

   @param AVLTree_kv_t instance
*/
#define AVLTree_kv_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_dispose )
void AVLTree_kv_dispose( Prefix )( AVLTree_kv_type( Prefix ) **avltree_kv );

/**
   AVLTree_kv_deep_dispose

   Frees a AVLTree_kv_t instance and its contained keys and values.

   @param AVLTree_kv_t instance
*/
#define AVLTree_kv_deep_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_deep_dispose )
void AVLTree_kv_deep_dispose( Prefix )( AVLTree_kv_type( Prefix ) **avltree_kv );

/**
   AVLTree_kv_cursor_dispose

   Frees a AVLTree_kv_cursor_t instance. Its avltree_kv is not disposed.

   @param AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_dispose )
void AVLTree_kv_cursor_dispose( Prefix )( AVLTree_kv_cursor_type( Prefix ) **cursor );


/**
   AVLTree_kv_keys_as_array

   Returns the keys as an array.

   @param  AVLTree_kv_t instance
   @param  count pointer to returned number of elements in the array
   @return array of Key values
*/
#define AVLTree_kv_keys_as_array( arg ) PRIMITIVE_CAT( arg, _avltree_kv_keys_as_array )
Key *AVLTree_kv_keys_as_array( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, int32_t *count );

/**
   AVLTree_kv_values_as_array

   Returns the values as an array.

   @param  AVLTree_kv_t instance
   @param  count pointer to returned number of elements in the array
   @return array of Type values
*/
#define AVLTree_kv_values_as_array( arg ) PRIMITIVE_CAT( arg, _avltree_kv_values_as_array )
Type *AVLTree_kv_values_as_array( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, int32_t *count );

/*
   Access
*/

/**
   AVLTree_kv_cursor_key_at

   Returns the key of the item that the AVLTree_kv_cursor_t instance is pointing to.

   @param  AVLTree_kv_cursor_t instance
   @return a Key value
*/
#define AVLTree_kv_cursor_key_at( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_key_at )
Key AVLTree_kv_cursor_key_at( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_item_at

   Returns the value of the item that the AVLTree_kv_cursor_t instance is pointing to.

   @param  AVLTree_kv_cursor_t instance
   @return a Type value
*/
#define AVLTree_kv_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_item_at )
Type AVLTree_kv_cursor_item_at( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_key_at

   Returns the key of the item that the AVLTree_kv_t instance's internal
   cursor is pointing to.

   @param  avltree_kv AVLTree_kv_t instance
   @return a Key value
*/
#define AVLTree_kv_key_at( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_at )
Key AVLTree_kv_key_at( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_item_at

   Returns the value of the item that the AVLTree_kv_t instance's internal
   cursor is pointing to.

   @param  avltree_kv AVLTree_kv_t instance
   @return a Type value
*/
#define AVLTree_kv_item_at( arg ) PRIMITIVE_CAT( arg, _avltree_kv_item_at )
Type AVLTree_kv_item_at( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_key

   Returns the key of the item pointed to by index. First index is 0.

   @param  avltree_kv AVLTree_kv_t instance
   @param  index desired index
   @return a Key value
*/
#define AVLTree_kv_key( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key )
Key AVLTree_kv_key( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, int32_t index );

/**
   AVLTree_kv_item

   Returns the value of the item pointed to by index. First index is 0.

   @param  avltree_kv AVLTree_kv_t instance
   @param  index desired index
   @return a Type value
*/
#define AVLTree_kv_item( arg ) PRIMITIVE_CAT( arg, _avltree_kv_item )
Type AVLTree_kv_item( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, int32_t index );

/**
   AVLTree_kv_first

   Returns the value of the first item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
   @return a Type value
*/
#define AVLTree_kv_first( arg ) PRIMITIVE_CAT( arg, _avltree_kv_first )
Type AVLTree_kv_first( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_last

   Returns the value of the last item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
   @return a Type value
*/
#define AVLTree_kv_last( arg ) PRIMITIVE_CAT( arg, _avltree_kv_last )
Type AVLTree_kv_last( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_key_first

   Returns the key of the first item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
   @return a Key value
*/
#define AVLTree_kv_key_first( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_first )
Key AVLTree_kv_key_first( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_key_last

   Returns the key of the last item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
   @return a Key value
*/
#define AVLTree_kv_key_last( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_last )
Key AVLTree_kv_key_last( Prefix )( AVLTree_kv_type( Prefix ) *current );


/*
   Measurement
*/

/**
   AVLTree_kv_count

   Returns the number of items in the AVLTree_kv_t instance.

   @param  avltree_kv AVLTree_kv_t instance
   @return number of items in AVLTree_kv instance
*/
#define AVLTree_kv_count( arg ) PRIMITIVE_CAT( arg, _avltree_kv_count )
int32_t AVLTree_kv_count( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_height

   Returns the (max) height of the AVLTree_kv_t instance.

   @param  avltree_kv AVLTree_kv_t instance
   @return (max) height of the AVLTree_kv instance
*/
#define AVLTree_kv_height( arg ) PRIMITIVE_CAT( arg, _avltree_kv_height )
int32_t AVLTree_kv_height( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );


/*
   Status report
*/

/**
   AVLTree_kv_off

   Returns 1 if the AVLTree_kv_t instance's internal cursor is off, otherwise 0.

   @param  avltree_kv AVLTree_kv_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define AVLTree_kv_off( arg ) PRIMITIVE_CAT( arg, _avltree_kv_off )
int32_t AVLTree_kv_off( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_cursor_off

   Returns 1 if the AVLTree_kv_cursor_t instance is off, otherwise 0.

   @param  cursor AVLTree_kv_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define AVLTree_kv_cursor_off( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_off )
int32_t AVLTree_kv_cursor_off( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_is_first

   Returns 1 if the AVLTree_kv_cursor_t instance is at the first item, otherwise 0.

   @param  cursor AVLTree_kv_cursor_t instance
   @return 1 if internal cursor is at the first item, otherwise 0
*/
#define AVLTree_kv_cursor_is_first( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_is_first )
int32_t AVLTree_kv_cursor_is_first( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_is_last

   Returns 1 if the AVLTree_kv_cursor_t instance is at the last item, otherwise 0.

   @param  cursor AVLTree_kv_cursor_t instance
   @return 1 if internal cursor is at the last item, otherwise 0
*/
#define AVLTree_kv_cursor_is_last( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_is_last )
int32_t AVLTree_kv_cursor_is_last( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_key_search_forth

   Searches from the current position of the AVLTree_kv_cursor_t instance for key.

   @param  cursor AVLTree_kv_cursor_t instance
   @param  key the key to search for
*/
#define AVLTree_kv_cursor_key_search_forth( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_key_search_forth )
void AVLTree_kv_cursor_key_search_forth( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   AVLTree_kv_cursor_key_search_forth_eq_fn

   Searches from the current position of the AVLTree_kv_cursor_t instance for
   key that satisfies equalty_test_func

   @param  cursor AVLTree_kv_cursor_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define AVLTree_kv_cursor_key_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_key_search_forth_eq_fn )
void AVLTree_kv_cursor_key_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   AVLTree_kv_cursor_search_forth

   Searches from the current position of the AVLTree_kv_cursor_t instance for value.

   @param  cursor AVLTree_kv_cursor_t instance
   @param  value the value to search for
*/
#define AVLTree_kv_cursor_search_forth( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_search_forth )
void AVLTree_kv_cursor_search_forth( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Type value );

/**
   AVLTree_kv_cursor_search_forth_eq_fn

   Searches from the current position of the AVLTree_kv_cursor_t instance for
   value that satisfies equalty_test_func

   @param  cursor AVLTree_kv_cursor_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define AVLTree_kv_cursor_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_search_forth_eq_fn )
void AVLTree_kv_cursor_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   AVLTree_kv_cursor_key_search_back

   Searches from the current position of the AVLTree_kv_cursor_t instance for key.

   @param  cursor AVLTree_kv_cursor_t instance
   @param  key the key to search for
*/
#define AVLTree_kv_cursor_key_search_back( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_key_search_back )
void AVLTree_kv_cursor_key_search_back( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   AVLTree_kv_cursor_key_search_back_eq_fn

   Searches from the current position of the AVLTree_kv_cursor_t instance for
   key that satisfies equalty_test_func

   @param  cursor AVLTree_kv_cursor_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define AVLTree_kv_cursor_key_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_key_search_back_eq_fn )
void AVLTree_kv_cursor_key_search_back_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   AVLTree_kv_cursor_search_back

   Searches from the current position of the AVLTree_kv_cursor_t instance for value.

   @param  cursor AVLTree_kv_cursor_t instance
   @param  value the value to search for
*/
#define AVLTree_kv_cursor_search_back( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_search_back )
void AVLTree_kv_cursor_search_back( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Type value );

/**
   AVLTree_kv_cursor_search_back_eq_fn

   Searches from the current position of the AVLTree_kv_cursor_t instance for
   value that satisfies equalty_test_func

   @param  cursor AVLTree_kv_cursor_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define AVLTree_kv_cursor_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_search_back_eq_fn )
void AVLTree_kv_cursor_search_back_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   AVLTree_kv_is_empty

   Returns 1 if the AVLTree_kv_t instance contains no items, otherwise 0.

   @param  avltree_kv AVLTree_kv_t instance
   @return 1 if empty, otherwise 0
*/
#define AVLTree_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _avltree_kv_is_empty )
int32_t AVLTree_kv_is_empty( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_is_first

   Returns 1 if the AVLTree_kv_t instance is at the first item, otherwise 0.

   @param  current AVLTree_kv_t instance
   @return 1 if internal cursor is at the first item, otherwise 0
*/
#define AVLTree_kv_is_first( arg ) PRIMITIVE_CAT( arg, _avltree_kv_is_first )
int32_t AVLTree_kv_is_first( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_is_last

   Returns 1 if the AVLTree_kv_t instance is at the last item, otherwise 0.

   @param  current AVLTree_kv_t instance
   @return 1 if internal cursor is at the last item, otherwise 0
*/
#define AVLTree_kv_is_last( arg ) PRIMITIVE_CAT( arg, _avltree_kv_is_last )
int32_t AVLTree_kv_is_last( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_has

   Returns 1 if the AVLTree_kv_t instance contains the key, otherwise 0.

   @param  avltree_kv AVLTree_kv_t instance
   @param  key the key to search for
   @return 1 if avltree_kv has key, otherwise 0
*/
#define AVLTree_kv_has( arg ) PRIMITIVE_CAT( arg, _avltree_kv_has )
int32_t AVLTree_kv_has( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, Key key );

/**
   AVLTree_kv_has_eq_fn

   Returns 1 if the AVLTree_kv_t instance contains the key, otherwise 0.

   @param  avltree AVLTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key matches
   @return 1 if avltree has key, otherwise 0
*/
#define AVLTree_kv_has_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_has_eq_fn )
int32_t AVLTree_kv_has_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *avltree,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   AVLTree_kv_has_value

   Returns 1 if the AVLTree_kv_t instance contains the key, otherwise 0.

   @param  avltree AVLTree_kv_t instance
   @param  value the value to search for
   @return 1 if avltree has value, otherwise 0
*/
#define AVLTree_kv_has_value( arg ) PRIMITIVE_CAT( arg, _avltree_kv_has_value )
int32_t AVLTree_kv_has_value( Prefix )( AVLTree_kv_type( Prefix ) *avltree, Type value );

/**
   AVLTree_kv_has_value_eq_fn

   Returns 1 if the AVLTree_kv_t instance contains the key, otherwise 0.

   @param  avltree AVLTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value matches
   @return 1 if avltree has value, otherwise 0
*/
#define AVLTree_kv_has_value_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_has_value_eq_fn )
int32_t AVLTree_kv_has_value_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *avltree,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   AVLTree_kv_occurrences

   Returns count of matching keys int the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
   @param  key the key to search for
   @return count of matching keys in avltree
*/
#define AVLTree_kv_occurrences( arg ) PRIMITIVE_CAT( arg, _avltree_kv_occurrences )
int32_t AVLTree_kv_occurrences( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key );

/**
   AVLTree_kv_occurrences_eq_fn

   Returns count of matching keys in the AVLTree_kv_t instance according to
   equality_test_func.

   @param  current AVLTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key matches
   @return count of matching keys in avltree
*/
#define AVLTree_kv_occurrences_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_occurrences_eq_fn )
int32_t AVLTree_kv_occurrences_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   AVLTree_kv_occurrences_value

   Returns count of matching values int the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
   @param  value the value to search for
   @return count of matching values in avltree
*/
#define AVLTree_kv_occurrences_value( arg ) PRIMITIVE_CAT( arg, _avltree_kv_occurrences_value )
int32_t AVLTree_kv_occurrences_value( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value );

/**
   AVLTree_kv_occurrences_value_eq_fn

   Returns count of matching values in the AVLTree_kv_t instance according to
   equality_test_func.

   @param  current AVLTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value matches
   @return count of matching values in avltree
*/
#define AVLTree_kv_occurrences_value_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_occurrences_value_eq_fn )
int32_t AVLTree_kv_occurrences_value_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);


/*
   Cursor movement
*/

/**
   AVLTree_kv_cursor_forth

   Moves the AVLTree_kv_cursor_t instance to the next item or off.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_forth( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_forth )
void AVLTree_kv_cursor_forth( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_back

   Moves the AVLTree_kv_cursor_t instance to the next item or off.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_back( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_back )
void AVLTree_kv_cursor_back( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_go

   Moves the AVLTree_kv_t instance's internal cursor to the ith item in the avltree_kv.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define AVLTree_kv_cursor_go( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_go )
void AVLTree_kv_cursor_go( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, int32_t index );

/**
   AVLTree_kv_cursor_go_to_key

   Moves the AVLTree_kv_t instance's internal cursor to the item in the avltree with
   a matching key.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
   @param  key the key where the cursor will be moved to
*/
#define AVLTree_kv_cursor_go_to_key( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_go_to_key )
void AVLTree_kv_cursor_go_to_key( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Key key );

/**
   AVLTree_kv_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list AVLTree_kv_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define AVLTree_kv_cursor_index( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_index )
int32_t AVLTree_kv_cursor_index( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_remove_at

   Remove the item at the AVLTree_kv_cursor_t instance.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_remove_at( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_remove_at )
void AVLTree_kv_cursor_remove_at( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_remove_at_and_dispose

   Remove and dispose the item at the AVLTree_kv_cursor_t instance.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_remove_at_and_dispose )
void AVLTree_kv_cursor_remove_at_and_dispose( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_start

   Moves the AVLTree_kv_cursor_t instance to the first item or off if the avltree_kv is empty.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_start( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_start )
void AVLTree_kv_cursor_start( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_cursor_finish

   Moves the AVLTree_kv_cursor_t instance to the last item or off if the avltree_kv is empty.

   @param  avltree_kv_cursor AVLTree_kv_cursor_t instance
*/
#define AVLTree_kv_cursor_finish( arg ) PRIMITIVE_CAT( arg, _avltree_kv_cursor_finish )
void AVLTree_kv_cursor_finish( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   AVLTree_kv_back

   Moves the AVLTree_kv_t instance internal cursor to the previous item or off.

   @param  avltree_kv AVLTree_kv_t instance
*/
#define AVLTree_kv_back( arg ) PRIMITIVE_CAT( arg, _avltree_kv_back )
void AVLTree_kv_back( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_forth

   Moves the AVLTree_kv_t instance internal cursor to the next item or off.

   @param  avltree_kv AVLTree_kv_t instance
*/
#define AVLTree_kv_forth( arg ) PRIMITIVE_CAT( arg, _avltree_kv_forth )
void AVLTree_kv_forth( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_go

   Moves the AVLTree_kv_t instance's internal cursor to the ith item in the avltree_kv.

   @param  avltree_kv AVLTree_kv_t instance
   @param  index the index where the  will be moved to
*/
#define AVLTree_kv_go( arg ) PRIMITIVE_CAT( arg, _avltree_kv_go )
void AVLTree_kv_go( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, int32_t index );

/**
   AVLTree_kv_go_to_key

   Moves the AVLTree_kv_t instance's internal cursor to the item in the avltree with
   a matching key.

   @param  current AVLTree_kv_t instance
   @param  key the key where the cursor will be moved to
*/
#define AVLTree_kv_go_to_key( arg ) PRIMITIVE_CAT( arg, _avltree_kv_go_to_key )
void AVLTree_kv_go_to_key( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key );

/**
   AVLTree_kv_start

   Moves the AVLTree_kv_t instance's internal cursor to the first item or off if the avltree_kv is empty.

   @param  avltree_kv AVLTree_kv_t instance
*/
#define AVLTree_kv_start( arg ) PRIMITIVE_CAT( arg, _avltree_kv_start )
void AVLTree_kv_start( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_finish

   Moves the AVLTree_kv_t instance's internal cursor to the last item or off if the avltree_kv is empty.

   @param  avltree_kv AVLTree_kv_t instance
*/
#define AVLTree_kv_finish( arg ) PRIMITIVE_CAT( arg, _avltree_kv_finish )
void AVLTree_kv_finish( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  list AVLTree_kv_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define AVLTree_kv_index( arg ) PRIMITIVE_CAT( arg, _avltree_kv_index )
int32_t AVLTree_kv_index( Prefix )( AVLTree_kv_type( Prefix ) *list );

/**
   AVLTree_kv_key_search_forth

   Searches from the current position of the AVLTree_kv_t instance for key.

   @param  current AVLTree_kv_t instance
   @param  key the key to search for
*/
#define AVLTree_kv_key_search_forth( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_search_forth )
void AVLTree_kv_key_search_forth( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key );

/**
   AVLTree_kv_key_search_forth_eq_fn

   Searches from the current position of the AVLTree_kv_t instance for
   key that satisfies equalty_test_func

   @param  current AVLTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define AVLTree_kv_key_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_search_forth_eq_fn )
void AVLTree_kv_key_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   AVLTree_kv_search_forth

   Searches from the current position of the AVLTree_kv_t instance for value.

   @param  current AVLTree_kv_t instance
   @param  value the value to search for
*/
#define AVLTree_kv_search_forth( arg ) PRIMITIVE_CAT( arg, _avltree_kv_search_forth )
void AVLTree_kv_search_forth( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value );

/**
   AVLTree_kv_search_forth_eq_fn

   Searches from the current position of the AVLTree_kv_t instance for
   value that satisfies equalty_test_func

   @param  current AVLTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define AVLTree_kv_search_forth_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_search_forth_eq_fn )
void AVLTree_kv_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);

/**
   AVLTree_kv_key_search_back

   Searches from the current position of the AVLTree_kv_t instance for key.

   @param  current AVLTree_kv_t instance
   @param  key the key to search for
*/
#define AVLTree_kv_key_search_back( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_search_back )
void AVLTree_kv_key_search_back( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key );

/**
   AVLTree_kv_key_search_back_eq_fn

   Searches from the current position of the AVLTree_kv_t instance for
   key that satisfies equalty_test_func

   @param  current AVLTree_kv_t instance
   @param  key the key to search for
   @param  equality_test_func returns 1 if key satisfies equality
*/
#define AVLTree_kv_key_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_key_search_back_eq_fn )
void AVLTree_kv_key_search_back_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
);

/**
   AVLTree_kv_search_back

   Searches from the current position of the AVLTree_kv_t instance for value.

   @param  current AVLTree_kv_t instance
   @param  value the value to search for
*/
#define AVLTree_kv_search_back( arg ) PRIMITIVE_CAT( arg, _avltree_kv_search_back )
void AVLTree_kv_search_back( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value );

/**
   AVLTree_kv_search_back_eq_fn

   Searches from the current position of the AVLTree_kv_t instance for
   value that satisfies equalty_test_func

   @param  current AVLTree_kv_t instance
   @param  value the value to search for
   @param  equality_test_func returns 1 if value satisfies equality
*/
#define AVLTree_kv_search_back_eq_fn( arg ) PRIMITIVE_CAT( arg, _avltree_kv_search_back_eq_fn )
void AVLTree_kv_search_back_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
);



/*
   Element change
*/

/**
   AVLTree_kv_put

   Put the key-value pair into the AVLTree_kv_t instance. Replace any existing item
   that has the same key.

   @param  avltree_kv AVLTree_kv_t instance
   @param  value the value to insert
   @param  key the key to insert
*/
#define AVLTree_kv_put( arg ) PRIMITIVE_CAT( arg, _avltree_kv_put )
void AVLTree_kv_put( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, Type value, Key key );


/*
   Removal
*/

/**
   AVLTree_kv_remove

   Remove the item in the AVLTree_kv_t instance that has the key.

   @param  avltree_kv AVLTree_kv_t instance
   @param  key the key for the value
*/
#define AVLTree_kv_remove( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove )
void AVLTree_kv_remove( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, Key key );

/**
   AVLTree_kv_remove_and_dispose

   Remove the item in the AVLTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  avltree_kv AVLTree_kv_t instance
   @param  key the key for the value
*/
#define AVLTree_kv_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_and_dispose )
void AVLTree_kv_remove_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv, Key key );

/**
   AVLTree_kv_remove_by_index

   Remove the item in the AVLTree_kv_t instance at index.

   @param  avltree AVLTree_kv_t instance
   @param  index the index for the item
*/
#define AVLTree_kv_remove_by_index( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_by_index )
void AVLTree_kv_remove_by_index( Prefix )( AVLTree_kv_type( Prefix ) *avltree, int32_t index );

/**
   AVLTree_kv_remove_by_index_and_dispose

   Remove the item in the AVLTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  avltree AVLTree_kv_t instance
   @param  index the index for the item
*/
#define AVLTree_kv_remove_by_index_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_by_index_and_dispose )
void AVLTree_kv_remove_by_index_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *avltree, int32_t index );

/**
   AVLTree_kv_remove_value

   Remove the item in the AVLTree_kv_t instance at index.

   @param  avltree AVLTree_kv_t instance
   @param  value the value to remove
*/
#define AVLTree_kv_remove_value( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_value )
void AVLTree_kv_remove_value( Prefix )( AVLTree_kv_type( Prefix ) *avltree, Type value );

/**
   AVLTree_kv_remove_value_and_dispose

   Remove the item in the AVLTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  avltree AVLTree_kv_t instance
   @param  value the value to remove and dispose
*/
#define AVLTree_kv_remove_value_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_value_and_dispose )
void AVLTree_kv_remove_value_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *avltree, Type value );

/**
   AVLTree_kv_remove_at

   Remove the item at the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
*/
#define AVLTree_kv_remove_at( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_at )
void AVLTree_kv_remove_at( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_remove_at_and_dispose

   Remove and dispose the item at the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
*/
#define AVLTree_kv_remove_at_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_at_and_dispose )
void AVLTree_kv_remove_at_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_remove_first

   Remove the first item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
*/
#define AVLTree_kv_remove_first( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_first )
void AVLTree_kv_remove_first( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_remove_first_and_dispose

   Remove and dispose the first item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
*/
#define AVLTree_kv_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_first_and_dispose )
void AVLTree_kv_remove_first_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_remove_last

   Remove the last item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
*/
#define AVLTree_kv_remove_last( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_last )
void AVLTree_kv_remove_last( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_remove_last_and_dispose

   Remove and dispose the last item in the AVLTree_kv_t instance.

   @param  current AVLTree_kv_t instance
*/
#define AVLTree_kv_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_remove_last_and_dispose )
void AVLTree_kv_remove_last_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current );

/**
   AVLTree_kv_wipe_out

   Remove all items in the AVLTree_kv_t instance.

   @param  avltree_kv AVLTree_kv_t instance
*/
#define AVLTree_kv_wipe_out( arg ) PRIMITIVE_CAT( arg, _avltree_kv_wipe_out )
void AVLTree_kv_wipe_out( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );

/**
   AVLTree_kv_wipe_out_and_dispose

   Remove all items in the AVLTree_kv_t instance. Dispose of all keys and values.

   @param  avltree_kv AVLTree_kv_t instance
*/
#define AVLTree_kv_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_kv_wipe_out_and_dispose )
void AVLTree_kv_wipe_out_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *avltree_kv );


#ifdef __cplusplus
}
#endif

/* End of file */




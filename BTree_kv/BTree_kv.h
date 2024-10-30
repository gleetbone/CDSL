/**
 @file BTree_kv.h
 @author Greg Lee
 @version 2.0.0
 @brief: "B Trees of keys with values"

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

 Function declarations for the opaque BTree_kv_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Key    - the type of the key
   Type   - the type of the value

   Macros that must be present (external to this file):

   KEY_EQUAL_FUNCTION            -  compares two key instances for equality
   VALUE _EQUAL_FUNCTION         -  compares two value instances for equality
   KEY_DEEP_EQUAL_FUNCTION       -  compares two key instances for deep equality
   VALUE _DEEP_EQUAL_FUNCTION    -  compares two value instances for deep equality
   KEY_ORDER_FUNCTION            -  returns 1 if first key argument is "before" second argument
   KEY_DISPOSE_FUNCTION          -  disposes a key instance
   VALUE_DISPOSE_FUNCTION        -  disposes a value instance
   KEY_DEEP_DISPOSE_FUNCTION     -  deep disposes a key instance
   VALUE_DEEP_DISPOSE_FUNCTION   -  deep disposes a value instance
   KEY_DUPLICATE_FUNCTION        -  makes copy of a key instance
   VALUE_DUPLICATE_FUNCTION      -  makes copy of a value instance
   KEY_DEFAULT_VALUE             -  key default value
   VALUE_DEFAULT_VALUE           -  value default value

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define BTree_kv_struct( arg ) PRIMITIVE_CAT( arg, _btree_kv_struct )
#define BTree_kv_type( arg ) PRIMITIVE_CAT( arg, _btree_kv_t )
#define BTree_kv_name( arg ) PRIMITIVE_CAT( arg, _btree )

#define BTree_kv_cursor_struct( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_struct )
#define BTree_kv_cursor_type( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_t )
#define BTree_kv_cursor_name( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor )

/**
   Structure declarations
*/

struct BTree_kv_struct( Prefix );
struct BTree_kv_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct BTree_kv_struct( Prefix ) BTree_kv_type( Prefix );
typedef struct BTree_kv_cursor_struct( Prefix ) BTree_kv_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   BTree_kv_make

   Return a new empty BTree_kv_t instance.

   @param max_n_keys maximum numberof keys in a tree node. Maximun number of
          children will be max_n_keys + 1, minimum number of keys will be
          ( max_n_keys + 1 )/2
   @return BTree_kv_t instance
*/
#define BTree_kv_make( arg ) PRIMITIVE_CAT( arg, _btree_kv_make )
BTree_kv_type( Prefix ) * BTree_kv_make( Prefix )( int32_t max_n_keys );

/**
   BTree_kv_make_from_array

   Return a new BTree_kv_t instance that has the content of the input arrays. The key
   and value items in the input arrays are not copied.

   @param key_array the array of keys to copy from
   @param value_array the array of values to copy from
   @param count the number of items to copy
   @param max_n_keys maximum numberof keys in a tree node. Maximun number of
          children will be max_n_keys + 1, minimum number of keys will be
          ( max_n_keys + 1 )/2
   @return BTree_kv_t instance
*/
#define BTree_kv_make_from_array( arg ) PRIMITIVE_CAT( arg, _btree_kv_make_from_array )
BTree_kv_type( Prefix ) * BTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count, int32_t max_n_keys );

/**
   BTree_kv_clone

   Return a new BTree_kv_t instance that has the same content as current. The key
   and value items in current are not deep duplicated.

   @param  other the BTree_kv_t instance to copy from
   @return BTree_kv_t instance
*/
#define BTree_kv_clone( arg ) PRIMITIVE_CAT( arg, _btree_kv_clone )
BTree_kv_type( Prefix ) * BTree_kv_clone( Prefix )( BTree_kv_type( Prefix ) *other );

/**
   BTree_kv_deep_clone

   Return a new BTree_kv_t instance that has the same content as current. The key
   and value items in current are deep duplicated.

   @param  other the BTree_kv_t instance to copy from
   @return BTree_kv_t instance
*/
#define BTree_kv_deep_clone( arg ) PRIMITIVE_CAT( arg, _btree_kv_deep_clone )
BTree_kv_type( Prefix ) * BTree_kv_deep_clone( Prefix )( BTree_kv_type( Prefix ) *other );

/**
   BTree_kv_copy

   Copies contents of a BTree_kv_t instance into another. The key
   and value items in current are not deep duplicated.

   @param  current the BTree_kv_t instance to copy into
   @param  other the BTree_kv_t instance to copy from
*/
#define BTree_kv_copy( arg ) PRIMITIVE_CAT( arg, _btree_kv_copy )
void BTree_kv_copy( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other );

/**
   BTree_kv_deep_copy

   Copies contents of a BTree_kv_t instance into another. The key
   and value items in current are deep duplicated.

   @param  current the BTree_kv_t instance to copy into
   @param  other the BTree_kv_t instance to copy from
*/
#define BTree_kv_deep_copy( arg ) PRIMITIVE_CAT( arg, _btree_kv_deep_copy )
void BTree_kv_deep_copy( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other );

/**
   BTree_kv_is_equal

   Determines equality of two BTree_kv_t instances.

   @param  current the BTree_kv_t instance to compare to
   @param  other the BTree_kv_t instance to compare
*/
#define BTree_kv_is_equal( arg ) PRIMITIVE_CAT( arg, _btree_kv_is_equal )
int32_t BTree_kv_is_equal( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other );

/**
   BTree_kv_is_deep_equal

   Determines deep equality of two BTree_kv_t instances.

   @param  current the BTree_kv_t instance to compare to
   @param  other the BTree_kv_t instance to compare
*/
#define BTree_kv_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _btree_kv_is_deep_equal )
int32_t BTree_kv_is_deep_equal( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other );

/**
   BTree_kv_cursor_make

   Return a new BTree_kv_t cursor instance.

   @param  the BTree_kv_t instance the new cursor works on
   @return BTree_kv_cursor_t instance
*/
#define BTree_kv_cursor_make( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_make )
BTree_kv_cursor_type( Prefix ) * BTree_kv_cursor_make( Prefix )( BTree_kv_type( Prefix ) *current );


/*
   Disposal
*/

/**
   BTree_kv_dispose

   Frees a BTree_kv_t instance without freeing its contained keys and values.

   @param current BTree_kv_t instance
*/
#define BTree_kv_dispose( arg ) PRIMITIVE_CAT( arg, _btree_kv_dispose )
void BTree_kv_dispose( Prefix )( BTree_kv_type( Prefix ) **current );

/**
   BTree_kv_deep_dispose

   Frees a BTree_kv_t instance and its contained keys and values.

   @param current BTree_kv_t instance
*/
#define BTree_kv_deep_dispose( arg ) PRIMITIVE_CAT( arg, _btree_kv_deep_dispose )
void BTree_kv_deep_dispose( Prefix )( BTree_kv_type( Prefix ) **current );

/**
   BTree_kv_cursor_dispose

   Frees a BTree_kv_cursor_t instance. Its current is not disposed.

   @param cursor BTree_kv_cursor_t instance
*/
#define BTree_kv_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_dispose )
void BTree_kv_cursor_dispose( Prefix )( BTree_kv_cursor_type( Prefix ) **cursor );


/**
   BTree_kv_keys_as_array

   Returns the keys as an array.

   @param  BTree_kv_t instance
   @return array of Key values
*/
#define BTree_kv_keys_as_array( arg ) PRIMITIVE_CAT( arg, _btree_kv_keys_as_array )
Key *BTree_kv_keys_as_array( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_values_as_array

   Returns the values as an array.

   @param  BTree_kv_t instance
   @return array of Type values
*/
#define BTree_kv_values_as_array( arg ) PRIMITIVE_CAT( arg, _btree_kv_values_as_array )
Type *BTree_kv_values_as_array( Prefix )( BTree_kv_type( Prefix ) *current );

/*
   Access
*/

/**
   BTree_kv_item

   Returns the value of the item associated with key in the BTree_kv_t instance.

   @param  current BTree_kv_t instance
   @param  key Key instance
   @return a Type value
*/
#define BTree_kv_item( arg ) PRIMITIVE_CAT( arg, _btree_kv_item )
Type BTree_kv_item( Prefix )( BTree_kv_type( Prefix ) *current, Key key );

/**
   BTree_kv_cursor_key_at

   Returns the value of the key that the BTree_kv_cursor_t instance is pointing to.

   @param  BTree_kv_cursor_t instance
   @return a Key value
*/
#define BTree_kv_cursor_key_at( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_key_at )
Key BTree_kv_cursor_key_at( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_cursor_item_at

   Returns the value of the item that the BTree_kv_cursor_t instance is pointing to.

   @param  BTree_kv_cursor_t instance
   @return a Type value
*/
#define BTree_kv_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_item_at )
Type BTree_kv_cursor_item_at( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_key_at

   Returns the value of the key that the BTree_kv_t instance's internal
   cursor is pointing to.

   @param  current BTree_kv_t instance
   @return a Key value
*/
#define BTree_kv_key_at( arg ) PRIMITIVE_CAT( arg, _btree_kv_key_at )
Key BTree_kv_key_at( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_item_at

   Returns the value of the item that the BTree_kv_t instance's internal
   cursor is pointing to.

   @param  current BTree_kv_t instance
   @return a Type value
*/
#define BTree_kv_item_at( arg ) PRIMITIVE_CAT( arg, _btree_kv_item_at )
Type BTree_kv_item_at( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_key_at_index

   Returns the value of the key pointed to by index. First index is 0.

   @param  current BTree_kv_t instance
   @param  index desired index
   @return a Key value
*/
#define BTree_kv_key_at_index( arg ) PRIMITIVE_CAT( arg, _btree_kv_key_at_index )
Type BTree_kv_key_at_index( Prefix )( BTree_kv_type( Prefix ) *current, int32_t index );

/**
   BTree_kv_item_at_index

   Returns the value of the item pointed to by index. First index is 0.

   @param  current BTree_kv_t instance
   @param  index desired index
   @return a Type value
*/
#define BTree_kv_item_at_index( arg ) PRIMITIVE_CAT( arg, _btree_kv_item_at_index )
Type BTree_kv_item_at_index( Prefix )( BTree_kv_type( Prefix ) *current, int32_t index );


/*
   Measurement
*/

/**
   BTree_kv_count

   Returns the number of items in the BTree_kv_t instance.

   @param  current BTree_kv_t instance
   @return number of items in BTree_kv instance
*/
#define BTree_kv_count( arg ) PRIMITIVE_CAT( arg, _btree_kv_count )
int32_t BTree_kv_count( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_height

   Returns the height of the BTree_kv_t instance.

   @param  current BTree_kv_t instance
   @return (max) height of the BTree_kv instance
*/
#define BTree_kv_height( arg ) PRIMITIVE_CAT( arg, _btree_kv_height )
int32_t BTree_kv_height( Prefix )( BTree_kv_type( Prefix ) *current );


/*
   Status report
*/

/**
   BTree_kv_off

   Returns 1 if the BTree_kv_t instance's internal cursor is off, otherwise 0.

   @param  current BTree_kv_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define BTree_kv_off( arg ) PRIMITIVE_CAT( arg, _btree_kv_off )
int32_t BTree_kv_off( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_cursor_off

   Returns 1 if the BTree_kv_cursor_t instance is off, otherwise 0.

   @param  cursor BTree_kv_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define BTree_kv_cursor_off( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_off )
int32_t BTree_kv_cursor_off( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_is_empty

   Returns 1 if the BTree_kv_t instance contains no items, otherwise 0.

   @param  current BTree_kv_t instance
   @return 1 if empty, otherwise 0
*/
#define BTree_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _btree_kv_is_empty )
int32_t BTree_kv_is_empty( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_has

   Returns 1 if the BTree_kv_t instance contains the key, otherwise 0.

   @param  current BTree_kv_t instance
   @param  key the key to search for
   @return 1 if current has key, otherwise 0
*/
#define BTree_kv_has( arg ) PRIMITIVE_CAT( arg, _btree_kv_has )
int32_t BTree_kv_has( Prefix )( BTree_kv_type( Prefix ) *current, Key key );


/*
   Cursor movement
*/

/**
   BTree_kv_cursor_back

   Moves the BTree_kv_cursor_t instance to the previous item or off.

   @param  current_kv_cursor BTree_kv_cursor_t instance
*/
#define BTree_kv_cursor_back( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_back )
void BTree_kv_cursor_back( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_cursor_forth

   Moves the BTree_kv_cursor_t instance to the next item or off.

   @param  current_kv_cursor BTree_kv_cursor_t instance
*/
#define BTree_kv_cursor_forth( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_forth )
void BTree_kv_cursor_forth( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_cursor_go

   Moves the BTree_kv_t instance's internal cursor to the ith item in the current.

   @param  current_kv_cursor BTree_kv_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define BTree_kv_cursor_go( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_go )
void BTree_kv_cursor_go( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor, int32_t index );

/**
   BTree_kv_cursor_finish

   Moves the BTree_kv_cursor_t instance to the last item or off if the current is empty.

   @param  current_kv_cursor BTree_kv_cursor_t instance
*/
#define BTree_kv_cursor_finish( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_finish )
void BTree_kv_cursor_finish( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_cursor_start

   Moves the BTree_kv_cursor_t instance to the first item or off if the current is empty.

   @param  current_kv_cursor BTree_kv_cursor_t instance
*/
#define BTree_kv_cursor_start( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_start )
void BTree_kv_cursor_start( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list BTree_kv_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define BTree_kv_cursor_index( arg ) PRIMITIVE_CAT( arg, _btree_kv_cursor_index )
int32_t BTree_kv_cursor_index( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor );

/**
   BTree_kv_back

   Moves the BTree_kv_t instance internal cursor to the previous item or off.

   @param  current BTree_kv_t instance
*/
#define BTree_kv_back( arg ) PRIMITIVE_CAT( arg, _btree_kv_back )
void BTree_kv_back( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_forth

   Moves the BTree_kv_t instance internal cursor to the next item or off.

   @param  current BTree_kv_t instance
*/
#define BTree_kv_forth( arg ) PRIMITIVE_CAT( arg, _btree_kv_forth )
void BTree_kv_forth( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_go

   Moves the BTree_kv_t instance's internal cursor to the ith item in the current.

   @param  current BTree_kv_t instance
   @param  index the index where the  will be moved to
*/
#define BTree_kv_go( arg ) PRIMITIVE_CAT( arg, _btree_kv_go )
void BTree_kv_go( Prefix )( BTree_kv_type( Prefix ) *current, int32_t index );

/**
   BTree_kv_finish

   Moves the BTree_kv_t instance's internal cursor to the last item or off if the current is empty.

   @param  current BTree_kv_t instance
*/
#define BTree_kv_finish( arg ) PRIMITIVE_CAT( arg, _btree_kv_finish )
void BTree_kv_finish( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_start

   Moves the BTree_kv_t instance's internal cursor to the first item or off if the current is empty.

   @param  current BTree_kv_t instance
*/
#define BTree_kv_start( arg ) PRIMITIVE_CAT( arg, _btree_kv_start )
void BTree_kv_start( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  list BTree_kv_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define BTree_kv_index( arg ) PRIMITIVE_CAT( arg, _btree_kv_index )
int32_t BTree_kv_index( Prefix )( BTree_kv_type( Prefix ) *list );


/*
   Element change
*/

/**
   BTree_kv_put

   Put the key-value pair into the BTree_kv_t instance. Replace any existing item
   that has the same key.

   @param  current BTree_kv_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define BTree_kv_put( arg ) PRIMITIVE_CAT( arg, _btree_kv_put )
void BTree_kv_put( Prefix )( BTree_kv_type( Prefix ) *current, Type value, Key key );

/**
   BTree_kv_put_and_dispose

   Put the key-value pair into the BTree_kv_t instance. Replace any existing item
   that has the same key, disposing of the old value and key.

   @param  current BTree_kv_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define BTree_kv_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _btree_kv_put_and_dispose )
void BTree_kv_put_and_dispose( Prefix )( BTree_kv_type( Prefix ) *current, Type value, Key key );


/*
   Removal
*/

/**
   BTree_kv_remove

   Remove the item in the BTree_kv_t instance that has the key.

   @param  current BTree_kv_t instance
   @param  key the key for the value
*/
#define BTree_kv_remove( arg ) PRIMITIVE_CAT( arg, _btree_kv_remove )
void BTree_kv_remove( Prefix )( BTree_kv_type( Prefix ) *current, Key key );

/**
   BTree_kv_remove_and_dispose

   Remove the item in the BTree_kv_t instance that has the key and dispose
   of the key and the value.

   @param  current BTree_kv_t instance
   @param  key the key for the value
*/
#define BTree_kv_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _btree_kv_remove_and_dispose )
void BTree_kv_remove_and_dispose( Prefix )( BTree_kv_type( Prefix ) *current, Key key );

/**
   BTree_kv_wipe_out

   Remove all items in the BTree_kv_t instance.

   @param  current BTree_kv_t instance
*/
#define BTree_kv_wipe_out( arg ) PRIMITIVE_CAT( arg, _btree_kv_wipe_out )
void BTree_kv_wipe_out( Prefix )( BTree_kv_type( Prefix ) *current );

/**
   BTree_kv_wipe_out_and_dispose

   Remove all items in the BTree_kv_t instance. Dispose of all keys and values.

   @param  current BTree_kv_t instance
*/
#define BTree_kv_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _btree_kv_wipe_out_and_dispose )
void BTree_kv_wipe_out_and_dispose( Prefix )( BTree_kv_type( Prefix ) *current );

#ifdef __cplusplus
}
#endif

/* End of file */




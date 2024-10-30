/**
 @file Heap_kv.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Heaps of keys with values"

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

 Function declarations for the opaque Heap_kv_t type.

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

   KEY_EQUALITY_FUNCTION      -  compares two key instances for equality
   KEY_ORDER_FUNCTION         -  returns 1 if first key argument is "before" second argument
   KEY_DISPOSE_FUNCTION       -  frees a key instance
   VALUE_DISPOSE_FUNCTION     -  frees a value instance
   KEY_DUPLICATE_FUNCTION     -  makes copy of a key instance
   VALUE_DUPLICATE_FUNCTION   -  makes copy of a value instance
   KEY_DEFAULT_VALUE          -  key default value
   VALUE_DEFAULT_VALUE        -  value default value

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Heap_kv_struct( arg ) PRIMITIVE_CAT( arg, _heap_kv_struct )
#define Heap_kv_type( arg ) PRIMITIVE_CAT( arg, _heap_kv_t )
#define Heap_kv_name( arg ) PRIMITIVE_CAT( arg, _heap )

#define Heap_kv_cursor_struct( arg ) PRIMITIVE_CAT( arg, _heap_kv_cursor_struct )
#define Heap_kv_cursor_type( arg ) PRIMITIVE_CAT( arg, _heap_kv_cursor_t )
#define Heap_kv_cursor_name( arg ) PRIMITIVE_CAT( arg, _heap_kv_cursor )

/**
   Structure declarations
*/

struct Heap_kv_struct( Prefix );
struct Heap_kv_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Heap_kv_struct( Prefix ) Heap_kv_type( Prefix );
typedef struct Heap_kv_cursor_struct( Prefix ) Heap_kv_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   Heap_kv_make

   Return a new empty Heap_kv_t instance with default capacity.

   @return Heap_kv_t instance
*/
#define Heap_kv_make( arg ) PRIMITIVE_CAT( arg, _heap_kv_make )
Heap_kv_type( Prefix ) * Heap_kv_make( Prefix )( void );

/**
   Heap_kv_make_n

   Return a new empty Heap_kv_t instance with specified capacity.

   @return Heap_kv_t instance
*/
#define Heap_kv_make_n( arg ) PRIMITIVE_CAT( arg, _heap_kv_make_n )
Heap_kv_type( Prefix ) * Heap_kv_make_n( Prefix )( int32_t capacity );

/**
   Heap_kv_make_from_array

   Return a new Heap_kv_t instance that has the content of the input arrays. The key
   and value items in the input arrays are not copied.

   @param key_array the array of keys to copy from
   @param value_array the array of values to copy from
   @param count the number of items to copy
   @return Heap_kv_t instance
*/
#define Heap_kv_make_from_array( arg ) PRIMITIVE_CAT( arg, _heap_kv_make_from_array )
Heap_kv_type( Prefix ) * Heap_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count );


/*
   Basic
*/

/**
   Heap_kv_clone

   Return a new Heap_kv_t instance that has the same content as heap. The key
   and value items in heap are not copied.

   @param  heap the Heap_kv_t instance to clone
   @return Heap_kv_t instance
*/
#define Heap_kv_clone( arg ) PRIMITIVE_CAT( arg, _heap_kv_clone )
Heap_kv_type( Prefix ) * Heap_kv_clone( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_deep_clone

   Return a new Heap_kv_t instance with duplicate items from heap

   @return Heap_kv_t instance
*/

#define Heap_kv_deep_clone( arg ) PRIMITIVE_CAT( arg, _heap_kv_deep_clone )
Heap_kv_type( Prefix ) *
Heap_kv_deep_clone( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_copy

   Copies contents of a Heap_kv_t instance into another. The key and value
   items in heap are not copied, references to them are copied.

   @param  current the Heap_kv_t instance to copy into
   @return other the Heap_kv_t instance to copy from
*/
#define Heap_kv_copy( arg ) PRIMITIVE_CAT( arg, _heap_kv_copy )
void Heap_kv_copy( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other );

/**
   Heap_kv_deep_copy

   Copies contents of a Heap_kv_t instance into another. The key and value
   items in heap are copied.

   @param  current the Heap_kv_t instance to copy into
   @return other the Heap_kv_t instance to copy from
*/
#define Heap_kv_deep_copy( arg ) PRIMITIVE_CAT( arg, _heap_kv_deep_copy )
void Heap_kv_deep_copy( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other );

/**
   Heap_kv_is_equal

   Returns 1 if contents of a Heap_kv_t instance are the same as other. The key and value items in heap are compared with "=="

   @param  current the Heap_kv_t instance to compare to
   @return other the Heap_kv_t instance to compare
*/
#define Heap_kv_is_equal( arg ) PRIMITIVE_CAT( arg, _heap_kv_is_equal )
int32_t Heap_kv_is_equal( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other );

/**
   Heap_kv_is_deep_equal

   Returns 1 if contents of a Heap_kv_t instance are the same as other. The key and value items in heap are compared with KEY_EQUALITY_FUNCTION and VALUE_EQUALITY_FUNCTION.

   @param  current the Heap_kv_t instance to compare to
   @return other the Heap_kv_t instance to compare
*/
#define Heap_kv_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _heap_kv_is_deep_equal )
int32_t Heap_kv_is_deep_equal( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other );

/*
   Disposal
*/

/**
   Heap_kv_dispose

   Frees a Heap_kv_t instance without freeing its contained keys and values.

   @param Heap_kv_t instance
*/
#define Heap_kv_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_dispose )
void Heap_kv_dispose( Prefix )( Heap_kv_type( Prefix ) **heap );

/**
   Heap_kv_deep_dispose

   Frees a Heap_kv_t instance and its contained keys and values.

   @param Heap_kv_t instance
*/
#define Heap_kv_deep_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_deep_dispose )
void Heap_kv_deep_dispose( Prefix )( Heap_kv_type( Prefix ) **heap );


/**
   Heap_kv_keys_as_array

   Returns the keys as an array.

   @param  Heap_kv_t instance
   @return array of Key values
*/
#define Heap_kv_keys_as_array( arg ) PRIMITIVE_CAT( arg, _heap_kv_keys_as_array )
Key *Heap_kv_keys_as_array( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_values_as_array

   Returns the values as an array.

   @param  Heap_kv_t instance
   @return array of Type values
*/
#define Heap_kv_values_as_array( arg ) PRIMITIVE_CAT( arg, _heap_kv_values_as_array )
Type *Heap_kv_values_as_array( Prefix )( Heap_kv_type( Prefix ) *heap );

/*
   Access
*/

/**
   Heap_kv_key

   Returns the value of the key at the top of Heap_kv_t instance.

   @param  heap Heap_kv_t instance
   @return a Key value
*/
#define Heap_kv_key( arg ) PRIMITIVE_CAT( arg, _heap_kv_key )
Key Heap_kv_key( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_item

   Returns the value of the top item in the Heap_kv_t instance.

   @param  heap Heap_kv_t instance
   @return a Type value
*/
#define Heap_kv_item( arg ) PRIMITIVE_CAT( arg, _heap_kv_item )
Type Heap_kv_item( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_item_for_key

   Returns the value of the item for the key in the Heap_kv_t instance.

   @param  heap Heap_kv_t instance
   @param  key the key to look for
   @return a Type value
*/
#define Heap_kv_item_for_key( arg ) PRIMITIVE_CAT( arg, _heap_kv_item_for_key )
Type Heap_kv_item_for_key( Prefix )( Heap_kv_type( Prefix ) *heap, Key key );


/*
   Measurement
*/

/**
   Heap_kv_count

   Returns the number of items in the Heap_kv_t instance.

   @param  heap Heap_kv_t instance
   @return number of items in Heap_kv instance
*/
#define Heap_kv_count( arg ) PRIMITIVE_CAT( arg, _heap_kv_count )
int32_t Heap_kv_count( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_capacity

   Returns the largest number of items the Heap_kv_t instance can hold.

   @param  heap Heap_kv_t instance
   @return max number of items in Heap_kv instance
*/
#define Heap_kv_capacity( arg ) PRIMITIVE_CAT( arg, _heap_kv_capacity )
int32_t Heap_kv_capacity( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_height

   Returns the height of the Heap_kv_t instance.

   @param  heap Heap_kv_t instance
   @return (max) height of the Heap_kv instance
*/
#define Heap_kv_height( arg ) PRIMITIVE_CAT( arg, _heap_kv_height )
int32_t Heap_kv_height( Prefix )( Heap_kv_type( Prefix ) *heap );

/*
   Resize
*/

/**
   Heap_kv_set_capacity

   Sets the largest number of items the Heap_kv_t instance can hold.

   @param  heap Heap_kv_t instance
   @param max number of items in Heap_kv instance
*/
#define Heap_kv_set_capacity( arg ) PRIMITIVE_CAT( arg, _heap_kv_set_capacity )
void Heap_kv_set_capacity( Prefix )( Heap_kv_type( Prefix ) *heap, int32_t capacity );


/*
   Status report
*/

/**
   Heap_kv_is_empty

   Returns 1 if the Heap_kv_t instance contains no items, otherwise 0.

   @param  heap Heap_kv_t instance
   @return 1 if empty, otherwise 0
*/
#define Heap_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _heap_kv_is_empty )
int32_t Heap_kv_is_empty( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_has

   Returns 1 if the Heap_kv_t instance contains the key, otherwise 0.

   @param  heap Heap_kv_t instance
   @param  key the key to search for
   @return 1 if heap has key, otherwise 0
*/
#define Heap_kv_has( arg ) PRIMITIVE_CAT( arg, _heap_kv_has )
int32_t Heap_kv_has( Prefix )( Heap_kv_type( Prefix ) *heap, Key key );


/*
   Element change
*/

/**
   Heap_kv_put

   Put the key-value pair into the Heap_kv_t instance. Replace any existing item
   that has the same key.

   @param  heap Heap_kv_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define Heap_kv_put( arg ) PRIMITIVE_CAT( arg, _heap_kv_put )
void Heap_kv_put( Prefix )( Heap_kv_type( Prefix ) *heap, Type value, Key key );

/**
   Heap_kv_put_and_dispose

   Put the key-value pair into the Heap_kv_t instance. Replace any existing item
   that has the same key, disposing of the old value and key.

   @param  heap Heap_kv_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define Heap_kv_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_put_and_dispose )
void Heap_kv_put_and_dispose( Prefix )( Heap_kv_type( Prefix ) *heap, Type value, Key key );

/**
   Heap_kv_append

   Append the Heap_kv_t instance "other" into the Heap_kv_t instance. Replace any existing items
   in heap that have the same key in other.

   @param  heap Heap_kv_t instance
   @param  other Heap_kv_t instance to insert into heap
*/
#define Heap_kv_append( arg ) PRIMITIVE_CAT( arg, _heap_kv_append )
void Heap_kv_append( Prefix )( Heap_kv_type( Prefix ) *heap, Heap_kv_type( Prefix ) *other );

/**
   Heap_kv_append_and_dispose

   Append the Heap_kv_t instance "other" into the Heap_kv_t instance. Replace and dispose
   any existing items in heap that have the same key in other.

   @param  heap Heap_kv_t instance
   @param  other Heap_kv_t instance to insert into heap
*/
#define Heap_kv_append_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_append_and_dispose )
void Heap_kv_append_and_dispose( Prefix )( Heap_kv_type( Prefix ) *heap, Heap_kv_type( Prefix ) *other );


/*
   Removal
*/

/**
   Heap_kv_remove

   Remove the item in the Heap_kv_t instance that has the key.

   @param  heap Heap_kv_t instance
   @param  key the key for the value
*/
#define Heap_kv_remove( arg ) PRIMITIVE_CAT( arg, _heap_kv_remove )
void Heap_kv_remove( Prefix )( Heap_kv_type( Prefix ) *heap, Key key );

/**
   Heap_kv_remove_and_dispose

   Remove the item in the Heap_kv_t instance that has the key and dispose
   of the key and the value.

   @param  heap Heap_kv_t instance
   @param  key the key for the value
*/
#define Heap_kv_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_remove_and_dispose )
void Heap_kv_remove_and_dispose( Prefix )( Heap_kv_type( Prefix ) *heap, Key key );

/**
   Heap_kv_prune

   Remove items at the bottom of the Heap_kv_t instance.

   @param  heap Heap_kv_t instance
   @param  count the number of items to remove
*/
#define Heap_kv_prune( arg ) PRIMITIVE_CAT( arg, _heap_kv_prune )
void Heap_kv_prune( Prefix )( Heap_kv_type( Prefix ) *heap, int32_t count );

/**
   Heap_kv_prune_and_dispose

   Remove items at the bottom of the Heap_kv_t instance and dispose
   of the keys and the values.

   @param  heap Heap_kv_t instance
   @param  count the number of items to remove
*/
#define Heap_kv_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_prune_and_dispose )
void Heap_kv_prune_and_dispose( Prefix )( Heap_kv_type( Prefix ) *heap, int32_t count );

/**
   Heap_kv_keep

   Remove items at the bottom of the Heap_kv_t instance, keeping count at top.

   @param  heap Heap_kv_t instance
   @param  count the number of items to keep at the top of the heap
*/
#define Heap_kv_keep( arg ) PRIMITIVE_CAT( arg, _heap_kv_keep )
void Heap_kv_keep( Prefix )( Heap_kv_type( Prefix ) *heap, int32_t count );

/**
   Heap_kv_keep_and_dispose

   Remove items at the bottom of the Heap_kv_t instance, keeping count at top,
   and dispose of the keys and the values.

   @param  heap Heap_kv_t instance
   @param  count the number of items to keep at the top of the heap
*/
#define Heap_kv_keep_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_keep_and_dispose )
void Heap_kv_keep_and_dispose( Prefix )( Heap_kv_type( Prefix ) *heap, int32_t count );

/**
   Heap_kv_wipe_out

   Remove all items in the Heap_kv_t instance.

   @param  heap Heap_kv_t instance
*/
#define Heap_kv_wipe_out( arg ) PRIMITIVE_CAT( arg, _heap_kv_wipe_out )
void Heap_kv_wipe_out( Prefix )( Heap_kv_type( Prefix ) *heap );

/**
   Heap_kv_wipe_out_and_dispose

   Remove all items in the Heap_kv_t instance. Dispose of all keys and values.

   @param  heap Heap_kv_t instance
*/
#define Heap_kv_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_kv_wipe_out_and_dispose )
void Heap_kv_wipe_out_and_dispose( Prefix )( Heap_kv_type( Prefix ) *heap );

#ifdef __cplusplus
}
#endif

/* End of file */




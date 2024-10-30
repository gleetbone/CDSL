/**
 @file Heap.h
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

 Function declarations for the opaque Heap_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Type   - the type of the value

   Macros that must be present (external to this file):

   EQUALITY_FUNCTION      -  compares two instances for equality
   ORDER_FUNCTION         -  returns 1 if first argument is "before" second argument
   DISPOSE_FUNCTION       -  frees an instance
   DUPLICATE_FUNCTION     -  makes copy of an instance
   DEFAULT_VALUE          -  default value

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Heap_struct( arg ) PRIMITIVE_CAT( arg, _heap_struct )
#define Heap_type( arg ) PRIMITIVE_CAT( arg, _heap_t )
#define Heap_name( arg ) PRIMITIVE_CAT( arg, _heap )

#define Heap_cursor_struct( arg ) PRIMITIVE_CAT( arg, _heap_cursor_struct )
#define Heap_cursor_type( arg ) PRIMITIVE_CAT( arg, _heap_cursor_t )
#define Heap_cursor_name( arg ) PRIMITIVE_CAT( arg, _heap_cursor )

/**
   Structure declarations
*/

struct Heap_struct( Prefix );
struct Heap_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Heap_struct( Prefix ) Heap_type( Prefix );
typedef struct Heap_cursor_struct( Prefix ) Heap_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   Heap_make

   Return a new empty Heap_t instance with default capacity.

   @return Heap_t instance
*/
#define Heap_make( arg ) PRIMITIVE_CAT( arg, _heap_make )
Heap_type( Prefix ) * Heap_make( Prefix )( void );

/**
   Heap_make_n

   Return a new empty Heap_t instance with specified capacity.

   @return Heap_t instance
*/
#define Heap_make_n( arg ) PRIMITIVE_CAT( arg, _heap_make_n )
Heap_type( Prefix ) * Heap_make_n( Prefix )( int32_t capacity );

/**
   Heap_make_from_array

   Return a new Heap_t instance that has the content of the input arrays. The key
   and value items in the input arrays are not copied.

   @param key_array the array of keys to copy from
   @param value_array the array of values to copy from
   @param count the number of items to copy
   @return Heap_t instance
*/
#define Heap_make_from_array( arg ) PRIMITIVE_CAT( arg, _heap_make_from_array )
Heap_type( Prefix ) * Heap_make_from_array( Prefix )( Type *value_array, int32_t count );

/*
   Basic
*/

/**
   Heap_clone

   Return a new Heap_t instance that has the same content as heap. The key
   and value items in heap are not copied.

   @param  current the Heap_t instance to copy from
   @return Heap_t instance
*/
#define Heap_clone( arg ) PRIMITIVE_CAT( arg, _heap_clone )
Heap_type( Prefix ) * Heap_clone( Prefix )( Heap_type( Prefix ) *current );

/**
   Heap_deep_clone

   Return a new Heap_t instance with duplicate items from heap

   @return Heap_t instance
*/

#define Heap_deep_clone( arg ) PRIMITIVE_CAT( arg, _heap_deep_clone )
Heap_type( Prefix ) *
Heap_deep_clone( Prefix )( Heap_type( Prefix ) *current );

/**
   Heap_copy

   Copy contents of other Heap_t instance into current.

   @param  current the Heap_t instance to copy into
   @param  other the Heap_t instance to copy from
*/
#define Heap_copy( arg ) PRIMITIVE_CAT( arg, _heap_copy )
void Heap_copy( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other );

/**
   Heap_deep_copy

   Copy contents of other Heap_t instance into current.

   @param  current the Heap_t instance to copy into
   @param  other the Heap_t instance to copy from
*/
#define Heap_deep_copy( arg ) PRIMITIVE_CAT( arg, _heap_deep_copy )
void Heap_deep_copy( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other );

/**
   Heap_is_equal

   Compares contents of other Heap_t instance with current.

   @param  current the Heap_t instance to copy into
   @param  other the Heap_t instance to copy from
*/
#define Heap_is_equal( arg ) PRIMITIVE_CAT( arg, _heap_is_equal )
int32_t Heap_is_equal( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other );

/**
   Heap_is_deep_equal

   Compares contents of other Heap_t instance with current.

   @param  current the Heap_t instance to copy into
   @param  other the Heap_t instance to copy from
*/
#define Heap_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _heap_is_deep_equal )
int32_t Heap_is_deep_equal( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other );

/*
   Disposal
*/

/**
   Heap_dispose

   Frees a Heap_t instance without freeing its contained keys and values.

   @param Heap_t instance
*/
#define Heap_dispose( arg ) PRIMITIVE_CAT( arg, _heap_dispose )
void Heap_dispose( Prefix )( Heap_type( Prefix ) **current );

/**
   Heap_deep_dispose

   Frees a Heap_t instance and its contained keys and values.

   @param Heap_t instance
*/
#define Heap_deep_dispose( arg ) PRIMITIVE_CAT( arg, _heap_deep_dispose )
void Heap_deep_dispose( Prefix )( Heap_type( Prefix ) **current );


/**
   Heap_as_array

   Returns the values as an array.

   @param  Heap_t instance
   @return array of Type values
*/
#define Heap_as_array( arg ) PRIMITIVE_CAT( arg, _heap_as_array )
Type *Heap_as_array( Prefix )( Heap_type( Prefix ) *current );

/*
   Access
*/

/**
   Heap_item

   Returns the value of the top item in the Heap_t instance.

   @param  current Heap_t instance
   @return a Type value
*/
#define Heap_item( arg ) PRIMITIVE_CAT( arg, _heap_item )
Type Heap_item( Prefix )( Heap_type( Prefix ) *current );


/*
   Measurement
*/

/**
   Heap_count

   Returns the number of items in the Heap_t instance.

   @param  current Heap_t instance
   @return number of items in Heap instance
*/
#define Heap_count( arg ) PRIMITIVE_CAT( arg, _heap_count )
int32_t Heap_count( Prefix )( Heap_type( Prefix ) *current );

/**
   Heap_capacity

   Returns the largest number of items the Heap_t instance can hold.

   @param  current Heap_t instance
   @return max number of items in Heap instance
*/
#define Heap_capacity( arg ) PRIMITIVE_CAT( arg, _heap_capacity )
int32_t Heap_capacity( Prefix )( Heap_type( Prefix ) *current );

/**
   Heap_height

   Returns the height of the Heap_t instance.

   @param  current Heap_t instance
   @return (max) height of the Heap instance
*/
#define Heap_height( arg ) PRIMITIVE_CAT( arg, _heap_height )
int32_t Heap_height( Prefix )( Heap_type( Prefix ) *current );

/*
   Resize
*/

/**
   Heap_set_capacity

   Sets the largest number of items the Heap_t instance can hold.

   @param  current Heap_t instance
   @param max number of items in Heap instance
*/
#define Heap_set_capacity( arg ) PRIMITIVE_CAT( arg, _heap_set_capacity )
void Heap_set_capacity( Prefix )( Heap_type( Prefix ) *heap, int32_t capacity );


/*
   Status report
*/

/**
   Heap_is_empty

   Returns 1 if the Heap_t instance contains no items, otherwise 0.

   @param  current Heap_t instance
   @return 1 if empty, otherwise 0
*/
#define Heap_is_empty( arg ) PRIMITIVE_CAT( arg, _heap_is_empty )
int32_t Heap_is_empty( Prefix )( Heap_type( Prefix ) *current );

/**
   Heap_has

   Returns 1 if the Heap_t instance contains the key, otherwise 0.

   @param  current Heap_t instance
   @param  value the value to search for
   @return 1 if heap has value, otherwise 0
*/
#define Heap_has( arg ) PRIMITIVE_CAT( arg, _heap_has )
int32_t Heap_has( Prefix )( Heap_type( Prefix ) *heap, Type value );


/*
   Element change
*/

/**
   Heap_put

   Put the value into the Heap_t instance. Replace any existing item
   that has the same value.

   @param  current Heap_t instance
   @param  value the value to insert
*/
#define Heap_put( arg ) PRIMITIVE_CAT( arg, _heap_put )
void Heap_put( Prefix )( Heap_type( Prefix ) *heap, Type value );

/**
   Heap_put_and_dispose

   Put the value into the Heap_t instance. Replace any existing item
   that has the same value, disposing of the old value.

   @param  current Heap_t instance
   @param  value the value to insert
*/
#define Heap_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_put_and_dispose )
void Heap_put_and_dispose( Prefix )( Heap_type( Prefix ) *heap, Type value );

/**
   Heap_append

   Append the Heap_t instance "other" into the Heap_t instance. Replace any existing items
   in heap that have the same key in other.

   @param  current Heap_t instance
   @param  other Heap_t instance to insert into heap
*/
#define Heap_append( arg ) PRIMITIVE_CAT( arg, _heap_append )
void Heap_append( Prefix )( Heap_type( Prefix ) *heap, Heap_type( Prefix ) *other );

/**
   Heap_append_and_dispose

   Append the Heap_t instance "other" into the Heap_t instance. Replace and dispose
   any existing items in heap that have the same key in other.

   @param  current Heap_t instance
   @param  other Heap_t instance to insert into heap
*/
#define Heap_append_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_append_and_dispose )
void Heap_append_and_dispose( Prefix )( Heap_type( Prefix ) *heap, Heap_type( Prefix ) *other );


/*
   Removal
*/

/**
   Heap_remove

   Remove the item in the Heap_t instance that has the value.

   @param  current Heap_t instance
   @param  value the value
*/
#define Heap_remove( arg ) PRIMITIVE_CAT( arg, _heap_remove )
void Heap_remove( Prefix )( Heap_type( Prefix ) *heap, Type value );

/**
   Heap_remove_and_dispose

   Remove the item in the Heap_t instance that has the value and dispose
   of the value.

   @param  current Heap_t instance
   @param  value the value
*/
#define Heap_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_remove_and_dispose )
void Heap_remove_and_dispose( Prefix )( Heap_type( Prefix ) *heap, Type value );

/**
   Heap_prune

   Remove items at the bottom of the Heap_t instance.

   @param  current Heap_t instance
   @param  count the number of items to remove
*/
#define Heap_prune( arg ) PRIMITIVE_CAT( arg, _heap_prune )
void Heap_prune( Prefix )( Heap_type( Prefix ) *heap, int32_t count );

/**
   Heap_prune_and_dispose

   Remove items at the bottom of the Heap_t instance and dispose
   of the keys and the values.

   @param  current Heap_t instance
   @param  count the number of items to remove
*/
#define Heap_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_prune_and_dispose )
void Heap_prune_and_dispose( Prefix )( Heap_type( Prefix ) *heap, int32_t count );

/**
   Heap_keep

   Remove items at the bottom of the Heap_t instance, keeping count at top.

   @param  current Heap_t instance
   @param  count the number of items to keep at the top of the heap
*/
#define Heap_keep( arg ) PRIMITIVE_CAT( arg, _heap_keep )
void Heap_keep( Prefix )( Heap_type( Prefix ) *heap, int32_t count );

/**
   Heap_keep_and_dispose

   Remove items at the bottom of the Heap_t instance, keeping count at top,
   and dispose of the keys and the values.

   @param  current Heap_t instance
   @param  count the number of items to keep at the top of the heap
*/
#define Heap_keep_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_keep_and_dispose )
void Heap_keep_and_dispose( Prefix )( Heap_type( Prefix ) *heap, int32_t count );

/**
   Heap_wipe_out

   Remove all items in the Heap_t instance.

   @param  current Heap_t instance
*/
#define Heap_wipe_out( arg ) PRIMITIVE_CAT( arg, _heap_wipe_out )
void Heap_wipe_out( Prefix )( Heap_type( Prefix ) *current );

/**
   Heap_wipe_out_and_dispose

   Remove all items in the Heap_t instance. Dispose of all keys and values.

   @param  current Heap_t instance
*/
#define Heap_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _heap_wipe_out_and_dispose )
void Heap_wipe_out_and_dispose( Prefix )( Heap_type( Prefix ) *current );

#ifdef __cplusplus
}
#endif

/* End of file */




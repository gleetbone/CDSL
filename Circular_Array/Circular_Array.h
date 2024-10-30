/**
 @file Circular_Array.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Circular_Arrays (arrays that re-use allocated space when updated)"

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

 Function declarations for the opaque Circular_Array_t type.

*/

/**
   Version
*/

#define CIRCULAR_ARRAY_VERSION_MAJOR 2
#define CIRCULAR_ARRAY_VERSION_MINOR 0
#define CIRCULAR_ARRAY_VERSION_PATCH 0

#define CIRCULAR_ARRAY_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define CIRCULAR_ARRAY_VERSION \
   CIRCULAR_ARRAY_MAKE_VERSION( CIRCULAR_ARRAY_VERSION_MAJOR, \
                       CIRCULAR_ARRAY_VERSION_MINOR, \
                       CIRCULAR_ARRAY_VERSION_PATCH )

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

   DISPOSE_FUNCTION  -  frees a Type instance

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Circular_Array_struct( arg ) PRIMITIVE_CAT( arg, _circular_array_struct )
#define Circular_Array_type( arg ) PRIMITIVE_CAT( arg, _circular_array_t )
#define Circular_Array_name( arg ) PRIMITIVE_CAT( arg, _circular_array )

/**
   Structure declarations
*/

struct Circular_Array_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Circular_Array_struct( Prefix ) Circular_Array_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   Circular_Array_make

   Return a new empty Circular_Array_t instance with capacity of n.

   @param  n the capacity
   @return Circular_Array_t instance
*/
#define Circular_Array_make( arg ) PRIMITIVE_CAT( arg, _circular_array_make )
Circular_Array_type( Prefix ) * 
Circular_Array_make( Prefix )( int32_t n );

/**
   Circular_Array_make_from_array

   Return a new Circular_Array_t instance populated with contents of an array

   @param  array the carray
   @param  count the number of items in the array
   @param  capacity the number of positions in the array
   @return Circular_Array_t instance
*/
#define Circular_Array_make_from_array( arg ) PRIMITIVE_CAT( arg, _circular_array_make_from_array )
Circular_Array_type( Prefix ) * 
Circular_Array_make_from_array( Prefix )( Type *array, int32_t count, int32_t capacity );

/**
   Circular_Array_clone

   Return a shallow clone of the circular_array.

   @param  current Circular_Array_t instance
   @return clone of the circular_array
*/
#define Circular_Array_clone( arg ) PRIMITIVE_CAT( arg, _circular_array_clone )
Circular_Array_type( Prefix ) * Circular_Array_clone( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_deep_clone

   Return a deep clone of the circular_array.

   @param  current Circular_Array_t instance
   @return clone of the circular_array
*/
#define Circular_Array_deep_clone( arg ) PRIMITIVE_CAT( arg, _circular_array_deep_clone )
Circular_Array_type( Prefix ) * Circular_Array_deep_clone( Prefix )( Circular_Array_type( Prefix ) *current );

/*
   Basic
*/

/**
   Circular_Array_is_equal

   Is current (shallow) equal to  other.

   @param  current Circular_Array_t instance
   @param  other Circular_Array_t instance
   @return 1 if true, 0 otherwise
*/
#define Circular_Array_is_equal( arg ) PRIMITIVE_CAT( arg, _circular_array_is_equal )
int32_t Circular_Array_is_equal( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other );

/**
   Circular_Array_is_deep_equal

   Is current (deeo) equal to  other.

   @param  current Circular_Array_t instance
   @param  other Circular_Array_t instance
   @return 1 if true, 0 otherwise
*/
#define Circular_Array_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _circular_array_is_deep_equal )
int32_t Circular_Array_is_deep_equal( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other );

/**
   Circular_Array_copy

   Copy (shallow) other into current.

   @param  current Circular_Array_t instance
   @param  other Circular_Array_t instance
*/
#define Circular_Array_copy( arg ) PRIMITIVE_CAT( arg, _circular_array_copy )
void Circular_Array_copy( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other );

/**
   Circular_Array_deep_copy

   Copy (deeo) other into current.

   @param  current Circular_Array_t instance
   @param  other Circular_Array_t instance
*/
#define Circular_Array_deep_copy( arg ) PRIMITIVE_CAT( arg, _circular_array_deep_copy )
void Circular_Array_deep_copy( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other );

/*
   Disposal
*/

/**
   Circular_Array_dispose

   Free a Circular_Array_t instance. The value items are not disposed.

   @param  current pointer to Circular_Array_t instance
*/
#define Circular_Array_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_dispose )
void Circular_Array_dispose( Prefix )( Circular_Array_type( Prefix ) **current );

/**
   Circular_Array_deep_dispose

   Free a Circular_Array_t instance. The value items are disposed.

   @param  current pointer to Circular_Array_t instance
*/
#define Circular_Array_deep_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_deep_dispose )
void Circular_Array_deep_dispose( Prefix )( Circular_Array_type( Prefix ) **current );

/*
   Access
*/

/**
   Circular_Array_item

   Return the value in the circular_array at index.

   @param  current Circular_Array_t instance
   @param  index the index to the desired item
   @return the value of the item at the index in the circular_array
*/
#define Circular_Array_item( arg ) PRIMITIVE_CAT( arg, _circular_array_item )
Type Circular_Array_item( Prefix )( Circular_Array_type( Prefix ) *current, int32_t index );

/**
   Circular_Array_as_array

   Return the values of the the circular_array as a C array.

   @param  current Circular_Array_t instance
   @return the value of the item at the top of the circular_array
*/
#define Circular_Array_as_array( arg ) PRIMITIVE_CAT( arg, _circular_array_as_array )
Type * Circular_Array_as_array( Prefix )( Circular_Array_type( Prefix ) *current, int32_t *count );

/*
   Measurement
*/

/**
   Circular_Array_count

   Return the number of items in the circular_array.

   @param  current Circular_Array_t instance
   @return the number of items in the circular_array
*/
#define Circular_Array_count( arg ) PRIMITIVE_CAT( arg, _circular_array_count )
int32_t Circular_Array_count( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_capacity

   Return the number of slots available in the circular_array.

   @param  current Circular_Array_t instance
   @return the number of slots in the circular_array
*/
#define Circular_Array_capacity( arg ) PRIMITIVE_CAT( arg, _circular_array_capacity )
int32_t Circular_Array_capacity( Prefix )( Circular_Array_type( Prefix ) *current );


/*
   Status report
*/

/**
   Circular_Array_is_empty

   Returns 1 if the circular_array contains no items.

   @param  current Circular_Array_t instance
   @return 1 if circular_array is empty, 0 otherwise
*/
#define Circular_Array_is_empty( arg ) PRIMITIVE_CAT( arg, _circular_array_is_empty )
int32_t Circular_Array_is_empty( Prefix )( Circular_Array_type( Prefix ) *current );


/*
   Element change
*/

/**
   Circular_Array_put_first

   Insert new value at front of circular_array.

   @param  current Circular_Array_t instance
   @param  value what to insert
*/
#define Circular_Array_put_first( arg ) PRIMITIVE_CAT( arg, _circular_array_put_first )
void Circular_Array_put_first( Prefix )( Circular_Array_type( Prefix ) *current, Type value );

/**
   Circular_Array_put_last

   Insert new value at end of circular_array.

   @param  current Circular_Array_t instance
   @param  value what to insert
*/
#define Circular_Array_put_last( arg ) PRIMITIVE_CAT( arg, _circular_array_put_last )
void Circular_Array_put_last( Prefix )( Circular_Array_type( Prefix ) *current, Type value );

/**
   Circular_Array_remove_first

   Remove value at front of circular_array.

   @param  current Circular_Array_t instance
*/
#define Circular_Array_remove_first( arg ) PRIMITIVE_CAT( arg, _circular_array_remove_first )
void Circular_Array_remove_first( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_remove_first_and_dispose

   Remove value at front of circular_array and dispose it.

   @param  current Circular_Array_t instance
*/
#define Circular_Array_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_remove_first_and_dispose )
void Circular_Array_remove_first_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_remove_last

   Insert new value at end of circular_array.

   @param  current Circular_Array_t instance
   @param  value what to insert
*/
#define Circular_Array_remove_last( arg ) PRIMITIVE_CAT( arg, _circular_array_remove_last )
void Circular_Array_remove_last( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_remove_last_and_dispose

   Insert new value at end of circular_array.

   @param  current Circular_Array_t instance
   @param  value what to insert
*/
#define Circular_Array_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_remove_last_and_dispose )
void Circular_Array_remove_last_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_replace

   Replace value at index with value.

   @param  current Circular_Array_t instance
   @param  value what to replace with
   @param  index of the value
*/
#define Circular_Array_replace( arg ) PRIMITIVE_CAT( arg, _circular_array_replace )
void Circular_Array_replace( Prefix )( Circular_Array_type( Prefix ) *current, Type value, int32_t index );

/**
   Circular_Array_replace_and_dispose

   Replace value at index with value. Dispose of original value.

   @param  current Circular_Array_t instance
   @param  value what to replace with
   @param  index of the value
*/
#define Circular_Array_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_replace_and_dispose )
void Circular_Array_replace_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current, Type value, int32_t index );

/**
   Circular_Array_wipe_out

   Remove all items from circular_array.

   @param  current Circular_Array_t instance
*/
#define Circular_Array_wipe_out( arg ) PRIMITIVE_CAT( arg, _circular_array_wipe_out )
void Circular_Array_wipe_out( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_wipe_out_and_dispose

   Remove all items from circular_array. Dispose of removed values.

   @param  circular_array Circular_Array_t instance
*/
#define Circular_Array_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_wipe_out_and_dispose )
void Circular_Array_wipe_out_and_dispose( Prefix )( Circular_Array_type( Prefix ) *circular_array );

/**
   Circular_Array_set_count

   Set the count of the circular_array - must be same or lower than capacity

   @param  current Circular_Array_t instance
   @param  count the new count
*/
#define Circular_Array_set_count( arg ) PRIMITIVE_CAT( arg, _circular_array_set_count )
void Circular_Array_set_count( Prefix )( Circular_Array_type( Prefix ) *current, int32_t count );

/**
   Circular_Array_set_capacity

   Set the capacity of the circular_array - must be same or greater than count

   @param  current Circular_Array_t instance
   @param  capacity the new capacity
*/
#define Circular_Array_set_capacity( arg ) PRIMITIVE_CAT( arg, _circular_array_set_capacity )
void Circular_Array_set_capacity( Prefix )( Circular_Array_type( Prefix ) *current, int32_t capacity );

/**
   Circular_Array_ensure_count

   Ensure that the capacity and the count of the circular_array is capable of containing
   count entries

   @param  current Circular_Array_t instance
   @param  count the new count
*/
#define Circular_Array_ensure_count( arg ) PRIMITIVE_CAT( arg, _circular_array_ensure_count )
void Circular_Array_ensure_count( Prefix )( Circular_Array_type( Prefix ) *current, int32_t count );

/**
   Circular_Array_fill_default

   Fill every slot in the circular_array with the default value

   @param  current Circular_Array_t instance
*/
#define Circular_Array_fill_default( arg ) PRIMITIVE_CAT( arg, _circular_array_fill_default )
void Circular_Array_fill_default( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_fill_default_and_dispose

   Fill every slot in the circular_array with the default value, dispose of current
   items.

   @param  current Circular_Array_t instance
*/
#define Circular_Array_fill_default_and_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_fill_default_and_dispose )
void Circular_Array_fill_default_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current );

/**
   Circular_Array_replace_from_array

   Fill slots in the circular_array with the corresponding value of the array

   @param  current Circular_Array_t instance
   @param  array array of values to put into circular array
   @param  count number of items in the array
*/
#define Circular_Array_replace_from_array( arg ) PRIMITIVE_CAT( arg, _circular_array_replace_from_array )
void Circular_Array_replace_from_array( Prefix )( Circular_Array_type( Prefix ) *current, Type *array, int32_t count, int32_t start_index );

/**
   Circular_Array_replace_from_array_and_dispose

   Fill slots in the circular_array with the corresponding value of the array.
   Dispose existing items in circular buffer

   @param  current Circular_Array_t instance
   @param  array array of values to put into circular array
   @param  count number of items in the array
*/
#define Circular_Array_replace_from_array_and_dispose( arg ) PRIMITIVE_CAT( arg, _circular_array_replace_from_array_and_dispose )
void Circular_Array_replace_from_array_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current, Type *array, int32_t count, int32_t start_index );

/* End of file */




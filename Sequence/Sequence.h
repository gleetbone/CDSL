/**
 @file Sequence.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Sequences (resizable arrays)"

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

 Function declarations for the opaque Sequence_t type.

*/

/**
   Version
*/

#define SEQUENCE_VERSION_MAJOR 2
#define SEQUENCE_VERSION_MINOR 0
#define SEQUENCE_VERSION_PATCH 0

#define SEQUENCE_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define SEQUENCE_VERSION \
   SEQUENCE_MAKE_VERSION( SEQUENCE_VERSION_MAJOR, \
                       SEQUENCE_VERSION_MINOR, \
                       SEQUENCE_VERSION_PATCH )

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

#define Sequence_struct( arg ) PRIMITIVE_CAT( arg, _sequence_struct )
#define Sequence_type( arg ) PRIMITIVE_CAT( arg, _sequence_t )
#define Sequence_name( arg ) PRIMITIVE_CAT( arg, _sequence )

/**
   Structure declarations
*/

struct Sequence_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Sequence_struct( Prefix ) Sequence_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   Sequence_make

   Return a new empty Sequence_t instance.

   @return Sequence_t instance
*/
#define Sequence_make( arg ) PRIMITIVE_CAT( arg, _sequence_make )
Sequence_type( Prefix ) * Sequence_make( Prefix )( void );

/**
   Sequence_clone

   Return a shallow clone of the sequence.

   @param  current Sequence_t instance
   @return clone of the sequence
*/
#define Sequence_clone( arg ) PRIMITIVE_CAT( arg, _sequence_clone )
Sequence_type( Prefix ) * Sequence_clone( Prefix )( Sequence_type( Prefix ) *current );

/**
   Sequence_deep_clone

   Return a deep clone of the sequence.

   @param  current Sequence_t instance
   @return clone of the sequence
*/
#define Sequence_deep_clone( arg ) PRIMITIVE_CAT( arg, _sequence_deep_clone )
Sequence_type( Prefix ) * Sequence_deep_clone( Prefix )( Sequence_type( Prefix ) *current );

/**
   Sequence_make_n

   Return a new empty Sequence_t instance with capacity of n.

   @param  n the capacity
   @return Sequence_t instance
*/
#define Sequence_make_n( arg ) PRIMITIVE_CAT( arg, _sequence_make_n )
Sequence_type( Prefix ) * Sequence_make_n( Prefix )( int32_t n );

/**
   Sequence_make_from_array

   Return a new Sequence_t instance populated with contents of an array

   @param  array the carray
   @param  count the number of items in the array
   @param  capacity the number of positions in the array
   @return Sequence_t instance
*/
#define Sequence_make_from_array( arg ) PRIMITIVE_CAT( arg, _sequence_make_from_array )
Sequence_type( Prefix ) * Sequence_make_from_array( Prefix )( Type *array, int32_t count, int32_t capacity );

/*
   Basic
*/

/**
   Sequence_is_equal

   Is current (shallow) equal to  other.

   @param  current Sequence_t instance
   @param  other Sequence_t instance
   @return 1 if true, 0 otherwise
*/
#define Sequence_is_equal( arg ) PRIMITIVE_CAT( arg, _sequence_is_equal )
int32_t Sequence_is_equal( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other );

/**
   Sequence_is_deep_equal

   Is current (deeo) equal to  other.

   @param  current Sequence_t instance
   @param  other Sequence_t instance
   @return 1 if true, 0 otherwise
*/
#define Sequence_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _sequence_is_deep_equal )
int32_t Sequence_is_deep_equal( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other );

/**
   Sequence_copy

   Copy (shallow) other into current.

   @param  current Sequence_t instance
   @param  other Sequence_t instance
*/
#define Sequence_copy( arg ) PRIMITIVE_CAT( arg, _sequence_copy )
void Sequence_copy( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other );

/**
   Sequence_deep_copy

   Copy (deeo) other into current.

   @param  current Sequence_t instance
   @param  other Sequence_t instance
*/
#define Sequence_deep_copy( arg ) PRIMITIVE_CAT( arg, _sequence_deep_copy )
void Sequence_deep_copy( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other );

/*
   Disposal
*/

/**
   Sequence_dispose

   Free a Sequence_t instance. The value items are not disposed.

   @param  current pointer to Sequence_t instance
*/
#define Sequence_dispose( arg ) PRIMITIVE_CAT( arg, _sequence_dispose )
void Sequence_dispose( Prefix )( Sequence_type( Prefix ) **current );

/**
   Sequence_deep_dispose

   Free a Sequence_t instance. The value items are disposed.

   @param  current pointer to Sequence_t instance
*/
#define Sequence_deep_dispose( arg ) PRIMITIVE_CAT( arg, _sequence_deep_dispose )
void Sequence_deep_dispose( Prefix )( Sequence_type( Prefix ) **current );

/*
   Access
*/

/**
   Sequence_item

   Return the value of the top of the sequence at index.

   @param  current Sequence_t instance
   @param  index the index to the desired item
   @return the value of the item at the top of the sequence
*/
#define Sequence_item( arg ) PRIMITIVE_CAT( arg, _sequence_item )
Type Sequence_item( Prefix )( Sequence_type( Prefix ) *current, int32_t index );

/**
   Sequence_as_array

   Return the values of the the sequence as an array.

   @param  current Sequence_t instance
   @return the value of the item at the top of the sequence
*/
#define Sequence_as_array( arg ) PRIMITIVE_CAT( arg, _sequence_as_array )
Type * Sequence_as_array( Prefix )( Sequence_type( Prefix ) *current, int32_t *count );

/*
   Measurement
*/

/**
   Sequence_count

   Return the number of items in the sequence.

   @param  current Sequence_t instance
   @return the number of items in the sequence
*/
#define Sequence_count( arg ) PRIMITIVE_CAT( arg, _sequence_count )
int32_t Sequence_count( Prefix )( Sequence_type( Prefix ) *current );

/**
   Sequence_capacity

   Return the number of slots available in the sequence.

   @param  current Sequence_t instance
   @return the number of slots in the sequence
*/
#define Sequence_capacity( arg ) PRIMITIVE_CAT( arg, _sequence_capacity )
int32_t Sequence_capacity( Prefix )( Sequence_type( Prefix ) *current );


/*
   Status report
*/

/**
   Sequence_is_empty

   Returns 1 if the sequence contains no items.

   @param  current Sequence_t instance
   @return 1 if sequence is empty, 0 otherwise
*/
#define Sequence_is_empty( arg ) PRIMITIVE_CAT( arg, _sequence_is_empty )
int32_t Sequence_is_empty( Prefix )( Sequence_type( Prefix ) *current );


/*
   Element change
*/

/**
   Sequence_put

   Put a new value in the sequence at index.

   @param  current Sequence_t instance
   @param  value what to insert
   @param  index where to put the value
*/
#define Sequence_put( arg ) PRIMITIVE_CAT( arg, _sequence_put )
void Sequence_put( Prefix )( Sequence_type( Prefix ) *current, Type value, int32_t index );

/**
   Sequence_replace

   Replace value at index with value.

   @param  current Sequence_t instance
   @param  value what to replace with
   @param  index where to put the value
*/
#define Sequence_replace( arg ) PRIMITIVE_CAT( arg, _sequence_replace )
void Sequence_replace( Prefix )( Sequence_type( Prefix ) *current, Type value, int32_t index );

/**
   Sequence_replace_and_dispose

   Replace value at index with value. Dispose of original value.

   @param  current Sequence_t instance
   @param  value what to replace with
*/
#define Sequence_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _sequence_replace_and_dispose )
void Sequence_replace_and_dispose( Prefix )( Sequence_type( Prefix ) *current, Type value, int32_t index );

/**
   Sequence_wipe_out

   Remove all items from sequence.

   @param  current Sequence_t instance
*/
#define Sequence_wipe_out( arg ) PRIMITIVE_CAT( arg, _sequence_wipe_out )
void Sequence_wipe_out( Prefix )( Sequence_type( Prefix ) *current );

/**
   Sequence_wipe_out_and_dispose

   Remove all items from sequence. Dipose of removed values.

   @param  sequence Sequence_t instance
*/
#define Sequence_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _sequence_wipe_out_and_dispose )
void Sequence_wipe_out_and_dispose( Prefix )( Sequence_type( Prefix ) *sequence );

/**
   Sequence_set_count

   Set the count of the sequence - must be same or lower than capacity

   @param  current Sequence_t instance
   @param  count the new count
*/
#define Sequence_set_count( arg ) PRIMITIVE_CAT( arg, _sequence_set_count )
void Sequence_set_count( Prefix )( Sequence_type( Prefix ) *current, int32_t count );

/**
   Sequence_set_capacity

   Set the capacity of the sequence - must be same or greater than count

   @param  current Sequence_t instance
   @param  capacity the new capacity
*/
#define Sequence_set_capacity( arg ) PRIMITIVE_CAT( arg, _sequence_set_capacity )
void Sequence_set_capacity( Prefix )( Sequence_type( Prefix ) *current, int32_t capacity );

/**
   Sequence_ensure_count

   Ensure that the capacity and the count of the sequence is capable of containing
   count entries

   @param  current Sequence_t instance
   @param  count the new count
*/
#define Sequence_ensure_count( arg ) PRIMITIVE_CAT( arg, _sequence_ensure_count )
void Sequence_ensure_count( Prefix )( Sequence_type( Prefix ) *current, int32_t count );

/* End of file */




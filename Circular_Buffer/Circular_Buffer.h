/**
 @file Circular_Buffer.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Circular buffer"

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

 Function declarations for the opaque Circular_Buffer_t type.

*/

/**
   includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Type   - the type of the value

   Macros that must be present (external to this file):

   VALUE_DISPOSE_FUNCTION  -  frees a value instance

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Circular_Buffer_struct( arg ) PRIMITIVE_CAT( arg, _circular_buffer_struct )
#define Circular_Buffer_type( arg ) PRIMITIVE_CAT( arg, _circular_buffer_t )
#define Circular_Buffer_name( arg ) PRIMITIVE_CAT( arg, _circular_buffer )

/**
   Structure declarations
*/

struct Circular_Buffer_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Circular_Buffer_struct( Prefix ) Circular_Buffer_type( Prefix );


/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   Circular_Buffer_make

   Return a new empty Circular_Buffer_t instance.

   @return Circular_Buffer_t instance
*/
#define Circular_Buffer_make( arg ) PRIMITIVE_CAT( arg, _circular_buffer_make )
Circular_Buffer_type( Prefix ) * Circular_Buffer_make( Prefix )( int32_t capacity );


/*
   Disposal
*/

/**
   Circular_Buffer_dispose

   Free a Sbuffer_t instance. The value items are not disposed.

   @param  buffer Circular_Buffer_t instance
*/
#define Circular_Buffer_dispose( arg ) PRIMITIVE_CAT( arg, _circular_buffer_dispose )
void Circular_Buffer_dispose( Prefix )( Circular_Buffer_type( Prefix ) **buffer );

/*
   Access
*/

/**
   Circular_Buffer_item

   Return the value of the current item

   @param  buffer Circular_Buffer_t instance
   @return the value of the current
*/
#define Circular_Buffer_item( arg ) PRIMITIVE_CAT( arg, _circular_buffer_item )
Type Circular_Buffer_item( Prefix )( Circular_Buffer_type( Prefix ) *buffer );


/*
   Measurement
*/

/**
   Circular_Buffer_count

   Return the number of items in the buffer.

   @param  buffer Circular_Buffer_t instance
   @return the number of items in the buffer
*/
#define Circular_Buffer_count( arg ) PRIMITIVE_CAT( arg, _circular_buffer_count )
int32_t Circular_Buffer_count( Prefix )( Circular_Buffer_type( Prefix ) *buffer );

/*
   Circular_Buffer_capacity

   Return the max number of items in the buffer.

   @param  buffer Circular_Buffer_t instance
   @return the max number of items in the buffer
*/
#define Circular_Buffer_capacity( arg ) PRIMITIVE_CAT( arg, _circular_buffer_capacity )
int32_t Circular_Buffer_capacity( Prefix )( Circular_Buffer_type( Prefix ) *buffer );


/*
   Status report
*/

/**
   Circular_Buffer_is_empty

   Returns 1 if the buffer contains no items.

   @param  buffer Circular_Buffer_t instance
   @return 1 if buffer is empty, 0 otherwise
*/
#define Circular_Buffer_is_empty( arg ) PRIMITIVE_CAT( arg, _circular_buffer_is_empty )
int32_t Circular_Buffer_is_empty( Prefix )( Circular_Buffer_type( Prefix ) *buffer );

/**
   Circular_Buffer_is_full

   Returns 1 if the buffer contains max number of  items.

   @param  buffer Circular_Buffer_t instance
   @return 1 if buffer is full, 0 otherwise
*/
#define Circular_Buffer_is_full( arg ) PRIMITIVE_CAT( arg, _circular_buffer_is_full )
int32_t Circular_Buffer_is_full( Prefix )( Circular_Buffer_type( Prefix ) *buffer );


/*
   Cursor movement
*/

/**
   Circular_Buffer_forth

   Modifies the buffer's internals so the next item can be read from the buffer.

   @param  buffer Circular_Buffer_t instance
*/
#define Circular_Buffer_forth( arg ) PRIMITIVE_CAT( arg, _circular_buffer_forth )
void Circular_Buffer_forth( Prefix )( Circular_Buffer_type( Prefix ) *buffer );


/*
   Element change
*/

/**
   Circular_Buffer_put

   Insert value into buffer.

   @param  buffer Circular_Buffer_t instance
   @param  value what to insert
*/
#define Circular_Buffer_put( arg ) PRIMITIVE_CAT( arg, _circular_buffer_put )
void Circular_Buffer_put( Prefix )( Circular_Buffer_type( Prefix ) *buffer, Type value );

/*
   Removal
*/

/**
   Circular_Buffer_wipe_out

   Remove all items from buffer.

   @param  buffer Circular_Buffer_t instance
*/
#define Circular_Buffer_wipe_out( arg ) PRIMITIVE_CAT( arg, _circular_buffer_wipe_out )
void Circular_Buffer_wipe_out( Prefix )( Circular_Buffer_type( Prefix ) *buffer );


/* End of file */




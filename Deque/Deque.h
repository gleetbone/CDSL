/**
 @file Deque.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Deques (stack that can be appended to or popped from either end)"

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

 Function declarations for the opaque Deque_t type.

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

#define Deque_struct( arg ) PRIMITIVE_CAT( arg, _deque_struct )
#define Deque_type( arg ) PRIMITIVE_CAT( arg, _deque_t )
#define Deque_name( arg ) PRIMITIVE_CAT( arg, _deque )

/**
   Structure declarations
*/

struct Deque_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Deque_struct( Prefix ) Deque_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   Deque_make

   Return a new empty Deque_t instance.

   @return Deque_t instance
*/
#define Deque_make( arg ) PRIMITIVE_CAT( arg, _deque_make )
Deque_type( Prefix ) * Deque_make( Prefix )( void );

/**
   Deque_clone

   Return a clone of a Deque_t instance.

   @param other the Deque_t instance to clone
   @return cloned Deque_t instance
*/
#define Deque_clone( arg ) PRIMITIVE_CAT( arg, _deque_clone )
Deque_type( Prefix ) * Deque_clone( Prefix )( Deque_type( Prefix ) * other );

/**
   Deque_deep_clone

   Return a deep_clone of a Deque_t instance.

   @param other the Deque_t instance to clone
   @return cloned Deque_t instance
*/
#define Deque_deep_clone( arg ) PRIMITIVE_CAT( arg, _deque_deep_clone )
Deque_type( Prefix ) * Deque_deep_clone( Prefix )( Deque_type( Prefix ) * other );

/**
   Deque_copy

   Copy the contents of one Deque_t instance into another.

   @param current the Deque_t instance to copy into
   @param other the Deque_t instance to copy from
*/
#define Deque_copy( arg ) PRIMITIVE_CAT( arg, _deque_copy )
void Deque_copy( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other );

/**
   Deque_deep_copy

   Copy the contents of one Deque_t instance into another.

   @param current the Deque_t instance to copy into
   @param other the Deque_t instance to copy from
*/
#define Deque_deep_copy( arg ) PRIMITIVE_CAT( arg, _deque_deep_copy )
void Deque_deep_copy( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other );

/*
   Disposal
*/

/**
   Deque_dispose

   Free a Deque_t instance. The value items are not disposed.

   @param  deque Deque_t instance
*/
#define Deque_dispose( arg ) PRIMITIVE_CAT( arg, _deque_dispose )
void Deque_dispose( Prefix )( Deque_type( Prefix ) **deque );

/**
   Deque_deep_dispose

   Free a Deque_t instance. The value items are disposed.

   @param  deque Deque_t instance
*/
#define Deque_deep_dispose( arg ) PRIMITIVE_CAT( arg, _deque_deep_dispose )
void Deque_deep_dispose( Prefix )( Deque_type( Prefix ) **deque );

/*
   Access
*/

/**
   Deque_first

   Return the value of the start of the deque.

   @param  deque Deque_t instance
   @return the value of the item at the top of the deque
*/
#define Deque_first( arg ) PRIMITIVE_CAT( arg, _deque_first )
Type Deque_first( Prefix )( Deque_type( Prefix ) *deque );

/**
   Deque_last

   Return the value of the end of the deque.

   @param  deque Deque_t instance
   @return the value of the item at the top of the deque
*/
#define Deque_last( arg ) PRIMITIVE_CAT( arg, _deque_last )
Type Deque_last( Prefix )( Deque_type( Prefix ) *deque );

/*
   Measurement
*/

/**
   Deque_count

   Return the number of items in the deque.

   @param  deque Deque_t instance
   @return the number of items in the deque
*/
#define Deque_count( arg ) PRIMITIVE_CAT( arg, _deque_count )
int32_t Deque_count( Prefix )( Deque_type( Prefix ) *deque );


/*
   Basic
*/

/**
   Deque_is_equal

   Returns 1 if the contents of one Deque_t instance are the same as another.

   @param current the Deque_t instance to compare to
   @param other the Deque_t instance to compare from
   @return 1 if current and other are equal, 0 otherwise
*/
#define Deque_is_equal( arg ) PRIMITIVE_CAT( arg, _deque_is_equal )
int32_t Deque_is_equal( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other );

/**
   Deque_is_deep_equal

   Returns 1 if the contents of one Deque_t instance are deep equal to another.

   @param current the Deque_t instance to compare to
   @param other the Deque_t instance to compare from
   @return 1 if current and other are equal, 0 otherwise
*/
#define Deque_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _deque_is_deep_equal )
int32_t Deque_is_deep_equal( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other );

/*
   Status report
*/

/**
   Deque_is_empty

   Returns 1 if the deque contains no items.

   @param  deque Deque_t instance
   @return 1 if deque is empty, 0 otherwise
*/
#define Deque_is_empty( arg ) PRIMITIVE_CAT( arg, _deque_is_empty )
int32_t Deque_is_empty( Prefix )( Deque_type( Prefix ) *deque );


/*
   Element change
*/

/**
   Deque_put_first

   Insert new value at start of deque.

   @param  deque Deque_t instance
   @param  value what to insert
*/
#define Deque_put_first( arg ) PRIMITIVE_CAT( arg, _deque_put_first )
void Deque_put_first( Prefix )( Deque_type( Prefix ) *deque, Type value );

/**
   Deque_put_last

   Insert new value at end of deque.

   @param  deque Deque_t instance
   @param  value what to insert
*/
#define Deque_put_last( arg ) PRIMITIVE_CAT( arg, _deque_put_last )
void Deque_put_last( Prefix )( Deque_type( Prefix ) *deque, Type value );

/*
   Removal
*/

/**
   Deque_remove_first

   Remove value at start of deque.

   @param  deque Deque_t instance
*/
#define Deque_remove_first( arg ) PRIMITIVE_CAT( arg, _deque_remove_first )
void Deque_remove_first( Prefix )( Deque_type( Prefix ) *deque );

/**
   Deque_remove_first_and_dispose

   Remove value at start of deque. Dipose of removed value.

   @param  deque Deque_t instance
*/
#define Deque_remove_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_remove_first_and_dispose )
void Deque_remove_first_and_dispose( Prefix )( Deque_type( Prefix ) *deque );

/**
   Deque_remove_last

   Remove value at start of deque.

   @param  deque Deque_t instance
*/
#define Deque_remove_last( arg ) PRIMITIVE_CAT( arg, _deque_remove_last )
void Deque_remove_last( Prefix )( Deque_type( Prefix ) *deque );

/**
   Deque_remove_last_and_dispose

   Remove value at start of deque. Dipose of removed value.

   @param  deque Deque_t instance
*/
#define Deque_remove_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_remove_last_and_dispose )
void Deque_remove_last_and_dispose( Prefix )( Deque_type( Prefix ) *deque );

/**
   Deque_prune_first

   Remove count items from start of deque.

   @param  deque Deque_t instance
   @param  count how many items to prune
*/
#define Deque_prune_first( arg ) PRIMITIVE_CAT( arg, _deque_prune_first )
void Deque_prune_first( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_prune_first_and_dispose

   Remove count items from start of deque. Dispose of removed values.

   @param  deque Deque_t instance
   @param  count how many items to prune
*/
#define Deque_prune_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_prune_first_and_dispose )
void Deque_prune_first_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_prune_last

   Remove count items from start of deque.

   @param  deque Deque_t instance
   @param  count how many items to prune
*/
#define Deque_prune_last( arg ) PRIMITIVE_CAT( arg, _deque_prune_last )
void Deque_prune_last( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_prune_last_and_dispose

   Remove count items from start of deque. Dispose of removed values.

   @param  deque Deque_t instance
   @param  count how many items to prune
*/
#define Deque_prune_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_prune_last_and_dispose )
void Deque_prune_last_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_keep_first

   Remove items from deque to leave count items at start of deque.

   @param  deque Deque_t instance
   @param  count how many items to leave
*/
#define Deque_keep_first( arg ) PRIMITIVE_CAT( arg, _deque_keep_first )
void Deque_keep_first( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_keep_first_and_dispose

   Remove items from deque to leave count items at start of deque. Dispose of
   removed values.

   @param  deque Deque_t instance
   @param  count how many items to leave
*/
#define Deque_keep_first_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_keep_first_and_dispose )
void Deque_keep_first_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_keep_last

   Remove items from deque to leave count items at start of deque.

   @param  deque Deque_t instance
   @param  count how many items to leave
*/
#define Deque_keep_last( arg ) PRIMITIVE_CAT( arg, _deque_keep_last )
void Deque_keep_last( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_keep_last_and_dispose

   Remove items from deque to leave count items at start of deque. Dispose of
   removed values.

   @param  deque Deque_t instance
   @param  count how many items to leave
*/
#define Deque_keep_last_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_keep_last_and_dispose )
void Deque_keep_last_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count );

/**
   Deque_wipe_out

   Remove all items from deque.

   @param  deque Deque_t instance
*/
#define Deque_wipe_out( arg ) PRIMITIVE_CAT( arg, _deque_wipe_out )
void Deque_wipe_out( Prefix )( Deque_type( Prefix ) *deque );

/**
   Deque_wipe_out_and_dispose

   Remove all items from deque. Dipose of removed values.

   @param  deque Deque_t instance
*/
#define Deque_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _deque_wipe_out_and_dispose )
void Deque_wipe_out_and_dispose( Prefix )( Deque_type( Prefix ) *deque );



/* End of file */




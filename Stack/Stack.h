/**
 @file Stack.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Stacks"

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

 Function declarations for the opaque Stack_t type.

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

#define Stack_struct( arg ) PRIMITIVE_CAT( arg, _stack_struct )
#define Stack_type( arg ) PRIMITIVE_CAT( arg, _stack_t )
#define Stack_name( arg ) PRIMITIVE_CAT( arg, _stack )

/**
   Structure declarations
*/

struct Stack_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Stack_struct( Prefix ) Stack_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   Stack_make

   Return a new empty Stack_t instance.

   @return Stack_t instance
*/
#define Stack_make( arg ) PRIMITIVE_CAT( arg, _stack_make )
Stack_type( Prefix ) * Stack_make( Prefix )( void );

/*
   Basic
*/

/**
   Stack_clone

   Return a new Stack_t instance filled with the content of stack. The value
   of the items in stack are not copied.

   @param  stack Stack_t instance to copy from
   @return Stack_t instance
*/
#define Stack_clone( arg ) PRIMITIVE_CAT( arg, _stack_clone )
Stack_type( Prefix ) * Stack_clone( Prefix )( Stack_type( Prefix ) *stack );

/**
   Stack_deep_clone

   Return a new Stack_t instance filled with duplicates of the content of stack.
   The value of the items in stack are copied.

   @param  stack Stack_t instance to copy from
   @return Stack_t instance
*/

#define Stack_deep_clone( arg ) PRIMITIVE_CAT( arg, _stack_deep_clone )
Stack_type( Prefix ) *
Stack_deep_clone( Prefix )( Stack_type( Prefix ) *oher );

/**
   Stack_is_equal

   Check that stack contains same elements as other

   @param  current Stack_t instance
   @param  other Stack_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define Stack_is_equal( arg ) PRIMITIVE_CAT( arg, _stack_is_equal )
int32_t
Stack_is_equal( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other );

/**
   Stack_is_deep_equal

   Check that stack contains same elements as other

   @param  current Stack_t instance
   @param  other Stack_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define Stack_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _stack_is_deep_equal )
int32_t
Stack_is_deep_equal( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other );

/**
   Stack_copy

   Copy other into current

   @param  current Stack_t instance
   @param  other Stack_t instance to copy from

*/

#define Stack_copy( arg ) PRIMITIVE_CAT( arg, _stack_copy )
void
Stack_copy( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other );

/**
   Stack_deep_copy

   Deep copy other into current

   @param  current Stack_t instance
   @param  other Stack_t instance to deep_copy from

*/

#define Stack_deep_copy( arg ) PRIMITIVE_CAT( arg, _stack_deep_copy )
void
Stack_deep_copy( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other );


/*
   Disposal
*/

/**
   Stack_dispose

   Free a Stack_t instance. The value items are not disposed.

   @param  current Stack_t instance
*/
#define Stack_dispose( arg ) PRIMITIVE_CAT( arg, _stack_dispose )
void Stack_dispose( Prefix )( Stack_type( Prefix ) **current );

/**
   Stack_deep_dispose

   Free a Stack_t instance. The value items are disposed.

   @param  current Stack_t instance
*/
#define Stack_deep_dispose( arg ) PRIMITIVE_CAT( arg, _stack_deep_dispose )
void Stack_deep_dispose( Prefix )( Stack_type( Prefix ) **current );

/*
   Access
*/

/**
   Stack_item

   Return the value of the top of the stack.

   @param  current Stack_t instance
   @return the value of the item at the top of the stack
*/
#define Stack_item( arg ) PRIMITIVE_CAT( arg, _stack_item )
Type Stack_item( Prefix )( Stack_type( Prefix ) *current );

/*
   Measurement
*/

/**
   Stack_count

   Return the number of items in the stack.

   @param  current Stack_t instance
   @return the number of items in the stack
*/
#define Stack_count( arg ) PRIMITIVE_CAT( arg, _stack_count )
int32_t Stack_count( Prefix )( Stack_type( Prefix ) *current );


/*
   Status report
*/

/**
   Stack_is_empty

   Returns 1 if the stack contains no items.

   @param  current Stack_t instance
   @return 1 if stack is empty, 0 otherwise
*/
#define Stack_is_empty( arg ) PRIMITIVE_CAT( arg, _stack_is_empty )
int32_t Stack_is_empty( Prefix )( Stack_type( Prefix ) *current );


/*
   Element change
*/

/**
   Stack_put

   Insert new value at top of stack.

   @param  current Stack_t instance
   @param  value what to insert
*/
#define Stack_put( arg ) PRIMITIVE_CAT( arg, _stack_put )
void Stack_put( Prefix )( Stack_type( Prefix ) *current, Type value );

/**
   Stack_replace

   Replace value at top of stack with value.

   @param  current Stack_t instance
   @param  value what to replace with
*/
#define Stack_replace( arg ) PRIMITIVE_CAT( arg, _stack_replace )
void Stack_replace( Prefix )( Stack_type( Prefix ) *current, Type value );

/**
   Stack_replace_and_dispose

   Replace value at top of stack with value. Dispose of original value.

   @param  current Stack_t instance
   @param  value what to replace with
*/
#define Stack_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _stack_replace_and_dispose )
void Stack_replace_and_dispose( Prefix )( Stack_type( Prefix ) *current, Type value );

/*
   Removal
*/

/**
   Stack_remove

   Remove value at top of  stack.

   @param  current Stack_t instance
*/
#define Stack_remove( arg ) PRIMITIVE_CAT( arg, _stack_remove )
void Stack_remove( Prefix )( Stack_type( Prefix ) *current );

/**
   Stack_remove_and_dispose

   Remove value at top of stack. Dipose of removed value.

   @param  current Stack_t instance
*/
#define Stack_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _stack_remove_and_dispose )
void Stack_remove_and_dispose( Prefix )( Stack_type( Prefix ) *current );

/**
   Stack_prune

   Remove count items from stack.

   @param  current Stack_t instance
   @param  count how many items to prune
*/
#define Stack_prune( arg ) PRIMITIVE_CAT( arg, _stack_prune )
void Stack_prune( Prefix )( Stack_type( Prefix ) *current, int32_t count );

/**
   Stack_prune_and_dispose

   Remove count items from stack.Dipose of removed values.

   @param  current Stack_t instance
   @param  count how many items to prune
*/
#define Stack_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _stack_prune_and_dispose )
void Stack_prune_and_dispose( Prefix )( Stack_type( Prefix ) *current, int32_t count );

/**
   Stack_keep

   Remove items from stack to leave count items in stack.

   @param  current Stack_t instance
   @param  count how many items to leave
*/
#define Stack_keep( arg ) PRIMITIVE_CAT( arg, _stack_keep )
void Stack_keep( Prefix )( Stack_type( Prefix ) *current, int32_t count );

/**
   Stack_keep_and_dispose

   Remove items from stack to leave count items in stack.

   @param  current Stack_t instance
   @param  count how many items to leave
*/
#define Stack_keep_and_dispose( arg ) PRIMITIVE_CAT( arg, _stack_keep_and_dispose )
void Stack_keep_and_dispose( Prefix )( Stack_type( Prefix ) *current, int32_t count );

/**
   Stack_wipe_out

   Remove all items from stack.

   @param  current Stack_t instance
*/
#define Stack_wipe_out( arg ) PRIMITIVE_CAT( arg, _stack_wipe_out )
void Stack_wipe_out( Prefix )( Stack_type( Prefix ) *current );

/**
   Stack_wipe_out_and_dispose

   Remove all items from stack. Dipose of removed values.

   @param  current Stack_t instance
*/
#define Stack_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _stack_wipe_out_and_dispose )
void Stack_wipe_out_and_dispose( Prefix )( Stack_type( Prefix ) *current );



/* End of file */




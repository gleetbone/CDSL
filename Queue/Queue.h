/**
 @file Queue.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Queues (queue that can be added to on one end and popped on the other)"

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

 Function declarations for the opaque Queue_t type.

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

#define Queue_struct( arg ) PRIMITIVE_CAT( arg, _queue_struct )
#define Queue_type( arg ) PRIMITIVE_CAT( arg, _queue_t )
#define Queue_name( arg ) PRIMITIVE_CAT( arg, _queue )

/**
   Structure declarations
*/

struct Queue_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Queue_struct( Prefix ) Queue_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/


/*
   Initialization
*/

/**
   Queue_make

   Return a new empty Queue_t instance.

   @return Queue_t instance
*/
#define Queue_make( arg ) PRIMITIVE_CAT( arg, _queue_make )
Queue_type( Prefix ) * Queue_make( Prefix )( void );

/*
   Basic
*/

/**
   Queue_clone

   Return a new Queue_t instance filled with the content of queue. The value
   of the items in queue are not copied.

   @param  queue Queue_t instance to copy from
   @return Queue_t instance
*/
#define Queue_clone( arg ) PRIMITIVE_CAT( arg, _queue_clone )
Queue_type( Prefix ) * Queue_clone( Prefix )( Queue_type( Prefix ) *queue );

/**
   Queue_deep_clone

   Return a new Queue_t instance filled with duplicates of the content of queue.
   The value of the items in queue are copied.

   @param  queue Queue_t instance to copy from
   @return Queue_t instance
*/

#define Queue_deep_clone( arg ) PRIMITIVE_CAT( arg, _queue_deep_clone )
Queue_type( Prefix ) *
Queue_deep_clone( Prefix )( Queue_type( Prefix ) *oher );

/**
   Queue_is_equal

   Check that queue contains same elements as other

   @param  current Queue_t instance
   @param  other Queue_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define Queue_is_equal( arg ) PRIMITIVE_CAT( arg, _queue_is_equal )
int32_t
Queue_is_equal( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other );

/**
   Queue_is_deep_equal

   Check that queue contains same elements as other

   @param  current Queue_t instance
   @param  other Queue_t instance to compare to
   @return 1 if equal, 0 otherwise
*/

#define Queue_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _queue_is_deep_equal )
int32_t
Queue_is_deep_equal( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other );

/**
   Queue_copy

   Copy other into current

   @param  current Queue_t instance
   @param  other Queue_t instance to copy from

*/

#define Queue_copy( arg ) PRIMITIVE_CAT( arg, _queue_copy )
void
Queue_copy( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other );

/**
   Queue_deep_copy

   Deep copy other into current

   @param  current Queue_t instance
   @param  other Queue_t instance to deep_copy from

*/

#define Queue_deep_copy( arg ) PRIMITIVE_CAT( arg, _queue_deep_copy )
void
Queue_deep_copy( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other );

/*
   Disposal
*/

/**
   Queue_dispose

   Free a Queue_t instance. The value items are not disposed.

   @param  current Queue_t instance
*/
#define Queue_dispose( arg ) PRIMITIVE_CAT( arg, _queue_dispose )
void Queue_dispose( Prefix )( Queue_type( Prefix ) **current );

/**
   Queue_dispose_with_contents

   Free a Queue_t instance. The value items are disposed.

   @param  current Queue_t instance
*/
#define Queue_deep_dispose( arg ) PRIMITIVE_CAT( arg, _queue_deep_dispose )
void Queue_deep_dispose( Prefix )( Queue_type( Prefix ) **current );

/*
   Access
*/

/**
   Queue_item

   Return the value of the top of the queue.

   @param  current Queue_t instance
   @return the value of the item at the top of the queue
*/
#define Queue_item( arg ) PRIMITIVE_CAT( arg, _queue_item )
Type Queue_item( Prefix )( Queue_type( Prefix ) *current );

/*
   Measurement
*/

/**
   Queue_count

   Return the number of items in the queue.

   @param  current Queue_t instance
   @return the number of items in the queue
*/
#define Queue_count( arg ) PRIMITIVE_CAT( arg, _queue_count )
int32_t Queue_count( Prefix )( Queue_type( Prefix ) *current );


/*
   Status report
*/

/**
   Queue_is_empty

   Returns 1 if the queue contains no items.

   @param  current Queue_t instance
   @return 1 if queue is empty, 0 otherwise
*/
#define Queue_is_empty( arg ) PRIMITIVE_CAT( arg, _queue_is_empty )
int32_t Queue_is_empty( Prefix )( Queue_type( Prefix ) *current );


/*
   Element change
*/

/**
   Queue_put

   Insert new value at bottom of queue.

   @param  current Queue_t instance
   @param  value what to insert
*/
#define Queue_put( arg ) PRIMITIVE_CAT( arg, _queue_put )
void Queue_put( Prefix )( Queue_type( Prefix ) *current, Type value );

/*
   Removal
*/

/**
   Queue_remove

   Remove value at top of queue.

   @param  current Queue_t instance
*/
#define Queue_remove( arg ) PRIMITIVE_CAT( arg, _queue_remove )
void Queue_remove( Prefix )( Queue_type( Prefix ) *current );

/**
   Queue_remove_and_dispose

   Remove value at top of queue. Dipose of removed value.

   @param  current Queue_t instance
*/
#define Queue_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_remove_and_dispose )
void Queue_remove_and_dispose( Prefix )( Queue_type( Prefix ) *current );

/**
   Queue_prune

   Remove count items from queue.

   @param  current Queue_t instance
   @param  count how many items to prune
*/
#define Queue_prune( arg ) PRIMITIVE_CAT( arg, _queue_prune )
void Queue_prune( Prefix )( Queue_type( Prefix ) *current, int32_t count );

/**
   Queue_prune_and_dispose

   Remove count items from queue.Dipose of removed values.

   @param  current Queue_t instance
   @param  count how many items to prune
*/
#define Queue_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_prune_and_dispose )
void Queue_prune_and_dispose( Prefix )( Queue_type( Prefix ) *current, int32_t count );

/**
   Queue_keep

   Remove items from queue to leave count items in queue.

   @param  current Queue_t instance
   @param  count how many items to leave
*/
#define Queue_keep( arg ) PRIMITIVE_CAT( arg, _queue_keep )
void Queue_keep( Prefix )( Queue_type( Prefix ) *current, int32_t count );

/**
   Queue_keep_and_dispose

   Remove items from queue to leave count items in queue.

   @param  current Queue_t instance
   @param  count how many items to leave
*/
#define Queue_keep_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_keep_and_dispose )
void Queue_keep_and_dispose( Prefix )( Queue_type( Prefix ) *current, int32_t count );

/**
   Queue_wipe_out

   Remove all items from queue.

   @param  current Queue_t instance
*/
#define Queue_wipe_out( arg ) PRIMITIVE_CAT( arg, _queue_wipe_out )
void Queue_wipe_out( Prefix )( Queue_type( Prefix ) *current );

/**
   Queue_wipe_out_and_dispose

   Remove all items from queue. Dipose of removed values.

   @param  current Queue_t instance
*/
#define Queue_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_wipe_out_and_dispose )
void Queue_wipe_out_and_dispose( Prefix )( Queue_type( Prefix ) *current );

/* End of file */




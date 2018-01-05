/**
 @file Queue.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Queues (stack that can be added to on one end and popped on the other)"
 
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


/** 
   Initialization
*/

/**
   Queue_make
   
   Return a new empty Queue_t instance.
   
   @return Queue_t instance 
*/
#define Queue_make( arg ) PRIMITIVE_CAT( arg, _queue_make )
Queue_type( Prefix ) * Queue_make( Prefix )( void );

/**
   Disposal
*/

/**
   Queue_dispose
   
   Free a Queue_t instance. The value items are not disposed.
   
   @param  queue Queue_t instance 
*/
#define Queue_dispose( arg ) PRIMITIVE_CAT( arg, _queue_dispose )
void Queue_dispose( Prefix )( Queue_type( Prefix ) *queue );

/**
   Queue_dispose_with_contents
   
   Free a Queue_t instance. The value items are disposed.
   
   @param  queue Queue_t instance 
*/
#define Queue_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _queue_dispose_with_contents )
void Queue_dispose_with_contents( Prefix )( Queue_type( Prefix ) *queue );

/** 
   Access
*/

/**
   Queue_item
   
   Return the value of the top of the queue.
   
   @param  queue Queue_t instance 
   @return the value of the item at the top of the queue
*/
#define Queue_item( arg ) PRIMITIVE_CAT( arg, _queue_item )
Type Queue_item( Prefix )( Queue_type( Prefix ) *queue );

/** 
   Measurement
*/

/**
   Queue_count
   
   Return the number of items in the queue.
   
   @param  queue Queue_t instance 
   @return the number of items in the queue
*/
#define Queue_count( arg ) PRIMITIVE_CAT( arg, _queue_count )
Type Queue_count( Prefix )( Queue_type( Prefix ) *queue );


/** 
   Status report
*/

/**
   Queue_is_empty
   
   Returns 1 if the queue contains no items.
   
   @param  queue Queue_t instance 
   @return 1 if queue is empty, 0 otherwise
*/
#define Queue_is_empty( arg ) PRIMITIVE_CAT( arg, _queue_is_empty )
int32_t Queue_is_empty( Prefix )( Queue_type( Prefix ) *queue );


/** 
   Element change
*/

/**
   Queue_put
   
   Insert new value at bottom of queue.
   
   @param  queue Queue_t instance 
   @param  value what to insert
*/
#define Queue_put( arg ) PRIMITIVE_CAT( arg, _queue_put )
void Queue_put( Prefix )( Queue_type( Prefix ) *queue, Type value );

/**
   Removal
*/

/**
   Queue_remove
   
   Remove value at top of queue.
   
   @param  queue Queue_t instance 
*/
#define Queue_remove( arg ) PRIMITIVE_CAT( arg, _queue_remove )
void Queue_remove( Prefix )( Queue_type( Prefix ) *queue );

/**
   Queue_remove_and_dispose
   
   Remove value at top of queue. Dipose of removed value.
   
   @param  queue Queue_t instance 
*/
#define Queue_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_remove_and_dispose )
void Queue_remove_and_dispose( Prefix )( Queue_type( Prefix ) *queue );

/**
   Queue_prune
   
   Remove count items from queue. 
   
   @param  queue Queue_t instance 
   @param  count how many items to prune
*/
#define Queue_prune( arg ) PRIMITIVE_CAT( arg, _queue_prune )
void Queue_prune( Prefix )( Queue_type( Prefix ) *queue, int32_t count );

/**
   Queue_prune_and_dispose
   
   Remove count items from queue.Dipose of removed values.
   
   @param  queue Queue_t instance 
   @param  count how many items to prune
*/
#define Queue_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_prune_and_dispose )
void Queue_prune_and_dispose( Prefix )( Queue_type( Prefix ) *queue, int32_t count );

/**
   Queue_keep
   
   Remove items from queue to leave count items in queue.
   
   @param  queue Queue_t instance 
   @param  count how many items to leave
*/
#define Queue_keep( arg ) PRIMITIVE_CAT( arg, _queue_keep )
void Queue_keep( Prefix )( Queue_type( Prefix ) *queue, int32_t count );

/**
   Queue_keep_and_dispose
   
   Remove items from queue to leave count items in queue.
   
   @param  queue Queue_t instance 
   @param  count how many items to leave
*/
#define Queue_keep_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_keep_and_dispose )
void Queue_keep_and_dispose( Prefix )( Queue_type( Prefix ) *queue, int32_t count );

/**
   Queue_wipe_out
   
   Remove all items from queue.
   
   @param  queue Queue_t instance 
*/
#define Queue_wipe_out( arg ) PRIMITIVE_CAT( arg, _queue_wipe_out )
void Queue_wipe_out( Prefix )( Queue_type( Prefix ) *queue );

/**
   Queue_wipe_out_and_dispose
   
   Remove all items from queue. Dipose of removed values.
   
   @param  queue Queue_t instance 
*/
#define Queue_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _queue_wipe_out_and_dispose )
void Queue_wipe_out_and_dispose( Prefix )( Queue_type( Prefix ) *queue );



/* End of file */




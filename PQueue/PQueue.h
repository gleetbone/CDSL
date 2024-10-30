/**
 @file PQueue.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Priority Queues"

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

 Function declarations for the opaque PQueue_t type.

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
   VALUE_ORDER_FUNCTION    -  compares two values for priority order

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define PQueue_struct( arg ) PRIMITIVE_CAT( arg, _pqueue_struct )
#define PQueue_type( arg ) PRIMITIVE_CAT( arg, _pqueue_t )
#define PQueue_name( arg ) PRIMITIVE_CAT( arg, _pqueue )

/**
   Structure declarations
*/

struct PQueue_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct PQueue_struct( Prefix ) PQueue_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/


/**
   Initialization
*/

/**
   PQueue_make

   Return a new empty PQueue_t instance.

   @return PQueue_t instance
*/
#define PQueue_make( arg ) PRIMITIVE_CAT( arg, _pqueue_make )
PQueue_type( Prefix ) * PQueue_make( Prefix )( void );

/**
   Disposal
*/

/**
   PQueue_dispose

   Free a PQueue_t instance. The value items are not disposed.

   @param  PQueue PQueue_t instance
*/
#define PQueue_dispose( arg ) PRIMITIVE_CAT( arg, _pqueue_dispose )
void PQueue_dispose( Prefix )( PQueue_type( Prefix ) **current );

/**
   PQueue_deep_dispose

   Free a PQueue_t instance. The value items are disposed.

   @param  PQueue PQueue_t instance
*/
#define PQueue_deep_dispose( arg ) PRIMITIVE_CAT( arg, _pqueue_deep_dispose )
void PQueue_deep_dispose( Prefix )( PQueue_type( Prefix ) **current );

/**
   Access
*/

/**
   PQueue_item

   Return the value of the top of the PQueue.

   @param  PQueue PQueue_t instance
   @return the value of the item at the top of the PQueue
*/
#define PQueue_item( arg ) PRIMITIVE_CAT( arg, _pqueue_item )
Type PQueue_item( Prefix )( PQueue_type( Prefix ) *current );

/**
   Measurement
*/

/**
   PQueue_count

   Return the number of items in the PQueue.

   @param  PQueue PQueue_t instance
   @return the number of items in the PQueue
*/
#define PQueue_count( arg ) PRIMITIVE_CAT( arg, _pqueue_count )
Type PQueue_count( Prefix )( PQueue_type( Prefix ) *current );


/**
   Status report
*/

/**
   PQueue_is_empty

   Returns 1 if the PQueue contains no items.

   @param  PQueue PQueue_t instance
   @return 1 if PQueue is empty, 0 otherwise
*/
#define PQueue_is_empty( arg ) PRIMITIVE_CAT( arg, _pqueue_is_empty )
int32_t PQueue_is_empty( Prefix )( PQueue_type( Prefix ) *current );


/**
   Element change
*/

/**
   PQueue_put

   Insert new value at bottom of PQueue.

   @param  PQueue PQueue_t instance
   @param  value what to insert
*/
#define PQueue_put( arg ) PRIMITIVE_CAT( arg, _pqueue_put )
void PQueue_put( Prefix )( PQueue_type( Prefix ) *current, Type value );

/**
   Removal
*/

/**
   PQueue_remove

   Remove value at top of PQueue.

   @param  PQueue PQueue_t instance
*/
#define PQueue_remove( arg ) PRIMITIVE_CAT( arg, _pqueue_remove )
void PQueue_remove( Prefix )( PQueue_type( Prefix ) *current );

/**
   PQueue_remove_and_dispose

   Remove value at top of PQueue. Dipose of removed value.

   @param  PQueue PQueue_t instance
*/
#define PQueue_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _pqueue_remove_and_dispose )
void PQueue_remove_and_dispose( Prefix )( PQueue_type( Prefix ) *current );

/**
   PQueue_prune

   Remove count items from PQueue.

   @param  PQueue PQueue_t instance
   @param  count how many items to prune
*/
#define PQueue_prune( arg ) PRIMITIVE_CAT( arg, _pqueue_prune )
void PQueue_prune( Prefix )( PQueue_type( Prefix ) *current, int32_t count );

/**
   PQueue_prune_and_dispose

   Remove count items from PQueue.Dipose of removed values.

   @param  PQueue PQueue_t instance
   @param  count how many items to prune
*/
#define PQueue_prune_and_dispose( arg ) PRIMITIVE_CAT( arg, _pqueue_prune_and_dispose )
void PQueue_prune_and_dispose( Prefix )( PQueue_type( Prefix ) *current, int32_t count );

/**
   PQueue_keep

   Remove items from PQueue to leave count items in PQueue.

   @param  PQueue PQueue_t instance
   @param  count how many items to leave
*/
#define PQueue_keep( arg ) PRIMITIVE_CAT( arg, _pqueue_keep )
void PQueue_keep( Prefix )( PQueue_type( Prefix ) *current, int32_t count );

/**
   PQueue_keep_and_dispose

   Remove items from PQueue to leave count items in PQueue.

   @param  PQueue PQueue_t instance
   @param  count how many items to leave
*/
#define PQueue_keep_and_dispose( arg ) PRIMITIVE_CAT( arg, _pqueue_keep_and_dispose )
void PQueue_keep_and_dispose( Prefix )( PQueue_type( Prefix ) *current, int32_t count );

/**
   PQueue_wipe_out

   Remove all items from PQueue.

   @param  PQueue PQueue_t instance
*/
#define PQueue_wipe_out( arg ) PRIMITIVE_CAT( arg, _pqueue_wipe_out )
void PQueue_wipe_out( Prefix )( PQueue_type( Prefix ) *current );

/**
   PQueue_wipe_out_and_dispose

   Remove all items from PQueue. Dipose of removed values.

   @param  PQueue PQueue_t instance
*/
#define PQueue_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _pqueue_wipe_out_and_dispose )
void PQueue_wipe_out_and_dispose( Prefix )( PQueue_type( Prefix ) *current );



/* End of file */




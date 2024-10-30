/**
 @file P_Indexable.h
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Indexable protocol"

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

 Function declarations for the P_Indexable protocol.

*/

#include "base.h"
#include "Protocol_Base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Type   - the type of the value

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

/**
   Includes
*/

/**
   p_indexable_count

   returns number of elements in the p_indexable

   @param p_indexable the pointer to the indexable struct
   @return the number of elemements in the p_indexable
*/
#define P_Indexable_count( arg ) PRIMITIVE_CAT( arg, _indexable_count )
int32_t
P_Indexable_count( Prefix )
(
   protocol_base_t *p_indexable
);

/**
   p_indexable_item

   returns value at index in the p_indexable

   @param p_indexable the pointer to the protocol base struct
   @param index the index to look at in p_indexable
   @return the value at index in p_indexable
*/
#define P_Indexable_item( arg ) PRIMITIVE_CAT( arg, _indexable_item )
Type
P_Indexable_item( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t index
);

/**
   p_indexable_put

   puts value at index in p_indexable
   original item is overwritten and not disposed

   @param p_indexable the pointer to the protocol base struct
   @param value the value to put at index
   @param index the index to place value ( 0 to count-1 )
*/
#define P_Indexable_put( arg ) PRIMITIVE_CAT( arg, _indexable_put )
void
P_Indexable_put( Prefix )
(
   protocol_base_t *p_indexable,
   Type value,
   int32_t index
);

/**
   p_indexable_put_and_dispose

   puts value at index in p_indexable
   original item is overwritten and disposed

   @param p_indexable the pointer to the protocol base struct
   @param value the value to put at index
   @param index the index to place value ( 0 to count-1 )
*/
#define P_Indexable_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _indexable_put_and_dispose )
void
P_Indexable_put_and_dispose( Prefix )
(
   protocol_base_t *p_indexable,
   Type value,
   int32_t index
);

/* End of file */





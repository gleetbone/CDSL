/**
 @file P_Sorter.c
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Sorter protocol"

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

 Function definitions for the p_sorter protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Sorter.h"
#include "P_Sorter.ph"
#include "P_Indexable.ph"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_sorter_sort
*/
void
P_Sorter_sort( Prefix )
(
   protocol_base_t *p_sorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "p_sorter not null", p_sorter != NULL );
   PRECONDITION( "p_sorter is object", protocol_base_is_valid_object( p_sorter ) == 1 );
   PRECONDITION( "p_sorter supports protocol", protocol_base_supports_protocol( p_sorter, P_SORTER_TYPE ) == 1 );
   PRECONDITION( "p_indexable not null", p_sorter != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   void (*sort)( protocol_base_t *, protocol_base_t * )
      = ( *p_sorter ).get_function( P_SORTER_TYPE, P_SORTER_SORT );

   CHECK( "P_SORTER_SORT function not null", sort != NULL );

   sort( p_sorter, p_indexable );

   return;
}

/**
   p_sorter_is_sorted
*/
int32_t
P_Sorter_is_sorted( Prefix )
(
   protocol_base_t *p_sorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "p_sorter not null", p_sorter != NULL );
   PRECONDITION( "p_sorter is object", protocol_base_is_valid_object( p_sorter ) == 1 );
   PRECONDITION( "p_sorter supports protocol", protocol_base_supports_protocol( p_sorter, P_SORTER_TYPE ) == 1 );
   PRECONDITION( "p_indexable not null", p_sorter != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t result = 0;

   int32_t ( *is_sorted )( protocol_base_t *, protocol_base_t * )
      = ( *p_sorter ).get_function( P_SORTER_TYPE, P_SORTER_IS_SORTED );

   CHECK( "P_SORTER_SORT function not null", is_sorted != NULL );

   result = is_sorted( p_sorter, p_indexable );

   return result;
}

/* End of file */





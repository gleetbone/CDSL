/**
 @file P_Searcher.c
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Searcher protocol"
 
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

 Function definitions for the p_searcher protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Searcher.h"
#include "P_Searcher.ph"
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
   p_searcher_dispose
*/
void
P_Searcher_dispose( Prefix )
(
   protocol_base_t *p_searcher
)
{
   PRECONDITION( "p_searcher not null", p_searcher != NULL );
   PRECONDITION( "p_searcher is object", protocol_base_is_valid_object( p_searcher ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_searcher).get_function( P_SEARCHER, P_SEARCHER_DISPOSE );

   CHECK( "P_SEARCHER_DISPOSE function not null", dispose != NULL );

   dispose( p_searcher );

   return;
}

/**
   p_searcher_dispose_f
*/
searcher_dispose_f
P_Searcher_dispose_f( Prefix )
(
   protocol_base_t *p_searcher
)
{
   PRECONDITION( "p_searcher not null", p_searcher != NULL );
   PRECONDITION( "p_searcher is object", protocol_base_is_valid_object( p_searcher ) == 1 );
   PRECONDITION( "p_searcher supports protocol", protocol_base_supports_protocol( p_searcher, P_SEARCHER ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_searcher).get_function( P_SEARCHER, P_SEARCHER_DISPOSE );

   CHECK( "P_SEARCHER_DISPOSE function not null", dispose != NULL );

   return dispose;
}

/**
   p_searcher_search
*/
int32_t
P_Searcher_search( Prefix )
(
   protocol_base_t *p_searcher,
   protocol_base_t *p_indexable,
   Type target
)
{
   PRECONDITION( "p_searcher not null", p_searcher != NULL );
   PRECONDITION( "p_searcher is object", protocol_base_is_valid_object( p_searcher ) == 1 );
   PRECONDITION( "p_searcher supports protocol", protocol_base_supports_protocol( p_searcher, P_SEARCHER ) == 1 );
   PRECONDITION( "p_indexable not null", p_searcher != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );

   int32_t (*search)( protocol_base_t *, protocol_base_t *, Type target ) 
      = (*p_searcher).get_function( P_SEARCHER, P_SEARCHER_SEARCH );

   CHECK( "P_SEARCHER_SEARCH function not null", search != NULL );

   int32_t result = search( p_searcher, p_indexable, target );

   return result;
}

/**
   p_searcher_search_f
*/
searcher_search_f
P_Searcher_search_f( Prefix )
(
   protocol_base_t *p_searcher
)
{
   PRECONDITION( "p_searcher not null", p_searcher != NULL );
   PRECONDITION( "p_searcher is object", protocol_base_is_valid_object( p_searcher ) == 1 );
   PRECONDITION( "p_searcher supports protocol", protocol_base_supports_protocol( p_searcher, P_SEARCHER ) == 1 );

   int32_t (*search)( protocol_base_t *, protocol_base_t *, Type target ) 
      = (*p_searcher).get_function( P_SEARCHER, P_SEARCHER_SEARCH );

   CHECK( "P_SEARCHER_SEARCH function not null", search != NULL );

   return search;
}

/* End of file */





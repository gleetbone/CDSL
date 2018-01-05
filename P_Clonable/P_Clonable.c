/**
 @file P_Clonable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Clonable protocol"
 
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

 Function definitions for the P_Clonable protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Clonable.h"
#include "P_Clonable.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_clonable_dispose
*/
void
P_Clonable_dispose( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_DISPOSE );

   CHECK( "P_CLONABLE_DISPOSE function not null", dispose != NULL );

   dispose( p_clonable );

   return;
}

/**
   p_clonable_dispose_f
*/
clonable_dispose_f
P_Clonable_dispose_f( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_DISPOSE );

   CHECK( "P_CLONABLE_DISPOSE function not null", dispose != NULL );

   return dispose;
}

/**
   p_clonable_dispose_with_contents
*/
void
P_Clonable_dispose_with_contents( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_DISPOSE_WITH_CONTENTS );

   CHECK( "P_CLONABLE_DISPOSE function not null", dispose_with_contents != NULL );

   dispose_with_contents( p_clonable );

   return;
}

/**
   p_clonable_dispose_with_contents_f
*/
clonable_dispose_with_contents_f
P_Clonable_dispose_with_contents_f( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_DISPOSE_WITH_CONTENTS );

   CHECK( "P_CLONABLE_DISPOSE function not null", dispose_with_contents != NULL );
   
   return dispose_with_contents;
}

/**
   p_clonable_clone
*/
protocol_base_t *
P_Clonable_clone( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   protocol_base_t * (*clone)( protocol_base_t * ) 
      = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_CLONE );

   CHECK( "P_CLONABLE_CLONE function not null", clone != NULL );

   protocol_base_t *result = clone( p_clonable );

   return result;
}

/**
   p_clonable_clone_f
*/
clonable_clone_f
P_Clonable_clone_f( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   protocol_base_t * (*clone)( protocol_base_t * ) 
      = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_CLONE );

   CHECK( "P_CLONABLE_CLONE function not null", clone != NULL );

   return clone;
}

/**
   p_clonable_deep_clone
*/
protocol_base_t *
P_Clonable_deep_clone( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   protocol_base_t * (*deep_clone)( protocol_base_t * ) 
      = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_DEEP_CLONE );

   CHECK( "P_CLONABLE_DEEP_CLONE function not null", deep_clone != NULL );

   protocol_base_t *result = deep_clone( p_clonable );

   return result;
}

/**
   p_clonable_deep_clone_f
*/
clonable_deep_clone_f
P_Clonable_deep_clone_f( Prefix )
(
   protocol_base_t *p_clonable
)
{
   PRECONDITION( "p_clonable not null", p_clonable != NULL );
   PRECONDITION( "p_clonable is object", protocol_base_is_valid_object( p_clonable ) == 1 );
   PRECONDITION( "p_clonable supports protocol", protocol_base_supports_protocol( p_clonable, P_CLONABLE ) == 1 );

   protocol_base_t * (*deep_clone)( protocol_base_t * ) 
      = (*p_clonable).get_function( P_CLONABLE, P_CLONABLE_DEEP_CLONE );

   CHECK( "P_CLONABLE_DEEP_CLONE function not null", deep_clone != NULL );

   return deep_clone;
}


/* End of file */





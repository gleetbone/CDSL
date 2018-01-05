/**
 @file P_Searcher.h
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

 Function declarations for the p_searcher protocol.

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
   p_searcher_dispose

   dispose of p_searcher

   @param p_searcher the pointer to the p_searcher
*/
#define P_Searcher_dispose( arg ) PRIMITIVE_CAT( arg, _searcher_dispose )
void 
P_Searcher_dispose( Prefix )
(
   protocol_base_t *p_searcher
);

/**
   p_searcher_dispose_f

   returns function to dispose of p_searcher

   @param p_searcher the pointer to the p_searcher
   @return the function
*/
typedef void (*searcher_dispose_f)( protocol_base_t *p_searcher );
#define P_Searcher_dispose_f( arg ) PRIMITIVE_CAT( arg, _searcher_dispose_f )
searcher_dispose_f
P_Searcher_dispose_f( Prefix )
(
   protocol_base_t *p_searcher
);

/**
   p_searcher_search

   searches p_indexable

   @param p_searcher the pointer to the searcher
   @param p_indexable the pointer to the indexable
   @param target the value to search for in the p_indexable
   @return the index of target if found, -1 otherwise
*/
#define P_Searcher_search( arg ) PRIMITIVE_CAT( arg, _searcher_search )
int32_t
P_Searcher_search( Prefix )
(
   protocol_base_t *p_searcher,
   protocol_base_t *p_indexable,
   Type target
);

/**
   p_searcher_search_f

   returns function to search p_indexable

   @param p_searcher the pointer to the protocol base struct
   @return the function
*/
typedef int32_t (*searcher_search_f)( protocol_base_t *p_searcher, protocol_base_t *p_indexable, Type target );
#define P_Searcher_search_f( arg ) PRIMITIVE_CAT( arg, _searcher_search_f )
searcher_search_f
P_Searcher_search_f( Prefix )
(
   protocol_base_t *p_searcher
);

/* End of file */





/**
 @file LSearcher.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Linear searcher"

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

 Function declarations for the opaque LSearcher_t type.

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

#define LSearcher_struct( arg ) PRIMITIVE_CAT( arg, _lsearcher_struct )
#define LSearcher_type( arg ) PRIMITIVE_CAT( arg, _lsearcher_t )
#define LSearcher_name( arg ) PRIMITIVE_CAT( arg, _lsearcher )

/**
   Structure declarations
*/

struct LSearcher_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct LSearcher_struct( Prefix ) LSearcher_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   LSearcher_make

   make a LSearcher

   @return the lsearcher
*/
#define LSearcher_make( arg ) PRIMITIVE_CAT( arg, _lsearcher_make )
LSearcher_type( Prefix ) *
LSearcher_make( Prefix )( void );

/**
   LSearcher_clone

   clone a LSearcher

   @return the lsearcher
*/
#define LSearcher_clone( arg ) PRIMITIVE_CAT( arg, _lsearcher_clone )
LSearcher_type( Prefix ) *
LSearcher_clone( Prefix )( LSearcher_type( Prefix ) *other );

/**
   LSearcher_deep_clone

   deep_clone a LSearcher

   @return the lsearcher
*/
#define LSearcher_deep_clone( arg ) PRIMITIVE_CAT( arg, _lsearcher_deep_clone )
LSearcher_type( Prefix ) *
LSearcher_deep_clone( Prefix )( LSearcher_type( Prefix ) *other );

/**
   LSearcher_is_equal

   is_equal a LSearcher

   @return the lsearcher
*/
#define LSearcher_is_equal( arg ) PRIMITIVE_CAT( arg, _lsearcher_is_equal )
int32_t
LSearcher_is_equal( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other );

/**
   LSearcher_is_equal

   check is_equal for two LSearchers

   @return the lsearcher
*/
#define LSearcher_is_equal( arg ) PRIMITIVE_CAT( arg, _lsearcher_is_equal )
int32_t
LSearcher_is_equal( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other );

/**
   LSearcher_is_deep_equal

   check is_deep_equal for two LSearchers

   @return the lsearcher
*/
#define LSearcher_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _lsearcher_is_deep_equal )
int32_t
LSearcher_is_deep_equal( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other );

/**
   LSearcher_copy

   copy a LSearcher into another

   @return the lsearcher
*/
#define LSearcher_copy( arg ) PRIMITIVE_CAT( arg, _lsearcher_copy )
void
LSearcher_copy( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other );

/**
   LSearcher_deep_copy

   deep_copy a LSearcher into another

   @return the lsearcher
*/
#define LSearcher_deep_copy( arg ) PRIMITIVE_CAT( arg, _lsearcher_deep_copy )
void
LSearcher_deep_copy( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other );

/**
   LSearcher_dispose

   dispose a LSearcher

   @param the lsearcher
*/
#define LSearcher_dispose( arg ) PRIMITIVE_CAT( arg, _lsearcher_dispose )
void
LSearcher_dispose( Prefix )( LSearcher_type( Prefix ) **current );

/**
   LSearcher_deep_dispose

   deep dispose a LSearcher

   @param the lsearcher
*/
#define LSearcher_deep_dispose( arg ) PRIMITIVE_CAT( arg, _lsearcher_deep_dispose )
void
LSearcher_deep_dispose( Prefix )( LSearcher_type( Prefix ) **current );

/**
   LSearcher_search_predefined_comparison_function

   search an entire p_indexable with the predefined comparison function
   the p_indexable must have been sorted with the predefined comparison function

   @param lsearcher the lsearcher
   @param p_indexable the pointer to the p_indexable
   @param target the value to search for
   @return the index in p_indexable of the found item, -1 if not found
*/
#define LSearcher_search_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _lsearcher_search_predefined_comparison_function )
int32_t
LSearcher_search_predefined_comparison_function( Prefix )
(
   LSearcher_type( Prefix ) *lsearcher,
   protocol_base_t *p_indexable,
   Type target
);

/**
   LSearcher_search

   search an entire p_indexable
   note that this function can be called without making a lsearcher

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
   @return the index in p_indexable of the found item, -1 if not found
*/
#define LSearcher_search( arg ) PRIMITIVE_CAT( arg, _lsearcher_search )
int32_t
LSearcher_search( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   Type target
);

/* End of file */





/**
 @file BSearcher.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Binary Searcher"

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

 Function declarations for the opaque BSearcher_t type.

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

#define BSearcher_struct( arg ) PRIMITIVE_CAT( arg, _bsearcher_struct )
#define BSearcher_type( arg ) PRIMITIVE_CAT( arg, _bsearcher_t )
#define BSearcher_name( arg ) PRIMITIVE_CAT( arg, _bsearcher )

/**
   Structure declarations
*/

struct BSearcher_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct BSearcher_struct( Prefix ) BSearcher_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   BSearcher_make

   make a BSearcher

   @return the bsearcher
*/
#define BSearcher_make( arg ) PRIMITIVE_CAT( arg, _bsearcher_make )
BSearcher_type( Prefix ) *
BSearcher_make( Prefix )( void );

/**
   BSearcher_clone

   clone a BSearcher

   @return the bsearcher
*/
#define BSearcher_clone( arg ) PRIMITIVE_CAT( arg, _bsearcher_clone )
BSearcher_type( Prefix ) *
BSearcher_clone( Prefix )( BSearcher_type( Prefix ) *other );

/**
   BSearcher_deep_clone

   deep_clone a BSearcher

   @return the bsearcher
*/
#define BSearcher_deep_clone( arg ) PRIMITIVE_CAT( arg, _bsearcher_deep_clone )
BSearcher_type( Prefix ) *
BSearcher_deep_clone( Prefix )( BSearcher_type( Prefix ) *other );

/**
   BSearcher_is_equal

   is_equal a BSearcher

   @return the bsearcher
*/
#define BSearcher_is_equal( arg ) PRIMITIVE_CAT( arg, _bsearcher_is_equal )
int32_t
BSearcher_is_equal( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other );

/**
   BSearcher_is_equal

   check is_equal for two BSearchers

   @return the bsearcher
*/
#define BSearcher_is_equal( arg ) PRIMITIVE_CAT( arg, _bsearcher_is_equal )
int32_t
BSearcher_is_equal( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other );

/**
   BSearcher_is_deep_equal

   check is_deep_equal for two BSearchers

   @return the bsearcher
*/
#define BSearcher_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _bsearcher_is_deep_equal )
int32_t
BSearcher_is_deep_equal( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other );

/**
   BSearcher_copy

   copy a BSearcher into another

   @return the bsearcher
*/
#define BSearcher_copy( arg ) PRIMITIVE_CAT( arg, _bsearcher_copy )
void
BSearcher_copy( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other );

/**
   BSearcher_deep_copy

   deep_copy a BSearcher into another

   @return the bsearcher
*/
#define BSearcher_deep_copy( arg ) PRIMITIVE_CAT( arg, _bsearcher_deep_copy )
void
BSearcher_deep_copy( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other );

/**
   BSearcher_dispose

   dispose a BSearcher

   @param the bsearcher
*/
#define BSearcher_dispose( arg ) PRIMITIVE_CAT( arg, _bsearcher_dispose )
void
BSearcher_dispose( Prefix )( BSearcher_type( Prefix ) **bsearcher );

/**
   BSearcher_deep_dispose

   deep_dispose a BSearcher

   @param the bsearcher
*/
#define BSearcher_deep_dispose( arg ) PRIMITIVE_CAT( arg, _bsearcher_deep_dispose )
void
BSearcher_deep_dispose( Prefix )( BSearcher_type( Prefix ) **bsearcher );

/**
   BSearcher_search_predefined_comparison_function

   search an entire p_indexable with the predefined comparison function
   the p_indexable must have been sorted with the predefined comparison function

   @param bsearcher the bsearcher
   @param p_indexable the pointer to the p_indexable
   @param target the value to search for
   @return the index in p_indexable of the found item, -1 if not found
*/
#define BSearcher_search_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _bsearcher_search_predefined_comparison_function )
int32_t
BSearcher_search_predefined_comparison_function( Prefix )
(
   BSearcher_type( Prefix ) *bsearcher,
   protocol_base_t *p_indexable,
   Type target
);

/**
   BSearcher_search

   search an entire p_indexable
   note that this function can be called without making a bsearcher

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
   @return the index in p_indexable of the found item, -1 if not found
*/
#define BSearcher_search( arg ) PRIMITIVE_CAT( arg, _bsearcher_search )
int32_t
BSearcher_search( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   Type target
);

/* End of file */





/**
 @file BSorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Implementation of Bubble Sorter"

 @version 2.0.0
 @brief: "Bubble Sorter"

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

 Function declarations for the opaque BSorter_t type.

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

#define BSorter_struct( arg ) PRIMITIVE_CAT( arg, _bsorter_struct )
#define BSorter_type( arg ) PRIMITIVE_CAT( arg, _bsorter_t )
#define BSorter_name( arg ) PRIMITIVE_CAT( arg, _bsorter )

/**
   Structure declarations
*/

struct BSorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct BSorter_struct( Prefix ) BSorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   BSorter_make

   make a BSorter

   @return the bsorter
*/
#define BSorter_make( arg ) PRIMITIVE_CAT( arg, _bsorter_make )
BSorter_type( Prefix ) *
BSorter_make( Prefix )( void );

/**
   BSorter_clone

   clone a BSorter

   @return the bsorter
*/
#define BSorter_clone( arg ) PRIMITIVE_CAT( arg, _bsorter_clone )
BSorter_type( Prefix ) *
BSorter_clone( Prefix )( BSorter_type( Prefix ) *other );

/**
   BSorter_deep_clone

   deep_clone a BSorter

   @return the bsorter
*/
#define BSorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _bsorter_deep_clone )
BSorter_type( Prefix ) *
BSorter_deep_clone( Prefix )( BSorter_type( Prefix ) *other );

/**
   BSorter_is_equal

   is_equal a BSorter

   @return the bsorter
*/
#define BSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _bsorter_is_equal )
int32_t
BSorter_is_equal( Prefix )( BSorter_type( Prefix ) *current, BSorter_type( Prefix ) *other );

/**
   BSorter_is_equal

   check is_equal for two BSorters

   @return the bsorter
*/
#define BSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _bsorter_is_equal )
int32_t
BSorter_is_equal( Prefix )( BSorter_type( Prefix ) *current, BSorter_type( Prefix ) *other );

/**
   BSorter_is_deep_equal

   check is_deep_equal for two BSorters

   @return the bsorter
*/
#define BSorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _bsorter_is_deep_equal )
int32_t
BSorter_is_deep_equal( Prefix )( BSorter_type( Prefix ) *current, BSorter_type( Prefix ) *other );

/**
   BSorter_copy

   copy a BSorter into another

   @return the bsorter
*/
#define BSorter_copy( arg ) PRIMITIVE_CAT( arg, _bsorter_copy )
void
BSorter_copy( Prefix )( BSorter_type( Prefix ) *current, BSorter_type( Prefix ) *other );

/**
   BSorter_deep_copy

   deep_copy a BSorter into another

   @return the bsorter
*/
#define BSorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _bsorter_deep_copy )
void
BSorter_deep_copy( Prefix )( BSorter_type( Prefix ) *current, BSorter_type( Prefix ) *other );

/**
   BSorter_dispose

   dispose a BSorter

   @param the bsorter
*/
#define BSorter_dispose( arg ) PRIMITIVE_CAT( arg, _bsorter_dispose )
void
BSorter_dispose( Prefix )( BSorter_type( Prefix ) **current );

/**
   BSorter_deep_dispose

   deep dispose a BSorter

   @param the bsorter
*/
#define BSorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _bsorter_deep_dispose )
void
BSorter_deep_dispose( Prefix )( BSorter_type( Prefix ) **current );

/**
   BSorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param bsorter the bsorter
   @param p_indexable the pointer to the p_indexable
*/
#define BSorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _bsorter_sort_predefined_comparison_function )
void
BSorter_sort_predefined_comparison_function( Prefix )
(
   BSorter_type( Prefix ) *bsorter,
   protocol_base_t *p_indexable
);

/**
   BSorter_sort

   sort an entire p_indexable
   note that this function can be called without making a bsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define BSorter_sort( arg ) PRIMITIVE_CAT( arg, _bsorter_sort )
void
BSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   BSorter_is_sorted_predefined_comparison_function

   return 1 if p_indexable is in order
   note that this function can be called without making a bsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define BSorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _bsorter_is_sorted_predefined_comparison_function )
int32_t
BSorter_is_sorted_predefined_comparison_function( Prefix )
(
   BSorter_type( Prefix ) *bsorter,
   protocol_base_t *p_indexable
);

/**
   BSorter_is_sorted

   return 1 if p_indexable is in order
   note that this function can be called without making a bsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define BSorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _bsorter_is_sorted )
int32_t
BSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





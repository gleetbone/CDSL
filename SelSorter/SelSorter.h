/**
 @file SelSorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Selection Sorter"

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

 Function declarations for the opaque SelSorter_t type.

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

#define SelSorter_struct( arg ) PRIMITIVE_CAT( arg, _selsorter_struct )
#define SelSorter_type( arg ) PRIMITIVE_CAT( arg, _selsorter_t )
#define SelSorter_name( arg ) PRIMITIVE_CAT( arg, _selsorter )

/**
   Structure declarations
*/

struct SelSorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct SelSorter_struct( Prefix ) SelSorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   SelSorter_make

   make a SelSorter

   @return the selsorter
*/
#define SelSorter_make( arg ) PRIMITIVE_CAT( arg, _selsorter_make )
SelSorter_type( Prefix ) *
SelSorter_make( Prefix )( void );

/**
   SelSorter_clone

   clone a SelSorter

   @return the selsorter
*/
#define SelSorter_clone( arg ) PRIMITIVE_CAT( arg, _selsorter_clone )
SelSorter_type( Prefix ) *
SelSorter_clone( Prefix )( SelSorter_type( Prefix ) *other );

/**
   SelSorter_deep_clone

   deep_clone a SelSorter

   @return the selsorter
*/
#define SelSorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _selsorter_deep_clone )
SelSorter_type( Prefix ) *
SelSorter_deep_clone( Prefix )( SelSorter_type( Prefix ) *other );

/**
   SelSorter_is_equal

   is_equal a SelSorter

   @return the selsorter
*/
#define SelSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _selsorter_is_equal )
int32_t
SelSorter_is_equal( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other );

/**
   SelSorter_is_equal

   check is_equal for two SelSorters

   @return the selsorter
*/
#define SelSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _selsorter_is_equal )
int32_t
SelSorter_is_equal( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other );

/**
   SelSorter_is_deep_equal

   check is_deep_equal for two SelSorters

   @return the selsorter
*/
#define SelSorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _selsorter_is_deep_equal )
int32_t
SelSorter_is_deep_equal( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other );

/**
   SelSorter_copy

   copy a SelSorter into another

   @return the selsorter
*/
#define SelSorter_copy( arg ) PRIMITIVE_CAT( arg, _selsorter_copy )
void
SelSorter_copy( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other );

/**
   SelSorter_deep_copy

   deep_copy a SelSorter into another

   @return the selsorter
*/
#define SelSorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _selsorter_deep_copy )
void
SelSorter_deep_copy( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other );

/**
   SelSorter_dispose

   dispose a SelSorter

   @param the selsorter
*/
#define SelSorter_dispose( arg ) PRIMITIVE_CAT( arg, _selsorter_dispose )
void
SelSorter_dispose( Prefix )( SelSorter_type( Prefix ) **selsorter );

/**
   SelSorter_deep_dispose

   deep dispose a SelSorter

   @param the selsorter
*/
#define SelSorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _selsorter_deep_dispose )
void
SelSorter_deep_dispose( Prefix )( SelSorter_type( Prefix ) **current );

/**
   SelSorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param current the selsorter
   @param p_indexable the pointer to the p_indexable
*/
#define SelSorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _selsorter_sort_predefined_comparison_function )
void
SelSorter_sort_predefined_comparison_function( Prefix )
(
   SelSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   SelSorter_sort

   sort an entire p_indexable
   note that this function can be called without making a selsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define SelSorter_sort( arg ) PRIMITIVE_CAT( arg, _selsorter_sort )
void
SelSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   SelSorter_is_sorted_predefined_comparison_function

   return 1 if p_indexable is in order
   note that this function can be called without making a selsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define SelSorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _selsorter_is_sorted_predefined_comparison_function )
int32_t
SelSorter_is_sorted_predefined_comparison_function( Prefix )
(
   SelSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   SelSorter_is_sorted

   return 1 if p_indexable is in order
   note that this function can be called without making a selsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define SelSorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _selsorter_is_sorted )
int32_t
SelSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





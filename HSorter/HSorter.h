/**
 @file HSorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Heap Sorter"

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

 Function declarations for the opaque HSorter_t type.

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

#define HSorter_struct( arg ) PRIMITIVE_CAT( arg, _hsorter_struct )
#define HSorter_type( arg ) PRIMITIVE_CAT( arg, _hsorter_t )
#define HSorter_name( arg ) PRIMITIVE_CAT( arg, _hsorter )

/**
   Structure declarations
*/

struct HSorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct HSorter_struct( Prefix ) HSorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   HSorter_make

   make a HSorter

   @return the hsorter
*/
#define HSorter_make( arg ) PRIMITIVE_CAT( arg, _hsorter_make )
HSorter_type( Prefix ) *
HSorter_make( Prefix )( void );

/**
   HSorter_clone

   clone a HSorter

   @return the hsorter
*/
#define HSorter_clone( arg ) PRIMITIVE_CAT( arg, _hsorter_clone )
HSorter_type( Prefix ) *
HSorter_clone( Prefix )( HSorter_type( Prefix ) *other );

/**
   HSorter_deep_clone

   deep_clone a HSorter

   @return the hsorter
*/
#define HSorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _hsorter_deep_clone )
HSorter_type( Prefix ) *
HSorter_deep_clone( Prefix )( HSorter_type( Prefix ) *other );

/**
   HSorter_is_equal

   is_equal a HSorter

   @return the hsorter
*/
#define HSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _hsorter_is_equal )
int32_t
HSorter_is_equal( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other );

/**
   HSorter_is_equal

   check is_equal for two HSorters

   @return the hsorter
*/
#define HSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _hsorter_is_equal )
int32_t
HSorter_is_equal( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other );

/**
   HSorter_is_deep_equal

   check is_deep_equal for two HSorters

   @return the hsorter
*/
#define HSorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _hsorter_is_deep_equal )
int32_t
HSorter_is_deep_equal( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other );

/**
   HSorter_copy

   copy a HSorter into another

   @return the hsorter
*/
#define HSorter_copy( arg ) PRIMITIVE_CAT( arg, _hsorter_copy )
void
HSorter_copy( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other );

/**
   HSorter_deep_copy

   deep_copy a HSorter into another

   @return the hsorter
*/
#define HSorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _hsorter_deep_copy )
void
HSorter_deep_copy( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other );

/**
   HSorter_dispose

   dispose a HSorter

   @param the hsorter
*/
#define HSorter_dispose( arg ) PRIMITIVE_CAT( arg, _hsorter_dispose )
void
HSorter_dispose( Prefix )( HSorter_type( Prefix ) **hsorter );

/**
   HSorter_deep_dispose

   deep dispose a HSorter

   @param the hsorter
*/
#define HSorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _hsorter_deep_dispose )
void
HSorter_deep_dispose( Prefix )( HSorter_type( Prefix ) **current );

/**
   HSorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param hsorter the hsorter
   @param p_indexable the pointer to the p_indexable
*/
#define HSorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _hsorter_sort_predefined_comparison_function )
void
HSorter_sort_predefined_comparison_function( Prefix )
(
   HSorter_type( Prefix ) *hsorter,
   protocol_base_t *p_indexable
);

/**
   HSorter_sort

   sort an entire p_indexable
   note that this function can be called without making a hsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define HSorter_sort( arg ) PRIMITIVE_CAT( arg, _hsorter_sort )
void
HSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   HSorter_is_sorted_predefined_comparison_function

   return 1 if p_indexable is in order
   note that this function can be called without making a hsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define HSorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _hsorter_is_sorted_predefined_comparison_function )
int32_t
HSorter_is_sorted_predefined_comparison_function( Prefix )
(
   HSorter_type( Prefix ) *hsorter,
   protocol_base_t *p_indexable
);

/**
   HSorter_is_sorted

   return 1 if p_indexable is in order
   note that this function can be called without making a hsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define HSorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _hsorter_is_sorted )
int32_t
HSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





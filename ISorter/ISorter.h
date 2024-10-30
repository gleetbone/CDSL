/**
 @file ISorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Insertion Sorter"

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

 Function declarations for the opaque ISorter_t type.

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

#define ISorter_struct( arg ) PRIMITIVE_CAT( arg, _isorter_struct )
#define ISorter_type( arg ) PRIMITIVE_CAT( arg, _isorter_t )
#define ISorter_name( arg ) PRIMITIVE_CAT( arg, _isorter )

/**
   Structure declarations
*/

struct ISorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct ISorter_struct( Prefix ) ISorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   ISorter_make

   make a ISorter

   @return the isorter
*/
#define ISorter_make( arg ) PRIMITIVE_CAT( arg, _isorter_make )
ISorter_type( Prefix ) *
ISorter_make( Prefix )( void );

/**
   ISorter_clone

   clone a ISorter

   @return the isorter
*/
#define ISorter_clone( arg ) PRIMITIVE_CAT( arg, _isorter_clone )
ISorter_type( Prefix ) *
ISorter_clone( Prefix )( ISorter_type( Prefix ) *other );

/**
   ISorter_deep_clone

   deep_clone a ISorter

   @return the isorter
*/
#define ISorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _isorter_deep_clone )
ISorter_type( Prefix ) *
ISorter_deep_clone( Prefix )( ISorter_type( Prefix ) *other );

/**
   ISorter_is_equal

   is_equal a ISorter

   @return the isorter
*/
#define ISorter_is_equal( arg ) PRIMITIVE_CAT( arg, _isorter_is_equal )
int32_t
ISorter_is_equal( Prefix )( ISorter_type( Prefix ) *current, ISorter_type( Prefix ) *other );

/**
   ISorter_is_equal

   check is_equal for two ISorters

   @return the isorter
*/
#define ISorter_is_equal( arg ) PRIMITIVE_CAT( arg, _isorter_is_equal )
int32_t
ISorter_is_equal( Prefix )( ISorter_type( Prefix ) *current, ISorter_type( Prefix ) *other );

/**
   ISorter_is_deep_equal

   check is_deep_equal for two ISorters

   @return the isorter
*/
#define ISorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _isorter_is_deep_equal )
int32_t
ISorter_is_deep_equal( Prefix )( ISorter_type( Prefix ) *current, ISorter_type( Prefix ) *other );

/**
   ISorter_copy

   copy a ISorter into another

   @return the isorter
*/
#define ISorter_copy( arg ) PRIMITIVE_CAT( arg, _isorter_copy )
void
ISorter_copy( Prefix )( ISorter_type( Prefix ) *current, ISorter_type( Prefix ) *other );

/**
   ISorter_deep_copy

   deep_copy a ISorter into another

   @return the isorter
*/
#define ISorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _isorter_deep_copy )
void
ISorter_deep_copy( Prefix )( ISorter_type( Prefix ) *current, ISorter_type( Prefix ) *other );

/**
   ISorter_dispose

   dispose a ISorter

   @param the isorter
*/
#define ISorter_dispose( arg ) PRIMITIVE_CAT( arg, _isorter_dispose )
void
ISorter_dispose( Prefix )( ISorter_type( Prefix ) **isorter );

/**
   ISorter_deep_dispose

   deep dispose a ISorter

   @param the isorter
*/
#define ISorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _isorter_deep_dispose )
void
ISorter_deep_dispose( Prefix )( ISorter_type( Prefix ) **current );

/**
   ISorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param isorter the isorter
   @param p_indexable the pointer to the p_indexable
*/
#define ISorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _isorter_sort_predefined_comparison_function )
void
ISorter_sort_predefined_comparison_function( Prefix )
(
   ISorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   ISorter_sort

   sort an entire p_indexable
   note that this function can be called without making a isorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define ISorter_sort( arg ) PRIMITIVE_CAT( arg, _isorter_sort )
void
ISorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   ISorter_is_sorted_predefined_comparison_function

   return 1 if p_indexable is in order
   note that this function can be called without making a isorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define ISorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _isorter_is_sorted_predefined_comparison_function )
int32_t
ISorter_is_sorted_predefined_comparison_function( Prefix )
(
   ISorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   ISorter_is_sorted

   return 1 if p_indexable is in order
   note that this function can be called without making a isorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define ISorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _isorter_is_sorted )
int32_t
ISorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





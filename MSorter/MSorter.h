/**
 @file MSorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Merge Sorter"

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

 Function declarations for the opaque MSorter_t type.

*/

/**
   Includes
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

#define MSorter_struct( arg ) PRIMITIVE_CAT( arg, _msorter_struct )
#define MSorter_type( arg ) PRIMITIVE_CAT( arg, _msorter_t )
#define MSorter_name( arg ) PRIMITIVE_CAT( arg, _msorter )

/**
   Structure declarations
*/

struct MSorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct MSorter_struct( Prefix ) MSorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/*
   Function
*/

/**
   MSorter_make

   make a MSorter

   @return the msorter
*/
#define MSorter_make( arg ) PRIMITIVE_CAT( arg, _msorter_make )
MSorter_type( Prefix ) *
MSorter_make( Prefix )( void );

/**
   MSorter_clone

   clone a MSorter

   @return the msorter
*/
#define MSorter_clone( arg ) PRIMITIVE_CAT( arg, _msorter_clone )
MSorter_type( Prefix ) *
MSorter_clone( Prefix )( MSorter_type( Prefix ) *other );

/**
   MSorter_deep_clone

   deep_clone a MSorter

   @return the msorter
*/
#define MSorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _msorter_deep_clone )
MSorter_type( Prefix ) *
MSorter_deep_clone( Prefix )( MSorter_type( Prefix ) *other );

/**
   MSorter_is_equal

   is_equal a MSorter

   @return the msorter
*/
#define MSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _msorter_is_equal )
int32_t
MSorter_is_equal( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other );

/**
   MSorter_is_equal

   check is_equal for two MSorters

   @return the msorter
*/
#define MSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _msorter_is_equal )
int32_t
MSorter_is_equal( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other );

/**
   MSorter_is_deep_equal

   check is_deep_equal for two MSorters

   @return the msorter
*/
#define MSorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _msorter_is_deep_equal )
int32_t
MSorter_is_deep_equal( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other );

/**
   MSorter_copy

   copy a MSorter into another

   @return the msorter
*/
#define MSorter_copy( arg ) PRIMITIVE_CAT( arg, _msorter_copy )
void
MSorter_copy( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other );

/**
   MSorter_deep_copy

   deep_copy a MSorter into another

   @return the msorter
*/
#define MSorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _msorter_deep_copy )
void
MSorter_deep_copy( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other );

/**
   MSorter_dispose

   dispose a MSorter

   @param the msorter
*/
#define MSorter_dispose( arg ) PRIMITIVE_CAT( arg, _msorter_dispose )
void
MSorter_dispose( Prefix )( MSorter_type( Prefix ) **msorter );

/**
   MSorter_deep_dispose

   deep dispose a MSorter

   @param the msorter
*/
#define MSorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _msorter_deep_dispose )
void
MSorter_deep_dispose( Prefix )( MSorter_type( Prefix ) **current );

/**
   MSorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param msorter the msorter
   @param p_indexable the pointer to the p_indexable
*/
#define MSorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _msorter_sort_predefined_comparison_function )
void
MSorter_sort_predefined_comparison_function( Prefix )
(
   MSorter_type( Prefix ) *msorter,
   protocol_base_t *p_indexable
);

/**
   MSorter_sort

   sort an entire p_indexable
   note that this function can be called without making a msorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define MSorter_sort( arg ) PRIMITIVE_CAT( arg, _msorter_sort )
void
MSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   MSorter_is_sorted_predefined_comparison_function

   return 1 if p_indexable is in order
   note that this function can be called without making a msorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define MSorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _msorter_is_sorted_predefined_comparison_function )
int32_t
MSorter_is_sorted_predefined_comparison_function( Prefix )
(
   MSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   MSorter_is_sorted

   return 1 if p_indexable is in order
   note that this function can be called without making a msorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define MSorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _msorter_is_sorted )
int32_t
MSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





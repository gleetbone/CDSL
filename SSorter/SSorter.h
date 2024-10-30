/**
 @file SSorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Shell Sorter"

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

 Function declarations for the opaque SSorter_t type.

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

#define SSorter_struct( arg ) PRIMITIVE_CAT( arg, _ssorter_struct )
#define SSorter_type( arg ) PRIMITIVE_CAT( arg, _ssorter_t )
#define SSorter_name( arg ) PRIMITIVE_CAT( arg, _ssorter )

/**
   Structure declarations
*/

struct SSorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct SSorter_struct( Prefix ) SSorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   SSorter_make

   make a SSorter

   @return the ssorter
*/
#define SSorter_make( arg ) PRIMITIVE_CAT( arg, _ssorter_make )
SSorter_type( Prefix ) *
SSorter_make( Prefix )( void );

/**
   SSorter_clone

   clone a SSorter

   @return the ssorter
*/
#define SSorter_clone( arg ) PRIMITIVE_CAT( arg, _ssorter_clone )
SSorter_type( Prefix ) *
SSorter_clone( Prefix )( SSorter_type( Prefix ) *other );

/**
   SSorter_deep_clone

   deep_clone a SSorter

   @return the ssorter
*/
#define SSorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _ssorter_deep_clone )
SSorter_type( Prefix ) *
SSorter_deep_clone( Prefix )( SSorter_type( Prefix ) *other );

/**
   SSorter_is_equal

   is_equal a SSorter

   @return the ssorter
*/
#define SSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _ssorter_is_equal )
int32_t
SSorter_is_equal( Prefix )( SSorter_type( Prefix ) *current, SSorter_type( Prefix ) *other );

/**
   SSorter_is_equal

   check is_equal for two SSorters

   @return the ssorter
*/
#define SSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _ssorter_is_equal )
int32_t
SSorter_is_equal( Prefix )( SSorter_type( Prefix ) *current, SSorter_type( Prefix ) *other );

/**
   SSorter_is_deep_equal

   check is_deep_equal for two SSorters

   @return the ssorter
*/
#define SSorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _ssorter_is_deep_equal )
int32_t
SSorter_is_deep_equal( Prefix )( SSorter_type( Prefix ) *current, SSorter_type( Prefix ) *other );

/**
   SSorter_copy

   copy a SSorter into another

   @return the ssorter
*/
#define SSorter_copy( arg ) PRIMITIVE_CAT( arg, _ssorter_copy )
void
SSorter_copy( Prefix )( SSorter_type( Prefix ) *current, SSorter_type( Prefix ) *other );

/**
   SSorter_deep_copy

   deep_copy a SSorter into another

   @return the ssorter
*/
#define SSorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _ssorter_deep_copy )
void
SSorter_deep_copy( Prefix )( SSorter_type( Prefix ) *current, SSorter_type( Prefix ) *other );

/**
   SSorter_dispose

   dispose a SSorter

   @param the ssorter
*/
#define SSorter_dispose( arg ) PRIMITIVE_CAT( arg, _ssorter_dispose )
void
SSorter_dispose( Prefix )( SSorter_type( Prefix ) **ssorter );

/**
   SSorter_deep_dispose

   deep dispose a SSorter

   @param the ssorter
*/
#define SSorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _ssorter_deep_dispose )
void
SSorter_deep_dispose( Prefix )( SSorter_type( Prefix ) **current );

/**
   SSorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param current the ssorter
   @param p_indexable the pointer to the p_indexable
*/
#define SSorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _ssorter_sort_predefined_comparison_function )
void
SSorter_sort_predefined_comparison_function( Prefix )
(
   SSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   SSorter_sort

   sort an entire p_indexable
   note that this function can be called without making a ssorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define SSorter_sort( arg ) PRIMITIVE_CAT( arg, _ssorter_sort )
void
SSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   SSorter_is_sorted_predefined_comparison_function

   return 1 if p_indexable is in order
   note that this function can be called without making a ssorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define SSorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _ssorter_is_sorted_predefined_comparison_function )
int32_t
SSorter_is_sorted_predefined_comparison_function( Prefix )
(
   SSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
);

/**
   SSorter_is_sorted

   return 1 if p_indexable is in order
   note that this function can be called without making a ssorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define SSorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _ssorter_is_sorted )
int32_t
SSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





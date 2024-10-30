/**
 @file QSorter.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Quick Sorter"

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

 Function declarations for the opaque QSorter_t type.

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

#define QSorter_struct( arg ) PRIMITIVE_CAT( arg, _qsorter_struct )
#define QSorter_type( arg ) PRIMITIVE_CAT( arg, _qsorter_t )
#define QSorter_name( arg ) PRIMITIVE_CAT( arg, _qsorter )

/**
   Structure declarations
*/

struct QSorter_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct QSorter_struct( Prefix ) QSorter_type( Prefix );

/**
   (Some) Function names below are prepended with "Prefix_".
*/

/**
   Includes
*/

/**
   QSorter_make

   make a QSorter

   @return the qsorter
*/
#define QSorter_make( arg ) PRIMITIVE_CAT( arg, _qsorter_make )
QSorter_type( Prefix ) *
QSorter_make( Prefix )( void );

/**
   QSorter_clone

   clone a QSorter

   @return the qsorter
*/
#define QSorter_clone( arg ) PRIMITIVE_CAT( arg, _qsorter_clone )
QSorter_type( Prefix ) *
QSorter_clone( Prefix )( QSorter_type( Prefix ) *other );

/**
   QSorter_deep_clone

   deep_clone a QSorter

   @return the qsorter
*/
#define QSorter_deep_clone( arg ) PRIMITIVE_CAT( arg, _qsorter_deep_clone )
QSorter_type( Prefix ) *
QSorter_deep_clone( Prefix )( QSorter_type( Prefix ) *other );

/**
   QSorter_is_equal

   is_equal a QSorter

   @return the qsorter
*/
#define QSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _qsorter_is_equal )
int32_t
QSorter_is_equal( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other );

/**
   QSorter_is_equal

   check is_equal for two QSorters

   @return the qsorter
*/
#define QSorter_is_equal( arg ) PRIMITIVE_CAT( arg, _qsorter_is_equal )
int32_t
QSorter_is_equal( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other );

/**
   QSorter_is_deep_equal

   check is_deep_equal for two QSorters

   @return the qsorter
*/
#define QSorter_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _qsorter_is_deep_equal )
int32_t
QSorter_is_deep_equal( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other );

/**
   QSorter_copy

   copy a QSorter into another

   @return the qsorter
*/
#define QSorter_copy( arg ) PRIMITIVE_CAT( arg, _qsorter_copy )
void
QSorter_copy( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other );

/**
   QSorter_deep_copy

   deep_copy a QSorter into another

   @return the qsorter
*/
#define QSorter_deep_copy( arg ) PRIMITIVE_CAT( arg, _qsorter_deep_copy )
void
QSorter_deep_copy( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other );

/**
   QSorter_dispose

   dispose a QSorter

   @param the qsorter
*/
#define QSorter_dispose( arg ) PRIMITIVE_CAT( arg, _qsorter_dispose )
void
QSorter_dispose( Prefix )( QSorter_type( Prefix ) **qsorter );

/**
   QSorter_deep_dispose

   deep dispose a QSorter

   @param the qsorter
*/
#define QSorter_deep_dispose( arg ) PRIMITIVE_CAT( arg, _qsorter_deep_dispose )
void
QSorter_deep_dispose( Prefix )( QSorter_type( Prefix ) **current );

/**
   QSorter_sort_predefined_comparison_function

   sort an entire p_indexable with the predefined coomparison function

   @param qsorter the qsorter
   @param p_indexable the pointer to the p_indexable
*/
#define QSorter_sort_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _qsorter_sort_predefined_comparison_function )
void
QSorter_sort_predefined_comparison_function( Prefix )
(
   QSorter_type( Prefix ) *qsorter,
   protocol_base_t *p_indexable
);

/**
   QSorter_sort

   sort an entire p_indexable
   note that this function can be called without making a qsorter

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
*/
#define QSorter_sort( arg ) PRIMITIVE_CAT( arg, _qsorter_sort )
void
QSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/**
   QSorter_is_sorted_predefined_comparison_function

   Check whether p_indexable is sorted according to the predefined coomparison function

   @param qsorter the qsorter
   @param p_indexable the pointer to the p_indexable
   @return 1 if sorter, 0 otherwise
*/
#define QSorter_is_sorted_predefined_comparison_function( arg ) PRIMITIVE_CAT( arg, _qsorter_is_sorted_predefined_comparison_function )
int32_t
QSorter_is_sorted_predefined_comparison_function( Prefix )
(
   QSorter_type( Prefix ) *qsorter,
   protocol_base_t *p_indexable
);

/**
   QSorter_is_sorted

   Check whether p_indexable is sorted according to the coomparison function

   @param p_indexable the pointer to the p_indexable
   @param func function to compare two items in p_indexable
   @return 1 if sorter, 0 otherwise
*/
#define QSorter_is_sorted( arg ) PRIMITIVE_CAT( arg, _qsorter_is_sorted )
int32_t
QSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
);

/* End of file */





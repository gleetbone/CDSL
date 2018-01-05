/**
 @file Matvec.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Matrices and vectors"
 
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

 Function definitions for the opaque Matvec_t type.

    <--row-->
                               ^
    e00   e01   e02   e03      |  
    e10   e11   e12   e13      |  
    e20   e21   e22   e23      column
    e30   e31   e32   e33      |
                               |
                               v

    element( row, column )

    height is number of rows
    width is number of columns

    first element ( upper left ) is at row = 0, col = 0

*/

/**
   includes
*/

#include "base.h"
#include <stdarg.h>

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   Prefix - string used to name this container type
   Type   - the type of the value
   Magnitude_type - the type of the magnitude or precision of Type
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Matvec_struct( arg ) PRIMITIVE_CAT( arg, _matvec_struct )
#define Matvec_type( arg ) PRIMITIVE_CAT( arg, _matvec_t )
#define Matvec_name( arg ) PRIMITIVE_CAT( arg, _matvec )

/** 
   Structure declarations
*/

struct Matvec_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Matvec_struct( Prefix ) Matvec_type( Prefix );

/**
   Function typedefs
*/

#define Matvec_func( arg ) PRIMITIVE_CAT( arg, _func_t )
typedef Type (* Matvec_func( Prefix ) )( Type );

#define Matvec_test_func( arg ) PRIMITIVE_CAT( arg, _test_func_t )
typedef int32_t (* Matvec_test_func( Prefix ) )( Type );


/**
   Functions that have the word "vector" in their name can only be used on vectors.
   Some other functions have limitations on inputs, possibly requiring square 
   matrices or requiring vectors to be of length 2 or 3. Preconditions check 
   these prerequisites.
*/


/** 
   Initialization
*/

/**
   Matvec_make
   
   Return a new empty Matvec_t instance.
   
   @return Matvec_t instance 
*/
#define Matvec_make( arg ) PRIMITIVE_CAT( arg, _matvec_make )
Matvec_type( Prefix ) * Matvec_make( Prefix )( int32_t rows, int32_t columns );

/**
   Matvec_make_row_vector
   
   Return a new empty Matvec_t instance.
   
   @return Matvec_t instance 
*/
#define Matvec_make_row_vector( arg ) PRIMITIVE_CAT( arg, _matvec_make_row_vector )
Matvec_type( Prefix ) * Matvec_make_row_vector( Prefix )( int32_t columns );

/**
   Matvec_make_column_vector
   
   Return a new empty Matvec_t instance.
   
   @return Matvec_t instance 
*/
#define Matvec_make_column_vector( arg ) PRIMITIVE_CAT( arg, _matvec_make_column_vector )
Matvec_type( Prefix ) * Matvec_make_column_vector( Prefix )( int32_t rows );

/**
   Matvec_make_from
   
   Return a new Matvec_t instance that is a copy of another Matvec_t instance.
   
   @param  other Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_make_from( arg ) PRIMITIVE_CAT( arg, _matvec_make_from )
Matvec_type( Prefix ) * Matvec_make_from( Prefix )( Matvec_type( Prefix ) *other );

/**
   Matvec_make_from_args
   
   Return a new Matvec_t instance that contains arguments from the function call.
   
   @param  n_rows number of rows in matrix 
   @param  n_columns number of columns in matrix
   @param ... the entries in the matrix - row major order
   @return Matvec_t instance 
*/
#define Matvec_make_from_args( arg ) PRIMITIVE_CAT( arg, _matvec_make_from_args )
Matvec_type( Prefix ) * Matvec_make_from_args( Prefix )( int32_t n_rows, int32_t n_columns, int32_t count, ... );

/**
   Disposal
*/

/**
   Matvec_dispose
   
   Free a Matvec_t instance. The value items are not disposed.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_dispose )
void Matvec_dispose( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_dispose_with_contents
   
   Free a Matvec_t instance. The value items are disposed.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _matvec_dispose_with_contents )
void Matvec_dispose_with_contents( Prefix )( Matvec_type( Prefix ) *matvec );

/** 
   Access
*/

/**
   Matvec_rows
   
   Return the height of the matvec, number of rows.
   
   @param  matvec Matvec_t instance 
   @return the number of rows
*/
#define Matvec_rows( arg ) PRIMITIVE_CAT( arg, _matvec_rows )
int32_t Matvec_rows( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_columns
   
   Return the width of the matvec, number of columns.
   
   @param  matvec Matvec_t instance 
   @return the number of columns
*/
#define Matvec_columns( arg ) PRIMITIVE_CAT( arg, _matvec_columns )
int32_t Matvec_columns( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_length
   
   Return the length of the matvec row or column vector.
   
   @param  matvec Matvec_t instance 
   @return the number of entries
*/
#define Matvec_vector_length( arg ) PRIMITIVE_CAT( arg, _matvec_vector_length )
int32_t Matvec_vector_length( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_is_column_vector
   
   Return 1 if matvec is column vector
   
   @param  matvec Matvec_t instance 
   @return 1 if matvec is column vector, 0 otherwise
*/
#define Matvec_is_column_vector( arg ) PRIMITIVE_CAT( arg, _matvec_is_column_vector )
int32_t Matvec_is_column_vector( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_is_row_vector
   
   Return 1 if matvec is row vector
   
   @param  matvec Matvec_t instance 
   @return 1 if matvec is row vector, 0 otherwise
*/
#define Matvec_is_row_vector( arg ) PRIMITIVE_CAT( arg, _matvec_is_row_vector )
int32_t Matvec_is_row_vector( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_item
   
   Return the value the matvec at the desired index.
   
   @param  matvec Matvec_t instance 
   @param  i_row item index
   @param  i_column item index
   @return the value of the item
*/
#define Matvec_item( arg ) PRIMITIVE_CAT( arg, _matvec_item )
Type Matvec_item( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_row, int32_t i_column );

/**
   Matvec_vector_item
   
   Return the value the matvec row or column vector at the desired index.
   
   @param  matvec Matvec_t instance 
   @param  i item index 
   @return the value of the item
*/
#define Matvec_vector_item( arg ) PRIMITIVE_CAT( arg, _matvec_vector_item )
Type Matvec_vector_item( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i );

/**
   Matvec_vector_x
   
   Return the value the matvec vector at index 0.
   
   @param  matvec Matvec_t instance 
   @return the value of the item
*/
#define Matvec_vector_x( arg ) PRIMITIVE_CAT( arg, _matvec_vector_x )
Type Matvec_vector_x( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_y
   
   Return the value the matvec vector at index 1.
   
   @param  matvec Matvec_t instance 
   @return the value of the item
*/
#define Matvec_vector_y( arg ) PRIMITIVE_CAT( arg, _matvec_vector_y )
Type Matvec_vector_y( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_z
   
   Return the value the matvec vector at index 2.
   
   @param  matvec Matvec_t instance 
   @return the value of the item
*/
#define Matvec_vector_z( arg ) PRIMITIVE_CAT( arg, _matvec_vector_z )
Type Matvec_vector_z( Prefix )( Matvec_type( Prefix ) *matvec );

/** 
   Measurement
*/

/**
   Matvec_vector_magnitude
   
   Return the magnitude of the vector.
   
   @param  matvec Matvec_t instance 
   @return magnitude of the vector
*/
#define Matvec_vector_magnitude( arg ) PRIMITIVE_CAT( arg, _matvec_vector_magnitude )
Magnitude_type Matvec_vector_magnitude( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_squared_magnitude
   
   Return the squared magnitude of the vector.
   
   @param  matvec Matvec_t instance 
   @return squared magnitude of the vector
*/
#define Matvec_vector_squared_magnitude( arg ) PRIMITIVE_CAT( arg, _matvec_vector_squared_magnitude )
Magnitude_type Matvec_vector_squared_magnitude( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_max_item_magnitude
   
   Return the largest magnitude of all the items in the matvec.
   
   @param  matvec Matvec_t instance 
   @return max item magnitude of the matvec
*/
#define Matvec_max_item_magnitude( arg ) PRIMITIVE_CAT( arg, _matvec_max_item_magnitude )
Magnitude_type Matvec_max_item_magnitude( Prefix )( Matvec_type( Prefix ) *matvec );


/** 
   Status report
*/

/**
   Matvec_is_symmetric
   
   Returns 1 if the matvec is symmetric.
   
   @param  matvec Matvec_t instance 
   @return 1 if matvec is symmetric, 0 otherwise
*/
#define Matvec_is_symmetric( arg ) PRIMITIVE_CAT( arg, _matvec_is_symmetric )
int32_t Matvec_is_symmetric( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_is_hermitian_symmetric
   
   Returns 1 if the matvec is hermitian symmetric.
   
   @param  matvec Matvec_t instance 
   @return 1 if matvec is hermitian symmetric, 0 otherwise
*/
#define Matvec_is_hermitian_symmetric( arg ) PRIMITIVE_CAT( arg, _matvec_is_hermitian_symmetric )
int32_t Matvec_is_hermitian_symmetric( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_is_approximately_symmetric
   
   Returns 1 if the matvec is approximately symmetric.
   
   @param  matvec Matvec_t instance 
   @param precision tolerance for the equality check
   @return 1 if matvec is approximately symmetric, 0 otherwise
*/
#define Matvec_is_approximately_symmetric( arg ) PRIMITIVE_CAT( arg, _matvec_is_approximately_symmetric )
int32_t Matvec_is_approximately_symmetric( Prefix )( Matvec_type( Prefix ) *matvec, Magnitude_type precision );

/**
   Matvec_is_approximately_hermitian_symmetric
   
   Returns 1 if the matvec is approximately hermitian symmetric.
   
   @param  matvec Matvec_t instance 
   @param precision tolerance for the equality check
   @return 1 if matvec is approximately hermitian symmetric, 0 otherwise
*/
#define Matvec_is_approximately_hermitian_symmetric( arg ) PRIMITIVE_CAT( arg, _matvec_is_approximately_hermitian_symmetric )
int32_t Matvec_is_approximately_hermitian_symmetric( Prefix )( Matvec_type( Prefix ) *matvec, Magnitude_type precision );


/** 
   Comparison
*/

/**
   Matvec_is_equal
   
   Returns 1 if the matvec is equal to other.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return 1 if matvec is equal, 0 otherwise
*/
#define Matvec_is_equal( arg ) PRIMITIVE_CAT( arg, _matvec_is_equal )
int32_t Matvec_is_equal( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_is_approximately_equal
   
   Returns 1 if the matvec is approximately equal to other.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @param precision tolerance for the equality check
   @return 1 if matvec is approximately equal, 0 otherwise
*/
#define Matvec_is_approximately_equal( arg ) PRIMITIVE_CAT( arg, _matvec_is_approximately_equal )
int32_t Matvec_is_approximately_equal( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other, Magnitude_type precision );


/** 
   Element change
*/

/**
   Matvec_put
   
   Put value into matvec, don't dispose of previous value.
   
   @param  matvec Matvec_t instance 
   @param  value what to insert
   @param  i_row item index
   @param  i_column item index
*/
#define Matvec_put( arg ) PRIMITIVE_CAT( arg, _matvec_put )
void Matvec_put( Prefix )( Matvec_type( Prefix ) *matvec, Type value, int32_t i_row, int32_t i_column );

/**
   Matvec_put_and_dispose
   
   Put value into matvec, dispose of previous value.
   
   @param  matvec Matvec_t instance 
   @param  value what to insert
   @param  i_row item index
   @param  i_column item index
*/
#define Matvec_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_put_and_dispose )
void Matvec_put_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Type value, int32_t i_row, int32_t i_column );

/**
   Matvec_vector_put
   
   Put value into matvec vector, don't dispose of previous value.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
   @param  i item index
*/
#define Matvec_vector_put( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put )
void Matvec_vector_put( Prefix )( Matvec_type( Prefix ) *matvec, Type value, int32_t i );

/**
   Matvec_vector_put_and_dispose
   
   Put value into matvec vector, dispose of previous value.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
   @param  i item index
*/
#define Matvec_vector_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_and_dispose )
void Matvec_vector_put_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Type value, int32_t i );

/**
   Matvec_vector_put_x, don't dispose of previous value
   
   Put value into matvec vector at index 0.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
  
*/
#define Matvec_vector_put_x( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_x )
void Matvec_vector_put_x( Prefix )( Matvec_type( Prefix ) *matvec, Type value );

/**
   Matvec_vector_put_x_and_dispose, dispose of previous value
   
   Put value into matvec vector at index 0.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
  
*/
#define Matvec_vector_put_x_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_x_and_dispose )
void Matvec_vector_put_x_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Type value );

/**
   Matvec_vector_put_y, don't dispose of previous value
   
   Put value into matvec vector at index 1.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
  
*/
#define Matvec_vector_put_y( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_y )
void Matvec_vector_put_y( Prefix )( Matvec_type( Prefix ) *matvec, Type value );

/**
   Matvec_vector_put_y_and_dispose, dispose of previous value
   
   Put value into matvec vector at index 1.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
  
*/
#define Matvec_vector_put_y_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_y_and_dispose )
void Matvec_vector_put_y_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Type value );

/**
   Matvec_vector_put_z, don't dispose of previous value
   
   Put value into matvec vector at index 2.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
  
*/
#define Matvec_vector_put_z( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_z )
void Matvec_vector_put_z( Prefix )( Matvec_type( Prefix ) *matvec, Type value );

/**
   Matvec_vector_put_z_and_dispose, don't dispose of previous value
   
   Put value into matvec vector at index 2.
   
   @param  matvec Matvec_t vector instance 
   @param  value what to insert
  
*/
#define Matvec_vector_put_z_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_vector_put_z_and_dispose )
void Matvec_vector_put_z_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Type value );

/**
   Matvec_set_from
   
   Sets copies of values of other into matvec, don't dispose of previous values
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
*/
#define Matvec_set_from( arg ) PRIMITIVE_CAT( arg, _matvec_set_from )
void Matvec_set_from( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_set_from_and_dispose
   
   Sets copies of values of other into matvec, dispose of previous values
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
*/
#define Matvec_set_from_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_set_from_and_dispose )
void Matvec_set_from_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );


/**
   Iteration
*/

/**
   Matvec_do_and_set_all
   
   For each entry, calculate function result and replace that entry with result.
   Don't dispose of previous values.
   
   @param  matvec Matvec_t instance 
   @param  func the function to perform
*/
#define Matvec_do_and_set_all( arg ) PRIMITIVE_CAT( arg, _matvec_do_and_set_all )
void Matvec_do_and_set_all( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_func( Prefix ) func );

/**
   Matvec_do_and_set_all_and_dispose
   
   For each entry, calculate function result and replace that entry with result
   Dispose of previous values.
   
   @param  matvec Matvec_t instance 
   @param  func the function to perform
*/
#define Matvec_do_and_set_all_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_do_and_set_all_and_dispose )
void Matvec_do_and_set_all_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_func( Prefix ) func );

/**
   Matvec_do_and_set_if
   
   For each entry, calculate function result and replace that entry with result
   if test function is true. Don't dispose of previous values.
   
   @param  matvec Matvec_t instance 
   @param  func the function to perform
   @param  test_func the test function
*/
#define Matvec_do_and_set_if( arg ) PRIMITIVE_CAT( arg, _matvec_do_and_set_if )
void Matvec_do_and_set_if( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_func( Prefix ) func, Matvec_test_func( Prefix ) test_func );

/**
   Matvec_do_and_set_if_and_dispose
   
   For each entry, calculate function result and replace that entry with result
   if test function is true. Dispose of previous values if replaced.
   
   @param  matvec Matvec_t instance 
   @param  func the function to perform
   @param  test_func the test function
*/
#define Matvec_do_and_set_if_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_do_and_set_if_and_dispose )
void Matvec_do_and_set_if_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_func( Prefix ) func, Matvec_test_func( Prefix ) test_func );


/**
   Miscellaneous
*/

/**
   Matvec_one
   
   Return neutral element for "*" and "/"
   
   @param  matvec Matvec_t instance 
   @return the "one" matvec
   
*/
#define Matvec_one( arg ) PRIMITIVE_CAT( arg, _matvec_one )
Matvec_type( Prefix ) * Matvec_one( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_zero
   
   Return neutral element for "+" and "-"
   
   @param  matvec Matvec_t instance 
   @return the "zero" matvec
   
*/
#define Matvec_zero( arg ) PRIMITIVE_CAT( arg, _matvec_zero )
Matvec_type( Prefix ) * Matvec_zero( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_set_to_one
   
   Set to neutral element for "*" and "/". Don't dispose of previous values.
   
   @param  matvec Matvec_t instance 
   
*/
#define Matvec_set_to_one( arg ) PRIMITIVE_CAT( arg, _matvec_set_to_one )
void Matvec_set_to_one( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_set_to_one_and_dispose
   
   Set to neutral element for "*" and "/". Dispose of previous values.
   
   @param  matvec Matvec_t instance 
   
*/
#define Matvec_set_to_one_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_set_to_one_and_dispose )
void Matvec_set_to_one_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_set_to_zero
   
   set to neutral element for "+" and "-". Don't dispose of previous values.
   
   @param  matvec Matvec_t instance 
   
*/
#define Matvec_set_to_zero( arg ) PRIMITIVE_CAT( arg, _matvec_set_to_zero )
void Matvec_set_to_zero( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_set_to_zero_and_dispose
   
   set to neutral element for "+" and "-". Dispose of previous values.
   
   @param  matvec Matvec_t instance 
   
*/
#define Matvec_set_to_zero_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_set_to_zero_and_dispose )
void Matvec_set_to_zero_and_dispose( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_copied
   
   Return copy of matvec with new copies of items.
   
   @param  matvec Matvec_t instance 
   @return the "copied" matvec
   
*/
#define Matvec_copied( arg ) PRIMITIVE_CAT( arg, _matvec_copied )
Matvec_type( Prefix ) * Matvec_copied( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_subcopied
   
   Return sub copy of (part of) matvec with new copies of items
   
   @param  matvec Matvec_t instance 
   @param  i_row the starting row index of the subcopy
   @param  n_row the number of row indices of the subcopy
   @param  i_column the starting column index of the subcopy
   @param  n_column the number of column indices of the subcopy
   @return the "subcopied" matvec
   
*/
#define Matvec_subcopied( arg ) PRIMITIVE_CAT( arg, _matvec_subcopied )
Matvec_type( Prefix ) * 
Matvec_subcopied( Prefix )
( 
   Matvec_type( Prefix ) *matvec,
   int32_t i_row,
   int32_t n_row,
   int32_t i_column,
   int32_t n_column
);

/**
   Matvec_subcopy
   
   Set (part of) matvec from other. Don't dispose of previous items.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @param  i_row the starting row index of the subcopy in matvec
   @param  i_row_other the starting row index of the subcopy in other
   @param  n_row_other the number of row indices of the subcopy in other
   @param  i_column the starting column index of the subcopy in matvec
   @param  i_column_other the starting column index of the subcopy in other
   @param  n_column_other the number of column indices of the subcopy in other
   
*/
#define Matvec_subcopy( arg ) PRIMITIVE_CAT( arg, _matvec_subcopy )
void
Matvec_subcopy( Prefix )
( 
   Matvec_type( Prefix ) *matvec,
   Matvec_type( Prefix ) *other,
   int32_t i_row,
   int32_t i_row_other,
   int32_t n_row_other,
   int32_t i_column,
   int32_t i_column_other,
   int32_t n_column_other
);

/**
   Matvec_subcopy_and_dispose
   
   Set (part of) matvec from other. Dispose of previous items.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @param  i_row the starting row index of the subcopy in matvec
   @param  i_row_other the starting row index of the subcopy in other
   @param  n_row_other the number of row indices of the subcopy in other
   @param  i_column the starting column index of the subcopy in matvec
   @param  i_column_other the starting column index of the subcopy in other
   @param  n_column_other the number of column indices of the subcopy in other
*/
#define Matvec_subcopy_and_dispose( arg ) PRIMITIVE_CAT( arg, _matvec_subcopy_and_dispose )
void 
Matvec_subcopy_and_dispose( Prefix )
( 
   Matvec_type( Prefix ) *matvec,
   Matvec_type( Prefix ) *other,
   int32_t i_row,
   int32_t i_row_other,
   int32_t n_row_other,
   int32_t i_column,
   int32_t i_column_other,
   int32_t n_column_other
);

/**
   Matvec_as_array
   
   Return pointer to internal array of values. Do NOT free() this array.
   
   @param  matvec Matvec_t instance 
   @return pointer to the array
   
*/
#define Matvec_as_array( arg ) PRIMITIVE_CAT( arg, _matvec_as_array )
Type * Matvec_as_array( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_copy_as_array
   
   Return pointer to copy of internal array of values. free() this array to dispose.
   
   @param  matvec Matvec_t instance 
   @return pointer to the array
   
*/
#define Matvec_copy_as_array( arg ) PRIMITIVE_CAT( arg, _matvec_copy_as_array )
Type * Matvec_copy_as_array( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_from_row
   
   Return row of matvec as vector with new copies of items.
   
   @param  matvec Matvec_t instance 
   @param  i_row which row 
   @return the "copied" matvec
   
*/
#define Matvec_vector_from_row( arg ) PRIMITIVE_CAT( arg, _matvec_vector_from_row )
Matvec_type( Prefix ) * Matvec_vector_from_row( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_row );

/**
   Matvec_vector_from_column
   
   Return column of matvec as vector with new copies of items.
   
   @param  matvec Matvec_t instance 
   @param  i_column which column 
   @return the "copied" matvec
   
*/
#define Matvec_vector_from_column( arg ) PRIMITIVE_CAT( arg, _matvec_vector_from_column )
Matvec_type( Prefix ) * Matvec_vector_from_column( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_column );

/**
   Matvec_row_vector_dot
   
   Return dot product of two rows of matvec
   
   @param  matvec Matvec_t instance 
   @param  i_row_1 which row
   @param  i_row_2 which row
   @return the dot product of the two rows
   
*/
#define Matvec_row_vector_dot( arg ) PRIMITIVE_CAT( arg, _matvec_row_vector_dot )
Type Matvec_row_vector_dot( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_row_1, int32_t i_row_2 );

/**
   Matvec_row_vector_squared_magnitude
   
   Return squared magnitude of row of matvec
   
   @param  matvec Matvec_t instance 
   @param  i_row which row
   @return the dot product of the two rows
   
*/
#define Matvec_row_vector_squared_magnitude( arg ) PRIMITIVE_CAT( arg, _matvec_row_vector_squared_magnitude )
Magnitude_type Matvec_row_vector_squared_magnitude( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_row );

/**
   Matvec_row_vector_scale
   
   Scale a row of matvec
   
   @param  matvec Matvec_t instance
   @param  scale the scale factor
   @param  i_row which row
   
*/
#define Matvec_row_vector_scale( arg ) PRIMITIVE_CAT( arg, _matvec_row_vector_scale )
void Matvec_row_vector_scale( Prefix )( Matvec_type( Prefix ) *matvec, Type scale, int32_t i_row );

/**
   Matvec_column_vector_dot
   
   Return dot product of two columns of matvec
   
   @param  matvec Matvec_t instance 
   @param  i_column_1 which column
   @param  i_column_2 which column
   @return the dot product of the two columns
   
*/
#define Matvec_column_vector_dot( arg ) PRIMITIVE_CAT( arg, _matvec_column_vector_dot )
Type Matvec_column_vector_dot( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_column_1, int32_t i_column_2 );

/**
   Matvec_column_vector_squared_magnitude
   
   Return squared magnitude of column of matvec
   
   @param  matvec Matvec_t instance 
   @param  i_column which column
   @return the dot product of the two columns
   
*/
#define Matvec_column_vector_squared_magnitude( arg ) PRIMITIVE_CAT( arg, _matvec_column_vector_squared_magnitude )
Magnitude_type Matvec_column_vector_squared_magnitude( Prefix )( Matvec_type( Prefix ) *matvec, int32_t i_column );

/**
   Matvec_column_vector_scale
   
   Scale a column of matvec
   
   @param  matvec Matvec_t instance
   @param  scale the scale factor
   @param  i_column which column
   
*/
#define Matvec_column_vector_scale( arg ) PRIMITIVE_CAT( arg, _matvec_column_vector_scale )
void Matvec_column_vector_scale( Prefix )( Matvec_type( Prefix ) *matvec, Type scale, int32_t i_column );

/**
   Basic operations
*/

/**
   Matvec_add
   
   Add other to matvec.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
*/
#define Matvec_add( arg ) PRIMITIVE_CAT( arg, _matvec_add )
void Matvec_add( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_added
   
   Make copy of matvec, return copy added to other.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_added( arg ) PRIMITIVE_CAT( arg, _matvec_added )
Matvec_type( Prefix ) * Matvec_added( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_subtract
   
   Subtrace other from matvec.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
*/
#define Matvec_subtract( arg ) PRIMITIVE_CAT( arg, _matvec_subtract )
void Matvec_subtract( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_subtracted
   
   Make copy of matvec, return copy minus other.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_subtracted( arg ) PRIMITIVE_CAT( arg, _matvec_subtracted )
Matvec_type( Prefix ) * Matvec_subtracted( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_multiply
   
   Multiply matvec and other, result in matvec.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
*/
#define Matvec_multiply( arg ) PRIMITIVE_CAT( arg, _matvec_multiply )
void Matvec_multiply( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_multiplied
   
   Make copy of matvec, return copy multiplied by other.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_multiplied( arg ) PRIMITIVE_CAT( arg, _matvec_multiplied )
Matvec_type( Prefix ) * Matvec_multiplied( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_vector_normalize
   
   Normalize vector.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_vector_normalize( arg ) PRIMITIVE_CAT( arg, _matvec_vector_normalize )
void Matvec_vector_normalize( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_normalized
   
   Make copy of matvec, return normalized copy.
   
   @param  matvec Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_vector_normalized( arg ) PRIMITIVE_CAT( arg, _matvec_vector_normalized )
Matvec_type( Prefix ) * Matvec_vector_normalized( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_vector_dot
   
   Return dot product of two vectors
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return the dot product of the two rows
   
*/
#define Matvec_vector_dot( arg ) PRIMITIVE_CAT( arg, _matvec_vector_dot )
Type Matvec_vector_dot( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_vector_cross
   
   Set matvec to the cross product of matvec and other
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   
*/
#define Matvec_vector_cross( arg ) PRIMITIVE_CAT( arg, _matvec_vector_cross )
void Matvec_vector_cross( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_vector_crossed
   
   Return matvec as the cross product of matvec and other
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return the cross product Matvec_t instance 
   
*/
#define Matvec_vector_crossed( arg ) PRIMITIVE_CAT( arg, _matvec_vector_crossed )
Matvec_type( Prefix ) * Matvec_vector_crossed( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_item_by_item_multiply
   
   Multiply matvec and other element by element, result in matvec.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
*/
#define Matvec_item_by_item_multiply( arg ) PRIMITIVE_CAT( arg, _matvec_item_by_item_multiply )
void Matvec_item_by_item_multiply( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_item_by_item_multiplied
   
   Make copy of matvec, return copy item_by_item_multiplied by other.
   
   @param  matvec Matvec_t instance 
   @param  other Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_item_by_item_multiplied( arg ) PRIMITIVE_CAT( arg, _matvec_item_by_item_multiplied )
Matvec_type( Prefix ) * Matvec_item_by_item_multiplied( Prefix )( Matvec_type( Prefix ) *matvec, Matvec_type( Prefix ) *other );

/**
   Matvec_scale
   
   Scale all items of matvec.
   
   @param  matvec Matvec_t instance 
   @param  scale scale factor 
   @param  other Matvec_t instance 
*/
#define Matvec_scale( arg ) PRIMITIVE_CAT( arg, _matvec_scale )
void Matvec_scale( Prefix )( Matvec_type( Prefix ) *matvec, Type scale );

/**
   Matvec_scaled
   
   Make copy of matvec, return scaled copy.
   
   @param  matvec Matvec_t instance 
   @param  scale scale factor 
   @return Matvec_t instance 
*/
#define Matvec_scaled( arg ) PRIMITIVE_CAT( arg, _matvec_scaled )
Matvec_type( Prefix ) * Matvec_scaled( Prefix )( Matvec_type( Prefix ) *matvec, Type scale );

/**
   Matvec_negate
   
   Negate all items of matvec.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_negate( arg ) PRIMITIVE_CAT( arg, _matvec_negate )
void Matvec_negate( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_negated
   
   Make copy of matvec, return negated copy.
   
   @param  matvec Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_negated( arg ) PRIMITIVE_CAT( arg, _matvec_negated )
Matvec_type( Prefix ) * Matvec_negated( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_transpose
   
   Transpose matvec, requires matvec to be square matrix.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_transpose( arg ) PRIMITIVE_CAT( arg, _matvec_transpose )
void Matvec_transpose( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_transposed
   
   Return transposed copy of matvec.
   
   @param  matvec Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_transposed( arg ) PRIMITIVE_CAT( arg, _matvec_transposed )
Matvec_type( Prefix ) * Matvec_transposed( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_hermitian_transpose
   
   Hermitian transpose matvec, requires matvec to be square matrix.   
   @param  matvec Matvec_t instance 
*/
#define Matvec_hermitian_transpose( arg ) PRIMITIVE_CAT( arg, _matvec_hermitian_transpose )
void Matvec_hermitian_transpose( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_hermitian_transposed
   
   Return hermitian transposed copy of matvec.
   
   @param  matvec Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_hermitian_transposed( arg ) PRIMITIVE_CAT( arg, _matvec_hermitian_transposed )
Matvec_type( Prefix ) * Matvec_hermitian_transposed( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_conjugate
   
   Conjugate all items of matvec.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_conjugate( arg ) PRIMITIVE_CAT( arg, _matvec_conjugate )
void Matvec_conjugate( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_conjugated
   
   Make copy of matvec, return conjugated copy.
   
   @param  matvec Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_conjugated( arg ) PRIMITIVE_CAT( arg, _matvec_conjugated )
Matvec_type( Prefix ) * Matvec_conjugated( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_invert
   
   Invert matvec.
   
   @param  matvec Matvec_t instance 
*/
#define Matvec_invert( arg ) PRIMITIVE_CAT( arg, _matvec_invert )
void Matvec_invert( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_inverse
   
   Make copy of matvec, return inverted copy.
   
   @param  matvec Matvec_t instance 
   @return Matvec_t instance 
*/
#define Matvec_inverse( arg ) PRIMITIVE_CAT( arg, _matvec_inverse )
Matvec_type( Prefix ) * Matvec_inverse( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_determinant
   
   Return the determinant of the matvec.
   
   @param  matvec Matvec_t instance 
   @return max item magnitude of the matvec
*/
#define Matvec_determinant( arg ) PRIMITIVE_CAT( arg, _matvec_determinant )
Type Matvec_determinant( Prefix )( Matvec_type( Prefix ) *matvec );

/**
   Matvec_trace
   
   Return the trace of the matvec.
   
   @param  matvec Matvec_t instance 
   @return max item magnitude of the matvec
*/
#define Matvec_trace( arg ) PRIMITIVE_CAT( arg, _matvec_trace )
Type Matvec_trace( Prefix )( Matvec_type( Prefix ) *matvec );


/* End of file */




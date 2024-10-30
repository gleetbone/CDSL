/**
 @file Matvec.c
 @author Greg Lee
 @version 2.0.0
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

*/

#include "Matvec.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Type   - the type of the value
   Magnitude_type - the type of the magnitude or precision of Type
   Va_type - type returned from call to va_arg function (floats promoted to double, etc. )

   Macros that must be present (external to this file):

   DEFAULT_VALUE              -  constant that is the default value for type (zero)
   ONE_VALUE                  -  constant that is the "one" value for type
   IS_INVERTIBLE              -  constant 0 if not or 1 if type is invertible
   NEGATE_FUNCTION            -  additive inverse of type value
   ADD_FUNCTION               -  adds two type values
   SQUARED_MAGNITUDE_FUNCTION -  squared magnitude of type value
   MULTIPLY_FUNCTION          -  multiplies two type values
   INVERSE_FUNCTION           -  multiplicative inverse of type value
   CONJUGATE_FUNCTION         -  complex conjugate of type value
   EQUAL_FUNCTION             -  1 if items are equal, 0 otherwise
   DUPLICATE_FUNCTION         -  makes duplicate of a type value
   SET_FROM                   -  sets value from another
   DISPOSE_FUNCTION           -  frees a type value

*/

/**
   Matvec structure
*/

struct Matvec_struct( Prefix )
{
   int32_t _type;
   int32_t _item_type;

   // number of columns
   int32_t n_columns;

   // number of rows
   int32_t n_rows;

   // multithread values if we include threading support
   MULTITHREAD_MUTEX_DEFINITION( mutex );
   // the array of data
   Type *a;

};

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
num_rows_and_num_columns_positive( Matvec_type( Prefix ) *p )
{
   int32_t result = 0;

   if ( ( (*p).n_rows > 0 ) && ( (*p).n_columns > 0 ) )
   {
      result = 1;
   }

   return result;
}

static
int32_t
array_is_not_null( Matvec_type( Prefix ) *p )
{
   int32_t result = 0;

   if ( (*p).a != NULL )
   {
      result = 1;
   }

   return result;
}

static
void invariant( Matvec_type( Prefix ) *p )
{
   assert( ( ( void ) "num rows and num columns positive", num_rows_and_num_columns_positive( p ) ) );
   assert( ( ( void ) "array is not null", array_is_not_null( p ) ) );
   return;
}

#else

static
void invariant( p )
{
   return;
}

#endif

/**
   Matvec_make
*/

Matvec_type( Prefix ) *
Matvec_make( Prefix )( int32_t rows, int32_t columns )
{
   PRECONDITION( "rows positive", rows > 0 );
   PRECONDITION( "column positive", columns > 0 );

   int32_t i = 0;
   int32_t j = 0;
   Type *pa = NULL;

   // allocate result struct
   Matvec_type( Prefix ) * result
      = ( Matvec_type( Prefix ) * ) calloc( 1, sizeof( Matvec_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = MATVEC_TYPE;
   (*result)._item_type = Type_Code;

   // set rows and columns
   (*result).n_rows = rows;
   (*result).n_columns = columns;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // allocate array
   (*result).a = ( Type * ) calloc( rows * columns, sizeof( Type ) );
   CHECK( "(*result).a allocated correctly", (*result).a != NULL );
   pa = (*result).a;

   // fill array with default value
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa[ i * columns + j ] = DEFAULT_VALUE;
      }
   }

   INVARIANT( result );

   return result;
}

/**
   Matvec_make_row_vector
*/

Matvec_type( Prefix ) *
Matvec_make_row_vector( Prefix )( int32_t columns )
{
   PRECONDITION( "column positive", columns > 0 );

   int32_t rows = 1;
   int32_t i = 0;
   int32_t j = 0;
   Type *pa = NULL;

   // allocate result struct
   Matvec_type( Prefix ) * result
      = ( Matvec_type( Prefix ) * ) calloc( 1, sizeof( Matvec_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = MATVEC_TYPE;
   (*result)._item_type = Type_Code;

   // set rows and columns
   (*result).n_rows = rows;
   (*result).n_columns = columns;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // allocate array
   (*result).a = ( Type * ) calloc( rows * columns, sizeof( Type ) );
   CHECK( "(*result).a allocated correctly", (*result).a != NULL );
   pa = (*result).a;

   // fill array with default value
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa[ i * columns + j ] = DEFAULT_VALUE;
      }
   }

   INVARIANT( result );

   return result;
}

/**
   Matvec_make_column_vector
*/

Matvec_type( Prefix ) *
Matvec_make_column_vector( Prefix )( int32_t rows )
{
   PRECONDITION( "rows positive", rows > 0 );

   int32_t columns = 1;
   int32_t i = 0;
   int32_t j = 0;
   Type *pa = NULL;

   // allocate result struct
   Matvec_type( Prefix ) * result
      = ( Matvec_type( Prefix ) * ) calloc( 1, sizeof( Matvec_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = MATVEC_TYPE;
   (*result)._item_type = Type_Code;

   // set rows and columns
   (*result).n_rows = rows;
   (*result).n_columns = columns;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // allocate array
   (*result).a = ( Type * ) calloc( rows * columns, sizeof( Type ) );
   CHECK( "(*result).a allocated correctly", (*result).a != NULL );
   pa = (*result).a;

   // fill array with default value
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa[ i * columns + j ] = DEFAULT_VALUE;
      }
   }

   INVARIANT( result );

   return result;
}

/**
   Matvec_make_from
*/

Matvec_type( Prefix ) *
Matvec_make_from( Prefix )( Matvec_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );

   int32_t rows = (*other).n_rows;
   int32_t columns = (*other).n_columns;
   int32_t i = 0;
   int32_t j = 0;
   Type *pa = NULL;
   Type *pa_other = NULL;

   // allocate result struct
   Matvec_type( Prefix ) * result
      = ( Matvec_type( Prefix ) * ) calloc( 1, sizeof( Matvec_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = MATVEC_TYPE;
   (*result)._item_type = Type_Code;

   // set rows and columns
   (*result).n_rows = rows;
   (*result).n_columns = columns;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // allocate array
   (*result).a = ( Type * ) calloc( rows * columns, sizeof( Type ) );
   CHECK( "(*result).a allocated correctly", (*result).a != NULL );
   pa = (*result).a;
   pa_other = (*other).a;

   // fill array with duplicate values from other
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa[ i * columns + j ] = DUPLICATE_FUNCTION( pa_other[ i * columns + j ] );
      }
   }

   INVARIANT( result );

   return result;
}

/**
   Matvec_make_from_args
*/

Matvec_type( Prefix ) *
Matvec_make_from_args( Prefix )( int32_t n_rows, int32_t n_columns, int32_t count, ... )
{
   PRECONDITION( "n_rows positive", n_rows > 0 );
   PRECONDITION( "n_columns positive", n_columns > 0 );

   va_list valist;
   int32_t rows = n_rows;
   int32_t columns = n_columns;
   int32_t i = 0;
   int32_t j = 0;
   Type *pa = NULL;

   // allocate result struct
   Matvec_type( Prefix ) * result
      = ( Matvec_type( Prefix ) * ) calloc( 1, sizeof( Matvec_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = MATVEC_TYPE;
   (*result)._item_type = Type_Code;

   // set rows and columns
   (*result).n_rows = rows;
   (*result).n_columns = columns;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // allocate array
   (*result).a = ( Type * ) calloc( count, sizeof( Type ) );
   CHECK( "(*result).a allocated correctly", (*result).a != NULL );
   pa = (*result).a;

   // init valist
   va_start( valist, count );

   // fill array with duplicate values from other
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa[ i * columns + j ] = ( Type ) va_arg( valist, Va_type );
      }
   }
   // terminate valist
   va_end( valist );

   INVARIANT( result );

   return result;
}

/**
   Matvec_dispose
*/

void
Matvec_dispose( Prefix )( Matvec_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == MATVEC_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete current array
   free( (**current).a );
   (**current).a = NULL;

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set current to NULL
   *current = NULL;

   return;
}

/**
   Matvec_deep_dispose
*/

void
Matvec_deep_dispose( Prefix )( Matvec_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == MATVEC_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t rows = (**current).n_rows;
   int32_t columns = (**current).n_columns;
   int32_t i = 0;
   int32_t j = 0;

   // delete current items
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         DISPOSE_FUNCTION( (**current).a[ i * columns + j ] );
      }
   }

   // delete current array
   free( (**current).a );
   (**current).a = NULL;

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set current to NULL
   *current = NULL;

   return;
}

/**
   Matvec_rows
*/

int32_t
Matvec_rows( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).n_rows;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_columns
*/

int32_t
Matvec_columns( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).n_columns;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_length
*/

int32_t
Matvec_vector_length( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1 ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( (*current).n_rows == 1 )
   {
      result = (*current).n_columns;
   }
   else
   {
      result = (*current).n_rows;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_row_vector
*/

int32_t
Matvec_is_row_vector( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( (*current).n_rows == 1 )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_column_vector
*/

int32_t
Matvec_is_column_vector( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( (*current).n_columns == 1 )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_item
*/

Type
Matvec_item( Prefix )( Matvec_type( Prefix ) *current, int32_t i_row, int32_t i_column )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).a[ i_row * (*current).n_columns + i_column ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_item
*/

Type
Matvec_vector_item( Prefix )( Matvec_type( Prefix ) *current, int32_t i )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( i >= 0 ) && ( i < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( i >= 0 ) && ( i < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).a[i];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_x
*/

Type
Matvec_vector_x( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 0 >= 0 ) && ( 0 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 0 >= 0 ) && ( 0 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).a[0];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_y
*/

Type
Matvec_vector_y( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 1 >= 0 ) && ( 1 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 1 >= 0 ) && ( 1 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).a[1];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_z
*/

Type
Matvec_vector_z( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 2 >= 0 ) && ( 2 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 2 >= 0 ) && ( 2 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).a[2];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_magnitude
*/

Magnitude_type
Matvec_vector_magnitude( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Magnitude_type result = 0;
   int32_t i = 0;
   int32_t n = 0;
   Type item = DEFAULT_VALUE;
   Type *pa = NULL;

   if ( (*current).n_rows > (*current).n_columns )
   {
      n = (*current).n_rows;
   }
   else
   {
      n = (*current).n_columns;
   }

   pa = (*current).a;

   for ( i = 0; i < n; i++ )
   {
      item = pa[i];
      result = result + SQUARED_MAGNITUDE_FUNCTION( item );
   }

   result = sqrt( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_squared_magnitude
*/

Magnitude_type
Matvec_vector_squared_magnitude( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Magnitude_type result = 0;
   int32_t i = 0;
   int32_t n = 0;
   Type item = DEFAULT_VALUE;
   Type *pa = NULL;

   if ( (*current).n_rows > (*current).n_columns )
   {
      n = (*current).n_rows;
   }
   else
   {
      n = (*current).n_columns;
   }

   pa = (*current).a;

   for ( i = 0; i < n; i++ )
   {
      item = pa[i];
      result = result + SQUARED_MAGNITUDE_FUNCTION( item );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_max_item_magnitude
*/

Magnitude_type
Matvec_max_item_magnitude( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Magnitude_type result = 0;
   Magnitude_type x = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type item = DEFAULT_VALUE;
   Type *pa = NULL;

   item = (*current).a[0];
   result = SQUARED_MAGNITUDE_FUNCTION( item );

   pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = pa[i * columns + j];
         x = SQUARED_MAGNITUDE_FUNCTION( item );
         if ( x > result )
         {
            result = x;
         }
      }
   }

   result = sqrt( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_symmetric
*/

int32_t
Matvec_is_symmetric( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; ( ( i < rows ) && ( result == 1 ) ); i++ )
   {
      for ( j = i + 1; j < columns; j++ )
      {
         result = EQUAL_FUNCTION( pa[i * columns + j], pa[j * columns + i] );
         if ( result == 0 )
         {
            break;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_hermitian_symmetric
*/

int32_t
Matvec_is_hermitian_symmetric( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item1 = DEFAULT_VALUE;
   int32_t result = 1;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; ( ( i < rows ) && ( result == 1 ) ); i++ )
   {
      for ( j = i + 1; j < columns; j++ )
      {
         item1 = CONJUGATE_FUNCTION( pa[j * columns + i] );
         result = EQUAL_FUNCTION( pa[i * columns + j], item1 );
         DISPOSE_FUNCTION( item1 );

         if ( result == 0 )
         {
            break;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_approximately_symmetric
*/

int32_t
Matvec_is_approximately_symmetric( Prefix )( Matvec_type( Prefix ) *current, Magnitude_type precision )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   PRECONDITION( "precision not negative", precision >= 0.0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   Magnitude_type m = 0;
   Magnitude_type x = 0;
   Magnitude_type p = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type item = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;

   // get squared magnitude of largest item
   item = pa[0];
   m = SQUARED_MAGNITUDE_FUNCTION( item );

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = pa[i * columns + j];
         x = SQUARED_MAGNITUDE_FUNCTION( item );
         if ( x > m )
         {
            m = x;
         }
      }
   }

   // get precision value to compare to
   p = sqrt( m ) * precision;

   // go through each item, check that its symmetric items are p close to each other
   for ( i = 0; ( ( i < rows ) && ( result == 1 ) ); i++ )
   {
      for ( j = i + 1; j < columns; j++ )
      {
         item = pa[i * columns + j];
         item1 = NEGATE_FUNCTION( item );
         item2 = ADD_FUNCTION( pa[j * columns + i], item1 );
         x = SQUARED_MAGNITUDE_FUNCTION( item2 );
         DISPOSE_FUNCTION( item1 );
         DISPOSE_FUNCTION( item2 );

         x = sqrt( x );
         if ( x > p )
         {
            result = 0;
            break;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_approximately_hermitian_symmetric
*/

int32_t
Matvec_is_approximately_hermitian_symmetric( Prefix )( Matvec_type( Prefix ) *current, Magnitude_type precision )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   PRECONDITION( "precision not negative", precision >= 0.0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   Magnitude_type m = 0;
   Magnitude_type x = 0;
   Magnitude_type p = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type item = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;
   Type item4 = DEFAULT_VALUE;

   // get squared magnitude of largest item
   item = pa[0];
   m = SQUARED_MAGNITUDE_FUNCTION( item );

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = pa[i * columns + j];
         x = SQUARED_MAGNITUDE_FUNCTION( item );
         if ( x > m )
         {
            m = x;
         }
      }
   }

   // get precision value to compare to
   p = sqrt( m ) * precision;

   // go through each item, check that its symmetric items are p close to each other
   for ( i = 0; ( ( i < rows ) && ( result == 1 ) ); i++ )
   {
      for ( j = i + 1; j < columns; j++ )
      {
         item = pa[i * columns + j];
         item1 = pa[j * columns + i];
         item2 = CONJUGATE_FUNCTION( item1 );
         item3 = NEGATE_FUNCTION( item2 );
         item4 = ADD_FUNCTION( item, item3 );
         x = SQUARED_MAGNITUDE_FUNCTION( item4 );
         DISPOSE_FUNCTION( item2 );
         DISPOSE_FUNCTION( item3 );
         DISPOSE_FUNCTION( item4 );

         x = sqrt( x );
         if ( x > p )
         {
            result = 0;
            break;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_equal
*/

int32_t
Matvec_is_equal( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   for ( i = 0; ( ( i < rows ) && ( result == 1 ) ); i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         result = EQUAL_FUNCTION( pa[i * columns + j], pa_other[i * columns + j] );
         if ( result == 0 )
         {
            break;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_is_approximately_equal
*/

int32_t
Matvec_is_approximately_equal( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other, Magnitude_type precision )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   PRECONDITION( "precision not negative", precision >= 0.0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   Magnitude_type m = 0;
   Magnitude_type x = 0;
   Magnitude_type p = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type item = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;

   // get squared magnitude of largest item
   item = pa[0];
   m = SQUARED_MAGNITUDE_FUNCTION( item );

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = pa[i * columns + j];
         x = SQUARED_MAGNITUDE_FUNCTION( item );
         if ( x > m )
         {
            m = x;
         }

         item = pa_other[i * columns + j];
         x = SQUARED_MAGNITUDE_FUNCTION( item );
         if ( x > m )
         {
            m = x;
         }
      }
   }

   // get precision value to compare to
   p = sqrt( m ) * precision;

   // go through each item in current, check that its items are p close to
   // corresponding item in other
   for ( i = 0; ( ( i < rows ) && ( result == 1 ) ); i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = pa[i * columns + j];
         item1 = pa_other[i * columns + j];
         item2 = NEGATE_FUNCTION( item1 );
         item3 = ADD_FUNCTION( item, item2 );
         x = SQUARED_MAGNITUDE_FUNCTION( item3 );
         DISPOSE_FUNCTION( item2 );
         DISPOSE_FUNCTION( item3 );

         x = sqrt( x );
         if ( x > p )
         {
            result = 0;
            break;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_put
*/

void
Matvec_put( Prefix )( Matvec_type( Prefix ) *current, Type value, int32_t i_row, int32_t i_column )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).a[i_row * (*current).n_columns + i_column] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_put_and_dispose
*/

void
Matvec_put_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Type value, int32_t i_row, int32_t i_column )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // dispose of current item
   DISPOSE_FUNCTION( (*current).a[i_row * (*current).n_rows + i_column] );

   // set item with value
   (*current).a[i_row * (*current).n_columns + i_column] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put
*/

void
Matvec_vector_put( Prefix )( Matvec_type( Prefix ) *current, Type value, int32_t i )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( i >= 0 ) && ( i < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( i >= 0 ) && ( i < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).a[i] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_and_dispose
*/

void
Matvec_vector_put_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Type value, int32_t i )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( i >= 0 ) && ( i < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( i >= 0 ) && ( i < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // dispose of current item
   DISPOSE_FUNCTION( (*current).a[i] );

   // set item with value
   (*current).a[i] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_x
*/

void
Matvec_vector_put_x( Prefix )( Matvec_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 0 >= 0 ) && ( 0 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 0 >= 0 ) && ( 0 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).a[0] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_x_and_dispose
*/

void
Matvec_vector_put_x_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 0 >= 0 ) && ( 0 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 0 >= 0 ) && ( 0 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // dispose of current item
   DISPOSE_FUNCTION( (*current).a[0] );

   // set item with value
   (*current).a[0] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_y
*/

void
Matvec_vector_put_y( Prefix )( Matvec_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 1 >= 0 ) && ( 1 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 1 >= 0 ) && ( 1 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).a[1] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_y_and_dispose
*/

void
Matvec_vector_put_y_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 1 >= 0 ) && ( 1 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 1 >= 0 ) && ( 1 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // dispose of current item
   DISPOSE_FUNCTION( (*current).a[1] );

   // set item with value
   (*current).a[1] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_z
*/

void
Matvec_vector_put_z( Prefix )( Matvec_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 2 >= 0 ) && ( 2 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 2 >= 0 ) && ( 2 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).a[2] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_put_z_and_dispose
*/

void
Matvec_vector_put_z_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( ( 2 >= 0 ) && ( 2 < (*current).n_rows ) ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( ( 2 >= 0 ) && ( 2 < (*current).n_columns ) ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // dispose of current item
   DISPOSE_FUNCTION( (*current).a[2] );

   // set item with value
   (*current).a[2] = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_set_from
*/

void
Matvec_set_from( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         SET_FROM( pa[i * columns + j], pa_other[i * columns + j] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_set_from_and_dispose
*/

void
Matvec_set_from_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         DISPOSE_FUNCTION( pa[i * columns + j] );
         SET_FROM( pa[i * columns + j], pa_other[i * columns + j] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_do_and_set_all
*/

void
Matvec_do_and_set_all( Prefix )( Matvec_type( Prefix ) *current, Matvec_func( Prefix ) func )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "func not null", func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         SET_FROM( pa[i * columns + j], func( pa[i * columns + j] ) );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_do_and_set_all_and_dispose
*/

void
Matvec_do_and_set_all_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Matvec_func( Prefix ) func )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "func not null", func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t index = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type item = DEFAULT_VALUE;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         index = i * columns + j;
         item = func( pa[index] );
         DISPOSE_FUNCTION( ( pa[index] ) );
         pa[index] = item;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_do_and_set_if
*/

void
Matvec_do_and_set_if( Prefix )( Matvec_type( Prefix ) *current, Matvec_func( Prefix ) func, Matvec_test_func( Prefix ) test_func )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "func not null", func != NULL );
   PRECONDITION( "test_func not null", test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t flag = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         flag = test_func( pa[i * columns + j] );
         if( flag == 1 )
         {
            SET_FROM( pa[i * columns + j], func( pa[i * columns + j] ) );
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_do_and_set_if_and_dispose
*/

void
Matvec_do_and_set_if_and_dispose( Prefix )( Matvec_type( Prefix ) *current, Matvec_func( Prefix ) func, Matvec_test_func( Prefix ) test_func )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "func not null", func != NULL );
   PRECONDITION( "test_func not null", test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t flag = 0;
   int32_t index = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type item = DEFAULT_VALUE;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         index = i * columns + j;
         flag = test_func( pa[index] );

         if ( flag == 1 )
         {
            item = func( pa[index] );
            DISPOSE_FUNCTION( ( pa[index] ) );
            pa[index] = item;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_one
*/

Matvec_type( Prefix ) *
Matvec_one( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         if ( i == j )
         {
            pa[ i * columns + j ] = ONE_VALUE;
         }
         else
         {
            pa[ i * columns + j ] = DEFAULT_VALUE;
         }

      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_zero
*/

Matvec_type( Prefix ) *
Matvec_zero( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa[ i * columns + j ] = DEFAULT_VALUE;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_set_to_one
*/

void
Matvec_set_to_one( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         if ( i == j )
         {
            SET_FROM( pa[ i * columns + j ], ONE_VALUE );
         }
         else
         {
            SET_FROM( pa[ i * columns + j ], DEFAULT_VALUE );
         }

      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_set_to_one_and_dispose
*/

void
Matvec_set_to_one_and_dispose( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         DISPOSE_FUNCTION( pa[ i * columns + j ] );
         if ( i == j )
         {
            pa[ i * columns + j ] = ONE_VALUE;
         }
         else
         {
            pa[ i * columns + j ] = DEFAULT_VALUE;
         }

      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_set_to_zero
*/

void
Matvec_set_to_zero( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         SET_FROM( pa[ i * columns + j ], DEFAULT_VALUE );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_set_to_zero_and_dispose
*/

void
Matvec_set_to_zero_and_dispose( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         DISPOSE_FUNCTION( pa[ i * columns + j ] );
         pa[ i * columns + j ] = DEFAULT_VALUE;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_copied
*/

Matvec_type( Prefix ) *
Matvec_copied( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa_result[ i * columns + j ] = DUPLICATE_FUNCTION( pa[ i * columns + j ] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_subcopied
*/

Matvec_type( Prefix ) *
Matvec_subcopied( Prefix )
(
   Matvec_type( Prefix ) *current,
   int32_t i_row,
   int32_t n_row,
   int32_t i_column,
   int32_t n_column
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   PRECONDITION( "n_row OK", ( ( i_row + n_row - 1 >= 0 ) && ( i_row + n_row - 1 < (*current).n_rows ) ) );
   PRECONDITION( "n_column OK", ( ( i_column + n_column - 1 >= 0 ) && ( i_column + n_column - 1 < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( n_row, n_column );
   pa_result = (*result).a;

   for ( i = 0; i < n_column; i++ )
   {
      for ( j = 0; j < n_row; j++ )
      {
         pa_result[ i * n_row + j ]
            = DUPLICATE_FUNCTION( pa[ ( i + i_row ) * rows + j + i_column] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_subcopy
*/

void
Matvec_subcopy( Prefix )
(
   Matvec_type( Prefix ) *current,
   Matvec_type( Prefix ) *other,
   int32_t i_row,
   int32_t i_row_other,
   int32_t n_row_other,
   int32_t i_column,
   int32_t i_column_other,
   int32_t n_column_other
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   PRECONDITION( "i_row_other OK", ( ( i_row_other >= 0 ) && ( i_row_other < (*other).n_rows ) ) );
   PRECONDITION( "i_column_other OK", ( ( i_column_other >= 0 ) && ( i_column_other < (*other).n_columns ) ) );
   PRECONDITION( "n_row_other OK", ( ( i_row_other + n_row_other - 1 >= 0 ) && ( i_row_other + n_row_other - 1 < (*other).n_rows ) ) );
   PRECONDITION( "n_column_other OK", ( ( i_column_other + n_column_other - 1 >= 0 ) && ( i_column_other + n_column_other - 1 < (*other).n_columns ) ) );
   PRECONDITION( "n_row_other in current OK", ( ( i_row + n_row_other - 1 >= 0 ) && ( i_row + n_row_other - 1 < (*current).n_rows ) ) );
   PRECONDITION( "n_column_other in current OK", ( ( i_column + n_column_other - 1 >= 0 ) && ( i_column + n_column_other - 1 < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t columns = (*current).n_columns;
   int32_t columns_other = (*other).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   // write over part of current
   for ( i = 0; i < n_column_other; i++ )
   {
      for ( j = 0; j < n_row_other; j++ )
      {
         SET_FROM( pa[ ( i + i_row )*columns + j + i_column], pa_other[ ( i + i_row_other )*columns_other + j + i_column_other] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_subcopy_and_dispose
*/

void
Matvec_subcopy_and_dispose( Prefix )
(
   Matvec_type( Prefix ) *current,
   Matvec_type( Prefix ) *other,
   int32_t i_row,
   int32_t i_row_other,
   int32_t n_row_other,
   int32_t i_column,
   int32_t i_column_other,
   int32_t n_column_other
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   PRECONDITION( "i_row_other OK", ( ( i_row_other >= 0 ) && ( i_row_other < (*other).n_rows ) ) );
   PRECONDITION( "i_column_other OK", ( ( i_column_other >= 0 ) && ( i_column_other < (*other).n_columns ) ) );
   PRECONDITION( "n_row_other OK", ( ( i_row_other + n_row_other - 1 >= 0 ) && ( i_row_other + n_row_other - 1 < (*other).n_rows ) ) );
   PRECONDITION( "n_column_other OK", ( ( i_column_other + n_column_other - 1 >= 0 ) && ( i_column_other + n_column_other - 1 < (*other).n_columns ) ) );
   PRECONDITION( "n_row_other in current OK", ( ( i_row + n_row_other - 1 >= 0 ) && ( i_row + n_row_other - 1 < (*current).n_rows ) ) );
   PRECONDITION( "n_column_other in current OK", ( ( i_column + n_column_other - 1 >= 0 ) && ( i_column + n_column_other - 1 < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t rows_other = (*other).n_rows;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   // write over part of current
   for ( i = 0; i < n_column_other; i++ )
   {
      for ( j = 0; j < n_row_other; j++ )
      {
         DISPOSE_FUNCTION( pa[ ( i + i_row )*rows + j + i_column] );
         pa[ ( i + i_row )*rows + j + i_column]
            = DUPLICATE_FUNCTION( pa_other[ ( i + i_row_other ) * rows_other + j + i_column_other] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_as_array
*/

Type *
Matvec_as_array( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = (*current).a;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_copy_as_array
*/

Type *
Matvec_copy_as_array( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = NULL;
   int32_t i = 0;
   int32_t count = (*current).n_rows * (*current).n_columns;
   Type *pa = (*current).a;

   result = ( Type * ) calloc( count, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   for ( i = 0; i < count; i++ )
   {
      result[i] = DUPLICATE_FUNCTION( pa[i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_from_row
*/

Matvec_type( Prefix ) *
Matvec_vector_from_row( Prefix )( Matvec_type( Prefix ) *current, int32_t i_column )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make_row_vector( Prefix )( (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      pa_result[i] = DUPLICATE_FUNCTION( pa[ i_column * columns + i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_from_column
*/

Matvec_type( Prefix ) *
Matvec_vector_from_column( Prefix )
( Matvec_type( Prefix ) *current, int32_t i_row )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make_column_vector( Prefix )( (*current).n_rows );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      pa_result[i] = DUPLICATE_FUNCTION( pa[ i * columns + i_row] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_row_vector_dot
*/

Type
Matvec_row_vector_dot( Prefix )( Matvec_type( Prefix ) *current, int32_t i_row_1, int32_t i_row_2 )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row_1 OK", ( ( i_row_1 >= 0 ) && ( i_row_1 < (*current).n_rows ) ) );
   PRECONDITION( "i_row_2 OK", ( ( i_row_2 >= 0 ) && ( i_row_2 < (*current).n_rows ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < columns; i++ )
   {
      item1 = CONJUGATE_FUNCTION( pa[ i_row_2 * columns + i] );
      item2 = MULTIPLY_FUNCTION( pa[ i_row_1 * columns + i], item1 );
      result = ADD_FUNCTION( result, item2 );
      DISPOSE_FUNCTION( item1 );
      DISPOSE_FUNCTION( item2 );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_row_vector_squared_magnitude
*/

Magnitude_type
Matvec_row_vector_squared_magnitude( Prefix )( Matvec_type( Prefix ) *current, int32_t i_row )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Magnitude_type result = 0;
   int32_t i = 0;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < columns; i++ )
   {
      result = result + SQUARED_MAGNITUDE_FUNCTION( pa[ i_row * columns + i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_row_vector_scale
*/

void
Matvec_row_vector_scale( Prefix )( Matvec_type( Prefix ) *current, Type scale, int32_t i_row )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_row OK", ( ( i_row >= 0 ) && ( i_row < (*current).n_rows ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < columns; i++ )
   {
      item = MULTIPLY_FUNCTION( scale, pa[ i_row * columns + i] );
      SET_FROM( pa[ i_row * columns + i], item );
      DISPOSE_FUNCTION( item );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_column_vector_dot
*/

Type
Matvec_column_vector_dot( Prefix )( Matvec_type( Prefix ) *current, int32_t i_column_1, int32_t i_column_2 )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_column_1 OK", ( ( i_column_1 >= 0 ) && ( i_column_1 < (*current).n_columns ) ) );
   PRECONDITION( "i_column_2 OK", ( ( i_column_2 >= 0 ) && ( i_column_2 < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t columns = (*current).n_columns;
   int32_t rows = (*current).n_rows;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      item1 = CONJUGATE_FUNCTION( pa[ i * columns + i_column_2] );
      item2 = MULTIPLY_FUNCTION( pa[ i * columns + i_column_1], item1 );
      result = ADD_FUNCTION( result, item2 );
      DISPOSE_FUNCTION( item1 );
      DISPOSE_FUNCTION( item2 );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_column_vector_squared_magnitude
*/

Magnitude_type
Matvec_column_vector_squared_magnitude( Prefix )( Matvec_type( Prefix ) *current, int32_t i_column )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Magnitude_type result = 0;
   int32_t i = 0;
   int32_t columns = (*current).n_columns;
   int32_t rows = (*current).n_rows;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      result = result + SQUARED_MAGNITUDE_FUNCTION( pa[ i * columns + i_column] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_column_vector_scale
*/

void
Matvec_column_vector_scale( Prefix )( Matvec_type( Prefix ) *current, Type scale, int32_t i_column )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i_column OK", ( ( i_column >= 0 ) && ( i_column < (*current).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t columns = (*current).n_columns;
   int32_t rows = (*current).n_rows;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      item = MULTIPLY_FUNCTION( scale, pa[ i * columns + i_column] );
      SET_FROM( pa[ i * columns + i_column], item );
      DISPOSE_FUNCTION( item );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_add
*/

void
Matvec_add( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         SET_FROM( pa[i * columns + j], ADD_FUNCTION( pa[i * columns + j], pa_other[i * columns + j] ) );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_added
*/

Matvec_type( Prefix ) *
Matvec_added( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         pa_result[i * columns + j] = ADD_FUNCTION( pa[i * columns + j], pa_other[i * columns + j] );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_subtract
*/

void
Matvec_subtract( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item1 = NEGATE_FUNCTION( pa_other[i * columns + j] );
         item2 = ADD_FUNCTION( pa[i * columns + j], item1 );
         SET_FROM( pa[i * columns + j], item2 );
         DISPOSE_FUNCTION( item1 );
         DISPOSE_FUNCTION( item2 );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_subtracted
*/

Matvec_type( Prefix ) *
Matvec_subtracted( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item1 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item1 = NEGATE_FUNCTION( pa_other[i * columns + j] );
         pa_result[i * columns + j] = ADD_FUNCTION( pa[i * columns + j], item1 );
         DISPOSE_FUNCTION( item1 );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_multiply
*/

void
Matvec_multiply( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "other is square", ( (*other).n_rows == (*other).n_columns ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *temp = NULL;
   Type item1 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   int32_t other_rows = (*other).n_rows;
   int32_t other_columns = (*other).n_columns;
   Type item = DEFAULT_VALUE;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_temp = NULL;

   temp = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_temp = (*temp).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < other_columns; j++ )
      {
         item = DEFAULT_VALUE;
         for( k = 0; k < columns; k++ )
         {
            item1 = MULTIPLY_FUNCTION( pa[i * columns + k], pa_other[k * columns + j] );
            item = ADD_FUNCTION( item, item1 );
            DISPOSE_FUNCTION( item1 );
         }
         pa_temp[i * columns + j] = item;
      }
   }

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < other_rows; j++ )
      {
         SET_FROM( pa[i * columns + j], pa_temp[i * columns + j] );
      }
   }

   Matvec_deep_dispose( Prefix )( &temp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_multiplied
*/

Matvec_type( Prefix ) *
Matvec_multiplied( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are sized OK", ( (*current).n_columns == (*other).n_rows ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item1 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   int32_t other_columns = (*other).n_columns;
   Type item = DEFAULT_VALUE;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_result = NULL;

   result  = Matvec_make( Prefix )( (*current).n_rows, (*other).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < other_columns; j++ )
      {
         item = DEFAULT_VALUE;
         for( k = 0; k < columns; k++ )
         {
            item1 = MULTIPLY_FUNCTION( pa[i * columns + k], pa_other[k * other_columns + j] );
            item = ADD_FUNCTION( item, item1 );
            DISPOSE_FUNCTION( item1 );
         }
         pa_result[i * other_columns + j] = item;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_normalize
*/

void
Matvec_vector_normalize( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item1 = DEFAULT_VALUE;
   Magnitude_type scale = 0;
   int32_t i = 0;
   int32_t n = 0;
   Type *pa = (*current).a;

   if ( (*current).n_rows > (*current).n_columns )
   {
      n = (*current).n_rows;
   }
   else
   {
      n = (*current).n_columns;
   }

   // get magnitude inverse for scaling factor
   for ( i = 0; i < n; i++ )
   {
      scale = scale + SQUARED_MAGNITUDE_FUNCTION( pa[i] );
   }

   scale = 1.0 / sqrt( scale );

   for ( i = 0; i < n; i++ )
   {
      item1 = MULTIPLY_FUNCTION( scale, pa[i] );
      SET_FROM( pa[i], item1 );
      DISPOSE_FUNCTION( item1 );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_normalized
*/

Matvec_type( Prefix ) *
Matvec_vector_normalized( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Magnitude_type scale = 0;
   int32_t i = 0;
   int32_t n = 0;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   if ( (*current).n_rows > (*current).n_columns )
   {
      n = (*current).n_rows;
      result = Matvec_make_column_vector( Prefix )( n );
   }
   else
   {
      n = (*current).n_columns;
      result = Matvec_make_row_vector( Prefix )( n );
   }

   pa_result = (*result).a;

   // get magnitude inverse for scaling factor
   for ( i = 0; i < n; i++ )
   {
      scale = scale + SQUARED_MAGNITUDE_FUNCTION( pa[i] );
   }

   scale = 1.0 / sqrt( scale );

   for ( i = 0; i < n; i++ )
   {
      pa_result[i] = MULTIPLY_FUNCTION( scale, pa[i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_dot
*/

Type
Matvec_vector_dot( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "other not null", current != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "other is vector", ( ( (*other).n_rows == 1 ) || ( (*other).n_columns == 1  ) ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t n = 0;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   if ( (*current).n_rows == 1 )
   {
      n = (*current).n_columns;
   }
   else
   {
      n = (*current).n_rows;
   }

   for ( i = 0; i < n; i++ )
   {
      item1 = CONJUGATE_FUNCTION( pa_other[i] );
      item2 = MULTIPLY_FUNCTION( pa[i], item1 );
      result = ADD_FUNCTION( result, item2 );
      DISPOSE_FUNCTION( item1 );
      DISPOSE_FUNCTION( item2 );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_vector_cross
*/

void
Matvec_vector_cross( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "other is vector", ( ( (*other).n_rows == 1 ) || ( (*other).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( (*current).n_rows == 3 ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( (*current).n_columns == 3 ) : 1 );
   PRECONDITION( "i_row_other OK",    ( (*other).n_columns == 1 ) ? ( (*other).n_rows == 3 ) : 1 );
   PRECONDITION( "i_column_other OK", ( (*other).n_rows == 1 )    ? ( (*other).n_columns == 3 ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *temp = NULL;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t n = 0;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_temp = NULL;

   if ( (*current).n_rows > (*current).n_columns )
   {
      n = 3;
      temp = Matvec_make_column_vector( Prefix )( n );
   }
   else
   {
      n = 3;
      temp = Matvec_make_row_vector( Prefix )( n );
   }

   pa_temp = (*temp).a;

   item1 = MULTIPLY_FUNCTION( pa[1], pa_other[2] );
   item2 = MULTIPLY_FUNCTION( pa[2], pa_other[1] );
   item3 = NEGATE_FUNCTION( item2 );
   pa_temp[0] = ADD_FUNCTION( item1, item3 );
   DISPOSE_FUNCTION( item1 );
   DISPOSE_FUNCTION( item2 );
   DISPOSE_FUNCTION( item3 );

   item1 = MULTIPLY_FUNCTION( pa[2], pa_other[0] );
   item2 = MULTIPLY_FUNCTION( pa[0], pa_other[2] );
   item3 = NEGATE_FUNCTION( item2 );
   pa_temp[1] = ADD_FUNCTION( item1, item3 );
   DISPOSE_FUNCTION( item1 );
   DISPOSE_FUNCTION( item2 );
   DISPOSE_FUNCTION( item3 );

   item1 = MULTIPLY_FUNCTION( pa[0], pa_other[1] );
   item2 = MULTIPLY_FUNCTION( pa[1], pa_other[0] );
   item3 = NEGATE_FUNCTION( item2 );
   pa_temp[2] = ADD_FUNCTION( item1, item3 );
   DISPOSE_FUNCTION( item1 );
   DISPOSE_FUNCTION( item2 );
   DISPOSE_FUNCTION( item3 );

   for ( i = 0; i < n; i++ )
   {
      SET_FROM( pa[i], pa_temp[i] );
   }

   Matvec_deep_dispose( Prefix )( &temp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_vector_crossed
*/

Matvec_type( Prefix ) *
Matvec_vector_crossed( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is vector", ( ( (*current).n_rows == 1 ) || ( (*current).n_columns == 1  ) ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "other is vector", ( ( (*other).n_rows == 1 ) || ( (*other).n_columns == 1  ) ) );
   PRECONDITION( "i_row OK",    ( (*current).n_columns == 1 ) ? ( (*current).n_rows == 3 ) : 1 );
   PRECONDITION( "i_column OK", ( (*current).n_rows == 1 )    ? ( (*current).n_columns == 3 ) : 1 );
   PRECONDITION( "i_row_other OK",    ( (*other).n_columns == 1 ) ? ( (*other).n_rows == 3 ) : 1 );
   PRECONDITION( "i_column_other OK", ( (*other).n_rows == 1 )    ? ( (*other).n_columns == 3 ) : 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_result = NULL;

   if ( (*current).n_rows > (*current).n_columns )
   {
      result = Matvec_make_column_vector( Prefix )( 3 );
   }
   else
   {
      result = Matvec_make_row_vector( Prefix )( 3 );
   }

   pa_result = (*result).a;

   item1 = MULTIPLY_FUNCTION( pa[1], pa_other[2] );
   item2 = MULTIPLY_FUNCTION( pa[2], pa_other[1] );
   item3 = NEGATE_FUNCTION( item2 );
   pa_result[0] = ADD_FUNCTION( item1, item3 );
   DISPOSE_FUNCTION( item1 );
   DISPOSE_FUNCTION( item2 );
   DISPOSE_FUNCTION( item3 );

   item1 = MULTIPLY_FUNCTION( pa[2], pa_other[0] );
   item2 = MULTIPLY_FUNCTION( pa[0], pa_other[2] );
   item3 = NEGATE_FUNCTION( item2 );
   pa_result[1] = ADD_FUNCTION( item1, item3 );
   DISPOSE_FUNCTION( item1 );
   DISPOSE_FUNCTION( item2 );
   DISPOSE_FUNCTION( item3 );

   item1 = MULTIPLY_FUNCTION( pa[0], pa_other[1] );
   item2 = MULTIPLY_FUNCTION( pa[1], pa_other[0] );
   item3 = NEGATE_FUNCTION( item2 );
   pa_result[2] = ADD_FUNCTION( item1, item3 );
   DISPOSE_FUNCTION( item1 );
   DISPOSE_FUNCTION( item2 );
   DISPOSE_FUNCTION( item3 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_item_by_item_multiply
*/

void
Matvec_item_by_item_multiply( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = MULTIPLY_FUNCTION( pa[i * columns + j], pa_other[i * columns + j ] );
         SET_FROM( pa[i * columns + j], item );
         DISPOSE_FUNCTION( item );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_item_by_item_multiplied
*/

Matvec_type( Prefix ) *
Matvec_item_by_item_multiplied( Prefix )( Matvec_type( Prefix ) *current, Matvec_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == MATVEC_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "current and other are same size", ( ( (*current).n_rows == (*other).n_rows ) && ( (*current).n_columns == (*other).n_columns ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_other = (*other).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = MULTIPLY_FUNCTION( pa[i * columns + j], pa_other[i * columns + j ] );
         pa_result[i * columns + j] =  item ;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_scale
*/

void
Matvec_scale( Prefix )( Matvec_type( Prefix ) *current, Type scale )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = MULTIPLY_FUNCTION( scale, pa[i * columns + j] );
         SET_FROM( pa[i * columns + j], item );
         DISPOSE_FUNCTION( item );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_scaled
*/

Matvec_type( Prefix ) *
Matvec_scaled( Prefix )( Matvec_type( Prefix ) *current, Type scale )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = MULTIPLY_FUNCTION( scale, pa[i * columns + j] );
         pa_result[i * columns + j] = item ;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_negate
*/

void
Matvec_negate( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = NEGATE_FUNCTION( pa[i * columns + j] );
         SET_FROM( pa[i * columns + j], item );
         DISPOSE_FUNCTION( item );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_negated
*/

Matvec_type( Prefix ) *
Matvec_negated( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = NEGATE_FUNCTION( pa[i * columns + j] );
         pa_result[i * columns + j] = item ;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_transpose
*/

void
Matvec_transpose( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = i; j < columns; j++ )
      {
         item1 = pa[i * columns + j];
         item2 = pa[j * columns + i];
         pa[i * columns + j] = item2;
         pa[j * columns + i] = item1;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_transposed
*/

Matvec_type( Prefix ) *
Matvec_transposed( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_columns, (*current).n_rows );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = pa[i * columns + j];
         pa_result[j * rows + i] = DUPLICATE_FUNCTION( item );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_hermitian_transpose
*/

void
Matvec_hermitian_transpose( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = i; j < rows; j++ )
      {
         item1 = CONJUGATE_FUNCTION( pa[i * columns + j] );
         item2 = CONJUGATE_FUNCTION( pa[j * columns + i] );
         SET_FROM( pa[i * columns + j], item2 );
         SET_FROM( pa[j * columns + i], item1 );
         DISPOSE_FUNCTION( item1 );
         DISPOSE_FUNCTION( item2 );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_hermitian_transposed
*/

Matvec_type( Prefix ) *
Matvec_hermitian_transposed( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_columns, (*current).n_rows );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = CONJUGATE_FUNCTION( pa[i * columns + j] );
         pa_result[j * rows + i] = item;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_conjugate
*/

void
Matvec_conjugate( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = CONJUGATE_FUNCTION( pa[i * columns + j] );
         SET_FROM( pa[i * columns + j], item );
         DISPOSE_FUNCTION( item );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_conjugated
*/

Matvec_type( Prefix ) *
Matvec_conjugated( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *result = NULL;
   Type item = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;
   Type *pa_result = NULL;

   result = Matvec_make( Prefix )( (*current).n_rows, (*current).n_columns );
   pa_result = (*result).a;

   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         item = CONJUGATE_FUNCTION( pa[i * columns + j] );
         pa_result[i * columns + j] = item ;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_invert
*/

void
Matvec_invert( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *a = NULL;
   Matvec_type( Prefix ) *b = NULL;
   Type item = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;
   Type item4 = DEFAULT_VALUE;
   int32_t flag = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa_current = (*current).a;
   Type *pa = NULL;
   Type *pb = NULL;


   a = Matvec_make_from( Prefix )( current );
   pa = (*a).a;

   b = Matvec_make( Prefix )( (*current).n_columns, (*current).n_rows );
   pb = (*b).a;

   // set b to identity matrix
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         if ( i == j )
         {
            pb[i * columns + j ] = ONE_VALUE;
         }
         else
         {
            pb[i * columns + j ] = DEFAULT_VALUE;
         }
      }
   }

   // compute inverse by elimination
   for ( i = 0; i < rows; i++ )
   {
      // if main diagonal value is zero, resort the remaining columns
      if ( EQUAL_FUNCTION( pa_current[i * columns + i], DEFAULT_VALUE ) == 1 )
      {
         for ( j = i + 1; ( ( j < rows ) && ( flag == 0 ) ); j++ )
         {
            if ( EQUAL_FUNCTION( pa[j * columns + i], DEFAULT_VALUE ) == 0 )
            {
               for( k = 0; k < rows; k++ )
               {
                  item = pa[i * columns + k];
                  pa[i * columns + k] = pa[j * columns + k];
                  pa[j * columns + k] = item;
                  item = pb[i * columns + k];
                  pb[i * columns + k] = pb[j * columns + k];
                  pb[j * columns + k] = item;
               }
               flag = 1;
            }
         }
      }

      // get the inverse of the element on the diagonal, want to make it one
      item1 = INVERSE_FUNCTION( pa[i * columns + i] );

      // do same thing to original matrix and identity matrix
      for ( j = 0; j < columns; j++ )
      {
         item2 = MULTIPLY_FUNCTION( pa[i * columns + j], item1 );
         SET_FROM( pa[i * columns + j], item2 );
         DISPOSE_FUNCTION( item2 );

         item2 = MULTIPLY_FUNCTION( pb[i * columns + j], item1 );
         SET_FROM( pb[i * columns + j], item2 );
         DISPOSE_FUNCTION( item2 );
      }

      DISPOSE_FUNCTION( item1 );

      // now subtract multiple of row i to make other elements in column i zero
      for ( k = 0; k < rows; k++ )
      {
         if ( k != i )
         {
            item1 = pa[k * columns + i];

            for( j = 0; j < columns; j++ )
            {
               item2 = MULTIPLY_FUNCTION( pa[i * columns + j], item1 );
               item3 = NEGATE_FUNCTION( item2 );
               item4 = ADD_FUNCTION( pa[k * columns + j], item3 );
               SET_FROM( pa[k * columns + j], item4 );
               DISPOSE_FUNCTION( item2 );
               DISPOSE_FUNCTION( item3 );
               DISPOSE_FUNCTION( item4 );

               item2 = MULTIPLY_FUNCTION( pb[i * columns + j], item1 );
               item3 = NEGATE_FUNCTION( item2 );
               item4 = ADD_FUNCTION( pb[k * columns + j], item3 );
               SET_FROM( pb[k * columns + j], item4 );
               DISPOSE_FUNCTION( item2 );
               DISPOSE_FUNCTION( item3 );
               DISPOSE_FUNCTION( item4 );

            }

            DISPOSE_FUNCTION( item1 );
         }
      }

   }

   // set current from a
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         SET_FROM( pa_current[i * columns + j], pb[i * columns + j] );
      }
   }

   Matvec_deep_dispose( Prefix )( &a );
   Matvec_deep_dispose( Prefix )( &b );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Matvec_inverted
*/

Matvec_type( Prefix ) *
Matvec_inverse( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *a = NULL;
   Matvec_type( Prefix ) *b = NULL;
   Type item = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;
   Type item4 = DEFAULT_VALUE;
   int32_t flag = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa_current = (*current).a;
   Type *pa = NULL;
   Type *pb = NULL;

   a = Matvec_make_from( Prefix )( current );
   pa = (*a).a;

   b = Matvec_make( Prefix )( (*current).n_columns, (*current).n_rows );
   pb = (*b).a;

   // set b to identity matrix
   for ( i = 0; i < rows; i++ )
   {
      for ( j = 0; j < columns; j++ )
      {
         if ( i == j )
         {
            pb[i * columns + j ] = ONE_VALUE;
         }
         else
         {
            pb[i * columns + j ] = DEFAULT_VALUE;
         }
      }
   }

   // compute inverse by elimination
   for ( i = 0; i < rows; i++ )
   {
      // if main diagonal value is zero, resort the remaining columns
      if ( EQUAL_FUNCTION( pa_current[i * columns + i], DEFAULT_VALUE ) == 1 )
      {
         flag = 0;
         for ( j = i; ( ( j < rows ) && ( flag == 0 ) ); j++ )
         {
            if ( EQUAL_FUNCTION( pa[j * columns + i], DEFAULT_VALUE ) == 0 )
            {
               for( k = 0; k < rows; k++ )
               {
                  item = pa[i * columns + k];
                  pa[i * columns + k] = pa[j * columns + k];
                  pa[j * columns + k] = item;
                  item = pb[i * columns + k];
                  pb[i * columns + k] = pb[j * columns + k ];
                  pb[j * columns + k] = item;
               }
               flag = 1;
            }
         }
      }

      item1 = INVERSE_FUNCTION( pa[i * columns + i] );

      for ( j = 0; j < columns; j++ )
      {
         item2 = MULTIPLY_FUNCTION( pa[i * columns + j], item1 );
         SET_FROM( pa[i * columns + j], item2 );
         DISPOSE_FUNCTION( item2 );

         item2 = MULTIPLY_FUNCTION( pb[i * columns + j], item1 );
         SET_FROM( pb[i * columns + j], item2 );
         DISPOSE_FUNCTION( item2 );
      }

      DISPOSE_FUNCTION( item1 );

      for ( k = 0; k < rows; k++ )
      {
         if ( k != i )
         {
            item1 = pa[k * columns + i];

            for( j = 0; j < columns; j++ )
            {
               item2 = MULTIPLY_FUNCTION( pa[i * columns + j], item1 );
               item3 = NEGATE_FUNCTION( item2 );
               item4 = ADD_FUNCTION( pa[k * columns + j], item3 );
               SET_FROM( pa[k * columns + j], item4 );
               DISPOSE_FUNCTION( item2 );
               DISPOSE_FUNCTION( item3 );
               DISPOSE_FUNCTION( item4 );

               item2 = MULTIPLY_FUNCTION( pb[i * columns + j], item1 );
               item3 = NEGATE_FUNCTION( item2 );
               item4 = ADD_FUNCTION( pb[k * columns + j], item3 );
               SET_FROM( pb[k * columns + j], item4 );
               DISPOSE_FUNCTION( item2 );
               DISPOSE_FUNCTION( item3 );
               DISPOSE_FUNCTION( item4 );

            }

            DISPOSE_FUNCTION( item1 );
         }
      }

   }

   Matvec_deep_dispose( Prefix )( &a );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return b;
}

/**
   Matvec_determinant
*/

Type
Matvec_determinant( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Prefix ) *a = NULL;
   Type result = ONE_VALUE;
   Type factor = DEFAULT_VALUE;
   Type item = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   Type item2 = DEFAULT_VALUE;
   Type item3 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   int32_t flag = 0;
   Type *pa_current = (*current).a;
   Type *pa = NULL;

   // Use Gauss-Jordan elimination to transform the matrix into
   // an upper-triangular form (all matrix entries below the main
   // diagonal equal to zero). The determinant of the transformed matrix
   // is equal to the product of the entries on the main diagonal, and
   // is also equal to the determinant of the original matrix.

   a = Matvec_make_from( Prefix )( current );
   pa = (*a).a;

   for ( i = 0; ( ( i < rows ) && ( EQUAL_FUNCTION( result, DEFAULT_VALUE ) == 0 ) ); i++ )
   {

      // if main diagonal value is zero, resort with one of the remaining columns
      if ( EQUAL_FUNCTION( pa_current[i * columns + i], DEFAULT_VALUE ) == 1 )
      {
         flag = 0;
         for ( j = i + 1; ( ( j < rows ) && ( flag == 0 ) ); j++ )
         {
            if ( EQUAL_FUNCTION( pa[j * columns + i], DEFAULT_VALUE ) == 0 )
            {
               for( k = 0; k < rows; k++ )
               {
                  item = pa[i * columns + k];
                  pa[i * columns + k] = pa[j * columns + k];
                  pa[j * columns + k] = item;
               }
               // For Gauss-Jordan elimination,
               // if we swap columns, the determinant
               // gets multiplied by -1
               item = NEGATE_FUNCTION( result );
               DISPOSE_FUNCTION( result );
               result = item;
               flag = 1;
            }
         }
      }

      // if after the resorting attempts, the main diagonal value is
      // still zero, then the determinant is definitely zero
      if ( EQUAL_FUNCTION( pa[i * columns + i], DEFAULT_VALUE ) == 0 )
      {
         // eliminate the items below the main diagonal to transform
         // to upper triangular form
         for( j = i + 1; j < rows; j++ )
         {
            if ( EQUAL_FUNCTION( pa[j * columns + i], DEFAULT_VALUE ) == 0 )
            {
               item1 = INVERSE_FUNCTION( pa[i * columns + i] );
               factor = MULTIPLY_FUNCTION( pa[j * columns + i], item1 );
               DISPOSE_FUNCTION( item1 );
               for( k = 0; k < rows; k++ )
               {
                  item1 = MULTIPLY_FUNCTION( factor, pa[i * columns + k] );
                  item2 = NEGATE_FUNCTION( item1 );
                  item3 = ADD_FUNCTION( pa[j * columns + k], item2 );
                  SET_FROM( pa[j * columns + k], item3 );
                  DISPOSE_FUNCTION( item1 );
                  DISPOSE_FUNCTION( item2 );
                  DISPOSE_FUNCTION( item3 );
               }
               DISPOSE_FUNCTION( factor );
            }
         }
      }
      else
      {
         result = DEFAULT_VALUE;
      }

   }

   // calculate the product of the entries on the main diagonal as the determinant
   for( i = 0; i < rows; i++ )
   {
      item1 = MULTIPLY_FUNCTION( result, pa[i * columns + i ] );
      SET_FROM( result, item1 );
      DISPOSE_FUNCTION( item1 );
   }

   Matvec_deep_dispose( Prefix )( &a );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Matvec_trace
*/

Type
Matvec_trace( Prefix )( Matvec_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == MATVEC_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "current is square", ( (*current).n_rows == (*current).n_columns ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = DEFAULT_VALUE;
   Type item1 = DEFAULT_VALUE;
   int32_t i = 0;
   int32_t rows = (*current).n_rows;
   int32_t columns = (*current).n_columns;
   Type *pa = (*current).a;

   // sum the entries on the main diagonal
   for ( i = 0; i < rows; i++ )
   {
      item1 = ADD_FUNCTION( result, pa[i * columns + i] );
      SET_FROM( result, item1 );
      DISPOSE_FUNCTION( item1 );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/* End of file */


/**
 @file Lsqline.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Lsqlines"

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

 Function definitions for the opaque lsqline_t type.

*/

#include "Lsqline.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   Lsqline structure
*/

struct lsqline_struct
{
   int32_t _type;

   int32_t capacity;
   int32_t index;

   float32_t *x;
   float32_t *y;
   float32_t *x_sq;
   float32_t *y_sq;
   float32_t *xy;

   float32_t x_sum;
   float32_t y_sum;
   float32_t x_sq_sum;
   float32_t y_sq_sum;
   float32_t xy_sum;

   int32_t is_output_valid;

   float32_t slope;
   float32_t y_intercept;
   float32_t fit;
};

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
storage_not_null( lsqline_t *p )
{
   int32_t result = 0;

   if ( (*p).x != NULL )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      result = 0;
      if ( (*p).y != NULL )
      {
         result = 1;
      }
   }

   if ( result == 1 )
   {
      result = 0;
      if ( (*p).x_sq != NULL )
      {
         result = 1;
      }
   }

   if ( result == 1 )
   {
      result = 0;
      if ( (*p).y_sq != NULL )
      {
         result = 1;
      }
   }

   if ( result == 1 )
   {
      result = 0;
      if ( (*p).xy != NULL )
      {
         result = 1;
      }
   }

   return result;
}

static
int32_t
positive_capacity( lsqline_t *p )
{
   int32_t result = 1;

   result = ( (*p).capacity > 0 );

   return result;
}

static
int32_t
nonnegative_index( lsqline_t *p )
{
   int32_t result = 1;

   result = ( (*p).index >= 0 );

   return result;
}

static
void invariant( lsqline_t *p )
{
   assert( ( ( void ) "storage_not_null", storage_not_null( p ) ) );
   assert( ( ( void ) "positive_capacity", positive_capacity( p ) ) );
   assert( ( ( void ) "nonnegative_index", nonnegative_index( p ) ) );
   return;
}

#endif

/**
   lsqline_make
*/

lsqline_t *
lsqline_make( int32_t capacity )
{
   PRECONDITION( "capacity ok", capacity > 0 );

   // allocate Lsqline struct
   lsqline_t * current
      = ( lsqline_t * ) calloc( 1, sizeof( lsqline_t ) );
   CHECK( "current allocated correctly", current != NULL );

   // set type
   (*current)._type = LSQLINE_TYPE;

   // set capacity
   (*current).capacity = capacity;

   // set index
   (*current).index = 0;

   // set flag
   (*current).is_output_valid = 0;

   // set input point count
   (*current).is_output_valid = 0;

   // allocate storage
   (*current).x = ( float32_t * ) calloc( capacity, sizeof( float32_t ) );
   CHECK( "(*current).x allocated correctly", (*current).x != NULL );

   (*current).y = ( float32_t * ) calloc( capacity, sizeof( float32_t ) );
   CHECK( "(*current).y allocated correctly", (*current).y != NULL );

   (*current).x_sq = ( float32_t * ) calloc( capacity, sizeof( float32_t ) );
   CHECK( "(*current).x_sq allocated correctly", (*current).x_sq != NULL );

   (*current).y_sq = ( float32_t * ) calloc( capacity, sizeof( float32_t ) );
   CHECK( "(*current).y_sq allocated correctly", (*current).y_sq != NULL );

   (*current).xy = ( float32_t * ) calloc( capacity, sizeof( float32_t ) );
   CHECK( "(*current).xy allocated correctly", (*current).xy != NULL );

   INVARIANT( current );

   return current;
}

/**
   lsqline_clone
*/

lsqline_t *
lsqline_clone( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current  );

   int32_t i = 0;

   // allocate Lsqline struct
   lsqline_t * result
      = ( lsqline_t * ) calloc( 1, sizeof( lsqline_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = LSQLINE_TYPE;

   // copy from current
   (*result).capacity = (*current).capacity;
   (*result).index = (*current).index;
   (*result).is_output_valid = (*current).is_output_valid;

   // allocate storage
   (*result).x = ( float32_t * ) calloc(  (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).x allocated correctly", (*result).x != NULL );

   (*result).y = ( float32_t * )  calloc(  (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).y allocated correctly", (*result).y != NULL );

   (*result).x_sq = ( float32_t * ) calloc( (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).x_sq allocated correctly", (*result).x_sq != NULL );

   (*result).y_sq = ( float32_t * ) calloc( (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).y_sq allocated correctly", (*result).y_sq != NULL );

   (*result).xy = ( float32_t * ) calloc( (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).xy allocated correctly", (*result).xy != NULL );

   // copy data
   for ( i = 0; i < (*current).capacity; i++ )
   {
      (*result).x[i] = (*current).x[i];
      (*result).y[i] = (*current).y[i];
      (*result).x_sq[i] = (*current).x_sq[i];
      (*result).y_sq[i] = (*current).y_sq[i];
      (*result).xy[i] = (*current).xy[i];
   }

   (*result).x_sum = (*current).x_sum;
   (*result).y_sum = (*current).y_sum;
   (*result).x_sq_sum = (*current).x_sq_sum;
   (*result).y_sq_sum = (*current).y_sq_sum;
   (*result).xy_sum = (*current).xy_sum;

   (*result).slope = (*current).slope;
   (*result).y_intercept = (*current).y_intercept;
   (*result).fit = (*current).fit;

   INVARIANT( result );

   return result;
}

/**
   lsqline_deep_clone
*/

lsqline_t *
lsqline_deep_clone( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current  );

   int32_t i = 0;

   // allocate Lsqline struct
   lsqline_t * result
      = ( lsqline_t * ) calloc( 1, sizeof( lsqline_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = LSQLINE_TYPE;

   // copy from current
   (*result).capacity = (*current).capacity;
   (*result).index = (*current).index;
   (*result).is_output_valid = (*current).is_output_valid;

   // allocate storage
   (*result).x = ( float32_t * ) calloc(  (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).x allocated correctly", (*result).x != NULL );

   (*result).y = ( float32_t * )  calloc(  (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).y allocated correctly", (*result).y != NULL );

   (*result).x_sq = ( float32_t * ) calloc( (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).x_sq allocated correctly", (*result).x_sq != NULL );

   (*result).y_sq = ( float32_t * ) calloc( (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).y_sq allocated correctly", (*result).y_sq != NULL );

   (*result).xy = ( float32_t * ) calloc( (*current).capacity, sizeof( float32_t ) );
   CHECK( "(*result).xy allocated correctly", (*result).xy != NULL );

   // copy data
   for ( i = 0; i < (*current).capacity; i++ )
   {
      (*result).x[i] = (*current).x[i];
      (*result).y[i] = (*current).y[i];
      (*result).x_sq[i] = (*current).x_sq[i];
      (*result).y_sq[i] = (*current).y_sq[i];
      (*result).xy[i] = (*current).xy[i];
   }

   (*result).x_sum = (*current).x_sum;
   (*result).y_sum = (*current).y_sum;
   (*result).x_sq_sum = (*current).x_sq_sum;
   (*result).y_sq_sum = (*current).y_sq_sum;
   (*result).xy_sum = (*current).xy_sum;

   (*result).slope = (*current).slope;
   (*result).y_intercept = (*current).y_intercept;
   (*result).fit = (*current).fit;

   INVARIANT( result );

   return result;
}

/**
   lsqline_is_equal
*/

int32_t
lsqline_is_equal( lsqline_t *current, lsqline_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", (*current)._type == LSQLINE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", (*other)._type == LSQLINE_TYPE );

   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;

   // check capacity
   if ( (*current).capacity != (*other).capacity )
   {
      result = 0;
   }

   // check index
   if ( result == 1 )
   {
      if ( (*current).index != (*other).index )
      {
         result = 0;
      }
   }

   // check is_output_valid
   if ( result == 1 )
   {
      if ( (*current).is_output_valid != (*other).is_output_valid )
      {
         result = 0;
      }
   }

   // check history
   if ( result == 1 )
   {
      for ( i = 0; i < (*current).index; i++ )
      {
         if (
            ( (*current).x[i] != (*other).x[i] )
            ||
            ( (*current).y[i] != (*other).y[i] )
            ||
            ( (*current).x_sq[i] != (*other).x_sq[i] )
            ||
            ( (*current).y_sq[i] != (*other).y_sq[i] )
            ||
            ( (*current).xy[i] != (*other).xy[i] )
         )
         {
            result = 0;
         }
      }
   }

   // check results
   if ( result == 1 )
   {
      result = 0;
      if (
         ( (*current).x_sum == (*other).x_sum )
         &&
         ( (*current).y_sum == (*other).y_sum )
         &&
         ( (*current).x_sq_sum == (*other).x_sq_sum )
         &&
         ( (*current).y_sq_sum == (*other).y_sq_sum )
         &&
         ( (*current).xy_sum == (*other).xy_sum )
         &&
         ( (*current).slope == (*other).slope )
         &&
         ( (*current).y_intercept == (*other).y_intercept )
         &&
         ( (*current).fit == (*other).fit )
      )
      {
         result = 1;
      }
   }

   INVARIANT( current );

   return result;
}

/**
   lsqline_is_deep_equal
*/

int32_t
lsqline_is_deep_equal( lsqline_t *current, lsqline_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", (*current)._type == LSQLINE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", (*other)._type == LSQLINE_TYPE );

   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;

   // check capacity
   if ( (*current).capacity != (*other).capacity )
   {
      result = 0;
   }

   // check index
   if ( result == 1 )
   {
      if ( (*current).index != (*other).index )
      {
         result = 0;
      }
   }

   // check is_output_valid
   if ( result == 1 )
   {
      if ( (*current).is_output_valid != (*other).is_output_valid )
      {
         result = 0;
      }
   }

   // check history
   if ( result == 1 )
   {
      for ( i = 0; i < (*current).index; i++ )
      {
         if (
            ( (*current).x[i] != (*other).x[i] )
            ||
            ( (*current).y[i] != (*other).y[i] )
            ||
            ( (*current).x_sq[i] != (*other).x_sq[i] )
            ||
            ( (*current).y_sq[i] != (*other).y_sq[i] )
            ||
            ( (*current).xy[i] != (*other).xy[i] )
         )
         {
            result = 0;
         }
      }
   }

   // check results
   if ( result == 1 )
   {
      result = 0;
      if (
         ( (*current).x_sum == (*other).x_sum )
         &&
         ( (*current).y_sum == (*other).y_sum )
         &&
         ( (*current).x_sq_sum == (*other).x_sq_sum )
         &&
         ( (*current).y_sq_sum == (*other).y_sq_sum )
         &&
         ( (*current).xy_sum == (*other).xy_sum )
         &&
         ( (*current).slope == (*other).slope )
         &&
         ( (*current).y_intercept == (*other).y_intercept )
         &&
         ( (*current).fit == (*other).fit )
      )
      {
         result = 1;
      }
   }

   INVARIANT( current );

   return result;
}

/**
   lsqline_copy
*/

void
lsqline_copy( lsqline_t *current, lsqline_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", (*current)._type == LSQLINE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", (*other)._type == LSQLINE_TYPE );

   INVARIANT( current );

   int32_t i = 0;

   if ( (*current).capacity != (*other).capacity )
   {
      free( (*current).x );
      free( (*current).y );
      free( (*current).x_sq );
      free( (*current).y_sq );
      free( (*current).xy );

      (*current).capacity = (*other).capacity;

      // re-allocate storage
      (*current).x = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).x allocated correctly", (*current).x != NULL );

      (*current).y = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).y allocated correctly", (*current).y != NULL );

      (*current).x_sq = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).x_sq allocated correctly", (*current).x_sq != NULL );

      (*current).y_sq = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).y_sq allocated correctly", (*current).y_sq != NULL );

      (*current).xy = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).xy allocated correctly", (*current).xy != NULL );

   }

   (*current).index = (*other).index;
   (*current).is_output_valid = (*other).is_output_valid;

   // copy history
   for ( i = 0; i < (*other).capacity; i++ )
   {
      (*current).x[i] = (*other).x[i];
      (*current).y[i] = (*other).y[i];
      (*current).x_sq[i] = (*other).x_sq[i];
      (*current).y_sq[i] = (*other).y_sq[i];
      (*current).xy[i] = (*other).xy[i];
   }

   // copy results
   (*current).x_sum = (*other).x_sum;
   (*current).y_sum = (*other).y_sum;
   (*current).x_sq_sum = (*other).x_sq_sum;
   (*current).y_sq_sum = (*other).y_sq_sum;
   (*current).xy_sum = (*other).xy_sum;

   (*current).slope = (*other).slope;
   (*current).y_intercept = (*other).y_intercept;
   (*current).fit = (*other).fit;

   INVARIANT( current );

   return;
}

/**
   lsqline_deep_copy
*/

void
lsqline_deep_copy( lsqline_t *current, lsqline_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", (*current)._type == LSQLINE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", (*other)._type == LSQLINE_TYPE );

   INVARIANT( current );

   int32_t i = 0;

   if ( (*current).capacity != (*other).capacity )
   {
      free( (*current).x );
      free( (*current).y );
      free( (*current).x_sq );
      free( (*current).y_sq );
      free( (*current).xy );

      (*current).capacity = (*other).capacity;

      // re-allocate storage
      (*current).x = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).x allocated correctly", (*current).x != NULL );

      (*current).y = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).y allocated correctly", (*current).y != NULL );

      (*current).x_sq = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).x_sq allocated correctly", (*current).x_sq != NULL );

      (*current).y_sq = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).y_sq allocated correctly", (*current).y_sq != NULL );

      (*current).xy = ( float32_t * ) calloc( (*other).capacity, sizeof( float32_t ) );
      CHECK( "(*current).y allocated correctly", (*current).y != NULL );

   }

   (*current).index = (*other).index;
   (*current).is_output_valid = (*other).is_output_valid;

   // copy history
   for ( i = 0; i < (*other).capacity; i++ )
   {
      (*current).x[i] = (*other).x[i];
      (*current).y[i] = (*other).y[i];
      (*current).x_sq[i] = (*other).x_sq[i];
      (*current).y_sq[i] = (*other).y_sq[i];
      (*current).xy[i] = (*other).xy[i];
   }

   // copy results
   (*current).x_sum = (*other).x_sum;
   (*current).y_sum = (*other).y_sum;
   (*current).x_sq_sum = (*other).x_sq_sum;
   (*current).y_sq_sum = (*other).y_sq_sum;
   (*current).xy_sum = (*other).xy_sum;

   (*current).slope = (*other).slope;
   (*current).y_intercept = (*other).y_intercept;
   (*current).fit = (*other).fit;

   INVARIANT( current );

   return;
}

/**
   lsqline_dispose
*/

void
lsqline_dispose( lsqline_t **current )
{
   PRECONDITION( "Lsqline not null", current != NULL );
   PRECONDITION( "*Lsqline not null", *current != NULL );
   PRECONDITION( "Lsqline type OK", (**current)._type == LSQLINE_TYPE );
   INVARIANT(*current);

   // delete
   free( (**current).x );
   (**current).x = NULL;

   free( (**current).y );
   (**current).y = NULL;

   free( (**current).x_sq );
   (**current).x_sq = NULL;

   free( (**current).y_sq );
   (**current).y_sq = NULL;

   free( (**current).xy );
   (**current).xy = NULL;

   // delete Lsqline struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   lsqline_deep_dispose
*/

void
lsqline_deep_dispose( lsqline_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == LSQLINE_TYPE );
   INVARIANT(*current);

   // delete
   free( (**current).x );
   (**current).x = NULL;

   free( (**current).y );
   (**current).y = NULL;

   free( (**current).x_sq );
   (**current).x_sq = NULL;

   free( (**current).y_sq );
   (**current).y_sq = NULL;

   free( (**current).xy );
   (**current).xy = NULL;

   // delete Lsqline struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   lsqline_capacity
*/

int32_t
lsqline_capacity( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).capacity;

   INVARIANT( current );

   return result;
}

/**
   lsqline_count
*/

int32_t
lsqline_count( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).index;

   INVARIANT( current );

   return result;
}

/**
   lsqline_is_output_valid
*/

int32_t
lsqline_is_output_valid( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).is_output_valid;

   INVARIANT( current );

   return result;
}

/**
   lsqline_slope
*/

float32_t
lsqline_slope( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   float32_t result = 0.0;

   result = (*current).slope;

   INVARIANT( current );

   return result;
}

/**
   lsqline_y_intercept
*/

float32_t
lsqline_y_intercept( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   float32_t result = 0.0;

   result = (*current).y_intercept;

   INVARIANT( current );

   return result;
}

/**
   lsqline_fit
*/

float32_t
lsqline_fit( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   float32_t result = 0.0;

   result = (*current).fit;

   INVARIANT( current );

   return result;
}


/**
   lsqline_compute
*/
void
lsqline_compute( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   float32_t n_inverse = 0.0;
   float32_t SSxx = 0.0;
   float32_t SSyy = 0.0;
   float32_t SSxy = 0.0;

   n_inverse = 1.0 / ( ( float32_t ) (*current).index );

   // calculate SSxx
   SSxx = (*current).x_sq_sum - n_inverse * (*current).x_sum * (*current).x_sum;

   if ( ( SSxx == 0.0 ) || ( (*current).index <= 1 ) )
   {
      // output is not valid, will have division by zero down the line
      // or too few data points
      (*current).is_output_valid = 0;
      (*current).slope = 0.0;
      (*current).y_intercept = 0.0;
      (*current).fit = 0.0;
   }
   else
   {
      // output will be valid
      (*current).is_output_valid = 1;

      // more calculation
      SSyy = (*current).y_sq_sum - n_inverse * (*current).y_sum * (*current).y_sum;
      SSxy = (*current).xy_sum   - n_inverse * (*current).x_sum * (*current).y_sum;

      // slope
      (*current).slope = SSxy / SSxx;

      // y intercept
      (*current).y_intercept
         = n_inverse * ( (*current).y_sum - (*current).slope * (*current).x_sum );

      // fit
      (*current).fit = SSyy - (*current).slope * SSxy;
   }

   INVARIANT( current );

   return;
}

/**
   lsqline_put
*/

void
lsqline_put( lsqline_t *current, float32_t x, float32_t y )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   int32_t old_capacity = 0;
   int32_t index = 0;

   // get current index
   index = (*current).index;

   // increase storage if data count exceeds capacity
   if ( index >= (*current).capacity )
   {
      old_capacity = (*current).capacity;
      (*current).capacity = 2 * (*current).capacity;

      // reallocate storage
      (*current).x = ( float32_t * ) realloc( (*current).x, (*current).capacity * sizeof( float32_t ) );
      CHECK( "(*current).x allocated correctly", (*current).x != NULL );
      memset( &(*current).x[old_capacity], 0, old_capacity * sizeof( float32_t ) );

      (*current).y = ( float32_t * ) realloc( (*current).y, (*current).capacity * sizeof( float32_t ) );
      CHECK( "(*current).y allocated correctly", (*current).y != NULL );
      memset( &(*current).y[old_capacity], 0, old_capacity * sizeof( float32_t ) );

      (*current).x_sq = ( float32_t * ) realloc( (*current).x_sq, (*current).capacity * sizeof( float32_t ) );
      CHECK( "(*current).x_sq allocated correctly", (*current).x_sq != NULL );
      memset( &(*current).x_sq[old_capacity], 0, old_capacity * sizeof( float32_t ) );

      (*current).y_sq = ( float32_t * ) realloc( (*current).y_sq, (*current).capacity * sizeof( float32_t ) );
      CHECK( "(*current).y_sq allocated correctly", (*current).y_sq != NULL );
      memset( &(*current).y_sq[old_capacity], 0, old_capacity * sizeof( float32_t ) );

      (*current).xy = ( float32_t * ) realloc( (*current).xy, (*current).capacity * sizeof( float32_t ) );
      CHECK( "(*current).xy allocated correctly", (*current).xy != NULL );
      memset( &(*current).xy[old_capacity], 0, old_capacity * sizeof( float32_t ) );

   }

   // put in new x,y contributions
   (*current).x[ index ]    =   x;
   (*current).y[ index ]    =   y;
   (*current).x_sq[ index ] = x * x;
   (*current).y_sq[ index ] = y * y;
   (*current).xy[ index ]   = x * y;

   (*current).x_sum    = (*current).x_sum    +   x;
   (*current).y_sum    = (*current).y_sum    +   y;
   (*current).x_sq_sum = (*current).x_sq_sum + x * x;
   (*current).y_sq_sum = (*current).y_sq_sum + y * y;
   (*current).xy_sum   = (*current).xy_sum   + x * y;

   // update index
   (*current).index = index + 1;

   // computation no longer valid
   (*current).is_output_valid = 0;

   INVARIANT( current );

   return;
}

/**
   lsqline_reset
*/

void
lsqline_reset( lsqline_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSQLINE_TYPE );
   INVARIANT( current );

   // clear current index
   (*current).index = 0;

   // set internal variables to zero
   (*current).x_sum    = 0;
   (*current).y_sum    = 0;
   (*current).x_sq_sum = 0;
   (*current).y_sq_sum = 0;
   (*current).xy_sum   = 0;

   // put in new x,y contributions
   memset( (*current).x, 0, (*current).capacity * sizeof( float32_t ) );
   memset( (*current).y, 0, (*current).capacity * sizeof( float32_t ) );
   memset( (*current).x_sq, 0, (*current).capacity * sizeof( float32_t ) );
   memset( (*current).y_sq, 0, (*current).capacity * sizeof( float32_t ) );
   memset( (*current).xy, 0, (*current).capacity * sizeof( float32_t ) );

   INVARIANT( current );

   return;
}

/* End of file */


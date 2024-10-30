/**
 @file Rng_isaac_gaussian.c
 @author Greg Lee
 @version 2.0.0
 @brief: "ISAAC (pseudo) Random Number Generator for gaussian distribution"

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

 Function definitions for the opaque rng_isaac_gaussian_t type.

*/

#include "Rng_Isaac.h"
#include "Rng_Isaac_gaussian.h"

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
   rng_isaac_gaussian structure
*/

struct rng_isaac_gaussian_struct
{
   int32_t _type;

   // length, mask
   rng_isaac_t *rng;

   // internals for gaussian numbers
   int32_t index;
   float64_t gaussian_value_1;
   float64_t gaussian_value_2;

   // multithread values if we include threading support
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Function to compute gaussian random numbers

   Uses Box-Muller algorithm to compute two gaussian random numbers
   from two evenly distributed randoms x and y on [0,1]
   when x*x + y*y < 1.0
*/
static
void
set_gaussian_values( rng_isaac_gaussian_t *rng )
{
   PRECONDITION( "rng not null", rng != NULL );

   float64_t r = 0.0;
   float64_t factor = 0.0;
   float64_t v1 = 0.0;
   float64_t v2 = 0.0;
   uint64_t temp = 0;

   // look for two randoms that are inside the unit circle
   for( r = 2.0; r > 1.0; )
   {
      // get a float64_t random on [0,1]
      temp = rng_isaac_u64_item( (*rng).rng );
      rng_isaac_forth( (*rng).rng );
      v1 = 2.0 * ( 1.0 * temp / UINT64_MAX ) - 1.0;

      // get another float64_t random on [0,1]
      temp = rng_isaac_u64_item( (*rng).rng );
      rng_isaac_forth( (*rng).rng );
      v2 = 2.0 * ( 1.0 * temp / UINT64_MAX ) - 1.0;

      // see if they're inside the unit circle
      r = v1 * v1 + v2 * v2;
   }

   // apply Box-Muller algo to get two gaussians from two uniform distribution
   // random numbers on [-1,+1], set in structure
   factor = sqrt( -2.0 * log( r ) / r );

   (*rng).gaussian_value_1 = v1 * factor;
   (*rng).gaussian_value_2 = v2 * factor;

   (*rng).index = 0;

   return;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
rng_not_null( rng_isaac_gaussian_t *p )
{
   int32_t result = 0;

   if ( (*p).rng != NULL )
   {
      result = 1;
   }

   return result;
}

static
int32_t
index_ok( rng_isaac_gaussian_t *p )
{
   int32_t result = 0;

   if ( ( (*p).index == 0 ) || ( (*p).index == 1 ) )
   {
      result = 1;
   }

   return result;
}

static
void invariant( rng_isaac_gaussian_t *p )
{
   assert( ( ( void ) "rng not null", rng_not_null( p ) ) );
   assert( ( ( void ) "index ok", index_ok( p ) ) );
   return;
}

#endif

/**
   rng_isaac_gaussian_make
*/

rng_isaac_gaussian_t *
rng_isaac_gaussian_make( void )
{
   // allocate rng gaussian struct
   rng_isaac_gaussian_t * result
      = ( rng_isaac_gaussian_t * ) calloc( 1, sizeof( rng_isaac_gaussian_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RNG_ISAAC_GAUSSIAN_TYPE;

   // set values
   (*result).rng = rng_isaac_make();
   (*result).index = 0;
   (*result).gaussian_value_1 = 0.0;
   (*result).gaussian_value_2 = 0.0;

   // get first gaussian values
   set_gaussian_values( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   rng_isaac_gaussian_make_with_seed
*/

rng_isaac_gaussian_t *
rng_isaac_gaussian_make_with_seed( uint64_t seed )
{
   // allocate rng gaussian struct
   rng_isaac_gaussian_t * result
      = ( rng_isaac_gaussian_t * ) calloc( 1, sizeof( rng_isaac_gaussian_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RNG_ISAAC_GAUSSIAN_TYPE;

   // set values
   (*result).rng = rng_isaac_make_with_seed( seed );
   (*result).index = 0;
   (*result).gaussian_value_1 = 0.0;
   (*result).gaussian_value_2 = 0.0;

   // get first gaussian values
   set_gaussian_values( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}


/**
   rng_isaac_gaussian_dispose
*/

void
rng_isaac_gaussian_dispose( rng_isaac_gaussian_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == RNG_ISAAC_GAUSSIAN_TYPE  );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // free the current
   rng_isaac_dispose( &(**current).rng );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}

/**
   rng_isaac_gaussian_f32_item
*/

float32_t
rng_isaac_gaussian_f32_item( rng_isaac_gaussian_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_GAUSSIAN_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float32_t result = 0.0;

   if ( (*current).index == 0 )
   {
      result = ( float32_t ) (*current).gaussian_value_1;
   }
   else
   {
      result = ( float32_t ) (*current).gaussian_value_2;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_gaussian_f64_item
*/

float64_t
rng_isaac_gaussian_f64_item( rng_isaac_gaussian_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_GAUSSIAN_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float64_t result = 0.0;

   if ( (*current).index == 0 )
   {
      result = (*current).gaussian_value_1;
   }
   else
   {
      result = (*current).gaussian_value_2;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_gaussian_forth
*/

void
rng_isaac_gaussian_forth( rng_isaac_gaussian_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_GAUSSIAN_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // increment index
   ( (*current).index )++;

   // account for gaussian values depleted
   if ( (*current).index > 1 )
   {
      set_gaussian_values( current );
      (*current).index = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/* End of file */


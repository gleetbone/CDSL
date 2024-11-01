/**
 @file Rng_isaac.c
 @author Greg Lee
 @version 2.0.0
 @brief: "ISAAC (pseudo) Random Number Generator"

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

 Function definitions for the opaque rng_isaac_t type.

 Code taken from Bob Jenkin's ISAAC random number generator. As of this writing,
 ISAAC can be found at http://burtleburtle.net/bob/rand/isaacafa.html.

*/

#include "Rng_Isaac.h"

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

#define RANDBUF_LENGTH 256
#define RANDBUF_OFFSET_MASK ((RANDBUF_LENGTH-1)<<3)
#define RAND_BITS 64
#define RAND_HALF_BITS 32

#define UNION_CAST(x, destType) \
 (((union {__typeof__(x) a; destType b;})x).b)

/**
   rng_isaac structure
*/

struct rng_isaac_struct
{
   int32_t _type;

   // length, mask
   int32_t length;
   uint64_t offset_mask;

   // current index into buffer
   int32_t index;

   // global variables
   uint64_t aa;
   uint64_t bb;
   uint64_t cc;

   // internals for gaussian numbers
   int32_t is_next_gaussian_enabled;
   float64_t next_gaussian_value;

   // random number buffers
   uint64_t *randrsl;
   uint64_t *mm;

   // multithread values if we include threading support
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   ISAAC function prototypes
*/

static void randinit( rng_isaac_t *rng, uint64_t seed );

static void isaac64( rng_isaac_t *rng );

/**
   ISAAC function to intialize its random number buffer
*/

#define GOLDEN_RATIO 0x9e3779b97f4a7c13LL

/**
   randinit

   initialize the pseudo random number generator with a seed

   @param current the rng
   @param seed the seed for the rng
*/
static void randinit( rng_isaac_t *current, uint64_t seed )
{
   int32_t i = 0;

   uint64_t a = seed;
   uint64_t b = seed;
   uint64_t c = seed;
   uint64_t d = seed;
   uint64_t e = seed;
   uint64_t f = seed;
   uint64_t g = seed;
   uint64_t h = seed;

   uint64_t *randrsl = (*current).randrsl;
   uint64_t *mm = (*current).mm;

   // set global variables
   (*current).aa = 0;
   (*current).bb = 0;
   (*current).cc = 0;

   // mix up the golden ratios in a through h
   for ( i = 0; i < 4; i++ )
   {
      a -= e;
      f ^= h >> 9;
      h += a;
      b -= f;
      g ^= a << 9;
      a += b;
      c -= g;
      h ^= b >> 23;
      b += c;
      d -= h;
      a ^= c << 15;
      c += d;
      e -= a;
      b ^= d >> 14;
      d += e;
      f -= b;
      c ^= e << 20;
      e += f;
      g -= c;
      d ^= f >> 17;
      f += g;
      h -= d;
      e ^= g << 14;
      g += h;
   }

   for ( i = 0; i < RANDBUF_LENGTH; i += 8 )
   {
      // use the entire buffer as a seed
      a += randrsl[i  ];
      b += randrsl[i + 1];
      c += randrsl[i + 2];
      d += randrsl[i + 3];
      e += randrsl[i + 4];
      f += randrsl[i + 5];
      g += randrsl[i + 6];
      h += randrsl[i + 7];

      // scramble the numbers
      a -= e;
      f ^= h >> 9;
      h += a;
      b -= f;
      g ^= a << 9;
      a += b;
      c -= g;
      h ^= b >> 23;
      b += c;
      d -= h;
      a ^= c << 15;
      c += d;
      e -= a;
      b ^= d >> 14;
      d += e;
      f -= b;
      c ^= e << 20;
      e += f;
      g -= c;
      d ^= f >> 17;
      f += g;
      h -= d;
      e ^= g << 14;
      g += h;

      // set scrambled values into random number buffer
      mm[i  ] = a;
      mm[i + 1] = b;
      mm[i + 2] = c;
      mm[i + 3] = d;
      mm[i + 4] = e;
      mm[i + 5] = f;
      mm[i + 6] = g;
      mm[i + 7] = h;
   }


   // do a second pass
   for ( i = 0; i < RANDBUF_LENGTH; i += 8 )
   {
      // use the entire buffer as a seed
      a += mm[i ];
      b += mm[i + 1];
      c += mm[i + 2];
      d += mm[i + 3];
      e += mm[i + 4];
      f += mm[i + 5];
      g += mm[i + 6];
      h += mm[i + 7];

      // scramble the numbers
      a -= e;
      f ^= h >> 9;
      h += a;
      b -= f;
      g ^= a << 9;
      a += b;
      c -= g;
      h ^= b >> 23;
      b += c;
      d -= h;
      a ^= c << 15;
      c += d;
      e -= a;
      b ^= d >> 14;
      d += e;
      f -= b;
      c ^= e << 20;
      e += f;
      g -= c;
      d ^= f >> 17;
      f += g;
      h -= d;
      e ^= g << 14;
      g += h;

      // set scrambled values into random number buffer
      mm[i  ] = a;
      mm[i + 1] = b;
      mm[i + 2] = c;
      mm[i + 3] = d;
      mm[i + 4] = e;
      mm[i + 5] = f;
      mm[i + 6] = g;
      mm[i + 7] = h;
   }

   // get the first valid random number buffer
   isaac64( current );

   // reset the buffer index
   (*current).index = 0;

   return;
}


/**
   isaac64

   ISAAC function to compute the next random number buffer

   @param current the rng
*/

static void isaac64( rng_isaac_t *current )
{
   register uint64_t a = 0;
   register uint64_t b = 0;
   register uint64_t x = 0;
   register uint64_t y = 0;
   register uint64_t *m = NULL;
   register uint64_t *m2 = NULL;
   register uint64_t *r = NULL;
   register uint64_t *mend = NULL;
   register uint64_t *mm = NULL;

   // set pointers
   m = (*current).mm;
   mm = (*current).mm;
   r = (*current).randrsl;

   // set local variables from global variables
   a = (*current).aa;
   b = (*current).bb + ( ++( (*current).cc ) );

   // compute next buffer of random numbers
   for ( m = mm, mend = m2 = m + ( RANDBUF_LENGTH / 2 ); m < mend; )
   {
      x = *m;
      a = ( ~( a ^ ( a << 21 ) ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;

      x = *m;
      a = ( a ^ ( a >> 5 ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;

      x = *m;
      a = ( a ^ ( a << 12 ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;

      x = *m;
      a = ( a ^ ( a >> 33 ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;
   }

   for ( m2 = mm; m2 < mend; )
   {
      x = *m;
      a = ( ~( a ^ ( a << 21 ) ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;

      x = *m;
      a = ( a ^ ( a >> 5 ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;

      x = *m;
      a = ( a ^ ( a << 12 ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;

      x = *m;
      a = ( a ^ ( a >> 33 ) ) + *( m2++ );
      *( m++ ) = y = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( x ) & RANDBUF_OFFSET_MASK ) ) ) + a + b;
      *( r++ ) = b = ( *( uint64_t * )( ( uint8_t * )( mm ) + ( ( y >> ( 8 ) ) & RANDBUF_OFFSET_MASK ) ) ) + x;
   }

   // update global variables
   (*current).bb = b;
   (*current).aa = a;

   (*current).index = 0;

   return;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
arrays_not_null( rng_isaac_t *p )
{
   int32_t result = 0;

   if ( ( (*p).randrsl != NULL ) && ( (*p).mm != NULL ) )
   {
      result = 1;
   }

   return result;
}

static
void invariant( rng_isaac_t *p )
{
   assert( ( ( void ) "arrays not null", arrays_not_null( p ) ) );
   return;
}

#endif

/**
   rng_isaac_make
*/

rng_isaac_t *
rng_isaac_make( void )
{
   // allocate rng struct
   rng_isaac_t * result
      = ( rng_isaac_t * ) calloc( 1, sizeof( rng_isaac_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RNG_ISAAC_TYPE;

   // set values
   (*result).length = RANDBUF_LENGTH;
   (*result).offset_mask = RANDBUF_OFFSET_MASK;
   (*result).index = 0;
   (*result).aa = 0;
   (*result).bb = 0;
   (*result).cc = 0;

   // allocate arrays
   (*result).randrsl = ( uint64_t * ) calloc( RANDBUF_LENGTH, sizeof( int64_t ) );
   CHECK( "(*result).randrsl allocated correctly", (*result).randrsl != NULL );

   (*result).mm = ( uint64_t * ) calloc( RANDBUF_LENGTH, sizeof( int64_t ) );
   CHECK( "(*result).mm allocated correctly", (*result).mm != NULL );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // initialize rng
   randinit( result, GOLDEN_RATIO );

   INVARIANT( result );

   return result;
}

/**
   rng_isaac_make_with_seed
*/

rng_isaac_t *
rng_isaac_make_with_seed( uint64_t seed )
{
   // allocate rng struct
   rng_isaac_t * result
      = ( rng_isaac_t * ) calloc( 1, sizeof( rng_isaac_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RNG_ISAAC_TYPE;

   // set values
   (*result).length = RANDBUF_LENGTH;
   (*result).offset_mask = RANDBUF_OFFSET_MASK;
   (*result).index = 0;
   (*result).aa = 0;
   (*result).bb = 0;
   (*result).cc = 0;

   // allocate arrays
   (*result).randrsl = ( uint64_t * ) calloc( RANDBUF_LENGTH, sizeof( int64_t ) );
   CHECK( "(*result).randrsl allocated correctly", (*result).randrsl != NULL );

   (*result).mm = ( uint64_t * ) calloc( RANDBUF_LENGTH, sizeof( int64_t ) );
   CHECK( "(*result).mm allocated correctly", (*result).mm != NULL );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // initialize rng
   randinit( result, seed );

   INVARIANT( result );

   return result;
}


/**
   rng_isaac_dispose
*/

void
rng_isaac_dispose( rng_isaac_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == RNG_ISAAC_TYPE  );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // free the arrays
   free( (**current).randrsl );
   (**current).randrsl = NULL;

   free( (**current).mm );
   (**current).mm = NULL;

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   rng_isaac_i32_item
*/

int32_t
rng_isaac_i32_item( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   uint64_t temp = 0;

   temp = (*current).randrsl[ (*current).index ];
   result = UNION_CAST( ( temp >> RAND_HALF_BITS ), int32_t );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_u32_item
*/

uint32_t
rng_isaac_u32_item( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t result = 0;
   uint64_t temp = 0;

   temp = (*current).randrsl[ (*current).index ];
   result = UNION_CAST( ( temp >> RAND_HALF_BITS ), uint32_t );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_i64_item
*/

int64_t
rng_isaac_i64_item( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t result = 0;
   uint64_t temp = 0;

   temp = (*current).randrsl[ (*current).index ];
   result = UNION_CAST( temp, int64_t );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_u64_item
*/

uint64_t
rng_isaac_u64_item( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t result = 0;

   result = (*current).randrsl[ (*current).index ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_f32_item
*/

float32_t
rng_isaac_f32_item( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float32_t result = 0.0;
   uint64_t temp = 0;
   uint32_t temp1 = 0;

   temp = (*current).randrsl[ (*current).index ];
   temp1 = UNION_CAST( ( temp >> RAND_HALF_BITS ), uint32_t );

   result = 1.0 * temp1 / UINT32_MAX;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_f64_item
*/

float64_t
rng_isaac_f64_item( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float64_t result = 0.0;
   uint64_t temp = 0;

   temp = (*current).randrsl[ (*current).index ];

   result = 1.0 * temp / UINT64_MAX;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   rng_isaac_forth
*/

void
rng_isaac_forth( rng_isaac_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RNG_ISAAC_TYPE  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // increment index
   ( (*current).index )++;

   // account for wrap around
   if ( (*current).index == (*current).length )
   {
      isaac64( current );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/* End of file */


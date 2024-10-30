/**
 @file Date_Time_Duration.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Date-Time Duration class"

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

 Function definitions for the opaque date_time_duration_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Date_Time_Duration.h"

#include <Date_Time_Duration.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define MILLISECONDS_IN_SECOND 1000
#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24
#define MINUTES_IN_DAY HOURS_IN_DAY*MINUTES_IN_HOUR
#define MILLISECONDS_IN_MINUTE 1000*SECONDS_IN_MINUTE
#define SECONDS_IN_HOUR 60*SECONDS_IN_MINUTE
#define MILLISECONDS_IN_HOUR 1000*SECONDS_IN_HOUR
#define SECONDS_IN_DAY 24*SECONDS_IN_HOUR
#define MILLISECONDS_IN_DAY 1000*SECONDS_IN_DAY

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 60*SECONDS_IN_MINUTE
#define SECONDS_IN_DAY 24*SECONDS_IN_HOUR
#define SECONDS_IN_YEAR 365*SECONDS_IN_DAY
#define SECONDS_IN_LEAP_YEAR 366*SECONDS_IN_DAY

#define MAX_MILLISECONDS_IN_SECOND 999
#define MAX_SECONDS_IN_MINUTE 59
#define MAX_MINUTES_IN_HOUR 59
#define MAX_HOURS_IN_DAY 23
#define MAX_HOURS_IN_DAY_12 11

/**
   date_time_duration structure
*/

struct date_time_duration_struct
{
   int32_t _type;

   date_time_t *start_dt;
   date_time_t *end_dt;

   int32_t is_definite;
   int64_t duration_milliseconds;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   dhms to milliseconds
*/
static
int64_t
dhms_to_milliseconds
(
   int32_t days,
   int32_t hours,
   int32_t minutes,
   int32_t seconds,
   int32_t milliseconds
)
{
   int64_t result = 0;

   result
      =  milliseconds
         + seconds * MILLISECONDS_IN_SECOND
         + minutes * MILLISECONDS_IN_MINUTE
         + hours * MILLISECONDS_IN_HOUR
         + days * MILLISECONDS_IN_DAY;

   return result;
}

/**
   milliseconds_to_dhms
*/
static
void
milliseconds_to_dhms
(
   int64_t msecs,
   int32_t *days,
   int32_t *hours_24,
   int32_t *minutes,
   int32_t *seconds,
   int32_t *mseconds
)
{
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   d = ( int32_t ) ( msecs / ( ( int64_t ) MILLISECONDS_IN_DAY ) );

   h  =  ( int32_t )
         (
            ( msecs - d * ( ( int64_t ) MILLISECONDS_IN_DAY ) )
            /
            ( ( int64_t ) MILLISECONDS_IN_HOUR )
         );

   m  =  ( int32_t )
         (
            (
               msecs - d * ( ( int64_t ) MILLISECONDS_IN_DAY )
               - h * ( ( int64_t ) MILLISECONDS_IN_HOUR )
            )
            /
            ( ( int64_t ) MILLISECONDS_IN_MINUTE )
         );

   s  =  ( int32_t )
         (
            (
               msecs - d * ( ( int64_t ) MILLISECONDS_IN_DAY )
               - h * ( ( int64_t ) MILLISECONDS_IN_HOUR )
               - m * ( ( int64_t ) MILLISECONDS_IN_MINUTE )
            )
            /
            ( ( int64_t ) MILLISECONDS_IN_SECOND )
         );

   ms = ( int32_t ) ( msecs % ( ( int64_t ) MILLISECONDS_IN_SECOND ) );

   *days = d;
   *hours_24 = h;
   *minutes = m;
   *seconds = s;
   *mseconds = ms;

   return;
}

#if INVARIANT_CONDITIONAL != 0

static
int32_t
duration_nonnegative( date_time_duration_t *current )
{
   int32_t result = 0;

   result = ( (*current).duration_milliseconds >= 0 );

   return result;
}

static
int32_t
start_valid( date_time_duration_t *current )
{
   int32_t result = 1;

   if ( (*current).is_definite == 1 )
   {
      result = ( (*current).start_dt != NULL );
   }

   return result;
}

static
int32_t
end_valid( date_time_duration_t *current )
{
   int32_t result = 1;

   if ( (*current).is_definite == 1 )
   {
      result = ( (*current).end_dt != NULL );
   }

   return result;
}

static
void invariant( date_time_duration_t *current )
{
   assert( ( ( void ) "duration nonnegative", duration_nonnegative( current ) ) );
   assert( ( ( void ) "start valid", start_valid( current ) ) );
   assert( ( ( void ) "end valid", end_valid( current ) ) );
   return;
}

#endif

/**
   date_time_duration_make_start_end
*/

date_time_duration_t *
date_time_duration_make_start_end
(
   date_time_t *start_dt,
   date_time_t *end_dt
)
{
   PRECONDITION( "start_dt not null", start_dt != NULL );
   PRECONDITION( "end_dt not null", end_dt != NULL );
   PRECONDITION( "end after start", date_time_is_greater_than_or_equal( end_dt, start_dt ) == 1 );

   // allocate date_time_duration struct
   date_time_duration_t *result = ( date_time_duration_t * ) calloc( 1, sizeof( date_time_duration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_TYPE;

   // set is_definite
   (*result).is_definite = 1;

   // set start
   (*result).start_dt = date_time_clone( start_dt );

   // set end
   (*result).end_dt = date_time_clone( end_dt );

   // set duration
   (*result).duration_milliseconds = date_time_difference( (*result).start_dt, (*result).end_dt );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_make_start_dhms
*/

date_time_duration_t *
date_time_duration_make_start_dhms
(
   date_time_t *start_dt,
   int32_t days,
   int32_t hour_24,
   int32_t minute,
   int32_t second,
   int32_t millisecond
)
{
   PRECONDITION( "start_dt not null", start_dt != NULL );
   PRECONDITION( "days ok", ( days >= 0 ) );
   PRECONDITION( "hour_24 ok", ( hour_24 >= 0 ) && ( hour_24 <= MAX_HOURS_IN_DAY ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );

   int64_t milliseconds = 0;

   // allocate date_time_duration struct
   date_time_duration_t *result = ( date_time_duration_t * ) calloc( 1, sizeof( date_time_duration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_TYPE;

   // set is_definite
   (*result).is_definite = 1;

   // set start
   (*result).start_dt = date_time_clone( start_dt );

   // set end
   (*result).end_dt = date_time_clone( start_dt );
   milliseconds = dhms_to_milliseconds( days, hour_24, minute, second, millisecond );
   date_time_add_delta_milliseconds( (*result).end_dt, milliseconds );

   // set duration
   (*result).duration_milliseconds = date_time_difference( (*result).start_dt, (*result).end_dt );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_make_start_milliseconds
*/

date_time_duration_t *
date_time_duration_make_start_milliseconds
(
   date_time_t *start_dt,
   int64_t milliseconds
)
{
   PRECONDITION( "start_dt not null", start_dt != NULL );
   PRECONDITION( "milliseconds ok", milliseconds >= 0 );

   // allocate date_time_duration struct
   date_time_duration_t *result = ( date_time_duration_t * ) calloc( 1, sizeof( date_time_duration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_TYPE;

   // set is_definite
   (*result).is_definite = 1;

   // set start
   (*result).start_dt = date_time_clone( start_dt );

   // set end
   (*result).end_dt = date_time_clone( start_dt );
   date_time_add_delta_milliseconds( (*result).end_dt, milliseconds );

   // set duration
   (*result).duration_milliseconds = date_time_difference( (*result).start_dt, (*result).end_dt );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_make_dhms
*/

date_time_duration_t *
date_time_duration_make_dhms
(
   int32_t days,
   int32_t hour_24,
   int32_t minute,
   int32_t second,
   int32_t millisecond
)
{
   PRECONDITION( "days ok", ( days >= 0 ) );
   PRECONDITION( "hour_24 ok", ( hour_24 >= 0 ) && ( hour_24 <= MAX_HOURS_IN_DAY ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );

   // allocate date_time_duration struct
   date_time_duration_t *result = ( date_time_duration_t * ) calloc( 1, sizeof( date_time_duration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_TYPE;

   // set is_definite
   (*result).is_definite = 0;

   // set start
   (*result).start_dt = NULL;

   // set end
   (*result).end_dt = NULL;

   // set duration
   (*result).duration_milliseconds = dhms_to_milliseconds( days, hour_24, minute, second, millisecond );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_make_milliseconds
*/

date_time_duration_t *
date_time_duration_make_milliseconds
(
   int64_t milliseconds
)
{
   // allocate date_time_duration struct
   date_time_duration_t *result = ( date_time_duration_t * ) calloc( 1, sizeof( date_time_duration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_TYPE;

   // set is_definite
   (*result).is_definite = 0;

   // set start
   (*result).start_dt = NULL;

   // set end
   (*result).end_dt = NULL;

   // set duration
   (*result).duration_milliseconds = milliseconds;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_clone
*/

date_time_duration_t *
date_time_duration_clone( date_time_duration_t *current )
{
   PRECONDITION( "date_time_duration not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );

   date_time_duration_t *result = NULL;

   // allocate date_time_duration struct
   result = ( date_time_duration_t * ) calloc( 1, sizeof( date_time_duration_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_TYPE;

   // lock mutex
   LOCK( (*current).mutex );

   if ( (*current).is_definite == 1 )
   {
      (*result).start_dt = date_time_clone( (*current).start_dt );
      (*result).end_dt = date_time_clone( (*current).end_dt );
   }
   (*result).is_definite = (*current).is_definite;
   (*result).duration_milliseconds = (*current).duration_milliseconds;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_deep_clone
*/

date_time_duration_t *
date_time_duration_deep_clone( date_time_duration_t *current )
{
   // deep clone is same as clone for this type
   return date_time_duration_clone( current );
}

/**
  is_equal
*/

static
int32_t
is_equal(  date_time_duration_t *current, date_time_duration_t *other )
{
   int32_t result = 0;

   if ( (*current).is_definite != (*other).is_definite )
   {
      result = 0;
   }
   else
   {
      if ( (*current).is_definite == 1 )
      {
         result = 1;

         if ( date_time_is_equal( (*current).start_dt, (*other).start_dt ) == 0 )
         {
            result = 0;
         }

         if ( date_time_is_equal( (*current).end_dt, (*other).end_dt ) == 0 )
         {
            result = 0;
         }

         if ( (*current).duration_milliseconds != (*other).duration_milliseconds )
         {
            result = 0;
         }
      }

      if ( (*current).is_definite == 0 )
      {
         result = 1;
         if ( (*current).duration_milliseconds != (*other).duration_milliseconds )
         {
            result = 0;
         }
      }

   }

   return result;
};

/**
   date_time_duration_is_equal
*/

int32_t
date_time_duration_is_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_equal( current, other );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_deep_equal
*/

int32_t
date_time_duration_is_deep_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   // is_deep_equal is same as is_equal for this type
   return date_time_duration_is_equal( current, other );
}

/**
   date_time_duration_copy
*/

void
date_time_duration_copy( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   if ( (*other).is_definite == 1 )
   {
      date_time_copy( (*current).start_dt, (*other).start_dt );
      date_time_copy( (*current).end_dt, (*other).end_dt );
   }

   (*current).is_definite = (*other).is_definite;
   (*current).duration_milliseconds = (*other).duration_milliseconds;

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_deep_copy
*/

void
date_time_duration_deep_copy( date_time_duration_t *current, date_time_duration_t *other )
{
   // deep copy is same as copy for this type
   date_time_duration_copy( current, other );
   return;
}

/**
   date_time_duration_dispose
*/

void
date_time_duration_dispose( date_time_duration_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // free start and end times if they exist
   if ( (**current).is_definite == 1 )
   {
      date_time_dispose( &(**current).start_dt );
      date_time_dispose( &(**current).end_dt );
   }

   // delete date_time_duration struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   date_time_duration_deep_dispose
*/

void
date_time_duration_deep_dispose( date_time_duration_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   if ( (**current).is_definite == 1 )
   {
      date_time_dispose( &(**current).start_dt );
      date_time_dispose( &(**current).end_dt );
   }

   // delete date_time_duration struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   date_time_duration_start
*/

date_time_t *
date_time_duration_start( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_t *result = date_time_clone( (*current).start_dt );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_end
*/

date_time_t *
date_time_duration_end( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_t *result = date_time_clone( (*current).end_dt );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_definite
*/

int32_t
date_time_duration_is_definite( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).is_definite;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_duration_milliseconds
*/

int64_t
date_time_duration_duration_milliseconds( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t result = 0;

   result = (*current).duration_milliseconds;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_days_part
*/

int32_t
date_time_duration_days_part( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   milliseconds_to_dhms( (*current).duration_milliseconds, &d, &h, &m, &s, &ms );

   result = d;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_hours_part
*/

int32_t
date_time_duration_hours_part( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   milliseconds_to_dhms( (*current).duration_milliseconds, &d, &h, &m, &s, &ms );

   result = h;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_minutes_part
*/

int32_t
date_time_duration_minutes_part( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   milliseconds_to_dhms( (*current).duration_milliseconds, &d, &h, &m, &s, &ms );

   result = m;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_seconds_part
*/

int32_t
date_time_duration_seconds_part( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   milliseconds_to_dhms( (*current).duration_milliseconds, &d, &h, &m, &s, &ms );

   result = s;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_milliseconds_part
*/

int32_t
date_time_duration_milliseconds_part( date_time_duration_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   milliseconds_to_dhms( (*current).duration_milliseconds, &d, &h, &m, &s, &ms );

   result = ms;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


/**
  is_less_than
*/

static
int32_t
is_less_than( date_time_duration_t *current, date_time_duration_t *other )
{
   int32_t result = 0;

   if ( (*current).duration_milliseconds < (*other).duration_milliseconds )
   {
      result = 1;
   }

   return result;
}

/**
   date_time_duration_is_less_than
*/

int32_t
date_time_duration_is_less_than( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_less_than( current, other );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   is_less_than_or_equal
*/

static
int32_t
is_less_than_or_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   int32_t result = 0;

   if ( (*current).duration_milliseconds <= (*other).duration_milliseconds )
   {
      result = 1;
   }

   return result;
}

/**
   date_time_duration_is_less_than_or_equal
*/

int32_t
date_time_duration_is_less_than_or_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_less_than_or_equal( current, other );

      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   is_greater_than
*/

static
int32_t
is_greater_than( date_time_duration_t *current, date_time_duration_t *other )
{
   int32_t result = 0;

   if ( (*current).duration_milliseconds > (*other).duration_milliseconds )
   {
      result = 1;
   }

   return result;
}


/**
   date_time_duration_is_greater_than
*/

int32_t
date_time_duration_is_greater_than( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_greater_than( current, other );

      UNLOCK( (*other).mutex );

   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   is_greater_than_or_equal
*/

static
int32_t
is_greater_than_or_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   int32_t result = 0;

   if ( (*current).duration_milliseconds >= (*other).duration_milliseconds )
   {
      result = 1;
   }

   return result;
}

/**
   date_time_duration_is_greater_than_or_equal
*/

int32_t
date_time_duration_is_greater_than_or_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = is_greater_than_or_equal( current, other );

      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_compare
*/

int32_t
date_time_duration_compare( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      if ( is_less_than( current, other ) == 1 )
      {
         result = -1;
      }
      else if ( is_equal( current, other ) == 1 )
      {
         result = 0;
      }
      else if ( is_greater_than( current, other ) == 1 )
      {
         result = 1;
      }

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_earlier_than
*/

int32_t
date_time_duration_is_earlier_than( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = date_time_is_less_than( (*current).start_dt, (*other).start_dt );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_earlier_than_or_equal
*/

int32_t
date_time_duration_is_earlier_than_or_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = date_time_is_less_than_or_equal( (*current).start_dt, (*other).start_dt );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_later_than
*/

int32_t
date_time_duration_is_later_than( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = date_time_is_greater_than( (*current).start_dt, (*other).start_dt );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_later_than_or_equal
*/

int32_t
date_time_duration_is_later_than_or_equal( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = date_time_is_greater_than_or_equal( (*current).start_dt, (*other).start_dt );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_start_time_compare
*/

int32_t
date_time_duration_start_time_compare( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      if ( date_time_is_less_than( (*current).start_dt, (*other).start_dt ) == 1 )
      {
         result = -1;
      }
      else if ( date_time_is_equal( (*current).start_dt, (*other).start_dt ) == 1 )
      {
         result = 0;
      }
      else if ( date_time_is_greater_than( (*current).start_dt, (*other).start_dt ) == 1 )
      {
         result = 1;
      }

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_overlap
*/

date_time_duration_t *
date_time_duration_overlap( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_duration_t *result = NULL;
   date_time_t *dt1 = NULL;
   date_time_t *dt2 = NULL;

   if ( ( (*current).is_definite == 0 ) || ( (*other).is_definite == 0 ) )
   {
      result = NULL;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      // get latest start time
      if ( date_time_is_less_than( (*current).start_dt, (*other).start_dt ) == 1 )
      {
         dt1 = (*other).start_dt;
      }
      else
      {
         dt1 = (*current).start_dt;
      }

      // get earliest end time
      if ( date_time_is_less_than( (*current).end_dt, (*other).end_dt ) == 1 )
      {
         dt2 = (*current).end_dt;
      }
      else
      {
         dt2 = (*other).end_dt;
      }

      // if start < end, make result duration
      if ( date_time_is_less_than( dt1, dt2 ) == 0 )
      {
         result = NULL;
      }
      else
      {
         result = date_time_duration_make_start_end( dt1, dt2 );
      }

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_is_overlap
*/

int32_t
date_time_duration_is_overlap( date_time_duration_t *current, date_time_duration_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   date_time_t *dt1 = NULL;
   date_time_t *dt2 = NULL;

   if ( ( (*current).is_definite == 0 ) || ( (*other).is_definite == 0 ) )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      // get latest start time
      if ( date_time_is_less_than( (*current).start_dt, (*other).start_dt ) == 1 )
      {
         dt1 = (*other).start_dt;
      }
      else
      {
         dt1 = (*current).start_dt;
      }

      // get earliest end time
      if ( date_time_is_less_than( (*current).end_dt, (*other).end_dt ) == 1 )
      {
         dt2 = (*current).end_dt;
      }
      else
      {
         dt2 = (*other).end_dt;
      }

      // if start < end, make result duration
      if ( date_time_is_less_than( dt1, dt2 ) == 0 )
      {
         result = 0;
      }
      else
      {
         result = 1;
      }

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_put_start
*/

void
date_time_duration_put_start
(
   date_time_duration_t *current,
   date_time_t *start_dt
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "start_dt not null", start_dt != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set start date_time
   date_time_copy( (*current).start_dt, start_dt );

   // set end date_time
   date_time_copy( (*current).end_dt, start_dt );
   date_time_add_delta_milliseconds( (*current).end_dt, (*current).duration_milliseconds );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_put_end
*/

void
date_time_duration_put_end
(
   date_time_duration_t *current,
   date_time_t *end_dt
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "end_dt not null", end_dt != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set end date_time
   date_time_copy( (*current).end_dt, end_dt );

   // set start date_time
   date_time_copy( (*current).start_dt, end_dt );
   date_time_add_delta_milliseconds( (*current).start_dt, -(*current).duration_milliseconds );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_put_start_end
*/

void
date_time_duration_put_start_end
(
   date_time_duration_t *current,
   date_time_t *start_dt,
   date_time_t *end_dt
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "start_dt not null", start_dt != NULL );
   PRECONDITION( "end_dt not null", end_dt != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set start date_time
   date_time_copy( (*current).start_dt, start_dt );

   // set end date_time
   date_time_copy( (*current).end_dt, end_dt );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_put_start_duration_dhms
*/

void
date_time_duration_put_start_duration_dhms
(
   date_time_duration_t *current,
   date_time_t *start_dt,
   int32_t days,
   int32_t hours,
   int32_t minutes,
   int32_t seconds,
   int32_t milliseconds
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "start_dt not null", start_dt != NULL );
   PRECONDITION( "hour_24 ok", ( hours >= 0 ) && ( hours <= 23 ) );
   PRECONDITION( "minute ok", ( minutes >= 0 ) && ( minutes <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( seconds >= 0 ) && ( seconds <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( milliseconds >= 0 ) && ( milliseconds <= MAX_MILLISECONDS_IN_SECOND ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t duration = 0;

   duration = dhms_to_milliseconds( days, hours, minutes, seconds, milliseconds );

   // set start date_time
   date_time_copy( (*current).start_dt, start_dt );
   date_time_copy( (*current).end_dt, start_dt );
   date_time_add_delta_milliseconds( (*current).end_dt, duration );

   // set duration
   (*current).duration_milliseconds = duration;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_put_start_duration_milliseconds
*/

void
date_time_duration_put_start_duration_milliseconds
(
   date_time_duration_t *current,
   date_time_t *start_dt,
   int64_t milliseconds
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "start_dt not null", start_dt != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set start and end date_time
   date_time_copy( (*current).start_dt, start_dt );
   date_time_copy( (*current).end_dt, start_dt );
   date_time_add_delta_milliseconds( (*current).end_dt, milliseconds );

   // set duration
   (*current).duration_milliseconds = milliseconds;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_put_duration_dhms
*/

void
date_time_duration_put_duration_dhms
(
   date_time_duration_t *current,
   int32_t days,
   int32_t hours,
   int32_t minutes,
   int32_t seconds,
   int32_t milliseconds
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   PRECONDITION( "hour_24 ok", ( hours >= 0 ) && ( hours <= 23 ) );
   PRECONDITION( "minute ok", ( minutes >= 0 ) && ( minutes <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( seconds >= 0 ) && ( seconds <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( milliseconds >= 0 ) && ( milliseconds <= MAX_MILLISECONDS_IN_SECOND ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t duration = 0;

   duration = dhms_to_milliseconds( days, hours, minutes, seconds, milliseconds );

   // (re)set end date_time
   date_time_copy( (*current).end_dt, (*current).start_dt );
   date_time_add_delta_milliseconds( (*current).end_dt, duration );

   // set duration
   (*current).duration_milliseconds = duration;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_put_duration_milliseconds
*/

void
date_time_duration_put_duration_milliseconds
(
   date_time_duration_t *current,
   int64_t milliseconds
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // (re)set end date_time
   date_time_copy( (*current).end_dt, (*current).start_dt );
   date_time_add_delta_milliseconds( (*current).end_dt, milliseconds );

   // set duration
   (*current).duration_milliseconds = milliseconds;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


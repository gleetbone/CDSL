/**
 @file Date_Time.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Date-Time class"

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

 Function definitions for the opaque date_time_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Date_Time.h"
#include <time.h>

#include <Date_Time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
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
#define HOURS_IN_HALF_DAY 12
#define MILLISECONDS_IN_MINUTE 1000*SECONDS_IN_MINUTE
#define SECONDS_IN_HOUR 60*SECONDS_IN_MINUTE
#define MILLISECONDS_IN_HOUR 1000*SECONDS_IN_HOUR
#define SECONDS_IN_DAY 24*SECONDS_IN_HOUR
#define MILLISECONDS_IN_DAY 1000*SECONDS_IN_DAY

#define DAYS_IN_WEEK 7
#define DAYS_IN_YEAR 365
#define DAYS_IN_LEAP_YEAR 366

#define MAX_MILLISECONDS_IN_SECOND 999
#define MAX_SECONDS_IN_MINUTE 59
#define MAX_MINUTES_IN_HOUR 59
#define MAX_HOURS_IN_DAY 23
#define MAX_HOURS_IN_DAY_12 11

#define MIN_DAY 1
#define MAX_MONTH_DAY 31
#define MAX_MONTH_DAY_OTHER 30

#define MAX_DAY_JAN 31
#define MAX_DAY_FEB 28
#define MAX_DAY_FEB_LEAP_YEAR 29
#define MAX_DAY_MAR 31
#define MAX_DAY_APR 30
#define MAX_DAY_MAY 31
#define MAX_DAY_JUN 30
#define MAX_DAY_JUL 31
#define MAX_DAY_AUG 31
#define MAX_DAY_SEP 30
#define MAX_DAY_OCT 31
#define MAX_DAY_NOV 30
#define MAX_DAY_DEC 31

#define MIN_MONTH   1
#define MAX_MONTH  12

#define JAN_MONTH   1
#define FEB_MONTH   2
#define MAR_MONTH   3
#define APR_MONTH   4
#define MAY_MONTH   5
#define JUN_MONTH   6
#define JUL_MONTH   7
#define AUG_MONTH   8
#define SEP_MONTH   9
#define OCT_MONTH  10
#define NOV_MONTH  11
#define DEC_MONTH  12

// Day of week: Sunday is 7, Monday is 1, Friday is 5
#define MIN_DAY_OF_WEEK 1
#define MAX_DAY_OF_WEEK 7

#define BASE_YEAR 1600
#define BASE_YEAR_JAN_1ST_DAY_OF_WEEK 6

/**
   date_time structure
*/

struct date_time_struct
{
   int32_t _type;

   int32_t year;
   int32_t month;
   int32_t day;
   int32_t day_of_year;
   int32_t hour_24;
   int32_t minute;
   int32_t second;
   int32_t millisecond;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Local Function Prototypes
*/

/**
   is_less_than_or_equal
*/

static
int32_t
is_less_than_or_equal( date_time_t *result, date_time_t *other );

/**
   is_leap_year

   @param year the year of the date
   @return 1 if true, 0 otherwise
*/
static
int32_t
is_leap_year( int32_t year )
{
   int32_t result = 0;
   int32_t y = 0;

   if ( year >= 0 )
   {
      y = year;
   }
   else
   {
      y = -year - 1;
   }

   if ( ( y % 4 ) == 0 )
   {
      result = 1;
   }

   if  ( ( y % 100 ) == 0 )
   {
      result = 0;
   }

   if  ( ( y % 400 ) == 0 )
   {
      result = 1;
   }

   return result;
}

/**
   day_ok

   @param year the year of the date
   @param month the month of the date
   @param day the day of the month
   @return 1 if the day is valid, 0 if not (returns 1 for Feb 29 on a leap year for example)
*/
static
int32_t
day_ok( int32_t year, int32_t month, int32_t day )
{
   int32_t result = 0;

   if ( day >= MIN_DAY )
   {
      if ( day <= MAX_MONTH_DAY )
      {
         if ( ( is_leap_year( year ) == 1 ) && ( month == 2 ) )
         {
            if ( day <= MAX_DAY_FEB_LEAP_YEAR )
            {
               result = 1;
            }
         }
         else if ( ( is_leap_year( year ) == 0 ) && ( month == FEB_MONTH ) )
         {
            if ( day <= MAX_DAY_FEB )
            {
               result = 1;
            }
         }

         if (
            ( month == APR_MONTH )
            || ( month == JUN_MONTH )
            || ( month == SEP_MONTH )
            || ( month == NOV_MONTH )
         )
         {
            if ( day <= MAX_MONTH_DAY_OTHER )
            {
               result = 1;
            }
         }

         if (
            ( month == JAN_MONTH )
            || ( month == MAR_MONTH )
            || ( month == MAY_MONTH )
            || ( month == JUL_MONTH )
            || ( month == AUG_MONTH )
            || ( month == OCT_MONTH )
            || ( month == DEC_MONTH )
         )
         {
            if ( day <= MAX_MONTH_DAY )
            {
               result = 1;
            }
         }

      }
   }

   return result;
}

/**
   day_of_year_ok

   @param year the year of the date
   @param day_of_year the day in the year (Jan 1 is 1, Feb 1 is 29 in non-leap years)
   @return 1 if day of year is valid, 0 if not (invalid for 366 on non-leap years)
*/
static
int32_t
day_of_year_ok( int32_t year, int32_t day_of_year )
{
   int32_t result = 0;

   if ( is_leap_year( year ) )
   {
      result = ( ( day_of_year >= MIN_DAY ) && ( day_of_year <= DAYS_IN_LEAP_YEAR ) );
   }
   else
   {
      result = ( ( day_of_year >= MIN_DAY ) && ( day_of_year <= DAYS_IN_YEAR ) );
   }

   return result;
}

/**
   days_in_month

   @param year the year of the date
   @param month the month of the date
   @return count of days in that month
*/
static
int32_t
days_in_month( int32_t year, int32_t month )
{
   int32_t result = 0;

   result = 1;

   if ( ( is_leap_year( year ) == 1 ) && ( month == FEB_MONTH ) )
   {
      result = MAX_DAY_FEB_LEAP_YEAR;
   }
   else if ( ( is_leap_year( year ) == 0 ) && ( month == FEB_MONTH ) )
   {
      result = MAX_DAY_FEB;
   }
   else if
   (
      ( month == APR_MONTH )
      || ( month == JUN_MONTH )
      || ( month == SEP_MONTH )
      || ( month == NOV_MONTH )
   )
   {
      result = MAX_MONTH_DAY_OTHER;
   }
   else
   {
      result = MAX_MONTH_DAY;
   }

   return result;
}

/**
   day_of_year

   @param year the year of the date
   @param month the month of the date
   @param day the day of the month
   @return the day_of_year for this date
*/
static
int32_t
day_of_year( int32_t year, int32_t month, int32_t day )
{
   int32_t result = 0;
   int32_t i = 0;

   for ( i = 1; i < month; i++ )
   {
      result = result + days_in_month( year, i );
   }

   result = result + day;

   return result;
}

/**
   month_day_from_day_of_year

   @param year the year of the date
   @param day_of_year the day of the year
   @param month pointer to the return value of the month
   @param day pointer to the return value of the day of the month
*/
static
void
month_day_from_day_of_year( int32_t year, int32_t day_of_year, int32_t *month, int32_t *day )
{
   int32_t i_month = 0;
   int32_t i_day = 0;

   i_month = 1;
   i_day = day_of_year;

   // get month and day of month
   // subtract until we arrive at the correct month and day of month
   while ( i_day > days_in_month( year, i_month ) )
   {
      i_day = i_day - days_in_month( year, i_month );
      i_month = i_month + 1;
   }

   *month = i_month;
   *day = i_day;

   return;
}

/**
   days_in_year

   @param year the year of the date
   @return how many days in that year (365 or 366 for leap years)
*/
static
int32_t
days_in_year( int32_t year )
{
   int32_t result = DAYS_IN_YEAR;

   if ( is_leap_year( year ) == 1 )
   {
      result = DAYS_IN_LEAP_YEAR;
   }

   return result;
}

/**
   dt_difference

   @param current the current date
   @param other an other date
   @return milliseconds between current and other
*/
static
int64_t
dt_difference( date_time_t *current, date_time_t *other )
{
   date_time_t *dt1 = NULL;
   date_time_t *dt2 = NULL;
   int32_t sign = 0;
   int64_t result = 0;
   int32_t d_diff = 0;
   int32_t h_diff = 0;
   int32_t m_diff = 0;
   int32_t s_diff = 0;
   int32_t ms_diff = 0;
   int32_t i = 0;

   if ( is_less_than_or_equal( current, other ) )
   {
      dt1 = current;
      dt2 = other;
      sign = 1;
   }
   else
   {
      dt1 = other;
      dt2 = current;
      sign = -1;
   }

   // get year difference in days
   for ( i = (*dt1).year; i < (*dt2).year; i++ )
   {
      if ( i == 0 )
      {
         continue; // no 0 AD or 0 BC, time goes from 1 BC to 1 AD
      }

      d_diff = d_diff + days_in_year( i );
   }

   d_diff = d_diff - (*dt1).day_of_year;
   d_diff = d_diff + (*dt2).day_of_year;

   // get other differences
   h_diff = (*dt2).hour_24 - (*dt1).hour_24;

   m_diff = (*dt2).minute - (*dt1).minute;

   s_diff = (*dt2).second - (*dt1).second;

   ms_diff = (*dt2).millisecond - (*dt1).millisecond;

   // result is sum of differences as milliseconds
   result
      =     d_diff * SECONDS_IN_DAY
            +  h_diff * SECONDS_IN_HOUR
            +  m_diff * SECONDS_IN_MINUTE
            +  s_diff;

   result = result * 1000 + ms_diff;

   result = sign * result;

   return result;
}

/**
   milliseconds_to_dhms

   @param milliseconds the milliseconds of duration
   @param days pointer to return value of number of days in milliseconds
   @param hours_24 pointer to return value of number of hours in milliseconds
   @param minutes pointer to return value of number of minutes in milliseconds
   @param seconds pointer to return value of number of seconds in milliseconds
   @param mseconds pointer to return value of number of milliseconds in milliseconds

   milliseconds is equal to sum of days, hours_24, minutes, seconds, and mseconds
*/
static
void
milliseconds_to_dhms
(
   int64_t milliseconds,
   int32_t *days,
   int32_t *hours_24,
   int32_t *minutes,
   int32_t *seconds,
   int32_t *mseconds
)
{
   int32_t sign = 0;
   int64_t msecs = 0;
   int32_t d;
   int32_t h;
   int32_t m;
   int32_t s;
   int32_t ms;

   // get milliseconds as positive msecs and sign
   if ( milliseconds >= 0 )
   {
      sign = 1;
      msecs = milliseconds;
   }
   else
   {
      sign = -1;
      msecs = -milliseconds;
   }

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

   *days = d * sign;
   *hours_24 = h * sign;
   *minutes = m * sign;
   *seconds = s * sign;
   *mseconds = ms * sign;

   return;
}

/**
   increment_year
*/
void
increment_year( date_time_t *dt )
{
   int32_t year = 0;

   year = (*dt).year;

   if ( year == -1 )
   {
      year = 1;
   }
   else
   {
      year = year + 1;
   }

   (*dt).year = year;

   return;
}

/**
   decrement_year
*/
void
decrement_year( date_time_t *dt )
{
   if ( (*dt).year == 1 )
   {
      (*dt).year = -1;
   }
   else
   {
      (*dt).year = (*dt).year - 1;
   }

   return;
}

/**
   adjust_fields

   the fields of a date are adjusted to lie within their normal range
   (presumably after some computation has taken the fields out of bounds),
   for example 3 hours and -2 minutes becomes 2 hours and 58 minutes


   @param dt the date

*/
static
void
adjust_fields( date_time_t *dt )
{
   // milliseconds
   if ( (*dt).millisecond < 0 )
   {
      (*dt).millisecond = (*dt).millisecond + MILLISECONDS_IN_SECOND;
      (*dt).second = (*dt).second - 1;
   }
   else if ( (*dt).millisecond > MAX_MILLISECONDS_IN_SECOND )
   {
      (*dt).millisecond = (*dt).millisecond - MILLISECONDS_IN_SECOND;
      (*dt).second = (*dt).second + 1;
   }

   // seconds
   if ( (*dt).second < 0 )
   {
      (*dt).second = (*dt).second + SECONDS_IN_MINUTE;
      (*dt).minute = (*dt).minute - 1;
   }
   else if ( (*dt).second > MAX_SECONDS_IN_MINUTE )
   {
      (*dt).second = (*dt).second - SECONDS_IN_MINUTE;
      (*dt).minute = (*dt).minute + 1;
   }

   // minutes
   if ( (*dt).minute < 0 )
   {
      (*dt).minute = (*dt).minute + MINUTES_IN_HOUR;
      (*dt).hour_24 = (*dt).hour_24 - 1;
   }
   else if ( (*dt).minute > MAX_MINUTES_IN_HOUR )
   {
      (*dt).minute = (*dt).minute - MINUTES_IN_HOUR;
      (*dt).hour_24 = (*dt).hour_24 + 1;
   }

   // hours
   if ( (*dt).hour_24 < 0 )
   {
      (*dt).hour_24 = (*dt).hour_24 + HOURS_IN_DAY;
      (*dt).day_of_year = (*dt).day_of_year - 1;
   }
   else if ( (*dt).hour_24 > MAX_HOURS_IN_DAY )
   {
      (*dt).hour_24 = (*dt).hour_24 - HOURS_IN_DAY;
      (*dt).day_of_year = (*dt).day_of_year + 1;
   }

   while( ( (*dt).day_of_year < 1 ) || (*dt).day_of_year > days_in_year( (*dt).year ) )
   {
      // days
      if ( (*dt).day_of_year < 1 )
      {
         decrement_year( dt );
         if ( is_leap_year( (*dt).year ) == 1 )
         {
            (*dt).day_of_year = (*dt).day_of_year + DAYS_IN_LEAP_YEAR;
         }
         else
         {
            (*dt).day_of_year = (*dt).day_of_year + DAYS_IN_YEAR;
         }
      }
      else if ( (*dt).day_of_year > days_in_year( (*dt).year ) )
      {
         increment_year( dt );
         if ( is_leap_year( (*dt).year - 1 ) == 1 )
         {
            (*dt).day_of_year = (*dt).day_of_year - DAYS_IN_LEAP_YEAR;
         }
         else
         {
            (*dt).day_of_year = (*dt).day_of_year - DAYS_IN_YEAR;
         }
      }
   }

   month_day_from_day_of_year( (*dt).year, (*dt).day_of_year, &(*dt).month, &(*dt).day );

   return;
}

/**
   days_between_years

   returns the number of days between two years

   @param y1 the first date
   @param y2 the other date
   @return the number of days between y1 and y2
*/
static
int32_t
days_between_years( int32_t y1, int32_t y2 )
{
   int32_t result = 0;

   // days per year, accounting for leap years.
   // for years earlier than 1582, leap years are undefined
   // as different calendars than the Gregorian were in use.

   result
      =  ( y2 - y1 ) * DAYS_IN_YEAR
         + ( y2 - 1 ) / 4
         - ( y1 - 1 ) / 4
         - ( y2 - 1 ) / 100
         + ( y1 - 1 ) / 100
         + ( y2 - 1 ) / 400
         - ( y1 - 1 ) / 400;

   return result;
}

#if INVARIANT_CONDITIONAL != 0

static
int32_t
year_valid( date_time_t *current )
{
   int32_t result = 0;

   result = ( (*current).year != 0 );

   return result;
}

static
int32_t
month_valid( date_time_t *current )
{
   int32_t result = 0;

   result = ( (*current).month >= MIN_MONTH ) && ( (*current).month <= MAX_MONTH );

   return result;
}

static
int32_t
day_valid( date_time_t *current )
{
   int32_t result = 0;

   result = day_ok( (*current).year, (*current).month, (*current).day );

   return result;
}

static
int32_t
day_of_year_valid( date_time_t *current )
{
   int32_t result = 0;

   result = day_of_year_ok( (*current).year, (*current).day_of_year );

   return result;
}

static
int32_t
hour_valid( date_time_t *current )
{
   int32_t result = 0;

   result = ( (*current).hour_24 >= 0 ) && ( (*current).hour_24 <= MAX_HOURS_IN_DAY );

   return result;
}

static
int32_t
minute_valid( date_time_t *current )
{
   int32_t result = 0;

   result = ( (*current).minute >= 0 ) && ( (*current).minute <= MAX_MINUTES_IN_HOUR );

   return result;
}

static
int32_t
second_valid( date_time_t *current )
{
   int32_t result = 0;

   result = ( (*current).second >= 0 ) && ( (*current).second <= MAX_SECONDS_IN_MINUTE );

   return result;
}

static
int32_t
millisecond_valid( date_time_t *current )
{
   int32_t result = 0;

   result = ( (*current).millisecond >= 0 ) && ( (*current).millisecond <= MAX_MILLISECONDS_IN_SECOND );

   return result;
}

static
void invariant( date_time_t *current )
{
   assert( ( ( void ) "year_valid", year_valid( current ) ) );
   assert( ( ( void ) "month_valid", month_valid( current ) ) );
   assert( ( ( void ) "day_valid", day_valid( current ) ) );
   assert( ( ( void ) "day_of_year_valid", day_of_year_valid( current ) ) );
   assert( ( ( void ) "hour_valid", hour_valid( current ) ) );
   assert( ( ( void ) "minute_valid", minute_valid( current ) ) );
   assert( ( ( void ) "second_valid", second_valid( current ) ) );
   assert( ( ( void ) "millisecond_valid", millisecond_valid( current ) ) );
   return;
}

#endif

/**
   date_time_make
*/

date_time_t *
date_time_make
(
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour_24,
   int32_t minute,
   int32_t second,
   int32_t millisecond
)
{
   PRECONDITION( "year not zero", year != 0 );
   PRECONDITION( "month ok", ( month >= 1 ) && ( month <= 12 ) );
   PRECONDITION( "day of month ok", day_ok( year, month, day ) == 1 );
   PRECONDITION( "hour_24 ok", ( hour_24 >= 0 ) && ( hour_24 <= 23 ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );

   // allocate date_time struct
   date_time_t * result = ( date_time_t * ) calloc( 1, sizeof( date_time_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_TYPE;

   // set year
   (*result).year = year;

   // set month
   (*result).month = month;

   // set day
   (*result).day = day;

   // set hour_24
   (*result).hour_24 = hour_24;

   // set minute
   (*result).minute = minute;

   // set second
   (*result).second = second;

   // set millisecond
   (*result).millisecond = millisecond;

   // set_day_of_year
   (*result).day_of_year = day_of_year( year, month, day );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_make_day_of_year
*/

date_time_t *
date_time_make_day_of_year
(
   int32_t year,
   int32_t day_of_year,
   int32_t hour_24,
   int32_t minute,
   int32_t second,
   int32_t millisecond
)
{
   PRECONDITION( "year not zero", year != 0 );
   PRECONDITION( "day of year ok", day_of_year_ok( year, day_of_year ) == 1 );
   PRECONDITION( "hour_24 ok", ( hour_24 >= 0 ) && ( hour_24 <= MAX_HOURS_IN_DAY ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );

   // allocate date_time struct
   date_time_t * result = ( date_time_t * ) calloc( 1, sizeof( date_time_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_TYPE;

   // set year
   (*result).year = year;

   // set month and day
   month_day_from_day_of_year( (*result).year, day_of_year, &(*result).month, &(*result).day );

   // set hour_24
   (*result).hour_24 = hour_24;

   // set minute
   (*result).minute = minute;

   // set second
   (*result).second = second;

   // set millisecond
   (*result).millisecond = millisecond;

   // set_day_of_year
   (*result).day_of_year = day_of_year;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_make
*/

date_time_t *
date_time_make_hour_12
(
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour_12,
   int32_t minute,
   int32_t second,
   int32_t millisecond,
   int32_t meridiem
)
{
   PRECONDITION( "year not zero", year != 0 );
   PRECONDITION( "month ok", ( month >= 1 ) && ( month <= MAX_MONTH ) );
   PRECONDITION( "day of month ok", day_ok( year, month, day ) == 1 );
   PRECONDITION( "hour_12 ok", ( hour_12 >= 0 ) && ( hour_12 <= MAX_HOURS_IN_DAY_12 ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );
   PRECONDITION( "meridiem ok", ( meridiem == 0 ) || ( meridiem == 1 ) );

   // allocate date_time struct
   date_time_t * result = ( date_time_t * ) calloc( 1, sizeof( date_time_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_TYPE;

   // set year
   (*result).year = year;

   // set month
   (*result).month = month;

   // set day
   (*result).day = day;

   // set hour_24
   (*result).hour_24 = hour_12;
   if ( meridiem == 1 )
   {
      (*result).hour_24 = (*result).hour_24 + 12;
   }

   // set minute
   (*result).minute = minute;

   // set second
   (*result).second = second;

   // set millisecond
   (*result).millisecond = millisecond;

   // set_day_of_year
   (*result).day_of_year = day_of_year( year, month, day );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_make_now
*/

date_time_t *
date_time_make_now()
{
   time_t rawtime;
   struct tm *timeinfo = NULL;

   // allocate date_time struct
   date_time_t * result = ( date_time_t * ) calloc( 1, sizeof( date_time_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_TYPE;

   // get current time
   time( &rawtime );
   timeinfo = localtime( &rawtime );

   // set year
   (*result).year = (*timeinfo).tm_year + 1900;

   // set month
   (*result).month = (*timeinfo).tm_mon + 1;

   // set day
   (*result).day = (*timeinfo).tm_mday;

   // set hour_24
   (*result).hour_24 = (*timeinfo).tm_hour;

   // set minute
   (*result).minute = (*timeinfo).tm_min;

   // set second
   (*result).second = (*timeinfo).tm_sec;

   // set millisecond
   (*result).millisecond = 0;

   // set_day_of_year
   (*result).day_of_year = day_of_year( (*result).year, (*result).month, (*result).day );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_clone
*/

date_time_t *
date_time_clone( date_time_t *current )
{
   PRECONDITION( "date_time not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );

   // allocate date_time struct
   date_time_t * result = ( date_time_t * ) calloc( 1, sizeof( date_time_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = DATE_TIME_TYPE;

   (*result).year = (*current).year;
   (*result).month = (*current).month;
   (*result).day = (*current).day;
   (*result).hour_24 = (*current).hour_24;
   (*result).minute = (*current).minute;
   (*result).second = (*current).second;
   (*result).millisecond = (*current).millisecond;
   (*result).day_of_year = (*current).day_of_year;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   date_time_deep_clone
*/

date_time_t *
date_time_deep_clone( date_time_t *current )
{
   // deep clone is same as clone for this type
   return date_time_clone( current );
}

/**
  is_equal
*/

static
int32_t
is_equal(  date_time_t *current, date_time_t *other )
{
   int32_t result = 0;

   result =
      ( (*current).year == (*other).year )
      &&
      ( (*current).month == (*other).month )
      &&
      ( (*current).day == (*other).day )
      &&
      ( (*current).hour_24 == (*other).hour_24 )
      &&
      ( (*current).minute == (*other).minute )
      &&
      ( (*current).second == (*other).second )
      &&
      ( (*current).millisecond == (*other).millisecond );

   return result;
};

/**
   date_time_is_equal
*/

int32_t
date_time_is_equal( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
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
   date_time_is_deep_equal
*/

int32_t
date_time_is_deep_equal( date_time_t *current, date_time_t *other )
{
   // is_deep_equal is same as is_equal for this type
   return date_time_is_equal( current, other );
}

/**
   date_time_copy
*/

void
date_time_copy( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   (*current).year = (*other).year;
   (*current).month = (*other).month;
   (*current).day = (*other).day;
   (*current).hour_24 = (*other).hour_24;
   (*current).minute = (*other).minute;
   (*current).second = (*other).second;
   (*current).millisecond = (*other).millisecond;
   (*current).day_of_year = (*other).day_of_year;

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_deep_copy
*/

void
date_time_deep_copy( date_time_t *current, date_time_t *other )
{
   // deep copy is same as copy for this type
   date_time_copy( current, other );
   return;
}

/**
   date_time_dispose
*/

void
date_time_dispose( date_time_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == DATE_TIME_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete date_time struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   date_time_deep_dispose
*/

void
date_time_deep_dispose( date_time_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == DATE_TIME_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete date_time struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   date_time_year
*/

int32_t
date_time_year( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).year;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_month
*/

int32_t
date_time_month( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).month;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_day
*/

int32_t
date_time_day( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).day;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_day_of_year
*/

int32_t
date_time_day_of_year( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).day_of_year;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_day_of_week
*/

int32_t
date_time_day_of_week( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = days_between_years( BASE_YEAR, (*current).year );
   result = result + (*current).day_of_year;

   result = ( ( ( result - 1 ) + BASE_YEAR_JAN_1ST_DAY_OF_WEEK - 1 ) % DAYS_IN_WEEK ) + 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_hour_24
*/

int32_t
date_time_hour_24( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).hour_24;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_hour_12
*/

int32_t
date_time_hour_12( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).hour_24 % 12;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_minute
*/

int32_t
date_time_minute( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).minute;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_second
*/

int32_t
date_time_second( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).second;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_millisecond
*/

int32_t
date_time_millisecond( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).millisecond;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_meridiem
*/

int32_t
date_time_meridiem( date_time_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   if ( (*current).hour_24 > 12 )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_difference
*/

int64_t
date_time_difference( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   LOCK( (*other).mutex );

   int64_t result = 0;

   result = dt_difference( current, other );

   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
  is_less_than
*/

static
int32_t
is_less_than( date_time_t *current, date_time_t *other )
{
   int32_t result = 0;

   if ( (*current).year < (*other).year )
   {
      result = 1;
   }
   else if ( (*current).year == (*other).year )
   {
      if ( (*current).month < (*other).month )
      {
         result = 1;
      }
      else if ( (*current).month == (*other).month )
      {
         if ( (*current).day < (*other).day )
         {
            result = 1;
         }
         else if ( (*current).day == (*other).day )
         {
            if ( (*current).hour_24 < (*other).hour_24 )
            {
               result = 1;
            }
            else if ( (*current).hour_24 == (*other).hour_24 )
            {
               if ( (*current).minute < (*other).minute )
               {
                  result = 1;
               }
               else if ( (*current).minute == (*other).minute )
               {
                  if ( (*current).second < (*other).second )
                  {
                     result = 1;
                  }
                  else if ( (*current).second == (*other).second )
                  {
                     if ( (*current).millisecond < (*other).millisecond )
                     {
                        result = 1;
                     }
                  }
               }
            }
         }
      }
   }

   return result;
}

/**
   date_time_is_less_than
*/

int32_t
date_time_is_less_than( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
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
is_less_than_or_equal( date_time_t *current, date_time_t *other )
{
   int32_t result = 0;

   if ( (*current).year < (*other).year )
   {
      result = 1;
   }
   else if ( (*current).year == (*other).year )
   {
      if ( (*current).month < (*other).month )
      {
         result = 1;
      }
      else if ( (*current).month == (*other).month )
      {
         if ( (*current).day < (*other).day )
         {
            result = 1;
         }
         else if ( (*current).day == (*other).day )
         {
            if ( (*current).hour_24 < (*other).hour_24 )
            {
               result = 1;
            }
            else if ( (*current).hour_24 == (*other).hour_24 )
            {
               if ( (*current).minute < (*other).minute )
               {
                  result = 1;
               }
               else if ( (*current).minute == (*other).minute )
               {
                  if ( (*current).second < (*other).second )
                  {
                     result = 1;
                  }
                  else if ( (*current).second == (*other).second )
                  {
                     if ( (*current).millisecond <= (*other).millisecond )
                     {
                        result = 1;
                     }
                  }
               }
            }
         }
      }
   }

   return result;
}

/**
   date_time_is_less_than_or_equal
*/

int32_t
date_time_is_less_than_or_equal( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
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
is_greater_than( date_time_t *current, date_time_t *other )
{
   int32_t result = 0;

   if ( (*current).year > (*other).year )
   {
      result = 1;
   }
   else if ( (*current).year == (*other).year )
   {
      if ( (*current).month > (*other).month )
      {
         result = 1;
      }
      else if ( (*current).month == (*other).month )
      {
         if ( (*current).day > (*other).day )
         {
            result = 1;
         }
         else if ( (*current).day == (*other).day )
         {
            if ( (*current).hour_24 > (*other).hour_24 )
            {
               result = 1;
            }
            else if ( (*current).hour_24 == (*other).hour_24 )
            {
               if ( (*current).minute > (*other).minute )
               {
                  result = 1;
               }
               else if ( (*current).minute == (*other).minute )
               {
                  if ( (*current).second > (*other).second )
                  {
                     result = 1;
                  }
                  else if ( (*current).second == (*other).second )
                  {
                     if ( (*current).millisecond > (*other).millisecond )
                     {
                        result = 1;
                     }
                  }
               }
            }
         }
      }
   }

   return result;
}


/**
   date_time_is_greater_than
*/

int32_t
date_time_is_greater_than( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
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
is_greater_than_or_equal( date_time_t *current, date_time_t *other )
{
   int32_t result = 0;

   if ( (*current).year > (*other).year )
   {
      result = 1;
   }
   else if ( (*current).year == (*other).year )
   {
      if ( (*current).month > (*other).month )
      {
         result = 1;
      }
      else if ( (*current).month == (*other).month )
      {
         if ( (*current).day > (*other).day )
         {
            result = 1;
         }
         else if ( (*current).day == (*other).day )
         {
            if ( (*current).hour_24 > (*other).hour_24 )
            {
               result = 1;
            }
            else if ( (*current).hour_24 == (*other).hour_24 )
            {
               if ( (*current).minute > (*other).minute )
               {
                  result = 1;
               }
               else if ( (*current).minute == (*other).minute )
               {
                  if ( (*current).second > (*other).second )
                  {
                     result = 1;
                  }
                  else if ( (*current).second == (*other).second )
                  {
                     if ( (*current).millisecond >= (*other).millisecond )
                     {
                        result = 1;
                     }
                  }
               }
            }
         }
      }
   }

   return result;
}

/**
   date_time_is_greater_than_or_equal
*/

int32_t
date_time_is_greater_than_or_equal( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
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
   date_time_compare
*/

int32_t
date_time_compare( date_time_t *current, date_time_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_TYPE );
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
   date_time_put
*/

void
date_time_put
(
   date_time_t *current,
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour_24,
   int32_t minute,
   int32_t second,
   int32_t millisecond
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "year not zero", year != 0 );
   PRECONDITION( "month ok", ( month >= 1 ) && ( month <= MAX_MONTH ) );
   PRECONDITION( "day of month ok", day_ok( year, month, day ) == 1 );
   PRECONDITION( "hour_24 ok", ( hour_24 >= 0 ) && ( hour_24 <= MAX_HOURS_IN_DAY ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set year
   (*current).year = year;

   // set month
   (*current).month = month;

   // set day
   (*current).day = day;

   // set hour_24
   (*current).hour_24 = hour_24;

   // set minute
   (*current).minute = minute;

   // set second
   (*current).second = second;

   // set millisecond
   (*current).millisecond = millisecond;

   // set_day_of_year
   (*current).day_of_year = day_of_year( year, month, day );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_with_hour_12
*/

void
date_time_put_with_hour_12
(
   date_time_t *current,
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour_12,
   int32_t minute,
   int32_t second,
   int32_t millisecond,
   int32_t meridiem
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "year not zero", year != 0 );
   PRECONDITION( "month ok", ( month >= 1 ) && ( month <= MAX_MONTH ) );
   PRECONDITION( "day of month ok", day_ok( month, month, day ) == 1 );
   PRECONDITION( "hour_12 ok", ( hour_12 >= 0 ) && ( hour_12 <= MAX_HOURS_IN_DAY_12 ) );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );
   PRECONDITION( "meridiem ok", ( meridiem == 0 ) || ( meridiem == 1 ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set year
   (*current).year = year;

   // set month
   (*current).month = month;

   // set day
   (*current).day = day;

   // set hour_24
   (*current).hour_24 = hour_12;
   if ( meridiem == 1 )
   {
      (*current).hour_24 = (*current).hour_24 + HOURS_IN_HALF_DAY;
   }

   // set minute
   (*current).minute = minute;

   // set second
   (*current).second = second;

   // set millisecond
   (*current).millisecond = millisecond;

   // set_day_of_year
   (*current).day_of_year = day_of_year( year, month, day );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_year
*/

void
date_time_put_year( date_time_t *current, int32_t year )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "year not zero", year != 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set year
   (*current).year = year;

   // set_day_of_year
   (*current).day_of_year = day_of_year( (*current).year, (*current).month, (*current).day );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_month
*/

void
date_time_put_month( date_time_t *current, int32_t month )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "month ok", ( month >= MIN_MONTH ) && ( month <= MAX_MONTH ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set month
   (*current).month = month;

   // set_day_of_year
   (*current).day_of_year = day_of_year( (*current).year, (*current).month, (*current).day );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_day
*/

void
date_time_put_day( date_time_t *current, int32_t day )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "day of month ok", day_ok( (*current).year, (*current).month, day ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set day
   (*current).day = day;

   // set_day_of_year
   (*current).day_of_year = day_of_year( (*current).year, (*current).month, (*current).day );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_day_of_year
*/

void
date_time_put_day_of_year( date_time_t *current, int32_t day_of_year )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "day of year ok", day_of_year_ok( (*current).year, day_of_year ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set month and day
   month_day_from_day_of_year( (*current).year, day_of_year, &(*current).month, &(*current).day );

   // set_day_of_year
   (*current).day_of_year = day_of_year;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_hour_24
*/

void
date_time_put_hour_24( date_time_t *current, int32_t hour_24 )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "hour_24 ok", ( hour_24 >= 0 ) && ( hour_24 <= MAX_HOURS_IN_DAY ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set hour_24
   (*current).hour_24 = hour_24;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_hour_12
*/

void
date_time_put_hour_12( date_time_t *current, int32_t hour_12, int32_t meridiem )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "hour_12 ok", ( hour_12 >= 0 ) && ( hour_12 <= MAX_HOURS_IN_DAY_12 ) );
   PRECONDITION( "meridiem ok", ( meridiem == 0 ) || ( meridiem == 1 ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set hour_24
   (*current).hour_24 = hour_12;

   if ( meridiem == 1 )
   {
      (*current).hour_24 = (*current).hour_24 + HOURS_IN_HALF_DAY;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_minute
*/

void
date_time_put_minute( date_time_t *current, int32_t minute )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "minute ok", ( minute >= 0 ) && ( minute <= MAX_MINUTES_IN_HOUR ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set minute
   (*current).minute = minute;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_second
*/

void
date_time_put_second( date_time_t *current, int32_t second )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "second ok", ( second >= 0 ) && ( second <= MAX_SECONDS_IN_MINUTE ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set second
   (*current).second = second;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_put_millisecond
*/

void
date_time_put_millisecond( date_time_t *current, int32_t millisecond )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   PRECONDITION( "millisecond ok", ( millisecond >= 0 ) && ( millisecond <= MAX_MILLISECONDS_IN_SECOND ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set millisecond
   (*current).millisecond = millisecond;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_add_delta_milliseconds
*/

void
date_time_add_delta_milliseconds( date_time_t *current, int64_t milliseconds )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t days = 0;
   int32_t hours = 0;
   int32_t minutes = 0;
   int32_t seconds = 0;
   int32_t mseconds = 0;

   milliseconds_to_dhms( milliseconds, &days, &hours, &minutes, &seconds, &mseconds );

   // add milliseconds
   (*current).millisecond = (*current).millisecond + mseconds;
   adjust_fields( current );

   // add seconds
   (*current).second = (*current).second + seconds;
   adjust_fields( current );

   // add minutes
   (*current).minute = (*current).minute + minutes;
   adjust_fields( current );

   // add hours
   (*current).hour_24 = (*current).hour_24 + hours;
   adjust_fields( current );

   // add days
   (*current).day_of_year = (*current).day_of_year + days;
   adjust_fields( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


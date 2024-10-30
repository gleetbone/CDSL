/**
 @file Temporenc.c
 @author Greg Lee
 @version 0.0

 description: "Binary time format encoded into 64 bits"
 author: "Greg Lee"
 date: "$Date: 2014-06-26 10:34:55 -0800 (Thu, 26 Jun 2014) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Defines functions to create, dispose, set, and access temporenc 64 bit binary
 date/time format.

 */

#include "Temporenc.h"
#include <stdio.h>
#include <stdlib.h>

#include "dbc.h"

#define FIRST_YEAR 0
#define LAST_YEAR 4094
#define UNDEFINED_YEAR 4095

#define FIRST_MONTH 0
#define LAST_MONTH 11
#define UNDEFINED_MONTH 15

#define FIRST_DAY 0
#define LAST_DAY 30
#define UNDEFINED_DAY 31

#define FIRST_HOUR 0
#define LAST_HOUR 23
#define UNDEFINED_HOUR 31

#define FIRST_MINUTE 0
#define LAST_MINUTE 59
#define UNDEFINED_MINUTE 63

#define FIRST_SECOND 0
#define LAST_SECOND 59
#define UNDEFINED_SECOND 63

#define FIRST_MILLISECOND 0
#define LAST_MILLISECOND 999

#define FIRST_MILLISECOND 0
#define LAST_MILLISECOND 999

#define FIRST_TIMEZONE 0
#define LAST_TIMEZONE 125
#define MAX_TIMEZONE_HOUR 12
#define UNEXPRESSED_TIMEZONE 126
#define UNDEFINED_TIMEZONE 127
#define TIMEZONE_OFFSET 64
#define TIMEZONE_HOUR_SHIFT 2
#define TIMEZONE_MINUTE_MASK 0x3
#define TIMEZONE_MINUTES_PER_BIT 15
#define TIMEZONE_MINUTES_IN_HOUR 60
#define TIMEZONE_MINUTES_0 0
#define TIMEZONE_MINUTES_15 15
#define TIMEZONE_MINUTES_30 30
#define TIMEZONE_MINUTES_45 45

#define DTSZ_TAG 0x7
#define PRECISION 0
#define PRECISION_NO_MILLISECONDS 3

/**
   temporenc structure
*/

struct temporenc_struct
{
   int32_t _type;

   int32_t year;
   int32_t month;
   int32_t day;
   int32_t hour;
   int32_t minute;
   int32_t second;
   int32_t millisecond;

   int32_t millisecond_is_set;

   int32_t timezone_offset; // in fifteem minute chunks from UTC, +/- plus TIMEZONE_OFFSET
};

union temporenc_bitfields_union
{
   uint64_t value;
   struct
   {
      uint32_t pad3 : 3;
      uint32_t timezone : 7;
      uint32_t millisecond : 10;
      uint32_t second : 6;
      uint32_t minute : 6;
      uint32_t pad1 : 1;
      uint32_t hour : 5;
      uint32_t day : 5;
      uint32_t month : 4;
      uint32_t year : 12;
      uint32_t precision : 2;
      uint32_t tag : 3;
   } fields;
};

typedef union temporenc_bitfields_union temporenc_bitfields_t;

#if INVARIANT_CONDITIONAL != 0

/**
   year_ok

   check year for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
year_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).year >= FIRST_YEAR )
               &&
               ( (*current).year <= LAST_YEAR )
            )
            ||
            ( (*current).year == UNDEFINED_YEAR );

   return result;
}

/**
   month_ok

   check month for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
month_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).month >= FIRST_MONTH )
               &&
               ( (*current).month <= LAST_MONTH )
            )
            ||
            ( (*current).month == UNDEFINED_MONTH );

   return result;
}

/**
   day_ok

   check day for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
day_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).day >= FIRST_DAY )
               &&
               ( (*current).day <= LAST_DAY )
            )
            ||
            ( (*current).day == UNDEFINED_DAY );

   return result;
}

/**
   hour_ok

   check hour for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
hour_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).hour >= FIRST_HOUR )
               &&
               ( (*current).hour <= LAST_HOUR )
            )
            ||
            ( (*current).hour == UNDEFINED_HOUR );

   return result;
}

/**
   minute_ok

   check minute for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
minute_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).minute >= FIRST_MINUTE )
               &&
               ( (*current).minute <= LAST_MINUTE )
            )
            ||
            ( (*current).minute == UNDEFINED_MINUTE );

   return result;
}

/**
   second_ok

   check second for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
second_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).second >= FIRST_SECOND )
               &&
               ( (*current).second <= LAST_SECOND )
            )
            ||
            ( (*current).second == UNDEFINED_SECOND );

   return result;
}

/**
   millisecond_ok

   check millisecond for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
millisecond_ok( temporenc_t *current )
{
   int32_t result = 1;

   result
      =  ( (*current).millisecond_is_set == 0 )
         ||
         (
            ( (*current).millisecond >= FIRST_MILLISECOND )
            &&
            ( (*current).millisecond <= LAST_MILLISECOND )
         );

   return result;
}

/**
   timezone_ok

   check timezone for validity in a temporenc

   @param current the temporenc
   @return 1 if OK, 0 otherwise
*/
static
int32_t
timezone_ok( temporenc_t *current )
{
   int32_t result = 1;

   result = (
               ( (*current).timezone_offset >= FIRST_TIMEZONE )
               &&
               ( (*current).timezone_offset <= LAST_TIMEZONE )
            )
            ||
            ( (*current).timezone_offset == UNEXPRESSED_TIMEZONE )
            ||
            ( (*current).timezone_offset == UNDEFINED_TIMEZONE );

   return result;
}

static
void invariant( temporenc_t *current )
{
   assert( ( ( void ) "year_ok", year_ok( current ) ) );
   assert( ( ( void ) "month_ok", month_ok( current ) ) );
   assert( ( ( void ) "day_ok", day_ok( current ) ) );
   assert( ( ( void ) "hour_ok", hour_ok( current ) ) );
   assert( ( ( void ) "minute_ok", minute_ok( current ) ) );
   assert( ( ( void ) "second_ok", second_ok( current ) ) );
   assert( ( ( void ) "millisecond_ok", millisecond_ok( current ) ) );
   assert( ( ( void ) "timezone_ok", timezone_ok( current ) ) );
   return;
}

#else

static
void invariant( temporenc_t *current )
{
   return;
}

#endif


/**
   temporenc_make_default
*/

temporenc_t *
temporenc_make_default( void )
{
   // allocate temporenc struct
   temporenc_t * result = ( temporenc_t * ) calloc( 1, sizeof( temporenc_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TEMPORENC_TYPE;

   // set elements
   (*result).year = 0;
   (*result).month = 0;
   (*result).day = 0;
   (*result).hour = 0;
   (*result).minute = 0;
   (*result).second = 0;
   (*result).millisecond = 0;
   (*result).millisecond_is_set = 0;
   (*result).timezone_offset = 0;

   INVARIANT( result );

   return result;
}

/**
   temporenc_make
*/

temporenc_t *
temporenc_make
(
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour,
   int32_t minute,
   int32_t second,
   int32_t millisecond,
   int32_t millisecond_is_set,
   int32_t timezone_offset_sign,
   int32_t timezone_offset_hour,
   int32_t timezone_offset_minute
)
{
   PRECONDITION( "year ok", ( ( year >= FIRST_YEAR ) && ( year <= LAST_YEAR ) ) || ( year == UNDEFINED_YEAR ) );
   PRECONDITION( "month ok", ( ( month >= FIRST_MONTH ) && ( month <= LAST_MONTH ) ) || ( month == UNDEFINED_MONTH ) );
   PRECONDITION( "day ok", ( ( day >= FIRST_DAY ) && ( day <= LAST_DAY ) ) || ( day == UNDEFINED_DAY ) );
   PRECONDITION( "hour ok", ( ( hour >= FIRST_HOUR ) && ( hour <= LAST_HOUR ) ) || ( hour == UNDEFINED_HOUR ) );
   PRECONDITION( "minute ok", ( ( minute >= FIRST_MINUTE ) && ( minute <= LAST_MINUTE ) ) || ( minute == UNDEFINED_MINUTE ) );
   PRECONDITION( "second ok", ( ( second >= FIRST_SECOND ) && ( second <= LAST_SECOND ) ) || ( second == UNDEFINED_SECOND ) );
   PRECONDITION( "millisecond ok", ( ( millisecond >= FIRST_MILLISECOND ) && ( millisecond <= LAST_MILLISECOND ) ) || ( millisecond_is_set == 0 ) );
   PRECONDITION( "timezone_offset_sign ok", ( ( timezone_offset_sign == 1 ) || ( timezone_offset_sign == -1 ) ) );
   PRECONDITION( "timezone_offset_hour ok", ( ( timezone_offset_hour >= 0 ) && ( timezone_offset_hour <= MAX_TIMEZONE_HOUR ) ) );
   PRECONDITION
   (
      "timezone_offset_minute ok",
      (
         ( timezone_offset_minute == TIMEZONE_MINUTES_0 )
         ||
         ( timezone_offset_minute == TIMEZONE_MINUTES_15 )
         ||
         ( timezone_offset_minute == TIMEZONE_MINUTES_30 )
         ||
         ( timezone_offset_minute == TIMEZONE_MINUTES_45 )
      )
   );

   // allocate temporenc struct
   temporenc_t * result = ( temporenc_t * ) calloc( 1, sizeof( temporenc_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TEMPORENC_TYPE;

   // set elements
   (*result).year = year;
   (*result).month = month;
   (*result).day = day;
   (*result).hour = hour;
   (*result).minute = minute;
   (*result).second = second;
   (*result).millisecond = millisecond;
   (*result).millisecond_is_set = millisecond_is_set;

   (*result).timezone_offset
      =  timezone_offset_sign
         *
         (
            ( timezone_offset_hour << TIMEZONE_HOUR_SHIFT )
            + ( timezone_offset_minute / TIMEZONE_MINUTES_PER_BIT )
         )
         + TIMEZONE_OFFSET;


   INVARIANT( result );

   return result;
}

/**
   temporenc_make_gmt
*/

temporenc_t *
temporenc_make_gmt
(
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour,
   int32_t minute,
   int32_t second,
   int32_t millisecond
)
{
   PRECONDITION( "year ok", ( ( year >= FIRST_YEAR ) && ( year <= LAST_YEAR ) ) || ( year == UNDEFINED_YEAR ) );
   PRECONDITION( "month ok", ( ( month >= FIRST_MONTH ) && ( month <= LAST_MONTH ) ) || ( month == UNDEFINED_MONTH ) );
   PRECONDITION( "day ok", ( ( day >= FIRST_DAY ) && ( day <= LAST_DAY ) ) || ( day == UNDEFINED_DAY ) );
   PRECONDITION( "hour ok", ( ( hour >= FIRST_HOUR ) && ( hour <= LAST_HOUR ) ) || ( hour == UNDEFINED_HOUR ) );
   PRECONDITION( "minute ok", ( ( minute >= FIRST_MINUTE ) && ( minute <= LAST_MINUTE ) ) || ( minute == UNDEFINED_MINUTE ) );
   PRECONDITION( "second ok", ( ( second >= FIRST_SECOND ) && ( second <= LAST_SECOND ) ) || ( second == UNDEFINED_SECOND ) );
   PRECONDITION( "millisecond ok", ( millisecond >= FIRST_MILLISECOND ) && ( millisecond <= LAST_MILLISECOND ) );

   // allocate temporenc struct
   temporenc_t * result = ( temporenc_t * ) calloc( 1, sizeof( temporenc_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TEMPORENC_TYPE;

   // set elements
   (*result).year = year;
   (*result).month = month;
   (*result).day = day;
   (*result).hour = hour;
   (*result).minute = minute;
   (*result).second = second;
   (*result).millisecond = millisecond;
   (*result).millisecond_is_set = 1;

   (*result).timezone_offset = 0;

   INVARIANT( result );

   return result;
}

/**
   temporenc_clone
*/

temporenc_t *
temporenc_clone
(
   temporenc_t *current
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // allocate temporenc struct
   temporenc_t * result = ( temporenc_t * ) calloc( 1, sizeof( temporenc_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TEMPORENC_TYPE;

   // set elements
   (*result).year = (*current).year;
   (*result).month = (*current).month;
   (*result).day = (*current).day;
   (*result).hour = (*current).hour;
   (*result).minute = (*current).minute;
   (*result).second = (*current).second;
   (*result).millisecond = (*current).millisecond;
   (*result).millisecond_is_set = (*current).millisecond_is_set;
   (*result).timezone_offset = (*current).timezone_offset;

   INVARIANT( result );

   return result;
}

/**
   temporenc_deep_clone
*/

temporenc_t *
temporenc_deep_clone
(
   temporenc_t *current
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // allocate temporenc struct
   temporenc_t * result = ( temporenc_t * ) calloc( 1, sizeof( temporenc_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TEMPORENC_TYPE;

   // set elements
   (*result).year = (*current).year;
   (*result).month = (*current).month;
   (*result).day = (*current).day;
   (*result).hour = (*current).hour;
   (*result).minute = (*current).minute;
   (*result).second = (*current).second;
   (*result).millisecond = (*current).millisecond;
   (*result).millisecond_is_set = (*current).millisecond_is_set;
   (*result).timezone_offset = (*current).timezone_offset;

   INVARIANT( result );

   return result;
}

/**
   temporenc_copy
*/

void
temporenc_copy
(
   temporenc_t *current,
   temporenc_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // copy elements
   (*current).year = (*other).year;
   (*current).month = (*other).month;
   (*current).day = (*other).day;
   (*current).hour = (*other).hour;
   (*current).minute = (*other).minute;
   (*current).second = (*other).second;
   (*current).millisecond = (*other).millisecond;
   (*current).millisecond_is_set = (*other).millisecond_is_set;
   (*current).timezone_offset = (*other).timezone_offset;

   INVARIANT( current );

   return;
}

/**
   temporenc_deep_copy
*/

void
temporenc_deep_copy
(
   temporenc_t *current,
   temporenc_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // copy elements
   (*current).year = (*other).year;
   (*current).month = (*other).month;
   (*current).day = (*other).day;
   (*current).hour = (*other).hour;
   (*current).minute = (*other).minute;
   (*current).second = (*other).second;
   (*current).millisecond = (*other).millisecond;
   (*current).millisecond_is_set = (*other).millisecond_is_set;
   (*current).timezone_offset = (*other).timezone_offset;

   INVARIANT( current );

   return;
}

/**
   temporenc_is_equal
*/

int32_t
temporenc_is_equal
(
   temporenc_t *current,
   temporenc_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // check elements
   if (
      ( (*current).year == (*other).year )
      &&
      ( (*current).month == (*other).month )
      &&
      ( (*current).day == (*other).day )
      &&
      ( (*current).hour == (*other).hour )
      &&
      ( (*current).minute == (*other).minute )
      &&
      ( (*current).second == (*other).second )
      &&
      (
         ( (*current).millisecond_is_set == 0 )
         ||
         ( (*current).millisecond == (*other).millisecond )
      )
      &&
      ( (*current).millisecond_is_set == (*other).millisecond_is_set )
      &&
      ( (*current).timezone_offset == (*other).timezone_offset )
   )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_is_deep_equal
*/

int32_t
temporenc_is_deep_equal
(
   temporenc_t *current,
   temporenc_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // check elements
   if (
      ( (*current).year == (*other).year )
      &&
      ( (*current).month == (*other).month )
      &&
      ( (*current).day == (*other).day )
      &&
      ( (*current).hour == (*other).hour )
      &&
      ( (*current).minute == (*other).minute )
      &&
      ( (*current).second == (*other).second )
      &&
      (
         ( (*current).millisecond_is_set == 0 )
         ||
         ( (*current).millisecond == (*other).millisecond )
      )
      &&
      ( (*current).millisecond_is_set == (*other).millisecond_is_set )
      &&
      ( (*current).timezone_offset == (*other).timezone_offset )
   )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_dispose
*/
void
temporenc_dispose( temporenc_t **current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "*current ok", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == TEMPORENC_TYPE );
   INVARIANT(*current);

   // dispose of allocated memory
   free(*current);

   // set pointer to null
   *current = NULL;

   return;
}

/**
   temporenc_deep_dispose
*/
void
temporenc_deep_dispose( temporenc_t **current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "*current ok", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == TEMPORENC_TYPE );
   INVARIANT(*current);

   // dispose of allocated memory
   free(*current);

   // set pointer to null
   *current = NULL;

   return;
}

/**
   temporenc_year
*/
int32_t
temporenc_year( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get year
   result = (*current).year;

   if ( result == UNDEFINED_YEAR )
   {
      result = 0;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_year_is_undefined
*/
int32_t
temporenc_year_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether year is undefined
   if ( (*current).year == UNDEFINED_YEAR )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_put
*/
void
temporenc_put
(
   temporenc_t *current,
   int32_t year,
   int32_t month,
   int32_t day,
   int32_t hour,
   int32_t minute,
   int32_t second,
   int32_t millisecond,
   int32_t millisecond_is_set,
   int32_t timezone_offset_sign,
   int32_t timezone_offset_hour,
   int32_t timezone_offset_minute
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "year ok", ( ( year >= FIRST_YEAR ) && ( year <= LAST_YEAR ) ) || ( year == UNDEFINED_YEAR ) );
   PRECONDITION( "month ok", ( ( month >= FIRST_MONTH ) && ( month <= LAST_MONTH ) ) || ( month == UNDEFINED_MONTH ) );
   PRECONDITION( "day ok", ( ( day >= FIRST_DAY ) && ( day <= LAST_DAY ) ) || ( day == UNDEFINED_DAY ) );
   PRECONDITION( "hour ok", ( ( hour >= FIRST_HOUR ) && ( hour <= LAST_HOUR ) ) || ( hour == UNDEFINED_HOUR ) );
   PRECONDITION( "minute ok", ( ( minute >= FIRST_MINUTE ) && ( minute <= LAST_MINUTE ) ) || ( minute == UNDEFINED_MINUTE ) );
   PRECONDITION( "second ok", ( ( second >= FIRST_SECOND ) && ( second <= LAST_SECOND ) ) || ( second == UNDEFINED_SECOND ) );
   PRECONDITION( "millisecond ok", ( ( millisecond >= FIRST_MILLISECOND ) && ( millisecond <= LAST_MILLISECOND ) ) || ( millisecond_is_set == 0 ) );
   PRECONDITION( "timezone_offset_sign ok", ( ( timezone_offset_sign == 1 ) || ( timezone_offset_sign == -1 ) ) );
   PRECONDITION( "timezone_offset_hour ok", ( ( timezone_offset_hour >= 0 ) && ( timezone_offset_hour <= MAX_TIMEZONE_HOUR ) ) );
   PRECONDITION
   (
      "timezone_offset_minute ok",
      (
         ( timezone_offset_minute == TIMEZONE_MINUTES_0 )
         ||
         ( timezone_offset_minute == TIMEZONE_MINUTES_15 )
         ||
         ( timezone_offset_minute == TIMEZONE_MINUTES_30 )
         ||
         ( timezone_offset_minute == TIMEZONE_MINUTES_45 )
      )
   );
   INVARIANT( current );

   // set values
   (*current).year = year;
   (*current).month = month;
   (*current).day = day;
   (*current).hour = hour;
   (*current).minute = minute;
   (*current).second = second;
   (*current).millisecond = millisecond;
   (*current).millisecond_is_set = millisecond_is_set;

   (*current).timezone_offset
      =  timezone_offset_sign
         *
         (
            ( timezone_offset_hour << TIMEZONE_HOUR_SHIFT )
            + ( timezone_offset_minute / TIMEZONE_MINUTES_PER_BIT )
         )
         + TIMEZONE_OFFSET;

   INVARIANT( current );

   return;
}

/**
   temporenc_put_year
*/
void
temporenc_put_year( temporenc_t *current, int32_t year )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "year ok", ( ( year >= FIRST_YEAR ) && ( year <= LAST_YEAR ) ) || ( year == UNDEFINED_YEAR ) );
   INVARIANT( current );

   // set year
   (*current).year = year;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_year_is_undefined
*/
void
temporenc_set_year_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // set year
   (*current).year = UNDEFINED_YEAR;

   INVARIANT( current );

   return;
}

/**
   temporenc_month
*/
int32_t
temporenc_month( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get month
   result = (*current).month;

   if ( result == UNDEFINED_MONTH )
   {
      result = 0;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_month_is_undefined
*/
int32_t
temporenc_month_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether month is undefined
   if ( (*current).month == UNDEFINED_MONTH )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_put_month
*/
void
temporenc_put_month( temporenc_t *current, int32_t month )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "month ok", ( ( month >= FIRST_MONTH ) && ( month <= LAST_MONTH ) ) || ( month == UNDEFINED_MONTH ) );
   INVARIANT( current );

   // set month
   (*current).month = month;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_month_is_undefined
*/
void
temporenc_set_month_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // set month
   (*current).month = UNDEFINED_MONTH;

   INVARIANT( current );

   return;
}

/**
   temporenc_day
*/
int32_t
temporenc_day( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get day
   result = (*current).day;

   if ( result == UNDEFINED_DAY )
   {
      result = 0;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_day_is_undefined
*/
int32_t
temporenc_day_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether day is undefined
   if ( (*current).day == UNDEFINED_DAY )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_put_day
*/
void
temporenc_put_day( temporenc_t *current, int32_t day )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "day ok", ( ( day >= FIRST_DAY ) && ( day <= LAST_DAY ) ) || ( day == UNDEFINED_DAY ) );
   INVARIANT( current );

   // set day
   (*current).day = day;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_day_is_undefined
*/
void
temporenc_set_day_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // set day
   (*current).day = UNDEFINED_DAY;

   INVARIANT( current );

   return;
}

/**
   temporenc_hour
*/
int32_t
temporenc_hour( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get hour
   result = (*current).hour;

   if ( result == UNDEFINED_HOUR )
   {
      result = 0;
   }

   return result;
}

/**
   temporenc_hour_is_undefined
*/
int32_t
temporenc_hour_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether hour is undefined
   if ( (*current).hour == UNDEFINED_HOUR )
   {
      result = 1;
   }

   return result;
}

/**
   temporenc_put_hour
*/
void
temporenc_put_hour( temporenc_t *current, int32_t hour )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "hour ok", ( ( hour >= FIRST_HOUR ) && ( hour <= LAST_HOUR ) ) || ( hour == UNDEFINED_HOUR ) );
   INVARIANT( current );

   // set hour
   (*current).hour = hour;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_hour_is_undefined
*/
void
temporenc_set_hour_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // set hour
   (*current).hour = UNDEFINED_HOUR;

   INVARIANT( current );

   return;
}

/**
   temporenc_minute
*/
int32_t
temporenc_minute( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get minute
   result = (*current).minute;

   if ( result == UNDEFINED_MINUTE )
   {
      result = 0;
   }

   return result;
}

/**
   temporenc_minute_is_undefined
*/
int32_t
temporenc_minute_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether minute is undefined
   if ( (*current).minute == UNDEFINED_MINUTE )
   {
      result = 1;
   }

   return result;
}


/**
   temporenc_put_minute
*/
void
temporenc_put_minute( temporenc_t *current, int32_t minute )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "minute ok", ( ( minute >= FIRST_MINUTE ) && ( minute <= LAST_MINUTE ) ) || ( minute == UNDEFINED_MINUTE ) );
   INVARIANT( current );

   // set minute
   (*current).minute = minute;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_minute_is_undefined
*/
void
temporenc_set_minute_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // set minute
   (*current).minute = UNDEFINED_MINUTE;

   INVARIANT( current );

   return;
}

/**
   temporenc_second
*/
int32_t
temporenc_second( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get second
   result = (*current).second;

   if ( result == UNDEFINED_SECOND )
   {
      result = 0;
   }

   return result;
}

/**
   temporenc_second_is_undefined
*/
int32_t
temporenc_second_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether second is undefined
   if ( (*current).second == UNDEFINED_SECOND )
   {
      result = 1;
   }

   return result;
}


/**
   temporenc_put_second
*/
void
temporenc_put_second( temporenc_t *current, int32_t second )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "second ok", ( ( second >= FIRST_SECOND ) && ( second <= LAST_SECOND ) ) || ( second == UNDEFINED_SECOND ) );
   INVARIANT( current );

   // set second
   (*current).second = second;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_second_is_undefined
*/
void
temporenc_set_second_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // set second
   (*current).second = UNDEFINED_SECOND;

   INVARIANT( current );

   return;
}

/**
   temporenc_millisecond
*/
int32_t
temporenc_millisecond( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // set millisecond
   result = (*current).millisecond;

   if ( (*current).millisecond_is_set == 0 )
   {
      result = 0;
   }

   return result;
}

/**
   temporenc_millisecond_is_undefined
*/
int32_t
temporenc_millisecond_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether millisecond is undefined
   result = !(*current).millisecond_is_set;

   return result;
}


/**
   temporenc_put_millisecond
*/
void
temporenc_put_millisecond( temporenc_t *current, int32_t millisecond )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "millisecond ok", ( ( millisecond >= FIRST_MILLISECOND ) && ( millisecond <= LAST_MILLISECOND ) ) );
   INVARIANT( current );

   // set millisecond
   (*current).millisecond = millisecond;
   (*current).millisecond_is_set = 1;

   INVARIANT( current );

   return;
}

/**
   temporenc_set_millisecond_is_undefined
*/
void
temporenc_set_millisecond_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // clear millisecond_is_set
   (*current).millisecond_is_set = 0;

   INVARIANT( current );

   return;
}

/**
   temporenc_timezone_offset_sign
*/
int32_t
temporenc_timezone_offset_sign( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 1;

   // get timezone sign
   if ( ( (*current).timezone_offset - TIMEZONE_OFFSET ) < 0 )
   {
      result = -1;
   }

   if ( ( (*current).timezone_offset == UNEXPRESSED_TIMEZONE ) || ( (*current).timezone_offset == UNDEFINED_TIMEZONE ) )
   {
      result = 0;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_timezone_offset_hour
*/
int32_t
temporenc_timezone_offset_hour( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get timezone
   result = abs( (*current).timezone_offset - TIMEZONE_OFFSET ) >> TIMEZONE_HOUR_SHIFT;

   if ( ( (*current).timezone_offset == UNEXPRESSED_TIMEZONE ) || ( (*current).timezone_offset == UNDEFINED_TIMEZONE ) )
   {
      result = 0;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_timezone_offset_minute
*/
int32_t
temporenc_timezone_offset_minute( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get timezone
   result = TIMEZONE_MINUTES_PER_BIT * ( (*current).timezone_offset & TIMEZONE_MINUTE_MASK );

   if ( ( (*current).timezone_offset - TIMEZONE_OFFSET ) < 0 )
   {
      result = TIMEZONE_MINUTES_IN_HOUR - result;
   }

   if ( ( (*current).timezone_offset == UNEXPRESSED_TIMEZONE ) || ( (*current).timezone_offset == UNDEFINED_TIMEZONE ) )
   {
      result = 0;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_timezone_offset_is_unexpressed
*/
int32_t
temporenc_timezone_offset_is_unexpressed( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether timezone is unexpressed
   if ( (*current).timezone_offset == UNEXPRESSED_TIMEZONE )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_timezone_offset_is_undefined
*/
int32_t
temporenc_timezone_offset_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // get whether timezone is undefined
   if ( (*current).timezone_offset == UNDEFINED_TIMEZONE )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_put_timezone_offset
*/
void
temporenc_put_timezone_offset( temporenc_t *current, int32_t sign, int32_t hour, int32_t minute )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "timezone_offset_sign ok", ( ( sign == 1 ) || ( sign == -1 ) ) );
   PRECONDITION( "timezone_offset_hour ok", ( ( hour >= 0 ) && ( hour <= MAX_TIMEZONE_HOUR ) ) );
   PRECONDITION
   (
      "timezone_offset_minute ok",
      (
         ( minute == TIMEZONE_MINUTES_0 )
         ||
         ( minute == TIMEZONE_MINUTES_15 )
         ||
         ( minute == TIMEZONE_MINUTES_30 )
         ||
         ( minute == TIMEZONE_MINUTES_45 )
      )
   );
   INVARIANT( current );

   int32_t timezone_offset = 0;

   // get timezone
   timezone_offset
      =  sign
         *
         (
            ( hour << TIMEZONE_HOUR_SHIFT )
            +
            ( minute / TIMEZONE_MINUTES_PER_BIT )
         )
         + TIMEZONE_OFFSET;

   (*current).timezone_offset = timezone_offset;

   INVARIANT( current );

   return;
}

/**
   temporenc_timezone_offset_set_is_unexpressed
*/
void
temporenc_timezone_offset_set_is_unexpressed( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // get whether timezone is unexpressed
   (*current).timezone_offset = UNEXPRESSED_TIMEZONE;

   INVARIANT( current );

   return;
}

/**
   temporenc_timezone_offset_set_is_undefined
*/
void
temporenc_timezone_offset_set_is_undefined( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   // get whether timezone is undefined
   (*current).timezone_offset = UNDEFINED_TIMEZONE;

   INVARIANT( current );

   return;
}

/**
   temporenc_encode
*/
uint64_t
temporenc_encode( temporenc_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   INVARIANT( current );

   temporenc_bitfields_t result = {0};

   // set fields
   result.fields.tag = DTSZ_TAG;
   result.fields.precision = PRECISION;

   result.fields.year = (*current).year;
   result.fields.month = (*current).month;
   result.fields.day = (*current).day;
   result.fields.hour = (*current).hour;
   result.fields.minute = (*current).minute;
   result.fields.second = (*current).second;
   if ( (*current).millisecond_is_set == 1 )
   {
      result.fields.millisecond = (*current).millisecond;
   }
   else
   {
      result.fields.precision = PRECISION_NO_MILLISECONDS;
   }

   result.fields.timezone = (*current).timezone_offset;

   INVARIANT( current );

   return result.value;
}

/**
   temporenc_decode
*/
void
temporenc_decode( temporenc_t *current, uint64_t arg )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "arg header tag ok", ( ( * ( temporenc_bitfields_t * ) &arg ).fields.tag == DTSZ_TAG ) );
   PRECONDITION( "arg header precision ok", ( ( * ( temporenc_bitfields_t * ) &arg ).fields.precision == PRECISION ) || ( ( * ( temporenc_bitfields_t * ) &arg ).fields.precision == PRECISION_NO_MILLISECONDS ) );
   INVARIANT( current );

   temporenc_bitfields_t value = {0};

   value.value = arg;

   // set fields
   (*current).year = value.fields.year;
   (*current).month = value.fields.month;
   (*current).day = value.fields.day;
   (*current).hour = value.fields.hour;
   (*current).minute = value.fields.minute;
   (*current).second = value.fields.second;

   if ( value.fields.precision == PRECISION_NO_MILLISECONDS )
   {
      (*current).millisecond_is_set = 0;
   }
   else
   {
      (*current).millisecond_is_set = 1;
      (*current).millisecond = value.fields.millisecond;
   }

   (*current).timezone_offset = value.fields.timezone;

   INVARIANT( current );

   return;
}

/**
   temporenc_is_less_than
*/
int32_t
temporenc_is_less_than( temporenc_t *current, temporenc_t *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );

   int32_t result = 0;

   if ( (*current).year < (*other).year )
   {
      result = 1;
   }
   else if ( (*current).year > (*other).year )
   {
      result = 0;
   }
   else
   {
      if ( (*current).month < (*other).month )
      {
         result = 1;
      }
      else if ( (*current).month > (*other).month )
      {
         result = 0;
      }
      else
      {
         if ( (*current).day < (*other).day )
         {
            result = 1;
         }
         else if ( (*current).day > (*other).day )
         {
            result = 0;
         }
         else
         {
            if ( (*current).hour < (*other).hour )
            {
               result = 1;
            }
            else if ( (*current).hour > (*other).hour )
            {
               result = 0;
            }
            else
            {
               if ( (*current).minute < (*other).minute )
               {
                  result = 1;
               }
               else if ( (*current).minute > (*other).minute )
               {
                  result = 0;
               }
               else
               {
                  if ( (*current).second < (*other).second )
                  {
                     result = 1;
                  }
                  else if ( (*current).second > (*other).second )
                  {
                     result = 0;
                  }
                  else
                  {
                     if ( (*current).millisecond < (*other).millisecond )
                     {
                        result = 1;
                     }
                     else if ( (*current).millisecond >= (*other).millisecond )
                     {
                        result = 0;
                     }
                  }
               }
            }
         }
      }
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_is_greater_than
*/
int32_t
temporenc_is_greater_than( temporenc_t *current, temporenc_t *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );

   int32_t result = 0;

   if ( (*current).year > (*other).year )
   {
      result = 1;
   }
   else if ( (*current).year < (*other).year )
   {
      result = 0;
   }
   else
   {
      if ( (*current).month > (*other).month )
      {
         result = 1;
      }
      else if ( (*current).month < (*other).month )
      {
         result = 0;
      }
      else
      {
         if ( (*current).day > (*other).day )
         {
            result = 1;
         }
         else if ( (*current).day < (*other).day )
         {
            result = 0;
         }
         else
         {
            if ( (*current).hour > (*other).hour )
            {
               result = 1;
            }
            else if ( (*current).hour < (*other).hour )
            {
               result = 0;
            }
            else
            {
               if ( (*current).minute > (*other).minute )
               {
                  result = 1;
               }
               else if ( (*current).minute < (*other).minute )
               {
                  result = 0;
               }
               else
               {
                  if ( (*current).second > (*other).second )
                  {
                     result = 1;
                  }
                  else if ( (*current).second < (*other).second )
                  {
                     result = 0;
                  }
                  else
                  {
                     if ( (*current).millisecond > (*other).millisecond )
                     {
                        result = 1;
                     }
                     else if ( (*current).millisecond <= (*other).millisecond )
                     {
                        result = 0;
                     }
                  }
               }
            }
         }
      }
   }

   INVARIANT( current );

   return result;
}

/**
   temporenc_is_equal_to
*/
int32_t
temporenc_is_equal_to( temporenc_t *current, temporenc_t *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TEMPORENC_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TEMPORENC_TYPE );

   int32_t result = 0;

   if ( (*current).year == (*other).year )
   {
      if ( (*current).month == (*other).month )
      {
         if ( (*current).day == (*other).day )
         {
            if ( (*current).hour == (*other).hour )
            {
               if ( (*current).minute == (*other).minute )
               {
                  if ( (*current).second == (*other).second )
                  {
                     if ( (*current).millisecond == (*other).millisecond )
                     {
                        result = 1;
                     }
                  }
               }
            }
         }
      }
   }

   INVARIANT( current );

   return result;
}

/* End of file */

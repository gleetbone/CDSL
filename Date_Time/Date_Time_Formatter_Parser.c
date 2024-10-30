/**
 @file Date_Time_Formatter_Parser.c
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

 Function definitions for the opaque date_time_formatter_parser_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Date_Time_Formatter_Parser.h"
#include <string.h>

#include <Date_Time_Formatter_Parser.h>
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
#define HOURS_IN_HALF_DAY 12
#define MILLISECONDS_IN_MINUTE 1000*SECONDS_IN_MINUTE
#define SECONDS_IN_HOUR 60*SECONDS_IN_MINUTE
#define MILLISECONDS_IN_HOUR 1000*SECONDS_IN_HOUR
#define SECONDS_IN_DAY 24*SECONDS_IN_HOUR
#define MILLISECONDS_IN_DAY 1000*SECONDS_IN_DAY

#define DAYS_IN_WEEK 7
#define DAYS_IN_YEAR 365
#define DAYS_IN_LEAP_YEAR 366

#define YEARS_IN_CENTURY 100

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

static char_t *JANUARY_TEXT   =  "Jan";
static char_t *FEBRUARY_TEXT  =  "Feb";
static char_t *MARCH_TEXT     =  "Mar";
static char_t *APRIL_TEXT     =  "Apr";
static char_t *MAY_TEXT       =  "May";
static char_t *JUNE_TEXT      =  "Jun";
static char_t *JULY_TEXT      =  "Jul";
static char_t *AUGUST_TEXT    =  "Aug";
static char_t *SEPTEMBER_TEXT =  "Sep";
static char_t *OCTOBER_TEXT   =  "Oct";
static char_t *NOVEMBER_TEXT  =  "Nov";
static char_t *DECEMBER_TEXT  =  "Dec";

// Day of week: Sunday is 7, Monday is 1, Saturday is 6
#define BASE_YEAR 1600
#define BASE_YEAR_JAN_1ST_DAY_OF_WEEK 6
#define MIN_DAY_OF_WEEK 1
#define MAX_DAY_OF_WEEK 7

static char_t *SUNDAY_TEXT    =  "Sun";
static char_t *MONDAY_TEXT    =  "Mon";
static char_t *TUESDAY_TEXT   =  "Tue";
static char_t *WEDNESDAY_TEXT =  "Wed";
static char_t *THURSDAY_TEXT  =  "Thu";
static char_t *FRIDAY_TEXT    =  "Fri";
static char_t *SATURDAY_TEXT  =  "Sat";

// AM and PM
#define AM_MERIDIEM 0
#define PM_MERIDIEM 1
static char_t *AM_TEXT =  "AM";
static char_t *PM_TEXT =  "PM";

// Format field codes and specifiers

// 4 digit year
#define CODE_YEAR_4 1
#define YEAR_4 "yyyy"
#define YEAR_4_LENGTH 4
static char_t *YEAR_4_FMTSPEC = "%4d";
#define YEAR_4_INPUT_LENGTH 4
static char_t *YEAR_4_SPACER = "    ";
static char_t *YEAR_4_ERROR = "Invalid 4 digit year at ";

// 2 digit year
#define CODE_YEAR_2 2
#define YEAR_2 "yy"
#define YEAR_2_LENGTH 2
static char_t *YEAR_2_FMTSPEC  = "%2d";
#define YEAR_2_INPUT_LENGTH 2
static char_t *YEAR_2_SPACER = "  ";
static char_t *YEAR_2_ERROR = "Invalid 2 digit year at ";

// 2 digit month, no leading zero
#define CODE_MONTH 3
#define MONTH "mm"
#define MONTH_LENGTH 2
static char_t *MONTH_FMTSPEC  = "%2d";
#define MONTH_INPUT_LENGTH 2
static char_t *MONTH_SPACER = "  ";
static char_t *MONTH_ERROR = "Invalid 2 digit month at ";

// 2 digit month, leading zero
#define CODE_MONTH_LZ 4
#define MONTH_LZ "[0]mm"
#define MONTH_LZ_LENGTH 5
static char_t *MONTH_LZ_FMTSPEC  = "%02d";
#define MONTH_LZ_INPUT_LENGTH 2
static char_t *MONTH_LZ_SPACER = "  ";
static char_t *MONTH_LZ_ERROR = "Invalid zero padded 2 digit month at ";

// 3 letter month
#define CODE_MONTH_LETTER 5
#define MONTH_LETTER "mmm"
#define MONTH_LETTER_LENGTH 3
static char_t *MONTH_LETTER_FMTSPEC  = "%3s";
#define MONTH_LETTER_INPUT_LENGTH 3
static char_t *MONTH_LETTER_SPACER = "   ";
static char_t *MONTH_LETTER_ERROR = "Invalid 3 character month at ";

// 2 digit day, no leading zero
#define CODE_DAY 6
#define DAY "dd"
#define DAY_LENGTH 2
static char_t *DAY_FMTSPEC  = "%2d";
#define DAY_INPUT_LENGTH 2
static char_t *DAY_SPACER = "  ";
static char_t *DAY_ERROR = "Invalid 2 digit day at ";

// 2 digit day, leading zero
#define CODE_DAY_LZ 7
#define DAY_LZ "[0]dd"
#define DAY_LZ_LENGTH 5
static char_t *DAY_LZ_FMTSPEC = "%02d";
#define DAY_LZ_INPUT_LENGTH 2
static char_t *DAY_LZ_SPACER = "  ";
static char_t *DAY_LZ_ERROR = "Invalid zero padded 2 digit day at ";

// 3 letter day (of week)
#define CODE_DAY_LETTER 8
#define DAY_LETTER "ddd"
#define DAY_LETTER_LENGTH 3
static char_t *DAY_LETTER_FMTSPEC = "%3s";
#define DAY_LETTER_INPUT_LENGTH 3
static char_t *DAY_LETTER_SPACER = "   ";
static char_t *DAY_LETTER_ERROR = "Invalid 3 character day of week at ";

// 2 digit hour, no leading zero
#define CODE_HOUR 9
#define HOUR "hh"
#define HOUR_LENGTH 2
static char_t *HOUR_FMTSPEC = "%2d";
#define HOUR_INPUT_LENGTH 2
static char_t *HOUR_SPACER = "  ";
static char_t *HOUR_ERROR = "Invalid 2 digit hour at ";

// 2 digit hour, leading zero
#define CODE_HOUR_LZ 10
#define HOUR_LZ "[0]hh"
#define HOUR_LZ_LENGTH 5
static char_t *HOUR_LZ_FMTSPEC = "%02d";
#define HOUR_LZ_INPUT_LENGTH 2
static char_t *HOUR_LZ_SPACER = "  ";
static char_t *HOUR_LZ_ERROR = "Invalid zero padded 2 digit hour at ";

// 2 digit hour_12, no leading zero
#define CODE_HOUR_12 11
#define HOUR_12 "h1"
#define HOUR_12_LENGTH 2
static char_t *HOUR_12_FMTSPEC = "%2d";
#define HOUR_12_INPUT_LENGTH 2
static char_t *HOUR_12_SPACER = "  ";
static char_t *HOUR_12_ERROR = "Invalid 2 digit hour_12 at ";

// 2 digit hour_12, leading zero
#define CODE_HOUR_12_LZ 12
#define HOUR_12_LZ "[0]h1"
#define HOUR_12_LZ_LENGTH 5
static char_t *HOUR_12_LZ_FMTSPEC = "%02d";
#define HOUR_12_LZ_INPUT_LENGTH 2
static char_t *HOUR_12_LZ_SPACER = "  ";
static char_t *HOUR_12_LZ_ERROR = "Invalid zero padded 2 digit hour_12 at ";

// 2 digit minute, no leading zero
#define CODE_MINUTE 13
#define MINUTE "mi"
#define MINUTE_LENGTH 2
static char_t *MINUTE_FMTSPEC = "%2d";
#define MINUTE_INPUT_LENGTH 2
static char_t *MINUTE_SPACER = "  ";
static char_t *MINUTE_ERROR = "Invalid 2 digit minute at ";

// 2 digit minute, leading zero
#define CODE_MINUTE_LZ 14
#define MINUTE_LZ "[0]mi"
#define MINUTE_LZ_LENGTH 5
static char_t *MINUTE_LZ_FMTSPEC = "%02d";
#define MINUTE_LZ_INPUT_LENGTH 2
static char_t *MINUTE_LZ_SPACER = "  ";
static char_t *MINUTE_LZ_ERROR = "Invalid zero padded 2 digit minute at ";

// 2 digit second, no leading zero
#define CODE_SECOND 15
#define SECOND "ss"
#define SECOND_LENGTH 2
static char_t *SECOND_FMTSPEC = "%2d";
#define SECOND_INPUT_LENGTH 2
static char_t *SECOND_SPACER = "  ";
static char_t *SECOND_ERROR = "Invalid 2 digit second at ";

// 2 digit second, leading zero
#define CODE_SECOND_LZ 16
#define SECOND_LZ "[0]ss"
#define SECOND_LZ_LENGTH 5
static char_t *SECOND_LZ_FMTSPEC = "%02d";
#define SECOND_LZ_INPUT_LENGTH 2
static char_t *SECOND_LZ_SPACER = "  ";
static char_t *SECOND_LZ_ERROR = "Invalid zero padded 2 digit second at ";

// 3 digit millisecond, leading zero
#define CODE_MILLISECOND_LZ 17
#define MILLISECOND_LZ "[0]mls"
#define MILLISECOND_LZ_LENGTH 6
static char_t *MILLISECOND_LZ_FMTSPEC = "%03d";
#define MILLISECOND_LZ_INPUT_LENGTH 3
static char_t *MILLISECOND_LZ_SPACER = "   ";
static char_t *MILLISECOND_LZ_ERROR = "Invalid zero padded 3 digit millisecond at ";

// 2 letter meridiem
#define CODE_MERIDIEM 18
#define MERIDIEM "md"
#define MERIDIEM_LENGTH 2
static char_t *MERIDIEM_FMTSPEC = "%2s";
#define MERIDIEM_INPUT_LENGTH 2
static char_t *MERIDIEM_SPACER = "  ";
static char_t *MERIDIEM_ERROR = "Invalid AM/PM ";


/**
   Format field structure
*/

struct format_field
{
   int32_t code;
   int32_t position;
   int32_t length;
   char_t *format_specifier;
   int32_t input_length;
   char_t *spacer;
   int32_t output_position;
   char_t *error_message;

   struct format_field *next;
};

typedef struct format_field format_field_t;


/**
   date_time_formatter_parser structure
*/

struct date_time_formatter_parser_struct
{
   int32_t _type;

   string_t *format_string;
   string_t *last_error;
   string_t *output_template;
   int32_t num_format_fields;
   format_field_t *format_fields;
   int32_t base_century;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Local functions
*/

/**
   is_digit

   @param c the input character
   @return 1 if character is a digit, 0 otherwise
*/

static
int32_t
is_digit( char_t c )
{
   int32_t result = 0;

   if ( ( c >= '0' ) && ( c <= '9' ) )
   {
      result = 1;
   }

   return result;
}

/**
   is_space

   @param c the input character
   @return 1 if character is a space, 0 otherwise
*/

static
int32_t
is_space( char_t c )
{
   int32_t result = 0;

   if ( c == ' ' )
   {
      result = 1;
   }

   return result;
}

/**
   month_abbrev_to_int

   @param str the month as an input string
   @return number of mmonth
*/

static
int32_t
month_abbrev_to_int( string_t *s )
{
   int32_t result = 0;

   string_to_lower( s );

   if ( string_is_equal_cstring( s, "jan" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s, "feb" ) == 1 )
   {
      result = 2;
   }
   else if ( string_is_equal_cstring( s, "mar" ) == 1 )
   {
      result = 3;
   }
   else if ( string_is_equal_cstring( s, "apr" ) == 1 )
   {
      result = 4;
   }
   else if ( string_is_equal_cstring( s, "may" ) == 1 )
   {
      result = 5;
   }
   else if ( string_is_equal_cstring( s, "jun" ) == 1 )
   {
      result = 6;
   }
   else if ( string_is_equal_cstring( s, "jul" ) == 1 )
   {
      result = 7;
   }
   else if ( string_is_equal_cstring( s, "aug" ) == 1 )
   {
      result = 8;
   }
   else if ( string_is_equal_cstring( s, "sep" ) == 1 )
   {
      result = 9;
   }
   else if ( string_is_equal_cstring( s, "oct" ) == 1 )
   {
      result = 10;
   }
   else if ( string_is_equal_cstring( s, "nov" ) == 1 )
   {
      result = 11;
   }
   else if ( string_is_equal_cstring( s, "dec" ) == 1 )
   {
      result = 12;
   }

   return result;
}

/**
   int_to_month_abbrev

   @param month the integer for a month
   @return the month name as a character string
*/

static
char_t *
int_to_month_abbrev( int32_t month )
{
   char_t *result = NULL;

   if ( month == 1 )
   {
      result = JANUARY_TEXT;
   }
   else if ( month == 2 )
   {
      result = FEBRUARY_TEXT;
   }
   else if ( month == 3 )
   {
      result = MARCH_TEXT;
   }
   else if ( month == 4 )
   {
      result = APRIL_TEXT;
   }
   else if ( month == 5 )
   {
      result = MAY_TEXT;
   }
   else if ( month == 6 )
   {
      result = JUNE_TEXT;
   }
   else if ( month == 7 )
   {
      result = JULY_TEXT;
   }
   else if ( month == 8 )
   {
      result = AUGUST_TEXT;
   }
   else if ( month == 9 )
   {
      result = SEPTEMBER_TEXT;
   }
   else if ( month == 10 )
   {
      result = OCTOBER_TEXT;
   }
   else if ( month == 11 )
   {
      result = NOVEMBER_TEXT;
   }
   else if ( month == 12 )
   {
      result = DECEMBER_TEXT;
   }

   return result;
}

/**
   int_to_day_abbrev

   @param day the integer for a day
   @return the day name as a character string
*/

static
char_t *
int_to_day_abbrev( int32_t day )
{
   char_t *result = NULL;

   if ( day == 1 )
   {
      result = MONDAY_TEXT;
   }
   else if ( day == 2 )
   {
      result = TUESDAY_TEXT;
   }
   else if ( day == 3 )
   {
      result = WEDNESDAY_TEXT;
   }
   else if ( day == 4 )
   {
      result = THURSDAY_TEXT;
   }
   else if ( day == 5 )
   {
      result = FRIDAY_TEXT;
   }
   else if ( day == 6 )
   {
      result = SATURDAY_TEXT;
   }
   else if ( day == 7 )
   {
      result = SUNDAY_TEXT;
   }

   return result;
}

/**
   meridiem_abbrev_to_int

   @param s the meridiem as a character string
   @return the meridem as an integer
*/

static
int32_t
meridiem_abbrev_to_int( string_t *s )
{
   int32_t result = 0;

   string_to_lower( s );

   if ( string_is_equal_cstring( s, "am" ) == 1 )
   {
      result = 0;
   }
   else if ( string_is_equal_cstring( s, "pm" ) == 1 )
   {
      result = 1;
   }

   return result;
}

/**
   int_to_meridiem_abbrev

   @param meridiem the meridiem as an integer
   @return the meridem as a character string
*/

static
char_t *
int_to_meridiem_abbrev( int32_t meridiem )
{
   char_t *result = 0;

   if ( meridiem == 0 )
   {
      result = AM_TEXT;
   }
   else if ( meridiem == 1 )
   {
      result = PM_TEXT;
   }

   return result;
}

/**
   is_leap_year

   @param year a year
   @return 1 if the year is a leap year, 0 otherwise
*/

static
int32_t
is_leap_year( int32_t year )
{
   int32_t result = 0;

   if ( ( year % 4 ) == 0 )
   {
      result = 1;
   }

   if  ( ( year % 100 ) == 0 )
   {
      result = 0;
   }

   if  ( ( year % 400 ) == 0 )
   {
      result = 1;
   }

   return result;
}

/**
   day_ok

   @param year a year
   @param month a month
   @param a day
   @return 1 if the year-month-day is valid, 0 otherwise
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
         else if ( month == FEB_MONTH )
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
   format_field_make

   construct a format field

   @param code the format field code
   @param position the format field position
   @param length the format field length
   @param format_specifier the format field format specifier
   @param input_length the format field input length
   @param spacer the format field spacer
   @param error_message the format field error message
   @return a new format field
*/

static
format_field_t *
format_field_make
(
   int32_t code,
   int32_t position,
   int32_t length,
   char_t *format_specifier,
   int32_t input_length,
   char_t *spacer,
   char_t *error_message
)
{
   format_field_t *result = NULL;

   result = ( format_field_t * ) calloc( 1, sizeof( format_field_t ) );
   CHECK( "result allocated correctly", result != NULL );

   (*result).code = code;
   (*result).position = position;
   (*result).length = length;
   (*result).format_specifier = format_specifier;
   (*result).input_length = input_length;
   (*result).spacer = spacer;
   (*result).error_message = error_message;
   (*result).next = NULL;

   return result;
}

/**
   format_field_clone

   clone a format field

   @param current the format field to clone
   @return a clone of current
*/

static
format_field_t *
format_field_clone( format_field_t *current )
{
   format_field_t *result = NULL;

   result = ( format_field_t * ) calloc( 1, sizeof( format_field_t ) );
   CHECK( "result allocated correctly", result != NULL );

   (*result).code = (*current).code;
   (*result).position = (*current).position;
   (*result).length = (*current).length;
   (*result).format_specifier = (*current).format_specifier;
   (*result).input_length = (*current).input_length;
   (*result).spacer = (*current).spacer;
   (*result).output_position = (*current).output_position;
   (*result).error_message = (*current).error_message;
   (*result).next = NULL;

   return result;
}

/**
   format_field_put

   set the fields of a format field

   @param current the format field to change
   @param code the format field code
   @param position the format field position
   @param length the format field length
   @param format_specifier the format field format specifier
   @param input_length the format field input length
   @param spacer the format field spacer
   @param error_message the format field error message
*/

static
void
format_field_put
(
   format_field_t *current,
   int32_t code,
   int32_t position,
   int32_t length,
   char_t *format_specifier,
   int32_t input_length,
   char_t *spacer,
   char_t *error_message
)
{
   (*current).code = code;
   (*current).position = position;
   (*current).length = length;
   (*current).format_specifier = format_specifier;
   (*current).input_length = input_length;
   (*current).spacer = spacer;
   (*current).output_position = 0;
   (*current).error_message = error_message;

   return;
}

/**
   format_field_put_output_position

   set the output position of a format field

   @param current the format field to change
   @param output_position the new output position
*/

static
void
format_field_put_output_position
(
   format_field_t *current,
   int32_t output_position
)
{
   (*current).output_position = output_position;

   return;
}

/**
   format_field_dispose

   dispose of a format field

   @param current the format field to dispose
*/

static
void
format_field_dispose( format_field_t **current )
{
   free(*current);

   *current = NULL;

   return;
}

/**
   find_next_format_field

   skip to the next format field after start_pos in a format string

   @param format_string the format string to analyze
   @param stary_pos where to start looking for the next field in the format string
   @return the found format field
*/

static
format_field_t *
find_next_format_field( string_t *format_string, int32_t *start_pos )
{
   format_field_t *result = NULL;
   int32_t index = 0;
   int32_t n = 0;
   int32_t i = 0;
   int32_t i1 = 0;

   n = string_count( format_string ) - 1;
   index = *start_pos;

   result = format_field_make( 0, 0, 0, "", 0, "", "" );

   i = n + 1;

   // YEAR_2
   i1 = string_substring_index_in_bounds_cstring( format_string, YEAR_2, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_YEAR_2, i, YEAR_2_LENGTH, YEAR_2_FMTSPEC, YEAR_2_INPUT_LENGTH, YEAR_2_SPACER, YEAR_2_ERROR );
   }

   // YEAR_4
   i1 = string_substring_index_in_bounds_cstring( format_string, YEAR_4, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_YEAR_4, i, YEAR_4_LENGTH, YEAR_4_FMTSPEC, YEAR_4_INPUT_LENGTH, YEAR_4_SPACER, YEAR_4_ERROR );
   }

   // MONTH
   i1 = string_substring_index_in_bounds_cstring( format_string, MONTH, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_MONTH, i, MONTH_LENGTH, MONTH_FMTSPEC, MONTH_INPUT_LENGTH, MONTH_SPACER, MONTH_ERROR );
   }

   // MONTH_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, MONTH_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_MONTH_LZ, i, MONTH_LZ_LENGTH, MONTH_LZ_FMTSPEC, MONTH_LZ_INPUT_LENGTH, MONTH_LZ_SPACER, MONTH_LZ_ERROR );
   }

   // MONTH_LETTER
   i1 = string_substring_index_in_bounds_cstring( format_string, MONTH_LETTER, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_MONTH_LETTER, i, MONTH_LETTER_LENGTH, MONTH_LETTER_FMTSPEC, MONTH_LETTER_INPUT_LENGTH, MONTH_LETTER_SPACER, MONTH_LETTER_ERROR );
   }

   // DAY
   i1 = string_substring_index_in_bounds_cstring( format_string, DAY, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_DAY, i, DAY_LENGTH, DAY_FMTSPEC, DAY_INPUT_LENGTH, DAY_SPACER, DAY_ERROR );
   }

   // DAY_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, DAY_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_DAY_LZ, i, DAY_LZ_LENGTH, DAY_LZ_FMTSPEC, DAY_LZ_INPUT_LENGTH, DAY_LZ_SPACER, DAY_LZ_ERROR );
   }

   // DAY_LETTER
   i1 = string_substring_index_in_bounds_cstring( format_string, DAY_LETTER, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_DAY_LETTER, i, DAY_LETTER_LENGTH, DAY_LETTER_FMTSPEC, DAY_LETTER_INPUT_LENGTH, DAY_LETTER_SPACER, DAY_LETTER_ERROR );
   }

   // HOUR
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_HOUR, i, HOUR_LENGTH, HOUR_FMTSPEC, HOUR_INPUT_LENGTH, HOUR_SPACER, HOUR_ERROR );
   }

   // HOUR_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_HOUR_LZ, i, HOUR_LZ_LENGTH, HOUR_LZ_FMTSPEC, HOUR_LZ_INPUT_LENGTH, HOUR_LZ_SPACER, HOUR_LZ_ERROR );
   }

   // HOUR_12
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_12, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_HOUR_12, i, HOUR_12_LENGTH, HOUR_12_FMTSPEC, HOUR_12_INPUT_LENGTH, HOUR_12_SPACER, HOUR_12_ERROR );
   }

   // HOUR_12_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_12_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_HOUR_12_LZ, i, HOUR_12_LZ_LENGTH, HOUR_12_LZ_FMTSPEC, HOUR_12_LZ_INPUT_LENGTH, HOUR_12_LZ_SPACER, HOUR_12_LZ_ERROR );
   }

   // MINUTE
   i1 = string_substring_index_in_bounds_cstring( format_string, MINUTE, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_MINUTE, i, MINUTE_LENGTH, MINUTE_FMTSPEC, MINUTE_INPUT_LENGTH, MINUTE_SPACER, MINUTE_ERROR );
   }

   // MINUTE_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, MINUTE_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_MINUTE_LZ, i, MINUTE_LZ_LENGTH, MINUTE_LZ_FMTSPEC, MINUTE_LZ_INPUT_LENGTH, MINUTE_LZ_SPACER, MINUTE_LZ_ERROR );
   }

   // SECOND
   i1 = string_substring_index_in_bounds_cstring( format_string, SECOND, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_SECOND, i, SECOND_LENGTH, SECOND_FMTSPEC, SECOND_INPUT_LENGTH, SECOND_SPACER, SECOND_ERROR );
   }

   // SECOND_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, SECOND_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_SECOND_LZ, i, SECOND_LZ_LENGTH, SECOND_LZ_FMTSPEC, SECOND_LZ_INPUT_LENGTH, SECOND_LZ_SPACER, SECOND_LZ_ERROR );
   }

   // MILLISECOND_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, MILLISECOND_LZ, index, n );
   if ( ( i1 >= 0 ) && ( i1 < i ) )
   {
      i = i1;
      format_field_put( result, CODE_MILLISECOND_LZ, i, MILLISECOND_LZ_LENGTH, MILLISECOND_LZ_FMTSPEC, MILLISECOND_LZ_INPUT_LENGTH, MILLISECOND_LZ_SPACER, MILLISECOND_LZ_ERROR );
   }

   // MERIDIEM
   i1 = string_substring_index_in_bounds_cstring( format_string, MERIDIEM, index, n );
   if ( ( i1 >= 0 ) && ( i1 <= i ) )
   {
      i = i1;
      format_field_put( result, CODE_MERIDIEM, i, MERIDIEM_LENGTH, MERIDIEM_FMTSPEC, MERIDIEM_INPUT_LENGTH, MERIDIEM_SPACER, MERIDIEM_ERROR );
   }

   if ( (*result).code == 0 )
   {
      // if format not found, return NULL
      format_field_dispose( &result );
   }
   else
   {
      // update start_pos
      *start_pos = i + (*result).length;
   }

   return result;
}

/**
   parse_format_string

   fill a formatter-parser with the info in its format string

   @param dtfp the date time formatter parser
*/

static
void
parse_format_string( date_time_formatter_parser_t *dtfp )
{
   int32_t start_pos = 0;
   int32_t n = 0;
   int32_t index = 0;
   format_field_t *ff = NULL;
   format_field_t *last_ff = NULL;
   string_t *s = NULL;
   string_t *format_string = NULL;
   string_t *output_template = NULL;

   n = string_count( (*dtfp).format_string ) - 1;
   format_string = (*dtfp).format_string;
   output_template = (*dtfp).output_template;
   string_wipe_out( output_template );

   // find and save format fields
   while( start_pos < n )
   {
      ff = find_next_format_field( format_string, &start_pos );
      if ( ff == NULL )
      {
         break;
      }
      else
      {
         (*dtfp).num_format_fields = (*dtfp).num_format_fields + 1;

         if ( (*dtfp).format_fields == NULL )
         {
            (*dtfp).format_fields = ff;
            (*ff).next = NULL;
            last_ff = ff;
         }
         else
         {
            ( *last_ff ).next = ff;
            last_ff = ff;
            (*ff).next = NULL;
         }

      }
   }

   // fill output_template
   if ( (*dtfp).format_fields != NULL )
   {
      ff = (*dtfp).format_fields;

      while( ff != NULL )
      {
         if ( index <= (*ff).position - 1 )
         {
            s = string_substring( format_string, index, (*ff).position - 1 );
            string_append( output_template, s );
            string_deep_dispose( &s );
         }

         format_field_put_output_position( ff, string_count( output_template ) );

         string_append_cstring( output_template, (*ff).spacer );
         index = (*ff).position + (*ff).length;
         ff = (*ff).next;
      }

      // get text after last format field specifier to end of format string
      if ( index <= n )
      {
         s = string_substring( format_string, index, n );
         string_append( output_template, s );
         string_deep_dispose( &s );
      }
   }

   return;
}

#if INVARIANT_CONDITIONAL != 0

static
int32_t
format_string_not_null( date_time_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).format_string != NULL );

   return result;
}

static
int32_t
last_error_not_null( date_time_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).last_error != NULL );

   return result;
}

static
int32_t
output_template_not_null( date_time_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).output_template != NULL );

   return result;
}

static
int32_t
format_fields_valid( date_time_formatter_parser_t *current )
{
   int32_t result = 1;
   int32_t count = 0;
   int32_t flag = 0;
   format_field_t *ff = NULL;

   if ( (*current).format_fields != NULL )
   {
      ff = (*current).format_fields;
      while( count <= (*current).num_format_fields + 1 )
      {
         if ( ff != NULL )
         {
            count = count + 1;
            ff = (*ff).next;
         }
         else
         {
            flag = 1;
            break;
         }
      }
      result = ( ( (*current).num_format_fields == count ) && ( flag == 1 ) );
   }

   return result;
}

static
int32_t
base_century_ok( date_time_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( ( (*current).base_century % 100 ) == 0 );

   if ( result == 1 )
   {
      result = ( (*current).base_century >= 0 );
   }

   return result;
}

static
void invariant( date_time_formatter_parser_t *current )
{
   assert( ( ( void ) "format string not null", format_string_not_null( current ) ) );
   assert( ( ( void ) "last error not null", last_error_not_null( current ) ) );
   assert( ( ( void ) "output template not null", output_template_not_null( current ) ) );
   assert( ( ( void ) "format fields valid", format_fields_valid( current ) ) );
   assert( ( ( void ) "base century ok", base_century_ok( current ) ) );
   return;
}

#endif

/**
   date_time_formatter_parser_make
*/

date_time_formatter_parser_t *
date_time_formatter_parser_make
(
   string_t *format_string
)
{
   PRECONDITION( "format_string not null", format_string != NULL );

   // allocate date_time_formatter_parser struct
   date_time_formatter_parser_t * result = ( date_time_formatter_parser_t * ) calloc( 1, sizeof( date_time_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_FORMATTER_PARSER_TYPE;

   // init format_string
   (*result).format_string = string_deep_clone( format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_format_fields
   (*result).num_format_fields = 0;

   // init format_fields
   (*result).format_fields = NULL;

   // set default base century;
   (*result).base_century = 2000;

   // parse the format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_formatter_parser_make_cstring
*/

date_time_formatter_parser_t *
date_time_formatter_parser_make_cstring
(
   char_t *format_string
)
{
   PRECONDITION( "format_string not null", format_string != NULL );

   // allocate date_time_formatter_parser struct
   date_time_formatter_parser_t * result = ( date_time_formatter_parser_t * ) calloc( 1, sizeof( date_time_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_FORMATTER_PARSER_TYPE;

   // init format_string
   (*result).format_string = string_make_from_cstring( format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_format_fields
   (*result).num_format_fields = 0;

   // init format_fields
   (*result).format_fields = NULL;

   // set default base century;
   (*result).base_century = 2000;

   // parse the format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_formatter_parser_clone
*/

date_time_formatter_parser_t *
date_time_formatter_parser_clone( date_time_formatter_parser_t *current )
{
   PRECONDITION( "date_time_formatter_parser not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );

   date_time_formatter_parser_t *result = NULL;
   format_field_t *ff = NULL;
   format_field_t *ff1 = NULL;
   format_field_t *last_ff = NULL;

   // allocate date_time_formatter_parser struct
   result = ( date_time_formatter_parser_t * ) calloc( 1, sizeof( date_time_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_FORMATTER_PARSER_TYPE;

   // lock mutex
   LOCK( (*current).mutex );

   // format_string
   (*result).format_string = string_deep_clone( (*current).format_string );

   // last_error
   (*result).last_error = string_deep_clone( (*current).last_error );

   // output_template
   (*result).output_template = string_deep_clone( (*current).output_template );

   // num_format_fields
   (*result).num_format_fields = (*current).num_format_fields;

   // format_fields
   ff = (*current).format_fields;
   while( ff != NULL )
   {
      ff1 = format_field_clone( ff );

      if ( last_ff == NULL )
      {
         (*result).format_fields = ff1;
         (*ff1).next = NULL;
         last_ff = ff1;
      }
      else
      {
         ( *last_ff ).next = ff1;
         last_ff = ff1;
         (*ff1).next = NULL;
      }

      ff = (*ff).next;
   }

   // base century
   (*result).base_century = (*current).base_century;

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_formatter_parser_deep_clone
*/

date_time_formatter_parser_t *
date_time_formatter_parser_deep_clone( date_time_formatter_parser_t *current )
{
   // deep clone is same as clone for this type
   return date_time_formatter_parser_clone( current );
}

/**
  is_equal
*/

static
int32_t
is_equal( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other )
{
   int32_t result = 1;

   if ( string_is_deep_equal( (*current).format_string, (*other).format_string ) == 0 )
   {
      result = 0;
   }

   if ( (*current).base_century != (*other).base_century )
   {
      result = 0;
   }

   return result;
};

/**
   date_time_formatter_parser_is_equal
*/

int32_t
date_time_formatter_parser_is_equal( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
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
   date_time_formatter_parser_is_deep_equal
*/

int32_t
date_time_formatter_parser_is_deep_equal( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other )
{
   // is_deep_equal is same as is_equal for this type
   return date_time_formatter_parser_is_equal( current, other );
}

/**
   date_time_formatter_parser_copy
*/

void
date_time_formatter_parser_copy( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_FORMATTER_PARSER_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   format_field_t *ff_current = NULL;
   format_field_t *ff1 = NULL;
   format_field_t *ff_other = NULL;
   format_field_t *last_ff = NULL;

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   // format_string
   string_wipe_out( (*current).format_string );
   string_append( (*current).format_string, (*other).format_string );

   // last_error
   string_wipe_out( (*current).last_error );
   string_append( (*current).last_error, (*other).last_error );

   // output_template
   string_wipe_out( (*current).output_template );
   string_append( (*current).output_template, (*other).output_template );

   // wipe out format fields
   ff_current = (*current).format_fields;
   (*current).format_fields = NULL;

   while ( ff_current != NULL )
   {
      ff1 = ( *ff_current ).next;
      format_field_dispose( &ff_current );
      ff_current = ff1;
   }

   // num_format_fields
   (*current).num_format_fields = (*other).num_format_fields;
   (*current).format_fields = NULL;

   // format_fields
   ff_other = (*other).format_fields;
   while( ff_other != NULL )
   {
      ff1 = format_field_clone( ff_other );

      if ( (*current).format_fields == NULL )
      {
         (*current).format_fields = ff1;
         (*ff1).next = NULL;
         last_ff = ff1;
      }
      else
      {
         ( *last_ff ).next = ff1;
         last_ff = ff1;
         (*ff1).next = NULL;
      }

      ff_other = ( *ff_other ).next;
   }

   // base_century
   (*current).base_century = (*other).base_century;

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_formatter_parser_deep_copy
*/

void
date_time_formatter_parser_deep_copy( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other )
{
   // deep copy is same as copy for this type
   date_time_formatter_parser_copy( current, other );
   return;
}

/**
   date_time_formatter_parser_dispose
*/

void
date_time_formatter_parser_dispose( date_time_formatter_parser_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   format_field_t *ff_current = NULL;
   format_field_t *ff1 = NULL;

   // free strings
   string_deep_dispose( &(**current).format_string );
   string_deep_dispose( &(**current).last_error );
   string_deep_dispose( &(**current).output_template );

   (**current).num_format_fields = 0;

   // free format fields
   ff_current = (**current).format_fields;
   (**current).format_fields = NULL;

   while ( ff_current != NULL )
   {
      ff1 = ( *ff_current ).next;
      format_field_dispose( &ff_current );
      ff_current = ff1;
   }

   // delete date_time_formatter_parser struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   date_time_formatter_parser_deep_dispose
*/

void
date_time_formatter_parser_deep_dispose( date_time_formatter_parser_t **current )
{
   // deep_dispose is same as dispose for this type
   date_time_formatter_parser_dispose( current );
   return;
}

/**
   date_time_formatter_parser_format_string
*/

string_t *
date_time_formatter_parser_format_string( date_time_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).format_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_last_error
*/

string_t *
date_time_formatter_parser_last_error( date_time_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).last_error );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_base_century
*/

int32_t
date_time_formatter_parser_base_century( date_time_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).base_century;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Helper functions
*/

/**
   string_code_year_4_valid

   evaluate a string containing a year against a format field for validity

   @param s the year as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_year_4_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   char_t c0 = 0;
   char_t c1 = 0;
   char_t c2 = 0;
   char_t c3 = 0;
   char_t str[80] = {0};

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );
   c2 = string_item( s, (*ff).input_length - 3 );
   c3 = string_item( s, (*ff).input_length - 4 );

   str[0] = c3;
   str[1] = c2;
   str[2] = c1;
   str[3] = c0;
   str[4] = 0;

   sscanf( str, "%d", &result );

   if (
      ( is_digit( c0 ) == 1 )
      && ( is_digit( c1 ) == 1 )
      && ( is_digit( c2 ) == 1 )
      && ( is_digit( c3 ) == 1 )
   )
   {
      result = 1;
   }
   else if (
      ( is_digit( c0 ) == 1 )
      && ( is_digit( c1 ) == 1 )
      && ( is_digit( c2 ) == 1 )
      && ( is_space( c3 ) == 1 )
   )
   {
      result = 1;
   }
   else if (
      ( is_digit( c0 ) == 1 )
      && ( is_digit( c1 ) == 1 )
      && ( is_space( c2 ) == 1 )
      && ( is_space( c3 ) == 1 )
   )
   {
      result = 1;
   }
   else if (
      ( is_digit( c0 ) == 1 )
      && ( is_space( c1 ) == 1 )
      && ( is_space( c2 ) == 1 )
      && ( is_space( c3 ) == 1 )
   )
   {
      result = 1;
   }

   // no year 0
   if ( result == 1 )
   {
      if ( string_as_int32( s ) == 0 )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_year_2_valid

   evaluate a string containing a year against a format field for validity

   @param s the year as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_year_2_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   return result;
}

/**
   string_code_month_valid

   evaluate a string containing a month against a format field for validity

   @param s the month as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_month_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < MIN_MONTH ) || ( i > MAX_MONTH ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_month_lz_valid

   evaluate a string containing a month against a format field for validity

   @param s the month as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_month_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < MIN_MONTH ) || ( i > MAX_MONTH ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_month_letter_valid

   evaluate a string containing a month against a format field for validity

   @param s the month as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_month_letter_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   char_t c0 = 0;
   char_t c1 = 0;
   char_t c2 = 0;
   char_t str[12] = {0};
   string_t *s1 = NULL;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );
   c2 = string_item( s, (*ff).input_length - 3 );

   str[0] = c2;
   str[1] = c1;
   str[2] = c0;
   str[3] = 0;

   s1 = string_make_from_cstring( str );
   string_to_lower( s1 );

   if ( string_is_equal_cstring( s1, "jan" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "feb" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "mar" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "apr" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "may" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "jun" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "jul" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "aug" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "sep" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "oct" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "nov" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "dec" ) == 1 )
   {
      result = 1;
   }

   string_deep_dispose( &s1 );

   return result;
}

/**
   string_code_day_valid

   evaluate a string containing a day against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_day_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < MIN_DAY ) || ( i > MAX_MONTH_DAY ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_day_lz_valid

   evaluate a string containing a day against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_day_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < MIN_DAY ) || ( i > MAX_MONTH_DAY ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_day_letter_valid

   evaluate a string containing a day against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_day_letter_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   char_t c0 = 0;
   char_t c1 = 0;
   char_t c2 = 0;
   char_t str[12] = {0};
   string_t *s1 = NULL;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );
   c2 = string_item( s, (*ff).input_length - 3 );

   str[0] = c2;
   str[1] = c1;
   str[2] = c0;
   str[3] = 0;

   s1 = string_make_from_cstring( str );
   string_to_lower( s1 );

   if ( string_is_equal_cstring( s1, "mon" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "tue" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "wed" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "thu" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "fri" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "sat" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "sun" ) == 1 )
   {
      result = 1;
   }

   string_deep_dispose( &s1 );

   return result;
}

/**
   string_code_hour_valid

   evaluate a string containing an hour against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_hour_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > MAX_HOURS_IN_DAY ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_hour_lz_valid

   evaluate a string containing an hour against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_hour_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > MAX_HOURS_IN_DAY ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_hour_12_valid

   evaluate a string containing an hour against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_hour_12_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > HOURS_IN_HALF_DAY ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_hour_12_lz_valid

   evaluate a string containing an hour against a format field for validity

   @param s the day as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_hour_12_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > HOURS_IN_HALF_DAY ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_minute_valid

   evaluate a string containing a minute against a format field for validity

   @param s the minute as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_minute_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > MAX_MINUTES_IN_HOUR ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_minute_lz_valid

   evaluate a string containing a minute against a format field for validity

   @param s the minute as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_minute_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > MAX_MINUTES_IN_HOUR ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_second_valid

   evaluate a string containing a second against a format field for validity

   @param s the second as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_second_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }
   else if ( ( is_digit( c0 ) == 1 ) && ( is_space( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > MAX_SECONDS_IN_MINUTE ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_second_lz_valid

   evaluate a string containing a second against a format field for validity

   @param s the second as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_second_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int32_t i = 0;
   char_t c0 = 0;
   char_t c1 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) )
   {
      result = 1;
   }

   if ( result == 1 )
   {
      i = string_as_int32( s );
      if ( ( i < 0 ) || ( i > MAX_SECONDS_IN_MINUTE ) )
      {
         result = 0;
      }
   }

   return result;
}

/**
   string_code_millisecond_lz_valid

   evaluate a string containing a millisecond against a format field for validity

   @param s the second as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_millisecond_lz_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   char_t c0 = 0;
   char_t c1 = 0;
   char_t c2 = 0;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );
   c2 = string_item( s, (*ff).input_length - 3 );

   if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) && ( is_digit( c2 ) == 1 ) )
   {
      result = 1;
   }

   return result;
}

/**
   string_code_meridiem_valid

   evaluate a string containing a meridiem against a format field for validity

   @param s the meridiem as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_meridiem_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   char_t c0 = 0;
   char_t c1 = 0;
   char_t str[12] = {0};
   string_t *s1 = NULL;

   c0 = string_item( s, (*ff).input_length - 1 );
   c1 = string_item( s, (*ff).input_length - 2 );

   str[0] = c1;
   str[1] = c0;
   str[2] = 0;

   s1 = string_make_from_cstring( str );
   string_to_lower( s1 );

   if ( string_is_equal_cstring( s1, "am" ) == 1 )
   {
      result = 1;
   }
   else if ( string_is_equal_cstring( s1, "pm" ) == 1 )
   {
      result = 1;
   }

   string_deep_dispose( &s1 );

   return result;
}

/**
   set_error_string

   set the error string in a format  field

   @param error_string the error string
   @param ff the format field
*/

static
void
set_error_string( string_t *error_string, format_field_t *ff )
{
   string_append_cstring( error_string, (*ff).error_message );
   string_insert_int32( error_string, (*ff).position, string_count( error_string ) );
   string_append_cstring( error_string, "." );

   return;
}

/**
   corresponds

   check the validity of a date-time string

   @param current the date time formatter parser
   @param input the date-time string to check
   @return 1 if the input is valid, 0 otherwise
*/

static
int32_t
corresponds( date_time_formatter_parser_t *current, string_t *input )
{
   int32_t result = 1;
   format_field_t *ff = NULL;
   string_t *s = NULL;
   int32_t year = 0;
   int32_t month = 0;
   int32_t day = 0;
   int32_t hour_12_flag = 0;
   int32_t meridiem_flag = 0;

   ff = (*current).format_fields;
   string_wipe_out( (*current).last_error );

   // test each format field
   while ( ( ff != NULL ) && ( result == 1 ) )
   {
      // get substring of input string that is associated with the format field
      if ( (*ff).output_position > string_count( input ) - 1 )
      {
         string_append_cstring( (*current).last_error, "Error - data string does not contain enough fields" );
         result = 0;
         break;
      }
      else
      {
         s = string_substring( input, (*ff).output_position, (*ff).output_position + (*ff).input_length - 1 );
      }

      if ( (*ff).code == CODE_YEAR_4 )
      {
         result = string_code_year_4_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            year = string_as_int32( s );
         }
      }
      else if ( (*ff).code == CODE_YEAR_2 )
      {
         result = string_code_year_2_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            year = (*current).base_century + string_as_int32( s );
         }
      }
      else if ( (*ff).code == CODE_MONTH )
      {
         result = string_code_month_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            month = string_as_int32( s );
         }
      }
      else if ( (*ff).code == CODE_MONTH_LZ )
      {
         result = string_code_month_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            month = string_as_int32( s );
         }
      }
      else if ( (*ff).code == CODE_MONTH_LETTER )
      {
         result = string_code_month_letter_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            month = month_abbrev_to_int( s );
         }
      }
      else if ( (*ff).code == CODE_DAY )
      {
         result = string_code_day_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            day = string_as_int32( s );
         }
      }
      else if ( (*ff).code == CODE_DAY_LZ )
      {
         result = string_code_day_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            day = string_as_int32( s );
         }
      }
      else if ( (*ff).code == CODE_DAY_LETTER )
      {
         result = string_code_day_letter_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
         else
         {
            // day of week is not day of month
         }
      }
      else if ( (*ff).code == CODE_HOUR )
      {
         result = string_code_hour_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_HOUR_LZ )
      {
         result = string_code_hour_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_HOUR_12 )
      {
         hour_12_flag = 1;
         result = string_code_hour_12_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_HOUR_12_LZ )
      {
         hour_12_flag = 1;
         result = string_code_hour_12_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_MINUTE )
      {
         result = string_code_minute_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_MINUTE_LZ )
      {
         result = string_code_minute_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_SECOND )
      {
         result = string_code_second_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_SECOND_LZ )
      {
         result = string_code_second_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_MILLISECOND_LZ )
      {
         result = string_code_millisecond_lz_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }
      else if ( (*ff).code == CODE_MERIDIEM )
      {
         meridiem_flag = 1;
         result = string_code_meridiem_valid( s, ff );
         if ( result == 0 )
         {
            set_error_string( (*current).last_error, ff );
         }
      }

      // get next format field
      ff = (*ff).next;

      // dispose of temp variable
      string_deep_dispose( &s );
   }

   if ( result == 1 )
   {
      if ( day_ok( year, month, day ) == 0 )
      {
         result = 0;
         string_append_cstring( (*current).last_error, "Invalid day of month." );
      }

      if ( ( hour_12_flag == 0 ) && ( meridiem_flag == 1 ) )
      {
         result = 0;
         string_append_cstring( (*current).last_error, "AM/PM set but hour set to 24 hours." );
      }
      else if ( ( hour_12_flag == 1 ) && ( meridiem_flag == 0 ) )
      {
         result = 0;
         string_append_cstring( (*current).last_error, "Hour set to 12 hours but no AM/PM." );
      }

   }

   return result;
}

/**
   parse

   parse a date-time string into a date-time class instance

   @param current the date time formatter parser
   @param input the date-time string to check
   @return a new date-time class instance
*/

static
date_time_t *
parse( date_time_formatter_parser_t *current, string_t *input )
{
   date_time_t *result = NULL;
   format_field_t *ff = NULL;
   string_t *s = NULL;
   int32_t year = 0;
   int32_t month = 0;
   int32_t day = 0;
   int32_t hour = 0;
   int32_t minute = 0;
   int32_t second = 0;
   int32_t millisecond = 0;
   int32_t meridiem = 0;

   ff = (*current).format_fields;

   // test each format field
   while ( ff != NULL )
   {
      // get substring of input string that is associated with the format field
      s = string_substring( input, (*ff).output_position, (*ff).output_position + (*ff).input_length - 1 );

      if ( (*ff).code == CODE_YEAR_4 )
      {
         year = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_YEAR_2 )
      {
         year = (*current).base_century + string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MONTH )
      {
         month = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MONTH_LZ )
      {
         month = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MONTH_LETTER )
      {
         month = month_abbrev_to_int( s );
      }
      else if ( (*ff).code == CODE_DAY )
      {
         day = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_DAY_LZ )
      {
         day = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_DAY_LETTER )
      {
         // day of week is not day of month
      }
      else if ( (*ff).code == CODE_HOUR )
      {
         hour = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_HOUR_LZ )
      {
         hour = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_HOUR_12 )
      {
         hour = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_HOUR_12_LZ )
      {
         hour = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MINUTE )
      {
         minute = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MINUTE_LZ )
      {
         minute = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_SECOND )
      {
         second = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_SECOND_LZ )
      {
         second = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MILLISECOND_LZ )
      {
         millisecond = string_as_int32( s );
      }
      else if ( (*ff).code == CODE_MERIDIEM )
      {
         meridiem = meridiem_abbrev_to_int( s );
      }

      // get next format field
      ff = (*ff).next;

      // dispose of temp variable
      string_deep_dispose( &s );
   }

   result
      =  date_time_make
         (
            year,
            month,
            day,
            hour + meridiem * HOURS_IN_HALF_DAY,
            minute,
            second,
            millisecond
         );

   return result;
}

/**
   put_date_field_in_string

   put a formatted date-time field into a string

   @param output the date-time string being built up
   @param ff the format field
   @param value the value being formatted
*/

static
void
put_date_field_in_string( string_t *output, format_field_t *ff, int32_t value )
{
   string_t *s = NULL;
   char_t str[80] = {0};

   sprintf( str, (*ff).format_specifier, value );
   s = string_make_from_cstring(  str );
   string_replace( output, s, (*ff).output_position, (*ff).output_position + (*ff).input_length - 1 );
   string_deep_dispose( &s );

   return;
}

/**
   format

   format a date-time class instance into a date-time string

   @param current the date time formatter parser
   @param dt the data time class instance
   @param the formatted date-time string
*/

static
string_t *
format( date_time_formatter_parser_t *current, date_time_t *dt )
{
   string_t *result = NULL;
   format_field_t *ff = NULL;
   int32_t i = 0;
   string_t *s = NULL;

   result = string_deep_clone( (*current).output_template );

   ff = (*current).format_fields;

   // test each format field
   while ( ff != NULL )
   {
      // put formatted date into output string

      if ( (*ff).code == CODE_YEAR_4 )
      {
         i = date_time_year( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_YEAR_2 )
      {
         i = date_time_year( dt ) % YEARS_IN_CENTURY;
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MONTH )
      {
         i = date_time_month( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MONTH_LZ )
      {
         i = date_time_month( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MONTH_LETTER )
      {
         i = date_time_month( dt );
         s = string_make_from_cstring( int_to_month_abbrev( i ) );
         string_replace( result, s, (*ff).output_position, (*ff).output_position + (*ff).length - 1 );
         string_deep_dispose( &s );
      }
      else if ( (*ff).code == CODE_DAY )
      {
         i = date_time_day( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_DAY_LZ )
      {
         i = date_time_day( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_DAY_LETTER )
      {
         i = date_time_day_of_week( dt );
         s = string_make_from_cstring( int_to_day_abbrev( i ) );
         string_replace( result, s, (*ff).output_position, (*ff).output_position + (*ff).length - 1 );
         string_deep_dispose( &s );
      }
      else if ( (*ff).code == CODE_HOUR )
      {
         i = date_time_hour_24( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_HOUR_LZ )
      {
         i = date_time_hour_24( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_HOUR_12 )
      {
         i = date_time_hour_12( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_HOUR_12_LZ )
      {
         i = date_time_hour_12( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MINUTE )
      {
         i = date_time_minute( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MINUTE_LZ )
      {
         i = date_time_minute( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_SECOND )
      {
         i = date_time_second( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_SECOND_LZ )
      {
         i = date_time_second( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MILLISECOND_LZ )
      {
         i = date_time_millisecond( dt );
         put_date_field_in_string( result, ff, i );
      }
      else if ( (*ff).code == CODE_MERIDIEM )
      {
         i = date_time_meridiem( dt );
         s = string_make_from_cstring( int_to_meridiem_abbrev( i ) );
         string_replace( result, s, (*ff).output_position, (*ff).output_position + (*ff).length - 1 );
         string_deep_dispose( &s );
      }

      // get next format field
      ff = (*ff).next;

   }

   return result;
}

/**
   date_time_formatter_corresponds
*/

int32_t
date_time_formatter_parser_corresponds( date_time_formatter_parser_t *current, string_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = corresponds( current, input );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_corresponds_cstring
*/

int32_t
date_time_formatter_parser_corresponds_cstring( date_time_formatter_parser_t *current, char_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   string_t *s = string_make_from_cstring( input );

   result = corresponds( current, s );

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_parse
*/

date_time_t *
date_time_formatter_parser_parse( date_time_formatter_parser_t *current, string_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_t *result = parse( current, input );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_duration_parse_cstring
*/

date_time_t *
date_time_formatter_parser_parse_cstring( date_time_formatter_parser_t *current, char_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_t *result = NULL;
   string_t *s = string_make_from_cstring( input );

   result = parse( current, s );

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_format
*/

string_t *
date_time_formatter_parser_format( date_time_formatter_parser_t *current, date_time_t *dt )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "dt not null", dt != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = format( current, dt );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_format_cstring
*/

char_t *
date_time_formatter_parser_format_cstring( date_time_formatter_parser_t *current, date_time_t *dt )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "dt not null", dt != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = NULL;
   string_t *s = format( current, dt );

   result = calloc( string_count( s ) + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   strcpy( result, string_as_cstring( s ) );

   string_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_formatter_parser_put_format_string
*/

void
date_time_formatter_parser_put_format_string
(
   date_time_formatter_parser_t *current,
   string_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   format_field_t *ff = NULL;
   format_field_t *ff1 = NULL;

   // format_string
   string_wipe_out( (*current).format_string );
   string_append( (*current).format_string, format_string );

   // init last_error
   string_wipe_out( (*current).last_error );

   // init output_template
   string_wipe_out( (*current).output_template );

   // init num_format_fields
   (*current).num_format_fields = 0;

   // free format fields
   ff = (*current).format_fields;
   (*current).format_fields = NULL;

   while ( ff != NULL )
   {
      ff1 = (*ff).next;
      format_field_dispose( &ff );
      ff = ff1;
   }

   // parse the format string
   parse_format_string( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_formatter_parser_put_format_string_cstring
*/

void
date_time_formatter_parser_put_format_string_cstring
(
   date_time_formatter_parser_t *current,
   char_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *s = string_make_from_cstring( format_string );

   format_field_t *ff = NULL;
   format_field_t *ff1 = NULL;

   // format_string
   string_wipe_out( (*current).format_string );
   string_append( (*current).format_string, s );

   // init last_error
   string_wipe_out( (*current).last_error );

   // init output_template
   string_wipe_out( (*current).output_template );

   // init num_format_fields
   (*current).num_format_fields = 0;

   // free format fields
   ff = (*current).format_fields;
   (*current).format_fields = NULL;

   while ( ff != NULL )
   {
      ff1 = (*ff).next;
      format_field_dispose( &ff );
      ff = ff1;
   }

   // parse the format string
   parse_format_string( current );

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_formatter_parser_put_base_century
*/

void
date_time_formatter_parser_put_base_century
(
   date_time_formatter_parser_t *current,
   int32_t base_century
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_FORMATTER_PARSER_TYPE );
   PRECONDITION( "base_century positive", base_century > 0 );
   PRECONDITION( "base_century ok", ( base_century % 100 ) == 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set base century
   (*current).base_century = base_century;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


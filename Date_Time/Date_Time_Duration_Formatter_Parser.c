/**
 @file Date_Time_Duration_Formatter_Parser.c
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

 Function definitions for the opaque date_time_duration_formatter_parser_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Date_Time_Duration_Formatter_Parser.h"
#include "Date_Time_Formatter_Parser.h"
#include "Date_Time.h"
#include <string.h>

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

// Day of week: Sunday is 1, Monday is 2, Saturday is 7
#define BASE_YEAR 1600

// AM and PM
#define AM_MERIDIEM 0
#define PM_MERIDIEM 1
static char_t *AM_TEXT =  "AM";
static char_t *PM_TEXT =  "PM";

// Format field codes and specifiers

// days
#define CODE_DAY_N 5
#define DAY_N "*DD"
static char_t *DAY_N_FMTSPEC  = "%d";
static char_t *DAY_N_TAG = "%*DD%";
static char_t *DAY_N_ERROR = "Invalid day at ";

// hours
#define CODE_HOUR_N 7
#define HOUR_N "*HH"
static char_t *HOUR_N_FMTSPEC = "%d";
static char_t *HOUR_N_TAG = "%*HH%";
static char_t *HOUR_N_ERROR = "Invalid hour at ";

// 2 digit hour, no leading zero
#define CODE_HOUR 8
#define HOUR "HH"
static char_t *HOUR_FMTSPEC = "%d";
static char_t *HOUR_TAG = "%HH%";
static char_t *HOUR_ERROR = "Invalid 2 digit hour at ";

// 2 digit hour, leading zero
#define CODE_HOUR_LZ 9
#define HOUR_LZ "[0]HH"
static char_t *HOUR_LZ_FMTSPEC = "%02d";
static char_t *HOUR_LZ_TAG = "%[0]HH%";
static char_t *HOUR_LZ_ERROR = "Invalid zero padded 2 digit hour at ";

// 2 digit hour_12, no leading zero
#define CODE_HOUR_12 10
#define HOUR_12 "H1"
static char_t *HOUR_12_FMTSPEC = "%d";
static char_t *HOUR_12_TAG = "%H1%";
static char_t *HOUR_12_ERROR = "Invalid 2 digit hour_12 at ";

// 2 digit hour_12, leading zero
#define CODE_HOUR_12_LZ 11
#define HOUR_12_LZ "[0]H1"
static char_t *HOUR_12_LZ_FMTSPEC = "%02d";
static char_t *HOUR_12_LZ_TAG = "%[0]H1%";
static char_t *HOUR_12_LZ_ERROR = "Invalid zero padded 2 digit hour_12 at ";

// minutes
#define CODE_MINUTE_N 12
#define MINUTE_N "*MI"
static char_t *MINUTE_N_FMTSPEC = "%d";
static char_t *MINUTE_N_TAG = "%*MI%";
static char_t *MINUTE_N_ERROR = "Invalid minute at ";

// 2 digit minute, no leading zero
#define CODE_MINUTE 13
#define MINUTE "MI"
static char_t *MINUTE_FMTSPEC = "%d";
static char_t *MINUTE_TAG = "%MI%";
static char_t *MINUTE_ERROR = "Invalid 2 digit minute at ";

// 2 digit minute, leading zero
#define CODE_MINUTE_LZ 14
#define MINUTE_LZ "[0]MI"
static char_t *MINUTE_LZ_FMTSPEC = "%02d";
static char_t *MINUTE_LZ_TAG = "%[0]MI%";
static char_t *MINUTE_LZ_ERROR = "Invalid zero padded 2 digit minute at ";

// seconds
#define CODE_SECOND_N 15
#define SECOND_N "*SS"
static char_t *SECOND_N_FMTSPEC = "%d";
static char_t *SECOND_N_TAG = "%*SS%";
static char_t *SECOND_N_ERROR = "Invalid second at ";

// 2 digit second, no leading zero
#define CODE_SECOND 16
#define SECOND "SS"
static char_t *SECOND_FMTSPEC = "%d";
static char_t *SECOND_TAG = "%SS%";
static char_t *SECOND_ERROR = "Invalid 2 digit second at ";

// 2 digit second, leading zero
#define CODE_SECOND_LZ 17
#define SECOND_LZ "[0]SS"
static char_t *SECOND_LZ_FMTSPEC = "%02d";
static char_t *SECOND_LZ_TAG = "%[0]SS%";
static char_t *SECOND_LZ_ERROR = "Invalid zero padded 2 digit second at ";

// milliseconds
#define CODE_MILLISECOND_N 18
#define MILLISECOND_N "*MLS"
static char_t *MILLISECOND_N_FMTSPEC = "%ld";
static char_t *MILLISECOND_N_TAG = "%*MLS%";
static char_t *MILLISECOND_N_ERROR = "Invalid millisecond at ";

// milliseconds
#define CODE_MILLISECOND 19
#define MILLISECOND "MLS"
static char_t *MILLISECOND_FMTSPEC = "%d";
static char_t *MILLISECOND_TAG = "%MLS%";
static char_t *MILLISECOND_ERROR = "Invalid milliseconds at ";

// 3 digit millisecond, leading zero
#define CODE_MILLISECOND_LZ 20
#define MILLISECOND_LZ "[0]MLS"
static char_t *MILLISECOND_LZ_FMTSPEC = "%03d";
static char_t *MILLISECOND_LZ_TAG = "%[0]MLS%";
static char_t *MILLISECOND_LZ_ERROR = "Invalid zero padded 3 digit millisecond at ";

// 2 letter meridiem
#define CODE_MERIDIEM 21
#define MERIDIEM "MD"
static char_t *MERIDIEM_FMTSPEC = "%2s";
static char_t *MERIDIEM_TAG = "%MD%";
static char_t *MERIDIEM_ERROR = "Invalid AM/PM at";

/**
   Format field structure
*/

struct format_field
{
   int32_t code;
   int32_t position;
   char_t *scode;
   char_t *format_specifier;
   char_t *tag;
   char_t *error_message;

   struct format_field *next;
};

typedef struct format_field format_field_t;


/**
   date_time_duration_formatter_parser structure
*/

struct date_time_duration_formatter_parser_struct
{
   int32_t _type;

   date_time_formatter_parser_t *start_fp;
   date_time_formatter_parser_t *end_fp;
   string_t *separator;
   string_t *duration_format_string;
   int32_t separator_count;
   string_t *last_error;
   string_t *output_template;
   int32_t num_duration_format_fields;
   format_field_t *duration_format_fields;
   int32_t base_century;
   int32_t is_start_end;
   int32_t end_is_time_only;
   int32_t is_fixed;

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
   format_field_make

   construct a format field

   @param code the format field code
   @param position the format field position
   @param scode the format field scode
   @param format_specifier the format field format specifier
   @param input_length the format field input length
   @param tag the format field tag
   @param error_message the format field error message
   @return a new format field
*/

static
format_field_t *
format_field_make
(
   int32_t code,
   int32_t position,
   char_t *scode,
   char_t *format_specifier,
   char_t *tag,
   char_t *error_message
)
{
   format_field_t *result = NULL;

   result = ( format_field_t * ) calloc( 1, sizeof( format_field_t ) );
   CHECK( "result allocated correctly", result != NULL );

   (*result).code = code;
   (*result).position = position;
   (*result).format_specifier = format_specifier;
   (*result).scode = scode;
   (*result).tag = tag;
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
   (*result).scode = (*current).scode;
   (*result).format_specifier = (*current).format_specifier;
   (*result).tag = (*current).tag;
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
   @param scode the format field scode
   @param format_specifier the format field format specifier
   @param input_length the format field input length
   @param tag the format field tag
   @param error_message the format field error message
*/

static
void
format_field_put
(
   format_field_t *current,
   int32_t code,
   int32_t position,
   char_t *scode,
   char_t *format_specifier,
   char_t *tag,
   char_t *error_message
)
{
   (*current).code = code;
   (*current).position = position;
   (*current).scode = scode;
   (*current).format_specifier = format_specifier;
   (*current).tag = tag;
   (*current).error_message = error_message;

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
   int32_t n = 0;
   int32_t i = 0;
   int32_t i1 = 0;

   n = string_count( format_string ) - 1;
   i = *start_pos;

   result = format_field_make( 0, 0, "", "", "", "" );

   // DAY_N
   i1 = string_substring_index_in_bounds_cstring( format_string, DAY_N, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( DAY_N );
      format_field_put( result, CODE_DAY_N, i, DAY_N, DAY_N_FMTSPEC, DAY_N_TAG, DAY_N_ERROR );
      goto format_field_found;
   }

   // HOUR_N
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_N, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( HOUR_N );
      format_field_put( result, CODE_HOUR_N, i, HOUR_N, HOUR_N_FMTSPEC, HOUR_N_TAG, HOUR_N_ERROR );
      goto format_field_found;
   }

   // HOUR_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_LZ, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( HOUR_LZ );
      format_field_put( result, CODE_HOUR_LZ, i, HOUR_LZ, HOUR_LZ_FMTSPEC, HOUR_LZ_TAG, HOUR_LZ_ERROR );
      goto format_field_found;
   }

   // HOUR_12_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_12_LZ, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( HOUR_12_LZ );
      format_field_put( result, CODE_HOUR_12_LZ, i, HOUR_12_LZ, HOUR_12_LZ_FMTSPEC, HOUR_12_LZ_TAG, HOUR_12_LZ_ERROR );
      goto format_field_found;
   }

   // HOUR_12
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR_12, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( HOUR_12 );
      format_field_put( result, CODE_HOUR_12, i, HOUR_12, HOUR_12_FMTSPEC, HOUR_12_TAG, HOUR_12_ERROR );
      goto format_field_found;
   }

   // HOUR
   i1 = string_substring_index_in_bounds_cstring( format_string, HOUR, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( HOUR );
      format_field_put( result, CODE_HOUR, i, HOUR, HOUR_FMTSPEC, HOUR_TAG, HOUR_ERROR );
      goto format_field_found;
   }

   // MINUTE_N
   i1 = string_substring_index_in_bounds_cstring( format_string, MINUTE_N, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MINUTE_N );
      format_field_put( result, CODE_MINUTE_N, i, MINUTE_N, MINUTE_N_FMTSPEC, MINUTE_N_TAG, MINUTE_N_ERROR );
      goto format_field_found;
   }

   // MINUTE_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, MINUTE_LZ, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MINUTE_LZ );
      format_field_put( result, CODE_MINUTE_LZ, i, MINUTE_LZ, MINUTE_LZ_FMTSPEC, MINUTE_LZ_TAG, MINUTE_LZ_ERROR );
      goto format_field_found;
   }

   // MINUTE
   i1 = string_substring_index_in_bounds_cstring( format_string, MINUTE, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MINUTE );
      format_field_put( result, CODE_MINUTE, i, MINUTE, MINUTE_FMTSPEC, MINUTE_TAG, MINUTE_ERROR );
      goto format_field_found;
   }

   // SECOND_N
   i1 = string_substring_index_in_bounds_cstring( format_string, SECOND_N, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( SECOND_N );
      format_field_put( result, CODE_SECOND_N, i, SECOND_N, SECOND_N_FMTSPEC, SECOND_N_TAG, SECOND_N_ERROR );
      goto format_field_found;
   }

   // SECOND_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, SECOND_LZ, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( SECOND_LZ );
      format_field_put( result, CODE_SECOND_LZ, i, SECOND_LZ, SECOND_LZ_FMTSPEC, SECOND_LZ_TAG, SECOND_LZ_ERROR );
      goto format_field_found;
   }

   // SECOND
   i1 = string_substring_index_in_bounds_cstring( format_string, SECOND, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( SECOND );
      format_field_put( result, CODE_SECOND, i, SECOND, SECOND_FMTSPEC, SECOND_TAG, SECOND_ERROR );
      goto format_field_found;
   }

   // MILLISECOND_N
   i1 = string_substring_index_in_bounds_cstring( format_string, MILLISECOND_N, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MILLISECOND_N );
      format_field_put( result, CODE_MILLISECOND_N, i, MILLISECOND_N, MILLISECOND_N_FMTSPEC, MILLISECOND_N_TAG, MILLISECOND_N_ERROR );
      goto format_field_found;
   }

   // MILLISECOND_LZ
   i1 = string_substring_index_in_bounds_cstring( format_string, MILLISECOND_LZ, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MILLISECOND_LZ );
      format_field_put( result, CODE_MILLISECOND_LZ, i, MILLISECOND_LZ, MILLISECOND_LZ_FMTSPEC, MILLISECOND_LZ_TAG, MILLISECOND_LZ_ERROR );
      goto format_field_found;
   }

   // MILLISECOND
   i1 = string_substring_index_in_bounds_cstring( format_string, MILLISECOND, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MILLISECOND );
      format_field_put( result, CODE_MILLISECOND, i, MILLISECOND, MILLISECOND_FMTSPEC, MILLISECOND_TAG, MILLISECOND_ERROR );
      goto format_field_found;
   }

   // MERIDIEM
   i1 = string_substring_index_in_bounds_cstring( format_string, MERIDIEM, i, n );
   if ( i1 >= 0 )
   {
      i = i1 + strlen( MERIDIEM );
      format_field_put( result, CODE_MERIDIEM, i, MERIDIEM, MERIDIEM_FMTSPEC, MERIDIEM_TAG, MERIDIEM_ERROR );
   }

format_field_found:

   if ( (*result).code == 0 )
   {
      // if format not found, return NULL
      format_field_dispose( &result );
   }
   else
   {
      // update start_pos
      *start_pos = i;
   }

   return result;
}

/**
   parse_format_string

   fill a formatter-parser with the info in its format string

   @param dtdfp the date time duration formatter parser
*/

static
void
parse_format_string( date_time_duration_formatter_parser_t *dtdfp )
{
   int32_t start_pos = 0;
   int32_t n = 0;
   format_field_t *ff = NULL;
   format_field_t *last_ff = NULL;
   string_t *format_string = NULL;
   string_t *output_template = NULL;

   n = string_count( (*dtdfp).duration_format_string ) - 1;
   format_string = (*dtdfp).duration_format_string;
   output_template = (*dtdfp).output_template;
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
         (*dtdfp).num_duration_format_fields = (*dtdfp).num_duration_format_fields + 1;

         if ( (*dtdfp).duration_format_fields == NULL )
         {
            (*dtdfp).duration_format_fields = ff;
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
   string_append( output_template, format_string );

   if ( (*dtdfp).duration_format_fields != NULL )
   {
      ff = (*dtdfp).duration_format_fields;

      while( ff != NULL )
      {
         string_replace_all_cstring2( output_template, (*ff).scode, (*ff).tag );
         ff = (*ff).next;
      }
   }

   return;
}

#if INVARIANT_CONDITIONAL != 0

static
int32_t
start_formatter_parser_not_null( date_time_duration_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).start_fp != NULL );

   return result;
}

static
int32_t
end_formatter_parser_not_null( date_time_duration_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).end_fp != NULL );

   return result;
}

static
int32_t
duration_format_string_not_null( date_time_duration_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).duration_format_string != NULL );

   return result;
}

static
int32_t
last_error_not_null( date_time_duration_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).last_error != NULL );

   return result;
}

static
int32_t
output_template_not_null( date_time_duration_formatter_parser_t *current )
{
   int32_t result = 0;

   result = ( (*current).output_template != NULL );

   return result;
}

static
int32_t
format_fields_valid( date_time_duration_formatter_parser_t *current )
{
   int32_t result = 1;
   int32_t count = 0;
   int32_t flag = 0;
   format_field_t *ff = NULL;

   if ( (*current).duration_format_fields != NULL )
   {
      ff = (*current).duration_format_fields;
      while( count <= (*current).num_duration_format_fields + 1 )
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
      result = ( ( (*current).num_duration_format_fields == count ) && ( flag == 1 ) );
   }

   return result;
}

static
int32_t
base_century_ok( date_time_duration_formatter_parser_t *current )
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
void invariant( date_time_duration_formatter_parser_t *current )
{
   assert( ( ( void ) "start formatter parser not null", start_formatter_parser_not_null( current ) ) );
   assert( ( ( void ) "end formatter parser not null", end_formatter_parser_not_null( current ) ) );
   assert( ( ( void ) "duration format string not null", duration_format_string_not_null( current ) ) );
   assert( ( ( void ) "last error not null", last_error_not_null( current ) ) );
   assert( ( ( void ) "output template not null", output_template_not_null( current ) ) );
   assert( ( ( void ) "format fields valid", format_fields_valid( current ) ) );
   assert( ( ( void ) "base century ok", base_century_ok( current ) ) );
   return;
}

#endif

/**
   date_time_duration_formatter_parser_make_start_end
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end
(
   string_t *start_format_string,
   string_t *end_format_string,
   string_t *separator
)
{
   PRECONDITION( "start_format_string not null", start_format_string != NULL );
   PRECONDITION( "end_format_string not null", end_format_string != NULL );
   PRECONDITION( "separator not null", separator != NULL );

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t * result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make( start_format_string );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make( end_format_string );

   // separator
   (*result).separator = string_clone( separator );
   (*result).separator_count
      =   string_substring_count( start_format_string, separator )
          + 1
          + string_substring_count( end_format_string, separator );

   // init duration_format_string
   (*result).duration_format_string = string_make();

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 1;

   // set end_is_time_only
   (*result).end_is_time_only = 0;

   // set is_fixed
   (*result).is_fixed = 1;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_start_end_cstring
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end_cstring
(
   char_t *start_format_string,
   char_t *end_format_string,
   char_t *separator
)
{
   PRECONDITION( "start_format_string not null", start_format_string != NULL );
   PRECONDITION( "end_format_string not null", end_format_string != NULL );

   string_t *s1 = NULL;
   string_t *s2 = NULL;

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t * result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make_cstring( start_format_string );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make_cstring( end_format_string );

   // separator
   (*result).separator = string_make_from_cstring( separator );
   s1 = date_time_formatter_parser_format_string( (*result).start_fp );
   s2 = date_time_formatter_parser_format_string( (*result).end_fp );
   (*result).separator_count
      =  string_substring_count_cstring( s1, separator )
         + 1
         + string_substring_count_cstring( s2, separator );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );

   // init duration_format_string
   (*result).duration_format_string = string_make();

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 1;

   // set end_is_time_only
   (*result).end_is_time_only = 0;

   // set is_fixed
   (*result).is_fixed = 1;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_start_end_time
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end_time
(
   string_t *start_format_string,
   string_t *end_format_string,
   string_t *separator
)
{
   PRECONDITION( "start_format_string not null", start_format_string != NULL );
   PRECONDITION( "end_format_string not null", end_format_string != NULL );
   PRECONDITION( "separator not null", separator != NULL );

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t *result
      =  ( date_time_duration_formatter_parser_t * )
         calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make( start_format_string );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make( end_format_string );

   // separator
   (*result).separator = string_clone( separator );
   (*result).separator_count
      =   string_substring_count( start_format_string, separator )
          + 1
          + string_substring_count( end_format_string, separator );

   // init duration_format_string
   (*result).duration_format_string = string_clone( end_format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 1;

   // set end_is_time_only
   (*result).end_is_time_only = 1;

   // set is_fixed
   (*result).is_fixed = 1;

   // parse the duration format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_start_end_time_cstring
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end_time_cstring
(
   char_t *start_format_string,
   char_t *end_format_string,
   char_t *separator
)
{
   PRECONDITION( "start_format_string not null", start_format_string != NULL );
   PRECONDITION( "end_format_string not null", end_format_string != NULL );
   PRECONDITION( "separator not null", separator != NULL );

   string_t *s1 = NULL;
   string_t *s2 = NULL;

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t *result
      =  ( date_time_duration_formatter_parser_t * )
         calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make_cstring( start_format_string );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make_cstring( end_format_string );

   // separator
   (*result).separator = string_make_from_cstring( separator );
   s1 = date_time_formatter_parser_format_string( (*result).start_fp );
   s2 = date_time_formatter_parser_format_string( (*result).end_fp );
   (*result).separator_count
      =   string_substring_count_cstring( s1, separator )
          + 1
          + string_substring_count_cstring( s2, separator );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );

   // init duration_format_string
   (*result).duration_format_string = string_make_from_cstring( end_format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 1;

   // set end_is_time_only
   (*result).end_is_time_only = 1;

   // set is_fixed
   (*result).is_fixed = 1;

   // parse the duration format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_start_duration
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_duration
(
   string_t *start_format_string,
   string_t *duration_format_string,
   string_t *separator
)
{
   PRECONDITION( "start_format_string not null", start_format_string != NULL );
   PRECONDITION( "duration_format_string not null", duration_format_string != NULL );
   PRECONDITION( "separator not null", separator != NULL );

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t * result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make( start_format_string );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make( start_format_string );

   // separator
   (*result).separator = string_clone( separator );
   (*result).separator_count
      =  string_substring_count( start_format_string, separator )
         + 1
         + string_substring_count( duration_format_string, separator );

   // init duration_format_string
   (*result).duration_format_string = string_clone( duration_format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 0;

   // set end_is_time_only
   (*result).end_is_time_only = 0;

   // set is_fixed
   (*result).is_fixed = 1;

   // parse the duration format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_start_duration_cstring
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_duration_cstring
(
   char_t *start_format_string,
   char_t *duration_format_string,
   char_t *separator
)
{
   PRECONDITION( "start_format_string not null", start_format_string != NULL );
   PRECONDITION( "duration_format_string not null", duration_format_string != NULL );
   PRECONDITION( "separator not null", separator != NULL );

   string_t *s1 = NULL;
   string_t *s2 = NULL;

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t * result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make_cstring( start_format_string );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make_cstring( start_format_string );

   // separator
   (*result).separator = string_make_from_cstring( separator );
   s1 = date_time_formatter_parser_format_string( (*result).start_fp );
   s2 = string_make_from_cstring( duration_format_string );
   (*result).separator_count
      =   string_substring_count_cstring( s1, separator )
          + 1
          + string_substring_count_cstring( s2, separator );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );

   // init duration_format_string
   (*result).duration_format_string = string_make_from_cstring( duration_format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 0;

   // set end_is_time_only
   (*result).end_is_time_only = 0;

   // set is_fixed
   (*result).is_fixed = 1;

   // parse the duration format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_duration
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_duration
(
   string_t *duration_format_string
)
{
   PRECONDITION( "duration_format_string not null", duration_format_string != NULL );

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t * result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make_cstring( "" );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make_cstring( "" );

   // separator
   (*result).separator = string_make();
   (*result).separator_count = 0;

   // init duration_format_string
   (*result).duration_format_string = string_clone( duration_format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 0;

   // set end_is_time_only
   (*result).is_start_end = 0;

   // set is_fixed
   (*result).is_fixed = 0;

   // parse the duration format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_make_duration_cstring
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_duration_cstring
(
   char_t *duration_format_string
)
{
   PRECONDITION( "duration_format_string not null", duration_format_string != NULL );

   // allocate date_time_duration_formatter_parser struct
   date_time_duration_formatter_parser_t * result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // start formatter
   (*result).start_fp = date_time_formatter_parser_make_cstring( "" );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_make_cstring( "" );

   // separator
   (*result).separator = string_make();
   (*result).separator_count = 0;

   // init duration_format_string
   (*result).duration_format_string = string_make_from_cstring( duration_format_string );

   // init last_error
   (*result).last_error = string_make();

   // init output_template
   (*result).output_template = string_make();

   // init num_duration_format_fields
   (*result).num_duration_format_fields = 0;

   // init duration_format_fields
   (*result).duration_format_fields = NULL;

   // set default base century
   (*result).base_century = 2000;

   // set is_start_end
   (*result).is_start_end = 0;

   // set end_is_time_only
   (*result).is_start_end = 0;

   // set is_fixed
   (*result).is_fixed = 0;

   // parse the duration format string
   parse_format_string( result );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_clone
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_clone( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "date_time_duration_formatter_parser not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );

   date_time_duration_formatter_parser_t *result = NULL;
   format_field_t *ff = NULL;
   format_field_t *ff1 = NULL;
   format_field_t *last_ff = NULL;

   // allocate date_time_duration_formatter_parser struct
   result = ( date_time_duration_formatter_parser_t * ) calloc( 1, sizeof( date_time_duration_formatter_parser_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DATE_TIME_DURATION_FORMATTER_PARSER_TYPE;

   // lock mutex
   LOCK( (*current).mutex );

   // start formatter
   (*result).start_fp = date_time_formatter_parser_clone( (*current).start_fp );

   // end formatter
   (*result).end_fp = date_time_formatter_parser_clone( (*current).end_fp );

   // separator
   (*result).separator = string_deep_clone( (*current).separator );

   // duration_format_string
   (*result).duration_format_string = string_deep_clone( (*current).duration_format_string );

   // last_error
   (*result).last_error = string_deep_clone( (*current).last_error );

   // output_template
   (*result).output_template = string_deep_clone( (*current).output_template );

   // num_duration_format_fields
   (*result).num_duration_format_fields = (*current).num_duration_format_fields;

   // format_fields
   ff = (*current).duration_format_fields;
   while( ff != NULL )
   {
      ff1 = format_field_clone( ff );

      if ( last_ff == NULL )
      {
         (*result).duration_format_fields = ff1;
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

   // is_start_end
   (*result).is_start_end = (*current).is_start_end;

   // end_is_time_only
   (*result).end_is_time_only = (*current).end_is_time_only;

   // is_fixed
   (*result).is_fixed = (*current).is_fixed;

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( result );

   return result;
}

/**
   date_time_duration_formatter_parser_deep_clone
*/

date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_deep_clone( date_time_duration_formatter_parser_t *current )
{
   // deep clone is same as clone for this type
   return date_time_duration_formatter_parser_clone( current );
}

/**
  is_equal
*/

static
int32_t
is_equal( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other )
{
   int32_t result = 1;

   if ( date_time_formatter_parser_is_equal( (*current).start_fp, (*other).start_fp ) != 1  )
   {
      result = 0;
   }

   if ( date_time_formatter_parser_is_equal( (*current).end_fp, (*other).end_fp ) != 1  )
   {
      result = 0;
   }

   if ( string_is_deep_equal( (*current).separator, (*other).separator ) == 0 )
   {
      result = 0;
   }

   if ( string_is_deep_equal( (*current).duration_format_string, (*other).duration_format_string ) == 0 )
   {
      result = 0;
   }

   if ( (*current).base_century != (*other).base_century )
   {
      result = 0;
   }

   if ( (*current).is_start_end != (*other).is_start_end )
   {
      result = 0;
   }

   if ( (*current).end_is_time_only != (*other).end_is_time_only )
   {
      result = 0;
   }

   if ( (*current).is_fixed != (*other).is_fixed )
   {
      result = 0;
   }

   return result;
};

/**
   date_time_duration_formatter_parser_is_equal
*/

int32_t
date_time_duration_formatter_parser_is_equal( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
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
   date_time_duration_formatter_parser_is_deep_equal
*/

int32_t
date_time_duration_formatter_parser_is_deep_equal( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other )
{
   // is_deep_equal is same as is_equal for this type
   return date_time_duration_formatter_parser_is_equal( current, other );
}

/**
   date_time_duration_formatter_parser_copy
*/

void
date_time_duration_formatter_parser_copy( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   format_field_t *ff_current = NULL;
   format_field_t *ff1 = NULL;
   format_field_t *ff_other = NULL;
   format_field_t *last_ff = NULL;

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   // start_fp
   date_time_formatter_parser_dispose( &(*current).start_fp );
   (*current).start_fp = date_time_formatter_parser_clone( (*other).start_fp );

   // end_fp
   date_time_formatter_parser_dispose( &(*current).end_fp );
   (*current).end_fp = date_time_formatter_parser_clone( (*other).end_fp );

   // separator
   string_wipe_out( (*current).separator );
   string_append( (*current).separator, (*other).separator );

   // duration_format_string
   string_wipe_out( (*current).duration_format_string );
   string_append( (*current).duration_format_string, (*other).duration_format_string );

   // last_error
   string_wipe_out( (*current).last_error );
   string_append( (*current).last_error, (*other).last_error );

   // output_template
   string_wipe_out( (*current).output_template );
   string_append( (*current).output_template, (*other).output_template );

   // wipe out format fields
   ff_current = (*current).duration_format_fields;
   (*current).duration_format_fields = NULL;

   while ( ff_current != NULL )
   {
      ff1 = ( *ff_current ).next;
      format_field_dispose( &ff_current );
      ff_current = ff1;
   }

   // num_duration_format_fields
   (*current).num_duration_format_fields = (*other).num_duration_format_fields;
   (*current).duration_format_fields = NULL;

   // format_fields
   ff_other = (*other).duration_format_fields;
   while( ff_other != NULL )
   {
      ff1 = format_field_clone( ff_other );

      if ( (*current).duration_format_fields == NULL )
      {
         (*current).duration_format_fields = ff1;
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

   // is_start_end
   (*current).is_start_end = (*other).is_start_end;

   // is_fixed
   (*current).is_fixed = (*other).is_fixed;

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_deep_copy
*/

void
date_time_duration_formatter_parser_deep_copy( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other )
{
   // deep copy is same as copy for this type
   date_time_duration_formatter_parser_copy( current, other );
   return;
}

/**
   date_time_duration_formatter_parser_dispose
*/

void
date_time_duration_formatter_parser_dispose( date_time_duration_formatter_parser_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   format_field_t *ff_current = NULL;
   format_field_t *ff1 = NULL;

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   if ( (**current).start_fp != NULL )
   {
      date_time_formatter_parser_dispose( &(**current).start_fp );
   }

   if ( (**current).end_fp != NULL )
   {
      date_time_formatter_parser_dispose( &(**current).end_fp );
   }

   // free strings
   string_deep_dispose( &(**current).separator );
   string_deep_dispose( &(**current).duration_format_string );
   string_deep_dispose( &(**current).last_error );
   string_deep_dispose( &(**current).output_template );

   (**current).num_duration_format_fields = 0;

   // free format fields
   ff_current = (**current).duration_format_fields;
   (**current).duration_format_fields = NULL;

   while ( ff_current != NULL )
   {
      ff1 = ( *ff_current ).next;
      format_field_dispose( &ff_current );
      ff_current = ff1;
   }

   // delete date_time_duration_formatter_parser struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   date_time_duration_formatter_parser_deep_dispose
*/

void
date_time_duration_formatter_parser_deep_dispose( date_time_duration_formatter_parser_t **current )
{
   // deep_dispose is same as dispose for this type
   date_time_duration_formatter_parser_dispose( current );
   return;
}

/**
   date_time_duration_formatter_parser_is_start_end
*/

int32_t
date_time_duration_formatter_parser_is_start_end( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).is_start_end;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_is_time_duration
*/

int32_t
date_time_duration_formatter_parser_is_time_duration( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).end_is_time_only;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_is_fixed
*/

int32_t
date_time_duration_formatter_parser_is_fixed( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).is_fixed;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_last_error
*/

string_t *
date_time_duration_formatter_parser_last_error( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).last_error );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_base_century
*/

int32_t
date_time_duration_formatter_parser_base_century( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).base_century;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_start_format_string
*/

string_t *
date_time_duration_formatter_parser_start_format_string( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = date_time_formatter_parser_format_string( (*current).start_fp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_end_format_string
*/

string_t *
date_time_duration_formatter_parser_end_format_string( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = date_time_formatter_parser_format_string( (*current).end_fp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_duration_format_string
*/

string_t *
date_time_duration_formatter_parser_duration_format_string( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).duration_format_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_separator
*/

string_t *
date_time_duration_formatter_parser_separator( date_time_duration_formatter_parser_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).separator );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Helper functions
*/

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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= MAX_HOURS_IN_DAY ) )
   {
      result = 1;
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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= MAX_HOURS_IN_DAY ) )
   {
      result = 1;
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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= HOURS_IN_HALF_DAY ) )
   {
      result = 1;
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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= HOURS_IN_HALF_DAY ) )
   {
      result = 1;
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
   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= MAX_MINUTES_IN_HOUR ) )
   {
      result = 1;
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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= MAX_MINUTES_IN_HOUR ) )
   {
      result = 1;
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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= MAX_SECONDS_IN_MINUTE ) )
   {
      result = 1;
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

   i = string_as_int32( s );
   if ( ( i >= 0 ) && ( i <= MAX_SECONDS_IN_MINUTE ) )
   {
      result = 1;
   }

   return result;
}

/**
   string_code_millisecond_valid

   evaluate a string containing a millisecond against a format field for validity

   @param s the second as a string
   @param ff the format field
   @return 1 if valid, 0 otherwise
*/

static
int32_t
string_code_millisecond_valid( string_t *s, format_field_t *ff )
{
   int32_t result = 0;
   int64_t i = 0;

   i = string_as_int64( s );
   if ( ( i >= 0 ) && ( i <= 999 ) )
   {
      result = 1;
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

   if ( string_count( s ) != 3 )
   {
      result = 0;
   }
   else
   {

      c0 = string_item( s, 0 );
      c1 = string_item( s, 1 );
      c2 = string_item( s, 2 );

      if ( ( is_digit( c0 ) == 1 ) && ( is_digit( c1 ) == 1 ) && ( is_digit( c2 ) == 1 ) )
      {
         result = 1;
      }
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
   string_t *s1 = NULL;

   s1 = string_clone( s );
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
   duration corresponds

   check the validity of a date-time duration string

   @param current the date time formatter parser
   @param input the date-time string to check
   @return 1 if the input is valid, 0 otherwise
*/

static
int32_t
duration_corresponds( date_time_duration_formatter_parser_t *current, string_t *input )
{
   int32_t result = 1;
   format_field_t *ff = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   int32_t i = 0;
   int32_t i1 = 0;
   int32_t flag = 0;
   int32_t day_flag = 0;
   int32_t hour_flag = 0;
   int32_t minute_flag = 0;
   int32_t second_flag = 0;
   int32_t millisecond_flag = 0;

   // get index where duration begins
   i1 = 0;

   // get duration part of input string
   s2 = string_substring( input, i1, string_count( input ) - 1 );

   // loop through all format fields
   ff = (*current).duration_format_fields;

   while( ff != NULL )
   {
      // find first digit in next field
      flag = 0;
      while( flag == 0 )
      {
         if ( i >= string_count( s2 ) )
         {
            break;
         }

         if ( is_digit( string_item( s2, i ) ) == 0 )
         {
            i = i + 1;
         }
         else
         {
            flag = 1;
         }
      }

      // start of numeric field
      i1 = i;
      flag = 0;
      while( flag == 0 )
      {
         if ( i >= string_count( s2 ) )
         {
            break;
         }

         if ( is_digit( string_item( s2, i ) ) == 1 )
         {
            i = i + 1;
         }
         else
         {
            flag = 1;
         }
      }

      if ( i1 <= ( i - 1 ) )
      {
         // get numeric field
         s1 = string_substring( s2, i1, i - 1 );

         // test numeric field as a duration field
         if ( (*ff).code == CODE_DAY_N )
         {
            day_flag = 1;
         }
         else if ( (*ff).code == CODE_HOUR_N )
         {
            hour_flag = 1;
         }
         else if ( (*ff).code == CODE_HOUR )
         {
            result = string_code_hour_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               hour_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_HOUR_LZ )
         {
            result = string_code_hour_lz_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               hour_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_MINUTE_N )
         {
            minute_flag = 1;
         }
         else if ( (*ff).code == CODE_MINUTE )
         {
            result = string_code_minute_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               minute_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_MINUTE_LZ )
         {
            result = string_code_minute_lz_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               minute_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_SECOND_N )
         {
            second_flag = 1;
         }
         else if ( (*ff).code == CODE_SECOND )
         {
            result = string_code_second_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               second_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_SECOND_LZ )
         {
            result = string_code_second_lz_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               second_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_MILLISECOND_N )
         {
            millisecond_flag = 1;
         }
         else if ( (*ff).code == CODE_MILLISECOND )
         {
            result = string_code_millisecond_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               millisecond_flag = 1;
            }
         }
         else if ( (*ff).code == CODE_MILLISECOND_LZ )
         {
            result = string_code_millisecond_lz_valid( s1, ff );
            if ( result == 0 )
            {
               set_error_string( (*current).last_error, ff );
            }
            else
            {
               millisecond_flag = 1;
            }
         }

         string_deep_dispose( &s1 );
      }
      else
      {
         result = 0;
         string_wipe_out( (*current).last_error );
         string_append_cstring( (*current).last_error, "Not enough numeric fields at " );

      }

      ff = (*ff).next;
   }

   // loop through all format fields
   ff = (*current).duration_format_fields;

   while( ff != NULL )
   {
      if ( (*ff).code == CODE_DAY_N )
      {
         if ( day_flag == 0 )
         {
            result = 0;
         }
      }
      if ( ( (*ff).code == CODE_HOUR_N ) || ( (*ff).code == CODE_HOUR ) || ( (*ff).code == CODE_HOUR_LZ ) )
      {
         if ( hour_flag == 0 )
         {
            result = 0;
         }
      }
      if ( ( (*ff).code == CODE_MINUTE_N ) || ( (*ff).code == CODE_MINUTE ) || ( (*ff).code == CODE_MINUTE_LZ ) )
      {
         if ( minute_flag == 0 )
         {
            result = 0;
         }
      }
      if ( ( (*ff).code == CODE_SECOND_N ) || ( (*ff).code == CODE_SECOND ) || ( (*ff).code == CODE_SECOND_LZ ) )
      {
         if ( second_flag == 0 )
         {
            result = 0;
         }
      }
      if ( ( (*ff).code == CODE_MILLISECOND_N ) || ( (*ff).code == CODE_MILLISECOND_LZ ) )
      {
         if ( millisecond_flag == 0 )
         {
            result = 0;
         }
      }

      ff = (*ff).next;
   }

   string_deep_dispose( &s2 );

   return result;
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
corresponds( date_time_duration_formatter_parser_t *current, string_t *input )
{
   int32_t result = 0;
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   format_field_t *ff = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   int32_t i = 0;
   int32_t i1 = 0;
   int32_t flag = 0;
   int32_t hour_flag = 0;
   int32_t hour_12_flag = 0;
   int32_t meridiem_flag = 0;
   int32_t hour = 0;
   int32_t hour_12 = 0;
   int32_t minute = 0;
   int32_t second = 0;
   int32_t millisecond = 0;
   int32_t meridiem = 0;

   // start end
   if ( ( (*current).is_start_end == 1 ) && ( (*current).end_is_time_only == 0 ) )
   {
      i = string_substring_index( input, (*current).separator );
      s1 = string_substring( input, 0, i );
      s2 = string_substring( input, i + string_count( (*current).separator ), string_count( input ) - 1 );

      result = date_time_formatter_parser_corresponds( (*current).start_fp, s1 );

      if ( result == 1 )
      {
         result = date_time_formatter_parser_corresponds( (*current).end_fp, s2 );
      }

      if ( result == 1 )
      {
         start_dt = date_time_formatter_parser_parse( (*current).start_fp, s1 );
         end_dt = date_time_formatter_parser_parse( (*current).end_fp, s2 );

         if ( date_time_is_less_than( start_dt, end_dt ) == 0 )
         {
            result = 0;
         }

         date_time_dispose( &start_dt );
         date_time_dispose( &end_dt );
      }

      string_deep_dispose( &s1 );
      string_deep_dispose( &s2 );
   }

   // start end time only
   else if ( ( (*current).is_start_end == 1 ) && ( (*current).end_is_time_only == 1 ) )
   {
      flag = 0;
      i = -1;

      // see if have proper number of separators
      i = string_substring_count( input, (*current).separator );
      if ( i != (*current).separator_count )
      {
         // if not, doesn't correspond, skip to end
         result = 0;
         goto start_end_time_only_end;
      }

      // get last separator - between date and duration
      while ( flag == 0 )
      {
         if ( ( i + 1 ) >= string_count( input ) )
         {
            break;
         }

         i1 = string_substring_index_in_bounds( input, (*current).separator, i + 1, string_count( input ) - 1 );

         if ( i1 != -1 )
         {
            i = i1;
         }
         else
         {
            flag = 1;
            break;
         }
      }

      // last separator is at i

      s1 = string_substring( input, 0, i );
      if ( i + string_count( (*current).separator ) >= string_count( input ) )
      {
         result = 0;
         s2 = string_make();
      }
      else
      {
         s2 = string_substring( input, i + string_count( (*current).separator ), string_count( input ) - 1 );
      }

      result = date_time_formatter_parser_corresponds( (*current).start_fp, s1 );

      if ( result == 1 )
      {

         start_dt = date_time_formatter_parser_parse( (*current).start_fp, s1 );

         // get index where duration begins
         i1 = i + string_count( (*current).separator );

         // loop through all format fields
         ff = (*current).duration_format_fields;

         i = 0;
         while( ff != NULL )
         {
            // find first digit in next field
            flag = 0;
            if ( (*ff).code != CODE_MERIDIEM )
            {
               while( flag == 0 )
               {
                  if ( i >= string_count( s2 ) )
                  {
                     flag = 1;
                     break;
                  }

                  if ( is_digit( string_item( s2, i ) ) == 0 )
                  {
                     i = i + 1;
                  }
                  else
                  {
                     flag = 1;
                  }
               }

               // start of numeric field
               i1 = i;
               flag = 0;
               while( flag == 0 )
               {
                  if ( i >= string_count( s2 ) )
                  {
                     flag = 1;
                     break;
                  }

                  if ( is_digit( string_item( s2, i ) ) == 1 )
                  {
                     i = i + 1;
                  }
                  else
                  {
                     flag = 1;
                  }
               }

               // get numeric field
               if ( i1 <= ( i - 1 ) )
               {
                  s3 = string_substring( s2, i1, i - 1 );
               }
               else
               {
                  s3 = string_make();
               }
            }
            else
            {
               while( flag == 0 )
               {
                  if ( ( i + 1 ) >= string_count( s2 ) )
                  {
                     break;
                  }

                  if (
                     ( string_item( s2, i ) != 'A' )
                     &&
                     ( string_item( s2, i ) != 'a' )
                     &&
                     ( string_item( s2, i ) != 'P' )
                     &&
                     ( string_item( s2, i ) != 'p' )
                     &&
                     ( string_item( s2, i + 1 ) != 'M' )
                     &&
                     ( string_item( s2, i + 1 ) != 'm' )
                  )
                  {
                     i = i + 1;
                  }
                  else
                  {
                     flag = 1;
                  }
               }

               // get meridiem field
               if ( ( i + 1 ) < string_count( s2 ) )
               {
                  s3 = string_substring( s2, i, i + 1 );
               }
               else
               {
                  s3 = string_make();
               }

            }

            // test numeric field as a duration field
            if ( (*ff).code == CODE_HOUR )
            {
               flag = string_code_hour_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  hour = string_as_int32( s3 );
                  hour_flag = 1;
               }
            }
            else if ( (*ff).code == CODE_HOUR_LZ )
            {
               flag = string_code_hour_lz_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  hour = string_as_int32( s3 );
                  hour_flag = 1;
               }
            }
            else if ( (*ff).code == CODE_HOUR_12 )
            {
               flag = string_code_hour_12_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  hour_12 = string_as_int32( s3 );
                  hour_12_flag = 1;
               }
            }
            else if ( (*ff).code == CODE_HOUR_12_LZ )
            {
               flag = string_code_hour_12_lz_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  hour_12 = string_as_int32( s3 );
                  hour_12_flag = 1;
               }
            }
            else if ( (*ff).code == CODE_MINUTE )
            {
               flag = string_code_minute_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  minute = string_as_int32( s3 );
               }
            }
            else if ( (*ff).code == CODE_MINUTE_LZ )
            {
               flag = string_code_minute_lz_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  minute = string_as_int32( s3 );
               }
            }
            else if ( (*ff).code == CODE_SECOND )
            {
               flag = string_code_second_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  second = string_as_int32( s3 );
               }
            }
            else if ( (*ff).code == CODE_SECOND_LZ )
            {
               flag = string_code_second_lz_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  second = string_as_int32( s3 );
               }
            }
            else if ( (*ff).code == CODE_MILLISECOND_LZ )
            {
               flag = string_code_millisecond_lz_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  millisecond = string_as_int32( s3 );
               }
            }
            else if ( (*ff).code == CODE_MERIDIEM )
            {
               flag = string_code_meridiem_valid( s3, ff );
               if ( flag == 0 )
               {
                  result = 0;
                  set_error_string( (*current).last_error, ff );
               }
               else
               {
                  meridiem = 0;
                  string_to_lower( s3 );
                  if ( string_is_equal_cstring( s3, "pm" ) == 1 )
                  {
                     meridiem = 1;
                  }
                  meridiem_flag = 1;
               }
            }

            string_deep_dispose( &s3 );
            ff = (*ff).next;
         }

         if ( result == 1 )
         {

            if (
               ( ( hour_12_flag == 1 ) && ( meridiem_flag == 0 ) )
               ||
               ( ( hour_12_flag == 0 ) && ( meridiem_flag == 1 ) )
            )
            {
               result = 0;
            }

            if ( result == 1 )
            {
               if ( hour_flag == 1 )
               {
                  end_dt
                     =  date_time_make
                        (
                           date_time_year( start_dt ),
                           date_time_month( start_dt ),
                           date_time_day( start_dt ),
                           hour,
                           minute,
                           second,
                           millisecond
                        );
               }
               else if ( hour_12_flag == 1 )
               {
                  end_dt
                     =  date_time_make_hour_12
                        (
                           date_time_year( start_dt ),
                           date_time_month( start_dt ),
                           date_time_day( start_dt ),
                           hour_12,
                           minute,
                           second,
                           millisecond,
                           meridiem
                        );
               }

               if ( end_dt != NULL )
               {
                  if ( date_time_is_less_than( start_dt, end_dt ) == 0 )
                  {
                     result = 0;
                  }
               }
            }

         }
         date_time_dispose( &start_dt );
         if ( end_dt != NULL )
         {
            date_time_dispose( &end_dt );
         }
      }

      string_deep_dispose( &s1 );
      string_deep_dispose( &s2 );

start_end_time_only_end:
      result = result;
   }

   // start and duration
   else if ( ( (*current).is_start_end == 0 ) && ( (*current).is_fixed == 1 ) )
   {
      i = 0;
      flag = 0;
      while ( flag == 0 )
      {
         i = string_substring_index_in_bounds( input, (*current).separator, i, string_count( input ) - 1 );
         if ( i == -1 )
         {
            flag = 1;
            break;
         }
         else
         {
            i1 = i;
            i = i + 1;
         }
      }

      i = i1;
      s1 = string_substring( input, 0, i - 1 );
      result = date_time_formatter_parser_corresponds( (*current).end_fp, s1 );
      string_deep_dispose( &s1 );

      if ( result == 1 )
      {
         // get index where duration begins
         i1 = i + string_count( (*current).separator );

         // get duration part of input string
         s2 = string_substring( input, i1, string_count( input ) - 1 );

         // check duration part
         result = duration_corresponds( current, s2 );

         string_deep_dispose( &s2 );
      }
   }

   // duration only
   else if ( (*current).is_fixed == 0 )
   {
      // get index where duration begins
      i1 = 0;

      // get duration part of input string
      s2 = string_clone( input );

      // check duration part
      result = duration_corresponds( current, s2 );

      string_deep_dispose( &s2 );
   }

   return result;
}

/**
   duration parse

   parse a date-time duration string into a date-time class instance

   @param current the date time formatter parser
   @param input the date-time string to check
   @return a new date-time class instance
*/

static
int64_t
duration_parse( date_time_duration_formatter_parser_t *current, string_t *input )
{
   int64_t result = 0;
   format_field_t *ff = NULL;
   string_t *s1 = NULL;
   int32_t i = 0;
   int32_t i1 = 0;
   int32_t flag = 0;
   int64_t day = 0;
   int64_t hour = 0;
   int64_t minute = 0;
   int64_t second = 0;
   int64_t millisecond = 0;

   // loop through all format fields
   ff = (*current).duration_format_fields;

   while( ff != NULL )
   {
      // find first digit in next field
      flag = 0;
      while( flag == 0 )
      {
         if ( is_digit( string_item( input, i ) ) == 0 )
         {
            i = i + 1;
         }
         else
         {
            flag = 1;
         }
      }

      // start of numeric field
      i1 = i;
      flag = 0;
      while( flag == 0 )
      {
         if ( i >= string_count( input ) )
         {
            break;
         }

         if ( is_digit( string_item( input, i ) ) == 1 )
         {
            i = i + 1;
         }
         else
         {
            flag = 1;
         }
      }

      // get numeric field
      s1 = string_substring( input, i1, i - 1 );

      // test numeric field as a duration field
      if ( (*ff).code == CODE_DAY_N )
      {
         day = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_HOUR_N )
      {
         hour = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_HOUR )
      {
         hour = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_HOUR_LZ )
      {
         hour = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_MINUTE_N )
      {
         minute = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_MINUTE )
      {
         minute = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_MINUTE_LZ )
      {
         minute = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_SECOND_N )
      {
         second = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_SECOND )
      {
         second = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_SECOND_LZ )
      {
         second = string_as_int64( s1 );
      }
      else if ( (*ff).code == CODE_MILLISECOND_LZ )
      {
         millisecond = string_as_int64( s1 );
      }

      string_deep_dispose( &s1 );
      ff = (*ff).next;
   }

   // calculate result in milliseconds

   result
      =  millisecond
         + second * MILLISECONDS_IN_SECOND
         + minute * MILLISECONDS_IN_MINUTE
         + hour * MILLISECONDS_IN_HOUR
         + day * MILLISECONDS_IN_DAY;

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
date_time_duration_t *
parse( date_time_duration_formatter_parser_t *current, string_t *input )
{
   date_time_duration_t *result = NULL;
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   format_field_t *ff = NULL;
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   int32_t flag = 0;
   int32_t i = 0;
   int32_t i1 = 0;
   int32_t hour_flag = 0;
   int32_t hour_12_flag = 0;
   int32_t hour = 0;
   int32_t hour_12 = 0;
   int32_t minute = 0;
   int32_t second = 0;
   int32_t millisecond = 0;
   int32_t meridiem = 0;
   int64_t milliseconds = 0;

   ff = (*current).duration_format_fields;

   // start end
   if ( ( (*current).is_start_end == 1 ) && ( (*current).end_is_time_only == 0 ) )
   {
      i = string_substring_index( input, (*current).separator );
      s1 = string_substring( input, 0, i );
      s2 = string_substring( input, i + string_count( (*current).separator ), string_count( input ) - 1 );

      start_dt = date_time_formatter_parser_parse( (*current).start_fp, s1 );
      end_dt = date_time_formatter_parser_parse( (*current).end_fp, s2 );

      result = date_time_duration_make_start_end( start_dt, end_dt );

      date_time_dispose( &start_dt );
      date_time_dispose( &end_dt );

      string_deep_dispose( &s1 );
      string_deep_dispose( &s2 );
   }

   // start end time only
   else if ( ( (*current).is_start_end == 1 ) && ( (*current).end_is_time_only == 1 ) )
   {
      flag = 0;
      i = -1;
      while ( flag == 0 )
      {
         if ( ( i + 1 ) >= string_count( input ) )
         {
            break;
         }

         i1 = string_substring_index_in_bounds( input, (*current).separator, i + 1, string_count( input ) - 1 );

         if ( i1 != -1 )
         {
            i = i1;
         }
         else
         {
            break;
         }
      }

      s1 = string_substring( input, 0, i );
      if ( i + string_count( (*current).separator ) >= string_count( input ) )
      {
         result = 0;
         s2 = string_make();
      }
      else
      {
         s2 = string_substring( input, i + string_count( (*current).separator ), string_count( input ) - 1 );
      }

      start_dt = date_time_formatter_parser_parse( (*current).start_fp, s1 );

      // get index where duration begins
      i1 = i + string_count( (*current).separator );

      // loop through all format fields
      ff = (*current).duration_format_fields;

      i = 0;
      while( ff != NULL )
      {
         // find first digit in next field
         flag = 0;

         if ( (*ff).code != CODE_MERIDIEM )
         {
            while( flag == 0 )
            {
               if ( is_digit( string_item( s2, i ) ) == 0 )
               {
                  i = i + 1;
               }
               else
               {
                  flag = 1;
               }
            }

            // start of numeric field
            i1 = i;
            flag = 0;
            while( flag == 0 )
            {
               if ( i >= string_count( s2 ) )
               {
                  break;
               }

               if ( is_digit( string_item( s2, i ) ) == 1 )
               {
                  i = i + 1;
               }
               else
               {
                  flag = 1;
               }
            }

            // get numeric field
            s3 = string_substring( s2, i1, i - 1 );

         }
         else
         {
            while( flag == 0 )
            {
               if (
                  ( string_item( s2, i ) != 'A' )
                  &&
                  ( string_item( s2, i ) != 'a' )
                  &&
                  ( string_item( s2, i ) != 'P' )
                  &&
                  ( string_item( s2, i ) != 'p' )
                  &&
                  ( string_item( s2, i + 1 ) != 'M' )
                  &&
                  ( string_item( s2, i + 1 ) != 'm' )
               )
               {
                  i = i + 1;
               }
               else
               {
                  flag = 1;
               }
            }

            // get meridiem field
            s3 = string_substring( s2, i, i + 1 );

         }

         // test numeric field as a duration field
         if ( (*ff).code == CODE_HOUR )
         {
            hour = string_as_int32( s3 );
            hour_flag = 1;
         }
         else if ( (*ff).code == CODE_HOUR_LZ )
         {
            hour = string_as_int32( s3 );
            hour_flag = 1;
         }
         else if ( (*ff).code == CODE_HOUR_12 )
         {
            hour_12 = string_as_int32( s3 );
            hour_12_flag = 1;
         }
         else if ( (*ff).code == CODE_HOUR_12_LZ )
         {
            hour_12 = string_as_int32( s3 );
            hour_12_flag = 1;
         }
         else if ( (*ff).code == CODE_MINUTE )
         {
            minute = string_as_int32( s3 );
         }
         else if ( (*ff).code == CODE_MINUTE_LZ )
         {
            minute = string_as_int32( s3 );
         }
         else if ( (*ff).code == CODE_SECOND )
         {
            second = string_as_int32( s3 );
         }
         else if ( (*ff).code == CODE_SECOND_LZ )
         {
            second = string_as_int32( s3 );
         }
         else if ( (*ff).code == CODE_MILLISECOND_LZ )
         {
            millisecond = string_as_int32( s3 );
         }
         else if ( (*ff).code == CODE_MERIDIEM )
         {
            meridiem = 0;
            string_to_lower( s3 );
            if ( string_is_equal_cstring( s3, "pm" ) == 1 )
            {
               meridiem = 1;
            }
         }

         string_deep_dispose( &s3 );
         ff = (*ff).next;
      }

      if ( hour_flag == 1 )
      {
         end_dt
            =  date_time_make
               (
                  date_time_year( start_dt ),
                  date_time_month( start_dt ),
                  date_time_day( start_dt ),
                  hour,
                  minute,
                  second,
                  millisecond
               );
      }
      else if ( hour_12_flag == 1 )
      {
         end_dt
            =  date_time_make_hour_12
               (
                  date_time_year( start_dt ),
                  date_time_month( start_dt ),
                  date_time_day( start_dt ),
                  hour_12,
                  minute,
                  second,
                  millisecond,
                  meridiem
               );
      }

      if ( end_dt == NULL )
      {
         end_dt = date_time_clone( start_dt );
         result = date_time_duration_make_start_end( start_dt, end_dt );
      }
      else
      {
         result = date_time_duration_make_start_end( start_dt, end_dt );
      }

      date_time_dispose( &start_dt );
      date_time_dispose( &end_dt );

      string_deep_dispose( &s1 );
      string_deep_dispose( &s2 );
   }

   // start and duration
   else if ( ( (*current).is_start_end == 0 ) && ( (*current).is_fixed == 1 ) )
   {
      i = string_substring_index_in_bounds( input, (*current).separator, i, string_count( input ) - 1 );

      s1 = string_substring( input, 0, i );

      start_dt = date_time_formatter_parser_parse( (*current).start_fp, s1 );

      // get index where duration begins
      i1 = i + string_count( (*current).separator );

      // get duration part of input string
      s2 = string_substring( input, i1, string_count( input ) - 1 );

      // get duration part in milliseconds
      milliseconds = duration_parse( current, s2 );

      result = date_time_duration_make_start_milliseconds( start_dt, milliseconds );

      string_deep_dispose( &s1 );
      string_deep_dispose( &s2 );
      date_time_dispose( &start_dt );
   }

   // duration only
   else if ( (*current).is_fixed == 0 )
   {
      // get duration part in milliseconds
      milliseconds = duration_parse( current, input );

      result = date_time_duration_make_milliseconds( milliseconds );
   }

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
put_date_field_in_string( string_t *output, format_field_t *ff, int64_t value )
{
   char_t str[80] = {0};

   sprintf( str, (*ff).format_specifier, value );
   string_replace_all_cstring2( output, (*ff).tag, str );

   return;
}

/**
   duration format

   format a date-time duration class instance into a date-time string

   @param current the date time duration formatter parser
   @param dtd the data time duration class instance
   @param the formatted date-time duration string
*/

static
string_t *
duration_format( date_time_duration_formatter_parser_t *current, date_time_duration_t *dtd )
{
   string_t *result = NULL;
   format_field_t *ff = NULL;
   int32_t day_flag = 0;
   int32_t hour_flag = 0;
   int32_t minute_flag = 0;
   int32_t second_flag = 0;
   int32_t millisecond_flag = 0;
   int64_t day = 0;
   int64_t hour = 0;
   int64_t minute = 0;
   int64_t second = 0;
   int64_t millisecond = 0;
   int64_t milliseconds = 0;

   result = string_make();

   string_append( result, (*current).output_template );

   milliseconds = date_time_duration_duration_milliseconds( dtd );

   day = milliseconds / ( ( int64_t ) MILLISECONDS_IN_DAY );

   hour
      =  ( milliseconds - day * ( ( int64_t ) MILLISECONDS_IN_DAY ) )
         / ( ( int64_t ) MILLISECONDS_IN_HOUR );

   minute
      =  (
            milliseconds
            - day * ( ( int64_t ) MILLISECONDS_IN_DAY )
            - hour * ( ( int64_t ) MILLISECONDS_IN_HOUR )
         )
         / ( ( int64_t ) MILLISECONDS_IN_MINUTE );

   second
      =  (
            milliseconds
            - day * ( ( int64_t ) MILLISECONDS_IN_DAY )
            - hour * ( ( int64_t ) MILLISECONDS_IN_HOUR )
            - minute * ( ( int64_t ) MILLISECONDS_IN_MINUTE )
         )
         / ( ( int64_t ) MILLISECONDS_IN_SECOND );

   millisecond
      =  milliseconds
         - day * ( ( int64_t ) MILLISECONDS_IN_DAY )
         - hour * ( ( int64_t ) MILLISECONDS_IN_HOUR )
         - minute * ( ( int64_t ) MILLISECONDS_IN_MINUTE )
         - second * ( ( int64_t ) MILLISECONDS_IN_SECOND );

   // look for largest time unit in duration
   ff = (*current).duration_format_fields;
   while( ff != NULL )
   {
      if ( (*ff).code == CODE_DAY_N )
      {
         day_flag = 1;
      }
      else if ( (*ff).code == CODE_HOUR_N )
      {
         hour_flag = 1;
      }
      else if ( (*ff).code == CODE_MINUTE_N )
      {
         minute_flag = 1;
      }
      else if ( (*ff).code == CODE_SECOND_N )
      {
         second_flag = 1;
      }
      else if ( (*ff).code == CODE_MILLISECOND_N )
      {
         millisecond_flag = 1;
      }

      ff = (*ff).next;
   }

   // rearrange values of time units if necessary
   if ( day_flag == 1 )
   {
      // no change required
   }
   else if ( hour_flag == 1 )
   {
      // put days into hours
      hour = hour + day * ( ( int64_t ) HOURS_IN_DAY );
   }
   else if ( minute_flag == 1 )
   {
      // put days and hours into minutes
      minute
         =  minute
            + hour * ( ( int64_t ) MINUTES_IN_HOUR )
            + day * ( ( int64_t ) MINUTES_IN_DAY );
   }
   else if ( second_flag == 1 )
   {
      // put days, hours, minutes into seconds
      second
         =  second
            + minute * ( ( int64_t ) SECONDS_IN_MINUTE )
            + hour * ( ( int64_t ) SECONDS_IN_HOUR )
            + day * ( ( int64_t ) SECONDS_IN_DAY );
   }
   else if ( millisecond_flag == 1 )
   {
      // get duration in milliseconds
      millisecond = milliseconds;
   }

   // put duration values into output
   ff = (*current).duration_format_fields;
   while( ff != NULL )
   {
      if ( (*ff).code == CODE_DAY_N )
      {
         put_date_field_in_string( result, ff, day );
      }
      else if ( (*ff).code == CODE_HOUR_N )
      {
         put_date_field_in_string( result, ff, hour );
      }
      else if ( (*ff).code == CODE_HOUR )
      {
         put_date_field_in_string( result, ff, hour );
      }
      else if ( (*ff).code == CODE_MINUTE_N )
      {
         put_date_field_in_string( result, ff, minute );
      }
      else if ( (*ff).code == CODE_MINUTE )
      {
         put_date_field_in_string( result, ff, minute );
      }
      else if ( (*ff).code == CODE_SECOND_N )
      {
         put_date_field_in_string( result, ff, second );
      }
      else if ( (*ff).code == CODE_SECOND )
      {
         put_date_field_in_string( result, ff, second );
      }
      else if ( (*ff).code == CODE_MILLISECOND_N )
      {
         put_date_field_in_string( result, ff, millisecond );
      }
      else if ( (*ff).code == CODE_MILLISECOND_LZ )
      {
         put_date_field_in_string( result, ff, millisecond );
      }
      else if ( (*ff).code == CODE_MILLISECOND )
      {
         put_date_field_in_string( result, ff, millisecond );
      }
      ff = (*ff).next;
   }

   return result;
}

/**
   format

   format a date-time duration class instance into a date-time duration string

   @param current the date time duration formatter parser
   @param dtd the data time duration class instance
   @param the formatted date-time duration string
*/

static
string_t *
format( date_time_duration_formatter_parser_t *current, date_time_duration_t *dtd )
{
   string_t *result = NULL;
   format_field_t *ff = NULL;
   string_t *s = NULL;
   int64_t hour = 0;
   int64_t minute = 0;
   int64_t second = 0;
   int64_t millisecond = 0;
   int32_t meridiem = 0;
   date_time_t *dt;

   result = string_make();

   // start end
   if ( ( (*current).is_start_end == 1 ) && ( (*current).end_is_time_only == 0 ) )
   {
      dt = date_time_duration_start( dtd );
      s = date_time_formatter_parser_format( (*current).start_fp, dt );
      date_time_dispose( &dt );
      string_append( result, s );
      string_deep_dispose( &s );
      string_append( result, (*current).separator );
      dt = date_time_duration_end( dtd );
      s = date_time_formatter_parser_format( (*current).end_fp, dt );
      date_time_dispose( &dt );
      string_append( result, s );
      string_deep_dispose( &s );
   }

   // start end time only
   else if ( ( (*current).is_start_end == 1 ) && ( (*current).end_is_time_only == 1 ) )
   {
      dt = date_time_duration_start( dtd );
      s = date_time_formatter_parser_format( (*current).start_fp, dt );
      date_time_dispose( &dt );
      string_append( result, s );
      string_deep_dispose( &s );
      string_append( result, (*current).separator );
      string_append( result, (*current).output_template );

      dt = date_time_duration_end( dtd );
      hour = date_time_hour_24( dt );
      minute = date_time_minute( dt );
      second = date_time_second( dt );
      millisecond = date_time_millisecond( dt );
      meridiem = date_time_meridiem( dt );
      date_time_dispose( &dt );

      // test for and replace each format field
      ff = (*current).duration_format_fields;
      while ( ff != NULL )
      {
         if ( (*ff).code == CODE_HOUR )
         {
            put_date_field_in_string( result, ff, hour );
         }
         else if ( (*ff).code == CODE_HOUR_LZ )
         {
            put_date_field_in_string( result, ff, hour );
         }
         else if ( (*ff).code == CODE_HOUR_12 )
         {
            if ( hour > HOURS_IN_HALF_DAY )
            {
               hour = hour - HOURS_IN_HALF_DAY;
            }
            put_date_field_in_string( result, ff, hour );
         }
         else if ( (*ff).code == CODE_HOUR_12_LZ )
         {
            if ( hour > HOURS_IN_HALF_DAY )
            {
               hour = hour - HOURS_IN_HALF_DAY;
            }
            put_date_field_in_string( result, ff, hour );
         }
         else if ( (*ff).code == CODE_MINUTE )
         {
            put_date_field_in_string( result, ff, minute );
         }
         else if ( (*ff).code == CODE_MINUTE_LZ )
         {
            put_date_field_in_string( result, ff, minute );
         }
         else if ( (*ff).code == CODE_SECOND )
         {
            put_date_field_in_string( result, ff, second );
         }
         else if ( (*ff).code == CODE_SECOND_LZ )
         {
            put_date_field_in_string( result, ff, second );
         }
         else if ( (*ff).code == CODE_MILLISECOND )
         {
            put_date_field_in_string( result, ff, millisecond );
         }
         else if ( (*ff).code == CODE_MILLISECOND_LZ )
         {
            put_date_field_in_string( result, ff, millisecond );
         }
         else if ( (*ff).code == CODE_MERIDIEM )
         {
            string_replace_all_cstring2( result, (*ff).tag, int_to_meridiem_abbrev( meridiem ) );
         }
         ff = (*ff).next;
      }

   }

   // start and duration
   else if ( ( (*current).is_start_end == 0 ) && ( (*current).is_fixed == 1 ) )
   {
      dt = date_time_duration_start( dtd );
      s = date_time_formatter_parser_format( (*current).start_fp, dt );
      date_time_dispose( &dt );
      string_append( result, s );
      string_deep_dispose( &s );
      string_append( result, (*current).separator );

      s = duration_format( current, dtd );
      string_append( result, s );
      string_deep_dispose( &s );
   }

   // duration only
   else if ( (*current).is_fixed == 0 )
   {
      s = duration_format( current, dtd );
      string_append( result, s );
      string_deep_dispose( &s );
   }


   return result;
}

/**
   date_time_formatter_corresponds
*/

int32_t
date_time_duration_formatter_parser_corresponds( date_time_duration_formatter_parser_t *current, string_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = corresponds( current, input );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_corresponds_cstring
*/

int32_t
date_time_duration_formatter_parser_corresponds_cstring( date_time_duration_formatter_parser_t *current, char_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
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
   date_time_duration_formatter_parser_parse
*/

date_time_duration_t *
date_time_duration_formatter_parser_parse( date_time_duration_formatter_parser_t *current, string_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_duration_t *result = parse( current, input );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_duration_parse_cstring
*/

date_time_duration_t *
date_time_duration_formatter_parser_parse_cstring( date_time_duration_formatter_parser_t *current, char_t *input )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "input not null", input != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_duration_t *result = NULL;
   string_t *s = string_make_from_cstring( input );

   result = parse( current, s );

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_format
*/

string_t *
date_time_duration_formatter_parser_format( date_time_duration_formatter_parser_t *current, date_time_duration_t *dtd )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "dtd not null", dtd != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = format( current, dtd );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_format_cstring
*/

char_t *
date_time_duration_formatter_parser_format_cstring( date_time_duration_formatter_parser_t *current, date_time_duration_t *dtd )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "dtd not null", dtd != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = NULL;
   string_t *s = format( current, dtd );

   result = string_as_cstring( s );
   string_dispose_wrapper( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   date_time_duration_formatter_parser_put_start_format_string
*/

void
date_time_duration_formatter_parser_put_start_format_string
(
   date_time_duration_formatter_parser_t *current,
   string_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_formatter_parser_put_format_string( (*current).start_fp, format_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_start_format_string_cstring
*/

void
date_time_duration_formatter_parser_put_start_format_string_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *s = string_make_from_cstring( format_string );

   date_time_formatter_parser_put_format_string( (*current).start_fp, s );

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_end_format_string
*/

void
date_time_duration_formatter_parser_put_end_format_string
(
   date_time_duration_formatter_parser_t *current,
   string_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   date_time_formatter_parser_put_format_string( (*current).end_fp, format_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_end_format_string_cstring
*/

void
date_time_duration_formatter_parser_put_end_format_string_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *s = string_make_from_cstring( format_string );

   date_time_formatter_parser_put_format_string( (*current).end_fp, s );

   string_deep_dispose( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_duration_format_string
*/

void
date_time_duration_formatter_parser_put_duration_format_string
(
   date_time_duration_formatter_parser_t *current,
   string_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_wipe_out( (*current).duration_format_string );
   string_append( (*current).duration_format_string, format_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_duration_format_string_cstring
*/

void
date_time_duration_formatter_parser_put_duration_format_string_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *format_string
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "format_string not null", format_string != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_wipe_out( (*current).duration_format_string );
   string_append_cstring( (*current).duration_format_string, format_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_separator
*/

void
date_time_duration_formatter_parser_put_separator
(
   date_time_duration_formatter_parser_t *current,
   string_t *separator
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "separator not null", separator != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_wipe_out( (*current).separator );
   string_append( (*current).separator, separator );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_separator_cstring
*/

void
date_time_duration_formatter_parser_put_separator_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *separator
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "separator not null", separator != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_wipe_out( (*current).separator );
   string_append_cstring( (*current).separator, separator );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_is_time_duration
*/

void
date_time_duration_formatter_parser_put_is_time_duration
(
   date_time_duration_formatter_parser_t *current,
   int32_t is_time_duration
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set end_is_time_only flag
   (*current).end_is_time_only = is_time_duration;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   date_time_duration_formatter_parser_put_base_century
*/

void
date_time_duration_formatter_parser_put_base_century
(
   date_time_duration_formatter_parser_t *current,
   int32_t base_century
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == DATE_TIME_DURATION_FORMATTER_PARSER_TYPE );
   PRECONDITION( "base_century positive", base_century > 0 );
   PRECONDITION( "base_century ok", ( base_century % 100 ) == 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set base century
   (*current).base_century = base_century;

   date_time_formatter_parser_put_base_century( (*current).start_fp, base_century );
   date_time_formatter_parser_put_base_century( (*current).end_fp, base_century );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


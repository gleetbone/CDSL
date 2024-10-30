/**
 @file Date_Time_Duration_Formatter_Parser.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Specifies a time on a date"

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

 Function declarations for the opaque date_time_duration_formatter_parser_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATE_TIME_DURATION_FORMATTER_PARSER_T_H
#define DATE_TIME_DURATION_FORMATTER_PARSER_T_H


/**
   Version
*/

#define DATE_TIME_DURATION_FORMATTER_PARSER_VERSION_MAJOR 2
#define DATE_TIME_DURATION_FORMATTER_PARSER_VERSION_MINOR 0
#define DATE_TIME_DURATION_FORMATTER_PARSER_VERSION_PATCH 0

#define DATE_TIME_DURATION_FORMATTER_PARSER_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define DATE_TIME_DURATION_FORMATTER_PARSER_VERSION \
   DATE_TIME_DURATION_FORMATTER_PARSER_MAKE_VERSION( DATE_TIME_DURATION_FORMATTER_PARSER_VERSION_MAJOR, \
                       DATE_TIME_DURATION_FORMATTER_PARSER_VERSION_MINOR, \
                       DATE_TIME_DURATION_FORMATTER_PARSER_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"
#include "Date_Time_Duration.h"
#include "String.h"

/**
   Structure declaration
*/

struct date_time_duration_formatter_parser_struct;

/**
   Structure typedef
*/

typedef struct date_time_duration_formatter_parser_struct date_time_duration_formatter_parser_t;


/*
   Initialization
*/

/**
   date_time_duration_formatter_parser_make_start_end

   Create and initialize a date_time_duration_formatter_parser_t instance from
   format for start and end time with separator.

   @param start_format_string the format code string for the start date_time
   @param end_format_string the format code string for the end date_time
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end
(
   string_t *start_format_string,
   string_t *end_format_string,
   string_t *separator
);

/**
   date_time_duration_formatter_parser_make_start_end_cstring

   Create and initialize a date_time_duration_formatter_parser_t instance from input parameters.

   @param start_format_string the format code string for the start date_time
   @param end_format_string the format code string for the end date_time
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end_cstring
(
   char_t *format_string,
   char_t *end_format_string,
   char_t *separator
);

/**
   date_time_duration_formatter_parser_make_start_end_time

   Create and initialize a date_time_duration_formatter_parser_t instance from
   input parameters. End date takes year, month, and day from start; only
   the time of day is different.

   @param start_format_string the format code string for the start date_time
   @param end_format_string the format code string for the end time
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end_time
(
   string_t *start_format_string,
   string_t *end_format_string,
   string_t *separator
);

/**
   date_time_duration_formatter_parser_make_start_end_time_cstring

   Create and initialize a date_time_duration_formatter_parser_t instance from
   input parameters. End date takes year, month, and day from start; only
   the time of day is different.

   @param start_format_string the format code string for the start date_time
   @param end_format_string the format code string for the end time
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_end_time_cstring
(
   char_t *format_string,
   char_t *end_format_string,
   char_t *separator
);

/**
   date_time_duration_formatter_parser_make_start_duration

   Create and initialize a date_time_duration_formatter_parser_t instance from input parameters.

   @param start_format_string the format code string for the start date_time and duration
   @param duration_format_string the format code string for the duration
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_duration
(
   string_t *start_format_string,
   string_t *duration_format_string,
   string_t *separator
);

/**
   date_time_duration_formatter_parser_make_start_duration_cstring

   Create and initialize a date_time_duration_formatter_parser_t instance from input parameters.

   @param start_format_string the format code string for the start date_time and duration
   @param duration_format_string the format code string for the duration
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_start_duration_cstring
(
   char_t *start_format_string,
   char_t *duration_format_string,
   char_t *separator
);

/**
   date_time_duration_formatter_parser_make_duration

   Create and initialize a date_time_duration_formatter_parser_t instance from input parameters.

   @param duration_format_string the format code string for the duration
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_duration
(
   string_t *duration_format_string
);

/**
   date_time_duration_formatter_parser_make_duration_cstring

   Create and initialize a date_time_duration_formatter_parser_t instance from input parameters.

   @param duration_format_string the format code string for the duration
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_make_duration_cstring
(
   char_t *duration_format_string
);

/*
   Basic
*/

/**
   date_time_duration_formatter_parser_clone

   Create and initialize a clone of a date_time_duration_formatter_parser_t instance.

   @param current the date_time_duration_formatter_parser_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_clone( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_deep_clone

   Create and initialize a deep clone of a date_time_duration_formatter_parser_t instance.

   @param current the date_time_duration_formatter_parser_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_duration_formatter_parser_t *
date_time_duration_formatter_parser_deep_clone( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_is_equal

   Returns 1 if the current contains the same values as other

   @param current the first date_time_duration_formatter_parser_t instance
   @param other the first date_time_duration_formatter_parser_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_duration_formatter_parser_is_equal( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other );

/**
   date_time_duration_formatter_parser_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the first date_time_duration_formatter_parser_t instance
   @param other the first date_time_duration_formatter_parser_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_duration_formatter_parser_is_deep_equal( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other );

/**
   date_time_duration_formatter_parser_copy

   Puts contents of other into current

   @param current the date_time_duration_formatter_parser_t instance to copy into
   @param other the date_time_duration_formatter_parser_t to copy from
*/
void date_time_duration_formatter_parser_copy( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other );

/**
   date_time_duration_formatter_parser_deep_copy

   Puts contents of other into current

   @param current the date_time_duration_formatter_parser_t instance to copy into
   @param other the date_time_duration_formatter_parser_t to copy from
*/
void date_time_duration_formatter_parser_deep_copy( date_time_duration_formatter_parser_t *current, date_time_duration_formatter_parser_t *other );


/*
   Disposal
*/

/**
   date_time_duration_formatter_parser_dispose

   Deallocates a date_time_duration_formatter_parser_t instance.

   @param current pointer to the date_time_duration_formatter_parser instance to dispose
*/
void
date_time_duration_formatter_parser_dispose( date_time_duration_formatter_parser_t **current );

/**
   date_time_duration_formatter_parser_deep_dispose

   Deallocates a date_time_duration_formatter_parser_t instance.

   @param current pointer to the date_time_duration_formatter_parser instance to dispose
*/
void
date_time_duration_formatter_parser_deep_dispose( date_time_duration_formatter_parser_t **current );


/*
   Access
*/


/**
   date_time_duration_formatter_parser_start_format_string

   Returns the start time format string of the instance.

   @param current the date_time_duration_formatter_parser_t instance
   @return copy of the start format string
*/
string_t *
date_time_duration_formatter_parser_start_format_string( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_end_format_string

   Returns the end time format string of the instance.

   @param current the date_time_duration_formatter_parser_t instance
   @return copy of the end format string
*/
string_t *
date_time_duration_formatter_parser_end_format_string( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_duration_format_string

   Returns the duration format string of the instance.

   @param current the date_time_duration_formatter_parser_t instance
   @return copy of the end format string
*/
string_t *
date_time_duration_formatter_parser_duration_format_string( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_separator

   Returns the separator string of the instance.

   @param current the date_time_duration_formatter_parser_t instance
   @return copy of the separator string
*/
string_t *
date_time_duration_formatter_parser_separator( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_is_start_end

   Returns whether the instance format has a start and end time.

   @param current the date_time_duration_formatter_parser_t instance
   @return 1 = has start and end, 0 = is start and duration or duration only
*/
int32_t
date_time_duration_formatter_parser_is_start_end( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_is_time_duration

   Returns whether the instance has a time duration.

   @param current the date_time_duration_formatter_parser_t instance
   @return 1 = is time duration, 0 = not
*/
int32_t
date_time_duration_formatter_parser_is_time_duration( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_is_fixed

   Returns whether the instance has a specified start time.

   @param current the date_time_duration_formatter_parser_t instance
   @return 1 = is definite, 0 = not
*/
int32_t
date_time_duration_formatter_parser_is_fixed( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_last_error

   Returns the last error string of the instance to explain why an input
   string did not correspond to the format string.

   @param current the date_time_duration_formatter_parser_t instance
   @return copy of the last error string
*/
string_t *
date_time_duration_formatter_parser_last_error( date_time_duration_formatter_parser_t *current );

/**
   date_time_duration_formatter_parser_base_century

   Returns the last error string of the instance to explain why an input
   string did not correspond to the format string.

   @param current the date_time_duration_formatter_parser_t instance
   @return the base century
*/
int32_t
date_time_duration_formatter_parser_base_century( date_time_duration_formatter_parser_t *current );

/*
   Measurement
*/

/**
   date_time_duration_formatter_parser_corresponds

   Returns 1 if input string is valid according to format string. If result is
   0, date_time_duration_formatter_parser_last_error contains error message with details.

   @param current the first date_time_duration_formatter_parser_t instance
   @param input the input string to check
   @return 1 if input is valid
*/
int32_t
date_time_duration_formatter_parser_corresponds
(
   date_time_duration_formatter_parser_t *current,
   string_t *input
);

/**
   date_time_duration_formatter_parser_corresponds_cstring

   Returns 1 if input string is valid according to format string. If result is
   0, date_time_duration_formatter_parser_last_error contains error message with details.


   @param current the first date_time_duration_formatter_parser_t instance
   @param input the input string to check
   @return 1 if input is valid
*/
int32_t
date_time_duration_formatter_parser_corresponds_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *input
);

/*
   Status Report
*/

/*
   Comparison
*/

/*
   Conversion
*/

/**
   date_time_duration_formatter_parser_parse

   Returns date_time from input string

   @param current the first date_time_duration_formatter_parser_t instance
   @param input the input string to check
   @return the date_time_duration parsed from the input string
*/
date_time_duration_t *
date_time_duration_formatter_parser_parse
(
   date_time_duration_formatter_parser_t *current,
   string_t *input
);

/**
   date_time_duration_formatter_parser_parse_cstring

   Returns date_time from input string

   @param current the first date_time_duration_formatter_parser_t instance
   @param input the input string to check
   @return the date_time_duration parsed from the input string
*/
date_time_duration_t *
date_time_duration_formatter_parser_parse_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *input
);

/**
   date_time_duration_formatter_parser_format

   Returns date_time_duration as string according to the format string.

   @param current the first date_time_duration_formatter_parser_t instance
   @param dt the input date_time_duration
   @return the date_time formatted as a string
*/
string_t *
date_time_duration_formatter_parser_format
(
   date_time_duration_formatter_parser_t *current,
   date_time_duration_t *dtd
);

/**
   date_time_duration_formatter_parser_format_cstring

   Returns date_time_duration as string according to the format string.

   @param current the first date_time_duration_formatter_parser_t instance
   @param dt the input date_time_duration
   @return the date_time formatted as a string
*/
char_t *
date_time_duration_formatter_parser_format_cstring
(
   date_time_duration_formatter_parser_t *current,
   date_time_duration_t *dtd
);

/*
   Element Change
*/

/**
   date_time_duration_formatter_parser_put_start_format_string

   Sets start time format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_duration_formatter_parser_put_start_format_string
(
   date_time_duration_formatter_parser_t *current,
   string_t *format_string
);

/**
   date_time_duration_formatter_parser_put_start_format_string_cstring

   Sets start time format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_duration_formatter_parser_put_start_format_string_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *format_string
);

/**
   date_time_duration_formatter_parser_put_end_format_string

   Sets end time format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_duration_formatter_parser_put_end_format_string
(
   date_time_duration_formatter_parser_t *current,
   string_t *format_string
);

/**
   date_time_duration_formatter_parser_put_end_format_string_cstring

   Sets end time format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_duration_formatter_parser_put_end_format_string_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *format_string
);

/**
   date_time_duration_formatter_parser_put_duration_format_string

   Sets duration time format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_duration_formatter_parser_put_duration_format_string
(
   date_time_duration_formatter_parser_t *current,
   string_t *format_string
);

/**
   date_time_duration_formatter_parser_put_duration_format_string_cstring

   Sets duration time format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_duration_formatter_parser_put_duration_format_string_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *format_string
);

/**
   date_time_duration_formatter_parser_put_separator

   Sets separator string.

   @param pointer to the data structure
   @param format_string the new separator string
*/
void
date_time_duration_formatter_parser_put_separator
(
   date_time_duration_formatter_parser_t *current,
   string_t *separator
);

/**
   date_time_duration_formatter_parser_put_separator_cstring

   Sets separator string.

   @param pointer to the data structure
   @param format_string the new separator string
*/
void
date_time_duration_formatter_parser_put_separator_cstring
(
   date_time_duration_formatter_parser_t *current,
   char_t *separator
);

/**
   date_time_duration_formatter_parser_put_is_time_duration

   Sets whether duration is less than 24 hours.

   @param pointer to the data structure
   @param new value for is_time_duration
*/
void
date_time_duration_formatter_parser_put_is_time_duration
(
   date_time_duration_formatter_parser_t *current,
   int32_t is_time_duration
);

/**
   date_time_duration_formatter_parser_put_base_century

   Sets base century

   @param pointer to the data structure
   @param base_century the new base century (default is 2000)
*/
void
date_time_duration_formatter_parser_put_base_century
(
   date_time_duration_formatter_parser_t *current,
   int32_t base_century
);

/*
   Duplication
*/

/*
   Removal
*/

/*
   Resize
*/


#ifdef __cplusplus
}
#endif

#endif /* DATE_TIME_DURATION_FORMATTER_PARSER_T_H */

/* End of file */





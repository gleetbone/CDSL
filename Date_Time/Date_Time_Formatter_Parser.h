/**
 @file Date_Time_Formatter_Parser.h
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

 Function declarations for the opaque date_time_formatter_parser_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATE_TIME_FORMATTER_PARSER_T_H
#define DATE_TIME_FORMATTER_PARSER_T_H


/**
   Version
*/

#define DATE_TIME_FORMATTER_PARSER_VERSION_MAJOR 2
#define DATE_TIME_FORMATTER_PARSER_VERSION_MINOR 0
#define DATE_TIME_FORMATTER_PARSER_VERSION_PATCH 0

#define DATE_TIME_FORMATTER_PARSER_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define DATE_TIME_FORMATTER_PARSER_VERSION \
   DATE_TIME_FORMATTER_PARSER_MAKE_VERSION( DATE_TIME_FORMATTER_PARSER_VERSION_MAJOR, \
                       DATE_TIME_FORMATTER_PARSER_VERSION_MINOR, \
                       DATE_TIME_FORMATTER_PARSER_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"
#include "Date_Time.h"
#include "String.h"

/**
   Structure declaration
*/

struct date_time_formatter_parser_struct;

/**
   Structure typedef
*/

typedef struct date_time_formatter_parser_struct date_time_formatter_parser_t;


/*
   Initialization
*/

/**
   date_time_formatter_parser_make

   Create and initialize a date_time_formatter_parser_t instance from input parameters.

   @param format_string the format code string
   @return pointer to the new data structure
*/
date_time_formatter_parser_t *
date_time_formatter_parser_make
(
   string_t *format_string
);

/**
   date_time_formatter_parser_make_cstring

   Create and initialize a date_time_formatter_parser_t instance from input parameters.

   @param format_string the format code string
   @return pointer to the new data structure
*/
date_time_formatter_parser_t *
date_time_formatter_parser_make_cstring
(
   char_t *format_string
);

/*
   Basic
*/

/**
   date_time_formatter_parser_clone

   Create and initialize a clone of a date_time_formatter_parser_t instance.

   @param current the date_time_formatter_parser_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_formatter_parser_t *
date_time_formatter_parser_clone( date_time_formatter_parser_t *current );

/**
   date_time_formatter_parser_deep_clone

   Create and initialize a deep clone of a date_time_formatter_parser_t instance.

   @param current the date_time_formatter_parser_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_formatter_parser_t *
date_time_formatter_parser_deep_clone( date_time_formatter_parser_t *current );

/**
   date_time_formatter_parser_is_equal

   Returns 1 if the current contains the same values as other

   @param current the first date_time_formatter_parser_t instance
   @param other the first date_time_formatter_parser_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_formatter_parser_is_equal( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other );

/**
   date_time_formatter_parser_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the first date_time_formatter_parser_t instance
   @param other the first date_time_formatter_parser_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_formatter_parser_is_deep_equal( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other );

/**
   date_time_formatter_parser_copy

   Puts contents of other into current

   @param current the date_time_formatter_parser_t instance to copy into
   @param other the date_time_formatter_parser_t to copy from
*/
void date_time_formatter_parser_copy( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other );

/**
   date_time_formatter_parser_deep_copy

   Puts contents of other into current

   @param current the date_time_formatter_parser_t instance to copy into
   @param other the date_time_formatter_parser_t to copy from
*/
void date_time_formatter_parser_deep_copy( date_time_formatter_parser_t *current, date_time_formatter_parser_t *other );


/*
   Disposal
*/

/**
   date_time_formatter_parser_dispose

   Deallocates a date_time_formatter_parser_t instance.

   @param current pointer to the date_time_formatter_parser instance to dispose
*/
void
date_time_formatter_parser_dispose( date_time_formatter_parser_t **current );

/**
   date_time_formatter_parser_deep_dispose

   Deallocates a date_time_formatter_parser_t instance.

   @param current pointer to the date_time_formatter_parser instance to dispose
*/
void
date_time_formatter_parser_deep_dispose( date_time_formatter_parser_t **current );


/*
   Access
*/


/**
   date_time_formatter_parser_format_string

   Returns the format string of the instance.

   @param current the date_time_formatter_parser_t instance
   @return copy of the format string
*/
string_t *
date_time_formatter_parser_format_string( date_time_formatter_parser_t *current );

/**
   date_time_formatter_parser_last_error

   Returns the last error string of the instance to explain why an input
   string did not correspond to the format string.

   @param current the date_time_formatter_parser_t instance
   @return copy of the last error string
*/
string_t *
date_time_formatter_parser_last_error( date_time_formatter_parser_t *current );

/**
   date_time_formatter_parser_base_century

   Returns the last error string of the instance to explain why an input
   string did not correspond to the format string.

   @param current the date_time_formatter_parser_t instance
   @return the base century
*/
int32_t
date_time_formatter_parser_base_century( date_time_formatter_parser_t *current );

/*
   Measurement
*/

/**
   date_time_formatter_parser_corresponds

   Returns 1 if input string is valid according to format string. If result is
   0, date_time_formatter_parser_last_error contains error message with details.

   @param current the first date_time_formatter_parser_t instance
   @param input the input string to check
   @return 1 if input is valid
*/
int32_t
date_time_formatter_parser_corresponds
(
   date_time_formatter_parser_t *current,
   string_t *input
);

/**
   date_time_formatter_parser_corresponds_cstring

   Returns 1 if input string is valid according to format string. If result is
   0, date_time_formatter_parser_last_error contains error message with details.


   @param current the first date_time_formatter_parser_t instance
   @param input the input string to check
   @return 1 if input is valid
*/
int32_t
date_time_formatter_parser_corresponds_cstring
(
   date_time_formatter_parser_t *current,
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
   date_time_formatter_parser_parse

   Returns date_time from input string

   @param current the first date_time_formatter_parser_t instance
   @param input the input string to check
   @return the date_time parsed from the input string
*/
date_time_t *
date_time_formatter_parser_parse
(
   date_time_formatter_parser_t *current,
   string_t *input
);

/**
   date_time_formatter_parser_parse_cstring

   Returns date_time from input string

   @param current the first date_time_formatter_parser_t instance
   @param input the input string to check
   @return the date_time parsed from the input string
*/
date_time_t *
date_time_formatter_parser_parse_cstring
(
   date_time_formatter_parser_t *current,
   char_t *input
);

/**
   date_time_formatter_parser_format

   Returns date_time as string according to the format string.

   @param current the first date_time_formatter_parser_t instance
   @param dt the input date_time
   @return the date_time formatted as a string
*/
string_t *
date_time_formatter_parser_format
(
   date_time_formatter_parser_t *current,
   date_time_t *dt
);

/**
   date_time_formatter_parser_format_cstring

   Returns date_time as string according to the format string.

   @param current the first date_time_formatter_parser_t instance
   @param dt the input date_time
   @return the date_time formatted as a string
*/
char_t *
date_time_formatter_parser_format_cstring
(
   date_time_formatter_parser_t *current,
   date_time_t *dt
);

/*
   Element Change
*/

/**
   date_time_formatter_parser_put_format_string

   Sets format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_formatter_parser_put_format_string
(
   date_time_formatter_parser_t *current,
   string_t *format_string
);

/**
   date_time_formatter_parser_put_format_string_cstring

   Sets format string.

   @param pointer to the data structure
   @param format_string the new format string
*/
void
date_time_formatter_parser_put_format_string_cstring
(
   date_time_formatter_parser_t *current,
   char_t *format_string
);

/**
   date_time_formatter_parser_put_base_century

   Sets base century

   @param pointer to the data structure
   @param base_century the new base century (default is 2000)
*/
void
date_time_formatter_parser_put_base_century
(
   date_time_formatter_parser_t *current,
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

#endif /* DATE_TIME_FORMATTER_PARSER_T_H */

/* End of file */





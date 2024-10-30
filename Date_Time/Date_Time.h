/**
 @file Date_Time.h
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

 Function declarations for the opaque date_time_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATE_TIME_T_H
#define DATE_TIME_T_H


/**
   Version
*/

#define DATE_TIME_VERSION_MAJOR 2
#define DATE_TIME_VERSION_MINOR 0
#define DATE_TIME_VERSION_PATCH 0

#define DATE_TIME_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define DATE_TIME_VERSION \
   DATE_TIME_MAKE_VERSION( DATE_TIME_VERSION_MAJOR, \
                       DATE_TIME_VERSION_MINOR, \
                       DATE_TIME_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"

/**
   Structure declaration
*/

struct date_time_struct;

/**
   Structure typedef
*/

typedef struct date_time_struct date_time_t;


/*
   Initialization
*/

/**
   date_time_make

   Create and initialize a date_time_t instance from input parameters.

   @param year the year AD of the date
   @param month the month 1-12 of the date
   @param day the day of the month 1-31 of the date
   @param hour_24 the hour 0-23 of the date in 24 hour format
   @param minute the minute 0-59 of the date
   @param second the second 0-59 of the date
   @param millisecond the millisecond 0-999 of the date
   @return pointer to the new data structure
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
);

/**
   date_time_make_day_of_year

   Create and initialize a date_time_t instance from input parameters.

   @param year the year AD of the date
   @param day_of_year the day of the year 1-365(6)
   @param hour_24 the hour 0-23 of the date in 24 hour format
   @param minute the minute 0-59 of the date
   @param second the second 0-59 of the date
   @param millisecond the millisecond 0-999 of the date
   @return pointer to the new data structure
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
);

/**
   date_time_make_hour_12

   Create and initialize a date_time_t instance from input parameters.

   @param year the year AD of the date
   @param month the month 1-12 of the date
   @param day the day of the month 1-31 of the date
   @param hour_12 the hour 0-11 of the date in 24 hour format
   @param minute the minute 0-59 of the date
   @param second the second 0-59 of the date
   @param millisecond the millisecond 0-999 of the date
   @param meridiem AM = 0, PM = 1
   @return pointer to the new data structure
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
);

/**
   date_time_make_now

   Create and initialize a date_time_t instance from curreny time.

   @return pointer to the new data structure
*/
date_time_t *
date_time_make_now();

/*
   Basic
*/

/**
   date_time_clone

   Create and initialize a clone of a date_time_t instance.

   @param current the date_time_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_t *
date_time_clone( date_time_t *current );

/**
   date_time_deep_clone

   Create and initialize a deep clone of a date_time_t instance.

   @param current the date_time_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_t *
date_time_deep_clone( date_time_t *current );

/**
   date_time_is_equal

   Returns 1 if the current contains the same values as other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_is_equal( date_time_t *current, date_time_t *other );

/**
   date_time_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_is_deep_equal( date_time_t *current, date_time_t *other );

/**
   date_time_copy

   Puts contents of other into current

   @param current the date_time_t instance to copy into
   @param other the date_time_t to copy from
*/
void date_time_copy( date_time_t *current, date_time_t *other );

/**
   date_time_deep_copy

   Puts contents of other into current

   @param current the date_time_t instance to copy into
   @param other the date_time_t to copy from
*/
void date_time_deep_copy( date_time_t *current, date_time_t *other );


/*
   Disposal
*/

/**
   date_time_dispose

   Deallocates a date_time_t instance.

   @param current pointer to the date_time instance to dispose
*/
void
date_time_dispose( date_time_t **current );

/**
   date_time_deep_dispose

   Deallocates a date_time_t instance.

   @param current pointer to the date_time instance to dispose
*/
void
date_time_deep_dispose( date_time_t **current );


/*
   Access
*/


/**
   date_time_year

   Returns the year AD of the instance.

   @param current pointer to the date_time instance
   @return the year AD
*/
int32_t
date_time_year( date_time_t *current );

/**
   date_time_month

   Returns the month of the instance.

   @param current pointer to the date_time instance
   @return the month 1-12
*/
int32_t
date_time_month( date_time_t *current );

/**
   date_time_day

   Returns the day of month of the instance.

   @param current pointer to the date_time instance
   @return the day of month 1-31
*/
int32_t
date_time_day( date_time_t *current );

/**
   date_time_day_of_year

   Returns the day of the year of the instance. February 1 is day_of_year 32.

   @param current pointer to the date_time instance
   @return the day of the year 1-365(6)
*/
int32_t
date_time_day_of_year( date_time_t *current );

/**
   date_time_day_of_week

   Returns the day of the week of the instance. Sunday is 1, Monday is 2, etc.

   @param current pointer to the date_time instance
   @return the day of the week 1-7
*/
int32_t
date_time_day_of_week( date_time_t *current );

/**
   date_time_hour_24

   Returns the hour of the instance.

   @param current pointer to the date_time instance
   @return the month 0-23
*/
int32_t
date_time_hour_24( date_time_t *current );

/**
   date_time_hour_12

   Returns the hour of the instance.

   @param current pointer to the date_time instance
   @return the month 0-11
*/
int32_t
date_time_hour_12( date_time_t *current );

/**
   date_time_minute

   Returns the minute of the instance.

   @param current pointer to the date_time instance
   @return the minute 0-59
*/
int32_t
date_time_minute( date_time_t *current );

/**
   date_time_second

   Returns the second of the instance.

   @param current pointer to the date_time instance
   @return the second 0-59
*/
int32_t
date_time_second( date_time_t *current );

/**
   date_time_millisecond

   Returns the millisecond of the instance.

   @param current pointer to the date_time instance
   @return the millisecond 0-999
*/
int32_t
date_time_millisecond( date_time_t *current );

/**
   date_time_meridiem

   Returns the meridiem of the instance AM (0) or PM (1). Noon is PM.

   @param current pointer to the date_time instance
   @return the meridiem  AM = 0, POM = 1
*/
int32_t
date_time_meridiem( date_time_t *current );

/*
   Measurement
*/

/**
   date_time_difference

   Returns the delta time difference between other and current in milliseconds.

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return the other - current in milliseconds
*/
int64_t
date_time_difference( date_time_t *current, date_time_t *other );

/*
   Status Report
*/

/*
   Comparison
*/

/**
   date_time_is_less_than

   Returns 1 if current is less than other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return 1 if current is less than other, 0 otherwise
*/
int32_t date_time_is_less_than( date_time_t *current, date_time_t *other );

/**
   date_time_is_less_than_or_equal

   Returns 1 if current is less than or equal to other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return 1 if current is less than or equal to other, 0 otherwise
*/
int32_t date_time_is_less_than_or_equal( date_time_t *current, date_time_t *other );

/**
   date_time_is_greater_than

   Returns 1 if current is greater than other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return 1 if current is greater than other, 0 otherwise
*/
int32_t date_time_is_greater_than( date_time_t *current, date_time_t *other );

/**
   date_time_is_greater_than_or_equal

   Returns 1 if current is greater than other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return 1 if current is greater than or equal to other, 0 otherwise
*/
int32_t date_time_is_greater_than_or_equal( date_time_t *current, date_time_t *other );

/**
   date_time_compare

   Returns negative if current is less than other, 0 if current equal to other, positive if
   current greater than other

   @param current the date_time_t instance
   @param other the other date_time_t instance
   @return negative if current < other, 0 if current == other, positive if current > other
*/
int32_t date_time_compare( date_time_t *current, date_time_t *other );


/*
   Conversion
*/

/*
   Element Change
*/

/**
   date_time_put

   Replaces date time instance to parameter values.

   @param current pointer to the data structure
   @param year the year AD of the date
   @param month the month 1-12 of the date
   @param day the day of the month 1-31 of the date
   @param hour_24 the hour 0-23 of the date in 24 hour format
   @param minute the minute 0-59 of the date
   @param second the second 0-59 of the date
   @param millisecond the millisecond 0-999 of the date
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
);

/**
   date_time_put_with_hour_12

   Replaces date time instance to parameter values.

   @param current pointer to the data structure
   @param year the year AD of the date
   @param month the month 1-12 of the date
   @param day the day of the month 1-31 of the date
   @param hour_12 the hour 0-11 of the date in 24 hour format
   @param minute the minute 0-59 of the date
   @param second the second 0-59 of the date
   @param millisecond the millisecond 0-999 of the date
   @param meridiem AM = 0, PM = 1
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
);

/**
   date_time_put_year

   Sets date time year.

   @param current pointer to the data structure
   @param year the year AD of the date
*/
void
date_time_put_year
(
   date_time_t *current,
   int32_t year
);

/**
   date_time_put_month

   Sets date time month.

   @param current pointer to the data structure
   @param month the month 1-12 of the date
*/
void
date_time_put_month
(
   date_time_t *current,
   int32_t month
);

/**
   date_time_put_day

   Sets date time day.

   @param current pointer to the data structure
   @param day the day 1-31 of the date
*/
void
date_time_put_day
(
   date_time_t *current,
   int32_t day
);

/**
   date_time_put_day_of_year

   Sets date time day of year.

   @param current pointer to the data structure
   @param day the day 1-365(6) of the date
*/
void
date_time_put_day_of_year
(
   date_time_t *current,
   int32_t day_of_year
);

/**
   date_time_put_hour_24

   Sets date time hour_24.

   @param current pointer to the data structure
   @param hour_24 the hour 0-23 of the date
*/
void
date_time_put_hour_24
(
   date_time_t *current,
   int32_t hour_24
);

/**
   date_time_put_hour_12

   Sets date time hour_12.

   @param current pointer to the data structure
   @param hour_12 the hour 0-11 of the date
   @param meridiem AM = 0, PM = 1
*/
void
date_time_put_hour_12
(
   date_time_t *current,
   int32_t hour_12,
   int32_t meridiem
);

/**
   date_time_put_minute

   Sets date time minute.

   @param current pointer to the data structure
   @param minute the minute 0-59 of the date
*/
void
date_time_put_minute
(
   date_time_t *current,
   int32_t minute
);

/**
   date_time_put_second

   Sets date time second.

   @param current pointer to the data structure
   @param second the second 0-59 of the date
*/
void
date_time_put_second
(
   date_time_t *current,
   int32_t second
);

/**
   date_time_put_millisecond

   Sets date time millisecond.

   @param current pointer to the data structure
   @param millisecond the millisecond 0-999 of the date
*/
void
date_time_put_millisecond
(
   date_time_t *current,
   int32_t millisecond
);

/**
   date_time_add_delta_milliseconds

   Adds specified milliseconds to date.

   @param current pointer to the data structure
   @param milliseconds when positive, date will be later - negative, earlier
*/
void
date_time_add_delta_milliseconds
(
   date_time_t *current,
   int64_t milliseconds
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

#endif /* DATE_TIME_T_H */

/* End of file */





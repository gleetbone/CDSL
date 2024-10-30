/**
 @file Date_Time_Duration.h
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

 Function declarations for the opaque date_time_duration_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATE_TIME_DURATION_T_H
#define DATE_TIME_DURATION_T_H


/**
   Version
*/

#define DATE_TIME_DURATION_VERSION_MAJOR 2
#define DATE_TIME_DURATION_VERSION_MINOR 0
#define DATE_TIME_DURATION_VERSION_PATCH 0

#define DATE_TIME_DURATION_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define DATE_TIME_DURATION_VERSION \
   DATE_TIME_DURATION_MAKE_VERSION( DATE_TIME_DURATION_VERSION_MAJOR, \
                       DATE_TIME_DURATION_VERSION_MINOR, \
                       DATE_TIME_DURATION_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"
#include "Date_Time.h"

/**
   Structure declaration
*/

struct date_time_duration_struct;

/**
   Structure typedef
*/

typedef struct date_time_duration_struct date_time_duration_t;


/*
   Initialization
*/

/**
   date_time_duration_make_start_end

   Create and initialize a date_time_duration_t instance from input parameters.
   Duration has definite start date_time.

   @param start_dt the start date_time
   @param end_dt the end time date time
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_make_start_end
(
   date_time_t *start_dt,
   date_time_t *end_dt
);

/**
   date_time_duration_make_start_dhms

   Create and initialize a date_time_duration_t instance from input parameters.
   Duration has definite start date_time.

   @param start_dt the start date_time
   @param days the number of days of the duration
   @param hours the number of hours 0-23 of the duration
   @param minutes the number of minutes 0-59 of the duration
   @param seconds the number of seconds 0-59 of the duration
   @param milliseconds the number of milliseconds 0-999 of the duration
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_make_start_dhms
(
   date_time_t *start_dt,
   int32_t days,
   int32_t hours,
   int32_t minutes,
   int32_t seconds,
   int32_t milliseconds
);

/**
   date_time_duration_make_start_milliseconds

   Create and initialize a date_time_duration_t instance from input parameters.
   Duration has definite start date_time.

   @param start_dt the start date_time
   @param milliseconds the number of milliseconds of the duration
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_make_start_milliseconds
(
   date_time_t *start_dt,
   int64_t milliseconds
);

/**
   date_time_duration_make_dhms

   Create and initialize a date_time_duration_t instance from input parameters.
   Duration has no definite start date_time.
   If days, hours, and minutes are zero, seconds may be any positive integer.

   @param days the number of days of the duration
   @param hours the number of hours 0-23 of the duration
   @param minutes the number of minutes 0-59 of the duration
   @param seconds the number of seconds 0-59 of the duration, see note above
   @param milliseconds the number of milliseconds 0-999 of the duration
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_make_dhms
(
   int32_t days,
   int32_t hours,
   int32_t minutes,
   int32_t seconds,
   int32_t milliseconds
);

/**
   date_time_duration_make_milliseconds

   Create and initialize a date_time_duration_t instance from input parameters.
   Duration has no definite start date_time.
   @param milliseconds the number of milliseconds of the duration
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_make_milliseconds
(
   int64_t milliseconds
);

/*
   Basic
*/

/**
   date_time_duration_clone

   Create and initialize a clone of a date_time_duration_t instance.

   @param current the date_time_duration_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_clone( date_time_duration_t *current );

/**
   date_time_duration_deep_clone

   Create and initialize a deep clone of a date_time_duration_t instance.

   @param current the date_time_duration_t instance to initialize from
   @return pointer to the new data structure
*/
date_time_duration_t *
date_time_duration_deep_clone( date_time_duration_t *current );

/**
   date_time_duration_is_equal

   Returns 1 if the current contains the same values as other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_duration_is_equal( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t date_time_duration_is_deep_equal( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_copy

   Puts contents of other into current

   @param current the date_time_duration_t instance to copy into
   @param other the date_time_duration_t to copy from
*/
void date_time_duration_copy( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_deep_copy

   Puts contents of other into current

   @param current the date_time_duration_t instance to copy into
   @param other the date_time_duration_t to copy from
*/
void date_time_duration_deep_copy( date_time_duration_t *current, date_time_duration_t *other );


/*
   Disposal
*/

/**
   date_time_duration_dispose

   Deallocates a date_time_duration_t instance.

   @param current pointer to the date_time_duration instance to dispose
*/
void
date_time_duration_dispose( date_time_duration_t **current );

/**
   date_time_duration_deep_dispose

   Deallocates a date_time_duration_t instance.

   @param current pointer to the date_time_duration instance to dispose
*/
void
date_time_duration_deep_dispose( date_time_duration_t **current );


/*
   Access
*/


/**
   date_time_duration_start

   Returns the start date_time of the instance if duration has definite start.

   @return the start date_time
*/
date_time_t *
date_time_duration_start( date_time_duration_t *current );

/**
   date_time_duration_end

   Returns the end date_time of the instance if duration has definite start.

   @return the end date_time
*/
date_time_t *
date_time_duration_end( date_time_duration_t *current );

/**
   date_time_duration_duration_milliseconds

   Returns the duration as a number of milliseconds.

   @return the number of milliseconds in the duration
*/
int64_t
date_time_duration_duration_milliseconds( date_time_duration_t *current );

/**
   date_time_duration_days_part

   Returns the number of whole days in the duration.

   @return the number of whole days in the duration
*/
int32_t
date_time_duration_days_part( date_time_duration_t *current );

/**
   date_time_duration_hours_part

   Returns the number of whole hours in the duration when whole days
   are subtracted out.

   @return the number of whole hours in the duration, 0-23
*/
int32_t
date_time_duration_hours_part( date_time_duration_t *current );

/**
   date_time_duration_minutes_part

   Returns the number of whole minutes in the duration when whole days
   are subtracted out.

   @return the number of whole minutes in the duration, 0-59
*/
int32_t
date_time_duration_minutes_part( date_time_duration_t *current );

/**
   date_time_duration_seconds_part

   Returns the number of whole seconds in the duration when whole days
   and whole minutes are subtracted out.

   @return the number of whole seconds in the duration, 0-59
*/
int32_t
date_time_duration_seconds_part( date_time_duration_t *current );

/**
   date_time_duration_milliseconds_part

   Returns the number of whole milliseconds in the duration when whole days,
   whole minutes, and whole seconds are subtracted out.

   @return the number of whole milliseconds in the duration, 0-999
*/
int32_t
date_time_duration_milliseconds_part( date_time_duration_t *current );

/**
   date_time_duration_is_definite

   Returns 1 if duration has definite start time, 0 otherwise.

   @param pointer to the data structure
   @return 0 - indefinite, 1 - definite
*/
int32_t
date_time_duration_is_definite
(
   date_time_duration_t *current
);

/*
   Measurement
*/

/*
   Status Report
*/

/*
   Comparison
*/

/**
   date_time_duration_is_less_than

   Returns 1 if current is less than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is less than other, 0 otherwise
*/
int32_t date_time_duration_is_less_than( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_less_than_or_equal

   Returns 1 if current is less than or equal to other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is less than or equal to other, 0 otherwise
*/
int32_t date_time_duration_is_less_than_or_equal( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_greater_than

   Returns 1 if current is greater than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is greater than other, 0 otherwise
*/
int32_t date_time_duration_is_greater_than( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_greater_than_or_equal

   Returns 1 if current is greater than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is greater than or equal to other, 0 otherwise
*/
int32_t date_time_duration_is_greater_than_or_equal( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_compare

   Returns negative if current is less than other, 0 if current equal to other, positive if
   current greater than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return negative if current < other, 0 if current == other, positive if current > other
*/
int32_t date_time_duration_compare( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_earlier_than

   Returns 1 if current is earlier than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is earlier than other, 0 otherwise
*/
int32_t date_time_duration_is_earlier_than( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_earlier_than_or_equal

   Returns 1 if current is earlier than or equal to other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is earlier than or equal to other, 0 otherwise
*/
int32_t date_time_duration_is_earlier_than_or_equal( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_later_than

   Returns 1 if current is later than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is later than other, 0 otherwise
*/
int32_t date_time_duration_is_later_than( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_later_than_or_equal

   Returns 1 if current is later than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return 1 if current is later than or equal to other, 0 otherwise
*/
int32_t date_time_duration_is_later_than_or_equal( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_start_time_compare

   Returns negative if current is earlier than other, 0 if current equal to other, positive if
   current later than other

   @param current the first date_time_duration_t instance
   @param other the first date_time_duration_t instance
   @return negative if current < other, 0 if current == other, positive if current > other
*/
int32_t date_time_duration_start_time_compare( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_overlap

   Returns date_time_duration if current overlaps other, NULL otherwise.

   @param current the date_time_duration_t instance
   @param other the other date_time_duration_t instance
   @return date_time_duration of overlap between current and other, NULL otherwise
*/
date_time_duration_t *date_time_duration_overlap( date_time_duration_t *current, date_time_duration_t *other );

/**
   date_time_duration_is_overlap

   Returns 1 if current overlaps other, NULL otherwise.

   @param current the date_time_duration_t instance
   @param other the other date_time_duration_t instance
   @return 1 if overlap between current and other, 0 otherwise
*/
int32_t date_time_duration_is_overlap( date_time_duration_t *current, date_time_duration_t *other );


/*
   Conversion
*/

/*
   Element Change
*/

/**
   date_time_duration_put_start

   Sets start date_time value.

   @param pointer to the data structure
   @param start_dt the new start date_time
*/
void
date_time_duration_put_start
(
   date_time_duration_t *current,
   date_time_t *start_dt
);

/**
   date_time_duration_put_end

   Sets end date_time value.

   @param pointer to the data structure
   @param end_dt the new end date_time
*/
void
date_time_duration_put_end
(
   date_time_duration_t *current,
   date_time_t *end_dt
);

/**
   date_time_duration_put_start_end

   Sets start and end date_time value.

   @param pointer to the data structure
   @param start_dt the new start date_time
   @param end_dt the new start date_time
*/
void
date_time_duration_put_start_end
(
   date_time_duration_t *current,
   date_time_t *start_dt,
   date_time_t *end_dt
);

/**
   date_time_duration_put_start_duration_dhms

   Sets date time duration instance to new start and duration.

   @param pointer to the new data structure
   @param start_dt the new start date_time
   @param days the number of days of the duration
   @param hours the number of hours 0-23 of the duration
   @param minutes the number of minutes 0-59 of the duration
   @param seconds the number of seconds 0-59 of the duration
   @param milliseconds the number of milliseconds 0-999 of the duration
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
);

/**
   date_time_duration_put_start_duration_milliseconds

   Sets date time duration instance to new duration.

   @param pointer to the data structure
   @param start_dt the new start date_time
   @param milliseconds the number of milliseconds for the duration
*/
void
date_time_duration_put_start_duration_milliseconds
(
   date_time_duration_t *current,
   date_time_t *start_dt,
   int64_t milliseconds
);

/**
   date_time_duration_put_duration_dhms

   Sets date time duration instance to new duration.

   @param pointer to the new data structure
   @param days the number of days of the duration
   @param hours the number of hours 0-23 of the duration
   @param minutes the number of minutes 0-59 of the duration
   @param seconds the number of seconds 0-59 of the duration
   @param milliseconds the number of milliseconds 0-999 of the duration
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
);

/**
   date_time_duration_put_duration_milliseconds

   Sets date time duration instance to new duration.

   @param pointer to the data structure
   @param milliseconds the number of milliseconds for the duration
*/
void
date_time_duration_put_duration_milliseconds
(
   date_time_duration_t *current,
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

#endif /* DATE_TIME_DURATION_T_H */

/* End of file */





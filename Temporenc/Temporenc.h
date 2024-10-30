/**
 @file Temporenc.h
 @author Greg Lee
 @version 0.0

 description: "Binary time format"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Defines functions to create, dispose, set, and access 64 bit binary
 date/time format.

*/

#include "base.h"

#ifndef TEMPORENC_H
#define TEMPORENC_H

/**
   Version
*/

#define TEMPORENC_VERSION_MAJOR 2
#define TEMPORENC_VERSION_MINOR 0
#define TEMPORENC_VERSION_PATCH 0

#define TEMPORENC_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define TEMPORENC_VERSION \
   TEMPORENC_MAKE_VERSION( TEMPORENC_VERSION_MAJOR, \
                       TEMPORENC_VERSION_MINOR, \
                       TEMPORENC_VERSION_PATCH )

/**
   Includes
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <base.h>

/**
   Structure declaration
*/

struct temporenc_struct;

/**
   Structure typedef
*/

typedef struct temporenc_struct temporenc_t;

/**
   temporenc_make_default

   Make a default temporenc_t

   @return the new structure
*/

temporenc_t *
temporenc_make_default( void );

/**
   temporenc_make

   Make a temporenc_t

   @param year the year 0 - 4094 (AD)
   @param month the month 0 - 11
   @param day the day 0 - 30
   @param hour the hour 0 - 23
   @param minute the minute 0 - 59
   @param second the second 0 - 59
   @param millisecond the millisecond 0 - 999
   @param millisecond_is_set 1 if milliseconds set, 0 otherwise
   @param time_zone_sign 1 if positive  or zero, -1 if negative
   @param time_zone_hour 0 to 12
   @param time_zone_minute 0, 15, 30, or 45
   @return the new structure
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
);

/**
   temporenc_make_gmt

   Make a temporenc_t in GMT

   @param year the year 0 - 4094 (AD)
   @param month the month 0 - 11
   @param day the day 0 - 30
   @param hour the hour 0 - 23
   @param minute the minute 0 - 59
   @param second the second 0 - 59
   @param millisecond the millisecond 0 - 999
   @return the new structure
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
);

/**
   temporenc_clone

   Creates and initializes temporenc from a temporenc

   @param current the other component
   @return pointer to new temporenc
*/
temporenc_t *
temporenc_clone( temporenc_t *current );

/**
   temporenc_deep_clone

   Creates and initializes temporenc from a temporenc

   @param current the other component
   @return pointer to new temporenc
*/
temporenc_t *
temporenc_deep_clone( temporenc_t *current );

/**
   temporenc_copy

   Puts contents of other into current

   @param temporenc the temporenc
   @param other the other temporenc
*/
void
temporenc_copy( temporenc_t *current, temporenc_t *other );

/**
   temporenc_deep_copy

   Puts contents of other into current

   @param temporenc the temporenc
   @param other the other temporenc
*/
void
temporenc_deep_copy( temporenc_t *current, temporenc_t *other );

/**
   temporenc_is_equal

   Returns 1 of temporenc is equal to other, 0 otherwise

   @param current the temporenc
   @param other the other temporenc
   @return 1 if equal, 0 otherwise
*/
int32_t
temporenc_is_equal( temporenc_t *current, temporenc_t *other );

/**
   temporenc_is_deep_equal

   Returns 1 of temporenc is equal to other, 0 otherwise

   @param current the temporenc
   @param other the other temporenc
   @return 1 if equal, 0 otherwise
*/
int32_t
temporenc_is_deep_equal( temporenc_t *current, temporenc_t *other );

/**
   temporenc_dispose

   Disposes of temporenc

   @param current the temporenc to dispose of
*/

void
temporenc_dispose( temporenc_t **current );

/**
   temporenc_deep_dispose

   Disposes of temporenc

   @param current the temporenc to dispose of
*/

void
temporenc_deep_dispose( temporenc_t **current );

/**
   temporenc_year

   Gets year

   @param current the temporenc
*/

int32_t
temporenc_year( temporenc_t *current );

/**
   temporenc_year_is_undefined

   Gets year_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_year_is_undefined( temporenc_t *current );

/**
   temporenc_put

   Set all temporenc_t values

   @param current the temporenc_t instance
   @param year the year 0 - 4094 (AD)
   @param month the month 0 - 11
   @param day the day 0 - 30
   @param hour the hour 0 - 23
   @param minute the minute 0 - 59
   @param second the second 0 - 59
   @param millisecond the millisecond 0 - 999
   @param millisecond_is_set 1 if milliseconds set, 0 otherwise
   @param time_zone_sign 1 if positive  or zero, -1 if negative
   @param time_zone_hour 0 to 12
   @param time_zone_minute 0, 15, 30, or 45
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
);

/**
   temporenc_put_year

   Sets year, 0 - 4094 (AD)

   @param current the temporenc
   @param year the year
*/

void
temporenc_put_year( temporenc_t *current, int32_t year );

/**
   temporenc_set_year_is_undefined

   Sets year_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_year_is_undefined( temporenc_t *current );

/**
   temporenc_month

   Gets month

   @param current the temporenc
*/

int32_t
temporenc_month( temporenc_t *current );

/**
   temporenc_month_is_undefined

   Gets month_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_month_is_undefined( temporenc_t *current );

/**
   temporenc_put_month

   Sets month, 0 - 11

   @param current the temporenc
   @param month the month
*/

void
temporenc_put_month( temporenc_t *current, int32_t month );

/**
   temporenc_set_month_is_undefined

   Sets month_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_month_is_undefined( temporenc_t *current );

/**
   temporenc_day

   Gets day

   @param current the temporenc
*/

int32_t
temporenc_day( temporenc_t *current );

/**
   temporenc_day_is_undefined

   Gets day_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_day_is_undefined( temporenc_t *current );

/**
   temporenc_put_day

   Sets day, 0 - 30

   @param current the temporenc
   @param day the day
*/

void
temporenc_put_day( temporenc_t *current, int32_t day );

/**
   temporenc_set_day_is_undefined

   Sets day_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_day_is_undefined( temporenc_t *current );

/**
   temporenc_hour

   Gets hour

   @param current the temporenc
*/

int32_t
temporenc_hour( temporenc_t *current );

/**
   temporenc_hour_is_undefined

   Gets hour_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_hour_is_undefined( temporenc_t *current );

/**
   temporenc_put_hour

   Sets hour, 0 - 23

   @param current the temporenc
   @param hour the hour
*/

void
temporenc_put_hour( temporenc_t *current, int32_t hour );

/**
   temporenc_set_hour_is_undefined

   Sets hour_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_hour_is_undefined( temporenc_t *current );

/**
   temporenc_minute

   Gets minute

   @param current the temporenc
*/

int32_t
temporenc_minute( temporenc_t *current );

/**
   temporenc_minute_is_undefined

   Gets minute_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_minute_is_undefined( temporenc_t *current );

/**
   temporenc_put_minute

   Sets minute, 0 - 59

   @param current the temporenc
   @param minute the minute
*/

void
temporenc_put_minute( temporenc_t *current, int32_t minute );

/**
   temporenc_set_minute_is_undefined

   Sets minute_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_minute_is_undefined( temporenc_t *current );

/**
   temporenc_second

   Gets second

   @param current the temporenc
*/

int32_t
temporenc_second( temporenc_t *current );

/**
   temporenc_second_is_undefined

   Gets second_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_second_is_undefined( temporenc_t *current );

/**
   temporenc_put_second

   Sets second, 0 - 59

   @param current the temporenc
   @param second the second
*/

void
temporenc_put_second( temporenc_t *current, int32_t second );

/**
   temporenc_set_second_is_undefined

   Sets second_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_second_is_undefined( temporenc_t *current );

/**
   temporenc_millisecond

   Gets millisecond

   @param current the temporenc
*/

int32_t
temporenc_millisecond( temporenc_t *current );

/**
   temporenc_millisecond_is_undefined

   Gets millisecond_is_undefined flag

   @param current the temporenc
*/

int32_t
temporenc_millisecond_is_undefined( temporenc_t *current );

/**
   temporenc_put_millisecond

   Sets millisecond, 0 - 999

   @param current the temporenc
   @param millisecond the millisecond
*/

void
temporenc_put_millisecond( temporenc_t *current, int32_t millisecond );

/**
   temporenc_set_millisecond_is_undefined

   Sets millisecond_is_undefined flag

   @param current the temporenc
*/

void
temporenc_set_millisecond_is_undefined( temporenc_t *current );

/**
   temporenc_timezone_offset_sign

   Gets timezone offset sign

   @param current the temporenc
   @return 1 if positive or zero, -1 if negative
*/

int32_t
temporenc_timezone_offset_sign( temporenc_t *current );

/**
   temporenc_timezone_offset_hour

   Gets timezone offset hour 0 - 12

   @param current the temporenc
   @return  hours in timezone offset (positive number, for negative numbers
            see temporenc_timezone_offset_sign
*/

int32_t
temporenc_timezone_offset_hour( temporenc_t *current );

/**
   temporenc_timezone_offset_minute

   Gets timezone offset minute 0, 14, 30, or 45

   @param current the temporenc
   @return  minutes in timezone offset (positive number, for negative numbers
            see temporenc_timezone_offset_sign
*/

int32_t
temporenc_timezone_offset_minute( temporenc_t *current );

/**
   temporenc_timezone_offset_is_unexpressed

   Gets whether timezone offset is expressed in the temporenc

   @param current the temporenc
   @return 1 if unexpressed
*/

int32_t
temporenc_timezone_offset_is_unexpressed( temporenc_t *current );

/**
   temporenc_timezone_offset_is_undefined

   Gets whether timezone offset is expressed in the temporenc

   @param current the temporenc
   @return 1 if undefined
*/

int32_t
temporenc_timezone_offset_is_undefined( temporenc_t *current );

/**
   temporenc_put_timezone_offset

   Sets timezone offset

   @param current the temporenc
   @param sign whether the offset is positive (or zero) or negative
   @param hour 0 - 12
   @param minute 0, 15, 30, or 45
*/

void
temporenc_put_timezone_offset( temporenc_t *current, int32_t sign, int32_t hour, int32_t minute );

/**
   temporenc_timezone_offset_set_is_unexpressed

   Sets timezone is_unexpressed

   @param current the temporenc
*/

void
temporenc_timezone_offset_set_is_unexpressed( temporenc_t *current );

/**
   temporenc_timezone_offset_set_is_undefined

   Sets timezone is_undefined

   @param current the temporenc
*/

void
temporenc_timezone_offset_set_is_undefined( temporenc_t *current );

/**
   temporenc_encode

   Return the temporenc encoded in a 64 bit integer

   @param current the temporenc
   @return  encoded temporenc
*/

uint64_t
temporenc_encode( temporenc_t *current );

/**
   temporenc_decode

   Return the temporenc encoded in a 64 bit integer

   @param current the temporenc
   @param arg encoded temporenc
*/

void
temporenc_decode( temporenc_t *current, uint64_t arg );

/**
   temporenc_is_less_than

   Returns 1 if current is less than other, 0 otherwise

   @param current the temporenc
   @param other the temporenc to compare with
   @return  1 if current < other, 0 otherwise
*/

int32_t
temporenc_is_less_than( temporenc_t *current, temporenc_t *other );

/**
   temporenc_is_greater_than

   Returns 1 if current is greater than other, 0 otherwise

   @param current the temporenc
   @param other the temporenc to compare with
   @return  1 if current > other, 0 otherwise
*/

int32_t
temporenc_is_greater_than( temporenc_t *current, temporenc_t *other );

/**
   temporenc_is_equal_to

   Returns 1 if current is equal to other, 0 otherwise

   @param current the temporenc
   @param other the temporenc to compare with
   @return  1 if current == other, 0 otherwise
*/

int32_t
temporenc_is_equal_to( temporenc_t *current, temporenc_t *other );

#ifdef __cplusplus
}
#endif

#endif /* TEMPORENC_H */

/* End of file */


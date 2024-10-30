/**
 @file Lsqline.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Lsqlines"

 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2022 Greg Lee

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

 Function declarations for the opaque lsqline_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LSQLINE_T_H
#define LSQLINE_T_H


/**
   Version
*/

#define LSQLINE_VERSION_MAJOR 2
#define LSQLINE_VERSION_MINOR 0
#define LSQLINE_VERSION_PATCH 0

#define LSQLINE_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define LSQLINE_VERSION \
   LSQLINE_MAKE_VERSION( LSQLINE_VERSION_MAJOR, \
                       LSQLINE_VERSION_MINOR, \
                       LSQLINE_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Type   - the type of the value

   Macros that must be present (external to this file):

   VALUE_DISPOSE_FUNCTION  -  frees a value instance

*/

/**
   Structure declarations
*/

struct lsqline_struct;

/**
   Structure typedefs
*/

typedef struct lsqline_struct lsqline_t;

/*
   Initialization
*/

/**
   lsqline_make

   Return a new empty lsqline_t instance.

   @param  n number of history points to hold
   @return lsqline_t instance
*/
lsqline_t * lsqline_make( int32_t n );

/*
   Basic
*/

/**
   lsqline_clone

   Return a new lsqline_t instance filled with the content of current.

   @param  current lsqline_t instance to copy from
   @return lsqline_t instance
*/
lsqline_t * lsqline_clone( lsqline_t *current );

/**
   lsqline_deep_clone

   Return a new lsqline_t instance filled with duplicates of the content of current.

   @param  current lsqline_t instance to copy from
   @return lsqline_t instance
*/
lsqline_t * lsqline_deep_clone( lsqline_t *current );

/**
   lsqline_is_equal

   Check that current contains same elements as other

   @param  current lsqline_t instance
   @param  other lsqline_t instance to compare to
   @return 1 if equal, 0 otherwise
*/
int32_t lsqline_is_equal( lsqline_t *current, lsqline_t *other );

/**
   lsqline_is_deep_equal

   Check that current contains same elements as other

   @param  current lsqline_t instance
   @param  other lsqline_t instance to compare to
   @return 1 if equal, 0 otherwise
*/
int32_t lsqline_is_deep_equal( lsqline_t *current, lsqline_t *other );

/**
   lsqline_copy

   Copy other into current

   @param  current lsqline_t instance
   @param  other lsqline_t instance to copy from

*/
void lsqline_copy( lsqline_t *current, lsqline_t *other );

/**
   lsqline_deep_copy

   Deep copy other into current

   @param  current lsqline_t instance
   @param  other lsqline_t instance to deep_copy from

*/
void lsqline_deep_copy( lsqline_t *current, lsqline_t *other );


/*
   Disposal
*/

/**
   lsqline_dispose

   Free a lsqline_t instance.

   @param  current lsqline_t instance
*/
void lsqline_dispose( lsqline_t **current );

/**
   lsqline_deep_dispose

   Free a lsqline_t instance. The value items are disposed.

   @param  current lsqline_t instance
*/
void lsqline_deep_dispose( lsqline_t **current );

/*
   Access
*/

/**
   lsqline_slope

   Return last computed line slope.

   @param  current lsqline_t instance
   @return slope
*/
float32_t lsqline_slope( lsqline_t *current );

/**
   lsqline_y_intercept

   Return last computed y intercept.

   @param  current lsqline_t instance
   @return y intercept
*/
float32_t lsqline_y_intercept( lsqline_t *current );

/**
   lsqline_fit

   Return last computed line fit ( lower number is better fit).

   @param  current lsqline_t instance
   @return fit
*/
float32_t lsqline_fit( lsqline_t *current );

/*
   Measurement
*/

/**
   lsqline_capacity

   Return capacity of slots for x,y point history.

   @param  current lsqline_t instance
   @return max number of bins for storage
*/
int32_t lsqline_capacity( lsqline_t *current );

/**
   lsqline_count

   Return nuber pf points in x,y input

   @param  current lsqline_t instance
   @return number of input points
*/
int32_t lsqline_count( lsqline_t *current );

/**
   lsqline_is_output_valid

   Return is_output_valid flag. False if computation would divide b zero
   or there are insufficient data points saved into the history.

   @param  current lsqline_t instance
   @return is_output_valid flag
*/
int32_t lsqline_is_output_valid( lsqline_t *current );

/*
   Basic Operations
*/

/**
   lsqline_compute

   Compute the linear regression for the data in the buffers.

   @param  current lsqline_t instance
*/
void lsqline_compute( lsqline_t *current );

/**
   lsqline_put

   Insert new line point values.

   @param  current lsqline_t instance
   @param  x the x value of the new point
   @param  y the y value of the new point
*/
void lsqline_put( lsqline_t *current, float32_t x, float32_t y );

/**
   lsqline_reset

   Reset internal state to re-start data input and computation

   @param  current lsqline_t instance
*/
void lsqline_reset( lsqline_t *current );


#ifdef __cplusplus
}
#endif

#endif /* LSQLINE_T_H */

/* End of file */

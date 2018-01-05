/**
 @file rng_isaac_gaussian.h
 @author Greg Lee
 @version 1.0.0
 @brief: "ISAAC (pseudo) Random Number Generator for gaussian distribution"
 
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

 Function declarations for the opaque rng_isaac_gaussian_t type.

*/

/**
   includes
*/

#include "base.h"

/** 
   Structure declarations
*/

struct rng_isaac_gaussian_struct;

/**
   Structure typedefs
*/

typedef struct rng_isaac_gaussian_struct rng_isaac_gaussian_t;


/** 
   Initialization
*/

/**
   rng_isaac_gaussian_make
   
   Return a new rng_isaac_gaussian_t instance with the default seed.
   
   @return rng_isaac_gaussian_t instance 
*/
rng_isaac_gaussian_t * rng_isaac_gaussian_make( void );

/**
   rng_isaac_gaussian_make_with_seed
   
   Return a new rng_isaac_gaussian_t instance with the specified seed.
   
   @param seed the seed for the rng
   @return rng_isaac_gaussian_t instance 
*/
rng_isaac_gaussian_t * rng_isaac_gaussian_make_with_seed( uint64_t seed );

/**
   Disposal
*/

/**
   rng_isaac_gaussian_dispose
   
   Free a rng_isaac_gaussian_t instance. The value items are not disposed.
   
   @param  rng_isaac_gaussian rng_isaac_gaussian_t instance 
*/
void rng_isaac_gaussian_dispose( rng_isaac_gaussian_t *rng_isaac_gaussian );

/** 
   Access
*/

/**
   rng_isaac_gaussian_f32_item
   
   Return a float32_t random number, [0, 1]
   
   @param  rng_isaac_gaussian rng_isaac_gaussian_t instance 
   @return the random number
*/
float32_t rng_isaac_gaussian_f32_item( rng_isaac_gaussian_t *rng_isaac_gaussian );

/**
   rng_isaac_gaussian_f64_item
   
   Return a float64_t random number, [0, 1]
   
   @param  rng_isaac_gaussian rng_isaac_gaussian_t instance 
   @return the random number
*/
float64_t rng_isaac_gaussian_f64_item( rng_isaac_gaussian_t *rng_isaac_gaussian );

/**
   Cursor movement
*/

/**
   rng_isaac_gaussian_forth
   
   Go to the next random number
   
   @param  rng_isaac_gaussian rng_isaac_gaussian_t instance 
*/
void rng_isaac_gaussian_forth( rng_isaac_gaussian_t *rng_isaac_gaussian );


/* End of file */




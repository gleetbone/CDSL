/**
 @file rng_isaac.h
 @author Greg Lee
 @version 1.0.0
 @brief: "ISAAC (pseudo) Random Number Generator"
 
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

 Function declarations for the opaque rng_isaac_t type.

 Code taken from Bob Jenkin's ISAAC random number generator. As of this writing,
 ISAAC can be found at http://burtleburtle.net/bob/rand/isaacafa.html.
 
*/

/**
   includes
*/

#include "base.h"

/** 
   Structure declarations
*/

struct rng_isaac_struct;

/**
   Structure typedefs
*/

typedef struct rng_isaac_struct rng_isaac_t;


/** 
   Initialization
*/

/**
   rng_isaac_make
   
   Return a new rng_isaac_t instance with the default seed.
   
   @return rng_isaac_t instance 
*/
rng_isaac_t * rng_isaac_make( void );

/**
   rng_isaac_make_with_seed
   
   Return a new rng_isaac_t instance with the specified seed.
   
   @param seed the seed for the rng
   @return rng_isaac_t instance 
*/
rng_isaac_t * rng_isaac_make_with_seed( uint64_t seed );

/**
   Disposal
*/

/**
   rng_isaac_dispose
   
   Free a rng_isaac_t instance. The value items are not disposed.
   
   @param  rng_isaac rng_isaac_t instance 
*/
void rng_isaac_dispose( rng_isaac_t *rng_isaac );

/** 
   Access
*/

/**
   rng_isaac_i32_item
   
   Return an int32_t random number
   
   @param  rng_isaac rng_isaac_t instance 
   @return the random number
*/
int32_t rng_isaac_i32_item( rng_isaac_t *rng_isaac );

/**
   rng_isaac_u32_item
   
   Return an uint32_t random number
   
   @param  rng_isaac rng_isaac_t instance 
   @return the random number
*/
uint32_t rng_isaac_u32_item( rng_isaac_t *rng_isaac );

/**
   rng_isaac_i64_item
   
   Return an int64_t random number
   
   @param  rng_isaac rng_isaac_t instance 
   @return the random number
*/
int64_t rng_isaac_i64_item( rng_isaac_t *rng_isaac );

/**
   rng_isaac_u64_item
   
   Return an uint64_t random number
   
   @param  rng_isaac rng_isaac_t instance 
   @return the random number
*/
uint64_t rng_isaac_u64_item( rng_isaac_t *rng_isaac );

/**
   rng_isaac_f32_item
   
   Return a float32_t random number, [0, 1]
   
   @param  rng_isaac rng_isaac_t instance 
   @return the random number
*/
float32_t rng_isaac_f32_item( rng_isaac_t *rng_isaac );

/**
   rng_isaac_f64_item
   
   Return a float64_t random number, [0, 1]
   
   @param  rng_isaac rng_isaac_t instance 
   @return the random number
*/
float64_t rng_isaac_f64_item( rng_isaac_t *rng_isaac );

/**
   Cursor movement
*/

/**
   rng_isaac_forth
   
   Go to the next random number
   
   @param  rng_isaac rng_isaac_t instance 
*/
void rng_isaac_forth( rng_isaac_t *rng_isaac );


/* End of file */




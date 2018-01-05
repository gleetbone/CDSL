/**
 @file Svd.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Singular Value Decomposition"
 
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

 Function declarations for the opaque Svd_t type.

*/

/**
   includes
*/

#include "base.h"
#include "Matvec.h"
#include <stdarg.h>

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   Prefix - string used to name this container type
   Matvec_prefix - string used to name the matrix type
   Type   - the type of the value
   Magnitude_type - the type of the magnitude or precision of Type
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Svd_struct( arg ) PRIMITIVE_CAT( arg, _svd_struct )
#define Svd_type( arg ) PRIMITIVE_CAT( arg, _svd_t )
#define Svd_name( arg ) PRIMITIVE_CAT( arg, _svd )

/** 
   Structure declarations
*/

struct Svd_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Svd_struct( Prefix ) Svd_type( Prefix );


/** 
   Initialization
*/

/**
   Svd_make
   
   Return a new empty Svd_t instance.
   
   @return Svd_t instance 
*/
#define Svd_make( arg ) PRIMITIVE_CAT( arg, _svd_make )
Svd_type( Prefix ) * Svd_make( Prefix )( void );

/**
   Disposal
*/

/**
   Svd_dispose
   
   Free a Svd_t instance. The value items are not disposed.
   
   @param  svd Svd_t instance 
*/
#define Svd_dispose( arg ) PRIMITIVE_CAT( arg, _svd_dispose )
void Svd_dispose( Prefix )( Svd_type( Prefix ) *svd );

/**
   Svd_dispose_with_contents
   
   Free a Svd_t instance. The value items are disposed.
   
   @param  svd Svd_t instance 
*/
#define Svd_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _svd_dispose_with_contents )
void Svd_dispose_with_contents( Prefix )( Svd_type( Prefix ) *svd );

/** 
   Access
*/

/**
   Svd_input
   
   Return the input matrix.
   
   @param  svd Svd_t instance 
   @return the input matrix
*/
#define Svd_input( arg ) PRIMITIVE_CAT( arg, _svd_input )
Matvec_type( Matvec_prefix ) * Svd_input( Prefix )( Svd_type( Prefix ) *svd );

/**
   Svd_singular_values
   
   Return the singular values vector
   
   @param  svd Svd_t instance 
   @return the singular values
*/
#define Svd_singular_values( arg ) PRIMITIVE_CAT( arg, _svd_singular_values )
Matvec_type( Matvec_prefix ) * Svd_singular_values( Prefix )( Svd_type( Prefix ) *svd );

/**
   Svd_left_singular_vectors
   
   Return the left singular vectors
   
   @param  svd Svd_t instance 
   @return the left singular vectors
*/
#define Svd_left_singular_vectors( arg ) PRIMITIVE_CAT( arg, _svd_left_singular_vectors )
Matvec_type( Matvec_prefix ) * Svd_left_singular_vectors( Prefix )( Svd_type( Prefix ) *svd );

/**
   Svd_right_singular_vectors
   
   Return the right singular vectors
   
   @param  svd Svd_t instance 
   @return 1 if svd is column vector, 0 otherwise
*/
#define Svd_right_singular_vectors( arg ) PRIMITIVE_CAT( arg, _svd_right_singular_vectors )
Matvec_type( Matvec_prefix ) * Svd_right_singular_vectors( Prefix )( Svd_type( Prefix ) *svd );


/** 
   Measurement
*/

/**
   Svd_reconstructed_input
   
   Return the reconstructed input from the svd decomposition
   
   @param  svd Svd_t instance 
   @return the reconstructed input
*/
#define Svd_reconstructed_input( arg ) PRIMITIVE_CAT( arg, _svd_reconstructed_input )
Matvec_type( Matvec_prefix ) * Svd_reconstructed_input( Prefix )( Svd_type( Prefix ) *svd );

/** 
   Element change
*/

/**
   Svd_set_input
   
   Sets the input to the svd solver
   
   @param  svd Svd_t instance 
   @param  input the input to the svd herwise
*/
#define Svd_set_input( arg ) PRIMITIVE_CAT( arg, _svd_set_input )
void Svd_set_input( Prefix )( Svd_type( Prefix ) *svd, Matvec_type( Matvec_prefix ) *input );

/**
   Svd_set_rotation_error
   
   Set the rotation error for the svd
   
   @param  svd Svd_t instance 
   @param rotation_error the rotation error
*/
#define Svd_set_rotation_error( arg ) PRIMITIVE_CAT( arg, _svd_set_rotation_error )
void Svd_set_rotation_error( Prefix )( Svd_type( Prefix ) *svd, Magnitude_type rotation_error );

/**
   Svd_set_singular_value_threshold
   
   Set the singular value threshold for the svd
   
   @param  svd Svd_t instance 
   @param singular_value_threshold the singular value threshold
*/
#define Svd_set_singular_value_threshold( arg ) PRIMITIVE_CAT( arg, _svd_set_singular_value_threshold )
void Svd_set_singular_value_threshold( Prefix )( Svd_type( Prefix ) *svd, Magnitude_type singular_value_threshold );

/**
   Transformation
*/

/**
   Svd_inverse
   
   Returns the (pseudo)inverse of the input matrix
   
   @param  svd Svd_t instance 
   @return the inverse 
*/
#define Svd_inverse( arg ) PRIMITIVE_CAT( arg, _svd_inverse )
Matvec_type( Matvec_prefix ) * Svd_inverse( Prefix )( Svd_type( Prefix ) *svd );

/**
   Svd_svd
   
   Perform the singular value decomposition
   
   @param  svd Svd_t instance 
*/
#define Svd_svd( arg ) PRIMITIVE_CAT( arg, _svd_svd )
void Svd_svd( Prefix )( Svd_type( Prefix ) *svd );


/* End of file */




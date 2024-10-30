/**
 @file Fft.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Fast Fourier Transform"

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

 Function declarations for the opaque Fft_t type.

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
   Matvec_prefix - string used to name the vector type
   Matvec_magnitude_prefix - string used to name the magnitude vector type
   Type   - the type of the value
   Magnitude_type - the type of the magnitude or precision of Type

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Fft_struct( arg ) PRIMITIVE_CAT( arg, _fft_struct )
#define Fft_type( arg ) PRIMITIVE_CAT( arg, _fft_t )
#define Fft_name( arg ) PRIMITIVE_CAT( arg, _fft )

/**
   Structure declarations
*/

struct Fft_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Fft_struct( Prefix ) Fft_type( Prefix );


/*
   Initialization
*/

/**
   Fft_make

   Return a new Fft_t instance.

   @param length the length of the fft, must be power of two
   @return Fft_t instance
*/
#define Fft_make( arg ) PRIMITIVE_CAT( arg, _fft_make )
Fft_type( Prefix ) * Fft_make( Prefix )( int32_t length );

/*
   Disposal
*/

/**
   Fft_dispose

   Free a Fft_t instance. The value items are not disposed.

   @param  fft Fft_t instance
*/
#define Fft_dispose( arg ) PRIMITIVE_CAT( arg, _fft_dispose )
void Fft_dispose( Prefix )( Fft_type( Prefix ) **current );

/**
   Fft_deep_dispose

   Free a Fft_t instance. The value items are disposed.

   @param  fft Fft_t instance
*/
#define Fft_deep_dispose( arg ) PRIMITIVE_CAT( arg, _fft_deep_dispose )
void Fft_deep_dispose( Prefix )( Fft_type( Prefix ) **current );

/*
   Access
*/

/**
   Fft_input

   Return the input vector.

   @param  fft Fft_t instance
   @return the input vector
*/
#define Fft_input( arg ) PRIMITIVE_CAT( arg, _fft_input )
Matvec_type( Matvec_prefix ) * Fft_input( Prefix )( Fft_type( Prefix ) *current );

/**
   Fft_output

   Return the output vector

   @param  fft Fft_t instance
   @return the output vector
*/
#define Fft_output( arg ) PRIMITIVE_CAT( arg, _fft_output )
Matvec_type( Matvec_prefix ) * Fft_output( Prefix )( Fft_type( Prefix ) *current );

/**
   Fft_psd

   Return the power spectral density vector

   @param  fft Fft_t instance
   @return the power spectral density vector
*/
#define Fft_psd( arg ) PRIMITIVE_CAT( arg, _fft_psd )
Matvec_type( Matvec_magnitude_prefix ) * Fft_psd( Prefix )( Fft_type( Prefix ) *current );

/**
   Fft_log_psd

   Return the log power spectral density vector

   @param  fft Fft_t instance
   @return the log power spectral density vector
*/
#define Fft_log_psd( arg ) PRIMITIVE_CAT( arg, _fft_log_psd )
Matvec_type( Matvec_magnitude_prefix ) * Fft_log_psd( Prefix )( Fft_type( Prefix ) *current );

/**
   Fft_phase

   Return the phase vector

   @param  fft Fft_t instance
   @return the phase vector
*/
#define Fft_phase( arg ) PRIMITIVE_CAT( arg, _fft_phase )
Matvec_type( Matvec_magnitude_prefix ) * Fft_phase( Prefix )( Fft_type( Prefix ) *current );

/**
   Fft_phase_degrees

   Return the phase vector in degrees

   @param  fft Fft_t instance
   @return the phase vector
*/
#define Fft_phase_degrees( arg ) PRIMITIVE_CAT( arg, _fft_phase_degrees )
Matvec_type( Matvec_magnitude_prefix ) * Fft_phase_degrees( Prefix )( Fft_type( Prefix ) *current );


/*
   Element change
*/

/**
   Fft_set_input

   Sets the input to the fft solver

   @param  fft Fft_t instance
   @param  input the input to the fft
*/
#define Fft_set_input( arg ) PRIMITIVE_CAT( arg, _fft_set_input )
void Fft_set_input( Prefix )( Fft_type( Prefix ) *current, Matvec_type( Matvec_prefix ) *input );

/**
   Fft_set_output

   Sets the output to the fft solver for inverse Fft

   @param  fft Fft_t instance
   @param  input the input to the fft
*/
#define Fft_set_output( arg ) PRIMITIVE_CAT( arg, _fft_set_output )
void Fft_set_output( Prefix )( Fft_type( Prefix ) *current, Matvec_type( Matvec_prefix ) *output );

/*
   Transformation
*/

/**
   Fft_fft

   Perform the fast fourier transform on the input

   @param  fft Fft_t instance
*/
#define Fft_fft( arg ) PRIMITIVE_CAT( arg, _fft_fft )
void Fft_fft( Prefix )( Fft_type( Prefix ) *current );

/**
   Fft_inverse_fft

   Perform the inverse fast fourier transfor on the output

   @param  fft Fft_t instance
*/
#define Fft_inverse_fft( arg ) PRIMITIVE_CAT( arg, _fft_inverse_fft )
void Fft_inverse_fft( Prefix )( Fft_type( Prefix ) *current );


/* End of file */




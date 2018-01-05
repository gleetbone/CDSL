/**
 @file cf_Matvec.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for matrices of complex floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for cf_matvec type.

*/

#include "cf_Matvec.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_VALUE 0.0
#define ONE_VALUE 1.0 + 0.0*I
#define IS_INVERTIBLE 1

#define NEGATE_FUNCTION( arg ) ( -(arg) )
#define ADD_FUNCTION( arg1, arg2 ) ( ( (arg1) + (arg2) ) )
#define SQUARED_MAGNITUDE_FUNCTION( arg ) ( (arg)*conj(arg) )
#define MULTIPLY_FUNCTION( arg1, arg2 ) ( ( (arg1)*(arg2) ) )
#define INVERSE_FUNCTION( arg ) ( 1.0/(arg) )
#define CONJUGATE_FUNCTION( arg ) ( conj(arg) )
#define EQUAL_FUNCTION( arg1, arg2 ) ( ( (arg1) == (arg2) ) )
#define DUPLICATE_FUNCTION( arg ) ( arg )
#define SET_FROM( arg1, arg2 ) ( ( (arg1) = (arg2) ) )
#define DISPOSE_FUNCTION( arg )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix cf
#define Type complex float
#define Type_Code complex64_type_code
#define Magnitude_type float
#define Va_type complex double

#include "Matvec.c"

#ifdef __cplusplus
}
#endif

/* End of file */


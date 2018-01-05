/**
 @file cd_Svd.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for svd of matrices of complex doubles"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for cd_svd type.

*/

#include "cd_Svd.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_VALUE 0.0
#define ONE_VALUE 1.0 + 0.0*I
#define IS_INVERTIBLE 1

#define NEGATE_FUNCTION( arg ) ( -(arg) )
#define ADD_FUNCTION( arg1, arg2 ) ( ( (arg1) + (arg2) ) )
#define SQUARED_MAGNITUDE_FUNCTION( arg ) ( ( double ) ( (arg)*conj(arg) ) )
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

#define Prefix cd
#define Matvec_prefix cd
#define Type double complex
#define Type_Code complex128_type_code
#define Magnitude_type double

#include "Svd.c"

#ifdef __cplusplus
}
#endif

/* End of file */


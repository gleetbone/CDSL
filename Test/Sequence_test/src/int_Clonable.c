/**
 @file i_Clonable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for Clonable of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_Clonable type.

*/

#include "int_Clonable.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix int
#define Type int32_t

#include "P_Clonable.c"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file f_Quaternion.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for quaternions of floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for f_quaternion type.

*/

#include "f_Quaternion.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Prefix f
#define Mv_Prefix f
#define Type float
#define Type_Code float32_type_code

#include "Quaternion.c"

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file s_DIterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for DIterable of Strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for s_DIterable type.

*/

#include "s_DIterable.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix s
#define Type string_t *

#include "P_DIterable.c"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

/* End of file */


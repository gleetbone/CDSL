/**
 @file i_Iterable_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for Iterable_kv of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_Iterable type.

*/

#include "ii_Iterable_kv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix ii
#define Key int32_t
#define Type int32_t

#include "P_Iterable_kv.c"

#undef Prefix
#undef Key
#undef Type

#ifdef __cplusplus
}
#endif

/* End of file */


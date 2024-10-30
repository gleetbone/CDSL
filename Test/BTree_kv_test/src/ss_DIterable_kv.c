/**
 @file ss_DIterable_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for DIterable_kv of strubgs"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for ss_DIterable _kvtype.

*/

#include "ss_DIterable_kv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix ss
#define Key string_t *
#define Type string_t *

#include "P_DIterable_kv.c"

#undef Prefix
#undef Key
#undef Type

#ifdef __cplusplus
}
#endif

/* End of file */


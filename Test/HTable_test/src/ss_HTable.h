/**
 @file ss_HTable.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for hash table of strings to strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a htable into a ss_htable.

*/

#ifndef STRING_STRING_HTABLE_H_
#define STRING_STRING_HTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"
#include "String.h"

#define Prefix ss
#define Type string_t *
#define Key string_t *

#include "HTable.h"

#undef Prefix
#undef Type
#undef Key

#ifdef __cplusplus
}
#endif

#endif /* STRING_STRING_HTABLE_H_ */

/* End of file */




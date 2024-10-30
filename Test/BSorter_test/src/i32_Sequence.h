/**
 @file i32_Sequence.h
 @author Greg Lee
 @version 0.0

 description: "include file for sequences of 32 bit signed ints"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Defines to make a sequence into a i32_sequence.

*/

#ifndef I32_SEQUENCE_H_
#define I32_SEQUENCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix i32
#define Type int32_t

#include "Sequence.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* I32_SEQUENCE_H_ */

/* End of file */




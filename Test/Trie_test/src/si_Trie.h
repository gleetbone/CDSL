/**
 @file si_Trie.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for trie of strings to ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines to make a trie into a si_trie.

*/

#ifndef CSTRING_INT_TRIE_H_
#define CSTRING_INT_TRIE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix si
#define Type int32_t
#define Key char_t *
#define Key_Element char_t

#include "Trie.h"

#undef Prefix
#undef Type
#undef Key
#undef Key_Element

#ifdef __cplusplus
}
#endif

#endif /* CSTRING_INT_TRIE_H_ */

/* End of file */




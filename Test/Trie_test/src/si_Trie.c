/**
 @file si_Trie.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for hash table of ints to ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines for si_Trie_t type.

*/

#include "si_Trie.h"

#ifdef __cplusplus
extern "C" {
#endif

static
int32_t
compare_chars( char_t a, char_t b )
{
   int32_t result = 0;

   if ( a < b )
   {
      result = -1;
   }
   else if ( a > b )
   {
      result = 1;
   }

   return result;
}

#define KEY_ELEMENT_ACCESS_FUNCTION( arg1, arg2 ) ( arg1[arg2] )

#define KEY_ELEMENT_EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define KEY_ELEMENT_COMPARISON_FUNCTION( arg1, arg2 ) ( compare_chars( arg1, arg2 ) )

#define VALUE_DISPOSE_FUNCTION( arg )


#define Prefix si
#define Type int32_t
#define Key char_t *
#define Key_Element char_t

#define Key_Code char_ptr_type_code
#define Key_Element_Code char_type_code
#define Type_Code int32_type_code

#define Key_Element_Default_Value 0
#define Type_Default_Value 0

#include "Trie.c"

#undef Prefix
#undef Type
#undef Key
#undef Key_Code
#undef Key_Element_Code
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */


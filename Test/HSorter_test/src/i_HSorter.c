/**
 @file i_HSorter.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for sorter of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_HSorter type.

*/

#include "i_HSorter.h"

#ifdef __cplusplus
extern "C" {
#endif

static
int32_t
func( int32_t a, int32_t b )
{
   int32_t result = 0;

   if ( a < b )
   {
      result = -1;
   }
   else if ( a == b )
   {
      result = 0;
   }
   else
   {
      result = 1;
   }

   return result;
}

#define DISPOSE_FUNCTION( arg )
#define SORT_FUNCTION_NAME func

#define Prefix i
#define Type int32_t

#include "HSorter.c"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file hello.c
 @author Greg Lee
 @version 0.0

 description: "function to demonstrate agent"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Function to demonstrate agent.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void do_hello( int32_t i )
{
   printf( "hello %d\n", i );
   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


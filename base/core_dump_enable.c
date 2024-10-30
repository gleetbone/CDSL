/**
 @file core_dump_enable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Enables core dump for assertion and other fails"
 
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):
 
 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package. 

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.
 
 @section Description

 Function definition for the core_dump_enable function.

*/

/**
   Includes
*/

#include <assert.h>
#include <execinfo.h>
#include <stdio.h>
#include <sys/resource.h>

#ifdef __cplusplus
extern "C" {
#endif

static int core_dump_enabled = 0;

void core_dump_enable()
{
   if ( core_dump_enabled == 0 )
   {
      struct rlimit core_limit = { RLIM_INFINITY, RLIM_INFINITY };
      
      // enable core dumps for debug builds 
      assert( setrlimit( RLIMIT_CORE, &core_limit ) == 0 );
      
      // set flag so setrlimit not called more than once
      core_dump_enabled = 1;
   }
   
   return;   
}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file date_time_test_minute.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for date_time_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for date_time_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Date_Time.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_minute_1
*/

void test_minute_1( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_minute( date_time ) == 2 );
 
   date_time_dispose( &date_time );

   return;
}

int
add_test_minute( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_minute", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_minute_1
   add_test_to_suite( p_suite, test_minute_1, "test_minute_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


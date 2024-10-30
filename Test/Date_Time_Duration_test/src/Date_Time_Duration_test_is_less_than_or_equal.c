/**
 @file date_time_duration_test_is_less_than_or_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for date_time_duration_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for date_time_duration_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Date_Time_Duration.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_less_than_or_equal_1
*/

void test_is_less_than_or_equal_1( void )
{
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   date_time_duration_t *date_time_duration = NULL;
   date_time_duration_t *date_time_duration_1 = NULL;
   
   start_dt = date_time_make( 2020, 1, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 1, 1, 0, 0, 0 );
   date_time_duration = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_add_delta_milliseconds( end_dt, 1 );
   date_time_duration_1 = date_time_duration_make_start_end( start_dt, end_dt );
   
   CU_ASSERT( date_time_duration != NULL );
   CU_ASSERT( date_time_duration_1 != NULL );
   
   CU_ASSERT( date_time_duration_is_less_than_or_equal( date_time_duration, date_time_duration ) == 1 );
   CU_ASSERT( date_time_duration_is_less_than_or_equal( date_time_duration, date_time_duration_1 ) == 1 );
 
   date_time_dispose( &start_dt );
   date_time_dispose( &end_dt );
   
   date_time_duration_dispose( &date_time_duration );
   date_time_duration_dispose( &date_time_duration_1 );

   return;
}

int
add_test_is_less_than_or_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_less_than_or_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_less_than_or_equal_1
   add_test_to_suite( p_suite, test_is_less_than_or_equal_1, "test_is_less_than_or_equal_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


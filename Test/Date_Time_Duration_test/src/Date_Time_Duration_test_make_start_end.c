/**
 @file date_time_duration_test_make_start_end.c
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
   test_make_start_end_1
*/

void test_make_start_end_1( void )
{
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   date_time_t *dt = NULL;
   date_time_duration_t *date_time_duration = NULL;
   
   start_dt = date_time_make( 2020, 1, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 1, 1, 0, 0, 0 );
   date_time_duration = date_time_duration_make_start_end( start_dt, end_dt );
   
   CU_ASSERT( date_time_duration != NULL );
   
   dt = date_time_duration_start( date_time_duration );
   CU_ASSERT( date_time_is_equal( start_dt, dt ) == 1 );
   date_time_dispose( &dt );
   
   dt = date_time_duration_end( date_time_duration );
   CU_ASSERT( date_time_is_equal( end_dt, dt ) == 1 );
   date_time_dispose( &dt );
   
   CU_ASSERT( date_time_duration_duration_milliseconds( date_time_duration ) == 3600000L );
   CU_ASSERT( date_time_duration_is_definite( date_time_duration ) == 1 );
 
   date_time_dispose( &start_dt );
   date_time_dispose( &end_dt );
   
   date_time_duration_dispose( &date_time_duration );

   return;
}

int
add_test_make_start_end( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_start_end", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_start_end_1
   add_test_to_suite( p_suite, test_make_start_end_1, "test_make_start_end_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

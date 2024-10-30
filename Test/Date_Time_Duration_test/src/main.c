/*
   Tests for Date_Time_Duration
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#ifdef __cplusplus
extern "C" {
#endif

// test suite declarations

int
add_test_make_start_end( void );

int
add_test_make_start_dhms( void );

int
add_test_make_start_milliseconds( void );

int
add_test_make_dhms( void );

int
add_test_make_milliseconds( void );

int
add_test_clone( void );

int
add_test_deep_clone( void );

int
add_test_is_equal( void );

int
add_test_is_deep_equal( void );

int
add_test_copy( void );

int
add_test_deep_copy( void );

int
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_start( void );

int
add_test_end( void );

int
add_test_duration_milliseconds( void );

int
add_test_days_part( void );

int
add_test_hours_part( void );

int
add_test_minutes_part( void );

int
add_test_seconds_part( void );

int
add_test_milliseconds_part( void );

int
add_test_is_definite( void );

int
add_test_is_less_than( void );

int
add_test_is_less_than_or_equal( void );

int
add_test_is_greater_than( void );

int
add_test_is_greater_than_or_equal( void );

int
add_test_compare( void );

int
add_test_is_earlier_than( void );

int
add_test_is_earlier_than_or_equal( void );

int
add_test_is_later_than( void );

int
add_test_is_later_than_or_equal( void );

int
add_test_start_time_compare( void );

int
add_test_overlap( void );

int
add_test_is_overlap( void );

int
add_test_put_start( void );

int
add_test_put_end( void );

int
add_test_put_start_end( void );

int
add_test_put_start_duration_dhms( void );

int
add_test_put_start_duration_milliseconds( void );

int
add_test_put_duration_dhms( void );

int
add_test_put_duration_milliseconds( void );


int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name )
{
   // add the test to the suite

   // test_make_1
   CU_pTest p_test = CU_add_test( p_suite, name, test );

   if ( p_test == NULL )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return CUE_SUCCESS;
}

/**
   main() function for setting up and running the tests.

   Returns a CUE_SUCCESS on successful running, another
   CUnit error code on failure.

*/

int main()
{
   CU_ErrorCode result;

   // initialize the CUnit test registry
   result = CU_initialize_registry();
   if ( result != CUE_SUCCESS )
   {
      return CU_get_error();
   }

   // add tests

   add_test_make_start_end();
   add_test_make_start_dhms();
   add_test_make_start_milliseconds();
   add_test_make_dhms();
   add_test_make_milliseconds();
   add_test_clone();
   add_test_deep_clone();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_copy();
   add_test_deep_copy();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_start();
   add_test_end();
   add_test_duration_milliseconds();
   add_test_days_part();
   add_test_hours_part();
   add_test_minutes_part();
   add_test_seconds_part();
   add_test_milliseconds_part();
   add_test_is_definite();
   add_test_is_less_than();
   add_test_is_less_than_or_equal();
   add_test_is_greater_than();
   add_test_is_greater_than_or_equal();
   add_test_compare();
   add_test_is_earlier_than();
   add_test_is_earlier_than_or_equal();
   add_test_is_later_than();
   add_test_is_later_than_or_equal();
   add_test_start_time_compare();
   add_test_overlap();
   add_test_is_overlap();
   add_test_put_start();
   add_test_put_end();
   add_test_put_start_end();
   add_test_put_start_duration_dhms();
   add_test_put_start_duration_milliseconds();
   add_test_put_duration_dhms();
   add_test_put_duration_milliseconds();

   // Run all tests using the CUnit Basic interface

   // set the test mode to verbose
   CU_basic_set_mode( CU_BRM_VERBOSE );

   // run the tests
   CU_basic_run_tests();

   // do any cleanup
   CU_cleanup_registry();

   // exit with error code
   return CU_get_error();
}

#ifdef __cplusplus
}
#endif

/* End of file */


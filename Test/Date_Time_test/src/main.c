/*
   Tests for Date_Time
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
add_test_make( void );

int
add_test_make_day_of_year( void );

int
add_test_make_hour_12( void );

int
add_test_make_now( void );

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
add_test_year( void );

int
add_test_month( void );

int
add_test_day( void );

int
add_test_day_of_year( void );

int
add_test_day_of_week( void );

int
add_test_hour_24( void );

int
add_test_hour_12( void );

int
add_test_minute( void );

int
add_test_second( void );

int
add_test_millisecond( void );

int
add_test_meridiem( void );

int
add_test_difference( void );

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
add_test_put( void );

int
add_test_put_with_hour_12( void );

int
add_test_put_year( void );

int
add_test_put_month( void );

int
add_test_put_day( void );

int
add_test_put_day_of_year( void );

int
add_test_put_hour_24( void );

int
add_test_put_hour_12( void );

int
add_test_put_minute( void );

int
add_test_put_second( void );

int
add_test_put_millisecond( void );

int
add_test_add_delta_milliseconds( void );


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

   add_test_make();
   add_test_make_day_of_year();
   add_test_make_hour_12();
   add_test_make_now();
   add_test_clone();
   add_test_deep_clone();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_copy();
   add_test_deep_copy();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_year();
   add_test_month();
   add_test_day();
   add_test_day_of_year();
   add_test_day_of_week();
   add_test_hour_24();
   add_test_hour_12();
   add_test_minute();
   add_test_second();
   add_test_millisecond();
   add_test_meridiem();
   add_test_difference();
   add_test_is_less_than();
   add_test_is_less_than_or_equal();
   add_test_is_greater_than();
   add_test_is_greater_than_or_equal();
   add_test_compare();
   add_test_put();
   add_test_put_with_hour_12();
   add_test_put_year();
   add_test_put_month();
   add_test_put_day();
   add_test_put_day_of_year();
   add_test_put_hour_24();
   add_test_put_hour_12();
   add_test_put_minute();
   add_test_put_second();
   add_test_put_millisecond();
   add_test_add_delta_milliseconds();

   // Run all tests using the CUnit Basic interface

   // set the test mode to verbose
   CU_basic_set_mode(CU_BRM_VERBOSE);

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


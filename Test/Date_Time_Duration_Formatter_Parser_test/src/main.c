/*
   Tests for Date_Time_Duration_Formatter_Parser
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "base.h"

#ifdef __cplusplus
extern "C" {
#endif

// test suite declarations

int
add_test_make_start_end( void );

int
add_test_make_start_end_cstring( void );

int
add_test_make_start_end_time( void );

int
add_test_make_start_end_time_cstring( void );

int
add_test_make_start_duration( void );

int
add_test_make_start_duration_cstring( void );

int
add_test_make_duration( void );

int
add_test_make_duration_cstring( void );

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
add_test_start_format_string( void );

int
add_test_end_format_string( void );

int
add_test_duration_format_string( void );

int
add_test_separator( void );

int
add_test_is_start_end( void );

int
add_test_is_time_duration( void );

int
add_test_is_fixed( void );

int
add_test_last_error( void );

int
add_test_base_century( void );

int
add_test_put_start_format_string( void );

int
add_test_put_start_format_string_cstring( void );

int
add_test_put_end_format_string( void );

int
add_test_put_end_format_string_cstring( void );

int
add_test_put_duration_format_string( void );

int
add_test_put_duration_format_string_cstring( void );

int
add_test_put_separator( void );

int
add_test_put_separator_cstring( void );

int
add_test_put_is_time_duration( void );

int
add_test_put_base_century( void );

int
add_test_corresponds( void );

int
add_test_corresponds_cstring( void );

int
add_test_parse( void );

int
add_test_parse_cstring( void );

int
add_test_format( void );

int
add_test_format_cstring( void );


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

   // enable core dump on failure
   core_dump_enable();
   
   // initialize the CUnit test registry
   result = CU_initialize_registry();
   if ( result != CUE_SUCCESS )
   {
      return CU_get_error();
   }

   // add tests

   add_test_make_start_end();
   add_test_make_start_end_cstring();
   add_test_make_start_end_time();
   add_test_make_start_end_time_cstring();
   add_test_make_start_duration();
   add_test_make_start_duration_cstring();
   add_test_make_duration();
   add_test_make_duration_cstring();
   add_test_clone();
   add_test_deep_clone();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_copy();
   add_test_deep_copy();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_start_format_string();
   add_test_end_format_string();
   add_test_duration_format_string();
   add_test_separator();
   add_test_is_start_end();
   add_test_is_time_duration();
   add_test_is_fixed();
   add_test_last_error();
   add_test_base_century();
   add_test_put_start_format_string();
   add_test_put_start_format_string_cstring();
   add_test_put_end_format_string();
   add_test_put_end_format_string_cstring();
   add_test_put_duration_format_string();
   add_test_put_duration_format_string_cstring();
   add_test_put_separator();
   add_test_put_separator_cstring();
   add_test_put_is_time_duration();
   add_test_put_base_century();
   add_test_corresponds();
   add_test_corresponds_cstring();
   add_test_parse();
   add_test_parse_cstring();
   add_test_format();
   add_test_format_cstring();

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


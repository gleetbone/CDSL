/*
   Tests for Fft
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
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_input( void );

int
add_test_output( void );

int
add_test_set_input( void );

int
add_test_set_output( void );

int
add_test_fft( void );

int
add_test_inverse_fft( void );

int
add_test_psd( void );

int
add_test_log_psd( void );

int
add_test_phase( void );

int
add_test_phase_degrees( void );


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

   // add tests for DList_make

   add_test_make();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_input();
   add_test_output();
   add_test_set_input();
   add_test_set_output();
   add_test_fft();
   add_test_inverse_fft();
   add_test_psd();
   add_test_log_psd();
   add_test_phase();
   add_test_phase_degrees();

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


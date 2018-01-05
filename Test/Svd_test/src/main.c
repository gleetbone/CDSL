/*
   Tests for matvec
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
add_test_dispose_with_contents( void );

int
add_test_set_rotation_error( void );

int
add_test_set_singular_value_threshold( void );

int
add_test_set_input( void );

int
add_test_svd( void );

int
add_test_input( void );

int
add_test_reconstructed_input( void );

int
add_test_inverse( void );


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

   add_test_input();

   // add tests for DList_make

   add_test_make();
   add_test_dispose();
   add_test_dispose_with_contents();
   add_test_set_rotation_error();
   add_test_set_singular_value_threshold();
   add_test_set_input();
   add_test_svd();
   add_test_input();
   add_test_reconstructed_input();
   add_test_inverse();

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


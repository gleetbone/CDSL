/*
   Tests for configuration_t
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
add_test_make( void );

int
add_test_clone( void );

int
add_test_deep_clone( void );

int
add_test_copy( void );

int
add_test_deep_copy( void );

int
add_test_is_equal( void );

int
add_test_is_deep_equal( void );

int
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_put( void );

int
add_test_item( void );

int
add_test_has( void );

int
add_test_set_from_file( void );

int
add_test_superkey_has( void );

int
add_test_superkey_item( void );

int
add_test_list_items( void );

int
add_test_superkey_list_items( void );


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

   // add tests for path utilites

   add_test_make();
   add_test_clone();
   add_test_deep_clone();
   add_test_copy();
   add_test_deep_copy();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_put();
   add_test_item();
   add_test_has();
   add_test_set_from_file();
   add_test_superkey_has();
   add_test_superkey_item();
   add_test_list_items();
   add_test_superkey_list_items();
   
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


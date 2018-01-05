/*
   Tests for sequence
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
add_test_make_n( void );

int
add_test_make_from_array( void );

int
add_test_dispose( void );

int
add_test_dispose_with_contents( void );

int
add_test_item( void );

int
add_test_count( void );

int
add_test_capacity( void );

int
add_test_is_empty( void );

int
add_test_put( void );

int
add_test_replace( void );

int
add_test_replace_and_dispose( void );

int
add_test_wipe_out( void );

int
add_test_wipe_out_and_dispose( void );

int
add_test_set_count( void );

int
add_test_ensure_count( void );

int
add_test_set_capacity( void );

int
add_test_clone( void );

int
add_test_deep_clone( void );

int
add_test_as_array( void );

int
add_test_protocol( void );

int
add_test_p_clonable( void );

int
add_test_p_indexable( void );


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
   add_test_make_n();
   add_test_make_from_array();
   add_test_dispose();
   add_test_dispose_with_contents();
   add_test_item();
   add_test_count();
   add_test_capacity();
   add_test_is_empty();
   add_test_put();
   add_test_replace();
   add_test_replace_and_dispose();
   add_test_wipe_out();
   add_test_wipe_out_and_dispose();
   add_test_set_count();
   add_test_ensure_count();
   add_test_set_capacity();
   add_test_clone();
   add_test_deep_clone();
   add_test_as_array();
   add_test_protocol();
   add_test_p_clonable();
   add_test_p_indexable();


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


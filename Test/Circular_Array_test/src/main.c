/*
   Tests for Circular_Array
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
add_test_make_from_array( void );

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
add_test_item( void );

int
add_test_as_array( void );

int
add_test_count( void );

int
add_test_capacity( void );

int
add_test_is_empty( void );

int
add_test_put_first( void );

int
add_test_remove_first( void );

int
add_test_remove_first_and_dispose( void );

int
add_test_put_last( void );

int
add_test_remove_last( void );

int
add_test_remove_last_and_dispose( void );

int
add_test_replace( void );

int
add_test_replace_and_dispose( void );

int
add_test_replace_from_array( void );

int
add_test_replace_from_array_and_dispose( void );

int
add_test_wipe_out( void );

int
add_test_wipe_out_and_dispose( void );

int
add_test_set_count( void );

int
add_test_set_capacity( void );

int
add_test_ensure_count( void );

int
add_test_fill_default( void );

int
add_test_fill_default_and_dispose( void );



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
   add_test_make_from_array();   
   add_test_clone();   
   add_test_deep_clone();   
   add_test_copy();   
   add_test_deep_copy();   
   add_test_is_equal();   
   add_test_is_deep_equal(); 
   add_test_dispose();   
   add_test_deep_dispose();   
   add_test_item();  
   add_test_as_array();
   add_test_count();   
   add_test_capacity();   
   add_test_is_empty();   
   add_test_put_first();   
   add_test_remove_first();   
   add_test_remove_first_and_dispose();   
   add_test_put_last();   
   add_test_remove_last();   
   add_test_remove_last_and_dispose();   
   add_test_replace();   
   add_test_replace_and_dispose();   
   add_test_replace_from_array();   
   add_test_replace_from_array_and_dispose();   
   add_test_wipe_out();   
   add_test_wipe_out_and_dispose();   
   add_test_set_count();   
   add_test_set_capacity();   
   add_test_ensure_count();   
   add_test_fill_default();
   add_test_fill_default_and_dispose();
   
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


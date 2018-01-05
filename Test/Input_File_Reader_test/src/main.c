/*
   Tests for Input_File_Reader
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#ifdef __cplusplus
extern "C" {
#endif

// declarations

int
add_test_make( void );

int
add_test_empty( void );

int
add_test_one_line( void );

int
add_test_one_line_comment( void );

int
add_test_two_line( void );

int
add_test_three_line( void );

int
add_test_multiline( void );

int
add_test_quotes( void );


int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name )
{
   // add the test to the suite
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

int main(int argc, char *argv[] )
{
   CU_ErrorCode result;

   // initialize the CUnit test registry
   result = CU_initialize_registry();
   if ( result != CUE_SUCCESS )
   {
      return CU_get_error();
   }

   // add tests for Input_File_Reader

   add_test_make();
   add_test_empty();
   add_test_one_line();
   add_test_one_line_comment();
   add_test_two_line();
   add_test_three_line();
   add_test_multiline();
   add_test_quotes();

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


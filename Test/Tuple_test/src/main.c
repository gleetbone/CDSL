/*
   Tests for temporenc
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
add_test_field_info( void );

int
add_test_int8( void );

int
add_test_int16( void );

int
add_test_int32( void );

int
add_test_int64( void );

int
add_test_uint8( void );

int
add_test_uint16( void );

int
add_test_uint32( void );

int
add_test_uint64( void );

int
add_test_float32( void );

int
add_test_float64( void );

int
add_test_pointer( void );

int
add_test_string( void );

int
add_test_header_byte_array( void );

int
add_test_byte_array( void );

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

   // add tests for temporenc

   add_test_make();   
   add_test_clone();   
   add_test_deep_clone();   
   add_test_copy();   
   add_test_deep_copy();
   add_test_is_equal();   
   add_test_is_deep_equal();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_field_info();
   add_test_int8();
   add_test_int16();
   add_test_int32();
   add_test_int64();
   add_test_uint8();
   add_test_uint16();
   add_test_uint32();
   add_test_uint64();
   add_test_float32();
   add_test_float64();
   add_test_pointer();
   add_test_string();
   add_test_header_byte_array();
   add_test_byte_array();
  
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


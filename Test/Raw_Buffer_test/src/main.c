/*
   Tests for raw_buffer_t
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
add_test_make_from_pointer( void );

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
add_test_subcopy( void );

int
add_test_clear( void );

int
add_test_append( void );

int
add_test_resize( void );

int
add_test_base( void );

int
add_test_count( void );

int
add_test_read_char( void );

int
add_test_read_uint8( void );

int
add_test_read_uint16( void );

int
add_test_read_uint32( void );

int
add_test_read_uint64( void );

int
add_test_read_int8( void );

int
add_test_read_int16( void );

int
add_test_read_int32( void );

int
add_test_read_int64( void );

int
add_test_read_float32( void );

int
add_test_read_float64( void );

int
add_test_read_pointer( void );

int
add_test_put_char( void );

int
add_test_put_uint8( void );

int
add_test_put_uint16( void );

int
add_test_put_uint32( void );

int
add_test_put_uint64( void );

int
add_test_put_int8( void );

int
add_test_put_int16( void );

int
add_test_put_int32( void );

int
add_test_put_int64( void );

int
add_test_put_float32( void );

int
add_test_put_float64( void );

int
add_test_put_pointer( void );

int
add_test_read_string_zero_terminated( void );

int
add_test_read_cstring_zero_terminated( void );

int
add_test_read_string( void );

int
add_test_read_cstring( void );

int
add_test_put_string( void );

int
add_test_put_cstring( void );

int
add_test_to_hex_string( void );

int
add_test_to_hex_cstring( void );

int
add_test_from_hex_string( void );

int
add_test_from_hex_cstring( void );

int
add_test_to_display_string( void );


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
   add_test_make_from_pointer();
   add_test_clone();
   add_test_deep_clone();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_copy();
   add_test_deep_copy();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_subcopy();
   add_test_clear();
   add_test_append();
   add_test_resize();
   add_test_base();
   add_test_count();
   add_test_read_char();
   add_test_read_uint8();
   add_test_read_uint16();
   add_test_read_uint32();
   add_test_read_uint64();
   add_test_read_int8();
   add_test_read_int16();
   add_test_read_int32();
   add_test_read_int64();
   add_test_read_float32();
   add_test_read_float64();
   add_test_read_pointer();
   add_test_put_char();
   add_test_put_uint8();
   add_test_put_uint16();
   add_test_put_uint32();
   add_test_put_uint64();
   add_test_put_int8();
   add_test_put_int16();
   add_test_put_int32();
   add_test_put_int64();
   add_test_put_float32();
   add_test_put_float64();
   add_test_put_pointer();
   add_test_read_string_zero_terminated();
   add_test_read_cstring_zero_terminated();
   add_test_read_string();
   add_test_read_cstring();
   add_test_put_string();
   add_test_put_cstring();
   add_test_to_hex_string();
   add_test_to_hex_cstring();
   add_test_from_hex_string();
   add_test_from_hex_cstring();
   add_test_to_display_string();
   
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


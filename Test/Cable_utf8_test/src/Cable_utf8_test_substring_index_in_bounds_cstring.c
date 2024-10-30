/**
 @file Cable_utf8_test_substring_index_in_bounds_cstring.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Cable_utf8"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Cable_utf8.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Cable_utf8.h"

cable_utf8_t *
cable_utf8_make_capacity( int32_t capacity );

cable_utf8_t *
cable_utf8_make_capacity_from_cstring( char_t *str, int32_t capacity );

int32_t
cable_utf8_capacity( cable_utf8_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_substring_index_in_bounds_cstring_1
*/

void test_substring_index_in_bounds_cstring_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "a", 0, 3 ) == 0 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "ab", 0, 3 ) == 0 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "bc", 0, 3 ) == 1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 0, 3 ) == 2 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "d", 0, 3 ) == 3 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "ac", 0, 3 ) == -1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "bd", 0, 3 ) == -1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "A", 0, 3 ) == -1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 1, 3 ) == 2 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 2, 3 ) == 2 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 3, 3 ) == -1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_substring_index_in_bounds_cstring_2
*/

void test_substring_index_in_bounds_cstring_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "a", 0, 9 ) == 0 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "ab", 0, 9 ) == 0 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "bc", 0, 9 ) == 1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 0, 9 ) == 2 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "d", 0, 9 ) == 3 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "de", 0, 9 ) == 3 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "ef", 0, 9 ) == 4 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "hi", 0, 9 ) == 7 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "ij", 0, 9 ) == 8 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "j", 0, 9 ) == 9 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "ac", 0, 9 ) == -1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "bd", 0, 9 ) == -1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "A", 0, 9 ) == -1 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 1, 9 ) == 2 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 2, 9 ) == 2 );
   CU_ASSERT( cable_utf8_substring_index_in_bounds_cstring( cable, "cd", 3, 9 ) == -1 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_substring_index_in_bounds_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring_index_in_bounds_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_index_in_bounds_cstring_1
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_1, "test_substring_index_in_bounds_cstring_1" );

   // test_substring_index_in_bounds_cstring_2
   add_test_to_suite( p_suite, test_substring_index_in_bounds_cstring_2, "test_substring_index_in_bounds_cstring_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_test_substring_index_in_bounds.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Cable.h"

cable_t *
cable_make_capacity( int32_t capacity );

cable_t *
cable_make_capacity_from_cstring( char_t *str, int32_t capacity );

int32_t
cable_capacity( cable_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_substring_index_in_bounds_1
*/

void test_substring_index_in_bounds_1( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable1 = cable_make_from_cstring( "a" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == 0 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "ab" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == 0 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "bc" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == 2 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "d" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == 3 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "ac" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == -1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "bd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == -1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "A" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 3 ) == -1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 1, 3 ) == 2 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 2, 3 ) == 2 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 3, 3 ) == -1 );
   cable_dispose( &cable1 );

   cable_dispose( &cable );

   return;
}

/**
   test_substring_index_in_bounds_2
*/

void test_substring_index_in_bounds_2( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable1 = cable_make_from_cstring( "a" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 0 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "ab" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 0 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "bc" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 2 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "d" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 3 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "de" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 3 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "ef" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 4 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "h" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 7 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "hi" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 7 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "ij" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 8 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "j" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == 9 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "ac" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == -1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "bd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == -1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "A" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 0, 9 ) == -1 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 1, 9 ) == 2 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cd" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 2, 9 ) == 2 );
   cable_dispose( &cable1 );

   cable1 = cable_make_from_cstring( "cde" );
   CU_ASSERT( cable_substring_index_in_bounds( cable, cable1, 3, 9 ) == -1 );
   cable_dispose( &cable1 );

   cable_dispose( &cable );

   return;
}

int
add_test_substring_index_in_bounds( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring_index_in_bounds", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_index_in_bounds_1
   add_test_to_suite( p_suite, test_substring_index_in_bounds_1, "test_substring_index_in_bounds_1" );

   // test_substring_index_in_bounds_2
   add_test_to_suite( p_suite, test_substring_index_in_bounds_2, "test_substring_index_in_bounds_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


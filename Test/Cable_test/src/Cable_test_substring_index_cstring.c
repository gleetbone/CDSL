/**
 @file Cable_test_substring_index_cstring.c
 @author Greg Lee
 @version 1.0.0
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
   test_substring_index_cstring_1
*/

void test_substring_index_cstring_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_substring_index_cstring( cable, "a" ) == 0 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ab" ) == 0 );
   CU_ASSERT( cable_substring_index_cstring( cable, "bc" ) == 1 );
   CU_ASSERT( cable_substring_index_cstring( cable, "cd" ) == 2 );
   CU_ASSERT( cable_substring_index_cstring( cable, "d" ) == 3 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ac" ) == -1 );
   CU_ASSERT( cable_substring_index_cstring( cable, "bd" ) == -1 );
   CU_ASSERT( cable_substring_index_cstring( cable, "A" ) == -1 );

   cable_dispose( cable );

   return;
}

/**
   test_substring_index_cstring_2
*/

void test_substring_index_cstring_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_substring_index_cstring( cable, "a" ) == 0 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ab" ) == 0 );
   CU_ASSERT( cable_substring_index_cstring( cable, "bc" ) == 1 );
   CU_ASSERT( cable_substring_index_cstring( cable, "cd" ) == 2 );
   CU_ASSERT( cable_substring_index_cstring( cable, "d" ) == 3 );
   CU_ASSERT( cable_substring_index_cstring( cable, "de" ) == 3 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ef" ) == 4 );
   CU_ASSERT( cable_substring_index_cstring( cable, "gh" ) == 6 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ghi" ) == 6 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ij" ) == 8 );
   CU_ASSERT( cable_substring_index_cstring( cable, "j" ) == 9 );
   CU_ASSERT( cable_substring_index_cstring( cable, "ac" ) == -1 );
   CU_ASSERT( cable_substring_index_cstring( cable, "bd" ) == -1 );
   CU_ASSERT( cable_substring_index_cstring( cable, "A" ) == -1 );

   cable_dispose( cable );

   return;
}

int
add_test_substring_index_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_substring_index_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_substring_index_cstring_1
   add_test_to_suite( p_suite, test_substring_index_cstring_1, "test_substring_index_cstring_1" );

   // test_substring_index_cstring_2
   add_test_to_suite( p_suite, test_substring_index_cstring_2, "test_substring_index_cstring_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


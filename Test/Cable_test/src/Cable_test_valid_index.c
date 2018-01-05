/**
 @file Cable_test_valid_index.c
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
   test_valid_index_1
*/

void test_valid_index_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_valid_index( cable, 0 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 1 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 2 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 3 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 4 ) == 0 );

   cable_dispose( cable );

   return;
}

/**
   test_valid_index_2
*/

void test_valid_index_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_valid_index( cable, 0 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 1 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 2 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 3 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 4 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 5 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 6 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 7 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 8 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 9 ) == 1 );
   CU_ASSERT( cable_valid_index( cable, 10 ) == 0 );

   cable_dispose( cable );

   return;
}

int
add_test_valid_index( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_valid_index", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_valid_index_1
   add_test_to_suite( p_suite, test_valid_index_1, "test_valid_index_1" );

   // test_valid_index_2
   add_test_to_suite( p_suite, test_valid_index_2, "test_valid_index_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


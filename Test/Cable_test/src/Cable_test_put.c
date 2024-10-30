/**
 @file Cable_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_count( cable ) == 4 );
   CU_ASSERT( cable_is_empty( cable ) == 0 );

   cable_put( cable, 'w', 0 );
   cable_put( cable, 'x', 1 );
   cable_put( cable, 'y', 2 );
   cable_put( cable, 'z', 3 );

   CU_ASSERT( cable_item( cable, 0 ) == 'w' );
   CU_ASSERT( cable_item( cable, 1 ) == 'x' );
   CU_ASSERT( cable_item( cable, 2 ) == 'y' );
   CU_ASSERT( cable_item( cable, 3 ) == 'z' );

   cable_dispose( &cable );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_count( cable ) == 10 );
   CU_ASSERT( cable_is_empty( cable ) == 0 );

   cable_put( cable, 'w', 0 );
   cable_put( cable, 'x', 1 );
   cable_put( cable, 'y', 2 );
   cable_put( cable, 'z', 3 );
   cable_put( cable, 'A', 4 );
   cable_put( cable, 'B', 5 );
   cable_put( cable, 'C', 6 );
   cable_put( cable, 'D', 7 );
   cable_put( cable, 'E', 8 );
   cable_put( cable, 'F', 9 );

   CU_ASSERT( cable_item( cable, 0 ) == 'w' );
   CU_ASSERT( cable_item( cable, 1 ) == 'x' );
   CU_ASSERT( cable_item( cable, 2 ) == 'y' );
   CU_ASSERT( cable_item( cable, 3 ) == 'z' );
   CU_ASSERT( cable_item( cable, 4 ) == 'A' );
   CU_ASSERT( cable_item( cable, 5 ) == 'B' );
   CU_ASSERT( cable_item( cable, 6 ) == 'C' );
   CU_ASSERT( cable_item( cable, 7 ) == 'D' );
   CU_ASSERT( cable_item( cable, 8 ) == 'E' );
   CU_ASSERT( cable_item( cable, 9 ) == 'F' );

   cable_dispose( &cable );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


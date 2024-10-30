/**
 @file Cable_test_as_lower.c
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
   test_as_lower_1
*/

void test_as_lower_1( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "ABCD" );

   CU_ASSERT( cable != NULL );

   cable1 = cable_as_lower( cable, 0, 0 );

   CU_ASSERT( cable1 != NULL );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "a" ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_as_lower( cable, 2, 3 );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "cd" ) == 1 );
   cable_dispose( &cable1 );

   cable_dispose( &cable );

   return;
}

/**
   test_as_lower_2
*/

void test_as_lower_2( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "ABCDEFGHIJ", 4 );

   CU_ASSERT( cable != NULL );

   cable1 = cable_as_lower( cable, 0, 0 );

   CU_ASSERT( cable1 != NULL );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "a" ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_as_lower( cable, 2, 3 );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "cd" ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_as_lower( cable, 3, 5 );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "def" ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_as_lower( cable, 7, 9 );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "hij" ) == 1 );
   cable_dispose( &cable1 );

   cable1 = cable_as_lower( cable, 0, 9 );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_equal_cstring( cable1, "abcdefghij" ) == 1 );
   cable_dispose( &cable1 );

   cable_dispose( &cable );

   return;
}

int
add_test_as_lower( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_lower", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_lower_1
   add_test_to_suite( p_suite, test_as_lower_1, "test_as_lower_1" );

   // test_as_lower_2
   add_test_to_suite( p_suite, test_as_lower_2, "test_as_lower_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


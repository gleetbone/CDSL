/**
 @file Cable_utf8_test_is_empty.c
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

int32_t
cable_utf8_capacity( cable_utf8_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity( 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 0 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 1 );
   CU_ASSERT( cable_utf8_capacity( cable ) == 4 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_is_empty_2
*/

void test_is_empty_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcde" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 5 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_is_empty( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_empty", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_empty_1
   add_test_to_suite( p_suite, test_is_empty_1, "test_is_empty_1" );

   // test_is_empty_2
   add_test_to_suite( p_suite, test_is_empty_2, "test_is_empty_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


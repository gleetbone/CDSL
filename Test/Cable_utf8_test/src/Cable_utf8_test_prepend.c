/**
 @file Cable_utf8_test_prepend.c
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
   test_prepend_1
*/

void test_prepend_1( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );
   cable1 = cable_utf8_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_utf8_prepend( cable, cable1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "xabcd" ) == 1 );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "x" ) == 1 );

   cable_utf8_dispose( &cable );
   cable_utf8_dispose( &cable1 );

   return;
}

/**
   test_prepend_2
*/

void test_prepend_2( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );
   cable1 = cable_utf8_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_utf8_prepend( cable, cable1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "xyzabcd" ) == 1 );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_utf8_dispose( &cable );
   cable_utf8_dispose( &cable1 );

   return;
}

/**
   test_prepend_3
*/

void test_prepend_3( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_utf8_make_capacity_from_cstring( "x", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_utf8_prepend( cable, cable1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "xabcdefghij" ) == 1 );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "x" ) == 1 );

   cable_utf8_dispose( &cable );
   cable_utf8_dispose( &cable1 );

   return;
}

/**
   test_prepend_4
*/

void test_prepend_4( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_utf8_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_utf8_prepend( cable, cable1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "xyzabcdefghij" ) == 1 );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_utf8_dispose( &cable );
   cable_utf8_dispose( &cable1 );

   return;
}

int
add_test_prepend( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_prepend", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_prepend_1
   add_test_to_suite( p_suite, test_prepend_1, "test_prepend_1" );

   // test_prepend_2
   add_test_to_suite( p_suite, test_prepend_2, "test_prepend_2" );

   // test_prepend_3
   add_test_to_suite( p_suite, test_prepend_3, "test_prepend_3" );

   // test_prepend_4
   add_test_to_suite( p_suite, test_prepend_4, "test_prepend_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

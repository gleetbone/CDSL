/**
 @file Cable_utf8_test_to_lower.c
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
   test_to_lower_1
*/

void test_to_lower_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "ABCD" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 0, 0 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "aBCD" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_2
*/

void test_to_lower_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "ABCD" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 0, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abCD" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_3
*/

void test_to_lower_3( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "ABCD" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 1, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "AbCD" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_4
*/

void test_to_lower_4( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "ABCD" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 2, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABcd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_5
*/

void test_to_lower_5( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "ABCD" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 3, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABCd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_6
*/

void test_to_lower_6( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "ABCDEFGHIJ", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 4, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABCDeFGHIJ" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_7
*/

void test_to_lower_7( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "ABCDEFGHIJ", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 4, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABCDefGHIJ" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_8
*/

void test_to_lower_8( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "ABCDEFGHIJ", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 5, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABCDEfGHIJ" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_9
*/

void test_to_lower_9( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "ABCDEFGHIJ", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABCDEFghIJ" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_lower_10
*/

void test_to_lower_10( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "ABCDEFGHIJ", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_lower( cable, 7, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABCDEFGhIJ" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_to_lower( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_to_lower", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_to_lower_1
   add_test_to_suite( p_suite, test_to_lower_1, "test_to_lower_1" );

   // test_to_lower_2
   add_test_to_suite( p_suite, test_to_lower_2, "test_to_lower_2" );

   // test_to_lower_3
   add_test_to_suite( p_suite, test_to_lower_3, "test_to_lower_3" );

   // test_to_lower_4
   add_test_to_suite( p_suite, test_to_lower_4, "test_to_lower_4" );

   // test_to_lower_5
   add_test_to_suite( p_suite, test_to_lower_5, "test_to_lower_5" );

   // test_to_lower_6
   add_test_to_suite( p_suite, test_to_lower_6, "test_to_lower_6" );

   // test_to_lower_7
   add_test_to_suite( p_suite, test_to_lower_7, "test_to_lower_7" );

   // test_to_lower_8
   add_test_to_suite( p_suite, test_to_lower_8, "test_to_lower_8" );

   // test_to_lower_9
   add_test_to_suite( p_suite, test_to_lower_9, "test_to_lower_9" );

   // test_to_lower_10
   add_test_to_suite( p_suite, test_to_lower_10, "test_to_lower_10" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


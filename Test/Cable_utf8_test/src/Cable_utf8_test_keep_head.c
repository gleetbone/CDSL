/**
 @file Cable_utf8_test_keep_head.c
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
   test_keep_head_1
*/

void test_keep_head_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "a" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_2
*/

void test_keep_head_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 2 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ab" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_3
*/

void test_keep_head_3( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abc" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_4
*/

void test_keep_head_4( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_5
*/

void test_keep_head_5( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "a" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_6
*/

void test_keep_head_6( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 2 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ab" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_7
*/

void test_keep_head_7( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abc" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_keep_head_8
*/

void test_keep_head_8( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_keep_head( cable, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefg" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_keep_head( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keep_head", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keep_head_1
   add_test_to_suite( p_suite, test_keep_head_1, "test_keep_head_1" );

   // test_keep_head_2
   add_test_to_suite( p_suite, test_keep_head_2, "test_keep_head_2" );

   // test_keep_head_3
   add_test_to_suite( p_suite, test_keep_head_3, "test_keep_head_3" );

   // test_keep_head_4
   add_test_to_suite( p_suite, test_keep_head_4, "test_keep_head_4" );

   // test_keep_head_5
   add_test_to_suite( p_suite, test_keep_head_5, "test_keep_head_5" );

   // test_keep_head_6
   add_test_to_suite( p_suite, test_keep_head_6, "test_keep_head_6" );

   // test_keep_head_7
   add_test_to_suite( p_suite, test_keep_head_7, "test_keep_head_7" );

   // test_keep_head_8
   add_test_to_suite( p_suite, test_keep_head_8, "test_keep_head_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


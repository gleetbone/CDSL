/**
 @file Cable_test_replace_cstring.c
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
   test_replace_cstring_1
*/

void test_replace_cstring_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xy", 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xycd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_2
*/

void test_replace_cstring_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xyz", 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_3
*/

void test_replace_cstring_3( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "x", 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_4
*/

void test_replace_cstring_4( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xy", 1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_5
*/

void test_replace_cstring_5( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xyz", 1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_6
*/

void test_replace_cstring_6( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "x", 1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_7
*/

void test_replace_cstring_7( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xy", 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxy" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_8
*/

void test_replace_cstring_8( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xyz", 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxyz" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_9
*/

void test_replace_cstring_9( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "x", 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abx" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_10
*/

void test_replace_cstring_10( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xy", 4, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_11
*/

void test_replace_cstring_11( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xyz", 4, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyzghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_12
*/

void test_replace_cstring_12( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "x", 4, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_13
*/

void test_replace_cstring_13( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xy", 5, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyhij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_14
*/

void test_replace_cstring_14( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xyz", 5, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyzhij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_15
*/

void test_replace_cstring_15( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "x", 5, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexhij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_16
*/

void test_replace_cstring_16( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xy", 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxyij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_17
*/

void test_replace_cstring_17( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "xyz", 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxyzij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_replace_cstring_18
*/

void test_replace_cstring_18( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_cstring( cable, "x", 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxij" ) == 1 );

   cable_dispose( cable );

   return;
}

int
add_test_replace_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_cstring_1
   add_test_to_suite( p_suite, test_replace_cstring_1, "test_replace_cstring_1" );

   // test_replace_cstring_2
   add_test_to_suite( p_suite, test_replace_cstring_2, "test_replace_cstring_2" );

   // test_replace_cstring_3
   add_test_to_suite( p_suite, test_replace_cstring_3, "test_replace_cstring_3" );

   // test_replace_cstring_4
   add_test_to_suite( p_suite, test_replace_cstring_4, "test_replace_cstring_4" );

   // test_replace_cstring_5
   add_test_to_suite( p_suite, test_replace_cstring_5, "test_replace_cstring_5" );

   // test_replace_cstring_6
   add_test_to_suite( p_suite, test_replace_cstring_6, "test_replace_cstring_6" );

   // test_replace_cstring_7
   add_test_to_suite( p_suite, test_replace_cstring_7, "test_replace_cstring_7" );

   // test_replace_cstring_8
   add_test_to_suite( p_suite, test_replace_cstring_8, "test_replace_cstring_8" );

   // test_replace_cstring_9
   add_test_to_suite( p_suite, test_replace_cstring_9, "test_replace_cstring_9" );

   // test_replace_cstring_10
   add_test_to_suite( p_suite, test_replace_cstring_10, "test_replace_cstring_10" );

   // test_replace_cstring_11
   add_test_to_suite( p_suite, test_replace_cstring_11, "test_replace_cstring_11" );

   // test_replace_cstring_12
   add_test_to_suite( p_suite, test_replace_cstring_12, "test_replace_cstring_12" );

   // test_replace_cstring_13
   add_test_to_suite( p_suite, test_replace_cstring_13, "test_replace_cstring_13" );

   // test_replace_cstring_14
   add_test_to_suite( p_suite, test_replace_cstring_14, "test_replace_cstring_14" );

   // test_replace_cstring_15
   add_test_to_suite( p_suite, test_replace_cstring_15, "test_replace_cstring_15" );

   // test_replace_cstring_16
   add_test_to_suite( p_suite, test_replace_cstring_16, "test_replace_cstring_16" );

   // test_replace_cstring_17
   add_test_to_suite( p_suite, test_replace_cstring_17, "test_replace_cstring_17" );

   // test_replace_cstring_18
   add_test_to_suite( p_suite, test_replace_cstring_18, "test_replace_cstring_18" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_test_replace.c
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
   test_replace_1
*/

void test_replace_1( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xycd" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_2
*/

void test_replace_2( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzcd" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_3
*/

void test_replace_3( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xcd" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_4
*/

void test_replace_4( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyd" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_5
*/

void test_replace_5( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzd" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_6
*/

void test_replace_6( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axd" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_7
*/

void test_replace_7( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxy" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_8
*/

void test_replace_8( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_9
*/

void test_replace_9( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abx" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_10
*/

void test_replace_10( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 4, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyghij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_11
*/

void test_replace_11( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 4, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyzghij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_12
*/

void test_replace_12( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 4, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxhij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_13
*/

void test_replace_13( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 5, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyhij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_14
*/

void test_replace_14( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 5, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyzhij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_15
*/

void test_replace_15( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 5, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexhij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_16
*/

void test_replace_16( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxyij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_17
*/

void test_replace_17( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxyzij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_18
*/

void test_replace_18( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_replace_19
*/

void test_replace_19( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "vwxyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_replace( cable, cable1, 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefvwxyzij" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

int
add_test_replace( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_1
   add_test_to_suite( p_suite, test_replace_1, "test_replace_1" );

   // test_replace_2
   add_test_to_suite( p_suite, test_replace_2, "test_replace_2" );

   // test_replace_3
   add_test_to_suite( p_suite, test_replace_3, "test_replace_3" );

   // test_replace_4
   add_test_to_suite( p_suite, test_replace_4, "test_replace_4" );

   // test_replace_5
   add_test_to_suite( p_suite, test_replace_5, "test_replace_5" );

   // test_replace_6
   add_test_to_suite( p_suite, test_replace_6, "test_replace_6" );

   // test_replace_7
   add_test_to_suite( p_suite, test_replace_7, "test_replace_7" );

   // test_replace_8
   add_test_to_suite( p_suite, test_replace_8, "test_replace_8" );

   // test_replace_9
   add_test_to_suite( p_suite, test_replace_9, "test_replace_9" );

   // test_replace_10
   add_test_to_suite( p_suite, test_replace_10, "test_replace_10" );

   // test_replace_11
   add_test_to_suite( p_suite, test_replace_11, "test_replace_11" );

   // test_replace_12
   add_test_to_suite( p_suite, test_replace_12, "test_replace_12" );

   // test_replace_13
   add_test_to_suite( p_suite, test_replace_13, "test_replace_13" );

   // test_replace_14
   add_test_to_suite( p_suite, test_replace_14, "test_replace_14" );

   // test_replace_15
   add_test_to_suite( p_suite, test_replace_15, "test_replace_15" );

   // test_replace_16
   add_test_to_suite( p_suite, test_replace_16, "test_replace_16" );

   // test_replace_17
   add_test_to_suite( p_suite, test_replace_17, "test_replace_17" );

   // test_replace_18
   add_test_to_suite( p_suite, test_replace_18, "test_replace_18" );

   // test_replace_19
   add_test_to_suite( p_suite, test_replace_19, "test_replace_19" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


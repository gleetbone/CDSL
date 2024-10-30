/**
 @file Cable_test_replace_all_cstring.c
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
   test_replace_all_cstring_1
*/

void test_replace_all_cstring_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "a", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xybcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_2
*/

void test_replace_all_cstring_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "a", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzbcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_3
*/

void test_replace_all_cstring_3( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "a", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xbcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_4
*/

void test_replace_all_cstring_4( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "bc", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_5
*/

void test_replace_all_cstring_5( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "bc", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_6
*/

void test_replace_all_cstring_6( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "bc", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "axd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_4a
*/

void test_replace_all_cstring_4a( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "b", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "axcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_5a
*/

void test_replace_all_cstring_5a( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "b", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "axycd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_7
*/

void test_replace_all_cstring_7( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "d", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxy" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_8
*/

void test_replace_all_cstring_8( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "d", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxyz" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_9
*/

void test_replace_all_cstring_9( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "d", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcx" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_10
*/

void test_replace_all_cstring_10( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "xyzMxyzMMxyz" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "xyz", "a" );

   CU_ASSERT( cable_is_equal_cstring( cable, "aMaMMa" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_11
*/

void test_replace_all_cstring_11( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcMabcMMabc" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "abc", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_12
*/

void test_replace_all_cstring_12( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "aMaMMa" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "a", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_13
*/

void test_replace_all_cstring_13( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "e", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyfghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_14
*/

void test_replace_all_cstring_14( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "e", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyzfghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_15
*/

void test_replace_all_cstring_15( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "e", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxfghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_16
*/

void test_replace_all_cstring_16( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "fg", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyhij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_17
*/

void test_replace_all_cstring_17( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "fg", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyzhij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_18
*/

void test_replace_all_cstring_18( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "fg", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexhij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_16a
*/

void test_replace_all_cstring_16a( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "f", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_17a
*/

void test_replace_all_cstring_17a( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "e", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyfghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_19
*/

void test_replace_all_cstring_19( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "h", "xy" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxyij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_20
*/

void test_replace_all_cstring_20( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "h", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxyzij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_21
*/

void test_replace_all_cstring_21( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcdefghij" );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "h", "x" );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_22
*/

void test_replace_all_cstring_22( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "xyzMxyzMMxyz", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "xyz", "a" );

   CU_ASSERT( cable_is_equal_cstring( cable, "aMaMMa" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_23
*/

void test_replace_all_cstring_23( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcMabcMMabc", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "abc", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_replace_all_cstring_24
*/

void test_replace_all_cstring_24( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "aMaMMa", 4 );

   CU_ASSERT( cable != NULL );

   cable_replace_all_cstring( cable, "a", "xyz" );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( &cable );

   return;
}

int
add_test_replace_all_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_all_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_all_cstring_1
   add_test_to_suite( p_suite, test_replace_all_cstring_1, "test_replace_all_cstring_1" );

   // test_replace_all_cstring_2
   add_test_to_suite( p_suite, test_replace_all_cstring_2, "test_replace_all_cstring_2" );

   // test_replace_all_cstring_3
   add_test_to_suite( p_suite, test_replace_all_cstring_3, "test_replace_all_cstring_3" );

   // test_replace_all_cstring_4
   add_test_to_suite( p_suite, test_replace_all_cstring_4, "test_replace_all_cstring_4" );

   // test_replace_all_cstring_5
   add_test_to_suite( p_suite, test_replace_all_cstring_5, "test_replace_all_cstring_5" );

   // test_replace_all_cstring_6
   add_test_to_suite( p_suite, test_replace_all_cstring_6, "test_replace_all_cstring_6" );

   // test_replace_all_cstring_4a
   add_test_to_suite( p_suite, test_replace_all_cstring_4a, "test_replace_all_cstring_4a" );

   // test_replace_all_cstring_5a
   add_test_to_suite( p_suite, test_replace_all_cstring_5a, "test_replace_all_cstring_5a" );

   // test_replace_all_cstring_7
   add_test_to_suite( p_suite, test_replace_all_cstring_7, "test_replace_all_cstring_7" );

   // test_replace_all_cstring_8
   add_test_to_suite( p_suite, test_replace_all_cstring_8, "test_replace_all_cstring_8" );

   // test_replace_all_cstring_9
   add_test_to_suite( p_suite, test_replace_all_cstring_9, "test_replace_all_cstring_9" );

   // test_replace_all_cstring_10
   add_test_to_suite( p_suite, test_replace_all_cstring_10, "test_replace_all_cstring_10" );

   // test_replace_all_cstring_11
   add_test_to_suite( p_suite, test_replace_all_cstring_11, "test_replace_all_cstring_11" );

   // test_replace_all_cstring_12
   add_test_to_suite( p_suite, test_replace_all_cstring_12, "test_replace_all_cstring_12" );

   // test_replace_all_cstring_13
   add_test_to_suite( p_suite, test_replace_all_cstring_13, "test_replace_all_cstring_13" );

   // test_replace_all_cstring_14
   add_test_to_suite( p_suite, test_replace_all_cstring_14, "test_replace_all_cstring_14" );

   // test_replace_all_cstring_15
   add_test_to_suite( p_suite, test_replace_all_cstring_15, "test_replace_all_cstring_15" );

   // test_replace_all_cstring_16
   add_test_to_suite( p_suite, test_replace_all_cstring_16, "test_replace_all_cstring_16" );

   // test_replace_all_cstring_17
   add_test_to_suite( p_suite, test_replace_all_cstring_17, "test_replace_all_cstring_17" );

   // test_replace_all_cstring_18
   add_test_to_suite( p_suite, test_replace_all_cstring_18, "test_replace_all_cstring_18" );

   // test_replace_all_cstring_16a
   add_test_to_suite( p_suite, test_replace_all_cstring_16a, "test_replace_all_cstring_16a" );

   // test_replace_all_cstring_17a
   add_test_to_suite( p_suite, test_replace_all_cstring_17a, "test_replace_all_cstring_17a" );

   // test_replace_all_cstring_19
   add_test_to_suite( p_suite, test_replace_all_cstring_19, "test_replace_all_cstring_19" );

   // test_replace_all_cstring_20
   add_test_to_suite( p_suite, test_replace_all_cstring_20, "test_replace_all_cstring_20" );

   // test_replace_all_cstring_21
   add_test_to_suite( p_suite, test_replace_all_cstring_21, "test_replace_all_cstring_21" );

   // test_replace_all_cstring_22
   add_test_to_suite( p_suite, test_replace_all_cstring_22, "test_replace_all_cstring_22" );

   // test_replace_all_cstring_23
   add_test_to_suite( p_suite, test_replace_all_cstring_23, "test_replace_all_cstring_23" );

   // test_replace_all_cstring_24
   add_test_to_suite( p_suite, test_replace_all_cstring_24, "test_replace_all_cstring_24" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_test_replace_all.c
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
   test_replace_all_1
*/

void test_replace_all_1( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "a" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xybcd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_2
*/

void test_replace_all_2( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "a" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzbcd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_3
*/

void test_replace_all_3( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "a" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xbcd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_4
*/

void test_replace_all_4( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "bc" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_5
*/

void test_replace_all_5( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "bc" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_6
*/

void test_replace_all_6( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "bc" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_4a
*/

void test_replace_all_4a( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "b" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axcd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_5a
*/

void test_replace_all_5a( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "b" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axycd" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_7
*/

void test_replace_all_7( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "d" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxy" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_8
*/

void test_replace_all_8( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "d" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxyz" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_9
*/

void test_replace_all_9( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "d" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcx" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_10
*/

void test_replace_all_10( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "xyzMxyzMMxyz" );
   cable1 = cable_make_from_cstring( "xyz" );
   cable2 = cable_make_from_cstring( "a" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "aMaMMa" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_11
*/

void test_replace_all_11( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "abcMabcMMabc" );
   cable1 = cable_make_from_cstring( "abc" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_12
*/

void test_replace_all_12( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_from_cstring( "aMaMMa" );
   cable1 = cable_make_from_cstring( "a" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_13
*/

void test_replace_all_13( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "e" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyfghij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_14
*/

void test_replace_all_14( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "e" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyzfghij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_15
*/

void test_replace_all_15( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "e" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxfghij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_16
*/

void test_replace_all_16( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "fg" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyhij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_17
*/

void test_replace_all_17( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "fg" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyzhij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_18
*/

void test_replace_all_18( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "fg" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexhij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_16a
*/

void test_replace_all_16a( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "f" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexghij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_17a
*/

void test_replace_all_17a( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "f" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyghij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_19
*/

void test_replace_all_19( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "h" );
   cable2 = cable_make_from_cstring( "xy" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxyij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_20
*/

void test_replace_all_20( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "h" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxyzij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_21
*/

void test_replace_all_21( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_from_cstring( "h" );
   cable2 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxij" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_22
*/

void test_replace_all_22( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "xyzMxyzMMxyz", 4 );
   cable1 = cable_make_from_cstring( "xyz" );
   cable2 = cable_make_from_cstring( "a" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "aMaMMa" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_23
*/

void test_replace_all_23( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "abcMabcMMabc", 4 );
   cable1 = cable_make_from_cstring( "abc" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

/**
   test_replace_all_24
*/

void test_replace_all_24( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;
   cable_t *cable2 = NULL;

   cable = cable_make_capacity_from_cstring( "aMaMMa", 4 );
   cable1 = cable_make_from_cstring( "a" );
   cable2 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable2 != NULL );

   cable_replace_all( cable, cable1, cable2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzMxyzMMxyz" ) == 1 );

   cable_dispose( cable );
   cable_dispose( cable1 );
   cable_dispose( cable2 );

   return;
}

int
add_test_replace_all( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_all", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_all_1
   add_test_to_suite( p_suite, test_replace_all_1, "test_replace_all_1" );

   // test_replace_all_2
   add_test_to_suite( p_suite, test_replace_all_2, "test_replace_all_2" );

   // test_replace_all_3
   add_test_to_suite( p_suite, test_replace_all_3, "test_replace_all_3" );

   // test_replace_all_4
   add_test_to_suite( p_suite, test_replace_all_4, "test_replace_all_4" );

   // test_replace_all_5
   add_test_to_suite( p_suite, test_replace_all_5, "test_replace_all_5" );

   // test_replace_all_6
   add_test_to_suite( p_suite, test_replace_all_6, "test_replace_all_6" );

   // test_replace_all_4a
   add_test_to_suite( p_suite, test_replace_all_4a, "test_replace_all_4a" );

   // test_replace_all_5a
   add_test_to_suite( p_suite, test_replace_all_5a, "test_replace_all_5a" );

   // test_replace_all_7
   add_test_to_suite( p_suite, test_replace_all_7, "test_replace_all_7" );

   // test_replace_all_8
   add_test_to_suite( p_suite, test_replace_all_8, "test_replace_all_8" );

   // test_replace_all_9
   add_test_to_suite( p_suite, test_replace_all_9, "test_replace_all_9" );

   // test_replace_all_10
   add_test_to_suite( p_suite, test_replace_all_10, "test_replace_all_10" );

   // test_replace_all_11
   add_test_to_suite( p_suite, test_replace_all_11, "test_replace_all_11" );

   // test_replace_all_12
   add_test_to_suite( p_suite, test_replace_all_12, "test_replace_all_12" );

   // test_replace_all_13
   add_test_to_suite( p_suite, test_replace_all_13, "test_replace_all_13" );

   // test_replace_all_14
   add_test_to_suite( p_suite, test_replace_all_14, "test_replace_all_14" );

   // test_replace_all_15
   add_test_to_suite( p_suite, test_replace_all_15, "test_replace_all_15" );

   // test_replace_all_16
   add_test_to_suite( p_suite, test_replace_all_16, "test_replace_all_16" );

   // test_replace_all_17
   add_test_to_suite( p_suite, test_replace_all_17, "test_replace_all_17" );

   // test_replace_all_18
   add_test_to_suite( p_suite, test_replace_all_18, "test_replace_all_18" );

   // test_replace_all_16a
   add_test_to_suite( p_suite, test_replace_all_16a, "test_replace_all_16a" );

   // test_replace_all_17a
   add_test_to_suite( p_suite, test_replace_all_17a, "test_replace_all_17a" );

   // test_replace_all_19
   add_test_to_suite( p_suite, test_replace_all_19, "test_replace_all_19" );

   // test_replace_all_20
   add_test_to_suite( p_suite, test_replace_all_20, "test_replace_all_20" );

   // test_replace_all_21
   add_test_to_suite( p_suite, test_replace_all_21, "test_replace_all_21" );

   // test_replace_all_22
   add_test_to_suite( p_suite, test_replace_all_22, "test_replace_all_22" );

   // test_replace_all_23
   add_test_to_suite( p_suite, test_replace_all_23, "test_replace_all_23" );

   // test_replace_all_24
   add_test_to_suite( p_suite, test_replace_all_24, "test_replace_all_24" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


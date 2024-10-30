/**
 @file Cable_utf8_test_remove_substring.c
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
   test_remove_substring_1
*/

void test_remove_substring_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 0, 0 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "bcd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_2
*/

void test_remove_substring_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 0, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "cd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_3
*/

void test_remove_substring_3( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 1, 2 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ad" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_4
*/

void test_remove_substring_4( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 2, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ab" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_5
*/

void test_remove_substring_5( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 3, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abc" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_6
*/

void test_remove_substring_6( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 4, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdfghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_7
*/

void test_remove_substring_7( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 4, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_8
*/

void test_remove_substring_8( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 5, 6 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdehij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_9
*/

void test_remove_substring_9( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_10
*/

void test_remove_substring_10( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 7, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefgij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_11
*/

void test_remove_substring_11( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 0, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "efghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_12
*/

void test_remove_substring_12( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 3, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcfghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_13
*/

void test_remove_substring_13( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 3, 8 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcj" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_14
*/

void test_remove_substring_14( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefij" ) == 1 );

   cable_utf8_remove_substring( cable, 5, 6 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdej" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_15
*/

void test_remove_substring_15( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefij" ) == 1 );

   cable_utf8_remove_substring( cable, 5, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdeij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_16
*/

void test_remove_substring_16( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefij" ) == 1 );

   cable_utf8_remove_substring( cable, 3, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcfij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_17
*/

void test_remove_substring_17( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefij" ) == 1 );

   cable_utf8_remove_substring( cable, 6, 6 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefj" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_18
*/

void test_remove_substring_18( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 4, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdghij" ) == 1 );

   cable_utf8_remove_substring( cable, 3, 6 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcj" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_19
*/

void test_remove_substring_19( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 4, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdghij" ) == 1 );

   cable_utf8_remove_substring( cable, 3, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abchij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_remove_substring_20
*/

void test_remove_substring_20( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefgh", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_remove_substring( cable, 0, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_remove_substring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_substring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_substring_1
   add_test_to_suite( p_suite, test_remove_substring_1, "test_remove_substring_1" );

   // test_remove_substring_2
   add_test_to_suite( p_suite, test_remove_substring_2, "test_remove_substring_2" );

   // test_remove_substring_3
   add_test_to_suite( p_suite, test_remove_substring_3, "test_remove_substring_3" );

   // test_remove_substring_4
   add_test_to_suite( p_suite, test_remove_substring_4, "test_remove_substring_4" );

   // test_remove_substring_5
   add_test_to_suite( p_suite, test_remove_substring_5, "test_remove_substring_5" );

   // test_remove_substring_6
   add_test_to_suite( p_suite, test_remove_substring_6, "test_remove_substring_6" );

   // test_remove_substring_7
   add_test_to_suite( p_suite, test_remove_substring_7, "test_remove_substring_7" );

   // test_remove_substring_8
   add_test_to_suite( p_suite, test_remove_substring_8, "test_remove_substring_8" );

   // test_remove_substring_9
   add_test_to_suite( p_suite, test_remove_substring_9, "test_remove_substring_9" );

   // test_remove_substring_10
   add_test_to_suite( p_suite, test_remove_substring_10, "test_remove_substring_10" );

   // test_remove_substring_11
   add_test_to_suite( p_suite, test_remove_substring_11, "test_remove_substring_11" );

   // test_remove_substring_12
   add_test_to_suite( p_suite, test_remove_substring_12, "test_remove_substring_12" );

   // test_remove_substring_13
   add_test_to_suite( p_suite, test_remove_substring_13, "test_remove_substring_13" );

   // test_remove_substring_14
   add_test_to_suite( p_suite, test_remove_substring_14, "test_remove_substring_14" );

   // test_remove_substring_15
   add_test_to_suite( p_suite, test_remove_substring_15, "test_remove_substring_15" );

   // test_remove_substring_16
   add_test_to_suite( p_suite, test_remove_substring_16, "test_remove_substring_16" );

   // test_remove_substring_17
   add_test_to_suite( p_suite, test_remove_substring_17, "test_remove_substring_17" );

   // test_remove_substring_18
   add_test_to_suite( p_suite, test_remove_substring_18, "test_remove_substring_18" );

   // test_remove_substring_19
   add_test_to_suite( p_suite, test_remove_substring_19, "test_remove_substring_19" );

   // test_remove_substring_20
   add_test_to_suite( p_suite, test_remove_substring_20, "test_remove_substring_20" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_test_insert_cstring.c
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
   test_insert_cstring_1
*/

void test_insert_cstring_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xabcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_2
*/

void test_insert_cstring_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axbcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_3
*/

void test_insert_cstring_3( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_4
*/

void test_insert_cstring_4( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_5
*/

void test_insert_cstring_5( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzabcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_6
*/

void test_insert_cstring_6( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzbcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_7
*/

void test_insert_cstring_7( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxyzcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_8
*/

void test_insert_cstring_8( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxyzd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_9
*/

void test_insert_cstring_9( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xabcdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_10
*/

void test_insert_cstring_10( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axbcdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_11
*/

void test_insert_cstring_11( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxcdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_12
*/

void test_insert_cstring_12( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "x", 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_13
*/

void test_insert_cstring_13( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzabcdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_14
*/

void test_insert_cstring_14( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzbcdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_15
*/

void test_insert_cstring_15( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxyzcdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_16
*/

void test_insert_cstring_16( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxyzdefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_17
*/

void test_insert_cstring_17( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 4 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyzefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_18
*/

void test_insert_cstring_18( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyzfghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_19
*/

void test_insert_cstring_19( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxyzghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_20
*/

void test_insert_cstring_20( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxyzhij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_21
*/

void test_insert_cstring_21( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 8 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefghxyzij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_22
*/

void test_insert_cstring_22( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "xyz", 9 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefghixyzj" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_23
*/

void test_insert_cstring_23( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity( 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "abcde", 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcde" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_24
*/

void test_insert_cstring_24( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity( 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "abcde", 0 );
   cable_insert_cstring( cable, "abcd", 4 );
   cable_insert_cstring( cable, "abcdefg", 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdaabcdefgbcde" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_25
*/

void test_insert_cstring_25( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity( 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "abc", 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abc" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_cstring_26
*/

void test_insert_cstring_26( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity( 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_cstring( cable, "abcdefgh", 0 );

   cable_remove_substring( cable, 3, 4 );

   cable_insert_cstring( cable, "x", 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcfgxh" ) == 1 );

   cable_dispose( cable );

   return;
}

int
add_test_insert_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_insert_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_insert_cstring_1
   add_test_to_suite( p_suite, test_insert_cstring_1, "test_insert_cstring_1" );

   // test_insert_cstring_2
   add_test_to_suite( p_suite, test_insert_cstring_2, "test_insert_cstring_2" );

   // test_insert_cstring_3
   add_test_to_suite( p_suite, test_insert_cstring_3, "test_insert_cstring_3" );

   // test_insert_cstring_4
   add_test_to_suite( p_suite, test_insert_cstring_4, "test_insert_cstring_4" );

   // test_insert_cstring_5
   add_test_to_suite( p_suite, test_insert_cstring_5, "test_insert_cstring_5" );

   // test_insert_cstring_6
   add_test_to_suite( p_suite, test_insert_cstring_6, "test_insert_cstring_6" );

   // test_insert_cstring_7
   add_test_to_suite( p_suite, test_insert_cstring_7, "test_insert_cstring_7" );

   // test_insert_cstring_8
   add_test_to_suite( p_suite, test_insert_cstring_8, "test_insert_cstring_8" );

   // test_insert_cstring_9
   add_test_to_suite( p_suite, test_insert_cstring_9, "test_insert_cstring_9" );

   // test_insert_cstring_10
   add_test_to_suite( p_suite, test_insert_cstring_10, "test_insert_cstring_10" );

   // test_insert_cstring_11
   add_test_to_suite( p_suite, test_insert_cstring_11, "test_insert_cstring_11" );

   // test_insert_cstring_12
   add_test_to_suite( p_suite, test_insert_cstring_12, "test_insert_cstring_12" );

   // test_insert_cstring_13
   add_test_to_suite( p_suite, test_insert_cstring_13, "test_insert_cstring_13" );

   // test_insert_cstring_14
   add_test_to_suite( p_suite, test_insert_cstring_14, "test_insert_cstring_14" );

   // test_insert_cstring_15
   add_test_to_suite( p_suite, test_insert_cstring_15, "test_insert_cstring_15" );

   // test_insert_cstring_16
   add_test_to_suite( p_suite, test_insert_cstring_16, "test_insert_cstring_16" );

   // test_insert_cstring_17
   add_test_to_suite( p_suite, test_insert_cstring_17, "test_insert_cstring_17" );

   // test_insert_cstring_18
   add_test_to_suite( p_suite, test_insert_cstring_18, "test_insert_cstring_18" );

   // test_insert_cstring_19
   add_test_to_suite( p_suite, test_insert_cstring_19, "test_insert_cstring_19" );

   // test_insert_cstring_20
   add_test_to_suite( p_suite, test_insert_cstring_20, "test_insert_cstring_20" );

   // test_insert_cstring_21
   add_test_to_suite( p_suite, test_insert_cstring_21, "test_insert_cstring_21" );

   // test_insert_cstring_22
   add_test_to_suite( p_suite, test_insert_cstring_22, "test_insert_cstring_22" );

   // test_insert_cstring_23
   add_test_to_suite( p_suite, test_insert_cstring_23, "test_insert_cstring_23" );

   // test_insert_cstring_24
   add_test_to_suite( p_suite, test_insert_cstring_24, "test_insert_cstring_24" );

   // test_insert_cstring_25
   add_test_to_suite( p_suite, test_insert_cstring_25, "test_insert_cstring_25" );

   // test_insert_cstring_26
   add_test_to_suite( p_suite, test_insert_cstring_26, "test_insert_cstring_26" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


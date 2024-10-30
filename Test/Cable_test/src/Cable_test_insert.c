/**
 @file Cable_test_insert.c
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
   test_insert_1
*/

void test_insert_1( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xabcd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_2
*/

void test_insert_2( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axbcd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_3
*/

void test_insert_3( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxcd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_4
*/

void test_insert_4( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "x" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_5
*/

void test_insert_5( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzabcd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_6
*/

void test_insert_6( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzbcd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_7
*/

void test_insert_7( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxyzcd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_8
*/

void test_insert_8( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = cable_make_from_cstring( "xyz" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxyzd" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_9
*/

void test_insert_9( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "x", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xabcdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_10
*/

void test_insert_10( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "x", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axbcdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_11
*/

void test_insert_11( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "x", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxcdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_12
*/

void test_insert_12( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "x", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "x" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_13
*/

void test_insert_13( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xyzabcdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_14
*/

void test_insert_14( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axyzbcdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_15
*/

void test_insert_15( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxyzcdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_16
*/

void test_insert_16( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxyzdefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_17
*/

void test_insert_17( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 4 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxyzefghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_18
*/

void test_insert_18( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexyzfghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_19
*/

void test_insert_19( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxyzghij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_20
*/

void test_insert_20( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxyzhij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_21
*/

void test_insert_21( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 8 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefghxyzij" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

/**
   test_insert_22
*/

void test_insert_22( void )
{
   cable_t *cable = NULL;
   cable_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = cable_make_capacity_from_cstring( "xyz", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );

   cable_insert( cable, cable1, 9 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefghixyzj" ) == 1 );
   CU_ASSERT( cable_is_equal_cstring( cable1, "xyz" ) == 1 );

   cable_dispose( &cable );
   cable_dispose( &cable1 );

   return;
}

int
add_test_insert( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_insert", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_insert_1
   add_test_to_suite( p_suite, test_insert_1, "test_insert_1" );

   // test_insert_2
   add_test_to_suite( p_suite, test_insert_2, "test_insert_2" );

   // test_insert_3
   add_test_to_suite( p_suite, test_insert_3, "test_insert_3" );

   // test_insert_4
   add_test_to_suite( p_suite, test_insert_4, "test_insert_4" );

   // test_insert_5
   add_test_to_suite( p_suite, test_insert_5, "test_insert_5" );

   // test_insert_6
   add_test_to_suite( p_suite, test_insert_6, "test_insert_6" );

   // test_insert_7
   add_test_to_suite( p_suite, test_insert_7, "test_insert_7" );

   // test_insert_8
   add_test_to_suite( p_suite, test_insert_8, "test_insert_8" );

   // test_insert_9
   add_test_to_suite( p_suite, test_insert_9, "test_insert_9" );

   // test_insert_10
   add_test_to_suite( p_suite, test_insert_10, "test_insert_10" );

   // test_insert_11
   add_test_to_suite( p_suite, test_insert_11, "test_insert_11" );

   // test_insert_12
   add_test_to_suite( p_suite, test_insert_12, "test_insert_12" );

   // test_insert_13
   add_test_to_suite( p_suite, test_insert_13, "test_insert_13" );

   // test_insert_14
   add_test_to_suite( p_suite, test_insert_14, "test_insert_14" );

   // test_insert_15
   add_test_to_suite( p_suite, test_insert_15, "test_insert_15" );

   // test_insert_16
   add_test_to_suite( p_suite, test_insert_16, "test_insert_16" );

   // test_insert_17
   add_test_to_suite( p_suite, test_insert_17, "test_insert_17" );

   // test_insert_18
   add_test_to_suite( p_suite, test_insert_18, "test_insert_18" );

   // test_insert_19
   add_test_to_suite( p_suite, test_insert_19, "test_insert_19" );

   // test_insert_20
   add_test_to_suite( p_suite, test_insert_20, "test_insert_20" );

   // test_insert_21
   add_test_to_suite( p_suite, test_insert_21, "test_insert_21" );

   // test_insert_22
   add_test_to_suite( p_suite, test_insert_22, "test_insert_22" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


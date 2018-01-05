/**
 @file Cable_test_insert_character.c
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
   test_insert_character_1
*/

void test_insert_character_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "xabcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_2
*/

void test_insert_character_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "axbcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_3
*/

void test_insert_character_3( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 2 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abxcd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_4
*/

void test_insert_character_4( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcxd" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_5
*/

void test_insert_character_5( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 4 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdxefghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_6
*/

void test_insert_character_6( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdexfghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_7
*/

void test_insert_character_7( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 6 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefxghij" ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_insert_character_8
*/

void test_insert_character_8( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_insert_character( cable, 'x', 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgxhij" ) == 1 );

   cable_dispose( cable );

   return;
}

int
add_test_insert_character( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_insert_character", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_insert_character_1
   add_test_to_suite( p_suite, test_insert_character_1, "test_insert_character_1" );

   // test_insert_character_2
   add_test_to_suite( p_suite, test_insert_character_2, "test_insert_character_2" );

   // test_insert_character_3
   add_test_to_suite( p_suite, test_insert_character_3, "test_insert_character_3" );

   // test_insert_character_4
   add_test_to_suite( p_suite, test_insert_character_4, "test_insert_character_4" );

   // test_insert_character_5
   add_test_to_suite( p_suite, test_insert_character_5, "test_insert_character_5" );

   // test_insert_character_6
   add_test_to_suite( p_suite, test_insert_character_6, "test_insert_character_6" );

   // test_insert_character_7
   add_test_to_suite( p_suite, test_insert_character_7, "test_insert_character_7" );

   // test_insert_character_8
   add_test_to_suite( p_suite, test_insert_character_8, "test_insert_character_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_test_to_upper.c
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

/**
   Additional "hidden" API functions
   Include these function prototypes in your C file if you wish to use them.
   These functions are used for testing.
*/

/**
   cable_make_capacity

   Create and initialize a cable_t instance.
   Content will be the empty cable and the capacity of each node will be "capacity".

   @return pointer to the new data structure
*/
cable_t *
cable_make_capacity( int32_t capacity );

/**
   cable_make_capacity_from_cstring

   Create and initialize a cable_t instance.
   Content will be from other and the capacity of each node will be "capacity".

   @param str the cstring to copy from
   @param capacity the new cable's node capacity
   @return pointer to the new data structure
*/
cable_t *
cable_make_capacity_from_cstring( char_t *str, int32_t capacity );

/**
   cable_capacity

   Returns the number of available characters in cable nodes.

   @param cable the cable_t instance
   @return number of characters available for storage in cable
*/
int32_t
cable_capacity( cable_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_to_upper_1
*/

void test_to_upper_1( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 0, 0 );

   CU_ASSERT( cable_is_equal_cstring( cable, "Abcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_2
*/

void test_to_upper_2( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 0, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "ABcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_3
*/

void test_to_upper_3( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 1, 1 );

   CU_ASSERT( cable_is_equal_cstring( cable, "aBcd" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_4
*/

void test_to_upper_4( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 2, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abCD" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_5
*/

void test_to_upper_5( void )
{
   cable_t *cable = NULL;

   cable = cable_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 3, 3 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcD" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_6
*/

void test_to_upper_6( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 4, 4 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdEfghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_7
*/

void test_to_upper_7( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 4, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdEFghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_8
*/

void test_to_upper_8( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 5, 5 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdeFghij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_9
*/

void test_to_upper_9( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 6, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefGHij" ) == 1 );

   cable_dispose( &cable );

   return;
}

/**
   test_to_upper_10
*/

void test_to_upper_10( void )
{
   cable_t *cable = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_to_upper( cable, 7, 7 );

   CU_ASSERT( cable_is_equal_cstring( cable, "abcdefgHij" ) == 1 );

   cable_dispose( &cable );

   return;
}

int
add_test_to_upper( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_to_upper", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_to_upper_1
   add_test_to_suite( p_suite, test_to_upper_1, "test_to_upper_1" );

   // test_to_upper_2
   add_test_to_suite( p_suite, test_to_upper_2, "test_to_upper_2" );

   // test_to_upper_3
   add_test_to_suite( p_suite, test_to_upper_3, "test_to_upper_3" );

   // test_to_upper_4
   add_test_to_suite( p_suite, test_to_upper_4, "test_to_upper_4" );

   // test_to_upper_5
   add_test_to_suite( p_suite, test_to_upper_5, "test_to_upper_5" );

   // test_to_upper_6
   add_test_to_suite( p_suite, test_to_upper_6, "test_to_upper_6" );

   // test_to_upper_7
   add_test_to_suite( p_suite, test_to_upper_7, "test_to_upper_7" );

   // test_to_upper_8
   add_test_to_suite( p_suite, test_to_upper_8, "test_to_upper_8" );

   // test_to_upper_9
   add_test_to_suite( p_suite, test_to_upper_9, "test_to_upper_9" );

   // test_to_upper_10
   add_test_to_suite( p_suite, test_to_upper_10, "test_to_upper_10" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


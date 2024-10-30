/**
 @file Cable_utf8_test_to_upper.c
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

/**
   Additional "hidden" API functions
   Include these function prototypes in your C file if you wish to use them.
   These functions are used for testing.
*/

/**
   cable_utf8_make_capacity

   Create and initialize a cable_utf8_t instance.
   Content will be the empty cable and the capacity of each node will be "capacity".

   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make_capacity( int32_t capacity );

/**
   cable_utf8_make_capacity_from_cstring

   Create and initialize a cable_utf8_t instance.
   Content will be from other and the capacity of each node will be "capacity".

   @param str the cstring to copy from
   @param capacity the new cable's node capacity
   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make_capacity_from_cstring( char_t *str, int32_t capacity );

/**
   cable_utf8_capacity

   Returns the number of available characters in cable nodes.

   @param cable the cable_utf8_t instance
   @return number of characters available for storage in cable
*/
int32_t
cable_utf8_capacity( cable_utf8_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_to_upper_1
*/

void test_to_upper_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 0, 0 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "Abcd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_2
*/

void test_to_upper_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 0, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "ABcd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_3
*/

void test_to_upper_3( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 1, 1 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "aBcd" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_4
*/

void test_to_upper_4( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 2, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abCD" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_5
*/

void test_to_upper_5( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 3, 3 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcD" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_6
*/

void test_to_upper_6( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 4, 4 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdEfghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_7
*/

void test_to_upper_7( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 4, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdEFghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_8
*/

void test_to_upper_8( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 5, 5 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdeFghij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_9
*/

void test_to_upper_9( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 6, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefGHij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_10
*/

void test_to_upper_10( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 7, 7 );

   CU_ASSERT( cable_utf8_is_equal_cstring( cable, "abcdefgHij" ) == 1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_11
*/

void test_to_upper_11( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[16] = {0};
   char_t *cp = NULL;

   s[0] = 0xC3;
   s[1] = 0x9f;
   s[2] = 0xC3;
   s[3] = 0x9F;
   s[4] = 0xC3;
   s[5] = 0x9f;

   cable = cable_utf8_make_capacity_from_cstring( s, 4 );
   CU_ASSERT( cable_utf8_count( cable ) == 3 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 0, 2 );
   CU_ASSERT( cable_utf8_count( cable ) == 6 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == ( char_t ) 0x53 );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == ( char_t ) 0x53 );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0x53 );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == ( char_t ) 0x53 );
   free( cp );
   
   cp = cable_utf8_item( cable, 4 );
   CU_ASSERT( cp[0] == ( char_t ) 0x53 );
   free( cp );
   
   cp = cable_utf8_item( cable, 5 );
   CU_ASSERT( cp[0] == ( char_t ) 0x53 );
   free( cp );
   
   cable_utf8_dispose( &cable );
   return;
}

/**
   test_to_upper_12
*/

void test_to_upper_12( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[16] = {0};
   char_t *cp = NULL;
   
   s[0] = 0xC5;
   s[1] = 0x89;

   cable = cable_utf8_make_capacity_from_cstring( s, 4 );
   
   CU_ASSERT( cable_utf8_count( cable ) == 1 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 0, 0 );
   CU_ASSERT( cable_utf8_count( cable ) == 2 );
   
   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCA );
   CU_ASSERT( cp[1] == ( char_t ) 0xBC );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == ( char_t ) 0x4E );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_13
*/

void test_to_upper_13( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[16] = {0};
   char_t *cp = NULL;
   
   s[0] = 0xC5;
   s[1] = 0x89;
   s[2] = 0xC5;
   s[3] = 0x89;

   cable = cable_utf8_make_capacity_from_cstring( s, 4 );
   
   CU_ASSERT( cable_utf8_count( cable ) == 2 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 0, 0 );
   CU_ASSERT( cable_utf8_count( cable ) == 3 );
   
   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCA );
   CU_ASSERT( cp[1] == ( char_t ) 0xBC );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == ( char_t ) 0x4E );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0xC5 );
   CU_ASSERT( cp[1] == ( char_t ) 0x89 );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_to_upper_14
*/

void test_to_upper_14( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[16] = {0};
   char_t *cp = NULL;
   
   s[0] = 0xC5;
   s[1] = 0x89;
   s[2] = 0xC5;
   s[3] = 0x89;

   cable = cable_utf8_make_capacity_from_cstring( s, 4 );
   
   CU_ASSERT( cable_utf8_count( cable ) == 2 );

   CU_ASSERT( cable != NULL );

   cable_utf8_to_upper( cable, 0, 1 );
   CU_ASSERT( cable_utf8_count( cable ) == 4 );
   
   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCA );
   CU_ASSERT( cp[1] == ( char_t ) 0xBC );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == ( char_t ) 0x4E );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCA );
   CU_ASSERT( cp[1] == ( char_t ) 0xBC );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == ( char_t ) 0x4E );
   free( cp );
   
   cable_utf8_dispose( &cable );

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

   // test_to_upper_11
   add_test_to_suite( p_suite, test_to_upper_11, "test_to_upper_11" );

   // test_to_upper_12
   add_test_to_suite( p_suite, test_to_upper_12, "test_to_upper_12" );

   // test_to_upper_13
   add_test_to_suite( p_suite, test_to_upper_13, "test_to_upper_13" );

   // test_to_upper_14
   add_test_to_suite( p_suite, test_to_upper_14, "test_to_upper_14" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


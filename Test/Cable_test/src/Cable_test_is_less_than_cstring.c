/**
 @file Cable_test_is_less_than_cstring.c
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
   test_is_less_than_cstring_1
*/

void test_is_less_than_cstring_1( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = "abce";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_1a
*/

void test_is_less_than_cstring_1a( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abce" );
   cable1 = "abcd";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 0 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_2
*/

void test_is_less_than_cstring_2( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_from_cstring( "abcd" );
   cable1 = "abcd";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 0 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_3
*/

void test_is_less_than_cstring_3( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;cable_t *
   cable_make_capacity( int32_t capacity );

   cable_t *
   cable_make_capacity_from_cstring( char_t *str, int32_t capacity );

   int32_t
   cable_capacity( cable_t *cable );



   cable = cable_make_from_cstring( "abcd" );
   cable1 = "abc";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 0 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_4
*/

void test_is_less_than_cstring_4( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcd", 4 );
   cable1 = "abcde";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_5
*/

void test_is_less_than_cstring_5( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = "abceefghij";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 1 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_6
*/

void test_is_less_than_cstring_6( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = "abcdefghij";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 0 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_7
*/

void test_is_less_than_cstring_7( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = "abcdefghi";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 0 );

   cable_dispose( cable );

   return;
}

/**
   test_is_less_than_cstring_8
*/

void test_is_less_than_cstring_8( void )
{
   cable_t *cable = NULL;
   char_t *cable1 = NULL;

   cable = cable_make_capacity_from_cstring( "abcdefghij", 4 );
   cable1 = "abcdefghijk";

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_is_less_than_cstring( cable, cable1 ) == 1 );

   cable_dispose( cable );

   return;
}

int
add_test_is_less_than_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_less_than_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_less_than_cstring_1
   add_test_to_suite( p_suite, test_is_less_than_cstring_1, "test_is_less_than_cstring_1" );

   // test_is_less_than_cstring_1a
   add_test_to_suite( p_suite, test_is_less_than_cstring_1a, "test_is_less_than_cstring_1a" );

   // test_is_less_than_cstring_2
   add_test_to_suite( p_suite, test_is_less_than_cstring_2, "test_is_less_than_cstring_2" );

   // test_is_less_than_cstring_3
   add_test_to_suite( p_suite, test_is_less_than_cstring_3, "test_is_less_than_cstring_3" );

   // test_is_less_than_cstring_4
   add_test_to_suite( p_suite, test_is_less_than_cstring_4, "test_is_less_than_cstring_4" );

   // test_is_less_than_cstring_5
   add_test_to_suite( p_suite, test_is_less_than_cstring_5, "test_is_less_than_cstring_5" );

   // test_is_less_than_cstring_6
   add_test_to_suite( p_suite, test_is_less_than_cstring_6, "test_is_less_than_cstring_6" );

   // test_is_less_than_cstring_7
   add_test_to_suite( p_suite, test_is_less_than_cstring_7, "test_is_less_than_cstring_7" );

   // test_is_less_than_cstring_8
   add_test_to_suite( p_suite, test_is_less_than_cstring_8, "test_is_less_than_cstring_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


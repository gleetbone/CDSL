/**
 @file Cable_utf8_test_split.c
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
   test_split_1
*/

void test_split_1( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_from_cstring( "axbxcd" );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "x", &count );

   CU_ASSERT( count == 3 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "cd" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_split_2
*/

void test_split_2( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_from_cstring( "xaxbxcdx" );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "x", &count );

   CU_ASSERT( count == 5 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[3];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "cd" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[4];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_split_3
*/

void test_split_3( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_capacity_from_cstring( "axbxcd", 4 );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "x", &count );

   CU_ASSERT( count == 3 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "cd" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_split_4
*/

void test_split_4( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_capacity_from_cstring( "xaxbxcdx", 4 );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "x", &count );

   CU_ASSERT( count == 5 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[3];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "cd" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[4];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_split_5
*/

void test_split_5( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_capacity_from_cstring( "xaxbxcxdxexfxgxhxixjx", 4 );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "x", &count );

   CU_ASSERT( count == 12 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[3];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "c" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[4];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "d" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[5];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "e" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[6];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "f" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[7];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "g" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[8];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "h" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[9];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "i" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[10];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "j" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[11];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_split_6
*/

void test_split_6( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_capacity_from_cstring( "xaxbxcxdxexfx", 4 );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "x", &count );

   CU_ASSERT( count == 8 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[3];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "c" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[4];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "d" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[5];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "e" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[6];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "f" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[7];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_split_7
*/

void test_split_7( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;
   cable_utf8_t **acable = NULL;
   int32_t count = 0;

   cable = cable_utf8_make_capacity_from_cstring( "xaxbzcydxezfxr", 4 );

   CU_ASSERT( cable != NULL );

   acable = cable_utf8_split( cable, "xyzABCDEFG", &count );

   CU_ASSERT( count == 8 );

   cable1 = acable[0];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[1];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "a" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[2];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "b" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[3];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "c" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[4];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "d" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[5];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "e" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[6];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "f" ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = acable[7];

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_is_equal_cstring( cable1, "r" ) == 1 );
   cable_utf8_dispose( &cable1 );

   free( acable );
   cable_utf8_dispose( &cable );

   return;
}

int
add_test_split( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_split", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_split_1
   add_test_to_suite( p_suite, test_split_1, "test_split_1" );

   // test_split_2
   add_test_to_suite( p_suite, test_split_2, "test_split_2" );

   // test_split_3
   add_test_to_suite( p_suite, test_split_3, "test_split_3" );

   // test_split_4
   add_test_to_suite( p_suite, test_split_4, "test_split_4" );

   // test_split_5
   add_test_to_suite( p_suite, test_split_5, "test_split_5" );

   // test_split_6
   add_test_to_suite( p_suite, test_split_6, "test_split_6" );

   // test_split_7
   add_test_to_suite( p_suite, test_split_7, "test_split_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_utf8_test_put_ascii.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Cable_utf8"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Cable_utf8

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
   test_put_ascii_1
*/

void test_put_ascii_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 4 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cable_utf8_put_ascii( cable, 'w', 0 );
   cable_utf8_put_ascii( cable, 'x', 1 );
   cable_utf8_put_ascii( cable, 'y', 2 );
   cable_utf8_put_ascii( cable, 'z', 3 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'w' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'x' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'y' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'z' );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_put_ascii_2
*/

void test_put_ascii_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 10 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cable_utf8_put_ascii( cable, 'w', 0 );
   cable_utf8_put_ascii( cable, 'x', 1 );
   cable_utf8_put_ascii( cable, 'y', 2 );
   cable_utf8_put_ascii( cable, 'z', 3 );
   cable_utf8_put_ascii( cable, 'A', 4 );
   cable_utf8_put_ascii( cable, 'B', 5 );
   cable_utf8_put_ascii( cable, 'C', 6 );
   cable_utf8_put_ascii( cable, 'D', 7 );
   cable_utf8_put_ascii( cable, 'E', 8 );
   cable_utf8_put_ascii( cable, 'F', 9 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'w' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'x' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'y' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'z' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 4 ) == 'A' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 5 ) == 'B' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 6 ) == 'C' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 7 ) == 'D' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 8 ) == 'E' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 9 ) == 'F' );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_put_ascii_3
*/

void test_put_ascii_3( void )
{
   cable_utf8_t *cable = NULL;
   char_t str[32] = {0};

   str[0] = 'a';
   str[1] = 0xC5;
   str[2] = 0x89;
   str[3] = 'b';
   
   cable = cable_utf8_make_capacity_from_cstring( str, 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 3 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cable_utf8_put_ascii( cable, 'x', 1 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'a' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'x' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'b' );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_put_ascii( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put_ascii", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_ascii_1
   add_test_to_suite( p_suite, test_put_ascii_1, "test_put_ascii_1" );

   // test_put_ascii_2
   add_test_to_suite( p_suite, test_put_ascii_2, "test_put_ascii_2" );

   // test_put_ascii_3
   add_test_to_suite( p_suite, test_put_ascii_3, "test_put_ascii_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_utf8_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   cable_utf8_t *cable = NULL;
   char_t str[8] = {0};

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 4 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   str[0] = 'e';
   
   cable_utf8_put( cable, str, 0 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'b' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'c' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );

   str[0] = 'f';
   
   cable_utf8_put( cable, str, 1 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'c' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );

   str[0] = 'g';
   
   cable_utf8_put( cable, str, 2 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'g' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );

   str[0] = 'h';
   
   cable_utf8_put( cable, str, 3 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'g' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'h' );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   cable_utf8_t *cable = NULL;
   char_t str[8] = {0};
   char_t *cp = NULL; 

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 10 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   str[0] = 0xC5;
   str[1] = 0x89;
   
   cable_utf8_put( cable, str, 0 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == ( char_t ) 0xC5 );
   CU_ASSERT( cp[1] == ( char_t ) 0x89 );
   CU_ASSERT( cp[2] == 0 );
   
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'b' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'c' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 4 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 5 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 6 ) == 'g' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 7 ) == 'h' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 8 ) == 'i' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 9 ) == 'j' );

   free( cp );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   cable_utf8_t *cable = NULL;
   char_t str[8] = {0};
   char_t *cp = NULL; 

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 10 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   str[0] = 0xC5;
   str[1] = 0x89;
   
   cable_utf8_put( cable, str, 2 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'a' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'b' );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0xC5 );
   CU_ASSERT( cp[1] == ( char_t ) 0x89 );
   CU_ASSERT( cp[2] == 0 );
   
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 4 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 5 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 6 ) == 'g' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 7 ) == 'h' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 8 ) == 'i' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 9 ) == 'j' );

   free( cp );
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   cable_utf8_t *cable = NULL;
   char_t str[8] = {0};
   char_t *cp = NULL; 

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_count( cable ) == 10 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   str[0] = 0xC5;
   str[1] = 0x89;
   
   cable_utf8_put( cable, str, 9 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'a' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'b' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'c' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 4 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 5 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 6 ) == 'g' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 7 ) == 'h' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 8 ) == 'i' );

   cp = cable_utf8_item( cable, 9 );
   CU_ASSERT( cp[0] == ( char_t ) 0xC5 );
   CU_ASSERT( cp[1] == ( char_t ) 0x89 );
   CU_ASSERT( cp[2] == 0 );
   
   free( cp );
   cable_utf8_dispose( &cable );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


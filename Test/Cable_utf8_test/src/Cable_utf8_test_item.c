/**
 @file Cable_utf8_test_item.c
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
   test_item_1
*/

void test_item_1( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcd", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 4 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'a' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'b' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'c' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   cable_utf8_t *cable = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 10 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   CU_ASSERT( cable_utf8_item_ascii( cable, 0 ) == 'a' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 1 ) == 'b' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 2 ) == 'c' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 3 ) == 'd' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 4 ) == 'e' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 5 ) == 'f' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 6 ) == 'g' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 7 ) == 'h' );
   CU_ASSERT( cable_utf8_item_ascii( cable, 8 ) == 'i' );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   char_t *cp = NULL;

   s[0] = 0xCE;
   s[1] = 0xB1;
   
   s[2] = 0xD7;
   s[3] = 0x90;

   s[4] = 0xE0;
   s[5] = 0xA4;
   s[6] = 0x84;
      
   s[7] = 0xF0;
   s[8] = 0x92;
   s[9] = 0x80;
   s[10] = 0x80;
   
   cable = cable_utf8_make_capacity_from_cstring( s, 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 11 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCE );
   CU_ASSERT( cp[1] == ( char_t ) 0xB1 );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == ( char_t ) 0xD7 );
   CU_ASSERT( cp[1] == ( char_t ) 0x90 );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0xE0 );
   CU_ASSERT( cp[1] == ( char_t ) 0xA4 );
   CU_ASSERT( cp[2] == ( char_t ) 0x84 );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == ( char_t ) 0xF0 );
   CU_ASSERT( cp[1] == ( char_t ) 0x92 );
   CU_ASSERT( cp[2] == ( char_t ) 0x80 );
   CU_ASSERT( cp[3] == ( char_t ) 0x80 );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_4
*/

void test_item_4( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   char_t *cp = NULL;

   s[0] = 'a';
   
   s[1] = 0xCE;
   s[2] = 0xB1;
   
   s[3] = 0xD7;
   s[4] = 0x90;

   s[5] = 0xE0;
   s[6] = 0xA4;
   s[7] = 0x84;
      
   s[8] = 0xF0;
   s[9] = 0x92;
   s[10] = 0x80;
   s[11] = 0x80;
   
   cable = cable_utf8_make_capacity_from_cstring( s, 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 12 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == 'a' );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCE );
   CU_ASSERT( cp[1] == ( char_t ) 0xB1 );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0xD7 );
   CU_ASSERT( cp[1] == ( char_t ) 0x90 );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == ( char_t ) 0xE0 );
   CU_ASSERT( cp[1] == ( char_t ) 0xA4 );
   CU_ASSERT( cp[2] == ( char_t ) 0x84 );
   free( cp );
   
   cp = cable_utf8_item( cable, 4 );
   CU_ASSERT( cp[0] == ( char_t ) 0xF0 );
   CU_ASSERT( cp[1] == ( char_t ) 0x92 );
   CU_ASSERT( cp[2] == ( char_t ) 0x80 );
   CU_ASSERT( cp[3] == ( char_t ) 0x80 );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_5
*/

void test_item_5( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   char_t *cp = NULL;

   s[0] = 'a';
   s[1] = 'b';
   
   s[2] = 0xCE;
   s[3] = 0xB1;
   
   s[4] = 0xD7;
   s[5] = 0x90;

   s[6] = 0xE0;
   s[7] = 0xA4;
   s[8] = 0x84;
      
   s[9] = 0xF0;
   s[10] = 0x92;
   s[11] = 0x80;
   s[12] = 0x80;
   
   cable = cable_utf8_make_capacity_from_cstring( s, 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 13 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == 'a' );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == 'b' );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCE );
   CU_ASSERT( cp[1] == ( char_t ) 0xB1 );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == ( char_t ) 0xD7 );
   CU_ASSERT( cp[1] == ( char_t ) 0x90 );
   free( cp );
   
   cp = cable_utf8_item( cable, 4 );
   CU_ASSERT( cp[0] == ( char_t ) 0xE0 );
   CU_ASSERT( cp[1] == ( char_t ) 0xA4 );
   CU_ASSERT( cp[2] == ( char_t ) 0x84 );
   free( cp );
   
   cp = cable_utf8_item( cable, 5 );
   CU_ASSERT( cp[0] == ( char_t ) 0xF0 );
   CU_ASSERT( cp[1] == ( char_t ) 0x92 );
   CU_ASSERT( cp[2] == ( char_t ) 0x80 );
   CU_ASSERT( cp[3] == ( char_t ) 0x80 );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_6
*/

void test_item_6( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   char_t *cp = NULL;

   s[0] = 'a';
   s[1] = 'b';
   s[2] = 'c';
   
   s[3] = 0xCE;
   s[4] = 0xB1;
   
   s[5] = 0xD7;
   s[6] = 0x90;

   s[7] = 0xE0;
   s[8] = 0xA4;
   s[9] = 0x84;
      
   s[10] = 0xF0;
   s[11] = 0x92;
   s[12] = 0x80;
   s[13] = 0x80;
   
   cable = cable_utf8_make_capacity_from_cstring( s, 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 14 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == 'a' );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == 'b' );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == 'c' );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCE );
   CU_ASSERT( cp[1] == ( char_t ) 0xB1 );
   free( cp );
   
   cp = cable_utf8_item( cable, 4 );
   CU_ASSERT( cp[0] == ( char_t ) 0xD7 );
   CU_ASSERT( cp[1] == ( char_t ) 0x90 );
   free( cp );
   
   cp = cable_utf8_item( cable, 5 );
   CU_ASSERT( cp[0] == ( char_t ) 0xE0 );
   CU_ASSERT( cp[1] == ( char_t ) 0xA4 );
   CU_ASSERT( cp[2] == ( char_t ) 0x84 );
   free( cp );
   
   cp = cable_utf8_item( cable, 6 );
   CU_ASSERT( cp[0] == ( char_t ) 0xF0 );
   CU_ASSERT( cp[1] == ( char_t ) 0x92 );
   CU_ASSERT( cp[2] == ( char_t ) 0x80 );
   CU_ASSERT( cp[3] == ( char_t ) 0x80 );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_7
*/

void test_item_7( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   char_t *cp = NULL;

   s[0] = 'a';
   s[1] = 'b';
   s[2] = 'c';
   s[3] = 'd';
   
   s[4] = 0xCE;
   s[5] = 0xB1;
   
   s[6] = 0xD7;
   s[7] = 0x90;

   s[8] = 0xE0;
   s[9] = 0xA4;
   s[10] = 0x84;
      
   s[11] = 0xF0;
   s[12] = 0x92;
   s[13] = 0x80;
   s[14] = 0x80;
   
   cable = cable_utf8_make_capacity_from_cstring( s, 4 );

   CU_ASSERT( cable != NULL );
   CU_ASSERT( cable_utf8_byte_count( cable ) == 15 );
   CU_ASSERT( cable_utf8_is_empty( cable ) == 0 );

   cp = cable_utf8_item( cable, 0 );
   CU_ASSERT( cp[0] == 'a' );
   free( cp );
   
   cp = cable_utf8_item( cable, 1 );
   CU_ASSERT( cp[0] == 'b' );
   free( cp );
   
   cp = cable_utf8_item( cable, 2 );
   CU_ASSERT( cp[0] == 'c' );
   free( cp );
   
   cp = cable_utf8_item( cable, 3 );
   CU_ASSERT( cp[0] == 'd' );
   free( cp );
   
   cp = cable_utf8_item( cable, 4 );
   CU_ASSERT( cp[0] == ( char_t ) 0xCE );
   CU_ASSERT( cp[1] == ( char_t ) 0xB1 );
   free( cp );
   
   cp = cable_utf8_item( cable, 5 );
   CU_ASSERT( cp[0] == ( char_t ) 0xD7 );
   CU_ASSERT( cp[1] == ( char_t ) 0x90 );
   free( cp );
   
   cp = cable_utf8_item( cable, 6 );
   CU_ASSERT( cp[0] == ( char_t ) 0xE0 );
   CU_ASSERT( cp[1] == ( char_t ) 0xA4 );
   CU_ASSERT( cp[2] == ( char_t ) 0x84 );
   free( cp );
   
   cp = cable_utf8_item( cable, 7 );
   CU_ASSERT( cp[0] == ( char_t ) 0xF0 );
   CU_ASSERT( cp[1] == ( char_t ) 0x92 );
   CU_ASSERT( cp[2] == ( char_t ) 0x80 );
   CU_ASSERT( cp[3] == ( char_t ) 0x80 );
   free( cp );
   
   cable_utf8_dispose( &cable );

   return;
}

int
add_test_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_1
   add_test_to_suite( p_suite, test_item_1, "test_item_1" );

   // test_item_2
   add_test_to_suite( p_suite, test_item_2, "test_item_2" );

   // test_item_3
   add_test_to_suite( p_suite, test_item_3, "test_item_3" );

   // test_item_4
   add_test_to_suite( p_suite, test_item_4, "test_item_4" );

   // test_item_5
   add_test_to_suite( p_suite, test_item_5, "test_item_5" );

   // test_item_6
   add_test_to_suite( p_suite, test_item_6, "test_item_6" );

   // test_item_7
   add_test_to_suite( p_suite, test_item_7, "test_item_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


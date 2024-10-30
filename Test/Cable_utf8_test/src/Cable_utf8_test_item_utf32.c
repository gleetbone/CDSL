/**
 @file Cable_utf8_test_item_utf32.c
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
   test_item_utf32_1
*/

void test_item_utf32_1( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   uint32_t c = 0;

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

   c = cable_utf8_item_utf32( cable, 0 );
   CU_ASSERT( c == ( uint32_t ) 0x03B1 );
   
   c = cable_utf8_item_utf32( cable, 1 );
   CU_ASSERT( c == ( uint32_t ) 0x05D0 );
   
   c = cable_utf8_item_utf32( cable, 2 );
   CU_ASSERT( c == ( uint32_t ) 0x0904 );
   
   c = cable_utf8_item_utf32( cable, 3 );
   CU_ASSERT( c == ( uint32_t ) 0x12000 );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_utf32_2
*/

void test_item_utf32_2( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   uint32_t c = 0;

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

   c = cable_utf8_item_ascii( cable, 0 );
   CU_ASSERT( c == 'a' );
   
   c = cable_utf8_item_utf32( cable, 1 );
   CU_ASSERT( c == ( uint32_t ) 0x03B1 );
   
   c = cable_utf8_item_utf32( cable, 2 );
   CU_ASSERT( c == ( uint32_t ) 0x05D0 );
   
   c = cable_utf8_item_utf32( cable, 3 );
   CU_ASSERT( c == ( uint32_t ) 0x0904 );
   
   c = cable_utf8_item_utf32( cable, 4 );
   CU_ASSERT( c == ( uint32_t ) 0x12000 );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_utf32_3
*/

void test_item_utf32_3( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   uint32_t c = 0;

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

   c = cable_utf8_item_ascii( cable, 0 );
   CU_ASSERT( c == 'a' );
   
   c = cable_utf8_item_ascii( cable, 1 );
   CU_ASSERT( c == 'b' );
   
   c = cable_utf8_item_utf32( cable, 2 );
   CU_ASSERT( c == ( uint32_t ) 0x03B1 );
   
   c = cable_utf8_item_utf32( cable, 3 );
   CU_ASSERT( c == ( uint32_t ) 0x05D0 );
   
   c = cable_utf8_item_utf32( cable, 4 );
   CU_ASSERT( c == ( uint32_t ) 0x0904 );
   
   c = cable_utf8_item_utf32( cable, 5 );
   CU_ASSERT( c == ( uint32_t ) 0x12000 );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_utf32_4
*/

void test_item_utf32_4( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   uint32_t c = 0;

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

   c = cable_utf8_item_ascii( cable, 0 );
   CU_ASSERT( c == 'a' );
   
   c = cable_utf8_item_ascii( cable, 1 );
   CU_ASSERT( c == 'b' );
   
   c = cable_utf8_item_ascii( cable, 2 );
   CU_ASSERT( c == 'c' );
   
   c = cable_utf8_item_utf32( cable, 3 );
   CU_ASSERT( c == ( uint32_t ) 0x03B1 );
   
   c = cable_utf8_item_utf32( cable, 4 );
   CU_ASSERT( c == ( uint32_t ) 0x05D0 );
   
   c = cable_utf8_item_utf32( cable, 5 );
   CU_ASSERT( c == ( uint32_t ) 0x0904 );
   
   c = cable_utf8_item_utf32( cable, 6 );
   CU_ASSERT( c == ( uint32_t ) 0x12000 );
   
   cable_utf8_dispose( &cable );

   return;
}

/**
   test_item_utf32_5
*/

void test_item_utf32_5( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   uint32_t c = 0;

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

   c = cable_utf8_item_ascii( cable, 0 );
   CU_ASSERT( c == 'a' );
   
   c = cable_utf8_item_ascii( cable, 1 );
   CU_ASSERT( c == 'b' );
   
   c = cable_utf8_item_ascii( cable, 2 );
   CU_ASSERT( c == 'c' );
   
   c = cable_utf8_item_ascii( cable, 3 );
   CU_ASSERT( c == 'd' );
   
   c = cable_utf8_item_utf32( cable, 4 );
   CU_ASSERT( c == ( uint32_t ) 0x03B1 );
   
   c = cable_utf8_item_utf32( cable, 5 );
   CU_ASSERT( c == ( uint32_t ) 0x05D0 );
   
   c = cable_utf8_item_utf32( cable, 6 );
   CU_ASSERT( c == ( uint32_t ) 0x0904 );
   
   c = cable_utf8_item_utf32( cable, 7 );
   CU_ASSERT( c == ( uint32_t ) 0x12000 );
   
   cable_utf8_dispose( &cable );

   return;
}

int
add_test_item_utf32( void )
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

   // test_item_utf32_1
   add_test_to_suite( p_suite, test_item_utf32_1, "test_item_utf32_1" );

   // test_item_utf32_2
   add_test_to_suite( p_suite, test_item_utf32_2, "test_item_utf32_2" );

   // test_item_utf32_3
   add_test_to_suite( p_suite, test_item_utf32_3, "test_item_utf32_3" );

   // test_item_utf32_4
   add_test_to_suite( p_suite, test_item_utf32_4, "test_item_utf32_4" );

   // test_item_utf32_5
   add_test_to_suite( p_suite, test_item_utf32_5, "test_item_utf32_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


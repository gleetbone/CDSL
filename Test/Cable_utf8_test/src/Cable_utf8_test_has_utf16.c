/**
 @file Cable_utf8_test_has_utf16.c
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
   test_has_utf16_1
*/

void test_has_utf16_1( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[32] = {0};
   uint16_t c[4] = {0};

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
   
   s[12] = 'b';
   
   cable = cable_utf8_make_capacity_from_cstring( s, 4 );
   
   CU_ASSERT( cable != NULL );

   c[0] = ( uint16_t ) 'a';
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 1 );

   c[0] = ( uint16_t ) 0x03B1;
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 1 );

   c[0] = ( uint16_t ) 0x05D0;
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 1 );

   c[0] = ( uint16_t ) 0x0904;
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 1 );

   c[0] = ( uint16_t ) 0xD808;
   c[1] = ( uint16_t ) 0xDC00;
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 1 );

   c[0] = ( uint16_t ) 'b';
   c[1] = 0;
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 1 );

   c[0] = ( uint16_t ) 'A';
   CU_ASSERT( cable_utf8_has_utf16( cable, c ) == 0 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_has_utf16( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_utf16", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_utf16_1
   add_test_to_suite( p_suite, test_has_utf16_1, "test_has_utf16_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


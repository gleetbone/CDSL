/**
 @file Cable_utf8_test_has.c
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
   test_has_1
*/

void test_has_1( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[5] = {0};

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   s[0] = 'a';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'a' ) == 1 );

   s[0] = 'b';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'b' ) == 1 );

   s[0] = 'c';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'c' ) == 1 );

   s[0] = 'd';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'd' ) == 1 );

   s[0] = 'e';
   CU_ASSERT( cable_utf8_has( cable, s ) == 0 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'e' ) == 0 );

   s[0] = 'A';
   CU_ASSERT( cable_utf8_has( cable, s ) == 0 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'A' ) == 0 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   cable_utf8_t *cable = NULL;
   char_t s[5] = {0};

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   s[0] = 'a';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'a' ) == 1 );

   s[0] = 'b';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'b' ) == 1 );

   s[0] = 'c';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'c' ) == 1 );

   s[0] = 'd';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'd' ) == 1 );

   s[0] = 'e';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'e' ) == 1 );

   s[0] = 'f';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'f' ) == 1 );

   s[0] = 'g';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'g' ) == 1 );

   s[0] = 'h';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'h' ) == 1 );

   s[0] = 'i';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'i' ) == 1 );

   s[0] = 'j';
   CU_ASSERT( cable_utf8_has( cable, s ) == 1 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'j' ) == 1 );

   s[0] = 'A';
   CU_ASSERT( cable_utf8_has( cable, s ) == 0 );
   CU_ASSERT( cable_utf8_has_ascii( cable, 'A' ) == 0 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_has( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_1
   add_test_to_suite( p_suite, test_has_1, "test_has_1" );

   // test_has_2
   add_test_to_suite( p_suite, test_has_2, "test_has_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Cable_utf8_test_ends_with.c
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
   test_ends_with_1
*/

void test_ends_with_1( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_from_cstring( "abcd" );

   CU_ASSERT( cable != NULL );

   cable1 = cable_utf8_make_from_cstring( "d" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "cd" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "bcd" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "abcd" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "c" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "ac" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "bd" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "A" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable_utf8_dispose( &cable );

   return;
}

/**
   test_ends_with_2
*/

void test_ends_with_2( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_capacity_from_cstring( "abcdefghij", 4 );

   CU_ASSERT( cable != NULL );

   cable1 = cable_utf8_make_from_cstring( "j" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "ij" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "hij" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "efghij" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "defghij" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 1 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "c" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "ac" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "bd" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable1 = cable_utf8_make_from_cstring( "A" );
   CU_ASSERT( cable_utf8_ends_with( cable, cable1 ) == 0 );
   cable_utf8_dispose( &cable1 );

   cable_utf8_dispose( &cable );

   return;
}

int
add_test_ends_with( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_ends_with", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_ends_with_1
   add_test_to_suite( p_suite, test_ends_with_1, "test_ends_with_1" );

   // test_ends_with_2
   add_test_to_suite( p_suite, test_ends_with_2, "test_ends_with_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


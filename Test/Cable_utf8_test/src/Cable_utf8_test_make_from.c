/**
 @file Cable_utf8_test_make_from.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Cable_utf8_make_from
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Cable_utf8_make_from.

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

int32_t
cable_utf8_capacity( cable_utf8_t *cable );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_1
*/

void test_make_from_1( void )
{
   cable_utf8_t *cable = NULL;
   cable_utf8_t *cable1 = NULL;

   cable = cable_utf8_make_capacity( 4 );
   cable1 = cable_utf8_make_from( cable );

   CU_ASSERT( cable1 != NULL );
   CU_ASSERT( cable_utf8_count( cable1 ) == 0 );
   CU_ASSERT( cable_utf8_is_empty( cable1 ) == 1 );
   CU_ASSERT( cable_utf8_capacity( cable1 ) == 4 );

   cable_utf8_dispose( &cable );
   cable_utf8_dispose( &cable1 );

   return;
}

int
add_test_make_from( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_1
   add_test_to_suite( p_suite, test_make_from_1, "test_make_from_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file HTable_test_put.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HTable_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HTable_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_HTable.h"
#include "ss_HTable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_put_1
*/

void test_put_1( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 1000 );

   CU_ASSERT( ii_htable_count( htable ) == 1 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 0 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 10000 );

   CU_ASSERT( ii_htable_count( htable ) == 1 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 0 );

   ii_htable_put( htable, 13, 20000 );

   CU_ASSERT( ii_htable_count( htable ) == 2 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 0 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 10000 );
   ii_htable_put( htable, 25, 20000 );
   ii_htable_put( htable, 26, 30000 );
   ii_htable_put( htable, 27, 40000 );
   ii_htable_put( htable, 28, 50000 );
   ii_htable_put( htable, 29, 60000 );
   ii_htable_put( htable, 30, 70000 );
   ii_htable_put( htable, 31, 80000 );
   ii_htable_put( htable, 32, 90000 );
   ii_htable_put( htable, 33, 11000 );
   ii_htable_put( htable, 34, 12000 );
   ii_htable_put( htable, 35, 13000 );
   ii_htable_put( htable, 36, 14000 );
   ii_htable_put( htable, 37, 15000 );
   ii_htable_put( htable, 38, 16000 );
   ii_htable_put( htable, 39, 17000 );
   ii_htable_put( htable, 40, 18000 );
   ii_htable_put( htable, 41, 19000 );

   CU_ASSERT( ii_htable_count( htable ) == 18 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 0 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 10000 );
   ii_htable_put( htable, 25, 10000 );

   CU_ASSERT( ii_htable_count( htable ) == 1 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 0 );

   ii_htable_put( htable, 13, 20000 );

   CU_ASSERT( ii_htable_count( htable ) == 2 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 0 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   ss_htable_t *htable = NULL;

   htable = ss_htable_make();

   string_t *k1 = string_make_from_cstring( "k1" );
   string_t *v1 = string_make_from_cstring( "v1" );
   
   string_t *k2 = string_make_from_cstring( "k2" );
   string_t *v2 = string_make_from_cstring( "v2" );
   
   string_t *k3 = string_make_from_cstring( "k3" );
   string_t *v3 = string_make_from_cstring( "v3" );
   
   ss_htable_put( htable, v1, k1 );
   ss_htable_put( htable, v2, k1 );

   CU_ASSERT( ss_htable_count( htable ) == 1 );
   CU_ASSERT( ss_htable_is_empty( htable ) == 0 );

   ss_htable_put( htable, v3, k3 );

   CU_ASSERT( ss_htable_count( htable ) == 2 );
   CU_ASSERT( ss_htable_is_empty( htable ) == 0 );

   string_deep_dispose( &v1 );
   string_deep_dispose( &k2 );
   ss_htable_deep_dispose( &htable );

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

   // test_put_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


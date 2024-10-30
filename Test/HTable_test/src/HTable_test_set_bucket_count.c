/**
 @file HTable_test_set_bucket_count.c
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
   test_set_bucket_count_1
*/

void test_set_bucket_count_1( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();
   ii_htable_put( htable, 1, 10 );

   CU_ASSERT( ii_htable_bucket_count( htable ) == 13 );

   ii_htable_set_bucket_count( htable, 23 );

   CU_ASSERT( ii_htable_bucket_count( htable ) == 23 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_set_bucket_count_2
*/

void test_set_bucket_count_2( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make_n( 23 );
   ii_htable_put( htable, 1, 10 );

   CU_ASSERT( ii_htable_bucket_count( htable ) == 23 );

   ii_htable_set_bucket_count( htable, 37 );

   CU_ASSERT( ii_htable_bucket_count( htable ) == 37 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_set_bucket_count_3
*/

void test_set_bucket_count_3( void )
{
   ss_htable_t *htable = NULL;

   htable = ss_htable_make_n( 23 );
   
   string_t *k1 = string_make_from_cstring( "k1" );
   string_t *v1 = string_make_from_cstring( "v1" );
   
   ss_htable_put( htable, v1, k1 );

   CU_ASSERT( ss_htable_bucket_count( htable ) == 23 );

   ss_htable_set_bucket_count( htable, 37 );

   CU_ASSERT( ss_htable_bucket_count( htable ) == 37 );

   ss_htable_deep_dispose( &htable );

   return;
}

int
add_test_set_bucket_count( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_set_bucket_count", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_set_bucket_count_1
   add_test_to_suite( p_suite, test_set_bucket_count_1, "test_set_bucket_count_1" );

   // test_set_bucket_count_2
   add_test_to_suite( p_suite, test_set_bucket_count_2, "test_set_bucket_count_2" );

   // test_set_bucket_count_3
   add_test_to_suite( p_suite, test_set_bucket_count_3, "test_set_bucket_count_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


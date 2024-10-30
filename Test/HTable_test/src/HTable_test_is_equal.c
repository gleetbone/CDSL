/**
 @file HTable_test_is_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HTable_clone"
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   ii_htable_t *htable = NULL;
   ii_htable_t *htable1 = NULL;
   
   htable = ii_htable_make();
   ii_htable_put( htable, 1, 10 );
   
   htable1 = ii_htable_make();
   
   CU_ASSERT( ii_htable_is_equal( htable1, htable ) == 0 );
 
   ii_htable_put( htable1, 12, 120 );
   
   CU_ASSERT( ii_htable_is_equal( htable1, htable ) == 0 );
 
   ii_htable_put( htable, 12, 120 );
   ii_htable_put( htable1, 1, 10 );
   
   CU_ASSERT( ii_htable_is_equal( htable1, htable ) == 1 );
 
   ii_htable_put( htable, 13, 130 );
   ii_htable_put( htable1, 14, 130 );
   
   CU_ASSERT( ii_htable_is_equal( htable1, htable ) == 0 );
 
   ii_htable_put( htable1, 13, 130 );
   
   CU_ASSERT( ii_htable_is_equal( htable1, htable ) == 1 );
 
   ii_htable_dispose( &htable );
   ii_htable_dispose( &htable1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   ss_htable_t *htable = NULL;
   ss_htable_t *htable1 = NULL;
   
   htable = ss_htable_make();
   htable1 = ss_htable_make();
   
   string_t *k1 = string_make_from_cstring( "key" );
   string_t *v1 = string_make_from_cstring( "value" );
   
   string_t *k2 = string_make_from_cstring( "key" );
   string_t *v2 = string_make_from_cstring( "value" );
   
   ss_htable_put( htable, v1, k1 );
   
   CU_ASSERT( ss_htable_is_equal( htable1, htable ) == 0 );
 
   ss_htable_put( htable1, v2, k2 );
   
   CU_ASSERT( ss_htable_is_equal( htable1, htable ) == 0 );
 
   ss_htable_deep_dispose( &htable );
   ss_htable_deep_dispose( &htable1 );

   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


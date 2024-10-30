/**
 @file BSTree_kv_test_search_back.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_kv_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "ss_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_search_back_1
*/

void test_search_back_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_start( bstree );
   ii_bstree_kv_search_back( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_search_back_2
*/

void test_search_back_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_finish( bstree );
   ii_bstree_kv_search_back( bstree, 10 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
   CU_ASSERT( ii_bstree_kv_index( bstree ) == 0 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_search_back_3
*/

void test_search_back_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_finish( bstree );
   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
   CU_ASSERT( ii_bstree_kv_index( bstree ) == 1 );

   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
   CU_ASSERT( ii_bstree_kv_index( bstree ) == 1 );

   ii_bstree_kv_back( bstree );
   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_search_back_4
*/

void test_search_back_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   
   ii_bstree_kv_finish( bstree );
   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
   CU_ASSERT( ii_bstree_kv_index( bstree ) == 2 );

   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
   CU_ASSERT( ii_bstree_kv_index( bstree ) == 2 );

   ii_bstree_kv_back( bstree );
   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
   CU_ASSERT( ii_bstree_kv_index( bstree ) == 1 );

   ii_bstree_kv_back( bstree );
   ii_bstree_kv_search_back( bstree, 20 );
   CU_ASSERT( ii_bstree_kv_off( bstree ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_search_back_5
*/

void test_search_back_5( void )
{
   ss_bstree_kv_t *bstree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s10 = string_make_from_cstring( "10" );
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s20 = string_make_from_cstring( "20" );
   
   string_t *s2a = string_make_from_cstring( "2" );
   string_t *s20a = string_make_from_cstring( "20" );
   
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s30 = string_make_from_cstring( "30" );
   
   bstree = ss_bstree_kv_make();
   
   ss_bstree_kv_put( bstree, s10, s1 );
   ss_bstree_kv_put( bstree, s20, s2 );
   ss_bstree_kv_put( bstree, s30, s3 );
   ss_bstree_kv_put( bstree, s20a, s2a );
   
   ss_bstree_kv_finish( bstree );
   ss_bstree_kv_search_back( bstree, s20 );
   CU_ASSERT( ss_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ss_bstree_kv_item_at( bstree ) == s20 );
   CU_ASSERT( ss_bstree_kv_index( bstree ) == 2 );

   ss_bstree_kv_search_back( bstree, s20 );
   CU_ASSERT( ss_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ss_bstree_kv_item_at( bstree ) == s20 );
   CU_ASSERT( ss_bstree_kv_index( bstree ) == 2 );

   ss_bstree_kv_back( bstree );
   ss_bstree_kv_search_back( bstree, s20 );
   CU_ASSERT( ss_bstree_kv_off( bstree ) == 0 );
   CU_ASSERT( ss_bstree_kv_item_at( bstree ) == s20a );
   CU_ASSERT( ss_bstree_kv_index( bstree ) == 1 );

   ss_bstree_kv_back( bstree );
   ss_bstree_kv_search_back( bstree, s20 );
   CU_ASSERT( ss_bstree_kv_off( bstree ) == 1 );
 
   ss_bstree_kv_deep_dispose( &bstree );

   return;
}

int
add_test_search_back( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_search_back", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_search_back_1
   add_test_to_suite( p_suite, test_search_back_1, "test_search_back_1" );

   // test_search_back_2
   add_test_to_suite( p_suite, test_search_back_2, "test_search_back_2" );

   // test_search_back_3
   add_test_to_suite( p_suite, test_search_back_3, "test_search_back_3" );

   // test_search_back_4
   add_test_to_suite( p_suite, test_search_back_4, "test_search_back_4" );

   // test_search_back_5
   add_test_to_suite( p_suite, test_search_back_5, "test_search_back_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


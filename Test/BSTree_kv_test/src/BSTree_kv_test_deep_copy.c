/**
 @file BSTree_test_deep_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
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
   test_deep_copy_1
*/

void test_deep_copy_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_t *bstree1 = NULL;
   
   bstree = ii_bstree_kv_make();
   ii_bstree_kv_put( bstree, 130, 13 );
   
   bstree1 = ii_bstree_kv_make();
   ii_bstree_kv_put( bstree1, 120, 12 );
   
   ii_bstree_kv_deep_copy( bstree1, bstree );
   
   CU_ASSERT( bstree1 != NULL );
   CU_ASSERT( ii_bstree_kv_count( bstree1 ) == 1 );
   CU_ASSERT( ii_bstree_kv_has( bstree1, 13 ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );
   ii_bstree_kv_dispose( &bstree1 );

   return;
}

/**
   test_deep_copy_2
*/

void test_deep_copy_2( void )
{
   ss_bstree_kv_t *bstree = NULL;
   ss_bstree_kv_t *bstree1 = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   
   bstree = ss_bstree_kv_make();
   ss_bstree_kv_put( bstree, s10, s1 );
   
   bstree1 = ss_bstree_kv_make();
   ss_bstree_kv_put( bstree1, s20, s2 );
   
   ss_bstree_kv_deep_copy( bstree1, bstree );
   
   CU_ASSERT( bstree1 != NULL );
   CU_ASSERT( ss_bstree_kv_count( bstree1 ) == 1 );
   CU_ASSERT( ss_bstree_kv_has( bstree1, s1 ) == 1 );
 
   ss_bstree_kv_deep_dispose( &bstree );
   ss_bstree_kv_deep_dispose( &bstree1 );

   return;
}

int
add_test_deep_copy( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_copy", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_copy_1
   add_test_to_suite( p_suite, test_deep_copy_1, "test_deep_copy_1" );

   // test_deep_copy_2
   add_test_to_suite( p_suite, test_deep_copy_2, "test_deep_copy_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


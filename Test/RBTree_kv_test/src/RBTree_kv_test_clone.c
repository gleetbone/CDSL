/**
 @file RBTree_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"
#include "ss_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   ii_rbtree_kv_t *rbtree1 = NULL;
   
   rbtree = ii_rbtree_kv_make();
   ii_rbtree_kv_put( rbtree, 130, 13 );
   
   rbtree1 = ii_rbtree_kv_clone( rbtree );
   
   CU_ASSERT( rbtree1 != NULL );
   CU_ASSERT( ii_rbtree_kv_count( rbtree1 ) == 1 );
   CU_ASSERT( ii_rbtree_kv_has( rbtree1, 13 ) == 1 );
 
   ii_rbtree_kv_dispose( &rbtree );
   ii_rbtree_kv_dispose( &rbtree1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   ss_rbtree_kv_t *rbtree1 = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   
   rbtree = ss_rbtree_kv_make();
   ss_rbtree_kv_put( rbtree, s10, s1 );
   
   rbtree1 = ss_rbtree_kv_clone( rbtree );
   
   CU_ASSERT( rbtree1 != NULL );
   CU_ASSERT( ss_rbtree_kv_count( rbtree1 ) == 1 );
   CU_ASSERT( ss_rbtree_kv_has( rbtree1, s1 ) == 1 );
 
   ss_rbtree_kv_deep_dispose( &rbtree );
   ss_rbtree_kv_dispose( &rbtree1 );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


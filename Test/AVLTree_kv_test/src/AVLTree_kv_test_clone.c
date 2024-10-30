/**
 @file AVLTree_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"
#include "ss_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   ii_avltree_kv_t *avltree1 = NULL;
   
   avltree = ii_avltree_kv_make();
   ii_avltree_kv_put( avltree, 130, 13 );
   
   avltree1 = ii_avltree_kv_clone( avltree );
   
   CU_ASSERT( avltree1 != NULL );
   CU_ASSERT( ii_avltree_kv_count( avltree1 ) == 1 );
   CU_ASSERT( ii_avltree_kv_has( avltree1, 13 ) == 1 );
 
   ii_avltree_kv_dispose( &avltree );
   ii_avltree_kv_dispose( &avltree1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   ss_avltree_kv_t *avltree = NULL;
   ss_avltree_kv_t *avltree1 = NULL;
   
   string_t *s1 = NULL;
   string_t *s10 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   
   avltree = ss_avltree_kv_make();
   ss_avltree_kv_put( avltree, s10, s1 );
   
   avltree1 = ss_avltree_kv_clone( avltree );
   
   CU_ASSERT( avltree1 != NULL );
   CU_ASSERT( ss_avltree_kv_count( avltree1 ) == 1 );
   CU_ASSERT( ss_avltree_kv_has( avltree1, s1 ) == 1 );
 
   ss_avltree_kv_deep_dispose( &avltree );
   ss_avltree_kv_dispose( &avltree1 );

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


/**
 @file BSTree_test_make.c
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
   test_make_1
*/

void test_make_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   CU_ASSERT( bstree != NULL );
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   CU_ASSERT( ii_bstree_kv_is_empty( bstree ) == 1 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   ss_bstree_kv_t *bstree = NULL;
   
   bstree = ss_bstree_kv_make();
   
   CU_ASSERT( bstree != NULL );
   CU_ASSERT( ss_bstree_kv_count( bstree ) == 0 );
   CU_ASSERT( ss_bstree_kv_is_empty( bstree ) == 1 );
 
   ss_bstree_kv_dispose( &bstree );

   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


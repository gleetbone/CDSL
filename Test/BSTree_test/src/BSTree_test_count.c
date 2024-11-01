/**
 @file BSTree_test_count.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"
#include "s_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_count_1
*/

void test_count_1( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   CU_ASSERT( bstree != NULL );
   CU_ASSERT( i_bstree_count( bstree ) == 0 );
   CU_ASSERT( i_bstree_is_empty( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_count_2
*/

void test_count_2( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   i_bstree_put( bstree, 13 );
   
   CU_ASSERT( i_bstree_count( bstree ) == 1 );
   CU_ASSERT( i_bstree_has( bstree, 13 ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_count_3
*/

void test_count_3( void )
{
   s_bstree_t *bstree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   
   bstree = s_bstree_make();
   s_bstree_put( bstree, s1 );
   
   CU_ASSERT( s_bstree_count( bstree ) == 1 );
   CU_ASSERT( s_bstree_has( bstree, s1 ) == 1 );
 
   s_bstree_deep_dispose( &bstree );

   return;
}

int
add_test_count( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_count", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_count_1
   add_test_to_suite( p_suite, test_count_1, "test_count_1" );

   // test_count_2
   add_test_to_suite( p_suite, test_count_2, "test_count_2" );

   // test_count_3
   add_test_to_suite( p_suite, test_count_3, "test_count_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


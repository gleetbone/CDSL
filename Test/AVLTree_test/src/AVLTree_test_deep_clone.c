/**
 @file AVLTree_test_deep_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_deep_clone_1
*/

void test_deep_clone_1( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_t *avltree1 = NULL;
   
   avltree = i_avltree_make();
   
   avltree1 = i_avltree_deep_clone( avltree );
   
   CU_ASSERT( avltree1 != NULL );
   CU_ASSERT( i_avltree_count( avltree1 ) == 0 );
 
   i_avltree_dispose( &avltree );
   i_avltree_dispose( &avltree1 );

   return;
}

/**
   test_deep_clone_2
*/

void test_deep_clone_2( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_t *avltree1 = NULL;
   
   avltree = i_avltree_make();
   i_avltree_put( avltree, 13 );
   
   avltree1 = i_avltree_deep_clone( avltree );
   
   CU_ASSERT( avltree1 != NULL );
   CU_ASSERT( i_avltree_count( avltree1 ) == 1 );
   CU_ASSERT( i_avltree_has( avltree1, 13 ) == 1 );
 
   i_avltree_dispose( &avltree );
   i_avltree_dispose( &avltree1 );

   return;
}

/**
   test_deep_clone_3
*/

void test_deep_clone_3( void )
{
   s_avltree_t *avltree = NULL;
   s_avltree_t *avltree1 = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   
   avltree = s_avltree_make();
   s_avltree_put( avltree, s1 );
   
   avltree1 = s_avltree_deep_clone( avltree );
   
   CU_ASSERT( avltree1 != NULL );
   CU_ASSERT( s_avltree_count( avltree1 ) == 1 );
   CU_ASSERT( s_avltree_has( avltree1, s1 ) == 1 );
 
   s_avltree_deep_dispose( &avltree );
   s_avltree_deep_dispose( &avltree1 );

   return;
}

int
add_test_deep_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_clone_1
   add_test_to_suite( p_suite, test_deep_clone_1, "test_deep_clone_1" );

   // test_deep_clone_2
   add_test_to_suite( p_suite, test_deep_clone_2, "test_deep_clone_2" );

   // test_deep_clone_3
   add_test_to_suite( p_suite, test_deep_clone_3, "test_deep_clone_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


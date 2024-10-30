/**
 @file AVLTree_test_make.c
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
   test_make_1
*/

void test_make_1( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   CU_ASSERT( avltree != NULL );
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   CU_ASSERT( i_avltree_is_empty( avltree ) == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_make_2
*/

void test_make_3( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   i_avltree_put( avltree, 13 );
   
   CU_ASSERT( i_avltree_count( avltree ) == 1 );
   CU_ASSERT( i_avltree_has( avltree, 13 ) == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_make_3
*/

void test_make_2( void )
{
   s_avltree_t *avltree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   
   avltree = s_avltree_make();
   s_avltree_put( avltree, s1 );
   
   CU_ASSERT( s_avltree_count( avltree ) == 1 );
   CU_ASSERT( s_avltree_has( avltree, s1 ) == 1 );
 
   s_avltree_deep_dispose( &avltree );

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

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


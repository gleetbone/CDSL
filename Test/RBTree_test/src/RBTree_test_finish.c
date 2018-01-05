/**
 @file RBTree_test_finish.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_finish_1
*/

void test_finish_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_finish( rbtree );
   
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 0 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_finish_2
*/

void test_finish_2( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_finish( rbtree );
   
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_finish_3
*/

void test_finish_3( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_finish( rbtree );
   
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_finish_4
*/

void test_finish_4( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_finish( rbtree );
   
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_finish_5
   
            4
         2      6
       1  
*/

void test_finish_5( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_finish( rbtree );
   
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_finish_6
   
            4
         2      6
            3       
*/

void test_finish_6( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_finish( rbtree );
   
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}


int
add_test_finish( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_finish", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_finish_1
   add_test_to_suite( p_suite, test_finish_1, "test_finish_1" );

   // test_finish_2
   add_test_to_suite( p_suite, test_finish_2, "test_finish_2" );

   // test_finish_3
   add_test_to_suite( p_suite, test_finish_3, "test_finish_3" );

   // test_finish_4
   add_test_to_suite( p_suite, test_finish_4, "test_finish_4" );

   // test_finish_5
   add_test_to_suite( p_suite, test_finish_5, "test_finish_5" );

   // test_finish_6
   add_test_to_suite( p_suite, test_finish_6, "test_finish_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


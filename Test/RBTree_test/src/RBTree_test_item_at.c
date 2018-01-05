/**
 @file RBTree_test_item_at.c
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
   test_item_at_1
*/

void test_item_at_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_2
*/

void test_item_at_2( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_3
*/

void test_item_at_3( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_4
*/

void test_item_at_4( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_5
   
            4
         2      6
       1  
*/

void test_item_at_5( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
  
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_6
   
            4
         2      6
            3       
*/

void test_item_at_6( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_7
   
            4
         2      6
              5 
*/

void test_item_at_7( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 5 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_item_at_8
   
            4
         2      6
                  7   
*/

void test_item_at_8( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );\

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );

   i_rbtree_forth( rbtree );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 7 );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

int
add_test_item_at( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item_at", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_at_1
   add_test_to_suite( p_suite, test_item_at_1, "test_item_at_1" );

   // test_item_at_2
   add_test_to_suite( p_suite, test_item_at_2, "test_item_at_2" );

   // test_item_at_3
   add_test_to_suite( p_suite, test_item_at_3, "test_item_at_3" );

   // test_item_at_4
   add_test_to_suite( p_suite, test_item_at_4, "test_item_at_4" );

   // test_item_at_5
   add_test_to_suite( p_suite, test_item_at_5, "test_item_at_5" );

   // test_item_at_6
   add_test_to_suite( p_suite, test_item_at_6, "test_item_at_6" );

   // test_item_at_7
   add_test_to_suite( p_suite, test_item_at_7, "test_item_at_7" );

   // test_item_at_8
   add_test_to_suite( p_suite, test_item_at_8, "test_item_at_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


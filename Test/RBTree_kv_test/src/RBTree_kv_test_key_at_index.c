/**
 @file RBTree_test_key_at_index.c
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

#include "ii_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_key_at_index_1
*/

void test_key_at_index_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 1 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_2
*/

void test_key_at_index_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 1 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 3 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_3
*/

void test_key_at_index_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 1 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 3 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_4
*/

void test_key_at_index_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 1 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 3 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_5
   
            4
         2      6
       1  
*/

void test_key_at_index_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 1 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 4 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 3 ) == 6 );
  
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_6
   
            4
         2      6
            3       
*/

void test_key_at_index_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 3 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 4 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 3 ) == 6 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_7
   
            4
         2      6
              5 
*/

void test_key_at_index_7( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 4 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 5 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 3 ) == 6 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

/**
   test_key_at_index_8
   
            4
         2      6
                  7   
*/

void test_key_at_index_8( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 0 ) == 2 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 1 ) == 4 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 2 ) == 6 );
   CU_ASSERT( ii_rbtree_kv_key_at_index( rbtree, 3 ) == 7 );
 
   ii_rbtree_kv_dispose( rbtree );
   
   return;
}

int
add_test_key_at_index( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_key_at_index", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_key_at_index_1
   add_test_to_suite( p_suite, test_key_at_index_1, "test_key_at_index_1" );

   // test_key_at_index_2
   add_test_to_suite( p_suite, test_key_at_index_2, "test_key_at_index_2" );

   // test_key_at_index_3
   add_test_to_suite( p_suite, test_key_at_index_3, "test_key_at_index_3" );

   // test_key_at_index_4
   add_test_to_suite( p_suite, test_key_at_index_4, "test_key_at_index_4" );

   // test_key_at_index_5
   add_test_to_suite( p_suite, test_key_at_index_5, "test_key_at_index_5" );

   // test_key_at_index_6
   add_test_to_suite( p_suite, test_key_at_index_6, "test_key_at_index_6" );

   // test_key_at_index_7
   add_test_to_suite( p_suite, test_key_at_index_7, "test_key_at_index_7" );

   // test_key_at_index_8
   add_test_to_suite( p_suite, test_key_at_index_8, "test_key_at_index_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


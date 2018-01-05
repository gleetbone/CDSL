/**
 @file AVLTree_test_item_at_index.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_AVLTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_item_at_index_1
*/

void test_item_at_index_1( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 10 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_2
*/

void test_item_at_index_2( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 10 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 30 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_3
*/

void test_item_at_index_3( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 30, 3 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 10 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 30 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_4
*/

void test_item_at_index_4( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 10, 1 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 10 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 30 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_5
   
            4
         2      6
       1  
*/

void test_item_at_index_5( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 10, 1 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 10 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 40 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 3 ) == 60 );
  
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_6
   
            4
         2      6
            3       
*/

void test_item_at_index_6( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 30, 3 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 30 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 40 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 3 ) == 60 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_7
   
            4
         2      6
              5 
*/

void test_item_at_index_7( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 50, 5 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 40 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 50 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 3 ) == 60 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

/**
   test_item_at_index_8
   
            4
         2      6
                  7   
*/

void test_item_at_index_8( void )
{
   ii_avltree_kv_t *avltree = NULL;
   
   avltree = ii_avltree_kv_make();
   
   ii_avltree_kv_put( avltree, 40, 4 );
   ii_avltree_kv_put( avltree, 20, 2 );
   ii_avltree_kv_put( avltree, 60, 6 );
   ii_avltree_kv_put( avltree, 70, 7 );
   
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 0 ) == 20 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 1 ) == 40 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 2 ) == 60 );
   CU_ASSERT( ii_avltree_kv_item_at_index( avltree, 3 ) == 70 );
 
   ii_avltree_kv_dispose( avltree );

   return;
}

int
add_test_item_at_index( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item_at_index", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_at_index_1
   add_test_to_suite( p_suite, test_item_at_index_1, "test_item_at_index_1" );

   // test_item_at_index_2
   add_test_to_suite( p_suite, test_item_at_index_2, "test_item_at_index_2" );

   // test_item_at_index_3
   add_test_to_suite( p_suite, test_item_at_index_3, "test_item_at_index_3" );

   // test_item_at_index_4
   add_test_to_suite( p_suite, test_item_at_index_4, "test_item_at_index_4" );

   // test_item_at_index_5
   add_test_to_suite( p_suite, test_item_at_index_5, "test_item_at_index_5" );

   // test_item_at_index_6
   add_test_to_suite( p_suite, test_item_at_index_6, "test_item_at_index_6" );

   // test_item_at_index_7
   add_test_to_suite( p_suite, test_item_at_index_7, "test_item_at_index_7" );

   // test_item_at_index_8
   add_test_to_suite( p_suite, test_item_at_index_8, "test_item_at_index_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file BSTree_test_go.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_go_1
*/

void test_go_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
   
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_2
*/

void test_go_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 30 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_3
*/

void test_go_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 30 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_4
*/

void test_go_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 30 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_5
   
            4
         2      6
       1  
*/

void test_go_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 10 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 40 );
 
   ii_bstree_kv_go( bstree, 3 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 60 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_6
   
            4
         2      6
            3       
*/

void test_go_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 30 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 40 );
 
   ii_bstree_kv_go( bstree, 3 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 60 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_7
   
            4
         2      6
              5 
*/

void test_go_7( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 50, 5 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 40 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 50 );
 
   ii_bstree_kv_go( bstree, 3 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 60 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

/**
   test_go_8
   
            4
         2      6
                  7   
*/

void test_go_8( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_go( bstree, 0 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 20 );
 
   ii_bstree_kv_go( bstree, 1 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 40 );
 
   ii_bstree_kv_go( bstree, 2 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 60 );

   ii_bstree_kv_go( bstree, 3 );
   CU_ASSERT( ii_bstree_kv_item_at( bstree ) == 70 );
 
   ii_bstree_kv_dispose( bstree );

   return;
}

int
add_test_go( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_go", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_go_1
   add_test_to_suite( p_suite, test_go_1, "test_go_1" );

   // test_go_2
   add_test_to_suite( p_suite, test_go_2, "test_go_2" );

   // test_go_3
   add_test_to_suite( p_suite, test_go_3, "test_go_3" );

   // test_go_4
   add_test_to_suite( p_suite, test_go_4, "test_go_4" );

   // test_go_5
   add_test_to_suite( p_suite, test_go_5, "test_go_5" );

   // test_go_6
   add_test_to_suite( p_suite, test_go_6, "test_go_6" );

   // test_go_7
   add_test_to_suite( p_suite, test_go_7, "test_go_7" );

   // test_go_8
   add_test_to_suite( p_suite, test_go_8, "test_go_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file AVLTree_test_back.c
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

#include "i_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_back_1
*/

void test_back_1( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 0 );
   
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_2
*/

void test_back_2( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_3
*/

void test_back_3( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_4
*/

void test_back_4( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_5
   
            4
         2      6
       1  
*/

void test_back_5( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
  
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_6
   
            4
         2      6
            3       
*/

void test_back_6( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_7
   
            4
         2      6
              5 
*/

void test_back_7( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 5 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

/**
   test_back_8
   
            4
         2      6
                  7   
*/

void test_back_8( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_finish( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 7 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_back( avltree );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_dispose( avltree );

   return;
}

int
add_test_back( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_back", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_back_1
   add_test_to_suite( p_suite, test_back_1, "test_back_1" );

   // test_back_2
   add_test_to_suite( p_suite, test_back_2, "test_back_2" );

   // test_back_3
   add_test_to_suite( p_suite, test_back_3, "test_back_3" );

   // test_back_4
   add_test_to_suite( p_suite, test_back_4, "test_back_4" );

   // test_back_5
   add_test_to_suite( p_suite, test_back_5, "test_back_5" );

   // test_back_6
   add_test_to_suite( p_suite, test_back_6, "test_back_6" );

   // test_back_7
   add_test_to_suite( p_suite, test_back_7, "test_back_7" );

   // test_back_8
   add_test_to_suite( p_suite, test_back_8, "test_back_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file RBTree_test_item.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"
#include "s_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_item_1
*/

void test_item_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 1 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 1 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 3 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 1 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 3 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_4
*/

void test_item_4( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 1 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 3 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_5
   
            4
         2      6
       1  
*/

void test_item_5( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 1 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 4 );
   CU_ASSERT( i_rbtree_item( rbtree, 3 ) == 6 );
  
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_6
   
            4
         2      6
            3       
*/

void test_item_6( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 3 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 4 );
   CU_ASSERT( i_rbtree_item( rbtree, 3 ) == 6 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_7
   
            4
         2      6
              5 
*/

void test_item_7( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 4 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 5 );
   CU_ASSERT( i_rbtree_item( rbtree, 3 ) == 6 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_8
   
            4
         2      6
                  7   
*/

void test_item_8( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   CU_ASSERT( i_rbtree_item( rbtree, 0 ) == 2 );
   CU_ASSERT( i_rbtree_item( rbtree, 1 ) == 4 );
   CU_ASSERT( i_rbtree_item( rbtree, 2 ) == 6 );
   CU_ASSERT( i_rbtree_item( rbtree, 3 ) == 7 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_item_9
   
            4
         2      6
                  7   
*/

void test_item_9( void )
{
   s_rbtree_t *rbtree = NULL;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   rbtree = s_rbtree_make();
   
   s_rbtree_put( rbtree, s4 );
   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s6 );
   s_rbtree_put( rbtree, s7 );
   
   CU_ASSERT( s_rbtree_item( rbtree, 0 ) == s2 );
   CU_ASSERT( s_rbtree_item( rbtree, 1 ) == s4 );
   CU_ASSERT( s_rbtree_item( rbtree, 2 ) == s6 );
   CU_ASSERT( s_rbtree_item( rbtree, 3 ) == s7 );
 
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_item( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_1
   add_test_to_suite( p_suite, test_item_1, "test_item_1" );

   // test_item_2
   add_test_to_suite( p_suite, test_item_2, "test_item_2" );

   // test_item_3
   add_test_to_suite( p_suite, test_item_3, "test_item_3" );

   // test_item_4
   add_test_to_suite( p_suite, test_item_4, "test_item_4" );

   // test_item_5
   add_test_to_suite( p_suite, test_item_5, "test_item_5" );

   // test_item_6
   add_test_to_suite( p_suite, test_item_6, "test_item_6" );

   // test_item_7
   add_test_to_suite( p_suite, test_item_7, "test_item_7" );

   // test_item_8
   add_test_to_suite( p_suite, test_item_8, "test_item_8" );

   // test_item_9
   add_test_to_suite( p_suite, test_item_9, "test_item_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


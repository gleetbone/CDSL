/**
 @file AVLTree_test_item.c
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
   test_item_1
*/

void test_item_1( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 1 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 3 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 1 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 3 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_item_4
*/

void test_item_4( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 1 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 3 );
 
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 1 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 4 );
   CU_ASSERT( i_avltree_item( avltree, 3 ) == 6 );
  
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 3 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 3 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 4 );
   CU_ASSERT( i_avltree_item( avltree, 3 ) == 6 );
 
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 4 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 5 );
   CU_ASSERT( i_avltree_item( avltree, 3 ) == 6 );
 
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 7 );
   
   CU_ASSERT( i_avltree_item( avltree, 0 ) == 2 );
   CU_ASSERT( i_avltree_item( avltree, 1 ) == 4 );
   CU_ASSERT( i_avltree_item( avltree, 2 ) == 6 );
   CU_ASSERT( i_avltree_item( avltree, 3 ) == 7 );
 
   i_avltree_dispose( &avltree );

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
   s_avltree_t *avltree = NULL;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   avltree = s_avltree_make();
   
   s_avltree_put( avltree, s4 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s6 );
   s_avltree_put( avltree, s7 );
   
   CU_ASSERT( s_avltree_item( avltree, 0 ) == s2 );
   CU_ASSERT( s_avltree_item( avltree, 1 ) == s4 );
   CU_ASSERT( s_avltree_item( avltree, 2 ) == s6 );
   CU_ASSERT( s_avltree_item( avltree, 3 ) == s7 );
 
   s_avltree_deep_dispose( &avltree );

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

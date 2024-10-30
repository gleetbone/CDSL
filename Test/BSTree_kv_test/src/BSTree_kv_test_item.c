/**
 @file BSTree_test_item.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "ss_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_item_1
*/

void test_item_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 10 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 10 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 30 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 10 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 30 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_item_4
*/

void test_item_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 10 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 30 );
 
   ii_bstree_kv_dispose( &bstree );

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
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 10 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 40 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 3 ) == 60 );
  
   ii_bstree_kv_dispose( &bstree );

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
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 30 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 40 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 3 ) == 60 );
 
   ii_bstree_kv_dispose( &bstree );

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
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 50, 5 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 40 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 50 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 3 ) == 60 );
 
   ii_bstree_kv_dispose( &bstree );

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
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   CU_ASSERT( ii_bstree_kv_item( bstree, 0 ) == 20 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 1 ) == 40 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 2 ) == 60 );
   CU_ASSERT( ii_bstree_kv_item( bstree, 3 ) == 70 );
 
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_item_9
*/

void test_item_9( void )
{
   ss_bstree_kv_t *bstree = NULL;
   
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   string_t *s7 = NULL;
   string_t *s70 = NULL;
   
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "60" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   
   bstree = ss_bstree_kv_make();
   
   ss_bstree_kv_put( bstree, s40, s4 );
   ss_bstree_kv_put( bstree, s20, s2 );
   ss_bstree_kv_put( bstree, s60, s6 );
   ss_bstree_kv_put( bstree, s70, s7 );
   
   CU_ASSERT( ss_bstree_kv_item( bstree, 0 ) == s20 );
   CU_ASSERT( ss_bstree_kv_item( bstree, 1 ) == s40 );
   CU_ASSERT( ss_bstree_kv_item( bstree, 2 ) == s60 );
   CU_ASSERT( ss_bstree_kv_item( bstree, 3 ) == s70 );
 
   ss_bstree_kv_deep_dispose( &bstree );

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


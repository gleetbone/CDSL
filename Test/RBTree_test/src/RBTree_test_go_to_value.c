/**
 @file RBTree_test_go_to_value.c
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
   test_go_to_value_1
*/

void test_go_to_value_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_go_to_value( rbtree, 0 );

   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_1a
*/

void test_go_to_value_1a( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
   
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
   
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_2
*/

void test_go_to_value_2( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_3
*/

void test_go_to_value_3( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_4
*/

void test_go_to_value_4( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
  
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_5
   
            4
         2      6
       1  
*/

void test_go_to_value_5( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 5 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 6 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_go_to_value( rbtree, 10 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_6
   
            4
         2      6
            3       
*/

void test_go_to_value_6( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 3 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 5 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 6 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_go_to_value( rbtree, 10 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_7
   
            4
         2      6
              5 
*/

void test_go_to_value_7( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 5 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 5 );
 
   i_rbtree_go_to_value( rbtree, 6 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_go_to_value( rbtree, 10 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_8
   
            4
         2      6
                  7   
*/

void test_go_to_value_8( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_go_to_value( rbtree, 0 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 1 );
   CU_ASSERT( i_rbtree_off( rbtree ) == 1 );
 
   i_rbtree_go_to_value( rbtree, 2 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 3 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 2 );
 
   i_rbtree_go_to_value( rbtree, 4 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 5 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 4 );
 
   i_rbtree_go_to_value( rbtree, 6 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 6 );
 
   i_rbtree_go_to_value( rbtree, 7 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 7 );
 
   i_rbtree_go_to_value( rbtree, 10 );
   CU_ASSERT( i_rbtree_item_at( rbtree ) == 7 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_go_to_value_9
   
            4
         2      6
                  7   
*/

void test_go_to_value_9( void )
{
   s_rbtree_t *rbtree = NULL;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   string_t *s0 = string_make_from_cstring( "0" );
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s5 = string_make_from_cstring( "5" );
   string_t *s9 = string_make_from_cstring( "9" );
   
   rbtree = s_rbtree_make();
   
   s_rbtree_put( rbtree, s4 );
   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s6 );
   s_rbtree_put( rbtree, s7 );
   
   s_rbtree_go_to_value( rbtree, s0 );
   CU_ASSERT( s_rbtree_off( rbtree ) == 1 );
 
   s_rbtree_go_to_value( rbtree, s1 );
   CU_ASSERT( s_rbtree_off( rbtree ) == 1 );
 
   s_rbtree_go_to_value( rbtree, s2 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s2 );
 
   s_rbtree_go_to_value( rbtree, s3 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s2 );
 
   s_rbtree_go_to_value( rbtree, s4 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s4 );
 
   s_rbtree_go_to_value( rbtree, s5 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s4 );
 
   s_rbtree_go_to_value( rbtree, s6 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s6 );
 
   s_rbtree_go_to_value( rbtree, s7 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s7 );
 
   s_rbtree_go_to_value( rbtree, s9 );
   CU_ASSERT( s_rbtree_item_at( rbtree ) == s7 );
 
   string_deep_dispose( &s0 );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s3 );
   string_deep_dispose( &s5 );
   string_deep_dispose( &s9 );
   
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_go_to_value( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_go_to_value", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_go_to_value_1
   add_test_to_suite( p_suite, test_go_to_value_1, "test_go_to_value_1" );

   // test_go_to_value_1a
   add_test_to_suite( p_suite, test_go_to_value_1a, "test_go_to_value_1a" );

   // test_go_to_value_2
   add_test_to_suite( p_suite, test_go_to_value_2, "test_go_to_value_2" );

   // test_go_to_value_3
   add_test_to_suite( p_suite, test_go_to_value_3, "test_go_to_value_3" );

   // test_go_to_value_4
   add_test_to_suite( p_suite, test_go_to_value_4, "test_go_to_value_4" );

   // test_go_to_value_5
   add_test_to_suite( p_suite, test_go_to_value_5, "test_go_to_value_5" );

   // test_go_to_value_6
   add_test_to_suite( p_suite, test_go_to_value_6, "test_go_to_value_6" );

   // test_go_to_value_7
   add_test_to_suite( p_suite, test_go_to_value_7, "test_go_to_value_7" );

   // test_go_to_value_8
   add_test_to_suite( p_suite, test_go_to_value_8, "test_go_to_value_8" );

   // test_go_to_value_9
   add_test_to_suite( p_suite, test_go_to_value_9, "test_go_to_value_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


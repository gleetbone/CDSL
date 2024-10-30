/**
 @file AVLTree_test_go_to_value.c
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
   test_go_to_value_1
*/

void test_go_to_value_1( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_go_to_value( avltree, 0 );

   CU_ASSERT( i_avltree_off( avltree ) == 1 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_go_to_value_1a
*/

void test_go_to_value_1a( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
   
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
   
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_go_to_value_2
*/

void test_go_to_value_2( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_go_to_value_3
*/

void test_go_to_value_3( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_go_to_value_4
*/

void test_go_to_value_4( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
  
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 5 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 6 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_go_to_value( avltree, 10 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 3 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 5 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 6 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_go_to_value( avltree, 10 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 5 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 5 );
 
   i_avltree_go_to_value( avltree, 6 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_go_to_value( avltree, 10 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_go_to_value( avltree, 0 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 1 );
   CU_ASSERT( i_avltree_off( avltree ) == 1 );
 
   i_avltree_go_to_value( avltree, 2 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 3 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 2 );
 
   i_avltree_go_to_value( avltree, 4 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 5 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 4 );
 
   i_avltree_go_to_value( avltree, 6 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 6 );
 
   i_avltree_go_to_value( avltree, 7 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 7 );
 
   i_avltree_go_to_value( avltree, 10 );
   CU_ASSERT( i_avltree_item_at( avltree ) == 7 );
 
   i_avltree_dispose( &avltree );

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
   s_avltree_t *avltree = NULL;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   string_t *s0 = string_make_from_cstring( "0" );
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s5 = string_make_from_cstring( "5" );
   string_t *s9 = string_make_from_cstring( "9" );
   
   avltree = s_avltree_make();
   
   s_avltree_put( avltree, s4 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s6 );
   s_avltree_put( avltree, s7 );
   
   s_avltree_go_to_value( avltree, s0 );
   CU_ASSERT( s_avltree_off( avltree ) == 1 );
 
   s_avltree_go_to_value( avltree, s1 );
   CU_ASSERT( s_avltree_off( avltree ) == 1 );
 
   s_avltree_go_to_value( avltree, s2 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s2 );
 
   s_avltree_go_to_value( avltree, s3 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s2 );
 
   s_avltree_go_to_value( avltree, s4 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s4 );
 
   s_avltree_go_to_value( avltree, s5 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s4 );
 
   s_avltree_go_to_value( avltree, s6 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s6 );
 
   s_avltree_go_to_value( avltree, s7 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s7 );
 
   s_avltree_go_to_value( avltree, s9 );
   CU_ASSERT( s_avltree_item_at( avltree ) == s7 );
 
   string_deep_dispose( &s0 );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s3 );
   string_deep_dispose( &s5 );
   string_deep_dispose( &s9 );
   
   s_avltree_deep_dispose( &avltree );

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


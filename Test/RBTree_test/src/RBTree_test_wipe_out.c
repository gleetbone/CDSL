/**
 @file RBTree_test_wipe_out.c
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
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_wipe_out( rbtree );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
  
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_2a
*/

void test_wipe_out_2a( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_2b
*/

void test_wipe_out_2b( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_3a
*/

void test_wipe_out_3a( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_3b
*/

void test_wipe_out_3b( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_4a
*/

void test_wipe_out_4a( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_4b
*/

void test_wipe_out_4b( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5a
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5a( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5b
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5b( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5c
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5c( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5d
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5d( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5e
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5e( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_5f
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_5f( void )
{
   i_rbtree_t *rbtree = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_wipe_out( rbtree );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
   
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_6
*/

void test_wipe_out_6( void )
{
   i_rbtree_t *rbtree = NULL;
   i_rbtree_cursor_t *cursor = NULL;

   rbtree = i_rbtree_make();
   cursor = i_rbtree_cursor_make( rbtree );

   i_rbtree_put( rbtree, 1 );

   i_rbtree_wipe_out( rbtree );

   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );

   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_wipe_out_7
*/

void test_wipe_out_7( void )
{
   s_rbtree_t *rbtree = NULL;
   s_rbtree_cursor_t *cursor = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   
   rbtree = s_rbtree_make();
   cursor = s_rbtree_cursor_make( rbtree );

   s_rbtree_put( rbtree, s1 );

   s_rbtree_wipe_out( rbtree );

   CU_ASSERT( s_rbtree_count( rbtree ) == 0 );

   string_deep_dispose( &s1 );
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );
   add_test_to_suite( p_suite, test_wipe_out_2a, "test_wipe_out_2a" );
   add_test_to_suite( p_suite, test_wipe_out_2b, "test_wipe_out_2b" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );
   add_test_to_suite( p_suite, test_wipe_out_3a, "test_wipe_out_3a" );
   add_test_to_suite( p_suite, test_wipe_out_3b, "test_wipe_out_3b" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );
   add_test_to_suite( p_suite, test_wipe_out_4a, "test_wipe_out_4a" );
   add_test_to_suite( p_suite, test_wipe_out_4b, "test_wipe_out_4b" );

   // test_wipe_out_5
   add_test_to_suite( p_suite, test_wipe_out_5, "test_wipe_out_5" );
   add_test_to_suite( p_suite, test_wipe_out_5a, "test_wipe_out_5a" );
   add_test_to_suite( p_suite, test_wipe_out_5b, "test_wipe_out_5b" );
   add_test_to_suite( p_suite, test_wipe_out_5c, "test_wipe_out_5c" );
   add_test_to_suite( p_suite, test_wipe_out_5d, "test_wipe_out_5d" );
   add_test_to_suite( p_suite, test_wipe_out_5e, "test_wipe_out_5e" );
   add_test_to_suite( p_suite, test_wipe_out_5f, "test_wipe_out_5f" );

   // test_wipe_out_6
   add_test_to_suite( p_suite, test_wipe_out_6, "test_wipe_out_6" );

   // test_wipe_out_7
   add_test_to_suite( p_suite, test_wipe_out_7, "test_wipe_out_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


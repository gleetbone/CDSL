/**
 @file BSTree_test_wipe_out_and_dispose.c
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
   test_wipe_out_and_dispose_1
*/

void test_wipe_out_and_dispose_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
   
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
  
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_2
*/

void test_wipe_out_and_dispose_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_2a
*/

void test_wipe_out_and_dispose_2a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_2b
*/

void test_wipe_out_and_dispose_2b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_3
*/

void test_wipe_out_and_dispose_3( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_3a
*/

void test_wipe_out_and_dispose_3a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_3b
*/

void test_wipe_out_and_dispose_3b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 10, 1 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_4
*/

void test_wipe_out_and_dispose_4( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_4a
*/

void test_wipe_out_and_dispose_4a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_4b
*/

void test_wipe_out_and_dispose_4b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 30, 3 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5a
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5a( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5b
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5b( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5c
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5c( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5d
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5d( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5e
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5e( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_5f
   
            4
         2      6
       1   3  5   7
*/

void test_wipe_out_and_dispose_5f( void )
{
   ii_bstree_kv_t *bstree = NULL;
   
   bstree = ii_bstree_kv_make();
   
   ii_bstree_kv_put( bstree, 40, 4 );
   ii_bstree_kv_put( bstree, 20, 2 );
   ii_bstree_kv_put( bstree, 60, 6 );
   ii_bstree_kv_put( bstree, 10, 1 );
   ii_bstree_kv_put( bstree, 30, 3 );
   ii_bstree_kv_put( bstree, 50, 5 );
   ii_bstree_kv_put( bstree, 70, 7 );
   
   ii_bstree_kv_wipe_out_and_dispose( bstree );
 
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );
   
   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_6
*/

void test_wipe_out_and_dispose_6( void )
{
   ii_bstree_kv_t *bstree = NULL;
   ii_bstree_kv_cursor_t *cursor = NULL;

   bstree = ii_bstree_kv_make();
   cursor = ii_bstree_kv_cursor_make( bstree );

   ii_bstree_kv_put( bstree, 10, 1 );

   ii_bstree_kv_wipe_out_and_dispose( bstree );

   CU_ASSERT( ii_bstree_kv_count( bstree ) == 0 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_wipe_out_and_dispose_7
*/

void test_wipe_out_and_dispose_7( void )
{
   ss_bstree_kv_t *bstree = NULL;
   ss_bstree_kv_cursor_t *cursor = NULL;

   string_t *s1 = NULL;
   string_t *s10 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   
   bstree = ss_bstree_kv_make();
   cursor = ss_bstree_kv_cursor_make( bstree );

   ss_bstree_kv_put( bstree, s10, s1 );

   ss_bstree_kv_wipe_out_and_dispose( bstree );

   CU_ASSERT( ss_bstree_kv_count( bstree ) == 0 );

   ss_bstree_kv_dispose( &bstree );

   return;
}

int
add_test_wipe_out_and_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out_and_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_and_dispose_1
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_1, "test_wipe_out_and_dispose_1" );

   // test_wipe_out_and_dispose_2
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2, "test_wipe_out_and_dispose_2" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2a, "test_wipe_out_and_dispose_2a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_2b, "test_wipe_out_and_dispose_2b" );

   // test_wipe_out_and_dispose_3
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3, "test_wipe_out_and_dispose_3" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3a, "test_wipe_out_and_dispose_3a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_3b, "test_wipe_out_and_dispose_3b" );

   // test_wipe_out_and_dispose_4
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4, "test_wipe_out_and_dispose_4" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4a, "test_wipe_out_and_dispose_4a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_4b, "test_wipe_out_and_dispose_4b" );

   // test_wipe_out_and_dispose_5
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5, "test_wipe_out_and_dispose_5" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5a, "test_wipe_out_and_dispose_5a" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5b, "test_wipe_out_and_dispose_5b" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5c, "test_wipe_out_and_dispose_5c" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5d, "test_wipe_out_and_dispose_5d" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5e, "test_wipe_out_and_dispose_5e" );
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_5f, "test_wipe_out_and_dispose_5f" );

   // test_wipe_out_and_dispose_6
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_6, "test_wipe_out_and_dispose_6" );

   // test_wipe_out_and_dispose_7
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_7, "test_wipe_out_and_dispose_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


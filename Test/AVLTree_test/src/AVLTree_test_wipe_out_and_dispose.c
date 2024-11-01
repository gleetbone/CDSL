/**
 @file AVLTree_test_wipe_out_and_dispose.c
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
   test_wipe_out_and_dispose_1
*/

void test_wipe_out_and_dispose_1( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_wipe_out_and_dispose( avltree );
   
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
  
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_1a
*/

void test_wipe_out_and_dispose_1a( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;

   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );

   i_avltree_put( avltree, 1 );

   i_avltree_wipe_out_and_dispose( avltree );

   CU_ASSERT( i_avltree_count( avltree ) == 0 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_2
*/

void test_wipe_out_and_dispose_2( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_2a
*/

void test_wipe_out_and_dispose_2a( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_2b
*/

void test_wipe_out_and_dispose_2b( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_3
*/

void test_wipe_out_and_dispose_3( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_3a
*/

void test_wipe_out_and_dispose_3a( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_3b
*/

void test_wipe_out_and_dispose_3b( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_4
*/

void test_wipe_out_and_dispose_4( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_4a
*/

void test_wipe_out_and_dispose_4a( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_4b
*/

void test_wipe_out_and_dispose_4b( void )
{
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;

   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

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
   i_avltree_t *avltree = NULL;

   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_wipe_out_and_dispose( avltree );
 
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_wipe_out_and_dispose_6
*/

void test_wipe_out_and_dispose_6( void )
{
   s_avltree_t *avltree = NULL;
   s_avltree_cursor_t *cursor = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   
   avltree = s_avltree_make();
   cursor = s_avltree_cursor_make( avltree );

   s_avltree_put( avltree, s1 );

   s_avltree_wipe_out_and_dispose( avltree );

   CU_ASSERT( s_avltree_count( avltree ) == 0 );

   s_avltree_deep_dispose( &avltree );

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
   add_test_to_suite( p_suite, test_wipe_out_and_dispose_1a, "test_wipe_out_and_dispose_1a" );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


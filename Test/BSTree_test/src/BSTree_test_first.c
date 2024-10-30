/**
 @file BSTree_test_first.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"
#include "s_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_first_1
*/

void test_first_1( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_2
*/

void test_first_2( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 1 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_3
*/

void test_first_3( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_4
*/

void test_first_4( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 1 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_5
   
            4
         2      6
       1  
*/

void test_first_5( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 1 );
  
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_6
   
            4
         2      6
            3       
*/

void test_first_6( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 3 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 2 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_7
   
            4
         2      6
              5 
*/

void test_first_7( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 5 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 2 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_8
   
            4
         2      6
                  7   
*/

void test_first_8( void )
{
   i_bstree_t *bstree = NULL;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 7 );
   
   CU_ASSERT( i_bstree_first( bstree ) == 2 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_first_9
   
            4
         2      6
                  7   
*/

void test_first_9( void )
{
   s_bstree_t *bstree = NULL;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   bstree = s_bstree_make();
   
   s_bstree_put( bstree, s4 );
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s6 );
   s_bstree_put( bstree, s7 );
   
   CU_ASSERT( s_bstree_first( bstree ) == s2 );
 
   s_bstree_deep_dispose( &bstree );

   return;
}

int
add_test_first( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_first", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_first_1
   add_test_to_suite( p_suite, test_first_1, "test_first_1" );

   // test_first_2
   add_test_to_suite( p_suite, test_first_2, "test_first_2" );

   // test_first_3
   add_test_to_suite( p_suite, test_first_3, "test_first_3" );

   // test_first_4
   add_test_to_suite( p_suite, test_first_4, "test_first_4" );

   // test_first_5
   add_test_to_suite( p_suite, test_first_5, "test_first_5" );

   // test_first_6
   add_test_to_suite( p_suite, test_first_6, "test_first_6" );

   // test_first_7
   add_test_to_suite( p_suite, test_first_7, "test_first_7" );

   // test_first_8
   add_test_to_suite( p_suite, test_first_8, "test_first_8" );

   // test_first_9
   add_test_to_suite( p_suite, test_first_9, "test_first_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


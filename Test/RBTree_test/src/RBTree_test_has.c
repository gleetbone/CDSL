/**
 @file RBTree_test_has.c
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
   test_has_1
*/

void test_has_1( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_3
*/

void test_has_3( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_4
*/

void test_has_4( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
  
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_5
   
            4
         2      6
       1  
*/

void test_has_5( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_6
   
            4
         2      6
            3       
*/

void test_has_6( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_7
   
            4
         2      6
              5 
*/

void test_has_7( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_8
   
            4
         2      6
                  7   
*/

void test_has_8( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 0 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_has_9
   
            4
         2      6
                  7   
*/

void test_has_9( void )
{
   s_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s4 = string_make_from_cstring( "4" );
   string_t *s6 = string_make_from_cstring( "6" );
   string_t *s7 = string_make_from_cstring( "7" );
   
   string_t *s0 = string_make_from_cstring( "0" );
   
   rbtree = s_rbtree_make();
   
   s_rbtree_put( rbtree, s4 );
   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s6 );
   s_rbtree_put( rbtree, s7 );
   
   result = s_rbtree_has( rbtree, s4 );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has( rbtree, s2 );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has( rbtree, s6 );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has( rbtree, s7 );
   CU_ASSERT( result == 1 );
 
   result = s_rbtree_has( rbtree, s0 );
   CU_ASSERT( result == 0 );
 
   string_deep_dispose( &s0 );
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_has( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_1
   add_test_to_suite( p_suite, test_has_1, "test_has_1" );

   // test_has_2
   add_test_to_suite( p_suite, test_has_2, "test_has_2" );

   // test_has_3
   add_test_to_suite( p_suite, test_has_3, "test_has_3" );

   // test_has_4
   add_test_to_suite( p_suite, test_has_4, "test_has_4" );

   // test_has_5
   add_test_to_suite( p_suite, test_has_5, "test_has_5" );

   // test_has_6
   add_test_to_suite( p_suite, test_has_6, "test_has_6" );

   // test_has_7
   add_test_to_suite( p_suite, test_has_7, "test_has_7" );

   // test_has_8
   add_test_to_suite( p_suite, test_has_8, "test_has_8" );

   // test_has_9
   add_test_to_suite( p_suite, test_has_9, "test_has_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


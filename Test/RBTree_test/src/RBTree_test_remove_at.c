/**
 @file RBTree_test_remove_at.c
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
   test_remove_at_1
*/

void test_remove_at_1( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   i_rbtree_remove_at( rbtree );
   
   CU_ASSERT( i_rbtree_count( rbtree ) == 0 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_2
*/

void test_remove_at_2( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_2a
*/

void test_remove_at_2a( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_2b
*/

void test_remove_at_2b( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_3
*/

void test_remove_at_3( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_3a
*/

void test_remove_at_3a( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_3b
*/

void test_remove_at_3b( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_4
*/

void test_remove_at_4( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_4a
*/

void test_remove_at_4a( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_4b
*/

void test_remove_at_4b( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_rbtree_count( rbtree ) == 2 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5a( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5b( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5c( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5d( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5e( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_5f( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );
   
   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );
 
   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );
   
   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_6

            4
         2      6
       1   3  5   7
*/

void test_remove_at_6( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = i_rbtree_make();

   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 5 );
   i_rbtree_put( rbtree, 7 );

   i_rbtree_start( rbtree );
   i_rbtree_remove_at( rbtree );

   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 0 );

   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 5 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_rbtree_count( rbtree ) == 6 );

   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_6a

            4
         2      6
       1   3  5   7
*/

void test_remove_at_6a( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = i_rbtree_make();

   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );

   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );

   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_rbtree_count( rbtree ) == 1 );

   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_6b

            4
         2      6
       1   3  5   7
*/

void test_remove_at_6b( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = i_rbtree_make();

   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 8 );
   i_rbtree_put( rbtree, 7 );
   i_rbtree_put( rbtree, 6 );

   i_rbtree_start( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_forth( rbtree );
   i_rbtree_remove_at( rbtree );

   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 6 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 7 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_rbtree_count( rbtree ) == 3 );

   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_6c

            4
         2      6
       1   3  5   7
*/

void test_remove_at_6c( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = i_rbtree_make();

   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );

   i_rbtree_start( rbtree );
   i_rbtree_remove_at( rbtree );

   result = i_rbtree_has( rbtree, 1 );
   CU_ASSERT( result == 0 );

   result = i_rbtree_has( rbtree, 2 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 3 );
   CU_ASSERT( result == 1 );

   result = i_rbtree_has( rbtree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_rbtree_count( rbtree ) == 3 );

   i_rbtree_dispose( &rbtree );

   return;
}

/**
   test_remove_at_7
*/

void test_remove_at_7( void )
{
   s_rbtree_t *rbtree = NULL;
   int32_t result = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   rbtree = s_rbtree_make();

   s_rbtree_put( rbtree, s4 );
   s_rbtree_put( rbtree, s1 );
   s_rbtree_put( rbtree, s2 );
   s_rbtree_put( rbtree, s3 );

   s_rbtree_start( rbtree );
   s_rbtree_remove_at( rbtree );

   result = s_rbtree_has( rbtree, s1 );
   CU_ASSERT( result == 0 );

   result = s_rbtree_has( rbtree, s2 );
   CU_ASSERT( result == 1 );

   result = s_rbtree_has( rbtree, s3 );
   CU_ASSERT( result == 1 );

   result = s_rbtree_has( rbtree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( s_rbtree_count( rbtree ) == 3 );

   string_deep_dispose( &s1 );
   s_rbtree_deep_dispose( &rbtree );

   return;
}

int
add_test_remove_at( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_at", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_at_1
   add_test_to_suite( p_suite, test_remove_at_1, "test_remove_at_1" );

   // test_remove_at_2
   add_test_to_suite( p_suite, test_remove_at_2, "test_remove_at_2" );
   add_test_to_suite( p_suite, test_remove_at_2a, "test_remove_at_2a" );
   add_test_to_suite( p_suite, test_remove_at_2b, "test_remove_at_2b" );

   // test_remove_at_3
   add_test_to_suite( p_suite, test_remove_at_3, "test_remove_at_3" );
   add_test_to_suite( p_suite, test_remove_at_3a, "test_remove_at_3a" );
   add_test_to_suite( p_suite, test_remove_at_3b, "test_remove_at_3b" );

   // test_remove_at_4
   add_test_to_suite( p_suite, test_remove_at_4, "test_remove_at_4" );
   add_test_to_suite( p_suite, test_remove_at_4a, "test_remove_at_4a" );
   add_test_to_suite( p_suite, test_remove_at_4b, "test_remove_at_4b" );

   // test_remove_at_5
   add_test_to_suite( p_suite, test_remove_at_5, "test_remove_at_5" );
   add_test_to_suite( p_suite, test_remove_at_5a, "test_remove_at_5a" );
   add_test_to_suite( p_suite, test_remove_at_5b, "test_remove_at_5b" );
   add_test_to_suite( p_suite, test_remove_at_5c, "test_remove_at_5c" );
   add_test_to_suite( p_suite, test_remove_at_5d, "test_remove_at_5d" );
   add_test_to_suite( p_suite, test_remove_at_5e, "test_remove_at_5e" );
   add_test_to_suite( p_suite, test_remove_at_5f, "test_remove_at_5f" );

   // test_remove_at_6
   add_test_to_suite( p_suite, test_remove_at_6, "test_remove_at_6" );
   add_test_to_suite( p_suite, test_remove_at_6a, "test_remove_at_6a" );
   add_test_to_suite( p_suite, test_remove_at_6b, "test_remove_at_6b" );
   add_test_to_suite( p_suite, test_remove_at_6c, "test_remove_at_6c" );

   // test_remove_at_7
   add_test_to_suite( p_suite, test_remove_at_7, "test_remove_at_7" );
   
   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


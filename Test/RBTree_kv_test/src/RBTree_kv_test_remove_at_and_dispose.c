/**
 @file RBTree_test_remove_at_and_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_RBTree_kv.h"
#include "ss_RBTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_at_and_dispose_1
*/

void test_remove_at_and_dispose_1( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
   
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 0 );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_2
*/

void test_remove_at_and_dispose_2( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_2a
*/

void test_remove_at_and_dispose_2a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_2b
*/

void test_remove_at_and_dispose_2b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_3
*/

void test_remove_at_and_dispose_3( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_3a
*/

void test_remove_at_and_dispose_3a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_3b
*/

void test_remove_at_and_dispose_3b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_4
*/

void test_remove_at_and_dispose_4( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_4a
*/

void test_remove_at_and_dispose_4a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_4b
*/

void test_remove_at_and_dispose_4b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 2 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_start( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5c( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5d( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5e( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_5f( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;
   
   rbtree = ii_rbtree_kv_make();
   
   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   
   ii_rbtree_kv_finish( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );
 
   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );
 
   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );
   
   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_6

            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_6( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = ii_rbtree_kv_make();

   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 60, 6 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 30, 3 );
   ii_rbtree_kv_put( rbtree, 50, 5 );
   ii_rbtree_kv_put( rbtree, 70, 7 );

   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_remove_at_and_dispose( rbtree );

   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 6 );

   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_6a

            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_6a( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = ii_rbtree_kv_make();

   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 20, 2 );

   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );

   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 1 );

   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_6b

            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_6b( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = ii_rbtree_kv_make();

   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 80, 8 );
   ii_rbtree_kv_put( rbtree, 70, 7 );
   ii_rbtree_kv_put( rbtree, 60, 6 );

   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   ii_rbtree_kv_forth( rbtree );
   
   ii_rbtree_kv_remove_at_and_dispose( rbtree );

   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 3 );

   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_6c

            4
         2      6
       1   3  5   7
*/

void test_remove_at_and_dispose_6c( void )
{
   ii_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;

   rbtree = ii_rbtree_kv_make();

   ii_rbtree_kv_put( rbtree, 40, 4 );
   ii_rbtree_kv_put( rbtree, 10, 1 );
   ii_rbtree_kv_put( rbtree, 20, 2 );
   ii_rbtree_kv_put( rbtree, 30, 3 );

   ii_rbtree_kv_start( rbtree );
   ii_rbtree_kv_remove_at_and_dispose( rbtree );

   result = ii_rbtree_kv_has( rbtree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_rbtree_kv_has( rbtree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_rbtree_kv_has( rbtree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_rbtree_kv_count( rbtree ) == 3 );

   ii_rbtree_kv_dispose( &rbtree );

   return;
}

/**
   test_remove_at_and_dispose_7
*/

void test_remove_at_and_dispose_7( void )
{
   ss_rbtree_kv_t *rbtree = NULL;
   int32_t result = 0;

   string_t *s1 = NULL;
   string_t *s10 = NULL;
   string_t *s1a = NULL;
   string_t *s10a = NULL;
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s3 = NULL;
   string_t *s30 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   
   s1 = string_make_from_cstring( "1" );
   s10 = string_make_from_cstring( "10" );
   s1a = string_make_from_cstring( "1" );
   s10a = string_make_from_cstring( "10" );
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s3 = string_make_from_cstring( "3" );
   s30 = string_make_from_cstring( "30" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   
   rbtree = ss_rbtree_kv_make();

   ss_rbtree_kv_put( rbtree, s40, s4 );
   ss_rbtree_kv_put( rbtree, s10, s1 );
   ss_rbtree_kv_put( rbtree, s20, s2 );
   ss_rbtree_kv_put( rbtree, s30, s3 );

   ss_rbtree_kv_start( rbtree );
   ss_rbtree_kv_remove_at_and_dispose( rbtree );

   result = ss_rbtree_kv_has( rbtree, s1a );
   CU_ASSERT( result == 0 );

   result = ss_rbtree_kv_has( rbtree, s2 );
   CU_ASSERT( result == 1 );

   result = ss_rbtree_kv_has( rbtree, s3 );
   CU_ASSERT( result == 1 );

   result = ss_rbtree_kv_has( rbtree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ss_rbtree_kv_count( rbtree ) == 3 );

   string_deep_dispose( &s1a );
   string_deep_dispose( &s10a );
   ss_rbtree_kv_deep_dispose( &rbtree );

   return;
}

int
add_test_remove_at_and_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_at_and_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_at_and_dispose_1
   add_test_to_suite( p_suite, test_remove_at_and_dispose_1, "test_remove_at_and_dispose_1" );

   // test_remove_at_and_dispose_2
   add_test_to_suite( p_suite, test_remove_at_and_dispose_2, "test_remove_at_and_dispose_2" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_2a, "test_remove_at_and_dispose_2a" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_2b, "test_remove_at_and_dispose_2b" );

   // test_remove_at_and_dispose_3
   add_test_to_suite( p_suite, test_remove_at_and_dispose_3, "test_remove_at_and_dispose_3" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_3a, "test_remove_at_and_dispose_3a" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_3b, "test_remove_at_and_dispose_3b" );

   // test_remove_at_and_dispose_4
   add_test_to_suite( p_suite, test_remove_at_and_dispose_4, "test_remove_at_and_dispose_4" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_4a, "test_remove_at_and_dispose_4a" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_4b, "test_remove_at_and_dispose_4b" );

   // test_remove_at_and_dispose_5
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5, "test_remove_at_and_dispose_5" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5a, "test_remove_at_and_dispose_5a" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5b, "test_remove_at_and_dispose_5b" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5c, "test_remove_at_and_dispose_5c" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5d, "test_remove_at_and_dispose_5d" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5e, "test_remove_at_and_dispose_5e" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_5f, "test_remove_at_and_dispose_5f" );

   // test_remove_at_and_dispose_6
   add_test_to_suite( p_suite, test_remove_at_and_dispose_6, "test_remove_at_and_dispose_6" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_6a, "test_remove_at_and_dispose_6a" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_6b, "test_remove_at_and_dispose_6b" );
   add_test_to_suite( p_suite, test_remove_at_and_dispose_6c, "test_remove_at_and_dispose_6c" );

   // test_remove_at_and_dispose_7
   add_test_to_suite( p_suite, test_remove_at_and_dispose_7, "test_remove_at_and_dispose_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


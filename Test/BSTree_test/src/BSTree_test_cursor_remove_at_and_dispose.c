/**
 @file BSTree_test_cursor_remove_at_and_dispose.c
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
   test_cursor_remove_at_and_dispose_1
*/

void test_cursor_remove_at_and_dispose_1( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 1 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
   
   CU_ASSERT( i_bstree_count( bstree ) == 0 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_2
*/

void test_cursor_remove_at_and_dispose_2( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_2a
*/

void test_cursor_remove_at_and_dispose_2a( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_2b
*/

void test_cursor_remove_at_and_dispose_2b( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_3
*/

void test_cursor_remove_at_and_dispose_3( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_3a
*/

void test_cursor_remove_at_and_dispose_3a( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_3b
*/

void test_cursor_remove_at_and_dispose_3b( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_4
*/

void test_cursor_remove_at_and_dispose_4( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_4a
*/

void test_cursor_remove_at_and_dispose_4a( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_4b
*/

void test_cursor_remove_at_and_dispose_4b( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5a
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5a( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5b
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5b( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5c
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5c( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5d
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5d( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5e
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5e( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_5f
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_5f( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );
   
   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_bstree_count( bstree ) == 6 );
   
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_6

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_6( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 5 );
   i_bstree_put( bstree, 7 );

   i_bstree_cursor_start( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_bstree_count( bstree ) == 6 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_6a

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_6a( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );

   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_bstree_count( bstree ) == 1 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_6b

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_6b( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 8 );
   i_bstree_put( bstree, 7 );
   i_bstree_put( bstree, 6 );

   i_bstree_cursor_start( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_forth( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_bstree_count( bstree ) == 3 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_6c

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_and_dispose_6c( void )
{
   int32_t result = 0;
   i_bstree_t *bstree = NULL;
   i_bstree_cursor_t *cursor = NULL;
   
   bstree = i_bstree_make();
   cursor = i_bstree_cursor_make( bstree );

   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );

   i_bstree_cursor_start( cursor );
   i_bstree_cursor_remove_at_and_dispose( cursor );

   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 0 );

   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );

   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_bstree_count( bstree ) == 3 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_cursor_remove_at_and_dispose_7
*/

void test_cursor_remove_at_and_dispose_7( void )
{
   int32_t result = 0;
   s_bstree_t *bstree = NULL;
   s_bstree_cursor_t *cursor = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s1a = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   bstree = s_bstree_make();
   cursor = s_bstree_cursor_make( bstree );

   s_bstree_put( bstree, s4 );
   s_bstree_put( bstree, s1 );
   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s3 );

   s_bstree_cursor_start( cursor );
   s_bstree_cursor_remove_at_and_dispose( cursor );

   result = s_bstree_has( bstree, s1a );
   CU_ASSERT( result == 0 );

   result = s_bstree_has( bstree, s2 );
   CU_ASSERT( result == 1 );

   result = s_bstree_has( bstree, s3 );
   CU_ASSERT( result == 1 );

   result = s_bstree_has( bstree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( s_bstree_count( bstree ) == 3 );

   string_deep_dispose( &s1a );
   s_bstree_deep_dispose( &bstree );

   return;
}

int
add_test_cursor_remove_at_and_dispose( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_remove_at_and_dispose", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_remove_at_and_dispose_1
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_1, "test_cursor_remove_at_and_dispose_1" );

   // test_cursor_remove_at_and_dispose_2
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_2, "test_cursor_remove_at_and_dispose_2" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_2a, "test_cursor_remove_at_and_dispose_2a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_2b, "test_cursor_remove_at_and_dispose_2b" );

   // test_cursor_remove_at_and_dispose_3
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_3, "test_cursor_remove_at_and_dispose_3" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_3a, "test_cursor_remove_at_and_dispose_3a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_3b, "test_cursor_remove_at_and_dispose_3b" );

   // test_cursor_remove_at_and_dispose_4
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_4, "test_cursor_remove_at_and_dispose_4" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_4a, "test_cursor_remove_at_and_dispose_4a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_4b, "test_cursor_remove_at_and_dispose_4b" );

   // test_cursor_remove_at_and_dispose_5
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5, "test_cursor_remove_at_and_dispose_5" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5a, "test_cursor_remove_at_and_dispose_5a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5b, "test_cursor_remove_at_and_dispose_5b" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5c, "test_cursor_remove_at_and_dispose_5c" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5d, "test_cursor_remove_at_and_dispose_5d" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5e, "test_cursor_remove_at_and_dispose_5e" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_5f, "test_cursor_remove_at_and_dispose_5f" );

   // test_cursor_remove_at_and_dispose_6
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_6, "test_cursor_remove_at_and_dispose_6" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_6a, "test_cursor_remove_at_and_dispose_6a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_6b, "test_cursor_remove_at_and_dispose_6b" );
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_6c, "test_cursor_remove_at_and_dispose_6c" );

   // test_cursor_remove_at_and_dispose_7
   add_test_to_suite( p_suite, test_cursor_remove_at_and_dispose_7, "test_cursor_remove_at_and_dispose_7" );
   
   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


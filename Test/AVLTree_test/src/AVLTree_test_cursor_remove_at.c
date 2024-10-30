/**
 @file AVLTree_test_cursor_remove_at.c
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
   test_cursor_remove_at_1
*/

void test_cursor_remove_at_1( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_remove_at( cursor );
   
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_2
*/

void test_cursor_remove_at_2( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_2a
*/

void test_cursor_remove_at_2a( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_2b
*/

void test_cursor_remove_at_2b( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_3
*/

void test_cursor_remove_at_3( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_3a
*/

void test_cursor_remove_at_3a( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_3b
*/

void test_cursor_remove_at_3b( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_4
*/

void test_cursor_remove_at_4( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_4a
*/

void test_cursor_remove_at_4a( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_4b
*/

void test_cursor_remove_at_4b( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
  
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5a
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5a( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5b
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5b( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5c
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5c( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5d
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5d( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5e
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5e( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_5f
   
            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_5f( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 6 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_6

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_6( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_cursor_start( cursor );
   i_avltree_cursor_remove_at( cursor );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 6 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_6a

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_6a( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );

   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 1 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_6b

            4
         2      6
       1   3  5   7
*/

void test_cursor_remove_at_6b( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 7 );
   i_avltree_put( avltree, 6 );

   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_forth( cursor );
   i_avltree_cursor_remove_at( cursor );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 3 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_6c
*/

void test_cursor_remove_at_6c( void )
{
   int32_t result = 0;
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );

   i_avltree_cursor_start( cursor );
   i_avltree_cursor_remove_at( cursor );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 3 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_cursor_remove_at_7
*/

void test_cursor_remove_at_7( void )
{
   int32_t result = 0;
   s_avltree_t *avltree = NULL;
   s_avltree_cursor_t *cursor = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   avltree = s_avltree_make();
   cursor = s_avltree_cursor_make( avltree );

   s_avltree_put( avltree, s4 );
   s_avltree_put( avltree, s1 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s3 );

   s_avltree_cursor_start( cursor );
   s_avltree_cursor_remove_at( cursor );

   result = s_avltree_has( avltree, s1 );
   CU_ASSERT( result == 0 );

   result = s_avltree_has( avltree, s2 );
   CU_ASSERT( result == 1 );

   result = s_avltree_has( avltree, s3 );
   CU_ASSERT( result == 1 );

   result = s_avltree_has( avltree, s4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( s_avltree_count( avltree ) == 3 );

   string_deep_dispose( &s1 );
   s_avltree_deep_dispose( &avltree );

   return;
}

int
add_test_cursor_remove_at( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_remove_at", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_remove_at_1
   add_test_to_suite( p_suite, test_cursor_remove_at_1, "test_cursor_remove_at_1" );

   // test_cursor_remove_at_2
   add_test_to_suite( p_suite, test_cursor_remove_at_2, "test_cursor_remove_at_2" );
   add_test_to_suite( p_suite, test_cursor_remove_at_2a, "test_cursor_remove_at_2a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_2b, "test_cursor_remove_at_2b" );

   // test_cursor_remove_at_3
   add_test_to_suite( p_suite, test_cursor_remove_at_3, "test_cursor_remove_at_3" );
   add_test_to_suite( p_suite, test_cursor_remove_at_3a, "test_cursor_remove_at_3a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_3b, "test_cursor_remove_at_3b" );

   // test_cursor_remove_at_4
   add_test_to_suite( p_suite, test_cursor_remove_at_4, "test_cursor_remove_at_4" );
   add_test_to_suite( p_suite, test_cursor_remove_at_4a, "test_cursor_remove_at_4a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_4b, "test_cursor_remove_at_4b" );

   // test_cursor_remove_at_5
   add_test_to_suite( p_suite, test_cursor_remove_at_5, "test_cursor_remove_at_5" );
   add_test_to_suite( p_suite, test_cursor_remove_at_5a, "test_cursor_remove_at_5a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_5b, "test_cursor_remove_at_5b" );
   add_test_to_suite( p_suite, test_cursor_remove_at_5c, "test_cursor_remove_at_5c" );
   add_test_to_suite( p_suite, test_cursor_remove_at_5d, "test_cursor_remove_at_5d" );
   add_test_to_suite( p_suite, test_cursor_remove_at_5e, "test_cursor_remove_at_5e" );
   add_test_to_suite( p_suite, test_cursor_remove_at_5f, "test_cursor_remove_at_5f" );

   // test_cursor_remove_at_6
   add_test_to_suite( p_suite, test_cursor_remove_at_6, "test_cursor_remove_at_6" );
   add_test_to_suite( p_suite, test_cursor_remove_at_6a, "test_cursor_remove_at_6a" );
   add_test_to_suite( p_suite, test_cursor_remove_at_6b, "test_cursor_remove_at_6b" );
   add_test_to_suite( p_suite, test_cursor_remove_at_6c, "test_cursor_remove_at_6c" );

   // test_cursor_remove_at_7
   add_test_to_suite( p_suite, test_cursor_remove_at_7, "test_cursor_remove_at_7" );
   
   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


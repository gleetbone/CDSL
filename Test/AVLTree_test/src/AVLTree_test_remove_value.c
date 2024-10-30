/**
 @file AVLTree_test_remove_value.c
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
#include <math.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_remove_value_1
*/

void test_remove_value_1( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_value( avltree, 1 );
   
   CU_ASSERT( i_avltree_count( avltree ) == 0 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_2
*/

void test_remove_value_2( void )
{
   i_avltree_t *avltree = NULL;
   i_avltree_cursor_t *cursor = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   cursor = i_avltree_cursor_make( avltree );
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_cursor_start( cursor );
   i_avltree_cursor_forth( cursor );

   i_avltree_remove_value( avltree, 2 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   CU_ASSERT( i_avltree_cursor_item_at( cursor ) == 3 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_2a
*/

void test_remove_value_2a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_value( avltree, 1 );
 
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
   test_remove_value_2b
*/

void test_remove_value_2b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_value( avltree, 3 );
 
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
   test_remove_value_3
*/

void test_remove_value_3( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_value( avltree, 2 );
 
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
   test_remove_value_3a
*/

void test_remove_value_3a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_value( avltree, 1 );
 
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
   test_remove_value_3b
*/

void test_remove_value_3b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   i_avltree_remove_value( avltree, 3 );
 
   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );
 
   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );
 
   CU_ASSERT( i_avltree_count( avltree ) == 2 );
   
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_4
*/

void test_remove_value_4( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_value( avltree, 2 );
 
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
   test_remove_value_4a
*/

void test_remove_value_4a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_value( avltree, 1 );
 
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
   test_remove_value_4b
*/

void test_remove_value_4b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   i_avltree_remove_value( avltree, 3 );
 
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
   test_remove_value_5
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 4 );
 
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
   test_remove_value_5a
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 1 );
 
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
   test_remove_value_5b
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 2 );
 
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
   test_remove_value_5c
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5c( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 3 );
 
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
   test_remove_value_5d
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5d( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 5 );
 
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
   test_remove_value_5e
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5e( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 6 );
 
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
   test_remove_value_5f
   
            4
         2      6
       1   3  5   7
*/

void test_remove_value_5f( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   
   i_avltree_remove_value( avltree, 7 );
 
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
   test_remove_value_6

            4
         2
       1   3
*/

void test_remove_value_6( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_value( avltree, 4 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 3 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_6a

            4
         2
       1   3
*/

void test_remove_value_6a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_value( avltree, 2 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 1 );
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
   test_remove_value_7

            4
                6
              5   7
*/

void test_remove_value_7( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_remove_value( avltree, 4 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 3 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_8

               5
            4
         2
       1   3
*/

void test_remove_value_8( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_value( avltree, 5 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 4 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_9

         3
            4
                6
              5   7
*/

void test_remove_value_9( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_remove_value( avltree, 3 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 4 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_10

                  6
               5
            4
         2
       1   3
*/

void test_remove_value_10( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_value( avltree, 6 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 5 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_11

      2
         3
            4
                6
              5   7
*/

void test_remove_value_11( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_remove_value( avltree, 2 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( i_avltree_count( avltree ) == 5 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_12

                  6
               5
            4
         2
       1   3
*/

void test_remove_value_12( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_value( avltree, 5 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 5 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_13

      2
         3
            4
                6
              5   7
*/

void test_remove_value_13( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_remove_value( avltree, 3 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 5 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_14

                  8
            4               12
         2       6      10       14
       1   3   5   7   9  11   13   15
*/

void test_remove_value_14( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 4 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 14 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_14a

                  8
            4               12
         2       6      10       14
       1   3   5   7   9  11   13   15
*/

void test_remove_value_14a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 12 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 14 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_15

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_15( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 24 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 20 );
   i_avltree_put( avltree, 28 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 18 );
   i_avltree_put( avltree, 22 );
   i_avltree_put( avltree, 26 );
   i_avltree_put( avltree, 30 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );
   i_avltree_put( avltree, 17 );
   i_avltree_put( avltree, 19 );
   i_avltree_put( avltree, 21 );
   i_avltree_put( avltree, 23 );
   i_avltree_put( avltree, 25 );
   i_avltree_put( avltree, 27 );
   i_avltree_put( avltree, 29 );
   i_avltree_put( avltree, 31 );

   i_avltree_remove_value( avltree, 4 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 17 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 18 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 20 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 25 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 30 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_15a

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_15a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 8 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 9 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_15b

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_15b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 12 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_15c

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_15c( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 10 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_15d

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_15d( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 14 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_15e

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_15e( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );

   i_avltree_remove_value( avltree, 8 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 5 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 24 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 20 );
   i_avltree_put( avltree, 28 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 18 );
   i_avltree_put( avltree, 22 );
   i_avltree_put( avltree, 26 );
   i_avltree_put( avltree, 30 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 5 );
   i_avltree_put( avltree, 7 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );
   i_avltree_put( avltree, 17 );
   i_avltree_put( avltree, 19 );
   i_avltree_put( avltree, 21 );
   i_avltree_put( avltree, 23 );
   i_avltree_put( avltree, 25 );
   i_avltree_put( avltree, 27 );
   i_avltree_put( avltree, 29 );
   i_avltree_put( avltree, 31 );

   i_avltree_remove_value( avltree, 4 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 5 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 6 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 7 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 17 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 18 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 20 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 25 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 30 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16a

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16a( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 24 );
   i_avltree_put( avltree, 28 );
   i_avltree_put( avltree, 26 );
   i_avltree_put( avltree, 30 );
   i_avltree_put( avltree, 25 );
   i_avltree_put( avltree, 27 );
   i_avltree_put( avltree, 29 );
   i_avltree_put( avltree, 31 );

   i_avltree_remove_value( avltree, 24 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 24 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 25 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16b

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16b( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );

   i_avltree_remove_value( avltree, 16 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 4 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 2 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 3 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( i_avltree_count( avltree ) == 4 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16c

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16c( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 24 );
   i_avltree_put( avltree, 20 );
   i_avltree_put( avltree, 22 );
   i_avltree_put( avltree, 18 );
   i_avltree_put( avltree, 23 );
   i_avltree_put( avltree, 21 );
   i_avltree_put( avltree, 19 );
   i_avltree_put( avltree, 17 );

   i_avltree_remove_value( avltree, 20 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 20 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 18 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 17 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16d

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16d( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 24 );
   i_avltree_put( avltree, 20 );
   i_avltree_put( avltree, 18 );
   i_avltree_put( avltree, 22 );
   i_avltree_put( avltree, 23 );
   i_avltree_put( avltree, 21 );
   i_avltree_put( avltree, 19 );
   i_avltree_put( avltree, 17 );

   i_avltree_remove_value( avltree, 18 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 24 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 20 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 18 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 22 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 23 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 21 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 19 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 17 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16e

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16e( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 8 );
   i_avltree_put( avltree, 12 );
   i_avltree_put( avltree, 10 );
   i_avltree_put( avltree, 14 );
   i_avltree_put( avltree, 9 );
   i_avltree_put( avltree, 11 );
   i_avltree_put( avltree, 13 );
   i_avltree_put( avltree, 15 );

   i_avltree_remove_value( avltree, 13 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 8 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 12 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 10 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 14 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 9 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 11 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 13 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 15 );
   CU_ASSERT( result == 1 );
   
   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16f

                             16
              8                              24
      4              12              20             28
  2       6      10      14      18      22      26      30
1   3   5   7   9  11  13  15  17  19  21  23  25  27  29  31
*/

void test_remove_value_16f( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;

   avltree = i_avltree_make();

   i_avltree_put( avltree, 16 );
   i_avltree_put( avltree, 24 );
   i_avltree_put( avltree, 28 );
   
   i_avltree_put( avltree, 26 );
   i_avltree_put( avltree, 30 );
   
   i_avltree_put( avltree, 27 );
   i_avltree_put( avltree, 31 );
   i_avltree_put( avltree, 29 );
   i_avltree_put( avltree, 1 );

   i_avltree_remove_value( avltree, 24 );

   result = i_avltree_has( avltree, 16 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 24 );
   CU_ASSERT( result == 0 );

   result = i_avltree_has( avltree, 28 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 26 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 30 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 27 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 31 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 29 );
   CU_ASSERT( result == 1 );

   result = i_avltree_has( avltree, 1 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( i_avltree_count( avltree ) == 8 );

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_16g

            4
         2      6
       1   3  5   7
*/

#define MAX_COUNT 100
#define MAX_VALUE 1000

void test_remove_value_16g( void )
{
   i_avltree_t *avltree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   avltree = i_avltree_make();

   srand( 100 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         if ( i_avltree_has( avltree, n ) == 0 )
         {
            i_avltree_put( avltree, n );
            values[i] = n;
            i = i + 1;
         }
      }

      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( i_avltree_has( avltree, values[i] ) == 1 )
         {
            i_avltree_remove_value( avltree, values[i] );
        	   j = j + 1;
         }
      }

      i_avltree_wipe_out( avltree );
   }

   i_avltree_dispose( &avltree );

   return;
}

/**
   test_remove_value_17
*/

void test_remove_value_17( void )
{
   s_avltree_t *avltree = NULL;
   int32_t result = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   string_t *s4 = string_make_from_cstring( "4" );
   
   avltree = s_avltree_make();

   s_avltree_put( avltree, s4 );
   s_avltree_put( avltree, s1 );
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s3 );

   s_avltree_finish( avltree );
   s_avltree_remove_value( avltree, s1 );

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
add_test_remove_value( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_value", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_value_1
   add_test_to_suite( p_suite, test_remove_value_1, "test_remove_value_1" );

   // test_remove_value_2
   add_test_to_suite( p_suite, test_remove_value_2, "test_remove_value_2" );
   add_test_to_suite( p_suite, test_remove_value_2a, "test_remove_value_2a" );
   add_test_to_suite( p_suite, test_remove_value_2b, "test_remove_value_2b" );

   // test_remove_value_3
   add_test_to_suite( p_suite, test_remove_value_3, "test_remove_value_3" );
   add_test_to_suite( p_suite, test_remove_value_3a, "test_remove_value_3a" );
   add_test_to_suite( p_suite, test_remove_value_3b, "test_remove_value_3b" );

   // test_remove_value_4
   add_test_to_suite( p_suite, test_remove_value_4, "test_remove_value_4" );
   add_test_to_suite( p_suite, test_remove_value_4a, "test_remove_value_4a" );
   add_test_to_suite( p_suite, test_remove_value_4b, "test_remove_value_4b" );

   // test_remove_value_5
   add_test_to_suite( p_suite, test_remove_value_5, "test_remove_value_5" );
   add_test_to_suite( p_suite, test_remove_value_5a, "test_remove_value_5a" );
   add_test_to_suite( p_suite, test_remove_value_5b, "test_remove_value_5b" );
   add_test_to_suite( p_suite, test_remove_value_5c, "test_remove_value_5c" );
   add_test_to_suite( p_suite, test_remove_value_5d, "test_remove_value_5d" );
   add_test_to_suite( p_suite, test_remove_value_5e, "test_remove_value_5e" );
   add_test_to_suite( p_suite, test_remove_value_5f, "test_remove_value_5f" );

   // test_remove_value_6
   add_test_to_suite( p_suite, test_remove_value_6, "test_remove_value_6" );
   add_test_to_suite( p_suite, test_remove_value_6a, "test_remove_value_6a" );

   // test_remove_value_7
   add_test_to_suite( p_suite, test_remove_value_7, "test_remove_value_7" );

   // test_remove_value_8
   add_test_to_suite( p_suite, test_remove_value_8, "test_remove_value_8" );

   // test_remove_value_9
   add_test_to_suite( p_suite, test_remove_value_9, "test_remove_value_9" );

   // test_remove_value_10
   add_test_to_suite( p_suite, test_remove_value_10, "test_remove_value_10" );

   // test_remove_value_11
   add_test_to_suite( p_suite, test_remove_value_11, "test_remove_value_11" );

   // test_remove_value_12
   add_test_to_suite( p_suite, test_remove_value_12, "test_remove_value_12" );

   // test_remove_value_13
   add_test_to_suite( p_suite, test_remove_value_13, "test_remove_value_13" );

   // test_remove_value_14
   add_test_to_suite( p_suite, test_remove_value_14, "test_remove_value_14" );
   add_test_to_suite( p_suite, test_remove_value_14a, "test_remove_value_14a" );

   // test_remove_value_15
   add_test_to_suite( p_suite, test_remove_value_15, "test_remove_value_15" );
   add_test_to_suite( p_suite, test_remove_value_15a, "test_remove_value_15a" );
   add_test_to_suite( p_suite, test_remove_value_15b, "test_remove_value_15b" );
   add_test_to_suite( p_suite, test_remove_value_15c, "test_remove_value_15c" );
   add_test_to_suite( p_suite, test_remove_value_15d, "test_remove_value_15d" );
   add_test_to_suite( p_suite, test_remove_value_15e, "test_remove_value_15e" );

   // test_remove_value_16
   add_test_to_suite( p_suite, test_remove_value_16, "test_remove_value_16" );
   add_test_to_suite( p_suite, test_remove_value_16a, "test_remove_value_16a" );
   add_test_to_suite( p_suite, test_remove_value_16b, "test_remove_value_16b" );
   add_test_to_suite( p_suite, test_remove_value_16c, "test_remove_value_16c" );
   add_test_to_suite( p_suite, test_remove_value_16d, "test_remove_value_16d" );
   add_test_to_suite( p_suite, test_remove_value_16e, "test_remove_value_16e" );
   add_test_to_suite( p_suite, test_remove_value_16f, "test_remove_value_16f" );
   add_test_to_suite( p_suite, test_remove_value_16g, "test_remove_value_16g" );

   // test_remove_value_17
   add_test_to_suite( p_suite, test_remove_value_17, "test_remove_value_17" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


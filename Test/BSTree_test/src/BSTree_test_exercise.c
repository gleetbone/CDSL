/**
 @file BSTree_test_exercise.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_forth"
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

extern int32_t print_flag;

#define MAX_COUNT 100
#define MAX_VALUE 1000

/**
   test_exercise_1
*/

void test_exercise_1( void )
{
   i_bstree_t *bstree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   bstree = i_bstree_make();

   srand( 101 );

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
         if ( i_bstree_has( bstree, n ) == 0 )
         {
            i_bstree_put( bstree, n );
            values[i] = n;
            i = i + 1;
         }
      }

      i_bstree_balance( bstree );
      
      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( i_bstree_has( bstree, values[i] ) == 1 )
         {
            i_bstree_remove_value( bstree, values[i] );
            j = j + 1;
         }
      }

      i_bstree_balance( bstree );
      
      i_bstree_wipe_out( bstree );
   }

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_exercise_2
*/

void test_exercise_2( void )
{
   s_bstree_t *bstree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   string_t *value = NULL;
   string_t * values[MAX_COUNT] = {NULL};
   char str[8] = {0};

   bstree = s_bstree_make();

   srand( 101 );

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
         str[0] = 0;
         sprintf( str, "%03d", n );
         
         value = string_make_from_cstring( str );
         
         if ( s_bstree_has( bstree, value ) == 0 )
         {
            s_bstree_put( bstree, value );
            values[i] = value;
            i = i + 1;
         }
         else
         {
            string_deep_dispose( &value );
         }
      }

      s_bstree_balance( bstree );
      
      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( values[i] != NULL )
         {
            if ( s_bstree_has( bstree, values[i] ) == 1 )
            {
               s_bstree_remove_value( bstree, values[i] );
               string_dispose( &values[i] );
               values[i] = NULL;
               j = j + 1;
            }
         }
      }

      s_bstree_balance( bstree );
      
      s_bstree_wipe_out( bstree );
      
      j = 0;
      while ( j < count )
      {
         if ( values[j] != NULL )
         {
            string_dispose( &values[j] );
            values[j] = NULL;
         }
         j = j + 1;
      }
      
   }

   s_bstree_dispose( &bstree );

   return;
}

/**
   test_exercise_3
*/

void test_exercise_3( void )
{
   s_bstree_t *bstree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   string_t *value = NULL;
   string_t * values[MAX_COUNT] = {NULL};
   char str[8] = {0};

   bstree = s_bstree_make();

   srand( 101 );

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
         str[0] = 0;
         sprintf( str, "%03d", n );
         
         value = string_make_from_cstring( str );
         
         if ( s_bstree_has( bstree, value ) == 0 )
         {
            s_bstree_put( bstree, value );
            values[i] = value;
            i = i + 1;
         }
         else
         {
            string_deep_dispose( &value );
         }
      }

      s_bstree_balance( bstree );
      
      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( values[i] != NULL )
         {
            if ( s_bstree_has( bstree, values[i] ) == 1 )
            {
               s_bstree_remove_value_and_dispose( bstree, values[i] );
               values[i] = NULL;
               j = j + 1;
            }
         }
      }

      s_bstree_balance( bstree );
      
      s_bstree_wipe_out_and_dispose( bstree );
            
   }

   s_bstree_dispose( &bstree );

   return;
}


int
add_test_exercise( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_exercise", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_exercise_1
   add_test_to_suite( p_suite, test_exercise_1, "test_exercise_1" );

   // test_exercise_2
   add_test_to_suite( p_suite, test_exercise_2, "test_exercise_2" );

   // test_exercise_3
   add_test_to_suite( p_suite, test_exercise_3, "test_exercise_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


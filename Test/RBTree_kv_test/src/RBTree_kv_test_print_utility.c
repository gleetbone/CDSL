/**
 @file RBTree_test_print_utility.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
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

#include "base.h"
#include "RBTree_kv_test_print_utility.h"

/**
   test_print_utility_make_array
*/

char_t ** test_print_utility_make_array( int32_t height, int32_t width )
{
   char_t **result = NULL;
   int32_t size = 0;
   int32_t i = 0;
   int32_t j = 0;

   size = width*floor( pow( 2.0, height ) );

   result = ( char_t ** ) calloc( height + 1, sizeof( char_t * ) );

   for( i = 0; i < height; i++ )
   {
      result[i] = ( char_t * ) calloc( size + 1, sizeof( char_t ) );

	   for( j=0; j<size; j++ )
      {
         result[i][j] = ' ';
      }
   }

   return result;
}

/**
   test_print_utility_dispose_array
*/

void test_print_utility_dispose_array( char_t **array )
{
   int32_t i = 0;

   for( i=0; array[i] != NULL; i++ )
   {
      free( array[i] );
   }

   free( array );

   return;
}

/**
   test_print_utility_clear_array
*/

void test_print_utility_clear_array( char_t **array, int32_t height, int32_t width )
{
   int32_t size = 0;
   int32_t i = 0;
   int32_t j = 0;

   size = width*floor( pow( 2.0, height ) );

   for( i = 0; i < height; i++ )
   {
	   for( j=0; j<size; j++ )
       {
          array[i][j] = ' ';
       }
   }

   return;
}

/**
   test_print_utility_print_array
*/

void test_print_utility_print_array( char_t **array )
{
   int32_t i = 0;

   printf( "\n" );
   for( i = 0; array[i] != NULL; i++ )
   {
      printf( "%s\n", array[i] );
   }

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


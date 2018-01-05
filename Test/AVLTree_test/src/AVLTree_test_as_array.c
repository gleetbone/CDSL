/**
 @file AVLTree_	.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_as_array_1
*/

void test_as_array_1( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 1 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_2
*/

void test_as_array_2( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 3 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_3
*/

void test_as_array_3( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_4
*/

void test_as_array_4( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_5
   
            4
         2      6
       1  
*/

void test_as_array_5( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 1 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 4 );
   CU_ASSERT( array[3] == 6 );
  
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_6
   
            4
         2      6
            3       
*/

void test_as_array_6( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 3 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 3 );
   CU_ASSERT( array[2] == 4 );
   CU_ASSERT( array[3] == 6 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_7
   
            4
         2      6
              5 
*/

void test_as_array_7( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 5 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 5 );
   CU_ASSERT( array[3] == 6 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

/**
   test_as_array_8
   
            4
         2      6
                  7   
*/

void test_as_array_8( void )
{
   i_avltree_t *avltree = NULL;
   int32_t *array = NULL;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 4 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 6 );
   i_avltree_put( avltree, 7 );
   
   array = i_avltree_as_array( avltree );
   
   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 7 );
 
   free( array );
   i_avltree_dispose( avltree );

   return;
}

int
add_test_as_array( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_array", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_array_1
   add_test_to_suite( p_suite, test_as_array_1, "test_as_array_1" );

   // test_as_array_2
   add_test_to_suite( p_suite, test_as_array_2, "test_as_array_2" );

   // test_as_array_3
   add_test_to_suite( p_suite, test_as_array_3, "test_as_array_3" );

   // test_as_array_4
   add_test_to_suite( p_suite, test_as_array_4, "test_as_array_4" );

   // test_as_array_5
   add_test_to_suite( p_suite, test_as_array_5, "test_as_array_5" );

   // test_as_array_6
   add_test_to_suite( p_suite, test_as_array_6, "test_as_array_6" );

   // test_as_array_7
   add_test_to_suite( p_suite, test_as_array_7, "test_as_array_7" );

   // test_as_array_8
   add_test_to_suite( p_suite, test_as_array_8, "test_as_array_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


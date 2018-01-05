/**
 @file BSTree_test_has.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_has_1
*/

void test_has_1( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 3 );
   
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

   return;
}

/**
   test_has_3
*/

void test_has_3( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 3 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 1 );
   
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

   return;
}

/**
   test_has_4
*/

void test_has_4( void )
{
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 1 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 3 );
   
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
  
   i_bstree_dispose( bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 1 );
   
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 3 );
   
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 3 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 5 );
   
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 5 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

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
   i_bstree_t *bstree = NULL;
   int32_t result = 0;
   
   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 4 );
   i_bstree_put( bstree, 2 );
   i_bstree_put( bstree, 6 );
   i_bstree_put( bstree, 7 );
   
   result = i_bstree_has( bstree, 4 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 2 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 6 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 7 );
   CU_ASSERT( result == 1 );
 
   result = i_bstree_has( bstree, 0 );
   CU_ASSERT( result == 0 );
 
   i_bstree_dispose( bstree );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


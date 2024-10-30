/**
 @file HSet_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet_clone"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"
#include "s_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   i_hset_t *hset = NULL;
   
   hset = i_hset_make();
   
   i_hset_t *hset1 = NULL;
   
   hset1 = i_hset_clone( hset );
   
   CU_ASSERT( hset1 != NULL );
   CU_ASSERT( i_hset_count( hset1 ) == 0 );
   CU_ASSERT( i_hset_is_empty( hset1 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &hset1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   s_hset_t *hset = NULL;
   
   hset = s_hset_make();
   
   string_t  *s1 = string_make_from_cstring( "a" );
   string_t  *s2 = string_make_from_cstring( "b" );

   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );
   
   s_hset_t *hset1 = NULL;
   
   hset1 = s_hset_clone( hset );
   
   CU_ASSERT( hset1 != NULL );
   
   CU_ASSERT( s_hset_count( hset1 ) == 2 );
   CU_ASSERT( s_hset_is_empty( hset1 ) == 0 );
   
   CU_ASSERT( s_hset_has( hset1, s1 ) == 1 );
   CU_ASSERT( s_hset_has( hset1, s2 ) == 1 );
 
   s_hset_dispose( &hset1 );
   s_hset_deep_dispose( &hset );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


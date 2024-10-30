/**
 @file HSet_test_make_n.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet_make_n"
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
   test_make_n_1
*/

void test_make_n_1( void )
{
   i_hset_t *hset = NULL;
   
   hset = i_hset_make_n( 23 );
   
   CU_ASSERT( hset != NULL );
   CU_ASSERT( i_hset_count( hset ) == 0 );
   CU_ASSERT( i_hset_is_empty( hset ) == 1 );
 
   i_hset_dispose( &hset );

   return;
}

/**
   test_make_n_2
*/

void test_make_n_2( void )
{
   s_hset_t *hset = NULL;
   
   hset = s_hset_make_n( 23 );
   
   CU_ASSERT( hset != NULL );
   CU_ASSERT( s_hset_count( hset ) == 0 );
   CU_ASSERT( s_hset_is_empty( hset ) == 1 );
 
   s_hset_dispose( &hset );

   return;
}

int
add_test_make_n( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_n", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_n_1
   add_test_to_suite( p_suite, test_make_n_1, "test_make_n_1" );

   // test_make_n_2
   add_test_to_suite( p_suite, test_make_n_2, "test_make_n_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file HSet_test_make_from.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HSet_make_from"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_make_from.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_1
*/

void test_make_from_1( void )
{
   i_hset_t *hset = NULL;
   
   hset = i_hset_make();
   
   i_hset_t *hset1 = NULL;
   
   hset1 = i_hset_make_from( hset );
   
   CU_ASSERT( hset1 != NULL );
   CU_ASSERT( i_hset_count( hset1 ) == 0 );
   CU_ASSERT( i_hset_is_empty( hset1 ) == 1 );
 
   i_hset_dispose( hset );
   i_hset_dispose( hset1 );

   return;
}

int
add_test_make_from( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_1
   add_test_to_suite( p_suite, test_make_from_1, "test_make_from_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


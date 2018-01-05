/**
 @file HTable_test_make_n.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HTable_make_n"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HTable_make_n.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_HTable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_n_1
*/

void test_make_n_1( void )
{
   ii_htable_t *htable = NULL;
   
   htable = ii_htable_make_n( 23 );
   
   CU_ASSERT( htable != NULL );
   CU_ASSERT( ii_htable_count( htable ) == 0 );
   CU_ASSERT( ii_htable_is_empty( htable ) == 1 );
 
   ii_htable_dispose( htable );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


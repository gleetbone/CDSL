/**
 @file HTable_test_make_duplicate_from.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HTable_make_from"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HTable_make_from.

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
   test_make_duplicate_from_1
*/

void test_make_duplicate_from_1( void )
{
   ii_htable_t *htable = NULL;
   
   htable = ii_htable_make();
   
   ii_htable_put( htable, 10, 100 );

   ii_htable_t *htable1 = NULL;
   
   htable1 = ii_htable_make_duplicate_from( htable );
   
   CU_ASSERT( htable1 != NULL );
   CU_ASSERT( ii_htable_count( htable1 ) == 1 );
   CU_ASSERT( ii_htable_is_empty( htable1 ) == 0 );
 
   ii_htable_dispose( htable );
   ii_htable_dispose( htable1 );

   return;
}

int
add_test_make_duplicate_from( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_duplicate_from", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_duplicate_from_1
   add_test_to_suite( p_suite, test_make_duplicate_from_1, "test_make_duplicate_from_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


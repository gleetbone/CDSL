/**
 @file HTable_test_keys_as_array.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HTable_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HTable_put.

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
   test_keys_as_array_1
*/

void test_keys_as_array_1( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 10000 );
   ii_htable_put( htable, 25, 20000 );
   ii_htable_put( htable, 26, 30000 );
   ii_htable_put( htable, 27, 40000 );
   ii_htable_put( htable, 28, 50000 );
   ii_htable_put( htable, 29, 60000 );
   ii_htable_put( htable, 30, 70000 );
   ii_htable_put( htable, 31, 80000 );
   ii_htable_put( htable, 32, 90000 );
   ii_htable_put( htable, 33, 11000 );
   ii_htable_put( htable, 34, 12000 );
   ii_htable_put( htable, 35, 13000 );
   ii_htable_put( htable, 36, 14000 );
   ii_htable_put( htable, 37, 15000 );
   ii_htable_put( htable, 38, 16000 );
   ii_htable_put( htable, 39, 17000 );
   ii_htable_put( htable, 40, 18000 );
   ii_htable_put( htable, 41, 19000 );

   CU_ASSERT( ii_htable_count( htable ) == 18 );
  
   int *keys = ii_htable_keys_as_array( htable );
   int *items = ii_htable_values_as_array( htable );
     
   CU_ASSERT( keys[0]  == 10000 );
   CU_ASSERT( items[0] == 24 );

   CU_ASSERT( keys[1]  == 20000 );
   CU_ASSERT( items[1] == 25 );

   CU_ASSERT( keys[2]  == 30000 );
   CU_ASSERT( items[2] == 26 );

   CU_ASSERT( keys[3]  == 40000 );
   CU_ASSERT( items[3] == 27 );

   CU_ASSERT( keys[4]  == 50000 );
   CU_ASSERT( items[4] == 28 );

   CU_ASSERT( keys[5]  == 60000 );
   CU_ASSERT( items[5] == 29 );

   CU_ASSERT( keys[6]  == 70000 );
   CU_ASSERT( items[6] == 30 );

   CU_ASSERT( keys[7]  == 80000 );
   CU_ASSERT( items[7] == 31 );

   CU_ASSERT( keys[8]  == 90000 );
   CU_ASSERT( items[8] == 32 );

   CU_ASSERT( keys[9]  == 11000 );
   CU_ASSERT( items[9] == 33 );

   CU_ASSERT( keys[10]  == 12000 );
   CU_ASSERT( items[10] == 34 );

   CU_ASSERT( keys[11]  == 13000 );
   CU_ASSERT( items[11] == 35 );

   CU_ASSERT( keys[12]  == 14000 );
   CU_ASSERT( items[12] == 36 );

   CU_ASSERT( keys[13]  == 15000 );
   CU_ASSERT( items[13] == 37 );

   CU_ASSERT( keys[14]  == 16000 );
   CU_ASSERT( items[14] == 38 );

   CU_ASSERT( keys[15]  == 17000 );
   CU_ASSERT( items[15] == 39 );

   CU_ASSERT( keys[16]  == 18000 );
   CU_ASSERT( items[16] == 40 );

   CU_ASSERT( keys[17]  == 19000 );
   CU_ASSERT( items[17] == 41 );

   free( keys );
   free( items );
   ii_htable_dispose( htable );

   return;
}

int
add_test_keys_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_keys_as_array_1, "test_keys_as_array_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


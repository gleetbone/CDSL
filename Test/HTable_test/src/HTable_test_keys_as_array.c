/**
 @file HTable_test_keys_as_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HTable_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HTable_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_HTable.h"
#include "ss_HTable.h"

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
   ii_htable_dispose( &htable );

   return;
}

/**
   test_keys_as_array_2
*/

void test_keys_as_array_2( void )
{
   ss_htable_t *htable = NULL;

   htable = ss_htable_make();

   string_t *k1 = string_make_from_cstring( "k1" );
   string_t *v1 = string_make_from_cstring( "v1" );
   
   string_t *k2 = string_make_from_cstring( "k2" );
   string_t *v2 = string_make_from_cstring( "v2" );
   
   string_t *k3 = string_make_from_cstring( "k3" );
   string_t *v3 = string_make_from_cstring( "v3" );
   
   string_t *k4 = string_make_from_cstring( "k4" );
   string_t *v4 = string_make_from_cstring( "v4" );
   
   string_t *k5 = string_make_from_cstring( "k5" );
   string_t *v5 = string_make_from_cstring( "v5" );
   
   string_t *k6 = string_make_from_cstring( "k6" );
   string_t *v6 = string_make_from_cstring( "v6" );
   
   string_t *k7 = string_make_from_cstring( "k7" );
   string_t *v7 = string_make_from_cstring( "v7" );
   
   string_t *k8 = string_make_from_cstring( "k8" );
   string_t *v8 = string_make_from_cstring( "v8" );
   
   string_t *k9 = string_make_from_cstring( "k9" );
   string_t *v9 = string_make_from_cstring( "v9" );
   
   string_t *k10 = string_make_from_cstring( "k10" );
   string_t *v10 = string_make_from_cstring( "v10" );
   
   string_t *k11 = string_make_from_cstring( "k11" );
   string_t *v11 = string_make_from_cstring( "v11" );
   
   string_t *k12 = string_make_from_cstring( "k12" );
   string_t *v12 = string_make_from_cstring( "v12" );
   
   string_t *k13 = string_make_from_cstring( "k13" );
   string_t *v13 = string_make_from_cstring( "v13" );
   
   string_t *k14 = string_make_from_cstring( "k14" );
   string_t *v14 = string_make_from_cstring( "v14" );
   
   string_t *k15 = string_make_from_cstring( "k15" );
   string_t *v15 = string_make_from_cstring( "v15" );
   
   string_t *k16 = string_make_from_cstring( "k16" );
   string_t *v16 = string_make_from_cstring( "v16" );
   
   string_t *k17 = string_make_from_cstring( "k17" );
   string_t *v17 = string_make_from_cstring( "v17" );
   
   string_t *k18 = string_make_from_cstring( "k18" );
   string_t *v18 = string_make_from_cstring( "v18" );
   
   string_t *k19 = string_make_from_cstring( "k19" );
   string_t *v19 = string_make_from_cstring( "v19" );
   
   ss_htable_put( htable, v1, k1 );
   ss_htable_put( htable, v2, k2 );
   ss_htable_put( htable, v3, k3 );
   ss_htable_put( htable, v4, k4 );
   ss_htable_put( htable, v5, k5 );
   ss_htable_put( htable, v6, k6 );
   ss_htable_put( htable, v7, k7 );
   ss_htable_put( htable, v8, k8 );
   ss_htable_put( htable, v9, k9 );
   ss_htable_put( htable, v10, k10 );
   ss_htable_put( htable, v11, k11 );
   ss_htable_put( htable, v12, k12 );
   ss_htable_put( htable, v13, k13 );
   ss_htable_put( htable, v14, k14 );
   ss_htable_put( htable, v15, k15 );
   ss_htable_put( htable, v16, k16 );
   ss_htable_put( htable, v17, k17 );
   ss_htable_put( htable, v18, k18 );
   ss_htable_put( htable, v19, k19 );

   CU_ASSERT( ss_htable_count( htable ) == 19 );
  
   string_t **keys = ss_htable_keys_as_array( htable );
   string_t **items = ss_htable_values_as_array( htable );
     
   CU_ASSERT( keys[0]  == k1 );
   CU_ASSERT( items[0] == v1 );

   CU_ASSERT( keys[1]  == k2 );
   CU_ASSERT( items[1] == v2 );

   CU_ASSERT( keys[2]  == k3 );
   CU_ASSERT( items[2] == v3 );

   CU_ASSERT( keys[3]  == k4 );
   CU_ASSERT( items[3] == v4 );

   CU_ASSERT( keys[4]  == k5 );
   CU_ASSERT( items[4] == v5 );

   CU_ASSERT( keys[5]  == k6 );
   CU_ASSERT( items[5] == v6 );

   CU_ASSERT( keys[6]  == k7 );
   CU_ASSERT( items[6] == v7 );

   CU_ASSERT( keys[7]  == k8 );
   CU_ASSERT( items[7] == v8 );

   CU_ASSERT( keys[8]  == k9 );
   CU_ASSERT( items[8] == v9 );

   CU_ASSERT( keys[9]  == k10 );
   CU_ASSERT( items[9] == v10 );

   CU_ASSERT( keys[10]  == k11 );
   CU_ASSERT( items[10] == v11 );

   CU_ASSERT( keys[11]  == k12 );
   CU_ASSERT( items[11] == v12 );

   CU_ASSERT( keys[12]  == k13 );
   CU_ASSERT( items[12] == v13 );

   CU_ASSERT( keys[13]  == k14 );
   CU_ASSERT( items[13] == v14 );

   CU_ASSERT( keys[14]  == k15 );
   CU_ASSERT( items[14] == v15 );

   CU_ASSERT( keys[15]  == k16 );
   CU_ASSERT( items[15] == v16 );

   CU_ASSERT( keys[16]  == k17 );
   CU_ASSERT( items[16] == v17 );

   CU_ASSERT( keys[17]  == k18 );
   CU_ASSERT( items[17] == v18 );

   CU_ASSERT( keys[18]  == k19 );
   CU_ASSERT( items[18] == v19 );

   CU_ASSERT( keys[19]  == NULL );
   CU_ASSERT( items[19] == NULL );

   free( keys );
   free( items );
   ss_htable_deep_dispose( &htable );

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

   // test_keys_as_array_1
   add_test_to_suite( p_suite, test_keys_as_array_1, "test_keys_as_array_1" );

   // test_keys_as_array_2
   add_test_to_suite( p_suite, test_keys_as_array_2, "test_keys_as_array_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file SelSorter_test_make.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SelSorter_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SelSorter_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_SelSorter.h"
#include "i_Sorter.h"
#include "p_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   i_selsorter_t *sorter = NULL;

   sorter = i_selsorter_make();
   CU_ASSERT( sorter != NULL );
   
   i_selsorter_dispose( &sorter );
   CU_ASSERT( sorter == NULL );
   
   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   i_selsorter_t *sorter = NULL;
   protocol_base_t *pb_sorter = ( protocol_base_t * ) sorter;

   sorter = i_selsorter_make();
   pb_sorter = ( protocol_base_t * ) sorter;
   
   CU_ASSERT( sorter != NULL );
   
   p_basic_deep_dispose( &pb_sorter );
   CU_ASSERT( pb_sorter == NULL );
   
   return;
}

int
add_test_make( void )
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
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


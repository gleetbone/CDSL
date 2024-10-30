/**
 @file BSorter_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSorter_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSorter_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSorter.h"
#include "i_Sorter.h"
#include "i_Sorter.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_clone_1
*/

void test_clone_1( void )
{
   i_bsorter_t *sorter = NULL;
   i_bsorter_t *sorter1 = NULL;

   sorter = i_bsorter_make();
   CU_ASSERT( sorter != NULL );
   
   sorter1 = i_bsorter_clone( sorter );
   CU_ASSERT( sorter1 != NULL );
   
   i_bsorter_dispose( &sorter );
   i_bsorter_dispose( &sorter1 );
   CU_ASSERT( sorter == NULL );
   CU_ASSERT( sorter1 == NULL );
   
   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   i_bsorter_t *sorter = NULL;
   i_bsorter_t *sorter1 = NULL;

   sorter = i_bsorter_make();
   CU_ASSERT( sorter != NULL );
   
   sorter1 = i_bsorter_deep_clone( sorter );
   CU_ASSERT( sorter1 != NULL );
   
   i_bsorter_deep_dispose( &sorter );
   i_bsorter_deep_dispose( &sorter1 );
   CU_ASSERT( sorter == NULL );
   CU_ASSERT( sorter1 == NULL );
   
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


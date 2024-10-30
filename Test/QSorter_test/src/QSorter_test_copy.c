/**
 @file QSorter_test_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for QSorter_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for QSorter_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_QSorter.h"
#include "i_Sorter.h"
#include "i_Sorter.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_copy_1
*/

void test_copy_1( void )
{
   i_qsorter_t *sorter = NULL;
   i_qsorter_t *sorter1 = NULL;

   sorter = i_qsorter_make();
   CU_ASSERT( sorter != NULL );
   
   sorter1 = i_qsorter_make();
   CU_ASSERT( sorter1 != NULL );
   
   i_qsorter_copy( sorter, sorter1 );
   
   i_qsorter_dispose( &sorter );
   i_qsorter_dispose( &sorter1 );
   CU_ASSERT( sorter == NULL );
   CU_ASSERT( sorter1 == NULL );
   
   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   i_qsorter_t *sorter = NULL;
   i_qsorter_t *sorter1 = NULL;

   sorter = i_qsorter_make();
   CU_ASSERT( sorter != NULL );
   
   sorter1 = i_qsorter_make();
   CU_ASSERT( sorter != NULL );
   
   i_qsorter_deep_copy( sorter, sorter1 );
   
   i_qsorter_deep_dispose( &sorter );
   i_qsorter_deep_dispose( &sorter1 );
   CU_ASSERT( sorter == NULL );
   CU_ASSERT( sorter1 == NULL );
   
   return;
}

int
add_test_copy( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_1
   add_test_to_suite( p_suite, test_copy_1, "test_copy_1" );

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


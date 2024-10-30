/**
 @file configuration_test_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for configuration_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for configuration_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Configuration.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_copy_1
*/

void test_copy_1( void )
{
   configuration_t *configuration = NULL;
   configuration_t *configuration1 = NULL;
   
   configuration = configuration_make();
   configuration1 = configuration_make();
   configuration_copy( configuration1, configuration );

   CU_ASSERT( configuration != NULL );
   CU_ASSERT( configuration1 != NULL );
 
   configuration_dispose( &configuration1 );
   configuration_deep_dispose( &configuration );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


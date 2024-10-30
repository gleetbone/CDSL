/**
 @file configuration_test_is_deep_equal.c
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
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   configuration_t *configuration = NULL;
   configuration_t *configuration1 = NULL;
   
   configuration = configuration_make();
   configuration1 = configuration_deep_clone( configuration );

   CU_ASSERT( configuration != NULL );
   CU_ASSERT( configuration1 != NULL );
   
   CU_ASSERT( configuration_is_deep_equal( configuration, configuration ) == 1 );
   CU_ASSERT( configuration_is_deep_equal( configuration, configuration1 ) == 1 );
 
   configuration_deep_dispose( &configuration1 );
   configuration_deep_dispose( &configuration );

   return;
}

int
add_test_is_deep_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_deep_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_deep_equal_1
   add_test_to_suite( p_suite, test_is_deep_equal_1, "test_is_deep_equal_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


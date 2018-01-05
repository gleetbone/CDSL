/**
 @file configuration_test_has.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for messaging_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for soa_node_make_dict.

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
   test_has_1
*/

void test_has_1( void )
{
   soa_configuration_t *configuration = soa_configuration_make();

   string_t *key = string_make_from_cstring( "fruit" );
   string_t *value = string_make_from_cstring( "apple" );

   soa_configuration_put( configuration, key, value );

   string_t *key1 = string_make_from_cstring( "meat" );
   string_t *value1 = string_make_from_cstring( "fish" );

   soa_configuration_put( configuration, key1, value1 );

   int32_t flag = soa_configuration_has( configuration, key );

   CU_ASSERT( flag == 1 );

   flag = soa_configuration_has( configuration, key1 );

   CU_ASSERT( flag == 1 );

   string_t *key2 = string_make_from_cstring( "bread" );

   flag = soa_configuration_has( configuration, key2 );

   CU_ASSERT( flag == 0 );

   string_dispose_with_contents( key2 );

   soa_configuration_dispose( configuration );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   soa_configuration_t *configuration = soa_configuration_make();

   soa_configuration_put_cstring( configuration, "fruit", "apple" );
   soa_configuration_put_cstring( configuration, "meat", "fish" );

   int32_t flag = soa_configuration_has_cstring( configuration, "fruit" );

   CU_ASSERT( flag == 1 );

   flag = soa_configuration_has_cstring( configuration, "meat" );

   CU_ASSERT( flag == 1 );

   flag = soa_configuration_has_cstring( configuration, "bread" );

   CU_ASSERT( flag == 0 );

   soa_configuration_dispose( configuration );

   return;
}

int
add_test_has( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_1
   add_test_to_suite( p_suite, test_has_1, "test_has_1" );

   // test_has_2
   add_test_to_suite( p_suite, test_has_2, "test_has_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


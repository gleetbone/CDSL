/**
 @file soa_configuration_test_set_from_file.c
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
   test_set_from_file_1
*/

void test_set_from_file_1( void )
{
   soa_configuration_t *configuration = soa_configuration_make();
   
   string_t *filename = string_make_from_cstring( "src/config.txt" );
   soa_configuration_set_from_file( configuration, filename );

   string_t *key = string_make_from_cstring( "fruit" );
   string_t *key1 = string_make_from_cstring( "meat" );
   string_t *key2 = string_make_from_cstring( "bread" );
   string_t *s = NULL;

   int32_t flag = soa_configuration_has( configuration, key );
   CU_ASSERT( flag == 1 );

   s = soa_configuration_item( configuration, key );
   CU_ASSERT( string_is_equal_cstring( s, "apple" ) );

   flag = soa_configuration_has( configuration, key1 );
   CU_ASSERT( flag == 1 );

   s = soa_configuration_item( configuration, key1 );
   CU_ASSERT( string_is_equal_cstring( s, "fish" ) );

   flag = soa_configuration_has( configuration, key2 );
   CU_ASSERT( flag == 0 );

   s = soa_configuration_item( configuration, key2 );
   CU_ASSERT( s == NULL );

   string_dispose_with_contents( filename );
   string_dispose_with_contents( key );
   string_dispose_with_contents( key1 );
   string_dispose_with_contents( key2 );

   soa_configuration_dispose( configuration );

   return;
}

/**
   test_set_from_file_2
*/

void test_set_from_file_2( void )
{
   soa_configuration_t *configuration = soa_configuration_make();
   
   soa_configuration_set_from_file_cstring( configuration, "src/config.txt" );

   int32_t flag = soa_configuration_has_cstring( configuration, "fruit" );
   CU_ASSERT( flag == 1 );

   string_t *s = soa_configuration_item_cstring( configuration, "fruit" );
   CU_ASSERT( string_is_equal_cstring( s, "apple" ) );

   flag = soa_configuration_has_cstring( configuration, "meat" );
   CU_ASSERT( flag == 1 );

   s = soa_configuration_item_cstring( configuration, "meat" );
   CU_ASSERT( string_is_equal_cstring( s, "fish" ) );

   flag = soa_configuration_has_cstring( configuration, "bread" );
   CU_ASSERT( flag == 0 );

   s = soa_configuration_item_cstring( configuration, "bread" );
   CU_ASSERT( s == NULL );

   soa_configuration_dispose( configuration );

   return;
}

int
add_test_set_from_file( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_set_from_file", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_set_from_file_1
   add_test_to_suite( p_suite, test_set_from_file_1, "test_set_from_file_1" );

   // test_set_from_file_2
   add_test_to_suite( p_suite, test_set_from_file_2, "test_set_from_file_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


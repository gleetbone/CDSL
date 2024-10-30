/**
 @file configuration_test_superkey_item.c
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
   test_superkey_item_1
*/

void test_superkey_item_1( void )
{
   configuration_t *configuration = configuration_make();
   
   string_t *key = string_make_from_cstring( "food:fruit" );
   string_t *value = string_make_from_cstring( "apple" );

   configuration_put( configuration, key, value );

   string_t *key1 = string_make_from_cstring( "fruit" );
   string_t *value1 = string_make_from_cstring( "apple" );

   configuration_put( configuration, key1, value1 );

   string_t *key2 = string_make_from_cstring( "meat" );
   string_t *value2 = string_make_from_cstring( "fish" );

   configuration_put( configuration, key2, value2 );

   string_t *s = string_make_from_cstring( "food" );
   string_t *k = string_make_from_cstring( "fruit" );
   string_t *k1 = string_make_from_cstring( "meat" );

   string_t *r = configuration_superkey_item( configuration, s, k );

   CU_ASSERT( string_is_equal_cstring( r, "apple" ) );

   r = configuration_superkey_item( configuration, s, k1 );

   CU_ASSERT( string_is_equal_cstring( r, "fish" ) );

   string_deep_dispose( &s );
   string_deep_dispose( &k );
   string_deep_dispose( &k1 );

   configuration_deep_dispose( &configuration );

   return;
}

/**
   test_superkey_item_2
*/

void test_superkey_item_2( void )
{
   configuration_t *configuration = configuration_make();

   configuration_put_cstring( configuration, "food:fruit", "apple" );
   configuration_put_cstring( configuration, "fruit", "apple" );
   configuration_put_cstring( configuration, "meat", "fish" );

   string_t *r = configuration_superkey_item_cstring( configuration, "food", "fruit" );

   CU_ASSERT( string_is_equal_cstring( r, "apple" ) );

   r = configuration_superkey_item_cstring( configuration, "food", "meat" );

   CU_ASSERT( string_is_equal_cstring( r, "fish" ) );

   configuration_deep_dispose( &configuration );

   return;
}

int
add_test_superkey_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_superkey_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_superkey_item_1
   add_test_to_suite( p_suite, test_superkey_item_1, "test_superkey_item_1" );

   // test_superkey_item_2
   add_test_to_suite( p_suite, test_superkey_item_2, "test_superkey_item_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


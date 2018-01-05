/**
 @file soa_configuration_test_superkey_list_items.c
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
   test_superkey_list_items_1
*/

void test_superkey_list_items_1( void )
{
   soa_configuration_t *configuration = soa_configuration_make();
   string_t *key = string_make_from_cstring( "food:fruit_1" );
   string_t *value = string_make_from_cstring( "apple" );
   
   soa_configuration_put( configuration, key, value );
   
   string_t *key1 = string_make_from_cstring( "fruit_1" );
   string_t *value1 = string_make_from_cstring( "orange" );
   
   soa_configuration_put( configuration, key1, value1 );
   
   string_t *key2 = string_make_from_cstring( "meat_1" );
   string_t *value2 = string_make_from_cstring( "fish" );

   soa_configuration_put( configuration, key2, value2 );

   string_t *k = string_make_from_cstring( "food" );
   string_t *k1 = string_make_from_cstring( "fruit" );
   s_dlist_t *list1 = soa_configuration_superkey_list_items( configuration, k, k1 );
 
   CU_ASSERT( string_is_equal_cstring( s_dlist_item( list1, 0 ), "apple" ) == 1 );
      
   string_t *k2 = string_make_from_cstring( "meat" );
   s_dlist_t *list2 = soa_configuration_superkey_list_items( configuration, k, k2 );

   CU_ASSERT( string_is_equal_cstring( s_dlist_item( list2, 0 ), "fish" ) == 1 );

   string_dispose_with_contents( k );
   string_dispose_with_contents( k1 );
   string_dispose_with_contents( k2 );
   s_dlist_dispose( list1 );
   s_dlist_dispose( list2 );

   soa_configuration_dispose( configuration );

   return;
}

/**
   test_superkey_list_items_2
*/

void test_superkey_list_items_2( void )
{
   soa_configuration_t *configuration = soa_configuration_make();
   
   soa_configuration_put_cstring( configuration, "food:fruit_1", "apple" );
   soa_configuration_put_cstring( configuration, "fruit_1", "orange" );
   soa_configuration_put_cstring( configuration, "meat_1", "fish" );
   
   s_dlist_t *list1 = soa_configuration_superkey_list_items_cstring( configuration, "food", "fruit" );
 
   CU_ASSERT( string_is_equal_cstring( s_dlist_item( list1, 0 ), "apple" ) == 1 );
   
   s_dlist_t *list2 = soa_configuration_superkey_list_items_cstring( configuration, "food", "meat" );
 
   CU_ASSERT( string_is_equal_cstring( s_dlist_item( list2, 0 ), "fish" ) == 1 );
   
   s_dlist_dispose( list1 );
   s_dlist_dispose( list2 );

   soa_configuration_dispose( configuration );

   return;
}

int
add_test_superkey_list_items( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_superkey_list_items", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_superkey_list_items_1
   add_test_to_suite( p_suite, test_superkey_list_items_1, "test_superkey_list_items_1" );

   // test_superkey_list_items_2
   add_test_to_suite( p_suite, test_superkey_list_items_2, "test_superkey_list_items_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */


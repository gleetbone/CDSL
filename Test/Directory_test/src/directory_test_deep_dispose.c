/**
 @file directory_test_deep_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for directory_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for directory_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Directory.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_deep_dispose_1
*/

void test_deep_dispose_1( void )
{
   directory_t *dir= NULL;
   string_t *name = NULL;

   name = string_make();
   
   string_append_cstring( name, "test_dir" );

   dir = directory_make( name );

   CU_ASSERT( dir != NULL );

   directory_open_read( dir );

   string_deep_dispose ( &name );
   directory_deep_dispose( &dir );
   
   return;
}

/**
   test_deep_dispose_2
*/

void test_deep_dispose_2( void )
{
   directory_t *dir= NULL;

   dir = directory_make_cstring( "dir" );

   CU_ASSERT( dir != NULL );

   directory_deep_dispose( &dir );
   
   return;
}



int
add_test_deep_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_dispose_1
   add_test_to_suite( p_suite, test_deep_dispose_1, "test_deep_dispose_1" );

   // test_deep_dispose_2
   add_test_to_suite( p_suite, test_deep_dispose_2, "test_deep_dispose_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


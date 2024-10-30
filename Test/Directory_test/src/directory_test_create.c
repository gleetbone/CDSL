/**
 @file directory_test_create.c
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
   test_create_1
*/

void test_create_1( void )
{
   directory_t *dir = NULL;
   string_t *name = NULL;
   int32_t flag = 0;
   
   name = string_make();
   
   string_append_cstring( name, "test_dir1" );

   dir = directory_make( name );

   flag = directory_exists( dir );
   
   CU_ASSERT( flag == 0 );

   directory_create( dir );
   
   flag = directory_exists( dir );
   
   CU_ASSERT( flag == 1 );

   directory_delete( dir );
   
   string_deep_dispose ( &name );
   directory_dispose( &dir );
   
   return;
}

/**
   test_create_2
*/

void test_create_2( void )
{
   directory_t *dir= NULL;
   int32_t flag = 0;
   
   dir = directory_make_cstring( "test_dirx" );

   flag = directory_exists( dir );
   
   CU_ASSERT( flag == 0 );

   directory_create( dir );
   
   flag = directory_exists( dir );
   
   CU_ASSERT( flag == 1 );

   directory_delete( dir );
   
   flag = directory_exists( dir );
   
   CU_ASSERT( flag == 0 );

   directory_dispose( &dir );
   
   return;
}



int
add_test_create( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_create", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_create_1
   add_test_to_suite( p_suite, test_create_1, "test_create_1" );

   // test_create_2
   add_test_to_suite( p_suite, test_create_2, "test_create_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


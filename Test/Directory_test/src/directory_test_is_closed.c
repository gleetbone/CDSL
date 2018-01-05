/**
 @file directory_test_is_closed.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for ifr_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for ifr_make_from_cstring.

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
   test_is_closed_1
*/

void test_is_closed_1( void )
{
   directory_t *dir = NULL;
   string_t *name = NULL;

   name = string_make();

   string_append_cstring( name, "test_dir" );

   dir = directory_make( name );

   CU_ASSERT( directory_is_closed( dir ) == 1 );

   directory_open_read( dir );

   CU_ASSERT( directory_is_closed( dir ) == 0 );

   directory_close( dir );

   CU_ASSERT( directory_is_closed( dir ) == 1 );

   string_dispose_with_contents( name );
   directory_dispose( dir );

   return;
}


int
add_test_is_closed( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_closed", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_closed_1
   add_test_to_suite( p_suite, test_is_closed_1, "test_is_closed_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


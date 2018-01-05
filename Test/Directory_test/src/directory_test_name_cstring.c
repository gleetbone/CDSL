/**
 @file directory_test_name_cstring.c
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
   test_name_cstring_1
*/

void test_name_cstring_1( void )
{
   directory_t *dir= NULL;
   char_t *name = NULL;
   char_t *s = NULL;

   name =  "dir";

   dir = directory_make_cstring( name );

   CU_ASSERT( dir != NULL );

   s = directory_name_cstring( dir );

   CU_ASSERT( strcmp( name, s ) == 0 );

   directory_dispose( dir );

   return;
}



int
add_test_name_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_name_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_name_cstring_1
   add_test_to_suite( p_suite, test_name_cstring_1, "test_name_cstring_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file directory_test_links_cstring.c
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
   test_links_cstring_1
*/

void test_links_cstring_1( void )
{
   directory_t *dir= NULL;
   char_t **array = NULL;
   char_t *s = NULL;

   int32_t i = 0;

   dir = directory_make_cstring( "test_dir" );

   array = directory_links_cstring( dir );

   CU_ASSERT( array != NULL );

   s = array[i];
   while( s != NULL )
   {
      free( s );
      i = i + 1;
      s = array[i];
   }
   free( array );

   CU_ASSERT( i == 3 );

   directory_dispose( dir );

   return;
}



int
add_test_links_cstring( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_links_cstring", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_links_cstring_1
   add_test_to_suite( p_suite, test_links_cstring_1, "test_links_cstring_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


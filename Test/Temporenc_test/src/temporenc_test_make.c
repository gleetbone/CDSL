/**
 @file temporenc_test_make.c
 @author Greg Lee
 @version 0.0

 description: "tests for Temporenc_t"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Unit tests for Temporenc_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "Temporenc.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make_default();
   
   CU_ASSERT( t != NULL );

   temporenc_dispose( &t );
   
   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 1, 1, 0, 0 );
   
   CU_ASSERT( t != NULL );

   temporenc_dispose( &t );
   
   return;
}

/**
   test_make_3
*/

void test_make_3( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make_gmt( 2020, 6, 7, 12, 15, 30, 123 );
   
   CU_ASSERT( t != NULL );

   temporenc_dispose( &t );
   
   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


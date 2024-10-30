/**
 @file temporenc_test_is_equal.c
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   temporenc_t *t = NULL;
   temporenc_t *t1 = NULL;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 1, 1, 0, 0 );
   t1 = temporenc_make_default();
   
   CU_ASSERT( t != NULL );
   CU_ASSERT( t1 != NULL );

   CU_ASSERT( temporenc_is_equal( t, t1 ) == 0 );
   
   temporenc_copy( t1, t );

   CU_ASSERT( temporenc_is_equal( t, t1 ) == 1 );
   
   temporenc_dispose( &t );
   temporenc_dispose( &t1 );
   
   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


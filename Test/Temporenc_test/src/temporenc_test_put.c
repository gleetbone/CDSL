/**
 @file temporenc_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   temporenc_t *t = NULL;

   t = temporenc_make_default();
   
   temporenc_put( t, 2020, 6, 7, 12, 15, 30, 123, 1, 1, 2, 15 );
   
   CU_ASSERT( temporenc_year( t ) == 2020 );
   CU_ASSERT( temporenc_month( t ) == 6 );
   CU_ASSERT( temporenc_day( t ) == 7 );
   CU_ASSERT( temporenc_hour( t ) == 12 );
   CU_ASSERT( temporenc_minute( t ) == 15 );
   CU_ASSERT( temporenc_second( t ) == 30 );
   CU_ASSERT( temporenc_millisecond( t ) == 123 );
   CU_ASSERT( temporenc_millisecond_is_undefined( t ) == 0 );
   CU_ASSERT( temporenc_timezone_offset_sign( t ) == 1 );
   CU_ASSERT( temporenc_timezone_offset_hour( t ) == 2 );
   CU_ASSERT( temporenc_timezone_offset_minute( t ) == 15 );
   
   temporenc_dispose( &t );
   
   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


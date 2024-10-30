/**
 @file temporenc_test_comparisons.c
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
   test_comparisons_1
*/

void test_comparisons_1( void )
{
   temporenc_t *t = NULL;
   temporenc_t *t1 = NULL;

   t = temporenc_make_gmt( 2020, 6, 7, 12, 15, 30, 123 );
   t1 = temporenc_make_gmt( 2020, 6, 7, 12, 15, 30, 122 );
   
   CU_ASSERT( t != NULL );
   CU_ASSERT( t1 != NULL );

   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
     
   temporenc_put_year( t1, 2019 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_put_year( t1, 2020 );
   temporenc_put_month( t1, 5 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_put_month( t1, 6 );
   temporenc_put_day( t1, 6 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_put_day( t1, 7 );
   temporenc_put_hour( t1, 11 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_put_hour( t1, 12 );
   temporenc_put_minute( t1, 14 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_put_minute( t1, 15 );
   temporenc_put_second( t1, 29 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 1 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_put_second( t1, 30 );
   temporenc_put_millisecond( t1, 123 );
   CU_ASSERT( temporenc_is_less_than( t1, t ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_equal_to( t, t1 ) == 1 );
   CU_ASSERT( temporenc_is_less_than( t, t1 ) == 0 );
   CU_ASSERT( temporenc_is_greater_than( t1, t ) == 0 );
   
   temporenc_dispose( &t );
   temporenc_dispose( &t1 );
   
   return;
}

int
add_test_comparisons( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_comparisons", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_comparisons_1
   add_test_to_suite( p_suite, test_comparisons_1, "test_comparisons_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


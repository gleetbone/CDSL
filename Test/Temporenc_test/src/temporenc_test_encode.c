/**
 @file temporenc_test_encode.c
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
   test_encode_1
*/

void test_encode_1( void )
{
   temporenc_t *t = NULL;
   temporenc_t *t1 = NULL;
   uint64_t value = 0;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 1, 1, 1, 15 );
   t1 = temporenc_make_default();
   
   CU_ASSERT( t != NULL );
   CU_ASSERT( t1 != NULL );

   value = temporenc_encode( t );
   
   temporenc_decode( t1, value );
   
   CU_ASSERT( temporenc_year( t1 ) == 2020 );
   CU_ASSERT( temporenc_month( t1 ) == 6 );
   CU_ASSERT( temporenc_day( t1 ) == 7 );
   CU_ASSERT( temporenc_hour( t1 ) == 12 );
   CU_ASSERT( temporenc_minute( t1 ) == 15 );
   CU_ASSERT( temporenc_second( t1 ) == 30 );
   CU_ASSERT( temporenc_millisecond( t1 ) == 123 );
   CU_ASSERT( temporenc_timezone_offset_sign( t1 ) == 1 );
   CU_ASSERT( temporenc_timezone_offset_hour( t1 ) == 1 );
   CU_ASSERT( temporenc_timezone_offset_minute( t1 ) == 15 );
   
   temporenc_dispose( &t );
   temporenc_dispose( &t1 );
   
   return;
}

/**
   test_encode_2
*/

void test_encode_2( void )
{
   temporenc_t *t = NULL;
   temporenc_t *t1 = NULL;
   uint64_t value = 0;

   t = temporenc_make( 2020, 6, 7, 12, 15, 30, 123, 0, 1, 1, 15 );
   t1 = temporenc_make_default();
   
   CU_ASSERT( t != NULL );
   CU_ASSERT( t1 != NULL );

   value = temporenc_encode( t );
   
   temporenc_decode( t1, value );
   
   CU_ASSERT( temporenc_year( t1 ) == 2020 );
   CU_ASSERT( temporenc_month( t1 ) == 6 );
   CU_ASSERT( temporenc_day( t1 ) == 7 );
   CU_ASSERT( temporenc_hour( t1 ) == 12 );
   CU_ASSERT( temporenc_minute( t1 ) == 15 );
   CU_ASSERT( temporenc_second( t1 ) == 30 );
   CU_ASSERT( temporenc_millisecond( t1 ) == 0 );
   CU_ASSERT( temporenc_timezone_offset_sign( t1 ) == 1 );
   CU_ASSERT( temporenc_timezone_offset_hour( t1 ) == 1 );
   CU_ASSERT( temporenc_timezone_offset_minute( t1 ) == 15 );
   
   temporenc_dispose( &t );
   temporenc_dispose( &t1 );
   
   return;
}

int
add_test_encode( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_encode", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_encode_1
   add_test_to_suite( p_suite, test_encode_1, "test_encode_1" );

   // test_encode_2
   add_test_to_suite( p_suite, test_encode_2, "test_encode_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


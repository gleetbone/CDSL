/**
 @file Svd_test_inverse.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Svd_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Svd_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "f_Matvec.h"
#include "d_Matvec.h"
#include "cf_Matvec.h"
#include "cd_Matvec.h"

#include "f_Svd.h"
#include "d_Svd.h"
#include "cf_Svd.h"
#include "cd_Svd.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_inverse_1
*/

void test_inverse_1( void )
{
   f_svd_t *fsvd = NULL;
   f_matvec_t *m = NULL;
   f_matvec_t *m1 = NULL;
   f_matvec_t *m2 = NULL;
   f_matvec_t *one = NULL;

   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   m1 = f_svd_inverse( fsvd );
   m2 = f_matvec_multiplied( m, m1 );
   one = f_matvec_one( m );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &m1 );
   f_matvec_dispose( &m2 );
   f_matvec_dispose( &one );


   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 1.0, 2.0 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   m1 = f_svd_inverse( fsvd );
   m2 = f_matvec_multiplied( m, m1 );
   one = f_matvec_one( m );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &m1 );
   f_matvec_dispose( &m2 );
   f_matvec_dispose( &one );


   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 3, 6, 1.0, 0.0, 2.0, 1.0, 2.0, 0.0 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   m1 = f_svd_inverse( fsvd );
   m2 = f_matvec_multiplied( m, m1 );
   one = f_matvec_one( m2 );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );
   CU_ASSERT( m2 != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &m1 );
   f_matvec_dispose( &m2 );
   f_matvec_dispose( &one );

   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 0.00000000000001 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   m1 = f_svd_inverse( fsvd );
   m2 = f_matvec_multiplied( m, m1 );
   one = f_matvec_one( m );
   f_matvec_put( one, 0.0, 1, 1 );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &m1 );
   f_matvec_dispose( &m2 );
   f_matvec_dispose( &one );

   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 3, 6, 1.0, 0.0, 0.0000000000002, 0.0, 0.0, 0.0000000000003 );
   f_svd_set_input( fsvd, m );
   f_svd_svd( fsvd );
   m1 = f_svd_inverse( fsvd );
   m2 = f_matvec_multiplied( m, m1 );
   one = f_matvec_one( m2 );
   f_matvec_put( one, 0.0, 1, 1 );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );
   CU_ASSERT( m2 != NULL );

   CU_ASSERT( f_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   f_svd_deep_dispose( &fsvd );
   f_matvec_dispose( &m1 );
   f_matvec_dispose( &m2 );
   f_matvec_dispose( &one );

   return;
}

/**
   test_inverse_2
*/
void test_inverse_2( void )
{
   d_svd_t *dsvd = NULL;
   d_matvec_t *m = NULL;
   d_matvec_t *m1 = NULL;
   d_matvec_t *m2 = NULL;
   d_matvec_t *one = NULL;

   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 1.0 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   m1 = d_svd_inverse( dsvd );
   m2 = d_matvec_multiplied( m, m1 );
   one = d_matvec_one( m );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &m1 );
   d_matvec_dispose( &m2 );
   d_matvec_dispose( &one );


   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 1.0, 2.0 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   m1 = d_svd_inverse( dsvd );
   m2 = d_matvec_multiplied( m, m1 );
   one = d_matvec_one( m );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &m1 );
   d_matvec_dispose( &m2 );
   d_matvec_dispose( &one );


   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 3, 6, 1.0, 0.0, 2.0, 1.0, 2.0, 0.0 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   m1 = d_svd_inverse( dsvd );
   m2 = d_matvec_multiplied( m, m1 );
   one = d_matvec_one( m2 );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &m1 );
   d_matvec_dispose( &m2 );
   d_matvec_dispose( &one );

   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 2, 4, 1.0, 0.0, 0.0, 0.0000000000001 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   m1 = d_svd_inverse( dsvd );
   m2 = d_matvec_multiplied( m, m1 );
   one = d_matvec_one( m );
   d_matvec_put( one, 0.0, 1, 1 );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &m1 );
   d_matvec_dispose( &m2 );
   d_matvec_dispose( &one );

   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 3, 6, 1.0, 0.0, 0.0000000000002, 0.0, 0.0000000000003, 0.0 );
   d_svd_set_input( dsvd, m );
   d_svd_svd( dsvd );
   m1 = d_svd_inverse( dsvd );
   m2 = d_matvec_multiplied( m, m1 );
   one = d_matvec_one( m2 );
   d_matvec_put( one, 0.0, 1, 1 );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( d_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   d_svd_deep_dispose( &dsvd );
   d_matvec_dispose( &m1 );
   d_matvec_dispose( &m2 );
   d_matvec_dispose( &one );


   return;
}


/**
   test_inverse_3
*/

void test_inverse_3( void )
{
   cf_svd_t *cfsvd = NULL;
   cf_matvec_t *m = NULL;
   cf_matvec_t *m1 = NULL;
   cf_matvec_t *m2 = NULL;
   cf_matvec_t *one = NULL;

   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   m1 = cf_svd_inverse( cfsvd );
   m2 = cf_matvec_multiplied( m, m1 );
   one = cf_matvec_one( m );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &m1 );
   cf_matvec_dispose( &m2 );
   cf_matvec_dispose( &one );


   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 2, 4, 0.0 + 2.0*I, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 1.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   m1 = cf_svd_inverse( cfsvd );
   m2 = cf_matvec_multiplied( m, m1 );
   one = cf_matvec_one( m );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &m1 );
   cf_matvec_dispose( &m2 );
   cf_matvec_dispose( &one );


   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 3, 6, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 2.0*I, 0.0 + 1.0*I, 0.0 + 2.0*I, 0.0 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   m1 = cf_svd_inverse( cfsvd );
   m2 = cf_matvec_multiplied( m, m1 );
   one = cf_matvec_one( m2 );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &m1 );
   cf_matvec_dispose( &m2 );
   cf_matvec_dispose( &one );

   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 0.0000000000001 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   m1 = cf_svd_inverse( cfsvd );
   m2 = cf_matvec_multiplied( m, m1 );
   one = cf_matvec_one( m );
   cf_matvec_put( one, 0.0 + 0.0*I, 1, 1 );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &m1 );
   cf_matvec_dispose( &m2 );
   cf_matvec_dispose( &one );


   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 3, 6, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 0.0000000000002*I, 0.0 + 0.0*I, 0.0 + 0.0000000000003*I, 0.0 + 0.0*I );
   cf_svd_set_input( cfsvd, m );
   cf_svd_svd( cfsvd );
   m1 = cf_svd_inverse( cfsvd );
   m2 = cf_matvec_multiplied( m, m1 );
   one = cf_matvec_one( m2 );
   cf_matvec_put( one, 0.0 + 0.0*I, 1, 1 );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cf_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cf_svd_deep_dispose( &cfsvd );
   cf_matvec_dispose( &m1 );
   cf_matvec_dispose( &m2 );
   cf_matvec_dispose( &one );

   return;
}

/**
   test_inverse_4
*/

void test_inverse_4( void )
{
   cd_svd_t *cdsvd = NULL;
   cd_matvec_t *m = NULL;
   cd_matvec_t *m1 = NULL;
   cd_matvec_t *m2 = NULL;
   cd_matvec_t *one = NULL;

   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 1.0 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   m1 = cd_svd_inverse( cdsvd );
   m2 = cd_matvec_multiplied( m, m1 );
   one = cd_matvec_one( m );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &m1 );
   cd_matvec_dispose( &m2 );
   cd_matvec_dispose( &one );


   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 2, 4, 0.0 + 2.0*I, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 1.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   m1 = cd_svd_inverse( cdsvd );
   m2 = cd_matvec_multiplied( m, m1 );
   one = cd_matvec_one( m );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &m1 );
   cd_matvec_dispose( &m2 );
   cd_matvec_dispose( &one );


   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 3, 6, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 2.0*I, 0.0 + 1.0*I, 0.0 + 2.0*I, 0.0 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   m1 = cd_svd_inverse( cdsvd );
   m2 = cd_matvec_multiplied( m, m1 );
   one = cd_matvec_one( m2 );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &m1 );
   cd_matvec_dispose( &m2 );
   cd_matvec_dispose( &one );


   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 0.0*I, 0.0 + 0.0*I, 0.0 + 0.0*I, 0.0000000000001 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   m1 = cd_svd_inverse( cdsvd );
   m2 = cd_matvec_multiplied( m, m1 );
   one = cd_matvec_one( m );
   cd_matvec_put( one, 0.0 + 0.0*I, 1, 1 );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &m1 );
   cd_matvec_dispose( &m2 );
   cd_matvec_dispose( &one );


   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 3, 6, 0.0 + 1.0*I, 0.0 + 0.0*I, 0.0 + 0.0000000000002*I, 0.0 + 0.0*I, 0.0 + 0.0000000000003*I, 0.0 + 0.0*I );
   cd_svd_set_input( cdsvd, m );
   cd_svd_svd( cdsvd );
   m1 = cd_svd_inverse( cdsvd );
   m2 = cd_matvec_multiplied( m, m1 );
   one = cd_matvec_one( m2 );
   cd_matvec_put( one, 0.0 + 0.0*I, 1, 1 );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m1 != NULL );

   CU_ASSERT( cd_matvec_is_approximately_equal( m2, one, 0.000001 ) == 1 );

   cd_svd_deep_dispose( &cdsvd );
   cd_matvec_dispose( &m1 );
   cd_matvec_dispose( &m2 );
   cd_matvec_dispose( &one );

   return;
}

int
add_test_inverse( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_inverse", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_inverse_1
   add_test_to_suite( p_suite, test_inverse_1, "test_inverse_1" );

   // test_inverse_2
   add_test_to_suite( p_suite, test_inverse_2, "test_inverse_2" );

   // test_inverse_3
   add_test_to_suite( p_suite, test_inverse_3, "test_inverse_3" );

   // test_inverse_4
   add_test_to_suite( p_suite, test_inverse_4, "test_inverse_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file Quaternion.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Quaternions"

 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):

 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package.

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.

 @section Description

 Function definitions for the opaque Quaternion_t type.

*/

#include "Quaternion.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define DTOR (M_PI/180.0)
#define RTOD (180.0/M_PI)

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix    - string used to name this container type
   Mv_Prefix - string used to name the associated matvec type
   Type      - the type of the value

*/

/**
   Quaternion structure
*/

struct Quaternion_struct( Prefix )
{
   int32_t _type;
   int32_t _item_type;

   // current entries
   Type q0;
   Type q1;
   Type q2;
   Type q3;

   // multithread values if we include threading support
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
void invariant( Quaternion_type( Prefix ) *p )
{
   return;
}

#else

static
void invariant( p )
{
   return;
}

#endif

/**
   Quaternion_make
*/

Quaternion_type( Prefix ) *
Quaternion_make( Prefix )( Type q0, Type q1, Type q2, Type q3 )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   // set elements
   (*result).q0 = q0;
   (*result).q1 = q1;
   (*result).q2 = q2;
   (*result).q3 = q3;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_default
*/

Quaternion_type( Prefix ) *
Quaternion_make_default( Prefix )( void )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   // set elements
   (*result).q0 = 1.0;
   (*result).q1 = 0.0;
   (*result).q2 = 0.0;
   (*result).q3 = 0.0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from
*/

Quaternion_type( Prefix ) *
Quaternion_make_from( Prefix )( Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );

   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   // set elements
   (*result).q0 = (*other).q0;
   (*result).q1 = (*other).q1;
   (*result).q2 = (*other).q2;
   (*result).q3 = (*other).q3;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_array
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_array( Prefix )( Type *array )
{
   PRECONDITION( "array not null", array != NULL );

   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   // set elements
   (*result).q0 = array[0];
   (*result).q1 = array[1];
   (*result).q2 = array[2];
   (*result).q3 = array[3];

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_vector
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_vector( Prefix )( Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 4 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 4 ) ) ) );

   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   // set elements
   (*result).q0 = Matvec_vector_item( Mv_Prefix )( matvec, 0 );
   (*result).q1 = Matvec_vector_item( Mv_Prefix )( matvec, 1 );
   (*result).q2 = Matvec_vector_item( Mv_Prefix )( matvec, 2 );
   (*result).q3 = Matvec_vector_item( Mv_Prefix )( matvec, 3 );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_rotation_about_vector
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_rotation_about_vector( Prefix )( Type angle, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 3 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 3 ) ) ) );

   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Matvec_type( Mv_Prefix ) *v = Matvec_vector_normalized( Mv_Prefix )( matvec );

   Type c = cos( angle / 2.0 );
   Type s = sin( angle / 2.0 );

   // set elements
   (*result).q0 = c;
   (*result).q1 = s * Matvec_vector_item( Mv_Prefix )( v, 0 );
   (*result).q2 = s * Matvec_vector_item( Mv_Prefix )( v, 1 );
   (*result).q3 = s * Matvec_vector_item( Mv_Prefix )( v, 2 );

   Matvec_dispose( Mv_Prefix )( &v );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_rotation_degrees_about_vector
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_rotation_degrees_about_vector( Prefix )( Type angle, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 3 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 3 ) ) ) );

   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Matvec_type( Mv_Prefix ) *v = Matvec_vector_normalized( Mv_Prefix )( matvec );

   Type c = cos( DTOR * angle / 2.0 );
   Type s = sin( DTOR * angle / 2.0 );

   // set elements
   (*result).q0 = c;
   (*result).q1 = s * Matvec_vector_item( Mv_Prefix )( v, 0 );
   (*result).q2 = s * Matvec_vector_item( Mv_Prefix )( v, 1 );
   (*result).q3 = s * Matvec_vector_item( Mv_Prefix )( v, 2 );

   Matvec_dispose( Mv_Prefix )( &v );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_rotation_about_xyz
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_rotation_about_xyz( Prefix )( Type angle, Type x, Type y, Type z )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Type c = cos( angle / 2.0 );
   Type s = sin( angle / 2.0 );
   Type d = sqrt( x * x + y * y + z * z );

   // set elements
   (*result).q0 = c;
   if ( d > 0.0 )
   {
      d = 1.0 / d;
      (*result).q1 = s * x * d;
      (*result).q2 = s * y * d;
      (*result).q3 = s * z * d;
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_rotation_degrees_about_xyz
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( Type angle, Type x, Type y, Type z )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Type c = cos( DTOR * angle / 2.0 );
   Type s = sin( DTOR * angle / 2.0 );
   Type d = sqrt( x * x + y * y + z * z );

   // set elements
   (*result).q0 = c;
   if ( d > 0.0 )
   {
      d = 1.0 / d;
      (*result).q1 = s * x * d;
      (*result).q2 = s * y * d;
      (*result).q3 = s * z * d;
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_roll_pitch_yaw
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_roll_pitch_yaw( Prefix )( Type roll, Type pitch, Type yaw )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *qroll = NULL;
   Quaternion_type( Prefix ) *qpitch = NULL;
   Quaternion_type( Prefix ) *qyaw = NULL;

   qroll = Quaternion_make_from_rotation_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );
   qpitch = Quaternion_make_from_rotation_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );
   qyaw = Quaternion_make_from_rotation_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );
   q = Quaternion_multiplied( Prefix )( qyaw, qpitch  );
   Quaternion_multiply( Prefix )( q, qroll  );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &qroll  );
   Quaternion_dispose( Prefix )( &qpitch  );
   Quaternion_dispose( Prefix )( &qyaw  );
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_roll_pitch_yaw_degrees
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_roll_pitch_yaw_degrees( Prefix )( Type roll, Type pitch, Type yaw )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *qroll = NULL;
   Quaternion_type( Prefix ) *qpitch = NULL;
   Quaternion_type( Prefix ) *qyaw = NULL;

   qroll = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );
   qpitch = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );
   qyaw = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );
   q = Quaternion_multiplied( Prefix )( qyaw, qpitch  );
   Quaternion_multiply( Prefix )( q, qroll  );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &qroll  );
   Quaternion_dispose( Prefix )( &qpitch  );
   Quaternion_dispose( Prefix )( &qyaw  );
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_roll
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_roll( Prefix )( Type roll )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_roll_degrees
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_roll_degrees( Prefix )( Type roll )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_pitch
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_pitch( Prefix )( Type pitch )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_pitch_degrees
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_pitch_degrees( Prefix )( Type pitch )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_yaw
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_yaw( Prefix )( Type yaw )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Quaternion_make_from_yaw_degrees
*/

Quaternion_type( Prefix ) *
Quaternion_make_from_yaw_degrees( Prefix )( Type yaw )
{
   // allocate result struct
   Quaternion_type( Prefix ) * result
      = ( Quaternion_type( Prefix ) * ) calloc( 1, sizeof( Quaternion_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUATERNION_TYPE;
   (*result)._item_type = Type_Code;

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );

   // set elements
   (*result).q0 = (*q).q0;
   (*result).q1 = (*q).q1;
   (*result).q2 = (*q).q2;
   (*result).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}


/**
   Quaternion_dispose
*/

void
Quaternion_dispose( Prefix )( Quaternion_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == QUATERNION_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   Quaternion_as_array
*/

Type *
Quaternion_as_array( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = ( Type * ) calloc( 4, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   result[0] = (*current).q0;
   result[1] = (*current).q1;
   result[2] = (*current).q2;
   result[3] = (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_as_vector
*/

Matvec_type( Mv_Prefix ) *
Quaternion_as_vector( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Mv_Prefix ) *result = Matvec_make_column_vector( Mv_Prefix )( 4 );;

   Matvec_vector_put( Mv_Prefix )( result, (*current).q0, 0 );
   Matvec_vector_put( Mv_Prefix )( result, (*current).q1, 1 );
   Matvec_vector_put( Mv_Prefix )( result, (*current).q2, 2 );
   Matvec_vector_put( Mv_Prefix )( result, (*current).q3, 3 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_q0
*/

Type
Quaternion_q0( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).q0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_q1
*/

Type
Quaternion_q1( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).q1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_q2
*/

Type
Quaternion_q2( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).q2;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_q3
*/

Type
Quaternion_q3( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_magnitude
*/

Type
Quaternion_magnitude( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = sqrt( (*current).q0 * (*current).q0 + (*current).q1 * (*current).q1 + (*current).q2 * (*current).q2 + (*current).q3 * (*current).q3 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_squared_magnitude
*/

Type
Quaternion_squared_magnitude( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = (*current).q0 * (*current).q0 + (*current).q1 * (*current).q1 + (*current).q2 * (*current).q2 + (*current).q3 * (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_is_equal
*/

int32_t
Quaternion_is_equal( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;

   result = (*current).q0 == (*other).q0;

   if ( result == 1 )
   {
      result = (*current).q1 == (*other).q1;
   }

   if ( result == 1 )
   {
      result = (*current).q2 == (*other).q2;
   }

   if ( result == 1 )
   {
      result = (*current).q3 == (*other).q3;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_is_approximately_equal
*/

int32_t
Quaternion_is_approximately_equal( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other, Type precision )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   PRECONDITION( "precision not negative", precision >= 0.0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   Type max = 0.0;
   Type d = 0.0;

   // get max magnitude entry of current
   max = ( Type ) fabs( (*current).q0 );

   if ( ( Type ) fabs( max ) < (*current).q1 )
   {
      max = ( Type ) fabs( (*current).q1 );
   }

   if ( ( Type ) fabs( max ) < (*current).q2 )
   {
      max = ( Type ) fabs( (*current).q2 );
   }

   if ( ( Type ) fabs( max ) < (*current).q3 )
   {
      max = ( Type ) fabs( (*current).q3 );
   }

   // get value for comparing differences
   max = max * precision;

   // compare differences to max
   d = ( Type ) fabs( (*current).q0 - (*other).q0 );
   result = ( d < max );

   if ( result == 1 )
   {
      d = ( Type ) fabs( (*current).q1 - (*other).q1 );
      result = ( d < max );
   }

   if ( result == 1 )
   {
      d = ( Type ) fabs( (*current).q2 - (*other).q2 );
      result = ( d < max );
   }

   if ( result == 1 )
   {
      d = ( Type ) fabs( (*current).q3 - (*other).q3 );
      result = ( d < max );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_set
*/

void
Quaternion_set( Prefix )( Quaternion_type( Prefix ) *current, Type value, int32_t i )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "i OK", ( ( i >= 0 ) && ( i < 4 ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   switch( i )
   {
      case 0:
         (*current).q0 = value;
         break;

      case 1:
         (*current).q1 = value;
         break;

      case 2:
         (*current).q2 = value;
         break;

      case 3:
         (*current).q3 = value;
         break;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_q0
*/

void
Quaternion_set_q0( Prefix )( Quaternion_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).q0 = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_q1
*/

void
Quaternion_set_q1( Prefix )( Quaternion_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).q1 = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_q2
*/

void
Quaternion_set_q2( Prefix )( Quaternion_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).q2 = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_q3
*/

void
Quaternion_set_q3( Prefix )( Quaternion_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set item with value
   (*current).q3 = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from
*/

void
Quaternion_set_from( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 = (*other).q0;
   (*current).q1 = (*other).q1;
   (*current).q2 = (*other).q2;
   (*current).q3 = (*other).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_array
*/

void
Quaternion_set_from_array( Prefix )( Quaternion_type( Prefix ) *current, Type *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 = other[0];
   (*current).q1 = other[1];
   (*current).q2 = other[2];
   (*current).q3 = other[3];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_vector
*/

void
Quaternion_set_from_vector( Prefix )( Quaternion_type( Prefix ) *current, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 4 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 4 ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 = Matvec_vector_item( Mv_Prefix )( matvec, 0 );
   (*current).q1 = Matvec_vector_item( Mv_Prefix )( matvec, 1 );
   (*current).q2 = Matvec_vector_item( Mv_Prefix )( matvec, 2 );
   (*current).q3 = Matvec_vector_item( Mv_Prefix )( matvec, 3 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_rotation_about_vector
*/

void
Quaternion_set_from_rotation_about_vector( Prefix )( Quaternion_type( Prefix ) *current, Type angle, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 3 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 3 ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Mv_Prefix ) *v = Matvec_vector_normalized( Mv_Prefix )( matvec );

   Type c = cos( angle / 2.0 );
   Type s = sin( angle / 2.0 );

   // set elements
   (*current).q0 = c;
   (*current).q1 = s * Matvec_vector_item( Mv_Prefix )( v, 0 );
   (*current).q2 = s * Matvec_vector_item( Mv_Prefix )( v, 1 );
   (*current).q3 = s * Matvec_vector_item( Mv_Prefix )( v, 2 );

   Matvec_dispose( Mv_Prefix )( &v );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_rotation_degrees_about_vector
*/

void
Quaternion_set_from_rotation_degrees_about_vector( Prefix )( Quaternion_type( Prefix ) *current, Type angle, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 3 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 3 ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Mv_Prefix ) *v = Matvec_vector_normalized( Mv_Prefix )( matvec );

   Type c = cos( DTOR * angle / 2.0 );
   Type s = sin( DTOR * angle / 2.0 );

   // set elements
   (*current).q0 = c;
   (*current).q1 = s * Matvec_vector_item( Mv_Prefix )( v, 0 );
   (*current).q2 = s * Matvec_vector_item( Mv_Prefix )( v, 1 );
   (*current).q3 = s * Matvec_vector_item( Mv_Prefix )( v, 2 );

   Matvec_dispose( Mv_Prefix )( &v );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_rotation_about_xyz
*/

void
Quaternion_set_from_rotation_about_xyz( Prefix )( Quaternion_type( Prefix ) *current, Type angle, Type x, Type y, Type z )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type c = cos( angle / 2.0 );
   Type s = sin( angle / 2.0 );
   Type d = sqrt( x * x + y * y + z * z );

   // set elements
   (*current).q0 = c;
   if ( d > 0.0 )
   {
      d = 1.0 / d;
      (*current).q1 = s * x * d;
      (*current).q2 = s * y * d;
      (*current).q3 = s * z * d;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_rotation_degrees_about_xyz
*/

void
Quaternion_set_from_rotation_degrees_about_xyz( Prefix )( Quaternion_type( Prefix ) *current, Type angle, Type x, Type y, Type z )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type c = cos( DTOR * angle / 2.0 );
   Type s = sin( DTOR * angle / 2.0 );
   Type d = sqrt( x * x + y * y + z * z );

   // set elements
   (*current).q0 = c;
   if ( d > 0.0 )
   {
      d = 1.0 / d;
      (*current).q1 = s * x * d;
      (*current).q2 = s * y * d;
      (*current).q3 = s * z * d;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_roll_pitch_yaw
*/

void
Quaternion_set_from_roll_pitch_yaw( Prefix )( Quaternion_type( Prefix ) *current, Type roll, Type pitch, Type yaw )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *qroll = NULL;
   Quaternion_type( Prefix ) *qpitch = NULL;
   Quaternion_type( Prefix ) *qyaw = NULL;

   qroll = Quaternion_make_from_rotation_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );
   qpitch = Quaternion_make_from_rotation_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );
   qyaw = Quaternion_make_from_rotation_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );
   q = Quaternion_multiplied( Prefix )( qyaw, qpitch  );
   Quaternion_multiply( Prefix )( q, qroll  );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &qroll  );
   Quaternion_dispose( Prefix )( &qpitch  );
   Quaternion_dispose( Prefix )( &qyaw  );
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_roll_pitch_yaw_degrees
*/

void
Quaternion_set_from_roll_pitch_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *current, Type roll, Type pitch, Type yaw )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *qroll = NULL;
   Quaternion_type( Prefix ) *qpitch = NULL;
   Quaternion_type( Prefix ) *qyaw = NULL;

   qroll = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );
   qpitch = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );
   qyaw = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );
   q = Quaternion_multiplied( Prefix )( qyaw, qpitch  );
   Quaternion_multiply( Prefix )( q, qroll  );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &qroll  );
   Quaternion_dispose( Prefix )( &qpitch  );
   Quaternion_dispose( Prefix )( &qyaw  );
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_roll
*/

void
Quaternion_set_from_roll( Prefix )( Quaternion_type( Prefix ) *current, Type roll )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_roll_degrees
*/

void
Quaternion_set_from_roll_degrees( Prefix )( Quaternion_type( Prefix ) *current, Type roll )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( roll, 1.0, 0.0, 0.0 );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_pitch
*/

void
Quaternion_set_from_pitch( Prefix )( Quaternion_type( Prefix ) *current, Type pitch )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_pitch_degrees
*/

void
Quaternion_set_from_pitch_degrees( Prefix )( Quaternion_type( Prefix ) *current, Type pitch )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( pitch, 0.0, 1.0, 0.0 );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_yaw
*/

void
Quaternion_set_from_yaw( Prefix )( Quaternion_type( Prefix ) *current, Type yaw )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_set_from_yaw_degrees
*/

void
Quaternion_set_from_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *current, Type yaw )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q = Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( yaw, 0.0, 0.0, 1.0 );

   // set elements
   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   Quaternion_interpolate
*/

void
Quaternion_interpolate( Prefix )
(
   Quaternion_type( Prefix ) *current,
   Quaternion_type( Prefix ) *other,
   Type current_weight,
   Type other_weight
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;

   q  =  Quaternion_make( Prefix )
         (
            (*current).q0 * current_weight + (*other).q0 * other_weight,
            (*current).q1 * current_weight + (*other).q1 * other_weight,
            (*current).q2 * current_weight + (*other).q2 * other_weight,
            (*current).q3 * current_weight + (*other).q3 * other_weight
         );

   Quaternion_normalize( Prefix )( q );

   (*current).q0 = (*q).q0;
   (*current).q1 = (*q).q1;
   (*current).q2 = (*q).q2;
   (*current).q3 = (*q).q3;

   // dispose of intermediate products
   Quaternion_dispose( Prefix )( &q  );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_interpolated
*/

Quaternion_type( Prefix ) *
Quaternion_interpolated( Prefix )
(
   Quaternion_type( Prefix ) *current,
   Quaternion_type( Prefix ) *other,
   Type current_weight,
   Type other_weight
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = NULL;

   result
      =  Quaternion_make( Prefix )
         (
            (*current).q0 * current_weight + (*other).q0 * other_weight,
            (*current).q1 * current_weight + (*other).q1 * other_weight,
            (*current).q2 * current_weight + (*other).q2 * other_weight,
            (*current).q3 * current_weight + (*other).q3 * other_weight
         );

   Quaternion_normalize( Prefix )( result );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_roll_pitch_yaw
*/

Type *
Quaternion_get_roll_pitch_yaw( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = ( Type * ) calloc( 3, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   Quaternion_type( Prefix ) *q = current;

   result[0]
      =  atan2
         (
            2.0 * ( (*q).q2 * (*q).q3 + (*q).q0 * (*q).q1 ),
            (*q).q0 * (*q).q0 - (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3
         );

   result[1] = asin( -2.0 * ( (*q).q1 * (*q).q3 - (*q).q0 * (*q).q2 ) );

   result[2]
      =  atan2
         (
            2.0 * ( (*q).q1 * (*q).q2 + (*q).q0 * (*q).q3 ),
            (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 - (*q).q3 * (*q).q3
         );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_roll_pitch_yaw_degrees
*/

Type *
Quaternion_get_roll_pitch_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = ( Type * ) calloc( 3, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   Quaternion_type( Prefix ) *q = current;

   result[0]
      =  atan2
         (
            2.0 * ( (*q).q2 * (*q).q3 + (*q).q0 * (*q).q1 ),
            (*q).q0 * (*q).q0 - (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3
         ) * RTOD;

   result[1] = asin( -2.0 * ( (*q).q1 * (*q).q3 - (*q).q0 * (*q).q2 ) ) * RTOD;

   result[2]
      =  atan2
         (
            2.0 * ( (*q).q1 * (*q).q2 + (*q).q0 * (*q).q3 ),
            (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 - (*q).q3 * (*q).q3
         ) * RTOD;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_roll
*/

Type
Quaternion_get_roll( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = 0.0;

   Quaternion_type( Prefix ) *q = current;

   result
      =  atan2
         (
            2.0 * ( (*q).q2 * (*q).q3 + (*q).q0 * (*q).q1 ),
            (*q).q0 * (*q).q0 - (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3
         );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_roll_degrees
*/

Type
Quaternion_get_roll_degrees( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = 0.0;

   Quaternion_type( Prefix ) *q = current;

   result
      =  atan2
         (
            2.0 * ( (*q).q2 * (*q).q3 + (*q).q0 * (*q).q1 ),
            (*q).q0 * (*q).q0 - (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3
         ) * RTOD;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_pitch
*/

Type
Quaternion_get_pitch( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = 0;

   Quaternion_type( Prefix ) *q = current;

   result = asin( -2.0 * ( (*q).q1 * (*q).q3 - (*q).q0 * (*q).q2 ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_pitch_degrees
*/

Type
Quaternion_get_pitch_degrees( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = 0;

   Quaternion_type( Prefix ) *q = current;

   result = asin( -2.0 * ( (*q).q1 * (*q).q3 - (*q).q0 * (*q).q2 ) ) * RTOD;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_yaw
*/

Type
Quaternion_get_yaw( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = 0.0;

   Quaternion_type( Prefix ) *q = current;

   result
      =  atan2
         (
            2.0 * ( (*q).q1 * (*q).q2 + (*q).q0 * (*q).q3 ),
            (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 - (*q).q3 * (*q).q3
         );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_get_yaw_degrees
*/

Type
Quaternion_get_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = 0.0;

   Quaternion_type( Prefix ) *q = current;

   result
      =  atan2
         (
            2.0 * ( (*q).q1 * (*q).q2 + (*q).q0 * (*q).q3 ),
            (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 - (*q).q2 * (*q).q2 - (*q).q3 * (*q).q3
         ) * RTOD;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_rotate_vector
*/

void
Quaternion_rotate_vector( Prefix )( Quaternion_type( Prefix ) *current, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 3 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 3 ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *r = NULL;
   Quaternion_type( Prefix ) *s = NULL;

   // set up return and temp variables
   q  =  Quaternion_make( Prefix )
         (
            0.0,
            Matvec_vector_x( Mv_Prefix )( matvec ),
            Matvec_vector_y( Mv_Prefix )( matvec ),
            Matvec_vector_z( Mv_Prefix )( matvec )
         );
   r = Quaternion_make_from( Prefix )( current );
   s = Quaternion_inverse( Prefix )( r );

   // perform the rotation as a sequence of current multiplications
   Quaternion_multiply( Prefix )( r, q );
   Quaternion_multiply( Prefix )( r, s );

   Matvec_vector_put_x( Mv_Prefix )( matvec, (*r).q1 );
   Matvec_vector_put_y( Mv_Prefix )( matvec, (*r).q2 );
   Matvec_vector_put_z( Mv_Prefix )( matvec, (*r).q3 );

   // dispose of temp variables
   Quaternion_dispose( Prefix )( &q );
   Quaternion_dispose( Prefix )( &r );
   Quaternion_dispose( Prefix )( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_rotated_vector
*/

Matvec_type( Mv_Prefix ) *
Quaternion_rotated_vector( Prefix )( Quaternion_type( Prefix ) *current, Matvec_type( Mv_Prefix ) *matvec )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "matvec not null", matvec != NULL );
   PRECONDITION( "matvec is ok", ( ( ( Matvec_rows( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_columns( Mv_Prefix )( matvec ) == 3 ) ) || ( ( Matvec_columns( Mv_Prefix )( matvec ) == 1 ) && ( Matvec_rows( Mv_Prefix )( matvec ) == 3 ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Matvec_type( Mv_Prefix ) *result = NULL;
   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *r = NULL;
   Quaternion_type( Prefix ) *s = NULL;

   // set up return and temp variables
   result = Matvec_make_from( Prefix )( matvec );
   q  =  Quaternion_make( Prefix )
         (
            0.0,
            Matvec_vector_x( Mv_Prefix )( matvec ),
            Matvec_vector_y( Mv_Prefix )( matvec ),
            Matvec_vector_z( Mv_Prefix )( matvec )
         );
   r = Quaternion_make_from( Prefix )( current );
   s = Quaternion_inverse( Prefix )( r );

   // perform the rotation as a sequence of current multiplications
   Quaternion_multiply( Prefix )( r, q );
   Quaternion_multiply( Prefix )( r, s );

   Matvec_vector_put_x( Mv_Prefix )( result, (*r).q1 );
   Matvec_vector_put_y( Mv_Prefix )( result, (*r).q2 );
   Matvec_vector_put_z( Mv_Prefix )( result, (*r).q3 );

   // dispose of temp variables
   Quaternion_dispose( Prefix )( &q );
   Quaternion_dispose( Prefix )( &r );
   Quaternion_dispose( Prefix )( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_rotate_xyz
*/

Type *
Quaternion_rotate_xyz( Prefix )( Quaternion_type( Prefix ) *current, Type x, Type y, Type z )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = NULL;
   Quaternion_type( Prefix ) *q = NULL;
   Quaternion_type( Prefix ) *r = NULL;
   Quaternion_type( Prefix ) *s = NULL;

   // set up return and temp variables
   result = ( Type * ) calloc( 3, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   q  =  Quaternion_make( Prefix )( 0.0, x, y, z );
   r = Quaternion_make_from( Prefix )( current );
   s = Quaternion_inverse( Prefix )( r );

   // perform the rotation as a sequence of current multiplications
   Quaternion_multiply( Prefix )( r, q );
   Quaternion_multiply( Prefix )( r, s );

   result[0] = (*r).q1;
   result[1] = (*r).q2;
   result[2] = (*r).q3;

   // dispose of temp variables
   Quaternion_dispose( Prefix )( &q );
   Quaternion_dispose( Prefix )( &r );
   Quaternion_dispose( Prefix )( &s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_scale
*/

void
Quaternion_scale( Prefix )( Quaternion_type( Prefix ) *current, Type scale )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 = (*current).q0 * scale;
   (*current).q1 = (*current).q1 * scale;
   (*current).q2 = (*current).q2 * scale;
   (*current).q3 = (*current).q3 * scale;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_scaled
*/

Quaternion_type( Prefix ) *
Quaternion_scaled( Prefix )( Quaternion_type( Prefix ) *current, Type scale )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = Quaternion_make_default( Prefix )();

   (*result).q0 = (*current).q0 * scale;
   (*result).q1 = (*current).q1 * scale;
   (*result).q2 = (*current).q2 * scale;
   (*result).q3 = (*current).q3 * scale;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_conjugate
*/

void
Quaternion_conjugate( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 =  (*current).q0;
   (*current).q1 = -(*current).q1;
   (*current).q2 = -(*current).q2;
   (*current).q3 = -(*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_conjugated
*/

Quaternion_type( Prefix ) *
Quaternion_conjugated( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = Quaternion_make_default( Prefix )();

   (*result).q0 =  (*current).q0;
   (*result).q1 = -(*current).q1;
   (*result).q2 = -(*current).q2;
   (*result).q3 = -(*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_invert
*/

void
Quaternion_invert( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = current;
   Type m = (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 + (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3;
   if ( m > 0.0 )
   {
      m = 1.0 / m;
   }

   (*current).q0 =  m * (*current).q0;
   (*current).q1 = -m * (*current).q1;
   (*current).q2 = -m * (*current).q2;
   (*current).q3 = -m * (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_inverse
*/

Quaternion_type( Prefix ) *
Quaternion_inverse( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = Quaternion_make_default( Prefix )();
   Quaternion_type( Prefix ) *q = current;
   Type m = (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 + (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3;
   if ( m > 0.0 )
   {
      m = 1.0 / m;
   }

   (*result).q0 =  m * (*current).q0;
   (*result).q1 = -m * (*current).q1;
   (*result).q2 = -m * (*current).q2;
   (*result).q3 = -m * (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_normalize
*/

void
Quaternion_normalize( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = current;
   Type m = (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 + (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3;
   if ( m > 0.0 )
   {
      m = sqrt( m );
      m = 1.0 / m;
   }

   (*current).q0 = m * (*current).q0;
   (*current).q1 = m * (*current).q1;
   (*current).q2 = m * (*current).q2;
   (*current).q3 = m * (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_normalized
*/

Quaternion_type( Prefix ) *
Quaternion_normalized( Prefix )( Quaternion_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = Quaternion_make_default( Prefix )();
   Quaternion_type( Prefix ) *q = current;
   Type m = (*q).q0 * (*q).q0 + (*q).q1 * (*q).q1 + (*q).q2 * (*q).q2 + (*q).q3 * (*q).q3;
   if ( m > 0.0 )
   {
      m = sqrt( m );
      m = 1.0 / m;
   }

   (*result).q0 = m * (*current).q0;
   (*result).q1 = m * (*current).q1;
   (*result).q2 = m * (*current).q2;
   (*result).q3 = m * (*current).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_add
*/

void
Quaternion_add( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 = (*current).q0 + (*other).q0;
   (*current).q1 = (*current).q1 + (*other).q1;
   (*current).q2 = (*current).q2 + (*other).q2;
   (*current).q3 = (*current).q3 + (*other).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_added
*/

Quaternion_type( Prefix ) *
Quaternion_added( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = NULL;

   result = Quaternion_make_default( Prefix )();

   (*result).q0 = (*current).q0 + (*other).q0;
   (*result).q1 = (*current).q1 + (*other).q1;
   (*result).q2 = (*current).q2 + (*other).q2;
   (*result).q3 = (*current).q3 + (*other).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_subtract
*/

void
Quaternion_subtract( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).q0 = (*current).q0 - (*other).q0;
   (*current).q1 = (*current).q1 - (*other).q1;
   (*current).q2 = (*current).q2 - (*other).q2;
   (*current).q3 = (*current).q3 - (*other).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_subtracted
*/

Quaternion_type( Prefix ) *
Quaternion_subtracted( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = NULL;

   result = Quaternion_make_default( Prefix )();

   (*result).q0 = (*current).q0 - (*other).q0;
   (*result).q1 = (*current).q1 - (*other).q1;
   (*result).q2 = (*current).q2 - (*other).q2;
   (*result).q3 = (*current).q3 - (*other).q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Quaternion_multiply
*/

void
Quaternion_multiply( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *q = current;
   Quaternion_type( Prefix ) *o = other;

   Type q0 = 0;
   Type q1 = 0;
   Type q2 = 0;
   Type q3 = 0;

   // perform multiplication
   q0 = (*q).q0 * (*o).q0 - (*q).q1 * (*o).q1 - (*q).q2 * (*o).q2 - (*q).q3 * (*o).q3;
   q1 = (*q).q0 * (*o).q1 + (*q).q1 * (*o).q0 + (*q).q2 * (*o).q3 - (*q).q3 * (*o).q2;
   q2 = (*q).q0 * (*o).q2 - (*q).q1 * (*o).q3 + (*q).q2 * (*o).q0 + (*q).q3 * (*o).q1;
   q3 = (*q).q0 * (*o).q3 + (*q).q1 * (*o).q2 - (*q).q2 * (*o).q1 + (*q).q3 * (*o).q0;

   // put result into current
   (*q).q0 = q0;
   (*q).q1 = q1;
   (*q).q2 = q2;
   (*q).q3 = q3;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Quaternion_multiplied
*/

Quaternion_type( Prefix ) *
Quaternion_multiplied( Prefix )( Quaternion_type( Prefix ) *current, Quaternion_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUATERNION_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == QUATERNION_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Quaternion_type( Prefix ) *result = NULL;
   Quaternion_type( Prefix ) *q = current;
   Quaternion_type( Prefix ) *o = other;

   Type q0 = 0;
   Type q1 = 0;
   Type q2 = 0;
   Type q3 = 0;

   // perform multiplication
   q0 = (*q).q0 * (*o).q0 - (*q).q1 * (*o).q1 - (*q).q2 * (*o).q2 - (*q).q3 * (*o).q3;
   q1 = (*q).q0 * (*o).q1 + (*q).q1 * (*o).q0 + (*q).q2 * (*o).q3 - (*q).q3 * (*o).q2;
   q2 = (*q).q0 * (*o).q2 - (*q).q1 * (*o).q3 + (*q).q2 * (*o).q0 + (*q).q3 * (*o).q1;
   q3 = (*q).q0 * (*o).q3 + (*q).q1 * (*o).q2 - (*q).q2 * (*o).q1 + (*q).q3 * (*o).q0;

   // make result
   result = Quaternion_make( Prefix )( q0, q1, q2, q3 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/* End of file */


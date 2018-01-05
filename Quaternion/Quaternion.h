/**
 @file Quaternion.h
 @author Greg Lee
 @version 1.0.0
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

 Function declarations for the opaque Quaternion_t type.

*/

/**
   includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   Prefix    - string used to name this container type
   Mv_Prefix - string used to name the corresponding matvec (quaternion) type
   Type      - the type of the value - either float or double (float32_t or float64_t)
   
   Definition of roll, pitch, yaw:

   roll is rotation about x axis
   if thumb of right hand is pointing towards +x,
   then fingers of right hand curl in direction of positive roll rotation

   pitch is rotation about y axis
   if thumb of right hand is pointing towards +y,
   then fingers of right hand curl in direction of positive pitch rotation

   yaw is rotation about z axis
   if thumb of right hand is pointing towards +z,
   then fingers of right hand curl in direction of positive yaw rotation

   PLEASE NOTE:
   Your definition of roll, pitch, and yaw is likely different from this one.
   This definition, if used to describe an airplane, would have +x going from
   the center of mass through the nose (positive roll is right wingtip down),
   +y going from the center of mass through the left wing tip, (positive
   pitch is nose down), and +z going from the center of mass through the
   top of the airplane (positive yaw is nose to the left).

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Quaternion_struct( arg ) PRIMITIVE_CAT( arg, _quaternion_struct )
#define Quaternion_type( arg ) PRIMITIVE_CAT( arg, _quaternion_t )
#define Quaternion_name( arg ) PRIMITIVE_CAT( arg, _quaternion )

/** 
   Structure declarations
*/

struct Quaternion_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Quaternion_struct( Prefix ) Quaternion_type( Prefix );

/** 
   Initialization
*/

/**
   Quaternion_make
   
   Return a new Quaternion_t instance.
   
   @return Quaternion_t instance 
*/
#define Quaternion_make( arg ) PRIMITIVE_CAT( arg, _quaternion_make )
Quaternion_type( Prefix ) * Quaternion_make( Prefix )( Type q0, Type q1, Type q2, Type q3 );

/**
   Quaternion_make_default
   
   Return a new empty Quaternion_t instance.
   
   @return Quaternion_t instance 
*/
#define Quaternion_make_default( arg ) PRIMITIVE_CAT( arg, _quaternion_make_default )
Quaternion_type( Prefix ) * Quaternion_make_default( Prefix )( void );

/**
   Quaternion_make_from
   
   Return a new Quaternion_t instance that is a copy of another Quaternion_t instance.
   
   @param  other Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_make_from( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from )
Quaternion_type( Prefix ) * Quaternion_make_from( Prefix )( Quaternion_type( Prefix ) *other );

/**
   Quaternion_make_from_array
   
   Return a new Quaternion_t instance that contains arguments from the array.
   
   @param qarray quaternion array
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_array( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_array )
Quaternion_type( Prefix ) * Quaternion_make_from_array( Prefix )( Type *qarray );

/**
   Quaternion_make_from_vector
   
   Return a new Quaternion_t instance that contains arguments from the vector.
   
   @param matvec vector
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_vector )
Quaternion_type( Prefix ) * Quaternion_make_from_vector( Prefix )( Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_make_from_rotation_about_vector
   
   Return a new Quaternion_t instance that contains arguments from the quaternion
   rotated by angle.
   
   @param angle the rotation angle in radians to rotate the quaternion
   @param matvec 3D quaternion
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_rotation_about_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_rotation_about_vector )
Quaternion_type( Prefix ) * Quaternion_make_from_rotation_about_vector( Prefix )( Type angle, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_make_from_rotation_degrees_about_vector
   
   Return a new Quaternion_t instance that contains arguments from the quaternion
   rotated by angle.
   
   @param angle the rotation angle in degrees to rotate the quaternion
   @param matvec 3D quaternion
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_rotation_degrees_about_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_rotation_degrees_about_vector )
Quaternion_type( Prefix ) * Quaternion_make_from_rotation_degrees_about_vector( Prefix )( Type angle, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_make_from_rotation_about_xyz
   
   Return a new Quaternion_t instance that contains arguments from the xyz "quaternion"
   rotated by angle.
   
   @param angle the rotation angle in radians to rotate the quaternion
   @param x
   @param y
   @param z
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_rotation_about_xyz( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_rotation_about_xyz )
Quaternion_type( Prefix ) * Quaternion_make_from_rotation_about_xyz( Prefix )( Type angle, Type x, Type y, Type z );

/**
   Quaternion_make_from_rotation_degrees_about_xyz
   
   Return a new Quaternion_t instance that contains arguments from the xyz "quaternion"
   rotated by angle.
   
   @param angle the rotation angle in degrees to rotate the quaternion
   @param x
   @param y
   @param z
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_rotation_degrees_about_xyz( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_rotation_degrees_about_xyz )
Quaternion_type( Prefix ) * Quaternion_make_from_rotation_degrees_about_xyz( Prefix )( Type angle, Type x, Type y, Type z );

/**
   Quaternion_make_from_roll_pitch_yaw
   
   Return a new Quaternion_t instance derived from roll, pitch, and yaw.
   
   @param roll in radians
   @param pitch in radians
   @param yaw in radians
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_roll_pitch_yaw( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_roll_pitch_yaw )
Quaternion_type( Prefix ) * Quaternion_make_from_roll_pitch_yaw( Prefix )( Type roll, Type pitch, Type yaw );

/**
   Quaternion_make_from_roll_pitch_yaw_degrees
   
   Return a new Quaternion_t instance derived from roll, pitch, and yaw.
   
   @param roll in degrees
   @param pitch in degrees
   @param yaw in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_roll_pitch_yaw_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_roll_pitch_yaw_degrees )
Quaternion_type( Prefix ) * Quaternion_make_from_roll_pitch_yaw_degrees( Prefix )( Type roll, Type pitch, Type yaw );

/**
   Quaternion_make_from_roll
   
   Return a new Quaternion_t instance derived from roll.
   
   @param roll in radians
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_roll( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_roll )
Quaternion_type( Prefix ) * Quaternion_make_from_roll( Prefix )( Type roll );

/**
   Quaternion_make_from_roll_degrees
   
   Return a new Quaternion_t instance derived from roll.
   
   @param roll in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_roll_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_roll_degrees )
Quaternion_type( Prefix ) * Quaternion_make_from_roll_degrees( Prefix )( Type roll );

/**
   Quaternion_make_from_pitch
   
   Return a new Quaternion_t instance derived from pitch.
   
   @param pitch in radians
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_pitch( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_pitch )
Quaternion_type( Prefix ) * Quaternion_make_from_pitch( Prefix )( Type pitch );

/**
   Quaternion_make_from_pitch_degrees
   
   Return a new Quaternion_t instance derived from pitch.
   
   @param pitch in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_pitch_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_pitch_degrees )
Quaternion_type( Prefix ) * Quaternion_make_from_pitch_degrees( Prefix )( Type pitch );

/**
   Quaternion_make_from_yaw
   
   Return a new Quaternion_t instance derived from yaw.
   
   @param yaw in radians
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_yaw( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_yaw )
Quaternion_type( Prefix ) * Quaternion_make_from_yaw( Prefix )( Type yaw );

/**
   Quaternion_make_from_yaw_degrees
   
   Return a new Quaternion_t instance derived from yaw.
   
   @param yaw in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_make_from_yaw_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_make_from_yaw_degrees )
Quaternion_type( Prefix ) * Quaternion_make_from_yaw_degrees( Prefix )( Type yaw );



/**
   Disposal
*/

/**
   Quaternion_dispose
   
   Free a Quaternion_t instance.
   
   @param  quaternion Quaternion_t instance 
*/
#define Quaternion_dispose( arg ) PRIMITIVE_CAT( arg, _quaternion_dispose )
void Quaternion_dispose( Prefix )( Quaternion_type( Prefix ) *quaternion );

/** 
   Access
*/

/**
   Quaternion_as_array
   
   Return the quaternion as an array. Dispose of the array with free().
   
   @param  quaternion Quaternion_t instance 
   @return four element array of Type containing quaternion entries
*/
#define Quaternion_as_array( arg ) PRIMITIVE_CAT( arg, _quaternion_as_array )
Type * Quaternion_as_array( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_as_vector
   
   Return the quaternion as a vector. Dispose of the matvec with Matvec_dispose().
   
   @param  quaternion Quaternion_t instance 
   @return four element vector of Type containing quaternion entries
*/
#define Quaternion_as_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_as_vector )
Matvec_type( Mv_Prefix ) * Quaternion_as_vector( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_q0
   
   Return the value the q0 quaternion element.
   
   @param  quaternion Quaternion_t instance 
   @return the value of the item
*/
#define Quaternion_q0( arg ) PRIMITIVE_CAT( arg, _quaternion_q0 )
Type Quaternion_q0( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_q1
   
   Return the value the q1 quaternion element.
   
   @param  quaternion Quaternion_t instance 
   @return the value of the item
*/
#define Quaternion_q1( arg ) PRIMITIVE_CAT( arg, _quaternion_q1 )
Type Quaternion_q1( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_q2
   
   Return the value the q2 quaternion element.
   
   @param  quaternion Quaternion_t instance 
   @return the value of the item
*/
#define Quaternion_q2( arg ) PRIMITIVE_CAT( arg, _quaternion_q2 )
Type Quaternion_q2( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_q3
   
   Return the value the q3 quaternion element.
   
   @param  quaternion Quaternion_t instance 
   @return the value of the item
*/
#define Quaternion_q3( arg ) PRIMITIVE_CAT( arg, _quaternion_q3 )
Type Quaternion_q3( Prefix )( Quaternion_type( Prefix ) *quaternion );

/** 
   Measurement
*/

/**
   Quaternion_magnitude
   
   Return the magnitude of the quaternion.
   
   @param  quaternion Quaternion_t instance 
   @return magnitude of the quaternion
*/
#define Quaternion_magnitude( arg ) PRIMITIVE_CAT( arg, _quaternion_magnitude )
Type Quaternion_magnitude( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_squared_magnitude
   
   Return the squared magnitude of the quaternion.
   
   @param  quaternion Quaternion_t instance 
   @return squared magnitude of the quaternion
*/
#define Quaternion_squared_magnitude( arg ) PRIMITIVE_CAT( arg, _quaternion_squared_magnitude )
Type Quaternion_squared_magnitude( Prefix )( Quaternion_type( Prefix ) *quaternion );


/** 
   Comparison
*/

/**
   Quaternion_is_equal
   
   Returns 1 if the quaternion is equal to other.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @return 1 if quaternion is equal, 0 otherwise
*/
#define Quaternion_is_equal( arg ) PRIMITIVE_CAT( arg, _quaternion_is_equal )
int32_t Quaternion_is_equal( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_is_approximately_equal
   
   Returns 1 if the quaternion is approximately equal to other.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @param precision tolerance for the equality check
   @return 1 if quaternion is approximately equal, 0 otherwise
*/
#define Quaternion_is_approximately_equal( arg ) PRIMITIVE_CAT( arg, _quaternion_is_approximately_equal )
int32_t Quaternion_is_approximately_equal( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other, Type precision );


/** 
   Element change
*/

/**
   Quaternion_set
   
   Put value into quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  value what to insert
   @param  i item index, 0 <= i <= 3
*/
#define Quaternion_set( arg ) PRIMITIVE_CAT( arg, _quaternion_set )
void Quaternion_set( Prefix )( Quaternion_type( Prefix ) *quaternion, Type value, int32_t i );

/**
   Quaternion_set_q0
   
   Put value into quaternion at index 0.
   
   @param  quaternion Quaternion_t instance 
   @param  value what to insert
  
*/
#define Quaternion_set_q0( arg ) PRIMITIVE_CAT( arg, _quaternion_set_q0 )
void Quaternion_set_q0( Prefix )( Quaternion_type( Prefix ) *quaternion, Type value );

/**
   Quaternion_set_q1
   
   Put value into quaternion at index 1.
   
   @param  quaternion Quaternion_t instance 
   @param  value what to insert
  
*/
#define Quaternion_set_q1( arg ) PRIMITIVE_CAT( arg, _quaternion_set_q1 )
void Quaternion_set_q1( Prefix )( Quaternion_type( Prefix ) *quaternion, Type value );

/**
   Quaternion_set_q2
   
   Put value into quaternion at index 2.
   
   @param  quaternion Quaternion_t instance 
   @param  value what to insert
  
*/
#define Quaternion_set_q2( arg ) PRIMITIVE_CAT( arg, _quaternion_set_q2 )
void Quaternion_set_q2( Prefix )( Quaternion_type( Prefix ) *quaternion, Type value );

/**
   Quaternion_set_q3
   
   Put value into quaternion at index 3.
   
   @param  quaternion Quaternion_t instance 
   @param  value what to insert
  
*/
#define Quaternion_set_q3( arg ) PRIMITIVE_CAT( arg, _quaternion_set_q3 )
void Quaternion_set_q3( Prefix )( Quaternion_type( Prefix ) *quaternion, Type value );

/**
   Quaternion_set_from
   
   Sets copies of values of other into quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
*/
#define Quaternion_set_from( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from )
void Quaternion_set_from( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_set_from_array
   
   Sets copies of values of array into quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  qarray array of quaternion values 
*/
#define Quaternion_set_from_array( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_array )
void Quaternion_set_from_array( Prefix )( Quaternion_type( Prefix ) *quaternion, Type *qarray );

/**
   Quaternion_set_from_vector
   
   Sets copies of values of vector into quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  matvec quaternion of quaternion values 
*/
#define Quaternion_set_from_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_vector )
void Quaternion_set_from_vector( Prefix )( Quaternion_type( Prefix ) *quaternion, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_set_from_rotation_about_vector
   
   Return a new Quaternion_t instance that contains arguments from the quaternion
   rotated by angle.
   
   @param angle the rotation angle in radians to rotate the quaternion
   @param matvec 3D quaternion
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_rotation_about_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_rotation_about_vector )
void Quaternion_set_from_rotation_about_vector( Prefix )( Quaternion_type( Prefix ) *quaternion, Type angle, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_set_from_rotation_degrees_about_vector
   
   Return a new Quaternion_t instance that contains arguments from the quaternion
   rotated by angle.
   
   @param angle the rotation angle in degrees to rotate the quaternion
   @param matvec 3D quaternion
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_rotation_degrees_about_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_rotation_degrees_about_vector )
void Quaternion_set_from_rotation_degrees_about_vector( Prefix )( Quaternion_type( Prefix ) *quaternion, Type angle, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_set_from_rotation_about_xyz
   
   Return a new Quaternion_t instance that contains arguments from the xyz "quaternion"
   rotated by angle.
   
   @param angle the rotation angle in radians to rotate the quaternion
   @param x
   @param y
   @param z
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_rotation_about_xyz( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_rotation_about_xyz )
void Quaternion_set_from_rotation_about_xyz( Prefix )( Quaternion_type( Prefix ) *quaternion, Type angle, Type x, Type y, Type z );

/**
   Quaternion_set_from_rotation_degrees_about_xyz
   
   Return a new Quaternion_t instance that contains arguments from the xyz "quaternion"
   rotated by angle.
   
   @param angle the rotation angle in degrees to rotate the quaternion
   @param x
   @param y
   @param z
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_rotation_degrees_about_xyz( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_rotation_degrees_about_xyz )
void Quaternion_set_from_rotation_degrees_about_xyz( Prefix )( Quaternion_type( Prefix ) *quaternion, Type angle, Type x, Type y, Type z );

/**
   Quaternion_set_from_roll_pitch_yaw
   
   Return a new Quaternion_t instance derived from roll, pitch, and yaw.
   
   @param roll in radians
   @param pitch in radians
   @param yaw in radians
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_roll_pitch_yaw( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_roll_pitch_yaw )
void Quaternion_set_from_roll_pitch_yaw( Prefix )( Quaternion_type( Prefix ) *quaternion, Type roll, Type pitch, Type yaw );

/**
   Quaternion_set_from_roll_pitch_yaw_degrees
   
   Return a new Quaternion_t instance derived from roll, pitch, and yaw.
   
   @param roll in degrees
   @param pitch in degrees
   @param yaw in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_roll_pitch_yaw_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_roll_pitch_yaw_degrees )
void Quaternion_set_from_roll_pitch_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion, Type roll, Type pitch, Type yaw );

/**
   Quaternion_set_from_roll
   
   Return a new Quaternion_t instance derived from roll.
   
   @param roll in radians
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_roll( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_roll )
void Quaternion_set_from_roll( Prefix )( Quaternion_type( Prefix ) *quaternion, Type roll );

/**
   Quaternion_set_from_roll_degrees
   
   Return a new Quaternion_t instance derived from roll.
   
   @param roll in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_roll_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_roll_degrees )
void Quaternion_set_from_roll_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion, Type roll );

/**
   Quaternion_set_from_pitch
   
   Return a new Quaternion_t instance derived from pitch.
   
   @param pitch in radians
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_pitch( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_pitch )
void Quaternion_set_from_pitch( Prefix )( Quaternion_type( Prefix ) *quaternion, Type pitch );

/**
   Quaternion_set_from_pitch_degrees
   
   Return a new Quaternion_t instance derived from pitch.
   
   @param pitch in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_pitch_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_pitch_degrees )
void Quaternion_set_from_pitch_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion, Type pitch );

/**
   Quaternion_set_from_yaw
   
   Return a new Quaternion_t instance derived from yaw.
   
   @param yaw in radians
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_yaw( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_yaw )
void Quaternion_set_from_yaw( Prefix )( Quaternion_type( Prefix ) *quaternion, Type yaw );

/**
   Quaternion_set_from_yaw_degrees
   
   Return a new Quaternion_t instance derived from yaw.
   
   @param yaw in degrees
   @return Quaternion_t instance 
*/
#define Quaternion_set_from_yaw_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_set_from_yaw_degrees )
void Quaternion_set_from_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion, Type yaw );


/**
   Transformation
*/

/**
   Quaternion_interpolate
   
   Set to interpolation of current and other
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @param  current_weight weight to apply to current values 
   @param  other_weight weight to apply to other values 
   
*/
#define Quaternion_interpolate( arg ) PRIMITIVE_CAT( arg, _quaternion_interpolate )
void Quaternion_interpolate( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other, Type current_weight, Type other_weight );

/**
   Quaternion_interpolated
   
   Return interpolation of current and other
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @param  current_weight weight to apply to current values 
   @param  other_weight weight to apply to other values 
   
*/
#define Quaternion_interpolated( arg ) PRIMITIVE_CAT( arg, _quaternion_interpolated )
Quaternion_type( Prefix ) * Quaternion_interpolated( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other, Type current_weight, Type other_weight );

/**
   Conversion
*/

/**
   Quaternion_get_roll_pitch_yaw
   
   Return array of roll, pitch, yaw - dispose of with free()
   
   @param  quaternion Quaternion_t instance 
   @return array of roll, pitch, yaw in radians
   
*/
#define Quaternion_get_roll_pitch_yaw( arg ) PRIMITIVE_CAT( arg, _quaternion_get_roll_pitch_yaw )
Type * Quaternion_get_roll_pitch_yaw( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_roll_pitch_yaw_degrees
   
   Return array of roll, pitch, yaw - dispose of with free()
   
   @param  quaternion Quaternion_t instance 
   @return array of roll, pitch, yaw in degrees
   
*/
#define Quaternion_get_roll_pitch_yaw_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_get_roll_pitch_yaw_degrees )
Type * Quaternion_get_roll_pitch_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_roll
   
   Return roll in radians
   
   @param  quaternion Quaternion_t instance 
   @return roll in radians
   
*/
#define Quaternion_get_roll( arg ) PRIMITIVE_CAT( arg, _quaternion_get_roll )
Type Quaternion_get_roll( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_roll_degrees
   
   Return roll in degrees
   
   @param  quaternion Quaternion_t instance 
   @return roll in degrees
   
*/
#define Quaternion_get_roll_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_get_roll_degrees )
Type Quaternion_get_roll_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_pitch
   
   Return pitch in radians
   
   @param  quaternion Quaternion_t instance 
   @return pitch in radians
   
*/
#define Quaternion_get_pitch( arg ) PRIMITIVE_CAT( arg, _quaternion_get_pitch )
Type Quaternion_get_pitch( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_pitch_degrees
   
   Return pitch in degrees
   
   @param  quaternion Quaternion_t instance 
   @return pitch in degrees
   
*/
#define Quaternion_get_pitch_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_get_pitch_degrees )
Type Quaternion_get_pitch_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_yaw
   
   Return yaw in radians
   
   @param  quaternion Quaternion_t instance 
   @return yaw in radians
   
*/
#define Quaternion_get_yaw( arg ) PRIMITIVE_CAT( arg, _quaternion_get_yaw )
Type Quaternion_get_yaw( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_get_yaw_degrees
   
   Return yaw in degrees
   
   @param  quaternion Quaternion_t instance 
   @return yaw in degrees
   
*/
#define Quaternion_get_yaw_degrees( arg ) PRIMITIVE_CAT( arg, _quaternion_get_yaw_degrees )
Type Quaternion_get_yaw_degrees( Prefix )( Quaternion_type( Prefix ) *quaternion );


/**
   Miscellaneous
*/

/**
   Quaternion_rotate_vector
   
   Rotate 3D vector 
   
   @param  quaternion Quaternion_t instance 
   @param  matvec a 3D quaternion, will be rotated
   
*/
#define Quaternion_rotate_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_rotate_vector )
void Quaternion_rotate_vector( Prefix )( Quaternion_type( Prefix ) *quaternion, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_rotated_vector
   
   Rotate 3D vector 
   
   @param  quaternion Quaternion_t instance 
   @param  matvec a 3D quaternion, will be rotated
   
*/
#define Quaternion_rotated_vector( arg ) PRIMITIVE_CAT( arg, _quaternion_rotated_vector )
Matvec_type( Mv_Prefix ) * Quaternion_rotated_vector( Prefix )( Quaternion_type( Prefix ) *quaternion, Matvec_type( Mv_Prefix ) *matvec );

/**
   Quaternion_rotate_xyz
   
   Rotate 3D xyz "quaternion" 
   
   @param  quaternion Quaternion_t instance 
   @param  x
   @param  y
   @param  z
   @return array of xyz rotated
   
*/
#define Quaternion_rotate_xyz( arg ) PRIMITIVE_CAT( arg, _quaternion_rotate_xyz )
Type * Quaternion_rotate_xyz( Prefix )( Quaternion_type( Prefix ) *quaternion, Type x, Type y, Type z );


/**
   Basic operations
*/

/**
   Quaternion_scale
   
   Scale all items of quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  scale scale factor 
   @param  other Quaternion_t instance 
*/
#define Quaternion_scale( arg ) PRIMITIVE_CAT( arg, _quaternion_scale )
void Quaternion_scale( Prefix )( Quaternion_type( Prefix ) *quaternion, Type scale );

/**
   Quaternion_scaled
   
   Make copy of quaternion, return scaled copy.
   
   @param  quaternion Quaternion_t instance 
   @param  scale scale factor 
   @return Quaternion_t instance 
*/
#define Quaternion_scaled( arg ) PRIMITIVE_CAT( arg, _quaternion_scaled )
Quaternion_type( Prefix ) * Quaternion_scaled( Prefix )( Quaternion_type( Prefix ) *quaternion, Type scale );

/**
   Quaternion_conjugate
   
   Conjugate all items of quaternion.
   
   @param  quaternion Quaternion_t instance 
*/
#define Quaternion_conjugate( arg ) PRIMITIVE_CAT( arg, _quaternion_conjugate )
void Quaternion_conjugate( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_conjugated
   
   Make copy of quaternion, return conjugated copy.
   
   @param  quaternion Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_conjugated( arg ) PRIMITIVE_CAT( arg, _quaternion_conjugated )
Quaternion_type( Prefix ) * Quaternion_conjugated( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_invert
   
   Invert quaternion.
   
   @param  quaternion Quaternion_t instance 
*/
#define Quaternion_invert( arg ) PRIMITIVE_CAT( arg, _quaternion_invert )
void Quaternion_invert( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_inverse
   
   Make copy of quaternion, return inverted copy.
   
   @param  quaternion Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_inverse( arg ) PRIMITIVE_CAT( arg, _quaternion_inverse )
Quaternion_type( Prefix ) * Quaternion_inverse( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_normalize
   
   Normalize quaternion.
   
   @param  quaternion Quaternion_t instance 
*/
#define Quaternion_normalize( arg ) PRIMITIVE_CAT( arg, _quaternion_normalize )
void Quaternion_normalize( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_normalized
   
   Make copy of quaternion, return normalized copy.
   
   @param  quaternion Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_normalized( arg ) PRIMITIVE_CAT( arg, _quaternion_normalized )
Quaternion_type( Prefix ) * Quaternion_normalized( Prefix )( Quaternion_type( Prefix ) *quaternion );

/**
   Quaternion_add
   
   Add other to quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
*/
#define Quaternion_add( arg ) PRIMITIVE_CAT( arg, _quaternion_add )
void Quaternion_add( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_added
   
   Make copy of quaternion, return copy added to other.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_added( arg ) PRIMITIVE_CAT( arg, _quaternion_added )
Quaternion_type( Prefix ) * Quaternion_added( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_subtract
   
   Subtrace other from quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
*/
#define Quaternion_subtract( arg ) PRIMITIVE_CAT( arg, _quaternion_subtract )
void Quaternion_subtract( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_subtracted
   
   Make copy of quaternion, return copy minus other.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_subtracted( arg ) PRIMITIVE_CAT( arg, _quaternion_subtracted )
Quaternion_type( Prefix ) * Quaternion_subtracted( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_multiply
   
   Multiply quaternion and other, result in quaternion.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
*/
#define Quaternion_multiply( arg ) PRIMITIVE_CAT( arg, _quaternion_multiply )
void Quaternion_multiply( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );

/**
   Quaternion_multiplied
   
   Make copy of quaternion, return copy multiplied by other.
   
   @param  quaternion Quaternion_t instance 
   @param  other Quaternion_t instance 
   @return Quaternion_t instance 
*/
#define Quaternion_multiplied( arg ) PRIMITIVE_CAT( arg, _quaternion_multiplied )
Quaternion_type( Prefix ) * Quaternion_multiplied( Prefix )( Quaternion_type( Prefix ) *quaternion, Quaternion_type( Prefix ) *other );


/* End of file */




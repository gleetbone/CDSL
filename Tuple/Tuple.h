/**
 @file Tuple.h
 @author Greg Lee
 @version 0.0

 description: "File that holds tick data"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Defines functions to create, dispose, set, and access 64 bit binary
 date/time format.

*/

#include "base.h"

#ifndef TUPLE_H
#define TUPLE_H

/**
   Version
*/

#define TUPLE_VERSION_MAJOR 2
#define TUPLE_VERSION_MINOR 0
#define TUPLE_VERSION_PATCH 0

#define TUPLE_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define TUPLE_VERSION \
   TUPLE_MAKE_VERSION( TUPLE_VERSION_MAJOR, \
                       TUPLE_VERSION_MINOR, \
                       TUPLE_VERSION_PATCH )

/**
   Includes
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <base.h>
#include <String.h>

/**
   Defines
*/

#define TUPLE_INT8_TYPE          0x01
#define TUPLE_UINT8_TYPE         0x11
#define TUPLE_INT16_TYPE         0x02
#define TUPLE_UINT16_TYPE        0x12
#define TUPLE_INT32_TYPE         0x04
#define TUPLE_UINT32_TYPE        0x14
#define TUPLE_INT64_TYPE         0x08
#define TUPLE_UINT64_TYPE        0x18

#define TUPLE_FLOAT32_TYPE       0x24
#define TUPLE_FLOAT64_TYPE       0x28

#define TUPLE_POINTER_TYPE       0x30

#define TUPLE_STRING_TYPE        0x41

#define TUPLE_ARRAY_INT8_TYPE    0x81
#define TUPLE_ARRAY_UINT8_TYPE   0x91
#define TUPLE_ARRAY_INT16_TYPE   0x82
#define TUPLE_ARRAY_UINT16_TYPE  0x92
#define TUPLE_ARRAY_INT32_TYPE   0x84
#define TUPLE_ARRAY_UINT32_TYPE  0x94
#define TUPLE_ARRAY_INT64_TYPE   0x88
#define TUPLE_ARRAY_UINT64_TYPE  0x98

#define TUPLE_ARRAY_FLOAT32_TYPE       0xA4
#define TUPLE_ARRAY_FLOAT64_TYPE       0xA8

#define TUPLE_ARRAY_POINTER_TYPE       0xB0

#define TUPLE_ARRAY_STRING_TYPE        0xC1


/**
   Structure declaration
*/

struct tuple_struct;

/**
   Structure typedef
*/

typedef struct tuple_struct tuple_t;

/**
   tuple_make

   Make a tuple_t

   @param name the name of the tuple
   @param field_count how many fields are present, also used to count variadic parameters

   different kinds of fields take different number of arguments -
   type(s) are defined above
   character strings are of max length length-1, zero terminated

   single basic types - integer, floating point

   @param int32_t type
   @param char_t *name

   single character string

   @param int32_t type
   @param char_t *name
   @param int32_t character string length

   array of basic types - integer, floating point

   @param int32_t type
   @param char_t *name
   @param int32_t count

   array of character strings

   @param int32_t type
   @param char_t *name
   @param int32_t character string length
   @param int32_t count

   maximum character string length is 256, maximum array count is 65536

   @return the new structure
*/

tuple_t *
tuple_make( char_t *name, int32_t field_count, ... );

/**
   tuple_make_from_header_byte_array

   Creates and initializes tuple from a tuple header byte array

   @param byte_array the byte array
   @param count the length of the byte array
   @return pointer to new tuple
*/
tuple_t *
tuple_make_from_header_byte_array( uint8_t *byte_array, int32_t count );

/**
   tuple_clone

   Creates and initializes tuple from a tuple

   @param current the other component
   @return pointer to new tuple
*/
tuple_t *
tuple_clone( tuple_t *current );

/**
   tuple_deep_clone

   Creates and initializes tuple from a tuple

   @param current the other component
   @return pointer to new tuple
*/
tuple_t *
tuple_deep_clone( tuple_t *current );

/**
   tuple_copy

   Puts contents of other into current

   @param tuple the tuple
   @param other the other tuple
*/
void
tuple_copy( tuple_t *current, tuple_t *other );

/**
   tuple_deep_copy

   Puts contents of other into current

   @param tuple the tuple
   @param other the other tuple
*/
void
tuple_deep_copy( tuple_t *current, tuple_t *other );

/**
   tuple_is_equal

   Returns 1 of tuple is equal to other, 0 otherwise

   @param current the tuple
   @param other the other tuple
   @return 1 if equal, 0 otherwise
*/
int32_t
tuple_is_equal( tuple_t *current, tuple_t *other );

/**
   tuple_is_deep_equal

   Returns 1 of tuple is equal to other, 0 otherwise

   @param current the tuple
   @param other the other tuple
   @return 1 if equal, 0 otherwise
*/
int32_t
tuple_is_deep_equal( tuple_t *current, tuple_t *other );

/**
   tuple_dispose

   Closes and disposes of tuple

   @param current the tuple to dispose of
*/

void
tuple_dispose( tuple_t **current );

/**
   tuple_deep_dispose

   Closes and disposes of tuple

   @param current the tuple to dispose of
*/

void
tuple_deep_dispose( tuple_t **current );

/**
   tuple_name

   Returns a copy of the filename

   @param current the tuple
   @return copy of the filename
*/

char_t *
tuple_name( tuple_t *current );

/**
   tuple_field_count

   Returns number of fields in tuple

   @param current the tuple
   @return the number of fields in the tuple
*/

int32_t
tuple_field_count( tuple_t *current );

/**
   tuple_field_type

   Returns type of field at index, whether a single value or an array.

   @param current the tuple
   @param index which field
   @return the type of the field at index
*/

int32_t
tuple_field_type( tuple_t *current, int32_t index );

/**
   tuple_field_name

   Returns copy of name of field at index

   @param current the tuple
   @param index which field
   @return the name of the field at index
*/

char_t *
tuple_field_name( tuple_t *current, int32_t index );

/**
   tuple_field_array_count

   Returns number of items of field at index. Returns count of arrays,
   length of character strings, 1 for single values.

   @param current the tuple
   @param index which field
   @return the count of the array field at index
*/

int32_t
tuple_field_array_count( tuple_t *current, int32_t index );

/**
   tuple_field_string_length

   Returns number of characters in character string field at index. Returns
   length of single character string or array of character strings.

   @param current the tuple
   @param index which field
   @return the length of the character string field at index
*/

int32_t
tuple_field_string_length( tuple_t *current, int32_t index );

/**
   tuple_field_is_array

   Returns whether field at index is an array. Returns 1 for arrays,
   of ints, floats, and character strings. Returns 0 for ints, floats,
   and character strings.

   @param current the tuple
   @param index which field
   @return 1 if field is an array, 0 otherwise
*/

int32_t
tuple_field_is_array( tuple_t *current, int32_t index );

/**
   tuple_field_is_string

   Returns whether field at index is a character string or an arra
   of character strings. Returns 1 if so, 0 otherwise.

   @param current the tuple
   @param index which field
   @return 1 if field is a character string, 0 otherwise
*/

int32_t
tuple_field_is_string( tuple_t *current, int32_t index );


/**
   tuple_item_int8

   Returns data value for int8 field

   @param current the tuple
   @param index which field
   @return the value
*/

int8_t
tuple_item_int8
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_int8

   Sets data value for int8 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_int8
(
   tuple_t *current,
   int32_t index,
   int8_t value
);

/**
   tuple_item_int16

   Returns data value for int16 field

   @param current the tuple
   @param index which field
   @return the value
*/

int16_t
tuple_item_int16
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_int16

   Sets data value for int16 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_int16
(
   tuple_t *current,
   int32_t index,
   int16_t value
);

/**
   tuple_item_int32

   Returns data value for int32 field

   @param current the tuple
   @param index which field
   @return the value
*/

int32_t
tuple_item_int32
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_int32

   Sets data value for int32 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_int32
(
   tuple_t *current,
   int32_t index,
   int32_t value
);

/**
   tuple_item_int64

   Returns data value for int64 field

   @param current the tuple
   @param index which field
   @return the value
*/

int64_t
tuple_item_int64
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_int64

   Sets data value for int64 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_int64
(
   tuple_t *current,
   int32_t index,
   int64_t value
);

/**
   tuple_item_uint8

   Returns data value for uint8 field

   @param current the tuple
   @param index which field
   @return the value
*/

uint8_t
tuple_item_uint8
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_uint8

   Sets data value for uint8 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_uint8
(
   tuple_t *current,
   int32_t index,
   uint8_t value
);

/**
   tuple_item_uint16

   Returns data value for uint16 field

   @param current the tuple
   @param index which field
   @return the value
*/

uint16_t
tuple_item_uint16
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_uint16

   Sets data value for uint16 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_uint16
(
   tuple_t *current,
   int32_t index,
   uint16_t value
);

/**
   tuple_item_uint32

   Returns data value for uint32 field

   @param current the tuple
   @param index which field
   @return the value
*/

uint32_t
tuple_item_uint32
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_uint32

   Sets data value for uint32 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_uint32
(
   tuple_t *current,
   int32_t index,
   uint32_t value
);

/**
   tuple_item_uint64

   Returns data value for uint64 field

   @param current the tuple
   @param index which field
   @return the value
*/

uint64_t
tuple_item_uint64
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_uint64

   Sets data value for uint64 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_uint64
(
   tuple_t *current,
   int32_t index,
   uint64_t value
);

/**
   tuple_item_float32

   Returns data value for float32 field

   @param current the tuple
   @param index which field
   @return the value
*/

float32_t
tuple_item_float32
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_float32

   Sets data value for float32 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_float32
(
   tuple_t *current,
   int32_t index,
   float32_t value
);

/**
   tuple_item_float64

   Returns data value for float64 field

   @param current the tuple
   @param index which field
   @return the value
*/

float64_t
tuple_item_float64
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_float64

   Sets data value for float64 field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_float64
(
   tuple_t *current,
   int32_t index,
   float64_t value
);

/**
   tuple_item_pointer

   Returns data value for pointer field

   @param current the tuple
   @param index which field
   @return the value
*/

void *
tuple_item_pointer
(
   tuple_t *current,
   int32_t index
);

/**
   tuple_put_pointer

   Sets data value for pointer field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_pointer
(
   tuple_t *current,
   int32_t index,
   void *value
);

/**
   tuple_item_string

   Returns copy of string value for field

   @param current the tuple
   @param index which field
   @param count the length of the string
   @return the value
*/

char_t *
tuple_item_string
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_string

   Sets (zero terminated) character string data value for float64 field.
   The string will be truncated at the defined length-1 (to allow for ending
   zero character) is its length exceeds the defined length for the field

   @param current the tuple
   @param index which field
   @param value
*/

void
tuple_put_string
(
   tuple_t *current,
   int32_t index,
   char_t *value
);


/**
   tuple_item_aint8

   Returns copy of data value for aint8 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

int8_t *
tuple_item_aint8
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_aint8

   Sets data value for aint8 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_aint8
(
   tuple_t *current,
   int32_t index,
   int8_t *value,
   int32_t count
);

/**
   tuple_item_element_aint8

   Returns copy of data value for aint8 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

int8_t
tuple_item_element_aint8
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_aint8

   Sets data value for aint8 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_aint8
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   int8_t value
);

/**
   tuple_item_aint16

   Returns copy of data value for aint16 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

int16_t *
tuple_item_aint16
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_aint16

   Sets data value for aint16 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_aint16
(
   tuple_t *current,
   int32_t index,
   int16_t *value,
   int32_t count
);

/**
   tuple_item_element_aint16

   Returns copy of data value for aint16 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

int16_t
tuple_item_element_aint16
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_aint16

   Sets data value for aint16 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_aint16
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   int16_t value
);

/**
   tuple_item_aint32

   Returns copy of data value for aint32 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

int32_t *
tuple_item_aint32
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_aint32

   Sets data value for aint32 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_aint32
(
   tuple_t *current,
   int32_t index,
   int32_t *value,
   int32_t count
);

/**
   tuple_item_element_aint32

   Returns copy of data value for aint32 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

int32_t
tuple_item_element_aint32
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_aint32

   Sets data value for aint32 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_aint32
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   int32_t value
);

/**
   tuple_item_aint64

   Returns copy of data value for aint64 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

int64_t *
tuple_item_aint64
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_aint64

   Sets data value for aint64 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_aint64
(
   tuple_t *current,
   int32_t index,
   int64_t *value,
   int32_t count
);

/**
   tuple_item_element_aint64

   Returns copy of data value for aint64 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

int64_t
tuple_item_element_aint64
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_aint64

   Sets data value for aint64 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_aint64
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   int64_t value
);


/**
   tuple_item_auint8

   Returns copy of data value for auint8 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

uint8_t *
tuple_item_auint8
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_auint8

   Sets data value for auint8 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_auint8
(
   tuple_t *current,
   int32_t index,
   uint8_t *value,
   int32_t count
);

/**
   tuple_item_element_auint8

   Returns copy of data value for auint8 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

uint8_t
tuple_item_element_auint8
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_auint8

   Sets data value for auint8 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_auint8
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   uint8_t value
);

/**
   tuple_item_auint16

   Returns copy of data value for auint16 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

uint16_t *
tuple_item_auint16
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_auint16

   Sets data value for auint16 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_auint16
(
   tuple_t *current,
   int32_t index,
   uint16_t *value,
   int32_t count
);

/**
   tuple_item_element_auint16

   Returns copy of data value for auint16 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

uint16_t
tuple_item_element_auint16
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_auint16

   Sets data value for auint16 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_auint16
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   uint16_t value
);

/**
   tuple_item_auint32

   Returns copy of data value for auint32 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

uint32_t *
tuple_item_auint32
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_auint32

   Sets data value for auint32 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_auint32
(
   tuple_t *current,
   int32_t index,
   uint32_t *value,
   int32_t count
);

/**
   tuple_item_element_auint32

   Returns copy of data value for auint32 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

uint32_t
tuple_item_element_auint32
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_auint32

   Sets data value for auint32 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_auint32
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   uint32_t value
);

/**
   tuple_item_auint64

   Returns copy of data value for auint64 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

uint64_t *
tuple_item_auint64
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_auint64

   Sets data value for auint64 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_auint64
(
   tuple_t *current,
   int32_t index,
   uint64_t *value,
   int32_t count
);

/**
   tuple_item_element_auint64

   Returns copy of data value for auint64 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

uint64_t
tuple_item_element_auint64
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_auint64

   Sets data value for auint64 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_auint64
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   uint64_t value
);

/**
   tuple_item_afloat32

   Returns copy of data value for afloat32 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

float32_t *
tuple_item_afloat32
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_afloat32

   Sets data value for afloat32 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_afloat32
(
   tuple_t *current,
   int32_t index,
   float32_t *value,
   int32_t count
);

/**
   tuple_item_element_afloat32

   Returns copy of data value for afloat32 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

float32_t
tuple_item_element_afloat32
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_afloat32

   Sets data value for afloat32 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_afloat32
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   float32_t value
);

/**
   tuple_item_afloat64

   Returns copy of data value for afloat64 field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

float64_t *
tuple_item_afloat64
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_afloat64

   Sets data value for afloat64 field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_afloat64
(
   tuple_t *current,
   int32_t index,
   float64_t *value,
   int32_t count
);

/**
   tuple_item_element_afloat64

   Returns copy of data value for afloat64 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

float64_t
tuple_item_element_afloat64
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_afloat64

   Sets data value for afloat64 field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_afloat64
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   float64_t value
);

/**
   tuple_item_apointer

   Returns copy of data value for apointer field

   @param current the tuple
   @param index which field
   @param count the number of elements in the array
   @return the value
*/

void **
tuple_item_apointer
(
   tuple_t *current,
   int32_t index,
   int32_t *count
);

/**
   tuple_put_apointer

   Sets data value for apointer field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_apointer
(
   tuple_t *current,
   int32_t index,
   void **value,
   int32_t count
);

/**
   tuple_item_element_apointer

   Returns copy of data value for apointer field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

void *
tuple_item_element_apointer
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_apointer

   Sets data value for apointer field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_apointer
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   void *value
);

/**
   tuple_item_astring

   Returns copy of data value for astring field

   @param current the tuple
   @param index which field
   @param array_count the number of elements in the array
   @param string_length the (allocated) length of each string in the array
   @return the value
*/

char_t **
tuple_item_astring
(
   tuple_t *current,
   int32_t index,
   int32_t *array_count,
   int32_t *string_length
);

/**
   tuple_put_astring

   Sets data value for astring field

   @param current the tuple
   @param index which field
   @param value
   @param count the number of elements in the array
*/

void
tuple_put_astring
(
   tuple_t *current,
   int32_t index,
   char_t **value,
   int32_t array_count,
   int32_t string_length
);

/**
   tuple_item_element_astring

   Returns copy of data value for astring field at index

   @param current the tuple
   @param field_index which field
   @param array_index which elements in the array
   @return the value
*/

char_t *
tuple_item_element_astring
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index
);

/**
   tuple_put_element_astring

   Sets data value for astring field at index

   @param current the tuple
   @param field_index which field
   @param array_index which element in array
   @param value
*/

void
tuple_put_element_astring
(
   tuple_t *current,
   int32_t field_index,
   int32_t array_index,
   char_t *value
);

/**
   tuple_header_as_byte_array

   Returns byte array defining fields

   @param current the tuple
   @param count the length of the byte array
   @return the bute_array
*/

uint8_t *
tuple_header_as_byte_array
(
   tuple_t *current,
   int32_t *count
);

/**
   tuple_as_byte_array

   Returns copy of data in fields as byte array

   @param current the tuple
   @param count the length of the byte array
   @return the byte array
*/

uint8_t *
tuple_as_byte_array
(
   tuple_t *current,
   int32_t *count
);

/**
   tuple_from_byte_array

   Sets data in fields from byte array

   @param current the tuple
   @param the byte array
   @param count the length of the byte array
*/

void
tuple_from_byte_array
(
   tuple_t *current,
   uint8_t *byte_array,
   int32_t count
);

#ifdef __cplusplus
}
#endif

#endif /* TUPLE_H */

/* End of file */


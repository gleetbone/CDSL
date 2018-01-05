/**
 @file Raw_Buffer.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Raw Buffer (byte array addressable by word size and endianness)"
 
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

 Function declarations for the opaque raw_buffer_t type.

*/

#ifndef RAW_BUFFER_H
#define RAW_BUFFER_H


/**
   Includes
*/

#include "base.h"
#include "String.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
   Structure declarations
*/

struct raw_buffer_struct;

/**
   Structure typedefs
*/

typedef struct raw_buffer_struct raw_buffer_t;

/**
   creation
*/

/**
   raw_buffer_make

   Returns pointer to newly created raw_buffer_t

   @param n the size of the raw buffer
   @return pointer to raw buffer
*/

raw_buffer_t *
raw_buffer_make( int32_t n );


/**
   raw_buffer_make_copy_from

   Returns pointer to newly created raw_buffer_t, contents duplicated from
   other

   @param raw_buffer pointer to the buffer to be incorporated
   @return pointer to new raw buffer
*/

raw_buffer_t *
raw_buffer_make_copy_from( raw_buffer_t *other );


/**
   raw_buffer_make_from_pointer

   Returns pointer to newly created raw_buffer_t, contents make from
   pointer and count

   @param p pointer to the buffer to be incorporated
   @param n the size of the raw buffer
   @return pointer to raw buffer
*/

raw_buffer_t *
raw_buffer_make_from_pointer( uint8_t *p, int32_t n );


/**
   raw_buffer_dispose

   Disposes of raw buffer, does nothing to enclosed buffer of uint8_t's

   @param raw_buffer the raw buffer
*/

void
raw_buffer_dispose( raw_buffer_t *raw_buffer );

/**
   raw_buffer_dispose_with_contents

   Disposes of raw buffer, also frees enclosed buffer of uint8_t's

   @param raw_buffer the raw buffer
*/

void
raw_buffer_dispose_with_contents( raw_buffer_t *raw_buffer );


/**
   comparison
*/

/**
   raw_buffer_is_same

   If raw_buffer and other have same enclosed buffer of uint8_t's, returns 1,
   0 otherwise.

   @param raw_buffer the raw buffer
   @param other the other raw buffer
   @return 1 if contained buffers are same, 0 otherwise
*/

int32_t
raw_buffer_is_same( raw_buffer_t *raw_buffer, raw_buffer_t *other );


/**
   copying, changing
*/

/**
   raw_buffer_copy_from

   Put contents of other into raw buffer. Other has to be same size as raw_buffer

   @param raw_buffer the raw buffer
   @param other the other raw buffer
*/

void
raw_buffer_copy_from( raw_buffer_t *raw_buffer, raw_buffer_t *other );

/**
   raw_buffer_subcopy

   Put part of contents of other into raw buffer. 

   @param raw_buffer the raw buffer
   @param other the other raw buffer
   @param source_index where to start the copy from in other
   @param destination_index where to start the copy from in raw_buffer
   @param n how many uint8_t's to ciopy
*/

void
raw_buffer_subcopy
( 
   raw_buffer_t *raw_buffer, 
   raw_buffer_t *other, 
   int32_t destination_index,  
   int32_t source_index,  
   int32_t count  
);

/**
   raw_buffer_clear

   Set value of contained uint8_t's to zero

   @param raw_buffer the raw buffer
*/

void
raw_buffer_clear( raw_buffer_t *raw_buffer );

/**
   raw_buffer_append

   Append contents of other to end of raw_buffer. Other is unchanged

   @param raw_buffer the raw buffer
   @param other the other raw buffer
*/

void
raw_buffer_append( raw_buffer_t *raw_buffer, raw_buffer_t *other );

/**
   raw_buffer_resize

   Change size of contained uint8_t buffer. Added space is zero initialized

   @param raw_buffer the raw buffer
   @param n the new size for the buffer
*/

void
raw_buffer_resize( raw_buffer_t *raw_buffer, int32_t n );

/**
   measurement
*/

/**
   raw_buffer_base

   Return start address of contained uint8_t buffer

   @param raw_buffer the raw buffer
   @return pointer to the start of the uint8_t buffer
*/

uint8_t *
raw_buffer_base( raw_buffer_t *raw_buffer );

/**
   raw_buffer_count

   Return count of contained uint8_t buffer

   @param raw_buffer the raw buffer
   @return count of the uint8_t buffer
*/

int32_t
raw_buffer_count( raw_buffer_t *raw_buffer );


/**
   read primitive data item - platform specific
*/

/**
   raw_buffer_read_char

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

char_t
raw_buffer_read_char( raw_buffer_t *raw_buffer, int32_t index );


/**
   raw_buffer_read_uint8

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

uint8_t
raw_buffer_read_uint8( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_uint16

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

uint16_t
raw_buffer_read_uint16( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_uint32

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

uint32_t
raw_buffer_read_uint32( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_uint64

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

uint64_t
raw_buffer_read_uint64( raw_buffer_t *raw_buffer, int32_t index );


/**
   raw_buffer_read_int8

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

int8_t
raw_buffer_read_int8( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_int16

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

int16_t
raw_buffer_read_int16( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_int32

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

int32_t
raw_buffer_read_int32( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_int64

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

int64_t
raw_buffer_read_int64( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_float32

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

float32_t
raw_buffer_read_float32( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_float64

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

float64_t
raw_buffer_read_float64( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_pointer

   Read value at index

   @param raw_buffer the raw buffer
   @param index where to read from
   @return requested value
*/

void *
raw_buffer_read_pointer( raw_buffer_t *raw_buffer, int32_t index );


/**
   write primitive data item - platform specific
*/

/**
   raw_buffer_put_char

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_char( raw_buffer_t *raw_buffer, char_t value, int32_t index );


/**
   raw_buffer_put_uint8

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_uint8( raw_buffer_t *raw_buffer, uint8_t value, int32_t index );

/**
   raw_buffer_put_uint16

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_uint16( raw_buffer_t *raw_buffer, uint16_t value, int32_t index );

/**
   raw_buffer_put_uint32

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_uint32( raw_buffer_t *raw_buffer, uint32_t value, int32_t index );

/**
   raw_buffer_put_uint64

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_uint64( raw_buffer_t *raw_buffer, uint64_t value, int32_t index );


/**
   raw_buffer_put_int8

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_int8( raw_buffer_t *raw_buffer, int8_t value, int32_t index );

/**
   raw_buffer_put_int16

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_int16( raw_buffer_t *raw_buffer, int16_t value, int32_t index );

/**
   raw_buffer_put_int32

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_int32( raw_buffer_t *raw_buffer, int32_t value, int32_t index );

/**
   raw_buffer_put_int64

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_int64( raw_buffer_t *raw_buffer, int64_t value, int32_t index );

/**
   raw_buffer_put_float32

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_float32( raw_buffer_t *raw_buffer, float32_t value, int32_t index );

/**
   raw_buffer_put_float64

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_float64( raw_buffer_t *raw_buffer, float64_t value, int32_t index );

/**
   raw_buffer_put_pointer

   Write value at index

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_pointer( raw_buffer_t *raw_buffer, void *value, int32_t index );

/**
   strings
*/   

/**
   raw_buffer_read_string_zero_terminated

   Read string from index

   @param raw_buffer the raw buffer
   @param index where to write to
   @return string at index, zero terminated
*/

string_t *
raw_buffer_read_string_zero_terminated( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_cstring_zero_terminated

   Read cstring from index

   @param raw_buffer the raw buffer
   @param index where to write to
   @return cstring at index, zero terminated
*/

char_t *
raw_buffer_read_cstring_zero_terminated( raw_buffer_t *raw_buffer, int32_t index );

/**
   raw_buffer_read_string

   Read string from index with defined length

   @param raw_buffer the raw buffer
   @param index where to write to
   @param count the number of characters to read
   @return cstring at index
*/

string_t *
raw_buffer_read_string( raw_buffer_t *raw_buffer, int32_t index, int32_t count );

/**
   raw_buffer_read_cstring

   Read cstring from index with defined length

   @param raw_buffer the raw buffer
   @param index where to write to
   @param count the number of characters to read
   @return cstring at index
*/

char_t *
raw_buffer_read_cstring( raw_buffer_t *raw_buffer, int32_t index, int32_t count );

/**
   raw_buffer_put_string

   Write string to index. Does put terminating zero. 

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_string( raw_buffer_t *raw_buffer, string_t *value, int32_t index );

/**
   raw_buffer_put_cstring

   Write cstring to index. Does put terminating zero. 

   @param raw_buffer the raw buffer
   @param value what to write
   @param index where to write to
*/

void
raw_buffer_put_cstring( raw_buffer_t *raw_buffer, char_t *value, int32_t index );


/**
   hex strings
*/   

/**
   raw_buffer_to_display_string

   Convert buffer to hex display string 

   @param raw_buffer the raw buffer
   @param start_index where to start in the raw buffer
   @param count how many bytes to display in the raw buffer from start_index
   @return string of user friendly hex values 
*/

string_t *
raw_buffer_to_display_string( raw_buffer_t *raw_buffer, int32_t start_index, int32_t count );

/**
   raw_buffer_to_hex_string

   Convert buffer to hex string 

   @param raw_buffer the raw buffer
   @return cstring of hex values
*/

string_t *
raw_buffer_to_hex_string( raw_buffer_t *raw_buffer );

/**
   raw_buffer_to_hex_cstring

   Convert buffer to hex cstring 

   @param raw_buffer the raw buffer
   @return cstring of hex values
*/

char_t *
raw_buffer_to_hex_cstring( raw_buffer_t *raw_buffer );

/**
   raw_buffer_from_hex_string

   Convert hex string to enclosed buffer - changes count 

   @param raw_buffer the raw buffer
   @param string of hex values
*/

raw_buffer_t *
raw_buffer_from_hex_string( string_t *string );

/**
   raw_buffer_from_hex_cstring

   Convert hex cstring to enclosed buffer - changes count 

   @param raw_buffer the raw buffer
   @param string of hex values
*/

raw_buffer_t *
raw_buffer_from_hex_cstring( char_t *string );



#ifdef __cplusplus
}
#endif

#endif /* RAW_BUFFER_H */

/* End of file */




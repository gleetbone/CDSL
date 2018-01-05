/**
 @file Binary_File.h
 @author Greg Lee
 @version 1.0.0
 @brief: "binary file type"

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

 Function declarations for the opaque binary_file_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BINARY_FILE_T_H
#define BINARY_FILE_T_H


/**
   Includes
*/

#include "base.h"
#include "String.h"
#include "Raw_Buffer.h"

/**
   Structure declaration
*/

struct binary_file_struct;

/**
   Structure typedef
*/

typedef struct binary_file_struct binary_file_t;


/**
   Initialization
*/

/**
   binary_file_make

   Create and initialize a binary_file_t instance.
   Binary_File is not open by default.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make( string_t *name );

/**
   binary_file_make_cstring

   Create and initialize a binary_file_t instance.
   Binary_File is not open by default.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring( char_t *name );

/**
   binary_file_make_open_read

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_open_read( string_t *name );

/**
   binary_file_make_cstring_open_read

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_open_read( char_t *name );

/**
   binary_file_make_open_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for writing.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_open_write( string_t *name );

/**
   binary_file_make_cstring_open_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for writing.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_open_write( char_t *name );

/**
   binary_file_make_open_read_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and writing if it exists.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_open_read_write( string_t *name );

/**
   binary_file_make_cstring_open_read_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and writing if it exists.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_open_read_write( char_t *name );

/**
   binary_file_make_create_read_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and writing.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_create_read_write( string_t *name );

/**
   binary_file_make_cstring_create_read_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and writing.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_create_read_write( char_t *name );

/**
   binary_file_make_cstring_open_read_write

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and writing.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_open_read_write( char_t *name );

/**
   binary_file_make_open_append

   Create and initialize a binary_file_t instance.
   Binary_File is opened for appending.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_open_append( string_t *name );

/**
   binary_file_make_cstring_open_append

   Create and initialize a binary_file_t instance.
   Binary_File is opened for appending.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_open_append( char_t *name );

/**
   binary_file_make_open_read_append

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and appending.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_open_read_append( string_t *name );

/**
   binary_file_make_cstring_open_read_append

   Create and initialize a binary_file_t instance.
   Binary_File is opened for reading and appending.

   @param name the file name
   @return pointer to the new data structure
*/
binary_file_t *
binary_file_make_cstring_open_read_append( char_t *name );

/**
   Disposal
*/

/**
   binary_file_dispose

   Deallocates a binary_file_t instance.

   @param binary_file the binary_file struct to dispose
*/
void
binary_file_dispose( binary_file_t *binary_file );


/**
   Access
*/


/**
   binary_file_name

   Returns the binary_file name.

   @param binary_file the binary_file_t instance
   @return the name
*/
string_t *
binary_file_name( binary_file_t *binary_file );

/**
   binary_file_name_cstring

   Returns the binary_file name.

   @param binary_file the binary_file_t instance
   @return the name
*/
char_t *
binary_file_name_cstring( binary_file_t *binary_file );


/**
   binary_file_position

   Returns the current file position.

   @param binary_file the binary_file_t instance
   @return the file position
*/
int64_t
binary_file_position( binary_file_t *binary_file );


/**
   Measurement
*/

/**
   binary_file_count

   Returns the binary_file size.

   @param binary_file the binary_file_t instance
   @return the size
*/
int64_t
binary_file_count( binary_file_t *binary_file );


/**
   Status Report
*/

/**
   binary_file_after

   Returns 1 if binary_file has no valid cursor position to right

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 otherwise
*/
int32_t
binary_file_after( binary_file_t *binary_file );

/**
   binary_file_before

   Returns 1 if binary_file has no valid cursor position to left

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 otherwise
*/
int32_t
binary_file_before( binary_file_t *binary_file );

/**
   binary_file_off

   Returns 1 if binary_file has no item at current position

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 otherwise
*/
int32_t
binary_file_off( binary_file_t *binary_file );

/**
   binary_file_end_of_file

   Returns 1 if binary_file is at end of file

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 otherwise
*/
int32_t
binary_file_end_of_file( binary_file_t *binary_file );

/**
   binary_file_exists

   Returns 1 if binary_file exists

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 otherwise
*/
int32_t
binary_file_exists( binary_file_t *binary_file );

/**
   binary_file_is_closed

   Returns 1 if binary_file is closed

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 othewise
*/
int32_t
binary_file_is_closed( binary_file_t *binary_file );

/**
   binary_file_is_open_read

   Returns 1 if binary_file is open for reading

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 othewise
*/
int32_t
binary_file_is_open_read( binary_file_t *binary_file );

/**
   binary_file_is_open_write

   Returns 1 if binary_file is open for writing

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 othewise
*/
int32_t
binary_file_is_open_write( binary_file_t *binary_file );

/**
   binary_file_is_open_append

   Returns 1 if binary_file is open for appending

   @param binary_file the binary_file_t instance
   @return 1 if true, 0 othewise
*/
int32_t
binary_file_is_open_append( binary_file_t *binary_file );


/**
   Status Setting
*/

/**
   binary_file_open_read

   Opens binary_file for reading

   @param binary_file the binary_file_t instance
*/

void
binary_file_open_read( binary_file_t *binary_file );

/**
   binary_file_open_write

   Opens binary_file for writing

   @param binary_file the binary_file_t instance
*/

void
binary_file_open_write( binary_file_t *binary_file );

/**
   binary_file_open_append

   Opens binary_file for appending

   @param binary_file the binary_file_t instance
*/

void
binary_file_open_append( binary_file_t *binary_file );

/**
   binary_file_open_read_write

   Opens binary_file for reading and writing

   @param binary_file the binary_file_t instance
*/

void
binary_file_open_read_write( binary_file_t *binary_file );

/**
   binary_file_create_read_write

   Creates binary_file for reading and writing

   @param binary_file the binary_file_t instance
*/

void
binary_file_create_read_write( binary_file_t *binary_file );

/**
   binary_file_open_read_append

   Opens binary_file for reading and appending

   @param binary_file the binary_file_t instance
*/

void
binary_file_open_read_append( binary_file_t *binary_file );

/**
   binary_file_close

   Closes binary_file for reading

   @param binary_file the binary_file_t instance
*/

void
binary_file_close( binary_file_t *binary_file );

/**
   binary_file_create

   Creates binary_file (if it doesn't exist)

   @param binary_file the binary_file_t instance
*/



/**
   Cursor Movement
*/

/**
   binary_file_start

   Sets file pointer to start of file

   @param binary_file the binary_file_t instance
*/
void binary_file_start( binary_file_t *binary_file );

/**
   binary_file_finish

   Sets file pointer to end of file

   @param binary_file the binary_file_t instance
*/
void binary_file_finish( binary_file_t *binary_file );

/**
   binary_file_forth

   Advance file pointer by one

   @param binary_file the binary_file_t instance
*/
void binary_file_forth( binary_file_t *binary_file );

/**
   binary_file_back

   Advance file pointer by minus one

   @param binary_file the binary_file_t instance
*/
void binary_file_back( binary_file_t *binary_file );

/**
   binary_file_move

   Advance file pointer from current location by offset

   @param binary_file the binary_file_t instance
   @param offset the number of bytes to move the file pointer 
*/
void binary_file_move( binary_file_t *binary_file, int64_t offset );

/**
   binary_file_go

   Set file pointer to pos

   @param binary_file the binary_file_t instance
   @param pos the new file pointer 
*/
void binary_file_go( binary_file_t *binary_file, int64_t pos );

/**
   binary_file_recede

   Set file pointer offset backwards from end 

   @param binary_file the binary_file_t instance
   @param offset the number of bytes to move the file pointer back from EOF 
*/
void binary_file_recede( binary_file_t *binary_file, int64_t pos );


/**
   Element Change
*/

/**
   binary_file_flush

   Tell operating system to flush buffered data to disk

   @param binary_file the binary_file_t instance
*/
void binary_file_flush( binary_file_t *binary_file );

/**
   binary_file_touch

   Tell operating system to update time stamp for file

   @param binary_file the binary_file_t instance
*/
void binary_file_touch( binary_file_t *binary_file );

/**
   binary_file_rename

   Rename file

   @param binary_file the binary_file_t instance
   @param name the new file name
*/
void binary_file_rename( binary_file_t *binary_file, string_t *name );

/**
   binary_file_rename_cstring

   Rename file

   @param binary_file the binary_file_t instance
   @param name the new file name
*/
void binary_file_rename_cstring( binary_file_t *binary_file, char_t *name );

/**
   binary_file_put_int8

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_int8( binary_file_t *binary_file, int8_t arg );

/**
   binary_file_put_int16

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_int16( binary_file_t *binary_file, int16_t arg );

/**
   binary_file_put_int32

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_int32( binary_file_t *binary_file, int32_t arg );

/**
   binary_file_put_int64

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_int64( binary_file_t *binary_file, int64_t arg );

/**
   binary_file_put_uint8

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_uint8( binary_file_t *binary_file, uint8_t arg );

/**
   binary_file_put_uint16

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_uint16( binary_file_t *binary_file, uint16_t arg );

/**
   binary_file_put_uint32

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_uint32( binary_file_t *binary_file, uint32_t arg );

/**
   binary_file_put_uint64

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_uint64( binary_file_t *binary_file, uint64_t arg );

/**
   binary_file_put_float32

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_float32( binary_file_t *binary_file, float32_t arg );

/**
   binary_file_put_float64

   Write argument at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_float64( binary_file_t *binary_file, float64_t arg );

/**
   binary_file_put_raw_buffer

   Write contents of raw buffer at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_raw_buffer( binary_file_t *binary_file, raw_buffer_t *arg );

/**
   binary_file_put_string

   Write contents of string including terminating null at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_string( binary_file_t *binary_file, string_t *arg );

/**
   binary_file_put_cstring

   Write contents of cstring including terminating null at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_cstring( binary_file_t *binary_file, char_t *arg );

/**
   binary_file_put_bytes

   Write contents of arg at current file position

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
void binary_file_put_bytes( binary_file_t *binary_file, uint8_t *arg, int32_t count );

/**
   Input
*/

/**
   binary_file_read_int8

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
int8_t
binary_file_read_int8( binary_file_t *binary_file );

/**
   binary_file_read_int16

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
int16_t
binary_file_read_int16( binary_file_t *binary_file );

/**
   binary_file_read_int32

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
int32_t
binary_file_read_int32( binary_file_t *binary_file );

/**
   binary_file_read_int64

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
int64_t
binary_file_read_int64( binary_file_t *binary_file );

/**
   binary_file_read_uint8

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
uint8_t
binary_file_read_uint8( binary_file_t *binary_file );

/**
   binary_file_read_uint16

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
uint16_t
binary_file_read_uint16( binary_file_t *binary_file );

/**
   binary_file_read_uint32

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
uint32_t
binary_file_read_uint32( binary_file_t *binary_file );

/**
   binary_file_read_uint64

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
uint64_t
binary_file_read_uint64( binary_file_t *binary_file );

/**
   binary_file_read_float32

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
float32_t
binary_file_read_float32( binary_file_t *binary_file );

/**
   binary_file_read_float64

   Read item at current file position

   @param binary_file the binary_file_t instance
*/
float64_t
binary_file_read_float64( binary_file_t *binary_file );

/**
   binary_file_read_raw_buffer

   Return raw buffer containing count bytes from current position

   @param binary_file the binary_file_t instance
   @param count number of bytes to read
*/
raw_buffer_t *
binary_file_read_raw_buffer( binary_file_t *binary_file, int32_t count );

/**
   binary_file_read_string

   Return string containing count bytes from current position.
   Result will also contain trailing null byte.

   @param binary_file the binary_file_t instance
   @param count number of bytes to read
*/
string_t *
binary_file_read_string( binary_file_t *binary_file, int32_t count );

/**
   binary_file_read_cstring

   Return string containing count bytes from current position.
   Result will also contain trailing null byte.

   @param binary_file the binary_file_t instance
   @param count number of bytes to read
*/
char_t *
binary_file_read_cstring( binary_file_t *binary_file, int32_t count );

/**
   binary_file_read_bytes

   Return array of count bytes

   @param binary_file the binary_file_t instance
   @param arg the item to be written  
*/
uint8_t *
binary_file_read_bytes( binary_file_t *binary_file, int32_t count );

/**
   Removal
*/

/**
   binary_file_wipe_out

   Set file length to 0.

   @param binary_file the binary_file_t instance
*/
void
binary_file_wipe_out( binary_file_t *binary_file );

/**
   binary_file_delete

   Delete file.

   @param binary_file the binary_file_t instance
*/
void
binary_file_delete( binary_file_t *binary_file );


#ifdef __cplusplus
}
#endif

#endif /* BINARY_FILE_T_H */

/* End of file */





/**
 @file Directory.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Directories (contains files, links, and other directories"
 
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

 Function declarations for the opaque directory_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DIRECTORY_T_H
#define DIRECTORY_T_H


/**
   Includes
*/

#include "base.h"
#include "String.h"

/**
   Structure declaration
*/

struct directory_struct;

/**
   Structure typedef
*/

typedef struct directory_struct directory_t;


/**
   Initialization
*/

/**
   directory_make

   Create and initialize a directory_t instance.
   Directory is not open by default.

   @return pointer to the new data structure
*/
directory_t *
directory_make( string_t *name );

/**
   directory_make_cstring

   Create and initialize a directory_t instance.
   Directory is not open by default.

   @return pointer to the new data structure
*/
directory_t *
directory_make_cstring( char_t *name );

/**
   Disposal
*/

/**
   directory_dispose

   Deallocates a directory_t instance.

   @param directory the directory struct to dispose
*/
void
directory_dispose( directory_t *directory );


/**
   Access
*/


/**
   directory_name

   Returns the directory name.

   @param directory the directory_t instance
   @return the name
*/
string_t *
directory_name( directory_t *directory );

/**
   directory_name_cstring

   Returns the directory name.

   @param directory the directory_t instance
   @return the name
*/
char_t *
directory_name_cstring( directory_t *directory );

/**
   directory_last_entry

   Returns the current directory entry after the last call to read_entry.
   Null if off end of list.

   @param directory the directory_t instance
   @return the entry
*/
string_t *
directory_last_entry( directory_t *directory );

/**
   directory_last_entry_cstring

   Returns the current directory entry after the last call to read_entry.
   Null if off end of list.

   @param directory the directory_t instance
   @return the entry
*/
char_t *
directory_last_entry_cstring( directory_t *directory );

/**
   directory_filenames

   Returns the array of filename entries in directory. Last
   entry in array is NULL pointer

   @param directory the directory_t instance
   @return pointer to the array of filename entries
*/
string_t **
directory_filenames( directory_t *directory );

/**
   directory_filenames_cstring

   Returns the array of filename entries in directory. Last
   entry in array is NULL pointer

   @param directory the directory_t instance
   @return pointer to the array of filename entries
*/
char_t **
directory_filenames_cstring( directory_t *directory );

/**
   directory_filenames_count

   Returns the number of of filename entries in directory.

   @param directory the directory_t instance
   @return number of filenames
*/
int32_t
directory_filenames_count( directory_t *directory );

/**
   directory_directories

   Returns the array of directory entries in directory. Last
   entry in array is NULL pointer

   @param directory the directory_t instance
   @return pointer to the array of directory entries
*/
string_t **
directory_directories( directory_t *directory );

/**
   directory_directories_cstring

   Returns the array of directory entries in directory. Last
   entry in array is NULL pointer

   @param directory the directory_t instance
   @return pointer to the array of directory entries
*/
char_t **
directory_directories_cstring( directory_t *directory );

/**
   directory_directories_count

   Returns the number of directory entries in directory.

   @param directory the directory_t instance
   @return count of directories
*/
int32_t
directory_directories_count( directory_t *directory );

/**
   directory_links

   Returns the array of link entries in directory. Last
   entry in array is NULL pointer

   @param directory the directory_t instance
   @return pointer to the array of link entries
*/
string_t **
directory_links( directory_t *directory );

/**
   directory_links_cstring

   Returns the array of link entries in directory. Last
   entry in array is NULL pointer

   @param directory the directory_t instance
   @return pointer to the array of link entries
*/
char_t **
directory_links_cstring( directory_t *directory );

/**
   directory_links_count

   Returns the count of link entries in directory.

   @param directory the directory_t instance
   @return count of link entries
*/
int32_t
directory_links_count( directory_t *directory );


/**
   Status Report
*/

/**
   directory_is_closed

   Returns 1 if directory is not open

   @param directory the directory_t instance
   @return 1 if directory is not open, 0 otherwise
*/
int32_t
directory_is_closed( directory_t *directory );

/**
   directory_is_open_read

   Returns 1 if directory is open for reading

   @param directory the directory_t instance
   @return 1 if directory is open, 0 otherwise
*/
int32_t
directory_is_open_read( directory_t *directory );

/**
   directory_end_of_input

   Returns 1 if all directory entries have been read.

   @param directory the directory_t instance
   @return 1 if all entries have been read, 0 otherwise
*/
int32_t
directory_end_of_input( directory_t *directory );

/**
   directory_exists

   Returns 1 if directory exists

   @param directory the directory_t instance
   @return 1 if directory exists
*/
int32_t
directory_exists( directory_t *directory );

/**
   directory_is_readable

   Returns 1 if directory can be read

   @param directory the directory_t instance
   @return 1 if directory can be read
*/
int32_t
directory_is_readable( directory_t *directory );

/**
   directory_is_empty

   Returns 1 if directory is empty

   @param directory the directory_t instance
   @return 1 if directory is empty
*/
int32_t
directory_is_empty( directory_t *directory );


/**
   Basic Operations
*/

/**
   directory_open_read

   Opens directory for reading

   @param directory the directory_t instance
*/

void
directory_open_read( directory_t *directory );

/**
   directory_close

   Closes directory for reading

   @param directory the directory_t instance
*/

void
directory_close( directory_t *directory );

/**
   directory_create

   Creates directory (if it doesn't exist)

   @param directory the directory_t instance
*/

void
directory_create( directory_t *directory );

/**
   directory_create_mode

   Creates directory (if it doesn't exist) with specified mode

   @param directory the directory_t instance
   @param mode the desired directory mode
*/

void
directory_create_mode( directory_t *directory, int32_t mode );

/**
   directory_recursive_create

   Creates directory and its parent directories (if they don't exist)

   @param directory the directory_t instance
*/

void
directory_recursive_create( directory_t *directory );

/**
   directory_delete

   Deletes directory

   @param directory the directory_t instance
*/

void
directory_delete( directory_t *directory );

/**
   directory_delete_files

   Deletes all files in a directory

   @param directory the directory_t instance
*/

void
directory_delete_files( directory_t *directory );

/**
   directory_recursive_delete

   Deletes directory and its parent directories

   @param directory the directory_t instance
*/

void
directory_recursive_delete( directory_t *directory );


/**
   Input
*/

/**
   directory_read_next_entry

   Reads the next entry from directory, entry goes in last_entry

   @param directory the directory_t instance
*/
void directory_read_next_entry( directory_t *directory );


#ifdef __cplusplus
}
#endif

#endif /* DIRECTORY_T_H */

/* End of file */





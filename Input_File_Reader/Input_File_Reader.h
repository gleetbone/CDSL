/**
 @file Input_File_Reader.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Simple text file parser"
 
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

 Function declarations for the opaque ifr_t type.
 Parses a text file line by line into tokens

*/

#ifndef INPUT_FILE_READER_T_H
#define INPUT_FILE_READER_T_H

/**
   includes
*/

#include "base.h"
#include "String.h"
#include "s_DList.h"

/** 
   Structure declaration
*/

struct input_file_reader_struct;

/**
   Structure typedef
*/

typedef struct input_file_reader_struct ifr_t;


/** 
   Initialization
*/

/**
   ifr_make
   
   Return a new input_file_reader_t instance focused on "filename".
   First line is NOT processed.
   
   @param  filename fully qualified file name as a string_t  
   @return input_file_reader_t instance, NULL if filename does not exist 
*/
ifr_t *ifr_make( string_t *filename );

/**
   ifr_make_cstring
   
   Return a new input_file_reader_t instance focused on "filename".
   First line is NOT processed.
   
   @param  filename fully qualified file name as a C character string  
   @return input_file_reader_t instance, NULL if filename does not exist 
*/
ifr_t *ifr_make_cstring( char_t *filename );


/**
   Disposal
*/

/**
   ifr_dispose
   
   Free a ifr_t instance. The file is closed.
   
   @param  ifr ifr_t instance 
*/
void ifr_dispose( ifr_t *ifr );


/** 
   Access
*/

/**
   ifr_tokens
   
   Return the tokens of the most recently processed line.
   Tokens are valid until next call of forth or dispose on ifr instance.
   
   @param  ifr ifr_t instance 
   @return dlist of tokens
*/
s_dlist_t *ifr_tokens( ifr_t *ifr );

/**
   ifr_line
   
   Return the most recently processed line.
   Line is valid until next call of forth or dispose on ifr instance.
   
   @param  ifr ifr_t instance 
   @return last line processed
*/
string_t *ifr_line( ifr_t *ifr );

/**
   ifr_filename
   Return the filename being processed.
   
   @param  ifr ifr_t instance 
   @return filename being processed
*/
string_t *ifr_filename( ifr_t *ifr );


/** 
   Status Report
*/

/**
   ifr_eof
   
   Return 1 if file is at end, 0 otherwise
   
   @param  ifr ifr_t instance 
   @return 1 if file is eof, 0 otherwise
*/
int32_t ifr_eof( ifr_t *ifr );

/**
   ifr_skip_comments
   
   Return skip comments flag
   
   @param  ifr ifr_t instance 
   @return 1 if comments are to be skipped, 0 otherwise
*/
int32_t ifr_skip_comments( ifr_t *ifr );


/** 
   Element Change
*/

/**
   ifr_set_skip_comments
   
   set to 1 to skip comments, 0 to not skip comments
   
   @param  ifr ifr_t instance 
   @param  flag 1 to skip comments, 0 to not  otherwise
*/
void ifr_set_skip_comments( ifr_t *ifr, int32_t flag );


/** 
   Cursor Movement
*/

/**
   ifr_forth
   
   processes next line of input file, results accesed by tokens and line
   
   @param  ifr ifr_t instance 
*/
void ifr_forth( ifr_t *ifr );


#endif /* INPUT_FILE_READER_T_H */

/* End of file */




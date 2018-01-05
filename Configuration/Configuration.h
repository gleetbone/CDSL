/**
 @file Configuration.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Configuration composed of key-value pairs"
 
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

 Thread safe configuration object. Holds string-string configuration values.
 Function declarations for the opaque soa_configuration_t type.

*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
   Includes
*/

#include "base.h"
#include "String.h"
#include "s_DList.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
   Structure declarations
*/

struct soa_configuration_struct;

/**
   Structure typedefs
*/

typedef struct soa_configuration_struct soa_configuration_t;

/**
   soa_configuration_make

   create and initialize configuration for use

   @return the configuration
*/
soa_configuration_t *
soa_configuration_make( void );

/**
   soa_configuration_dispose

   dispose of configuration
   
   @param configuration the configuration
*/
void
soa_configuration_dispose( soa_configuration_t *configuration );

/**
   soa_configuration_put

   add key-value pair to configuration

   @param configuration the configuration
   @param key the name of the property
   @param value the value of the property
*/
void
soa_configuration_put
(
   soa_configuration_t *configuration,
   string_t *key,
   string_t *value
);

/**
   soa_configuration_put_cstring

   add key-value pair to configuration

   @param configuration the configuration
   @param key the name of the property
   @param value the value of the property
*/
void
soa_configuration_put_cstring
(
   soa_configuration_t *configuration,
   char_t *key,
   char_t *value
);

/**
   soa_configuration_has

   returns 1 if key is in configuration

   @param configuration the configuration
   @param key the name of the property
*/
int32_t
soa_configuration_has
(
   soa_configuration_t *configuration,
   string_t *key
);

/**
   soa_configuration_has_cstring

   returns 1 if key is in configuration

   @param key the name of the property
*/
int32_t
soa_configuration_has_cstring
(
   soa_configuration_t *configuration,
   char_t *key
);

/**
   soa_configuration_item

   returns value for key, NULL if key not present

   @param configuration the configuration
   @param key the name of the property
   @return value for key, or NULL if key not present
*/
string_t *
soa_configuration_item
(
   soa_configuration_t *configuration,
   string_t *key
);

/**
   soa_configuration_item_cstring

   returns value for key, NULL if key not present

   @param configuration the configuration
   @param key the name of the property
   @return value for key, or NULL if key not present
*/
string_t *
soa_configuration_item_cstring
(
   soa_configuration_t *configuration,
   char_t *key
);


/**
   soa_configuration_superkey_has

   returns 1 if superkey:key OR key is in configuration

   @param configuration the configuration
   @param superkey the higher level name part of the property
   @param key the name of the property
   @return 1 if superkey or key is present
*/
int32_t
soa_configuration_superkey_has
(
   soa_configuration_t *configuration,
   string_t *superkey,
   string_t *key
);

/**
   soa_configuration_superkey_has_cstring

   returns 1 if super:key OR key is in configuration

   @param configuration the configuration
   @param superkey the higher level name part of the property
   @param key the name of the property
   @return 1 if superkey or key is present
*/
int32_t
soa_configuration_superkey_has_cstring
(
   soa_configuration_t *configuration,
   char_t *superkey,
   char_t *key
);

/**
   soa_configuration_superkey_item

   Returns value for superkey:key if present. If not, returns value for
   key, if present. Else returns NULL.

   Allows for default value ( for key ) and specialized value
   ( superkey:key ) if present

   @param configuration the configuration
   @param superkey the higher level name part of the property
   @param key the name of the property
   @return value for superkey:key, else for key, else NULL
*/
string_t *
soa_configuration_superkey_item
(
   soa_configuration_t *configuration,
   string_t *superkey,
   string_t *key
);

/**
   soa_configuration_superkey_item_cstring

   Returns value for superkey:key if present. If not, returns value for
   key, if present. Else returns NULL.

   Allows for default value ( for key ) and specialized value
   ( superkey:key ) if present

   @param configuration the configuration
   @param superkey the higher level name part of the property
   @param key the name of the property
   @return value for superkey:key, else for key, else NULL
*/
string_t *
soa_configuration_superkey_item_cstring
(
   soa_configuration_t *configuration,
   char_t *superkey,
   char_t *key
);

/**
   soa_configuration_list_items

   Returns list of values for key_X, where X is a monotonically increasing
   integral numeral starting with 1. If not present, returns empty list.

   @param configuration the configuration
   @param key the base name of the property
   @return values for key_X where X is a numeral
*/
s_dlist_t *
soa_configuration_list_items
(
   soa_configuration_t *configuration,
   string_t *key
);

/**
   soa_configuration_list_items_cstring

   Returns list of values for key_X, where X is a monotonically increasing
   integral numeral starting with 1. If not present, returns empty list.

   @param configuration the configuration
   @param key the base name of the property
   @return values for key_X where X is a numeral
*/
s_dlist_t *
soa_configuration_list_items_cstring
(
   soa_configuration_t *configuration,
   char_t *key
);

/**
   soa_configuration_superkey_list_items

   Returns list of values for superkey:key_X (key_X), where X is a
   monotonically increasing integral numeral starting with 1. If not present,
   returns empty list. If superkey is present for *_1, will only return
   items with superkey

   @param configuration the configuration
   @param superkey the first part of the name of the property
   @param key the name of the property
   @return value for key, or NULL if key not present
*/
s_dlist_t *
soa_configuration_superkey_list_items
(
   soa_configuration_t *configuration,
   string_t *superkey,
   string_t *key
);

/**
   soa_configuration_superkey_list_items_cstring

   Returns list of values for superkey:key_X (key_X), where X is a
   monotonically increasing integral numeral starting with 1. If not present,
   returns empty list. Is superkey is present for *_1, will only return
   items with superkey

   @param configuration the configuration
   @param superkey the first part of the name of the property
   @param key the name of the property
   @return value for key, or NULL if key not present
*/
s_dlist_t *
soa_configuration_superkey_list_items_cstring
(
   soa_configuration_t *configuration,
   char_t *superkey,
   char_t *key
);

/**
   soa_configuration_set_from_file

   add key-value pairs to configuration from file

   @param configuration the configuration
   @param filename path to the file
*/
void
soa_configuration_set_from_file
(
   soa_configuration_t *configuration,
   string_t *filename
);

/**
   soa_configuration_set_from_file_cstring

   add key-value pairs to configuration from file

   @param configuration the configuration
   @param filename path to the file
*/
void
soa_configuration_set_from_file_cstring
(
   soa_configuration_t *configuration,
   char_t *filename
);

#ifdef __cplusplus
}
#endif

#endif /* CONFIGURATION_H */

/* End of file */




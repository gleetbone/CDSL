/**
 @file Configuration.h
 @author Greg Lee
 @version 2.0.0
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
 Function declarations for the opaque configuration_t type.

*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
   Version
*/

#define CONFIGURATION_VERSION_MAJOR 2
#define CONFIGURATION_VERSION_MINOR 0
#define CONFIGURATION_VERSION_PATCH 0

#define CONFIGURATION_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define CONFIGURATION_VERSION \
   CONFIGURATION_MAKE_VERSION( CONFIGURATION_VERSION_MAJOR, \
                       CONFIGURATION_VERSION_MINOR, \
                       CONFIGURATION_VERSION_PATCH )

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

struct configuration_struct;

/**
   Structure typedefs
*/

typedef struct configuration_struct configuration_t;

/*
   Initialization
*/

/**
   configuration_make

   create and initialize configuration for use

   @return the configuration
*/
configuration_t *
configuration_make( void );

/*
   Basic
*/

/**
   configuration_clone

   Create and initialize a clone of a configuration_t instance.

   @param current the configuration_t instance to initialize from
   @return pointer to the new data structure
*/
configuration_t *
configuration_clone( configuration_t *current );

/**
   configuration_deep_clone

   Create and initialize a deep clone of a configuration_t instance.

   @param current the configuration_t instance to initialize from
   @return pointer to the new data structure
*/
configuration_t *
configuration_deep_clone( configuration_t *current );

/**
   configuration_is_equal

   Returns 1 if the current contains the same values as other

   @param current the configuration_t instance
   @param other the other configuration_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t configuration_is_equal( configuration_t *current, configuration_t *other );

/**
   configuration_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the configuration_t instance
   @param other the other configuration_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t configuration_is_deep_equal( configuration_t *current, configuration_t *other );

/**
   configuration_copy

   Puts contents of other into current

   @param current the configuration_t instance to copy into
   @param other the configuration_t to copy from
*/
void configuration_copy( configuration_t *current, configuration_t *other );

/**
   configuration_deep_copy

   Puts contents of other into current

   @param current the configuration_t instance to copy into
   @param other the configuration_t to copy from
*/
void configuration_deep_copy( configuration_t *current, configuration_t *other );


/*
   Disposal
*/

/**
   configuration_dispose

   Free a configuration_t instance. The file is closed.

   @param  configuration configuration_t instance
*/
void configuration_dispose( configuration_t **configuration );

/**
   configuration_deep_dispose

   Free a configuration_t instance. The file is closed.

   @param  configuration configuration_t instance
*/
void configuration_deep_dispose( configuration_t **configuration );

/*
   Access
*/

/**
   configuration_item

   returns value for key, NULL if key not present

   @param configuration the configuration
   @param key the name of the property
   @return value for key, or NULL if key not present
*/
string_t *
configuration_item
(
   configuration_t *configuration,
   string_t *key
);

/**
   configuration_item_cstring

   returns value for key, NULL if key not present

   @param configuration the configuration
   @param key the name of the property
   @return value for key, or NULL if key not present
*/
string_t *
configuration_item_cstring
(
   configuration_t *configuration,
   char_t *key
);

/**
   configuration_superkey_item

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
configuration_superkey_item
(
   configuration_t *configuration,
   string_t *superkey,
   string_t *key
);

/**
   configuration_superkey_item_cstring

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
configuration_superkey_item_cstring
(
   configuration_t *configuration,
   char_t *superkey,
   char_t *key
);

/**
   configuration_list_items

   Returns list of values for key_X, where X is a monotonically increasing
   integral numeral starting with 1. If not present, returns empty list.

   @param configuration the configuration
   @param key the base name of the property
   @return values for key_X where X is a numeral
*/
s_dlist_t *
configuration_list_items
(
   configuration_t *configuration,
   string_t *key
);

/**
   configuration_list_items_cstring

   Returns list of values for key_X, where X is a monotonically increasing
   integral numeral starting with 1. If not present, returns empty list.

   @param configuration the configuration
   @param key the base name of the property
   @return values for key_X where X is a numeral
*/
s_dlist_t *
configuration_list_items_cstring
(
   configuration_t *configuration,
   char_t *key
);

/**
   configuration_superkey_list_items

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
configuration_superkey_list_items
(
   configuration_t *configuration,
   string_t *superkey,
   string_t *key
);

/**
   configuration_superkey_list_items_cstring

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
configuration_superkey_list_items_cstring
(
   configuration_t *configuration,
   char_t *superkey,
   char_t *key
);


/*
   Status Report
*/

/**
   configuration_has

   returns 1 if key is in configuration

   @param configuration the configuration
   @param key the name of the property
*/
int32_t
configuration_has
(
   configuration_t *configuration,
   string_t *key
);

/**
   configuration_has_cstring

   returns 1 if key is in configuration

   @param key the name of the property
*/
int32_t
configuration_has_cstring
(
   configuration_t *configuration,
   char_t *key
);

/**
   configuration_superkey_has

   returns 1 if superkey:key OR key is in configuration

   @param configuration the configuration
   @param superkey the higher level name part of the property
   @param key the name of the property
   @return 1 if superkey or key is present
*/
int32_t
configuration_superkey_has
(
   configuration_t *configuration,
   string_t *superkey,
   string_t *key
);

/**
   configuration_superkey_has_cstring

   returns 1 if super:key OR key is in configuration

   @param configuration the configuration
   @param superkey the higher level name part of the property
   @param key the name of the property
   @return 1 if superkey or key is present
*/
int32_t
configuration_superkey_has_cstring
(
   configuration_t *configuration,
   char_t *superkey,
   char_t *key
);

/*
   Element Change
*/

/**
   configuration_put

   add key-value pair to configuration

   @param configuration the configuration
   @param key the name of the property
   @param value the value of the property
*/
void
configuration_put
(
   configuration_t *configuration,
   string_t *key,
   string_t *value
);

/**
   configuration_put_cstring

   add key-value pair to configuration

   @param configuration the configuration
   @param key the name of the property
   @param value the value of the property
*/
void
configuration_put_cstring
(
   configuration_t *configuration,
   char_t *key,
   char_t *value
);

/*
   Basic Operation
*/

/**
   configuration_set_from_file

   add key-value pairs to configuration from file

   @param configuration the configuration
   @param filename path to the file
*/
void
configuration_set_from_file
(
   configuration_t *configuration,
   string_t *filename
);

/**
   configuration_set_from_file_cstring

   add key-value pairs to configuration from file

   @param configuration the configuration
   @param filename path to the file
*/
void
configuration_set_from_file_cstring
(
   configuration_t *configuration,
   char_t *filename
);

#ifdef __cplusplus
}
#endif

#endif /* CONFIGURATION_H */

/* End of file */




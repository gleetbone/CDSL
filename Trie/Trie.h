/**
 @file Trie.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Trie"

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

 Function declarations for the opaque Trie_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix      - string used to name this container type
   Key         - the type of the key
   Key_Element - the type of the key element
   Type        - the type of the value

   Macros that must be present (external to this file):

   KEY_ELEMENT_ACCESS_FUNCTION      -  gets the key element from a key instance
                                       at an index, first index is zero
   KEY_ELEMENT_EQUALITY_FUNCTION    -  compares two key element instances for equality
   KEY_ELEMENT_COMPARISON_FUNCTION  -  compares two key element instances for greater/lesser
   VALUE_DISPOSE_FUNCTION           -  frees a value instance

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define Trie_struct( arg ) PRIMITIVE_CAT( arg, _trie_struct )
#define Trie_type( arg ) PRIMITIVE_CAT( arg, _trie_t )
#define Trie_name( arg ) PRIMITIVE_CAT( arg, _trie )

#define Trie_cursor_struct( arg ) PRIMITIVE_CAT( arg, _trie_cursor_struct )
#define Trie_cursor_type( arg ) PRIMITIVE_CAT( arg, _trie_cursor_t )
#define Trie_cursor_name( arg ) PRIMITIVE_CAT( arg, _trie_cursor )

/**
   Structure declarations
*/

struct Trie_struct( Prefix );
struct Trie_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct Trie_struct( Prefix ) Trie_type( Prefix );
typedef struct Trie_cursor_struct( Prefix ) Trie_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   Trie_make

   Return a new empty Trie_t instance.

   @param  capacity the maximum number of items the cache can hold
   @return Trie_t instance
*/
#define Trie_make( arg ) PRIMITIVE_CAT( arg, _trie_make )
Trie_type( Prefix ) * Trie_make( Prefix )( void );

/*
   Disposal
*/

/**
   Trie_dispose

   Frees a Trie_t instance without freeing its contained key elements and values.

   @param current Trie_t instance
*/
#define Trie_dispose( arg ) PRIMITIVE_CAT( arg, _trie_dispose )
void Trie_dispose( Prefix )( Trie_type( Prefix ) **current );

/**
   Trie_dispose_with_contents

   Frees a Trie_t instance and its contained key elements and values.

   @param current Trie_t instance
*/
#define Trie_deep_dispose( arg ) PRIMITIVE_CAT( arg, _trie_deep_dispose )
void Trie_deep_dispose( Prefix )( Trie_type( Prefix ) **current );

/*
   Access
*/

/**
   Trie_item

   Returns the value of the item in the Trie_t instance associated
   with key, if present.

   @param  current Trie_t instance
   @param  key a Key instance
   @return a Type value
*/
#define Trie_item( arg ) PRIMITIVE_CAT( arg, _trie_item )
Type Trie_item( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length );


/*
   Measurement
*/

/**
   Trie_count

   Returns count of the Trie_t instance's items.

   @param  current Trie_t instance
   @return count of items in trie
*/
#define Trie_count( arg ) PRIMITIVE_CAT( arg, _trie_count )
int32_t Trie_count( Prefix )( Trie_type( Prefix ) *current );

/*
   Status report
*/

/**
   Trie_is_empty

   Returns 1 if the Trie_t instance contains no items, otherwise 0.

   @param  current Trie_t instance
   @return 1 if empty, otherwise 0
*/
#define Trie_is_empty( arg ) PRIMITIVE_CAT( arg, _trie_is_empty )
int32_t Trie_is_empty( Prefix )( Trie_type( Prefix ) *current );

/**
   Trie_has_key

   Returns 1 if the Trie_t instance contains the key, otherwise 0.

   @param  current Trie_t instance
   @return 1 if trie has key, otherwise 0
*/
#define Trie_has_key( arg ) PRIMITIVE_CAT( arg, _trie_has_key )
int32_t Trie_has_key( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length );

/**
   Trie_has

   Returns 1 if the Trie_t instance contains an item at the key, otherwise 0.

   @param  current Trie_t instance
   @return 1 if trie has key, otherwise 0
*/
#define Trie_has( arg ) PRIMITIVE_CAT( arg, _trie_has )
int32_t Trie_has( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length );


/*
   Element change
*/

/**
   Trie_put

   Put the value into the Trie_t instance. Replace any existing item
   that has the same key.

   @param  current Trie_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define Trie_put( arg ) PRIMITIVE_CAT( arg, _trie_put )
void Trie_put( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length );

/**
   Trie_put_and_dispose

   Put the value into the Trie_t instance. Replace any existing item
   that has the same key and dispose the old value.

   @param  current Trie_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define Trie_put_and_dispose( arg ) PRIMITIVE_CAT( arg, _trie_put_and_dispose )
void Trie_put_and_dispose( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length );

/**
   Trie_replace

   Replace the value in the Trie_t instance that has the same key.

   @param  current Trie_t instance
   @param  value the value to replace with
   @param  key the key for the value
*/
#define Trie_replace( arg ) PRIMITIVE_CAT( arg, _trie_replace )
void Trie_replace( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length );

/**
   Trie_replace_and_dispose

   Replace the value in the Trie_t instance that has the same key. Dispose of
   the original value. Leave the key unchanged.

   @param  current Trie_t instance
   @param  value the value to replace with
   @param  key the key for the value
*/
#define Trie_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _trie_replace_and_dispose )
void Trie_replace_and_dispose( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length );


/*
   Removal
*/

/**
   Trie_remove

   Remove the item in the Trie_t instance that has the key.

   @param  current Trie_t instance
   @param  key the key for the value
*/
#define Trie_remove( arg ) PRIMITIVE_CAT( arg, _trie_remove )
void Trie_remove( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length );

/**
   Trie_remove_and_dispose

   Remove the item in the Trie_t instance that has the key and dispose
   of the key and the value.

   @param  current Trie_t instance
   @param  key the key for the value
*/
#define Trie_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _trie_remove_and_dispose )
void Trie_remove_and_dispose( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length );

/**
   Trie_wipe_out

   Remove all items in the Trie_t instance.

   @param  current Trie_t instance
*/
#define Trie_wipe_out( arg ) PRIMITIVE_CAT( arg, _trie_wipe_out )
void Trie_wipe_out( Prefix )( Trie_type( Prefix ) *current );

/**
   Trie_wipe_out_and_dispose

   Remove all items in the Trie_t instance. Dispose of all keys and values.

   @param  current Trie_t instance
*/
#define Trie_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _trie_wipe_out_and_dispose )
void Trie_wipe_out_and_dispose( Prefix )( Trie_type( Prefix ) *current );

#ifdef __cplusplus
}
#endif

/* End of file */




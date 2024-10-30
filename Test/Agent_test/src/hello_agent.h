/**
 @file Agent.h
 @author Greg Lee
 @version 0.0

 description: "Generalized action to be executed (closure, continuation)"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Functions to support a generalized action to be executed 

*/

#include "base.h"

#ifndef HELLO_AGENT_H
#define HELLO_AGENT_H

/**
   Includes
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <base.h>
#include "Agent.h"

/**
   Defines
*/

/**
   Structure declaration
*/

struct hello_agent_struct;

/**
   Structure typedef
*/

typedef struct hello_agent_struct hello_agent_t;

/**
   hello_agent_make

   Makes a hello_agent

   @param i the integer argument for do_hello
*/
agent_t *
hello_agent_make( int32_t i );

/**
   hello_agent_execute

   Execute a hello_agent

   @param current this hello agent
*/
void
hello_agent_execute( agent_t *agent );

/**
   hello_agent_dispose

   Closes and disposes of hello_agent

   @param current the hello_agent to dispose of
*/

void
hello_agent_dispose( agent_t **agent );

#ifdef __cplusplus
}
#endif

#endif /* HELLO_AGENT_H */

/* End of file */


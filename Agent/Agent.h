/**
 @file Agent.h
 @author Greg Lee
 @version 2.0.0

 description: "Generalized action to be executed (closure, continuation)"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Functions to support a generalized action to be executed

*/

#include "base.h"

#ifndef AGENT_H
#define AGENT_H

/**
   Version
*/

#define AGENT_VERSION_MAJOR 2
#define AGENT_VERSION_MINOR 0
#define AGENT_VERSION_PATCH 0

#define AGENT_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define AGENT_VERSION \
   AGENT_MAKE_VERSION( AGENT_VERSION_MAJOR, \
                       AGENT_VERSION_MINOR, \
                       AGENT_VERSION_PATCH )

/**
   Includes
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <base.h>

/**
   Defines
*/

/**
   Structure declaration
*/

struct agent_struct;

/**
   Structure typedef
*/

typedef struct agent_struct agent_t;

/**
   agent_execute

   Execute an agent

   @param agent the agent to execute
*/
void
agent_execute( agent_t *agent );

/**
   agent_dispose

   Closes and disposes of agent

   @param current the agent to dispose of
*/

void
agent_dispose( agent_t **current );

#ifdef __cplusplus
}
#endif

#endif /* AGENT_H */

/* End of file */


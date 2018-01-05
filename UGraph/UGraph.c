/**
 @file UGraph.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Undirected Graphs with nodes and edges"
 
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

 Function definitions for the opaque UGraph_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"
#include "UGraph.h"

/**
   defines
*/

#define UGRAPH_TYPE 0xA5000610
#define UGRAPH_EDGE_TYPE 0xA5006011
#define UGRAPH_VERTEX_TYPE 0xA5000612

#define UGraph_has_internal( arg ) PRIMITIVE_CAT( arg, _ugraph_has_internal )
int32_t
UGraph_has_internal( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *vertex 
);

#define UGraph_edge_v1_v2_internal( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_v1_v2_internal )
UGraph_edge_type( Prefix ) *UGraph_edge_v1_v2_internal( Prefix )
( 
   UGraph_type( Prefix ) *ugraph,
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
);

/**
   Node structure definition. Holds a value and references to its neighbor vertices
   and the edges that connect them.
*/

struct UGraph_vertex_struct( Prefix )
{
   int32_t type;
   int32_t value_type;
   
   int32_t hash_code;
   UGraph_type( Prefix ) *ugraph;
   Value value;
   HSet_type( Vertex_prefix ) *neighbors;
};

/**
   Edge structure definition. Holds a value and references to its start and 
   ending vertices. Represents a one way or directed edge. v1 <= v2.
*/

struct UGraph_edge_struct( Prefix )
{
   int32_t type;
   int32_t edge_type;
   
   int32_t hash_code;
   Edge value;
   UGraph_vertex_type( Prefix ) *v1;
   UGraph_vertex_type( Prefix ) *v2;
};

/**
   Directed graph structure definition.
*/

struct UGraph_struct( Prefix )
{
   int32_t type;
   int32_t edge_type;
   int32_t value_type;
   
   HSet_type( Vertex_prefix ) *vertices;
   HSet_type( Edge_prefix ) *edges;
   UGraph_cursor_type( Prefix ) *first_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to ugraph, current vertex, vertex
   stack, and a pointer to the next cursor.
*/

struct UGraph_cursor_struct( Prefix )
{
   UGraph_type( Prefix ) *ugraph; // the ugraph we're working with
   
   HSet_cursor_type( Vertex_prefix ) *cursor; // vertex cursor
   HSet_cursor_type( Edge_prefix ) *edge_cursor; // edge cursor
   
   int32_t is_depth_first; // search type flag
   HSet_type( Vertex_prefix ) *is_visited; // set of visited vertices for search
   
   UGraph_cursor_type( Prefix ) *next_cursor; // pointer to next cursor

   // if we're in a multithreaded environment, define mutex and cv for each instance
   MULTITHREAD_MUTEX_DEFINITION( mutex );

};

/**
   structure address to hash code
*/

#define HASH_PRIME_NUMBER 8388593U // largest prime number less than 2^24

#define UGraph_address_to_hash( arg ) PRIMITIVE_CAT( arg, _ugraph_address_to_hash )

int32_t
UGraph_address_to_hash( Prefix )( UGraph_vertex_type( Prefix ) *vertex )
{
   int32_t result = 0;
   
   void *p = vertex;
   
   // get pointer as 64 bit unsigned integer
   uint64_t u64 =  ( uint64_t ) p;
      
   // if pointer has last hex digit as all zeros, shift down 4 bits to eliminate zeros
   if ( ( u64 & 0xF ) == 0 )
   {
      u64 = u64 >> 4;
   }
   
   // make sure 64 bit unsigned integer fits into 32 bit signed integer
   u64 = ( u64 % HASH_PRIME_NUMBER );
   
   // return the 32 bit signed integer as the hash code of the pointer
   result = ( int32_t ) u64;   
   
   return result;
}

#define PRIME_1 23
#define PRIME_2 31

#define UGraph_edge_address_to_hash( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_address_to_hash )

int32_t
UGraph_edge_address_to_hash( Prefix )( UGraph_edge_type( Prefix ) *edge )
{
   int32_t result = 0;
   
   void *p1 = (*edge).v1;
   void *p2 = (*edge).v2;
   
   uint64_t hash = PRIME_1;
   
   // get pointer as 64 bit unsigned integer
   uint64_t u64 = ( uint64_t ) p1;
   
   // if pointer has last hex digit as all zeros, shift down 4 bits to eliminate zeros
   if ( ( u64 & 0xF ) == 0 )
   {
      u64 = u64 >> 4;
   }
   
   // get remainder of pointer with large prime 
   u64 = u64 % HASH_PRIME_NUMBER;   
   
   // update computed hash code 
   hash = hash*PRIME_2 + u64;
   hash = hash % HASH_PRIME_NUMBER;
   
   // get pointer as 64 bit unsigned integer
   u64 = ( uint64_t ) p2;
   
   // if pointer has last hex digit as all zeros, shift down 4 bits to eliminate zeros
   if ( ( u64 & 0xF ) == 0 )
   {
      u64 = u64 >> 4;
   }
   
   // get remainder of pointer with large prime 
   u64 = u64 % HASH_PRIME_NUMBER;   
   
   // update computed hash code 
   hash = hash*PRIME_2 + u64;
   
   // make sure 64 bit unsigned integer fits into 32 bit signed integer
   hash = hash % HASH_PRIME_NUMBER;
   
   // return the 32 bit signed integer as the hash code of the pointer
   result = ( int32_t ) hash;   
   
   return result;
}

#define UGraph_dispose_of_vertex( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose_of_vertex )

void
UGraph_dispose_of_vertex( Prefix )( UGraph_vertex_type( Prefix ) *vertex )
{
   UGraph_vertex_type( Prefix ) *v1 = NULL;
   UGraph_edge_type( Prefix ) *e = NULL;
   
   UGraph_type( Prefix ) *ugraph = (*vertex).ugraph;
   
   if ( 
         ( ugraph != NULL ) 
         && 
         ( (*ugraph).edges != NULL ) 
         && 
         ( (*vertex).neighbors != NULL ) 
      )
   {
      // dispose of edges
      for
      ( 
         HSet_start( Vertex_prefix )( (*vertex).neighbors );
         HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0;
         HSet_forth( Vertex_prefix )( (*vertex).neighbors )
      )
      {   
         v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
         e = UGraph_edge_v1_v2_internal( Prefix )( ugraph, vertex, v1 );
         if ( e != NULL )
         {
            EDGE_DISPOSE_FUNCTION( (*e).value );
            HSet_remove( Edge_prefix )( (*ugraph).edges, e );
            free( e );
         }
      }
      
      // dispose of neighbor vertex hash sets but not their contents
      HSet_dispose( Vertex_prefix )( (*vertex).neighbors );
      (*vertex).neighbors = NULL;

   }
   else if ( (*vertex).neighbors != NULL ) 
   {
      // dispose of neighbor vertex hash sets but not their contents
      HSet_dispose( Vertex_prefix )( (*vertex).neighbors );
      (*vertex).neighbors = NULL;
   }

   free( vertex );
   
   return;
}

/**
   UGraph_vertex_make
*/

UGraph_vertex_type( Prefix ) *
UGraph_vertex_make( Prefix )( Value value )
{
   // allocate vertex
   UGraph_vertex_type( Prefix ) *vertex 
   =  ( UGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( UGraph_vertex_type( Prefix ) ) );
   
   // set type codes
   (*vertex).type = UGRAPH_VERTEX_TYPE;
   (*vertex).value_type = Value_Code;
   
   // set hash code
   (*vertex).hash_code = UGraph_address_to_hash( Prefix )( ( void * ) vertex );
   
   // set value
   (*vertex).value = value;
   
   // initialize vertex hash sets
   (*vertex).neighbors = HSet_make( Vertex_prefix )();
   
   POSTCONDITION( "vertex not null", vertex != NULL );
   
   return vertex;
}

/**
   edge_make
*/

static
UGraph_edge_type( Prefix ) *
edge_make( UGraph_vertex_type( Prefix ) *v1, UGraph_vertex_type( Prefix ) *v2, Edge value )
{
   PRECONDITION( "v1 vertex not null", v1 != NULL );
   PRECONDITION( "v2 vertex not null", v2 != NULL );
   
   // allocate edge
   UGraph_edge_type( Prefix ) *edge = ( UGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( UGraph_edge_type( Prefix ) ) );
   
   // set type codes
   (*edge).type = UGRAPH_EDGE_TYPE;
   (*edge).edge_type = Edge_Code;
   
   // set value
   (*edge).value = value;
      
   // set v1 and v2 vertex so that v1 < v2
   if ( v1 < v2 )
   {
      (*edge).v1 = v1;
      (*edge).v2 = v2;
   }
   else
   {
      (*edge).v1 = v2;
      (*edge).v2 = v1;
   }
   
   // set hash code
   (*edge).hash_code = UGraph_edge_address_to_hash( Prefix )( edge );
   
   POSTCONDITION( "edge not null", edge != NULL );
   
   return edge;
}

/**
   UGraph_dispose_of_edge
*/

#define UGraph_dispose_of_edge( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose_of_edge )

void
UGraph_dispose_of_edge( Prefix )( UGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   
   // do not dispose of value
   
   // do not dispose of start and end vertex

   // dispose of edge   
   free( edge );
   
   return;
}

/**
   edge_dispose
*/

static
void
edge_dispose( UGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   
   // do not dispose of value
   
   // do not dispose of start and end vertex

   // dispose of edge   
   free( edge );
   
   return;
}

/**
   edge_dispose_with_contents
*/

static
void
edge_dispose_with_contents( UGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   
   // dispose of value
   EDGE_DISPOSE_FUNCTION( (*edge).value );
   
   // do not dispose of start and end vertex

   // dispose of edge   
   free( edge );
   
   return;
}

/**
   UGraph_edge_equal
*/

#define UGraph_edge_equal( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_equal )

int32_t
UGraph_edge_equal( Prefix )( UGraph_edge_type( Prefix ) *edge1, UGraph_edge_type( Prefix ) *edge2 )
{
   PRECONDITION( "edge1 not null", edge1 != NULL );
   PRECONDITION( "edge1 type ok", ( (*edge1).type == UGRAPH_EDGE_TYPE ) && ( (*edge1).edge_type == Edge_Code ) );
   PRECONDITION( "edge2 not null", edge2 != NULL );
   PRECONDITION( "edge2 type ok", ( (*edge2).type == UGRAPH_EDGE_TYPE ) && ( (*edge2).edge_type == Edge_Code ) );
   
   int32_t result = 1;
   
   // check from
   if ( (*edge1).v1 != (*edge2).v1 )
   {
      result = 0;
   }
   
   // check to
   if ( (*edge1).v2 != (*edge2).v2 )
   {
      result = 0;
   }
   
   return result;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
edge_from_and_to_vertices_exist( UGraph_type( Prefix ) *ugraph )
{
   int32_t result = 1;
   UGraph_edge_type( Prefix ) *edge = NULL;
   UGraph_vertex_type( Prefix ) *v1;   
   UGraph_vertex_type( Prefix ) *v2;   
   HSet_cursor_type( Edge_prefix ) *cursor;
   
   cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );
   
   HSet_cursor_start( Edge_prefix )( cursor );
   while( ( HSet_cursor_off( Edge_prefix )( cursor ) == 0 ) && ( result == 1 ) )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( cursor );
      v1 = (*edge).v1;
      v2 = (*edge).v2;
      
      result = UGraph_has_internal( Prefix )( ugraph, v1 );
      if ( result == 1 )
      {
         result = UGraph_has_internal( Prefix )( ugraph, v2 );
      }
      HSet_cursor_forth( Edge_prefix )( cursor );
   }

   HSet_cursor_dispose( Edge_prefix )( cursor );
   
   return result;
}

static
int32_t
cursors_ok( UGraph_type( Prefix ) *ugraph )
{
   int32_t result = 1;

   UGraph_cursor_type( Prefix ) *cursor = (*ugraph).first_cursor;

   while ( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).ugraph == ugraph );
      cursor = (*cursor).next_cursor;
   }

   return result;
}


static
void invariant( UGraph_type( Prefix ) *ugraph )
{
   assert(((void) "edge from and to vertices exist", edge_from_and_to_vertices_exist( ugraph ) ));
   assert(((void) "cursors OK", cursors_ok( ugraph ) ));
   return;
}

#endif

/**
   UGraph_vertex_dispose
*/

void
UGraph_vertex_dispose( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   
   UGraph_vertex_type( Prefix ) *v1 = NULL;
   UGraph_edge_type( Prefix ) *e = NULL;
   
   if ( (*vertex).ugraph != NULL )
   {
    
      if ( HSet_has( Vertex_prefix )( (*ugraph).vertices, vertex ) == 1 )
      {
         // dispose of edges to vertex
         for
         ( 
            HSet_start( Vertex_prefix )( (*vertex).neighbors );
            HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0;
            HSet_forth( Vertex_prefix )( (*vertex).neighbors )
         )
         {   
            v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
            e = UGraph_edge_v1_v2_internal( Prefix )( ugraph, vertex, v1 );
            if ( e != NULL )
            {
               EDGE_DISPOSE_FUNCTION( (*e).value );
               HSet_remove( Edge_prefix )( (*ugraph).edges, e );
               free( e );
            }
         }
         
         // remove vertex from graph
         HSet_remove( Vertex_prefix )( (*ugraph).vertices, vertex );
         
      }
   }
   
   // do not dispose of value
   
   // dispose of neighbor vertex hash sets but not their contents
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors );

   (*vertex).hash_code = 0;
   (*vertex).ugraph = NULL;
   (*vertex).neighbors = NULL;
   
   // dispose of vertex   
   free( vertex );
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_vertex_dispose_with_contents
*/

void
UGraph_vertex_dispose_with_contents( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   
   UGraph_vertex_type( Prefix ) *v1 = NULL;
   UGraph_edge_type( Prefix ) *e = NULL;
   
   if ( (*vertex).ugraph != NULL )
   {
            
      if ( HSet_has( Vertex_prefix )( (*ugraph).vertices, vertex ) == 1 )
      {
         // dispose of edges to vertex
         for
         ( 
            HSet_start( Vertex_prefix )( (*vertex).neighbors );
            HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0;
            HSet_forth( Vertex_prefix )( (*vertex).neighbors )
         )
         {   
            v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
            e = UGraph_edge_v1_v2_internal( Prefix )( ugraph, vertex, v1 );
            if ( e != NULL )
            {
               EDGE_DISPOSE_FUNCTION( (*e).value );
               HSet_remove( Edge_prefix )( (*ugraph).edges, e );
               free( e );
            }
         }
         
         // remove vertex from graph
         HSet_remove( Vertex_prefix )( (*ugraph).vertices, vertex );
      }
   }
   
   // dispose of neighbor vertex hash sets but not their contents
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors );

   (*vertex).hash_code = 0;
   (*vertex).ugraph = NULL;
   (*vertex).neighbors = NULL;
   
   // dispose of value
   DISPOSE_FUNCTION( (*vertex).value );
   
   // dispose of vertex   
   free( vertex );
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}


/**
   UGraph_make_depth
*/

UGraph_type( Prefix ) *
UGraph_make_depth( Prefix )( void )
{
   // allocate ugraph struct
   UGraph_type( Prefix ) * ugraph
      = ( UGraph_type( Prefix ) * ) calloc( 1, sizeof( UGraph_type( Prefix ) ) );

   // set type codes
   (*ugraph).type = UGRAPH_TYPE;
   (*ugraph).edge_type = Edge_Code;
   (*ugraph).value_type = Value_Code;
   
   // init hash set of vertices 
   (*ugraph).vertices = HSet_make( Vertex_prefix )();

   // init hash set of edges 
   (*ugraph).edges = HSet_make( Edge_prefix )();

   // allocate cursor struct
   UGraph_cursor_type( Prefix ) *cursor
      =  ( UGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( UGraph_cursor_type( Prefix ) ) );

   // set ugraph in cursor
   (*cursor).ugraph = ugraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*ugraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );

   // set cursor to depth first
   (*cursor).is_depth_first = 1;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // set ugraph first cursor
   (*ugraph).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*ugraph).mutex );

   INVARIANT( ugraph );

   return ugraph;
}

/**
   UGraph_make_breadth
*/

UGraph_type( Prefix ) *
UGraph_make_breadth( Prefix )( void )
{
   // allocate ugraph struct
   UGraph_type( Prefix ) * ugraph
      = ( UGraph_type( Prefix ) * ) calloc( 1, sizeof( UGraph_type( Prefix ) ) );

   // set type codes
   (*ugraph).type = UGRAPH_TYPE;
   (*ugraph).edge_type = Edge_Code;
   (*ugraph).value_type = Value_Code;
   
   // init hash set of vertices 
   (*ugraph).vertices = HSet_make( Vertex_prefix )();

   // init hash set of edges 
   (*ugraph).edges = HSet_make( Edge_prefix )();

   // allocate cursor struct
   UGraph_cursor_type( Prefix ) *cursor
      =  ( UGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( UGraph_cursor_type( Prefix ) ) );

   // set ugraph in cursor
   (*cursor).ugraph = ugraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*ugraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );

   // set cursor to breadth first
   (*cursor).is_depth_first = 0;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // set ugraph first cursor
   (*ugraph).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*ugraph).mutex );

   INVARIANT( ugraph );

   return ugraph;
}

/**
   UGraph_cursor_make_depth
*/

UGraph_cursor_type( Prefix ) *
UGraph_cursor_make_depth( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *c = NULL;
   
   // allocate cursor struct
   UGraph_cursor_type( Prefix ) *cursor
      =  ( UGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( UGraph_cursor_type( Prefix ) ) );

   // set ugraph in cursor
   (*cursor).ugraph = ugraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*ugraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );

   // set cursor to depth first
   (*cursor).is_depth_first = 1;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // get last cursor reference in ugraph structure
   c = (*ugraph).first_cursor;
   while ( (*c).next_cursor != NULL )
   {
      c = (*c).next_cursor;
   }

   // add new cursor to end of cursor "list"
   (*c).next_cursor = cursor;
   
   MULTITHREAD_MUTEX_INIT( (*ugraph).mutex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return cursor;
}

/**
   UGraph_cursor_make_breadth
*/

UGraph_cursor_type( Prefix ) *
UGraph_cursor_make_breadth( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *c = NULL;
   
   // allocate cursor struct
   UGraph_cursor_type( Prefix ) *cursor
      =  ( UGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( UGraph_cursor_type( Prefix ) ) );

   // set ugraph in cursor
   (*cursor).ugraph = ugraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*ugraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );

   // set cursor to breadth first
   (*cursor).is_depth_first = 0;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // get last cursor reference in ugraph structure
   c = (*ugraph).first_cursor;
   while ( (*c).next_cursor != NULL )
   {
      c = (*c).next_cursor;
   }

   // add new cursor to end of cursor "list"
   (*c).next_cursor = cursor;
   
   MULTITHREAD_MUTEX_INIT( (*ugraph).mutex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return cursor;
}

/**
   UGraph_dispose
*/

void
UGraph_dispose( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *cursor = NULL;
   UGraph_cursor_type( Prefix ) *c = NULL;
   
   // dispose of cursors
   cursor = (*ugraph).first_cursor;
   
   // walk through cursors
   while( cursor != NULL )
   {
      // free allocated memory
      HSet_cursor_dispose( Vertex_prefix )( (*cursor).cursor );
      HSet_cursor_dispose( Edge_prefix )( (*cursor).edge_cursor );
      HSet_dispose( Vertex_prefix )( (*cursor).is_visited );
      c = cursor;
      cursor = (*cursor).next_cursor;
      // and free the cursor struct
      free( c );
   }

   // dipose of edges
   HSet_dispose_with_contents( Edge_prefix )( (*ugraph).edges );
   (*ugraph).edges = NULL;
   
   // dispose of vertices
   HSet_dispose_with_contents( Vertex_prefix )( (*ugraph).vertices );
   
   MULTITHREAD_MUTEX_DESTROY( (*ugraph).mutex );

   // delete ugraph struct
   free( ugraph );

   return;
}

/**
   UGraph_dispose_with_contents
*/

void
UGraph_dispose_with_contents( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *cursor = NULL;
   UGraph_cursor_type( Prefix ) *c = NULL;
   
   // dispose of cursors
   cursor = (*ugraph).first_cursor;
   
   // walk through cursors
   while( cursor != NULL )
   {
      // free allocated memory
      HSet_cursor_dispose( Vertex_prefix )( (*cursor).cursor );
      HSet_cursor_dispose( Edge_prefix )( (*cursor).edge_cursor );
      HSet_dispose( Vertex_prefix )( (*cursor).is_visited );
      c = cursor;
      cursor = (*cursor).next_cursor;
      // and free the cursor struct
      free( c );
   }

   // dispose of edge values
   HSet_start( Edge_prefix )( (*ugraph).edges );
   while( HSet_off( Edge_prefix )( (*ugraph).edges ) == 0 )
   {
      EDGE_DISPOSE_FUNCTION( (* HSet_item_at( Edge_prefix )( (*ugraph).edges ) ).value );
      HSet_forth( Edge_prefix )( (*ugraph).edges );
   }

   // dipose of edges
   HSet_dispose_with_contents( Edge_prefix )( (*ugraph).edges );
   (*ugraph).edges = NULL;
   
   // dispose of vertex values
   HSet_start( Vertex_prefix )( (*ugraph).vertices );
   while( HSet_off( Vertex_prefix )( (*ugraph).vertices ) == 0 )
   {
      DISPOSE_FUNCTION( (* HSet_item_at( Vertex_prefix )( (*ugraph).vertices ) ).value );
      HSet_forth( Vertex_prefix )( (*ugraph).vertices );
   }

   // dispose of vertices
   HSet_dispose_with_contents( Vertex_prefix )( (*ugraph).vertices );
   
   MULTITHREAD_MUTEX_DESTROY( (*ugraph).mutex );

   // delete ugraph struct
   free( ugraph );

   return;
}

/**
   UGraph_cursor_dispose
*/

void
UGraph_cursor_dispose( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   UGraph_type( Prefix ) *ugraph = (*cursor).ugraph;

   UGraph_cursor_type( Prefix ) *c1 = NULL;
   UGraph_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from ugraph structure
   c1 = (*(*cursor).ugraph).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
      {
         // if we have a match, remove "c2" from the cursor ugraph, set flag
         (*c1).next_cursor = (*c2).next_cursor;
         flag = 1;

         // now advance c1 and c2
         c1 = (*c1).next_cursor;
         if ( c1 != NULL )
         {
            c2 = (*c1).next_cursor;
         }
         else
         {
            c2 = NULL;
         }
      }
      else
      {
         // advance c1 and c2
         c1 = c2;
         if ( c1 != NULL )
         {
            c2 = (*c1).next_cursor;
         }
      }
   }

   // free allocated memory in cursor
   HSet_cursor_dispose( Vertex_prefix )( (*cursor).cursor );
   HSet_cursor_dispose( Edge_prefix )( (*cursor).edge_cursor );
   HSet_dispose( Vertex_prefix )( (*cursor).is_visited );
      
   // delete cursor struct
   free( cursor );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_value

*/

Value
UGraph_value( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   Value result = (*vertex).value;

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_v1_v2

*/

UGraph_edge_type( Prefix ) *
UGraph_edge_v1_v2_internal( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   UGraph_edge_type( Prefix ) *result = NULL;
   UGraph_edge_type( Prefix ) *edge = NULL;
   UGraph_edge_type( Prefix ) *edge1 = NULL;
   
   // get the edge, if it exists
   edge1 = edge_make( v1, v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = edge;
   }   
   
   return result;
}

/**
   UGraph_edge_v1_v2

*/

UGraph_edge_type( Prefix ) *
UGraph_edge_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "v1 not null", v1 != NULL );
   PRECONDITION( "v1 type ok", ( (*v1).type == UGRAPH_VERTEX_TYPE ) && ( (*v1).value_type == Value_Code ) );
   PRECONDITION( "v2 not null", v2 != NULL );
   PRECONDITION( "v2 type ok", ( (*v2).type == UGRAPH_VERTEX_TYPE ) && ( (*v2).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) *result 
      = UGraph_edge_v1_v2_internal( Prefix )( ugraph, v1, v2 );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );
   
   return result;
}

/**
   UGraph_edge_value_v1_v2

*/

Edge
UGraph_edge_value_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "v1 not null", v1 != NULL );
   PRECONDITION( "v1 type ok", ( (*v1).type == UGRAPH_VERTEX_TYPE ) && ( (*v1).value_type == Value_Code ) );
   PRECONDITION( "v2 not null", v2 != NULL );
   PRECONDITION( "v2 type ok", ( (*v2).type == UGRAPH_VERTEX_TYPE ) && ( (*v2).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   Edge result = (* UGraph_edge_v1_v2_internal( Prefix )( ugraph, v1, v2 ) ).value;

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );
   
   return result;
}

/**
   UGraph_edge_value

*/

Edge
UGraph_edge_value( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_edge_type( Prefix ) *edge 
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   Edge result = (*edge).value;
   
   // get the edge, if it exists
   UGraph_edge_type( Prefix ) *edge1 = edge_make( (*edge).v1, (*edge).v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = (*edge).value;
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_v1

*/

UGraph_vertex_type( Prefix ) *
UGraph_edge_v1( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_edge_type( Prefix ) *edge 
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *result = NULL;
   
   // get the edge, if it exists
   UGraph_edge_type( Prefix ) *edge1 = edge_make( (*edge).v1, (*edge).v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = (*edge).v1;
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_v2

*/

UGraph_vertex_type( Prefix ) *
UGraph_edge_v2( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_edge_type( Prefix ) *edge 
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *result = NULL;
   
   // get the edge, if it exists
   UGraph_edge_type( Prefix ) *edge1 = edge_make( (*edge).v1, (*edge).v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = (*edge).v2;
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_at
*/

UGraph_vertex_type( Prefix ) *
UGraph_at( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *result = HSet_item_at( Vertex_prefix )( (*ugraph).vertices );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_at
*/

UGraph_vertex_type( Prefix ) *
UGraph_cursor_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );
   PRECONDITION( "cursor not off", HSet_cursor_off( Vertex_prefix )( (*cursor).cursor ) == 0 );

   UGraph_vertex_type( Prefix ) *result = HSet_cursor_item_at( Vertex_prefix )( (*cursor).cursor );

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   UGraph_cursor_value_at
*/

Value
UGraph_cursor_value_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );
   PRECONDITION( "cursor not off", HSet_cursor_off( Vertex_prefix )( (*cursor).cursor ) == 0 );

   Value result = (* HSet_cursor_item_at( Vertex_prefix )( (*cursor).cursor ) ).value;

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}


/**
   UGraph_value_at
*/

Value
UGraph_value_at( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   PRECONDITION( "not off", HSet_off( Vertex_prefix )( (*ugraph).vertices  ) == 0 );

   Value result = (* HSet_item_at( Vertex_prefix )( (*ugraph).vertices ) ).value;

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_edge_at
*/

UGraph_edge_type( Prefix ) *
UGraph_cursor_edge_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );
   PRECONDITION( "edge_cursor not off", HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor ) == 0 );

   UGraph_edge_type( Prefix ) *result = HSet_cursor_item_at( Edge_prefix )( (*cursor).edge_cursor );

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}


/**
   UGraph_edge_at
*/

UGraph_edge_type( Prefix ) *
UGraph_edge_at( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   PRECONDITION( "not off", HSet_off( Edge_prefix )( (*ugraph).edges ) == 0 );

   UGraph_edge_type( Prefix ) *result = HSet_item_at( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_edge_value_at
*/

Edge
UGraph_cursor_edge_value_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );
   PRECONDITION( "cursor not off", HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor ) == 0 );

   Edge result = (* HSet_cursor_item_at( Edge_prefix )( (*cursor).edge_cursor ) ).value;

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}


/**
   UGraph_edge_value_at
*/

Edge
UGraph_edge_value_at( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   PRECONDITION( "not off", HSet_off( Edge_prefix )( (*ugraph).edges ) == 0 );

   Edge result = (* HSet_item_at( Edge_prefix )( (*ugraph).edges ) ).value;

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_as_array
*/

UGraph_vertex_type( Prefix ) **
UGraph_as_array( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) **result = NULL;
   UGraph_vertex_type( Prefix ) *vertex = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Vertex_prefix )( (*ugraph).vertices );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( UGraph_vertex_type( Prefix ) ** ) calloc( n + 1, sizeof( UGraph_vertex_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_start( Vertex_prefix )( (*ugraph).vertices );
   i = 0;
   while ( HSet_off( Vertex_prefix )( (*ugraph).vertices ) == 0 )
   {
      vertex = HSet_item_at( Vertex_prefix )( (*ugraph).vertices );
      result[i] = vertex;
      i++;
      HSet_forth( Vertex_prefix )( (*ugraph).vertices );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edges_as_array
*/

UGraph_edge_type( Prefix ) **
UGraph_edges_as_array( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) **result = NULL;
   UGraph_edge_type( Prefix ) *edge = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Edge_prefix )( (*ugraph).edges );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( UGraph_edge_type( Prefix ) ** ) calloc( n + 1, sizeof( UGraph_edge_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_cursor_start( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   i = 0;
   while ( HSet_cursor_off( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
      result[i] = edge;
      i++;
      HSet_cursor_forth( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_count
*/

int32_t
UGraph_count( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t count = HSet_count( Vertex_prefix )( (*ugraph).vertices );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return count;
}

/**
   UGraph_edge_count
*/

int32_t
UGraph_edge_count( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t count = HSet_count( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return count;
}

/**
   UGraph_are_adjacent
*/

int32_t
UGraph_are_adjacent( Prefix )
( 
   UGraph_type( Prefix ) *ugraph,
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "v1 not null", v1 != NULL );
   PRECONDITION( "v1 type ok", ( (*v1).type == UGRAPH_VERTEX_TYPE ) && ( (*v1).value_type == Value_Code ) );
   PRECONDITION( "v2 not null", v2 != NULL );
   PRECONDITION( "v2 type ok", ( (*v2).type == UGRAPH_VERTEX_TYPE ) && ( (*v2).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = 0;
   UGraph_edge_type( Prefix ) *edge = NULL;
   
   // get the edge, if it exists
   UGraph_edge_type( Prefix ) *edge1 = edge_make( v1, v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = 1;
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_off
*/

int32_t
UGraph_off( Prefix)( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = HSet_off( Vertex_prefix )( (*ugraph).vertices );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_off
*/

int32_t
UGraph_cursor_off( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = HSet_cursor_off( Vertex_prefix )( (*cursor).cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   UGraph_is_empty
*/

int32_t
UGraph_is_empty( Prefix)( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = HSet_is_empty( Vertex_prefix )( (*ugraph).vertices );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_off
*/

int32_t
UGraph_edge_off( Prefix)( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = HSet_off( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_edge_off
*/

int32_t
UGraph_cursor_edge_off( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   UGraph_edge_is_empty
*/

int32_t
UGraph_edge_is_empty( Prefix)( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = HSet_is_empty( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   ugraph_depth_is_connected
   
   use hash set to accumulate visited vertices
*/

static
void
ugraph_depth_is_connected( UGraph_cursor_type( Prefix ) *cursor, UGraph_vertex_type( Prefix ) *vertex )
{
   UGraph_vertex_type( Prefix ) *v = NULL;
   
   if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, vertex ) == 0 )
   {
      
      // put vertex into visited set
      HSet_put( Vertex_prefix )( (*cursor).is_visited, vertex );
            
      // put connected vertices into is_visited hash set
      HSet_start( Vertex_prefix )( (*vertex).neighbors );
      while( HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0 )
      {
         v = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
         if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, v ) == 0 )
         {
            ugraph_depth_is_connected( cursor, v );
         }
         HSet_forth( Vertex_prefix )( (*vertex).neighbors );
      }
            
   }

   return;
}

/**
   ugraph_breadth_is_connected
   
   use hash set to accumulate visited vertices
*/

static
void
ugraph_breadth_is_connected
( 
   UGraph_cursor_type( Prefix ) *cursor, 
   UGraph_vertex_type( Prefix ) *vertex,
   HSet_type( Vertex_prefix ) *queue
)
{
   UGraph_vertex_type( Prefix ) *v = NULL;
   UGraph_vertex_type( Prefix ) *v1 = NULL;
   
   // put vertex into visited set
   HSet_put( Vertex_prefix )( (*cursor).is_visited, vertex );
         
   // put vertex into queue
   HSet_put( Vertex_prefix )( queue, vertex );
   
   // work on contents of the queue
   while( HSet_is_empty( Vertex_prefix )( queue ) == 0 )
   {
      // get first vertex in queue
      HSet_start( Vertex_prefix )(  queue );
      v = HSet_item_at( Vertex_prefix )( queue );
      HSet_remove( Vertex_prefix )( queue, v );
      
      // put adjacent vertices into is_visited hash set
      HSet_start( Vertex_prefix )( (*v).neighbors );
      while( HSet_off( Vertex_prefix )( (*v).neighbors ) == 0 )
      {
         v1 = HSet_item_at( Vertex_prefix )( (*v).neighbors );
         if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, v1 ) == 0 )
         {
            HSet_put( Vertex_prefix )( (*cursor).is_visited, v1 );
            HSet_put( Vertex_prefix )( queue, v1 );
         }
         HSet_forth( Vertex_prefix )( (*v).neighbors );
      }
      
   }
   
   return;
}

/**
   UGraph_is_connected
*/

int32_t
UGraph_is_connected( Prefix)( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = 0;
   UGraph_vertex_type( Prefix ) *vertex = NULL;
   UGraph_cursor_type( Prefix ) *cursor = (*ugraph).first_cursor;
   
   if ( HSet_count( Vertex_prefix )( (*ugraph).vertices ) <= 1 )
   {
      // zero or one vertex graphs are connected
      result = 1;
   }
   else if ( (*cursor).is_depth_first == 1 ) 
   {
      // get first vertex
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      HSet_start( Vertex_prefix )( (*ugraph).vertices );
      vertex = HSet_item_at( Vertex_prefix )( (*ugraph).vertices );
      
      // fill is_visited hash set with connected vertices
      ugraph_depth_is_connected( cursor, vertex );
      
      // graph is connected if all vertices have been visited, which means
      // that the count of is_visited is the same as the count of vertices
      if ( 
            HSet_count( Vertex_prefix )( (*cursor).is_visited ) 
               == HSet_count( Vertex_prefix )( (*ugraph).vertices )
         )
      {
         result = 1;
      }
   }
   else // breadth first 
   {
      // get first vertex
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      HSet_start( Vertex_prefix )( (*ugraph).vertices );
      vertex = HSet_item_at( Vertex_prefix )( (*ugraph).vertices );
      
      HSet_type( Vertex_prefix ) *queue 
         = HSet_make( Vertex_prefix )(); // queue of visited vertices for search
      
      // fill is_visited hash set with connected vertices
      ugraph_breadth_is_connected( cursor, vertex, queue );
      
      // graph is connected if all vertices have been visited, which means
      // that the count of is_visited is the same as the count of vertices
      if ( 
            HSet_count( Vertex_prefix )( (*cursor).is_visited ) 
               == HSet_count( Vertex_prefix )( (*ugraph).vertices )
         )
      {
         result = 1;
      }
      
      HSet_dispose( Vertex_prefix )( queue );
      
   }
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_has_internal
*/

int32_t
UGraph_has_internal( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   
   int32_t result = HSet_has( Vertex_prefix )( (*ugraph).vertices, vertex );
   return result;
}


int32_t
UGraph_has( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = UGraph_has_internal( Prefix )( ugraph, vertex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_has
*/

int32_t
UGraph_edge_has( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = HSet_has( Edge_prefix )( (*ugraph).edges, edge );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_has_value
*/

int32_t
UGraph_has_value( Prefix )( UGraph_type( Prefix ) *ugraph, Value value )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = 0;
   Value v;
   
   HSet_start( Vertex_prefix )( (*ugraph).vertices );
   while( HSet_off( Vertex_prefix )( (*ugraph).vertices ) == 0 )
   {
      v = (* HSet_item_at( Vertex_prefix )( (*ugraph).vertices ) ).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = 1;
         break;
      }
      HSet_forth( Vertex_prefix )( (*ugraph).vertices );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_has_value
*/

int32_t
UGraph_edge_has_value( Prefix )( UGraph_type( Prefix ) *ugraph, Edge value )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   int32_t result = 0;
   Edge v;
   
   HSet_cursor_start( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor ) == 0 )
   {
      v = (* HSet_cursor_item_at( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor ) ).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = 1;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_neighbors
*/
UGraph_vertex_type( Prefix ) **
UGraph_neighbors( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) **result = NULL;
   UGraph_vertex_type( Prefix ) *v = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Vertex_prefix )( (*vertex).neighbors );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( UGraph_vertex_type( Prefix ) ** ) calloc( n + 1, sizeof( UGraph_vertex_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_start( Vertex_prefix )( (*vertex).neighbors );
   i = 0;
   while ( HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0 )
   {
      v = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
      result[i] = v;
      i++;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_forth
*/
void
UGraph_cursor_forth( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   HSet_cursor_forth( Vertex_prefix )( (*cursor).cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   UGraph_cursor_start
*/

void
UGraph_cursor_start( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   HSet_cursor_start( Vertex_prefix )( (*cursor).cursor );

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   UGraph_forth
*/
void
UGraph_forth( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   PRECONDITION( "not off", HSet_off( Vertex_prefix )( (*ugraph).vertices ) == 0 );

   HSet_forth( Vertex_prefix )( (*ugraph).vertices );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_start
*/

void
UGraph_start( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   HSet_start( Vertex_prefix )( (*ugraph).vertices );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_find_value
*/

UGraph_vertex_type( Prefix ) *
UGraph_find_value( Prefix )( UGraph_type( Prefix ) *ugraph, Value value )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *result = NULL;
   UGraph_vertex_type( Prefix ) *vertex = NULL;
   Value v;
   
   HSet_cursor_start( Vertex_prefix )( (*(*ugraph).first_cursor).cursor );
   while( HSet_cursor_off( Vertex_prefix )( (*(*ugraph).first_cursor).cursor ) == 0 )
   {
      vertex = HSet_cursor_item_at( Vertex_prefix )( (*(*ugraph).first_cursor).cursor );
      v = (*vertex).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = vertex;
         break;
      }
      HSet_cursor_forth( Vertex_prefix )( (*(*ugraph).first_cursor).cursor );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_find_next_value
*/

UGraph_vertex_type( Prefix ) *
UGraph_find_next_value( Prefix )( UGraph_type( Prefix ) *ugraph, Value value )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *result = NULL;
   UGraph_vertex_type( Prefix ) *vertex = NULL;
   Value v;
   
   HSet_cursor_forth( Vertex_prefix )( (*(*ugraph).first_cursor).cursor );
   while( HSet_cursor_off( Vertex_prefix )( (*(*ugraph).first_cursor).cursor ) == 0 )
   {
      vertex = HSet_cursor_item_at( Vertex_prefix )( (*(*ugraph).first_cursor).cursor );
      v = (*vertex).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = vertex;
         break;
      }
      HSet_cursor_forth( Vertex_prefix )( (*(*ugraph).first_cursor).cursor );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_find_value
*/

UGraph_vertex_type( Prefix ) *
UGraph_cursor_find_value( Prefix )( UGraph_cursor_type( Prefix ) *cursor, Value value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   UGraph_vertex_type( Prefix ) *result = NULL;
   UGraph_vertex_type( Prefix ) *vertex = NULL;
   Value v;
   
   HSet_cursor_start( Vertex_prefix )( (*cursor).cursor );
   while( HSet_cursor_off( Vertex_prefix )( (*cursor).cursor ) == 0 )
   {
      vertex = HSet_cursor_item_at( Vertex_prefix )( (*cursor).cursor );
      v = (*vertex).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = vertex;
         break;
      }
      HSet_cursor_forth( Vertex_prefix )( (*cursor).cursor );
   }

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_find_next_value
*/

UGraph_vertex_type( Prefix ) *
UGraph_cursor_find_next_value( Prefix )( UGraph_cursor_type( Prefix ) *cursor, Value value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   UGraph_vertex_type( Prefix ) *result = NULL;
   UGraph_vertex_type( Prefix ) *vertex = NULL;
   Value v;
   
   HSet_cursor_forth( Vertex_prefix )( (*cursor).cursor );
   while( HSet_cursor_off( Vertex_prefix )( (*cursor).cursor ) == 0 )
   {
      vertex = HSet_cursor_item_at( Vertex_prefix )( (*cursor).cursor );
      v = (*vertex).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = vertex;
         break;
      }
      HSet_cursor_forth( Vertex_prefix )( (*cursor).cursor );
   }

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_edge_forth
*/
void
UGraph_cursor_edge_forth( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   HSet_cursor_forth( Edge_prefix )( (*cursor).edge_cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   UGraph_cursor_edge_start
*/

void
UGraph_cursor_edge_start( Prefix )( UGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   HSet_cursor_start( Edge_prefix )( (*cursor).edge_cursor );

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   UGraph_edge_forth
*/
void
UGraph_edge_forth( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );
   PRECONDITION( "not off", HSet_off( Edge_prefix )( (*ugraph).edges ) == 0 );

   HSet_forth( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_start
*/

void
UGraph_edge_start( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   HSet_start( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_find_value
*/

UGraph_edge_type( Prefix ) *
UGraph_edge_find_value( Prefix )( UGraph_type( Prefix ) *ugraph, Edge value )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) *result = NULL;
   UGraph_edge_type( Prefix ) *edge = NULL;
   Edge v;
   
   HSet_cursor_start( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
      v = (*edge).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = edge;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_edge_find_next_value
*/

UGraph_edge_type( Prefix ) *
UGraph_edge_find_next_value( Prefix )( UGraph_type( Prefix ) *ugraph, Edge value )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) *result = NULL;
   UGraph_edge_type( Prefix ) *edge = NULL;
   Edge v;
   
   HSet_cursor_forth( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
      v = (*edge).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = edge;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*(*ugraph).first_cursor).edge_cursor );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_edge_find_value
*/

UGraph_edge_type( Prefix ) *
UGraph_cursor_edge_find_value( Prefix )( UGraph_cursor_type( Prefix ) *cursor, Edge value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   UGraph_edge_type( Prefix ) *result = NULL;
   UGraph_edge_type( Prefix ) *edge = NULL;
   Edge v;
   
   HSet_cursor_start( Edge_prefix )( (*cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*cursor).edge_cursor );
      v = (*edge).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = edge;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*cursor).edge_cursor );
   }

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );

   return result;
}

/**
   UGraph_cursor_edge_find_next_value
*/

UGraph_edge_type( Prefix ) *
UGraph_cursor_edge_find_next_value( Prefix )( UGraph_cursor_type( Prefix ) *cursor, Value value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).ugraph).type == UGRAPH_TYPE ) && ( (*(*cursor).ugraph).edge_type == Edge_Code ) && ( (*(*cursor).ugraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).ugraph).mutex );
   INVARIANT( (*cursor).ugraph );

   UGraph_edge_type( Prefix ) *result = NULL;
   UGraph_edge_type( Prefix ) *edge = NULL;
   Edge v;
   
   HSet_cursor_forth( Edge_prefix )( (*cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*cursor).edge_cursor );
      v = (*edge).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = edge;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*cursor).edge_cursor );
   }

   INVARIANT( (*cursor).ugraph );
   UNLOCK( (*(*cursor).ugraph).mutex );

   return result;
}

/**
   UGraph_vertex_set_bucket_count
*/

void
UGraph_vertex_set_bucket_count( Prefix )( UGraph_type( Prefix ) *ugraph, int32_t bucket_count )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "bucket_count positive", bucket_count > 0 );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *vertex = NULL;
   UGraph_cursor_type( Prefix ) *cursor = NULL;
   
   // set bucket count in each vertex HSet
   HSet_start( Vertex_prefix )( (*ugraph).vertices );
   while( HSet_off( Vertex_prefix )( (*ugraph).vertices ) == 0 )
   {
      vertex = HSet_item_at( Vertex_prefix )( (*ugraph).vertices );
      HSet_set_bucket_count( Vertex_prefix )( (*vertex).neighbors, bucket_count );
      HSet_forth( Vertex_prefix )( (*ugraph).vertices );
   }
   
   HSet_set_bucket_count( Vertex_prefix )( (*ugraph).vertices, bucket_count );
   
   // set bucket counts in cursors
   cursor = (*ugraph).first_cursor;
   
   while( cursor != NULL )
   {
      HSet_set_bucket_count( Vertex_prefix )( (*cursor).is_visited, bucket_count );
      cursor = (*cursor).next_cursor;
   }
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_set_bucket_count
*/

void
UGraph_edge_set_bucket_count( Prefix )( UGraph_type( Prefix ) *ugraph, int32_t bucket_count )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "bucket_count positive", bucket_count > 0 );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   // set bucket count in each edge HSet
   HSet_set_bucket_count( Edge_prefix )( (*ugraph).edges, bucket_count );
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_put
*/

void
UGraph_put( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   // set ugraph
   (*vertex).ugraph = ugraph; 
   
   HSet_put( Vertex_prefix )( (*ugraph).vertices, vertex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_put
*/

void
UGraph_edge_put( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   Edge value,
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "v1 not null", v1 != NULL );
   PRECONDITION( "v1 type ok", ( (*v1).type == UGRAPH_VERTEX_TYPE ) && ( (*v1).value_type == Value_Code ) );
   PRECONDITION( "v2 not null", v2 != NULL );
   PRECONDITION( "v2 type ok", ( (*v2).type == UGRAPH_VERTEX_TYPE ) && ( (*v2).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   // add edge
   UGraph_edge_type( Prefix ) *edge = NULL;
   
   // make edge
   edge = edge_make( v1, v2, value );
   HSet_put( Edge_prefix )( (*ugraph).edges, edge );

   // add to neighbors of v1
   HSet_put( Vertex_prefix )( (*v1).neighbors, v2 );
   
   // add to neighbors of v2
   HSet_put( Vertex_prefix )( (*v2).neighbors, v1 );
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_set_value
*/

void
UGraph_set_value( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *vertex,
   Value value
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   (*vertex).value = value;

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_set
*/

void
UGraph_edge_set( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2,
   Edge value
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) *edge = NULL;
   UGraph_edge_type( Prefix ) *e1 = NULL;
   
   edge = edge_make( v1, v2, value );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge ) == 1 )
   {
      e1 = HSet_item( Edge_prefix )( (*ugraph).edges, edge );
   }
   edge_dispose( edge );
   
   if ( e1 != NULL )
   {
      (*e1).value = value;
   }
   
   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_set_value
*/

void
UGraph_edge_set_value( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_edge_type( Prefix ) *edge,
   Edge value
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   (*edge).value = value;

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_remove
*/

void
UGraph_remove( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex  != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *v1 = NULL;
   UGraph_edge_type( Prefix ) *e = NULL;
   
   // dispose of edges
   for
   ( 
      HSet_start( Vertex_prefix )( (*vertex).neighbors );
      HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors )
   )
   {   
      v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
      e = UGraph_edge_v1_v2_internal( Prefix )( ugraph, vertex, v1 );
      if ( e != NULL )
      {
         EDGE_DISPOSE_FUNCTION( (*e).value );
         HSet_remove( Edge_prefix )( (*ugraph).edges, e );
         free( e );
      }
   }
   
   // wipe out neighbor vertex hash set but not its contents
   HSet_wipe_out( Vertex_prefix )( (*vertex).neighbors );
   
   HSet_remove( Vertex_prefix )( (*ugraph).vertices, vertex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_remove_and_dispose
*/

void
UGraph_remove_and_dispose( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex  != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == UGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_vertex_type( Prefix ) *v1 = NULL;
   UGraph_edge_type( Prefix ) *e = NULL;
   
   // dispose of edges to vertex
   for
   ( 
      HSet_start( Vertex_prefix )( (*vertex).neighbors );
      HSet_off( Vertex_prefix )( (*vertex).neighbors ) == 0;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors )
   )
   {   
      v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors );
      e = UGraph_edge_v1_v2_internal( Prefix )( ugraph, vertex, v1 );
      if ( e != NULL )
      {
         EDGE_DISPOSE_FUNCTION( (*e).value );
         HSet_remove( Edge_prefix )( (*ugraph).edges, e );
         free( e );
      }
   }
   
   // dispose of neighbor vertex hash sets but not their contents
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors );
   (*vertex).neighbors = NULL;
   
   HSet_remove_and_dispose( Vertex_prefix )( (*ugraph).vertices, vertex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}


/**
   UGraph_edge_remove
*/

void
UGraph_edge_remove( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   HSet_remove_and_dispose( Edge_prefix )( (*ugraph).edges, edge );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_remove_and_dispose
*/

void
UGraph_edge_remove_and_dispose( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge  != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == UGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   EDGE_DISPOSE_FUNCTION( (*edge).value );
   HSet_remove_and_dispose( Edge_prefix )( (*ugraph).edges, edge );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}


/**
   UGraph_edge_remove_v1_v2
*/

void
UGraph_edge_remove_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "v1 not null", v1 != NULL );
   PRECONDITION( "v1 type ok", ( (*v1).type == UGRAPH_VERTEX_TYPE ) && ( (*v1).value_type == Value_Code ) );
   PRECONDITION( "v2 not null", v2 != NULL );
   PRECONDITION( "v2 type ok", ( (*v2).type == UGRAPH_VERTEX_TYPE ) && ( (*v2).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) *edge = NULL;
   
   // get the edge, if it exists
   UGraph_edge_type( Prefix ) *edge1 = edge_make( v1, v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );

   if ( edge != NULL )
   {
      HSet_remove_and_dispose( Edge_prefix )( (*ugraph).edges, edge );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_remove_and_dispose_v1_v2
*/

void
UGraph_edge_remove_and_dispose_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
)
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   PRECONDITION( "v1 not null", v1 != NULL );
   PRECONDITION( "v1 type ok", ( (*v1).type == UGRAPH_VERTEX_TYPE ) && ( (*v1).value_type == Value_Code ) );
   PRECONDITION( "v2 not null", v2 != NULL );
   PRECONDITION( "v2 type ok", ( (*v2).type == UGRAPH_VERTEX_TYPE ) && ( (*v2).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_edge_type( Prefix ) *edge = NULL;
   
   // get the edge, if it exists
   UGraph_edge_type( Prefix ) *edge1 = edge_make( v1, v2, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*ugraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*ugraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );

   if ( edge != NULL )
   {
      EDGE_DISPOSE_FUNCTION( (*edge).value );
      HSet_remove_and_dispose( Edge_prefix )( (*ugraph).edges, edge );
   }

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}


/**
   UGraph_wipe_out
*/

void
UGraph_wipe_out( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *cursor = NULL;
   UGraph_cursor_type( Prefix ) *c = NULL;
   int32_t is_depth_first = 0;
   
   cursor = (*ugraph).first_cursor;
   is_depth_first = (*cursor).is_depth_first;
   
   while( cursor != NULL  )
   {
      HSet_cursor_dispose( Vertex_prefix )( (*cursor).cursor );
      HSet_cursor_dispose( Edge_prefix )( (*cursor).edge_cursor );
      HSet_dispose( Vertex_prefix )( (*cursor).is_visited );
      c = cursor;
      cursor = (*cursor).next_cursor;
      free( c );
   }
   
   // wipe out the hsets for vertices and edges, including all their cursors
   HSet_wipe_out_and_dispose( Vertex_prefix )( (*ugraph).vertices );
   HSet_wipe_out_and_dispose( Edge_prefix )( (*ugraph).edges );

   // (re)set internal hset cursors
   (*ugraph).first_cursor
      =  ( UGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( UGraph_cursor_type( Prefix ) ) );
   
   (*(*ugraph).first_cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*ugraph).vertices );
   (*(*ugraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );
   (*(*ugraph).first_cursor).is_visited = HSet_make( Vertex_prefix )();
   (*(*ugraph).first_cursor).next_cursor = NULL;
   (*(*ugraph).first_cursor).ugraph = ugraph;
   (*(*ugraph).first_cursor).is_depth_first = is_depth_first;
   MULTITHREAD_MUTEX_INIT( (*(*ugraph).first_cursor).mutex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_wipe_out_and_dispose
*/

void
UGraph_wipe_out_and_dispose( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *cursor = NULL;
   UGraph_cursor_type( Prefix ) *c = NULL;
   int32_t is_depth_first = 0;
   
   cursor = (*ugraph).first_cursor;
   is_depth_first = (*cursor).is_depth_first;
   
   while( cursor != NULL  )
   {
      HSet_cursor_dispose( Vertex_prefix )( (*cursor).cursor );
      HSet_cursor_dispose( Edge_prefix )( (*cursor).edge_cursor );
      HSet_dispose( Vertex_prefix )( (*cursor).is_visited );
      c = cursor;
      cursor = (*cursor).next_cursor;
      free( c );
   }
   
   // wipe out the hsets for vertices and edges, including all their cursors
   HSet_start( Edge_prefix )( (*ugraph).edges );
   while( HSet_off( Edge_prefix )( (*ugraph).edges ) == 0 )
   {
      EDGE_DISPOSE_FUNCTION( (* HSet_item_at( Edge_prefix )( (*ugraph).edges ) ).value );
      HSet_forth( Edge_prefix )( (*ugraph).edges );
   }
   HSet_wipe_out_and_dispose( Edge_prefix )( (*ugraph).edges );
   
   HSet_start( Vertex_prefix )( (*ugraph).vertices );
   while( HSet_off( Vertex_prefix )( (*ugraph).vertices ) == 0 )
   {
      DISPOSE_FUNCTION( (* HSet_item_at( Vertex_prefix )( (*ugraph).vertices ) ).value );
      HSet_forth( Vertex_prefix )( (*ugraph).vertices );
   }
   HSet_wipe_out_and_dispose( Vertex_prefix )( (*ugraph).vertices );

   // (re)set internal hset cursors
   (*ugraph).first_cursor
      =  ( UGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( UGraph_cursor_type( Prefix ) ) );
   
   (*(*ugraph).first_cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*ugraph).vertices );
   (*(*ugraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );
   (*(*ugraph).first_cursor).is_visited = HSet_make( Vertex_prefix )();
   (*(*ugraph).first_cursor).next_cursor = NULL;
   (*(*ugraph).first_cursor).ugraph = ugraph;
   (*(*ugraph).first_cursor).is_depth_first = is_depth_first;
   MULTITHREAD_MUTEX_INIT( (*(*ugraph).first_cursor).mutex );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_wipe_out
*/

void
UGraph_edge_wipe_out( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *cursor = NULL;
   
   cursor = (*ugraph).first_cursor;
   while( cursor != NULL  )
   {
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      cursor = (*cursor).next_cursor;
   }
   
   // dispose of edges
   HSet_wipe_out_and_dispose( Edge_prefix )( (*ugraph).edges );

   // get new cursor to replace cursor eliminated by previous call
   (*(*ugraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

/**
   UGraph_edge_wipe_out_and_dispose
*/

void
UGraph_edge_wipe_out_and_dispose( Prefix )( UGraph_type( Prefix ) *ugraph )
{
   PRECONDITION( "ugraph not null", ugraph != NULL );
   PRECONDITION( "ugraph type ok", ( (*ugraph).type == UGRAPH_TYPE ) && ( (*ugraph).edge_type == Edge_Code ) && ( (*ugraph).value_type == Value_Code ) );
   LOCK( (*ugraph).mutex );
   INVARIANT( ugraph );

   UGraph_cursor_type( Prefix ) *cursor = NULL;
   
   cursor = (*ugraph).first_cursor;
   while( cursor != NULL  )
   {
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      cursor = (*cursor).next_cursor;
   }
   
   // dispose of edge values
   HSet_start( Edge_prefix )( (*ugraph).edges );
   while( HSet_off( Edge_prefix )( (*ugraph).edges ) == 0 )
   {
      EDGE_DISPOSE_FUNCTION( (* HSet_item_at( Edge_prefix )( (*ugraph).edges ) ).value );
      HSet_forth( Edge_prefix )( (*ugraph).edges );
   }
   
   // dispose of edges
   HSet_wipe_out_and_dispose( Edge_prefix )( (*ugraph).edges );

   // get new cursor to replace cursor eliminated by previous call
   (*(*ugraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*ugraph).edges );

   INVARIANT( ugraph );
   UNLOCK( (*ugraph).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


/**
 @file DGraph.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Directed graph with edges and nodes"
 
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

 Function definitions for the opaque DGraph_t type.

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
#include "DGraph.h"

/**
   defines
*/

#define DGRAPH_TYPE 0xA5000600
#define DGRAPH_EDGE_TYPE 0xA5000601
#define DGRAPH_VERTEX_TYPE 0xA5000602

#define DGraph_has_internal( arg ) PRIMITIVE_CAT( arg, _dgraph_has_internal )
int32_t
DGraph_has_internal( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *vertex 
);

#define DGraph_edge_from_to_internal( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_from_to_internal )
DGraph_edge_type( Prefix ) *DGraph_edge_from_to_internal( Prefix )
( 
   DGraph_type( Prefix ) *dgraph,
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
);

/**
   Node structure definition. Holds a value and references to its neighbor vertices
   and the edges that connect them.
*/

struct DGraph_vertex_struct( Prefix )
{
   int32_t type;
   int32_t value_type;
   
   int32_t hash_code;
   DGraph_type( Prefix ) *dgraph;
   Value value;
   HSet_type( Vertex_prefix ) *neighbors_from;
   HSet_type( Vertex_prefix ) *neighbors_to;
};

/**
   Edge structure definition. Holds a value and references to its start and 
   ending vertices. Represents a one way or directed edge.
*/

struct DGraph_edge_struct( Prefix )
{
   int32_t type;
   int32_t edge_type;
   
   int32_t hash_code;
   Edge value;
   DGraph_vertex_type( Prefix ) *v_from;
   DGraph_vertex_type( Prefix ) *v_to;
};

/**
   Directed graph structure definition.
*/

struct DGraph_struct( Prefix )
{
   int32_t type;
   int32_t edge_type;
   int32_t value_type;
   
   HSet_type( Vertex_prefix ) *vertices;
   HSet_type( Edge_prefix ) *edges;
   DGraph_cursor_type( Prefix ) *first_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to dgraph, current vertex, vertex
   stack, and a pointer to the next cursor.
*/

struct DGraph_cursor_struct( Prefix )
{
   DGraph_type( Prefix ) *dgraph; // the dgraph we're working with
   
   HSet_cursor_type( Vertex_prefix ) *cursor; // vertex cursor
   HSet_cursor_type( Edge_prefix ) *edge_cursor; // edge cursor
   
   int32_t is_depth_first; // search type flag
   HSet_type( Vertex_prefix ) *is_visited; // set of visited vertices for search
   
   DGraph_cursor_type( Prefix ) *next_cursor; // pointer to next cursor

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   structure address to hash code
*/

#define HASH_PRIME_NUMBER 8388593U // largest prime number less than 2^24

#define DGraph_address_to_hash( arg ) PRIMITIVE_CAT( arg, _dgraph_address_to_hash )

int32_t
DGraph_address_to_hash( Prefix )( DGraph_vertex_type( Prefix ) *vertex )
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

#define DGraph_edge_address_to_hash( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_address_to_hash )

int32_t
DGraph_edge_address_to_hash( Prefix )( DGraph_edge_type( Prefix ) *edge )
{
   int32_t result = 0;
   
   void *p1 = (*edge).v_from;
   void *p2 = (*edge).v_to;
   
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

#define DGraph_dispose_of_vertex( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose_of_vertex )

void
DGraph_dispose_of_vertex( Prefix )( DGraph_vertex_type( Prefix ) *vertex )
{
   DGraph_vertex_type( Prefix ) *v1 = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   
   DGraph_type( Prefix ) *dgraph = (*vertex).dgraph;
   
   if ( 
         ( dgraph != NULL ) 
         && 
         ( (*dgraph).edges != NULL ) 
         && 
         ( (*vertex).neighbors_to != NULL ) 
         && 
         ( (*vertex).neighbors_from != NULL ) 
      )
   {
      // dispose of edges to vertex
      for
      ( 
         HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
         HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0;
         HSet_forth( Vertex_prefix )( (*vertex).neighbors_to )
      )
      {   
         v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
         e = DGraph_edge_from_to_internal( Prefix )( dgraph, vertex, v1 );
         if ( e != NULL )
         {
            EDGE_DISPOSE_FUNCTION( (*e).value );
            HSet_remove( Edge_prefix )( (*dgraph).edges, e );
            free( e );
         }
      }
      
      // dispose of edges from vertex
      for
      ( 
         HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
         HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0;
         HSet_forth( Vertex_prefix )( (*vertex).neighbors_from )
      )
      {   
         v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
         e = DGraph_edge_from_to_internal( Prefix )( dgraph, v1, vertex );
         if ( e != NULL )
         {
            EDGE_DISPOSE_FUNCTION( (*e).value );
            HSet_remove( Edge_prefix )( (*dgraph).edges, e );
            free( e );
         }
      }
      
      // dispose of neighbor vertex hash sets but not their contents
      HSet_dispose( Vertex_prefix )( (*vertex).neighbors_to );
      (*vertex).neighbors_to = NULL;

      HSet_dispose( Vertex_prefix )( (*vertex).neighbors_from );
      (*vertex).neighbors_from = NULL;
   
   }
   else if ( 
         ( (*vertex).neighbors_to != NULL ) 
         && 
         ( (*vertex).neighbors_from != NULL ) 
      )
   {
      // dispose of neighbor vertex hash sets but not their contents
      HSet_dispose( Vertex_prefix )( (*vertex).neighbors_to );
      (*vertex).neighbors_to = NULL;

      HSet_dispose( Vertex_prefix )( (*vertex).neighbors_from );
      (*vertex).neighbors_from = NULL;
   }

   free( vertex );
   
   return;
}

/**
   DGraph_vertex_make
*/

DGraph_vertex_type( Prefix ) *
DGraph_vertex_make( Prefix )( Value value )
{
   // allocate vertex
   DGraph_vertex_type( Prefix ) *vertex 
   =  ( DGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( DGraph_vertex_type( Prefix ) ) );
   
   // set type
   (*vertex).type = DGRAPH_VERTEX_TYPE;
   (*vertex).value_type = Value_Code;
   
   // set hash code
   (*vertex).hash_code = DGraph_address_to_hash( Prefix )( ( void * ) vertex );
   
   // set value
   (*vertex).value = value;
   
   // initialize vertex hash sets
   (*vertex).neighbors_to = HSet_make( Vertex_prefix )();
   (*vertex).neighbors_from = HSet_make( Vertex_prefix )();
   
   POSTCONDITION( "vertex not null", vertex != NULL );
   
   return vertex;
}

/**
   edge_make
*/

static
DGraph_edge_type( Prefix ) *
edge_make( DGraph_vertex_type( Prefix ) *v_from, DGraph_vertex_type( Prefix ) *v_to, Edge value )
{
   PRECONDITION( "v_from vertex not null", v_from != NULL );
   PRECONDITION( "v_to vertex not null", v_to != NULL );
   
   // allocate edge
   DGraph_edge_type( Prefix ) *edge = ( DGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( DGraph_edge_type( Prefix ) ) );
   
   // set type
   (*edge).type = DGRAPH_EDGE_TYPE;
   (*edge).edge_type = Edge_Code;
   
   // set value
   (*edge).value = value;
      
   // set v_from and v_to vertex
   (*edge).v_from = v_from;
   (*edge).v_to = v_to;
   
   // set hash code
   (*edge).hash_code = DGraph_edge_address_to_hash( Prefix )( edge );
   
   POSTCONDITION( "edge not null", edge != NULL );
   
   return edge;
}

/**
   DGraph_dispose_of_edge
*/

#define DGraph_dispose_of_edge( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose_of_edge )

void
DGraph_dispose_of_edge( Prefix )( DGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   
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
edge_dispose( DGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   
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
edge_dispose_with_contents( DGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   
   // dispose of value
   EDGE_DISPOSE_FUNCTION( (*edge).value );
   
   // do not dispose of start and end vertex

   // dispose of edge   
   free( edge );
   
   return;
}

/**
   DGraph_edge_equal
*/

#define DGraph_edge_equal( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_equal )

int32_t
DGraph_edge_equal( Prefix )( DGraph_edge_type( Prefix ) *edge1, DGraph_edge_type( Prefix ) *edge2 )
{
   PRECONDITION( "edge1 not null", edge1 != NULL );
   PRECONDITION( "edge1 type ok", ( (*edge1).type == DGRAPH_EDGE_TYPE ) && ( (*edge1).edge_type == Edge_Code ) );
   PRECONDITION( "edge2 not null", edge2 != NULL );
   PRECONDITION( "edge2 type ok", ( (*edge2).type == DGRAPH_EDGE_TYPE ) && ( (*edge2).edge_type == Edge_Code ) );
   
   int32_t result = 1;
   
   // check from
   if ( (*edge1).v_from != (*edge2).v_from )
   {
      result = 0;
   }
   
   // check to
   if ( (*edge1).v_to != (*edge2).v_to )
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
edge_from_and_to_vertices_exist( DGraph_type( Prefix ) *dgraph )
{
   int32_t result = 1;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_vertex_type( Prefix ) *v1;   
   DGraph_vertex_type( Prefix ) *v2;   
   HSet_cursor_type( Edge_prefix ) *cursor;
   
   cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );
   
   HSet_cursor_start( Edge_prefix )( cursor );
   while( ( HSet_cursor_off( Edge_prefix )( cursor ) == 0 ) && ( result == 1 ) )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( cursor );
      v1 = (*edge).v_from;
      v2 = (*edge).v_to;
      result = DGraph_has_internal( Prefix )( dgraph, v1 );
      if ( result == 1 )
      {
         result = DGraph_has_internal( Prefix )( dgraph, v2 );
      }
      HSet_cursor_forth( Edge_prefix )( cursor );
   }

   HSet_cursor_dispose( Edge_prefix )( cursor );
   
   return result;
}

static
int32_t
cursors_ok( DGraph_type( Prefix ) *dgraph )
{
   int32_t result = 1;

   DGraph_cursor_type( Prefix ) *cursor = (*dgraph).first_cursor;

   while ( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).dgraph == dgraph );
      cursor = (*cursor).next_cursor;
   }

   return result;
}


static
void invariant( DGraph_type( Prefix ) *dgraph )
{
   assert(((void) "edge from and to vertices exist", edge_from_and_to_vertices_exist( dgraph ) ));
   assert(((void) "cursors OK", cursors_ok( dgraph ) ));
   return;
}

#endif

/**
   DGraph_vertex_dispose
*/

void
DGraph_vertex_dispose( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   
   DGraph_vertex_type( Prefix ) *v1 = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   
   if ( (*vertex).dgraph != NULL )
   {
    
      if ( HSet_has( Vertex_prefix )( (*dgraph).vertices, vertex ) == 1 )
      {
         // dispose of edges to vertex
         for
         ( 
            HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
            HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0;
            HSet_forth( Vertex_prefix )( (*vertex).neighbors_to )
         )
         {   
            v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
            e = DGraph_edge_from_to_internal( Prefix )( dgraph, vertex, v1 );
            if ( e != NULL )
            {
               EDGE_DISPOSE_FUNCTION( (*e).value );
               HSet_remove( Edge_prefix )( (*dgraph).edges, e );
               free( e );
            }
         }
         
         // dispose of edges from vertex
         for
         ( 
            HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
            HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0;
            HSet_forth( Vertex_prefix )( (*vertex).neighbors_from )
         )
         {   
            v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
            e = DGraph_edge_from_to_internal( Prefix )( dgraph, v1, vertex );
            if ( e != NULL )
            {
               EDGE_DISPOSE_FUNCTION( (*e).value );
               HSet_remove( Edge_prefix )( (*dgraph).edges, e );
               free( e );
            }
         }
         
         // remove vertex from graph
         HSet_remove( Vertex_prefix )( (*dgraph).vertices, vertex );
         
      }
   }
   
   // do not dispose of value
      
   // dispose of neighbor vertex hash sets but not their contents
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors_to );
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors_from );

   (*vertex).hash_code = 0;
   (*vertex).dgraph = NULL;
   (*vertex).neighbors_from = NULL;
   (*vertex).neighbors_to = NULL;
   
   // dispose of vertex   
   free( vertex );
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_vertex_dispose_with_contents
*/

void
DGraph_vertex_dispose_with_contents( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   
   DGraph_vertex_type( Prefix ) *v1 = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   
   if ( (*vertex).dgraph != NULL )
   {
            
      if ( HSet_has( Vertex_prefix )( (*dgraph).vertices, vertex ) == 1 )
      {
         // dispose of edges to vertex
         for
         ( 
            HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
            HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0;
            HSet_forth( Vertex_prefix )( (*vertex).neighbors_to )
         )
         {   
            v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
            e = DGraph_edge_from_to_internal( Prefix )( dgraph, vertex, v1 );
            if ( e != NULL )
            {
               EDGE_DISPOSE_FUNCTION( (*e).value );
               HSet_remove( Edge_prefix )( (*dgraph).edges, e );
               free( e );
            }
         }
         
         // dispose of edges from vertex
         for
         ( 
            HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
            HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0;
            HSet_forth( Vertex_prefix )( (*vertex).neighbors_from )
         )
         {   
            v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
            e = DGraph_edge_from_to_internal( Prefix )( dgraph, v1, vertex );
            if ( e != NULL )
            {
               EDGE_DISPOSE_FUNCTION( (*e).value );
               HSet_remove( Edge_prefix )( (*dgraph).edges, e );
               free( e );
            }
         }
         
         // remove vertex from graph
         HSet_remove( Vertex_prefix )( (*dgraph).vertices, vertex );
      }
   }
   
   // dispose of neighbor vertex hash sets but not their contents
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors_to );
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors_from );

   (*vertex).hash_code = 0;
   (*vertex).dgraph = NULL;
   (*vertex).neighbors_from = NULL;
   (*vertex).neighbors_to = NULL;
   
   // dispose of value
   DISPOSE_FUNCTION( (*vertex).value );
   
   // dispose of vertex   
   free( vertex );
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}



/**
   DGraph_make_depth
*/

DGraph_type( Prefix ) *
DGraph_make_depth( Prefix )( void )
{
   // allocate dgraph struct
   DGraph_type( Prefix ) * dgraph
      = ( DGraph_type( Prefix ) * ) calloc( 1, sizeof( DGraph_type( Prefix ) ) );

   // set type codes
   (*dgraph).type = DGRAPH_TYPE;
   (*dgraph).edge_type = Edge_Code;
   (*dgraph).value_type = Value_Code;
   
   // init hash set of vertices 
   (*dgraph).vertices = HSet_make( Vertex_prefix )();

   // init hash set of edges 
   (*dgraph).edges = HSet_make( Edge_prefix )();

   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );

   // set dgraph in cursor
   (*cursor).dgraph = dgraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*dgraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );

   // set cursor to depth first
   (*cursor).is_depth_first = 1;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // set dgraph first cursor
   (*dgraph).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*dgraph).mutex );

   INVARIANT( dgraph );

   return dgraph;
}

/**
   DGraph_make_breadth
*/

DGraph_type( Prefix ) *
DGraph_make_breadth( Prefix )( void )
{
   // allocate dgraph struct
   DGraph_type( Prefix ) * dgraph
      = ( DGraph_type( Prefix ) * ) calloc( 1, sizeof( DGraph_type( Prefix ) ) );

   // set type codes
   (*dgraph).type = DGRAPH_TYPE;
   (*dgraph).edge_type = Edge_Code;
   (*dgraph).value_type = Value_Code;
   
   // init hash set of vertices 
   (*dgraph).vertices = HSet_make( Vertex_prefix )();

   // init hash set of edges 
   (*dgraph).edges = HSet_make( Edge_prefix )();

   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );

   // set dgraph in cursor
   (*cursor).dgraph = dgraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*dgraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );

   // set cursor to breadth first
   (*cursor).is_depth_first = 0;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // set dgraph first cursor
   (*dgraph).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*dgraph).mutex );

   INVARIANT( dgraph );

   return dgraph;
}

/**
   DGraph_cursor_make_depth
*/

DGraph_cursor_type( Prefix ) *
DGraph_cursor_make_depth( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *c = NULL;
   
   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );

   // set dgraph in cursor
   (*cursor).dgraph = dgraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*dgraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );

   // set cursor to depth first
   (*cursor).is_depth_first = 1;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // get last cursor reference in dgraph structure
   c = (*dgraph).first_cursor;
   while ( (*c).next_cursor != NULL )
   {
      c = (*c).next_cursor;
   }

   // add new cursor to end of cursor "list"
   (*c).next_cursor = cursor;
   
   MULTITHREAD_MUTEX_INIT( (*dgraph).mutex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return cursor;
}

/**
   DGraph_cursor_make_breadth
*/

DGraph_cursor_type( Prefix ) *
DGraph_cursor_make_breadth( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *c = NULL;
   
   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );

   // set dgraph in cursor
   (*cursor).dgraph = dgraph;

   // set internal hset cursors
   (*cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*dgraph).vertices );
   (*cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );

   // set cursor to breadth first
   (*cursor).is_depth_first = 0;
   
   // initialize is_visited hset
   (*cursor).is_visited = HSet_make( Vertex_prefix )();
   
   // set next cursor to null
   (*cursor).next_cursor = NULL;
   
   // get last cursor reference in dgraph structure
   c = (*dgraph).first_cursor;
   while ( (*c).next_cursor != NULL )
   {
      c = (*c).next_cursor;
   }

   // add new cursor to end of cursor "list"
   (*c).next_cursor = cursor;
   
   MULTITHREAD_MUTEX_INIT( (*cursor).mutex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return cursor;
}

/**
   DGraph_dispose
*/

void
DGraph_dispose( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;
   
   // dispose of cursors
   cursor = (*dgraph).first_cursor;
   
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
   HSet_dispose_with_contents( Edge_prefix )( (*dgraph).edges );
   (*dgraph).edges = NULL;
   
   // dispose of vertices
   HSet_dispose_with_contents( Vertex_prefix )( (*dgraph).vertices );
   
   MULTITHREAD_MUTEX_DESTROY( (*dgraph).mutex );

   // delete dgraph struct
   free( dgraph );

   return;
}

/**
   DGraph_dispose_with_contents
*/

void
DGraph_dispose_with_contents( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;
   
   // dispose of cursors
   cursor = (*dgraph).first_cursor;
   
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
   HSet_start( Edge_prefix )( (*dgraph).edges );
   while( HSet_off( Edge_prefix )( (*dgraph).edges ) == 0 )
   {
      EDGE_DISPOSE_FUNCTION( (* HSet_item_at( Edge_prefix )( (*dgraph).edges ) ).value );
      HSet_forth( Edge_prefix )( (*dgraph).edges );
   }

   // dispose of edges
   HSet_dispose_with_contents( Edge_prefix )( (*dgraph).edges );
   (*dgraph).edges = NULL;
   
   // dispose of vertex values
   HSet_start( Vertex_prefix )( (*dgraph).vertices );
   while( HSet_off( Vertex_prefix )( (*dgraph).vertices ) == 0 )
   {
      DISPOSE_FUNCTION( (* HSet_item_at( Vertex_prefix )( (*dgraph).vertices ) ).value );
      HSet_forth( Vertex_prefix )( (*dgraph).vertices );
   }

   // dispose of vertices
   HSet_dispose_with_contents( Vertex_prefix )( (*dgraph).vertices );
   
   MULTITHREAD_MUTEX_DESTROY( (*dgraph).mutex );

   // delete dgraph struct
   free( dgraph );

   return;
}

/**
   DGraph_cursor_dispose
*/

void
DGraph_cursor_dispose( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_type( Prefix ) *dgraph = (*cursor).dgraph;

   DGraph_cursor_type( Prefix ) *c1 = NULL;
   DGraph_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from dgraph structure
   c1 = (*(*cursor).dgraph).first_cursor;
   c2 = (*c1).next_cursor;

   // otherwise search through rest of the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
      {
         // if we have a match, remove "c2" from the cursor dgraph, set flag
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

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_value

*/

Value
DGraph_value( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   Value result = (*vertex).value;

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_from_to

*/

DGraph_edge_type( Prefix ) *
DGraph_edge_from_to_internal( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   DGraph_edge_type( Prefix ) *result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_edge_type( Prefix ) *edge1 = NULL;
   
   // get the edge, if it exists
   edge1 = edge_make( v_from, v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = edge;
   }   
   
   return result;
}

/**
   DGraph_edge_from_to

*/

DGraph_edge_type( Prefix ) *
DGraph_edge_from_to( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) *result 
      = DGraph_edge_from_to_internal( Prefix )( dgraph, v_from, v_to );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );
   
   return result;
}

/**
   DGraph_edge_value_from_to

*/

Edge
DGraph_edge_value_from_to( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   Edge result = (* DGraph_edge_from_to_internal( Prefix )( dgraph, v_from, v_to ) ).value;

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );
   
   return result;
}

/**
   DGraph_edge_value

*/

Edge
DGraph_edge_value( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_edge_type( Prefix ) *edge 
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   Edge result = (*edge).value;
   
   // get the edge, if it exists
   DGraph_edge_type( Prefix ) *edge1 = edge_make( (*edge).v_from, (*edge).v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = (*edge).value;
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_vertex_from

*/

DGraph_vertex_type( Prefix ) *
DGraph_edge_vertex_from( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_edge_type( Prefix ) *edge 
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *result = NULL;
   
   // get the edge, if it exists
   DGraph_edge_type( Prefix ) *edge1 = edge_make( (*edge).v_from, (*edge).v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = (*edge).v_from;
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_vertex_to

*/

DGraph_vertex_type( Prefix ) *
DGraph_edge_vertex_to( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_edge_type( Prefix ) *edge 
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *result = NULL;
   
   // get the edge, if it exists
   DGraph_edge_type( Prefix ) *edge1 = edge_make( (*edge).v_from, (*edge).v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = (*edge).v_to;
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_at
*/

DGraph_vertex_type( Prefix ) *
DGraph_at( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *result = HSet_item_at( Vertex_prefix )( (*dgraph).vertices );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_at
*/

DGraph_vertex_type( Prefix ) *
DGraph_cursor_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );
   PRECONDITION( "cursor not off", HSet_cursor_off( Vertex_prefix )( (*cursor).cursor ) == 0 );

   DGraph_vertex_type( Prefix ) *result = HSet_cursor_item_at( Vertex_prefix )( (*cursor).cursor );

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   DGraph_cursor_value_at
*/

Value
DGraph_cursor_value_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );
   PRECONDITION( "cursor not off", HSet_cursor_off( Vertex_prefix )( (*cursor).cursor ) == 0 );

   Value result = (* HSet_cursor_item_at( Vertex_prefix )( (*cursor).cursor ) ).value;

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}


/**
   DGraph_value_at
*/

Value
DGraph_value_at( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   PRECONDITION( "not off", HSet_off( Vertex_prefix )( (*dgraph).vertices  ) == 0 );

   Value result = (* HSet_item_at( Vertex_prefix )( (*dgraph).vertices ) ).value;

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_edge_at
*/

DGraph_edge_type( Prefix ) *
DGraph_cursor_edge_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );
   PRECONDITION( "edge_cursor not off", HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor ) == 0 );

   DGraph_edge_type( Prefix ) *result = HSet_cursor_item_at( Edge_prefix )( (*cursor).edge_cursor );

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}


/**
   DGraph_edge_at
*/

DGraph_edge_type( Prefix ) *
DGraph_edge_at( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   PRECONDITION( "not off", HSet_off( Edge_prefix )( (*dgraph).edges ) == 0 );

   DGraph_edge_type( Prefix ) *result = HSet_item_at( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_edge_value_at
*/

Edge
DGraph_cursor_edge_value_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );
   PRECONDITION( "cursor not off", HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor ) == 0 );

   Edge result = (* HSet_cursor_item_at( Edge_prefix )( (*cursor).edge_cursor ) ).value;

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}


/**
   DGraph_edge_value_at
*/

Edge
DGraph_edge_value_at( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   PRECONDITION( "not off", HSet_off( Edge_prefix )( (*dgraph).edges ) == 0 );

   Edge result = (* HSet_item_at( Edge_prefix )( (*dgraph).edges ) ).value;

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_as_array
*/

DGraph_vertex_type( Prefix ) **
DGraph_as_array( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) **result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Vertex_prefix )( (*dgraph).vertices );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( DGraph_vertex_type( Prefix ) ** ) calloc( n + 1, sizeof( DGraph_vertex_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_start( Vertex_prefix )( (*dgraph).vertices );
   i = 0;
   while ( HSet_off( Vertex_prefix )( (*dgraph).vertices ) == 0 )
   {
      vertex = HSet_item_at( Vertex_prefix )( (*dgraph).vertices );
      result[i] = vertex;
      i++;
      HSet_forth( Vertex_prefix )( (*dgraph).vertices );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edges_as_array
*/

DGraph_edge_type( Prefix ) **
DGraph_edges_as_array( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) **result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Edge_prefix )( (*dgraph).edges );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( DGraph_edge_type( Prefix ) ** ) calloc( n + 1, sizeof( DGraph_edge_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_cursor_start( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   i = 0;
   while ( HSet_cursor_off( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
      result[i] = edge;
      i++;
      HSet_cursor_forth( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_count
*/

int32_t
DGraph_count( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t count = HSet_count( Vertex_prefix )( (*dgraph).vertices );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return count;
}

/**
   DGraph_edge_count
*/

int32_t
DGraph_edge_count( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t count = HSet_count( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return count;
}

/**
   DGraph_are_adjacent
*/

int32_t
DGraph_are_adjacent( Prefix )
( 
   DGraph_type( Prefix ) *dgraph,
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = 0;
   DGraph_edge_type( Prefix ) *edge = NULL;
   
   // get the edge, if it exists
   DGraph_edge_type( Prefix ) *edge1 = edge_make( v_from, v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );
   
   if ( edge != NULL )
   {
      result = 1;
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_off
*/

int32_t
DGraph_off( Prefix)( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = HSet_off( Vertex_prefix )( (*dgraph).vertices );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_off
*/

int32_t
DGraph_cursor_off( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = HSet_cursor_off( Vertex_prefix )( (*cursor).cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   DGraph_is_empty
*/

int32_t
DGraph_is_empty( Prefix)( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = HSet_is_empty( Vertex_prefix )( (*dgraph).vertices );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_off
*/

int32_t
DGraph_edge_off( Prefix)( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = HSet_off( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_edge_off
*/

int32_t
DGraph_cursor_edge_off( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = HSet_cursor_off( Edge_prefix )( (*cursor).edge_cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   DGraph_edge_is_empty
*/

int32_t
DGraph_edge_is_empty( Prefix)( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = HSet_is_empty( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   dgraph_depth_is_connected
   
   use hash set to accumulate visited vertices
*/

static
void
dgraph_depth_is_connected( DGraph_cursor_type( Prefix ) *cursor, DGraph_vertex_type( Prefix ) *vertex )
{
   DGraph_vertex_type( Prefix ) *v = NULL;
   
   if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, vertex ) == 0 )
   {
      
      // put vertex into visited set
      HSet_put( Vertex_prefix )( (*cursor).is_visited, vertex );
            
      // put connected vertices into is_visited hash set
      HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
      while( HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0 )
      {
         v = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
         if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, v ) == 0 )
         {
            dgraph_depth_is_connected( cursor, v );
         }
         HSet_forth( Vertex_prefix )( (*vertex).neighbors_to );
      }
      
      HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
      while( HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0 )
      {
         v = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
         if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, v ) == 0 )
         {
            dgraph_depth_is_connected( cursor, v );
         }
         HSet_forth( Vertex_prefix )( (*vertex).neighbors_from );
      }
      
   }

   return;
}

/**
   dgraph_breadth_is_connected
   
   use hash set to accumulate visited vertices
*/

static
void
dgraph_breadth_is_connected
( 
   DGraph_cursor_type( Prefix ) *cursor, 
   DGraph_vertex_type( Prefix ) *vertex,
   HSet_type( Vertex_prefix ) *queue
)
{
   DGraph_vertex_type( Prefix ) *v = NULL;
   DGraph_vertex_type( Prefix ) *v1 = NULL;
   
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
      HSet_start( Vertex_prefix )( (*v).neighbors_to );
      while( HSet_off( Vertex_prefix )( (*v).neighbors_to ) == 0 )
      {
         v1 = HSet_item_at( Vertex_prefix )( (*v).neighbors_to );
         if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, v1 ) == 0 )
         {
            HSet_put( Vertex_prefix )( (*cursor).is_visited, v1 );
            HSet_put( Vertex_prefix )( queue, v1 );
         }
         HSet_forth( Vertex_prefix )( (*v).neighbors_to );
      }
      
      HSet_start( Vertex_prefix )( (*v).neighbors_from );
      while( HSet_off( Vertex_prefix )( (*v).neighbors_from ) == 0 )
      {
         v1 = HSet_item_at( Vertex_prefix )( (*v).neighbors_from );
         if ( HSet_has( Vertex_prefix )( (*cursor).is_visited, v1 ) == 0 )
         {
            HSet_put( Vertex_prefix )( (*cursor).is_visited, v1 );
            HSet_put( Vertex_prefix )( queue, v1 );
         }
         HSet_forth( Vertex_prefix )( (*v).neighbors_from );
      }
   
   }
   
   return;
}

/**
   DGraph_is_connected
*/

int32_t
DGraph_is_connected( Prefix)( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = 0;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   DGraph_cursor_type( Prefix ) *cursor = (*dgraph).first_cursor;
   
   if ( HSet_count( Vertex_prefix )( (*dgraph).vertices ) <= 1 )
   {
      // zero or one vertex graphs are connected
      result = 1;
   }
   else if ( (*cursor).is_depth_first == 1 ) 
   {
      // get first vertex
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      HSet_start( Vertex_prefix )( (*dgraph).vertices );
      vertex = HSet_item_at( Vertex_prefix )( (*dgraph).vertices );
      
      // fill is_visited hash set with connected vertices
      dgraph_depth_is_connected( cursor, vertex );
      
      // graph is connected if all vertices have been visited, which means
      // that the count of is_visited is the same as the count of vertices
      if ( 
            HSet_count( Vertex_prefix )( (*cursor).is_visited ) 
               == HSet_count( Vertex_prefix )( (*dgraph).vertices )
         )
      {
         result = 1;
      }
   }
   else // breadth first 
   {
      // get first vertex
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      HSet_start( Vertex_prefix )( (*dgraph).vertices );
      vertex = HSet_item_at( Vertex_prefix )( (*dgraph).vertices );
      
      HSet_type( Vertex_prefix ) *queue 
         = HSet_make( Vertex_prefix )(); // queue of visited vertices for search
      
      // fill is_visited hash set with connected vertices
      dgraph_breadth_is_connected( cursor, vertex, queue );
      
      // graph is connected if all vertices have been visited, which means
      // that the count of is_visited is the same as the count of vertices
      if ( 
            HSet_count( Vertex_prefix )( (*cursor).is_visited ) 
               == HSet_count( Vertex_prefix )( (*dgraph).vertices )
         )
      {
         result = 1;
      }
      
      HSet_dispose( Vertex_prefix )( queue );
      
   }
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_has_internal
*/

int32_t
DGraph_has_internal( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   
   int32_t result = HSet_has( Vertex_prefix )( (*dgraph).vertices, vertex );
   return result;
}


int32_t
DGraph_has( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = DGraph_has_internal( Prefix )( dgraph, vertex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_has
*/

int32_t
DGraph_edge_has( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = HSet_has( Edge_prefix )( (*dgraph).edges, edge );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_has_value
*/

int32_t
DGraph_has_value( Prefix )( DGraph_type( Prefix ) *dgraph, Value value )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = 0;
   Value v;
   
   HSet_start( Vertex_prefix )( (*dgraph).vertices );
   while( HSet_off( Vertex_prefix )( (*dgraph).vertices ) == 0 )
   {
      v = (* HSet_item_at( Vertex_prefix )( (*dgraph).vertices ) ).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = 1;
         break;
      }
      HSet_forth( Vertex_prefix )( (*dgraph).vertices );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_has_value
*/

int32_t
DGraph_edge_has_value( Prefix )( DGraph_type( Prefix ) *dgraph, Edge value )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   int32_t result = 0;
   Edge v;
   
   HSet_cursor_start( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor ) == 0 )
   {
      v = (* HSet_cursor_item_at( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor ) ).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = 1;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_neighbors_from
*/
DGraph_vertex_type( Prefix ) **
DGraph_neighbors_from( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) **result = NULL;
   DGraph_vertex_type( Prefix ) *v = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Vertex_prefix )( (*vertex).neighbors_from );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( DGraph_vertex_type( Prefix ) ** ) calloc( n + 1, sizeof( DGraph_vertex_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
   i = 0;
   while ( HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0 )
   {
      v = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
      result[i] = v;
      i++;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors_from );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_neighbors_to
*/
DGraph_vertex_type( Prefix ) **
DGraph_neighbors_to( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) **result = NULL;
   DGraph_vertex_type( Prefix ) *v = NULL;
   int32_t i = 0;
   int32_t n = HSet_count( Vertex_prefix )( (*vertex).neighbors_to );

   // allocate space for array of vertex pointers, one extra at end to be NULL
   result = ( DGraph_vertex_type( Prefix ) ** ) calloc( n + 1, sizeof( DGraph_vertex_type( Prefix ) ) );

   // put vertex pointers into result array
   HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
   i = 0;
   while ( HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0 )
   {
      v = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
      result[i] = v;
      i++;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors_to );
   }
   // last entry in array is NULL
   result[n] = NULL;
   
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_forth
*/
void
DGraph_cursor_forth( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   HSet_cursor_forth( Vertex_prefix )( (*cursor).cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DGraph_cursor_start
*/

void
DGraph_cursor_start( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   HSet_cursor_start( Vertex_prefix )( (*cursor).cursor );

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DGraph_forth
*/
void
DGraph_forth( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   PRECONDITION( "not off", HSet_off( Vertex_prefix )( (*dgraph).vertices ) == 0 );

   HSet_forth( Vertex_prefix )( (*dgraph).vertices );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_start
*/

void
DGraph_start( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   HSet_start( Vertex_prefix )( (*dgraph).vertices );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_find_value
*/

DGraph_vertex_type( Prefix ) *
DGraph_find_value( Prefix )( DGraph_type( Prefix ) *dgraph, Value value )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   Value v;
   
   HSet_cursor_start( Vertex_prefix )( (*(*dgraph).first_cursor).cursor );
   while( HSet_cursor_off( Vertex_prefix )( (*(*dgraph).first_cursor).cursor ) == 0 )
   {
      vertex = HSet_cursor_item_at( Vertex_prefix )( (*(*dgraph).first_cursor).cursor );
      v = (*vertex).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = vertex;
         break;
      }
      HSet_cursor_forth( Vertex_prefix )( (*(*dgraph).first_cursor).cursor );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_find_next_value
*/

DGraph_vertex_type( Prefix ) *
DGraph_find_next_value( Prefix )( DGraph_type( Prefix ) *dgraph, Value value )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   Value v;
   
   HSet_cursor_forth( Vertex_prefix )( (*(*dgraph).first_cursor).cursor );
   while( HSet_cursor_off( Vertex_prefix )( (*(*dgraph).first_cursor).cursor ) == 0 )
   {
      vertex = HSet_cursor_item_at( Vertex_prefix )( (*(*dgraph).first_cursor).cursor );
      v = (*vertex).value;
      if ( EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = vertex;
         break;
      }
      HSet_cursor_forth( Vertex_prefix )( (*(*dgraph).first_cursor).cursor );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_find_value
*/

DGraph_vertex_type( Prefix ) *
DGraph_cursor_find_value( Prefix )( DGraph_cursor_type( Prefix ) *cursor, Value value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_vertex_type( Prefix ) *result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
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

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_find_next_value
*/

DGraph_vertex_type( Prefix ) *
DGraph_cursor_find_next_value( Prefix )( DGraph_cursor_type( Prefix ) *cursor, Value value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_vertex_type( Prefix ) *result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
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

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_edge_forth
*/
void
DGraph_cursor_edge_forth( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );

   HSet_cursor_forth( Edge_prefix )( (*cursor).edge_cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DGraph_cursor_edge_start
*/

void
DGraph_cursor_edge_start( Prefix )( DGraph_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   HSet_cursor_start( Edge_prefix )( (*cursor).edge_cursor );

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DGraph_edge_forth
*/
void
DGraph_edge_forth( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );
   PRECONDITION( "not off", HSet_off( Edge_prefix )( (*dgraph).edges ) == 0 );

   HSet_forth( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_start
*/

void
DGraph_edge_start( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   HSet_start( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_find_value
*/

DGraph_edge_type( Prefix ) *
DGraph_edge_find_value( Prefix )( DGraph_type( Prefix ) *dgraph, Edge value )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) *result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   Edge v;
   
   HSet_cursor_start( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
      v = (*edge).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = edge;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_edge_find_next_value
*/

DGraph_edge_type( Prefix ) *
DGraph_edge_find_next_value( Prefix )( DGraph_type( Prefix ) *dgraph, Edge value )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) *result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   Edge v;
   
   HSet_cursor_forth( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   while( HSet_cursor_off( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor ) == 0 )
   {
      edge = HSet_cursor_item_at( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
      v = (*edge).value;
      if ( EDGE_EQUALITY_FUNCTION( value, v ) == 1 )
      {
         result = edge;
         break;
      }
      HSet_cursor_forth( Edge_prefix )( (*(*dgraph).first_cursor).edge_cursor );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_edge_find_value
*/

DGraph_edge_type( Prefix ) *
DGraph_cursor_edge_find_value( Prefix )( DGraph_cursor_type( Prefix ) *cursor, Edge value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_edge_type( Prefix ) *result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
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

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );

   return result;
}

/**
   DGraph_cursor_edge_find_next_value
*/

DGraph_edge_type( Prefix ) *
DGraph_cursor_edge_find_next_value( Prefix )( DGraph_cursor_type( Prefix ) *cursor, Value value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).dgraph).type == DGRAPH_TYPE ) && ( (*(*cursor).dgraph).edge_type == Edge_Code ) && ( (*(*cursor).dgraph).value_type == Value_Code ) );
   LOCK( (*(*cursor).dgraph).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_edge_type( Prefix ) *result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
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

   INVARIANT( (*cursor).dgraph );
   UNLOCK( (*(*cursor).dgraph).mutex );

   return result;
}

/**
   DGraph_vertex_set_bucket_count
*/

void
DGraph_vertex_set_bucket_count( Prefix )( DGraph_type( Prefix ) *dgraph, int32_t bucket_count )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "bucket_count positive", bucket_count > 0 );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *vertex = NULL;
   DGraph_cursor_type( Prefix ) *cursor = NULL;
   
   // set bucket count in each vertex HSet
   HSet_start( Vertex_prefix )( (*dgraph).vertices );
   while( HSet_off( Vertex_prefix )( (*dgraph).vertices ) == 0 )
   {
      vertex = HSet_item_at( Vertex_prefix )( (*dgraph).vertices );
      HSet_set_bucket_count( Vertex_prefix )( (*vertex).neighbors_from, bucket_count );
      HSet_set_bucket_count( Vertex_prefix )( (*vertex).neighbors_to, bucket_count );
      HSet_forth( Vertex_prefix )( (*dgraph).vertices );
   }
   
   HSet_set_bucket_count( Vertex_prefix )( (*dgraph).vertices, bucket_count );
   
   // set bucket counts in cursors
   cursor = (*dgraph).first_cursor;
   
   while( cursor != NULL )
   {
      HSet_set_bucket_count( Vertex_prefix )( (*cursor).is_visited, bucket_count );
      cursor = (*cursor).next_cursor;
   }
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_set_bucket_count
*/

void
DGraph_edge_set_bucket_count( Prefix )( DGraph_type( Prefix ) *dgraph, int32_t bucket_count )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "bucket_count positive", bucket_count > 0 );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   // set bucket count in each edge HSet
   HSet_set_bucket_count( Edge_prefix )( (*dgraph).edges, bucket_count );
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_put
*/

void
DGraph_put( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   // set dgraph
   (*vertex).dgraph = dgraph; 
   
   HSet_put( Vertex_prefix )( (*dgraph).vertices, vertex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_put
*/

void
DGraph_edge_put( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   Edge value,
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   // add edge
   DGraph_edge_type( Prefix ) *edge = NULL;
   edge = edge_make( v_from, v_to, value );
   HSet_put( Edge_prefix )( (*dgraph).edges, edge );

   // add to neighbors_to of v_from
   HSet_put( Vertex_prefix )( (*v_from).neighbors_to, v_to );
   
   // add to neighbors_to of v_to
   HSet_put( Vertex_prefix )( (*v_to).neighbors_from, v_from );
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_set_value
*/

void
DGraph_set_value( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *vertex,
   Value value
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   (*vertex).value = value;

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_set
*/

void
DGraph_edge_set( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to,
   Edge value
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_edge_type( Prefix ) *e1 = NULL;
   
   edge = edge_make( v_from, v_to, value );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge ) == 1 )
   {
      e1 = HSet_item( Edge_prefix )( (*dgraph).edges, edge );
   }
   edge_dispose( edge );
   
   if ( e1 != NULL )
   {
      (*e1).value = value;
   }
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_set_value
*/

void
DGraph_edge_set_value( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_edge_type( Prefix ) *edge,
   Edge value
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   (*edge).value = value;

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_remove
*/

void
DGraph_remove( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex  != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *v1 = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   
   // dispose of edges to vertex
   for
   ( 
      HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
      HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors_to )
   )
   {   
      v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
      e = DGraph_edge_from_to_internal( Prefix )( dgraph, vertex, v1 );
      if ( e != NULL )
      {
         EDGE_DISPOSE_FUNCTION( (*e).value );
         HSet_remove( Edge_prefix )( (*dgraph).edges, e );
         free( e );
      }
   }
   
   // dispose of edges from vertex
   for
   ( 
      HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
      HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors_from )
   )
   {   
      v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
      e = DGraph_edge_from_to_internal( Prefix )( dgraph, v1, vertex );
      if ( e != NULL )
      {
         EDGE_DISPOSE_FUNCTION( (*e).value );
         HSet_remove( Edge_prefix )( (*dgraph).edges, e );
         free( e );
      }
   }
   
   // wipe out neighbor vertex hash sets but not their contents
   HSet_wipe_out( Vertex_prefix )( (*vertex).neighbors_to );
   HSet_wipe_out( Vertex_prefix )( (*vertex).neighbors_from );
   
   HSet_remove( Vertex_prefix )( (*dgraph).vertices, vertex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_remove_and_dispose
*/

void
DGraph_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "vertex not null", vertex  != NULL );
   PRECONDITION( "vertex type ok", ( (*vertex).type == DGRAPH_VERTEX_TYPE ) && ( (*vertex).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_vertex_type( Prefix ) *v1 = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   
   // dispose of edges to vertex
   for
   ( 
      HSet_start( Vertex_prefix )( (*vertex).neighbors_to );
      HSet_off( Vertex_prefix )( (*vertex).neighbors_to ) == 0;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors_to )
   )
   {   
      v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_to );
      e = DGraph_edge_from_to_internal( Prefix )( dgraph, vertex, v1 );
      if ( e != NULL )
      {
         EDGE_DISPOSE_FUNCTION( (*e).value );
         HSet_remove( Edge_prefix )( (*dgraph).edges, e );
         free( e );
      }
   }
   
   // dispose of edges from vertex
   for
   ( 
      HSet_start( Vertex_prefix )( (*vertex).neighbors_from );
      HSet_off( Vertex_prefix )( (*vertex).neighbors_from ) == 0;
      HSet_forth( Vertex_prefix )( (*vertex).neighbors_from )
   )
   {   
      v1 = HSet_item_at( Vertex_prefix )( (*vertex).neighbors_from );
      e = DGraph_edge_from_to_internal( Prefix )( dgraph, v1, vertex );
      if ( e != NULL )
      {
         EDGE_DISPOSE_FUNCTION( (*e).value );
         HSet_remove( Edge_prefix )( (*dgraph).edges, e );
         free( e );
      }
   }
   
   // dispose of neighbor vertex hash sets but not their contents
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors_to );
   (*vertex).neighbors_to = NULL;
   
   HSet_dispose( Vertex_prefix )( (*vertex).neighbors_from );
   (*vertex).neighbors_from = NULL;

   HSet_remove_and_dispose( Vertex_prefix )( (*dgraph).vertices, vertex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}


/**
   DGraph_edge_remove
*/

void
DGraph_edge_remove( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   HSet_remove_and_dispose( Edge_prefix )( (*dgraph).edges, edge );
   
   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_remove_and_dispose
*/

void
DGraph_edge_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_edge_type( Prefix ) *edge )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "edge not null", edge  != NULL );
   PRECONDITION( "edge type ok", ( (*edge).type == DGRAPH_EDGE_TYPE ) && ( (*edge).edge_type == Edge_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   EDGE_DISPOSE_FUNCTION( (*edge).value );
   HSet_remove_and_dispose( Edge_prefix )( (*dgraph).edges, edge );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}


/**
   DGraph_edge_remove_from_to
*/

void
DGraph_edge_remove_from_to( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) *edge = NULL;
   
   // get the edge, if it exists
   DGraph_edge_type( Prefix ) *edge1 = edge_make( v_from, v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );

   if ( edge != NULL )
   {
      HSet_remove_and_dispose( Edge_prefix )( (*dgraph).edges, edge );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_remove_and_dispose_from_to
*/

void
DGraph_edge_remove_and_dispose_from_to( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
)
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   PRECONDITION( "v_from not null", v_from != NULL );
   PRECONDITION( "v_from type ok", ( (*v_from).type == DGRAPH_VERTEX_TYPE ) && ( (*v_from).value_type == Value_Code ) );
   PRECONDITION( "v_to not null", v_to != NULL );
   PRECONDITION( "v_to type ok", ( (*v_to).type == DGRAPH_VERTEX_TYPE ) && ( (*v_to).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_edge_type( Prefix ) *edge = NULL;
   
   // get the edge, if it exists
   DGraph_edge_type( Prefix ) *edge1 = edge_make( v_from, v_to, EDGE_DEFAULT_VALUE );
   if ( HSet_has( Edge_prefix )( (*dgraph).edges, edge1 ) == 1 )
   {
      edge = HSet_item( Edge_prefix )( (*dgraph).edges, edge1 );
   }
   edge_dispose_with_contents( edge1 );

   if ( edge != NULL )
   {
      EDGE_DISPOSE_FUNCTION( (*edge).value );
      HSet_remove_and_dispose( Edge_prefix )( (*dgraph).edges, edge );
   }

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}


/**
   DGraph_wipe_out
*/

void
DGraph_wipe_out( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;
   int32_t is_depth_first = 0;
   
   cursor = (*dgraph).first_cursor;
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
   HSet_wipe_out_and_dispose( Vertex_prefix )( (*dgraph).vertices );
   HSet_wipe_out_and_dispose( Edge_prefix )( (*dgraph).edges );

   // (re)set internal hset cursors
   (*dgraph).first_cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );
   
   (*(*dgraph).first_cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*dgraph).vertices );
   (*(*dgraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );
   (*(*dgraph).first_cursor).is_visited = HSet_make( Vertex_prefix )();
   (*(*dgraph).first_cursor).next_cursor = NULL;
   (*(*dgraph).first_cursor).dgraph = dgraph;
   (*(*dgraph).first_cursor).is_depth_first = is_depth_first;
   MULTITHREAD_MUTEX_INIT( (*(*dgraph).first_cursor).mutex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_wipe_out_and_dispose
*/

void
DGraph_wipe_out_and_dispose( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;
   int32_t is_depth_first = 0;
   
   cursor = (*dgraph).first_cursor;
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
   HSet_start( Edge_prefix )( (*dgraph).edges );
   while( HSet_off( Edge_prefix )( (*dgraph).edges ) == 0 )
   {
      EDGE_DISPOSE_FUNCTION( (* HSet_item_at( Edge_prefix )( (*dgraph).edges ) ).value );
      HSet_forth( Edge_prefix )( (*dgraph).edges );
   }
   HSet_wipe_out_and_dispose( Edge_prefix )( (*dgraph).edges );
   
   HSet_start( Vertex_prefix )( (*dgraph).vertices );
   while( HSet_off( Vertex_prefix )( (*dgraph).vertices ) == 0 )
   {
      DISPOSE_FUNCTION( (* HSet_item_at( Vertex_prefix )( (*dgraph).vertices ) ).value );
      HSet_forth( Vertex_prefix )( (*dgraph).vertices );
   }
   HSet_wipe_out_and_dispose( Vertex_prefix )( (*dgraph).vertices );

   // (re)set internal hset cursors
   (*dgraph).first_cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );
   
   (*(*dgraph).first_cursor).cursor = HSet_cursor_make( Vertex_prefix )( (*dgraph).vertices );
   (*(*dgraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );
   (*(*dgraph).first_cursor).is_visited = HSet_make( Vertex_prefix )();
   (*(*dgraph).first_cursor).next_cursor = NULL;
   (*(*dgraph).first_cursor).dgraph = dgraph;
   (*(*dgraph).first_cursor).is_depth_first = is_depth_first;
   MULTITHREAD_MUTEX_INIT( (*(*dgraph).first_cursor).mutex );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_wipe_out
*/

void
DGraph_edge_wipe_out( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   
   cursor = (*dgraph).first_cursor;
   while( cursor != NULL  )
   {
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      cursor = (*cursor).next_cursor;
   }
   
   // dispose of edges
   HSet_wipe_out_and_dispose( Edge_prefix )( (*dgraph).edges );
   
   // get new cursor to replace cursor eliminated by previous call
   (*(*dgraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

/**
   DGraph_edge_wipe_out_and_dispose
*/

void
DGraph_edge_wipe_out_and_dispose( Prefix )( DGraph_type( Prefix ) *dgraph )
{
   PRECONDITION( "dgraph not null", dgraph != NULL );
   PRECONDITION( "dgraph type ok", ( (*dgraph).type == DGRAPH_TYPE ) && ( (*dgraph).edge_type == Edge_Code ) && ( (*dgraph).value_type == Value_Code ) );
   LOCK( (*dgraph).mutex );
   INVARIANT( dgraph );

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   
   cursor = (*dgraph).first_cursor;
   while( cursor != NULL  )
   {
      HSet_wipe_out( Vertex_prefix )( (*cursor).is_visited );
      cursor = (*cursor).next_cursor;
   }
   
   // dispose of edge values
   HSet_start( Edge_prefix )( (*dgraph).edges );
   while( HSet_off( Edge_prefix )( (*dgraph).edges ) == 0 )
   {
      EDGE_DISPOSE_FUNCTION( (* HSet_item_at( Edge_prefix )( (*dgraph).edges ) ).value );
      HSet_forth( Edge_prefix )( (*dgraph).edges );
   }
   
   // dispose of edges
   HSet_wipe_out_and_dispose( Edge_prefix )( (*dgraph).edges );
   
   // get new cursor to replace cursor eliminated by previous call
   (*(*dgraph).first_cursor).edge_cursor = HSet_cursor_make( Edge_prefix )( (*dgraph).edges );

   INVARIANT( dgraph );
   UNLOCK( (*dgraph).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */


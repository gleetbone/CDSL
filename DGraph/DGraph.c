/**
 @file DGraph.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Directed graph with edges and nodes"

 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2024 Greg Lee

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

#define START_CAPACITY 4

/**
   Vertex structure definition. Holds a value and references to its neighbor vertices
   and the edges that connect them.
*/
#define DGraph_vertex_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_struct )
#define DGraph_vertex_type( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_t )
typedef struct DGraph_vertex_struct( Prefix ) DGraph_vertex_type( Prefix );
struct DGraph_vertex_struct( Prefix )
{
   int32_t _type;
   int32_t _value_type;

   DGraph_type( Prefix ) *dgraph; // the dgraph vertex is associated with

   int32_t id;
   Value value;

   int32_t *neighbors_from;
   int32_t nfcount;
   int32_t nfcapacity;

   int32_t *neighbors_to;
   int32_t ntcount;
   int32_t ntcapacity;
};


/**
   Edge structure definition. Holds a value and references to its start and
   ending vertices. Represents a one way or directed edge.
*/

#define DGraph_edge_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_struct )
#define DGraph_edge_type( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_t )
typedef struct DGraph_edge_struct( Prefix ) DGraph_edge_type( Prefix );
struct DGraph_edge_struct( Prefix )
{
   int32_t _type;
   int32_t _value_type;

   DGraph_type( Prefix ) *dgraph; // the dgraph edge is associated with

   int32_t id;
   Edge value;

   int32_t v_from;
   int32_t v_to;
};


/**
   Directed graph structure definition.
*/

struct DGraph_struct( Prefix )
{
   int32_t _type;
   int32_t _edge_type;
   int32_t _value_type;

   DGraph_vertex_type( Prefix ) **vp;
   int32_t vcount;
   int32_t vcapacity;
   int32_t vnot_filled;

   DGraph_edge_type( Prefix ) **ep;
   int32_t ecount;
   int32_t ecapacity;
   int32_t enot_filled;

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

   int32_t vcursor; // vertex cursor - current index
   int32_t ecursor; // edge cursor - current index

   DGraph_cursor_type( Prefix ) *next_cursor; // pointer to next cursor

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/*
   Local function prototypes
*/

static
DGraph_edge_type( Prefix ) *
get_edge_from_to
(
   DGraph_type( Prefix ) *current,
   int32_t v1_index,
   int32_t v2_index
);

static
void
vertex_dispose
(
   DGraph_vertex_type( Prefix ) **vertex
);

static
void
vertex_deep_dispose
(
   DGraph_vertex_type( Prefix ) **vertex
);

static
void
edge_dispose
(
   DGraph_edge_type( Prefix ) **edge
);

static
void
edge_deep_dispose
(
   DGraph_edge_type( Prefix ) **edge
);

/*
   pointer_insert
*/

static
int32_t
pointer_insert( void ***ap, int32_t *count, int32_t *capacity, int32_t *not_filled, void *p )
{
   PRECONDITION( "ap not NULL", ap != NULL );
   PRECONDITION( "ap not NULL", *ap != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );
   PRECONDITION( "not_filled not NULL", not_filled != NULL );

   int32_t result = -1;
   int32_t new_capacity = 0;
   int32_t i = 0;
   int32_t flag = 0;

   if ( *not_filled == 0 )
   {
      if ( *count < *capacity )
      {
         result = *count;
         *count = *count + 1;
         (*ap)[result] = p;
      }
      else
      {
         new_capacity = 2 * (*capacity);
         (*ap) = realloc( (*ap), new_capacity * sizeof( void * ) );
         CHECK( "ap allocated correctly", (*ap) != NULL );

         memset( &(*ap)[*capacity], 0, (*capacity)*sizeof( void * ) );

         *capacity = new_capacity;
         result = *count;
         *count = *count + 1;
         (*ap)[result] = p;
      }
   }
   else
   {
      for ( i = 0; ( i < *count ) && ( flag == 0 ); i++ )
      {
         if ( (*ap)[i] == ( void * ) 0 )
         {
            result = i;
            flag = 1;
            *not_filled = *not_filled - 1;
            (*ap)[result] = p;
         }
      }
   }

   POSTCONDITION( "return is not negative", result >= 0 );
   return result;
}

/*
   pointer_remove
*/

static
void
pointer_remove(  void **ap, int32_t *count, int32_t *capacity, int32_t *not_filled, int32_t index )
{
   PRECONDITION( "ap not NULL", ap != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );
   PRECONDITION( "not_filled not NULL", not_filled != NULL );
   PRECONDITION( "index not negative", index >= 0 );

   ap[index] = ( void * ) 0;
   *not_filled = *not_filled + 1;

   return;
}

/**
   get_edge_from_to
*/
static
DGraph_edge_type( Prefix ) *
get_edge_from_to
(
   DGraph_type( Prefix ) *current,
   int32_t v1_index,
   int32_t v2_index
)
{
   DGraph_edge_type( Prefix ) *result = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   int32_t i = 0;

   for( i = 0; ( i < (*current).ecount ) && ( result == NULL ); i++ )
   {
      edge = (*current).ep[i];
      if ( edge != NULL )
      {
         if (
            ( (*edge).v_from == v1_index )
            &&
            ( (*edge).v_to == v2_index )
         )
         {
            result = edge;
         }

      }
   }

   return result;
}

/*
   index_first
*/

static
int32_t
index_first( int32_t *ip, int32_t *count, int32_t *capacity )
{
   PRECONDITION( "ip not NULL", ip != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );

   int32_t result = 0;

   result = ip[0];

   POSTCONDITION( "return is not negative", result >= 0 );

   return result;
}

/*
   index_put_last
*/

static
void
index_put_last( int32_t **ip, int32_t *count, int32_t *capacity, int32_t index )
{
   PRECONDITION( "ip not NULL", ip != NULL );
   PRECONDITION( "ip not NULL", *ip != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );
   PRECONDITION( "index is not negative", index >= 0 );

   int32_t new_capacity = 0;

   if ( *count < *capacity )
   {
      (*ip)[*count] = index;
      *count = *count + 1;
   }
   else
   {
      new_capacity = 2 * (*capacity);
      (*ip) = realloc( (*ip), new_capacity * sizeof( int32_t ) );
      CHECK( "ip allocated correctly", (*ip) != NULL );

      memset( &(*ip)[*capacity], 0xFF, (*capacity)*sizeof( int32_t ) );

      *capacity = new_capacity;
      (*ip)[*count] = index;
      *count = *count + 1;
   }

   return;
}

/*
   index_remove
*/

static
void
index_remove( int32_t *ip, int32_t *count, int32_t *capacity, int32_t index )
{
   PRECONDITION( "ip not NULL", ip != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "count positive", *count > 0 );
   PRECONDITION( "capacity not NULL", capacity != NULL );
   PRECONDITION( "index is not negative", index >= 0 );

   int32_t i = 0;
   int32_t flag = 0;

   for ( i = 0; ( i < *count ) && ( flag == 0 ); i++ )
   {
      if ( ip[i] == index )
      {
         if ( i == *count - 1 )
         {
            ip[i] = -1;
            *count = *count - 1;
         }
         else
         {
            memmove( &ip[i], &ip[i + 1], ( *count - 1 )*sizeof( int32_t ) );
            ip[*count - 1] = -1;
            *count = *count - 1;
         }
         flag = 1;
      }
   }

   return;
}

/*
   index_remove_first
*/

static
void
index_remove_first( int32_t *ip, int32_t *count, int32_t *capacity )
{
   PRECONDITION( "ip not NULL", ip != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );

   int32_t i = 0;
   int32_t flag = 0;

   for ( i = 0; ( i < *count ) && ( flag == 0 ); i++ )
   {
      if ( *count == 1 )
      {
         ip[0] = -1;
         *count = 0;
      }
      else if ( *count > 1 )
      {
         memmove( &ip[0], &ip[1], ( *count - 1 )*sizeof( int32_t ) );
         ip[*count - 1] = -1;
         *count = *count - 1;
      }
      flag = 1;
   }

   return;
}

/*
   index_remove_last

   not used in this class
*/
/*
static
void
index_remove_last( int32_t *ip, int32_t *count, int32_t *capacity )
{
   PRECONDITION( "ip not NULL", ip != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );

   int32_t i = 0;
   int32_t flag = 0;

   for ( i = 0; ( i < *count ) && ( flag == 0 ); i++ )
   {
      if ( *count >= 1 )
      {
         ip[*count - 1] = -1;
         *count = *count - 1;
      }
      flag = 1;
   }

   return;
}
*/

/*
   index_has
*/

static
int32_t
index_has( int32_t *ip, int32_t *count, int32_t *capacity, int32_t index )
{
   PRECONDITION( "ip not NULL", ip != NULL );
   PRECONDITION( "count not NULL", count != NULL );
   PRECONDITION( "capacity not NULL", capacity != NULL );
   PRECONDITION( "index is not negative", index >= 0 );

   int32_t i = 0;
   int32_t flag = 0;
   int32_t result = 0;

   for ( i = 0; ( i < *count ) && ( flag == 0 ); i++ )
   {
      if ( ip[i] == index )
      {
         result = 1;
         flag = 1;
      }
   }

   return result;
}

/**
   find_connected_vertices_breadth_first

   walk through the graph, finding vertices that are connected to vertex
   breadth first search

   @param current the dgraph
   @param vertex_id the id of the vertex to start from - will be included in result
   @param queue queue of vertex ids
   @param qcount number of vertex ids in queue
   @param qcapacity size of vertex id queue
   @param is_visited list of vertex ids already looked at
   @param ivcount number or vertices already looked at
   @param ivcapacity size of already looked at list
*/

static
void
find_connected_vertices_breadth_first
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t **queue,
   int32_t *qcount,
   int32_t *qcapacity,
   int32_t **is_visited,
   int32_t *ivcount,
   int32_t *ivcapacity
)
{
   DGraph_vertex_type( Prefix ) *v = NULL;
   int32_t id = 0;
   int32_t i = 0;

   // put vertex into visited set
   index_put_last( is_visited, ivcount, ivcapacity, vertex_id );

   // put vertex into queue
   index_put_last( queue, qcount, qcapacity, vertex_id );

   // work on contents of the queue
   while( *qcount > 0 )
   {
      // get first vertex in queue
      id = index_first( *queue, qcount, qcapacity );
      v = (*current).vp[id];
      index_remove_first( *queue, qcount, qcapacity );

      // put adjacent vertices into is_visited hash set
      for( i = 0; i < (*v).ntcount; i++ )
      {
         id = (*v).neighbors_to[i];
         if ( index_has( *is_visited, ivcount, ivcapacity, id ) == 0 )
         {
            index_put_last( is_visited, ivcount, ivcapacity, id );
            index_put_last( queue, qcount, qcapacity, id );
         }
      }
   }

   return;
}


/**
   find_connected_vertices_depth_first

   walk through the graph, finding vertices that are connected to vertex
   depth first search

   @param current the dgraph
   @param vertex_id the id of the vertex to start from - will be included in result
   @param is_visited list of vertex ids already looked at
   @param ivcount number or vertices already looked at
   @param ivcapacity size of already looked at list
*/

static
void
find_connected_vertices_depth_first
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t **is_visited,
   int32_t *ivcount,
   int32_t *ivcapacity
)
{
   DGraph_vertex_type( Prefix ) *v = NULL;
   int32_t id = 0;
   int32_t i = 0;

   if ( index_has( *is_visited, ivcount, ivcapacity, vertex_id ) == 0 )
   {

      // put vertex id into visited set
      index_put_last( is_visited, ivcount, ivcapacity, vertex_id );

      // get vertex
      v = (*current).vp[vertex_id];

      // put connected vertices into is_visited hash set
      for( i = 0; i < (*v).ntcount; i++ )
      {
         id = (*v).neighbors_to[i];
         if ( index_has( *is_visited, ivcount, ivcapacity, id ) == 0 )
         {
            // if not visited, recurse into it
            find_connected_vertices_depth_first
            (
               current,
               id,
               is_visited,
               ivcount,
               ivcapacity
            );
         }
      }

   }

   return;
}




/**
   vertex_dispose
*/

static
void
vertex_dispose
(
   DGraph_vertex_type( Prefix ) **vertex
)
{
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex not null", *vertex != NULL );
   PRECONDITION( "vertex type ok", ( (**vertex)._type == DGRAPH_VERTEX_TYPE ) && ( (**vertex)._value_type == Value_Code ) );

   DGraph_type( Prefix ) *current = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   int32_t i = 0;

   // get the dgraph
   current = (**vertex).dgraph;

   // remove edges from another to vertex
   for( i = 0; i < (*current).ecount; i++ )
   {
      e = (*current).ep[i];
      if ( e != NULL )
      {
         if ( (*e).v_to == (**vertex).id )
         {
            edge_dispose( &e );
         }
      }
   }

   // remove edges from vertex to another
   for( i = 0; i < (*current).ecount; i++ )
   {
      e = (*current).ep[i];
      if ( e != NULL )
      {
         if ( (*e).v_from == (**vertex).id )
         {
            edge_dispose( &e );
         }
      }
   }

   // dispose of vertex neighbors_from index array
   free( (**vertex).neighbors_from );

   // dispose of vertex neighbors_to index array
   free( (**vertex).neighbors_to );

   // do not dispose of value

   // get the vertex id
   i = (**vertex).id;

   // free the vertex
   free(*vertex);

   // set to null
   *vertex = NULL;

   // remove vertex from graph
   pointer_remove
   (
      ( void ** ) (*current).vp,
      &(*current).vcount,
      &(*current).vcapacity,
      &(*current).vnot_filled,
      i
   );

   return;

}

/**
   vertex_deep_dispose
*/

static
void
vertex_deep_dispose
(
   DGraph_vertex_type( Prefix ) **vertex
)
{
   PRECONDITION( "vertex not null", vertex != NULL );
   PRECONDITION( "vertex not null", *vertex != NULL );
   PRECONDITION( "vertex type ok", ( (**vertex)._type == DGRAPH_VERTEX_TYPE ) && ( (**vertex)._value_type == Value_Code ) );

   DGraph_type( Prefix ) *current = NULL;
   DGraph_edge_type( Prefix ) *e = NULL;
   int32_t i = 0;

   // get the dgraph
   current = (**vertex).dgraph;

   // remove edges from another to vertex
   for( i = 0; i < (*current).ecount; i++ )
   {
      e = (*current).ep[i];
      if ( e != NULL )
      {
         if ( (*e).v_to == (**vertex).id )
         {
            edge_deep_dispose( &e );
         }
      }
   }

   // remove edges from vertex to another
   for( i = 0; i < (*current).ecount; i++ )
   {
      e = (*current).ep[i];
      if ( e != NULL )
      {
         if ( (*e).v_from == (**vertex).id )
         {
            edge_deep_dispose( &e );
         }
      }
   }

   // dispose of vertex neighbors_from index array
   free( (**vertex).neighbors_from );

   // dispose of vertex neighbors_to index array
   free( (**vertex).neighbors_to );

   // dispose of value
   VERTEX_VALUE_DEEP_DISPOSE_FUNCTION( (**vertex).value );

   // get the vertex id
   i = (**vertex).id;

   // free the vertex
   free(*vertex);

   // set to null
   *vertex = NULL;

   // remove vertex from graph
   pointer_remove
   (
      ( void ** ) (*current).vp,
      &(*current).vcount,
      &(*current).vcapacity,
      &(*current).vnot_filled,
      i
   );

   return;

}

/**
   edge_dispose
*/

static
void
edge_dispose
(
   DGraph_edge_type( Prefix ) **edge
)
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge not null", *edge != NULL );
   PRECONDITION( "edge type ok", ( (**edge)._type == DGRAPH_EDGE_TYPE ) && ( (**edge)._value_type == Edge_Code ) );

   DGraph_type( Prefix ) *current = NULL;
   int32_t i = 0;
   DGraph_vertex_type( Prefix ) *vertex = NULL;

   // get the dgraph
   current = (**edge).dgraph;

   // remove edge vertex_to from edge vertex_from's neighbors_to list
   vertex = (*current).vp[ (**edge).v_from ];

   index_remove
   (
      (*vertex).neighbors_to,
      &(*vertex).ntcount,
      &(*vertex).ntcapacity,
      (**edge).v_to
   );

   // remove edge vertex_from from edge vertex_to's neighbors_from list
   vertex = (*current).vp[ (**edge).v_to ];

   index_remove
   (
      (*vertex).neighbors_from,
      &(*vertex).nfcount,
      &(*vertex).nfcapacity,
      (**edge).v_from
   );

   // do not dispose of value

   // do not dispose of start and end vertex

   // do not dispose of value

   // get the edge id
   i = (**edge).id;

   // dispose of edge
   free(*edge);

   // set to NULL
   *edge = NULL;

   // remove edge from graph
   pointer_remove
   (
      ( void ** ) (*current).ep,
      &(*current).ecount,
      &(*current).ecapacity,
      &(*current).enot_filled,
      i
   );

   return;
}

/**
   edge_deep_dispose
*/

static
void
edge_deep_dispose
(
   DGraph_edge_type( Prefix ) **edge
)
{
   PRECONDITION( "edge not null", edge != NULL );
   PRECONDITION( "edge not null", *edge != NULL );
   PRECONDITION( "edge type ok", ( (**edge)._type == DGRAPH_EDGE_TYPE ) && ( (**edge)._value_type == Edge_Code ) );

   DGraph_type( Prefix ) *current = NULL;
   int32_t i = 0;
   DGraph_vertex_type( Prefix ) *vertex = NULL;

   // get the dgraph
   current = (**edge).dgraph;

   // remove edge vertex_to from edge vertex_from's neighbors_to list
   vertex = (*current).vp[ (**edge).v_from ];

   index_remove
   (
      (*vertex).neighbors_to,
      &(*vertex).ntcount,
      &(*vertex).ntcapacity,
      (**edge).v_to
   );

   // remove edge vertex_from from edge vertex_to's neighbors_from list
   vertex = (*current).vp[ (**edge).v_to ];

   index_remove
   (
      (*vertex).neighbors_from,
      &(*vertex).nfcount,
      &(*vertex).nfcapacity,
      (**edge).v_from
   );

   // dispose of value
   EDGE_VALUE_DEEP_DISPOSE_FUNCTION( (**edge).value );

   // get the edge id
   i = (**edge).id;

   // dispose of edge
   free(*edge);

   // set to NULL
   *edge = NULL;

   // remove edge from graph
   pointer_remove
   (
      ( void ** ) (*current).ep,
      &(*current).ecount,
      &(*current).ecapacity,
      &(*current).enot_filled,
      i
   );


   return;
}

/*
   cursor_vertex_off
*/

static
int32_t
cursor_vertex_off( DGraph_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;

   if ( (*cursor).vcursor >= ( *(*cursor).dgraph ).vcount )
   {
      result = 1;
   }

   return result;
}

/*
   cursor_edge_off
*/

static
int32_t
cursor_edge_off( DGraph_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;

   if ( (*cursor).ecursor >= ( *(*cursor).dgraph ).ecount )
   {
      result = 1;
   }

   return result;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
edge_from_and_to_vertices_exist( DGraph_type( Prefix ) *current )
{
   int32_t result = 1;
   DGraph_edge_type( Prefix ) *edge = NULL;
   int32_t i = 0;

   for( i = 0; ( i < (*current).ecount ) && ( result == 1 ); i++ )
   {
      if ( (*current).ep[i] != NULL )
      {
         edge = (*current).ep[i];

         if ( result == 1 )
         {
            result = 0;
            if ( (*current).vp[ (*edge).v_from ] != NULL )
            {
               result = 1;
            }
         }

         if ( result == 1 )
         {
            result = 0;
            if ( (*current).vp[ (*edge).v_to ] != NULL )
            {
               result = 1;
            }
         }
      }
   }

   return result;
}

static
int32_t
edge_implies_vertex_neighbor_from_and_to( DGraph_type( Prefix ) *current )
{
   int32_t result = 1;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   int32_t i = 0;

   for( i = 0; ( i < (*current).ecount ) && ( result == 1 ); i++ )
   {
      if ( (*current).ep[i] != NULL )
      {
         edge = (*current).ep[i];

         // edge start vertex
         if ( result == 1 )
         {
            result = 0;
            if ( (*current).vp[ (*edge).v_from ] != NULL )
            {
               result = 1;
            }
         }

         if ( result == 1 )
         {
            result = 0;
            vertex = (*current).vp[ (*edge).v_from ];
            result
               = index_has
                 (
                    (*vertex).neighbors_to,
                    &(*vertex).ntcount,
                    &(*vertex).ntcapacity,
                    (*edge).v_to
                 );
         }

         // edge end vertex
         if ( result == 1 )
         {
            if ( (*current).vp[ (*edge).v_to ] != NULL )
            {
               result = 1;
            }
         }

         if ( result == 1 )
         {
            result = 0;
            vertex = (*current).vp[ (*edge).v_to ];
            result
               = index_has
                 (
                    (*vertex).neighbors_from,
                    &(*vertex).nfcount,
                    &(*vertex).nfcapacity,
                    (*edge).v_from
                 );
         }

      }
   }

   return result;
}


static
int32_t
vertex_neighbor_from_and_to_implies_edge( DGraph_type( Prefix ) *current )
{
   int32_t result = 1;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t vertex_from = 0;
   int32_t vertex_to = 0;

   for( i = 0; ( i < (*current).vcount ) && ( result == 1 ); i++ )
   {
      if ( (*current).vp[i] != NULL )
      {
         vertex = (*current).vp[i];

         // neighbors_from
         for( j = 0; ( j < (*vertex).nfcount ) && ( result == 1 ); j++ )
         {
            vertex_from = (*vertex).neighbors_from[j];
            edge = get_edge_from_to( current, vertex_from, (*vertex).id );
            if ( result == 1 )
            {
               result = 0;
               if ( edge != NULL )
               {
                  result = 1;
               }
            }
         }

         // neighbors_to
         for( j = 0; ( j < (*vertex).ntcount ) && ( result == 1 ); j++ )
         {
            vertex_to = (*vertex).neighbors_to[j];
            edge = get_edge_from_to( current, (*vertex).id, vertex_to );
            if ( result == 1 )
            {
               result = 0;
               if ( edge != NULL )
               {
                  result = 1;
               }
            }
         }
      }
   }

   return result;
}


static
int32_t
cursors_ok( DGraph_type( Prefix ) *current )
{
   int32_t result = 1;

   DGraph_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while ( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).dgraph == current );
      cursor = (*cursor).next_cursor;
   }

   return result;
}


static
void invariant( DGraph_type( Prefix ) *current )
{
   assert( ( ( void ) "edge from and to vertices exist", edge_from_and_to_vertices_exist( current ) ) );
   assert( ( ( void ) "edge implies vertex neighbor from and to", edge_implies_vertex_neighbor_from_and_to( current ) ) );
   assert( ( ( void ) "vertex neighbor from and to implies edge", vertex_neighbor_from_and_to_implies_edge( current ) ) );
   assert( ( ( void ) "cursors OK", cursors_ok( current ) ) );
   return;
}

#endif


/**
   DGraph_make
*/

DGraph_type( Prefix ) *
DGraph_make( Prefix )( void )
{
   // allocate dgraph struct
   DGraph_type( Prefix ) *result
      = ( DGraph_type( Prefix ) * ) calloc( 1, sizeof( DGraph_type( Prefix ) ) );
   CHECK( "result allocated successfully", result != NULL );

   // set type codes
   (*result)._type = DGRAPH_TYPE;
   (*result)._edge_type = Edge_Code;
   (*result)._value_type = Value_Code;

   // init vertex array
   (*result).vp = calloc( START_CAPACITY, sizeof( void * ) );
   CHECK( "(*result).vp allocated successfully", (*result).vp != NULL );
   (*result).vcount = 0;
   (*result).vcapacity = START_CAPACITY;
   (*result).vnot_filled = 0;

   // init edge array
   (*result).ep = calloc( START_CAPACITY, sizeof( void * ) );
   CHECK( "(*result).ep allocated successfully", (*result).ep != NULL );
   (*result).ecount = 0;
   (*result).ecapacity = START_CAPACITY;
   (*result).enot_filled = 0;

   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated successfully", cursor != NULL );

   // set dgraph in cursor
   (*cursor).dgraph = result;

   // set internal cursors
   (*cursor).vcursor = 0;
   (*cursor).ecursor = 0;

   // set next cursor to null
   (*cursor).next_cursor = NULL;

   // set dgraph first cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Dgraph_make_cursor
*/

DGraph_cursor_type( Prefix ) *
DGraph_make_cursor( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DGraph_cursor_type( Prefix ) *result = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;

   // allocate cursor struct
   result
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );
   CHECK( "result allocated successfully", result != NULL );

   // set dgraph in cursor
   (*result).dgraph = current;

   // init internal hset cursors
   (*result).vcursor = 0;
   (*result).ecursor = 0;

   // set next cursor to null
   (*result).next_cursor = NULL;

   // place into current at end of cursor list
   c = (*current).first_cursor;

   while ( (*c).next_cursor != NULL )
   {
      c = (*c).next_cursor;
   }

   (*c).next_cursor = result;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_is_equal
*/

int32_t
DGraph_is_equal( Prefix )( DGraph_type( Prefix ) *current, DGraph_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DGRAPH_TYPE ) && ( (*other)._edge_type == Edge_Code ) && ( (*other)._value_type == Value_Code ) );

   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   INVARIANT( current );
   INVARIANT( other );

   DGraph_vertex_type( Prefix ) *vertex = NULL;
   int32_t result = 1;
   int32_t i = 0;
   int32_t j = 0;

   // check vertices
   if ( (*current).vcount != (*other).vcount )
   {
      result = 0;
   }
   else
   {

      // vertex null in current implies vertex null in other
      for ( i = 0; i < (*current).vcount; i++ )
      {
         if ( ( (*current).vp[i] == NULL ) && ( (*other).vp[i] != NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).vp[i] != NULL ) && ( (*other).vp[i] == NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).vp[i] != NULL ) && ( (*other).vp[i] != NULL ) )
         {
            // neighbors_from count same
            if ( ( *(*current).vp[i] ).nfcount != ( *(*other).vp[i] ).nfcount )
            {
               result = 0;
            }

            // neighbors_from same
            for ( j = 0; j < ( *(*current).vp[i] ).nfcount; j++ )
            {
               vertex = (*other).vp[i];
               if (
                  index_has
                  (
                     (*vertex).neighbors_from,
                     &(*vertex).nfcount,
                     &(*vertex).nfcapacity,
                     ( *(*current).vp[i] ).neighbors_from[j]
                  )
                  == 0
               )
               {
                  result = 0;
               }
            }

            // neighbors_to count same
            if ( ( *(*current).vp[i] ).ntcount != ( *(*other).vp[i] ).ntcount )
            {
               result = 0;
            }

            // neighbors_to same
            for ( j = 0; j < ( *(*current).vp[i] ).ntcount; j++ )
            {
               vertex = (*other).vp[i];
               if (
                  index_has
                  (
                     (*vertex).neighbors_to,
                     &(*vertex).ntcount,
                     &(*vertex).ntcapacity,
                     ( *(*current).vp[i] ).neighbors_to[j]
                  )
                  == 0
               )
               {
                  result = 0;
               }
            }

            // value
            if ( ( *(*current).vp[i] ).value != ( *(*other).vp[i] ).value )
            {
               result = 0;
            }

         }
      }
   }

   // check edges
   if ( (*current).ecount != (*other).ecount )
   {
      result = 0;
   }
   else
   {
      // edge null in current implies edge null in other
      for ( i = 0; i < (*current).ecount; i++ )
      {
         if ( ( (*current).ep[i] == NULL ) && ( (*other).ep[i] != NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).ep[i] != NULL ) && ( (*other).ep[i] == NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).ep[i] != NULL ) && ( (*other).ep[i] != NULL ) )
         {
            // value
            if ( ( *(*current).ep[i] ).value != ( *(*other).ep[i] ).value )
            {
               result = 0;
            }
         }
      }
   }


   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   DGraph_is_deep_equal
*/

int32_t
DGraph_is_deep_equal( Prefix )( DGraph_type( Prefix ) *current, DGraph_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DGRAPH_TYPE ) && ( (*other)._edge_type == Edge_Code ) && ( (*other)._value_type == Value_Code ) );

   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   INVARIANT( current );
   INVARIANT( other );

   DGraph_vertex_type( Prefix ) *vertex = NULL;
   int32_t result = 1;
   int32_t i = 0;
   int32_t j = 0;

   // check vertices
   if ( (*current).vcount != (*other).vcount )
   {
      result = 0;
   }
   else
   {

      // vertex null in current implies vertex null in other
      for ( i = 0; i < (*current).vcount; i++ )
      {
         if ( ( (*current).vp[i] == NULL ) && ( (*other).vp[i] != NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).vp[i] != NULL ) && ( (*other).vp[i] == NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).vp[i] != NULL ) && ( (*other).vp[i] != NULL ) )
         {
            // neighbors_from count same
            if ( ( *(*current).vp[i] ).nfcount != ( *(*other).vp[i] ).nfcount )
            {
               result = 0;
            }

            // neighbors_from same
            for ( j = 0; j < ( *(*current).vp[i] ).nfcount; j++ )
            {
               vertex = (*other).vp[i];
               if (
                  index_has
                  (
                     (*vertex).neighbors_from,
                     &(*vertex).nfcount,
                     &(*vertex).nfcapacity,
                     ( *(*current).vp[i] ).neighbors_from[j]
                  )
                  == 0
               )
               {
                  result = 0;
               }
            }

            // neighbors_to count same
            if ( ( *(*current).vp[i] ).ntcount != ( *(*other).vp[i] ).ntcount )
            {
               result = 0;
            }

            // neighbors_to same
            for ( j = 0; j < ( *(*current).vp[i] ).ntcount; j++ )
            {
               vertex = (*other).vp[i];
               if (
                  index_has
                  (
                     (*vertex).neighbors_to,
                     &(*vertex).ntcount,
                     &(*vertex).ntcapacity,
                     ( *(*current).vp[i] ).neighbors_to[j]
                  )
                  == 0
               )
               {
                  result = 0;
               }
            }

            // value
            if (
               VERTEX_VALUE_DEEP_EQUAL_FUNCTION
               (
                  ( *(*current).vp[i] ).value,
                  ( *(*other).vp[i] ).value
               )
               != 1
            )
            {
               result = 0;
            }

         }
      }
   }

   // check edges
   if ( (*current).ecount != (*other).ecount )
   {
      result = 0;
   }
   else
   {
      // edge null in current implies edge null in other
      for ( i = 0; i < (*current).ecount; i++ )
      {
         if ( ( (*current).ep[i] == NULL ) && ( (*other).ep[i] != NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).ep[i] != NULL ) && ( (*other).ep[i] == NULL ) )
         {
            result = 0;
         }
         else if ( ( (*current).ep[i] != NULL ) && ( (*other).ep[i] != NULL ) )
         {
            // value
            if (
               EDGE_VALUE_DEEP_EQUAL_FUNCTION
               (
                  ( *(*current).ep[i] ).value,
                  ( *(*other).ep[i] ).value
               )
               != 1
            )
            {
               result = 0;
            }
         }
      }
   }


   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return result;
}


/**
   DGraph_copy
*/

void
DGraph_copy( Prefix )( DGraph_type( Prefix ) *current, DGraph_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DGRAPH_TYPE ) && ( (*other)._edge_type == Edge_Code ) && ( (*other)._value_type == Value_Code ) );

   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   INVARIANT( current );
   INVARIANT( other );

   DGraph_vertex_type( Prefix ) *vertex = NULL;
   DGraph_vertex_type( Prefix ) *vertex1 = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_edge_type( Prefix ) *edge1 = NULL;
   int32_t i = 0;

   // first, empty current
   for ( i = 0; i < (*current).vcount; i++ )
   {

      if ( (*current).vp[i] != NULL )
      {
         // get vertex
         vertex = (*current).vp[i];

         // dispose vertex
         vertex_deep_dispose( &vertex );
      }
   }

   // now copy vertices using the same values
   for ( i = 0; i < (*other).vcount; i++ )
   {

      if ( (*other).vp[i] != NULL )
      {
         // get vertex
         vertex1 = (*other).vp[i];

         // allocate vertex
         vertex = ( DGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( DGraph_vertex_type( Prefix ) ) );
         CHECK( "vertex allocated correctly", vertex != NULL );

         // set type
         (*vertex)._type = DGRAPH_VERTEX_TYPE;
         (*vertex)._value_type = Value_Code;

         // set dgraph
         (*vertex).dgraph = current;

         // set value
         (*vertex).value = (*vertex1).value;

         // initialize neighbors_from
         (*vertex).neighbors_from = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_from allocated correctly", (*vertex).neighbors_from != NULL );
         (*vertex).nfcount = 0;
         (*vertex).nfcapacity = START_CAPACITY;

         // initialize neighbors_to
         (*vertex).neighbors_to = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_to allocated correctly", (*vertex).neighbors_to != NULL );
         (*vertex).ntcount = 0;
         (*vertex).ntcapacity = START_CAPACITY;

         // put vertex into current, and set its index
         (*vertex).id
            = pointer_insert
              (
                 ( void *** ) & ( (*current).vp ),
                 &(*current).vcount,
                 &(*current).vcapacity,
                 &(*current).vnot_filled,
                 vertex
              );

      }
   }

   // now copy edges using the same values
   for ( i = 0; i < (*other).ecount; i++ )
   {

      if ( (*other).ep[i] != NULL )
      {
         // get edge
         edge1 = (*other).ep[i];

         // allocate edge
         edge = ( DGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( DGraph_edge_type( Prefix ) ) );
         CHECK( "edge allocated correctly", edge != NULL );

         // set type
         (*edge)._type = DGRAPH_EDGE_TYPE;
         (*edge)._value_type = Edge_Code;

         // set dgraph
         (*edge).dgraph = current;

         // set value
         (*edge).value = (*edge1).value;

         // set from and to
         (*edge).v_from = (*edge1).v_from;
         (*edge).v_to = (*edge1).v_to;

         // put edge into DGraph, and set its index
         (*edge).id
            = pointer_insert
              (
                 ( void *** ) & ( (*current).ep ),
                 &(*current).ecount,
                 &(*current).ecapacity,
                 &(*current).enot_filled,
                 edge
              );

         // add v_to to v_from's neighbors_to
         vertex = (*current).vp[(*edge).v_from];
         index_put_last( &( (*vertex).neighbors_to ), &(*vertex).ntcount, &(*vertex).ntcapacity, (*edge).v_to );

         // add v_from to v_to's neighbors_from
         vertex = (*current).vp[(*edge).v_to];
         index_put_last( &( (*vertex).neighbors_from ), &(*vertex).nfcount, &(*vertex).nfcapacity, (*edge).v_from );
      }
   }


   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}


/**
   DGraph_deep_copy
*/

void
DGraph_deep_copy( Prefix )( DGraph_type( Prefix ) *current, DGraph_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DGRAPH_TYPE ) && ( (*other)._edge_type == Edge_Code ) && ( (*other)._value_type == Value_Code ) );

   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   INVARIANT( current );
   INVARIANT( other );

   DGraph_vertex_type( Prefix ) *vertex = NULL;
   DGraph_vertex_type( Prefix ) *vertex1 = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_edge_type( Prefix ) *edge1 = NULL;
   int32_t i = 0;

   // first, empty current
   for ( i = 0; i < (*current).vcount; i++ )
   {

      if ( (*current).vp[i] != NULL )
      {
         // get vertex
         vertex = (*current).vp[i];

         // dispose vertex
         vertex_deep_dispose( &vertex );
      }
   }

   // now copy vertices using the same values
   for ( i = 0; i < (*other).vcount; i++ )
   {

      if ( (*other).vp[i] != NULL )
      {
         // get vertex
         vertex1 = (*other).vp[i];

         // allocate vertex
         vertex = ( DGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( DGraph_vertex_type( Prefix ) ) );
         CHECK( "vertex allocated correctly", vertex != NULL );

         // set type
         (*vertex)._type = DGRAPH_VERTEX_TYPE;
         (*vertex)._value_type = Value_Code;

         // set dgraph
         (*vertex).dgraph = current;

         // set value
         (*vertex).value = VERTEX_VALUE_DEEP_CLONE_FUNCTION( (*vertex1).value );

         // initialize neighbors_from
         (*vertex).neighbors_from = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_from allocated correctly", (*vertex).neighbors_from != NULL );
         (*vertex).nfcount = 0;
         (*vertex).nfcapacity = START_CAPACITY;

         // initialize neighbors_to
         (*vertex).neighbors_to = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_to allocated correctly", (*vertex).neighbors_to != NULL );
         (*vertex).ntcount = 0;
         (*vertex).ntcapacity = START_CAPACITY;

         // put vertex into current, and set its index
         (*vertex).id
            = pointer_insert
              (
                 ( void *** ) & ( (*current).vp ),
                 &(*current).vcount,
                 &(*current).vcapacity,
                 &(*current).vnot_filled,
                 vertex
              );

      }
   }

   // now copy edges using the same values
   for ( i = 0; i < (*other).ecount; i++ )
   {

      if ( (*other).ep[i] != NULL )
      {
         // get edge
         edge1 = (*other).ep[i];

         // allocate edge
         edge = ( DGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( DGraph_edge_type( Prefix ) ) );
         CHECK( "edge allocated correctly", edge != NULL );

         // set type
         (*edge)._type = DGRAPH_EDGE_TYPE;
         (*edge)._value_type = Edge_Code;

         // set dgraph
         (*edge).dgraph = current;

         // set value
         (*edge).value = EDGE_VALUE_DEEP_CLONE_FUNCTION( (*edge1).value );

         // set from and to
         (*edge).v_from = (*edge1).v_from;
         (*edge).v_to = (*edge1).v_to;

         // put edge into DGraph, and set its index
         (*edge).id
            = pointer_insert
              (
                 ( void *** ) & ( (*current).ep ),
                 &(*current).ecount,
                 &(*current).ecapacity,
                 &(*current).enot_filled,
                 edge
              );

         // add v_to to v_from's neighbors_to
         vertex = (*current).vp[(*edge).v_from];
         index_put_last( &( (*vertex).neighbors_to ), &(*vertex).ntcount, &(*vertex).ntcapacity, (*edge).v_to );

         // add v_from to v_to's neighbors_from
         vertex = (*current).vp[(*edge).v_to];
         index_put_last( &( (*vertex).neighbors_from ), &(*vertex).nfcount, &(*vertex).nfcapacity, (*edge).v_from );
      }
   }


   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   DGraph_clone
*/

DGraph_type( Prefix ) *
DGraph_clone( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );

   LOCK( (*current).mutex );

   INVARIANT( current );

   DGraph_type( Prefix ) *result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   DGraph_vertex_type( Prefix ) *vertex1 = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_edge_type( Prefix ) *edge1 = NULL;
   int32_t i = 0;

   // allocate dgraph struct
   result = ( DGraph_type( Prefix ) * ) calloc( 1, sizeof( DGraph_type( Prefix ) ) );
   CHECK( "result allocated successfully", result != NULL );

   // set type codes
   (*result)._type = DGRAPH_TYPE;
   (*result)._edge_type = Edge_Code;
   (*result)._value_type = Value_Code;

   // init vertex array
   (*result).vp = calloc( START_CAPACITY, sizeof( void * ) );
   CHECK( "(*result).vp allocated successfully", (*result).vp != NULL );
   (*result).vcount = 0;
   (*result).vcapacity = START_CAPACITY;
   (*result).vnot_filled = 0;

   // init edge array
   (*result).ep = calloc( START_CAPACITY, sizeof( void * ) );
   CHECK( "(*result).ep allocated successfully", (*result).ep != NULL );
   (*result).ecount = 0;
   (*result).ecapacity = START_CAPACITY;
   (*result).enot_filled = 0;

   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated successfully", cursor != NULL );

   // set dgraph in cursor
   (*cursor).dgraph = result;

   // set internal cursors
   (*cursor).vcursor = 0;
   (*cursor).ecursor = 0;

   // set next cursor to null
   (*cursor).next_cursor = NULL;

   // set dgraph first cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // now copy vertices using the same values
   for ( i = 0; i < (*current).vcount; i++ )
   {

      if ( (*current).vp[i] != NULL )
      {
         // get vertex
         vertex1 = (*current).vp[i];

         // allocate vertex
         vertex = ( DGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( DGraph_vertex_type( Prefix ) ) );
         CHECK( "vertex allocated correctly", vertex != NULL );

         // set type
         (*vertex)._type = DGRAPH_VERTEX_TYPE;
         (*vertex)._value_type = Value_Code;

         // set dgraph
         (*vertex).dgraph = result;

         // set value
         (*vertex).value = (*vertex1).value;

         // initialize neighbors_from
         (*vertex).neighbors_from = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_from allocated correctly", (*vertex).neighbors_from != NULL );
         (*vertex).nfcount = 0;
         (*vertex).nfcapacity = START_CAPACITY;

         // initialize neighbors_to
         (*vertex).neighbors_to = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_to allocated correctly", (*vertex).neighbors_to != NULL );
         (*vertex).ntcount = 0;
         (*vertex).ntcapacity = START_CAPACITY;

         // put vertex into result, and set its index
         (*vertex).id
            = pointer_insert
              (
                 ( void *** ) & ( (*result).vp ),
                 &(*result).vcount,
                 &(*result).vcapacity,
                 &(*result).vnot_filled,
                 vertex
              );

      }
   }

   // now copy edges using the same values
   for ( i = 0; i < (*current).ecount; i++ )
   {

      if ( (*current).ep[i] != NULL )
      {
         // get edge
         edge1 = (*current).ep[i];

         // allocate edge
         edge = ( DGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( DGraph_edge_type( Prefix ) ) );
         CHECK( "edge allocated correctly", edge != NULL );

         // set type
         (*edge)._type = DGRAPH_EDGE_TYPE;
         (*edge)._value_type = Edge_Code;

         // set dgraph
         (*edge).dgraph = result;

         // set value
         (*edge).value = (*edge1).value;

         // set from and to
         (*edge).v_from = (*edge1).v_from;
         (*edge).v_to = (*edge1).v_to;

         // put edge into DGraph, and set its index
         (*edge).id
            = pointer_insert
              (
                 ( void *** ) & ( (*result).ep ),
                 &(*result).ecount,
                 &(*result).ecapacity,
                 &(*result).enot_filled,
                 edge
              );

         // add v_to to v_from's neighbors_to
         vertex = (*result).vp[(*edge).v_from];
         index_put_last( &( (*vertex).neighbors_to ), &(*vertex).ntcount, &(*vertex).ntcapacity, (*edge).v_to );

         // add v_from to v_to's neighbors_from
         vertex = (*result).vp[(*edge).v_to];
         index_put_last( &( (*vertex).neighbors_from ), &(*vertex).nfcount, &(*vertex).nfcapacity, (*edge).v_from );
      }
   }


   INVARIANT( current );
   INVARIANT( result );

   UNLOCK( (*current).mutex );

   return result;
}


/**
   DGraph_deep_clone
*/

DGraph_type( Prefix ) *
DGraph_deep_clone( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );

   LOCK( (*current).mutex );

   INVARIANT( current );

   DGraph_type( Prefix ) *result = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;
   DGraph_vertex_type( Prefix ) *vertex1 = NULL;
   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_edge_type( Prefix ) *edge1 = NULL;
   int32_t i = 0;

   // allocate dgraph struct
   result = ( DGraph_type( Prefix ) * ) calloc( 1, sizeof( DGraph_type( Prefix ) ) );
   CHECK( "result allocated successfully", result != NULL );

   // set type codes
   (*result)._type = DGRAPH_TYPE;
   (*result)._edge_type = Edge_Code;
   (*result)._value_type = Value_Code;

   // init vertex array
   (*result).vp = calloc( START_CAPACITY, sizeof( void * ) );
   CHECK( "(*result).vp allocated successfully", (*result).vp != NULL );
   (*result).vcount = 0;
   (*result).vcapacity = START_CAPACITY;
   (*result).vnot_filled = 0;

   // init edge array
   (*result).ep = calloc( START_CAPACITY, sizeof( void * ) );
   CHECK( "(*result).ep allocated successfully", (*result).ep != NULL );
   (*result).ecount = 0;
   (*result).ecapacity = START_CAPACITY;
   (*result).enot_filled = 0;

   // allocate cursor struct
   DGraph_cursor_type( Prefix ) *cursor
      =  ( DGraph_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DGraph_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated successfully", cursor != NULL );

   // set dgraph in cursor
   (*cursor).dgraph = result;

   // set internal cursors
   (*cursor).vcursor = 0;
   (*cursor).ecursor = 0;

   // set next cursor to null
   (*cursor).next_cursor = NULL;

   // set dgraph first cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // now copy vertices using the same values
   for ( i = 0; i < (*current).vcount; i++ )
   {

      if ( (*current).vp[i] != NULL )
      {
         // get vertex
         vertex1 = (*current).vp[i];

         // allocate vertex
         vertex = ( DGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( DGraph_vertex_type( Prefix ) ) );
         CHECK( "vertex allocated correctly", vertex != NULL );

         // set type
         (*vertex)._type = DGRAPH_VERTEX_TYPE;
         (*vertex)._value_type = Value_Code;

         // set dgraph
         (*vertex).dgraph = result;

         // set value
         (*vertex).value = VERTEX_VALUE_DEEP_CLONE_FUNCTION( (*vertex1).value );

         // initialize neighbors_from
         (*vertex).neighbors_from = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_from allocated correctly", (*vertex).neighbors_from != NULL );
         (*vertex).nfcount = 0;
         (*vertex).nfcapacity = START_CAPACITY;

         // initialize neighbors_to
         (*vertex).neighbors_to = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
         CHECK( "(*vertex).neighbors_to allocated correctly", (*vertex).neighbors_to != NULL );
         (*vertex).ntcount = 0;
         (*vertex).ntcapacity = START_CAPACITY;

         // put vertex into result, and set its index
         (*vertex).id
            = pointer_insert
              (
                 ( void *** ) & ( (*result).vp ),
                 &(*result).vcount,
                 &(*result).vcapacity,
                 &(*result).vnot_filled,
                 vertex
              );

      }
   }

   // now copy edges using the same values
   for ( i = 0; i < (*current).ecount; i++ )
   {

      if ( (*current).ep[i] != NULL )
      {
         // get edge
         edge1 = (*current).ep[i];

         // allocate edge
         edge = ( DGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( DGraph_edge_type( Prefix ) ) );
         CHECK( "edge allocated correctly", edge != NULL );

         // set type
         (*edge)._type = DGRAPH_EDGE_TYPE;
         (*edge)._value_type = Edge_Code;

         // set dgraph
         (*edge).dgraph = result;

         // set value
         (*edge).value = EDGE_VALUE_DEEP_CLONE_FUNCTION( (*edge1).value );

         // set from and to
         (*edge).v_from = (*edge1).v_from;
         (*edge).v_to = (*edge1).v_to;

         // put edge into DGraph, and set its index
         (*edge).id
            = pointer_insert
              (
                 ( void *** ) & ( (*result).ep ),
                 &(*result).ecount,
                 &(*result).ecapacity,
                 &(*result).enot_filled,
                 edge
              );

         // add v_to to v_from's neighbors_to
         vertex = (*result).vp[(*edge).v_from];
         index_put_last( &( (*vertex).neighbors_to ), &(*vertex).ntcount, &(*vertex).ntcapacity, (*edge).v_to );

         // add v_from to v_to's neighbors_from
         vertex = (*result).vp[(*edge).v_to];
         index_put_last( &( (*vertex).neighbors_from ), &(*vertex).nfcount, &(*vertex).nfcapacity, (*edge).v_from );
      }
   }


   INVARIANT( current );
   INVARIANT( result );

   UNLOCK( (*current).mutex );

   return result;
}



/**
   DGraph_dispose
*/

void
DGraph_dispose( Prefix )( DGraph_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == DGRAPH_TYPE ) && ( (**current)._edge_type == Edge_Code ) && ( (**current)._value_type == Value_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;
   int32_t i = 0;

   // dipose of edges
   for ( i = 0; i < (**current).ecount; i++ )
   {
      if ( (**current).ep[i] != NULL )
      {
         edge_dispose( &( (**current).ep[i] ) );
      }
   }

   // dispose of vertices
   for ( i = 0; i < (**current).vcount; i++ )
   {
      if ( (**current).vp[i] != NULL )
      {
         vertex_dispose( &( (**current).vp[i] ) );
      }
   }

   // dispose of edge pointer array
   free( (**current).ep );
   (**current).ep = NULL;

   // dispose of vertex pointer array
   free( (**current).vp );
   (**current).vp = NULL;

   // dispose of cursors
   cursor = (**current).first_cursor;

   // walk through cursors
   while( cursor != NULL )
   {
      c = cursor;
      cursor = (*cursor).next_cursor;

      // free the cursor struct
      free( c );
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete dgraph struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   DGraph_deep_dispose
*/

void
DGraph_deep_dispose( Prefix )( DGraph_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == DGRAPH_TYPE ) && ( (**current)._edge_type == Edge_Code ) && ( (**current)._value_type == Value_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   DGraph_cursor_type( Prefix ) *cursor = NULL;
   DGraph_cursor_type( Prefix ) *c = NULL;
   int32_t i = 0;

   // dipose of edges
   for ( i = 0; i < (**current).ecount; i++ )
   {
      if ( (**current).ep[i] != NULL )
      {
         edge_deep_dispose( &( (**current).ep[i] ) );
      }
   }

   // dispose of vertices
   for ( i = 0; i < (**current).vcount; i++ )
   {
      if ( (**current).vp[i] != NULL )
      {
         vertex_deep_dispose( &( (**current).vp[i] ) );
      }
   }

   // dispose of edge pointer array
   free( (**current).ep );
   (**current).ep = NULL;

   // dispose of vertex pointer array
   free( (**current).vp );
   (**current).vp = NULL;

   // dispose of cursors
   cursor = (**current).first_cursor;

   // walk through cursors
   while( cursor != NULL )
   {
      c = cursor;
      cursor = (*cursor).next_cursor;

      // free the cursor struct
      free( c );
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete dgraph struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   DGraph_cursor_dispose
*/

void
DGraph_cursor_dispose( Prefix )( DGraph_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor not null", *cursor != NULL );
   LOCK( ( *(**cursor).dgraph ).mutex );
   INVARIANT( (**cursor).dgraph );

   DGraph_cursor_type( Prefix ) *c = NULL;
   DGraph_type( Prefix ) *current = NULL;
   int32_t flag = 0;

   // get dgraph
   current = (**cursor).dgraph;

   // dispose of cursor
   c = (*current).first_cursor;

   // walk through cursors, find cursor
   while( c != NULL || flag == 0 )
   {
      if ( (*c).next_cursor == *cursor )
      {
         (*c).next_cursor = (**cursor).next_cursor;
         flag = 1;
      }
      else
      {
         c = (*c).next_cursor;
      }
   }

   // free the cursor struct
   free(*cursor);

   // set to NULL
   *cursor = NULL;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_vertex_add
*/

int32_t
DGraph_vertex_add( Prefix )( DGraph_type( Prefix ) *current, Value value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DGraph_vertex_type( Prefix ) *vertex = NULL;

   // allocate vertex
   vertex = ( DGraph_vertex_type( Prefix ) * ) calloc( 1, sizeof( DGraph_vertex_type( Prefix ) ) );
   CHECK( "vertex allocated correctly", vertex != NULL );

   // set type
   (*vertex)._type = DGRAPH_VERTEX_TYPE;
   (*vertex)._value_type = Value_Code;

   // set dgraph
   (*vertex).dgraph = current;

   // set value
   (*vertex).value = value;

   // initialize neighbors_from
   (*vertex).neighbors_from = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
   CHECK( "(*vertex).neighbors_from allocated correctly", (*vertex).neighbors_from != NULL );
   (*vertex).nfcount = 0;
   (*vertex).nfcapacity = START_CAPACITY;

   // initialize neighbors_to
   (*vertex).neighbors_to = ( int32_t * ) calloc( START_CAPACITY, sizeof( int32_t ) );
   CHECK( "(*vertex).neighbors_to allocated correctly", (*vertex).neighbors_to != NULL );
   (*vertex).ntcount = 0;
   (*vertex).ntcapacity = START_CAPACITY;

   // put vertex into DGraph, and set its index
   (*vertex).id
      = pointer_insert
        (
           ( void *** ) & ( (*current).vp ),
           &(*current).vcount,
           &(*current).vcapacity,
           &(*current).vnot_filled,
           vertex
        );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return (*vertex).id;
}

/**
   DGraph_vertex_remove
*/

void
DGraph_vertex_remove( Prefix )( DGraph_type( Prefix ) *current, int32_t id )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "vertex present", (*current).vp[id] != NULL );
   INVARIANT( current );

   DGraph_vertex_type( Prefix ) *vertex = NULL;

   // get vertex
   vertex = (*current).vp[id];

   // dispose vertex
   vertex_dispose( &vertex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_vertex_remove_and_dispose
*/

void
DGraph_vertex_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *current, int32_t id )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "vertex present", (*current).vp[id] != NULL );
   INVARIANT( current );

   DGraph_vertex_type( Prefix ) *vertex = NULL;

   // get vertex
   vertex = (*current).vp[id];

   // dispose vertex
   vertex_deep_dispose( &vertex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_wipe_out
*/

void
DGraph_wipe_out( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DGraph_vertex_type( Prefix ) *vertex = NULL;

   int32_t i = 0;


   for ( i = 0; i < (*current).vcount; i++ )
   {

      if ( (*current).vp[i] != NULL )
      {
         // get vertex
         vertex = (*current).vp[i];

         // dispose vertex
         vertex_dispose( &vertex );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_wipe_out_and_dispose
*/

void
DGraph_wipe_out_and_dispose( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DGraph_vertex_type( Prefix ) *vertex = NULL;

   int32_t i = 0;


   for ( i = 0; i < (*current).vcount; i++ )
   {

      if ( (*current).vp[i] != NULL )
      {
         // get vertex
         vertex = (*current).vp[i];

         // dispose vertex
         vertex_deep_dispose( &vertex );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_vertex_count
*/

int32_t
DGraph_vertex_count( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).vcount - (*current).vnot_filled;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_vertex_value
*/

Value
DGraph_vertex_value( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "vertex present", (*current).vp[id] != NULL );
   INVARIANT( current );

   Value result;

   result = ( *(*current).vp[id] ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_vertex_value_put
*/

void
DGraph_vertex_value_put( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id,
   Value value
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "vertex present", (*current).vp[id] != NULL );
   INVARIANT( current );

   ( *(*current).vp[id] ).value = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_vertex_neighbors_from
*/

int32_t *
DGraph_vertex_neighbors_from( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id,
   int32_t *count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   PRECONDITION( "vertex present", (*current).vp[id] != NULL );
   INVARIANT( current );

   int32_t *result = NULL;
   int32_t min_count = 1;
   int32_t i = 0;

   if ( ( *(*current).vp[id] ).nfcount > 0 )
   {
      min_count = ( *(*current).vp[id] ).nfcount + 1;
   }

   result = calloc( min_count, sizeof( int32_t ) );
   CHECK( "result allocated_correctly", result != NULL );

   *count = ( *(*current).vp[id] ).nfcount;

   for( i = 0; i < (*count); i++ )
   {
      result[i] = ( *(*current).vp[id] ).neighbors_from[i];
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_vertex_neighbors_to
*/

int32_t *
DGraph_vertex_neighbors_to( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id,
   int32_t *count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   PRECONDITION( "vertex present", (*current).vp[id] != NULL );
   INVARIANT( current );

   int32_t *result = NULL;
   int32_t min_count = 1;
   int32_t i = 0;

   if ( ( *(*current).vp[id] ).ntcount > 0 )
   {
      min_count = ( *(*current).vp[id] ).ntcount + 1;
   }

   result = calloc( min_count, sizeof( int32_t ) );
   CHECK( "result allocated_correctly", result != NULL );

   *count = ( *(*current).vp[id] ).ntcount;

   for( i = 0; i < (*count); i++ )
   {
      result[i] = ( *(*current).vp[id] ).neighbors_to[i];
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_edge_for_from_to
*/

int32_t
DGraph_edge_for_from_to( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t v_from,
   int32_t v_to
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   PRECONDITION( "v_from non negative", v_from >= 0 );
   PRECONDITION( "v_to non negative", v_to >= 0 );
   LOCK( (*current).mutex );
   PRECONDITION( "v_from present", (*current).vp[v_from] != NULL );
   PRECONDITION( "v_to present", (*current).vp[v_to] != NULL );
   INVARIANT( current );

   int32_t result = -1;
   int32_t i = 0;

   for( i = 0; ( i < (*current).ecount ) && ( result == -1 ); i++ )
   {
      if ( (*current).ep[i] != NULL )
      {
         if (
            ( ( *(*current).ep[i] ).v_from == v_from )
            &&
            ( ( *(*current).ep[i] ).v_to == v_to )
         )
         {
            result = i;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_edge_add
*/

int32_t
DGraph_edge_add( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_from,
   int32_t vertex_to,
   Edge value
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "graph has vertex_from", (*current).vp[vertex_from] != NULL );
   PRECONDITION( "graph has vertex_to", (*current).vp[vertex_to] != NULL );
   INVARIANT( current );

   DGraph_edge_type( Prefix ) *edge = NULL;
   DGraph_vertex_type( Prefix ) *vertex = NULL;

   // allocate edge
   edge = ( DGraph_edge_type( Prefix ) * ) calloc( 1, sizeof( DGraph_edge_type( Prefix ) ) );
   CHECK( "edge allocated correctly", edge != NULL );

   // set type
   (*edge)._type = DGRAPH_EDGE_TYPE;
   (*edge)._value_type = Edge_Code;

   // set dgraph
   (*edge).dgraph = current;

   // set value
   (*edge).value = value;

   // set from and to
   (*edge).v_from = vertex_from;
   (*edge).v_to = vertex_to;

   // put edge into DGraph, and set its index
   (*edge).id
      = pointer_insert
        (
           ( void *** ) & ( (*current).ep ),
           &(*current).ecount,
           &(*current).ecapacity,
           &(*current).enot_filled,
           edge
        );

   // add v_to to v_from's neighbors_to
   vertex = (*current).vp[vertex_from];
   index_put_last( &( (*vertex).neighbors_to ), &(*vertex).ntcount, &(*vertex).ntcapacity, vertex_to );

   // add v_from to v_to's neighbors_from
   vertex = (*current).vp[vertex_to];
   index_put_last( &( (*vertex).neighbors_from ), &(*vertex).nfcount, &(*vertex).nfcapacity, vertex_from );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return (*edge).id;
}

/**
   DGraph_edge_remove
*/

void
DGraph_edge_remove( Prefix )( DGraph_type( Prefix ) *current, int32_t id )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "edge present", (*current).ep[id] != NULL );
   INVARIANT( current );

   DGraph_edge_type( Prefix ) *edge = NULL;

   // get edge
   edge = (*current).ep[id];

   // dispose edge
   edge_dispose( &edge );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_edge_remove_and_dispose
*/

void
DGraph_edge_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *current, int32_t id )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "edge present", (*current).ep[id] != NULL );
   INVARIANT( current );

   DGraph_edge_type( Prefix ) *edge = NULL;

   // get edge
   edge = (*current).ep[id];

   // dispose edge
   edge_deep_dispose( &edge );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_wipe_out_edges
*/

void
DGraph_wipe_out_edges( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DGraph_edge_type( Prefix ) *edge = NULL;
   int32_t i = 0;

   for ( i = 0; i < (*current).ecount; i++ )
   {
      if ( (*current).ep[i] != NULL )
      {
         // get edge
         edge = (*current).ep[i];

         // dispose edge
         edge_dispose( &edge );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_wipe_out_edges_and_dispose
*/

void
DGraph_wipe_out_edges_and_dispose( Prefix )( DGraph_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DGraph_edge_type( Prefix ) *edge = NULL;
   int32_t i = 0;

   for ( i = 0; i < (*current).ecount; i++ )
   {
      if ( (*current).ep[i] != NULL )
      {
         // get edge
         edge = (*current).ep[i];

         // dispose edge
         edge_deep_dispose( &edge );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_edge_count
*/

int32_t
DGraph_edge_count( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).ecount - (*current).enot_filled;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_edge_value
*/

Edge
DGraph_edge_value( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "edge present", (*current).ep[id] != NULL );
   INVARIANT( current );

   Edge result;

   result = ( *(*current).ep[id] ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_edge_value_put
*/

void
DGraph_edge_value_put( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id,
   Edge value
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "edge present", (*current).ep[id] != NULL );
   INVARIANT( current );

   ( *(*current).ep[id] ).value = value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_edge_vertex_from
*/

int32_t
DGraph_edge_vertex_from( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "edge present", (*current).ep[id] != NULL );
   INVARIANT( current );

   int32_t result = -1;

   result = ( *(*current).ep[id] ).v_from;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_edge_vertex_to
*/

int32_t
DGraph_edge_vertex_to( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "edge present", (*current).ep[id] != NULL );
   INVARIANT( current );

   int32_t result = -1;

   result = ( *(*current).ep[id] ).v_to;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_vertex_start
*/

void
DGraph_vertex_start( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).vcursor = 0;

   if ( ( (*current).vcount - (*current).vnot_filled ) > 0 )
   {
      ( *(*current).first_cursor ).vcursor = 0;
   }

   while
   (
      ( (*current).vp[ ( *(*current).first_cursor ).vcursor ] == NULL )
      &&
      ( ( *(*current).first_cursor ).vcursor < (*current).vcount )
   )
   {
      ( *(*current).first_cursor ).vcursor++;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_cursor_vertex_start
*/

void
DGraph_cursor_vertex_start( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "current not null", (*cursor).dgraph != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).dgraph )._type == DGRAPH_TYPE ) && ( ( *(*cursor).dgraph )._edge_type == Edge_Code ) && ( ( *(*cursor).dgraph )._value_type == Value_Code ) );
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_type( Prefix ) *current = NULL;

   current = (*cursor).dgraph;

   (*cursor).vcursor = 0;

   if ( ( (*current).vcount - (*current).vnot_filled ) > 0 )
   {
      (*cursor).vcursor = 0;
   }

   while
   (
      ( (*current).vp[ (*cursor).vcursor ] == NULL )
      &&
      ( (*cursor).vcursor < (*current).vcount )
   )
   {
      (*cursor).vcursor++;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_vertex_forth
*/

void
DGraph_vertex_forth( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "internal cursor not off", cursor_vertex_off( (*current).first_cursor ) == 0 );
   INVARIANT( current );

   if ( ( *(*current).first_cursor ).vcursor < (*current).vcount )
   {

      ( *(*current).first_cursor ).vcursor = ( *(*current).first_cursor ).vcursor + 1;

      if ( ( *(*current).first_cursor ).vcursor < (*current).vcount )
      {
         while
         (
            ( (*current).vp[ ( *(*current).first_cursor ).vcursor ] == NULL )
            &&
            ( ( *(*current).first_cursor ).vcursor < (*current).vcount )
         )
         {
            ( *(*current).first_cursor ).vcursor++;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_cursor_vertex_forth
*/

void
DGraph_cursor_vertex_forth( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   PRECONDITION( "cursor not off", cursor_vertex_off( cursor ) == 0 );
   INVARIANT( (*cursor).dgraph );

   if ( (*cursor).vcursor < ( *(*cursor).dgraph ).vcount )
   {

      (*cursor).vcursor = (*cursor).vcursor + 1;

      if ( (*cursor).vcursor < ( *(*cursor).dgraph ).vcount )
      {
         while
         (
            ( ( *(*cursor).dgraph ).vp[ (*cursor).vcursor ] == NULL )
            &&
            ( (*cursor).vcursor < ( *(*cursor).dgraph ).vcount )
         )
         {
            (*cursor).vcursor++;
         }
      }
   }

   INVARIANT( (*cursor).dgraph );
   UNLOCK( ( *(*cursor).dgraph ).mutex );

   return;
}

/**
   DGraph_vertex_id_at
*/

int32_t
DGraph_vertex_id_at( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "internal cursor not off", cursor_vertex_off( (*current).first_cursor ) == 0 );
   INVARIANT( current );

   int32_t result = -1;

   if ( ( *(*current).first_cursor ).vcursor < (*current).vcount )
   {
      if
      (
         ( (*current).vp[ ( *(*current).first_cursor ).vcursor ] != NULL )
      )
      {
         result = ( *(*current).first_cursor ).vcursor;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_cursor_vertex_id_at
*/

int32_t
DGraph_cursor_vertex_id_at( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   PRECONDITION( "cursor not off", cursor_vertex_off( cursor ) == 0 );
   INVARIANT( (*cursor).dgraph );

   int32_t result = -1;

   if ( (*cursor).vcursor < ( *(*cursor).dgraph ).vcount )
   {
      if
      (
         ( ( *(*cursor).dgraph ).vp[ (*cursor).vcursor ] != NULL )
      )
      {
         result = (*cursor).vcursor;
      }
   }

   INVARIANT( (*cursor).dgraph );
   UNLOCK( ( *(*cursor).dgraph ).mutex );

   return result;
}

/**
   DGraph_vertex_off
*/

int32_t
DGraph_vertex_off( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = cursor_vertex_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_cursor_vertex_off
*/

int32_t
DGraph_cursor_vertex_off( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   INVARIANT( (*cursor).dgraph );

   int32_t result = 0;

   result = cursor_vertex_off( cursor );

   INVARIANT( (*cursor).dgraph );
   UNLOCK( ( *(*cursor).dgraph ).mutex );

   return result;
}

/**
   DGraph_edge_start
*/

void
DGraph_edge_start( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).ecursor = 0;

   if ( ( (*current).ecount - (*current).enot_filled ) > 0 )
   {
      ( *(*current).first_cursor ).ecursor = 0;
   }

   while
   (
      ( (*current).ep[ ( *(*current).first_cursor ).ecursor ] == NULL )
      &&
      ( ( *(*current).first_cursor ).ecursor < (*current).ecount )
   )
   {
      ( *(*current).first_cursor ).ecursor++;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_cursor_edge_start
*/

void
DGraph_cursor_edge_start( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "current not null", (*cursor).dgraph != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).dgraph )._type == DGRAPH_TYPE ) && ( ( *(*cursor).dgraph )._edge_type == Edge_Code ) && ( ( *(*cursor).dgraph )._value_type == Value_Code ) );
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   INVARIANT( (*cursor).dgraph );

   DGraph_type( Prefix ) *current = NULL;

   current = (*cursor).dgraph;

   (*cursor).ecursor = 0;

   if ( ( (*current).ecount - (*current).enot_filled ) > 0 )
   {
      (*cursor).ecursor = 0;
   }

   while
   (
      ( (*current).ep[ (*cursor).ecursor ] == NULL )
      &&
      ( (*cursor).ecursor < (*current).ecount )
   )
   {
      (*cursor).ecursor++;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_edge_forth
*/

void
DGraph_edge_forth( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "internal cursor not off", cursor_edge_off( (*current).first_cursor ) == 0 );
   INVARIANT( current );

   if ( ( *(*current).first_cursor ).ecursor < (*current).ecount )
   {

      ( *(*current).first_cursor ).ecursor = ( *(*current).first_cursor ).ecursor + 1;

      if ( ( *(*current).first_cursor ).ecursor < (*current).ecount )
      {
         while
         (
            ( (*current).ep[ ( *(*current).first_cursor ).ecursor ] == NULL )
            &&
            ( ( *(*current).first_cursor ).ecursor < (*current).ecount )
         )
         {
            ( *(*current).first_cursor ).ecursor++;
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DGraph_cursor_edge_forth
*/

void
DGraph_cursor_edge_forth( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   PRECONDITION( "cursor not off", cursor_edge_off( cursor ) == 0 );
   INVARIANT( (*cursor).dgraph );

   if ( (*cursor).ecursor < ( *(*cursor).dgraph ).ecount )
   {

      (*cursor).ecursor = (*cursor).ecursor + 1;

      if ( (*cursor).ecursor < ( *(*cursor).dgraph ).ecount )
      {
         while
         (
            ( ( *(*cursor).dgraph ).ep[ (*cursor).ecursor ] == NULL )
            &&
            ( (*cursor).ecursor < ( *(*cursor).dgraph ).ecount )
         )
         {
            (*cursor).ecursor++;
         }
      }
   }

   INVARIANT( (*cursor).dgraph );
   UNLOCK( ( *(*cursor).dgraph ).mutex );

   return;
}

/**
   DGraph_edge_id_at
*/

int32_t
DGraph_edge_id_at( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "internal cursor not off", cursor_edge_off( (*current).first_cursor ) == 0 );
   INVARIANT( current );

   int32_t result = -1;

   if ( ( *(*current).first_cursor ).ecursor < (*current).ecount )
   {
      if
      (
         ( (*current).ep[ ( *(*current).first_cursor ).ecursor ] != NULL )
      )
      {
         result = ( *(*current).first_cursor ).ecursor;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_cursor_edge_id_at
*/

int32_t
DGraph_cursor_edge_id_at( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   PRECONDITION( "cursor not off", cursor_edge_off( cursor ) == 0 );
   INVARIANT( (*cursor).dgraph );

   int32_t result = -1;

   if ( (*cursor).ecursor < ( *(*cursor).dgraph ).ecount )
   {
      if
      (
         ( ( *(*cursor).dgraph ).ep[ (*cursor).ecursor ] != NULL )
      )
      {
         result = (*cursor).ecursor;
      }
   }

   INVARIANT( (*cursor).dgraph );
   UNLOCK( ( *(*cursor).dgraph ).mutex );

   return result;
}

/**
   DGraph_edge_off
*/

int32_t
DGraph_edge_off( Prefix )
(
   DGraph_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DGRAPH_TYPE ) && ( (*current)._edge_type == Edge_Code ) && ( (*current)._value_type == Value_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = cursor_edge_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DGraph_cursor_edge_off
*/

int32_t
DGraph_cursor_edge_off( Prefix )
(
   DGraph_cursor_type( Prefix ) *cursor
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   LOCK( ( *(*cursor).dgraph ).mutex );
   INVARIANT( (*cursor).dgraph );

   int32_t result = 0;

   result = cursor_edge_off( cursor );

   INVARIANT( (*cursor).dgraph );
   UNLOCK( ( *(*cursor).dgraph ).mutex );

   return result;
}

/**
   DGraph_connected_vertices_breadth_first
*/

int32_t *
DGraph_connected_vertices_breadth_first( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t *count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "vertex_id OK", vertex_id >= 0 );
   PRECONDITION( "count OK", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t *queue = NULL;
   int32_t qcount = 0;
   int32_t qcapacity = 0;
   int32_t *is_visited = NULL;
   int32_t ivcount = 0;
   int32_t ivcapacity = 0;

   // allocate queue and is_visited arrays
   queue = ( int32_t * ) calloc(  START_CAPACITY, sizeof( int32_t ) );
   CHECK( "queue allocate correctly", queue != NULL );
   qcount = 0;
   qcapacity = START_CAPACITY;

   is_visited = ( int32_t * ) calloc(  START_CAPACITY, sizeof( int32_t ) );
   CHECK( "is_visited allocate correctly", is_visited != NULL );
   ivcount = 0;
   ivcapacity = START_CAPACITY;

   // find all vertices connected to vertex_id breadth first search
   find_connected_vertices_breadth_first
   (
      current,
      vertex_id,
      &queue,
      &qcount,
      &qcapacity,
      &is_visited,
      &ivcount,
      &ivcapacity
   );

   // deallocate queue
   free( queue );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // result is in is_visited
   (*count) = ivcount;

   return is_visited;
}

/**
   DGraph_connected_vertices_depth_first
*/

int32_t *
DGraph_connected_vertices_depth_first( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t *count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "vertex_id OK", vertex_id >= 0 );
   PRECONDITION( "count OK", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t *is_visited = NULL;
   int32_t ivcount = 0;
   int32_t ivcapacity = 0;

   // allocate is_visited arrays
   is_visited = ( int32_t * ) calloc(  START_CAPACITY, sizeof( int32_t ) );
   CHECK( "is_visited allocate correctly", is_visited != NULL );

   ivcount = 0;
   ivcapacity = START_CAPACITY;

   // find all vertices connected to vertex_id depth first search
   find_connected_vertices_depth_first
   (
      current,
      vertex_id,
      &is_visited,
      &ivcount,
      &ivcapacity
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // result is in is_visited
   (*count) = ivcount;

   return is_visited;
}


#ifdef __cplusplus
}
#endif

/* End of file */


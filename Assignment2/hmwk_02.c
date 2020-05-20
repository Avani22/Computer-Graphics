// Chandorkar, Avani
// arc8554
// 2020-04-20
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "projection.h"
#include "triangle.h"
#include "view.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <modelFileName> <viewFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  // Load the desired model and view.
  Model *m = loadModel( argv[1] );
  View *v = loadView( argv[2] );

  // Compute the projection corresponding to the view.
  Projection *p = computeProjection( v );

  //--------------------------------------
  // Dump all of these data structures as a check.
  dumpModel( m );
  dumpView( v );
  dumpProjection( p );

  //--------------------------------------
  // Project all of the vertices of the model.
  projectVertexList( p, m->m_vertex, m->m_numVertices );

  // We dump the model again so we can see the projected
  // vertex coordinates as a check.
  dumpModel( m );

  //--------------------------------------
  // Print the canvas size for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  //--------------------------------------
  // Draw lines corresponding to the viewport region.

  // TODO: Print four 'l' lines, corresponding to the
  //         the edges of the viewport region.
  //       Start in the lower-left corner (xMin, yMin) and draw
  //         the lines going counter-clockwise.

  printf( "l %8d %8d %8d %8d\n",
    v->m_portalXMin, v->m_portalYMin, v->m_portalXMin, v->m_portalYMax );
 
  printf( "l %8d %8d %8d %8d\n",
    v->m_portalXMin, v->m_portalYMax, v->m_portalXMax, v->m_portalYMax ); 
 
  printf( "l %8d %8d %8d %8d\n",
    v->m_portalXMax, v->m_portalYMax, v->m_portalXMax, v->m_portalYMin ); 
 
  printf( "l %8d %8d %8d %8d\n",
    v->m_portalXMax, v->m_portalYMin, v->m_portalXMin, v->m_portalYMin );

  //--------------------------------------
  // Dump all of the faces of the model using the
  // projected vertices.

  // TODO: For each face of the model, draw the triangle
  //         represented by its three vertices.
  //       (This is just a for loop with a call to dumpTriangle()
  //        inside.)
   for ( int i=0; i<m->m_numFaces; i++ ) 
   {
    dumpTriangle(
      &m->m_vertex[m->m_face[i].v1],
      &m->m_vertex[m->m_face[i].v2],
      &m->m_vertex[m->m_face[i].v3] );
   }

  //--------------------------------------
  freeModel( m );
  freeView( v );
  freeProjection( p );
}

//----------------------------------------------------------
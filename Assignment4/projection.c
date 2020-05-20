// Chandorkar, Avani
// arc8554
// 2020-05-08
//----------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "projection.h"

//----------------------------------------------------------
Projection *allocProjection()
{
  Projection *p;

  p = (Projection *) calloc( 1, sizeof( Projection ) );
  if ( p == NULL ) {
    fprintf( stderr, "allocProjection: Unable to allocate Projection.\n" );
    exit( 1 );
  }

  return p;
}

//----------------------------------------------------------
Projection *computeProjection( View *v )
{
  Projection *p = allocProjection();

  p->m_fx = -v->m_worldXMin;
  p->m_fy = -v->m_worldYMin;

  p->m_gx = v->m_width*v->m_viewportXMin;
  p->m_gy = v->m_height*v->m_viewportYMin;

  p->m_sx = ( v->m_width*( v->m_viewportXMax - v->m_viewportXMin ) ) /
    ( v->m_worldXMax - v->m_worldXMin );
  p->m_sy = ( v->m_height*( v->m_viewportYMax - v->m_viewportYMin ) ) /
    ( v->m_worldYMax - v->m_worldYMin );

  p->m_ax = p->m_fx*p->m_sx + p->m_gx;
  p->m_ay = p->m_fy*p->m_sy + p->m_gy;

  p->m_cameraDistance = v->m_cameraDistance;

  return p;
}

//----------------------------------------------------------
void dumpProjection( Projection *p )
{
  printf( "#- Projection parameters ---------------\n" );
  printf( "# (fx, fy) : ( %13.6f, %13.6f )\n", p->m_fx, p->m_fy );
  printf( "# (gx, gy) : ( %13.6f, %13.6f )\n", p->m_gx, p->m_gy );
  printf( "# (sx, sy) : ( %13.6f, %13.6f )\n", p->m_sx, p->m_sy );
  printf( "# (ax, ay) : ( %13.6f, %13.6f )\n", p->m_ax, p->m_ay );
  printf( "# Camera distance : %13.6f\n", p->m_cameraDistance );
  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeProjection( Projection *p )
{
  if ( p != NULL ) {
    free( p );
  }
}

//----------------------------------------------------------
void projectVertex( Projection *p, Vertex *v1, Vertex *v2 )
{
  double x = v1->x;
  double y = v1->y;
  double z = v1->z;

  if ( p->m_cameraDistance != 0.0 ) {
    if ( z >= p->m_cameraDistance ) {
      fprintf( stderr, "Vertex has z (%13.6f) >= the camera distance (%13.6f)\n",
        z, p->m_cameraDistance );
    } else {
      x = x / ( 1 - z/p->m_cameraDistance );
      y = y / ( 1 - z/p->m_cameraDistance );
    }
  }

  v2->x = p->m_sx*x + p->m_ax;
  v2->y = p->m_sy*y + p->m_ay;
  v2->z = 0.0;
}

void projectVertexList2( Projection *projection, Vertex *vertex, int numVertices, Vertex *destination )
{
  // TODO: Use projectVertex() to project each of the
  //         numVertices starting at vertex into the
  //         corresponding space in destination.

  for ( int i=0; i<numVertices; i++ ) 
  {
    projectVertex( projection, &vertex[i], &vertex[i] );
  }
}

//----------------------------------------------------------


// Chandorkar, Avani
// arc8554
// 2020-05-08
//----------------------------------------------------------
#include <stdio.h>

#include "line.h"
#include "triangle.h"

//----------------------------------------------------------
void dumpTriangle( View *view, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO: Using a Line structure and calling clipLine(), check
  //         each of the three lines v1->v2, v2->v3, v3->v1 for
  //         clipping status and print an 'l' line for those that
  //         are not rejected.  Do the lines in that order!
	
  Line l;

  l.p1X = v1->x;
  l.p1Y = v1->y;
  l.p2X = v2->x;
  l.p2Y = v2->y;

  if ( clipLine( &l,view->m_portalXMin, view->m_portalYMin, view->m_portalXMax, view->m_portalYMax  ) ) 
  {
    dumpLine( &l );
  }

  l.p1X = v2->x;
  l.p1Y = v2->y;
  l.p2X = v3->x;
  l.p2Y = v3->y;

  if ( clipLine( &l,view->m_portalXMin, view->m_portalYMin, view->m_portalXMax, view->m_portalYMax  ) ) 
  {
    dumpLine( &l );
  }

  l.p1X = v3->x;
  l.p1Y = v3->y;
  l.p2X = v1->x;
  l.p2Y = v1->y;

  if ( clipLine( &l,view->m_portalXMin, view->m_portalYMin, view->m_portalXMax, view->m_portalYMax ) )
  {
    dumpLine( &l );
  }
}

//----------------------------------------------------------


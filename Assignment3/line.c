// Chandorkar, Avani
// arc8554
// 2020-04-28
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "line.h"

//----------------------------------------------------------
#define INSIDE (0)
#define LEFT   (1)
#define RIGHT  (2)
#define BELOW  (4)
#define ABOVE  (8)

#define EPSILON (1e-13)

int _regionCode( double x, double y, double xMin, double yMin, double xMax, double yMax );

//----------------------------------------------------------
int clipLine( Line *l, double xMin, double yMin, double xMax, double yMax )
{
  // TODO: Implement the clipLine algorithm here.
  //       Arguments:
  //           l : a pointer to the line to clip.
  //
  //           xMin, yMin, xMax, yMax
  //             : the four bounding lines of the view region to
  //               clip against.
  //
  //       Compute the codes of the two endpoints of the line l
  //         using _regionCode().
  //
  //       In an infinite while loop,
  //         Do a trivial accept if possible.
  //         Do a trivial reject if possible.
  //         If neither is possible, select one of the point
  //           codes that's not in the INSIDE region.
  //         If it's ABOVE, slide the point to the yMax line.
  //         ElIf it's BELOW, slide the point to the yMin line.
  //         ElIf it's RIGHT, slide the point to the xMax line.
  //         Elif it's LEFT, slide the point to the xMin line.
  //         Else an error occurred.  Print a message and exit.
  //         Update whichever point got slid in l.
  //         Recompute the code of that point.
  //
  // This routine should return 1 if trivial accept happens, 0 if
  // trivial reject happens.
  //
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  //   You can look at the code in the Clipping handout as a
  //   reference, but remember that code is written in Python and
  //   this is C.
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT

  int p1_region = _regionCode(l->p1X, l->p1Y, xMin, yMin, xMax, yMax);    //Region codes for line l
  int p2_region = _regionCode(l->p2X, l->p2Y, xMin, yMin, xMax, yMax);

  while(1)        //infinite while loop
  {
      int code_out = ( p1_region == INSIDE )? p2_region : p1_region;
      int pt = ( p1_region == INSIDE )? 2 : 1;

      if ( (p1_region == p2_region) && (p1_region == INSIDE) )
      {
        return 1;         //trivial accept
      }
      else if( ( p1_region & p2_region) != INSIDE) 
      {
        return 0;         //trivial reject
      }

      else
      {
            double x, y;

            if (code_out & ABOVE)
            {
                // point is above the clip rectangle
                 x = l->p1X + ( l->p2X - l->p1X ) * ( yMax - l->p1Y ) / ( l->p2Y - l->p1Y );
                 y = yMax;
            }
            else if (code_out & BELOW)
            {
                // point is below the rectangle
                 x = l->p1X + ( l->p2X - l->p1X ) * ( yMin - l->p1Y ) / ( l->p2Y - l->p1Y );
                 y = yMin;
            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                x = xMax;
                y = l->p1Y + ( l->p2Y - l->p1Y ) * ( xMax - l->p1X ) / ( l->p2X - l->p1X );
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                x = xMin;
                y = l->p1Y + ( l->p2Y - l->p1Y ) * ( xMin - l->p1X ) / ( l->p2X - l->p1X );
            }

            if (pt == 1)
            {
                l->p1X = x;
                l->p1Y = y;
                p1_region = _regionCode(l->p1X, l->p1Y, xMin, yMin, xMax, yMax);
            }
            else
            {
                l->p2X = x;
                l->p2Y = y;
                p2_region = _regionCode(l->p2X, l->p2Y, xMin, yMin, xMax, yMax);
            }
      }
  }

}

//----------------------------------------------------------
void dumpLine( Line *l )
{
  // TODO: Print an 'l' line for the given Line l.
    printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    l->p1X, l->p1Y, l->p2X, l->p2Y );
}

//----------------------------------------------------------
int _regionCode( double x, double y, double xMin, double yMin, double xMax, double yMax )
{
  // TODO: Implement the region code computation here.
  //       Arguments:
  //           x, y
  //             : the point whose region must be computed.
  //
  //           xMin, yMin, xMax, yMax
  //             : the four bounding lines of the view region to
  //               check against.
  //
  //       Assume the region is INSIDE to start.
  //       Check against xMin to see if the point is LEFT.
  //       Check against xMax to see if the point is RIGHT.
  //       Check against yMin to see if the point is BELOW.
  //       Check against yMax to see if the point is ABOVE.
  //
  // This routine should return the code with the proper bits set.
  // (The bits are already defined above for your use.)

  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT
  //   (1) Ensure that you do EPSILON comparisions when
  //       checking against xMin, yMin, xMax, yMax.  EPSILON is
  //       already defined above for your use.
  //   (2) You can look at the code in the Clipping handout as a
  //       reference, but remember that code is written in Python
  //       and this is C.
  // IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT -- IMPORTANT

      int CODE = INSIDE;

      if( x < xMin - EPSILON ) 
      {
        CODE = CODE | LEFT;
      }
      else if( x > xMax + EPSILON )
      {
        CODE = CODE | RIGHT;
      }
      if( y < yMin - EPSILON ) 
      {
        CODE = CODE | BELOW;
      }
      else if( y > yMax + EPSILON )
      {
        CODE = CODE | ABOVE;
      }
      return CODE;
}

//----------------------------------------------------------
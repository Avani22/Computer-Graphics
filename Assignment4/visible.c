// Chandorkar, Avani
// arc8554
// 2020-05-08

//----------------------------------------------------------
#include <stdio.h>

#include "visible.h"

//----------------------------------------------------------
int isVisible( Vertex *cameraPosition, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO:  Purpose:  Determine if the triangle represented by
  //          vertices v1, v2, and v3 is visible from the given
  //          camera position.
  //
  //        Compute the toTriangle vector from the camera position
  //          to v1 of the triangle.
  //
  //        Derive the surface normal for the triangle by
  //          computing the cross product of the vector from v1
  //          to v2 with the vector from v1 to v3.
  //
  //        Compute the angle between the toTriangle vector and
  //          the surface normal vector.
  //
  //        Return 1 if this angle indicates the triangle is
  //          visible from the camera position, 0 otherwise.

    Vertex toTriangle;
    toTriangle.x = v1->x - cameraPosition->x;
    toTriangle.y = v1->y - cameraPosition->y;
    toTriangle.z = v1->z - cameraPosition->z;

    Vertex Vector1;
    Vector1.x = v1->x - v2->x;
    Vector1.y = v1->y - v2->y;
    Vector1.z = v1->z - v2->z;

    Vertex Vector2;
    Vector2.x = v3->x - v2->x;
    Vector2.y = v3->y - v2->y;
    Vector2.z = v3->z - v2->z;

    Vertex normal;
    normal.x = ( Vector1.y * Vector2.z ) - ( Vector1.z * Vector2.y );
    normal.y = ( Vector1.z * Vector2.x ) - ( Vector1.x * Vector2.z );
    normal.z = ( Vector1.x * Vector2.y ) - ( Vector1.y * Vector2.x );
    
    double angle = ( toTriangle.x * normal.x ) + ( toTriangle.y * normal.y ) + ( toTriangle.z * normal.z );
    
    if(angle > 0) 
    {
      return 1;
    }
    else 
    {
      return 0;
    }

}

//----------------------------------------------------------

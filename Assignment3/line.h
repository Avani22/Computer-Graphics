// Chandorkar, Avani
// arc8554
// 2020-04-28

#if !defined( __LINE_H__ )
#define __LINE_H__

//----------------------------------------------------------
typedef struct _Line {
  double p1X;
  double p1Y;
  double p2X;
  double p2Y;
} Line;

//----------------------------------------------------------
int  clipLine( Line *line, double xMin, double yMin, double xMax, double yMax );
void dumpLine( Line *line );

//----------------------------------------------------------
#endif

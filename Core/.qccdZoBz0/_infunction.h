






  typedef struct {
    double n;
    double (* pos) (Point, vector, coord *, coord *);
  } NormPos;
  struct { NormPos x, y, z; } n;
  {
#line 682

    n.x.n = val(f,1,0,0) - val(f,-1,0,0), n.x.pos = pos_x;
#line 682

    n.y.n = val(f,0,1,0) - val(f,0,-1,0), n.y.pos = pos_y;}




  if (fabs(n.x.n) < fabs(n.y.n))
    swap (NormPos, n.x, n.y);
#line 700 "/home/laxyos/basilisk/src/curvature.h"
  double pos = nodata;
  {
#line 701

    if (pos == nodata)
      pos = n.x.pos (point, h, G, Z);
#line 701

    if (pos == nodata)
      pos = n.y.pos (point, h, G, Z);}

  return pos;

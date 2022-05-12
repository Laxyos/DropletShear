typedef struct {

#line 1019 "/home/laxyos/basilisk/src/common.h"

  double (** boundary) (Point, Point, scalar, void *);
  double (** boundary_homogeneous) (Point, Point, scalar, void *);
  double (* gradient) (double, double, double);
  void (* delete) (scalar);
  char * name;
  struct {
    int x;

    int y;




  } d;
  vector v;
  int face;
  bool nodump, freed;
  int block;
  scalar * depends;

#line 18 "/home/laxyos/basilisk/src/grid/stencils.h"

  double * write;
  int * read;
  int dirty;




#line 17 "/home/laxyos/basilisk/src/grid/multigrid-common.h"

  void (* prolongation) (Point, scalar);
  void (* restriction) (Point, scalar);

#line 8 "/home/laxyos/basilisk/src/grid/tree-common.h"

  void (* refine) (Point, scalar);

#line 94 "/home/laxyos/basilisk/src/grid/tree-common.h"

  void (* coarsen) (Point, scalar);

#line 27 "/home/laxyos/basilisk/src/vof.h"

  scalar * tracers, c;
  bool inverse;

#line 81 "/home/laxyos/basilisk/src/fractions.h"

  vector n;

#line 20 "/home/laxyos/basilisk/src/iforce.h"

  scalar phi;

#line 454 "/home/laxyos/basilisk/src/heights.h"

  vector height;

#line 21 "/home/laxyos/basilisk/src/tension.h"

  double sigma;

} _Attributes;
_Attributes * _attribute;

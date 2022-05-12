/* Title: getting Data from simulation snapshot
# Author: Vatsal Sanjay
# vatsalsanjay@gmail.com
# Physics of Fluids
*/

#include "embed.h"
#include "navier-stokes/centered.h"
#include "fractions.h"

char filename[80];
int nx, ny, len;
double xmin, ymin, xmax, ymax, Hy, Deltax, Deltay;
scalar f[], D2[], vel[];
face vector D2f[];
scalar * list = NULL;

int main(int a, char const *arguments[]){

  sprintf (filename, "%s", arguments[1]);
  // These are corners of the domain of interest
  // You can take this to be the whole domain, or just 
  // a small part where something interesting is happening.
  xmin = atof(arguments[2]); ymin = atof(arguments[3]);
  xmax = atof(arguments[4]); ymax = atof(arguments[5]);
  // This is how much of vertical space of the domain 
  // you want to fill in. 
  Hy = atof(arguments[6]);
  // This is the number of grids you want in the vertical direction.
  ny = atoi(arguments[7]);
  // This is the grid spacing the in the vertical direction.
  Deltay = (double)(ymax-ymin)/(ny);
  // This is the number of grids in the horizontal direction.
  // caclculated so that the grid cells are square.
  nx = (int)(xmax - xmin)/Deltay;
  // This is the grid spacing in the horizontal direction.
  Deltax = (double)(xmax-xmin)/(nx);

  list = list_add (list, D2);
  list = list_add (list, vel);

  // boundary conditions
  periodic (right);

  /*
  Actual run and codes!
  */
  restore (file = filename);
  f.prolongation = fraction_refine;
  solid (cs, fs, difference (0.5*Hy+y,-0.5*Hy+y));
  u.t[embed] = dirichlet(0);
  u.n[embed] = dirichlet(y>0?1:-1);
  boundary((scalar *){f, cs, u.x, u.y});

  foreach_face(x) {
    double D11 = (u.x[] - u.x[-1,0]);
    double D22 = ((u.y[0,1]-u.y[0,-1])+(u.y[-1,1]-u.y[-1,-1]))/4.0;
    double D12 = 0.5*(((u.x[0,1]-u.x[0,-1])+(u.x[-1,1]-u.x[-1,-1]))/4.0 + (u.y[] - u.y[-1,0]));
    double D2 = sqrt(sq(D11)+sq(D22)+2.0*sq(D12))/(Delta);
    D2f.x[] = D2/sqrt(2);
  }

  foreach_face(y) {
    double D11 = (u.y[0,0] - u.y[0,-1])/Delta;
    double D22 = 0.5*( (u.x[1,0] - u.x[-1,0] + u.x[1,-1] - u.x[-1,-1])/(2.*Delta) );
    double D12 = 0.5*( (u.x[0,0] - u.x[0,-1])/Delta + 0.5*( (u.y[1,0] - u.y[-1,0] + u.y[1,-1] - u.y[-1,-1])/(2.*Delta) ) );
    double D2 = sqrt( sq(D11) + sq(D22) + 2*sq(D12) );
    D2f.y[] = D2/sqrt(2);
  }

  foreach(){
    D2[] = (D2f.x[]+D2f.y[]+D2f.x[1,0]+D2f.y[0,1])/4.;
    if (D2[] > 0.){
      D2[] = log(D2[])/log(10);
    } else {
      D2[] = -10;
    }
    vel[] = sqrt(sq(u.x[]) + sq(u.y[]));
  }
  boundary(all);


  FILE * fp = ferr;
  // fprintf(ferr, "%g\n", Deltax);
  len = list_len(list);
  // fprintf(ferr, "%d\n", len);
  double ** field = (double **) matrix_new (nx, ny+1, len*sizeof(double));
  for (int i = 0; i < nx; i++) {
    double x = Deltax*(i+1./2) + xmin;
    for (int j = 0; j < ny; j++) {
      double y = Deltay*(j+1./2) + ymin;
      int k = 0;
      for (scalar s in list){
        field[i][len*j + k++] = interpolate (s, x, y);
      }
    }
  }

  for (int i = 0; i < nx; i++) {
    double x = Deltax*(i+1./2) + xmin;
    for (int j = 0; j < ny; j++) {
      double y = Deltay*(j+1./2) + ymin;
      fprintf (fp, "%g %g", x, y);
      int k = 0;
      for (scalar s in list){
        fprintf (fp, " %g", field[i][len*j + k++]);
      }
      fputc ('\n', fp);
    }
  }
  fflush (fp);
  fclose (fp);
  matrix_free (field);
}

// --------------------------------------------------------------------
// Author:                  Vatsal
// Last used by Tom on:     1-Feb-2022
// --------------------------------------------------------------------

//Headers

#include "navier-stokes/centered.h"                 // header for NS and continuity equation
#define FILTERED
#include "two-phaseVP.h"                            // header for constituion eqn model (Bingham)
#include "navier-stokes/conserving.h"               // header guarentees momentum conservation
#include "tension.h"                                // header for surface tenstion forces

#define tsnap (0.05)

// Error tolerancs
#define fErr (1e-3)                                 // error tolerance in f1 VOF
#define KErr (1e-6)                                 // error tolerance in f2 VOF
#define VelErr (5e-3)                               // error tolerances in velocity
#define OmegaErr (1e-2)                             // error tolerances in vorticity

// Numbers!
#define SIGMA 1.0
#define RHO21 1.0
#define MU21 1.0
#define Ldomain 5.0
#define GAP 0.1

// boundary conditions
u.t[top] = dirichlet(1.);                          
u.t[bottom] = dirichlet(-1.);

int MAXlevel;                                     
double Bi, Re, Ca, tmax;                              
char nameOut[80], dumpFile[80];  

int  main(int argc, char const *argv[]) {
  L0 = Ldomain;                                    
  origin (-L0/2., -L0/2.);                          
  init_grid (1 << 6);                               
  periodic (right);                             
  if (argc < 6){
    fprintf(ferr, "Lack of command line arguments. Check! Need %d more arguments\n",5-argc);
    return 1;
  }
  
  MAXlevel = atoi(argv[1]);
  Bi = atof(argv[2]);
  Re = atof(argv[3]);
  Ca = atof(argv[4]);
  tmax = atof(argv[5]);
  
  fprintf(ferr, "Level %d, Bi %2.1e, Re %4.3f, Ca %4.3f tmax %g\n", MAXlevel, Bi, Re, Ca, tmax);
  char comm[80];
  sprintf (comm, "mkdir -p intermediate");
  system(comm);
  sprintf (dumpFile, "dump");



  tauy = Bi;                               
  mumax = 1e10;                       
  rho1 = Re, rho2 = RHO21*Re;                     
  mu1 = 1., mu2 = MU21;         
  f.sigma = 1./Ca;

  run();
}

event init (t = 0) {
  if (!restore (file = dumpFile)){
    fraction (f, max (- (sq(x - 0.5 - GAP/2.0) + sq(y-0.2) - sq(0.5)),- (sq(x + 0.5 + GAP/2.0) + sq(y+0.2) - sq(0.5))));
    //fraction(f, - 1 + sq(x) + sq(y)); 
    foreach(){
      u.x[] = (2*y/Ldomain);          
    }
  }
}

scalar omega[];
event adapt(i++)                       
{
  scalar KAPPA[];
  curvature(f, KAPPA);        
  vorticity (u, omega);                
  foreach(){
    omega[] *= f[];   
  }
  boundary ((scalar *){KAPPA, omega});                  
  adapt_wavelet((scalar *){f, u.x, u.y, KAPPA, omega},  
  (double[]){fErr, VelErr, VelErr, KErr, OmegaErr},
  MAXlevel);
}

// Outputs
event writingFiles (t = 0; t += tsnap; t <= tmax) {
  dump (file = dumpFile);
  sprintf (nameOut, "intermediate/snapshot-%5.4f", t);
  dump(file=nameOut);
}

event end (t = end) {
  fprintf(ferr, "Done: Level %d, Bi %2.1e, Re %4.3f, Ca %4.3f tmax %g\n", MAXlevel, Bi, Re, Ca, tmax);
}

event logWriting (i++) {
  double ke = 0.;
  foreach (reduction(+:ke)){
    ke += (0.5*(sq(u.x[]) + sq(u.y[])))*sq(Delta);
  }
  static FILE * fp;
  if (i == 0) {
    fprintf (ferr, "i dt t ke\n");
    fp = fopen ("log", "w");
    fprintf (fp, "i dt t ke\n");
    fprintf (fp, "%d %g %g %g\n", i, dt, t, ke);
    fclose(fp);
  } else {
    fp = fopen ("log", "a");
    fprintf (fp, "%d %g %g %g\n", i, dt, t, ke);
    fclose(fp);
  }
  fprintf (ferr, "%d %g %g %g\n", i, dt, t, ke);
}


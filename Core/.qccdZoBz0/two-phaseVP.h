#ifndef BASILISK_HEADER_24
#define BASILISK_HEADER_24
#line 1 "./two-phaseVP.h"
/**
# Two-phase interfacial flows

This file helps setup simulations for flows of two fluids separated by
an interface (i.e. immiscible fluids). It is typically used in
combination with a [Navier--Stokes solver](navier-stokes/centered.h).

The interface between the fluids is tracked with a Volume-Of-Fluid
method. The volume fraction in fluid 1 is $f=1$ and $f=0$ in fluid
2. The densities and dynamic viscosities for fluid 1 and 2 are *rho1*,
*mu1*, *rho2*, *mu2*, respectively. */

#include "vof.h"

scalar f[], * interfaces = {f};
scalar D2[];
face vector D2f[];
double rho1 = 1., mu1 = 0., rho2 = 1., mu2 = 0.;
double mumax = 0., tauy = 0.;
/**
Auxilliary fields are necessary to define the (variable) specific
volume $\alpha=1/\rho$ as well as the cell-centered density. */

face vector alphav[];   // VELOCITIES ON FACE OF GRID??
scalar rhov[];

event defaults (i = 0) {
  alpha = alphav;
  rho = rhov;

  /**
  If the viscosity is non-zero, we need to allocate the face-centered
  viscosity field. */

  if (mu1 || mu2)  // ????????
    mu = new face vector;
}

/**
The density and viscosity are defined using arithmetic averages by
default. The user can overload these definitions to use other types of
averages (i.e. harmonic). */

#ifndef rho
# define rho(f) (clamp(f,0.,1.)*(rho1 - rho2) + rho2)
#endif
#ifndef mu
# define mu(muTemp, mu2, f)  (clamp(f,0.,1.)*(muTemp - mu2) + mu2)
#endif

/**
We have the option of using some "smearing" of the density/viscosity
jump. */

#ifdef FILTERED
scalar sf[];
#else
# define sf f
#endif

event properties (i++) {

  /**
  When using smearing of the density jump, we initialise *sf* with the
  vertex-average of *f*. */

// IGNORE THIS BIT 
#ifndef sf
#if dimension <= 2
  foreach()
    sf[] = (4.*f[] +
	    2.*(f[0,1] + f[0,-1] + f[1,0] + f[-1,0]) +
	    f[-1,-1] + f[1,-1] + f[1,1] + f[-1,1])/16.;
#else // dimension == 3
  foreach()
    sf[] = (8.*f[] +
	    4.*(f[-1] + f[1] + f[0,1] + f[0,-1] + f[0,0,1] + f[0,0,-1]) +
	    2.*(f[-1,1] + f[-1,0,1] + f[-1,0,-1] + f[-1,-1] +
		f[0,1,1] + f[0,1,-1] + f[0,-1,1] + f[0,-1,-1] +
		f[1,1] + f[1,0,1] + f[1,-1] + f[1,0,-1]) +
	    f[1,-1,1] + f[-1,1,1] + f[-1,1,-1] + f[1,1,1] +
	    f[1,1,-1] + f[-1,-1,-1] + f[1,-1,-1] + f[-1,-1,1])/64.;
#endif
#endif


// LOOK AT THIS BIT 
#if TREE
  sf.prolongation = refine_bilinear;
  boundary ({sf});
#endif

  foreach_face(x) {
    double ff = (sf[] + sf[-1])/2.;
    alphav.x[] = fm.x[]/rho(ff);
    double muTemp = mu1;
    face vector muv = mu;
    double D11 = (u.x[] - u.x[-1,0]);
    double D22 = ((u.y[0,1]-u.y[0,-1])+(u.y[-1,1]-u.y[-1,-1]))/4.0;
    double D12 = 0.5*(((u.x[0,1]-u.x[0,-1])+(u.x[-1,1]-u.x[-1,-1]))/4.0 + (u.y[] - u.y[-1,0]));
    double D2 = sqrt(sq(D11)+sq(D22)+2.0*sq(D12))/(Delta);
    if (D2 > 0. && tauy > 0.){
      double temp = tauy/(sqrt(2.)*D2) + mu1;
      muTemp = min(temp, mumax);
    } else {
      if (tauy > 0.){
        muTemp = mumax;
      } else {
        muTemp = mu1;
      }
    }
    muv.x[] = fm.x[]*mu(muTemp, mu2, ff);
    D2f.x[] = D2;
  }

  foreach_face(y) {
    double ff = (sf[0,0] + sf[0,-1])/2.;
    alphav.y[] = fm.y[]/rho(ff);
    double muTemp = mu1;
    face vector muv = mu;
    double D11 = (u.y[0,0] - u.y[0,-1])/Delta;
    double D22 = 0.5*( (u.x[1,0] - u.x[-1,0] + u.x[1,-1] - u.x[-1,-1])/(2.*Delta) );
    double D12 = 0.5*( (u.x[0,0] - u.x[0,-1])/Delta + 0.5*( (u.y[1,0] - u.y[-1,0] + u.y[1,-1] - u.y[-1,-1])/(2.*Delta) ) );

    double D2 = sqrt( sq(D11) + sq(D22) + 2*sq(D12) );
    if (D2 > 0. && tauy > 0.){
      double temp = tauy/(sqrt(2.)*D2) + mu1;
      muTemp = min(temp, mumax);
    } else {
      if (tauy > 0.){
        muTemp = mumax;
      } else {
        muTemp = mu1;
      }
    }
    muv.y[] = fm.y[]*mu(muTemp, mu2, ff);
    D2f.y[] = D2;
  }

  foreach(){
    rhov[] = cm[]*rho(sf[]);
    D2[] = (D2f.x[]+D2f.y[]+D2f.x[1,0]+D2f.y[0,1])/4.;
    if (D2[] > 0.){
      D2[] = log(D2[])/log(10);
    } else {
      D2[] = -10;
    }
  }
  boundary(all);
#if TREE
  sf.prolongation = fraction_refine;
  boundary ({sf});
#endif
}


#endif

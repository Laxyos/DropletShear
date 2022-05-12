/**
 * @file getDeformation.c
 * @author Tom
 * @brief 
 * @version 0.2
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// Last updated on 8-Feb-2022




#include "navier-stokes/centered.h"
#include "fractions.h"


// the name of the file
char filename[80];
// volume of fluid (0 inside droplet)
scalar f[];

double Ldomain;

int main(int a, char const *arguments[])
{
    sprintf (filename, "%s", arguments[1]);
    Ldomain = atof(arguments[2]);

    restore (file = filename);
    f.prolongation = fraction_refine;
    boundary ((scalar *){f});

    L0 = Ldomain;                                
    origin (-L0/2, -L0/2.);

    /* First let us find the COM of the droplet
    */

    double wt = 0., xcm = 0., ycm = 0.;

    foreach(reduction(+:wt), reduction(+:xcm), reduction(+:ycm)){
        wt += (1.-f[])*sq(Delta);
        xcm += (1.-f[])*x*sq(Delta);
        ycm += (1.-f[])*y*sq(Delta);
    }

    // fprintf(ferr,"%f %f %f\n", wt, xcm, ycm);
    xcm /= wt; ycm /= wt;
    // fprintf(ferr,"%f %f %f\n", wt, xcm, ycm);

    /*
    Vatsal's method of circles
    */

    // initial bounds on droplet dimensions
    double r_min = 0, r_max = 0;

    // set the range of integrating circle radii
    double R_step = 0.01, R_max = Ldomain;

    // tolerances
    double tolerance = 0.00001;

    // intial temporary area of droplet
    double Area_temp = 0;

    // for all possible integrating circles
    for (double R = R_step; R < R_max; R += R_step){

        // area of integrating circle
        double Area_c = pi*sq(R);
        
        // area of droplet interesect int. circle.
        double Area_d = 0;
        
        // for each stencil in grid
        foreach(reduction(+:Area_d)){
            // radial distance from origin to stencil
            double r = sqrt(sq(x-xcm) + sq(y-ycm));
            // if stencil is in the circle
            if (r < R){
                // add intersecting area of stencil
                Area_d += (1.-f[])*sq(Delta);
            }
        }

        // ratio of drop intersect circle and circle
        double ratio = Area_d/Area_c;

        // if ratio drops below 1, update rmin.
        if (ratio > 1. - tolerance){
            r_min = R;
        }

        // if drop area increases, update rmax
        if (Area_d > Area_temp + tolerance){
            r_max = R;
            // update temporary maximum area
            Area_temp = Area_d; 
        }
    }

    /* 
    Now we implement Tom's method
    Assuming rotational symmetry, find the interfacial location farthest away from 
    the center of mass of the droplet. That will give r_max2. Then, find the interfacial
    location nearest to the center of mass of the droplet. That will give r_min2. 
    Here, we save the coordinates (xImax, yImax) and (xImin, yImin) as well
    */

    double xImax = 0., xImin = 0., yImax = 0., yImin = 0.;
    // also distances
    double r_max2 = 0., r_min2 = HUGE; // rmin is intialized with a large number

    face vector s[]; // need s for normal construction (see below)
    s.x.i = -1; // just book keeping -- ignore
    foreach(reduction(+:r_max2), reduction(+:r_min2), reduction(+:xImax), reduction(+:xImin), reduction(+:yImax), reduction(+:yImin)){
        if (y > ycm){// assuming rotational symmetry

            // check whether or not this is an interfacial cell
            if (f[] > 1e-6 && f[] < 1. - 1e-6){
                coord n = facet_normal (point, f, s); // construct normal to the interface
                double alpha = plane_alpha (f[], n); // construct the intercept. remember y = mx+ alpha
                coord segment[2]; // where the interfacial coordinates are saved

                // we should only move forward if there both points of the interfacial line segment is in this cell. We want to skip cells which merely touches the interface
                if (facets (n, alpha, segment) == 2){
                    /* 
                    the two points on the interface are essentially segment[0] and segment[1].
                    So, we can find the centroid of the interface in this cell.
                    */
                    double xc = x + (segment[0].x+segment[1].x)*Delta/2.;
                    double yc = y + (segment[0].y+segment[1].y)*Delta/2.;

                    // calculate the distance of this interfacial location from the ceneter of mass of the droplet
                    double rTemp = sqrt(sq(xc-xcm) + sq(yc-ycm));

                    // checl for rmax2 and rmin2
                    if (rTemp > r_max2){
                        r_max2 = rTemp;
                        xImax = xc; yImax = yc;
                    }
                    if (rTemp < r_min2){
                        r_min2 = rTemp;
                        xImin = xc; yImin = yc;
                    }
                }
            }
            
        }
    }



    // compute the Taylor Deformation Vatsal
    double deform = (r_max/r_min - 1)/(r_max/r_min + 1);
    // compute the Taylor Deformation Tom
    double deform2 = (r_max2/r_min2 - 1)/(r_max2/r_min2 + 1);

    double theta = atan((yImax-ycm)/(xImax-xcm))*180./M_PI;

    // print the minimal, maximal dimensions and T.D.
    fprintf(ferr, "%f %f %f %f %f %f %f %f %f %f %f %f %f\n", xcm, ycm, r_min, r_max, deform, xImin, yImin, r_min2, xImax, yImax, r_max2, deform2, theta);
}


            


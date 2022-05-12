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
    sprintf(filename, "%s", arguments[1]);
    
    periodic (right);

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


    double Bi = atof(arguments[2]);
    double totalD2 = 0;
    double totalTau = 0;

    foreach( reduction(+:totalD2) , reduction(+:totalTau)){
        D2[] = (D2f.x[]+D2f.y[]+D2f.x[1,0]+D2f.y[0,1])/4.;
        if (D2[] > 0.){
        D2[] = log(D2[])/log(10);
        } else {
        D2[] = -10;
        }
        double littleD2 = pow(10, D2[])*sq(Delta);
        // double littleTau = 2*littleD2 + Bi;

        double littleTau = (2*pow(10, D2[]) + Bi)*sq(Delta);
        totalD2 += littleD2;
        totalTau += littleTau;
    }
    //FILE * fp = ferr;
    fprintf(ferr, "%f %f", totalD2, totalTau);
}

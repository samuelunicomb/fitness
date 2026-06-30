#ifndef LAB_TOPOLOGYDIR_H_
#define LAB_TOPOLOGYDIR_H_

#include <string>

#include "topology.h"
//#include "pkdistributions.h"
//#include "utilitystructures.h"

/*

high-level network structure details, used in both *graph*.h and *config*.h

*/
class topologydir : public topology
{
  public:

    // arguments are out- and in-degree distributions
    topologydir(){};
    topologydir(pkregular, pkregular);
    topologydir(pkregular, pkpoisson);
    topologydir(pkregular, pkpoissonmin);
    topologydir(pkregular, pkexponential);
    topologydir(pkpowerlaw, pkpoisson);
    topologydir(pkpowerlaw, pkregular);

    string degreedisto, degreedisti;

    // parameters particular to degree distribution
    struct{double z; int k;} regulari;
    struct{double z;} poissoni;
    struct{double z, zresultant; int kmin, kmax;} poissoncuti;
    struct{double z, zresultant; int kmin, kmax;} poissonmini;
    struct{double z, sigma, sigmascale;} lognormali;
    struct{double z, alpha; int kmin, kmax;} powerlawi;
    struct{double z, kappa;} exponentiali;
    struct{double z; int kmin, kmax;} bimodali;

    struct{double z; int k;} regularo;
    struct{double z;} poissono;
    struct{double z, zresultant; int kmin, kmax;} poissoncuto;
    struct{double z, zresultant; int kmin, kmax;} poissonmino;
    struct{double z, sigma, sigmascale;} lognormalo;
    struct{double z, alpha; int kmin, kmax;} powerlawo;
    struct{double z, kappa;} exponentialo;
    struct{double z; int kmin, kmax;} bimodalo;
};
#endif

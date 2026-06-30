#ifndef LAB_TOPOLOGY_H_
#define LAB_TOPOLOGY_H_

#include <string>

#include "pkdistributions.h"
#include "utilitystructures.h"

/*

high-level network structure details, used in both *graph*.h and *config*.h

*/
class topology
{
  public:

    // constructors, for configuration spaces and graphs
    topology(){};
    topology(pkregular);
    topology(pkpoisson);
    topology(pkpoissoncut);
    topology(pkpoissonmin);
    topology(pklognormal);
    topology(pkpowerlaw);
    topology(pkexponential);
    topology(pkbimodal);
    topology(pktrilattice);
    topology(pktriangles);
    topology(pksbm);

    unsigned int netsize, n, m;  // number of nodes, edgetypes, active edges

    //int M; // TEMPORARY, WHILE UNTANGLING GRAPH.H AND GRAPHMUL.H
    string degreedist;

    double z, zresultant, zoriginal, zburn, var;

    vector<double> vz, pw;
    double varz;

    set<int> pksupport;
    map<int, double> pk;

    vector<weight> wdist;                   // vector of weight, density pairs
    vector<degree> kdist;                   // vector of degree, mass pairs

    // sampling integers to form degree sequence
    void sampleregular(int, vector<int>&);
    void samplepoisson(int, vector<int>&);
    void samplepoissoncut(int, vector<int>&);
    void samplepoissonmin(int, vector<int>&);
    void samplelognormal(int, vector<int>&);
    void sampleexponential(int, vector<int>&);
    void samplepowerlaw(int, vector<int>&);
    void samplebimodal(int, vector<int>&);

    // parameters particular to degree distribution
    struct {double z; int k;} regular;
    struct {double z;} poisson;
    struct {double z, zresultant; int kmin, kmax;} poissoncut;
    struct {double z, zresultant; int kmin, kmax;} poissonmin;
    struct {double z, sigma, sigmascale;} lognormal;
    struct {double z, alpha; int kmin, kmax;} powerlaw;
    struct {double z, kappa;} exponential;
    struct {double z; int kmin, kmax;} bimodal;
    struct {int lwidth, lheight;} trilattice;
    struct {int ksum; double ptri;} triangles;
    struct {double c1; double z1; double z2; double z12;} sbm;
};
#endif

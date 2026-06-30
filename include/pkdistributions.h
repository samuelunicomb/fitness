#ifndef LAB_PKDISTRIBUTIONS_H_
#define LAB_PKDISTRIBUTIONS_H_

#include <cmath>
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>

/*

This file contains structures containing degree distribution parameters.

Used in topology*.h constructors, and in turn *graph*.h and *config*.h constructors.

*/
struct pkregular
{
  pkregular(int a){ k = a; }

  int k;
};

struct pkpoisson
{
  pkpoisson(double a){ z = a; kmin = 0; kmax = std::min(int(5 * a), 15); }
  pkpoisson(double a, int b){ z = a; kmax = b; }

  double z;
  int kmin, kmax;
};

struct pkpoissoncut
{
  pkpoissoncut(double a, int b){ z = a; kmin = 0; kmax = b; }
  pkpoissoncut(double a, int b, int c){ z = a; kmin = b; kmax = c; }

  double z;
  int kmin, kmax;
};

struct pkpoissonmin
{
  pkpoissonmin(double a){ z = a; kmin = 0; kmax = std::min(int(5 * a), 15); }
  pkpoissonmin(double a, int b, int c){ z = a; kmin = b; kmax = c; }

  double z;
  int kmin, kmax;
};

struct pklognormal
{
  pklognormal(double a, double b){ z = a; sigma = b; kmin = 0; kmax = int(2 * a); }
  pklognormal(double a, double b, double c){ z = a; sigma = b; sigmascale = c; kmin = 0; kmax = int(2 * a); }
  pklognormal(double a, double b, int c, int d){ z = a; sigma = b; kmin = c; kmax = d; }

  double z, sigma, sigmascale;
  int kmin, kmax;
};

struct pkexponential
{
  pkexponential(double a){ z = a; calculatekappa(); }
  pkexponential(double a, int b, int c){ z = a; kmin = b; kmax = c; }

  double z, kappa;
  int kmin, kmax;

  void calculatekappa(){
    kappa = 1 / log(1 / z + 1);
  }
};

struct pkpowerlaw
{
  pkpowerlaw(double a){ z = a; alpha = 2.5; kmin = 1; }

  // TODO note that this is the constructor you use in fitness study
  pkpowerlaw(double a, int b, int c){
    alpha = a; kmin = b; kmax = c - 1; 

    calculatez();
  }

  // std::string argument is a dummy to allow overloading
  //pkpowerlaw(double a, int b, int c){
  //  ztarget = a; 
  //  kmin = b;
  //  kmax = c;
  //  locatealpha();

  //  assert(alpha > 1.0);
  //  assert(z < 1.05 * ztarget && z > 0.95 * ztarget);
  //}

  pkpowerlaw(double a, int b){
    ztarget = a; 
    kmax = b;
    locatealphakmin();

    assert(alpha > 1.0);
    assert(z < 1.05 * ztarget && z > 0.95 * ztarget);
  }

  // calculate average degree induced by kmin, kmax and alpha
  void calculatez(){
    double norm = 0;
    for(int i = kmin; i <= kmax; ++i)
      norm += pow(i, -alpha);

    z = 0;
    for(int i = kmin; i <= kmax; ++i)
      z += i * pow(i, -alpha) / norm;
  }

  // bisection method to locate alpha, which must be greater than 1
  void locatealpha(){
    double alphalo = 0.1;
    double alphahi = 15;
    while(alphahi - alphalo > 1e-4){
      alpha = (alphalo + alphahi) / 2.0;
      calculatez();
      if(z > ztarget)
        alphalo = alpha;
      else
        alphahi = alpha;
    }
  }

  // find the kmin for which alpha is closest to 2.5
  void locatealphakmin(){
    double dalpha = 100;
    int kminopt = 2;
    for(int k = 2; k < kmax; ++k){
      kmin = k;
      locatealpha();
      if(abs(alpha - 2.5) < dalpha){
        kminopt = k;
        dalpha = abs(alpha - 2.5);
      }
    }
    kmin = kminopt;
    locatealpha();
  }

  double z, alpha, ztarget;
  int kmin, kmax;
};

struct pkbimodal
{
  pkbimodal(int a, int b){ kmin = a; kmax = b; }

  double z;
  int kmin, kmax;
};

// triangular lattice, lattice width and lattice height
struct pktrilattice
{
  pktrilattice(int a){ lwidth = a; lheight = a; }

  double z;
  int lwidth, lheight;
};

struct pktriangles
{
  pktriangles(int a, double b){ k = a; p = b; }

  int k;             // total adjacent dyads, e.g. one adjacent triangle contains two dyads
  double p;          // fraction of pairs of edges that are part of a triangle

  /* 
  1. if a node has k = 2, with probability p they are part of a triangle
  2. if a node has k = 3 and p = 1, then one edge will be a singlet, and two
  will form a triangle, since triangles are disjoint.
  3. if a node has k = 4, then it either has four singlets, two singlets and
  one triangle, or two triangles, depending on the value of p. If p = 0, then
  all edges are singlets, if p = 0.5, some will be singlets and some
  triangles, if p = 1, then each node is adjacent to two disjoint triangles.
  */
};

// stochastic block model parameters
struct pksbm
{
  pksbm(double a1, double a2, double a3, double a4){ 
    c1 = a1;
    z1 = a2;
    z2 = a3;
    z12 = a4;
  }

  double z;           // total average degree
  double z1, z2, z12; // average degree within group 1 and 2, and between them
  double c1;          // fraction of nodes in group 1
};
#endif

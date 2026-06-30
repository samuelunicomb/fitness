#include "topology.h"

#include <iostream>

#include "utilityfunctions.h"

topology::topology(pkregular p)
{
  degreedist = "regular";
  regular.k = p.k;
  pksupport = set<int>{p.k};
  pk = map<int, double>{{p.k, 1.0}};
  vz = vector<double>{double(p.k)};
  z = double(p.k);
}

/*

constructors based on poisson degree distribution

*/
topology::topology(pkpoisson p)
{
  degreedist = "poisson";

  poisson.z = p.z;
  z = p.z;

  pksupport = set<int> {};
  pk = map<int, double> {};

  for(int i = p.kmin; i < p.kmax + 1; ++i) {
    pksupport.insert(i);
    pk[i] = poisson_mpfr(i, z);
  }

  vz = vector<double>{double(p.z)};
}

topology::topology(pkpoissoncut p)
{
  degreedist = "poissoncut";

  poissoncut.z = p.z;
  poissoncut.kmin = p.kmin;
  poissoncut.kmax = p.kmax;
  z = p.z;

  pksupport = set<int> {};
  pk = map<int, double> {};

  double norm = 0;
  for(int i = p.kmin; i < p.kmax + 1; ++i) {
    pksupport.insert(i);
    pk[i] = poisson_mpfr(i, z);
    norm += pk[i];
  }

  zresultant = 0;
  for(auto &it : pk) {
    it.second /= norm;
    zresultant += it.first * it.second;
  }
  poissoncut.zresultant = zresultant;

  vz = vector<double>{zresultant};
}

/*

constructors based on exponential degree distribution

*/
topology::topology(pkexponential p)
{
  degreedist = "exponential";

  exponential.z = p.z;
  exponential.kappa = p.kappa;
  z = p.z;

  pksupport = set<int> {};
  pk = map<int, double> {};

  for(int i = p.kmin; i < p.kmax + 1; ++i) {
    pksupport.insert(i);
    pk[i] = poisson_mpfr(i, z);
  }

  vz = vector<double>{z};
}

/*

Constructors based on power law degree distribution.

FIXME pkpowerlaw has multiple constructors, will this work with all of them?
code below assumes we supplyt target z, kmin, and kmax, then tunes alpha 
accordingly. but not all constructors assume these variables to be fixed.

*/
topology::topology(pkpowerlaw p)
{
  degreedist = "powerlaw";

  // and if kmin and kmax haven't been provided to p...?
  powerlaw.kmin = p.kmin;
  powerlaw.kmax = p.kmax;
  powerlaw.alpha = p.alpha;

  pksupport = set<int>{};
  pk = map<int, double>{};

  double norm = 0;
  for(int i = p.kmin; i <= p.kmax; ++i)
    norm += pow(i, -p.alpha);

  z = 0;
  var = 0;
  for(int i = p.kmin; i <= p.kmax; ++i){
    pksupport.insert(i);
    pk[i] = pow(i, -p.alpha) / norm;
    z += i * pk[i];
    var += i * i * pk[i];
  }
  var -= z * z;

  powerlaw.z = p.z;
  z = p.z;

  vz = vector<double>{z};
}

// constructor based on bimodal distribution
topology::topology(pkbimodal p)
{
  degreedist = "bimodal";

  bimodal.kmin = p.kmin;
  bimodal.kmax = p.kmax;

  pksupport = set<int> {p.kmin, p.kmax};
}

// constructor based on triangular lattice
topology::topology(pktrilattice p)
{
  degreedist = "trilattice";

  trilattice.lwidth = p.lwidth;
  trilattice.lheight = p.lheight;
}

//// constructor based on configuration model with triangles
//topology::topology(pktriangles p)
//{
//  degreedist = "triangles";
//
//  // we assume k regular, k being total degree, i.e. single plus triangle edges
//  triangles.ksum = p.ksum;     // int
//  triangles.ptri = p.ptri;     // double
//
//  for(int i = 0; i <= p.ksum / 2; ++i){
//    vector<int> dummy{p.ksum - 2 * i, i};  
//
//    //pkmulsupport.insert(dummy);
//    //pkmul[dummy] = ?
//  }
//
//  //pkmulsupport = set<vector<int>>{p.k};
//  //pkmul = map<vector<int>, double>{{p.k, 1.0}};
//}

// constructor based on stochastic block model
topology::topology(pksbm p)
{
  degreedist = "sbm";

  sbm.c1 = p.c1;   // fraction of nodes in the first community
  sbm.z1 = p.z1;   //
  sbm.z2 = p.z2;   //
  sbm.z12 = p.z12; //
}

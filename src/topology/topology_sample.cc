#include "topology.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;

/*

used for batch inverse-transform sampling

*/
static void sampleuniform(int count, vector<double> &p)
{
  mt19937 gen(random_device{}());
  uniform_real_distribution<double> distribution(0, 1);
  p = vector<double>{};

  for(long int i = 0; i < count; ++i)
    p.push_back(distribution(gen));

  sort(p.begin(), p.end());
}

/*

simply fills the vector kset with desired integer

*/
void topology::sampleregular(int count, vector<int> &kset)
{
  kset = vector<int> (count, regular.k);
}

/*

simple wrappers for <random> poisson functions

*/
void topology::samplepoisson(int count, vector<int> &kset)
{
  mt19937 gen(random_device{}());
  poisson_distribution<int> distribution(poisson.z);
  kset = vector<int>{};

  for(int i = 0; i != count; ++i) 
    kset.push_back(distribution(gen));
}

void topology::samplepoissoncut(int count, vector<int> &kset) // rename poissonmax?
{
  mt19937 gen(random_device{}());
  poisson_distribution<int> distribution(poissoncut.z);
  kset = vector<int>{};

  for(int i = 0; i != count; ++i){
    int k = poissoncut.kmax + 1;
    while(k > poissoncut.kmax) 
      k = distribution(gen);
    kset.push_back(k);
  }
}

void topology::samplepoissonmin(int count, vector<int> &kset)
{
  mt19937 gen(random_device{}());
  poisson_distribution<int> distribution(poissonmin.z);
  kset = vector<int>{};

  for(int i = 0; i != count; ++i) {
    int k = 0;
    while(k < 1) 
      k = distribution(gen);
    kset.push_back(k);
  }
}

/*

simple wrapper for <random> lognormal function

*/
void topology::samplelognormal(int count, vector<int> &kset)
{
  mt19937 gen(random_device{}());

  lognormal_distribution<double> distribution;

  double m = lognormal.z;
  double s = lognormal.sigma;

  double mnormal = log(pow(m, 2) / sqrt(pow(m, 2) + pow(s, 2)));
  double snormal = sqrt(log(pow(s, 2) / pow(m, 2) + 1));
  distribution = lognormal_distribution<double>(mnormal, snormal);
  
  kset = vector<int>{};

  for(int i = 0; i != count; ++i){
    kset.push_back(int(round(distribution(gen))));
  }
}

/*

uses batch inverse transform sampling. assumes z given, calculates kappa

*/
void topology::sampleexponential(int count, vector<int> &kset)
{
  vector<double> p;
  sampleuniform(count, p);

  kset = vector<int>{};

  exponential.kappa = 1 / log(1 / exponential.z + 1);

  int k = 0;
  double pk = 1 - exp((-1 * k - 1) / exponential.kappa);
  for(unsigned int i = 0; i < p.size(); ++i){
    while(p[i] > pk){
      k += 1;
      pk = 1 - exp((-1 * k - 1) / exponential.kappa);
    }
    kset.push_back(k);
  }
  shuffle(kset.begin(), kset.end(), mt19937(random_device{}()));
}

// Helper function, calculates the Hurwitz, or incomplete zeta function.
static void hurwitz(double alpha, int kmin, int kmax, map<int, double> &cdf)
{
  map<int, double> pmf;

  double norm = 0;
  for(int k = kmin; k < kmax + 1; ++k){ // double check norm
    pmf[k] = pow(k, -alpha);
    norm += pmf[k];
  }

  for(auto &it : pmf) it.second /= norm;

  double dummy = 0;
  cdf = map<int, double>{};
  for(int k = kmin; k < kmax + 1; ++k){
    dummy += pmf[k];
    cdf[k] = dummy;
  }
  cdf[kmax] = 1;
}

// Batch inverse transform sampling of the power-law degree distribution.
void topology::samplepowerlaw(int count, vector<int> &kset)
{
  vector<double> p;
  sampleuniform(count, p);
  map<int, double> f;

  if(powerlaw.kmax < powerlaw.kmin) powerlaw.kmax = netsize;

  hurwitz(powerlaw.alpha, powerlaw.kmin, powerlaw.kmax, f); // see above

  int k = powerlaw.kmin;
  double pk = f[k];
  kset = vector<int>{};

  for(unsigned int i = 0; i < p.size(); ++i){
    while(p[i] > pk){
      k += 1;
      pk = f[k];
    }
    kset.push_back(k);
  }
}

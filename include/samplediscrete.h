#ifndef LAB_SAMPLEDISCRETE_H_
#define LAB_SAMPLEDISCRETE_H_

#include <vector>

using namespace std;

// DEPRECATED! THESE ARE HANDLED IN TOPOLOGY.H NOW

// random regular degree distribution, single
int randomsample_rr (double z);

// Erdos-Renyi degree distribution, single
int randomsample_er (double z);

// scale free dergee distribution, single
int randomsample_sf (double z, double alpha);

// lognormal degree distribution, single
int randomsample_ln (double z, double sigma_k);

// exponential degree distribution, single
int randomsample_exp (double kappa);

// random regular degree distribution, set
vector<int> randomsample_rr (int count, double z);

// Erdos-Renyi degree distribution, set
vector<int> randomsample_er (int count, double z);

// scale-free dergee distribution, set
vector<int> randomsample_sf (int count, double z, double alpha);

// log-normal degree distribution, set
vector<int> randomsample_ln (int count, double z, double sigma_k);

// exponential degree distribution, set
vector<int> randomsample_exp (int count, double kappa);

#endif

#include "graphdir.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

/*

builds a directed network with specified in- and out-distributions

network = vector<map<int, stub>> avoids double edges but allows loops

*/

static set<set<int>> alledges; // NEED TO INCLUDE THIS

void graphdir::build(){
  alledges.clear();

  network = vector<vector<stub>> (top.netsize);

  vector<stub> stubseto = buildstubset(top.degreedisto, 0); // out edges
  vector<stub> stubseti = buildstubset(top.degreedisti, 1); // in edges

  wirestubsets(stubseto, stubseti);
}

vector<stub> graphdir::buildstubset(string degreedist, int edgetype){
  vector<int> kset;
  if(degreedist == "regular") top.sampleregular(top.netsize, kset);
  if(degreedist == "poisson") top.samplepoisson(top.netsize, kset);
  if(degreedist == "poissonmin") top.samplepoissonmin(top.netsize, kset);
  if(degreedist == "exponential") top.sampleexponential(top.netsize, kset);
  if(degreedist == "powerlaw") top.samplepowerlaw(top.netsize, kset);

  shuffle(begin(kset), end(kset), mt19937(random_device {} ()));

  vector<stub> stubset;
  for(unsigned int i = 0; i != kset.size(); ++i)
    for(int j = 0; j < kset[i]; ++j)
      stubset.push_back(stub {int(i), edgetype});
  shuffle(begin(stubset), end(stubset), mt19937(random_device {} ()));

  if(stubset.size() % 2 == 1) stubset.pop_back();

  return stubset;
}

void graphdir::wirestubsets(vector<stub> &stubseto, vector<stub> &stubseti){
  for(unsigned int i = 0; i != stubseto.size(); ++i){
    if(stubseti.size() > i) {
      int u = stubseto[i].nodeindex;
      int v = stubseti[i].nodeindex;

      if(u != v && alledges.find(set<int> {u, v}) == alledges.end()) {
        network[stubseto[i].nodeindex].push_back(stub {stubseti[i].nodeindex, 0});
        //TODO uncomment if you need the in-degree distribution
        //network[stubseti[i].nodeindex].push_back(stub {stubseto[i].nodeindex, 1});

        alledges.insert(set<int> {u, v});
      }
    }
  }

  //mt19937 gendummy(random_device {}());
  //uniform_int_distribution<int> uniformdummy(0, network.size() - 1);

  //for(int i = 0; i < network.size(); ++i)
  //{
  //  int kin = 0;
  //  for(int j = 0; j < network[i].size(); ++j)
  //  {
  //    if(network[i][j].edgetype == 1) ++kin;
  //  }
  //  if(kin == 0)
  //  {
  //    int l = uniformdummy(gendummy);
  //    network[i].push_back(stub {l, 1});
  //    network[l].push_back(stub {i, 0});
  //  }
  //}
}

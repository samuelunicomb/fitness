#include <iostream>

#include "fitness.h"

using namespace std;

void fitness::initialiserun()
{
  gen = mt19937(random_device{}());
  edist = exponential_distribution<double>(1.0);

  memes = map<unsigned long long int, memedata>{};
  screen = vector<unsigned long long int>(N);
  nodeevents = set<event>{};
  nodeeventsdic = vector<event>(N);
  ageevents = set<event>{};
  ageeventsdic = map<unsigned long long int, event>{};

  for(int i = 0; i < N; ++i){
    memes[(unsigned long long int)i] = samplememepars(0);
    screen[i] = (unsigned long long int)i;
    nodeeventsdic[i] = sampletimes((unsigned int)i, 0);
    nodeevents.insert(nodeeventsdic[i]);
    ageeventsdic[(unsigned long long int)i] = event{(unsigned long long int)i, Tage};
    ageevents.insert(ageeventsdic[(unsigned long long int)i]);
  }
}

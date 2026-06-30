#include <iostream>

#include "fitness.h"

using namespace std;

void fitness::initialiserun()
{
  gen = mt19937(random_device{}());
  edist = exponential_distribution<double>(1.0);

  memes = map<unsigned int, memedata>{};
  screen = vector<unsigned int>(N);
  nodeevents = set<event>{};
  nodeeventsdic = vector<event>(N);
  ageevents = set<event>{};
  ageeventsdic = map<unsigned int, event>{};

  for(int i = 0; i < N; ++i){
    memes[(unsigned int)i] = samplememepars(0);
    screen[i] = (unsigned int)i;
    nodeeventsdic[i] = sampletimes((unsigned int)i, 0);
    nodeevents.insert(nodeeventsdic[i]);

    ageeventsdic[(unsigned int)i] = event{(unsigned int)i, Tage};
    ageevents.insert(ageeventsdic[(unsigned int)i]);
  }
}

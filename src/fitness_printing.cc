#include <iostream>
#include <cassert>
#include <algorithm>

#include "fitness.h"

using namespace std;

void fitness::sanitycheck()
{
  unsigned int abundance = 0;
  for(auto it : memes) abundance += it.second.abundance;

  assert(G.top.netsize == int(abundance));
  assert(G.top.netsize == int(nodeevents.size()));
  assert(ageevents.size() == ageeventsdic.size());
}


void fitness::print_popularity(map<int, int> dist, int flag)
{
  dist.erase(0);

  int norm = 0;
  for(auto it : dist) norm += it.second;

  map<int, double> popularitycdf;
  double dummy = 0;
  for(auto it : dist){
    popularitycdf[it.first] = dummy / norm;
    dummy += it.second;
  }

  for(auto it : popularitycdf){
    cout << it.first << " ";
    cout << 1 - it.second << " ";
    cout << "flag" << flag << " ";
    cout << endl;
  }
}


void fitness::print_popularity()
{
  agedist.erase(0);

  int norm = 0;
  for(auto it : agedist) norm += it.second;

  map<int, double> popularitycdf;
  double dummy = 0;
  for(auto it : agedist){
    popularitycdf[it.first] = dummy / norm;
    dummy += it.second;
  }

  for(auto it : popularitycdf){
    cout << it.first << " ";
    cout << 1 - it.second << " ";
    for(unsigned int i = 0; i < printargs.size(); ++i)
      cout << "arg" << i << " " << printargs[i] << "_ ";
    cout << endl;
  }
}


void fitness::print_abundance()
{
  vector<unsigned int> abundance;
  for(auto it : memes)
    abundance.push_back(it.second.abundance);

  sort(abundance.begin(), abundance.end(), greater<unsigned int>());

  unsigned int i = 0;
  cout << "# ";
  cout << Tage << " ";
  while(i < 5 && i < abundance.size()){
    cout << abundance[i] / double(G.top.netsize) << " ";
    ++i;
  }
  for(unsigned int i = 0; i < printargs.size(); ++i)
    cout << "arg" << i << " " << printargs[i] << " ";
  cout << endl;
}

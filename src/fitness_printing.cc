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


void fitness::strajcheck()
{
  set<memedatasorted> smax;
  for(auto it : memes)
    smax.insert(memedatasorted(it.first, it.second.abundance, it.second.wr));

  set<memedatasorted>::reverse_iterator sit;
  sit = smax.rbegin();
  int count = 20;
  cout << t << " ";
  for(int i = 0; i < count; ++i){
    if(sit != smax.rend()){
      cout << sit->abundance << " ";
      ++sit;
    }else{
      cout << 0 << " "; 
    }
  }

  sit = smax.rbegin();
  for(int i = 0; i < count; ++i){
    if(sit != smax.rend()){
      cout << sit->id << " ";
      ++sit;
    }else{
      cout << 0 << " "; 
    }
  }

  sit = smax.rbegin();
  for(int i = 0; i < count; ++i){
    if(sit != smax.rend()){
      cout << sit->wr << " ";
      ++sit;
    }else{
      cout << 0 << " "; 
    }
  }
  cout << endl;

  //multiset<int> smax;
  //for(auto it : memes)
  //  smax.insert(it.second.abundance);

  //multiset<int>::reverse_iterator sit;
  //sit = smax.rbegin();
  //cout << t << " ";
  //for(int i = 0; i < 20; ++i){
  //  if(sit != smax.rend()){
  //    cout << *sit << " ";
  //    ++sit;
  //  }else{
  //    cout << 0 << " ";
  //  }
  //}
  //cout << "abundances ";
  //cout << "N" << N << " ";
  //cout << endl;


  //for(auto it : memes){
  //  double rho = it.second.abundance / double(G.top.netsize);
  //  if(rho > 0.1){
  //    straj[it.first].rho.push_back(vector<double>{t, rho});
  //    straj[it.first].w = int(100 * it.second.wr);
  //  }
  //}
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

  long long int norm = 0;
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
    cout << "arg" << i << " " << printargs[i] << "_ ";
  cout << endl;
}


void fitness::print_si()
{
  int bins = 100;
  vector<unsigned int> si_wr(bins + 1, 0), si_wb(bins + 1, 0);
  for(int i = 0; i < screen.size(); ++i){
    double wr = memes[screen[i]].wr;
    double wb = memes[screen[i]].wb;

    ++si_wr[int(bins * wr)];
    ++si_wb[int(bins * wb)];
  }

  for(unsigned int i = 0; i < si_wr.size(); ++i){
    cout << i / double(bins) << " ";
    cout << si_wr[i] / double(G.top.netsize) << " ";
    cout << si_wb[i] / double(G.top.netsize) << " ";

    for(unsigned int j = 0; j < printargs.size(); ++j)
      cout << "arg" << j << " " << printargs[j] << "_ ";

    cout << endl;
  }
}


void fitness::print_straj()
{
  int count = 0;
  for(auto it : straj){
    vector<vector<double>> s = it.second.rho;
    int w = it.second.w;
    for(int i = 0; i < s.size(); ++i){
      cout << s[i][0] << " ";  // t
      cout << s[i][1] << " ";  // s(t)
      cout << w << " ";
      cout << count << " ";  // meme id
      for(unsigned int j = 0; j < printargs.size(); ++j)
        cout << "arg" << j << " " << printargs[j] << "_ ";
      cout << endl;
    }
    ++count;
  }
}

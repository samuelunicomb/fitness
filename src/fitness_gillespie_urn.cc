#include <iostream>

#include "fitness.h"

using namespace std;

static uniform_int_distribution<int> uintdist;

void fitness::gillespie_urn()
{
  initialiserun();

  uintdist = uniform_int_distribution<int>(0, G.top.netsize - 1);

  u = (*nodeevents.begin()).u;
  t = (*nodeevents.begin()).t;
  type = (*nodeevents.begin()).type;

  uage = (*ageevents.begin()).u;
  tage = (*ageevents.begin()).t;

  count = 0;

  while(t < T){
    u = (*nodeevents.begin()).u;
    t = (*nodeevents.begin()).t;
    type = (*nodeevents.begin()).type;

    while(tage < t && ageevents.size() > 0){
      agedist[memes[uage].popularity] += 1;
      ageevents.erase(ageeventsdic[uage]);
      ageeventsdic.erase(uage);
      uage = (*ageevents.begin()).u;
      tage = (*ageevents.begin()).t;
    }

    count += 1;

    if(count % int(1 * N) == 0){
      fprintf(stderr, "    %8.3f / %6.0f ", t, T);
      fprintf(stderr, "%4d ", int(count / double(N)));
      fprintf(stderr, "%zu ", memes.size());
      fprintf(stderr, "\r");
      sanitycheck();
    }

    if(type == 0){
      // TODO following snippet is identical to that below, refactor
      if(memes[screen[u]].abundance == 1){
        if(ageeventsdic.find(screen[u]) != ageeventsdic.end()){
          agedist[memes[screen[u]].popularity] += 1;
          ageevents.erase(ageeventsdic[screen[u]]);
          ageeventsdic.erase(screen[u]);
          uage = (*ageevents.begin()).u;
          tage = (*ageevents.begin()).t;
        }
        assert(memes.find(screen[u]) != memes.end());
        memes.erase(screen[u]);
      }else{
        memes[screen[u]].abundance -= 1;
      }

      screen[u] = memes.rbegin()->first + 1;
      assert(memes.find(screen[u]) == memes.end());
      memes[screen[u]] = samplememepars(t);
      ageeventsdic[screen[u]] = event{screen[u], t + Tage};
      ageevents.insert(ageeventsdic[screen[u]]);
    }

    memes[screen[u]].popularity += 1;

    nodeevents.erase(nodeeventsdic[u]);
    nodeeventsdic[u] = sampletimes(u, t);
    nodeevents.insert(nodeeventsdic[u]);

    // choose k nodes uniformly at random, ignore the network
    set<int> neighbourstmp;
    while(neighbourstmp.size() < G.network[u].size()){
      int v = uintdist(gen);
      if(v != u) neighbourstmp.insert(v);
    }

    for(auto it : neighbourstmp){
      if(udist(gen) < memes[screen[u]].wb){
        int v = it;
        // TODO following snippet is identical to that above, refactor
        if(memes[screen[v]].abundance == 1){
          if(ageeventsdic.find(screen[v]) != ageeventsdic.end()){
            agedist[memes[screen[v]].popularity] += 1;
            ageevents.erase(ageeventsdic[screen[v]]);
            ageeventsdic.erase(screen[v]);
            uage = (*ageevents.begin()).u;
            tage = (*ageevents.begin()).t;
          }
          assert(memes.find(screen[v]) != memes.end());
          memes.erase(screen[v]);
        }else{
          memes[screen[v]].abundance -= 1;
        }

        screen[v] = screen[u];
        memes[screen[v]].abundance += 1;

        nodeevents.erase(nodeeventsdic[v]);
        nodeeventsdic[v] = sampletimes(v, t);
        nodeevents.insert(nodeeventsdic[v]);
      }
    }
  }

  fprintf(stderr, "                                                        \r");
}

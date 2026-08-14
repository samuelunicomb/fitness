#include <iostream>

#include "fitness.h"

using namespace std;

// When a meme is born, or first posted, give it a new id, and schedule its
// popularity measurement at t + Tage.
void fitness::memebirth(int u)
{
  unsigned long long int memeid = memes.rbegin()->first + 1;
  screen[u] = memeid;
  assert(memes.find(memeid) == memes.end());
  memes[memeid] = samplememepars(t);
  ageeventsdic[memeid] = event{memeid, t + Tage};
  ageevents.insert(ageeventsdic[memeid]);
}


// A meme dies when its abundance goes to zero, ie it is no longer on any screen.
void fitness::memedeath(int u)
{
  int memeid = screen[u];
  assert(memes.find(memeid) != memes.end());

  // A meme's popularity will be constant after its death. As such, if there's
  // still a popularity recording event set, you will no longer need it. There may
  // not be one set though, if its age is already older than Tage. 
  if(ageeventsdic.find(memeid) != ageeventsdic.end()){
    ++agedist[memes[memeid].popularity];
    ageevents.erase(ageeventsdic[memeid]);
    ageeventsdic.erase(memeid);
    uage = (*ageevents.begin()).u;
    tage = (*ageevents.begin()).t;
  }

  // Uncomment this if you wish to do a branching number study. wrmaxtmp is the fitness
  // cutoff, meaning you only want the branching number of memes that are fitter.
  //if(memes[memeid].wr >= wrmaxtmp) ++progenydist[memes[memeid].popularity];
  memes.erase(memeid);
}


void fitness::schedule_nodeevent(int u)
{
  nodeevents.erase(nodeeventsdic[u]);
  nodeeventsdic[u] = sampletimes(u, t);
  nodeevents.insert(nodeeventsdic[u]);
}


void fitness::gillespie()
{
  initialiserun();

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

    if(count % int(1 * N) == 0){
      fprintf(stderr, "    %8.3f / %6.0f \r", t, T);
      sanitycheck();
      strajcheck();
    }

    if(count % int(5 * N) == 0){
      //print_popularity(); // print with count info
      cout << count / int(5 * N) << " is couuuuuuuuuuuunt" << endl;
    }

    if(type == 0){
      --memes[screen[u]].abundance;
      if(memes[screen[u]].abundance == 0) memedeath(u);
      memebirth(u);
    }

    memes[screen[u]].popularity += 1;
    schedule_nodeevent(u);

    for(unsigned int i = 0; i < G.network[u].size(); ++i){
      if(udist(gen) < memes[screen[u]].wb){
        int v = G.network[u][i].nodeindex;
        if(screen[v] != screen[u]){
          --memes[screen[v]].abundance;
          if(memes[screen[v]].abundance == 0) memedeath(v);
          screen[v] = screen[u];
          ++memes[screen[u]].abundance;
          schedule_nodeevent(v);
        }
      }
    }
    ++count;
  }
  fprintf(stderr, "                                                        \r");
}

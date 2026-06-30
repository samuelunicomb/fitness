#include <iostream>

#include "fitness.h"

using namespace std;

memedata fitness::samplememepars(const double &t)
{
  memedata m;
  m.popularity = 0;
  m.abundance = 1;
  m.birthtime = t;
  m.wp = wpdist.sample();
  m.wr = wrdist.sample();
  m.wb = wbdist.sample();
  return m;
}

event fitness::sampletimes(const unsigned int &i, const double &t)
{
  dtp = 1e12;
  if(memes[screen[i]].wp > 0) dtp = edist(gen) / memes[screen[i]].wp;
  dtr = 1e12;
  if(memes[screen[i]].wr > 0) dtr = edist(gen) / memes[screen[i]].wr;
  dt = dtp < dtr ? dtp : dtr;
  typetmp = dtp < dtr ? 0 : 1;

  return event{i, typetmp, t + dt};
}

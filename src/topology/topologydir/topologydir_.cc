#include "topologydir.h"

#include "utilityfunctions.h"

/*

This is currently ugly, we need to set undirected pkdistributions, as
well as directed ones

*/

topologydir::topologydir(pkregular po, pkregular pi)
{
  degreedisto = "regular";
  degreedisti = "regular";

  regulari.z = pi.k;
  regularo.k = po.k;

  regular.z = pi.k;
  regular.k = po.k;

  z = pi.k;

  pksupport = set<int> {};
  pk = map<int, double> {};
}

topologydir::topologydir(pkregular po, pkpoisson pi)
{
  degreedisto = "regular";
  degreedisti = "poisson";

  poissoni.z = pi.z;
  regularo.k = po.k;

  poisson.z = pi.z;
  regular.k = po.k;

  z = pi.z;

  pksupport = set<int> {};
  pk = map<int, double> {};
}

topologydir::topologydir(pkregular po, pkpoissonmin pi)
{
  degreedisto = "regular";
  degreedisti = "poissonmin";

  poissonmini.z = pi.z;
  regularo.k = po.k;

  poissonmin.z = pi.z;
  poisson.z = pi.z;
  regular.k = po.k;

  z = pi.z;

  pksupport = set<int> {};
  pk = map<int, double> {};
}

topologydir::topologydir(pkregular po, pkexponential pi)
{
  degreedisto = "regular";
  degreedisti = "exponential";

  exponentiali.z = pi.z;
  regularo.k = po.k;

  exponential.z = pi.z;
  regular.k = po.k;

  z = pi.z;

  pksupport = set<int> {};
  pk = map<int, double> {};
}

topologydir::topologydir(pkpowerlaw po, pkpoisson pi)
{
  degreedisto = "powerlaw";
  degreedisti = "poisson";

  // TODO pi is a placeholder, overwrite pi.z with po.z
  poissoni.z = po.z;
  powerlawo.alpha = po.alpha;
  powerlawo.kmin = po.kmin;

  poisson.z = po.z;
  powerlaw.alpha = po.alpha;
  powerlaw.kmin = po.kmin;

  z = po.z;

  //poissoni.z = pi.z;
  //powerlawo.alpha = po.alpha;
  //powerlawo.kmin = po.kmin;

  //poisson.z = pi.z;
  //powerlaw.alpha = po.alpha;
  //powerlaw.kmin = po.kmin;

  //z = pi.z;

  pksupport = set<int> {};
  pk = map<int, double> {};
}

topologydir::topologydir(pkpowerlaw po, pkregular pi)
{
  degreedisto = "powerlaw";
  degreedisti = "regular";

  regulari.k = pi.k;
  regular.k = pi.k;

  powerlawo.alpha = po.alpha;
  powerlawo.kmin = po.kmin;

  powerlaw.alpha = po.alpha;
  powerlaw.kmin = po.kmin;

  pksupport = set<int> {};
  pk = map<int, double> {};
}

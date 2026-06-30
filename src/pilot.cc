#include <iostream>

#include "variables.h"

#include "fitness.h"

using namespace std;

int main(int argc, char* argv[]) 
{
  srand(time(NULL));

  g_argc = argc;
  g_argv = argv;

  fitness F;
  F.N = 1e5;
  F.Tage = 200;
  F.T = 2.05 * F.Tage;
  F.G = graphdir(topologydir{pkregular{10}, pkpoisson{10}}, F.N);
  //F.G = graphdir(topologydir{pkpowerlaw{2.5, 4, int(F.N)}, pkpoisson{0}}, F.N);
  F.wrdist = distribution(distbeta(1.0, 1.25));
  F.wbdist = distribution(distdelta(1.0));
  F.wpdist = distribution(distdelta(0.182));
  //F.wrdist = distribution(distdelta(1.0));
  //F.wbdist = distribution(distbeta(1.0, 1.25));
  //F.wpdist = distribution(distdelta(0.272));
  F.gillespie(); 
  F.print_popularity();

  //fitness F;
  //F.N = 1e5;
  //F.Tage = 100;
  //F.T = 2.05 * F.Tage;
  //F.G = graphdir(topologydir{pkpowerlaw{2.5, 4, int(F.N)}, pkpoisson{0}}, F.N);
  //F.wrdist = distribution(distbeta(1.0, 2.5));
  //F.wbdist = distribution(distbeta(1.0, 2.5));
  //F.wpdist = distribution(distdelta(1.8));
  //F.gillespie(); 
  //F.print_popularity();

  // TODO most recent
  //fitness F;
  //F.N = 2e4;
  //F.Tage = 200;
  //F.T = 2 * F.Tage;
  //F.G = graphdir(topologydir{pkpowerlaw{2.5, 4, int(F.N)}, pkpoisson{0}}, F.N);
  //F.wrdist = distribution(distbeta(1.0, 6.0));
  //F.wbdist = distribution(distdelta(1.0));
  //F.wpdist = distribution(distdelta(1.59));
  //F.gillespie(); 
  //F.print_popularity();
  //F.print_abundance();

  //for(double w = 0.0001; w < 50; w *= 1.5){
  //  fitness F;
  //  F.N = 1e5;
  //  F.Tage = 50;
  //  F.T = 2 * F.Tage;
  //  F.G = graphdir(topologydir{pkregular{10}, pkpoisson{10}}, F.N);
  //  F.wrdist = distribution(distbeta(1.0, 0.01));
  //  F.wbdist = distribution(distdelta(1.0));
  //  F.wpdist = distribution(distdelta(w));
  //  F.gillespie(); 
  //  printf("%f \n", w);
  //  F.print_abundance();
  //}
}

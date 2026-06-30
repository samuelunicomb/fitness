#include "graphdir.h"

#include <iostream>
#include <random>

using namespace std;

vector<vector<stub>> graphdir::rewire () // rewire directed edges
{
  vector<stub> s0, s1, s2;

  for (unsigned int i = 0; i != network.size (); ++i) 
  {
    for (unsigned int j = 0; j != network[i].size (); ++j) 
    {
      if (network[i][j].edgetype == 0)
      {
        s0.push_back (stub {int(i), 0});
      }
      else if (network[i][j].edgetype == 1)
      {
        s1.push_back (stub {int(i), 1});
      }
      else if (network[i][j].edgetype == 2)
      {
        s2.push_back (stub {int(i), 2});
      }
    }
  }
  shuffle (s0.begin (), s0.end (), mt19937 {random_device {} ()});
  shuffle (s1.begin (), s1.end (), mt19937 {random_device {} ()});
  shuffle (s2.begin (), s2.end (), mt19937 {random_device {} ()});

  vector<vector<stub>> dummy (network.size ());

  if (s0.size () != s1.size ()) exit (EXIT_FAILURE);

  for (unsigned int i = 0; i != s0.size (); ++i) // pairing type 0 and 1 edges
  {
    stub sdummy0 = s0[i];
    stub sdummy1 = s1[i];

    int u = sdummy0.nodeindex;
    int v = sdummy1.nodeindex;

    sdummy0.nodeindex = v;
    sdummy1.nodeindex = u;

    dummy[u].push_back (sdummy0);
    dummy[v].push_back (sdummy1);
  }

  for (unsigned int i = 0; i != s2.size (); i += 2) // pairing type 2 edges
  {
    stub sdummya = s2[i];
    stub sdummyb = s2[i + 1];

    int u = sdummya.nodeindex;
    int v = sdummyb.nodeindex;

    sdummya.nodeindex = v;
    sdummyb.nodeindex = u;

    dummy[u].push_back (sdummya);
    dummy[v].push_back (sdummyb);
  }
  return dummy;
}

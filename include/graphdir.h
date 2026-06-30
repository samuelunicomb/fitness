#ifndef LAB_GRAPHDIR_H_
#define LAB_GRAPHDIR_H_

#include "topologydir.h"

class graphdir
{
  public:
    graphdir(){};
    graphdir(topologydir, int);

    topologydir top;

    vector<vector<stub>> network;

    void build();
    vector<stub> buildstubset(string, int);
    void wirestubsets(vector<stub>&, vector<stub>&);
    vector<vector<stub>> rewire();

    void print_neighbourlist();
    void print_neighbourlistout();
    void print_neighbourlistin();
};
#endif

#include "graphdir.h"

#include <iostream>

/*

there's nothing here to ensure that objects are constructed with netsize?

*/

graphdir::graphdir(topologydir t, int n)
{
  top = t;
  top.netsize = n;

  build();
}

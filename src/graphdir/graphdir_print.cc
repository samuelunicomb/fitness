#include "graphdir.h"

#include <iostream>

using namespace std;

void graphdir::print_neighbourlist ()
{
  for (unsigned int i = 0; i != network.size (); ++i)
  {
    cout << i << "; ";

    if (network[i].size () > 0)
    {
      for (unsigned int j = 0; j != network[i].size (); ++j)
      {
        cout << network[i][j].nodeindex << "; ";
        cout << "(";
        cout << network[i][j].edgetype;
        cout << ") ";
      }
      cout << '\n';
    }
    else
    {
      cout << '\n';
    }
  }
}

void graphdir::print_neighbourlistout ()
{
  for (unsigned int i = 0; i != network.size (); ++i)
  {
    cout << i << "; ";

    if (network[i].size () > 0)
    {
      for (unsigned int j = 0; j != network[i].size (); ++j)
      {
        if (network[i][j].edgetype == 0)
        {
          cout << network[i][j].nodeindex << "; ";
          cout << "(";
          cout << network[i][j].edgetype;
          cout << ") ";
        }
      }
      cout << '\n';
    }
    else
    {
      cout << '\n';
    }
  }
}

void graphdir::print_neighbourlistin ()
{
  for (unsigned int i = 0; i != network.size (); ++i)
  {
    cout << i << "; ";

    if (network[i].size () > 0)
    {
      for (unsigned int j = 0; j != network[i].size (); ++j)
      {
        if (network[i][j].edgetype == 1)
        {
          cout << network[i][j].nodeindex << "; ";
          cout << "(";
          cout << network[i][j].edgetype;
          cout << ") ";
        }
      }
      cout << '\n';
    }
    else
    {
      cout << '\n';
    }
  }
}

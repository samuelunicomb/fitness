#ifndef LAB_UTILITYSTRUCTURES_H_
#define LAB_UTILITYSTRUCTURES_H_

#include <vector>
#include <map>
#include <set>

#include <gmp.h>
#include <mpfr.h>

using namespace std;

struct stub // properties of a neighbour, link
{
  stub(){};

  stub(int u, int j){
    nodeindex = u;
    edgetype = j;
  }

	int nodeindex, edgetype, state, weighttype;
  double w, w0, w1;
  long double last_event, next_event;

	bool operator<(const stub& rhs) const{
  	return nodeindex < rhs.nodeindex;
 	}
};


struct event // node event
{
  event(){};

  event(unsigned long long int a, double b){
    u = a;
    t = b;
  }

  event(unsigned long long int a, unsigned int b, double c){
    u = a;
    type = b;
    t = c;
  }

  unsigned long long int u;     // node index and node event type
  unsigned int type;  // type of event, post or repost, 0 or 1
  double t;  // time of event

	bool operator<(const event& rhs) const{
    if(t == rhs.t)
      return u < rhs.u;
    else
      return t < rhs.t;
  }
};


//struct degree // degree distribution FIXME why does removing this slow down execution?
//{
//  degree(){};
//
//  degree(int a, double b){
//    k = a;
//    pk = b;
//  }
//  
//	int k;
//
//	double pk;
//};
//
//
//struct weight // weight distribution FIXME same comment as above
//{
//  weight(){};
//
//  weight(int a, double b){
//    w = a;
//    pw = b;
//  }
//
//	double w, pw;
//};

#endif

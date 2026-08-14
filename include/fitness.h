#ifndef FITNESS_H_
#define FITNESS_H_

#include <random>

#include "dist.h"
#include "memedata.h"
#include "graphdir.h"

//template <Dist D>
class distribution
{
  public:
    distribution(){}

    distribution(distdelta d){
      gen = mt19937(random_device{}());
      dist = Dist::delta;
      ddist = d.val;
    }

    distribution(distuniform d){
      gen = mt19937(random_device{}());
      dist = Dist::uniform;
      udist = uniform_real_distribution<double>(d.lo, d.hi);
    }

    distribution(distbeta d){
      gen = mt19937(random_device{}());
      dist = Dist::beta;
      gdista = gamma_distribution<double>(d.alpha, 1);
      gdistb = gamma_distribution<double>(d.beta, 1);
    }

    distribution(distlognormal d){
      gen = mt19937(random_device{}());
      dist = Dist::lognormal;
      double lnmean = d.mean;
      double lnsdv = d.sdv;
      double nmean = log(lnmean * lnmean / sqrt(lnmean * lnmean + lnsdv * lnsdv));
      double nsdv = sqrt(log(1 + lnsdv * lnsdv / (lnmean * lnmean)));
      ldist = lognormal_distribution<double>(nmean, nsdv);
    }

    //double sample(){
    //  if constexpr(D == Dist::delta){
    //    return ddist;
    //  }else if constexpr(D == Dist::uniform){
    //    return udist(gen);
    //  }else if constexpr(D == Dist::beta){
    //    double x = gdista(gen);
    //    double y = gdistb(gen);
    //    return x / (x + y);
    //  }else if constexpr(D == Dist::lognormal){
    //    return ldist(gen);
    //  }
    //}

    double sample(){
      switch(dist){
        case(Dist::delta):
          return ddist; 

        case(Dist::uniform):
          return udist(gen);

        case(Dist::beta):
          x = gdista(gen); 
          y = gdistb(gen); 
          return x / (x + y);

        case(Dist::lognormal):
          return ldist(gen);
      }
    }

    Dist dist;

    mt19937 gen;
    double ddist, x, y;
    exponential_distribution<double> edist;
    uniform_real_distribution<double> udist;
    gamma_distribution<double> gdista, gdistb;
    lognormal_distribution<double> ldist;
};


struct trajectory
{
  int w;
  vector<vector<double>> rho;
};


class fitness
{
  public:
    fitness(){};

    graphdir G;
    unsigned int N;  // network size
		double T, Tage;  // global runtime, and meme age at measurement

		unsigned int u, uage, type;  // gillespie event node index and type
		double t, tage;  // gillespie event times
		unsigned long long int count;  // gillespie counter

    distribution wrdist, wpdist, wbdist;  // distributions of rates wr, wp and wb

    map<unsigned long long int, memedata> memes;
    set<event> nodeevents, ageevents;
    vector<event> nodeeventsdic;
		map<unsigned long long int, event> ageeventsdic;
    vector<unsigned long long int> screen;
    map<unsigned int, trajectory> straj;  // s(t) trajectories for dominant memes

    mt19937 gen;
    exponential_distribution<double> edist;
    uniform_real_distribution<double> udist;

    double dtp, dtr, dt;
    unsigned int typetmp;

    void initialiserun();
    void initialisedists();

    void memebirth(int);
    void memedeath(int);
    void schedule_nodeevent(int);
    void gillespie();

    void gillespie_urn();
    void sanitycheck();
    void strajcheck();

    memedata samplememepars(const double&);
    event sampletimes(const unsigned int &, const double &);

		map<int, int> agedist;  // popularity distribution at Tage

		vector<int> printargs;  // integer flags for printing

    void print_popularity(map<int, int>, int);
    void print_popularity();
    void print_abundance();
    void print_si();
    void print_straj();
};
#endif

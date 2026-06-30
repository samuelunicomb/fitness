#ifndef DIST_H_
#define DIST_H_

enum Dist{delta, uniform, beta, lognormal};

struct distdelta{
  distdelta(double a) : val(a) {}

  double val;
};

struct distuniform{
  distuniform(double a, double b) : lo(a), hi(b) {}

  double lo, hi;
};

struct distbeta{
  distbeta(double a, double b) : alpha(a), beta(b) {}

  double alpha, beta;
};

struct distlognormal{
  distlognormal(double a, double b) : mean(a), sdv(b) {}

  double mean, sdv;
};


#endif

#include "utilitystructures.h"

/*

could call this numbertheory.h, like number theory section in GMP, MPFR docs?

*/
long long int bnk(int n, int k);                               // binomial coefficient
double bnkp(int n, int k, double p);                           // binomial coefficient with p
double bnkp_gmp(int n, int k, double p);                       // binomial coefficient for large n, k
double multinomial_gmp(vector<int> k, vector<double> p);       // calculates multinomial coefficient
double multinomial_gmp(map<int, int> k, vector<double> p);     // calculates multinomial coefficient
double exponential_mpfr(int k, double kappa);                  // exponential distribution
double geometric_mpfr(int k, double p);                        // geometric distribution
double poisson_mpfr(int k, double lambda);                     // poisson distribution
double tnkp_gmp(int k, int k1, int k2, double p1, double p2);  // trinomial coefficient for k1 + k2 + k3 = k, p1 + p2 + p3 = 1
double gamma_li_normalised(double x, double p);                // lower incomplete Gamma integral, x and p must be greater than 0
long int factorial(int n);                                     // calculates factorial
long int factorialset(vector<int> alpha);                      // multiindex factorial

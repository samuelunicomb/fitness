#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <cassert>

#include <gmp.h>
#include <mpfr.h>

#include "utilitystructures.h"

/*

There should probably be some more rhyme and reason to this file. Otherwise,
should break it into smaller ones.

*/

using namespace std;

long long int bnk(int n, int k) // binomial coefficient
{
  if(k > n - k) k = n - k;

  long double dummy = 1;

  if(n < 0){ // if negative, will be -1
    dummy = 1;
  }else if(n == 0){
    dummy = 1;
  }else if(k < 1){
    dummy = 1;
  }else{
    for(int i = 1; i != k + 1; i++)
      dummy *= (n - (k - i)) / (double) i;
  }
  //long long int integer_part = (long long int) dummy;
  //return integer_part;
  return(long long int) dummy;
}

double bnkp(int n, int k, double p) // returns binomial probability
{
  long long int a = bnk(n,k);
  double b = pow(p, k) * pow(1 - p, n - k);
  return a * b;
}

double bnkp_gmp(int n, int k, double p) // returns binomial coefficient
{
  mpz_t a1;
  mpf_t a2;
  mpz_init(a1);
  mpz_bin_uiui(a1, n, k);
  mpf_init(a2);
  mpf_set_z(a2, a1);

  mpf_t b1;
  mpf_t b2;
  mpf_init_set_d(b1, p);
  mpf_init_set_d(b2, 1 - p);

  mpf_pow_ui(b1, b1, k);
  mpf_pow_ui(b2, b2, n - k);
  mpf_mul   (b1, b1, b2);

  mpf_mul(b1, b1, a2);

  return mpf_get_d(b1);
}

double poisson_mpfr(int k, double lambda) // returns Poisson distribution value
{
  // exponential constant
  mpfr_t a;
  mpfr_init (a);
  mpfr_set_d(a, -lambda, MPFR_RNDN);
  mpfr_exp  (a, a, MPFR_RNDN); 

  // factorial and power
  mpfr_t b, c;
  mpfr_init (b);
  mpfr_init (c);
  mpfr_set_d(b, lambda, MPFR_RNDN);
  mpfr_pow_ui(b, b, k, MPFR_RNDN);
  mpfr_fac_ui(c, k, MPFR_RNDN);

  // combine
  mpfr_mul(a, a, b, MPFR_RNDN);
  mpfr_div(a, a, c, MPFR_RNDN);

  double p = mpfr_get_d(a, MPFR_RNDN);

  mpfr_clears(a, b, c, (mpfr_ptr) 0);

  return p;
}

/* 

evaluates discrete exponential distribution at a given value k, and we put

kappa = 1 / ln (1 + 1 / z)

for a desired z.

*/
double exponential_mpfr(int k, double kappa) 
{
  // exponential coefficient
  mpfr_t a;
  mpfr_init (a);
  mpfr_set_d(a, -1 / kappa, MPFR_RNDN);
  mpfr_exp  (a, a, MPFR_RNDN); 
  mpfr_d_sub(a, 1, a, MPFR_RNDN); 

  // exponential part
  mpfr_t b;
  mpfr_init  (b);
  mpfr_set_ui(b, k, MPFR_RNDN);
  mpfr_div_d (b, b, -kappa, MPFR_RNDN);
  mpfr_exp   (b, b, MPFR_RNDN); 

  // combine
  mpfr_mul(a, a, b, MPFR_RNDN);

  return mpfr_get_d(a, MPFR_RNDN);
}

// returns the value of the geometric distribution assuming a support 
// k \in {1, 2, 3, ...}
double geometric_mpfr(int k, double p) 
{
  assert(k >= 1);
  assert(p > 0);

  double peff = p;
  if(peff > 1.0) peff = 1.0;

  mpfr_t a;
  mpfr_init  (a);
  mpfr_set_d (a, 1 - p, MPFR_RNDN);
  mpfr_pow_ui(a, a, k - 1, MPFR_RNDN);
  mpfr_mul_d (a, a, p, MPFR_RNDN);

  return mpfr_get_d(a, MPFR_RNDN);
}

long int factorial(int n) 
{
  mpz_t ngmp;

  mpz_init  (ngmp);
  mpz_fac_ui(ngmp, n);

  return mpz_get_ui(ngmp);
}

long int factorialset(vector<int> alpha) 
{
  long int f = 1;

  for(unsigned int i = 0; i < alpha.size(); ++i)
    f *= factorial(alpha[i]);

  return f;
}

// calculates trinomial coefficient for k1 + k2 + k3 = k, p1 + p2 + p3 = 1
double tnkp_gmp(int k, int k1, int k2, double p1, double p2) 
{
  int k3 = k - k1 - k2;

  double p3 = 1 - p1 - p2;

  // integer part

  // declare
  mpz_t k_fact, k1_fact, k2_fact, k3_fact;
  mpf_t a;

  // initialise
  mpz_init(k_fact);
  mpz_init(k1_fact);
  mpz_init(k2_fact);
  mpz_init(k3_fact);
  mpf_init(a);
  
  // calculate factorials
  mpz_fac_ui(k_fact, k);
  mpz_fac_ui(k1_fact, k1);
  mpz_fac_ui(k2_fact, k2);
  mpz_fac_ui(k3_fact, k3);

  // divide fraction
  mpz_cdiv_q(k_fact, k_fact, k1_fact); 
  mpz_cdiv_q(k_fact, k_fact, k2_fact); 
  mpz_cdiv_q(k_fact, k_fact, k3_fact); 

  // convert integer to float
  mpf_set_z(a, k_fact);

  // double part 
  mpf_t b1, b2, b3;
  mpf_init_set_d(b1, p1);
  mpf_init_set_d(b2, p2);
  mpf_init_set_d(b3, p3);

  // raise to powers and multiply
  mpf_pow_ui(b1, b1, k1);
  mpf_pow_ui(b2, b2, k2);
  mpf_pow_ui(b3, b3, k3);
  mpf_mul(b1, b1, b2);
  mpf_mul(b1, b1, b3);

  // combine
  mpf_mul(b1, b1, a);

  return mpf_get_d(b1);
}

double multinomial_gmp(vector<int> k, vector<double> p) 
{
  double norm = 0;
  for(auto &it : p) norm += it;
  assert(norm > 1 - 1e-8 && norm < 1 + 1e-8);

  int ksum = 0;
  for(unsigned int i = 0; i < k.size(); ++i) ksum += k[i];

  mpz_t num, den, dummy;
  mpz_init_set_ui(num, 1);
  mpz_init_set_ui(den, 1);
  mpz_init_set_ui(dummy, 1);
  mpz_fac_ui    (num, ksum);
  for(unsigned int i = 0; i < k.size(); ++i){ // multiply factorials
    mpz_fac_ui(dummy, k[i]); 
    mpz_mul  (den, den, dummy);
  }
  mpz_tdiv_q(num, num, den);

  mpf_t prod;
  mpf_init_set_ui(prod, 1);
  for(unsigned int i = 0; i < p.size(); ++i){ // multiply probabilities
    mpf_t pdummy;
    mpf_init_set_d(pdummy, p[i]);
    mpf_pow_ui   (pdummy, pdummy, k[i]);
    mpf_mul      (prod, prod, pdummy);
  }

  mpf_t fdummy;
  mpf_init(fdummy);
  mpf_set_z(fdummy, num);
  mpf_mul (fdummy, fdummy, prod);

  return mpf_get_d(fdummy);
}

// TO DO; simply convert map to vector and call other mutlinomial_gmp
double multinomial_gmp(map<int, int> k, vector<double> p)
{
  double norm = 0;
  for(auto &it : p) norm += it;
  assert(norm > 1 - 1e-8 && norm < 1 + 1e-8);

  int ksum = 0;
  for(auto &it : k) ksum += it.second;

  assert(k.size() == p.size());

  mpz_t num, den, dummy;
  mpz_init_set_ui(num, 1);
  mpz_init_set_ui(den, 1);
  mpz_init_set_ui(dummy, 1);
  mpz_fac_ui     (num, ksum);
  for(auto &it : k){                  // multiply factorials
    mpz_fac_ui(dummy, it.second); 
    mpz_mul   (den, den, dummy);
  }
  mpz_tdiv_q(num, num, den);

  mpf_t prod;
  mpf_init_set_ui(prod, 1);
  for(unsigned int i = 0; i < p.size(); ++i){ // multiply probabilities
    mpf_t pdummy;
    mpf_init_set_d(pdummy, p[i]);
    mpf_pow_ui    (pdummy, pdummy, k[i]);
    mpf_mul       (prod, prod, pdummy);
  }

  mpf_t fdummy;
  mpf_init(fdummy);
  mpf_set_z(fdummy, num);
  mpf_mul  (fdummy, fdummy, prod);

  return mpf_get_d(fdummy);
}

// lower incomplete Gamma integral, x and p must be greater than 0
double gamma_li_normalised(double p, double x)
{
  double a, arg, c , e, f, uflo, value;
  //double a;
  //double arg;
  //double c;
  //double e = 1.0E-09;
  //double f;
  //double uflo = 1.0E-37;
  //double value;

  e = 1.0E-09;
  uflo = 1.0E-37;

  if(x <= 0.0){
    value = 0.0;
    return value;
  }

  if(p <= 0.0){
    value = 0.0;
    return value;
  }

  arg = p * log(x) - lgamma(p + 1.0) - x;

  if(arg < log(uflo)){
    value = 0.0;
    return value;
  }

  f = exp(arg);

  if(f == 0.0){
    value = 0.0;
    return value;
  }

  c = 1.0;
  value = 1.0;
  a = p;

  for( ; ; ){ // calculates infinite series
    a = a + 1.0;
    c = c * x / a;
    value = value + c;

    if(c <= e * value) break;
  }

  value = value * f;

  return value;
}

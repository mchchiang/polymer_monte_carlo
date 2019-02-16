/*
 * bond_distrb_fene.cpp
 *
 *  Created on: 13 Feb 2019
 *      Author: michaelchiang
 */

#include <cmath>
#include <vector>
#include <functional>
#include <iostream>
#include "bond_distrb_fene.hpp"
#include "bond_fene.hpp"
#include "util_vector.hpp"
#include "util_numeric.hpp"

using std::vector;
using std::function;
using std::cout;
using std::endl;
using FENEDistrb = BondDistributionFENE;

FENEDistrb::BondDistributionFENE(int _ntypes, double _temp,
                                 int seed, BondFENE* fene) :
  BondDistribution{seed}, feneBond {fene}, temp {_temp}, ntypes {_ntypes} {
  nbins = 1000;
  binsize = 1.0 / static_cast<double>(nbins);
  invcdf = vector<Data2D>(ntypes);

  int nintbins {1000};
  double cdfinc {0.001};
  double buffer {1E-5};
  double start {buffer};
  double end;
  double norm;

  function<double(double)> f;
  Data2D cdf;

  for (int i {}; i < ntypes; i++) {
    end = feneBond->getCoeff(i,3)-buffer;

    // Find normalisation constant
    f = [&i, this] (double r)
        {return r * r * exp(-(feneBond->compute(i, r)) / temp);};
    norm = integrate(start, end, nintbins, f);

    // Find CDF
    f = [&norm, &i, this] (double r)
        {return r * r / norm * exp(-(feneBond->compute(i, r)) / temp);};
    cdf = computeCDF(start, end, cdfinc, nintbins, f);

    // Find inverse CDF (swap cdfx and cdfy and smooth the interval)
    invcdf[i] = smooth(nbins+1, invert(cdf));
  }
}

FENEDistrb::~BondDistributionFENE() {}

void FENEDistrb::generate(int type, const Vec& v1,
                          double* value, double* energy) {
  double r {nextRand()};
  int i {static_cast<int>(floor(r / static_cast<double>(binsize)))};
  double result {};
  if (i < 0) {
    result = invcdf[type].y[0];
  } else if (i >= nbins-1) {
    result = invcdf[type].y[nbins-1];
  } else {
    result = linearInterpolate(invcdf[type].x[i], invcdf[type].x[i+1],
                               invcdf[type].y[i], invcdf[type].y[i+1], r);
  }
  *value = result;
  *energy = feneBond->compute(type, r);
}

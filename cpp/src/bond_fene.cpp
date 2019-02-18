/*
 * bond_fene.cpp
 *
 *  Created on: 5 Feb 2019
 *      Author: michaelchiang
 */


#include <cmath>
#include <vector>
#include <limits>
#include "bond_fene.hpp"
#include "util_vector.hpp"

using std::vector;

BondFENE::BondFENE(int ntypes, double _epsilon, double _sigma,
                   double _kf, double _r0) {
  epsilon = vector<double>(ntypes, _epsilon);
  sigma = vector<double>(ntypes, _sigma);
  kf = vector<double>(ntypes, _kf);
  r0 = vector<double>(ntypes, _r0);
}

BondFENE::~BondFENE() {}

double BondFENE::compute(int type, const Vec& r1, const Vec& r2) {
  return compute(type, Vec::dist(r1,r2));
}

double BondFENE::compute(int type, double r) {
  double rsq {r*r};
  double s {sigma[type]/r};
  double r0sq {r0[type]*r0[type]};
  double ssq {s*s};
  double s6 {ssq*ssq*ssq};
  double rlogarg = 1.0-rsq/r0sq;

  if (r < rc*sigma[type]) {
    return 4.0*epsilon[type]*(s6*(s6-1.0)+0.25)-0.5*kf[type]*r0sq*log(rlogarg);
  } else if (r < r0[type]) {
    return -0.5*kf[type]*r0sq*log(rlogarg);
  } else {
    return std::numeric_limits<double>::infinity();
  }
}

void BondFENE::setCoeff(int type, const std::vector<double>& args) {
  if (args.size() >= 4) {
    epsilon[type] = args[0];
    sigma[type] = args[1];
    kf[type] = args[2];
    r0[type] = args[3];
  }
}

void BondFENE::setCoeff(int type, int iarg, double value) {
  switch(iarg) {
    case 0: epsilon[type] = value; break;
    case 1: sigma[type] = value; break;
    case 2: kf[type] = value; break;
    case 3: r0[type] = value; break;
  }
}

double BondFENE::getCoeff(int type, int iarg) {
  switch(iarg) {
    case 0: return epsilon[type];
    case 1: return sigma[type];
    case 2: return kf[type];
    case 3: return r0[type];
    default: return 0.0;
  }
}

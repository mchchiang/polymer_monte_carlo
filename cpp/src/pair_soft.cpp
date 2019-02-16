/*
 * pair_soft.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include <cmath>
#include <vector>
#include "pair_soft.hpp"
#include "util_vector.hpp"

using std::vector;

PairSoft::PairSoft(int _ntypes, double _a, double _cutoff) {
  ntypes = _ntypes;
  int ntypesSq {ntypes*ntypes};
  a = vector<double>(ntypesSq, _a);
  cutoff = vector<double>(ntypesSq, _cutoff);
}

PairSoft::~PairSoft() {}

double PairSoft::compute(int type1, int type2, const Vec& v1, const Vec& v2) {
  return compute(type1, type2, Vec::dist(v1, v2));
}

double PairSoft::compute(int type1, int type2, double r) {
  int type {type1*ntypes+type2};
  double rc {cutoff[type]};
  if (r < rc) {
    return a[type]*cos(1.0+(M_PI*r/rc));
  } else {
    return 0.0;
  }
}

void PairSoft::setCoeff(int type1, int type2, const vector<double>& args) {
  if (args.size() == 2) {
    int type {type1*ntypes+type2};
    a[type] = args[0];
    cutoff[type] = args[1];
  }
}

double PairSoft::getCoeff(int type1, int type2, int iarg) {
  int type {type1*ntypes+type2};
  switch(iarg) {
    case 0: return a[type];
    case 1: return cutoff[type];
    default: return 0.0;
  }
}

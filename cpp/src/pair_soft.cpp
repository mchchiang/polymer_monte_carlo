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
    int t1 {type1*ntypes+type2};
    int t2 {type2*ntypes+type1};
    a[t1] = args[0];
    a[t2] = args[0];
    cutoff[t1] = args[1];
    cutoff[t2] = args[1];
  }
}

void PairSoft::setCoeff(int type1, int type2, int iarg, double value) {
  int t1 {type1*ntypes+type2};
  int t2 {type2*ntypes+type1};
  switch(iarg) {
    case 0:
      a[t1] = value;
      a[t2] = value;
      break;
    case 1:
      cutoff[t1] = value;
      cutoff[t2] = value;
      break;
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

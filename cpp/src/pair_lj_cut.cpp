/*
 * pair_lj_cut.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include <vector>
#include <limits>
#include "pair_lj_cut.hpp"
#include "util_vector.hpp"

using std::vector;

PairLJCut::PairLJCut(int _ntypes, double _epsilon,
                     double _sigma, double _cutoff) {
  ntypes = _ntypes;
  int ntypesSq = ntypes*ntypes;
  epsilon = vector<double>(ntypesSq, _epsilon);
  sigma = vector<double>(ntypesSq, _sigma);
  cutoff = vector<double>(ntypesSq, _cutoff);
}

PairLJCut::~PairLJCut() {}

double PairLJCut::compute(int type1, int type2, const Vec& v1, const Vec& v2) {
  return compute(type1, type2, Vec::dist(v1,v2));
}

double PairLJCut::compute(int type1, int type2, double r) {
  int type {type1*ntypes+type2};
  double rc {cutoff[type]};
  if (r < rc) {
    double sr {sigma[type]/r};
    double sr2 {sr*sr};
    double sr6 {sr2*sr2*sr2};
    double src {sigma[type]/rc};
    double src2 {src*src};
    double src6 {src2*src2*src2};
    return 4.0*epsilon[type]*(sr6*(sr6-1.0)-src6*(src6-1.0));
  } else {
    return 0.0;
  }
}

void PairLJCut::setCoeff(int type1, int type2, const vector<double>& args) {
  if (args.size() == 3) {
    int t1 {type1*ntypes+type2};
    int t2 {type2*ntypes+type1};
    epsilon[t1] = args[0];
    epsilon[t2] = args[0];
    sigma[t1] = args[1];
    sigma[t2] = args[1];
    cutoff[t1] = args[2];
    cutoff[t2] = args[2];
  }
}

void PairLJCut::setCoeff(int type1, int type2, int iarg, double value) {
  int t1 {type1*ntypes+type2};
  int t2 {type2*ntypes+type1};
  switch(iarg) {
    case 0:
      epsilon[t1] = value;
      epsilon[t2] = value;
      break;
    case 1:
      sigma[t1] = value;
      sigma[t2] = value;
      break;
    case 2:
      cutoff[t1] = value;
      cutoff[t2] = value;
      break;
  }
}

double PairLJCut::getCoeff(int type1, int type2, int iarg) {
  int type {type1*ntypes+type2};
  switch(iarg) {
    case 0: return epsilon[type];
    case 1: return sigma[type];
    case 2: return cutoff[type];
    default: return 0.0;
  }
}


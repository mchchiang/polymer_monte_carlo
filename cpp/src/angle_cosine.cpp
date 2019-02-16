/*
 * angle_cosine.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include <cmath>
#include <vector>
#include "angle_cosine.hpp"
#include "util_vector.hpp"

using std::vector;

AngleCosine::AngleCosine(int ntypes, double _k) {
  k = vector<double>(ntypes, _k);
}

AngleCosine::~AngleCosine() {}

double AngleCosine::compute(int type, const Vec& v1,
                            const Vec& v2, const Vec& v3) {
  // U(theta) = K(1 - cos(theta))
  // Get angle theta
  Vec t1, t2;
  Vec::diff(v2, v1, t1);
  Vec::diff(v3, v2, t2);
  double theta = Vec::dot(t1, t2) / (Vec::mag(t1) * Vec::mag(t2));
  return k[type]*(1-cos(theta));
}

double AngleCosine::compute(int type, double theta) {
  return k[type]*(1-cos(theta));
}

void AngleCosine::setCoeff(int type, const vector<double>& args) {
  if (args.size() >= 1) {
    k[type] = args[0];
  }
}

double AngleCosine::getCoeff(int type, int iarg) {
  return k[type];
}

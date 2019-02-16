/*
 * angle_distrb_cosine.cpp
 *
 *  Created on: 8 Feb 2019
 *      Author: michaelchiang
 */

#include <cmath>
#include "angle_distrb_cosine.hpp"
#include "angle_cosine.hpp"
#include "angle.hpp"
#include "util_vector.hpp"

using CosineDistrb = AngleDistributionCosine;

void CosineDistrb::generate(int type, const Vec& v1, const Vec& v2,
                              double* value, double* energy) {
  double u {nextRand()};
  double betaK {angleCosine->getCoeff(type,0)/temp};
  *value = acos(1.0 + 1.0/betaK*log(1.0-u*(1.0-exp(-2.0*betaK))));
  *energy = angleCosine->compute(type, *value);
}



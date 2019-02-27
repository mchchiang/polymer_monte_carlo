/*
 * angle_distrb_cosine.hpp
 *
 *  Created on: 8 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_DISTRB_COSINE_HPP_
#define ANGLE_DISTRB_COSINE_HPP_

#include "distrb.hpp"
#include "angle_cosine.hpp"
#include "util_vector.hpp"

class AngleDistributionCosine : public Distribution {

private:
  AngleCosine* angleCosine;
  double temp;

public:
  AngleDistributionCosine(double temp, int seed, AngleCosine* cosine) :
    Distribution{seed}, angleCosine{cosine}, temp {temp} {}
  ~AngleDistributionCosine() {}
  double generate(int type) {
    double u {nextRand()};
    double betaK {angleCosine->getCoeff(type,0)/temp};
    return acos(1.0 + 1.0/betaK*log(1.0-u*(1.0-exp(-2.0*betaK))));
  }
};

#endif /* ANGLE_DISTRB_COSINE_HPP_ */

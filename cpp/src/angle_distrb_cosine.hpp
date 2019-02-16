/*
 * angle_distrb_cosine.hpp
 *
 *  Created on: 8 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_DISTRB_COSINE_HPP_
#define ANGLE_DISTRB_COSINE_HPP_

#include "angle_distrb.hpp"
#include "angle_cosine.hpp"
#include "util_vector.hpp"

class AngleDistributionCosine : public AngleDistribution {

private:
  AngleCosine* angleCosine;
  double temp;

public:
  AngleDistributionCosine(double temp, int seed, AngleCosine* cosine) :
    AngleDistribution{seed}, angleCosine{cosine}, temp {temp} {}
  ~AngleDistributionCosine() {}
  void generate(int angleType, const Vec& v1, const Vec& v2,
                  double* value, double* energy);

};

#endif /* ANGLE_DISTRB_COSINE_HPP_ */

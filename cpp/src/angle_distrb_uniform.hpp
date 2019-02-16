/*
 * angle_distrb_uniform.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_DISTRB_UNIFORM_HPP_
#define ANGLE_DISTRB_UNIFORM_HPP_

#include <cmath>
#include "angle_distrb.hpp"
#include "util_vector.hpp"

class AngleDistributionUniform : public AngleDistribution {

public:
  AngleDistributionUniform(int seed) : AngleDistribution(seed) {}
  ~AngleDistributionUniform() {}
  void generate(int angleType, const Vec& v1, const Vec& v2,
                double* value, double* energy) {
    *value = acos(1.0-2.0*nextRand());
    *energy = 0.0;
  }

};

#endif /* ANGLE_DISTRB_UNIFORM_HPP_ */

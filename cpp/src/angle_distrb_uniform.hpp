/*
 * angle_distrb_uniform.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_DISTRB_UNIFORM_HPP_
#define ANGLE_DISTRB_UNIFORM_HPP_

#include <cmath>
#include "distrb.hpp"
#include "util_vector.hpp"

class AngleDistributionUniform : public Distribution {

public:
  AngleDistributionUniform(int seed) : Distribution(seed) {}
  ~AngleDistributionUniform() {}
  double generate(int angleType) {
    return acos(1.0-2.0*nextRand());
  }

};

#endif /* ANGLE_DISTRB_UNIFORM_HPP_ */

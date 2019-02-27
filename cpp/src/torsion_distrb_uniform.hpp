/*
 * torsion_distrb_uniform.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef TORSION_DISTRB_UNIFORM_HPP_
#define TORSION_DISTRB_UNIFORM_HPP_

#include <cmath>
#include "distrb.hpp"
#include "util_vector.hpp"

class TorsionDistributionUniform : public Distribution {
public:
  TorsionDistributionUniform(int seed) : Distribution{seed} {}
  ~TorsionDistributionUniform() {}
  double generate(int type) {
    return nextRand()*2.0*M_PI;
  }
};

#endif /* TORSION_DISTRB_UNIFORM_HPP_ */

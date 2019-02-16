/*
 * torsion_distrb_uniform.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef TORSION_DISTRB_UNIFORM_HPP_
#define TORSION_DISTRB_UNIFORM_HPP_

#include <cmath>
#include "torsion_distrb.hpp"
#include "util_vector.hpp"

class TorsionDistributionUniform : public TorsionDistribution {
public:
  TorsionDistributionUniform(int seed) : TorsionDistribution(seed) {}
  ~TorsionDistributionUniform() {}
  void generate(int torsionType, const Vec& v1, const Vec& v2, const Vec& v3,
                double* value, double* energy) {
    *value = nextRand()*2.0*M_PI;
    *energy = 0.0;
  }
};

#endif /* TORSION_DISTRB_UNIFORM_HPP_ */

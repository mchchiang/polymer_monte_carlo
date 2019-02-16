/*
 * torsion_distribution.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef TORSION_DISTRB_HPP_
#define TORSION_DISTRB_HPP_

#include "distrb.hpp"
#include "util_vector.hpp"

class TorsionDistribution : public Distribution {
protected:
  TorsionDistribution(int seed) : Distribution(seed) {}
public:
  virtual ~TorsionDistribution() {}
  virtual void generate(int torsioType, const Vec& v1, const Vec& v2,
                        const Vec& v3, double* value, double* energy) = 0;
};

#endif /* TORSION_DISTRB_HPP_ */

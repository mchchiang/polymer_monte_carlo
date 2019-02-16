/*
 * angle_distribution.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_DISTRB_HPP_
#define ANGLE_DISTRB_HPP_

#include "distrb.hpp"
#include "util_vector.hpp"

class AngleDistribution : public Distribution {

protected:
  AngleDistribution(int seed) : Distribution(seed) {}

public:
  virtual ~AngleDistribution() {}
  virtual void generate(int angleType, const Vec& v1, const Vec& v2,
                        double* value, double* energy) = 0;

};

#endif /* ANGLE_DISTRB_HPP_ */

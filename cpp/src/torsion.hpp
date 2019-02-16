/*
 * torsion.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef TORSION_HPP_
#define TORSION_HPP_

#include "util_vector.hpp"

class Torsion {

public:
  virtual ~Torsion() {}
  virtual double compute(int torsionType, const Vec& r1, const Vec& r2,
                         const Vec& r3, const Vec& r4) = 0;

};

#endif /* TORSION_HPP_ */

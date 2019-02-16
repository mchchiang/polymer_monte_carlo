/*
 * torsion_none.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef TORSION_NONE_HPP_
#define TORSION_NONE_HPP_

#include "torsion.hpp"
#include "util_vector.hpp"

class TorsionNone : public Torsion {

public:
  TorsionNone() {}
  ~TorsionNone() {}
  double compute(int torsionType, const Vec& r1, const Vec& r2,
                 const Vec& r3, const Vec& r4) {return 0.0;}

};

#endif /* TORSION_NONE_HPP_ */

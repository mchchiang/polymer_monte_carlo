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
  double compute(int type, const Vec& r1, const Vec& r2,
                 const Vec& r3, const Vec& r4) {return 0.0;}
  double compute(int type, double phi) {return 0.0;}
  void setCoeff(int type, const std::vector<double>& args) {}
  void setCoeff(int type, int iarg, double value) {}
  double getCoeff(int type, int iarg) {return 0.0;}

};

#endif /* TORSION_NONE_HPP_ */

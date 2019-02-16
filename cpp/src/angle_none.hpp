/*
 * angle_none.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_NONE_HPP_
#define ANGLE_NONE_HPP_

#include <vector>
#include "angle.hpp"
#include "util_vector.hpp"

class AngleNone : public Angle {

public:
  AngleNone() {}
  ~AngleNone() {}
  double compute(int angleType, const Vec& r1,
                 const Vec& r2, const Vec& r3) {return 0.0;}
  double compute(int angleType, double theta) {return 0.0;}
  void setCoeff(int nargs, const std::vector<double>& args) {} // Do nothing
  double getCoeff(int type, int iarg) {return 0.0;} // Do nothing

};

#endif /* ANGLE_NONE_HPP_ */

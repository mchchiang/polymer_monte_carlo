/*
 * AnglePotential.hpp
 *
 *  Created on: 5 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_HPP_
#define ANGLE_HPP_

#include <vector>

#include "util_vector.hpp"

class Angle {

public:
  virtual ~Angle() {}
  virtual double compute(int angleType, const Vec& r1,
                         const Vec& r2, const Vec& r3) = 0;
  virtual double compute(int angleType, double theta) = 0;
  virtual void setCoeff(int type, const std::vector<double>& args) = 0;
  virtual double getCoeff(int type, int iarg) = 0;

};

#endif /* ANGLE_HPP_ */

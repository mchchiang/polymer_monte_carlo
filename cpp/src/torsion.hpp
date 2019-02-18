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
  virtual double compute(int type, const Vec& r1, const Vec& r2,
                         const Vec& r3, const Vec& r4) = 0;
  virtual double compute(int type, double phi) = 0;
  virtual void setCoeff(int type, const std::vector<double>& args) = 0;
  virtual void setCoeff(int type, int iarg, double value) = 0;
  virtual double getCoeff(int type, int iarg) = 0;

};

#endif /* TORSION_HPP_ */

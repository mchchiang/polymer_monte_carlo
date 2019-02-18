/*
 * bond.hpp
 *
 *  Created on: 5 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_HPP_
#define BOND_HPP_

#include <vector>

#include "util_vector.hpp"

class Bond {

public:
  virtual ~Bond() {}
  virtual double compute(int type, const Vec& r1, const Vec& r2) = 0;
  virtual double compute(int type, double r) = 0;
  virtual void setCoeff(int type, const std::vector<double>& args) = 0;
  virtual void setCoeff(int type, int iarg, double value) = 0;
  virtual double getCoeff(int type, int iarg) = 0;

};

#endif /* BOND_HPP_ */

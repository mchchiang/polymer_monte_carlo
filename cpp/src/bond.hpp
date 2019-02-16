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
  virtual double compute(int bondType, const Vec& r1, const Vec& r2) = 0;
  virtual double compute(int bondType, double r) = 0;
  virtual void setCoeff(int bondType, const std::vector<double>& args) = 0;
  virtual double getCoeff(int bondType, int iarg) = 0;

};

#endif /* BOND_HPP_ */

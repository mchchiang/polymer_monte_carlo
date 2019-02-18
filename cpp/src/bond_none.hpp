/*
 * bond_none.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_NONE_HPP_
#define BOND_NONE_HPP_

#include <vector>
#include "bond.hpp"
#include "util_vector.hpp"

class BondNone : public Bond {

public:
  BondNone() {}
  ~BondNone() {}
  double compute(int type, const Vec& r1, const Vec& r2) {return 0.0;}
  double compute(int type, double r) {return 0.0;}
  void setCoeff(int type, const std::vector<double>& args) {} // Do nothing
  void setCoeff(int type, int iarg, double value) {} // Do nothing
  double getCoeff(int type, int iarg) {return 0.0;}

};

#endif /* BOND_NONE_HPP_ */

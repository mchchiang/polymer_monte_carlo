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
  double compute(int bondType, const Vec& r1, const Vec& r2) {return 0.0;}
  double compute(int bondType, double r) {return 0.0;}
  void setCoeff(int bondType, const std::vector<double>& args) {} // Do nothing
  double getCoeff(int bondType, int iarg) {return 0.0;}

};

#endif /* BOND_NONE_HPP_ */

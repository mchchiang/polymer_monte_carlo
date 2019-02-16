/*
 * bond_distrb_fixed.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_DISTRB_FIXED_HPP_
#define BOND_DISTRB_FIXED_HPP_

#include "bond_distrb.hpp"
#include "util_vector.hpp"

class BondDistributionFixed : public BondDistribution {

private:
  double length;

public:
  BondDistributionFixed(int seed, double len) :
    BondDistribution(seed), length {len} {}
  ~BondDistributionFixed() {}
  void generate(int type, const Vec& v1, double* value, double* energy) {
    *value = length;
    *energy = 0.0;
  }

};

#endif /* BOND_DISTRB_FIXED_HPP_ */

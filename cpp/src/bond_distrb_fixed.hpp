/*
 * bond_distrb_fixed.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_DISTRB_FIXED_HPP_
#define BOND_DISTRB_FIXED_HPP_

#include "distrb.hpp"
#include "util_vector.hpp"

class BondDistributionFixed : public Distribution {

private:
  double length;

public:
  BondDistributionFixed(int seed, double len) :
    Distribution(seed), length {len} {}
  ~BondDistributionFixed() {}
  double generate(int type) {
    return length;
  }

};

#endif /* BOND_DISTRB_FIXED_HPP_ */

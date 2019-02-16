/*
 * bond_distribution.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_DISTRB_HPP_
#define BOND_DISTRB_HPP_

#include "distrb.hpp"
#include "util_vector.hpp"

class BondDistribution : public Distribution {
protected:
  BondDistribution(int seed) : Distribution(seed) {}
public:
  virtual ~BondDistribution() {}
  virtual void generate(int bondType, const Vec& v1,
                        double* value, double* energy) = 0;
};

#endif /* BOND_DISTRB_HPP_ */

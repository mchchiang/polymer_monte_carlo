/*
 * bond_distribution_fene.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_DISTRB_FENE_HPP_
#define BOND_DISTRB_FENE_HPP_

#include <vector>
#include "distrb.hpp"
#include "bond_fene.hpp"
#include "util_vector.hpp"
#include "util_numeric.hpp"

class BondDistributionFENE : public Distribution {

private:
  BondFENE* feneBond;
  double temp;
  std::vector<Data> invcdf;
  int nbins;
  double binsize;
  int ntypes;

public:
  BondDistributionFENE(int ntypes, double temp, int seed, BondFENE* bond);
  ~BondDistributionFENE();
  double generate(int type);

};

#endif /* BOND_DISTRB_FENE_HPP_ */

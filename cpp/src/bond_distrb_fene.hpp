/*
 * bond_distribution_fene.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_DISTRB_FENE_HPP_
#define BOND_DISTRB_FENE_HPP_

#include <vector>
#include "bond_distrb.hpp"
#include "bond_fene.hpp"
#include "util_vector.hpp"
#include "util_numeric.hpp"

class BondDistributionFENE : public BondDistribution {

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
  void generate(int bondType, const Vec& v1, double* value, double* energy);

};

#endif /* BOND_DISTRB_FENE_HPP_ */

/*
 * bond_factory.cpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#include <utility>
#include <string>
#include <vector>
#include "bond_factory.hpp"
#include "bond.hpp"
#include "bond_fene.hpp"
#include "bond_none.hpp"
#include "bond_distrb.hpp"
#include "bond_distrb_fene.hpp"
#include "bond_distrb_fixed.hpp"

using std::pair;
using std::string;
using std::vector;
using std::make_pair;
using BondPair = std::pair<Bond*, BondDistribution*>;

BondPair BondFactory::createBondFENE(int ntypes, double epsilon, double sigma,
                                     double kf, double r0, double temp,
                                     int seed) {
  BondFENE* bond {new BondFENE(ntypes, epsilon, sigma, kf, r0)};
  BondDistributionFENE* bondDistrb {
    new BondDistributionFENE(ntypes, temp, seed, bond)};
  return make_pair(bond, bondDistrb);
}

BondPair BondFactory::createBondFixed(int length) {
  BondNone* bond {new BondNone()};
  BondDistributionFixed* bondDistrb {new BondDistributionFixed(0, length)};
  return make_pair(bond, bondDistrb);
}

BondPair BondFactory::createBond(string bondName, int ntypes,
                                 const vector<double>& args,
                                 double temp, int seed) {
  if (bondName.compare("fixed") == 0) {
    return createBondFixed(args[0]);
  } else if (bondName.compare("fene") == 0) {
    return createBondFENE(ntypes, args[0], args[1],
                          args[2], args[3], temp, seed);
  } else {
    return createBondFixed(1.0);
  }
}

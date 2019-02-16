/*
 * bond_factory.hpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_FACTORY_HPP_
#define BOND_FACTORY_HPP_

#include <utility>
#include <string>
#include <vector>
#include "bond.hpp"
#include "bond_distrb.hpp"


class BondFactory {

private:
  std::pair<Bond*,BondDistribution*>
  createBondFENE(int ntypes, double epsilon, double sigma,
                 double kf, double r0, double temp, int seed);
  std::pair<Bond*,BondDistribution*> createBondFixed(int length);

public:
  std::pair<Bond*,BondDistribution*> createBond(
      std::string, int ntypes, const std::vector<double>& args,
        double temp, int seed);
};

#endif /* BOND_FACTORY_HPP_ */

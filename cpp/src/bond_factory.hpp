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
#include "distrb.hpp"


class BondFactory {

private:
  std::pair<Bond*,Distribution*>
  createBondFENE(int ntypes, double epsilon, double sigma,
                 double kf, double r0, double temp, int seed);
  std::pair<Bond*,Distribution*> createBondFixed(int length);

public:
  std::pair<Bond*,Distribution*> createBond(
      std::string, int ntypes, const std::vector<double>& args,
        double temp, int seed);
};

#endif /* BOND_FACTORY_HPP_ */

/*
 * torsion_factory.hpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#ifndef TORSION_FACTORY_HPP_
#define TORSION_FACTORY_HPP_

#include <utility>
#include <string>
#include <vector>
#include "torsion.hpp"
#include "distrb.hpp"


class TorsionFactory {

private:
  std::pair<Torsion*,Distribution*> createTorsionNone(int seed);

public:
  std::pair<Torsion*,Distribution*> createTorsion(
      std::string torsionName, int ntypes, const std::vector<double>& params,
        double temp, int seed);
};

#endif /* TORSION_FACTORY_HPP_ */

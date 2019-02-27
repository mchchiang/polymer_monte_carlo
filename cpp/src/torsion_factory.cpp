/*
 * torsion_factory.cpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#include <utility>
#include <string>
#include <vector>
#include "torsion_factory.hpp"
#include "torsion.hpp"
#include "torsion_none.hpp"
#include "distrb.hpp"
#include "torsion_distrb_uniform.hpp"

using std::pair;
using std::string;
using std::vector;
using std::make_pair;
using TorsionPair = std::pair<Torsion*, Distribution*>;

TorsionPair TorsionFactory::createTorsionNone(int seed) {
  TorsionNone* torsion {new TorsionNone()};
  TorsionDistributionUniform* torsionDistrb {
    new TorsionDistributionUniform(seed)};
  return make_pair(torsion, torsionDistrb);
}

TorsionPair TorsionFactory::createTorsion(string torsionName, int ntypes,
                                          const vector<double>& params,
                                          double temp, int seed) {
  return createTorsionNone(seed);
}



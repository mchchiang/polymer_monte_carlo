/*
 * pair_factory.cpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#include <string>
#include <vector>
#include "pair_factory.hpp"
#include "pair.hpp"
#include "pair_lj_cut.hpp"
#include "pair_soft.hpp"
#include "pair_none.hpp"

using std::string;
using std::vector;

Pair* PairFactory::createPairLJCut(int ntypes, double epsilon,
                                   double sigma, double cutoff) {
  return new PairLJCut(ntypes, epsilon, sigma, cutoff);
}

Pair* PairFactory::createPairSoft(int ntypes, double a, double cutoff) {
  return new PairSoft(ntypes, a, cutoff);
}

Pair* PairFactory::createPairNone() {
  return new PairNone();
}

Pair* PairFactory::createPair(string pairName, int ntypes,
                              const vector<double>& args) {
  if (pairName.compare("ljcut") ==  0) {
    return createPairLJCut(ntypes, args[0], args[1], args[2]);
  } else if (pairName.compare("soft") == 0) {
    return createPairSoft(ntypes, args[0], args[1]);
  } else {
    return createPairNone();
  }
}


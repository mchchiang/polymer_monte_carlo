/*
 * pair_factory.hpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#ifndef PAIR_FACTORY_HPP_
#define PAIR_FACTORY_HPP_

#include <string>
#include <vector>
#include "pair.hpp"

class PairFactory {

private:
  Pair* createPairLJCut(int ntypes, double epsilon,
                        double sigma, double cutoff);
  Pair* createPairSoft(int ntypes, double a, double cutoff);
  Pair* createPairNone();

public:
  Pair* createPair(std::string pairName, int ntypes,
                   const std::vector<double>& args);

};

#endif /* PAIR_FACTORY_HPP_ */

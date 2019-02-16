/*
 * pair_none.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef PAIR_NONE_HPP_
#define PAIR_NONE_HPP_

#include <vector>
#include "pair.hpp"
#include "util_vector.hpp"

class PairNone : public Pair {

public:
  PairNone() {}
  ~PairNone() {}
  double compute(int type1, int type2,
                 const Vec& v1, const Vec& v2) {return 0.0;}
  double compute(int type1, int type2, double r) {return 0.0;}
  void setCoeff(int type1, int type2, const std::vector<double>& args) {}
  double getCoeff(int type1, int type2, int iarg) {return 0.0;}

};

#endif /* PAIR_NONE_HPP_ */

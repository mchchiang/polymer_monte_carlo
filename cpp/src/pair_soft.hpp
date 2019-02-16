/*
 * pair_soft.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef PAIR_SOFT_HPP_
#define PAIR_SOFT_HPP_

#include <vector>
#include "pair.hpp"
#include "util_vector.hpp"

class PairSoft : public Pair {

private:
  int ntypes;
  std::vector<double> a;
  std::vector<double> cutoff;

public:
  PairSoft(int ntypes, double a, double cutoff);
  ~PairSoft();
  double compute(int type1, int type2, const Vec& v1, const Vec& v2);
  double compute(int type1, int type2, double r);
  void setCoeff(int type1, int type2, const std::vector<double>& args);
  double getCoeff(int type1, int type2, int iarg);

};

#endif /* PAIR_SOFT_HPP_ */

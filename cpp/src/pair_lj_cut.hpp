/*
 * pair_lj_cut.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef PAIR_LJ_CUT_HPP_
#define PAIR_LJ_CUT_HPP_

#include <vector>
#include "pair.hpp"
#include "util_vector.hpp"

class PairLJCut : public Pair {

private:
  int ntypes;
  std::vector<double> epsilon;
  std::vector<double> sigma;
  std::vector<double> cutoff;

public:
  PairLJCut(int ntypes, double epsilon, double sigma, double cutoff);
  ~PairLJCut();
  double compute(int type1, int type2, const Vec& v1, const Vec& v2);
  double compute(int type1, int type2, double r);
  void setCoeff(int type1, int type2, const std::vector<double>& args);
  double getCoeff(int type1, int type2, int iarg);

};

#endif /* PAIR_LJ_CUT_HPP_ */

/*
 * bond_fene.hpp
 *
 *  Created on: 5 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOND_FENE_HPP_
#define BOND_FENE_HPP_

#include <vector>
#include "bond.hpp"
#include "util_vector.hpp"

class BondFENE : public Bond {

private:
  std::vector<double> epsilon;
  std::vector<double> sigma;
  std::vector<double> kf;
  std::vector<double> r0;
  const double rc {1.122462048309373}; // WCA cutoff

public:
  BondFENE(int ntypes, double epsilon, double sigma, double kf, double r0);
  ~BondFENE();
  double compute(int type, const Vec& r1, const Vec& r2);
  double compute(int type, double r);
  void setCoeff(int type, const std::vector<double>& args);
  void setCoeff(int type, int iarg, double value);
  double getCoeff(int type, int iarg);

};

#endif /* BOND_FENE_HPP_ */

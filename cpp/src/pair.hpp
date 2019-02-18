/*
 * pair.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef PAIR_HPP_
#define PAIR_HPP_

#include <vector>
#include "util_vector.hpp"

class Pair {

public:
  virtual ~Pair() {}
  virtual double compute(int type1, int type2,
                         const Vec& v1, const Vec& v2) = 0;
  virtual double compute(int type1, int type2, double r) = 0;
  virtual void setCoeff(int type1, int type2,
                        const std::vector<double>& args) = 0;
  virtual void setCoeff(int type1, int type2, int iarg, double value) = 0;
  virtual double getCoeff(int type1, int type2, int iarg) = 0;

};

#endif /* PAIR_HPP_ */

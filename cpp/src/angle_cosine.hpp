/*
 * angle_cosine.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_COSINE_HPP_
#define ANGLE_COSINE_HPP_

#include <vector>
#include "angle.hpp"
#include "util_vector.hpp"

class AngleCosine : public Angle {

private:
  std::vector<double> k;

public:
  AngleCosine(int ntypes, double k);
  ~AngleCosine();
  double compute(int type, const Vec& v1, const Vec& v2, const Vec& v3);
  double compute(int type, double theta);
  void setCoeff(int type, const std::vector<double>& k);
  void setCoeff(int type, int iarg, double value);
  double getCoeff(int type, int iarg);

};

#endif /* ANGLE_COSINE_HPP_ */

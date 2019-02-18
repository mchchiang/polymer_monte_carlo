/*
 * wall_none.hpp
 *
 *  Created on: 17 Feb 2019
 *      Author: michaelchiang
 */

#ifndef WALL_NONE_HPP_
#define WALL_NONE_HPP_

#include "wall.hpp"

class WallNone : public Wall {

public:
  WallNone() {}
  ~WallNone() {}
  double compute(unsigned int beadMask, const Vec& pos) {return 0.0;}
  void setCoeff(const std::vector<double>& args) {}
  void setCoeff(int iarg, double value) {}
  double getCoeff(int iarg) {return 0.0;}
  unsigned int getMask() {return 0;}
};

#endif /* WALL_NONE_HPP_ */

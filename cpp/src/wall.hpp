/*
 * wall.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef WALL_HPP_
#define WALL_HPP_

#include <vector>
#include "util_vector.hpp"

class Wall {

public:
  virtual ~Wall() {}
  virtual double compute(unsigned int beadMask, const Vec& pos) = 0;
  virtual void setCoeff(const std::vector<double>& args) = 0;
  virtual void setCoeff(int iarg, double value) = 0;
  virtual double getCoeff(int iarg) = 0;
  virtual unsigned int getMask() = 0;
};

#endif /* WALL_HPP_ */

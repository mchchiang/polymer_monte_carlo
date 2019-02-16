/*
 * wall.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef WALL_HPP_
#define WALL_HPP_

#include "util_vector.hpp"

class Wall {

public:
  virtual ~Wall() {}
  double compute(const Vec& v1);
};

#endif /* WALL_HPP_ */

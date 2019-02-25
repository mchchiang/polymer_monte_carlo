/*
 * bead.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BEAD_HPP_
#define BEAD_HPP_

#include "util_vector.hpp"

struct Bead {

  Vec pos {};
  int image[3] {0,0,0}; // Image count for periodic boundaries
  int type {};
  unsigned int mask {};

};

#endif /* BEAD_HPP_ */

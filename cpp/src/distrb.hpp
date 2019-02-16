/*
 * distrb.hpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#ifndef DISTRB_HPP_
#define DISTRB_HPP_

#include <random>

class Distribution {
private:
  std::mt19937 mt;
  std::uniform_real_distribution<double> rand;
protected:
  Distribution(int seed) {
    mt = std::mt19937(seed);
    rand = std::uniform_real_distribution<double>(0.0,1.0);
  }
  double nextRand() {return rand(mt);}
public:
  virtual ~Distribution() {}
};

#endif /* DISTRB_HPP_ */

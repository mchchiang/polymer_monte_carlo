/*
 * random_util.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef UTIL_RANDOM_HPP_
#define UTIL_RANDOM_HPP_

#include <random>

class RandomInt {
private:
  std::mt19937 mt;
  std::uniform_int_distribution<int> randInt;
  int seed;
  int min, max;

public:
  RandomInt(int _seed, int _min, int _max) :
    seed{_seed}, min{_min}, max{_max} {
      mt = std::mt19937(seed);
      randInt = std::uniform_int_distribution<int>(min, max);
    }
  ~RandomInt() {}
  int nextInt() {return randInt(mt);}
};

class RandomDouble {
private:
  std::mt19937 mt;
  std::uniform_real_distribution<double> randDouble;
  int seed;
  double min, max;

public:
  RandomDouble(int _seed, double _min, double _max) :
    seed{_seed}, min{_min}, max{_max} {
      mt = std::mt19937(seed);
      randDouble = std::uniform_real_distribution<double>(min, max);
    }
  ~RandomDouble() {}
  double nextDouble() {return randDouble(mt);}
};

#endif /* UTIL_RANDOM_HPP_ */

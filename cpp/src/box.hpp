/*
 * box.hpp
 *
 *  Created on: 21 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BOX_HPP_
#define BOX_HPP_

#include "util_vector.hpp"

class Box {

private:
  double boxSize[3];
  double boxLo[3];
  double boxHi[3];
  bool bound[3]; // periodic or not
  bool allUnbound;

public:
  Box(double xlo, double xhi, double ylo, double yhi, double zlo, double zhi,
      bool xBound, bool yBound, bool zBound);
  ~Box();
  double dist(const Vec& v1, const Vec& v2);
  double dist2(const Vec& v1, const Vec& v2);
  void wrapPos(Vec* v, int* image);
  void unwrapPos(Vec* v, int* image);

  double getBoxHi(int comp) const;
  double getBoxLo(int comp) const;
  double getBoxSize(int comp) const;

};

#endif /* BOX_HPP_ */

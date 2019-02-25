/*
 * box.cpp
 *
 *  Created on: 21 Feb 2019
 *      Author: michaelchiang
 */

#include "box.hpp"
#include "util_vector.hpp"

Box::Box(double xlo, double xhi, double ylo, double yhi,
         double zlo, double zhi, bool xBound, bool yBound, bool zBound) {
  boxLo[0] = xlo;
  boxLo[1] = ylo;
  boxLo[2] = zlo;
  boxHi[0] = xhi;
  boxHi[1] = yhi;
  boxHi[2] = zhi;
  boxSize[0] = xhi - xlo;
  boxSize[1] = yhi - ylo;
  boxSize[2] = zhi - zlo;
  bound[0] = xBound;
  bound[1] = yBound;
  bound[2] = zBound;
  allUnbound = !xBound && !yBound && !zBound;
}

Box::~Box() {}

double Box::dist(const Vec& v1, const Vec& v2) {
  if (allUnbound) {
    return Vec::dist(v1, v2);
  } else {
    double d1, d2;
    double sum {};
    for (int i {}; i < 3; i++) {
      if (bound[i]) {
        d1 = fabs(v1[i] - v2[i]);
        d2 = boxSize[i] - d1;
        sum += d1 < d2 ? d1*d1 : d2*d2;
      } else {
        d1 = v1[i] - v2[i];
        sum += d1*d1;
      }
    }
    return sqrt(sum);
  }
}

double Box::dist2(const Vec& v1, const Vec& v2) {
  if (allUnbound) {
    return Vec::dist2(v1, v2);
  } else {
    double d1, d2;
    double sum {};
    for (int i {}; i < 3; i++) {
      if (bound[i]) {
        d1 = fabs(v1[i] - v2[i]);
        d2 = boxSize[i] - d1;
        sum += d1<d2 ? d1*d1 : d2*d2;
      } else {
        d1 = v1[i] - v2[i];
        sum += d1*d1;
      }
    }
    return sum;
  }
}

void Box::wrapPos(Vec* v, int* image) {
  double diff;
  int count;
  for (int i {}; i < 3; i++) {
    if (bound[i]) {
      if ((*v)[i] > boxHi[i]) {
        diff = (*v)[i] - boxHi[i];
        count = static_cast<int>(floor(diff/boxSize[i]));
        (*v)[i] = boxLo[i] + (diff-count*boxSize[i]);
        image[i] += count + 1;
      } else if ((*v)[i] < boxLo[i]) {
        diff = boxLo[i] - (*v)[i];
        count = static_cast<int>(floor(diff/boxSize[i]));
        (*v)[i] = boxHi[i] - (diff-count*boxSize[i]);
        image[i] -= (count + 1);
      }
    } else {
      image[i] += 0;
    }
  }
}

void Box::unwrapPos(Vec* v, int* image) {
  for (int i {}; i < 3; i++) {
    (*v)[i] += boxSize[i]*image[i];
  }
}

double Box::getBoxHi(int comp) const {
  return boxHi[comp];
}

double Box::getBoxLo(int comp) const {
  return boxLo[comp];
}

double Box::getBoxSize(int comp) const {
  return boxSize[comp];
}

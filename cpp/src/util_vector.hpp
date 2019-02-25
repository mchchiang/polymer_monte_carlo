/*
 * vector_util.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef UTIL_VECTOR_HPP_
#define UTIL_VECTOR_HPP_

#include <cmath>

class Vec {

private:
  double vec[3];

public:

  Vec();
  Vec(double x, double y, double z);
  Vec(const Vec& v);
  ~Vec();

  double& operator [](const int& i);
  const double& operator [](const int& i) const;
  Vec& operator =(const Vec& v);
  bool operator ==(const Vec& v);
  Vec operator +(const Vec& v) const;
  Vec operator -(const Vec& v) const;
  Vec operator *(double a) const;
  Vec operator /(double a) const;
  Vec& operator +=(const Vec& v);
  Vec& operator -=(const Vec& v);
  Vec& operator *=(double a);
  Vec& operator /=(double a);

  static double mag(const Vec& a);
  static double mag2(const Vec& a);
  static double dist(const Vec& a, const Vec& b);
  static double dist2(const Vec& a, const Vec& b);
  static Vec add(const Vec& a, const Vec& b);
  static Vec diff(const Vec& a, const Vec& b);
  static double dot(const Vec& a, const Vec& b);

};

class Mat {

private:
  Vec mat[3];

public:

  Mat();
  Mat(const Mat& m);
  ~Mat();

  Vec& operator [](const int& i);
  const Vec& operator [](const int& i) const;
  Mat& operator =(const Mat& n);
  bool operator ==(const Mat& n);
  Mat operator +(const Mat& n) const;
  Mat operator -(const Mat& n) const;
  Mat operator *(double a) const;
  Mat operator /(double a) const;
  void dot(const Mat& m);
  void toUnity();

  static Vec matvec(const Mat& m, const Vec& v);
  static Mat matmat(const Mat& m, const Mat& n);
  static Mat unity();

};

#endif /* UTIL_VECTOR_HPP_ */

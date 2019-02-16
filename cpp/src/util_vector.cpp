/*
 * vector_util.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include "util_vector.hpp"

Vec::Vec() : Vec(0,0,0) {}
Vec::Vec(double _x, double _y, double _z) : vec {_x, _y, _z} {}
Vec::Vec(const Vec& v) : vec {v.vec[0], v.vec[1], v.vec[2]} {}
Vec::~Vec() {}

Vec& Vec::operator =(const Vec& v) {
  vec[0] = v.vec[0];
  vec[1] = v.vec[1];
  vec[2] = v.vec[2];
  return *this;
}

double& Vec::operator [](const int& i) {
  return vec[i];
}

const double& Vec::operator [](const int& i) const {
  return vec[i];
}

bool Vec::operator ==(const Vec& v) {
  return (vec[0] == v.vec[0] && vec[1] == v.vec[1] && vec[2] == v.vec[2]);
}

Vec Vec::operator +(const Vec& v) const {
  return Vec(vec[0] + v.vec[0], vec[1] + v.vec[1], vec[2] + v.vec[2]);
}

Vec Vec::operator -(const Vec& v) const {
  return Vec(vec[0] - v.vec[0], vec[1] - v.vec[1],vec[2] - v.vec[2]);
}

Vec Vec::operator *(double a) const {
  return Vec(a*vec[0], a*vec[1], a*vec[2]);
}

Vec Vec::operator /(double a) const {
  return Vec(vec[0]/a, vec[1]/a, vec[2]/a);
}

double Vec::mag(const Vec& a) {
  return sqrt(a.vec[0] * a.vec[0] + a.vec[1] * a.vec[1] + a.vec[2] * a.vec[2]);
}

double Vec::mag2(const Vec& a) {
  return a.vec[0] * a.vec[0] + a.vec[1] * a.vec[1] + a.vec[2] * a.vec[2];
}

double Vec::dist(const Vec& a, const Vec& b) {
  double delx, dely, delz;
  delx = a.vec[0] - b.vec[0];
  dely = a.vec[1] - b.vec[1];
  delz = a.vec[2] - b.vec[2];
  return sqrt(delx * delx + dely * dely + delz * delz);
}

double Vec::dist2(const Vec& a, const Vec& b) {
  double delx, dely, delz;
  delx = a.vec[0] - b.vec[0];
  dely = a.vec[1] - b.vec[1];
  delz = a.vec[2] - b.vec[2];
  return delx * delx + dely * dely + delz * delz;
}

void Vec::add(const Vec& a, const Vec& b, Vec& c) {
  c.vec[0] = a.vec[0] + b.vec[0];
  c.vec[1] = a.vec[1] + b.vec[1];
  c.vec[2] = a.vec[2] + b.vec[2];
}

void Vec::diff(const Vec& a, const Vec& b, Vec& c) {
  c.vec[0] = a.vec[0] - b.vec[0];
  c.vec[1] = a.vec[1] - b.vec[1];
  c.vec[2] = a.vec[2] - b.vec[2];
}

double Vec::dot(const Vec& a, const Vec& b) {
  return a.vec[0] * b.vec[0] + a.vec[1] * b.vec[1] + a.vec[2] * b.vec[2];
}

Mat::Mat() {}
Mat::Mat(const Mat& m) {
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      mat[i][j] = m.mat[i][j];
    }
  }
}
Mat::~Mat() {}

Mat& Mat::operator =(const Mat& m) {
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      mat[i][j] = m.mat[i][j];
    }
  }
  return *this;
}

Vec& Mat::operator [](const int& i) {
  return mat[i];
}

const Vec& Mat::operator [](const int& i) const {
  return mat[i];
}

bool Mat::operator ==(const Mat& m) {
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      if (mat[i][j] != m.mat[i][j]) return false;
    }
  }
  return true;
}

Mat Mat::operator +(const Mat& m) const {
  Mat n {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      n.mat[i][j] = mat[i][j] + m.mat[i][j];
    }
  }
  return n;
}

Mat Mat::operator -(const Mat& m) const {
  Mat n {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      n.mat[i][j] = mat[i][j] - m.mat[i][j];
    }
  }
  return n;
}

Mat Mat::operator *(double a) const {
  Mat n {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      n.mat[i][j] = mat[i][j] * a;
    }
  }
  return n;
}

Mat Mat::operator /(double a) const {
  Mat n {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      n.mat[i][j] = mat[i][j] / a;
    }
  }
  return n;
}

void Mat::dot(const Mat& m) {
  Vec v {};
  for (int i {}; i < 3; i++) {
    v[0] = mat[i][0];
    v[1] = mat[i][1];
    v[2] = mat[i][2];
    for (int j {}; j < 3; j++) {
      mat[i][j] = v[0] * m.mat[0][j];
      mat[i][j] += v[1] * m.mat[1][j];
      mat[i][j] += v[2] * m.mat[2][j];
    }
  }
}

void Mat::toUnity() {
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      mat[i][j] = (i==j ? 1.0 : 0.0);
    }
  }
}

Vec Mat::matvec(const Mat& m, const Vec& v) {
  Vec w {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      w[i] += m.mat[i][j]*v[j];
    }
  }
  return w;
}

Mat Mat::matmat(const Mat& m, const Mat& n) {
  Mat o {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      for (int k {}; k < 3; k++) {
        o[i][j] += m[i][k] * n[k][j];
      }
    }
  }
  return o;
}

Mat Mat::unity() {
  Mat m {};
  for (int i {}; i < 3; i++) {
    m.mat[i][i] = 1.0;
  }
  return m;
}

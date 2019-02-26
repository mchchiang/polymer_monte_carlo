/*
 * test_util_vector.cpp
 *
 *  Created on: 18 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "util_vector.hpp"

BOOST_AUTO_TEST_SUITE(TestVec)

const double tol {1e-10};

// Test the Vec class
BOOST_AUTO_TEST_CASE(TestSubscript) {
  Vec v {1.43, 2.68, -3.74};
  BOOST_CHECK_CLOSE(v[0], 1.43, tol);
  BOOST_CHECK_CLOSE(v[1], 2.68, tol);
  BOOST_CHECK_CLOSE(v[2], -3.74, tol);
}

BOOST_AUTO_TEST_CASE(TestAssignment) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 = v1;
  BOOST_CHECK_CLOSE(v2[0], 1.43, tol);
  BOOST_CHECK_CLOSE(v2[1], 2.68, tol);
  BOOST_CHECK_CLOSE(v2[2], -3.74, tol);
}

BOOST_AUTO_TEST_CASE(TestAdd) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  Vec v3 {v1 + v2};
  Vec expected {3.75, 3.55, 1.38};
  BOOST_CHECK_CLOSE(v3[0], expected[0], tol);
  BOOST_CHECK_CLOSE(v3[1], expected[1], tol);
  BOOST_CHECK_CLOSE(v3[2], expected[2], tol);
}

BOOST_AUTO_TEST_CASE(TestDiff) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  Vec expected {-0.89, 1.81, -8.86};
  Vec v3 {v1 - v2};
  BOOST_CHECK_CLOSE(v3[0], expected[0], tol);
  BOOST_CHECK_CLOSE(v3[1], expected[1], tol);
  BOOST_CHECK_CLOSE(v3[2], expected[2], tol);
}

BOOST_AUTO_TEST_CASE(TestMultiply) {
  Vec v1 {1.43, 2.68, -3.74};
  double a {-4.2};
  Vec v2 {v1 * a};
  Vec expected {-6.006, -11.256, 15.708};
  BOOST_CHECK_CLOSE(v2[0], expected[0], tol);
  BOOST_CHECK_CLOSE(v2[1], expected[1], tol);
  BOOST_CHECK_CLOSE(v2[2], expected[2], tol);
}

BOOST_AUTO_TEST_CASE(TestDivide) {
  Vec v1 {1.43, 2.68, -3.74};
  double a {-2.0};
  Vec v2 {v1 / a};
  Vec expected {-0.715, -1.34, 1.87};
  BOOST_CHECK_CLOSE(v2[0], expected[0], tol);
  BOOST_CHECK_CLOSE(v2[1], expected[1], tol);
  BOOST_CHECK_CLOSE(v2[2], expected[2], tol);
}

BOOST_AUTO_TEST_CASE(TestStaticMag) {
  Vec v {1.43, 2.68, -3.74};
  double expected {4.818184305316683};
  BOOST_CHECK_CLOSE(Vec::mag(v), expected, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticMag2) {
  Vec v {1.43, 2.68, -3.74};
  double expected {23.2149};
  BOOST_CHECK_CLOSE(Vec::mag2(v), expected, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticDist) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  double expected {9.086682562959927};
  BOOST_CHECK_CLOSE(Vec::dist(v1, v2), expected, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticDist2) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  double expected {82.5678};
  BOOST_CHECK_CLOSE(Vec::dist2(v1, v2), expected, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticAdd) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  Vec expected {3.75, 3.55, 1.38};
  Vec v3 {Vec::add(v1,v2)};
  BOOST_CHECK_CLOSE(v3[0], expected[0], tol);
  BOOST_CHECK_CLOSE(v3[1], expected[1], tol);
  BOOST_CHECK_CLOSE(v3[2], expected[2], tol);
}

BOOST_AUTO_TEST_CASE(TestStaticDiff) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  Vec expected {-0.89, 1.81, -8.86};
  Vec v3 {Vec::diff(v1,v2)};
  BOOST_CHECK_CLOSE(v3[0], expected[0], tol);
  BOOST_CHECK_CLOSE(v3[1], expected[1], tol);
  BOOST_CHECK_CLOSE(v3[2], expected[2], tol);
}

BOOST_AUTO_TEST_CASE(TestStaticDot) {
  Vec v1 {1.43, 2.68, -3.74};
  Vec v2 {2.32, 0.87, 5.12};
  double expected {-13.4996};
  BOOST_CHECK_CLOSE(Vec::dot(v1, v2), expected, tol);
}

BOOST_AUTO_TEST_SUITE_END()

// Test the Mat class
BOOST_AUTO_TEST_SUITE(TestMat)

const double tol {1e-10};

BOOST_AUTO_TEST_CASE(TestEmptyConstructor) {
  Mat m {};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      BOOST_CHECK_CLOSE(m[i][j], 0.0, tol);
    }
  }
}

BOOST_AUTO_TEST_CASE(TestSubscript) {
  Vec v[3] {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}};
  Mat m {v};
  BOOST_CHECK_CLOSE(m[0][0], 1.0, tol);
  BOOST_CHECK_CLOSE(m[0][1], 2.0, tol);
  BOOST_CHECK_CLOSE(m[0][2], 3.0, tol);
  BOOST_CHECK_CLOSE(m[1][0], 4.0, tol);
  BOOST_CHECK_CLOSE(m[1][1], 5.0, tol);
  BOOST_CHECK_CLOSE(m[1][2], 6.0, tol);
  BOOST_CHECK_CLOSE(m[2][0], 7.0, tol);
  BOOST_CHECK_CLOSE(m[2][1], 8.0, tol);
  BOOST_CHECK_CLOSE(m[2][2], 9.0, tol);
}

BOOST_AUTO_TEST_CASE(TestAssignment) {
  Vec v[3] {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}};
  Mat m1 {v};
  Mat m2 {};
  m2 = m1;
  BOOST_CHECK_CLOSE(m2[0][0], 1.0, tol);
  BOOST_CHECK_CLOSE(m2[0][1], 2.0, tol);
  BOOST_CHECK_CLOSE(m2[0][2], 3.0, tol);
  BOOST_CHECK_CLOSE(m2[1][0], 4.0, tol);
  BOOST_CHECK_CLOSE(m2[1][1], 5.0, tol);
  BOOST_CHECK_CLOSE(m2[1][2], 6.0, tol);
  BOOST_CHECK_CLOSE(m2[2][0], 7.0, tol);
  BOOST_CHECK_CLOSE(m2[2][1], 8.0, tol);
  BOOST_CHECK_CLOSE(m2[2][2], 9.0, tol);
}

BOOST_AUTO_TEST_CASE(TestAdd) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Vec v2[3] {
    {6.0, 2.0, 5.0},
    {4.0, 3.0, 8.0},
    {9.0, 1.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {v2};
  Mat m3 {m1 + m2};
  BOOST_CHECK_CLOSE(m3[0][0], 9.0, tol);
  BOOST_CHECK_CLOSE(m3[0][1], 3.0, tol);
  BOOST_CHECK_CLOSE(m3[0][2], 9.0, tol);
  BOOST_CHECK_CLOSE(m3[1][0], 6.0, tol);
  BOOST_CHECK_CLOSE(m3[1][1], 8.0, tol);
  BOOST_CHECK_CLOSE(m3[1][2], 16.0, tol);
  BOOST_CHECK_CLOSE(m3[2][0], 15.0, tol);
  BOOST_CHECK_CLOSE(m3[2][1], 10.0, tol);
  BOOST_CHECK_CLOSE(m3[2][2], 14.0, tol);
}

BOOST_AUTO_TEST_CASE(TestSubtract) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Vec v2[3] {
    {6.0, 2.0, 5.0},
    {4.0, 3.0, 8.0},
    {9.0, 1.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {v2};
  Mat m3 {m1 - m2};
  BOOST_CHECK_CLOSE(m3[0][0], -3.0, tol);
  BOOST_CHECK_CLOSE(m3[0][1], -1.0, tol);
  BOOST_CHECK_CLOSE(m3[0][2], -1.0, tol);
  BOOST_CHECK_CLOSE(m3[1][0], -2.0, tol);
  BOOST_CHECK_CLOSE(m3[1][1], 2.0, tol);
  BOOST_CHECK_CLOSE(m3[1][2], 0.0, tol);
  BOOST_CHECK_CLOSE(m3[2][0], -3.0, tol);
  BOOST_CHECK_CLOSE(m3[2][1], 8.0, tol);
  BOOST_CHECK_CLOSE(m3[2][2], 0.0, tol);
}

BOOST_AUTO_TEST_CASE(TestMultiply) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {m1 * 2.0};
  BOOST_CHECK_CLOSE(m2[0][0], 6.0, tol);
  BOOST_CHECK_CLOSE(m2[0][1], 2.0, tol);
  BOOST_CHECK_CLOSE(m2[0][2], 8.0, tol);
  BOOST_CHECK_CLOSE(m2[1][0], 4.0, tol);
  BOOST_CHECK_CLOSE(m2[1][1], 10.0, tol);
  BOOST_CHECK_CLOSE(m2[1][2], 16.0, tol);
  BOOST_CHECK_CLOSE(m2[2][0], 12.0, tol);
  BOOST_CHECK_CLOSE(m2[2][1], 18.0, tol);
  BOOST_CHECK_CLOSE(m2[2][2], 14.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDivide) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {m1 / 2.0};
  BOOST_CHECK_CLOSE(m2[0][0], 1.5, tol);
  BOOST_CHECK_CLOSE(m2[0][1], 0.5, tol);
  BOOST_CHECK_CLOSE(m2[0][2], 2.0, tol);
  BOOST_CHECK_CLOSE(m2[1][0], 1.0, tol);
  BOOST_CHECK_CLOSE(m2[1][1], 2.5, tol);
  BOOST_CHECK_CLOSE(m2[1][2], 4.0, tol);
  BOOST_CHECK_CLOSE(m2[2][0], 3.0, tol);
  BOOST_CHECK_CLOSE(m2[2][1], 4.5, tol);
  BOOST_CHECK_CLOSE(m2[2][2], 3.5, tol);
}

BOOST_AUTO_TEST_CASE(TestToUnity) {
  Mat m {};
  m.toUnity();
  BOOST_CHECK_CLOSE(m[0][0], 1.0, tol);
  BOOST_CHECK_CLOSE(m[0][1], 0.0, tol);
  BOOST_CHECK_CLOSE(m[0][2], 0.0, tol);
  BOOST_CHECK_CLOSE(m[1][0], 0.0, tol);
  BOOST_CHECK_CLOSE(m[1][1], 1.0, tol);
  BOOST_CHECK_CLOSE(m[1][2], 0.0, tol);
  BOOST_CHECK_CLOSE(m[2][0], 0.0, tol);
  BOOST_CHECK_CLOSE(m[2][1], 0.0, tol);
  BOOST_CHECK_CLOSE(m[2][2], 1.0, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticUnity) {
  Mat m {Mat::unity()};
  BOOST_CHECK_CLOSE(m[0][0], 1.0, tol);
  BOOST_CHECK_CLOSE(m[0][1], 0.0, tol);
  BOOST_CHECK_CLOSE(m[0][2], 0.0, tol);
  BOOST_CHECK_CLOSE(m[1][0], 0.0, tol);
  BOOST_CHECK_CLOSE(m[1][1], 1.0, tol);
  BOOST_CHECK_CLOSE(m[1][2], 0.0, tol);
  BOOST_CHECK_CLOSE(m[2][0], 0.0, tol);
  BOOST_CHECK_CLOSE(m[2][1], 0.0, tol);
  BOOST_CHECK_CLOSE(m[2][2], 1.0, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticMatVec) {
  Vec v[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Mat m {v};
  Vec u {4.0, 2.0, 7.0};
  Vec w {Mat::matvec(m, u)};
  BOOST_CHECK_CLOSE(w[0], 42.0, tol);
  BOOST_CHECK_CLOSE(w[1], 74.0, tol);
  BOOST_CHECK_CLOSE(w[2], 91.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDot1) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Vec v2[3] {
    {6.0, 2.0, 5.0},
    {4.0, 3.0, 8.0},
    {9.0, 1.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {v2};
  m1.dot(m2);
  BOOST_CHECK_CLOSE(m1[0][0], 58.0, tol);
  BOOST_CHECK_CLOSE(m1[0][1], 13.0, tol);
  BOOST_CHECK_CLOSE(m1[0][2], 51.0, tol);
  BOOST_CHECK_CLOSE(m1[1][0], 104.0, tol);
  BOOST_CHECK_CLOSE(m1[1][1], 27.0, tol);
  BOOST_CHECK_CLOSE(m1[1][2], 106.0, tol);
  BOOST_CHECK_CLOSE(m1[2][0], 135.0, tol);
  BOOST_CHECK_CLOSE(m1[2][1], 46.0, tol);
  BOOST_CHECK_CLOSE(m1[2][2], 151.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDot2) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Vec v2[3] {
    {6.0, 2.0, 5.0},
    {4.0, 3.0, 8.0},
    {9.0, 1.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {v2};
  m2.dot(m1);
  BOOST_CHECK_CLOSE(m2[0][0], 52.0, tol);
  BOOST_CHECK_CLOSE(m2[0][1], 61.0, tol);
  BOOST_CHECK_CLOSE(m2[0][2], 75.0, tol);
  BOOST_CHECK_CLOSE(m2[1][0], 66.0, tol);
  BOOST_CHECK_CLOSE(m2[1][1], 91.0, tol);
  BOOST_CHECK_CLOSE(m2[1][2], 96.0, tol);
  BOOST_CHECK_CLOSE(m2[2][0], 71.0, tol);
  BOOST_CHECK_CLOSE(m2[2][1], 77.0, tol);
  BOOST_CHECK_CLOSE(m2[2][2], 93.0, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticMatMat1) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Vec v2[3] {
    {6.0, 2.0, 5.0},
    {4.0, 3.0, 8.0},
    {9.0, 1.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {v2};
  Mat m3 {Mat::matmat(m1, m2)};
  BOOST_CHECK_CLOSE(m3[0][0], 58.0, tol);
  BOOST_CHECK_CLOSE(m3[0][1], 13.0, tol);
  BOOST_CHECK_CLOSE(m3[0][2], 51.0, tol);
  BOOST_CHECK_CLOSE(m3[1][0], 104.0, tol);
  BOOST_CHECK_CLOSE(m3[1][1], 27.0, tol);
  BOOST_CHECK_CLOSE(m3[1][2], 106.0, tol);
  BOOST_CHECK_CLOSE(m3[2][0], 135.0, tol);
  BOOST_CHECK_CLOSE(m3[2][1], 46.0, tol);
  BOOST_CHECK_CLOSE(m3[2][2], 151.0, tol);
}

BOOST_AUTO_TEST_CASE(TestStaticMatMat2) {
  Vec v1[3] {
    {3.0, 1.0, 4.0},
    {2.0, 5.0, 8.0},
    {6.0, 9.0, 7.0}};
  Vec v2[3] {
    {6.0, 2.0, 5.0},
    {4.0, 3.0, 8.0},
    {9.0, 1.0, 7.0}};
  Mat m1 {v1};
  Mat m2 {v2};
  Mat m3 {Mat::matmat(m2, m1)};
  BOOST_CHECK_CLOSE(m3[0][0], 52.0, tol);
  BOOST_CHECK_CLOSE(m3[0][1], 61.0, tol);
  BOOST_CHECK_CLOSE(m3[0][2], 75.0, tol);
  BOOST_CHECK_CLOSE(m3[1][0], 66.0, tol);
  BOOST_CHECK_CLOSE(m3[1][1], 91.0, tol);
  BOOST_CHECK_CLOSE(m3[1][2], 96.0, tol);
  BOOST_CHECK_CLOSE(m3[2][0], 71.0, tol);
  BOOST_CHECK_CLOSE(m3[2][1], 77.0, tol);
  BOOST_CHECK_CLOSE(m3[2][2], 93.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()


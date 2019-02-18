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

BOOST_AUTO_TEST_CASE(TestSubscript) {

}

BOOST_AUTO_TEST_CASE(TestAssignment) {

}

BOOST_AUTO_TEST_CASE(TestStaticUnity) {
  Mat m {Mat::unity()};

}

BOOST_AUTO_TEST_SUITE_END()


/*
 * test_box.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "box.hpp"

struct Fixture {
  double lo1[3] {-10.0, -20.0, -30.0};
  double hi1[3] {10.0, 20.0, 30.0};
  bool bound[3] {true, true, true};
  Box box1 {lo1[0], hi1[0], lo1[1], hi1[1], lo1[2], hi1[2],
    bound[0], bound[1], bound[2]};
  Box box2 {lo1[0], hi1[0], lo1[1], hi1[1], lo1[2], hi1[2],
    true, true, false};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestBox, Fixture)

BOOST_AUTO_TEST_CASE(TestGetBoxLo) {
  BOOST_CHECK_CLOSE(box1.getBoxLo(0), lo1[0], tol);
  BOOST_CHECK_CLOSE(box1.getBoxLo(1), lo1[1], tol);
  BOOST_CHECK_CLOSE(box1.getBoxLo(2), lo1[2], tol);
}

BOOST_AUTO_TEST_CASE(TestGetBoxHi) {
  BOOST_CHECK_CLOSE(box1.getBoxHi(0), hi1[0], tol);
  BOOST_CHECK_CLOSE(box1.getBoxHi(1), hi1[1], tol);
  BOOST_CHECK_CLOSE(box1.getBoxHi(2), hi1[2], tol);
}

BOOST_AUTO_TEST_CASE(TestGetBoxSize) {
  BOOST_CHECK_CLOSE(box1.getBoxSize(0), hi1[0]-lo1[0], tol);
  BOOST_CHECK_CLOSE(box1.getBoxSize(1), hi1[1]-lo1[1], tol);
  BOOST_CHECK_CLOSE(box1.getBoxSize(2), hi1[2]-lo1[2], tol);
}

BOOST_AUTO_TEST_CASE(TestWrapPos1) {
  Vec v {2.0, 3.0, 4.0};
  Vec exp {2.0, 3.0, 4.0};
  int i[3] {0, 0, 0};
  int iexp[3] {0, 0, 0};
  box1.wrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
  BOOST_CHECK_EQUAL(i[0], iexp[0]);
  BOOST_CHECK_EQUAL(i[1], iexp[1]);
  BOOST_CHECK_EQUAL(i[2], iexp[2]);
}

BOOST_AUTO_TEST_CASE(TestWrapPos2) {
  Vec v {24.0, -33.0, 46.0};
  Vec exp {4.0, 7.0, -14.0};
  int i[3] {0, 0, 0};
  int iexp[3] {1, -1, 1};
  box1.wrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
  BOOST_CHECK_EQUAL(i[0], iexp[0]);
  BOOST_CHECK_EQUAL(i[1], iexp[1]);
  BOOST_CHECK_EQUAL(i[2], iexp[2]);
}

BOOST_AUTO_TEST_CASE(TestWrapPos3) {
  Vec v {2.0, 3.0, 4.0};
  Vec exp {2.0, 3.0, 4.0};
  int i[3] {0, 0, 0};
  int iexp[3] {0, 0, 0};
  box2.wrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
  BOOST_CHECK_EQUAL(i[0], iexp[0]);
  BOOST_CHECK_EQUAL(i[1], iexp[1]);
  BOOST_CHECK_EQUAL(i[2], iexp[2]);
}

BOOST_AUTO_TEST_CASE(TestWrapPos4) {
  Vec v {24.0, -33.0, 46.0};
  Vec exp {4.0, 7.0, 46.0};
  int i[3] {0, 0, 0};
  int iexp[3] {1, -1, 0};
  box2.wrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
  BOOST_CHECK_EQUAL(i[0], iexp[0]);
  BOOST_CHECK_EQUAL(i[1], iexp[1]);
  BOOST_CHECK_EQUAL(i[2], iexp[2]);
}

BOOST_AUTO_TEST_CASE(TestUnwrapPos1) {
  Vec v {2.0, 3.0, 4.0};
  Vec exp {2.0, 3.0, 4.0};
  int i[3] {0, 0, 0};
  box1.unwrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
}

BOOST_AUTO_TEST_CASE(TestUnwrapPos2) {
  Vec v {4.0, 7.0, -14.0};
  Vec exp {24.0, -33.0, 46.0};
  int i[3] {1, -1, 1};
  box1.unwrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
}

BOOST_AUTO_TEST_CASE(TestUnwrapPos3) {
  Vec v {2.0, 3.0, 4.0};
  Vec exp {2.0, 3.0, 4.0};
  int i[3] {0, 0, 0};
  box2.unwrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
}

BOOST_AUTO_TEST_CASE(TestUnwrapPos4) {
  Vec v {4.0, 7.0, -14.0};
  Vec exp {24.0, -33.0, 46.0};
  int i[3] {1, -1, 1};
  box2.unwrapPos(&v, i);
  BOOST_CHECK_CLOSE(v[0], exp[0], tol);
  BOOST_CHECK_CLOSE(v[1], exp[1], tol);
  BOOST_CHECK_CLOSE(v[2], exp[2], tol);
}

BOOST_AUTO_TEST_CASE(TestDist1) {
  Vec v1 {2.0, 3.0, 4.0};
  Vec v2 {5.0, -1.0, 6.0};
  BOOST_CHECK_CLOSE(box1.dist(v1,v2), 5.385164807134504, tol);
}

BOOST_AUTO_TEST_CASE(TestDist21) {
  Vec v1 {2.0, 3.0, 4.0};
  Vec v2 {5.0, -1.0, 6.0};
  BOOST_CHECK_CLOSE(box1.dist2(v1,v2), 29.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDist2) {
  Vec v1 {9.0, 18.0, 18.0};
  Vec v2 {-8.0, -6.0, -25.0};
  BOOST_CHECK_CLOSE(box1.dist(v1,v2), 23.53720459187964, tol);
}

BOOST_AUTO_TEST_CASE(TestDist22) {
  Vec v1 {9.0, 18.0, 18.0};
  Vec v2 {-8.0, -6.0, -25.0};
  BOOST_CHECK_CLOSE(box1.dist2(v1,v2), 554.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDist3) {
  Vec v1 {8.0, 4.0, 10.0};
  Vec v2 {-6.0, -8.0, -18.0};
  BOOST_CHECK_CLOSE(box1.dist(v1,v2), 31.04834939252005, tol);
}

BOOST_AUTO_TEST_CASE(TestDist23) {
  Vec v1 {8.0, 4.0, 10.0};
  Vec v2 {-6.0, -8.0, -18.0};
  BOOST_CHECK_CLOSE(box1.dist2(v1,v2), 964.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDist4) {
  Vec v1 {2.0, 3.0, 4.0};
  Vec v2 {5.0, -1.0, 6.0};
  BOOST_CHECK_CLOSE(box2.dist(v1,v2), 5.385164807134504, tol);
}

BOOST_AUTO_TEST_CASE(TestDist24) {
  Vec v1 {2.0, 3.0, 4.0};
  Vec v2 {5.0, -1.0, 6.0};
  BOOST_CHECK_CLOSE(box2.dist2(v1,v2), 29.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDist5) {
  Vec v1 {9.0, 18.0, 18.0};
  Vec v2 {-8.0, -6.0, -25.0};
  BOOST_CHECK_CLOSE(box2.dist(v1,v2), 45.9782557302906, tol);
}

BOOST_AUTO_TEST_CASE(TestDist25) {
  Vec v1 {9.0, 18.0, 18.0};
  Vec v2 {-8.0, -6.0, -25.0};
  BOOST_CHECK_CLOSE(box2.dist2(v1,v2), 2114.0, tol);
}

BOOST_AUTO_TEST_CASE(TestDist6) {
  Vec v1 {8.0, 4.0, 10.0};
  Vec v2 {-6.0, -8.0, -26.0};
  BOOST_CHECK_CLOSE(box2.dist(v1,v2), 38.41874542459709, tol);
}

BOOST_AUTO_TEST_CASE(TestDist26) {
  Vec v1 {8.0, 4.0, 10.0};
  Vec v2 {-6.0, -8.0, -26.0};
  BOOST_CHECK_CLOSE(box2.dist2(v1,v2), 1476.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()

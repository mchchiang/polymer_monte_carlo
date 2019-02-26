/*
 * test_wall_none.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "wall_none.hpp"

struct Fixture {
  WallNone wallNone {};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestWallNone, Fixture)

BOOST_AUTO_TEST_CASE(TestComputeDist) {
  BOOST_CHECK_CLOSE(wallNone.compute(0, {3.2, -5.1, 0.8}), 0.0, tol);
  BOOST_CHECK_CLOSE(wallNone.compute(1, {34.2, 8.1, 9.34}), 0.0, tol);
  BOOST_CHECK_CLOSE(wallNone.compute(2, {1.22, 4.1, -6.8}), 0.0, tol);
  BOOST_CHECK_CLOSE(wallNone.compute(3, {12.2, -0.98, 2.4}), 0.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff) {
  BOOST_CHECK_CLOSE(wallNone.getCoeff(0), 0.0, tol);
  BOOST_CHECK_CLOSE(wallNone.getCoeff(1), 0.0, tol);
  BOOST_CHECK_CLOSE(wallNone.getCoeff(2), 0.0, tol);
  BOOST_CHECK_CLOSE(wallNone.getCoeff(3), 0.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()



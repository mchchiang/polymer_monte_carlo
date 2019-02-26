/*
 * test_angle_none.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "angle_none.hpp"

struct Fixture {
  AngleNone angleNone {};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestAngleNone, Fixture)

BOOST_AUTO_TEST_CASE(TestComputeTheta) {
  BOOST_CHECK_CLOSE(angleNone.compute(0, 1.4522), 0.0, tol);
  BOOST_CHECK_CLOSE(angleNone.compute(1, -2.2342), 0.0, tol);
  BOOST_CHECK_CLOSE(angleNone.compute(2, 3.8342), 0.0, tol);
  BOOST_CHECK_CLOSE(angleNone.compute(3, 65.3421), 0.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff) {
  BOOST_CHECK_CLOSE(angleNone.getCoeff(0, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(angleNone.getCoeff(1, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(angleNone.getCoeff(1, 2), 0.0, tol);
  BOOST_CHECK_CLOSE(angleNone.getCoeff(0, 2), 0.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()

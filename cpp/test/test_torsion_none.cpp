/*
 * test_torsion_none.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "torsion_none.hpp"

struct Fixture {
  TorsionNone torsionNone {};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestTorsionNone, Fixture)

BOOST_AUTO_TEST_CASE(TestComputePhi) {
  BOOST_CHECK_CLOSE(torsionNone.compute(0, 3.2342), 0.0, tol);
  BOOST_CHECK_CLOSE(torsionNone.compute(1, -1.7453), 0.0, tol);
  BOOST_CHECK_CLOSE(torsionNone.compute(2, 4.32491), 0.0, tol);
  BOOST_CHECK_CLOSE(torsionNone.compute(3, 35.932), 0.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff) {
  BOOST_CHECK_CLOSE(torsionNone.getCoeff(0, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(torsionNone.getCoeff(1, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(torsionNone.getCoeff(1, 2), 0.0, tol);
  BOOST_CHECK_CLOSE(torsionNone.getCoeff(0, 2), 0.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()



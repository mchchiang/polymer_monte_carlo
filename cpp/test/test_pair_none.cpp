/*
 * test_pair_none.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "pair_none.hpp"

struct Fixture {
  PairNone pairNone {};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestPairNone, Fixture)

BOOST_AUTO_TEST_CASE(TestComputeDist) {
  BOOST_CHECK_CLOSE(pairNone.compute(0, 2, 1.4522), 0.0, tol);
  BOOST_CHECK_CLOSE(pairNone.compute(1, 1, -2.2342), 0.0, tol);
  BOOST_CHECK_CLOSE(pairNone.compute(2, 0, 3.8342), 0.0, tol);
  BOOST_CHECK_CLOSE(pairNone.compute(1, 0, 65.3421), 0.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff) {
  BOOST_CHECK_CLOSE(pairNone.getCoeff(0, 1, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(pairNone.getCoeff(1, 0, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(pairNone.getCoeff(1, 2, 2), 0.0, tol);
  BOOST_CHECK_CLOSE(pairNone.getCoeff(1, 1, 2), 0.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()



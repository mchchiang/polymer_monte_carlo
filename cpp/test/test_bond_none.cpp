/*
 * test_bond_none.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include "bond_none.hpp"

struct Fixture {
  BondNone bondNone {};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestBondNone, Fixture)

BOOST_AUTO_TEST_CASE(TestComputeDist) {
  BOOST_CHECK_CLOSE(bondNone.compute(0, 34.234), 0.0, tol);
  BOOST_CHECK_CLOSE(bondNone.compute(1, 21.22), 0.0, tol);
  BOOST_CHECK_CLOSE(bondNone.compute(2, 1.34223), 0.0, tol);
  BOOST_CHECK_CLOSE(bondNone.compute(3, 0.3421), 0.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff) {
  BOOST_CHECK_CLOSE(bondNone.getCoeff(0, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(bondNone.getCoeff(1, 0), 0.0, tol);
  BOOST_CHECK_CLOSE(bondNone.getCoeff(1, 2), 0.0, tol);
  BOOST_CHECK_CLOSE(bondNone.getCoeff(0, 2), 0.0, tol);
}

BOOST_AUTO_TEST_SUITE_END()


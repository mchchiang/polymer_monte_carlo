/*
 * test_bond_distrb_fixed.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "bond_distrb_fixed.hpp"

const double tol {1e-10};

BOOST_AUTO_TEST_SUITE(TestBondDistributionFixed)

BOOST_AUTO_TEST_CASE(TestGenerate1) {
  BondDistributionFixed distrb {3242, 1.0};
  double value {distrb.generate(0)};
  BOOST_CHECK_CLOSE(value, 1.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGenerate2) {
  BondDistributionFixed distrb {431, 3.0};
  double value {distrb.generate(0)};
  BOOST_CHECK_CLOSE(value, 3.0, tol);
}

BOOST_AUTO_TEST_CASE(TestGenerate3) {
  BondDistributionFixed distrb {99, 2.4};
  double value {distrb.generate(0)};
  BOOST_CHECK_CLOSE(value, 2.4, tol);
}

BOOST_AUTO_TEST_SUITE_END()

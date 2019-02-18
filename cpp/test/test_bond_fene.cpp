/*
 * test_bond_fene.cpp
 *
 *  Created on: 18 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include <limits>
#include <vector>
#include "bond_fene.hpp"

using std::vector;

struct Fixture {
  // Typical bond setup for MD or MC simulations
  BondFENE feneBond0 {1, 1.0, 1.0, 30.0, 1.6};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestBondFENE, Fixture)

BOOST_AUTO_TEST_CASE(TestComputeDist1) {
  double r {1.60001};
  double expected {std::numeric_limits<double>::infinity()};
  BOOST_CHECK_EQUAL(feneBond0.compute(0, r), expected);
}

BOOST_AUTO_TEST_CASE(TestComputeDist2) {
  double r {0.0};
  double expected {std::numeric_limits<double>::infinity()};
  BOOST_CHECK_EQUAL(feneBond0.compute(0, r), expected);
}

BOOST_AUTO_TEST_CASE(TestComputeDist3) {
  // Test a range of finite values
  vector<double> r {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55,
    0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2,
    1.25, 1.3, 1.35, 1.4, 1.45, 1.5, 1.55};
  vector<double> expected {
    3999996000001.15039062500,
    30829035352.39392089844,
    976500001.60473692417,
    67092481.94913383573,
    7521221.09848748520,
    1181531.85623665806,
    237445.49488077417,
    57533.38495731281,
    16132.94597378398,
    5081.77076255652,
    1758.66026604904,
    658.12287083977,
    264.14943643340,
    114.33000142045,
    54.99586343312,
    31.24875423158,
    22.24315142261,
    19.65333236877,
    20.02034318963,
    21.87261746532,
    24.58888992661,
    27.91349925238,
    31.74445721028,
    36.19239892645,
    41.44394211168,
    47.78866365157,
    55.71198267869,
    66.12424906591,
    81.06970521579,
    107.07214384158
  };
  for (size_t i {}; i < r.size(); i++) {
    BOOST_CHECK_CLOSE(feneBond0.compute(0,r[i]), expected[i], tol);
  }
}

BOOST_AUTO_TEST_CASE(TestSetCoeff1) {
  BondFENE bond {1, 0.6, 3.2, 30.0, 1.6};
  bond.setCoeff(0, 0, 4.6);
  bond.setCoeff(0, 1, 2.8);
  bond.setCoeff(0, 2, 42.0);
  bond.setCoeff(0, 3, 2.5);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 0), 4.6, tol);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 1), 2.8, tol);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 2), 42.0, tol);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 3), 2.5, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff1) {
  BondFENE bond {1, 0.6, 3.2, 9.34, 1.78};
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 0), 0.6, tol);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 1), 3.2, tol);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 2), 9.34, tol);
  BOOST_CHECK_CLOSE(bond.getCoeff(0, 3), 1.78, tol);
}

BOOST_AUTO_TEST_SUITE_END()



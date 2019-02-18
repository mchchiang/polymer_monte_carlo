/*
 * test_pair_lj_cut.cpp
 *
 *  Created on: 18 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include <limits>
#include <vector>
#include "pair_lj_cut.hpp"

using std::vector;

struct Fixture {
  // WCA potential (steric, purely repulsive)
  PairLJCut wca {1, 1.0, 1.0, 1.122462048309373};
  PairLJCut pairLJAttract {1, 2.0, 1.0, 1.8};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestPairLJCut, Fixture)


BOOST_AUTO_TEST_CASE(TestComputeDist1) {
  double r {0.0};
  double expected {std::numeric_limits<double>::infinity()};
  BOOST_CHECK_EQUAL(wca.compute(0, 0, r), expected);
}

BOOST_AUTO_TEST_CASE(TestComputeDist2) {
  double r {0.0};
  double expected {std::numeric_limits<double>::infinity()};
  BOOST_CHECK_EQUAL(pairLJAttract.compute(0, 0, r), expected);
}

BOOST_AUTO_TEST_CASE(TestComputeDist3) {
  vector<double> r {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6,
    0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2};
  vector<double> expected {
    3999996000001.0000000000000,
    30829035352.0549278259277,
    976500001.0000000000000,
    67092481.0000000000000,
    7521219.7241857433692,
    1181529.9733182094060,
    237443.0166015625000,
    57530.2205852309125,
    16129.0000000000000,
    5076.9419912727171,
    1752.8407499609561,
    651.1966499119241,
    255.9910242267788,
    104.8025444028593,
    43.9488718509674,
    18.5152640663382,
    7.6361189532529,
    2.9609746568876,
    1.0000000000000,
    0.2424880861637,
    0.01662755062631,
    0.0000000000000,
    0.0000000000000
  };
  for (size_t i {}; i < r.size(); i++) {
    BOOST_CHECK_CLOSE(wca.compute(0, 0, r[i]), expected[i], tol);
  }
}

BOOST_AUTO_TEST_CASE(TestComputeDist4) {
  vector<double> r {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6,
    0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2, 1.25,
    1.3, 1.35, 1.4, 1.45, 1.5, 1.55, 1.6};
  vector<double> expected {
    7999992000000.2285156250000,
    61658070702.3381500244141,
    1953000000.2282941341400,
    134184960.2282941192389,
    15042437.6766655966640,
    2363058.1749305301346,
    474884.2614972362062,
    115058.6694645729876,
    32256.2282941111735,
    10152.1122766566077,
    3503.9097940330857,
    1300.6215939350213,
    510.2103425647308,
    207.8333829168919,
    86.1260378131080,
    35.2588222438497,
    13.5005320176791,
    4.1502434249485,
    0.2282941111732,
    -1.2867297164993,
    -1.7384507875741,
    -1.7350694546259,
    -1.5536364639929,
    -1.3191020749388,
    -1.0857397177469,
    -0.8749517845934,
    -0.6930797332390,
    -0.5398522559450,
    -0.4123790773839,
    -0.3070033452382,
    -0.2201213375995
  };
  for (size_t i {}; i < r.size(); i++) {
    BOOST_CHECK_CLOSE(pairLJAttract.compute(0, 0, r[i]), expected[i], tol);
  }
}

BOOST_AUTO_TEST_CASE(TestGetCoeff1) {
  PairLJCut pair {1, 2.3, 0.5, 8.9};
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 0, 0), 2.3, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 0, 1), 0.5, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 0, 2), 8.9, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff2) {
  PairLJCut pair {3, 2.3, 0.5, 8.9};
  for (int i {}; i < 3; i++) {
    for (int j {}; j < 3; j++) {
      BOOST_CHECK_CLOSE(pair.getCoeff(i, j, 0), 2.3, tol);
      BOOST_CHECK_CLOSE(pair.getCoeff(i, j, 1), 0.5, tol);
      BOOST_CHECK_CLOSE(pair.getCoeff(i, j, 2), 8.9, tol);
    }
  }
}

BOOST_AUTO_TEST_CASE(TestSetCoeff1) {
  PairLJCut pair {1, 2.3, 0.5, 8.9};
  pair.setCoeff(0, 0, 0, 4.5);
  pair.setCoeff(0, 0, 1, 1.2);
  pair.setCoeff(0, 0, 2, 3.1);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 0, 0), 4.5, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 0, 1), 1.2, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 0, 2), 3.1, tol);
}

BOOST_AUTO_TEST_CASE(TestSetCoeff2) {
  PairLJCut pair {3, 2.3, 0.5, 8.9};
  pair.setCoeff(0, 2, 0, 4.5);
  pair.setCoeff(1, 0, 1, 1.2);
  pair.setCoeff(2, 1, 2, 3.1);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 2, 0), 4.5, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(2, 0, 0), 4.5, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(0, 1, 1), 1.2, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(1, 0, 1), 1.2, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(2, 1, 2), 3.1, tol);
  BOOST_CHECK_CLOSE(pair.getCoeff(1, 2, 2), 3.1, tol);
}

BOOST_AUTO_TEST_SUITE_END()


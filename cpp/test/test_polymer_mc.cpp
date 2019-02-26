/*
 * test_polymer_mc.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <vector>
#include <iostream>
#include <typeinfo>
#include <boost/test/unit_test.hpp>
#include "polymer_mc.hpp"
#include "bead.hpp"
#include "pair.hpp"
#include "pair_factory.hpp"

using std::vector;
using std::cout;
using std::endl;

struct Fixture {
  int chainSize0 {10};
  double lo0[3] {-10.0, -10.0, -10.0};
  double hi0[3] {10.0, 10.0, 10.0};
  int ntrials0 {10};
  bool bound0[3] {true, true, true};
  PolymerMC* polysim0 {new PolymerMC(chainSize0, lo0[0], hi0[0], lo0[1], hi0[1],
                                     lo0[2], hi0[2], bound0[0], bound0[1],
                                     bound0[2], ntrials0, 78146)};
  ~Fixture() {
    delete polysim0;
  }
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestPolymerMC, Fixture)

BOOST_AUTO_TEST_CASE(TestBuildNeighbourList) {
  const int nbeads {10};
  Vec v[nbeads] {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 0.0, 0.0},
    {1.0, -1.0, 0.0},
    {0.0, -1.0, 0.0},
    {-1.0, -1.0, 0.0},
    {-1.0, 0.0, 0.0},
    {-1.0, 1.0, 0.0},
    {-1.0, 1.0, -1.0}
  };
  vector<Bead> chain (nbeads, Bead());
  for (int i {}; i < nbeads; i++) {
    chain[i].pos = v[i];
  }
  vector<Bead*> list {};
  vector<Bead*> expected;
  polysim0->buildNeighbourList(chain, 1, 1.1, &list);
  expected = {&chain[0]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 2, 1.1, &list);
  expected = {&chain[1]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 3, 1.1, &list);
  expected = {&chain[0], &chain[2]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 4, 1.5, &list);
  expected = {&chain[0], &chain[2], &chain[3]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 4, 1.8, &list);
  expected = {&chain[0], &chain[1], &chain[2], &chain[3]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 5, 1.5, &list);
  expected = {&chain[0], &chain[1], &chain[3], &chain[4]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 5, 1.8, &list);
  expected = {&chain[0], &chain[1], &chain[2], &chain[3], &chain[4]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 6, 1.5, &list);
  expected = {&chain[0], &chain[5]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 6, 1.8, &list);
  expected = {&chain[0], &chain[1], &chain[5]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 6, 2.1, &list);
  expected = {&chain[0], &chain[1], &chain[4], &chain[5]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 7, 1.5, &list);
  expected = {&chain[0], &chain[1], &chain[5], &chain[6]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 7, 2.1, &list);
  expected = {&chain[0], &chain[1], &chain[3], &chain[5], &chain[6]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 7, 2.3, &list);
  expected = {&chain[0], &chain[1], &chain[2], &chain[3],
      &chain[4], &chain[5], &chain[6]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 8, 1.5, &list);
  expected = {&chain[0], &chain[7]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 8, 1.8, &list);
  expected = {&chain[0], &chain[1], &chain[7]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 8, 2.1, &list);
  expected = {&chain[0], &chain[1], &chain[6], &chain[7]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 8, 2.3, &list);
  expected = {&chain[0], &chain[1], &chain[3], &chain[5], &chain[6], &chain[7]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 9, 1.5, &list);
  expected = {&chain[7], &chain[8]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 9, 2.1, &list);
  expected = {&chain[0], &chain[7], &chain[8]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
  polysim0->buildNeighbourList(chain, 9, 2.3, &list);
  expected = {&chain[0], &chain[6], &chain[7], &chain[8]};
  BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(),
                                expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(TestComputeNonBondEnergy1) {
  const int nbeads {10};
  Vec v[nbeads] {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 0.0, 0.0},
    {1.0, -1.0, 0.0},
    {0.0, -1.0, 0.0},
    {-1.0, -1.0, 0.0},
    {-1.0, 0.0, 0.0},
    {-1.0, 1.0, 0.0},
    {-1.0, 1.0, -1.0}
  };
  vector<Bead> chain (nbeads, Bead());
  for (int i {}; i < nbeads; i++) {
    chain[i].pos = v[i];
  }
  vector<Bead*> list {};
  PairFactory pairFactory {};
  Pair* pair = pairFactory.createPair(
      "ljcut", 1, {1.0, 1.0, 1.122462048309373});
  double energy, expected;
  polysim0->buildNeighbourList(chain, 1, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[2].pos, list, *pair);
  expected = 0.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 2, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[3].pos, list, *pair);
  expected = 1.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 3, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[4].pos, list, *pair);
  expected = 0.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 4, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[5].pos, list, *pair);
  expected = 1.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 5, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[6].pos, list, *pair);
  expected = 0.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 6, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[7].pos, list, *pair);
  expected = 1.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 7, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[8].pos, list, *pair);
  expected = 0.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 8, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[9].pos, list, *pair);
  expected = 0.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  delete pair;
}

BOOST_AUTO_TEST_CASE(TestComputeNonBondEnergy2) {
  const int nbeads {10};
  Vec v[nbeads] {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.5},
    {0.5, 0.0, 0.5},
    {0.5, 0.0, 0.0},
    {0.5, -0.5, 0.0},
    {0.0, -0.5, 0.0},
    {-0.5, -0.5, 0.0},
    {-0.5, 0.0, 0.0},
    {-0.5, 0.5, 0.0},
    {-0.5, 0.5, -0.5}
  };
  vector<Bead> chain (nbeads, Bead());
  for (int i {}; i < nbeads; i++) {
    chain[i].pos = v[i];
  }
  vector<Bead*> list {};
  PairFactory pairFactory {};
  Pair* pair = pairFactory.createPair(
      "ljcut", 1, {1.0, 1.0, 1.122462048309373});
  double energy, expected;
  polysim0->buildNeighbourList(chain, 1, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[2].pos, list, *pair);
  expected = 225.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 2, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[3].pos, list, *pair);
  expected = 16354.0;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 3, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[4].pos, list, *pair);
  expected = 463.993141289437;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 4, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[5].pos, list, *pair);
  expected = 16592.993141289437;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 5, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[6].pos, list, *pair);
  expected = 239.99371728943734;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 6, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[7].pos, list, *pair);
  expected = 16580.001152;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 7, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[8].pos, list, *pair);
  expected = 239.99429328943734;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  polysim0->buildNeighbourList(chain, 8, 2.5, &list);
  energy = polysim0->computeNonBondEnergy(chain, 0, chain[9].pos, list, *pair);
  expected = 238.99371728943734;
  BOOST_CHECK_CLOSE(energy, expected, tol);
  delete pair;
}

BOOST_AUTO_TEST_SUITE_END()





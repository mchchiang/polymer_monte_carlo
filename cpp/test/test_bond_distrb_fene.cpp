/*
 * test_bond_distrb_fene.cpp
 *
 *  Created on: 25 Feb 2019
 *      Author: michaelchiang
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "bond_fene.hpp"
#include "bond_distrb_fene.hpp"

using std::ofstream;
using std::endl;

BOOST_AUTO_TEST_SUITE(TestBondDistributionFENE)

BOOST_AUTO_TEST_CASE(TestGenerate) {
  ofstream writer;
  writer.open("TestBondDistributionFENE.dat");
  BondFENE fene {1, 1.0, 1.0, 30.0, 1.6};
  BondDistributionFENE distrbFene {1, 1.0, 6732, &fene};
  Vec v {};
  double value {};
  int npoints {100000};
  for (int i {}; i < npoints; i++) {
    value = distrbFene.generate(0);
    writer << value << endl;
  }
  writer.close();
}

BOOST_AUTO_TEST_SUITE_END()



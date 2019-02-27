/*
 * test_angle_distrb_uniform.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: michaelchiang
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "angle_distrb_uniform.hpp"

using std::ofstream;
using std::endl;

BOOST_AUTO_TEST_SUITE(TestAngleDistributionUniform)

BOOST_AUTO_TEST_CASE(TestGenerate) {
  ofstream writer;
  writer.open("TestAngleDistributionUniform.dat");
  AngleDistributionUniform distrb {82342};
  Vec v {};
  double value {};
  int npoints {100000};
  for (int i {}; i < npoints; i++) {
    value = distrb.generate(0);
    writer << value << endl;
  }
  writer.close();
}

BOOST_AUTO_TEST_SUITE_END()



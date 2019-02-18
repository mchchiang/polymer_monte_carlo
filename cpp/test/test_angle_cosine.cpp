/*
 * test_angle_cosine.cpp
 *
 *  Created on: 18 Feb 2019
 *      Author: michaelchiang
 */

#include <boost/test/unit_test.hpp>
#include <vector>
#include "angle_cosine.hpp"

using std::vector;

struct Fixture {
  // Typical angle cosine setup for MD or MC simulations
  AngleCosine angleCosine0 {1, 3.0};
};

const double tol {1e-10};

BOOST_FIXTURE_TEST_SUITE(TestAngleCosine, Fixture)

BOOST_AUTO_TEST_CASE(TestComputeTheta1) {
  vector<double> theta {
    0.0000000000000,
    0.3141592653590,
    0.6283185307180,
    0.9424777960769,
    1.2566370614359,
    1.5707963267949,
    1.8849555921539,
    2.1991148575129,
    2.5132741228718,
    2.8274333882308,
    3.1415926535898,
    3.4557519189488,
    3.7699111843078,
    4.0840704496667,
    4.3982297150257,
    4.7123889803847,
    5.0265482457437,
    5.3407075111026,
    5.6548667764616,
    5.9690260418206,
    6.2831853071796};

  vector<double> expected {
    0.0000000000000,
    0.1468304511145,
    0.5729490168752,
    1.2366442431226,
    2.0729490168752,
    3.0000000000000,
    3.9270509831248,
    4.7633557568774,
    5.4270509831248,
    5.8531695488855,
    6.0000000000000,
    5.8531695488855,
    5.4270509831248,
    4.7633557568774,
    3.9270509831248,
    3.0000000000000,
    2.0729490168752,
    1.2366442431226,
    0.5729490168752,
    0.1468304511145,
    0.0000000000000
  };

  for (size_t i {}; i < theta.size(); i++) {
    BOOST_CHECK_CLOSE(angleCosine0.compute(0, theta[i]), expected[i], tol);
  }
}

BOOST_AUTO_TEST_CASE(TestGetCoeff1) {
  AngleCosine cosine {1, 4.5};
  BOOST_CHECK_CLOSE(cosine.getCoeff(0, 0), 4.5, tol);
}

BOOST_AUTO_TEST_CASE(TestGetCoeff2) {
  AngleCosine cosine {3, 4.5};
  BOOST_CHECK_CLOSE(cosine.getCoeff(0, 0), 4.5, tol);
  BOOST_CHECK_CLOSE(cosine.getCoeff(1, 0), 4.5, tol);
  BOOST_CHECK_CLOSE(cosine.getCoeff(2, 0), 4.5, tol);
}

BOOST_AUTO_TEST_CASE(TestSetCoeff1) {
  AngleCosine cosine {1, 3.6};
  cosine.setCoeff(0, 0, 5.8);
  BOOST_CHECK_CLOSE(cosine.getCoeff(0, 0), 5.8, tol);
}

BOOST_AUTO_TEST_CASE(TestSetCoeff2) {
  AngleCosine cosine {3, 3.6};
  cosine.setCoeff(0, 0, 5.8);
  cosine.setCoeff(1, 0, 2.4);
  cosine.setCoeff(2, 0, 10.2);
  BOOST_CHECK_CLOSE(cosine.getCoeff(0, 0), 5.8, tol);
  BOOST_CHECK_CLOSE(cosine.getCoeff(1, 0), 2.4, tol);
  BOOST_CHECK_CLOSE(cosine.getCoeff(2, 0), 10.2, tol);
}

BOOST_AUTO_TEST_SUITE_END()



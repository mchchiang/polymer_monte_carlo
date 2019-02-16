/*
 * angle_factory.cpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#include <utility>
#include <string>
#include <vector>
#include "angle_factory.hpp"
#include "angle.hpp"
#include "angle_cosine.hpp"
#include "angle_none.hpp"
#include "angle_distrb.hpp"
#include "angle_distrb_cosine.hpp"
#include "angle_distrb_uniform.hpp"

using std::pair;
using std::string;
using std::vector;
using std::make_pair;
using AnglePair = std::pair<Angle*, AngleDistribution*>;

AnglePair AngleFactory::createAngleCosine(int ntypes, double k,
                                          double temp, int seed) {
  AngleCosine* angle {new AngleCosine(ntypes, k)};
  AngleDistributionCosine* angleDistrb {
    new AngleDistributionCosine(temp, seed, angle)};
  return make_pair(angle, angleDistrb);
}

AnglePair AngleFactory::createAngleNone(int seed) {
  AngleNone* angle {new AngleNone()};
  AngleDistributionUniform* angleDistrb {new AngleDistributionUniform(seed)};
  return make_pair(angle, angleDistrb);
}

AnglePair AngleFactory::createAngle(string angleName, int ntypes,
                                    const vector<double>& args,
                                    double temp, int seed) {
  if (angleName.compare("cosine") == 0) {
    return createAngleCosine(ntypes, args[0], temp, seed);
  } else {
    return createAngleNone(seed);
  }
}

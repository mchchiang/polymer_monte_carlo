/*
 * angle_factory.hpp
 *
 *  Created on: 16 Feb 2019
 *      Author: michaelchiang
 */

#ifndef ANGLE_FACTORY_HPP_
#define ANGLE_FACTORY_HPP_

#include <utility>
#include <string>
#include <vector>
#include "angle.hpp"
#include "distrb.hpp"


class AngleFactory {

private:
  std::pair<Angle*,Distribution*>
  createAngleCosine(int ntypes, double k, double temp, int seed);
  std::pair<Angle*,Distribution*> createAngleNone(int seed);

public:
  std::pair<Angle*,Distribution*> createAngle(
      std::string angleName, int ntypes, const std::vector<double>& args,
        double temp, int seed);
};

#endif /* ANGLE_FACTORY_HPP_ */

/*
 * wall_factory.cpp
 *
 *  Created on: 17 Feb 2019
 *      Author: michaelchiang
 */

#include <string>
#include <vector>
#include "wall_factory.hpp"
#include "wall.hpp"
#include "wall_lj_cut.hpp"
#include "wall_none.hpp"

using std::string;
using std::vector;

Wall* WallFactory::createWallLJCut(int mask, int dir, double pos,
                                   bool fromBelow, double epsilon,
                                   double sigma, double cutoff) {
  return new WallLJCut(mask, dir, pos, fromBelow, epsilon, sigma, cutoff);
}

Wall* WallFactory::createWallNone() {
  return new WallNone();
}

Wall* WallFactory::createWall(const string& wallName, int mask, int dir,
                              double pos, bool fromBelow,
                              const vector<double>& args) {
  if (wallName.compare("ljcut") == 0) {
    return createWallLJCut(mask, dir, pos,fromBelow, args[0], args[1], args[2]);
  } else {
    return createWallNone();
  }
}




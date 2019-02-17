/*
 * wall_factory.hpp
 *
 *  Created on: 17 Feb 2019
 *      Author: michaelchiang
 */

#ifndef WALL_FACTORY_HPP_
#define WALL_FACTORY_HPP_

#include <string>
#include <vector>
#include "wall.hpp"

class WallFactory {

private:
  Wall* createWallLJCut(int mask, int dir, double pos, bool fromBelow,
                        double epsilon, double sigma, double cutoff);
  Wall* createWallNone();

public:
  Wall* createWall(const std::string& wallName, int mask, int dir, double pos,
                   bool fromBelow, const std::vector<double>& args);

};

#endif /* WALL_FACTORY_HPP_ */

/*
 * wall_lj_cut.hpp
 *
 *  Created on: 17 Feb 2019
 *      Author: michaelchiang
 */

#ifndef WALL_LJ_CUT_HPP_
#define WALL_LJ_CUT_HPP_

#include <vector>
#include "wall.hpp"

class WallLJCut : public Wall {

private:
  unsigned int groupMask;
  int dir;
  bool fromBelow;
  double pos;
  double epsilon;
  double sigma;
  double cutoff;

public:
  WallLJCut(unsigned int groupMask, int dir, double pos, bool fromBelow,
            double epsilon, double sigma, double cutoff);
  ~WallLJCut();
  double compute(unsigned int beadMask, const Vec& pos);
  void setCoeff(const std::vector<double>& args);
  void setCoeff(int iarg, double value);
  double getCoeff(int iarg);
  unsigned int getMask();

};

#endif /* WALL_LJ_CUT_HPP_ */

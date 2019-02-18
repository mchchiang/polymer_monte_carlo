/*
 * wall_lj_cut.cpp
 *
 *  Created on: 17 Feb 2019
 *      Author: michaelchiang
 */

#include <vector>
#include <limits>
#include "wall_lj_cut.hpp"
#include "util_vector.hpp"

using std::vector;

WallLJCut::WallLJCut(unsigned int mask, int _dir, double _pos, bool below,
                     double _epsilon, double _sigma, double _cutoff) :
                         groupMask {mask}, dir {_dir}, fromBelow {below},
                         pos {_pos}, epsilon {_epsilon}, sigma {_sigma},
                         cutoff {_cutoff} {}

WallLJCut::~WallLJCut() {}

double WallLJCut::compute(unsigned int beadMask, const Vec& v) {
  if ((beadMask & groupMask) == groupMask) {// Only apply to beads in the group
    double r;
    if (fromBelow) {
      r = pos - v[dir];
    } else {
      r = v[dir] - pos;
    }
    if (r < 0.0) {
      return std::numeric_limits<double>::infinity();
    } else if (r < cutoff) {
      double sr {sigma/r};
      double sr2 {sr*sr};
      double sr6 {sr2*sr2*sr2};
      double src {sigma/cutoff};
      double src2 {src*src};
      double src6 {src2*src2*src2};
      return 4.0*epsilon*(sr6*(sr6-1.0)-src6*(src6-1.0));
    } else {
      return 0.0;
    }
  } else {
    return 0.0;
  }
}

void WallLJCut::setCoeff(const vector<double>& args) {
  if (args.size() == 3) {
    epsilon = args[0];
    sigma = args[1];
    cutoff = args[2];
  }
}

void WallLJCut::setCoeff(int iarg, double value) {
  switch(iarg) {
    case 0: epsilon = value; break;
    case 1: sigma = value; break;
    case 2: cutoff = value; break;
  }
}

double WallLJCut::getCoeff(int iarg) {
  switch(iarg) {
    case 0: return epsilon;
    case 1: return sigma;
    case 2: return cutoff;
    default: return 0.0;
  }
}

unsigned int WallLJCut::getMask() {
  return groupMask;
}


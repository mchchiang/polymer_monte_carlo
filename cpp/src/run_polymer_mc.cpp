/*
 * run_polymer_mc.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include <iostream>
#include "polymer_mc.hpp"

using std::cout;
using std::endl;

int main (int argc, char* argv[]) {
  int L {100};
  int n {500};
  int seed {7689};
  int ntrials {25};
  PolymerMC* sim {new PolymerMC(L, n, seed, ntrials)};
  sim->createGroupWith("sticky", {0});
  sim->setNeighbourListCutoff(5.0);
  sim->setBond("fene", {1.0, 1.0, 30.0, 1.6}, 3242);
  //sim->setAngle("cosine", {3.0}, 23);
  sim->setPair("ljcut", {1.0, 1.0, 1.122462048309373});
  sim->createWall("wallZHI", "all", "ljcut", 2, L*0.5, true,
                  {5.0, 1.0, 1.8});
  sim->createWall("wallZLO", "all", "ljcut", 2, -L*0.5, false,
                 {1.0, 1.0, 1.122462048309373});
  sim->run(0,3000,10);
  delete sim;
}


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
  int n {100};
  int seed {18473};
  int ntrials {50};
  PolymerMC* sim {new PolymerMC(L, n, seed, ntrials)};
  sim->createGroupWith("sticky", {0});
  sim->setNeighbourListCutoff(5.0);
  sim->setBond("fene", {1.0, 1.0, 30.0, 1.6}, 3242);
  //sim->setAngle("cosine", {0.0}, 23);
  sim->setPair("ljcut", {1.0, 1.0, 1.122462048309373});
  sim->createWall("wallZHI", "all", "ljcut", 2, 0.0, true,
                  {10.0, 1.0, 1.8});
  sim->createWall("wallZLO", "all", "ljcut", 2, -L, false,
                    {1.0, 1.0, 1.122462048309373});
  //sim->setPair("ljcut", {5.0, 1.0, 1.8});
  sim->run(10,1000,10);
  delete sim;
}


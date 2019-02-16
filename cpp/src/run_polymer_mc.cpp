/*
 * run_polymer_mc.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include <iostream>
#include "polymer_mc.hpp"
#include "bond_fene.hpp"
#include "angle_cosine.hpp"
#include "pair_lj_cut.hpp"
#include "bond_distrb_fene.hpp"
#include "angle_distrb_cosine.hpp"

using std::cout;
using std::endl;

int main (int argc, char* argv[]) {
  int L {100};
  int n {1000};
  int seed {18473};
  int ntrials {100};
  PolymerMC* sim = new PolymerMC(L, n, seed, ntrials);
  sim->setNeighbourListCutoff(5.0);
  BondFENE fene {BondFENE(1, 1.0, 1.0, 30.0, 1.6)};
  BondDistributionFENE distrbFENE {BondDistributionFENE(1, 1.0, 3242, &fene)};
  //AngleCosine cosine = AngleCosine(1, 1.0);
  //PairLJCut ljcut {PairLJCut(1, 1.0, 1.0, 1.122462048309373)};
  PairLJCut ljcut = PairLJCut(1, 2.0, 1.0, 1.8);
  /*AngleDistributionCosine distrbCosine =
      AngleDistributionCosine(23, &cosine, 1.0);*/
  sim->setBond(&fene);
  //sim->setAngle(&cosine);
  sim->setPair(&ljcut);
  sim->setBondDistribution(&distrbFENE);
  //sim->setAngleDistribution(&distrbCosine);

  sim->run(10, 10, 10);
}


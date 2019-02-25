/*
 * dump_gyration.cpp
 *
 *  Created on: 24 Feb 2019
 *      Author: michaelchiang
 */

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include "dump_gyration.hpp"
#include "polymer_mc.hpp"
#include "util_vector.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;

DumpGyration::DumpGyration(string name, int freq, unsigned int _mask) :
    Dump(name, freq), mask {_mask} {}

DumpGyration::~DumpGyration() {
  writer.close();
}

void DumpGyration::dump(const int& timestep, const PolymerMC& sim) {
  if (timestep % dumpfreq == 0) {
    int nbeads {sim.getNumOfBeads()};
    double boxSize[3] {sim.getBoxSize(0), sim.getBoxSize(1), sim.getBoxSize(2)};
    int count {};
    // Find centre of mass
    Vec cm {0.0, 0.0, 0.0};
    vector<Vec> pos (nbeads, {0.0, 0.0, 0.0});
    Bead b;
    for (int i {}; i < nbeads; i++) {
      b = sim.getBead(i);
      if ((b.mask & this->mask) == this->mask) {
        // Use unwrapped position
        pos[count][0] = b.pos[0] + boxSize[0] * b.image[0];
        pos[count][1] = b.pos[1] + boxSize[1] * b.image[1];
        pos[count][2] = b.pos[2] + boxSize[2] * b.image[2];
        cm += pos[count];
        count++;
      }
    }
    // Normalise
    cm /= static_cast<double>(count);

    // Find gyration tensor components
    // 0 = rg, 1 = rgxx, 2 = rgyy, 3 = rgzz, 4 = rgxy, 5 = rgxz, 6 = rgyz
    double rg[7];
    Vec diff;
    for (int i {}; i < count; i++) {
      diff = pos[i] - cm;
      rg[0] += Vec::mag2(diff);
      rg[1] += diff[0] * diff[0];
      rg[2] += diff[1] * diff[1];
      rg[3] += diff[2] * diff[2];
      rg[4] += diff[0] * diff[1];
      rg[5] += diff[0] * diff[2];
      rg[6] += diff[1] * diff[2];
    }
    // Normalise
    for (int i {}; i < 7; i++) {
      rg[i] /= static_cast<double>(count);
    }
    rg[0] = sqrt(rg[0]);

    // Output
    writer << timestep << " ";
    for (int i {}; i < 7; i++) {
      writer << rg[i] << " ";
    }
    writer << endl;
  }
}




/*
 * dump_position.cpp
 *
 *  Created on: 24 Feb 2019
 *      Author: michaelchiang
 */

#include <string>
#include <sstream>
#include "dump_position.hpp"
#include "polymer_mc.hpp"

using std::string;
using std::ostringstream;
using std::endl;

DumpPosition::DumpPosition(string name, int freq, unsigned int _mask) :
    Dump(name, freq), mask {_mask} {
  typeToSim = {"O","N","C","H","S","F","B"};
}

DumpPosition::~DumpPosition() {
  writer.close();
}

void DumpPosition::dump(const int& timestep, const PolymerMC& sim) {
  if (timestep % dumpfreq == 0) {
    int nbeads {sim.getNumOfBeads()};
    ostringstream ss;
    int count {};
    Bead b;
    for (int i {}; i < nbeads; i++) {
      b = sim.getBead(i);
      if ((b.mask & this->mask) == this->mask) {
        ss << typeToSim[b.type] << " "
           << b.pos[0] << " " << b.pos[1] << " " << b.pos[2] << " "
           << b.image[0] << " " << b.image[1] << " " << b.image[2] << endl;
        count++;
       }
    }
    writer << count << endl;
    writer << "Atoms. Timestep: " << timestep << endl;
    writer << ss.str();
  }
}

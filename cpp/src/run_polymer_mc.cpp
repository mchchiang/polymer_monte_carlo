/*
 * run_polymer_mc.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "polymer_mc.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
using std::getline;
using std::istringstream;

bool readInt(const vector<string>& args, int* value, bool* read);
bool readDouble(const vector<string>& args, double* value, bool* read);
bool readBox(const vector<string>& args, double* lo, double* hi,
             bool* bound, bool* read);
bool readBondPotential(const vector<string>& args, string* name,
                        int* seed, vector<double>* numargs);
bool readNonBondPotential(const vector<string>& args, string* name,
                           vector<double>* numargs);
bool readWallPotential(const vector<string>& args, string* id, string* group,
                       string* name, int* dir, double* pos, bool* fromBelow,
                       vector<double>* numargs);
bool readDump(const vector<string>& args, string* id, string* group,
              string* name, string* filename, int* freq);


int main (int argc, char* argv[]) {

  if (argc != 2) {
    cout << "Usage: run_polymer_mc [input file]" << endl;
    return 1;
  }

  int iarg {};
  string inputFile {argv[++iarg]};

  cout << "Configurational Bias Monte Carlo" << endl;
  cout << "Version 1.0" << endl;

  cout << "Reading input file ..." << endl;
  ifstream input (inputFile);
  if (!input) {
    cout << "Problem with reading input file!" << endl;
    return 1;
  }

  // Read contents from the input file
  int nbeads {}, ntrials {}, seed {};
  double boxLo[3], boxHi[3];
  bool bound[3];
  bool hasReadBead {false};
  bool hasReadTrial {false};
  bool hasReadSeed {false};
  bool hasReadBox[3] {false, false, false};
  bool readOK {false};

  string line, s, keyword;
  istringstream iss;

  while (!input.eof() && !(hasReadBead && hasReadTrial &&
      hasReadBox[0] && hasReadBox[1] && hasReadBox[2])) {
    getline(input, line);
    // Ignore comments
    if (line.size() == 0 || line[0] == '#') continue;
    iss.clear();
    iss.str(line);

    vector<string> tokens {};
    while (getline(iss, s, ' ')) {
      tokens.push_back(s);
    }

    // Ignore empty lines
    if (tokens.size() == 0) continue;

    // Determine the keyword
    keyword = tokens[0];
    if (keyword.compare("seed") == 0) {
      cout << "Reading generator seed ..." << endl;
      readOK = readInt(tokens, &seed, &hasReadSeed);
      if (!readOK) {
        cout << "Error: Incorrect parameters for random generator seed" << endl;
        cout << "Expect: seed [seed]" << endl;
        return 1;
      }
    } else if (keyword.compare("bead") == 0) {
      cout << "Reading number of beads ..." << endl;
      readOK = readInt(tokens, &nbeads, &hasReadBead);
      if (!readOK) {
        cout << "Error: Incorrect parameters for number of beads" << endl;
        cout << "Expect: bead [nbeads]" << endl;
        return 1;
      }
    } else if (keyword.compare("box") == 0) {
      cout << "Reading box size ..." << endl;
      readOK = readBox(tokens, boxLo, boxHi, bound, hasReadBox);
      if (!readOK) {
        cout << "Error: Incorrect parameters for box size" << endl;
        cout << "Expect: box [dir] [lo] [hi] [p/f]" << endl;
        return 1;
      }
    } else if (keyword.compare("trial") == 0) {
      cout << "Reading number of trials ..." << endl;
      readOK = readInt(tokens, &ntrials, &hasReadTrial);
      if (!readOK) {
        cout << "Error: Incorrect parameters for number of trials" << endl;
        cout << "Expect: trial [ntrials]" << endl;
        return 1;
      }
    }
  }

  if (!hasReadBead || !hasReadTrial ||
      !hasReadBox[0] || !hasReadBox[1] || !hasReadBox[2]) {
    cout << "Error: Number of beads, number of trials and box size " << endl;
    cout << "must be specified for running the simulation" << endl;
    return 1;
  }

  if (!hasReadSeed) {
    cout << "Warning: No seed specified for the random generator" << endl;
    cout << "A random seed is generated using system's clock time" << endl;
    srand(time(NULL));
    seed = rand();
    cout << "seed = " << seed << endl;
  }

  // Initialise the simulation box
  PolymerMC* sim {new PolymerMC(nbeads, boxLo[0], boxHi[0], boxLo[1],
                                boxHi[1], boxLo[2], boxHi[2], bound[0],
                                bound[1], bound[2], ntrials, seed)};

  bool hasReadBond {false};
  bool hasReadAngle {false};
  bool hasReadPair {false};
  bool hasReadTimesteps {false};
  bool hasReadEquil {false};

  int potSeed, timesteps, nequil {};
  string potName;
  vector<double> potArgs {};
  while (!input.eof()) {
    getline(input, line);

    // Ignore comments
    if (line.size() == 0 || line[0] == '#') continue;
    iss.clear();
    iss.str(line);

    vector<string> tokens {};
    while (getline(iss, s, ' ')) {
      tokens.push_back(s);
    }

    // Ignore empty lines
    if (tokens.size() == 0) continue;

    // Determine the keyword
    keyword = tokens[0];
    if (keyword.compare("bond") == 0) {
      readOK = readBondPotential(tokens, &potName, &potSeed, &potArgs);
      if (!readOK) {
        cout << "Error: Incorrect parameters for bond potential" << endl;
        cout << "Expect: bond [bond_type] [seed] [bond_params ...]" << endl;
        return 1;
      }
      sim->setBond(potName, potArgs, potSeed);
      cout << "Using " << potName << " for bond interactions" << endl;
      hasReadBond = true;
    } else if (keyword.compare("angle") == 0) {
      readOK = readBondPotential(tokens, &potName, &potSeed, &potArgs);
      if (!readOK) {
        cout << "Error: Incorrect parameters for angle potential" << endl;
        cout << "Expect: angle [angle_type] [seed] [angle_params ...]" << endl;
        return 1;
      }
      sim->setAngle(potName, potArgs, potSeed);
      cout << "Using " << potName << " for angle interactions" << endl;
      hasReadAngle = true;
    } else if (keyword.compare("pair") == 0) {
      readOK = readNonBondPotential(tokens, &potName, &potArgs);
      if (!readOK) {
        cout << "Error: Incorrect parameters for pair potential" << endl;
        cout << "Expect: pair [pair_type] [pair_params ...]" << endl;
        return 1;
      }
      sim->setPair(potName, potArgs);
      cout << "Using " << potName << " for pair interactions" << endl;
      hasReadPair = true;
    } else if (keyword.compare("wall") == 0) {
      string id {}, group {};
      int dir {};
      double pos {};
      bool below {};
      readOK = readWallPotential(tokens, &id, &group, &potName, &dir, &pos,
                                 &below, &potArgs);
      if (!readOK) {
        cout << "Error: Incorrect parameters for wall potential" << endl;
        cout << "Expect: wall [wall_id] [group] [wall_type] [dir=(x/y/z)] "
             << "[pos] [below/above] [wall_params ...]" << endl;
        return 1;
      }
      sim->createWall(id, group, potName, dir, pos, below, potArgs);
    } else if (keyword.compare("run") == 0) {
      readOK = readInt(tokens, &timesteps, &hasReadTimesteps);
      if (!readOK) {
        cout << "Error: Incorrect parameters for run timesteps" << endl;
        cout << "Expect: run [time steps] " << endl;
        return 1;
      }
    } else if (keyword.compare("equil") == 0) {
      readOK = readInt(tokens, &nequil, &hasReadEquil);
      if (!readOK) {
        cout << "Error: Incorrect parameters for equilibration timesteps"
            << endl;
        cout << "Expect: equil [time steps] " << endl;
        return 1;
      }
    }else if (keyword.compare("neighbour_cutoff") == 0) {
      double cutoff {};
      bool read {};
      readOK = readDouble(tokens, &cutoff, &read);
      if (!readOK) {
        cout << "Error: Incorrect parameters for neigbour_cutoff" << endl;
        cout << "Expect: neighbour_cutoff [cutoff]" << endl;
        return 1;
      }
      sim->setNeighbourListCutoff(cutoff);
    } else if (keyword.compare("dump") == 0) {
      string filename {}, group {}, id {}, dumpType {};
      int freq {};
      readOK = readDump(tokens, &id, &group, &dumpType, &filename, &freq);
      if (!readOK) {
        cout << "Error: Incorrect parameters for dump" << endl;
        cout << "Expect: dump [id] [group] [dump type] [freq] [filename]"
             << endl;
        return 1;
      }
      sim->dump(id, group, dumpType, filename, freq);
    }
  }

  if (!hasReadBond) {
    cout << "Warning: No bond interaction specified" << endl;
    cout << "Default is bond_fixed with l = 1" << endl;
  }
  if (!hasReadAngle) {
    cout << "Warning: No angle interaction specified" << endl;
    cout << "Default is angle_none" << endl;
  }
  if (!hasReadPair) {
    cout << "Warning: No pair interaction specified" << endl;
    cout << "Default is pair_none" << endl;
  }

  if (!hasReadEquil) {
    cout << "Warning: No equilibration timesteps specified" << endl;
    cout << "Default is equil = 0" << endl;
  }

  if (hasReadTimesteps) {
    cout << "Starting simulation ..." << endl;
    sim->run(nequil,timesteps);
  }
  delete sim;
}

bool readBox(const vector<string>& args, double* lo, double* hi,
             bool* bound, bool* read) {
  if (args.size() != 5) return false;
  string dir {args[1]};
  int idir {};
  if (dir.compare("x") == 0) {
    idir = 0;
  } else if (dir.compare("y") == 0) {
    idir = 1;
  } else if (dir.compare("z") == 0) {
    idir = 2;
  } else {
    return false;
  }

  double l1, l2;
  l1 = stod(args[2], nullptr);
  l2 = stod(args[3], nullptr);
  if (l1 > l2) return false;
  lo[idir] = l1;
  hi[idir] = l2;

  if (args[4].compare("p") == 0) {
    bound[idir] = true;
  } else if (args[4].compare("f") == 0) {
    bound[idir] = false;
  } else {
    return false;
  }
  read[idir] = true;
  return true;
}

bool readInt(const vector<string>& args, int* nbeads, bool* read) {
  if (args.size() != 2) return false;
  *nbeads = stoi(args[1], nullptr, 10);
  *read = true;
  return true;
}

bool readDouble(const vector<string>& args, double* nbeads, bool* read) {
  if (args.size() != 2) return false;
  *nbeads = stod(args[1], nullptr);
  *read = true;
  return true;
}


bool readBondPotential(const vector<string>& args, string* name,
                        int* seed, vector<double>* numargs) {
  if (args.size() <= 2) return false;
  *name = args[1];
  *seed = stoi(args[2], nullptr, 10);
  *numargs = vector<double>(args.size()-3);
  for (size_t i {}; i < numargs->size(); i++) {
    (*numargs)[i] = stod(args[i+3], nullptr);
  }
  return true;
}

bool readNonBondPotential(const vector<string>& args, string* name,
                           vector<double>* numargs) {
  if (args.size() <= 1) return false;
  *name = args[1];
  *numargs = vector<double>(args.size()-2);
  for (size_t i {}; i < numargs->size(); i++) {
    (*numargs)[i] = stod(args[i+2], nullptr);
  }
  return true;
}

bool readWallPotential(const vector<string>& args, string *id, string *group,
                       string *name, int* dir, double* pos, bool* below,
                       vector<double>* numargs) {
  if (args.size() <= 7) return false;
  *id = args[1];
  *group = args[2];
  *name = args[3];
  if (args[4].compare("x") == 0) {
    *dir = 0;
  } else if (args[4].compare("y") == 0) {
    *dir = 1;
  } else if (args[4].compare("z") == 0) {
    *dir = 2;
  } else {
    return false;
  }
  *pos = stod(args[5], nullptr);
  if (args[6].compare("below") == 0) {
    *below = true;
  } else if (args[6].compare("above") == 0) {
    *below = false;
  } else {
    return false;
  }
  *numargs = vector<double>(args.size()-7);
  for (size_t i {}; i < numargs->size(); i++) {
    (*numargs)[i] = stod(args[i+7], nullptr);
  }
  return true;
}

bool readDump(const vector<string>& args, string* id, string* group,
              string* name, string* filename, int* freq) {
  if (args.size() < 6) return false;
  *id = args[1];
  *group = args[2];
  *name = args[3];
  *freq = stoi(args[4], nullptr, 10);
  *filename = args[5];
  return true;
}



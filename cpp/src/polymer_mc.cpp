/*
 * polymer_mc.cpp
 *
 *  Created on: 5 Feb 2019
 *      Author: michaelchiang
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <random>
#include <cmath>
#include <utility>
#include <tuple>
#include "polymer_mc.hpp"
#include "pair_none.hpp"
#include "util_vector.hpp"
#include "dump_position.hpp"
#include "dump_gyration.hpp"
#include "dump_factory.hpp"

using std::string;
using std::vector;
using std::pair;
using std::tie;
using std::set;
using std::cout;
using std::endl;
using std::ofstream;
using std::stringstream;

PolymerMC::PolymerMC(int _chainSize, double xlo, double xhi,
                     double ylo, double yhi, double zlo, double zhi,
                     bool xBound, bool yBound, bool zBound,
                     int _ntrials, int _seed) :
  box {Box(xlo, xhi, ylo, yhi, zlo, zhi, xBound, yBound, zBound)},
  rand {RandomDouble(_seed, 0.0, 1.0)} {

  chainSize = _chainSize;
  seed = _seed;

  numOfBeadTypes = 1;
  numOfBondTypes = 1;
  numOfAngleTypes = 1;
  numOfTorsionTypes = 1;

  numOfGroups = 1; // group 'all'
  groups["all"] = 0;

  ntrials = _ntrials;
  temp = 1.0;

  neighbourListCutoff = 0.0;

  oldLogRosenbluth = 0.0;
  newLogRosenbluth = 0.0;

  oldNonBondEnergy = 0.0;
  newNonBondEnergy = 0.0;

  oldChainIndex = 0;
  newChainIndex = 1;

  hasOldChain = false;

  bondFactory = BondFactory();
  angleFactory = AngleFactory();
  torsionFactory = TorsionFactory();

  std::mt19937 mt(seed);
  std::uniform_int_distribution<int> randInt (0, 10000);

  tie(bond, distrbBond) =
      bondFactory.createBond("fixed", numOfBondTypes, {1.0}, temp, randInt(mt));
  tie(angle, distrbAngle) =
      angleFactory.createAngle("none", numOfAngleTypes, {}, temp, randInt(mt));
  tie(angleNone, distrbAngleUni) =
      angleFactory.createAngle("none", numOfAngleTypes, {}, temp, randInt(mt));
  tie(torsion, distrbTorsion) =
      torsionFactory.createTorsion(
          "none", numOfTorsionTypes, {}, temp, randInt(mt));
  tie(torsionNone, distrbTorsionUni) =
      torsionFactory.createTorsion(
          "none", numOfTorsionTypes, {}, temp, randInt(mt));

  pair = pairFactory.createPair("none", numOfBeadTypes, {});

  chains[0] = vector<Bead>(chainSize, Bead());
  chains[1] = vector<Bead>(chainSize, Bead());
  chainCoords[0] = vector<Vec>(chainSize, Vec(0.0, 0.0, 0.0));
  chainCoords[1] = vector<Vec>(chainSize, Vec(0.0, 0.0, 0.0));

  neighbourList = vector<Bead*>();

  bondType = vector<int>(chainSize, 0);
  angleType = vector<int>(chainSize, 0);
  torsionType = vector<int>(chainSize, 0);

  walls = std::map<std::string, Wall*>();
  dumps = std::map<std::string, Dump*>();

  startPos = Vec(0.0, 0.0, 0.0);
  trialPos = vector<Vec>(ntrials, Vec(0.0, 0.0, 0.0));
  trialCoords = vector<Vec>(ntrials, Vec(0.0, 0.0, 0.0));
  trialImage = vector<int*>(ntrials);
  for (int i {}; i < ntrials; i++) {
    trialImage[i] = new int[3] {0,0,0};
  }
  trialProbs = vector<double>(ntrials, 0.0);
  trialBondEnergy = vector<double>(ntrials, 0.0);
  trialNonBondEnergy = vector<double>(ntrials, 0.0);

  dumpFactory = DumpFactory();

  rotate = Mat::unity();
}

PolymerMC::~PolymerMC() {

  chains[0].clear();
  chains[1].clear();
  neighbourList.clear();

  for (int i {}; i < ntrials; i++) {
    delete trialImage[i];
  }
  delete distrbBond;
  delete distrbAngle;
  delete distrbAngleUni;
  delete distrbTorsion;
  delete distrbTorsionUni;

  delete bond;
  delete angle;
  delete angleNone;
  delete torsion;
  delete torsionNone;
  delete pair;

  for (auto const& w : walls) {
    delete w.second;
  }
  for (auto const& d : dumps) {
    delete d.second;
  }
}

void PolymerMC::setBond(const string& bondName,
                        const vector<double>& args, int _seed) {
  delete distrbBond;
  delete bond;
  tie(bond, distrbBond) = bondFactory.createBond(
      bondName, numOfBondTypes, args, temp, _seed);
}

void PolymerMC::setAngle(const string& angleName,
                         const vector<double>& args, int _seed) {
  delete distrbAngle;
  delete angle;
  tie(angle, distrbAngle) = angleFactory.createAngle(
      angleName, numOfAngleTypes, args, temp, _seed);
}

void PolymerMC::setTorsion(const string& torsionName,
                           const vector<double>& args, int _seed) {
  delete distrbTorsion;
  delete torsion;
  tie(torsion, distrbTorsion) = torsionFactory.createTorsion(
      torsionName, numOfTorsionTypes, args, temp, _seed);
}

void PolymerMC::setPair(string pairName, const vector<double>& args) {
  delete pair;
  pair = pairFactory.createPair(pairName, numOfBeadTypes, args);
}

void PolymerMC::setBondType(int type) {
  for (int i {}; i < chainSize; i++) {
    bondType[i] = type;
  }
}

void PolymerMC::setAngleType(int type) {
  for (int i {}; i < chainSize; i++) {
    angleType[i] = type;
  }
}

void PolymerMC::setTorsionType(int type) {
  for (int i {}; i < chainSize; i++) {
    torsionType[i] = type;
  }
}

void PolymerMC::setNeighbourListCutoff(double cutoff) {
  if (cutoff >= 0.0) {
    neighbourListCutoff = cutoff;
  }
}

void PolymerMC::createGroupWith(const string& groupName,
                                const set<int>& types) {
  // Only create a new group if the group name has not been defined before
  if (groups.find(groupName) == groups.end()) {
    unsigned int groupMask {(static_cast<unsigned int>(1) << (numOfGroups-1))};
    unsigned int beadMask;
    groups[groupName] = groupMask;
    for (int i {}; i < chainSize; i++) {
      for (const int& t : types) {
        if (chains[0][i].type == t) {
          beadMask = chains[0][i].mask;
          beadMask |= groupMask;
          chains[0][i].mask = beadMask;
          chains[1][i].mask = beadMask;
          break;
        }
      }
    }
  }
}

void PolymerMC::deleteGroup(const string& groupName) {
  if (groups.find(groupName) != groups.end()) {
    unsigned int groupMask {groups[groupName]};

    // Remove all the fixes associated with the group
    std::map<string,Wall*>::iterator it = walls.begin();
    Wall* wall;
    while (it != walls.end()) {
      wall = it->second;
      if (wall->getMask() == groupMask) {
        delete wall;
        it = walls.erase(it);
      } else {
        it++;
      }
    }

    // Remove the group mask from the relevant beads
    unsigned int invertGroupMask {~(groupMask)};
    unsigned int beadMask;
    for (int i {}; i < chainSize; i++) {
      beadMask = chains[0][i].mask;
      beadMask &= invertGroupMask;
      chains[0][i].mask = beadMask;
      chains[1][i].mask = beadMask;
    }
  }
}

void PolymerMC::createWall(const string& wallID, const string& groupName,
                           const string& wallType, int dir, double pos,
                           bool below, const vector<double>& args) {
  if (walls.find(wallID) == walls.end() &&
      groups.find(groupName) != groups.end()) {
    unsigned int mask {groups[groupName]};
    Wall* wall {wallFactory.createWall(wallType, mask, dir, pos, below, args)};
    walls[wallID] = wall;
  }
}

void PolymerMC::deleteWall(const string& wallID) {
  std::map<string,Wall*>::iterator it {walls.find(wallID)};
  if (it != walls.end()) {
    delete it->second;
    walls.erase(it);
  }
}

void PolymerMC::dump(const string& dumpID, const string& groupName,
                     const string& dumpType, const string& filename, int freq) {
  if (dumps.find(dumpID) == dumps.end() &&
      groups.find(groupName) != groups.end()) {
    unsigned int mask {groups[groupName]};
    Dump* dump {dumpFactory.createDump(dumpType, filename, freq, mask)};
    dumps[dumpID] = dump;
  }
}

void PolymerMC::undump(const string& dumpID) {
  std::map<string,Dump*>::iterator it {dumps.find(dumpID)};
  if (it != dumps.end()) {
    delete it->second;
    dumps.erase(it);
  }
}

void PolymerMC::run(int nequil, int nsteps) {
  cout << "Running equilibration steps ..." << endl;
  for (int n {1}; n <= nequil; n++) {
    cout << "Step " << n << endl;
    mcstep(n);
  }
  cout << "Running main simulation steps ..." << endl;
  for (int n {1}; n <= nsteps; n++) {
    cout << "Step " << n << endl;
    mcstep(n);
    for (auto& dump : dumps) {
      dump.second->dump(n, *this);
    }
  }
  cout << "Done simulating" << endl;
}

void PolymerMC::mcstep(int istep) {
  double logP, logRatio;
  bool accepted {false};
  while (!accepted) {
    growNewChain();
    if (hasOldChain) traceOldChain();
    logP = log(rand.nextDouble());
    logRatio = newLogRosenbluth - oldLogRosenbluth;
    cout << istep << " " << newLogRosenbluth << " " << oldLogRosenbluth << endl;
    if (logRatio > 0.0 || logP < logRatio) { // New config is accepted
      hasOldChain = true;
      oldChainIndex = (oldChainIndex == 0 ? 1 : 0);
      newChainIndex = (newChainIndex == 0 ? 1 : 0);
      accepted = true;
    }
  }
}

void PolymerMC::growNewChain() {
  rotate.toUnity();
  newLogRosenbluth = 0.0;
  newNonBondEnergy = 0.0;

  chains[newChainIndex][0].pos = startPos;

  int btype, atype, ttype, ptype;
  unsigned int beadMask;
  Vec v1, v2, v3;

  for (int i {1}; i < chainSize; i++) {
    v1 = chains[newChainIndex][i-1].pos;
    v2 = (i == 1 ? v1 : chains[newChainIndex][i-2].pos);
    v3 = (i <= 2 ? v2 : chains[newChainIndex][i-3].pos);
    btype = bondType[i];
    atype = angleType[i];
    ttype = torsionType[i];
    ptype = chains[newChainIndex][i].type;
    beadMask = chains[newChainIndex][i].mask;
    buildNeighbourList(chains[newChainIndex], i-1, neighbourListCutoff,
                       &neighbourList);

    double expEnergy {};
    double weight {}; // Rosenbluth weight
    for (int k {}; k < ntrials; k++) {
      generateBead(v1, v2, v3, btype, atype, ttype,
                   i, &trialCoords[k], &trialBondEnergy[k]);

      double r {trialCoords[k][0]};
      double theta {trialCoords[k][1]};
      double phi {trialCoords[k][2]};
      double costheta {cos(theta)};
      double sintheta {sin(theta)};
      double cosphi {cos(phi)};
      double sinphi {sin(phi)};
      Vec pos {r*sintheta*cosphi, r*sintheta*sinphi, r*costheta};

      for (int j {}; j < 3; j++) {
        trialImage[k][j] = chains[newChainIndex][i-1].image[j];
      }

      // Get lab frame coordinates
      trialPos[k] = Mat::matvec(rotate, pos) + v1;
      box.wrapPos(&trialPos[k], trialImage[k]);

      trialNonBondEnergy[k] =
          computeNonBondEnergy(ptype, trialPos[k], neighbourList, *pair);
      trialNonBondEnergy[k] += computeWallEnergy(beadMask, trialPos[k]);
      expEnergy = exp(-trialNonBondEnergy[k]/temp);
      trialProbs[k] = expEnergy;
      weight += expEnergy;
    }

    // Pick which trial segment to accept
    for (int k {}; k < ntrials; k++) {
      trialProbs[k] /= weight;
    }

    double p {rand.nextDouble()};
    int selected {};
    for (int k {}; k < ntrials; k++) {
      p -= trialProbs[k];
      if (p < 0.0) {
        selected = k;
        break;
      }
    }
    chainCoords[newChainIndex][i] = trialCoords[selected];
    chains[newChainIndex][i].pos = trialPos[selected];
    newNonBondEnergy += trialNonBondEnergy[selected];
    for (int k {}; k < 3; k++) {
      chains[newChainIndex][i].image[k] = trialImage[selected][k];
    }
    rotate.dot(getRotateMatrix(trialCoords[selected][1],
                               trialCoords[selected][2]));

    newLogRosenbluth += log(weight);
  }
}

Mat PolymerMC::getRotateMatrix(double theta, double phi) {
  double ct {cos(theta)};
  double st {sin(theta)};
  double cp {cos(phi)};
  double sp {sin(phi)};

  Mat frame {};
  frame[0][0] = ct*cp;
  frame[0][1] = -sp;
  frame[0][2] = st*cp;
  frame[1][0] = ct*sp;
  frame[1][1] = cp;
  frame[1][2] = st*sp;
  frame[2][0] = -st;
  frame[2][1] = 0.0;
  frame[2][2] = ct;

  return frame;
}

void PolymerMC::traceOldChain() {
  rotate.toUnity();
  oldLogRosenbluth = 0.0;
  oldNonBondEnergy = 0.0;

  int btype, atype, ttype, ptype;
  unsigned int beadMask;
  Vec v1, v2, v3;

  for (int i {1}; i < chainSize; i++) {
    trialPos[0] = chains[oldChainIndex][i].pos; // Store current config
    trialCoords[0] = chainCoords[oldChainIndex][i];
    for (int j {}; j < 3; j++) {
      trialImage[0][j] = chains[oldChainIndex][i].image[j];
    }
    v1 = chains[oldChainIndex][i-1].pos;
    v2 = (i == 1 ? v1 : chains[oldChainIndex][i-2].pos);
    v3 = (i <= 2 ? v2 : chains[oldChainIndex][i-3].pos);
    btype = bondType[i];
    atype = angleType[i];
    ttype = torsionType[i];
    ptype = chains[oldChainIndex][i].type;
    beadMask = chains[oldChainIndex][i].mask;
    buildNeighbourList(chains[oldChainIndex], i-1, neighbourListCutoff,
                       &neighbourList);

    double weight {}; // Rosenbluth weight
    double expEnergy {};

    trialNonBondEnergy[0] =
        computeNonBondEnergy(ptype, trialPos[0], neighbourList, *pair);
    trialNonBondEnergy[0] += computeWallEnergy(beadMask, trialPos[0]);
    oldNonBondEnergy += trialNonBondEnergy[0];
    expEnergy = exp(-trialNonBondEnergy[0]/temp);
    weight += expEnergy;

    for (int k {1}; k < ntrials; k++) {
      generateBead(v1, v2, v3, btype, atype, ttype,
                   i, &trialCoords[k], &trialBondEnergy[k]);

      double r {trialCoords[k][0]};
      double theta {trialCoords[k][1]};
      double phi {trialCoords[k][2]};
      double costheta {cos(theta)};
      double sintheta {sin(theta)};
      double cosphi {cos(phi)};
      double sinphi {sin(phi)};
      Vec pos {r*sintheta*cosphi, r*sintheta*sinphi, r*costheta};

      for (int j {}; j < 3; j++) {
        trialImage[k][j] = chains[oldChainIndex][i-1].image[j];
      }

      // Get lab frame coordinates
      trialPos[k] = Mat::matvec(rotate, pos) + v1;
      box.wrapPos(&trialPos[k], trialImage[k]);

      trialNonBondEnergy[k] =
          computeNonBondEnergy(ptype, trialPos[k], neighbourList, *pair);
      trialNonBondEnergy[k] += computeWallEnergy(beadMask, trialPos[k]);
      expEnergy = exp(-trialNonBondEnergy[k]/temp);
      weight += expEnergy;
    }

    rotate.dot(getRotateMatrix(trialCoords[0][1], trialCoords[0][2]));

    oldLogRosenbluth += log(weight);
  }
}

void PolymerMC::buildNeighbourList(vector<Bead>& chain,
                                   int beadIndex, double cutoff,
                                   vector<Bead*>* list) {
  list->clear();
  for (int i {}; i < beadIndex; i++) {
    if (box.dist(chain[beadIndex].pos, chain[i].pos) < cutoff) {
      list->push_back(&chain[i]);
    }
  }
}

double PolymerMC::computeNonBondEnergy(int pairType, const Vec& pos,
                                       vector<Bead*>& list,
                                       Pair& pairPotential) {
  double energy {};
  for (size_t i {}; i < list.size(); i++) {
    energy += pairPotential.compute(list[i]->type, pairType,
                                     box.dist(list[i]->pos, pos));
  }
  return energy;
}

double PolymerMC::computeWallEnergy(unsigned int beadMask, const Vec& pos) {
  double energy {};
  for (auto const& w : walls) {
    energy += w.second->compute(beadMask, pos);
  }
  return energy;
}

void PolymerMC::generateBead(const Vec& v1, const Vec& v2, const Vec& v3,
                             int btype, int atype, int ttype,
                             int beadIndex, Vec* coords, double* energy) {
  double r {}, theta {}, phi {};
  double bondEnergy {}, angleEnergy {}, torsionEnergy {};

  if (beadIndex == 1) {
    distrbBond->generate(btype, v1, &r, &bondEnergy);
    distrbAngleUni->generate(atype, v1, v2, &theta, &angleEnergy);
    distrbTorsionUni->generate(ttype, v1, v2, v3, &phi, &torsionEnergy);
  } else if (beadIndex == 2) {
    distrbBond->generate(btype, v1, &r, &bondEnergy);
    distrbAngle->generate(atype, v1, v2, &theta, &angleEnergy);
    distrbTorsionUni->generate(ttype, v1, v2, v3, &phi, &torsionEnergy);
  } else if (beadIndex > 2) {
    distrbBond->generate(btype, v1, &r, &bondEnergy);
    distrbAngle->generate(atype, v1, v2, &theta, &angleEnergy);
    distrbTorsion->generate(ttype, v1, v2, v3, &phi, &torsionEnergy);
  }

  (*coords)[0] = r;
  (*coords)[1] = theta;
  (*coords)[2] = phi;

  *energy = bondEnergy + angleEnergy + torsionEnergy;
}

void PolymerMC::setStartPos(const Vec& v) {
  startPos = v;
}

Bead& PolymerMC::getBead(int index) {
  return chains[newChainIndex][index];
}

const Bead& PolymerMC::getBead(int index) const {
  return chains[newChainIndex][index];
}

int PolymerMC::getNumOfBeads() const {
  return chainSize;
}

double PolymerMC::getBoxSize(int comp) const {
  return box.getBoxSize(comp);
}

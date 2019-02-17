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

using std::string;
using std::vector;
using std::pair;
using std::tie;
using std::set;
using std::cout;
using std::endl;
using std::ofstream;
using std::stringstream;

PolymerMC::PolymerMC(double _boxSize, int _chainSize, int _seed, int _ntrials) :
  rand {RandomDouble(_seed, 0.0, 1.0)} {
  lx = _boxSize;
  ly = _boxSize;
  lz = _boxSize;
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

  oldChainIndex = 0;
  newChainIndex = 1;

  hasOldChain = false;

  bondFactory = BondFactory();
  angleFactory = AngleFactory();
  torsionFactory = TorsionFactory();

  tie(bond, distrbBond) =
      bondFactory.createBond("fixed", numOfBondTypes, {1.0}, temp, 0);
  tie(angle, distrbAngle) =
      angleFactory.createAngle("none", numOfAngleTypes, {}, temp, 87);
  tie(angleNone, distrbAngleUni) =
      angleFactory.createAngle("none", numOfAngleTypes, {}, temp, 34);
  tie(torsion, distrbTorsion) =
      torsionFactory.createTorsion("none", numOfTorsionTypes, {}, temp, 32);
  tie(torsionNone, distrbTorsionUni) =
      torsionFactory.createTorsion("none", numOfTorsionTypes, {}, temp, 12);

  pair = pairFactory.createPair("none", numOfBeadTypes, {});

  chains[0] = vector<Bead>(chainSize, Bead());
  chains[1] = vector<Bead>(chainSize, Bead());

  neighbourList = vector<Bead*>();

  bondType = vector<int>(chainSize, 0);
  angleType = vector<int>(chainSize, 0);
  torsionType = vector<int>(chainSize, 0);

  trialPos = vector<Vec>(ntrials, Vec(0.0, 0.0, 0.0));
  trialCoords = vector<Vec>(ntrials, Vec(0.0, 0.0, 0.0));
  trialProbs = vector<double>(ntrials, 0.0);
  trialBondEnergy = vector<double>(ntrials, 0.0);
  trialNonBondEnergy = vector<double>(ntrials, 0.0);

  rotate = Mat::unity();
}

PolymerMC::~PolymerMC() {
  chains[0].clear();
  chains[1].clear();
  neighbourList.clear();

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

  // delete walls
  for (auto const& w : walls) {
    delete w.second;
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
        if (chains[0][i].getType() == t) {
          beadMask = chains[0][i].getMask();
          beadMask |= groupMask;
          chains[0][i].setMask(beadMask);
          chains[1][i].setMask(beadMask);
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
      beadMask = chains[0][i].getMask();
      beadMask &= invertGroupMask;
      chains[0][i].setMask(beadMask);
      chains[1][i].setMask(beadMask);
    }
  }
}

void PolymerMC::createWall(const string& wallID, const string& groupName,
                           const string& wallType, int dir, double pos,
                           bool below, const vector<double>& args) {
  if (walls.find(wallID) == walls.end() &&
      groups.find(groupName) != groups.end()) {
    unsigned int mask {groups[groupName]};
    Wall* wall = wallFactory.createWall(wallType, mask, dir, pos, below, args);
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

void PolymerMC::run(int nequil, int nsteps, int nsample) {
  for (int n {}; n < nequil; n++) {
    mcstep(n);
  }
  for (int n {}; n < nsteps; n++) {
    mcstep(n);
    if (n % nsample == 0) {
      stringstream ss;
      ss.clear();
      ss << "pos_t_" << n << ".dat";
      ofstream writer (ss.str());
      Vec* v;
      for (int i {}; i < chainSize; i++) {
        v = chains[newChainIndex][i].getPos();
        writer << i << " " << (*v)[0] << " "
               << (*v)[1] << " " << (*v)[2] << endl;
      }
    }
  }
}

void PolymerMC::mcstep(int istep) {
  double logP, logRatio;
  bool accepted {false};
  while (!accepted) {
    growNewChain();
    if (hasOldChain) traceOldChain();
    logP = log(rand.nextDouble());
    logRatio = newLogRosenbluth - oldLogRosenbluth;
    if (logRatio > 0.0 || logP < logRatio) { // New config is accepted
      hasOldChain = true;
      oldChainIndex = (oldChainIndex == 0 ? 1 : 0);
      newChainIndex = (newChainIndex == 0 ? 1 : 0);
      accepted = true;
      cout << istep << " accepted" << endl;
    } else {
      cout << istep << " rejected" << endl;
    }
  }
}

void PolymerMC::growNewChain() {
  rotate.toUnity();
  newLogRosenbluth = 0.0;
  double weight {}; // Rosenbluth weight
  int btype, atype, ttype, ptype;
  unsigned int beadMask;
  Vec* v1; Vec* v2; Vec* v3;
  double expEnergy;

  for (int i {1}; i < chainSize; i++) {
    v1 = chains[newChainIndex][i-1].getPos();
    v2 = (i == 1 ? v1 : chains[newChainIndex][i-2].getPos());
    v3 = (i <= 2 ? v2 : chains[newChainIndex][i-3].getPos());
    btype = bondType[i];
    atype = angleType[i];
    ttype = torsionType[i];
    ptype = chains[newChainIndex][i].getType();
    beadMask = chains[newChainIndex][i].getMask();
    buildNeighbourList(chains[newChainIndex], i-1, neighbourListCutoff);

    for (int k {}; k < ntrials; k++) {
      generateBead(*v1, *v2, *v3, btype, atype, ttype,
                   i, &trialCoords[k], &trialBondEnergy[k]);

      double r {trialCoords[k][0]};
      double theta {trialCoords[k][1]};
      double phi {trialCoords[k][2]};
      double costheta {cos(theta)};
      double sintheta {sin(theta)};
      double cosphi {cos(phi)};
      double sinphi {sin(phi)};
      Vec pos {r*sintheta*cosphi, r*sintheta*sinphi, r*costheta};

      // Get lab frame coordinates
      trialPos[k] = Mat::matvec(rotate, pos) + *v1;

      trialNonBondEnergy[k] =
          computeNonBondEnergy(chains[newChainIndex], ptype, i, trialPos[k]);
      trialNonBondEnergy[k] += computeWallEnergy(beadMask, trialPos[k]);
      expEnergy = exp(-trialNonBondEnergy[k]/temp);
      trialProbs[k] = expEnergy;
      weight += expEnergy;
    }

    // Pick which trial segment to accept
    double sum {};
    for (int k {}; k < ntrials; k++) {
      trialProbs[k] = trialProbs[k]/weight + sum;
      sum += trialProbs[k];
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

    chains[newChainIndex][i].setPos(trialPos[selected]);

    rotate.dot(getRotateMatrix(trialCoords[selected][1],
                               trialCoords[selected][2]));

    newLogRosenbluth += log(weight);

    weight = 0.0;
  }

  cout << newLogRosenbluth << endl;
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
  double weight {}; // Rosenbluth weight
  int btype, atype, ttype, ptype;
  unsigned int beadMask;
  Vec* v1; Vec* v2; Vec* v3;
  double expEnergy;

  for (int i {1}; i < chainSize; i++) {
    trialPos[0] = *chains[oldChainIndex][i].getPos(); // Store current config
    v1 = chains[oldChainIndex][i-1].getPos();
    v2 = (i == 1 ? v1 : chains[oldChainIndex][i-2].getPos());
    v3 = (i <= 2 ? v2 : chains[oldChainIndex][i-3].getPos());
    btype = bondType[i];
    atype = angleType[i];
    ttype = torsionType[i];
    ptype = chains[oldChainIndex][i].getType();
    beadMask = chains[oldChainIndex][i].getMask();
    buildNeighbourList(chains[oldChainIndex], i-1, neighbourListCutoff);

    for (int k {1}; k < ntrials; k++) {
      generateBead(*v1, *v2, *v3, btype, atype, ttype,
                   i, &trialCoords[k], &trialBondEnergy[k]);

      double r {trialCoords[k][0]};
      double theta {trialCoords[k][1]};
      double phi {trialCoords[k][2]};
      double costheta {cos(theta)};
      double sintheta {sin(theta)};
      double cosphi {cos(phi)};
      double sinphi {sin(phi)};

      Vec pos {r*sintheta*cosphi, r*sintheta*sinphi, r*costheta};

      // Get lab frame coordinates
      trialPos[k] = Mat::matvec(rotate, pos) + *v1;

      trialNonBondEnergy[k] =
          computeNonBondEnergy(chains[oldChainIndex], ptype, i, trialPos[k]);
      trialNonBondEnergy[k] += computeWallEnergy(beadMask, trialPos[k]);
      expEnergy = exp(-trialNonBondEnergy[k]/temp);
      weight += expEnergy;
    }

    rotate.dot(getRotateMatrix(trialCoords[0][1], trialCoords[0][2]));

    oldLogRosenbluth += log(weight);
    weight = 0.0;
  }

  cout << oldLogRosenbluth << endl;
}

void PolymerMC::buildNeighbourList(vector<Bead>& chain,
                                   int beadIndex, double cutoff) {
  neighbourList.clear();
  Vec* v1; Vec* v2;
  v1 = chain[beadIndex].getPos();
  for (int i {}; i < beadIndex; i++) {
    v2 = chain[i].getPos();
    if (Vec::dist(*v1,*v2) < cutoff) {
      neighbourList.push_back(&chain[i]);
    }
  }
}

double PolymerMC::computeNonBondEnergy(vector<Bead>& chain, int pairType,
                                       int beadIndex, const Vec& pos) {
  double energy {};
  for (size_t i {}; i < neighbourList.size(); i++) {
    energy += pair->compute(neighbourList[i]->getType(), pairType,
                            *(neighbourList[i]->getPos()), pos);
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
                             int beadIndex, Vec* pos, double* energy) {
  double r, theta, phi;
  double bondEnergy {}, angleEnergy {}, torsionEnergy {};

  if (beadIndex == 1) {
    distrbBond->generate(btype, v1, &r, &bondEnergy);
    distrbAngleUni->generate(atype, v1, v2, &theta, &angleEnergy);
    distrbTorsionUni->generate(ttype, v1, v2, v3, &phi, &torsionEnergy);
  } else if (beadIndex == 2) {
    distrbBond->generate(btype, v1, &r, &bondEnergy);
    distrbAngle->generate(atype, v1, v2, &theta, &angleEnergy);
    distrbTorsionUni->generate(ttype, v1, v2, v3, &phi, &torsionEnergy);
  } else {
    distrbBond->generate(btype, v1, &r, &bondEnergy);
    distrbAngle->generate(atype, v1, v2, &theta, &angleEnergy);
    distrbTorsionUni->generate(ttype, v1, v2, v3, &phi, &torsionEnergy);
  }

  (*pos)[0] = r;
  (*pos)[1] = theta;
  (*pos)[2] = phi;

  *energy = bondEnergy + angleEnergy + torsionEnergy;
}

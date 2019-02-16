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
using std::cout;
using std::endl;
using std::ofstream;
using std::stringstream;

PolymerMC::PolymerMC(double _boxSize, int _chainSize, int _seed, int _ntrials) :
  rand {RandomDouble(_seed, 0.0, 1.0)} {
  boxSize = _boxSize;
  chainSize = _chainSize;
  seed = _seed;

  numOfBeadTypes = 1;
  numOfBondTypes = 1;
  numOfAngleTypes = 1;
  numOfTorsionTypes = 1;

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

  for (int i {}; i < 2; i++) {
    chains[i] = new Bead [chainSize];
  }

  neighbourList = vector<Bead*>();

  bondType = vector<int>(chainSize, 0);
  angleType = vector<int>(chainSize, 0);
  torsionType = vector<int>(chainSize, 0);

  trialPos = new Vec [ntrials];
  trialCoords = new Vec [ntrials];
  trialBondEnergy = new double [ntrials];
  trialNonBondEnergy = new double [ntrials];
  for (int i {}; i < ntrials; i++) {
    trialBondEnergy[i] = 0.0;
    trialNonBondEnergy[i] = 0.0;
  }

  rotate = Mat::unity();
}

PolymerMC::~PolymerMC() {
  delete bond;
  delete angle;
  delete angleNone;
  delete torsion;
  delete torsionNone;
  delete pair;

  for (int i {}; i < 2; i++) {
    delete[] chains[i];
  }

  delete[] trialPos;
  delete[] trialCoords;
  delete[] trialBondEnergy;
  delete[] trialNonBondEnergy;

  delete distrbBond;
  delete distrbAngle;
  delete distrbAngleUni;
  delete distrbTorsion;
  delete distrbTorsionUni;
}

/*void PolymerMC::setNumTrials(int trials) {
  ntrials = trials;
}*/

void PolymerMC::setBond(string bondName,
                        const vector<double>& args, int _seed) {
  delete bond;
  delete distrbBond;
  tie(bond, distrbBond) = bondFactory.createBond(
      bondName, numOfBondTypes, args, temp, _seed);
}

void PolymerMC::setAngle(string angleName,
                         const vector<double>& args, int _seed) {
  delete angle;
  delete distrbAngle;
  tie(angle, distrbAngle) = angleFactory.createAngle(
      angleName, numOfAngleTypes, args, temp, _seed);
}

void PolymerMC::setTorsion(string torsionName,
                           const vector<double>& args, int _seed) {
  delete torsion;
  delete distrbTorsion;
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
  Vec* v1; Vec* v2; Vec* v3;
  double* probs = new double[ntrials];
  double expEnergy;

  for (int i {1}; i < chainSize; i++) {
    v1 = chains[newChainIndex][i-1].getPos();
    v2 = (i == 1 ? v1 : chains[newChainIndex][i-2].getPos());
    v3 = (i <= 2 ? v2 : chains[newChainIndex][i-3].getPos());
    btype = bondType[i];
    atype = angleType[i];
    ttype = torsionType[i];
    ptype = chains[newChainIndex][i].getType();
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

      //trialNonBondEnergy[k] += computeWallEnergy(trialPos[k]);
      expEnergy = exp(-trialNonBondEnergy[k]/temp);
      probs[k] = expEnergy;
      weight += expEnergy;
    }

    // Pick which trial segment to accept
    double sum {};
    for (int k {}; k < ntrials; k++) {
      probs[k] = probs[k]/weight + sum;
      sum += probs[k];
    }
    double p {rand.nextDouble()};
    int selected {};
    for (int k {}; k < ntrials; k++) {
      p -= probs[k];
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

  delete[] probs;
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
  Vec* v1; Vec* v2; Vec* v3;
  double* probs = new double[ntrials];
  double expEnergy;

  for (int i {1}; i < chainSize; i++) {
    trialPos[0] = *chains[newChainIndex][i].getPos(); // Store current config
    v1 = chains[newChainIndex][i-1].getPos();
    v2 = (i == 1 ? v1 : chains[newChainIndex][i-2].getPos());
    v3 = (i <= 2 ? v2 : chains[newChainIndex][i-3].getPos());
    btype = bondType[i];
    atype = angleType[i];
    ttype = torsionType[i];
    ptype = chains[newChainIndex][i].getType();
    buildNeighbourList(chains[newChainIndex], i-1, neighbourListCutoff);

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
          computeNonBondEnergy(chains[newChainIndex], ptype, i, trialPos[k]);

      //trialNonBondEnergy[k] += computeWallEnergy(trialPos[k]);
      expEnergy = exp(-trialNonBondEnergy[k]/temp);
      probs[k] = expEnergy;
      weight += expEnergy;
    }

    rotate.dot(getRotateMatrix(trialCoords[0][1], trialCoords[0][2]));

    oldLogRosenbluth += log(weight);
    weight = 0.0;
  }

  cout << oldLogRosenbluth << endl;

  delete[] probs;
}

void PolymerMC::buildNeighbourList(Bead* chain, int beadIndex, double cutoff) {
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

double PolymerMC::computeNonBondEnergy(Bead* chain, int pairType,
                                       int beadIndex, const Vec& pos) {
  double energy {};
  for (size_t i {}; i < neighbourList.size(); i++) {
    energy += pair->compute(neighbourList[i]->getType(), pairType,
                            *(neighbourList[i]->getPos()), pos);
  }
  return energy;
}

double PolymerMC::computeWallEnergy(const Vec& pos) {
  double energy {};

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

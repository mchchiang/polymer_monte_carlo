/*
 * polymer_mc.hpp
 *
 *  Created on: 5 Feb 2019
 *      Author: michaelchiang
 */

#ifndef POLYMER_MC_HPP_
#define POLYMER_MC_HPP_

#include <string>
#include <vector>
#include <map>
#include <set>
#include <random>
#include "box.hpp"
#include "bead.hpp"
#include "bond.hpp"
#include "bond_factory.hpp"
#include "angle.hpp"
#include "angle_factory.hpp"
#include "torsion.hpp"
#include "torsion_factory.hpp"
#include "distrb.hpp"
#include "pair.hpp"
#include "pair_factory.hpp"
#include "wall.hpp"
#include "wall_factory.hpp"
#include "util_random.hpp"
#include "util_vector.hpp"
#include "dump.hpp"
#include "dump_factory.hpp"

class PolymerMC {

private:
  Box box;

  int chainSize;
  int seed;

  int ntrials;
  double temp;

  int numOfBeadTypes;
  int numOfBondTypes;
  int numOfAngleTypes;
  int numOfTorsionTypes;

  int newChainIndex;
  int oldChainIndex;

  double newLogRosenbluth;
  double oldLogRosenbluth;

  double newNonBondEnergy;
  double oldNonBondEnergy;
  std::vector<Bead> chains[2];
  std::vector<Vec> chainCoords[2];
  std::vector<Bead*> neighbourList;
  std::vector<int> bondType;
  std::vector<int> angleType;
  std::vector<int> torsionType;

  Vec startPos;
  std::vector<Vec> trialPos;
  std::vector<Vec> trialCoords;
  std::vector<int*> trialImage;
  std::vector<double> trialProbs;
  std::vector<double> trialBondEnergy;
  std::vector<double> trialNonBondEnergy;

  int numOfGroups;
  std::map<std::string,unsigned int> groups;

  double neighbourListCutoff;
  bool hasOldChain;

  BondFactory bondFactory;
  AngleFactory angleFactory;
  TorsionFactory torsionFactory;
  PairFactory pairFactory;
  WallFactory wallFactory;

  Bond* bond;
  Angle* angle;
  Angle* angleNone;
  Torsion* torsion;
  Torsion* torsionNone;
  Pair* pair;
  std::map<std::string, Wall*> walls;
  std::map<std::string, Dump*> dumps;
  DumpFactory dumpFactory;

  Distribution* distrbBond;
  Distribution* distrbAngle;
  Distribution* distrbAngleUni;
  Distribution* distrbTorsion;
  Distribution* distrbTorsionUni;

  RandomDouble rand;

  // For coordinate transformation
  Mat rotate;

  // Helper functions
  Mat getRotateMatrix(double theta, double phi);

public:
  PolymerMC(int chainSize, double xlo, double xhi, double ylo, double yhi,
            double zlo, double zhi, bool xBound, bool yBound, bool zBound,
            int ntrials, int seed);
  ~PolymerMC();

  Vec generateCoords(int bondType, int angleType, int torsionType,
                     int beadIndex);

  void growNewChain();
  void traceOldChain();
  void buildNeighbourList(std::vector<Bead>& chain, int beadIndex,
                          double cutoff, std::vector<Bead*>* list);

  double computeNonBondEnergy(int pairType, const Vec& pos,
                              std::vector<Bead*>& list, Pair& pairPotential);
  double computeWallEnergy(unsigned int beadMask, const Vec& pos);

  void run(int nequil, int nsteps);
  void mcstep(int isteps);

  void setBond(const std::string& bondName,
               const std::vector<double>& args, int seed);
  void setAngle(const std::string& angleName,
                const std::vector<double>& args, int seed);
  void setTorsion(const std::string& torsionName,
                  const std::vector<double>& args, int seed);
  void setPair(std::string pairName, const std::vector<double>& args);

  void setBondType(int type);
  void setAngleType(int type);
  void setTorsionType(int type);

  void createGroupWith(const std::string& groupName,
                       const std::set<int>& types);
  void deleteGroup(const std::string& groupName);

  void createWall(const std::string& wallID, const std::string& groupName,
                  const std::string& wallType, int dir, double pos,
                  bool fromBelow, const std::vector<double>& args);
  void deleteWall(const std::string& wallID);

  void dump(const std::string& dumpID, const std::string& groupName,
            const std::string& dumpType, const std::string& filename,
            int freq);

  void undump(const std::string& dumpID);

  void setNeighbourListCutoff(double cutoff);

  void setStartPos(const Vec& v);

  Bead& getBead(int index);
  const Bead& getBead(int index) const;
  int getNumOfBeads() const;
  double getBoxSize(int comp) const;

};


#endif /* POLYMER_MC_HPP_ */

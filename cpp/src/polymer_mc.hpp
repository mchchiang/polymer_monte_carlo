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
#include <random>
#include "bead.hpp"
#include "bond.hpp"
#include "bond_distrb.hpp"
#include "bond_factory.hpp"
#include "angle.hpp"
#include "angle_distrb.hpp"
#include "angle_factory.hpp"
#include "torsion.hpp"
#include "torsion_distrb.hpp"
#include "torsion_factory.hpp"
#include "pair.hpp"
#include "pair_factory.hpp"
#include "util_random.hpp"
#include "util_vector.hpp"

class PolymerMC {

private:
	int boxSize;
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

	Bead* chains[2];
	std::vector<Bead*> neighbourList;
	std::vector<int> bondType;
	std::vector<int> angleType;
	std::vector<int> torsionType;

	Vec* trialPos;
	Vec* trialCoords;
	double* trialBondEnergy;
	double* trialNonBondEnergy;

	double neighbourListCutoff;
	bool hasOldChain;

	BondFactory bondFactory;
	AngleFactory angleFactory;
	TorsionFactory torsionFactory;
	PairFactory pairFactory;

	Bond* bond;
	Angle* angle;
	Angle* angleNone;
	Torsion* torsion;
	Torsion* torsionNone;
	Pair* pair;

  BondDistribution* distrbBond;
  AngleDistribution* distrbAngle;
  AngleDistribution* distrbAngleUni;
  TorsionDistribution* distrbTorsion;
  TorsionDistribution* distrbTorsionUni;

	RandomDouble rand;

	// For coordinate transformation
	Mat rotate;

	// Helper functions
	Mat getRotateMatrix(double theta, double phi);

public:
	PolymerMC(double boxSize, int chainSize, int seed, int ntrials);
	~PolymerMC();

	void generateBead(const Vec& v1, const Vec& v2, const Vec& v3,
	                  int bondType, int angleType, int torsionType,
	                  int beadIndex, Vec* pos, double* energy);

	void growNewChain();
	void traceOldChain();
	void buildNeighbourList(Bead* chain, int beadIndex, double cutoff);

	double computeNonBondEnergy(Bead* chain, int pairType,
	                            int beadIndex, const Vec& pos);
	double computeWallEnergy(const Vec& pos);

	void run(int nequil, int nsteps, int nsample);
	void mcstep(int isteps);

	// Accessor methods
	//int getChainSize() const;
	//double getBoxSize() const;

	//void setNumTrials(int trials);

  void setBond(std::string bondName,
               const std::vector<double>& args, int seed);
  void setAngle(std::string angleName,
                const std::vector<double>& args, int seed);
  void setTorsion(std::string torsionName,
                  const std::vector<double>& args, int seed);
  void setPair(std::string pairName, const std::vector<double>& args);

  void setBondType(int type);
  void setAngleType(int type);
  void setTorsionType(int type);

  void setNeighbourListCutoff(double cutoff);
};


#endif /* POLYMER_MC_HPP_ */

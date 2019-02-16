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
#include "angle.hpp"
#include "torsion.hpp"
#include "pair.hpp"
#include "angle_distrb.hpp"
#include "bond_distrb.hpp"
#include "torsion_distrb.hpp"
#include "util_random.hpp"
#include "util_vector.hpp"

class PolymerMC {

private:
	int boxSize;
	int chainSize;
	int seed;

	int ntrials;
	double temp;

  int newChainIndex;
  int oldChainIndex;

  double newLogRosenbluth;
  double oldLogRosenbluth;

	Bead* chains[2];
	std::vector<Bead*> neighbourList;
	int* bondType;
	int* angleType;
	int* torsionType;

	Vec* trialPos;
	Vec* trialCoords;
	double* trialBondEnergy;
	double* trialNonBondEnergy;

	double neighbourListCutoff;
	bool hasOldChain;

	Bond* bond;
	Angle* angle;
	Torsion* torsion;
	Pair* pair;

	RandomDouble rand;

	BondDistribution* distrbBond;
	AngleDistribution* distrbAngle;
	AngleDistribution* distrbAngleUni;
	TorsionDistribution* distrbTorsion;
	TorsionDistribution* distrbTorsionUni;

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

  void setBond(Bond* bond);
  void setAngle(Angle* angle);
  void setTorsion(Torsion* torsion);
  void setPair(Pair* pair);

  void setBondDistribution(BondDistribution* distrb);
  void setAngleDistribution(AngleDistribution* distrb);
  void setTorsionDistribution(TorsionDistribution* distrb);

  void setBondType(int type);
  void setAngleType(int type);
  void setTorsionType(int type);

  void setNeighbourListCutoff(double cutoff);
};


#endif /* POLYMER_MC_HPP_ */

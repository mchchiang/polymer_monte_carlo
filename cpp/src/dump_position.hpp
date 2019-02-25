/*
 * dump_position.hpp
 *
 *  Created on: 24 Feb 2019
 *      Author: michaelchiang
 */

#ifndef DUMP_POSITION_HPP_
#define DUMP_POSITION_HPP_

#include <string>
#include <vector>
#include "dump.hpp"
#include "polymer_mc.hpp"

class DumpPosition : public Dump {

private:
  unsigned int mask; // The group of atoms to dump
  std::vector<std::string> typeToSim;

public:
  DumpPosition(std::string name, int freq, unsigned int groupMask);
  ~DumpPosition();
  void dump(const int& timestep, const PolymerMC& sim);

};

#endif /* DUMP_POSITION_HPP_ */

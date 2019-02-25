/*
 * dump_gyration.hpp
 *
 *  Created on: 24 Feb 2019
 *      Author: michaelchiang
 */

#ifndef DUMP_GYRATION_HPP_
#define DUMP_GYRATION_HPP_

#include <string>
#include <vector>
#include "dump.hpp"
#include "polymer_mc.hpp"

class DumpGyration : public Dump {

private:
  unsigned int mask; // The group of atoms to dump

public:
  DumpGyration(std::string name, int freq, unsigned int groupMask);
  ~DumpGyration();
  void dump(const int& timestep, const PolymerMC& sim);

};

#endif /* DUMP_GYRATION_HPP_ */

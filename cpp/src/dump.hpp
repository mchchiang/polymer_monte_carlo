/*
 * dump.hpp
 *
 *  Created on: 24 Feb 2019
 *      Author: michaelchiang
 */

#ifndef DUMP_HPP_
#define DUMP_HPP_

#include <fstream>
#include <string>

class PolymerMC;

class Dump {

protected:
  std::ofstream writer;
  std::string filename;
  int dumpfreq;

public:
  Dump(std::string name, int freq);
  virtual ~Dump() {}
  virtual void dump(const int& timestep, const PolymerMC& sim) = 0;

};

#endif /* DUMP_HPP_ */

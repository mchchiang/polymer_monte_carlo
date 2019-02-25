/*
 * dump_none.hpp
 *
 *  Created on: 25 Feb 2019
 *      Author: michaelchiang
 */

#ifndef DUMP_NONE_HPP_
#define DUMP_NONE_HPP_

#include <string>
#include "dump.hpp"
#include "polymer_mc.hpp"

class DumpNone : public Dump {

public:
  DumpNone() : Dump({},0) {}
  ~DumpNone() {}
  void dump(const int& timestep, const PolymerMC& sim) {} // Do nothing
};


#endif /* DUMP_NONE_HPP_ */

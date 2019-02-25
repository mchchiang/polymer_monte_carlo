/*
 * dump_factory.cpp
 *
 *  Created on: 25 Feb 2019
 *      Author: michaelchiang
 */

#include <string>
#include "dump_factory.hpp"
#include "dump_position.hpp"
#include "dump_gyration.hpp"
#include "dump_none.hpp"

using std::string;

Dump* DumpFactory::createDumpPosition(const string& filename,
                                      int freq, int mask) {
  return new DumpPosition(filename, freq, mask);
}

Dump* DumpFactory::createDumpGyration(const string& filename,
                                      int freq, int mask) {
  return new DumpGyration(filename, freq, mask);
}

Dump* DumpFactory::createDumpNone() {
  return new DumpNone();
}

Dump* DumpFactory::createDump(const string& dumpName, const string& filename,
                              int freq, int mask) {
  if (dumpName.compare("position") == 0) {
    return createDumpPosition(filename, freq, mask);
  } else if (dumpName.compare("gyration") == 0) {
    return createDumpGyration(filename, freq, mask);
  } else {
    return createDumpNone();
  }
}

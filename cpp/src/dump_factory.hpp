/*
 * dump_factory.hpp
 *
 *  Created on: 25 Feb 2019
 *      Author: michaelchiang
 */

#ifndef DUMP_FACTORY_HPP_
#define DUMP_FACTORY_HPP_

#include <string>
#include "dump.hpp"

class DumpFactory {

private:
  Dump* createDumpPosition(const std::string& filename, int freq, int mask);
  Dump* createDumpGyration(const std::string& filename, int freq, int mask);
  Dump* createDumpNone();

public:
  Dump* createDump(const std::string& dumpName, const std::string& filename,
                   int freq, int mask);

};

#endif /* DUMP_FACTORY_HPP_ */

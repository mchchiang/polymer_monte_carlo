/*
 * dump.cpp
 *
 *  Created on: 24 Feb 2019
 *      Author: michaelchiang
 */

#include <string>
#include <fstream>
#include <sstream>
#include "dump.hpp"

using std::ofstream;
using std::string;
using std::ostringstream;

Dump::Dump(string name, int freq) :
    filename {name}, dumpfreq {freq} {
  // Set up the file stream
  writer.open(name, std::ios_base::out);
  if (!writer.good()) {
    ostringstream ss;
    ss << "Error: Problem with opening the file '" << name << "'";
    throw ss.str();
  }
}



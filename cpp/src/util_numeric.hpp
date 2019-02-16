/*
 * util_numeric.hpp
 *
 *  Created on: 14 Feb 2019
 *      Author: michaelchiang
 */

#ifndef UTIL_NUMERIC_HPP_
#define UTIL_NUMERIC_HPP_

#include <vector>
#include <functional>

struct Data2D {
  std::vector<double> x;
  std::vector<double> y;
};

// Integrate function using Simpson's 1/3 Rule
double integrate(double start, double end, int nbins,
                 const std::function<double(double)>& f);

// Build the cumulative distribution function for
// a particular probability distribution function
Data2D computeCDF(double start, double end, double inc, int nintbins,
                const std::function<double(double)>& f);

// Invert the x and y column of the data
Data2D invert(const Data2D& inData);

Data2D smooth(int nptsout, const Data2D& inData);

double linearInterpolate(double x1, double x2,
                         double y1, double y2, double x);

#endif /* UTIL_NUMERIC_HPP_ */

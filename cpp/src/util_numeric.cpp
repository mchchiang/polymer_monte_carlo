/*
 * util_numeric.cpp
 *
 *  Created on: 14 Feb 2019
 *      Author: michaelchiang
 */

#include <cmath>
#include <vector>
#include <functional>
#include <iostream>
#include "util_numeric.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::function;

// Integrate function using Simpson's 1/3 Rule
// int_a^b f(x) ~ (b-a)/6*[f(a)+4f((a+b)/2)+f(b)]
double integrate(double start, double end, int nbins,
                 const function<double(double)>& f) {
  double inc {(end-start)/static_cast<double>(nbins)};
  double total {};
  double left, right, centre;
  for (int i {}; i < nbins; i++) {
    left = start + inc * i;
    right = left + inc;
    centre = (left + right) * 0.5;
    total += inc / 6.0 * (f(left) + 4.0 * f(centre) + f(right));
  }
  return total;
}

// Build the cumulative distribution function for
// a particular probability distribution function
Data2D computeCDF(double start, double end, double inc, int nintbins,
                const function<double(double)>& f) {
  int nbins {static_cast<int>(ceil((end-start)/inc))};
  Data2D data;
  data.x = vector<double>(nbins);
  data.y = vector<double>(nbins);

  double total {};
  double s {};
  double x {start};
  double xend;
  for (int i {}; i < nbins; i++) {
    xend = (x+inc)>end ? end : x+inc;
    s = integrate(x, xend, nintbins, f);
    total += s;
    data.x[i] = (x+xend) * 0.5;
    data.y[i] = total;
    x += inc;
  }

  return data;
}

Data2D invert(const Data2D& inData) {
  vector<double> xnew;
  vector<double> ynew;
  Data2D outData;
  xnew = vector<double>(inData.y);
  ynew = vector<double>(inData.x);
  outData.x = xnew;
  outData.y = ynew;
  return outData;
}

Data2D smooth(int nptsout, const Data2D& inData) {
  int nptsin {static_cast<int>(inData.x.size())};
  double start {inData.x[0]};
  double end {inData.x[nptsin-1]};
  double inc {(end-start)/static_cast<double>(nptsout-1)};
  Data2D outData;
  outData.x = vector<double>(nptsout);
  outData.y = vector<double>(nptsout);

  int ilo {}, ihi {};
  outData.y[0] = inData.y[0];
  outData.y[nptsout-1] = inData.y[nptsin-1];

  for (int i {}; i < nptsout; i++) {
    outData.x[i] = start + i * inc;
  }

  for (int i {1}; i < nptsout-1; i++) {
    for (int j {}; j < nptsin; j++) {
      if (inData.x[j] > outData.x[i]) {
        ihi = j;
        break;
      }
    }
    ilo = ihi - 1;
    if (inData.x[ilo] == inData.x[ihi]) {
      outData.y[i] = inData.y[ilo];
    } else {
      outData.y[i] = linearInterpolate(inData.x[ilo], inData.x[ihi],
                                       inData.y[ilo], inData.y[ihi],
                                       outData.x[i]);
    }
  }
  return outData;
}

double linearInterpolate(double x1, double x2,
                         double y1, double y2, double x) {
  double dx12 {x1-x2};
  double dx1 {x-x1};
  double dx2 {x-x2};
  return (y1 * dx2 - y2 * dx1) / dx12;
}

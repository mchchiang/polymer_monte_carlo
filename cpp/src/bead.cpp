/*
 * bead.cpp
 *
 *  Created on: 7 Feb 2019
 *      Author: michaelchiang
 */

#include "bead.hpp"

Bead::Bead() {
  pos = Vec();
  image[0] = 0;
  image[1] = 0;
  image[2] = 0;
  type = 0;
  mask = 0;
}

Bead::~Bead() {}

Vec* Bead::getPos() {
  return &pos;
}

void Bead::setPos(const Vec& v) {
  pos = v; // Deep copy of v
}

int Bead::getImage(int comp) const {
  return image[comp];
}

void Bead::setImage(int comp, int value) {
  image[comp] = value;
}

int Bead::getType() const {
  return type;
}

void Bead::setType(int t) {
  type = t;
}

int Bead::getMask() const {
  return mask;
}

void Bead::setMask(int m) {
  mask = m;
}


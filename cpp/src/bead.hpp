/*
 * bead.hpp
 *
 *  Created on: 6 Feb 2019
 *      Author: michaelchiang
 */

#ifndef BEAD_HPP_
#define BEAD_HPP_

#include "util_vector.hpp"

class Bead {

private:
  Vec pos;
  int image[3]; // Image count for periodic boundaries
  int type;
  int mask;

public:
  Bead();
  ~Bead();

  // Accesor methods
  Vec* getPos();
  void setPos(const Vec& vec);
  int getImage(int comp) const;
  void setImage(int comp, int value);
  int getType() const;
  void setType(int type);
  int getMask() const;
  void setMask(int mask);

};


#endif /* BEAD_HPP_ */

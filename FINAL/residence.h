#ifndef RESIDENCE_H
#define RESIDENCE_H

#include <iostream>
#include "nonimprovable.h"


class Residence: public Nonimprovable {
  public:
  	void setOwner(char _owner);
    Residence();
    ~Residence();
};

#endif

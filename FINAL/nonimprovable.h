#ifndef NONIMPROVABLE_H
#define NONIMPROVABLE_H

#include <iostream>
#include "property.h"
using namespace std;


class Nonimprovable: public Property {
  public:
    Nonimprovable();
    ~Nonimprovable();
    //virtual void setOwner(char _owner, int pos) = 0;
};

#endif

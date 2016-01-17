#ifndef GYM_H
#define GYM_H

#include <iostream>
#include "nonimprovable.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class Gym: public Nonimprovable {
  public:
    Gym();
    ~Gym();

    void setOwner(char _owner);
};

#endif

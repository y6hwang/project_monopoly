#ifndef NON_PROPERTY_H
#define NON_PROPERTY_H
#include "board.h"
#include <iostream>


class NonProperty: public Board {
  public:
    NonProperty();
    ~NonProperty();

    void setOwner(char _owner, int pos);
};

#endif

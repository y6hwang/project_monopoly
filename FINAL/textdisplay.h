#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <sstream>
#include "view.h"

class TextDisplay : public View {

 public:
  TextDisplay();

  ~TextDisplay();


  virtual void notifyJoin(char player);
  virtual void notifyMove(char player, int pos, int prevpos);
  virtual void notifyImprov(int pos, bool buy);
  virtual void print() const ;
};

#endif

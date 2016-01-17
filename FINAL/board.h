#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
using namespace std;
//#include "nonproperty.h"
//#include "game.h"
class Game;

class Board{

protected:
  Game *game;
  string name;
  int purchaseCost;
  int improvCost;
  int TuitionFee;
  int improv;
  int improv4;
  int usefulImprov;
  bool prop;
  bool mortgaged;
  bool monopoly;
  char owner;
  string type;

  public:
    Board();
    ~Board();
    void setOwner(char _owner); // changing array;
    char getOwner();
    string getName();
    int getpurchaseCost();
    int getimprovCost();
    int getTuitionFee();
    void setTuitionFee(bool buy);
    void setFee(int fee);
    int getImprov();
    void setImprov(bool buy);
    bool getProp();
    bool getMortgaged();
    void setMortgaged(bool mortgage);
    bool getMonopoly();
    void setMonopoly(bool _monopoly);
    double getImproveSellCost();
    std::string getType();
};

#endif



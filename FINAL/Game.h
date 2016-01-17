#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "GameNotification.h"
#include "board.h"


class Game {
  protected:
  GameNotification notification;
  Board* board[40];
  //int curPlayer; 
  int rimsOut;
  public:
    Game();
    ~Game();
    void notifyLand();
    void notifyCollect();
    void notifyPay();
    void notifyTimLine();
    void notifyMove();
    bool notifyRimCup();

    Board* getBoard(int ind);

};

#endif

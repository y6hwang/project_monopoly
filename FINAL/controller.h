#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "GameNotification.h"
#include "Game.h"
#include "view.h"
#include "textdisplay.h"
class Bank;
class Player;
class Controller : public GameNotification {
    int curPlayer;
    int playerNum;
	protected:
    Game *game;
    View *td;
    Bank *bank;
    
    Player *players[8];
  public:
    Controller();
    ~Controller();
    int getplayerNum();
    void addPlayer(Player *p);
    void removePlayer(char player);
    void play();

    void notifyLand(int landed, bool doubledice);
    int notifySLC();
    int notifyNH();

    void notifyTrade(std::string name, std::string give, std::string receive);
    void notifyImprove(std::string property, std::string purpose);
    void notifyMortgage(std::string property);
    void notifyUnmortgage(std::string property);

    void getAsset(char player); // Assetlist from Game 
    void notifyCollect(char player, int amount); // to player
    void notifyTimLine(char player, int pMoney, int rimCups); // to bank
    void notifyPay(char player, int amount); // to player
    void notifyMove(char player, int prevPos, int pos); // to player
    void notifyOwnerChanged(char player, int propPos);
    void notifyAuction(char player, int propPos);
    void notifyLeaveTim(int landed);
    int getpMoney(char curPlayer);
    bool checkAsset(int owe);
};

#endif

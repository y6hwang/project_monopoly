#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include "controller.h"


class Bank {
	Controller *controller;

  public:
    Bank(Controller *c);
    ~Bank();

    void notifyLand(char player, int cost, int propPos, std::string building);
    void improveLand(char player, int cost, int propPos, std::string building, bool buy);
    void notifyLand(char owner, char player, bool mortgaged, int cost, std::string building);

    void Mortgage(char player, int pos, std::string building, int money);
    void Unmortgage(char player, int pos, std::string building, int money);

    void notifyTrade(char player, char offered, int money, string prop, int ind);
    void notifyTrade(char player, char offered, std::string gProp, std::string rProp, int ind1, int ind2);
    void notifyTrade(char player, char offered, std::string prop, int money, int ind);

    void notifyBankruptcy(char player, int *assetList, int numAsset, int owe);
    void notifyBankruptcy(char player, char receiver, int assetList[40], int numAsset, int owe);

    void notifyAuction(char plist[8], int mlist[8], string building, int propPos, char curPlayer);

    int notifyTimLine(char player, int pMoney, int rimCups, int turns);
    void notifyTuition(char player, int pMoney, int tWorth);
};

#endif

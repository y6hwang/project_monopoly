#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
//#include "controller.h"
class Controller;
class Player {
    std::string name;
    char c; 
    int pos, money, rimCups, prevPos, turnsLine;
    Controller* controller;

    public:
    Player(std::string _name, char _c);
    Player(std::string _name, char _c, int cup, int _money, int _pos);
    ~Player();
    void addPlayer(char c, int money, int rimCups, int prevPos);
    void setpos(int move);
    void setMoney(int amount);
    int getMoney();
    int getpos();
    int getPrevPos();
    std::string getName();
    int getLine();
    void setLine(bool plus);
    char getChar();
    void pay(int amount);
    int getrimCups();
    void setrimCups(bool plus);

};

#endif

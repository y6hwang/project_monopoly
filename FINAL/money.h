#ifndef MONEY_H
#define MONEY_H
#include <string>
#include <iostream>
#include "player.h"


class Money: public Player {
	static Money* instance;
	Money(std::string name, char c);
	Money(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Money* getInstance(std::string, char c);
  	static Money* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Money();
};

#endif

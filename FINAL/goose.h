#ifndef GOOSE_H
#define GOOSE_H

#include <string>
#include <iostream>
#include "player.h"


class Goose: public Player {
	static Goose* instance;
	Goose(std::string name, char c);
	Goose(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Goose* getInstance(std::string, char c);
  	static Goose* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Goose();
};

#endif


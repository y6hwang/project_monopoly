#ifndef LAPTOP_H
#define LAPTOP_H

#include <string>
#include <iostream>
#include "player.h"


class Laptop: public Player {
	static Laptop* instance;
	Laptop(std::string name, char c);
	Laptop(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Laptop* getInstance(std::string, char c);
  	static Laptop* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Laptop();
};

#endif


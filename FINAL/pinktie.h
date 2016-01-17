#ifndef PINKTIE_H
#define PINKTIE_H

#include <string>
#include <iostream>
#include "player.h"


class Pinktie: public Player {
	static Pinktie* instance;
	Pinktie(std::string name, char c);
	Pinktie(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Pinktie* getInstance(std::string, char c);
  	static Pinktie* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Pinktie();
};

#endif

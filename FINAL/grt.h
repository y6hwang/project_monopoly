#ifndef GRT_H
#define GRT_H

#include <string>
#include <iostream>
#include "player.h"


class Grt: public Player {
	static Grt* instance;
	Grt(std::string name, char c);

	Grt(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Grt* getInstance(std::string, char c);
  	static Grt* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Grt();
};

#endif


#ifndef THD_H
#define THD_H

#include <string>
#include <iostream>
#include "player.h"


class Thd: public Player {
	static Thd* instance;
	Thd(std::string name, char c);
	Thd(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Thd* getInstance(std::string, char c);
  	static Thd* getInstance(std::string name, char c, int cup, int _money, int _pos);
    //~Thd();
};

#endif

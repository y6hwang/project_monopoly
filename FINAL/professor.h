#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <string>
#include <iostream>
#include "player.h"


class Professor: public Player {
	static Professor* instance;
	Professor(std::string name, char c);
	Professor(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Professor* getInstance(std::string, char c);
  	static Professor* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Professor();
};

#endif

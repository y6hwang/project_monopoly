#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "player.h"


class Student: public Player {
	static Student* instance;
	Student(std::string name, char c);
	Student(std::string name, char c, int cup, int _money, int _pos);
	static void cleanup();
  public:
  	static Student* getInstance(std::string, char c);
  	static Student* getInstance(std::string, char c, int cup, int _money, int _pos);
    //~Student();
};

#endif

#include "student.h"

#include <cstdlib>

using namespace std;

Student* Student::instance = 0;

Student::Student(string name, char c): Player(name,c) {} // ctor
Student::Student(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Student::~Student(){}

Student* Student::getInstance(string name, char c) {
	if (!instance) {
		instance = new Student(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Student* Student::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Student(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Student::cleanup() {
	delete instance;
} // cleanup


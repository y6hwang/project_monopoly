#include "money.h"
#include <cstdlib>

using namespace std;

Money* Money::instance = 0;

Money::Money(string name, char c): Player(name,c) {} // ctor
Money::Money(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Money::~Money(){}

Money* Money::getInstance(string name, char c) {
	if (!instance) {
		instance = new Money(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Money* Money::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Money(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Money::cleanup() {
	delete instance;
} // cleanup


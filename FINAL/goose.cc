 #include "goose.h"

#include <cstdlib>

using namespace std;

Goose* Goose::instance = 0;

Goose::Goose(string name, char c): Player(name,c) {} // ctor
Goose::Goose(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Goose::~Goose(){}

Goose* Goose::getInstance(string name, char c) {
	if (!instance) {
		instance = new Goose(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Goose* Goose::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Goose(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Goose::cleanup() {
	delete instance;
} // cleanup


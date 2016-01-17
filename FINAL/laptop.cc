#include "laptop.h"
#include <cstdlib>

using namespace std;

Laptop* Laptop::instance = 0;

Laptop::Laptop(string name, char c): Player(name,c) {} // ctor
Laptop::Laptop(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Laptop::~Laptop(){}

Laptop* Laptop::getInstance(string name, char c) {
	if (!instance) {
		instance = new Laptop(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Laptop* Laptop::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Laptop(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Laptop::cleanup() {
	delete instance;
} // cleanup


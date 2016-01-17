#include "pinktie.h"

#include <cstdlib>

using namespace std;

Pinktie* Pinktie::instance = 0;

Pinktie::Pinktie(string name, char c): Player(name,c) {} // ctor
Pinktie::Pinktie(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Pinktie::~Pinktie(){}

Pinktie* Pinktie::getInstance(string name, char c) {
	if (!instance) {
		instance = new Pinktie(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Pinktie* Pinktie::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Pinktie(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Pinktie::cleanup() {
	delete instance;
} // cleanup


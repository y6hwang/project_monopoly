#include "thd.h"

#include <cstdlib>

using namespace std;

Thd* Thd::instance = 0;

Thd::Thd(string name, char c): Player(name,c) {} // ctor
Thd::Thd(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Thd::~Thd(){}

Thd* Thd::getInstance(string name, char c) {
	if (!instance) {
		instance = new Thd(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Thd* Thd::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Thd(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Thd::cleanup() {
	delete instance;
} // cleanup


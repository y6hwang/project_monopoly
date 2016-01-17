#include "professor.h"
#include <cstdlib>

using namespace std;

Professor* Professor::instance = 0;

Professor::Professor(string name, char c): Player(name,c) {} // ctor
Professor::Professor(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Professor::~Professor(){}

Professor* Professor::getInstance(string name, char c) {
	if (!instance) {
		instance = new Professor(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance

Professor* Professor::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Professor(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}

void Professor::cleanup() {
	delete instance;
} // cleanup


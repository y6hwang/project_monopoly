#include "grt.h"
#include <cstdlib>

using namespace std;

Grt* Grt::instance = 0;

Grt::Grt(string name, char c): Player(name,c) {} // ctor
Grt::Grt(std::string name, char c, int cup, int _money, int _pos): Player(name, c, cup, _money, _pos){};

//Grt::~Grt(){}

Grt* Grt::getInstance(string name, char c) {
	if (!instance) {
		instance = new Grt(name,c);
		atexit(cleanup);
	} // if
	return instance;
} // getinstance
Grt* Grt::getInstance(std::string name, char c, int cup, int _money, int _pos){
	if (!instance) {
		instance = new Grt(name, c, cup, _money, _pos);
		atexit(cleanup);
	} // if
	return instance;
}
void Grt::cleanup() {
	delete instance;
} // cleanup


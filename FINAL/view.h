#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <sstream>
using namespace std;

class View {

protected:
	string buildings[40];
  	char landed[40][8];
  	int improv[40];

public:
    View();


 virtual void notifyJoin(char player) = 0;
 virtual void notifyMove(char player, int pos, int prevpos) = 0;
 virtual void notifyImprov(int pos, bool buy) = 0;
 virtual void print() const = 0;

 virtual ~View() = 0;
};

#endif

#include "gym.h"
using namespace std; 

Gym::Gym(){
	purchaseCost = 150;
	type = "Gym";
}

void Gym::setOwner(char _owner){
	owner = _owner;
}

Gym::~Gym(){}


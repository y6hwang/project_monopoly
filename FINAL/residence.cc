#include "residence.h"
using namespace std;
Residence::Residence(){
	purchaseCost = 200;
	type = "Residence";
}
Residence::~Residence(){}

void Residence::setOwner(char _owner){
	owner = _owner;
}


#include "board.h"
using namespace std;

Board::Board(){
	game = NULL;
	name = "";
	purchaseCost = 0;
	improvCost = 0;
	improv = 0;
	TuitionFee = 0;
	improv4 = 0;
	usefulImprov = 0;
	prop = false;
	mortgaged = false;
	monopoly = false;
	owner = '\0';
	type = "";
}

Board::~Board(){}

char Board::getOwner(){
	return owner;
}

string Board::getName() {
	return name;
}

int Board::getpurchaseCost() {
	return purchaseCost;
}
int Board::getimprovCost() {
	return improvCost;
}
int Board::getTuitionFee() {
	return TuitionFee;
}

void Board::setOwner(char _owner){
	owner = _owner;
}

void Board::setTuitionFee(bool buy) {

	if (buy == true) {
		if (improv == 1) {
			TuitionFee *= 5;
		} else if (improv == 5) {
			int temp = TuitionFee;
			TuitionFee = usefulImprov;
			usefulImprov = temp;
		} else if (improv == 4) {
			int temp = TuitionFee;
			TuitionFee = improv4;
			improv4 = temp;
		} else {
			TuitionFee *= 3;
		}
	} else {
		if (improv == 0) {
			TuitionFee /= 5;
		} else if (improv == 4) {
			int temp = TuitionFee;
			TuitionFee = usefulImprov;
			usefulImprov = temp;
		} else if (improv == 3) {
			int temp = TuitionFee;
			TuitionFee = improv4;
			improv4 = temp;
		} else {
			TuitionFee /= 3;
		}
	}
}

void Board::setFee(int fee) {
	TuitionFee = fee;
}

int Board::getImprov() {
	return improv;
}

void Board::setImprov(bool buy) {
	if (buy > 0) ++improv;
	else --improv;
}
bool Board::getProp() {
	return prop;
}

bool Board::getMortgaged() {
	return mortgaged;
}
void Board::setMortgaged(bool mortgage) {
	mortgaged = mortgage;
}
bool Board::getMonopoly() {
	return monopoly;
}

void Board::setMonopoly(bool _monopoly) {
	monopoly = _monopoly;
}

double Board::getImproveSellCost() {
	return improvCost;
}

string Board::getType() {
	return type;
}



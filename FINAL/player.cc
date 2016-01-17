#include "player.h"
#include <string>
using namespace std;


Player::Player(string _name, char _c){
	name = _name;
	c = _c;
	money = 1500;
	pos = 0;
	prevPos = -1;
	turnsLine = 0;
	rimCups = 0;
}
Player::Player(string _name, char _c, int cup, int _money, int _pos){
	name = _name;
	c = _c;
	rimCups = cup;
	money = _money;
	prevPos = -1;
	pos = _pos;
	turnsLine = 0;
}

Player::~Player(){
}


void Player::setpos(int move){
	prevPos = pos;
	pos = pos + move;
	if (pos < 0) {
		pos += 40;
	}
}
int Player::getpos(){
	return pos;
}
int Player::getPrevPos(){
	return prevPos;
}
string Player::getName(){
	return name;
}
int Player::getLine(){
	return turnsLine;
}

void Player::setLine(bool plus){
	if (plus == true) ++turnsLine;
	else {
		turnsLine = 0;
	}
}

char Player::getChar(){
	return c;
}

void Player::setMoney(int amount){
	money = money + amount;
}

int Player::getMoney(){
	return money;
}

void Player::pay(int amount){
	money = money + amount;
}

int Player::getrimCups() {
	return rimCups;
}
void Player::setrimCups(bool plus) {
	if (plus == true) ++rimCups;
	else --rimCups;
}


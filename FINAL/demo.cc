#include "controller.h"
#include "player.h"
#include "professor.h"
#include "Laptop.h"
#include "Goose.h"
#include "Student.h"
#include "Money.h"
#include "Thd.h"
#include "Grt.h"
#include "Pinktie.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bank.h"

using namespace std;

Controller::Controller(){
	curPlayer = 0;
	game = new Game();
	bank = new Bank(this);
	playerNum = 0;
	td = new TextDisplay();
	for(int i = 0; i < 8; i++){
		players[i] = NULL;
	}
//td = NULL;
}


void Controller::addPlayer(Player *p){
	for(int i = 0; i < 8; i++){
		if(players[i] == NULL){
			players[i] = p;
			break;
		} else {}
	}
}

void Controller::play(){
	string cmd;
	bool initNum = false;
	bool goose = false;
	bool grt = false;
	bool tim = false;
	bool pro = false;
	bool stu = false;
	bool lap = false;
	bool mon = false;
	bool pink = false;
	bool rolled = false;
	string command;
	cout << "Enter the number of players: ";
	while (getline(cin, cmd)) {
		int numplayers;
		stringstream ss(cmd);
		bool first = false;
		if(!initNum){
			ss>>numplayers;
			while(numplayers < 2 || numplayers > 6){
				cout << "Number of players must be between 2-6" << endl;
				cout << "Re-enter the number of players : ";
				getline(cin, cmd);
				stringstream ss(cmd);
				ss >> numplayers;
			} // while
		} // if

		if(!initNum){
			for(int i = 1; i <= numplayers; i++){
				string name, character;
				cout << "Enter the name of " << i <<  " player: ";
				getline(cin, name);
				cout << endl;
				cout << "Choose the character that will represent player " << name << ": " << endl;

				if(!goose)
					cout << "Goose" << endl;
				if(!grt)
					cout << "GRT Bus" << endl;
				if(!tim)
					cout << "Tim Hortons Doughnuts" << endl;
				if(!pro)
					cout << "Professor" << endl;
				if(!stu)
					cout << "Student" << endl;
				if(!mon)
					cout << "Money" << endl;
				if(!lap)
					cout << "Laptop" << endl;
				if(!pink)
					cout << "Pinktie" << endl;

				cout << endl;
				getline(cin, character);
				char _c;

				while((character != "Goose" &&
					character != "GRT Bus" && 
					character != "Tim Hortons Doughnuts" &&
					character != "Professor" && 
					character != "Student" && 
					character != "Money" && 
					character != "Laptop" &&
					character != "Pinktie") ||
					((character == "Goose" && goose) ||
						(character == "GRT Bus" && grt) ||
						(character == "Tim Hortons Doughnuts" && tim) ||
						(character == "Professor" && pro) || 
						(character == "Student" && stu) || 
						(character == "Money" && mon) ||
						(character == "Laptop" && lap) ||
						(character == "Pinktie" && pink))) {

					cout << "Choose the character that will represent " << name << " player: " << endl;

					if(!goose)
						cout << "Goose" << endl;
					if(!grt)
						cout << "GRT Bus" << endl;
					if(!tim)
						cout << "Tim Hortons Doughnuts" << endl;
					if(!pro)
						cout << "Professor" << endl;
					if(!stu)
						cout << "Student" << endl;
					if(!mon)
						cout << "Money" << endl;
					if(!lap)
						cout << "Laptop" << endl;
					if(!pink)
						cout << "Pinktie" << endl;
					cout << endl;
					getline(cin, character);

		  		} // while

		  		Player *temp;

		  		if(character == "Goose"){
		  			_c = 'G';
		  			goose = true;
		  			temp = Goose::getInstance(name, _c);

		  		} else if (character == "GRT Bus") {
		  			_c = 'B';
		  			grt = true;
		  			temp = Grt::getInstance(name, _c);
		  		} else if (character == "Tim Hortons Doughnuts") {
		  			_c = 'D';
		  			tim = true;
		  			temp = Thd::getInstance(name, _c);
		  		} else if (character == "Professor") {
		  			_c = 'P';
		  			pro = true;
		  			temp = Professor::getInstance(name, _c);
		  		} else if (character == "Student") {
		  			_c = 'S';
		  			stu = true;
		  			temp = Student::getInstance(name, _c);
		  		} else if (character == "Money") {
		  			_c = '$';
		  			mon = true;
		  			temp = Money::getInstance(name, _c);
		  		} else if (character == "Laptop") {
		  			_c = 'L';
		  			lap = true;
		  			temp = Laptop::getInstance(name, _c);
		  		} else {
		  			_c = 'T';
		  			pink = true;
		  			temp = Pinktie::getInstance(name, _c);
		  		}

		  		++playerNum;
		  		addPlayer(temp);
		  		td->notifyJoin(temp->getChar());
		  		cout << endl;

	  		} // for


	  		initNum = true;
	  		cout << "Done registering all players" << endl;
	  		td->print();
	  		cout << endl << "====================START====================" << endl << endl;
	  		cout << "All players begin with $1500" << endl;

	  		for(int i = 0; i < playerNum; i++){
	  			cout << players[i]->getName() << "'s character: " << players[i]->getChar() << endl;
			} // for

			cout << endl << players[curPlayer]->getChar() << "'s turn. Roll the Dice (type roll)" << endl << endl;

		} else {
			ss >> command;
		} // if

		if (command == "roll") {
			Roll();
		} else if (cmd == "next") {
			rolled = false; 
			curPlayer = (curPlayer + 1) % playerNum;
			cout << players[curPlayer]->getChar() << "' turn:" << endl;
		} else if (cmd == "trade") {
			Trade(); // if
		} else if (cmd == "improve") {
			string property, purpose;
			cin >> property >> purpose;
			if(purpose == "buy"){

			} else if(purpose == "sell"){

			}
		} else if (cmd == "mortgage") {
			string property;
			cin >> property;
		} else if (cmd == "unmortgage") {
			string property;
			cin >> property;
		} else if (cmd == "bankrupt") {
		} else if (cmd == "assets") {
			cout << "You have: ";
			for(int i = 0; i < 40; i++){
				if(game->getBoard(i)->getProp()){
					if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
						cout << game->getBoard(i)->getName() << " ";
					} else{}
				}
			}
			cout << endl;
		} else if (cmd == "save") {

		}
	}
}

void Controller::Roll() {
	int dice1;
	int dice2;
	int total;
	int num;
	bool demo1 = false;
	bool demo2 = false;
	if(rolled){
		cout << "You can't roll twice" << endl;
	} else {
		while(ss>>num) {
			if(!demo1){
				dice1 = num;
				demo1 = true;
			} else if(!demo2){
				dice2 = num;
				demo2 = true;
			} // if
		}  // while

		if(demo1 && demo2){
			total = dice1 + dice2;
		} else {
			srand(time(NULL));
			dice1 = rand() % 6 + 1;
			srand(rand());
			dice2 = rand() % 6 + 1;
			total = dice1 + dice2;
		} // if

		rolled = true;
		players[curPlayer]->setpos(total);
		int landed = players[curPlayer]->getpos();

		if (players[curPlayer]->getPrevPos() > landed && landed != 0 ){
			players[curPlayer]->pay(150);
		}

		td->notifyMove(players[curPlayer]->getChar(), players[curPlayer]->getpos(), players[curPlayer]->getPrevPos());
		td->print();
		cout << endl << "First dice: " << dice1 << endl;
		cout << "Second dice " << dice2 << endl << endl;
		cout << "==== Landed on " << game->getBoard(landed)->getName() << " ===" << endl << endl;
		cout << "Currently have " << players[curPlayer]->getMoney() << endl << endl;

		command = "";

		if(game->getBoard(landed)->getProp()){
			if(game->getBoard(landed)->getOwner() == '\0'){
				bank->notifyLand(players[curPlayer]->getChar(), game->getBoard(landed)->getpurchaseCost(), landed, game->getBoard(landed)->getName());
			} else if(game->getBoard(landed)->getOwner() == players[curPlayer]->getChar()){
				bank->notifyLand(players[curPlayer]->getChar(), game->getBoard(landed)->getMonopoly(),
					game->getBoard(landed)->getMortgaged(), game->getBoard(landed)->getimprovCost(), landed, game->getBoard(landed)->getName());
			} else {
				bank->notifyLand(game->getBoard(landed)->getOwner(), players[curPlayer]->getChar(), 
					game->getBoard(landed)->getMortgaged(), game->getBoard(landed)->getTuitionFee(), game->getBoard(landed)->getName());
			} // if
		} else {
			if(landed == 0){
				players[curPlayer]->pay(150);
			} else if(landed == 20){
				cout << "You are are attacked by a flock of nesting geese" << endl; 
			} else if(landed == 10){

				int pMoney = players[curPlayer]->getMoney();
				int rimCups = players[curPlayer]->getrimCups();
				int turns = players[curPlayer]->getLine();
				int result = bank->notifyTimLine(players[curPlayer]->getChar(),pMoney,rimCups,turns);

				if (result == -13) {
					cout << "Nothing Happens" << endl;
				} else if (result == 0) {
					int numAsset = 0;

					for (int i = 0; i < 40; i++) {
						if(game->getBoard(i)->getProp()){
							if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
								++numAsset;
							}
						}
					}

					int assetList[40];
					int j = 0;
					for (int i = 0; i < 40; i++) {
						if(game->getBoard(i)->getProp()){
							if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
								assetList[j] = i;
								j++;
							}
						}
					}
					for (int i = j; i < 40; i++) {
						assetList[i] = -1;
					}

					bank->notifyBankruptcy(players[curPlayer]->getChar(), assetList, numAsset);
					players[curPlayer]->setLine(false);

				} else if (result == -1) {
					players[curPlayer]->setLine(true);
				} else if (result < 0) {
					players[curPlayer]->setrimCups(false);
					int newlanded = landed + (result * -1);
					td->notifyMove(players[curPlayer]->getChar(),newlanded,landed);
					landed = newlanded;
					td->print();
				} else if (result > 0) {
					players[curPlayer]->setLine(false);
					players[curPlayer]->pay(result*-1);
				} else {
					cout << "ERROR" << endl;
				}

			} else if(landed == 30){
				cout << "You are going to DC Tim Line! " << endl;
				players[curPlayer]->setpos(10);

			} else if(landed == 2 || landed == 17 || landed == 33){
				int move = notifySLC();
				cout << "You have landed on SLC." << endl;
				if (landed+move < 0) {
					move = 40 + landed + move;
				}
				string fDest = game->getBoard(landed+move)->getName();
				cout << "You moved " << move << " and landed on " << fDest << endl;

				td->notifyMove(players[curPlayer]->getChar(),landed+move,landed);
				landed = landed+move;

				players[curPlayer]->setpos(landed);
				td->print();
			} else if(landed == 4){
				int pMoney = players[curPlayer]->getMoney();
				int tWorth = pMoney;

				for (int i = 0; i < 40; i++) {
					if(game->getBoard(i)->getProp()){
						if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
							tWorth += game->getBoard(i)->getpurchaseCost();
						} 
					}
				}
				tWorth = tWorth / 10;
				cout << "You have to pay Tuition Fee." << endl;
				bank->notifyTuition(players[curPlayer]->getChar(), pMoney,tWorth);
			} else if(landed == 7 || landed == 22 || landed == 36){
				int money = notifyNH();
				cout << "You have landed on NH" << endl;
				if (money > 0) {
					cout << "You have earned " << money << endl;
				} else {
					cout << "You have lost " << money << endl;
				}
				notifyPay(players[curPlayer]->getChar(), money);
			} else if(landed == 38){
		  // COOP FEE
				cout << "You have to pay your Co-op Fee ($150)!" << endl;
				players[curPlayer]->pay(-150);

			} else {
				cout << "ERROR" << endl;
			}
		}
	}
}

void Controller::Trade() {

	string name, give, receive, comm;
	int numgive, numreceive;
	bool valname = false;
	bool valgive = false;
	bool valreceive = false;
	bool numg = false;
	bool numr = false;
	bool propgive = false;
	bool propreceive = false;
	char offerto;
	for(int i = 0; i < playerNum; i++){
		if(players[i]->getName() == name){
			offerto = players[i]->getChar();
		}
	}

	ss >> name;
	if(ss >> numgive){
		numg = true;
		valgive = true;
	} else if(ss >> give) {
		propgive = true;
	}
	if(ss >> numreceive){
		numr = true;
		valreceive = true;
	} else if(ss >> receive) {
		propreceive = true;
	}

	for(int i = 0; i < playerNum; i++){
		if((players[i]->getName() == name) && (players[curPlayer]->getName() != name)){
			valname = true;
		}
	}
	if(propgive){
		for(int i = 0; i < 40; i++){
			if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar() && game->getBoard(i)->getName() == give){
				valgive = true;
			}
		} //for
	} // if
	
	if(propreceive){
	  	for(int i = 0; i < 40; i++){
	  		if((game->getBoard(i)->getName() == name) && (game->getBoard(i)->getName() == receive)){
	  			valreceive = true;
	  		}
	  	}	
	}

	if(numg && numr){
	  	cout << "Can't trade money with money" << endl;
	} else if(valgive && valname && valreceive){


		if(propgive && propreceive){
			  // trade Nomair DC MC
			int ind1 = -1;
			int ind2 = -1;
			for (int i = 0; i < 40; i++) {
				if (game->getBoard(i)->getName() == give) {
					ind1 = i;
					break;
				}
			}
			for (int i = 0; i < 40; i++) {
				if (game->getBoard(i)->getName() == receive) {
					ind2 = i;
					break;
				}
				bank->notifyTrade(players[curPlayer]->getChar(), offerto, give, receive, ind1, ind2);
			} else if(propgive && numreceive){
			  // trade Nomair DC 500
				int ind = -1;
				for (int i = 0; i < 40; i++) {
					if (game->getBoard(i)->getName() == give) {
						ind = i;
						break;
					}
				}
	  			bank->notifyTrade(players[curPlayer]->getChar(), offerto, give, numreceive, ind);
	  		} else if(propreceive && numgive){
			  // trade Nomair 500 DC
	  			int ind = -1;
	  			for (int i = 0; i < 40; i++) {
	  				if (game->getBoard(i)->getName() == give) {
	  					ind = i;
	  					break;
	  				}
	  			}
	  			bank->notifyTrade(players[curPlayer]->getChar(), offerto, numgive, receive, ind);
	  		}
	  	}
	}
}

void Controller::notifyPay(char player, int amount){
	for(int i = 0; i < playerNum; i++){
		if(players[i]->getChar() == player){
			players[i]->pay(amount);
		} else{}
	}
}

void Controller::notifyImprove(int propPos){
	game->getBoard(propPos)->setImprov(true);
}

void Controller::notifyOwnerChanged(char player, int propPos){
	game->getBoard(propPos)->setOwner(player, propPos);
	cout << endl << "You bought " << game->getBoard(propPos)->getName() << endl << endl;
	cout << "Enter one of the followings to continue the game:" << endl;
	cout << "[next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl;
/*cout << "------------------------------" << endl;
cout << "|next                        |" << endl;
cout << "|assets                      |" << endl;
cout << "|trade                       |" << endl;
cout << "|improve                     |" << endl;
cout << "|mortgage                    |" << endl;
cout << "|unmortgage                  |" << endl;
cout << "------------------------------" << endl;*/

}

void Controller::notifyAuction(char player, int propPos){
	string building = game->getBoard(propPos)->getName();
	char plist[8];
	int i = 0;
	while (players[i] != NULL) {
		plist[i] = players[i]->getChar();
		++i;
	}

	for (int j = i; j < 8; j++) {
		plist[j] = 'n';
	}

	i = 0;
	int mlist[8];
	while (players[i] != NULL) {
		mlist[i] = players[i]->getMoney();
		++i;
	}

	for (int j = i; j < 8; j++) {
		mlist[j] = -1;
	}

	bank->notifyAuction(plist,mlist,building,propPos,player);
}



int Controller::notifySLC() {
	int move[24];
	for (int i = 0; i < 3; i++) {
		move[i] = -3;
	}
	for (int i = 3; i < 7; i++) {
		move[i] = -2;
	}
	for (int i = 7; i < 11; i++) {
		move[i] = -1;
	}
	for (int i = 11; i < 14; i++) {
		move[i] = 1;
	}
	for (int i = 14; i < 18; i++) {
		move[i] = 2;
	}
	for (int i = 18; i < 22; i++) {
		move[i] = 3;
	}
move[22] = -1; // TIMS LINE;
move[23] = -2; // COLLECT OSAP;

srand(time(NULL));
int random_int = rand() % 24 + 1;

return move[random_int];
}
int Controller::notifyNH() {
	int money[18];
	money[0] = -200;

	for (int i = 1; i < 3; i++) {
		money[i] = -100;
	}
	for (int i = 3; i < 6; i++) {
		money[i] = -50;
	}
	for (int i = 6; i < 12; i++) {
		money[i] = 25;
	}
	for (int i = 12; i < 15; i++) {
		money[i] = 50;
	}
	for (int i = 15; i < 17; i++) {
		money[i] = 100;
	}
	money[17] = 200;


	srand(time(NULL));
	int random_int = rand() % 18 + 1;

	return money[random_int];
}

Controller::~Controller(){

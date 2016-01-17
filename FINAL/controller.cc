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
#include <fstream>
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

int Controller::getplayerNum() {
	return playerNum;
}

void Controller::addPlayer(Player *p){
	for(int i = 0; i < 8; i++){
		if(players[i] == NULL){
			players[i] = p;
			break;
		} else {}
	}
}

void Controller::removePlayer(char player) {
	for (int i = 0; i < 8; i++) {
		if (players[i]->getChar() == player) {
			Player *temp = players[i];
			players[i] = NULL;
			delete temp;
			--playerNum;
			break;
		}
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
	bool doubledice = false;
	bool beginning = true;

	int count = 0;
	string command;
	

	// load
	string option;
	cout << endl << "====== Let's play Monopoly =====" << endl << endl;
	cout << "If you want to load a game, type 1" << endl;
	cout << "If you want to start a new game, type 2" << endl << endl;
	cin >> option;
	while(option != "1" && option != "2"){
		cout << option << endl;
		cout << "Type 1 or 2" << endl;
		cin >> option;
	}
	cin.ignore();
	if(option == "1"){
		initNum = true;
		string filename;
		string line, num;
		bool stuck = false;
		cout << "Enter the name of the file" << endl;
		cin >> filename;
		ifstream infile;
		infile.open (filename);
		getline(infile, num);
		istringstream(num) >> playerNum;
		for(int i = 0; i < playerNum; i++){
			string name;
			char character;
			int rollcup, money, pos, stucknum, lineturn;
			getline(infile, line);
			istringstream word(line);
			word >> name >> character >> rollcup >> money >> pos;
			if(word >> stucknum){
				if(stucknum == 1){
					stuck = true;
					word >> lineturn;
				}
			}
			Player *temp = NULL;
			if(character == 'G'){
				temp = Goose::getInstance(name, character, rollcup, money, pos);
			} else if (character == 'B') {
				temp = Grt::getInstance(name, character, rollcup, money, pos);
			} else if (character == 'D') {
				temp = Thd::getInstance(name, character, rollcup, money, pos);
			} else if (character == 'P') {
				temp = Professor::getInstance(name, character, rollcup, money, pos);
			} else if (character == 'S') {
				temp = Student::getInstance(name, character, rollcup, money, pos);
			} else if (character == '$') {
				temp = Money::getInstance(name, character, rollcup, money, pos);
			} else if (character == 'L') {
				temp = Laptop::getInstance(name, character, rollcup, money, pos);
			} else if (character == 'T') {
				temp = Pinktie::getInstance(name, character, rollcup, money, pos);
			}

			td->notifyJoin(character);
			td->notifyMove(character, pos, 0);
			if(stuck){
				temp->setLine(lineturn+1);
				stuck = false;
			}
			addPlayer(temp);
			
		} // for
		

		while(getline(infile, line)){
			string property, owner;
			int improve;
			stringstream word(line);
			word >> property >> owner >> improve;
			char _owner;
			for(int i = 0; i < playerNum; i++){
				if(players[i]->getName() == owner){
					_owner = players[i]->getChar();
					break;
				} else if(owner == "BANK"){
					_owner = '\0';
					break;
				} 
			}
			for(int i = 0; i < 40; i++){
				if(game->getBoard(i)->getName() == property){
					game->getBoard(i)->setOwner(_owner);
					if(improve < 0){
						game->getBoard(i)->setMortgaged(true);
						td->notifyImprov(i, false);
					} else {
						for(int x = 0; x < improve; x++){
							game->getBoard(i)->setImprov(true);
							td->notifyImprov(i, true);
							game->getBoard(i)->setTuitionFee(true);
						}
					}  break;
				}
			}
		}
		infile.close();
		td->print();
		cout << endl << players[curPlayer]->getChar() << "'s turn. Roll the Dice (type roll)" << endl << endl;
	}

	if(!initNum){
	cout << "Enter the number of players: ";
	}
	while (getline(cin, cmd)) {
		int numplayers;
		stringstream ss(cmd);
		//bool first = false;
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
				cout << "Enter the name of player " << i << ": ";
				getline(cin, name);
				cout << endl;
				cout << "Choose the character that will represent player " << name << ": " << endl;

				
				if(!goose)
					cout.fill(' ');
					cout.width(20);
					cout << left <<"[Goose]";
				if(!grt)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[GRT Bus]";
				if(!tim)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[Tim Hortons Doughnuts]";

				cout << endl;

				if(!pro)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[Professor]";
				if(!stu)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[Student]";
				if(!mon)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[Money]";

				cout << endl;

				if(!lap)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[Laptop]";
				if(!pink)
					cout.fill(' ');
					cout.width(20);
					cout << left << "[Pinktie]";
				cout << endl;

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
						cout.fill(' ');
						cout.width(20);
						cout << left <<"[Goose]";
					if(!grt)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[GRT Bus]";
					if(!tim)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[Tim Hortons Doughnuts]";

					cout << endl;

					if(!pro)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[Professor]";
					if(!stu)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[Student]";
					if(!mon)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[Money]";

					cout << endl;

					if(!lap)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[Laptop]";
					if(!pink)
						cout.fill(' ');
						cout.width(20);
						cout << left << "[Pinktie]";
					cout << endl;

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

			cout << endl << players[curPlayer]->getChar() << "'s turn. Roll the Dice. Type [roll]." << endl << endl;

		} else {
			ss >> command;
		} // if

		int landed = players[curPlayer]->getpos();
		if(doubledice){
			// cout << endl << "=== Double dice roll again ===" << endl << endl;

		} else if (!beginning && (command == "assets" || command == "improve" || command == "trade" || command == "mortagage" || command == "unmortgage")){

		} else {
			if ((!beginning && rolled) && (command == "roll")) {
				cout << "==== You can't roll twice ====" << endl;
			}
			else if ((players[curPlayer]->getLine() > 0) && (command == "roll")) {
				cout << "==== You are stuck in DC Tim Line. Not allowed to roll! ====" << endl;
			}
			cout << "==== Enter one of the followings to continue the game ====" << endl;
			cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
		} 
		if (command == "roll") {
			beginning = false;
			int dice1;
			int dice2;
			int total;
			int num;
			bool demo1 = false;
			bool demo2 = false;
			if(rolled){
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
					if(dice1 == dice2){
						doubledice = true;
						++count; 
					} else {
						doubledice = false;
						rolled = true;
					}
					total = dice1 + dice2;
				} else {
					srand(time(NULL));
					dice1 = rand() % 6 + 1;
					srand(rand());
					dice2 = rand() % 6 + 1;
					if(dice1 == dice2){
						++count; 
						doubledice = true;
					} else {
						doubledice = false;
						rolled = true;
					}

					total = dice1 + dice2;
	  			} // if



		  		if(count == 3){
		  			players[curPlayer]->setpos(10-landed);
					td->notifyMove(players[curPlayer]->getChar(),10,players[curPlayer]->getPrevPos());
					players[curPlayer]->setLine(true);
					td->print();
					cout << endl << "=== Double dice three times in a row! Go to Tims and rest ===" << endl;
					cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
					cout << "[next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
					count = 1;
					rolled = true;
					doubledice = false;

		  		} else {
	  				if(doubledice && count < 3){
	  				} else {
	  					rolled = true; 
	  				}

	  				players[curPlayer]->setpos(total);
	  				landed = players[curPlayer]->getpos();
						
						if(players[curPlayer]->getPrevPos() > landed && landed != 0 ){
	  					players[curPlayer]->pay(150);
	  				}

	  				command = "";
	  				td->notifyMove(players[curPlayer]->getChar(), players[curPlayer]->getpos(), players[curPlayer]->getPrevPos());
	  				td->print();

	  				cout << endl << "First dice: " << dice1 << endl;
	  				cout << "Second dice " << dice2 << endl << endl;
	  				notifyLand(landed, doubledice);
		  		}
		  			
	  		}	

		  	
		} else if (cmd == "next") {

			if ((!rolled) && (players[curPlayer]->getLine() < 0)) {
				cout << endl;
				cout << "==== You still have chance to roll! Please enter [roll].====" << endl;
				cout << endl;
			} else { 
				int nextPlayer = -1;
				for (int i = curPlayer+1; i < 8; i++) {
					if (players[i] != NULL) {
						nextPlayer = i;
						break;
					}
				}
				
				if (nextPlayer == -1) {
					for (int i = 0; i < curPlayer; i++) {
						if (players[i] != NULL) {
							nextPlayer = i;
							break;
						}
					}
					
				}

				if (nextPlayer == -1) {
					cout << "Congratualation! You have won the game!" << endl;
					cout << "Enter quit to end the game" << endl;
				}

				curPlayer = nextPlayer;

				if (players[curPlayer]->getLine() > 0) {
					
					cout << players[curPlayer]->getChar() << "' turn:" << endl;
					cout << "You are stuck in DC Tim Line" << endl;
					int pMoney = players[curPlayer]->getMoney();
					int rimCups = players[curPlayer]->getrimCups();
					int turns = players[curPlayer]->getLine();
					int result = bank->notifyTimLine(players[curPlayer]->getChar(),pMoney,rimCups,turns);

					if (result == 0) { // bankruptcy
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

						bank->notifyBankruptcy(players[curPlayer]->getChar(), assetList, numAsset,50);
						players[curPlayer]->setLine(false);

					} else if (result == -1) { // fail to get out
						players[curPlayer]->setLine(true);

					} else if (result < 0) { // used rim cups
						players[curPlayer]->setrimCups(false);
						players[curPlayer]->setLine(false);
						int newlanded = landed + (result * -1);
						td->notifyMove(players[curPlayer]->getChar(),newlanded,landed);
						landed = newlanded;
						td->print();
						notifyLand(newlanded, false);

					} else if (result > 0) { // get by paying or roll doubles
						int move = result;
						int landed = players[curPlayer]->getpos();
						players[curPlayer]->setLine(false);
						int newlanded = landed + move;
						td->notifyMove(players[curPlayer]->getChar(),newlanded,landed);
						players[curPlayer]->setpos(landed);
						
						td->print();
		
						notifyLand(newlanded, false);
					} else {
						cout << "ERROR" << endl;
					}
			
				} else {
					count = 0;
					rolled = false; 
					curPlayer = nextPlayer;
					cout << players[curPlayer]->getChar() << "' turn:" << endl;
				}
			}
		} else if (command == "trade") {
			command = "";
			string name, give, receive, comm;
			ss >> name;
			ss >> give;
			ss >> receive;
			notifyTrade(name,give,receive);

		} else if (command == "improve") {
		  	command = "";
		  	string property, purpose;
		  	ss >> property >> purpose;
		  	notifyImprove(property, purpose);





		} else if (command == "mortgage") {
		  	command = "";
		  	string property;
		  	ss >> property;

		  	notifyMortgage(property);
		  	
		} else if (command == "unmortgage") {
		  	command = "";
		  	string property;
		  	ss >> property;

		  	notifyUnmortgage(property);
		  	
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
			cout << endl << "Money: $" << players[curPlayer]->getMoney() << endl;
			cout << endl;
			cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
			cout << "[next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;

		} else if (command == "save"){
			ofstream output("bb7kSave.txt");
			output << playerNum << endl;

			for(int i = 0; i < playerNum; i++){
				string name;
				char character;
				int rim, money, position, line;
				name = players[i]->getName();
				character = players[i]->getChar();
				rim = players[i]->getrimCups();
				money = players[i]->getMoney();
				position = players[i]->getpos();
				line = players[i]->getLine();
				if(position != 10){
					output << name << " " << character << " " << rim << " " << money << " " << position << endl;
				} else if(position == 10){
					if(line == 0){
						output << name << " " << character << " " << rim << " " << money << " " << position << " " << 0 << endl;
					} else {
						output << name << " " << character << " " << rim << " " << money << " " << position << " " << 1 << " " << (line-1) << endl;
					}
				} else {}
			}
			for(int i = 0; i < 40; i++){
				if(game->getBoard(i)->getProp()){
					char _owner;
					string property, owner;
					int imp;
					property = game->getBoard(i)->getName();
					_owner = game->getBoard(i)->getOwner();
					if(game->getBoard(i)->getMortgaged()){
						imp = -1;
					} else {
						imp = game->getBoard(i)->getImprov();
					}
					if(_owner == '\0'){
						owner = "BANK";
					} else {
						for(int i = 0; i < playerNum; i++){
							if(players[i]->getChar() == _owner){
								owner = players[i]->getName();
								break;
							}
						}
					}	
					output << property << " " << owner << " " << imp << endl;
				}
			}
			output.close();
			cout << endl << "Save complete, filename: bb7kSave.txt" << endl;
		} else if (command == "quit"){
			break;
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

void Controller::notifyOwnerChanged(char player, int propPos){
	if (player != '\0') {
		game->getBoard(propPos)->setOwner(player);
		cout << endl << player << " now have " << game->getBoard(propPos)->getName() << endl << endl;
	}
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
	move[22] = 4; // TIMS LINE;
	move[23] = 5; // COLLECT OSAP;

	srand(time(NULL));
	int random_int = rand() % 24;

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
	int random_int = rand() % 18;

	return money[random_int];
}



void Controller::notifyLand(int landed, bool doubledice) {
	cout << "==== Landed on " << game->getBoard(landed)->getName() << " ===" << endl << endl;
	cout << "Currently have $" << players[curPlayer]->getMoney() << endl << endl;

	if(game->getBoard(landed)->getProp()){
		if(game->getBoard(landed)->getOwner() == '\0'){
			if (players[curPlayer]->getMoney() < game->getBoard(landed)->getpurchaseCost()) {
				cout << "You do not have enough money to purchas this building!" << endl;
			} else {
				bank->notifyLand(players[curPlayer]->getChar(), game->getBoard(landed)->getpurchaseCost(), landed, game->getBoard(landed)->getName());
			}
		} else if(game->getBoard(landed)->getOwner() == players[curPlayer]->getChar()){
				cout << "This is your property" << endl;
		} else {
			if(landed == 12){
				 //pac
				string rolldice;
				cout << "Roll dice to set price (roll)" << endl;
				cin >> rolldice;
				int total;
				while(rolldice != "roll"){
					cout << "Type roll" << endl;
					cin >> rolldice;
				}
				srand(time(NULL));
    			int dice1 = rand() % 6 + 1;
    			srand(rand());
    			int dice2 = rand() % 6 + 1;
    			total = dice1 + dice2;
    			cout << endl << "First dice :" << dice1 << endl;
    			cout << "Second dice :" << dice2 << endl;
				char payto = game->getBoard(landed)->getOwner();

				if(game->getBoard(28)->getOwner() == payto){
					game->getBoard(landed)->setFee(total*10);
				} else {
					game->getBoard(landed)->setFee(total*4);
				}
			} else if(landed == 28){
				string rolldice;
				cout << "Roll dice to set price (roll)" << endl;
				cin >> rolldice;
				int total;
				while(rolldice != "roll"){
					cout << "Type roll" << endl;
					cin >> rolldice;
				}
				srand(time(NULL));
    			int dice1 = rand() % 6 + 1;
    			srand(rand());
    			int dice2 = rand() % 6 + 1;
    			total = dice1 + dice2;
    			cout << endl << "First dice :" << dice1 << endl;
    			cout << "Second dice :" << dice2 << endl;
				char payto = game->getBoard(landed)->getOwner();

				if(game->getBoard(12)->getOwner() == payto){
					game->getBoard(landed)->setFee(total*10);
					
				} else {
					game->getBoard(landed)->setFee(total*4);
					
				}

			} else if (game->getBoard(landed)->getType() == "Residence"){
				int quantity = 0;
				char payto = game->getBoard(landed)->getOwner();
				for(int i = 0; i < 40; i++){
					if(game->getBoard(i)->getType() == "Residence" && game->getBoard(i)->getOwner() == payto){
						++quantity;
					}
				}
				if(quantity == 1){
					game->getBoard(landed)->setFee(25);
				} else if(quantity == 2){
					game->getBoard(landed)->setFee(50);
				} else if(quantity == 3){
					game->getBoard(landed)->setFee(100);
				} else if(quantity == 4){
					game->getBoard(landed)->setFee(200);
				} else {
					cout << "INVALID RES" << endl;
				}
			}
			//cout << "You need to pay $" << game->getBoard(landed)->getTuitionFee() << endl;
			if (players[curPlayer]->getMoney() < game->getBoard(landed)->getTuitionFee()) {
				int fee = game->getBoard(landed)->getTuitionFee();
				int assetList[40];
				int numAsset;
				int j = 0;
				for (int i = 0; i < 40; i++) {
					if (players[curPlayer]->getChar() == game->getBoard(i)->getOwner()) {
						assetList[j] = i;
						j++;
					}
				}
				numAsset = j;
				for (int i = j; i < 40; i++) {
					assetList[j] = -1;
				}

				bank->notifyBankruptcy(players[curPlayer]->getChar(),assetList,numAsset,fee);
			} else {
				bank->notifyLand(game->getBoard(landed)->getOwner(), players[curPlayer]->getChar(), 
				game->getBoard(landed)->getMortgaged(), game->getBoard(landed)->getTuitionFee(), game->getBoard(landed)->getName());
			}
		} // if
	} else {
		if(landed == 0){
			cout << "Collecting OSAP ($200)!" << endl;
			players[curPlayer]->pay(200);
		} else if(landed == 20){
			cout << "You are are attacked by a flock of nesting geese" << endl; 
		} else if(landed == 10){
		// Tim Line
			if (players[curPlayer]->getLine() == 0) {
				cout << "Nothing happens!" << endl;
				if (!doubledice) {
					cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
					cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
				}
			 } 
		} else if(landed == 30){
			cout << "You are going to DC Tim Line! Please enter [next]" << endl;
			doubledice = false;
			players[curPlayer]->setpos(-20);
			td->notifyMove(players[curPlayer]->getChar(),10,30);
			players[curPlayer]->setLine(true);
		} else if(landed == 2 || landed == 17 || landed == 33){
			int move = -3;
			//int move = notifySLC();
			if (move == 4) { // Tims Line
				cout << "Going to DC Tim Line!" << endl;
				doubledice = false;
				players[curPlayer]->setpos(10-landed);
				players[curPlayer]->setLine(true);
			} else if (move == 5) { // Collect Osap
				cout << "Going to collect OSAP!" << endl;
				players[curPlayer]->setpos(-landed);
			} else {
				//cout << "You have landed on SLC." << endl;
				int pos = (landed + move) % 40;
				string fDest = game->getBoard(pos)->getName();
				cout << "You moved " << move << " and landed on " << fDest << endl;

				players[curPlayer]->setpos(move);
			}

			td->notifyMove(players[curPlayer]->getChar(),players[curPlayer]->getpos(),players[curPlayer]->getPrevPos());

			td->print();

			notifyLand(players[curPlayer]->getpos(), doubledice);

		} else if(landed == 4){
			int pMoney = players[curPlayer]->getMoney();
			int tWorth = pMoney;
			for (int i = 0; i < 40; i++) {
				if(game->getBoard(i)->getProp()){
					if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
						tWorth += game->getBoard(i)->getpurchaseCost();
						tWorth += (game->getBoard(i)->getimprovCost()) * game->getBoard(i)->getImprov();
					} 
				}
			}
			tWorth = tWorth / 10;

			if ((pMoney < 300) && (pMoney < tWorth)) {
				cout << "You do not have enough money to pay Tuition!" << endl;
				int assetList[40];
				int numAsset;
				int j = 0;
				for (int i = 0; i < 40; i++) {
					if (players[curPlayer]->getChar() == game->getBoard(i)->getOwner()) {
						assetList[j] = i;
						j++;
					}
				}
				numAsset = j;
				for (int i = j; i < 40; i++) {
					assetList[j] = -1;
				}
				int owe;
				if (300 < tWorth) owe = 300;
				else owe = tWorth;

				bank->notifyBankruptcy(players[curPlayer]->getChar(),assetList,numAsset,owe);
			} else {
				cout << "You have to pay Tuition Fee." << endl;
				bank->notifyTuition(players[curPlayer]->getChar(), pMoney,tWorth);

			}
		} else if(landed == 7 || landed == 22 || landed == 36){
			bool drawCup = game->notifyRimCup();
			if (drawCup == true) {
				cout << "Congratualation! You have won a rim cup!" << endl;
				players[curPlayer]->setrimCups(true);
			} else {
				cout << "Sorry. You have failed to draw a rim cup." << endl;
			}
			int money = notifyNH();
			//cout << "You have landed on NH" << endl;
			
			int pMoney = players[curPlayer]->getMoney();

			if (money > pMoney) {
				cout << "You do not have enough money to pay $" << money << endl;
				int assetList[40];
				int numAsset;
				int j = 0;
				for (int i = 0; i < 40; i++) {
					if (players[curPlayer]->getChar() == game->getBoard(i)->getOwner()) {
						assetList[j] = i;
						j++;
					}
				}
				numAsset = j;
				for (int i = j; i < 40; i++) {
					assetList[j] = -1;
				}

				bank->notifyBankruptcy(players[curPlayer]->getChar(),assetList,numAsset,money);
			} else {
				if (money > 0) {
					cout << "You have earned " << money << endl;
				} else {
					cout << "You have lost " << money << endl;
				}
				notifyPay(players[curPlayer]->getChar(), money);
			}
		} else if(landed == 38){
			// COOP FEE
			
			int pMoney = players[curPlayer]->getMoney();
			if (pMoney < 150) {
				cout << "You do not have $150" << endl;
				int assetList[40];
				int numAsset;
				int j = 0;
				for (int i = 0; i < 40; i++) {
					if (players[curPlayer]->getChar() == game->getBoard(i)->getOwner()) {
						assetList[j] = i;
						j++;
					}
				}
				numAsset = j;
				for (int i = j; i < 40; i++) {
					assetList[j] = -1;
				}

				bank->notifyBankruptcy(players[curPlayer]->getChar(),assetList,numAsset,150);
			} else {
				cout << "You have to pay your Co-op Fee ($150)!" << endl;
				players[curPlayer]->pay(-150);
			}
			
		} else {
			cout << "ERROR" << endl;
		}
		if(doubledice){
			cout << endl << "==== Double dice roll again ====" << endl << endl;
		} 
		else {
		cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
		cout << "[next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
		}

	} 	
}

void Controller::notifyTrade(string name, string give, string receive) {
	
	int numgive, numreceive;
	bool valname = false;
	bool valgive = false;
	bool valreceive = false;
	bool numg = false;
	bool numr = false;
	bool propgive = false;
	bool propreceive = false;
	bool improved1 = false;
	bool improved2 = false;
	char offerto;
	
	for(int i = 0; i < playerNum; i++){
		if(players[i]->getName() == name){
			offerto = players[i]->getChar();
		}
	}
	


	if(istringstream(give) >> numgive){
		numg = true;
		valgive = true;
	} else {
		propgive = true;
	}
	if(istringstream(receive) >> numreceive){
		numr = true;
		valreceive = true;
	} else {
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
				string type = game->getBoard(i)->getType();
				for(int k = 0; k < 40; k++){
					if(game->getBoard(i)->getType() == type && game->getBoard(i)->getImprov() > 0){
						improved1 = true;
					}
				}
			}
		} //for
	} // if
	if(propreceive){
		for(int i = 0; i < 40; i++){
		  	if((game->getBoard(i)->getOwner() == offerto) && (game->getBoard(i)->getName() == receive)){
		  		valreceive = true;
		  		string type = game->getBoard(i)->getType();
				for(int k = 0; k < 40; k++){
					if(game->getBoard(i)->getType() == type && game->getBoard(i)->getImprov() > 0){
						improved1 = true;
					}
				}
		  	} else {}
		}	
	}

	if(numg && numr){
		cout << "Can't trade money with money" << endl;
	} else if(improved1 || improved2){
		cout << "Can't trade because property has improvements" << endl;
	} else if(valgive && valname && valreceive){
		if(propgive && propreceive){
			// trade Nomair DC MC
		  	int ind1 = 0;
		  	int ind2 = 0;
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
		  	}


		  	bank->notifyTrade(players[curPlayer]->getChar(), offerto, give, receive, ind1, ind2);
		  	
		} else if(propgive && numreceive){
			// trade Nomair DC 500
		  	int ind = 0;
		  	for (int i = 0; i < 40; i++) {
		  		if (game->getBoard(i)->getName() == give) {
		  			ind = i;
		  			break;
		  		}
		  	}

		  	int oMoney = 0;
		  	for (int i = 0; i < 8; i++) {
		  		if (players[i]->getChar() == offerto) {
		  			oMoney = players[i]->getMoney();
		  			break;
		  		}
		  	}

		  	if (oMoney < numreceive) {
		  		cout << "Invalid trade. " << name << " does not have $" << numreceive << endl;
		  	} else {
				bank->notifyTrade(players[curPlayer]->getChar(), offerto, give, numreceive, ind);
			}
		} else if(propreceive && numgive){
			// trade Nomair 500 DC
		  	int ind = 0;
		  	for (int i = 0; i < 40; i++) {
		  		if (game->getBoard(i)->getName() == receive) {
		  			ind = i;
		  			break;
		  		}
		  	}

		  	int pMoney = players[curPlayer]->getMoney();

		  	if (pMoney < numgive) {
		  		cout << "Invalid trade. You do not have $" << numgive << endl;
		  	} else {
		  		bank->notifyTrade(players[curPlayer]->getChar(), offerto, numgive, receive, ind);
		  	}
		}
	} else {
		cout << "Invalid trade" << endl;
    } // if
}

void Controller::notifyImprove(string property, string purpose) {
	bool valprop = false;
  	bool valpurpose = false;
  	bool onmort = false;
  	bool max = false;
  	bool monopoly = false;
  	int impCost, unimpCost, position;

  	for(int i = 0; i < 40; i++){
  		if(game->getBoard(i)->getName() == property && game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
  			valprop = true;
  			position = i;
  			impCost = game->getBoard(i)->getimprovCost();
  			unimpCost = game->getBoard(i)->getImproveSellCost();
  			string type = game->getBoard(i)->getType();
  			int quantity = 0;

  			for(int i = 0; i < 40; i++){
  				if(game->getBoard(i)->getType() == type && game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
  					++quantity;
  				}
  			}
  			if((type == "Math" || type == "Art1") && quantity == 2){
  				monopoly = true;
  			} else if((type == "Health" || type == "Art2" || type == "Engineering" ||
  					   type == "Environment" || type == "Science1" || type == "Science2") && quantity ==3){
  				monopoly = true;
  			}

  			if(game->getBoard(i)->getImprov() == -1){
  				onmort = true;
  			} else if(game->getBoard(i)->getImprov() == 5){
  				max = true;
  			}
  			break;
  		} else {}
  	}
  	if(purpose == "buy" || purpose == "sell"){
  		valpurpose = true;
  	}
  	if(valprop && valpurpose){
  		if(onmort){
  			cout << "Can't improve, under a mortgage" << endl;
  		} else if(max && purpose == "buy"){
  			cout << "Can't improve anymore" << endl;
  		} else if(!monopoly){
  			cout << "Can't improve buy/sell this building, not monopoly" << endl;
  		} else {
			if(purpose == "buy"){

				int pMoney = players[curPlayer]->getMoney();
				if (pMoney < impCost) {
					cout << "You have $" << pMoney << ", not enough to improve the building" << endl;
				} else {
					bank->improveLand(players[curPlayer]->getChar(), impCost, position, property, true);
					game->getBoard(position)->setImprov(true);
					game->getBoard(position)->setTuitionFee(true);
					td->notifyImprov(position, true);
					int imp = game->getBoard(position)->getImprov();
					cout << "Now your " << property << " has been improved for " << imp << " times!" << endl << endl;
					cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
					cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
	        	}

      		} else if(purpose == "sell"){
      			bank->improveLand(players[curPlayer]->getChar(), unimpCost, position, property, false);
      			game->getBoard(position)->setImprov(false);
      			game->getBoard(position)->setTuitionFee(false);
        		td->notifyImprov(position, false);
        		int imp = game->getBoard(position)->getImprov();
				cout << "Now your " << property << " has been improved for " << imp << " times!" << endl << endl;
				cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
				cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;

      		}
  		}
  	} else{
  		cout << "Invalid improve input" << endl;
  	}
}


void Controller::notifyMortgage(string property) {
	bool valprop = false;
  	bool mort = false;
  	int position;
  	bool improve = false;
  	int mortCost;
  	bool monopoly = false;
  	
  	for(int i = 0; i < 40; i++){
  		if(game->getBoard(i)->getName() == property && game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
  			valprop = true;
  			position = i;
  			mortCost = game->getBoard(i)->getpurchaseCost() * 0.5;

  			string type = game->getBoard(i)->getType();
  			int quantity = 0;

  			for(int i = 0; i < 40; i++){
  				if(game->getBoard(i)->getType() == type && game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
  					++quantity;
  				}
  			}
  			if((type == "Math" || type == "Art1") && quantity == 2){
  				monopoly = true;
  			} else if((type == "Health" || type == "Art2" || type == "Engineering" ||
  					   type == "Environment" || type == "Science1" || type == "Science2") && quantity ==3){
  				monopoly = true;
  			}
  			if(game->getBoard(i)->getImprov() > 0){
  				improve = true;
  			}
  			if(game->getBoard(i)->getMortgaged()){
  				mort = true;
  			}
  			break;
  		}
  	}  
  	if(mort){
  		cout << "Already on mortgage" << endl;
  	} else if(improve){
  		cout << "Need to sell all of the improvements of this property before getting a mortgage" << endl;

  	} else if(valprop){
  		bank->Mortgage(players[curPlayer]->getChar(), position, property, mortCost);
  		game->getBoard(position)->setMortgaged(true);
  		td->notifyImprov(position, false);
  	} else {
  		cout << "Invalid input" << endl;
  	}
	cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
	cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
}

void Controller::notifyUnmortgage(string property) {
	bool valprop = false;
  	bool mort = false;
  	int position, unmortCost;
  	
  	for(int i = 0; i < 40; i++){
  		if(game->getBoard(i)->getName() == property && game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
  			valprop = true;
  			position = i;
  			unmortCost = game->getBoard(i)->getpurchaseCost() * 0.6;
  			if(game->getBoard(i)->getMortgaged()){
  				mort = true;
  			}
  			break;
  		}
  	}  
  	if(!mort){
  		cout << "Doesn't have mortgage" << endl;
  	} else if(valprop){
  		bank->Unmortgage(players[curPlayer]->getChar(), position, property, unmortCost);
  		game->getBoard(position)->setMortgaged(false);
  		td->notifyImprov(position, true);
  	} else {
  		cout << "Invalid input" << endl;
  	}
	cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
	cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;

}
int Controller::getpMoney(char curPlayer) {
	int p = 0;
	for (int i = 0; i < 8; i++) {
		if(players[i]->getChar() == curPlayer) {
			p = i;
			break;
		}
	}
	return players[p]->getMoney();
}

bool Controller::checkAsset(int owe) {
	int pRaise = 0;
	bool noAsset = true;
	bool noMoney = true;
	for(int i = 0; i < 40; i++){
		if(game->getBoard(i)->getProp()){
			if(game->getBoard(i)->getOwner() == players[curPlayer]->getChar()){
				if (game->getBoard(i)->getImprov() > 0) {
					pRaise += game->getBoard(i)->getImprov() * game->getBoard(i)->getImproveSellCost();
				}
				if (!game->getBoard(i)->getMortgaged()) {
					pRaise += game->getBoard(i)->getpurchaseCost() / 2;
				}
			}
		}
	}
	if ((pRaise + players[curPlayer]->getMoney()) > owe) return false;
	else true;
}

Controller::~Controller(){
}



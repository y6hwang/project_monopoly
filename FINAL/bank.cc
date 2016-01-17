#include <iostream>
#include <string>
#include "bank.h"
using namespace std;

Bank::Bank(Controller *c){
	controller = c;
}
Bank::~Bank() {}

// Player on Empty Land
void Bank::notifyLand(char player, int cost, int propPos, string building){

	cout << "Do you want to buy " << building << " ($" << cost << ") " << "? y/n: " << endl;
	char response;
	cin >> response;

	if (response == 'y') {
		controller->notifyPay(player,(cost*-1));
		controller->notifyOwnerChanged(player,propPos);
	

	} else {

		controller->notifyAuction(player,propPos);
	}
}
// Player on Player's land
void Bank::improveLand(char player, int cost, int propPos, std::string building, bool buy) {
	if(buy){
		cout << "Do you want to improve "<< building << " for $" << cost << "? y/n: " << endl;
		char response;
		cin >> response;
		if (response == 'y') {
			controller->notifyPay(player,(cost*-1));
		} 
	} else {
		cout << "Do you want to sell improvement of " << building << " and get $" << cost << "? y/n: " << endl;
		char response;
		cin >> response;
		if (response == 'y'){
			controller->notifyPay(player,cost);
		} else {}
	}
	
}

// Player on other's land
void Bank::notifyLand(char owner, char player, bool mortgaged, int cost, string building) {
	if (mortgaged == true) {
		cout << building << " is mortgaged. No need to pay tutition!" << endl;
	} else {
		cout << "You have landed on " << owner << "'s " << building << endl;
		cout << "You have to pay $" << cost << "." << endl;
		controller->notifyPay(player,(cost*-1));
		controller->notifyPay(owner,cost);
	}


}

void Bank::Mortgage(char player, int pos, string building, int money) {
	cout << "Do you want to get mortgage for " << building <<" and receive $" << money << " ? y/n" << endl;
	char response;
	cin >> response;
	if(response == 'y'){
		controller->notifyPay(player, money);
	}

}

void Bank::Unmortgage(char player, int pos, string building, int money) {
	cout << "Do you want to unmortgage " << building << " for $" << money << " ? y/n" << endl;
	char response;
	cin >> response;
	if(response == 'y'){
		controller->notifyPay(player, (money*-1));
	}


}



void Bank::notifyTrade(char player, char offered, int money, string prop, int ind) {
	cout << offered << ", are you willing to trade " << money << " with " << prop << "?" << " (accept/reject)" << endl;
	string response;
	cin >> response;
	if(response == "accept"){
		controller->notifyPay(player, (money*-1));
		controller->notifyPay(offered, money);
		controller->notifyOwnerChanged(player, ind);

	} else if(response == "reject") {
		cout << offered << " rejected your offer" << endl;
	}

	

	
}
void Bank::notifyTrade(char player, char offered, string gProp, string rProp, int ind1, int ind2) {
	cout << offered << ", are you willing to trade " << rProp << " with " << gProp << "?" << " (accept/reject)" << endl;
	string response;
	cin >> response;
	if(response == "accept"){
		
		controller->notifyOwnerChanged(player,ind2);
		controller->notifyOwnerChanged(offered,ind1);

	} else if(response == "reject"){
		cout << offered << " rejected your offer" << endl;
	}


}

void Bank::notifyTrade(char player, char offered, string prop, int money, int ind) {
	cout << offered << ", are you willing to trade " << prop << " with " << money << "?" << " (accept/reject)" << endl;
	string response;
	cin >> response;
	if(response == "accept"){
		controller->notifyPay(player, money);
		controller->notifyPay(offered, (money*-1));
		controller->notifyOwnerChanged(offered, ind);
	} else if(response == "reject") {
		cout << offered << " rejected your offer" << endl;
	}

}


void Bank::notifyBankruptcy(char player, int assetList[40], int numAsset, int owe) {

	cout << "bankruptcy: You have to pay more money than currently possess." << endl;

	if (controller->checkAsset(owe) == true) {
		cout << "You can not raise money up to $" << owe << " by mortgaging or selling improvments." << endl;
		cout << "Please declare bankruptcy: [bankruptcy]" << endl;

		string response;
		cin >> response;

		bool valid;
		while (!valid) {
			if (response == "bankruptcy") {
				valid = true;



			} else {
				cout << "Please type [bankruptcy]" << endl;
			}
		}
	}
	cout << "1. Drop out: bankruptcy" << endl;
	cout << "2. Raise money by trade, selling improvement, and mortgage: raise" << endl;
	cout << "Type bankruptcy/raise." << endl;
	string response;
	cin >> response;

	// controller->removePlayer(player);


	if (response == "bankruptcy") {
		cout << "You chose to declare bankruptcy." << endl;
		cout << "Return your assets to the open market as an unmortgaged property. " << endl;
		bool correct = false;

		while (!correct) {
			
			int i = 0;
			while (i < numAsset) {
				controller->notifyAuction(player,assetList[i]);
				i++;
			}
		}
		correct = true;

	} else if (response == "raise") {
		// trade, improvement, mortgage gogogo!!
		bool done = false;
		char r;

		cout << "You have 3 options: " << endl;
		cout << "1. Trade you assets" << endl;
		cout << "2. Sell improvements" << endl;
		cout << "3. Mortgage you assets"  << endl;
		cout << "Please choose option 1/2/3 ";

		while (!done) {
			cin >> r;
			if ((r == '1') || (r = '0')) {
				cout << "Please enter: trade <name> <give> <receive>" << endl;
				string name, give, receive;
				cin >> name;
				cin >> give;
				cin >> receive;
				controller->notifyTrade(name,give,receive);
			} else if (r == '2') {
				cout << "Please enter: improve <property> sell" << endl;
				string property, purpose;
				cin >> property;
				controller->notifyImprove(property,"sell");
			} else if (r == '3') {
				cout << "Please enter: mortgage <property> " << endl;
				string property;
				cin >> property;
				controller->notifyMortgage(property);
			} else {
				cout << "Please enter 1/2/3: ";
			}

			cout << "You have collect $" << controller->getpMoney(player) << " and you owe $" << owe << endl;

			if (controller->checkAsset(owe) == true) {
				cout << "You cannot raise money anymore! You are dropped out. Byebye-. " << endl;
				controller->removePlayer(player);
				done = true;
				break;
			} else if (controller->getpMoney(player) >= owe) {
				cout << "You have enough money to pay. Do you want to continue? y/n: ";
				cin >> r;
				if (r == 'n') {
				done = true;
				break;
				}
			} else {
				cout << "You have to continue trading/selling improvements/mortgaging. " << endl;
				cout << "Please enter your option 1/2/3 or dropout (enter 0)" << endl;
			}
			


		}
	}

}



void Bank::notifyBankruptcy(char player, char receiver, int assetList[40], int numAsset, int owe) {
	cout << "bankruptcy: You have to pay more money than currently possess. You have two options: " << endl;
	cout << "1. Drop out: bankruptcy" << endl;
	cout << "2. Raise money by trade, selling improvement, and mortgage: raise" << endl;
	cout << "Type bankruptcy/raise." << endl;
	string response;
	cin >> response;
	bool valid = false;

	// controller->removePlayer(player);

	while (!valid) {
		if (response == "bankruptcy") {
			cout << "You chose to declare bankruptcy. You have two options: " << endl;
			cout << "1. Give your assets to " << receiver << "." << endl;
			cout << "2. Return your assets to the open market as an unmortgaged property. " << endl;
			cout << "Choose option 1/2: ";
			char r;
			
			cin >> r;
			bool correct = false;

			while (!correct) {
				if (r == '1') {
					int i = 0;
					while (i < numAsset) {
						controller->notifyOwnerChanged(receiver,assetList[i]);
						++i;
				}
				} else if (r == '2') {
					int i = 0;
					while (i < numAsset) {
						controller->notifyAuction(player,assetList[i]);
						i++;
					}
				} else {
					cout << "Please enter the option 1/2: " << endl;
				}
			}

		} else if (response == "raise") {
			// trade, improvement, mortgage gogogo!!
			bool done = false;
			char r;

			cout << "You have 3 options: " << endl;
			cout << "1. Trade you assets" << endl;
			cout << "2. Sell improvements" << endl;
			cout << "3. Mortgage you assets"  << endl;
			cout << "Please choose option 1/2/3 ";

			while (!done) {
				cin >> r;
				if (r == '1') {
					cout << "Please enter: trade <name> <give> <receive>" << endl;
					string name, give, receive;
					cin >> name;
					cin >> give;
					cin >> receive;
					controller->notifyTrade(name,give,receive);
				} else if (r == '2') {
					cout << "Please enter: improve <property> sell" << endl;
					string property, purpose;
					cin >> property;
					controller->notifyImprove(property,"sell");
				} else if (r == '3') {
					cout << "Please enter: mortgage <property> " << endl;
					string property;
					cin >> property;
					controller->notifyMortgage(property);
				} else {
					cout << "Please enter 1/2/3: ";
				}

				cout << "You have collect $" << controller->getpMoney(player) << " and you owe $" << owe << endl;

				if (controller->checkAsset(owe) == true) {
					cout << "You cannot raise money anymore! You are dropped out. Byebye-. " << endl;
					controller->removePlayer(player);
					done = true;
					break;
				} else if (controller->getpMoney(player) >= owe) {
					cout << "You have enough money to pay. Do you want to continue? y/n: ";
					cin >> r;
					if (r == 'n') {
					done = true;
					break;
					}
				} else {
					cout << "You have to continue trading/selling improvements/mortgaging. " << endl;
					cout << "Please enter your option 1/2/3 or dropout (enter 0)" << endl;
				}
				
			}

		} else {
			cout << "Please enter bankruptcy/raise." << endl;
		}
	}

}


void Bank::notifyAuction(char plist[8], int mlist[8], string building, int propPos, char curPlayer) {
	int bidlist[8];
	for (int i = 0; i < 8; i++) {
		bidlist[i] = 0;
	}

	int numPlayers = 0;
	for (int i = 0; i < 8; i++) {
		if (plist[i] == 'n') break;
		else ++numPlayers;
	}
	int maxBid = 0;
	int join = numPlayers - 1;
	bool done = false;



	cout << "Starting auction on " << building << endl;

	while (!done) {

		if (join == 0) {
			done = true;
			break;
		}
		
		for (int i = 0; i < 8; i++) {
			if (plist[i] == 'n') break;

			if ((bidlist[i] < 0) || (plist[i] == curPlayer)) continue;

			if (mlist[i] < maxBid) {
				cout << "You do not have enough money to raise the bid" << endl;
				bidlist[i] = -1;
				--join;
			} else {
				if ((join == 1) && (maxBid != 0)) {
					done = true;
					break;
				}
				cout << "Current max Bid is $" << maxBid << "." << endl;
				cout << plist[i] << "'s turn. Would you like to raise? y/n: ";
				char response;
				cin >> response;
				if (response == 'y') {
					cout << "Enter your bid (over $" << maxBid << "): ";
					int bid;
					cin >> bid;
					bool correct = false;
					while (!correct) {
						if (bid > mlist[i]) {
							cout << "You have $" << mlist[i] << ", not enough to bid $" << mlist[i] << endl;
							cout << "Please enter you bid again! (over $" << maxBid << ", less than $" << mlist[i] << "): "<< endl;
						} else {
							correct = true;
							bidlist[i] = bid;
							if (maxBid < bid) {
								maxBid = bid;
							} else {
								cout << "Your bid is less than $" << maxBid << ". You cannot participate in the auction anymore!" << endl;
								bidlist[i] = -1;
								--join;
							}
						}
					}
				} else if (response == 'n') {
					bidlist[i] = -1;
					--join;
					cout << "You have given up this auction. You cannot participate in the auction anymore!" << endl;
				} else {
					cout << "Plase entere 'y' (to participate) or 'n' (to give up)." << endl;
				}
			}
		}
	}	

	if (join != 0) {
		char newOwner = '\0';
		for (int i = 0; i < 8; i++) {
			if (bidlist[i] > 0) {
				newOwner = plist[i];
				break;
			} 
		}

		cout << "The new owner of " << building << " is " << newOwner << endl;

		controller->notifyPay(newOwner,(maxBid*-1));
		controller->notifyOwnerChanged(newOwner,propPos);
	} else {
		cout << "No one wants to buy the " << building << "." << endl;
		controller->notifyOwnerChanged('\0',propPos);
	}

}


int Bank::notifyTimLine(char player, int pMoney, int rimCups, int turns) {
	//if (turns == 0) { return -13;}
	cout << "You have 3 options to leave : " << endl;
	cout << "1. Pay $50" << endl;
	cout << "2. Use your Rim Cup" << endl;
	cout << "3. roll again and get doubles" << endl;
	cout << "Please chose option 1/2/3: ";

	bool correct = false;
	bool option1 = false;
	bool option2 = false;
	int total = -13;
	int dice1, dice2;

	while (!correct) {
		char response;
		cin >> response;

		if (response == '1') {
			option1 = true;
			if (pMoney >= 50) {
				cout << "You have chosen to pay $50" << endl;
				controller->notifyPay(player,-50);
				cout << "Roll again!" << endl;
				srand(time(NULL));
				dice1 = rand() % 6 + 1;
				srand(rand());
				dice2 = rand() % 6 + 1;
				total = dice1 + dice2;
      
      			cout << endl << "First dice: " << dice1 << endl;
      			cout << "Second dice " << dice2 << endl << endl;

				return total;
			} else {
				cout << "You do not have enough money to pay $50" << endl;
				if (option2 == true) {
					cout << "Please choose option 3: ";
				} else {
					cout << "Please choose other option 2/3: ";
				}
			}
		} else if (response == '2') {
			option2 = true;
			if (rimCups > 0) {
				cout << "You have chosen to use you rim cup" << endl;
				srand(time(NULL));
				dice1 = rand() % 6 + 1;
				srand(rand());
				dice2 = rand() % 6 + 1;
				total = dice1 + dice2;
      
      			cout << endl << "First dice: " << dice1 << endl;
      			cout << "Second dice " << dice2 << endl << endl;

				return total * -1; // notifying using rimcup.
			} else {
				cout << "You do not have any rim cups" << endl;
				if (option1 == true) {
					cout << "Please choose option 3: " << endl;
				} else {
					cout << "Please choose other option 1/3: ";
				}
			}
		} else if (response == '3') {
			if ((option1 == true) && (option2 == true) && (turns == 2)) {
				return 0; // notifying bankruptcy
			} else {
				cout << "Rolling dice!" << endl;
				srand(time(NULL));
				dice1 = rand() % 6 + 1;
				srand(rand());
				dice2 = rand() % 6 + 1;
				total = dice1 + dice2;
      
      			cout << endl << "First dice: " << dice1 << endl;
      			cout << "Second dice " << dice2 << endl << endl;

      			if (dice1 == dice2) {
      				cout << "You rolled doubles! Leaving Tim line" << endl;
      				return total;
      			} else {
      				if (turns == 3) {
      					cout << "You have failed rolling doubles for 3 times" << endl;
      					cout << "You have to choose option 1/2: ";
      				} else {
	      				cout << "You failed to roll doubles. Staying on Tim Line" << endl;
	      				cout << "You have " << 3-turns << " turns to roll doubles" << endl;
	      				cout << endl;
	      				return -1; // roll failed setupTurns + 1;
	      			}
      			}
      		}

      	} else {
      		cout << "Please enter 1/2/3: " << endl;

      	}
    }
    return total;
}

void Bank::notifyTuition(char player, int pMoney, int tWorth) {
	if (pMoney < 300) {
		cout << "You have to pay 10\% of you total worth ($" << tWorth << ")" << endl;
		cout << endl;
		controller->notifyPay(player,(tWorth * -1));

		cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
		cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;
	} else if (pMoney < tWorth) {
		cout << "You have to pay $300 for Tuition Fee." << endl;
		cout << endl;
		controller->notifyPay(player,-300);

		cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
		cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;

	} else {
		cout << "You have 2 options: " << endl;
		cout << "1. Pay $300" << endl;
		cout << "2. Pay 10\% of you total worth ($" << tWorth << ")" << endl;
		cout << "Please choose 1/2: ";

		bool correct = false;
		char response;

		while (!correct) {

			cin >> response;

			if (response == '1') {
				cout << "You choose to pay $300" << endl;
				controller->notifyPay(player,-300);
				correct = true;

				cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
				cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;

			} else if (response == '2') {
				cout << "You choose to pay 10\% of you total worth ($" << tWorth << ")" << endl;
				cout << endl;
				controller->notifyPay(player,(tWorth * -1));
				correct = true;

				cout << endl << "==== Enter one of the followings to continue the game ====" << endl;
				cout << "[roll]   [next]   [assets]   [trade]   [improve]   [mortagage]   [unmortgage]" << endl << endl;

			} else {
				cout << "Please enter 1/2: ";
			}
		}
	}
}

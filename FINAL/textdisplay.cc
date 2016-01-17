#include "textdisplay.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

TextDisplay::TextDisplay() {
	buildings[0] = " ";
	buildings[1] = "AL";
	buildings[2] = " ";
	buildings[3] = "ML";
	buildings[4] = " ";
	buildings[5] = " ";
	buildings[6] = "ECH";
	buildings[7] = " ";
	buildings[8] = "PAS";
	buildings[9] = "HH";
	buildings[10] = " ";
	buildings[11] = "RCH";
	buildings[12] = " ";
	buildings[13] = "DWE";
	buildings[14] = "CPH";
	buildings[15] = " ";
	buildings[16] = "LHI";
	buildings[17] = " ";
	buildings[18] = "BMH";
	buildings[19] = "OPT";
	buildings[20] = " ";
	buildings[21] = "EV1";
	buildings[22] = " ";
	buildings[23] = "EV2";
	buildings[24] = "EV3";
	buildings[25] = " ";
	buildings[26] = "PHYS";
	buildings[27] = "B1";
	buildings[28] = " ";
	buildings[29] = "B2";
	buildings[30] = " ";
	buildings[31] = "EIT";
	buildings[32] = "ESC";
	buildings[33] = " ";
	buildings[34] = "C2";
	buildings[35] = " ";
	buildings[36] = " ";
	buildings[37] = "MC";
	buildings[38] = " ";
	buildings[39] = "DC";

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 8; j++) {
			landed[i][j] = ' ';
		}
	}

	for (int i = 0; i < 40; i++) {
		improv[i] = 0;
	}
} // TextDisplay ctor

TextDisplay::~TextDisplay() {} // TextDisplay dtorzz

void TextDisplay::notifyJoin(char player) {
	if (player == 'G') {
		landed[0][0] = player;
	} else if (player == 'B') {
		landed[0][1] = player;
	} else if (player == 'D') {
		landed[0][2] = player;
	} else if (player == 'P') {
		landed[0][3] = player;
	} else if (player == 'S') {
		landed[0][4] = player;
	} else if (player == '$') {
		landed[0][5] = player;
	} else if (player == 'L') {
		landed[0][6] = player;
	} else if (player == 'T') {
		landed[0][7] = player;
	}
}

void TextDisplay::notifyMove(char player, int pos, int prevpos) {
	int player_ind = 0;

	
	for (int i = 0; i < 8; i++) {
		if (landed[prevpos][i] == player) {
			player_ind = i;
			break;
		}
	}
			
	landed[prevpos][player_ind] = ' ';
	landed[pos][player_ind] = player;

} // notify

void TextDisplay::notifyImprov(int pos, bool buy) {
	if (buy == true) ++improv[pos];
	else --improv[pos];
}

void TextDisplay::print() const {
	cout.fill('_');
	cout.width(111);
	cout << "" << endl;

// first line

	for (int i = 20; i <= 30; i++) {
		cout << "|";
		cout.fill(' ');
		cout.width(9);

		if (i == 20) {
			cout << left << "Goose";
		} else if ( i == 22) {
			cout << left << "NEEDLES";
		} else if (i == 25) {
			cout << left << "V1";
		} else if ( i == 28) {
			cout << left << "CIF";
		} else if ( i == 30) {
			cout << left <<"GO TO";
		} else {
			if (improv[i] == -1) {
				cout << "-1       ";
			} else {
				int repeat = improv[i];
				string display = "";
				for (int i = 0; i < repeat; i++) {
					display += "I";
				}
				cout.fill(' ');
				cout.width(9);
				cout << left << display;
				//cout << "|";
			}
		}
	}
	cout << "|" << endl;

	string midline = "---------";
	for (int i = 20; i <= 30; i++) {
		cout << "|";
		cout.fill(' ');
		cout.width(9);

		if (i == 20) {
			cout << left << "Nesting";
		} else if ( i == 22) {
			cout << left << "Hall";
		} else if (i == 25) {
			cout << left << "";
		} else if ( i == 28) {
			cout << left << "";
		} else if ( i == 30) {
			cout << left << "TIMS";
		} else {
			cout << midline;
		}
	}
	cout << "|" << endl;

	for (int i = 20; i <= 30; i++) {
		cout << "|";
		cout.fill(' ');
		cout.width(9);
		cout << left << buildings[i];
		
	}
	cout << "|" << endl;

	for (int i = 20; i <= 30; i++) {
		cout << "|";
		for (int j = 0; j < 8; j++) {
			cout << landed[i][j];
		}
		cout << " ";
	}
	cout << "|" << endl;

	string botline = "|_________";
	for (int i = 20; i <= 30; i++ ) {
		cout << botline;
	}
	cout << "|" << endl;

	int l,r;
	int line = 1;

// from second

	while (line < 10) {
		l = 20 - line;
		r = 30 + line;


		for (int i = 0; i <= 10; i++) {
			if (i == 0) {
				if (buildings[l] == " ") {
					if (l == 12) {
						cout.fill(' ');
						cout.width(10);
						cout << left << "|PAC ";
					} else if (l == 15) {
						cout.fill(' ');
						cout.width(10);
						cout << left << "|UWP ";
					} else if (l == 17) {
						cout.fill(' ');
						cout.width(10);
						cout << left << "|SLC ";
					}
				} else {
					cout << "|";
					if (improv[l] == -1) {
						cout << "-1       ";
					} else {
						int repeat = improv[l];
						string display = "";
						for (int i = 0; i < repeat; i++) {
							display += "I";
						}

						cout.fill(' ');
						cout.width(9);
						cout << left << display;
						//cout << "|";
					}
				}
			} else if ( i == 1) {
				cout << "|         ";
			} else if (i == 9) {
				cout << "          |";
			} else if (i == 10) {
				if (buildings[r] == " ") {
					if (r == 33) {
						cout.fill(' ');
						cout.width(9);
						cout << left << "SLC ";
					} else if (r == 35) {
						cout.fill(' ');
						cout.width(9);
						cout << left << "REV ";
					} else if (r == 36) {
						cout.fill(' ');
						cout.width(9);
						cout << left << "NEEDLES ";
					} else if( r == 38) {
						cout.fill(' ');
						cout.width(9);
						cout << left << "COOP ";
					}
					cout << "|";
				} else {
					if (improv[r] == -1) {
						cout << "-1      |";
					} else {
						int repeat = improv[r];
						string display = "";
						for (int i = 0; i < repeat; i++) {
							display += "I";
						}
						cout.fill(' ');
						cout.width(9);
						cout << left << display;
						cout << "|";
					}
				}
			} else {
				cout << "          ";
			}
		}
		cout << endl;

		for (int i = 0; i <= 10; i++) {
			if (i == 0) {
				if ((l == 17) || (l == 15) || (l == 12)) {
					cout << "|";
					cout.fill(' ');
					cout.width(9);
					cout << "";
				} else {
					cout << "|";
					cout.fill('-');
					cout.width(9);
					cout << "";
				}
			} else if ( i == 1) {
				cout << "|         ";
			} else if (i == 9) {
				cout << "          |";
			} else if (i == 10) {
				if (buildings[r] == " ") {
					if (r == 36) {
						cout.fill(' ');
						cout.width(9);
						cout << left << "HALL";
						cout << "|";
					}
					else if (r == 38) {
						cout.fill(' ');
						cout.width(9);
						cout << left << "FEE";
						cout << "|";
					} else {
						cout.fill(' ');
						cout.width(10);
						cout << right << "|";
					}
				} else {	
					cout.fill('-');
					cout.width(10);
					cout << right << "|";
				}
			} else {
				cout << "          ";
			}
		}
		cout << endl;

		for (int i = 0; i <= 10; i++) {

			if (i == 0) {
				cout << "|";
				cout.fill(' ');
				cout.width(9);
				cout << left << buildings[l];
			} else if ( i == 1) {
				cout << "|         ";
			} else if (i == 9) {
				cout << "          |";
			} else if (i == 10) {
				cout.fill(' ');
				cout.width(9);
				cout << left << buildings[r];
				cout << "|";
			} else {
				cout << "          ";
			}
		}
		cout << endl;

		for (int i = 0; i <= 10; i++) {
			if (i == 0) {
				cout << "| ";
				for (int j = 0; j < 8; j++) {
					cout << landed[l][j];
				}
			} else if ( i == 1) {
				cout << "|         ";
			} else if (i == 9) {
				cout << "          |";
			} else if (i == 10) {
				cout << " ";
				for (int j = 0; j < 8; j++) {
					cout << landed[r][j];
				}
				cout << "|";
			} else {
				cout << "          ";
			}
		}
		cout << endl;

		for (int i = 0; i <= 10; i++) {
			if (i == 0) {
				cout << "|";
				cout.fill('_');
				cout.width(9);
				cout << "";
			} else if ( i == 1) {
				if (line == 9) {
					cout << "|_________";
				} else {
					cout << "|         ";
				}
			} else if (i == 9) {
				if (line == 9) {
					cout << "__________|";
				} else {
					cout << "          |";
				}
			} else if (i == 10) {
				cout.fill('_');
				cout.width(9);
				cout << "";
				cout << "|";
			} else {
				if (line == 9) {
					cout << "__________";
				} else { 
					cout << "          ";
				}
			}
		}
		cout << endl;

		line++;
	}

// last line
	for (int i = 10; i >= 0; i--) {
		cout << "|";
		cout.fill(' ');
		cout.width(9);

		if (i == 10) {
			cout << left << "DC Tims";
		} else if ( i == 7) {
			cout << left << "NEEDLES";
		} else if (i == 5) {
			cout << left << "MKV";
		} else if ( i == 4) {
			cout << left << "TUITION";
		} else if ( i == 2) {
			cout << left << "SLC";
		} else if (i == 0) {
			cout << left << "COLLECT";
		} else {
			if (improv[i] == -1) {
				cout << "-1       ";
			} else {
				int repeat = improv[i];
				string display = "";
				for (int i = 0; i < repeat; i++) {
					display += "I";
				}
				cout << left << display;
				//cout << "|";
			}
		}
	}
	cout << "|" << endl;

	for (int i = 0; i <= 10; i++) {
		cout << "|";
		cout.fill(' ');
		cout.width(9);

		if (i == 0) {
			cout << left << "Lines";
		} else if ( i == 3) {
			cout << left << "HALL";
		} else if (i == 5) {
			cout << left << "";
		} else if ( i == 6) {
			cout << left << "";
		} else if ( i == 8) {
			cout << left << "";
		} else if (i == 10) {
			cout << left << "OSAP";
		} else {
			cout << midline;
		}
	}
	cout << "|" << endl;

	for (int i = 10; i >= 0; i--) {
		cout << "|";
		cout.fill(' ');
		cout.width(9);
		cout << left << buildings[i];
	}
	cout << "|" << endl;

	for (int i = 10; i >=0; i--) {
		cout << "|";
		for (int j = 0; j < 8; j++) {
			cout << landed[i][j];
		}
		cout << " ";
	}
	cout << "|" << endl;

	for (int i = 20; i <= 30; i++ ) {
		cout << botline;
	}
	cout << "|" << endl;

} // print



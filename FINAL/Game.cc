#include "Game.h"
#include "osap.h"
#include "al.h"
#include "slc.h"
#include "ml.h"
#include "tuition.h"
#include "mkv.h"
#include "ech.h"
#include "pas.h"
#include "nh.h"
#include "phys.h"
#include "b1.h"
#include "hh.h"
#include "dctimline.h"
#include "rch.h"
#include "pac.h"
#include "dwe.h"
#include "cph.h"
#include "uwp.h"
#include "lhi.h"
#include "bmh.h"
#include "opt.h"
#include "goosenesting.h"
#include "ev1.h"
#include "ev2.h"
#include "ev3.h"
#include "v1.h"
#include "cif.h"
#include "b2.h"
#include "gototims.h"
#include "eit.h"
#include "esc.h"
#include "c2.h"
#include "rev.h"
#include "mc.h"
#include "dc.h"
#include "coopfee.h"



Game::Game(){
	board[0] = new Osap();
	board[1] = new Al();
	board[2] = new Slc();
	board[3] = new Ml();
	board[4] = new Tuition();
	board[5] = new Mkv();
	board[6] = new Ech();
	board[7] = new Nh();
	board[8] = new Pas();
	board[9] = new Hh();
	board[10] = new Dctimline();
	board[11] = new Rch();
	board[12] = new Pac();
	board[13] = new Dwe();
	board[14] = new Cph();
	board[15] = new Uwp();
	board[16] = new Lhi();
	board[17] = new Slc();
	board[18] = new Bmh();
	board[19] = new Opt();
	board[20] = new Goosenesting();
	board[21] = new Ev1();
	board[22] = new Nh();
	board[23] = new Ev2();
	board[24] = new Ev3();
	board[25] = new V1();
	board[26] = new Phys();
	board[27] = new B1();
	board[28] = new Cif();
	board[29] = new B2();
	board[30] = new Gototims();
	board[31] = new Eit();
	board[32] = new Esc();
	board[33] = new Slc();
	board[34] = new C2();
	board[35] = new Rev();
	board[36] = new Nh();
	board[37] = new Mc();
	board[38] = new CoopFee();
	board[39] = new Dc();
	rimsOut = 0;
};


Game::~Game(){

};

Board* Game::getBoard(int ind){
	return board[ind];
}

bool Game::notifyRimCup() {
	if (rimsOut == 4) {
		return false;
	} 

	bool cups[100];
	cups[0] = true;

	for (int i = 1; i < 100; i++) {
		cups[i] = false;
	}


	srand(time(NULL));
	int random_int = rand()%100 + 1;
	++rimsOut;
	return cups[random_int];
}

void Game::notifyLand(){}
void Game::notifyCollect(){}
void Game::notifyPay(){}
void Game::notifyTimLine(){}
void Game::notifyMove(){}



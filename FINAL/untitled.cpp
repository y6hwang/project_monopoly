string building = game->getBoard(propPos)->getName();
int plist[8];
while (int i = 0; i < 8; i++) {
	plist[i] = players[i]->getChar();
}
int mlist[8];
while (int i = 0; i < 8; i++) {
	mlist[i] = players[i]->getMoney();
}
bank->notifyAuction(plist,mlist,building,propPos);
/**
 *	Driver Class for the game BlackJack 
 */

#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#include "game.h"

int main(){

	Game *blackJackGame = new Game();
	blackJackGame->setUpPhase();
	blackJackGame->start();
	delete blackJackGame;
	cout << "-------------END OF GAME---------------\n";

	return 0;
}

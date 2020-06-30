#ifndef GAME_H
#define GAME_H

#include <vector>
#include "deck.h"
#include "normalplayer.h"
#include "dealerplayer.h"

using namespace std;

class Game {
	public:
		Game();
		void setUpPhase();
		void start();
		~Game();
	private:
		int round;
		int pCount;
		int dCount;
		bool endOfRound;
		bool endOfGame;
		DealerPlayer *dealer;
		vector<NormalPlayer *> players;
		Deck *deck;		
		
		//called in start
		void resetForNewRound();
		void bettingPhase();
		void distributePhase();
		void surrenderPhase();
		void blackJackCheckingPhase();
		void printTable();
		bool isEndOfRound();
		bool isEndOfGame();
		void playerDecisionPhase();
		void dealerDecisionPhase();
		void checkPayouts();
		void splittingPhase(NormalPlayer *);
		void handPayOut(NormalPlayer *, Hand *);
		void playersTurn(NormalPlayer *, bool &);
};

#include "game.cpp"

#endif

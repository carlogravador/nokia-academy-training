/*
	Declaration of Class Player
	Member functions defined in player.cpp
*/


#ifndef HAND_H
#define HAND_H

#include "card.h"

class Hand{

	public:
		static const int DECISION_HIT = 1;
		static const int DECISION_STAND = 2;	
		static const int DECISION_DOUBLE = 3;
		static const int STATUS_BLACKJACK = 4;
		static const int STATUS_BUST = 5;
		
		void setScore(int);
		int getScore();
		
		void setStatus(int);
		int getStatus();
		
		void setBet(float);
		float getBet();
		
		void setDecision(int);
		int getDecision();
		
		void putCard(Card);

		int getBestScore();
				
	private:
		Card *card[22];
		int score;
		int status;		
		float bet;
		int decision;
		
		
		int aceCounter();
	
};

#endif

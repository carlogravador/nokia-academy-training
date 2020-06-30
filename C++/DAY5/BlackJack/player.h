/*
	Declaration of Class Player
	Member functions defined in player.cpp
*/

#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include "hand.h"
	
class Player{
		
	public:
		string getName();
		void setName(string);
			
	private:
		string name;
		Hand primaryHand;
		
};

#endif

/*
	Declaration of Class Card
	Member functions defined in card.cpp
*/

#ifndef CARD_H
#define CARD_H

#include<string>

using std::string;

class Card {
	
	public:
		/*
			Constructor for Card 
			Parameters
				string suit - (Diamond, Heart, Clubs, Spades)
				int number - (numerical representation of card)	    
				int value - (corresponding value of card, not always same as it's number)
				bool show - (status of card)
		*/
		Card(string, int, int, bool);
		
		/*
			Prints "?" if show is false
			else print the card normally
		*/
		void print();		

		/*
			change show to true;
		*/
		void show();		

		/*
			change show to false;
		*/
		void hide();		
		
		/*
			return the value of card		
		*/
		int getValue();

		/*
			Destructor
		*/
		~Card();

	private:
		string suit;				
		int number;				
		int value;
		bool isShow;					
};

#endif




/*
	Declaration of Class Deck
	Member functions defined in deck.cpp
*/

#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck {

	public:
		/*
			Constructor for Deck
			Parameters
				int size - number of decks to be created
		*/
		Deck(int);	
		/*
			Shuffle the deck
		*/
		void shuffle();
		
		/*
			Returns the card on the top of deck
		*/
		Card getCard();
		
		/*
			Reset the current deck
		*/
		void reset();
		
		/*
		
		*/
		int getSize();
		
		/*
			Destructor for card
		*/
		~Deck();
	
	
	private:
		int size;
		Card **cards;
		int index;
		
		void swap(Card **, Card **);
		
};

#endif

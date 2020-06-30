/**
 *	Declaration of Class Deck
 *	Member functions defined in deck.cpp
 */

#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck {

	public:
		/**
		 *	Constructor for Deck
		 *	@param int as number of decks to be created
		 */
		Deck(int);	
		/**
		 *	Shuffle the deck
		 */
		void shuffle();
		
		/**
		 *	@return the address of the most top card at the stack of deck
		 */
		Card *getCard();
		
		/**
		 *	Reset the current deck
		 */
		void reset();
		
		/**
		 *	@return the number of cards created in the deck
		 */
		int getSize() const;

		/**
		 *	@return the number of deck created; 
		 */
		int getDeckCount() const;

		/**
		 *	@return the position of pointer from array of cards; 
		 */
		int getIndex() const;

		/**
		 *	@return remaing cards in the deck. 
		 */
		int remainingCards() const;
		
		/**
		 *	Destructor for card
		 */
		~Deck();
	
	
	private:
		int size;
		Card **cards;
		int index;
		
		/**
		 *	Utility function for swapping
		 */
		void swap(Card **, Card **);
		
};

#endif

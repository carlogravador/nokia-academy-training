/**
 *	Declaration of Class Card
 *	Member functions defined in card.cpp
 */

#ifndef CARD_H
#define CARD_H

#include<string>

using std::string;

class Card {
	
	public:
		/**
		 *	Constructor for Card 
		 *	@param string as suit
		 *	@param int as numerical representation
		 *	@param int as value of card
		 *	@param bool as status of card - shown/hidden
		 */
		Card(string, int, int, bool);
		
		/**
		 *	Prints "?" if show is false
		 *	else print the card normally
		 */
		void print();		

		/**
		 *	change show to true
		 */
		void show();		

		/**
		 *	change show to false
		 */
		void hide();		
		
		/**
		 *	@return the value of card		
		 */
		int getValue() const;

		/**
		 *	Destructor
		 */
		~Card();

	private:
		string suit;				
		int number;				
		int value;
		bool isShow;					
};

#include "card.cpp"


#endif




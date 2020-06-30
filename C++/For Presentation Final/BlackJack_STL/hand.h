/**
 *	Declaration of Class Hand
 *	Member functions defined in Hand.cpp
 */
#ifndef HAND_H
#define HAND_H

#include<string>
#include<vector>

#include "card.h"

using namespace std;

class Hand{

	public:
		static const int DECISION_HIT = 1;
		static const int DECISION_STAND = 2;	
		static const int DECISION_DOUBLE = 3;

		static const string STATUS_BLACKJACK;
		static const string STATUS_BUST;
		static const string STATUS_WIN;
		static const string STATUS_LOSE;
		static const string STATUS_SURRENDER;

		/**
		 *	Constructor for Class Hand
		 */
		Hand();

		/**
		 * @brief Get the Card Count object
		 * 
		 * @return int 
		 */
		int getCardCount() const;

		/**
		 *	@return the best score for the hand
		 */
		int getScore() const;
		
		/**
		 *	@return status of the hand	
		 */
		string getStatus() const;

		/**
		 *	Sets the status for the hand
		 */
		void setStatus(const string);
		
		/**
		 *	Sets the bet for the hand
		 */
		void setBet(float);
		
		/**
		 * 	@return the bet of hand
		 */ 
		float getBet() const;
		
		/**
		 *	Sets the decision for the hand
		 */
		void setDecision(int);

		/**
		 *	@return decision of the hand
		 */
		int getDecision() const;
		
		/**
		 *	Stores the card in the hand Increments the cardCount.
		 *	Passing NULL decrements the cardCount - (FOR REMOVING LAST CARD)
		 *	@param Card* - card to be added to the hand.
		 */
		void putCard(Card*);

		/**
		 * @brief 
		 * removes the card on the hand
		 */
		void removeCard(Card*);

		/**
		 * @param int index of card you want to get.
		 * @return the address of card at index.
		 */
		Card *getCardAt(int) const;

		/**
		 *	Prints all cards in the hand.
		 */
		void printAllCards();

		/**
		 * @brief 
		 * Print all cards with mode.
		 * @param bool show or hidden
		 */
		void printAllCards(bool);

		/**
		 *	Prints all information related to hand. 
		 */
		void printHandInfo();

		/**
		 *	@return status of hand if blackJack
		 */
		bool isBlackJack() const;

		/**
		 * 	@return status of hand if busted
		 */
		bool isBusted() const;

		/**
		 *	@return if card is splitable
		 */
		bool isSplitable() const;

		/**
		 *	Hand gets another card.
		 *	@param Card* card received from deck
		 */
		void hit(Card*);

		/**
		 *	Hand stops receiving card from deck 
		 */
		void stand();
		
		/**
		 * 	@param float money of player
		 *	@return if bet * 2 <= money
		 */
		bool canDouble(float) const;

		/**
		 *	Hand double's the bet, hit(), then stand()
		 */
		void doubleMove(Card*);

		/**
		 *	Set Decision to surrender
		 *	Similar to stand();
		 */
		void surrender();
		
		/**
		 * @brief 
		 * Reset the status of hands.
		 */
		void reset();
		
		/**
		* @brief
		* Check if hand will have a payout on checkPayout phase
		*/
		bool hasPayout();
		
		/**
		* @brief
		* Check if hand can play
		*/
		bool canPlay();

		/**
		 *	Destructor for Class Hand
		 */
		~Hand();
				
	private:
		vector<Card *> card;
		int cardCount;
		int score;
		string status;		
		float bet;
		int decision;

		/**
		 *	Computes for the best possible score for the hand.
		 *	Save in score variable
		 */
		void computeBestScore();

};

#include "hand.cpp"

#endif

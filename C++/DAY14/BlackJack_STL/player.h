/**
*	Declaration of Class Player
*	Member functions defined in player.cpp
*/

#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include <vector>
#include "hand.h"

using namespace std;
	
class Player{
		
	public:
		static int count;

		/**
		 *	Constructor for Class Player
		 */
		Player();
		
		/**
		 * 
		 *	Prints all information about the player
		 */
		void printInfo();

		/**
		 * @brief 
		 * Resets the status of player
		 */
		void reset();

		/**
		*	@return hands[0] as primary hand
		*/
		Hand *getPrimaryHand() const;

		/**
		 *	@return id of player
		 */
		int getId() const;
		
		/**
		*
		*
		*/
		int getHandCount() const;
		
		/**
		*
		*/
		vector<Hand *> getAllHands();

		/**
		 *	Destructor for Class Player
		 */
		~Player();
			
	protected:
		int id;
		int handCount;
		vecotr<Hand *> hands;
		//Hand **hands;
		
};

#include "player.cpp"

#endif

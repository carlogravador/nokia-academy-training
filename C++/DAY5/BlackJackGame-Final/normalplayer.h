/**
 *  Declaration of Class NormalPlayer
 *  Derived from Class Player
 */

#ifndef NORMALPLAYER_H
#define NORMALPLAYER_H

#include "player.h"

class NormalPlayer : public Player {

    public:
        static const int SPLIT_ACCEPT = 1;
        static const int SPLIT_REFUSE = 2;
        /**
         *  Constructor for Class NormalPlayer
         *  @param int starting money;
         */
        NormalPlayer(int);

        /**
         *  @Override from base class Player
		 *	Prints all information about the player
		 */
		void printInfo();

        /**
         * @brief 
         * Set splitStatus
         */
        void setSplitStatus(int);

        /**
         * @brief 
         * @return int splitStatus
         */
        int getSplitStatus() const;

        /**
         * @brief 
         * @Override reset from base class Player
         * Reset player from variables
         */
        void reset();

        /**
         *  @return bool if player is bankcrupt
         */
        bool isBankrupt() ;

        /**
         *  @return capability of player to split his cards
         */
        bool canSplit() const;

        /**
         *  Splits the card of the player.
         */
        void split();

        /**
         *  @return bool if player already split his card
         */
        bool isHandSplited() const;

        /**
         *  @return total money of player
         */
        float getMoney() const;

        /**
         *  Add winnings to the total money.
         *  @param float - winnings to be added.
         */
        void addWinnings(float);

        /**
         *  Payout and subtracts to total money.
         *  @param float - money to payout
         */
        void payOut(float);
        
        /**
         * @brief Get the Secondary Hand object
         * 
         * @return Hand* 
         */
        Hand *getSecondaryHand() const;

        /**
		 *	@return hands at index
		 *	index must only be 0 (primary) or 1 (secondary) if player splits
		 */
		Hand *getHandAt(int) const;
        
        /**
         *  Destructor for NormalPlayer
         */
        ~NormalPlayer();
    
    private:
        bool handSplited;
        int splitStatus;
        bool bankrupt;
        float money;


};

#endif
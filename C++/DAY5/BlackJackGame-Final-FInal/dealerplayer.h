/**
 *  Declaration of class DealerPlayer
 *  Derived from class Player 
 */

#ifndef DEALERPLAYER_H
#define DEALERPLAYER_H

#include "player.h"

class DealerPlayer : public Player {

    public:
        /**
         *  Constructor for Class DealerPlayer 
         */
        DealerPlayer();

        /**
         *   @Override from base class Player
	     *   Prints all information about the player
	     */
	    void printInfo();

        /**
         *  Decision making for the dealerPlayer
         *  @return const string decision
         */
        int decide() const;

        /**
         *  Destructor for class DealerPlayer
         */
        ~DealerPlayer();
};

#endif
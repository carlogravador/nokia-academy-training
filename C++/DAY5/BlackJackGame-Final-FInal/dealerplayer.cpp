/**
 *  Member function definition for Class DealerPlayer
 *  Derived from Class Player
 */

#include<iostream>

using std::cout;
using std::endl;

#include "dealerplayer.h"


DealerPlayer::DealerPlayer(){
    hands = new Hand* [1];
    hands[0] = new Hand();
}

void DealerPlayer::printInfo(){
    cout << "--------DEALER-------" << endl;
    Player::printInfo();
    getPrimaryHand()->printAllCards(true);
    cout << "Score: " << getPrimaryHand()->getScore() << endl;
    cout << "Status: " << getPrimaryHand()->getStatus() << endl;
}

int DealerPlayer::decide() const{
    
    if(getPrimaryHand()->getScore() <= 17){
        getPrimaryHand()->setDecision(Hand::DECISION_HIT);
    } else {
        getPrimaryHand()->setDecision(Hand::DECISION_STAND);
    }
    
    return getPrimaryHand()->getDecision();
}

DealerPlayer::~DealerPlayer(){
    delete hands[0];
    delete hands;
}
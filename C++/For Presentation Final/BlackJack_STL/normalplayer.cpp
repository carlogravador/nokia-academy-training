/**
 *  Member function definition for Class NormalPlayer
 *  Derived from Class Player
 */
#include<iostream>

using std::cout;
using std::endl;

#include "normalplayer.h"

NormalPlayer::NormalPlayer(int money){
    hands.push_back(new Hand());
    handSplited = false;
    bankrupt = false;
    splitStatus = 0;
    this->money = money;
}

void NormalPlayer::printInfo(){
    Player::printInfo();
    cout << "Money: " << getMoney() << endl;
    
    int i = 0;
    for(auto &h : hands){
        i++;
        cout << "Hand " << i << endl;
        h->printHandInfo();
    }

}

void NormalPlayer::reset(){
    Player::reset();
    if(isHandSplited()){
        std::vector<Hand*>::iterator it = hands.begin();
        it++;
        Hand *secondHand = getHandAt(1);
        secondHand->reset();
        hands.erase(it);
        delete secondHand;
        
    } 
    handSplited = false;
    splitStatus = 0;
}

bool NormalPlayer::isBankrupt() {
    return bankrupt;
}

bool NormalPlayer::canSplit() const{ 
    return getPrimaryHand()->isSplitable() &&
        (getPrimaryHand()->getBet() * 2) <= money;
}

int NormalPlayer::getSplitStatus() const {
    return splitStatus;
}

void NormalPlayer::setSplitStatus(int status){
    splitStatus = status;
}

void NormalPlayer::split(){
    Card *temp = hands[0]->getCardAt(1);
    hands.push_back(new Hand());
    hands[1]->putCard(temp);
    hands[0]->removeCard(temp);
    handSplited = true;
    setSplitStatus(SPLIT_ACCEPT);
}

bool NormalPlayer::isHandSplited() const{
    return handSplited;
}

float NormalPlayer::getMoney() const{
    return money;
}

void NormalPlayer::addWinnings(float winnings) {
    money += winnings;
}

void NormalPlayer::payOut(float payOut){
    money -= payOut;
    if (money <= 0) bankrupt = true;
}

Hand* NormalPlayer::getSecondaryHand() const {
    return hands[1];
}

Hand* NormalPlayer::getHandAt(int index) const{
    return hands[index];
}

vector<Hand *> NormalPlayer::getAllHands() const {
	return hands;
}

NormalPlayer::~NormalPlayer(){

}

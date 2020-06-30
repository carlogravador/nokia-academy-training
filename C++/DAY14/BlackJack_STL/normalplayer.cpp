/**
 *  Member function definition for Class NormalPlayer
 *  Derived from Class Player
 */
#include<iostream>

using std::cout;
using std::endl;

#include "normalplayer.h"

NormalPlayer::NormalPlayer(int money){
    hands = new Hand* [2];
    hands[0] = new Hand();
    handSplited = false;
    bankrupt = false;
    splitStatus = 0;
    handCount = 1;
    this->money = money;
}

void NormalPlayer::printInfo(){
    Player::printInfo();
    cout << "Money: " << getMoney() << endl;

    for(int i = 0; i < 2; i++){
        cout << "Hand " << i + 1 << endl;
        getHandAt(i)->printHandInfo();
        if(!isHandSplited()) break;
    }
}

void NormalPlayer::reset(){
    Player::reset();
    handSplited = false;
    splitStatus = 0;
    handCount = 1;
    if(isHandSplited()) getHandAt(1)->reset();
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
    hands[1] = new Hand();
    hands[1]->putCard(temp);
    hands[0]->putCard(NULL);
    handCount++;
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
    if(handSplited) delete hands[1];
    delete hands[0];
    delete hands;
}

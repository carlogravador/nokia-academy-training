/**
 *	Member function definition
 *  for Class Hand
 */
#include<iostream>

using std::cout;
using std::endl;

#include "hand.h"

const string Hand::STATUS_BLACKJACK = "BLACKJACK!";
const string Hand::STATUS_BUST = "BUSTED!";
const string Hand::STATUS_WIN = "WIN!";
const string Hand::STATUS_LOSE = "LOSE!";
const string Hand::STATUS_SURRENDER = "SURRENDER!";

Hand::Hand(){
    cardCount = 0;
    score = 0;
    status = "?";
    bet = 0;
    decision = DECISION_HIT;
}

int Hand::getCardCount() const {
    return cardCount;
}

int Hand::getScore() const{
    return score;
}

string Hand::getStatus() const{
    return status;
}

void Hand::setStatus(const string status){
    this->status = status;
}

void Hand::setBet(float bet){
    this->bet = bet;
}

float Hand::getBet() const{
    return bet;
}

void Hand::setDecision(int decision){
    this->decision = decision;
}

int Hand::getDecision() const{
    return decision;
}

void Hand::putCard(Card *c){
    if(c == NULL) cardCount--;
    if(cardCount >= 0) card[cardCount] = c;
    if(c != NULL) cardCount++;
    computeBestScore();
}

Card* Hand::getCardAt(int index) const{
    return card[index];
}

void Hand::printAllCards(){
    for(int i = 0; i < cardCount; i++){
        getCardAt(i)->print();
    }
}

void Hand::printAllCards(bool show){
    for(int i = 0; i < cardCount; i++){
        if(show){
            getCardAt(i)->show();
        } else {
            getCardAt(i)->hide();
        }
        
        getCardAt(i)->print();
    }
}

void Hand::printHandInfo(){
    cout << "Bet: " << getBet() << endl;
    printAllCards();
    cout << "Score: " << getScore() << endl;
    cout << "Status: " << getStatus() << endl;
}

bool Hand::isBlackJack() const{
    return score == 21 && cardCount == 2;
}

bool Hand::isBusted() const{
    return score > 21;
}

bool Hand::isSplitable() const{
    return getCardAt(0)->getValue() == getCardAt(1)->getValue();
}

void Hand::hit(Card *cardReceived){
    putCard(cardReceived);
    setDecision(DECISION_HIT);
}

void Hand::stand(){
    setDecision(DECISION_STAND);
}

bool Hand::canDouble(float pMoney) const{
    return bet * 2 <= pMoney;
}

void Hand::doubleMove(Card *cardReceived){
    setBet(bet * 2);
    hit(cardReceived);
    stand();
}

void Hand::surrender(){
    setStatus(STATUS_SURRENDER);
}

void Hand::reset(){
    while(cardCount != 0) putCard(NULL);
    score = 0;
    status = "?";
    bet = 0;
    decision = DECISION_HIT;
}

void Hand::computeBestScore(){
    int aceCtr = 0;
    score = 0;
    for(int i = 0; i < cardCount; i++){
        if(getCardAt(i)->getValue() == 1){
            aceCtr++;
        }
    }

    for(int i = 0; i < cardCount; i++){
        score += getCardAt(i)->getValue();
    }

    while(aceCtr > 0 && score > 21) {
        score -= 10;
        aceCtr--;
    }

}

Hand::~Hand(){

}

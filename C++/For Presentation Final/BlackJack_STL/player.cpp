/**
 *	Member function definition
 *  for Class Player
 */
#include<iostream>

using std::cout;
using std::endl;

#include "player.h"

int Player::count = 0;

Player::Player(){
    id = count;
    count++;
}

Hand* Player::getPrimaryHand() const{
    return hands[0];
}

void Player::printInfo(){
    cout << "Player id: " << getId() << endl;
}

int Player::getId() const{
    return id;
}

void Player::reset(){
    getPrimaryHand()->reset();
}

Player::~Player(){
   for(auto &h : hands){
       delete h;
   }
}

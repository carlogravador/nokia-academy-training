#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#include "deck.h"

int main(){

	Deck *deck = new Deck(4);
	deck->shuffle();
	
	Card c1 = deck->getCard();
	Card c2 = deck->getCard();
	
	c1.print();
	c2.print();


}

/**
 *	Member function definition
 *	for Class Deck
 */
#include<string>
#include <new>
#include<cstdlib>

#include "deck.h"

Deck::Deck(int _size){

	this->size = 52 * _size;
	this->index = 0;
	
	int j = 0, k = 0;
	int values[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
	string suit[4] = {
		"\u2666",	//diamond
		"\u2665",	//heart
		"\u2663",	//clubs
		"\u2660"	//spades 
	};
	
	cards = new Card* [size];
	
	for(int i = 0; i < size; i++) {
		cards[i] = new Card(suit[j], k + 1, values[k], false);
		k++;
		if(((i + 1) % 13) == 0) j++;
		if((k % 13) == 0) k = 0;
		if(((i + 1) % 52) == 0) j = 0;
	}
	
}

void Deck::swap(Card **card1, Card **card2){
	Card *temp = *card1;
	*card1 = *card2;
	*card2 = temp;
}

void Deck::shuffle(){
	srand(time(0));
	
	for(int i = size - 1; i > 0; i--){
		int r = rand() % (i + 1);
		swap(&cards[i], &cards[r]);
	}	
}

int Deck::getSize() const{
	return size;
}

int Deck::getDeckCount() const{
	return size / 52;
}

int Deck::getIndex() const{
	return index;
}

int Deck::remainingCards() const{
	return size - index;
}

Card* Deck::getCard(){
	Card *c = cards[index];
	index++;

	return c;
}

void Deck::reset(){
	index = 0;
	shuffle();
}


Deck::~Deck(){
	for(int i = size - 1; i > 0; i--){
		delete cards[i];
	}
	delete cards;
}



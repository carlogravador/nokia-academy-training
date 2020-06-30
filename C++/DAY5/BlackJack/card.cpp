/*
	Member function implementation
	for Class Card
*/

#include<iostream>

using std::cout;
using std::endl;

#include "card.h"

Card::Card(string suit, int number, int value, bool isShow) {
	this->suit = suit;
	this->number = number;
	this->value = value;
	this->isShow = isShow;
}

int Card::getValue() {
	return value;
}

void Card::print() {
	bool flags = false;
	char nameEquiv;

	switch(number){
		case 1:
			nameEquiv = 'A';
			flags = true;
			break;
		case 11:
			nameEquiv = 'J';
			flags = true;
			break;
		case 12:
			nameEquiv = 'Q';
			flags = true;
			break;
		case 13:
			nameEquiv = 'K';
			flags = true;
			break;
	
	}

	if(isShow) {
		if(flags) {
			cout << nameEquiv << " of " << suit << endl;
		} else {
			cout << number << " of " << suit << endl;
		}
	} else {
		cout << "?\n";
	}

}

void Card::show() {
	isShow = true;
}

void Card::hide() {
	isShow = false;
}

Card::~Card() {
	
}





#include<cmath>
#include<iostream>
#include "island.h"

Island::Island(){
	xCord = 0;
	yCord = 0;
}

Island::Island(double x, double y){
	xCord = x;
	yCord = y;
}

void Island::setX(double x) {
	xCord = x;
}

void Island::setY(double y) {
	yCord = y;
}

double Island::getX() const{
	return xCord;
}

double Island::getY() const{
	return yCord;
}

double Island::getDistanceTo(Island *i) const{
	return sqrt(pow(xCord - i->getX(), 2) + pow(yCord - i->getY(), 2));
}

Island::~Island(){
}

void Island::print(){
	cout << "(" << xCord <<  ", " << yCord << ")" << endl;
}

#include <cmath>
#include "point.h"

Point::Point(double x, double y){
	this->x = x;
	this->y = y;
}

double Point::getDistanceTo(Point *p) const{
	double distance = 0;
	double x = p->getX() - this->getX();
	double y = p->getY() - this->getY();
	
	distance = sqrt( pow(x, 2) + pow(y, 2));
	
	return distance;
}

double Point::getX() const {
	return x;
}

double Point::getY() const {
	return y;
}

Point::~Point(){

}

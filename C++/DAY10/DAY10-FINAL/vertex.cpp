#include <cmath>
#include "vertex.h"

Vertex::Vertex(double x, double y){
	this->x = x;
	this->y = y;
}

double Vertex::getDistanceTo(Vertex *v) const{
	double distance = 0;
	double x = v->getX() - this->getX();
	double y = v->getY() - this->getY();
	
	distance = sqrt( pow(x, 2) + pow(y, 2));
	
	return distance;
}

double Vertex::getX() const {
	return x;
}

double Vertex::getY() const {
	return y;
}

Vertex::~Vertex(){

}

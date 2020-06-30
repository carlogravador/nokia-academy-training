#ifndef ISLAND_H
#define ISLAND_H

#include<string>
using namespace std;

class Island {

	public:
		Island();
		Island(double, double);
		void setX(double);
		void setY(double);
		double getX() const;
		double getY() const;
		double getDistanceTo(Island*) const;
		~Island();

		void print();
	
	private:
		double xCord;
		double yCord;
};

#include "island.cpp"

#endif

#ifndef POINT_H
#define POINT_H

class Point {
	public:
		Point(double, double);
		double getDistanceTo(Point *) const;
		double getX() const;
		double getY() const;
		~Point();
		
	private:
		double x;
		double y;
};

#include "point.cpp"

#endif

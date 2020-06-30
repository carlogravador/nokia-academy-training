#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
	public:
		Vertex(double, double);
		double getDistanceTo(Vertex *) const;
		double getX() const;
		double getY() const;
		~Vertex();
		
	private:
		double x;
		double y;
};

#include "vertex.cpp"

#endif

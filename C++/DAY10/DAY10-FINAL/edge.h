#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

class Edge {

	public:
		Edge(Vertex*, Vertex*);
		double getWeight() const;
		Vertex *getStart() const;
		Vertex *getEnd() const;
		~Edge();
		
	private:
		Vertex *start;
		Vertex *end;
		double weight;

};

#include "edge.cpp"

#endif

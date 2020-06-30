#include "edge.h"

Edge::Edge(Vertex *s, Vertex *e){
	start = s;
	end = e;
	weight = start->getDistanceTo(end);
}

double Edge::getWeight() const {
	return weight;
}

Vertex* Edge::getStart() const {
	return start;
}

Vertex* Edge::getEnd() const {
	return end;
}

Edge::~Edge(){

}

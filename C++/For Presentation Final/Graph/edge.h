#ifndef EDGE_H
#define EDGE_H

template <class T> class Vertex;

template <class T>
class Edge {
	public:
		Edge(Vertex<T> *, double);
		void setWeight(double);
		double getWeight() const;
		void setVisited(bool);
		bool isVisited() const;
		Vertex<T> *getEnd() const;
		~Edge();
	private:
		double weight;
		bool visited;
		Vertex<T> *end;
};

#include "edge.cpp"

#endif

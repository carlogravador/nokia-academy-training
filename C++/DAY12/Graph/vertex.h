#ifndef VERTEX_H
#define VERTEX_H

#include<vector>
#include<queue>

using namespace std;

template <class T> class Edge;

template <class T>
class Vertex {
	public:
		Vertex(T);
		T getData() const;
		bool isVisited() const;
		void setVisited(bool);
		void addEdgeTo(Vertex<T> *, double);
		bool removeEdgeTo(Vertex<T> *);
		void setValue(double);
		double getValue() const;
		void setPrev(Vertex<T> *);
		Vertex<T> *getPrev() const;
		Vertex<T> *getNext() const;
		vector<Edge<T> *> getAdjacent() const;
		~Vertex();
	private:
		vector<Edge<T> *> adjacent;
		T data;
		bool visited;
		double value;
		Vertex<T> *prev;
};

#include "vertex.cpp"

#endif

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include "edge.h"
#include "vertex.h"

using namespace std;

template <class T>
class Graph {

	public:
		Graph();
		bool addVertex(T);
		bool removeVertex(T);
		bool addEdge(T, T, double);
		bool removeEdge(T, T);
		int size() const;
		stack<T> dijkstra(T, T, double &);
		vector<Vertex<T> *> getVertices() const;
		~Graph();
	private:
		vector<Vertex<T> *> vertices;
		int s;
};

#include "graph.cpp"

#endif

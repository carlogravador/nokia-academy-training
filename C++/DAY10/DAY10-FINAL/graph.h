#ifndef GRAPH_H
#define GRAPH_H

#include "linkedlist.h"
#include "edge.h"
#include "vertex.h"

class Graph {
	
	public:
		Graph();
		void addEdge(Edge*);
		LinkedList<Vertex*> *getVertices();
		void addVertex(Vertex*);
		double minCost();
		~Graph();
	
	private:
		LinkedList<Edge*> *edges;
		LinkedList<Vertex*> *vertices;
		
};

#include "graph.cpp"

#endif


#include<iostream>
#include<limits>
#include "graph.h"

#define MAX numeric_limits<double>::max()

using namespace std;

Graph::Graph(){
	edges = new LinkedList<Edge*>();
	vertices = new LinkedList<Vertex*>();
}

void Graph::addEdge(Edge* edge){
	edges->add(edge);
}

LinkedList<Vertex*>* Graph::getVertices() {
	return vertices;
}

void Graph::addVertex(Vertex *v){
	vertices->add(v);
}

double Graph::minCost(){
	double cost = 0;
	double immediateMin = MAX;
	double tempMin;
	LinkedList<Vertex*> *visited = new LinkedList<Vertex*>();
	Vertex *start = vertices->get();
	Vertex *end;
	Vertex *s;
	Vertex *e;
	vertices->remove(start);
	visited->add(start);
	vertices->rewind();
	while(!vertices->isEmpty()){
		immediateMin = MAX;
		while(!visited->endOfList()){
			start = visited->get();
			vertices->rewind();
			while(!vertices->endOfList()){
				end = vertices->get();
				tempMin = start->getDistanceTo(end);
				if(tempMin < immediateMin){
					immediateMin = tempMin;
					s = start;
					e = end;
				}
			}
			vertices->rewind();
		}
		Edge *edge = new Edge(s, e);
		edges->add(edge);
		visited->add(e);
		vertices->remove(e);
		cost += immediateMin;
		visited->rewind();
	}
	
	delete vertices;
	vertices = visited;
	return cost;
}

Graph::~Graph(){
	vertices->rewind();
	while(!vertices->endOfList()){
		Vertex *v = vertices->get();
		delete v;
	}
	delete vertices;
	
	edges->rewind();
	while(!edges->endOfList()){
		Edge *e = edges->get();
		delete e;
	}
	delete edges;
}

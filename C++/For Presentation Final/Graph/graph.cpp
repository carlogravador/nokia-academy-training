#include <limits>
#include "graph.h"

#define INFINITY std::numeric_limits<double>::max()


template <class T>
Graph<T>::Graph(){
	s = 0;
}

template <class T>
stack<T> Graph<T>::dijkstra(T start, T end, double &pathCost){
	queue<Vertex<T> *> q;
	stack<T> s;
	
	Vertex<T> *startV, *endV;
	bool errorFlag = true;
	int foundCtr = 0;
	for(auto &vertex : vertices){
		if(vertex->getData() == start){
			startV = vertex;
			foundCtr++;
		}
		
		if(vertex->getData() == end){
			endV = vertex;
			foundCtr++;
		}
		
		if(foundCtr == 2) {
			errorFlag = false;
			break;
		}
		
	}
	
	if(errorFlag) return s;
	
	for(auto &v : vertices){
		v->setValue(INFINITY);
		v->setVisited(false);
	}
	
	startV->setValue(0);
	startV->setVisited(true);
	q.push(startV);
	
	while(!q.empty()){
		Vertex<T> *v = q.front();
		q.pop();
		for(auto &e: v->getAdjacent()){
			Vertex<T> *v1 = e->getEnd();
			double cost = v->getValue() + e->getWeight();
			if(!v1->isVisited()){
				v1->setValue(cost);
				v1->setVisited(true);
				v1->setPrev(v);
				q.push(v1);
			} else {
				if(cost < v1->getValue()){
					v1->setValue(cost);
					v1->setPrev(v);
				}
			}
		}			
	}
	
	pathCost = endV->getValue();
	
	while(endV != NULL){
		s.push(endV->getData());
		endV = endV->getPrev();
	}
	
	
		
	return s;
}

template <class T>
bool Graph<T>::addVertex(T data){
	for(auto &vertex : vertices){
		if(vertex->getData() == data){
			return false;
		}
	}
	Vertex<T> *v = new Vertex<T>(data);
	vertices.push_back(v);
	s++;
	return true;	
}

template <class T>
bool Graph<T>::removeVertex(T data){
	typename std::vector<Vertex<T> *>::iterator it;
	typename std::vector<Vertex<T> *>::iterator it2;
	for(it = vertices.begin(); it != vertices.end(); it++){
		Vertex<T> *vertex = *it;
		if(vertex->getData() == data){
			vertices.erase(it);
			for(it2 = vertices.begin(); it2 != vertices.end(); it2++){
				Vertex<T> *vertex2 = *it2;
				vertex2->removeEdgeTo(vertex);
			}
			delete vertex;
			s--;
			return true;
		}
	}

	return false;
}

template <class T>
bool Graph<T>::addEdge(T start, T end, double weight){
	int foundCtr = 0;
	Vertex<T> *startV, *endV;
	for(auto &vertex : vertices){
		if(vertex->getData() == start){
			startV = vertex;
			foundCtr++;
		}
		
		if(vertex->getData() == end){
			endV = vertex;
			foundCtr++;
		}
		
		if(foundCtr == 2) {
			startV->addEdgeTo(endV, weight);
			return true;
		}
	}
	return false;	
}

template <class T>
bool Graph<T>::removeEdge(T start, T end){
	int foundCtr = 0;
	Vertex<T> *startV, *endV;
	for(auto &vertex : vertices){
		if(vertex->getData() == start){
			startV = vertex;
			foundCtr++;
		}
		
		if(vertex->getData() == end){
			endV = end;
			foundCtr++;
		}
		
		if(foundCtr == 2){
			return startV->removeEdgeTo(endV);
		}
	}
	return false;
}

template <class T>
int Graph<T>::size() const {
	return s;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertices() const {
	return vertices;
}

template <class T>
Graph<T>::~Graph(){
	for(auto &v : vertices){
		delete v;
	}
}

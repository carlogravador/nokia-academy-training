#include "vertex.h"

using namespace std;

template <class T>
Vertex<T>::Vertex(T d){
	data = d;
	visited = false;
	value = 0;
	prev = NULL;
}

template <class T>
Vertex<T> * Vertex<T>::getPrev() const {
	return prev;
}

template <class T>
void Vertex<T>::setPrev(Vertex<T> *pV) {
	prev = pV;
}

template <class T>
T Vertex<T>::getData() const {
	return data;
}

template <class T>
double Vertex<T>::getValue() const {
	return value;
}

template <class T>
void Vertex<T>::setValue(double v){
	value = v;
}

template <class T>
bool Vertex<T>::isVisited() const{
	return visited;
}

template <class T> 
void Vertex<T>::setVisited(bool status){ 
	visited = status; 
}

template <class T>
void Vertex<T>::addEdgeTo(Vertex<T> *end, double weight){
	Edge<T> *e = new Edge<T>(end, weight);
	adjacent.push_back(e);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *end){
	typename std::vector<Edge<T> *>::iterator it;
	for(it = adjacent.begin(); it != adjacent.end(); it++){
		Edge<T> *e = *it;
		if(e->getEnd() == end){
			adjacent.erase(it);
			delete e;
			return true;
		}
	}
	return false;
}

template <class T>
Vertex<T> * Vertex<T>::getNext() const {
	return next;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdjacent() const {
	return adjacent;
}

template <class T>
Vertex<T>::~Vertex(){
	for(auto &e : adjacent)	{
		delete e;
	}
}



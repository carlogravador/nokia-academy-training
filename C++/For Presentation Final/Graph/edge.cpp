#include "edge.h"

template <class T>
Edge<T>::Edge(Vertex<T> *e, double w){
	end = e;
	weight = w;
	visited = false;
}

template <class T>
void Edge<T>::setWeight(double w){
	weight = w;
}

template <class T>
void Edge<T>::setVisited(bool status){
	visited = status;
}

template <class T>
bool Edge<T>::isVisited() const {
	return visited;
}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template <class T>
Vertex<T> * Edge<T>::getEnd() const {
	return end;
}

template <class T>
Edge<T>::~Edge(){

}

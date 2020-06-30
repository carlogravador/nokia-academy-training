#include <limits>
#include "shortestpathfinder.h"

using namespace std;

ShortestPathFinder::ShortestPathFinder(LinkedList<Island*> *toVisit){
	this->toVisit = toVisit;
	cost = 0;
}

LinkedList<Island*>* ShortestPathFinder::getShortestPath(){
	toVisit->rewind();
	shortestPath = new LinkedList<Island*>();
	Island *current = toVisit->getRandom();
	Island *next;
	Island *nearest;
	shortestPath->add(current);
	toVisit->remove(current);

	double tempLow = 0;
	double max = numeric_limits<double>::max();
	double lowestCost = max;
	toVisit->rewind();
	while(!toVisit->isEmpty()){
		while(!toVisit->endOfList()){
			next = toVisit->get();
			tempLow = current->getDistanceTo(next);
			if(tempLow < lowestCost){
				lowestCost = tempLow;
				nearest = next;
			}
		}
		current = nearest;
		shortestPath->add(nearest);
		toVisit->remove(nearest);
		tempLow = 0;
		lowestCost = max;
		toVisit->rewind();
	}
	return shortestPath;
}

double ShortestPathFinder::getCost(){
	cost = 0;
	Island *current = shortestPath->get();
	Island *next;
	while(!shortestPath->endOfList()){
		next = shortestPath->get();
		cost += current->getDistanceTo(next);
		current = next;
	}
	
	return cost;	
}

ShortestPathFinder::~ShortestPathFinder(){
	delete shortestPath;
}




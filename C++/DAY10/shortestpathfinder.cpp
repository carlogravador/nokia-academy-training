
#include "shortestpathfinder.h"

ShortestPathFinder::ShortestPathFinder(LinkedList<Island*> *toVisit){
	this->toVisit = toVisit;
	cost = 0;
}

LinkedList<Island*>* ShortestPathFinder::getShortestPath(){
	
	shortestPath = new LinkedList<Island*>();
	Island *current = toVisit->pull(toVisit->get());
	Island *next;
	Island *nearest;
	toVisit->rewind();
	shortestPath->add(current);
	
	double tempLow = 0;
	double lowestCost = 0;
	int ctr = 0;
	
	while(!toVisit->endOfList()){
		tempLow = 0;
		lowestCost = 0;
		while(!toVisit->endOfList()){
			next = toVisit->get();
			tempLow = current->getDistanceTo(next);
			cout << "next: " << next << endl;
			cout << "toVisit: " << toVisit->endOfList() << endl;
			cout << "tempLow: " << tempLow << endl;
			if(tempLow < lowestCost){
				lowestCost = tempLow;
				nearest = next;
			}
		}
		shortestPath->add(nearest);
		current = nearest;
		cout << "reach here\n";
		toVisit->pull(nearest);
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




#ifndef SHORTESTPATHFINDER_H
#define SHORTESTPATHFINDER_H

#include "linkedlist.h"
#include "island.h"

class ShortestPathFinder {

	public:
		ShortestPathFinder(LinkedList<Island*>*);
		LinkedList<Island*> *getShortestPath(); 
		double getCost();
		~ShortestPathFinder();
	
	private:
		LinkedList<Island*> *toVisit;
		LinkedList<Island*> *shortestPath;
		double cost;
		
};

#include "shortestpathfinder.cpp"


#endif

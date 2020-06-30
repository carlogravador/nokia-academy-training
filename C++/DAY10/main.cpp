#include <iostream>
#include "linkedlist.h"
#include "island.h"
#include "shortestpathfinder.h"

using namespace std;


int main (){
	
	LinkedList<Island*> *toVisit = new LinkedList<Island*>();
	
	toVisit->add(new Island(10,2));
	toVisit->add(new Island(5,9));
	toVisit->add(new Island(15,2));
	
	ShortestPathFinder *spt = new ShortestPathFinder(toVisit);
	LinkedList<Island*> *bestRoute = spt->getShortestPath();
	cout << "Cost: " << spt->getCost() << endl;
	
	return 0;
}

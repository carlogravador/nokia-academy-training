#include <iostream>
#include <fstream>
#include "linkedlist.h"
#include "island.h"
#include "shortestpathfinder.h"

using namespace std;


int main (){
	
	LinkedList<Island*> *toVisit = new LinkedList<Island*>();
	ifstream input("input.txt");
	while(1){
		int x, y;
		input >> x >> y;
		toVisit->add(new Island(x, y));
		if(input.eof()) break;
	}
	
	ShortestPathFinder *spt = new ShortestPathFinder(toVisit);
	LinkedList<Island*> *bestRoute = spt->getShortestPath();

	while(!bestRoute->endOfList()){
		Island *curr = bestRoute->get();
		curr->print();
	}
	bestRoute->rewind();
	cout << "Cost: " << spt->getCost() << endl;

	bestRoute->rewind();
	while(!bestRoute->endOfList()){
		Island *curr = bestRoute->get();
		delete curr;
	}
	delete spt;
	delete toVisit;
	input.close();
	return 0;
}

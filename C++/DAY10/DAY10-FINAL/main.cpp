#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main (){
	Graph *graph = new Graph();
	ifstream input("input.txt");
	while(1){
		double x, y;
		input >> x >> y;
		Vertex *v = new Vertex(x, y);
		graph->addVertex(v);
		if(input.eof()) break;
	}
	
	cout << "Minimun cost: " << graph->minCost() << endl;
	
	
	input.close();
	delete graph;
	return 0;
}

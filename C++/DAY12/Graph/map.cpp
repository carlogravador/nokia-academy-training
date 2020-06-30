#include "map.h"

const string Map::MOVE_UP = "UP";
const string Map::MOVE_DOWN = "DOWN";
const string Map::MOVE_LEFT = "LEFT";
const string Map::MOVE_RIGHT = "RIGHT";

//private
Point * Map::addPoint(Point *sPoint, int row, int col){
	char c;
	double w;
	Point *p;
	matrix->getDataAt(c, row, col);
//	cout << "FOUND: " << c << endl;	
	if(c == Map::STOP || c == Map::END){
		p = new Point(col, row);
		if(c == Map::END) end = p;
		points.push_back(p);
		matrix->setDataAt(Map::VISITED, row, col);
		graph.addVertex(p);
		w = sPoint->getDistanceTo(p);
		graph.addEdge(sPoint, p, w);
		return p;
	} 
	
	p = findPoint(col, row);
	w = sPoint->getDistanceTo(p);
	graph.addEdge(sPoint, p, w);
	
	return NULL;	
}

Point * Map::findPoint(int x, int y) {
	for(auto &p : points){
		if(p->getX() == x && p->getY() == y){
			return p;
		}
	}
	return NULL;
}

string Map::convertToMove(Point *start, Point *end){
	string move;
	
	if(start->getX() == end->getX()){	//vertical move
		double direction = start->getY() - end->getY();
		if(direction > 0){	//downward move
			move = MOVE_DOWN;
		} else {
			move = MOVE_UP;
		}
	} else {
		double direction = start->getX() - end->getX();
		if(direction > 0){	//downward move
			move = MOVE_RIGHT;
		} else {
			move = MOVE_LEFT;
		}
	}
	
	return move;
}

//public
Map::Map(Matrix<char> *src){
	matrix = src;
	start = NULL;
	end = NULL;
}

vector<string> Map::getMovesToFinish(double &cost){
	vector<string> moves;
	
	stack<Point *> path = graph.dijkstra(start, end, cost);
	if(path.size() == 0) {
		moves.push_back("No solution");
		return moves;
	}
	
	Point *startPoint;
	Point *endPoint = path.top();
	path.pop();
	while(!path.empty()){
		startPoint = path.top();
		path.pop();
		
		string move = convertToMove(startPoint, endPoint);
		moves.push_back(move);
		
		endPoint = startPoint;
	}
	
	return moves;
}

void Map::findAllPossiblePoints(){
	int row, col;
	matrix->find(Map::START, row, col);
	matrix->setDataAt(Map::VISITED, row, col);
	start = new Point(col, row);
	points.push_back(start);
	graph.addVertex(start);
	findAllPossiblePoints(start);
}

void Map::findAllPossiblePoints(Point *sPoint){
	if(sPoint == NULL){
		return;
	}

	int row, col;
	bool found = false;
	Point *p;
	
	found = matrix->findRight('*', sPoint->getY(), sPoint->getX(), row, col);
	if(found){
		col = col - 1;
		if(col != sPoint->getX()) {
			p = addPoint(sPoint, row, col);	
			findAllPossiblePoints(p);
		}
	}	
	
	found = matrix->findUp('*', sPoint->getY(), sPoint->getX(), row, col);
	if(found){
		row = row + 1;
		if(row != sPoint->getY()) {
			p = addPoint(sPoint, row, col);	
			findAllPossiblePoints(p);
		}		
	}
	
	found = matrix->findLeft('*', sPoint->getY(), sPoint->getX(), row, col);
	if(found){
		col = col + 1;
		if(col != sPoint->getX()) {		
			p = addPoint(sPoint, row, col);	
			findAllPossiblePoints(p);
		}
		
	}
	
	found = matrix->findDown('*', sPoint->getY(), sPoint->getX(), row, col);
	if(found){
		row = row - 1;
		if(row != sPoint->getY()) {
			p = addPoint(sPoint, row, col);	
			findAllPossiblePoints(p);
		}		
	}
}

Map::~Map(){
	for(auto &p: points){
		delete p;
	}
}

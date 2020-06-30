#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "matrix.h"
#include "point.h"
#include "graph.h"

class Map {
	public:	
		static const char START = 'A';
		static const char END = 'B';
		static const char STOP = ' ';
		static const char VISITED = 'V';
		static const char WALL = '*';
		
		static const string MOVE_UP;
		static const string MOVE_DOWN;
		static const string MOVE_LEFT;
		static const string MOVE_RIGHT;
	
		Map(Matrix<char> *);
		void findAllPossiblePoints();
		vector<string> getMovesToFinish(double &);
		~Map();

	private:
		Matrix<char> *matrix;
		vector<Point *> points;
		Graph<Point*> graph;
		Point *start;
		Point *end;
		
		string convertToMove(Point *, Point *);
		Point *addPoint(Point*, int, int);
		Point* findPoint(int, int);
		void findAllPossiblePoints(Point *);
		
};

#include "map.cpp"

#endif

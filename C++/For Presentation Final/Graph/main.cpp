#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <queue>
#include "graph.h"
#include "matrix.h"
#include "point.h"
#include "map.h"

#define LEN 1024

using namespace std;

Matrix<char> **readFile(int &out){
	char buffer[LEN] = {0};
	Matrix<char> **m;
	ifstream input("input.txt");
	int size;
	input.getline(buffer, LEN);
	size = atoi(buffer);
	out = size;
	m = new Matrix<char>* [size];
	for(int i = 0; i < size; i++){
		int row, col;
		input.getline(buffer, LEN);
		row = atoi(buffer);
		input.getline(buffer, LEN);
		col = atoi(buffer);
		m[i] = new Matrix<char>(row, col);
		for(int j = 0; j < row; j++){
			memset(buffer, '\0', LEN);
			input.getline(buffer, LEN);
			for(int k = 0; k < col; k++){
				char c = buffer[k];
				m[i]->setDataAt(c, j, k);
			}
		}
	}
	
	input.close();
	return m;
}


int main(){
	int mArraySize = 0;	
	Matrix<char> **mArray = readFile(mArraySize);
	
	for(int i = 0; i < mArraySize; i++){
		cout << "-----------------------------------\n";
		Map *map = new Map(mArray[i]);
		double cost = 0;
		map->findAllPossiblePoints();
		vector<string> moves = map->getMovesToFinish(cost);
		cout << "Cost: " << cost << endl;
		for(string s : moves){
			cout << s << endl;
		}	
		delete map;
	}
	
	for(int i = 0; i < mArraySize; i++){
		delete mArray[i];
	}
	delete mArray;
	cout << "End of program\n";
	return 0;
}

#ifndef MATRIX_H
#define MATRIX_H

#include "point.h"

using namespace std;

template<class T>
class Matrix {
	public:
		Matrix(int, int);
		void setDataAt(T, int, int);
		bool getDataAt(T &, int, int) const;
		void getDimension(int &, int &) const;
		int getRow() const;
		int getCol() const;
		bool find(T, int &, int&);
		bool findUp(T, int, int, int&, int&);
		bool findDown(T, int, int, int&, int&);
		bool findLeft(T, int, int, int&, int&);
		bool findRight(T, int, int, int&, int&);
		~Matrix();
	private:
		int row;
		int col;
		T **data;
		
};

#include "matrix.cpp"

#endif

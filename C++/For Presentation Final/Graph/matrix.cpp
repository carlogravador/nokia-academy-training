#include "matrix.h"

template<class T>
Matrix<T>::Matrix(int r, int c){
	row = r;
	col = c;
	data = new T* [row];
	for(int i = 0; i < row; i++){
		data[i] = new T [col];
	}
}

template<class T>
void Matrix<T>::setDataAt(T d, int r, int c) {
	data[r][c] = d;
	
}

template<class T>
bool Matrix<T>::getDataAt(T &dOut, int r, int c) const{
	if(r > row - 1|| c > col - 1) return false;
	dOut = data[r][c];
	return true;
}

template<class T>
void Matrix<T>::getDimension(int &r, int &c) const{
	r = row;
	c = col;
}

template<class T>
int Matrix<T>::getRow() const {
	return row;
}

template<class T>
int Matrix<T>::getCol() const {
	return col;
}

template<class T>
bool Matrix<T>::find(T toFind, int &posR, int &posC){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(toFind == data[i][j]) {
				posR = i;
				posC = j;
				return true;
			}
		}
	}
	return false;
}

template<class T>
bool Matrix<T>::findUp(T toFind, int sR, int sC, int &posR, int &posC){
	if(sR > row - 1|| sC > col - 1) return false;
	for(int i = sR; i >= 0; i--){
		if(toFind == data[i][sC]){
			posR = i;
			posC = sC;
			return true;
		}
	}
	return false;
}

template<class T>
bool Matrix<T>::findDown(T toFind, int sR, int sC, int &posR, int &posC){
	if(sR > row - 1|| sC > col - 1) return false;	
	for(int i = sR; i < row; i++){
		if(toFind == data[i][sC]){
			posR = i;
			posC = sC;
			return true;
		}
	}
	return false;
}

template<class T>
bool Matrix<T>::findLeft(T toFind, int sR, int sC, int &posR, int &posC){
	if(sR > row - 1|| sC > col - 1) return false;	
	for(int i = sC; i >= 0; i--){
		if(toFind == data[sR][i]){
			posR = sR;
			posC = i;
			return true;
		}
	}
	return false;
}

template<class T>
bool Matrix<T>::findRight(T toFind, int sR, int sC, int &posR, int &posC){
	if(sR > row - 1|| sC > col - 1) return false;	
	for(int i = sC; i < col; i++){
		if(toFind == data[sR][i]){
			posR = sR;
			posC = i;
			return true;
		}
	}
	return false;
}

template<class T>
Matrix<T>::~Matrix(){
	for(int i = 0; i < row; i++){
		delete data[i];
	}
	
	delete data;
}

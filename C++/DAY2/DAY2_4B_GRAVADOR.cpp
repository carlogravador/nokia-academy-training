#include<iostream>

using std::cout;
using std::cin;
using std::endl;


void printSpaces(int i, int space, int rows){
	
	if(space > rows - i){
		return;
	}
	cout << "  ";
	printSpaces(i, space + 1, rows);
}

void printStar(int i, int k){
	if(k == (2 * i) - 1){
		cout << endl;
		return;
	}
	cout << "* ";
	printStar(i, k + 1);
}

void printPyramid(int i, int k, int rows){
	
	if(i > rows){
		return;
	}
	
	printSpaces(i, 1, rows);
	printStar(i, k);
	printPyramid(i + 1, k, rows);
	
}

int main(void){
	
	int rows;
	int sentinel;
	
	
	while(1){
		
		cout << "Enter number of rows: ";
		cin >> rows;
		
		printPyramid(1, 0, rows);
		
		cout << endl;
		cout << "Press -1 to exit: ";
		cin >> sentinel;
		cin.ignore();
		if(sentinel == -1){
			break;
		}
	}	
	
	return 0;
}

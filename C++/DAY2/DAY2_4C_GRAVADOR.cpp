#include<iostream>

using std::cout;
using std::cin;
using std::endl;

void printNumbers(int i, int k, int rows, int *count, int *count1){
	if(k == (2 * i) - 1){
		return;
	}
	
	if(*count <= rows - 1){
		cout << i + k << " ";
		++*count;
	} else {
		++*count1;
		cout << i + k - 2 * *count1 << " ";
	}
	printNumbers(i, k + 1, rows, count, count1);
}

void printSpaces(int i, int space, int rows, int *count){
	if(space > rows - i){
		return;
	}
	cout << "  "; 
	++*count;
	printSpaces(i, space + 1, rows, count);
}

void printPyramid(int i, int rows){
	int count = 0, count1 = 0;
	if(i > rows){
		return;
	}
	printSpaces(i, 1, rows, &count);	
	printNumbers(i, 0, rows, &count, &count1);
	cout << endl;
	printPyramid(i + 1, rows);
}


int main(void){
	
	int rows;
	int sentinel;
	
	while(1){
		
		cout << "Enter number of rows: ";
		cin >> rows;
		
    		printPyramid(1, rows);
		
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

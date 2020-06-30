#include<iostream>

using std::cout;
using std::cin;
using std::endl;


void recurse(int i, int j){
	if(i >= 1){
		if(j <= i ){
			cout << j << " ";
			recurse(i, j + 1);
		} else {
			cout << endl;
			recurse(i - 1, 1);
		}
	}
}

int main(void){
	
	int rows;
	int sentinel;
		
	while(1){
		
		cout << "Enter rows: ";
		cin >> rows;
		
		recurse(rows, 1);
				
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

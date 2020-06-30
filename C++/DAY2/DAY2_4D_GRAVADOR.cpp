#include<iostream>

using std::cout;
using std::cin;
using std::endl;

void recurse(int i, int j, int rows, int *number){
	if(i <= rows){
		if(j <= i){
			cout << *number << " ";
			++*number;
			recurse(i, j + 1, rows, number);
		} else {
			cout << endl;
			recurse(i + 1, 1, rows, number);
		}
	}
}



int main(void){
	
	int rows, number = 1;
	int sentinel;
	
	while(1){
		
		cout << "Enter number of rows: ";
		cin >> rows;
		    		
    		number = 1;
    		recurse(1, 1, rows, &number);
		
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

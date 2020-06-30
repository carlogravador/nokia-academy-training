//number of 0's'

#include<iostream>


using std::cout;
using std::cin;
using std::endl;



int main(void){

	int input;
	int appearance = 0;
	
	while(1){
		cout << "Enter an integer: ";
		cin >> input;
	
		while(input > 0) {
			if(input % 10 == 0) {
				appearance++;
			}
			input /= 10;
		}
	
		cout << "Number of 0's: " << appearance << endl;
		
		cout << "Input -1 to exit: ";
		cin >> input;
		
		if(input == -1){
			break;
		}
	}
	
	cout << "The program will exit\n";
	
	return 0;
}

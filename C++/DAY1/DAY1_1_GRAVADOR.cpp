//factorial

#include<iostream>


using std::cout;
using std::cin;
using std::endl;

int main(void){

	int input;
	int factorial = 1;

	while(1){
		cout << "Solving for factorial. Input integer (0 - 12): ";
		cin >> input;
		
		if(input > 12) {
			cout << "Invalid input\n";
			continue;
		}
	
		while(input > 0){
			factorial *= input;
			input--;
		}
	
		cout << "The factorial is " << factorial << endl;
		
		cout << "Input -1 to exit: ";
		cin >> input;
		if(input == -1){
			break;
		}
	}
	cout << "The program will exit\n";
	
	return 0;
}

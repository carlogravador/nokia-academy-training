//number of trailing 0's'

#include<iostream>


using std::cout;
using std::cin;
using std::endl;



int main(void){
	int i;
	int power = 1;
	int ctr = 1;
	int input, copy;
	int appearance = 0;
	
	
	while(1) {
		cout << "Enter an integer: ";
		cin >> input;
		copy = input;
		
		ctr = 1;
		appearance = 0;
		
		while(1){
			input = copy;
			power = 1;
			
			//power function
			for(i = 1; i <= ctr; i++){
				power *= 5;
			}
			
			//trailing 0 in factorial is dependent on the power of 5;
			appearance += (input / power);		
			input /= power;
			if(input == 0) {	//means power is greater than input
				break;
			}
			ctr++;
		}
	
		cout << "Number of trailing 0's in the factorial: " << appearance << endl;
		
		cout << "Input -1 to exit: ";
		cin >> input;
		
		if(input == -1){
			break;
		}
	}
	
	cout << "The program will exit\n";
	
	return 0;
}

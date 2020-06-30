//power of 7

#include<iostream>


using std::cout;
using std::cin;
using std::endl;



int main(void){

	int input;

	while(1){
		cout << "Enter an integer: ";
		cin >> input;
	
		//all power of 7 is divisible by 7;
		if(input % 7 == 0) {
			cout << "YES\n";	
		} else {
		 	cout << "NO\n";
		}
		
		cout << "Input -1 to exit: ";
		cin >> input;
		if(input == -1){
			break;
		}
	}
	
	cout << "The program will exit\n";
	

	return 0;
}

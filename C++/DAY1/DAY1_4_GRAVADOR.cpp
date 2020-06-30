//smalles sum of factors

#include<iostream>


using std::cout;
using std::cin;
using std::endl;



int main(void){

	int input;
	int i;
	int div;
	int sum;
	int temp;

	while(1){
		cout << "Enter an integer: ";
		cin >> input;
		
		temp = input + 2;	//initial value;
	
		for(i = 1; i <= input; i++){
			if(input % i == 0){		//they are divisible
				div = input / i;	
				sum = div + i;
				if(sum < temp){
					temp = sum;
				}
			}	
		}
		
		cout << "The smallest sum is " << temp << endl;
		
		cout << "Input -1 to exit: ";
		cin >> input;
		if(input == -1){
			break;
		}
	}
	
	cout << "The program will exit\n";	

	return 0;
}

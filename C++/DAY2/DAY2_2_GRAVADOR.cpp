#include<iostream>

using std::cout;
using std::cin;
using std::endl;




int main(void){
	
	int sentinel;
	int size;
	int subArraySize;
	int ctr = 0;
	int i, j, k;
	int highest = 0, product = 1;
	
	
	while(1){
		//work here
		
		highest = 0;

		cout << "Enter array size: ";
		cin >> size;
				
		int array[size];
		int subArray[size];
		int highestSubArray[size];
		
		cout << "Enter array elemnts\n";
		//for input		
		for(i = 0; i < size; i++){
			cout << "array[" << i << "]: ";
			cin >> array[i]; 			
		}
		
		for(i = 0; i < size; i++){
			for(j = 0; j < size; j++){
				ctr = 0;
				product = 1;
				for(k = i; k <= j; k++){
					product *= array[k];
					subArray[ctr] = array[k];
					ctr++;
				}
				if(highest <= product){
					highest = product;
					for(k = 0; k < ctr; k++){
						highestSubArray[k] = subArray[k]; 	//store if its the highest
					}
					subArraySize = ctr;
				}
			}	
		}
		
		cout << "The product of the sub array: ";
		for(i = 0; i < subArraySize; i++){
			cout << highestSubArray[i] << ", ";
		}
		cout << "is " << highest << endl;
		
		
		//sentinel
		cout << "Press -1 to exit: ";
		cin >> sentinel;
		cin.ignore();
		if(sentinel == -1){
			break;
		}
	}	
	
	
	return 0;
}

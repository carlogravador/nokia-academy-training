#include<iostream>
#include<cstring>

using std::cout;
using std::cin;
using std::endl;


int main(void){
	
	char input[256];
	int i, j, len;
	int appearance = 0;
	int sentinel;
	
	
	while(1){
		//work here
		cout << "Enter a string: ";
		cin.getline(input, 256, '\n');
	
		len = strlen(input);
		cout << "Unique characters: ";
		
		for(i = 0; i < len; i++){
			appearance = 0;
			for(j = 1; j < len; j++){
				if(input[i] == input[j]){
					appearance++;
					if(appearance == 2) break;
				}
			}
		
			if(appearance < 2){
				cout << input[i];	
			}
		}
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

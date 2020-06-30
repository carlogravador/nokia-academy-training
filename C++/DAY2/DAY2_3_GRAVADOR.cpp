#include<iostream>
#include<cstring>

using std::cout;
using std::cin;
using std::endl;

void printUniqueCharacters(const char s1[], const char s2[]){
	int i, j, len1, len2;
	bool isFound;
	
	len1 = strlen(s1);
	len2 = strlen(s2);
		
	for(i = 0; i < len1; i++){
		isFound = false;
		for(j = 0; j < len2; j++){
			if(s1[i] == s2[j]){
				isFound = true;
				if(isFound) break;
			}
		}
		if(!isFound) cout << s1[i];
	}
	
}
int main(void){
	
	char s1[256];
	char s2[256];
	
	
	int sentinel;
	
	
	while(1){
		
		cout << "Enter string1: ";
		cin.getline(s1, 256, '\n');
		
		cout << "Enter string1: ";
		cin.getline(s2, 256, '\n');
	
		cout << "Unique Characters: ";
		printUniqueCharacters(s1, s2);
		printUniqueCharacters(s2,s1);	
				
		cout << "\nPress -1 to exit: ";
		cin >> sentinel;
		cin.ignore();
		if(sentinel == -1){
			break;
		}
	}	
	
	return 0;
}

//ME05_4.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int is_palindrome(char *w){
	int start = 0;
	int end = strlen(w) - 1;
	int i = end / 2;
	int ok = 1;
	
	while(i >= 0){
		if(toupper(*(w + start)) != toupper(*(w + end))){
			ok = 0;
			break;
		}
		start++;
		end--;
		i--;
	}

	return ok;
}

int main(void){

	char *words;
	int palindrome;
	int pos;
	words = (char*) malloc(sizeof(char) * 12);
	
	printf("Enter a word: ");
	fgets(words, 12, stdin);
	pos = strlen(words) - 1;
	
	*(words + pos) = '\0';
	

	
	palindrome = is_palindrome(words);
	if(palindrome){
		printf("%s is a palindrome\n", words);
	}else{
		printf("%s is not palindrome\n", words);
	}

	free(words);
	

	return 0;
}

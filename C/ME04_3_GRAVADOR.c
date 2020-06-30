//ME04_2.c
//pointers

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void reverse(char *w){
	char swapper;
	int start = 0;
	int end = strlen(w) - 2;
	int i = end / 2;

	while(i >= 0){
		//swap
		swapper = *(w + start);
		*(w + start) = *(w + end);
		*(w + end) = swapper;	
		start++;
		end--;
		i--;
	}
}


int main(void){
	
	char *words;
	words = (char*) malloc(sizeof(char) * 12);
	
	printf("Enter a word: ");
	fgets(words, 12, stdin);

	
	//printf("Size of word = %d", strlen(words));
	reverse(words);
	printf("Reverse word: %s \n", words);

	free(words);
	return 0;
}

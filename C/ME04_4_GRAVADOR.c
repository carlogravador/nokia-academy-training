//ME04_2.c
//pointers

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void replace_char(char *word, char c, int pos){
	*(word + pos - 1) = c;
}

int main(void){
	
	int input;
	char ch;
	char *words;

	words = (char*) malloc(sizeof(char) * 12);
		
	

	printf("Enter a string: ");
	fgets(words, 12, stdin);

	do{
		printf("Enter an integer from 1 - 10: ");
		scanf("%d", &input);
		printf("Enter a character: ");
		scanf("%c", &ch);
		if(ch == '\n'){
			scanf("%c", &ch);
		}


		replace_char(words, ch, input);
		printf("Modified string: %s\n", words);
		
	} while(input > 0 && input < 11);

	free(words);	

	return 0;
}

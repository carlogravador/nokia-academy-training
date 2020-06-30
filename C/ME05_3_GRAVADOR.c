//ME05_3.c

#include<stdio.h>
#include<stdlib.h>

#define LENGTH 52

//function to get length of input string
int get_length(char *p_w){
	int i = 0;
	while(*(p_w + i) != '\n'){
		i++;
	}
	return i;
}

//function to check if word is too long
int is_too_long(char *p_w){
	int size = get_length(p_w);
	if(*(p_w + 50) != '\n'  && size > LENGTH) return 1;
	return 0;
}

//check appearance of char in string
int count_appearance(char *p_w, char c){
	int ans = 0;
	int size = get_length(p_w);
	while(size > 0){
		size--;
		if(*(p_w + size) == c){
			ans++;	
		}
	}
	return ans;
}


int main(void){

	char *p_word;
	char c;
	int appearance;

	p_word = (char*) malloc(LENGTH * sizeof(char));

	//input	
	printf("Enter a string: ");
	fgets(p_word, LENGTH, stdin);

	if(is_too_long(p_word)) {
		printf("Word is too long for me.\n");
	} else {
		printf("Check count of this character: ");
		scanf("%c", &c);
		appearance = count_appearance(p_word, c);
		printf("%c appears %d times in %s\n", c, appearance, p_word);
	}
	
	free(p_word);
	return 0;
}

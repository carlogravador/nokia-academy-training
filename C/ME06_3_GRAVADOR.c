//ME06_3.c
#include<stdio.h>
#include<stdlib.h>

#define LENGTH 22

int main(int argc, char *argv[]){
	
	FILE *file;
	char *input;
	int input_ctr;
	int i;

	input = (char*) malloc(sizeof(char) * LENGTH);

	//check command line arguements
	if(argc != 3 ){
		printf("Use Comand Line Arugments with the format“./<program_name> <output_file><number_of_lines>”\n");
		return 1;
	}
	//open file
	file = fopen(argv[1], "w");	
	if(file == NULL){
		printf("Error writing to %s\n", argv[1]);
		return 0;
	}

	input_ctr = atoi(argv[2]);
	for(i = 0; i < input_ctr; i++){
		printf("Enter a word: " );
		scanf("%s", input);
		fprintf(file, "%s\n", input);
		
	}
	
	free(input);
	fclose(file);

	return 0;
}

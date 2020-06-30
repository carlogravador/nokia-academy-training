
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int get_file_size(FILE *f){
	int size = 0;
	while(!feof(f)){
		fgetc(f);
		size++;
	}
	rewind(f);
	return size;
}

int get_count(char *word, int size){
	int count = 0;
	int i;
	for(i = 0; i < size; i++){
		if(*(word + i) == ' ' || *(word + i) == '\n' || *(word + i) == '\t')
		{
			count++;
		}
	}
	return count;
}


int main(int argc, char *argv[]){
	//variables
	FILE *file;
	char *p_fname;
	char *p_sentence;
	int fsize;
	int count;

	//check command line arguements
	if(argc != 2 ){
		printf("Use Comand Line Arugments with the format“./<program_name> <input_file>”\n");
		return 1;
	}


	//malloc	
	p_fname = (char*) malloc(21 * sizeof(char));
	//get file name

	strcpy(p_fname,*(argv + 1));	
	//open and check the file	
	file = fopen(p_fname, "r");
	if(file == NULL){
		printf("Error: %s does not exist", p_fname);
		return 0;
	}

	//malloc size for word
	fsize = get_file_size(file);
	p_sentence = (char*) malloc(fsize * sizeof(char));

	//read text file and put to p_sentence
	fread(p_sentence, fsize, 1, file);
	count = get_count(p_sentence, fsize);
	
	printf("%s", p_sentence);
	printf("It has %d word/s.\n", count);

	
	free(p_fname);
	free(p_sentence);
	fclose(file);	
	return 0;
}
